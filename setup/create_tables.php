<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Create the database tables required for phpVideoPro                       #
 #############################################################################

 /* $Id$ */

#========================================================[ initial setup ]===
$pvpinstall = 1;
include ("../inc/config.inc");
include ("../inc/config_internal.inc");
include ("../inc/common_funcs.inc");
if ( !strpos(strtoupper($debug["log"]),"D")===false ) $db->Debug=1;

#====================================================[ Output page intro ]===
$title = "phpVideoPro: Setting up the Database";
?>
<HTML><HEAD>
 <TITLE><?=$title?></TITLE>
 <META http-equiv='Content-Type' content='text/html; charset=utf-8'>
 <LINK HREF='../templates/default/default.css' rel='stylesheet' type='text/css'>
</HEAD>
<BODY>
<H2 ALIGN=CENTER><?=$title?></H2>
<TABLE WIDTH="90%" ALIGN="center">
 <TR><TH>Introduction</TH></TR>
 <TR><TD><DIV ALIGN="justify"><P>This page is intended to create all tables
     needed for phpVideoPro as well as to insert initial data into them. Right
     now this is done in three steps:</P>
     <UL>
      <LI>Creation of all tables</LI>
      <LI>Insertion of an initial list of categories</LI>
      <LI>Insertion of technical data, i.e. colors (b/w, color, 3D), media types
         (DVD, original video tapes, self recorded video tapes), screen formats
         (4:3, 16:9), tone formats (from Mono to Digital Dolby 6.1).</LI>
    </UL>
    <P>For each of those mentioned steps you should be informed below if they
    were completed successfully. So, if below this are less than three
    statements about successfully completion, there was probably something going
    wrong...</P></DIV></TD></TR>
 <TR><TD><UL>
<?

#===================[ Get SQL statements from their files & execute them ]===
$create_script = "create_tables." . $database["type"];
$tables   = queryf($create_script,"Creation of tables");
if ($restore) {
  $restore  = queryf("restore.sql","Restore of a previously created Backup");
} else {
  $cats     = queryf("categories.sql","Insertion of categories");
  $techdata = queryf("tech_data.sql","Insertion of technical data");
  $def_lang = queryf("lang_en.sql","Prepare default language");
  $ps_lab   = queryf("pslabel." . $database["type"],"Set up PSLabel Tables");
}
$query_count = 5;

#=========================================================[ Closing page ]===
?>
     </UL></TD></TR>
 <TR><TD><DIV ALIGN="justify">Congratulations - if there are <?=$query_count?>
      lines stating "success", you've done it - the basic installation is
      complete! You can then proceed to the <A HREF="../login.php">login</A>
      page. Use the "admin" account on your first login, the needed password is
      "video". I strongly recommend you to go to the user management page
      (you'll find it within the admin menue) and change the admin password,
      plus optionally setup new accounts or modify the guest account, so you
      don't need to login the next time ;) More information on this you'll find
      within the online help system.</DIV></TD></TR>
 <TR><TD><DIV ALIGN="justify">Since there have been some problems reported
      concerning cookie and session management, after v0.4.8 I decided to change
      the initial values to somewhat fail-safe. As long as you use phpVideoPro
      in a single user environment only, you may stay with these settings,
      though they have their disadvantages. I recommend you to use cookies for
      several reasons - most important even in a single user environment is
      the storage of temporary preferences like filters. For a multi user
      environment, it is strongly recommended to enforce the usage of cookies
      by phpVideoPro -- otherwise users will overwrite each others preferences
      plus the application defaults, since without cookies both are the same
      at the moment.</DIV></TD></TR>
 <TR><TD><DIV ALIGN="justify">So please, after changing the master password,
      go to the admin-&gt;configuration menu and check at least the following
      items:<UL>
      <LI><b>enable cookies:</b> this ensures that phpVideoPro always uses
          cookies, so no user can overwrite another's preferences, plus you
          may use non-permanent preferences (via the edit menu -- preferences
          changed via the admin menu are permanent application defaults)</LI>
      <LI><b>cookies lifetime:</b> the new default is to expire the cookies
          with the browser session. If you want your users to be able to store
          their preferences beyond this limit, set it to somewhat different,
          e.g. "1 year"</LI>
      <LI><b>timeout inactive sessions:</b> this is a security relevant item,
          at least if you decide to put phpVideoPro online. Initially, a
          session is never expired. The recommended value is "2 hours" if the
          application can be accessed via the Internet.</LI></UL></DIV></TD></TR>
 <TR><TD><DIV ALIGN="justify">If you've read so far and noticed my hints, there's
          only one thing left to say for me: Enjoy phpVideoPro!</DIV></TD></TR>
</TABLE></BODY></HTML>
