<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Administration: User Access Management                                    #
 #############################################################################

 /* $Id$ */

 #========================================================[ initial setup ]==
 $page_id = "admin_users";
 include("../inc/includes.inc");

 #-------------------------------------------------[ Register global vars ]---
 $lines = $_POST["lines"];

 #--------------------------------------------------[ Check authorization ]---
 if (!$pvp->auth->admin) kickoff();

 #==================================================[ process the changes ]===
 if ($_POST["update"]) {
   for ($i=0;$i<$lines;++$i) {
     $user->id     = $_POST["user_".$i];
     $user->login  = $_POST["user_".$i."_login"];
     $user->comment= $_POST["user_".$i."_comment"];
     $access = array("admin","browse","add","upd","del");
     foreach ($access as $value) {
       $var = $value ."_".$user->id;
       if ($_POST[$var]) { $user->$value = "1"; } else { $user->$value = "0"; }
     }
     if ( !$db->set_user($user) ) $error .= ",".$user->id;
   }
   if ($error) {
     $error = substr($error,1);
     $save_result = "<SPAN CLASS='error'>" .lang("user_update_failed",$error) . "</SPAN><BR>\n";
   } else {
     $save_result = "<SPAN CLASS='ok'>" . lang("update_success") . ".</SPAN><BR>\n";
   }
 }

 #=======================================================[ build the form ]===
 include("../inc/header.inc");
?>
<SCRIPT LANGUAGE="JavaScript">
 function delconfirm(url) {
  check = confirm("<?=lang("confirm_delete")?>");
  if (check == true) window.location.href=url;
 }
</SCRIPT>
<?
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"admin_users.tpl"));
 $t->set_block("template","itemblock","item");
 $tpl_dir = str_replace($base_path,$base_url,$pvp->tpl_dir);
 $edit_img  = $tpl_dir . "/images/edit.png";
 $trash_img = $tpl_dir . "/images/trash.png";

 $users = $db->get_users();
 $usercount = count($users);
 for ($i=0;$i<$usercount;++$i) {
   $t->set_var("user_id","<INPUT TYPE='hidden' NAME='user_".$i."' VALUE='".$users[$i]->id."'>".$users[$i]->id);
   $t->set_var("login","<INPUT TYPE='hidden' NAME='user_".$i."_login' VALUE='".$users[$i]->login."'>".$users[$i]->login);
   $t->set_var("comment","<INPUT TYPE='hidden' NAME='user_".$i."_comment' VALUE='".$users[$i]->comment."'>".$users[$i]->comment);
   $t->set_var("browse",$pvp->common->make_checkbox("browse_".$users[$i]->id,$users[$i]->browse));
   $t->set_var("add",$pvp->common->make_checkbox("add_".$users[$i]->id,$users[$i]->add));
   $t->set_var("upd",$pvp->common->make_checkbox("upd_".$users[$i]->id,$users[$i]->upd));
   $t->set_var("del",$pvp->common->make_checkbox("del_".$users[$i]->id,$users[$i]->del));
   $t->set_var("isadmin",$pvp->common->make_checkbox("admin_".$users[$i]->id,$users[$i]->admin));
   $t->set_var("edit",$pvp->link->linkurl("useredit.php?id=".$users[$i]->id,"<IMG SRC='$edit_img' BORDER='0' ALT='".lang("edit")."'>"));
   $url = $pvp->link->slink("useredit.php?delete=".$users[$i]->id);
   $t->set_var("delete","<IMG SRC='$trash_img' BORDER='0' ALT='".lang("delete")."' onClick=\"delconfirm('$url')\">");
   $t->parse("item","itemblock",TRUE);
 }

 $t->set_var("listtitle",lang("admin_users"));
 $t->set_var("formtarget",$_SERVER["PHP_SELF"]);
 $t->set_var("update","<INPUT TYPE='submit' CLASS='submit' NAME='update' VALUE=".lang("update").">");
 $t->set_var("adduser",$pvp->link->linkurl("useredit.php?addnew=1",lang("add_user")));
 $t->set_var("save_result",$save_result);
 $t->set_var("head_users",lang("user"));
 $t->set_var("head_access",lang("data_access"));
 $t->set_var("head_admin",lang("admin"));
 $t->set_var("head_actions",lang("actions"));
 $t->set_var("head_id","ID");
 $t->set_var("head_login",lang("login"));
 $t->set_var("head_comment",lang("comments"));
 $t->set_var("head_browse",lang("read_access_short"));
 $t->set_var("head_add",lang("add_access_short"));
 $t->set_var("head_upd",lang("upd_access_short"));
 $t->set_var("head_del",lang("del_access_short"));
 $t->set_var("head_isadmin",lang("admin_access_short"));
# $t->set_var("head_edit",lang("edit"));
# $t->set_var("head_delete",lang("delete"));
 $hidden = "<INPUT TYPE='hidden' NAME='lines' VALUE='$usercount'>";
 if (!$pvp->config->enable_cookies) $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>";
 $t->set_var("hidden",$hidden);
 $t->pparse("out","template");

 include("../inc/footer.inc");
?>