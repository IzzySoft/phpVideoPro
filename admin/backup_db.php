<?php
 #############################################################################
 # phpVideoPro                              (c) 2001,2002 by Itzchak Rehberg #
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

 $t = new Template($pvp->tpl_dir);

 $t->set_file(array("template"=>"backup_db.tpl"));
 $t->set_block("template","itemblock","item");
 $t->set_var("listtitle",lang("backup_db"));

 if ($backup) {
   header("content-type: application/octet-stream");
   header("Content-Disposition: attachment; filename=pvp-backup.sql");
   echo "######################################\n"
      . "# Backup created by phpVideoPro v$version\n"
      . "######################################\n\n";
   switch ($btype) {
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
     echo "#\n\n# table '$name'\n#\n";
     if ($purge) echo "DELETE FROM $name;\n";
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
       echo "INSERT INTO $name ($fields) VALUES ($cols);\n";
     }
   }
   exit;
 } else {
   #===============================================[ initial hints & form ]===
   $t->set_var("title",lang("intro"));
   $t->set_var("details",lang("desc_backup_db"));
   $t->parse("item","itemblock");
   $t->set_var("title",lang("preferences"));
   $radio = "<INPUT TYPE='radio' NAME='btype' VALUE='all' CHECKED>".lang("backup_db_complete")."<BR>"
          . "<INPUT TYPE='radio' NAME='btype' VALUE='movies'>".lang("backup_db_movies")."<BR>"
          . "<INPUT TYPE='radio' NAME='btype' VALUE='moviedel'>".lang("backup_db_moviedel")."<BR>";
   $t->set_var("details",$radio);
   $t->parse("item","itemblock",TRUE);
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