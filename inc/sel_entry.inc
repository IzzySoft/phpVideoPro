<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # select form for single entry direct addressing                            #
 #############################################################################

 /* $Id$ */

 #======================[ if the form was submitted, redirect to edit.php ]===
 if ($sel_entry && $mtype_id && $cass_id && $part) {
   $nr       = $cass_id;
   while (strlen($nr)<4) { $nr = "0" . $nr; }
   $nr      .= "-";
   if (strlen($part)<2) {
     $nr .= "0" . $part;
   } else { $nr .= $part; }
?>
<HTML><HEAD>
  <meta http-equiv="refresh" content="0; URL=<?="edit.php?mtype_id=$mtype_id&cass_id=$cass_id&part=$part&nr=$nr"?>">
</HEAD></HTML>
<?
   exit;
 }

 include("inc/includes.inc");
 include("inc/header.inc");

 if ($sess_id) {
   $login_info = lang("logout_user",$pvp->auth->user->login,$base_url."login.php?logout=1");
 } else {
   $login_info = "<A HREF='".$base_url."login.php'>".lang("login")."</A>";
 }
  
 #=================================================[ build the input form ]===
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("list"=>"select_entry.tpl"));
 $t->set_var("login_info",$login_info);
 $t->set_var("form_target",$PHP_SELF);
 $t->set_var("goto_entry",lang("goto_entry"));
 $t->set_var("mtype",lang("mediatype"));
 $t->set_var("cass_id",lang("medianr"));
 $t->set_var("add_part",$form["addon_part"]);
 $t->set_var("add_cass",$form["addon_cass_id"]);
 $sel_mtype = "<SELECT NAME=\"mtype_id\">";
 $mtypes = $db->get_mtypes();
 for ($i=0;$i<count($mtypes);$i++) {
   $sel_mtype .= "<OPTION VALUE=\"" . $mtypes[$i][id] . "\">" . $mtypes[$i][sname] . "</OPTION>";
 }
 $sel_mtype .= "</SELECT>";
 $t->set_var("sel_mtype",$sel_mtype);
 $t->set_var("display",lang("display"));
 $t->pparse("out","list");
?>