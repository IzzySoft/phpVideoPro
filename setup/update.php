<? // create the tables for phpVideoPro

/* $Id$ */

##################################################################
# Configuration of Setup module
#
  include ("../inc/config.inc");
  include ("../inc/db_mysql.inc");
  include ("../inc/common_funcs.inc");
  include ("../inc/sql_helpers.inc");
  $db = new DB_Sql;
  $db->Host     = $database["host"];
  $db->Database = $database["database"];
  $db->User     = $database["user"];
  $db->Password = $database["password"];
  if ( !strpos(strtoupper($debug["log"]),"D")===false ) $db->Debug=1;

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
  echo "<H2 ALIGN=CENTER>$title</H2>\n";
  echo "<TABLE ALIGN=CENTER WIDTH=90%><TR><TD>\n";
  
  if ( !isset($oldversion) ) {
    $oldversion = get_version();
  ?>

<P ALIGN=JUSTIFY>This simple script will update your database from a previous
 version of phpVideoPro to the recent one. I strongly recommend you to backup
 your existing database before executing the script! Furthermore, please
 inspect config.inc for possible changes.</P>
<P ALIGN=JUSTIFY>For each update step, you should then be notified wether it
 was successfull or not. So if the amount of "comments" on the following page
 is less than the number of the upgrade you select from the list below, there
 probably went something wrong. Of course, if there are errors reported, you
 can be sure that something went wrong :) So now, if you've made your backup
 (or decided not to backup at all), we can go on with the update process.</P>
<P ALIGN=JUSTIFY>The version of phpVideoPro's database which is installed on
 your machine appears to be v<? echo $oldversion ?>. If this is <b>not</b>
 what you've expected, please <b><font color="#ff0000">PANIC</font></b> now!
 Otherwise (which <b>I</b> expect to be the case), follow this nice little
 <a href="<? echo "$PHP_SELF?oldversion=$oldversion" ?>">link</a> to finally
 <b>do</b> the real update...</p>
<?
  } else {
    $final = "";
    echo "<UL>\n";

    ##################################################################
    # Get SQL statements from their files and execute them
    switch ($oldversion) {
      case "0.1.0"    : queryf("0-1-0_to_0-1-1.sql","Update from v0.1.0 to v0.1.1");
      case "0.1.1"    : queryf("0-1-1_to_0-1-2.sql","Update from v0.1.1 to v0.1.2");
                        queryf("lang_en.sql","Activation of English language support");
      case "0.1.2"    : queryf("0-1-2_to_0-1-3.sql","Update from v0.1.2 to v0.1.3");
      case "0.1.3"    : queryf("0-1-3_to_0-1-4.sql","Update from v0.1.3 to v0.1.4");
                        queryf("lang_en.sql","Refresh of English language support");
      case "0.1.4"    : queryf("0-1-4_to_0-1-5.sql","Update from v0.1.4 to v0.1.5");
                        break;
      default         : $final = "Your database version seems to be current, there's nothing I can update for you!";
    }
    echo "</UL>\n";
    if ($final) echo "$final<br>\n";
    echo "<P ALIGN=JUSTIFY>If everything went right, you can now proceed to the\n"
        ." <a href=\"configure.php\">configuration</a> page.</p>\n";
  }

##################################################################
# Closing page
# ?>
</TD></TR></TABLE>
</BODY></HTML>
