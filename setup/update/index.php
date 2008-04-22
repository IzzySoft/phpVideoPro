<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Setup program: Updating from previous version                             #
 #############################################################################

 /* $Id$ */

#========================================================[ initial setup ]===
$runupdate = 1;
include ("../../inc/config.inc");
include ("../../inc/config_internal.inc");
include ($base_path."inc/common_funcs.inc");
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

#=================================================[ Initiate media owner ]===
# Starting with v0.8.1, every user has his own set of media. Before, this
# was not the case - so the "old" media must belong to somebody...
function initiate_owner() {
  GLOBAL $db;
  $users = $db->get_users();
  $uc = count($users);
  echo "<h3>Welcome to version 0.8.1</h3>";
  echo "<p align='justify'>Starting with this version, every user maintains his/her "
     . "own set of media. Since this was not the case before, we need to know "
     . "who shall own all media created so far. Of course, ownership can be "
     . "changed later on at any time for any medium. For the initial "
     . "assignment, please chose the owner:</p><p><br></p>\n";
  echo "<div align='center'>\n <form name='owner_select' method='post' action='"
     . $_SERVER["PHP_SELF"]."?oldversion=0.8.0'><select name='owner_id'>";
  for ($i=0;$i<$uc;++$i) {
    echo "<option value='".$users[$i]->id."'>".ucfirst($users[$i]->login)."</option>";
  }
  echo "</select>\n <input type='submit' name='submit' value='OK'></form></div>\n";
  echo "</TD></TR></TABLE>\n";
  die ("</BODY></HTML>");
}
#=============================================[ Initiate (Default) VNorm ]===
# New fields have been introduced to the video table with v0.8.2
function initiate_vnorm() {
  echo "<h3>Welcome to version 0.8.2</h3>";
  echo "<p align='justify'>Amongst other features, this version introduces the "
     . "maintenance of the movies video norm. So here you can chose the defaults "
     . "to set for this in your phpVideoPro installation. If most of your movies "
     . "use the same video norm (which is quite usual), you also may want to "
     . "update your records accordingly:</p><p><br></p>";
  echo "<form name='vnorm_update' method='post' action='".$_SERVER["PHP_SELF"]
     . "?oldversion=0.8.1'>\n<table align='center' border='0'>\n"
     . " <tr><td>Default Video Norm:&nbsp;</td><td><select name='vnorm_id'>"
     . "<option value='1'>PAL</option><option value='2'>NTSC</option></select></td></tr>\n"
     . " <tr><td>Update records:</td><td><input type='checkbox' class='checkbox' name='update_rec' value='1'>"
     . "&nbsp;Yes, please</td></tr>\n</table>\n<div align='center'><input type='submit' name='submit' value='OK'></div>\n</form>\n";
  echo "</TD></TR></TABLE>\n";
  die ("</BODY></HTML>");
}

