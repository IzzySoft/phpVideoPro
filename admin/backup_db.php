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
 include("inc/includes.inc");
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

 $t = new Template($pvp->tpl_dir);

 $t->set_file(array("template"=>"backup_db.tpl"));
 $t->set_block("template","itemblock","item");
 $t->set_block("itemblock","settingsblock","settings");
 $t->set_block("itemblock","descblock","desc");
 $t->set_var("listtitle",lang("backup_db"));

 if ($backup) {
   if ($btype=="removieint") die(lang("not_yet_implemented"));
   if ($btype=="movieint") {
     $mlist  = $db->get_movie();
     $mcount = count($mlist);
     fhead("movies.pvp");
     fout("PVP Movie Backup: [$mcount] records");
     for ($i=0;$i<$mcount;++$i) {
       fout( serialize($mlist[$i]) );
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
   #===============================================[ initial hints & form ]===
   $t->set_var("title",lang("intro"));
   $t->set_var("details",lang("desc_backup_db"));
   $t->set_var("settings","");
   $t->parse("desc","descblock");
   $t->parse("item","itemblock");
   $t->set_var("title",lang("preferences"));
   $space = str_replace($base_path,$base_url,$pvp->tpl_dir)."/images/blank.gif";
   $radio = "<INPUT TYPE='radio' NAME='btype' VALUE='all' CHECKED>".lang("backup_db_complete")."<BR>"
          . "<INPUT TYPE='radio' NAME='btype' VALUE='movies'>".lang("backup_db_movies")."<BR>"
          . "<INPUT TYPE='radio' NAME='btype' VALUE='moviedel'>".lang("backup_db_moviedel")."<BR>"
          . "<INPUT TYPE='radio' NAME='btype' VALUE='movieint'>".lang("backup_db_movie_internal")."<BR>"
          . "<IMG WIDTH='20' BORDER='0' SRC='$space'><INPUT TYPE='checkbox' NAME='compress' VALUE='1' CLASS='checkbox'>".lang("backup_compress")."<BR>";
   $t->set_var("dleft",$radio);
   $t->set_var("desc","");
   $radio = "<INPUT TYPE='radio' NAME='btype' VALUE='removieint'>".lang("restore_db_movie_internal");
   $t->set_var("dright",$radio);
   $t->set_var("hleft",lang("backup"));
   $t->set_var("hright",lang("restore"));
   $t->parse("settings","settingsblock");
   $t->parse("item","itemblock",TRUE);
   $t->set_var("settings","");
   $t->set_var("title",lang("backup_db_runscript"));
   $t->set_var("details","");
   $t->parse("item","itemblock",TRUE);
   $t->set_var("button","<INPUT TYPE='submit' NAME='backup' VALUE='".lang("yes")."'>");
   $t->set_var("formtarget",$PHP_SELF);
   if (!$pvp->config->enable_cookies) $t->set_var("hidden","<INPUT TYPE='hidden' NAME='sess_id' VALUE='$sess_id'>");
   include("../inc/header.inc");
   $t->pparse("out","template");
 }

 include("../inc/footer.inc");
?>