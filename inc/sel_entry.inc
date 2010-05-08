<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2010 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # select form for single entry direct addressing                            #
 #############################################################################

 /* $Id$ */

 $page_id = "start_page";
 include("inc/includes.inc");
 $details = array("sel_entry","mtype_id","cass_id","part");
 foreach ($details as $var) {
   if ( isset($_REQUEST[$var]) ) $$var = $_REQUEST[$var];
 }

 #======================[ if the form was submitted, redirect to edit.php ]===
 if ( (isset($sel_entry) && $sel_entry) && (isset($mtype_id) && $mtype_id) ) {
   if ($cass_id) {
     if (!$part) {
       header("Location: ".$pvp->link->slink($base_url ."medium.php?mtype_id=$mtype_id&cass_id=$cass_id"));
     } else {
       $nr       = $cass_id;
       while (strlen($nr)<4) { $nr = "0" . $nr; }
       $nr      .= "-";
       if (strlen($part)<2) {
         $nr .= "0" . $part;
       } else { $nr .= $part; }
       header("Location: ".$pvp->link->slink("edit.php?mtype_id=$mtype_id&cass_id=$cass_id&part=$part&nr=$nr"));
     }
   } else {
     header("Location: ".$pvp->link->slink("search.php?submit=1&mtype_id=$mtype_id"));
   }
   exit;
 }

 include("inc/header.inc");

 if ($sess_id && $pvp->session->verify($sess_id)) {
   $login_info = lang("logout_user",$pvp->auth->user->login,$base_url."login.php?logout=1");
 } else {
   $login_info = "<A HREF='".$base_url."login.php'>".lang("login")."</A>";
 }
  
 #=================================================[ build the input form ]===
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("list"=>"select_entry.tpl"));
 $t->set_block("list","introblock","intro");
 $t->set_var("login_info",$login_info);
 $t->set_var("form_target",$_SERVER["PHP_SELF"]);
 $t->set_var("listtitle",lang("welcome")." v$version");
 #----------------------------------------------------[ intro for newbies ]---
 if ( !$pvp->preferences->get("skip_intro") ) {
   $t->set_var("intro_head",lang("intro_usage_title"));
   $intro_text = lang("intro_usage").lang("intro_usage_skip");
   $t->set_var("intro_text",$intro_text);
   $t->parse("intro","introblock");
 }
 #----------------------------------------------------[ "goto_entry" form ]---
 $t->set_var("goto_entry",lang("goto_entry"));
 $t->set_var("mtype",lang("mediatype"));
 $t->set_var("cass_id",lang("medianr"));
 $t->set_var("add_part",$form["addon_part"]);
 $t->set_var("add_cass",$form["addon_cass_id"]);
 $sel_mtype = "<SELECT NAME=\"mtype_id\">";
 $mtypes = $db->get_mtypes();
 for ($i=0;$i<count($mtypes);$i++) {
   $sel_mtype .= "<OPTION VALUE=\"" . $mtypes[$i]['id'] . "\">" . $mtypes[$i]['sname'] . "</OPTION>";
 }
 $sel_mtype .= "</SELECT>";
 if (!$pvp->cookie->active) $sel_mtype .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='$sess_id'>";
 $t->set_var("sel_mtype",$sel_mtype);
 $t->set_var("display",lang("display"));
 $t->pparse("out","list");
?>