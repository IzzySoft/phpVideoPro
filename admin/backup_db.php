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
   $tables = $db->table_names();
   $tablecount = count($tables);
   header("content-type: application/octet-stream");
   header("Content-Disposition: attachment; filename=pvp-backup.sql");
   echo "######################################\n"
      . "# Backup created by phpVideoPro v$version\n"
      . "######################################\n\n";
   for ($i=0;$i<$tablecount;++$i) {
     $name = $tables[$i]["table_name"];
     $meta = $db->metadata($name);
     $db->dbquery("SELECT * FROM $name");
     echo "#\n# table '$name'\n#\n\n";
     while ( $db->next_record() ) {
       $fieldcount = count($meta);
       $fields = $cols = "";
       for ($k=0;$k<$fieldcount;++$k) {
         $field   = $meta[$k]["name"];
	 $col     = "'" . str_replace("'","\'",$db->f("$field")) . "'";
	 $col     = str_replace(";",":",$col);
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
   $t->set_var("button","<INPUT TYPE='submit' NAME='backup' VALUE='".lang("yes")."'>");
   $t->set_var("formtarget",$PHP_SELF);
   include("../inc/header.inc");
   $t->pparse("out","template");
 }

 include("../inc/footer.inc");
?>