<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2006 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Check for vulnerabilities and reject requests that look like intrusion    #
 #############################################################################

 /* $Id$ */

 #=========================================================[ helper funcs ]===
 function vul_kick() {
   $protocol = $_SERVER['SERVER_PROTOCOL'];
   header("$protocol 403 Forbidden");
   header("Status: 403 Forbidden");
   header("Connection: close");
   $charset="utf-8";
   $title = "Access Denied!";
?>
<HTML><HEAD>
 <meta http-equiv="Content-Type" content="text/html; charset=<?=$charset?>">
 <meta http-equiv="cache-control" content="no-cache">
 <meta http-equiv="content-language" content="<?=$contentlang?>">
 <Title><?=$title?></Title>
 <LINK REL="stylesheet" TYPE="text/css" HREF="templates/applicat/default.css">
</HEAD><BODY>
<BR STYLE="margin-top:50">
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="95%" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0" ALIGN="center"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle"><DIV STYLE="margin:2"><?=$title?></DIV></TD></TD></TR>
</TABLE></TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD>
<TABLE WIDTH="90%" ALIGN="center">
 <TR><TD><P ALIGN='justify'>Access to this page was denied due to wrong parameters. The intrusion detection of this application triggered an alert: Looks like you want to attack the system and place your own code here. We don't like that, so we aborted your request. If you think that's not your fault (i.e. you did not intentionally manipulate the URL string or POST data, but used the application in a "normal way" only), you may want to report this to the author(s) to fix the problem.</P></TD></TR>
</TABLE></TD></TR>
</TABLE>
</DIV>
</TD></TR></TABLE>
</DIV></BODY></HTML>
<? 
   exit;
 }
 function vul_num($var) {
   if (!empty($_POST[$var])) {
     if (preg_match("/\D/",$_POST[$var])) vul_kick(); }
   if (!empty($_GET[$var])) {
     if (preg_match("/\D/",$_GET[$var])) vul_kick(); }
 }
 function vul_alnum($var) {
   if (!empty($_POST[$var])) {
     if (preg_match("/[^\w-]/",$_POST[$var])) $vul_kick(); }
   if (!empty($_GET[$var])) {
     if (preg_match("/[^\w-]/",$_GET[$var])) vul_kick(); }
 }

 #==========================================================[ common vars ]===
 if (!empty($_GET["lang"]) && strlen($_GET["lang"]) > 2) vul_kick();
 vul_alnum("order");
 vul_alnum("tpl");
 if (!empty($_REQUEST["nr"])) vul_alnum("nr");
 if (!empty($_REQUEST["id"])) vul_num("id");
 if (!empty($_REQUEST["mtype_id"])) vul_num("mtype_id");
 if (!empty($_REQUEST["cass_id"])) vul_num("cass_id");
 if (!empty($_REQUEST["id"])) vul_num("id");

 #===========================================================[ search.php ]===
 if (basename($_SERVER["SCRIPT_NAME"])=="search.php") {
   if (!empty($_REQUEST["minlen"])) vul_num("minlen");
   if (!empty($_REQUEST["maxlen"])) vul_num("maxlen");
   if (!empty($_REQUEST["minfsk"])) vul_num("minfsk");
   if (!empty($_REQUEST["maxfsk"])) vul_num("maxfsk");
 }

 #============================================================[ login.php ]===
 if (!empty($_REQUEST["login_hint"])) vul_alnum("login_hint");
# if (basename($_SERVER["SCRIPT_NAME"])=="login.php") {
# }

 #=============================================================[ edit.php ]===
 if (basename($_SERVER["SCRIPT_NAME"])=="edit.php") {
   vul_num("part");
   vul_num("commercials_id");
   vul_num("recday");
   vul_num("recmon");
   vul_num("recday");
   vul_num("tone_id");
   vul_num("color_id");
   vul_num("pict_id");
   vul_alnum("director_list");
   vul_alnum("music_list");
   vul_alnum("label");
   for ($i=1;$i<4;++$i) {
     vul_num("cat${i}_id");
     vul_num("vis_actor$i");
     vul_alnum("subtitle$i");
   }
   for ($i=4;$i<9;++$i) {
     vul_alnum("subtitle$i");
   }
   vul_num("vis_actor4");
   vul_num("vis_actor5");
   vul_num("lp");
 }
?>