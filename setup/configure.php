<? // configuring phpVideoPro

/* $Id$ */

##################################################################
# Configuration of Configuration module
#
// $referer = substr(dirname($HTTP_REFERER),strlen(dirname($HTTP_REFERER))-6);
// if ($referer=="/setup" || $referer=="") {
if ($menue) {
  $page_id = "configure";
  if ($update) {
    include ("inc/config.inc");
    include ("inc/config_internal.inc");
    include ("inc/common_funcs.inc");
    include ("inc/sql_helpers.inc");
  } else {
    include ("inc/header.inc");
  }
} else {
  include ("../inc/config.inc");
  include ("../inc/config_internal.inc");
  include ("../inc/common_funcs.inc");
  include ("../inc/sql_helpers.inc");
}

##################################################################
# Update changes (when submitted)
#
  if ( isset($update) ) {
    $colors["page_background"] = $page_background;
    $colors["th_background"]   = $th_background;
    $colors["ok"]              = $color_ok;
    $colors["err"]             = $color_err;
    dbquery("UPDATE preferences SET value='$default_lang' WHERE name='lang'");
    dbquery("UPDATE preferences SET value='$charset' WHERE name='charset'");
    $colorcode = rawurlencode( serialize($colors) );
    dbquery("UPDATE preferences SET value='$colorcode' WHERE name='colors'");
    if ($install_lang && $install_lang != "-") {
      $sql_file = "lang_" . $install_lang . ".sql";
      queryf($sql_file,"Installation of additional language file",1);
    }?>
    <HTML><HEAD>
      <meta http-equiv="refresh" content="0; URL=<? echo $PHP_SELF ?>">
    </HEAD></HTML><?
    exit;
  }

##################################################################
# Obtain settings from DB
#
  #---------------------------------[ get available languages ]---
  dbquery("SELECT lang_id,lang_name,available FROM languages WHERE available='yes'");
  $i = 0;
  while ( $db->next_record() ) {
    $lang_avail[$i]["id"]   = $db->f('lang_id');
    $lang_avail[$i]["name"] = $db->f('lang_name');
    $lang[$lang_avail[$i]["id"]] = $lang_avail[$i]["name"];
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
  echo " <META http-equiv=\"Content-Type\" content=\"text/html; charset=$charset\">\n";
  $title = "phpVideoPro v$version: Configuration";
  echo " <TITLE>$title</TITLE>\n</HEAD>\n<BODY>\n";
  echo "<H2 ALIGN=CENTER>$title</H2>\n";
  echo "<TABLE ALIGN=CENTER WIDTH=90%>\n";
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
  if (!$none) $select .= "<OPTION VALUE=\"-\">-- None --</OPTION>";
  $select .= "</SELECT>";
?><? if ($none) { echo "No additional language available."; } else { echo $select; } ?></TD></TR>
<TR><TD><b>Select primary language:</b><br>(for missing phrases, there will always be a fall-back to English)</TD>
    <TD><SELECT NAME="default_lang"><?
  for ($i=0;$i<count($lang_installed);$i++) {
    echo "<OPTION VALUE=\"" . $lang_installed[$i] . "\"";
    if ( $lang_installed[$i]==$lang_preferred ) echo " SELECTED";
    echo ">" . $lang[$lang_installed[$i]] . "</OPTION>";
  }
?></SELECT></TD></TR>
<TR><TD><b>Enter charset to use:</b><br>(this is important for character encoding; if unsure, don't touch :)</TD>
    <TD><INPUT SIZE=10 NAME="charset" VALUE="<? echo $charset ?>"></TD></TR>
<TR><TD COLSPAN=2><b>Colors:</b></TD></TR>
<TR><TD>&nbsp;&nbsp;<b>Page Background:</b></TD>
    <TD><INPUT SIZE="7" MAXLENGTH="7" NAME="page_background" VALUE="<? echo $colors["page_background"] ?>"></TD></TR>
<TR><TD>&nbsp;&nbsp;<b>Table Headers Background:</b></TD>
    <TD><INPUT SIZE="7" MAXLENGTH="7" NAME="th_background" VALUE="<? echo $colors["th_background"] ?>"></TD></TR>
<TR><TD>&nbsp;&nbsp;<b>Feedback "OK":</b></TD>
    <TD><INPUT SIZE="7" MAXLENGTH="7" NAME="color_ok" VALUE="<? echo $colors["ok"] ?>"></TD></TR>
<TR><TD>&nbsp;&nbsp;<b>Feedback "Failure":</b></TD>
    <TD><INPUT SIZE="7" MAXLENGTH="7" NAME="color_err" VALUE="<? echo $colors["err"] ?>"></TD></TR>
<TR><TD COLSPAN=2 ALIGN=CENTER><hr><INPUT TYPE="SUBMIT" NAME="update" VALUE="Update"></TD></TR>
</FORM>
<?

##################################################################
# Closing page
# ?>
<TR><TD COLSPAN=2 ALIGN=CENTER><P><BR></P></TD></TR>
<? if (!$menue) { ?><TR><TD COLSPAN=2 ALIGN=CENTER><A HREF="../index.php">Start phpVideoPro</A></TD></TR><? } ?>
</TABLE>
</BODY></HTML>
