<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
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
include("../templates/default/default.css");
if ( !strpos(strtoupper($debug["log"]),"D")===false ) $db->Debug=1;

#====================================================[ Output page intro ]===
$title = "phpVideoPro: Setting up the Database";
?>
<HTML><HEAD>
 <TITLE><?=$title?></TITLE>
 <META http-equiv="Content-Type" content="text/html; charset=iso-8859-15">
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
}
$query_count = 4;

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
      within the online help system. Enjoy!</DIV></TD></TR>
</TABLE></BODY></HTML>
