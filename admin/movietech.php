<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Administration: User Access Management                                    #
 #############################################################################

 /* $Id$ */

 $page_id = "admin_movietech";
 include("../inc/includes.inc");
 if (!$pvp->auth->admin) kickoff();

 #==================================================[ process the changes ]===
 if ($update) {
   if ($error) {
     $error = substr($error,1);
     $save_result = $colors["err"] . lang("user_update_failed",$error) . "</Font><BR>\n";
   } else {
     $save_result = $colors["ok"] . lang("update_success") . ".</Font><BR>\n";
   }
 }

 #=======================================================[ build the form ]===
 #-------------------------------------------------------[ init templates ]---
 $tpl_dir = str_replace($base_path,$base_url,$pvp->tpl_dir);
 $edit_img  = $tpl_dir . "/images/edit.png";
 $trash_img = $tpl_dir . "/images/trash.png";
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"admin_movietech.tpl"));
 $t->set_block("template","mainblock","main");
 $t->set_block("mainblock","screenitemblock","screen");
 $t->set_block("mainblock","coloritemblock","color");
 $t->set_block("mainblock","mtypeitemblock","mtype");
 $t->set_block("template","editblock","edit");

 #---------------------------------------------------------[ screen block ]---
 $picts = $db->get_pict();
 $pictcount = count($picts);
 for ($i=0;$i<$pictcount;++$i) {
   $t->set_var("item_name",$picts[$i][name]);
   $t->set_var("item_sname",$picts[$i][sname]);
   $edit  = $pvp->link->linkurl("$PHP_SELF?type=pict&edit=" .$picts[$i][id],"<IMG SRC='$edit_img' BORDER='0'>");
   $trash = $pvp->link->linkurl("$PHP_SELF?type=pict&delete=" .$picts[$i][id],"<IMG SRC='$trash_img' BORDER='0'>");
   $t->set_var("edit",$edit);
   $t->set_var("trash",$trash);
   $t->parse("screen","screenitemblock",TRUE);
 }
 $t->set_var("screen_title",lang("screen"));
 $t->set_var("screen_add",$pvp->link->linkurl("$PHP_SELF?add=screen",lang("add_entry")));

 #----------------------------------------------------------[ color block ]---
 $colors = $db->get_color();
 $colorcount = count($colors);
 for ($i=0;$i<$colorcount;++$i) {
   $t->set_var("item_name",$colors[$i][name]);
   $t->set_var("item_sname",$colors[$i][sname]);
   $edit  = $pvp->link->linkurl("$PHP_SELF?type=color&edit=" .$colors[$i][id],"<IMG SRC='$edit_img' BORDER='0'>");
   $trash = $pvp->link->linkurl("$PHP_SELF?type=color&delete=" .$colors[$i][id],"<IMG SRC='$trash_img' BORDER='0'>");
   $t->set_var("edit",$edit);
   $t->set_var("trash",$trash);
   $t->parse("color","coloritemblock",TRUE);
 }
 $t->set_var("color_title",lang("picture"));
 $t->set_var("color_add",$pvp->link->linkurl("$PHP_SELF?add=color",lang("add_entry")));

 #---------------------------------------------------------[ mtypes block ]---
 $mtypes = $db->get_mtypes();
 $mtypecount = count($mtypes);
 for ($i=0;$i<$mtypecount;++$i) {
   $t->set_var("item_name",$mtypes[$i][name]);
   $t->set_var("item_sname",$mtypes[$i][sname]);
   $edit  = $pvp->link->linkurl("$PHP_SELF?type=mtype&edit=" .$mtypes[$i][id],"<IMG SRC='$edit_img' BORDER='0'>");
   $trash = $pvp->link->linkurl("$PHP_SELF?type=mtype&delete=" .$mtypes[$i][id],"<IMG SRC='$trash_img' BORDER='0'>");
   $t->set_var("edit",$edit);
   $t->set_var("trash",$trash);
   $t->parse("mtype","mtypeitemblock",TRUE);
 }
 $t->set_var("mtype_title",lang("mediatype"));
 $t->set_var("mtype_add",$pvp->link->linkurl("$PHP_SELF?add=mtype",lang("add_entry")));

 $t->set_var("name",lang("name"));
 $t->set_var("sname",lang("sname"));
 $t->parse("main","mainblock");
 
 $t->set_var("edit",""); # remove editblock
 $t->set_var("listtitle",lang("admin_movietech"));
 $t->set_var("formtarget",$PHP_SELF);
 $t->set_var("save_result",$save_result);

 if (!$pvp->config->enable_cookies) $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='$sess_id'>";
 $t->set_var("hidden",$hidden);
 include("../inc/header.inc");
 $t->pparse("out","template");

 include("../inc/footer.inc");
?>