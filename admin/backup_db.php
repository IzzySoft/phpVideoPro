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
 if ($_POST["backup"]) $silent = 1;
 include(dirname(__FILE__) . "/../inc/includes.inc");
 include("../inc/class.xfer.inc");
 if (!$pvp->auth->admin) kickoff();
 $save_result = "";

 function fhead($filename) {
   header("content-type: application/octet-stream");
   header("Content-Disposition: attachment; filename=$filename");
 }

 function fout($str) {
   GLOBAL $out;
   $str .= "\n";
   if ($_POST["compress"]) { $out .= $str; }
   else { echo $str; }
 }

 $t = new Template($pvp->tpl_dir);

 $t->set_file(array("template"=>"backup_db.tpl"));
 $t->set_block("template","itemblock","item");
 $t->set_block("itemblock","settingsblock","settings");
 $t->set_block("itemblock","descblock","desc");
 $t->set_var("listtitle",lang("backup_db"));

 #=======================================================[ run the backup ]===
 if (isset($_POST["backup"])) {
   $stamp = date('ymd'); // to generate a unique filename
   $xfer = new xfer("export");
   if ($_POST["compress"]) $xfer->compressionOn();
   switch ($_POST["btype"]) {
     case "movieint" : $xfer->fileExport("Movie"); exit; break;
     case "sysconf"  : $xfer->fileExport("SysConf"); exit; break;
     case "cats"     : $xfer->fileExport("Cats"); exit; break;
     default         : break;
   }
 #--------------------------------------[ Complete DB backup (SQL format) ]---
   if ($_POST["compress"]) { fhead("pvp-$stamp.sql.gz"); }
   else { fhead("pvp-$stamp.sql"); }
   fout("######################################");
   fout("# Backup created by phpVideoPro v$version");
   fout("######################################");
   $tables = $db->table_names();
   $tablecount = count($tables);
   for ($i=0;$i<$tablecount;++$i) {
     $name = $tables[$i]["table_name"];
     $meta = $db->metadata($name);
     $db->dbquery("SELECT * FROM $name");
     fout("\n#\n# table '$name'\n#");
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
   if ($_POST["compress"]) echo gzencode($out);
   exit;
 } else {
 #======================================================[ run the restore ]===
   if (isset($_POST["restore"])) { // restore data
     $xfer = new xfer("import");
     if ($_POST["compress"]) $xfer->compressionOn();
     $save_result = $xfer->fileImport($_POST["rfile"],$pvp->backup_dir,!$_POST["cleandb"]);
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
          . "<INPUT TYPE='radio' NAME='btype' VALUE='cats' CLASS='checkbox'>".lang("backup_db_cats")."<BR>"
          . "<INPUT TYPE='radio' NAME='btype' VALUE='sysconf' CLASS='checkbox'>".lang("backup_db_sysconf")."<BR>"
          . "<IMG WIDTH='20' BORDER='0' SRC='$space'><INPUT TYPE='checkbox' NAME='compress' VALUE='1' CLASS='checkbox'";
   if (isset($_POST["compress"])) $radio .= " CHECKED";
   $radio .= ">".lang("backup_compress")."<BR>";
   $t->set_var("dleft",$radio);
   $t->set_var("desc","");
   $radio = "<INPUT TYPE='radio' NAME='rtype' VALUE='removieint' CLASS='checkbox' CHECKED>".lang("restore_db_internal");
   if(is_dir($pvp->backup_dir)) {
     $filelist = $pvp->common->get_filenames($pvp->backup_dir,".pvp");
     asort($filelist); reset($filelist);
     if ( $fcount   = count($filelist) ) {
       $select   = "<SELECT NAME='rfile'>";
       foreach ($filelist as $var) {
         $select .= "<OPTION NAME='$var'>$var</OPTION>";
       }
       $select .= "</SELECT><BR>"
          . "<IMG WIDTH='20' BORDER='0' SRC='$space'><INPUT TYPE='checkbox' NAME='cleandb' VALUE='1' CLASS='checkbox'";
       if (isset($_POST["cleandb"])) $select .= " CHECKED";
       $select .= ">".lang("clean_restore")."<BR>";
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
   $t->set_var("formtarget",$_SERVER["PHP_SELF"]);
   $t->set_var("save_result",$save_result);
   if (!$pvp->cookie->active) $t->set_var("hidden","<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>");
   include("../inc/header.inc");
   $t->pparse("out","template");
 }

 include("../inc/footer.inc");
?>