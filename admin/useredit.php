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

 $page_id = "admin_useredit";
 include("../inc/includes.inc");
 if (!$pvp->auth->admin) kickoff();

 $t = new Template($pvp->tpl_dir);

 #==================================================[ update user account ]===
 if ($update) {
   $user->id     = $id;
   $user->login  = $login;
   $user->comment= $comment;
   $access = array("admin","browse","add","upd","del");
   foreach ($access as $value) {
     if (${$value}) { $user->$value = "1"; } else { $user->$value = "0"; }
   }
   $pwd_ok = 1;
   if ( isset($pwd1) || isset($pwd2) ) {
     if ($pwd1 == $pwd2) {
       $user->pwd = $pwd1;
     } else {
       $pwd_ok = 0;
       $save_result = $colors["err"] . lang("password_nomatch") . "</Font><BR>\n";
     }
   }
   if ( $db->set_user($user) ) {
     $save_result = $colors["ok"] . lang("update_success") . ".</Font><BR>\n";
   } else {
     $save_result = $colors["err"] . lang("user_update_failed",$id) . "</Font><BR>\n";
   }
 #=================================================[ add new user account ]===
 } elseif ($adduser) {
   $user->id     = $id;
   $user->login  = $login;
   $user->comment= $comment;
   $access = array("admin","browse","add","upd","del");
   foreach ($access as $value) {
     if (${$value}) { $user->$value = "1"; } else { $user->$value = "0"; }
   }
   $pwd_ok = 1;
   if ( isset($pwd1) || isset($pwd2) ) {
     if ($pwd1 == $pwd2) {
       $user->pwd = $pwd1;
     } else {
       $pwd_ok = 0;
       $save_result = $colors["err"] . lang("password_nomatch") . "</Font><BR>\n";
     }
   }
   if ( $pwd_ok && $db->add_user($user) ) {
     $save_result = $colors["ok"] . lang("create_success") . ".</Font><BR>\n";
   } else {
     $save_result .= $colors["err"] . lang("user_update_failed","#") . "</Font><BR>\n";
   }
 #==================================================[ delete user account ]===
 } elseif ($delete) {
   $user = $db->get_users($delete);
   if ($confirmed) {
     if ( $db->del_user($delete) ) {
       $save_result = $colors["ok"] . lang("user_deleted",$delete,$user->login,$user->comment) . ".</Font><BR>\n";
     } else {
       $save_result = $colors["err"] . lang("user_delete_failed",$delete,$user->login,$user->comment) . "</Font><BR>\n";
     }
     $t->set_file(array("template"=>"delete.tpl"));
     $t->set_var("listtitle",lang("user_delete_report"));
     $t->set_var("details",$save_result);
     include("../inc/header.inc");
     $t->pparse("out","template");
     exit;
   } else {
     $t->set_file(array("template"=>"admin_userdelete.tpl"));
     $t->set_var("listtitle",lang("confirm_userdelete",$delete));
     $t->set_var("formtarget",$PHP_SELF);
     $t->set_var("delete",$delete);
     $t->set_var("yes",lang("yes"));
     $t->set_var("no",lang("no"));
     $t->set_var("delete_yn",$colors["err"].lang("confirm_userdeletion",$user->login,$user->comment)."</FONT>");
     include("../inc/header.inc");
     $t->pparse("out","template");
     exit;
   }
 }

 #=====================================================[ build input form ]===
 $t->set_file(array("template"=>"admin_useredit.tpl"));

 $users = $db->get_users($id);
 $t->set_var("user_id","<INPUT TYPE='hidden' NAME='id' VALUE='$id'>$id");
 $t->set_var("login","<INPUT NAME='login' VALUE='".$users->login."'>");
 $t->set_var("comment","<INPUT NAME='comment' VALUE='".$users->comment."'>");
 $t->set_var("browse",$pvp->common->make_checkbox("browse",$users->browse));
 $t->set_var("add",$pvp->common->make_checkbox("add",$users->add));
 $t->set_var("upd",$pvp->common->make_checkbox("upd",$users->upd));
 $t->set_var("del",$pvp->common->make_checkbox("del",$users->del));
 $t->set_var("isadmin",$pvp->common->make_checkbox("admin",$users->admin));
 $t->set_var("password","<INPUT TYPE='password' NAME='pwd1' MAXLENGTH='10'>");
 $t->set_var("password2","<INPUT TYPE='password' NAME='pwd2' MAXLENGTH='10'>");

 $t->set_var("listtitle",lang("admin_useredit"));
 $t->set_var("formtarget",$PHP_SELF);
 $t->set_var("update","<INPUT TYPE='submit' NAME='update' VALUE='".lang("update")."'>");
 $t->set_var("adduser","<INPUT TYPE='submit' NAME='adduser' VALUE='".lang("add_user")."'>");
 $t->set_var("save_result",$save_result);
 $t->set_var("head_users",lang("user"));
 $t->set_var("head_access",lang("data_access"));
 $t->set_var("head_admin",lang("admin"));
 $t->set_var("head_actions",lang("actions"));
 $t->set_var("head_id","ID");
 $t->set_var("head_login",lang("login"));
 $t->set_var("head_comment",lang("comments"));
 $t->set_var("head_browse",lang("read_access"));
 $t->set_var("head_add",lang("add_access"));
 $t->set_var("head_upd",lang("upd_access"));
 $t->set_var("head_del",lang("del_access"));
 $t->set_var("head_isadmin",lang("admin_access"));
 $t->set_var("head_password",lang("password"));
 $t->set_var("head_password2",lang("password_retype"));
 include("../inc/header.inc");
 $t->pparse("out","template");

 include("../inc/footer.inc");
?>