#=====================================[ Setup initial CD/DVD label packs ]===
function insert_cddvd_eps() {
  GLOBAL $db;
  $ins = "INSERT INTO pvp_epstemplates (type,pack_id,description,eps_filename,ps_filename,llx,lly,urx,ury) VALUES (";
  $db->query("$ins 3,2,'Action','action_cddvd.eps','common_cddvd.ps',0,0,468,474)");
  $db->query("$ins 3,2,'Comedy','comedy_cddvd.eps','common_cddvd.ps',0,0,468,474)");
  $db->query("$ins 3,2,'Doku','docu_cddvd.eps','common_cddvd.ps',0,0,468,474)");
  $db->query("$ins 3,2,'SciFi','sf_cddvd.eps','common_cddvd.ps',0,0,468,474)");
  $db->query("$ins 3,2,'Simple','simple_cddvd.eps','common_cddvd.ps',0,0,468,474)");
  $db->query("INSERT INTO pvp_pspacks (id,rev,sname,name,descript,creator) VALUES (2,1,'pvplcs','Simple Color CD/DVD Labels','CD/DVD labels just using simple  colored background (originally shipped with phpVideoPro v0.8.5)','Izzy ([url]http://projects.izzysoft.de/?topic=progs;subject=phpvideopro[/url])')");
  $db->query("$ins 3,3,'Marmor','marmor_cddvd.eps','common_cddvd.ps',0,0,468,474)");
  $db->query("$ins 3,3,'Sky','sky_cddvd.eps','common_cddvd.ps',0,0,468,474)");
  $db->query("$ins 3,3,'Water','water_cddvd.eps','common_cddvd.ps',0,0,468,474)");
  $db->query("$ins 3,3,'Pool','pool_cddvd.eps','common_cddvd.ps',0,0,468,474)");
  $db->query("$ins 3,3,'Electronic','electronic_cddvd.eps','common_cddvd.ps',0,0,468,474)");
  $db->query("$ins 3,3,'Citrus','citrus_cddvd.eps','common_cddvd.ps',0,0,468,474)");
  $db->query("$ins 3,3,'World','world_cddvd.eps','common_cddvd.ps',0,0,468,474)");
  $db->query("$ins 3,3,'Clouds','clouds_cddvd.eps','common_cddvd.ps',0,0,468,474)");
  $db->query("$ins 3,3,'Celtic','celtic_cddvd.eps','common_cddvd.ps',0,0,470,468)");
  $db->query("INSERT INTO pvp_pspacks (id,rev,sname,name,descript,creator) VALUES (3,1,'pvplcp','Simple Pix CD/DVD Labels','CD/DVD labels using simple picture background (originally shipped with phpVideoPro v0.8.5)','Izzy ([url]http://projects.izzysoft.de/?topic=progs;subject=phpvideopro[/url])')");
  echo " <LI><SPAN CLASS='ok'>PSLabelPacks updated.</SPAN></LI>";
}

