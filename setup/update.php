<? // create the tables for phpVideoPro

/* $Id$ */

##################################################################
# Configuration of Setup module
#
  include ("../inc/config.inc");
  include ("../inc/common_funcs.inc");
  include ("../inc/db_mysql.inc");
  include ("../inc/sql_helpers.inc");
  $db = new DB_Sql;
  $db->Host     = $database["host"];
  $db->Database = $database["database"];
  $db->User     = $database["user"];
  $db->Password = $database["password"];
  if ( !strpos(strtoupper($debug["log"]),"D")===false ) $db->Debug=1;


##################################################################
# Output page intro
# 
  echo "<HTML><HEAD>\n";
  echo " <META http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">\n";
  $title = "phpVideoPro v$version: ";
  if ( !isset($oldversion) ){
    $title .= "Updating the Database";
  } else {
    $title .= "Updating from v$oldversion";
  }
  echo " <TITLE>$title</TITLE>\n</HEAD>\n<BODY>\n";
  
  if ( !isset($oldversion) ) {
  ?>

<H2 ALIGN=CENTER><? echo $title ?></H2>
<P ALIGN=JUSTIFY>This simple script will update your database from a previous
 version of phpVideoPro to the recent one. I strongly recommend you to backup
 your existing database before executing the script! As for now, the previously
 installed version of phpVideoPro is not yet autodetected, so you have to
 specify it manually. For each update step, you should then be notified wether
 it was successfull or not. So if the amount of "comments" on the following page
 is less than the number of the upgrade you select from the list below, there
 probably went something wrong. Of course, if there are errors reported, you can
 be sure that something went wrong :) So now, if you've made your backup (or
 decided not to backup at all), select the version you are upgrading from:</P>
<OL>
 <LI><A HREF="<? echo $PHP_SELF ?>?oldversion=0.1.0">v0.1.0</A>
</OL><?
  } else {
    echo "<UL>\n";

    ##################################################################
    # Get SQL statements from their files and execute them
    switch ($oldversion) {
      case "0.1.0"    : queryf("0-1-0_to_0-1-1.sql","Update from v0.1.0 to v0.1.1");
      case "0.1.1"    : break;
      default         : break;
    }
    echo "</UL>\n";
  }

##################################################################
# Closing page
# ?>
</BODY></HTML>
