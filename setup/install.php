<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Installation Program: First Time Installation                             #
 #############################################################################

 /* $Id$ */

  include ("../inc/config.inc");
  include("../templates/default/default.css");
  $title = "phpVideoPro Setup: Fresh Installation";

?>
<HTML><HEAD>
 <TITLE><?=$title?></TITLE>
 <META http-equiv="Content-Type" content="text/html; charset=iso-8859-15">
</HEAD>
<BODY>
<H1 ALIGN=CENTER><?=$title?></H1>

<TABLE WIDTH="90%" ALIGN="center">
 <TR><TH>Requirements</TH></TR>
 <TR><TD><DIV ALIGN="justify"><P>There are a few things you have to make sure
     first (without them the whole program, including this setup, won't work
     at all):</P>
     <OL>
      <LI>have a webserver running (I just tested it with Apache)</LI>
      <LI>have PHP running, at least v4.0b3 (a version less than this won't work;
          I recommend using Apache with PHP as loadable module, and that's
          the only combination I've tested)</LI>
      <LI>make sure your PHP has MySQL support built in! (if requirements
          1, 2 and 4 are met, click <A HREF="phpinfo.php">here</A> to see what
          features are supported by your PHP setup)</LI>
     </OL>
     <P>Guess your system meets these requirements - otherwise you wouldn't
     read this page, would you?</P></DIV></TD></TR>
 <TR><TH>Pre-Requisites</TH></TR>
 <TR><TD><DIV ALIGN="justify"><P>If this requirements are met, we can start
     setting up phpVideoPro. To do this, follow these steps:</P>
     <OL>
      <LI>edit inc/config.inc to reflect your structures. There are not many
          settings you <b>must</b> check, so this is done fast:<BR><BR>
          <TABLE WIDTH="90%" ALIGN="center" BORDER="1">
	   <COLGROUP><COL WIDTH="15%"><COL WIDTH="85%"></COLGROUP>
	   <TR><TD><b>$site</b></TD>
	       <TD>just the name for your running copy. It's only used to be
	       displayed in the title bar for now.</TD></TR>
           <TR><TD><b>$base_url</b></TD>
	       <TD>the root directory of your phpVideoPro copy. Make sure it has
               a leading slash (i.e. it has to be the complete path starting
               with your web servers document root) as well as a trailing slash.</TD></TR>
           <TR><TD><b>$base_path</b></TD>
               <TD>same as $base_url, but regarding your file system (so for
               Windoze this one starts with a drive letter)</TD></TR>
           <TR><TD><b>$database</b></TD>
               <TD>settings for the database (host running the db server,
               database name, user and password to access the database).</TD></TR>
          </TABLE><BR>
          The other settings you can leave unchanged, they have suitable defaults.
          you may change them in the future if you feel any need to :)</LI>
      <LI>create the database with the name you specified in inc/config.inc as
          $database["database"] on the host you configured there. Make sure the
          configured user has at least following privileges for this database:
          Select, Insert, Update, Delete, Create. For future versions (updates),
          the privileges Alter, Drop and References may also be needed.</LI>
     </OL></DIV></TD></TR>
 <TR><TH>Create the tables</TH></TR>
 <TR><TD><DIV ALIGN=justify>If all above mentioned requirements pre-requisites
     are met, you can follow this link to <A HREF="create_tables.php">create</A>
     the tables and fill them with initial data (such as categories, sound types
     etc). Alternatively, you may <A HREF="create_tables.php?restore=1">restore</A>
     a previously created backup instead of installing a default configuration
     only. With some luck (*grin*) you'll get no error message, and have the
     database ready to start with phpVideoPro then. So, if everything worked
     fine, you <b>then</b> can point your browser to phpVideoPro's
     <A HREF="../index.php">start screen</A>. Good luck - and enjoy!</DIV></TD></TR>
</TABLE></BODY></HTML>