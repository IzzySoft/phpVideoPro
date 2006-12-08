<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2006 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Grant other users permission to your records                              #
 #############################################################################

 /* $Id$ */

 #========================================================[ initial setup ]==
# $page_id = "user_grants";
 include("inc/includes.inc");

 #-------------------------------------------------[ Register global vars ]---
 if (isset($_POST["lines"])) $lines = $_POST["lines"]; else $lines = 0;

 #--------------------------------------------------[ Check authorization ]---
 if (!$pvp->auth->add) kickoff();
 $save_result = "";

 #==================================================[ vulnerability check ]===
 vul_num("delete");
 vul_num("lines");
 for ($i=0;$i<$lines;++$i) {
   vul_num("user_$i");
   vul_alnum("access_$i");
 }
 vul_num("adduser");
 vul_alnum("access_add");

 #==================================================[ process the changes ]===
 if (isset($_POST["update"])) {
   for ($i=$lines;$i>0;--$i) {
     $user->id     = $_POST["user_".$i];
     $user->access = $_POST["access_".$i];
     if ( !$db->set_usergrants($pvp->auth->user_id,$user->id,$user->access) ) $error .= ",".$user->id;
   }
   if ($_POST["adduser"] != "-") {
     $user->id     = $_POST["adduser"];
     $user->access = $_POST["access_add"];
     if ( !$db->set_usergrants($pvp->auth->user_id,$user->id,$user->access) ) $error .= ",".$user->id;
   }
   if (isset($error)) {
     $error = substr($error,1);
     $save_result = "<SPAN CLASS='error'>" .lang("user_update_failed",$error) . "</SPAN><BR>\n";
   } else {
     $save_result = "<SPAN CLASS='ok'>" . lang("update_success") . ".</SPAN><BR>\n";
   }
 } elseif (isset($_GET["delete"])) {
   if ( $db->set_usergrants($pvp->auth->user_id,$_GET["delete"],"") )
     $save_result = "<SPAN CLASS='ok'>" . lang("update_success") . ".</SPAN><BR>\n";
   else
     $save_result = "<SPAN CLASS='error'>" .lang("user_update_failed",$error) . "</SPAN><BR>\n";
 }

 #=======================================================[ build the form ]===
 include("inc/header.inc");
?>
<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript">
 function delconfirm(url) {
  check = confirm("<?=lang("confirm_delete")?>");
  if (check == true) window.location.href=url;
 }
</SCRIPT>
<?
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"usergrants.tpl"));
 $t->set_block("template","itemblock","item");
 $tpl_dir = str_replace($base_path,$base_url,$pvp->tpl_dir);
# $edit_img  = $tpl_dir . "/images/edit.gif";
 $trash_img = $tpl_dir . "/images/trash.gif";

 $users   = $db->get_users();
 $usercount = count($users);
 $grants  = $db->get_usergrants(array($pvp->auth->user_id));
 $adduser = "";
 $lines   = 0;
 for ($i=0;$i<$usercount;++$i) {
   if (isset($grants[$users[$i]->id])) {
     ++$lines;
     $t->set_var("user_id","<INPUT TYPE='hidden' NAME='user_".$i."' VALUE='".$users[$i]->id."'>");
     $t->set_var("login","<INPUT TYPE='hidden' NAME='user_".$i."_login' VALUE='".$users[$i]->login."'>".ucfirst($users[$i]->login));
     $sel = "<INPUT TYPE='radio' NAME='access_$i' VALUE='SELECT'";
     $ins = "<INPUT TYPE='radio' NAME='access_$i' VALUE='INSERT'";
     $upd = "<INPUT TYPE='radio' NAME='access_$i' VALUE='UPDATE'";
     $del = "<INPUT TYPE='radio' NAME='access_$i' VALUE='DELETE'";
     if (in_array("DELETE",($grants[$users[$i]->id]))) $del .= " CHECKED";
     elseif (in_array("UPDATE",($grants[$users[$i]->id]))) $upd .= " CHECKED";
     elseif (in_array("INSERT",($grants[$users[$i]->id]))) $ins .= " CHECKED";
     elseif (in_array("SELECT",($grants[$users[$i]->id]))) $sel .= " CHECKED";
     $sel .= ">"; $ins .= ">"; $upd .= ">"; $del .=">";
     $t->set_var("browse",$sel);
     $t->set_var("add",$ins);
     $t->set_var("upd",$upd);
     $t->set_var("del",$del);
     $url = $pvp->link->slink("usergrants.php?delete=".$users[$i]->id);
     $t->set_var("delete","<IMG SRC='$trash_img' BORDER='0' ALT='".lang("delete")."' onClick=\"delconfirm('$url')\">");
     if ($i) $t->parse("item","itemblock",TRUE);
       else $t->parse("item","itemblock");
   } else {
     if ($pvp->auth->user_id!=$users[$i]->id)
       $adduser .= "<OPTION VALUE='".$users[$i]->id."'>".ucfirst($users[$i]->login)."</OPTION>";
   }
 }
 if (!empty($adduser)) {
   $t->set_var("user_id","");
   $adduser = "<OPTION VALUE='-'>-</OPTION>$adduser";
   $t->set_var("login","<SELECT NAME='adduser'>$adduser</SELECT>");
   $t->set_var("browse","<INPUT TYPE='radio' NAME='access_add' VALUE='SELECT'>");
   $t->set_var("add","<INPUT TYPE='radio' NAME='access_add' VALUE='INSERT'>");
   $t->set_var("upd","<INPUT TYPE='radio' NAME='access_add' VALUE='UPDATE'>");
   $t->set_var("del","<INPUT TYPE='radio' NAME='access_add' VALUE='DELETE'>");
   $t->set_var("delete","&nbsp;");
   if (count($grants)) $t->parse("item","itemblock",TRUE);
     else $t->parse("item","itemblock");
 }

 $t->set_var("listtitle",lang("user_grants"));
 $t->set_var("formtarget",$_SERVER["PHP_SELF"]);
 $t->set_var("update","<INPUT TYPE='submit' CLASS='submit' NAME='update' VALUE=".lang("update").">");
 $t->set_var("save_result",$save_result);
 $t->set_var("head_users","&nbsp;");
 $t->set_var("head_access",lang("data_access"));
 $t->set_var("head_actions","&nbsp;");
 $t->set_var("head_login",lang("login"));
 $t->set_var("head_browse",lang("read_access_short"));
 $t->set_var("head_add",lang("add_access_short"));
 $t->set_var("head_upd",lang("upd_access_short"));
 $t->set_var("head_del",lang("del_access_short"));
 $hidden = "<INPUT TYPE='hidden' NAME='lines' VALUE='$lines'>";
 if (!$pvp->cookie->active) $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>";
 $t->set_var("hidden",$hidden);
 $t->pparse("out","template");

 include("inc/footer.inc");
?>