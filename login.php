<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # User Login Page                                                           #
 #############################################################################

 /* $Id$ */

 $page_id = "login";
 $details = array("sess_id","logout","login","passwd","url","redir","login_hint");
 foreach ($details as $var) {
   $$var = $_REQUEST[$var];
 }
 include("inc/includes.inc");
 if ($sess_id &!$pvp->session->verify($sess_id)) $login_hint = "session_expired";
 if (isset($redir)) {
   $url = $redir;
 }
 if (!strlen($url))  $url = $base_url . "index.php";
 if (isset($login_hint)) $login_hint = lang("$login_hint");
 if ($sess_id && $logout) {
   $pvp->session->end($sess_id);
   if ($pvp->cookie->active) $pvp->cookie->delete("sess_id");
   $sess_id = "";
 }
 $t = new Template($pvp->tpl_dir);

 if (isset($_POST["submit"])) {
   if ($sess_id = $pvp->session->create($login,$passwd) ) {
     $url = $pvp->link->slink($url);
     if ($pvp->cookie->active) {
       $pvp->cookie->set("sess_id",$sess_id);
     }
     header("Location: $url");
     exit;
   } else {
     $login_hint = "<SPAN CLASS='error'>" .lang("login_failed"). "</SPAN><BR>\n";
   }
 }

 $t->set_file(array("template"=>"login.tpl"));
 $t->set_var("formtarget",$_SERVER["PHP_SELF"]);
 if ( isset($login_hint)) $t->set_var("login_hint",$login_hint);
 $t->set_var("welcome",lang("welcome"));
 $t->set_var("head_login",lang("login")."<INPUT TYPE='hidden' NAME='url' VALUE='$url'>");
 $t->set_var("head_passwd",lang("password"));
 $t->set_var("submit",lang("submit"));

 $menue = 0;
 include("inc/header.inc");
 $t->pparse("out","template");

 include("inc/footer.inc");
?>