#====================================================[ Output page intro ]===
echo "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>\n";
echo "<HTML><HEAD>\n";
echo " <META http-equiv='Content-Type' content='text/html; charset=utf-8'>\n";
echo " <LINK HREF='".$base_url."templates/default/default.css' rel='stylesheet' type='text/css'>\n";

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
if ( !isset($_REQUEST["oldversion"]) ) {
  $oldversion = get_version();
?>
<TR><TH>Preamble</TH></TR>
<TR><TD>
<P ALIGN=JUSTIFY>This simple script will update your database from a previous
 version of phpVideoPro to the recent one. I strongly recommend you to backup
 your existing database before executing the script! Furthermore, please
 inspect inc/config.inc for possible changes.</P>
<P ALIGN=JUSTIFY>For each update step, you should then be notified whether it
 was successfull or not. So now, if you've made your backup
 (or decided not to backup at all), we can go on with the update process.</P>
<P ALIGN=JUSTIFY>The version of phpVideoPro's database which is installed on
 your machine appears to be <b>v<? echo $oldversion ?></b>. If this is <b>not</b>
 what you've expected, please <b><font color="#ff0000">PANIC</font></b> now!
 Otherwise (which <b>I</b> expect to be the case), click the button below to
 <b>do</b> the real update...</p>
<?
$button = "<DIV ALIGN='center'><A HREF='".$_SERVER["PHP_SELF"]
        ."?oldversion=$oldversion'><IMG BORDER='0' SRC='".$base_url
        ."templates/default/images/button-next.gif'></A></DIV>";
#========================================================[ Do the update ]===
} else {
  echo "<TR><TH>Updating...</TH></TR>\n<TR><TD>";
  $final = "";
  echo "<UL>\n";

$pvp->preferences->admin();
#-----------------[ Get SQL statements from their files and execute them ]---
  switch ($_REQUEST["oldversion"]) {
    case "0.1.0"    : queryf("0-1-0_to_0-1-1.sql","Upgrade to v0.1.1");
    case "0.1.1"    : queryf("0-1-1_to_0-1-2.sql","Upgrade to v0.1.2");
    case "0.1.2"    :
    case "0.1.3"    :
    case "0.1.4"    : queryf("0-1-4_to_0-1-5.sql","Upgrade to v0.1.6");
    case "0.1.5"    :
    case "0.1.6"    :
    case "0.1.7"    : queryf("0-1-7_to_0-2-0.sql","Upgrade to v0.2.0");
    case "0.2.0"    : queryf("0-2-0_to_0-2-1." . $database["type"],"Upgrade to v0.2.1");
    case "0.2.1"    : queryf("0-2-1_to_0-2-2." . $database["type"],"Upgrade to v0.2.2");
    case "0.2.2"    : queryf("0-2-2_to_0-2-3.sql","Upgrade to v0.2.3");
    case "0.2.3"    :
    case "0.2.4"    :
    case "0.2.5"    : queryf("0-2-5_to_0-2-6.sql","Upgrade to v0.2.6");
    case "0.2.6"    : queryf("0-2-6_to_0-2-7." . $database["type"],"Upgrade to v0.2.7");
    case "0.2.7"    : queryf("0-2-7_to_0-2-8.sql","Upgrade to v0.2.8");
                      queryf("../install/categories.sql","Refresh of categories");
    case "0.2.8"    :
    case "0.3.0"    :
    case "0.3.1"    :
    case "0.3.2"    :
    case "0.3.3"    : queryf("0-3-3_to_0-3-4.".$database["type"],"Upgrade to v0.3.4");
    case "0.3.4"    :
    case "0.3.5"    :
    case "0.3.6"    : queryf("0-3-6_to_0-3-7.".$database["type"],"Upgrade to v0.3.7");
		      $colors = $pvp->preferences->colors;
		      unset($colors["page_background"]);
		      unset($colors["table_background"]);
		      unset($colors["th_background"]);
		      $pvp->preferences->set("colors",rawurlencode( serialize($colors) ));
    case "0.3.7"    :
    case "0.3.8"    :
    case "0.4.0"    : queryf("0-4-0_to_0-4-1.".$database["type"],"Upgrade to v0.4.1");
    case "0.4.1"    : queryf("pslabel.".$database["type"],"Set up of PSLabel tables");
    case "0.4.2"    :
    case "0.4.3"    :
    case "0.4.4"    : queryf("0-4-2_to_0-4-5.sql","Upgrade to v0.4.5");
                      $commenturl = 1;
    case "0.4.5"    :
    case "0.4.6"    : queryf("0-4-6_to_0-4-7.sql","Upgrade to v0.4.7");
    case "0.4.7"    : queryf("0-4-7_to_0-4-8.sql","Upgrade to v0.4.8");
    case "0.4.8"    : 
                      include ("cleanconfig.php");
    case "0.5.0"    : queryf("0-5-0_to_0-5-1.".$database["type"],"Upgrade to v0.5.1");
    case "0.5.1"    :
    case "0.5.2"    :
    case "0.5.3"    : queryf("0-5-3_to_0-5-4.sql","Upgrade to v0.5.4");
    case "0.5.4"    : queryf("0-5-4_to_0-5-5.sql","Upgrade to v0.5.5");
    case "0.5.5"    : 
    case "0.5.6"    :
    case "0.5.7"    :
    case "0.5.8"    :
    case "0.6.0"    : queryf("0-6-0_to_0-6-1.".$database["type"],"Upgrade to v0.6.1");
    case "0.6.1"    : queryf("0-6-1_to_0-6-2.".$database["type"],"Upgrade to v0.6.2");
    case "0.6.2"    : $db2utf8 = TRUE;
    case "0.6.3"    :
    case "0.6.4"    :
    case "0.6.5"    : queryf("0-6-5_to_0-6-6.".$database["type"],"Upgrade to v0.6.6");
    case "0.6.6"    :
    case "0.6.7"    :
    case "0.6.8"    :
    case "0.6.9"    :
    case "0.6.10"   :
    case "0.6.11"   : queryf("0-6-6_to_0-7-0.sql","Upgrade to v0.7.0");
    case "0.7.0"    :
    case "0.7.1"    : queryf("0-7-1_to_0-7-2.sql","Upgrade to v0.7.2");
                      $db->query("SELECT DISTINCT lang AS lang FROM lang");
                      while ($db->next_record()) $lav[] = $db->f('lang');
                      queryf("../install/languages.sql","Refresh of language data");
                      foreach ($lav as $lavv) $db->query("UPDATE languages SET available='Yes' where lang_id='$lavv'");
    case "0.7.2"    : queryf("0-7-2_to_0-7-3.sql","Upgrade to v0.7.3");
    case "0.7.3"    : queryf("0-7-3_to_0-7-4.sql","Upgrade to v0.7.4");
    case "0.7.4"    : queryf("0-7-4_to_0-7-5.sql","Upgrade to v0.7.5");
    case "0.7.5"    :
    case "0.7.6"    :
    case "0.7.7"    :
    case "0.7.8"    :
    case "0.7.9"    : queryf("0-7-5_to_0-7-6.sql","Upgrade to v0.8.0");
                      $langs = $db->get_installedlang();
                      if (in_array("fr",$langs)) {
                        $db->delete_translations("fr");
                        queryf("../lang_fr.sql","Refresh of French language support");
                      }
    case "0.8.0"    : if (!isset($_POST["owner_id"])) initiate_owner();
                      queryf("0-8-0_to_0-8-1.".$database["type"],"Upgrade to v0.8.1");
                      queryf("../lang_en.sql","Refresh of English language support");
                      $db->query("UPDATE pvp_users SET id=0 WHERE login='PUBLIC'");
                      $db->query("UPDATE pvp_media SET owner=".$_POST["owner_id"]);
                      $query = "INSERT INTO pvp_media (id,mtype_id,owner)"
                             . " SELECT v.cass_id,v.mtype_id,".$_POST["owner_id"]
                             . "   FROM video v"
                             . "   LEFT JOIN pvp_media m ON (v.mtype_id=m.mtype_id AND v.cass_id=m.id)"
                             . "  WHERE m.id IS NULL";
                      $db->query($query); // fix orphaned movies
    case "0.8.1"    : if (!isset($_POST["vnorm_id"])) initiate_vnorm();
                      queryf("0-8-1_to_0-8-2.".$database["type"],"Upgrade to v0.8.2");
                      queryf("../lang_en.sql","Refresh of English language support");
                      $db->query("INSERT INTO preferences (name,value) VALUES ('default_vnorm_id','".$_POST["vnorm_id"]."')");
                      if ($_POST["update_rec"]) {
                        $db->query("UPDATE pvp_video SET vnorm_id=".$_POST["vnorm_id"]);
                      }
    case "0.8.2"    :
    case "0.8.3"    : queryf("0-8-2_to_0-8-3.sql","Upgrade to v0.8.4");
    case "0.8.4"    : queryf("0-8-4_to_0-8-5.sql","Upgrade to v0.8.5");
    case "0.8.5"    : queryf("0-8-5_to_0-8-6.".$database["type"],"Upgrade to v0.8.6");
                      if (file_exists($base_path."pslabels".$pvp->config->os_slash."celtic_cddvd.eps"))
                        insert_cddvd_eps();
    case "0.8.6"    : queryf("0-8-6_to_0-8-7.sql","Upgrade to v0.8.7");
    case "0.8.7"    : queryf("0-8-7_to_0-8-8.sql","Upgrade to v0.8.8");
    case "0.8.8"    : 
    case "0.9.0"    : 
    case "0.9.1"    : queryf("0-8-8_to_0-9-0.sql","Upgrade to v0.9.2");
                      queryf("../lang_en.sql","Refresh of English language support");
                      break;
    default         : $final = "Your database version seems to be current, there's nothing I can update for you!";
  }
  echo "</UL><DIV ALIGN='center'>\n";
  if ($final) echo "$final<br>\n";
  if (isset($commenturl))
    echo "<P>If you want to automatically update your movie comments with the "
       . "[url] tags introduced by v0.4.5 (see history for details), please "
       . "follow <A HREF='commenturl.php'>this link</A>.</P>\n";
  if (isset($db2utf8)) {
   echo "<P ALIGN='justify'>At this stage we need to convert all database content to the "
       ."UTF-8 character set. Please follow <a href='db2utf8.php'>this link</a> "
       ."now for this process. You only need to do this once, and you will be "
       ."guided through that process. More details (also about the background) "
       ."you will find on the page the link points to.</P>";
  } else {
   echo "<HR><P>If everything went right, you can now go to the\n"
      ." <a href='".$base_url."login.php'>Login</a> page - or, if you are already"
      ." logged in, just <a href='".$base_url."index.php'>continue</a> working "
      . "with phpVideoPro. To find out what has changed since your last update,"
      ." you can see the \"History\" link in the help menu. In case you want"
      ." to check your settings again, just follow"
      ." <a href='".$base_url."admin/configure.php'>this link</a>.</p></DIV>\n";
  } // end db2utf8
}

#=========================================================[ Closing page ]===
echo "</TD></TR></TABLE>\n";
if (isset($button)) echo $button;
?>
</BODY></HTML>
