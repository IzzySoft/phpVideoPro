<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Administration: Backup the DataBase                                       #
 #############################################################################

 /* $Id$ */

 $page_id = "backup_db";
 if ($backup) $silent = 1;
 include(dirname(__FILE__) . "/../inc/includes.inc");
 if (!$pvp->auth->admin) kickoff();

 function fhead($filename) {
   header("content-type: application/octet-stream");
   header("Content-Disposition: attachment; filename=$filename");
 }

 function fout($str) {
   GLOBAL $compress,$out;
   $str .= "\n";
   if ($compress) { $out .= $str; }
   else { echo $str; }
 }

 function mkavlang($avl) {
   $lc = count($avl);
   for ($i=0;$i<$lc;++$i) {
     $lang[] = $avl[$i]->id;
   }
   return $lang;
 }

 $t = new Template($pvp->tpl_dir);

 $t->set_file(array("template"=>"backup_db.tpl"));
 $t->set_block("template","itemblock","item");
 $t->set_block("itemblock","settingsblock","settings");
 $t->set_block("itemblock","descblock","desc");
 $t->set_var("listtitle",lang("backup_db"));

 #=======================================================[ run the backup ]===
 if ($backup) {
   if ($btype=="movieint") {
     $mlist  = $db->get_movieids_all();
     $mcount = count($mlist);
     fhead("movies_".date('ymd').".pvp");
     fout("PVP Movie Backup: [$mcount] records");
     for ($i=0;$i<$mcount;++$i) {
       $movie = $db->get_movie($mlist[$i]);
       fout( urlencode(serialize($movie)) );
     }
     if ($compress) echo gzencode($out);
     exit;
   }
   if ($compress) { fhead("pvp-backup.sql.gz"); }
   else { fhead("pvp-backup.sql"); }
   fout("######################################");
   fout("# Backup created by phpVideoPro v$version");
   fout("######################################");
   switch ($btype) {
     case "movieint" : $tables = array(); break;
     case "moviedel" : $purge = TRUE;
     case "movies"   :
       $tabs = array("video","cass","music","directors","actors");
       foreach ($tabs as $val) {
         $tables[]["table_name"] = $val;
       }
       break;
     default         :
       $tables = $db->table_names();
   }
   $tablecount = count($tables);
   for ($i=0;$i<$tablecount;++$i) {
     $name = $tables[$i]["table_name"];
     $meta = $db->metadata($name);
     $db->dbquery("SELECT * FROM $name");
     fout("\n#\n# table '$name'\n#");
     if ($purge) fout("DELETE FROM $name;");
     while ( $db->next_record() ) {
       $fieldcount = count($meta);
       $fields = $cols = "";
       for ($k=0;$k<$fieldcount;++$k) {
         $field   = $meta[$k]["name"];
	 $col     = "'" . str_replace("'","\'",$db->f("$field")) . "'";
	 $col     = str_replace("\\\'","\'",$col);
#	 $col     = "'" . $db->f("$field") . "'";
	 $fields .= $field;
	 $cols   .= $col;
	 if ( ($fieldcount - $k) > 1 ) {
	   $cols .= ","; $fields .= ",";
	 }
       }
       $cols = str_replace("''","' '",$cols);
       fout("INSERT INTO $name ($fields) VALUES ($cols);");
     }
   }
   if ($compress) echo gzencode($out);
   exit;
 } else {
 #======================================================[ run the restore ]===
   if ($restore) { // restore data
     if (!empty($rfile)) {
       if (file_exists($pvp->backup_dir."/$rfile")) {
         $imp->errors  = 0;
         if (!is_readable($pvp->backup_dir."/$rfile")) {
           $save_result = "<SPAN CLASS='error'>".lang("backup_file_unreadable")."</SPAN>";
           ++$imp->errors;
         } else {
           $data = @file_get_contents($pvp->backup_dir."/$rfile");
           if (substr($data,0,3)!="PVP") {
             if ( !$data = @gzinflate(substr($data,10)) ) {
               $save_result = "<SPAN CLASS='error'>".lang("backup_file_corrupt")."</SPAN>";
               ++$imp->errors;
             }
           }
         }
         if (!$imp->errors) {
           if ($cleandb) $db->drop_all_movies();
           $avl = mkavlang($db->get_avlang("audio"));
           $sub = mkavlang($db->get_avlang("subtitle"));
	   $tcatlist = $db->get_category();
	   $catcount = count($tcatlist);
	   for ($i=0;$i<$catcount;++$i) {
	     $catlist[$tcatlist[$i][internal]] = $tcatlist[$i][id];
	   }
           $data = explode("\n",$data);
           $mcount = count($data);
           $imp->records = $mcount -2;
           for ($i=1;$i<$mcount -1;++$i) {
             $movie = unserialize(urldecode($data[$i]));
             if ($movie[director_id]) $movie[director_id] = $db->check_person($movie[director_][name],$movie[director_][firstname],"directors",TRUE);
             if ($movie[music_id]) $movie[music_id] = $db->check_person($movie[music_][name],$movie[music_][firstname],"music",TRUE);
             for ($k=1;$k<6;++$k) {
               $pset = "actor_$k"; $pid = "actor$k"."_id";
               if ($movie[$pid]) $movie[$pid] = $db->check_person($movie[$pset][name],$movie[$pset][firstname],"actors",TRUE);
             }
	     for ($k=1;$k<4;++$k) { // add new cats if necessary
	       $tcat = "cat$k"."int"; $tcatid = "cat$k"."_id";
               if (!empty($movie[$tcat]) && !$catlist[$movie[$tcat]]>0) {
	         $db->add_category($movie[$tcat]);
		 $db->set_translation($movie[$tcat],$movie["cat$k"],"en");
		 $movie[$tcatid] = $db->get_category_id($movie[$tcat]);
		 $report .= "<li>added category '".$movie[$tcat]."' (".$movie["cat$k"].")";
	       }
	     }
             for ($k=0;$k<count($movie[audio]);++$k) { // check audio_ts
               if ( ($movie[audio][$k]) && !in_array($movie[audio][$k],$avl) ) {
                 $db->set_avlang($movie[audio][$k],1,"audio");
                 $avl[] = $movie[audio][$k];
               }
             }
             for ($k=0;$k<count($movie[subtitle]);++$k) { // check subtitles
               if ( ($movie[subtitle][$k]) && !in_array($movie[subtitle][$k],$sub) ) {
                 $db->set_avlang($movie[subtitle][$k],1,"subtitle");
                 $sub[] = $movie[subtitle][$k];
               }
             }
	     # if (!$cleandb) insert check for the MediaNr HERE *!*
             if (!$db->add_movie($movie)) ++$imp->errors;
           }
           if ($imp->errors) {
             $save_result = "<SPAN CLASS='error'>".lang("imp_errors",$imp->errors,$imp->records)."</SPAN>";
           } else {
             $save_result = "<SPAN CLASS='ok'>".lang("imp_success",$imp->records)."</SPAN>";
           }
         }
       } else {
         $save_result = "<SPAN CLASS='error'>".lang("no_restore_file")."</SPAN>";
       }
     }
   }
   #===============================================[ initial hints & form ]===
   $t->set_var("title",lang("intro"));
   $t->set_var("details",lang("desc_backup_db"));
   $t->set_var("settings","");
   $t->parse("desc","descblock");
   $t->parse("item","itemblock");
   $t->set_var("title",lang("preferences"));
   $space = str_replace($base_path,$base_url,$pvp->tpl_dir)."/images/blank.gif";
   $radio = "<INPUT TYPE='radio' NAME='btype' VALUE='all' CLASS='checkbox'>".lang("backup_db_complete")."<BR>"
          . "<INPUT TYPE='radio' NAME='btype' VALUE='movieint' CLASS='checkbox' CHECKED>".lang("backup_db_movie_internal")."<BR>"
          . "<IMG WIDTH='20' BORDER='0' SRC='$space'><INPUT TYPE='checkbox' NAME='compress' VALUE='1' CLASS='checkbox'>".lang("backup_compress")."<BR>";
   $t->set_var("dleft",$radio);
   $t->set_var("desc","");
   $radio = "<INPUT TYPE='radio' NAME='rtype' VALUE='removieint' CLASS='checkbox' CHECKED>".lang("restore_db_movie_internal");
   if(is_dir($pvp->backup_dir)) {
     $filelist = $pvp->common->get_filenames($pvp->backup_dir,".pvp");
     if ( $fcount   = count($filelist) ) {
       $select   = "<SELECT NAME='rfile'>";
       for ($i=0;$i<$fcount;++$i) {
         $select .= "<OPTION NAME='".$filelist[$i]."'>".$filelist[$i]."</OPTION>";
       }
       $select .= "</SELECT><BR>"
          . "<IMG WIDTH='20' BORDER='0' SRC='$space'><INPUT TYPE='checkbox' NAME='cleandb' VALUE='1' CLASS='checkbox' CHECKED>".lang("clean_restore")."<BR>";
     } else {
       $select = lang("no_backup_avail");
     }
   } else {
     $select = lang("invalid_backup_dir");
   }
   $t->set_var("dright",$radio."<IMG WIDTH='10' BORDER='0' SRC='$space'>".$select);
   $haction = "<INPUT TYPE='submit' CLASS='submit' NAME='backup' VALUE='".lang("button_backup")."'>";
   $t->set_var("hleft",$haction);
   $haction = "<INPUT TYPE='submit' CLASS='submit' NAME='restore' VALUE='".lang("button_restore")."'>";
   $t->set_var("hright",$haction);
   $t->parse("settings","settingsblock");
   $t->parse("item","itemblock",TRUE);
   $t->set_var("formtarget",$PHP_SELF);
   $t->set_var("save_result",$save_result);
   if (!$pvp->config->enable_cookies) $t->set_var("hidden","<INPUT TYPE='hidden' NAME='sess_id' VALUE='$sess_id'>");
   include("../inc/header.inc");
   $t->pparse("out","template");
 }

 include("../inc/footer.inc");
?>