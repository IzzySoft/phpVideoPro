<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Setup program: Updating from previous version                             #
 #############################################################################

 /* $Id$ */

#========================================================[ initial setup ]===
$runupdate = 1;
include ("../inc/config.inc");
include ("../inc/config_internal.inc");
include ("../inc/common_funcs.inc");
include("../templates/default/default.css");
$db->Host     = $database["host"];
$db->Database = $database["database"];
$db->User     = $database["user"];
$db->Password = $database["password"];
if ( !strpos(strtoupper($debug["log"]),"D")===false ) $db->Debug=1;

#=========================================[ obtain the installed version ]===
# this may be a bit tricky - while in recent versions, the version number is
# stored in the db, versions prior to 0.1.2 didn't do so...
function get_version() {
  GLOBAL $db;
  $tablelist = "#";
  $tables = $db->table_names();
  for ($i=0;$i<count($tables);$i++) {
    $tablelist .= strtolower($tables[$i]["table_name"]) . "#";
  }
  if ( strpos($tablelist,"#pvp_config#") ) {
    $db->query("SELECT value FROM pvp_config WHERE name='version'");
    $db->next_record();
    $oldversion = $db->f('value');
  } elseif ( strpos($tablelist,"#preferences#") ) {
    $oldversion = "0.1.1";
  } else {
    $oldversion = "0.1.0";
  }
  return $oldversion;
}

#====================================================[ Output page intro ]===
echo "<HTML><HEAD>\n";
echo " <META http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-15\">\n";
$title = "phpVideoPro: ";
if ( !isset($oldversion) ){
  $title .= "Updating the Database";
} else {
  $title .= "Updating from v$oldversion";
}
echo " <TITLE>$title</TITLE>\n</HEAD>\n<BODY>\n";
echo "<H2 ALIGN=CENTER>$title</H2>\n";
echo "<TABLE ALIGN='center' WIDTH='90%'>\n";

#=====================================================[ Output user info ]===
if ( !isset($oldversion) ) {
  $oldversion = get_version();
?>
<TR><TH>Preamble</TH></TR>
<TR><TD>
<P ALIGN=JUSTIFY>This simple script will update your database from a previous
 version of phpVideoPro to the recent one. I strongly recommend you to backup
 your existing database before executing the script! Furthermore, please
 inspect config.inc for possible changes.</P>
<P ALIGN=JUSTIFY>For each update step, you should then be notified wether it
 was successfull or not. So now, if you've made your backup
 (or decided not to backup at all), we can go on with the update process.</P>
<P ALIGN=JUSTIFY>The version of phpVideoPro's database which is installed on
 your machine appears to be v<? echo $oldversion ?>. If this is <b>not</b>
 what you've expected, please <b><font color="#ff0000">PANIC</font></b> now!
 Otherwise (which <b>I</b> expect to be the case), follow this nice little
 <a href="<? echo "$PHP_SELF?oldversion=$oldversion" ?>">link</a> to finally
 <b>do</b> the real update...</p>
<?
#========================================================[ Do the update ]===
} else {
  echo "<TR><TH>Updating...</TH></TR>\n<TR><TD>";
  $final = "";
  echo "<UL>\n";

$pvp->preferences->admin();
#-----------------[ Get SQL statements from their files and execute them ]---
  switch ($oldversion) {
    case "0.1.0"    : queryf("0-1-0_to_0-1-1.sql","Update from v0.1.0 to v0.1.1");
    case "0.1.1"    : queryf("0-1-1_to_0-1-2.sql","Update from v0.1.1 to v0.1.2");
    case "0.1.2"    :
    case "0.1.3"    :
    case "0.1.4"    : queryf("0-1-4_to_0-1-5.sql","Update from v0.1.5 to v0.1.6");
    case "0.1.5"    :
    case "0.1.6"    :
    case "0.1.7"    : queryf("0-1-7_to_0-2-0.sql","Update from v0.1.7 to v0.2.0");
    case "0.2.0"    : queryf("0-2-0_to_0-2-1." . $database["type"],"Update from v0.2.0 to v0.2.1");
    case "0.2.1"    : queryf("0-2-1_to_0-2-2." . $database["type"],"Update from v0.2.1 to v0.2.2");
    case "0.2.2"    : queryf("0-2-2_to_0-2-3.sql","Update from v0.2.2 to v0.2.3");
    case "0.2.3"    :
    case "0.2.4"    :
    case "0.2.5"    : queryf("0-2-5_to_0-2-6.sql","Update from v0.2.5 to v0.2.6");
    case "0.2.6"    : queryf("0-2-6_to_0-2-7." . $database["type"],"Update from v0.2.6 to v0.2.7");
    case "0.2.7"    : queryf("0-2-7_to_0-2-8.sql","Update from v0.2.7 to v0.2.8");
                      queryf("categories.sql","Refresh of categories");
    case "0.2.8"    :
    case "0.3.0"    :
    case "0.3.1"    :
    case "0.3.2"    :
    case "0.3.3"    : queryf("0-3-3_to_0-3-4.".$database["type"],"Update from v0.3.3 to v0.3.4");
    case "0.3.4"    :
    case "0.3.5"    :
    case "0.3.6"    : queryf("0-3-6_to_0-3-7.".$database["type"],"Update from v0.3.6 to v0.3.7");
		      $colors = $pvp->preferences->colors;
		      unset($colors["page_background"]);
		      unset($colors["table_background"]);
		      unset($colors["th_background"]);
		      $pvp->preferences->set("colors",rawurlencode( serialize($colors) ));
    case "0.3.7"    : queryf("0-3-7_to_0-3-8.sql","Update from v0.3.7 to v0.3.8");
                      queryf("lang_en.sql","Refresh of English language support");
    case "0.3.8"    : queryf("0-3-8_to_0-4-0.sql","Update from v0.3.8 to v0.4.0");
                      break;
    default         : $final = "Your database version seems to be current, there's nothing I can update for you!";
  }
  echo "</UL><DIV ALIGN='center'>\n";
  if ($final) echo "$final<br>\n";
  echo "<P>If everything went right, you can now proceed to the\n"
      ." <a href=\"../admin/configure.php\">configuration</a> page.</p></DIV>\n";
}

#=========================================================[ Closing page ]===
?>
</TD></TR></TABLE>
</BODY></HTML>
