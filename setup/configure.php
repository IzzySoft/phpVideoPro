<? // configuring phpVideoPro

/* $Id$ */

##################################################################
# Configuration of Configuration module
#
if ($menue) {
  $page_id = "configuration";
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
    $url = $PHP_SELF;
    $colors["page_background"] = $page_background;
    $colors["th_background"]   = $th_background;
    $colors["ok"]              = $color_ok;
    $colors["err"]             = $color_err;
    dbquery("UPDATE preferences SET value='$default_lang' WHERE name='lang'");
    dbquery("UPDATE preferences SET value='$charset' WHERE name='charset'");
    dbquery("UPDATE preferences SET value='$template_set' WHERE name='template'");
    $colorcode = rawurlencode( serialize($colors) );
    dbquery("UPDATE preferences SET value='$colorcode' WHERE name='colors'");
    if ($install_lang && $install_lang != "-") {
      $sql_file = dirname(__FILE__) . "/lang_" . $install_lang . ".sql";
      queryf($sql_file,"Installation of additional language file",1);
    }
    if ($refresh_lang && $refresh_lang != "-") {
      dbquery("DELETE FROM lang WHERE lang='$refresh_lang'");
      $sql_file = dirname(__FILE__) . "/lang_" . $refresh_lang . ".sql";
      queryf($sql_file,"Refresh of language phrases",1);
    }
    #-----------------------------[ get available language files ]---
    if ($scan_langfile) {
      chdir("$base_path/setup");
      $handle=opendir (".");
      while (false !== ($file = readdir ($handle))) {
        if ( substr($file,0,5) != "lang_" || substr($file,7) != ".sql") continue;
        $flang = substr($file,5,2);
        dbquery("UPDATE languages SET available='yes' WHERE lang_id='$flang'");
      }
      closedir($handle);
    }
    ?><HTML><HEAD>
      <meta http-equiv="refresh" content="0; URL=<? echo $url ?>">
    </HEAD></HTML><?
    exit;
  }

  #---------------------------------[ get available languages ]---
  dbquery("SELECT lang_id,lang_name,available FROM languages WHERE available='yes'");
  $i = 0;
  while ( $db->next_record() ) {
    $lang_avail[$i]["id"]   = $db->f('lang_id');
    $lang_avail[$i]["name"] = $db->f('lang_name');
    $lang[$lang_avail[$i]["id"]] = $lang_avail[$i]["name"];
    $i++;
  }

  #-------------------------------[ get unavailable languages ]---
  if ($scan_langfile) {
    dbquery("SELECT lang_id,lang_name,available FROM languages WHERE available='no'");
    $i = 0;
    while ( $db->next_record() ) {
      $lang_unavail[$i]["id"]   = $db->f('lang_id');
      $i++;
    }
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

  #---------------------------------------[ get user template ]---
  dbquery("SELECT value FROM preferences WHERE name='template'");
  if ( $db->next_record() ) {
    $template_set = $db->f('value');
  } else {
    debug("E","No user template in db?!?");
  }

##################################################################
# Obtain settings from file system
#
  #------------------------------[ get available template sets ]---
  chdir("$base_path/templates");
  $handle=opendir (".");
  $i = 0;
  while (false !== ($file = readdir ($handle))) {
   if ( in_array (strtolower($file), array("cvs",".","..")) ) continue;
   if ( is_dir($file) ) $tpldir[$i] = $file;
  }
  closedir($handle);
  chdir("$base_path/setup");



##################################################################
# Output page intro
# 
  echo "<HTML><HEAD>\n";
  echo " <META http-equiv=\"Content-Type\" content=\"text/html; charset=$charset\">\n";
  $title = "phpVideoPro v$version: Configuration";
  echo " <TITLE>$title</TITLE>\n</HEAD>\n<BODY>\n";
  echo "<H2 ALIGN=CENTER>$title</H2>\n";
  echo "<TABLE ALIGN=CENTER WIDTH=90% BORDER=1>\n";
  ?>

<FORM NAME="config_form" METHOD="post" ACTION="<? echo $PHP_SELF ?>">
<TR><TH>Language Settings:</TH></TR>
<TR><TD><TABLE WIDTH=100%>
 <TR><TD WIDTH=70%><b>Scan for new language files?</b><br>(If you created your own language file and put it into the setup directory, this will tell phpVideoPro to look for it)</TD>
    <TD WIDTH=30%><INPUT TYPE="checkbox" NAME="scan_langfile" VALUE="1"></TD></TR>
 <TR><TD WIDTH=70%><b>Select additional language to install:</b><br>(English is already installed and always will be - see next item. For other languages that are already installed, see next item, too.)</TD>
    <TD WIDTH=30%><?
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
 <TR><TD><b>Refresh language:</b><br>(re-insert phrases from language file into db)</TD>
    <TD><SELECT NAME="refresh_lang"><?
  echo "<OPTION VALUE=\"-\">-- None --</OPTION>";
  for ($i=0;$i<count($lang_installed);$i++) {
    echo "<OPTION VALUE=\"" . $lang_installed[$i] . "\"";
    echo ">" . $lang[$lang_installed[$i]] . "</OPTION>";
  }
?></SELECT></TD></TR>
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
</TABLE></TD></TR>
<TR><TH>Colors:</TH></TR><TR><TD><TABLE WIDTH=100%>
 <TR><TD WIDTH=70%>&nbsp;&nbsp;<b>Page Background:</b></TD>
    <TD WIDTH=30%><INPUT SIZE="7" MAXLENGTH="7" NAME="page_background" VALUE="<? echo $colors["page_background"] ?>"></TD></TR>
 <TR><TD>&nbsp;&nbsp;<b>Table Headers Background:</b></TD>
    <TD><INPUT SIZE="7" MAXLENGTH="7" NAME="th_background" VALUE="<? echo $colors["th_background"] ?>"></TD></TR>
 <TR><TD>&nbsp;&nbsp;<b>Feedback "OK":</b></TD>
    <TD><INPUT SIZE="7" MAXLENGTH="7" NAME="color_ok" VALUE="<? echo $colors["ok"] ?>"></TD></TR>
 <TR><TD>&nbsp;&nbsp;<b>Feedback "Failure":</b></TD>
    <TD><INPUT SIZE="7" MAXLENGTH="7" NAME="color_err" VALUE="<? echo $colors["err"] ?>"></TD></TR>
 <TR><TD>&nbsp;&nbsp;<b>Template Set:</b></TD>
    <TD><SELECT NAME="template_set"><?
 for ($i=0;$i<count($tpldir);$i++) {
   echo "<OPTION VALUE=\"" . $tpldir[$i] . "\"";
   if ($tpldir[$i] == $template_set) echo " SELECTED";
   echo ">" . ucfirst($tpldir[$i]) . "</OPTION>";
 } ?></SELECT></TD></TR>
</TABLE></TD></TR>
<TR><TD ALIGN=CENTER><INPUT TYPE="SUBMIT" NAME="update" VALUE="Update"></TD></TR>
</FORM>
<?

##################################################################
# Closing page
# ?>
<? if (!$menue) { ?><TR><TD COLSPAN=2 ALIGN=CENTER><A HREF="../index.php">Start phpVideoPro</A></TD></TR><? } ?>
</TABLE>
</BODY></HTML>
