<? // create the tables for phpVideoPro

/* $Id$ */

##################################################################
# Configuration of Configuration module
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

  #---------------------------------[ get available languages ]---
  dbquery("SELECT lang_id,lang_name,available FROM languages WHERE available='yes'");
  $i = 0;
  while ( $db->next_record() ) {
//    if ( $db->f('lang_id') == "en" ) continue;
    $lang_avail[$i]["id"]   = $db->f('lang_id');
    $lang_avail[$i]["name"] = $db->f('lang_name');
    $i++;
  }

  #---------------------------------[ get installed languages ]---
  dbquery("SELECT distinct lang FROM lang");
  $i = 0;
  while ( $db->next_record() ) {
    $lang_installed[$i] = $db->f('lang');
    $i++;
  }

  #---------------------------------[ get preferred languages ]---
  dbquery("SELECT value FROM preferences WHERE name='lang'");
  if ( $db->next_record() ) {
    $lang_preferred = $db->f('value');
  } else {
    debug("E","No default language set in DB!");
  }

  #-----------------------------------[ get configured colors ]---
  dbquery("SELECT value FROM preferences WHERE name='colors'");
  if ( $db->next_record() ) {
    $colors   = unserialize ( rawurldecode( $db->f('value') ) );
  } else {
    debug("E","No colors in db?!?");
  }

  #----------------------------------[ get configured charset ]---
  dbquery("SELECT value FROM preferences WHERE name='charset'");
  if ( $db->next_record() ) {
    $charset = $db->f('value');
  } else {
    debug("E","No charset in db?!?");
  }

##################################################################
# Output page intro
# 
  echo "<HTML><HEAD>\n";
  echo " <META http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">\n";
  $title = "phpVideoPro v$version: Configuration";
  echo " <TITLE>$title</TITLE>\n</HEAD>\n<BODY>\n";
  echo "<H2 ALIGN=CENTER>$title</H2>\n";
  echo "<TABLE ALIGN=CENTER WIDTH=90%>\n";
  
  if ( !isset($update) ) {
  ?>

<FORM NAME="config_form" METHOD="post" ACTION="<? echo $PHP_SELF ?>">
<TR><TD><b>Select additional language to install:</b><br>(English is already installed and always will be - see next item. For other languages that are already installed, see next item, too.)</TD>
    <TD><?
  $select = "<SELECT NAME=\"install_lang\">";
  $none = TRUE;
  for ($i=0;$i<count($lang_avail);$i++) {
    if ( in_array($lang_avail[$i]["id"],$lang_installed) ) continue;
    $select .= "<OPTION VALUE=\"" . $lang_avail[$i]["id"] . "\">" . $lang_avail[$i]["name"] . "</OPTION>";
    $none = FALSE;
  }
  $select .= "</SELECT>";
?><? if ($none) { echo "No additional language available."; } else { echo $select; } ?></TD></TR>
<TR><TD><b>Select primary language:</b><br>(for missing phrases, there will always be a fall-back to English)</TD>
    <TD><SELECT NAME="default_lang"><?
  for ($i=0;$i<count($lang_avail);$i++) {
    echo "<OPTION VALUE=\"" . $lang_avail[$i]["id"] . "\"";
    if ( $lang_avail[$i]["id"]==$lang_preferred ) echo " SELECTED";
    echo ">" . $lang_avail[$i]["name"] . "</OPTION>";
  }
?></SELECT></TD></TR>
<TR><TD><b>Enter charset to use:</b><br>(this is important for character encoding; if unsure, don't touch :)</TD>
    <TD><INPUT SIZE=10 NAME="charset" VALUE="<? echo $charset ?>"></TD></TR>
<TR><TD COLSPAN=2><b>Colors:</b></TD></TR>
<TR><TD>&nbsp;&nbsp;<b>Page Background:</b></TD>
    <TD><INPUT SIZE="7" MAXLENGTH="7" NAME=colors["page_background"] VALUE="<? echo $colors["page_background"] ?>"></TD></TR>
<TR><TD>&nbsp;&nbsp;<b>Table Headers Background:</b></TD>
    <TD><INPUT SIZE="7" MAXLENGTH="7" NAME=colors["th_background"] VALUE="<? echo $colors["th_background"] ?>"></TD></TR>
<TR><TD>&nbsp;&nbsp;<b>Feedback "OK":</b></TD>
    <TD><INPUT SIZE="7" MAXLENGTH="7" NAME=colors["ok"] VALUE="<? echo $colors["ok"] ?>"></TD></TR>
<TR><TD>&nbsp;&nbsp;<b>Feedback "Failure":</b></TD>
    <TD><INPUT SIZE="7" MAXLENGTH="7" NAME=colors["err"] VALUE="<? echo $colors["err"] ?>"></TD></TR>
<TR><TD COLSPAN=2 ALIGN=CENTER><hr><INPUT TYPE="SUBMIT" NAME="update" VALUE="Update"></TD></TR>
</FORM>
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
                        break;
      default         : $final = "Hey - you're already running the latest db version, there's nothing I could update for you!";
    }
    echo "</UL>\n";
    if ($final) echo "$final<br>\n";
  }

##################################################################
# Closing page
# ?>
</TABLE>
</BODY></HTML>
