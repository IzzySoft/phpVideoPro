<? // create the tables for phpVideoPro
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
# Helper functions
#
  # read a file containing sql statements and execute the statements one-by-one
  function get_sql($file) {
    $array = file ($file);
    $sql   = ""; $ok = 1;
    for ($i=0;$i<count($array);$i++) {
      $pos  = strpos(" " . trim($array[$i]),"#");
      if ($pos<>1) {
        $sql .= $array[$i];
        $endpos = strpos($sql,";");
        if ($endpos) {
          $sql = substr($sql,0,$endpos);
          if ( !dbquery($sql) ) $ok = 0;
          $sql = "";
        }
      }
    }
    return $ok;
  }

  function queryf($file,$comment) {
    GLOBAL $colors;
    if ( get_sql($file) ) {
      echo $colors["ok"] . " <li>$comment successful.</Font><BR>\n";
    } else {
      echo $colors["err"] . " <li>$comment failed, process stopped.</Font><BR>\n";
      exit;
    }
  }

##################################################################
# Output page intro
# 
  $title = "phpVideoPro v$version: Setting up the Database"; ?>
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
  $tables   = queryf("create_tables.sql","Creation of tables");
  $cats     = queryf("categories.sql","Insertion of categories");
  $techdata = queryf("tech_data.sql","Insertion of technical data");

##################################################################
# Closing page
# ?>
</UL>
</BODY></HTML>
