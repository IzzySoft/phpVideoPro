<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2009 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
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

 #=============================================[ vulnerability protection ]===
 $vuls = array();
 foreach ($_REQUEST as $var) {
   if ($var != "comment" && $var != "referer" && !$pvp->common->req_is_alnum($var))
     $vuls[] = $var;
 }
 if (!$pvp->common->req_is_num(owner_id)) $vuls[] = "owner_id";
 if (!$pvp->common->req_is_num(from_owner)) $vuls[] = "from_owner";
 if (!$pvp->common->req_is_num(to_owner)) $vuls[] = "to_owner";
 if ($vc = count($vuls)) {
   $msg = lang("input_errors_occured",$vc) . "<UL>\n";
   for ($i=0;$i<$vc;++$i) {
     $msg .= "<LI>Variable ".$vuls[$i]."</LI>\n";
   }
   $msg .= "</UL>";
   $pvp->common->die_error($msg);
 }

 #=======================================================[ setup template ]===
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
     case "movieint" :
       if ($_POST["backup_user"])
         $xfer->fileExport("Movie","",$_POST["owner_id"]);
       else
         $xfer->fileExport("Movie");
       exit;
       break;
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
     if ($_POST["check_owner"]) {
       $from_owner = $_POST["from_owner"];
       $to_owner   = $_POST["to_owner"];
     } else {
       $from_owner = $to_owner = "";
     }
     $save_result = $xfer->fileImport($_POST["rfile"],$pvp->backup_dir,!$_POST["cleandb"],$from_owner,$to_owner);
   }
   #===============================================[ initial hints & form ]===
   $t->set_var("title",lang("intro"));
   $t->set_var("details",lang("desc_backup_db"));
   $t->set_var("settings","");
   $t->parse("desc","descblock");
   $t->parse("item","itemblock");
   $t->set_var("title",lang("preferences"));
   $users = $db->get_users(); $uc = count($users);
   $usel = "<SCRIPT type='text/javascript'>function toggleUserSel() { if (document.backup_db.owner_id.disabled==true) { document.backup_db.owner_id.disabled=false; document.backup_db.owner_id.style.color='#000'; } else { document.backup_db.owner_id.disabled=true; document.backup_db.owner_id.style.color='#999'; } }</SCRIPT><SELECT NAME='owner_id' disabled='disabled' STYLE='color:#999'>";
   for ($i=0;$i<$uc;++$i) $usel .= "<OPTION VALUE='".$users[$i]->id."'>".$users[$i]->login."</OPTION>";
   $usel .= "</SELECT>";
   $space = str_replace($base_path,$base_url,$pvp->tpl_dir)."/images/blank.gif";
   $radio = "<INPUT TYPE='radio' NAME='btype' VALUE='all' CLASS='checkbox'>".lang("backup_db_complete")."<BR>"
          . "<INPUT TYPE='radio' NAME='btype' VALUE='movieint' CLASS='checkbox' CHECKED>".lang("backup_db_movie_internal")."<BR>"
          . "<IMG WIDTH='20' BORDER='0' SRC='$space' ALT=' '><INPUT TYPE='checkbox' NAME='backup_user' VALUE='1' onChange='toggleUserSel();'>".lang('restrict_to_user').":&nbsp;$usel<BR>"
          . "<INPUT TYPE='radio' NAME='btype' VALUE='cats' CLASS='checkbox'>".lang("backup_db_cats")."<BR>"
          . "<INPUT TYPE='radio' NAME='btype' VALUE='sysconf' CLASS='checkbox'>".lang("backup_db_sysconf")."<BR>"
          . "<INPUT TYPE='checkbox' NAME='compress' VALUE='1' CLASS='checkbox'";
   if ( (function_exists('gzencode')&&!isset($_POST["btype"]))||isset($_POST["compress"]) ) $radio .= " CHECKED";
   if ( !function_exists('gzencode') ) $radio .= " DISABLED";
   $radio .= ">".lang("backup_compress")."<BR>";
   $t->set_var("dleft",$radio);
   $t->set_var("desc","");
   $radio = "<INPUT TYPE='radio' NAME='rtype' VALUE='removieint' CLASS='checkbox' CHECKED>".lang("restore_db_internal");
   if(is_dir($pvp->backup_dir)) {
     $filelist = $pvp->common->get_filenames($pvp->backup_dir,".pvp");
     asort($filelist); reset($filelist);
     if ( $fcount   = count($filelist) ) {
       $usel_from = "<SCRIPT type='text/javascript'>function toggleUserSel2() { if (document.backup_db.from_owner.disabled==true) { document.backup_db.from_owner.disabled=false; document.backup_db.from_owner.style.color='#000';document.backup_db.to_owner.disabled=false; document.backup_db.to_owner.style.color='#000'; } else { document.backup_db.from_owner.disabled=true; document.backup_db.from_owner.style.color='#999'; document.backup_db.to_owner.disabled=true; document.backup_db.to_owner.style.color='#999'; } }</SCRIPT><SELECT NAME='from_owner' disabled='disabled' STYLE='color:#999'>";
       $usel_to   = "<SELECT NAME='to_owner' disabled='disabled' STYLE='color:#999'>";
       $usel2 = "<OPTION VALUE=''></OPTION>";
       for ($i=0;$i<$uc;++$i) $usel2 .= "<OPTION VALUE='".$users[$i]->id."'>".$users[$i]->login."</OPTION>";
       $usel_from .= "$usel2</SELECT>";
       $usel_to   .= "$usel2</SELECT>";
       $select   = "<SELECT NAME='rfile'>";
       foreach ($filelist as $var) {
         $select .= "<OPTION VALUE='$var'>$var</OPTION>";
       }
       $select .= "</SELECT><BR>"
          . "<IMG WIDTH='20' BORDER='0' SRC='$space' ALT=' '><INPUT TYPE='checkbox' NAME='check_owner' VALUE='1' onChange='toggleUserSel2();'>".lang('import_from_user').":&nbsp;$usel_from"
	  . "&nbsp;".lang('import_to_user').":&nbsp;$usel_to<BR>"
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
   $t->set_var("lhelp_icon",$pvp->link->linkhelp($page_id."#backup"));
   $haction = "<INPUT TYPE='submit' CLASS='submit' NAME='restore' VALUE='".lang("button_restore")."'>";
   $t->set_var("hright",$haction);
   $t->set_var("rhelp_icon",$pvp->link->linkhelp($page_id."#restore"));
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