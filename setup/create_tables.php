<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Create the database tables required for phpVideoPro                       *
 \***************************************************************************/

 /* $Id$ */

##################################################################
# Configuration of Setup module
#
  $pvpinstall = 1;
  include ("../inc/config.inc");
  include ("../inc/config_internal.inc");
  include ("../inc/common_funcs.inc");
  if ( !strpos(strtoupper($debug["log"]),"D")===false ) $db->Debug=1;

##################################################################
# Output page intro
# 
  $title = "phpVideoPro: Setting up the Database"; ?>
<HTML><HEAD>
 <TITLE><? echo $title ?></TITLE>
 <META http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</HEAD>
<BODY>
<H2 ALIGN=CENTER><? echo $title ?></H2>
<P ALIGN=JUSTIFY>This page is intended to create all tables needed for
 phpVideoPro as well as to insert initial data into them. Right now this
 is done in three steps:</P>
<UL>
 <LI>Creation of all tables
 <LI>Insertion of an initial list of categories
 <LI>Insertion of technical data, i.e. colors (b/w, color, 3D), media types
     (DVD, original video tapes, self recorded video tapes), screen formats
     (4:3, 16:9), tone formats (from Mono to Digital Dolby 6.1).
</UL>
<P ALIGN=JUSTIFY>For each of those mentioned steps you should be informed
 below if they were completed successfully. So, if below this are less than
 three statements about successfully completion, there was probably something
 going wrong...</P>
<UL>
<?

##################################################################
# Get SQL statements from their files and execute them
#
  $create_script = "create_tables." . $database["type"];
  $tables   = queryf($create_script,"Creation of tables");
  $cats     = queryf("categories.sql","Insertion of categories");
  $techdata = queryf("tech_data.sql","Insertion of technical data");
  $def_lang = queryf("lang_en.sql","Prepare default language");
  $query_count = 4;

##################################################################
# Closing page
# ?>
</UL>
<P ALIGN=JUSTIFY>Congratulations - if there are <? echo $query_count ?>
 lines stating "success", you've done it - the basic installation is complete!
 You can then proceed to the <A HREF="configure.php">configuration</A> page.</P>
</BODY></HTML>
