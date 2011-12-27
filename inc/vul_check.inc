<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2010 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Check for vulnerabilities and reject requests that look like intrusion    #
 #############################################################################

 /* $Id$ */

 #=========================================================[ helper funcs ]===
 function vul_kick($var="") {
   $protocol = $_SERVER['SERVER_PROTOCOL'];
   header("$protocol 403 Forbidden");
   header("Status: 403 Forbidden");
   header("Connection: close");
   $charset="utf-8";
   $title = "Access Denied!";
?>
<HTML><HEAD>
 <meta http-equiv="Content-Type" content="text/html; charset=<?php echo $charset?>">
 <meta http-equiv="cache-control" content="no-cache">
 <meta http-equiv="content-language" content="<?php echo $contentlang?>">
 <Title><?php echo $title?></Title>
 <LINK REL="stylesheet" TYPE="text/css" HREF="templates/applicat/default.css">
</HEAD><BODY>
<BR STYLE="margin-top:50">
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="95%" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0" ALIGN="center"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle"><DIV STYLE="margin:2"><?php echo $title?></DIV></TD></TD></TR>
</TABLE></TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD>
<TABLE WIDTH="90%" ALIGN="center">
 <TR><TD><P ALIGN='justify'>Access to this page was denied due to wrong parameters. The intrusion detection of this application triggered an alert: Looks like you want to attack the system and place your own code here. We don't like that, so we aborted your request. If you think that's not your fault (i.e. you did not intentionally manipulate the URL string or POST data, but used the application in a "normal way" only), you may want to report this to the author(s) to fix the problem.</P>
         <P>Offended variable: <?php echo $var?> = '<?php echo htmlentities($_REQUEST[$var])?>'</P></TD></TR>
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
     $test = (string) $_POST[$var];
     if (preg_match("/[^\d-]/",$test)) vul_kick($var); }
   if (!empty($_GET[$var])) {
     $test = (string) $_GET[$var];
     if (preg_match("/[^\d-]/",$test)) vul_kick($var); }
 }
 function vul_alnum($var) {
   $vuls = "/[^\w\s-\pL]/u";
   if (!empty($_POST[$var])) {
     $test = stripslashes((string) $_POST[$var]);
     if (@preg_match($vuls,$test)) vul_kick($var); }
   if (!empty($_GET[$var])) {
     $test = stripslashes((string) $_GET[$var]);
     if (@preg_match($vuls,$test)) vul_kick($var); }
 }

 #==========================================================[ common vars ]===
 if (!empty($_GET["lang"]) && strlen($_GET["lang"]) > 2) vul_kick();
 if (preg_match('![^\w\./-]!',$_SERVER['PHP_SELF'])) vul_kick();
 vul_alnum("order");
 vul_alnum("tpl");
 vul_alnum("nr");
 vul_num("id");
 if ($page_id!="search_movie") vul_num("mtype_id"); // array on the search page
 vul_num("cass_id");
 vul_num("part");
 vul_num("id");
 if (isset($_REQUEST['sess_id'])) $tid = $_REQUEST['sess_id'];
 elseif (isset($_COOKIE['sess_id'])) $tid = $_COOKIE['sess_id'];
 else $tid = '';
 if (!empty($tid) && preg_match("/\W/",$tid)!==0) vul_kick("sess_id");
 unset($tid);

 #============================================================[ users.php ]===
 if (basename($_SERVER["SCRIPT_NAME"])=="users.php") {
   vul_num("lines");
   for ($i=0;$i<$_REQUEST["lines"];++$i) {
     vul_num("user_$i");
     vul_alnum("user_${i}_login");
     vul_alnum("user_${i}_comment");
     vul_alnum("browse_$i");
     vul_alnum("add_$i");
     vul_alnum("upd_$i");
     vul_alnum("del_$i");
     vul_alnum("admin_$i");
   }
 }

 #=========================================================[ useredit.php ]===
 if (basename($_SERVER["SCRIPT_NAME"])=="useredit.php") {
   vul_alnum("ulogin");
   vul_alnum("comment");
   vul_alnum("pwd1");
   vul_alnum("pwd2");
   vul_alnum("browse");
   vul_alnum("add");
   vul_alnum("upd");
   vul_alnum("del");
   vul_alnum("admin");
   vul_alnum("update");
   vul_alnum("adduser");
 }
?>