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
 $page_id = "admin_useredit";
 include("../inc/includes.inc");

 #-------------------------------------------------[ Register global vars ]---
 $id     = $_REQUEST["id"];
 $delete = $_REQUEST["delete"];
 $pwd1   = $_POST["pwd1"];
 $pwd2   = $_POST["pwd2"];

 #--------------------------------------------------[ Check authorization ]---
 if ($pvp->auth->user->login == "guest") kickoff();
 if (!$pvp->auth->admin) $id = $pvp->auth->user_id;

 #--------------------------------------------------[ initialize template ]---
 $t = new Template($pvp->tpl_dir);

 #==================================================[ update user account ]===
 if ($_POST["update"]) {
   $user->id     = $id;
   if (!$pvp->auth->admin) {
     $users = $db->get_users($id);
     $user->login = $users->login;
     $user->comment = $users->comment;
     $access = array("admin","browse","add","upd","del");
     foreach ($access as $value) {
       $user->$value = $users->$value;
     }
   } else {
     $user->login  = $_POST["login"];
     $user->comment= $_POST["comment"];
     $access = array("admin","browse","add","upd","del");
     foreach ($access as $value) {
       if ($_POST[$value]) { $user->$value = "1"; } else { $user->$value = "0"; }
     }
   }
   $pwd_ok = 1;
   if ( isset($pwd1) || isset($pwd2) ) {
     if ($pwd1 == $pwd2) {
       $user->pwd = $pwd1;
     } else {
       $pwd_ok = 0;
       $save_result = "<SPAN CLASS='error'>". lang("password_nomatch") . "</SPAN><BR>\n";
     }
   }
   if ( $db->set_user($user) ) {
     $save_result = "<SPAN CLASS='ok'>" .lang("update_success") . ".</SPAN><BR>\n";
   } else {
     $save_result = "<SPAN CLASS='error'>" .lang("user_update_failed",$id). "</SPAN><BR>\n";
   }
 #=================================================[ add new user account ]===
 } elseif ($_POST["adduser"] && $pvp->auth->admin) {
   $user->id     = $_POST["id"];
   $user->login  = $_POST["login"];
   $user->comment= $_POST["comment"];
   $access = array("admin","browse","add","upd","del");
   foreach ($access as $value) {
     if ($_POST[$value]) { $user->$value = "1"; } else { $user->$value = "0"; }
   }
   $pwd_ok = 1;
   if ( isset($pwd1) || isset($pwd2) ) {
     if ($pwd1 == $pwd2) {
       $user->pwd = $pwd1;
     } else {
       $pwd_ok = 0;
       $save_result = "<SPAN CLASS='error'>" .lang("password_nomatch"). "</SPAN><BR>\n";
     }
   }
   if ( $pwd_ok && $db->add_user($user) ) {
     $save_result = "<SPAN CLASS='ok'>" .lang("create_success"). ".</SPAN><BR>\n";
   } else {
     $save_result .= "<SPAN CLASS='error'>" .lang("user_update_failed","#"). "</SPAN><BR>\n";
   }
 #==================================================[ delete user account ]===
 } elseif ($delete) {
   $user = $db->get_users($delete);
   if ($_POST["confirmed"]) {
     if ( $db->del_user($delete) ) {
       $save_result = "<SPAN CLASS='ok'>" .lang("user_deleted",$delete,$user->login,$user->comment) . ".</SPAN><BR>\n";
     } else {
       $save_result = "<SPAN CLASS='error'>" .lang("user_delete_failed",$delete,$user->login,$user->comment) . "</SPAN><BR>\n";
     }
     $t->set_file(array("template"=>"delete.tpl"));
     $t->set_var("listtitle",lang("user_delete_report"));
     $t->set_var("details",$save_result);
     header('refresh: 4; url=users.php');
     include("../inc/header.inc");
     $t->pparse("out","template");
     exit;
   } else {
     $t->set_file(array("template"=>"admin_userdelete.tpl"));
     $t->set_var("listtitle",lang("confirm_userdelete",$delete));
     $t->set_var("formtarget",$_SERVER["PHP_SELF"]);
     $t->set_var("delete",$delete);
     $t->set_var("yes",lang("yes"));
     $t->set_var("no",lang("no"));
     $t->set_var("delete_yn","<SPAN CLASS='error'>".lang("confirm_userdeletion",$user->login,$user->comment)."</SPAN>");
     if (!$pvp->config->enable_cookies) $t->set_var("hidden","<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>");
     include("../inc/header.inc");
     $t->pparse("out","template");
     exit;
   }
 }

 #=====================================================[ build input form ]===
 $t->set_file(array("template"=>"admin_useredit.tpl"));

 $users = $db->get_users($id);
 $t->set_var("user_id","<INPUT TYPE='hidden' NAME='id' VALUE='$id'>$id");
 if ($pvp->auth->admin) {
   $t->set_var("login","<INPUT NAME='login' VALUE='".$users->login."'>");
   $t->set_var("comment","<INPUT NAME='comment' VALUE='".$users->comment."'>");
   $t->set_var("browse",$pvp->common->make_checkbox("browse",$users->browse));
   $t->set_var("add",$pvp->common->make_checkbox("add",$users->add));
   $t->set_var("upd",$pvp->common->make_checkbox("upd",$users->upd));
   $t->set_var("del",$pvp->common->make_checkbox("del",$users->del));
   $t->set_var("isadmin",$pvp->common->make_checkbox("admin",$users->admin));
 } else {
   $t->set_var("login",$users->login);
   $t->set_var("comment",$users->comment);
   $t->set_var("browse",$users->browse);
   $t->set_var("add",$users->add);
   $t->set_var("upd",$users->upd);
   $t->set_var("del",$users->del);
   $t->set_var("isadmin",$users->admin);
 }
 $t->set_var("password","<INPUT TYPE='password' NAME='pwd1' MAXLENGTH='10'>");
 $t->set_var("password2","<INPUT TYPE='password' NAME='pwd2' MAXLENGTH='10'>");

 $t->set_var("listtitle",lang("admin_useredit"));
 $t->set_var("formtarget",$_SERVER["PHP_SELF"]);
 if ($id) $t->set_var("update","<INPUT TYPE='submit' CLASS='submit' NAME='update' VALUE='".lang("update")."'>");
 if ($pvp->auth->admin) {
   $t->set_var("adduser","<INPUT TYPE='submit' CLASS='submit' NAME='adduser' VALUE='".lang("add_user")."'>");
 }
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
 if (!$pvp->config->enable_cookies) $t->set_var("hidden","<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>");
 include("../inc/header.inc");
 $t->pparse("out","template");

 include("../inc/footer.inc");
?>