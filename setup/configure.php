<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Setup configuration options (display, languages, templates etc.)          *
 \***************************************************************************/

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
    $colors["page_background"]  = $page_background;
    $colors["table_background"] = $table_background;
    $colors["th_background"]    = $th_background;
    $colors["ok"]               = $color_ok;
    $colors["err"]              = $color_err;
    dbquery("UPDATE preferences SET value='$default_lang' WHERE name='lang'");
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
  $title = "phpVideoPro v$version: " . lang("configuration");
  if (!$menue) {
    echo "<HTML><HEAD>\n";
    echo " <META http-equiv=\"Content-Type\" content=\"text/html; charset=$charset\">\n";
    echo " <TITLE>$title</TITLE>\n</HEAD>\n<BODY>\n";
    include($base_path . "inc/template.inc");
  }
  $t = new Template($pvp->tpl_dir);
  $t->set_file(array("config"=>"configure.tpl",
                     "configEnd"=>"config_end.tpl"));
  $t->set_block("config","listblock","list");
  $t->set_block("listblock","itemblock","item");

  # setup configEnd when invoked from Setup
  if (!$menue) {
    $t->set_var("pvp_start","<A HREF=\"../index.php\">" . lang("start_pvp") . "</A>");
    $t->parse("config_end","configEnd");
  } else {
    $t->set_var("config_end","");
  }

  # generate the complete page  
  $t->set_var("listtitle",$title);
  $t->set_var("formtarget",$PHP_SELF);

  # setup block 1: language stuff
  $t->set_var("list_head",lang("language_settings"));

  # scan for new language files?
  $t->set_var("item_name",lang("scan_new_lang_files"));
  $t->set_var("item_comment",lang("scan_new_lang_comment"));
  $t->set_var("item_input","<INPUT TYPE=\"checkbox\" NAME=\"scan_langfile\" VALUE=\"1\">");
  $t->parse("item","itemblock");

  # additional language to install?
  $t->set_var("item_name",lang("select_add_lang"));
  $t->set_var("item_comment",lang("select_add_lang_comment"));
  $select = "<SELECT NAME=\"install_lang\">";
  $none = TRUE;
  for ($i=0;$i<count($lang_avail);$i++) {
    if ( in_array($lang_avail[$i]["id"],$lang_installed) ) continue;
    $select .= "<OPTION VALUE=\"" . $lang_avail[$i]["id"] . "\">" . $lang_avail[$i]["name"] . "</OPTION>";
    $none = FALSE;
  }
  if (!$none) $select .= "<OPTION VALUE=\"-\">-- " . lang("none") ." --</OPTION>";
  $select .= "</SELECT>";
  if ($none) $select = lang("no_add_lang");
  $t->set_var("item_input",$select);
  $t->parse("item","itemblock",TRUE);

  # refresh an installed language?
  $t->set_var("item_name",lang("refresh_lang"));
  $t->set_var("item_comment",lang("refresh_lang_comment"));
  $select  = "<SELECT NAME=\"refresh_lang\">";
  $select .= "<OPTION VALUE=\"-\">-- " . lang("none") . " --</OPTION>";
  for ($i=0;$i<count($lang_installed);$i++) {
    $select .= "<OPTION VALUE=\"" . $lang_installed[$i] . "\"";
    $select .= ">" . $lang[$lang_installed[$i]] . "</OPTION>";
  }
  $select .= "</SELECT>";
  $t->set_var("item_input",$select);
  $t->parse("item","itemblock",TRUE);

  # select primary language
  $t->set_var("item_name",lang("select_primary_lang"));
  $t->set_var("item_comment",lang("select_primary_lang_comment"));
  $select  = "<SELECT NAME=\"default_lang\">";
  for ($i=0;$i<count($lang_installed);$i++) {
    $select .= "<OPTION VALUE=\"" . $lang_installed[$i] . "\"";
    if ( $lang_installed[$i]==$lang_preferred ) $select .= " SELECTED";
    $select .= ">" . $lang[$lang_installed[$i]] . "</OPTION>";
  }
  $select .= "</SELECT>";
  $t->set_var("item_input",$select);
  $t->parse("item","itemblock",TRUE);

  # complete language block
  $t->parse("list","listblock");

  # setup block 2: color stuff
  $t->set_var("list_head",lang("colors"));
  $color_input = "<INPUT SIZE=\"7\" MAXLENGTH=\"7\"";

  # page background
  $t->set_var("item_name",lang("page_bg"));
  $t->set_var("item_comment","");
  $t->set_var("item_input",$color_input . " NAME=\"page_background\" VALUE=\"" . $colors["page_background"] . "\">");
  $t->parse("item","itemblock");

  # table background
  $t->set_var("item_name",lang("table_bg"));
  $t->set_var("item_comment","");
  $t->set_var("item_input",$color_input . " NAME=\"table_background\" VALUE=\"" .  $colors["table_background"] . "\">");
  $t->parse("item","itemblock",TRUE);

  # table header background
  $t->set_var("item_name",lang("th_bg"));
  $t->set_var("item_comment","");
  $t->set_var("item_input",$color_input . " NAME=\"th_background\" VALUE=\"" . $colors["th_background"] . "\">");
  $t->parse("item","itemblock",TRUE);

  # feedback "ok"
  $t->set_var("item_name",lang("feedback_ok"));
  $t->set_var("item_comment","");
  $t->set_var("item_input",$color_input . " NAME=\"color_ok\" VALUE=\"" . $colors["ok"] . "\">");
  $t->parse("item","itemblock",TRUE);

  # feedback "err"
  $t->set_var("item_name",lang("feedback_err"));
  $t->set_var("item_comment","");
  $t->set_var("item_input",$color_input . " NAME=\"color_err\" VALUE=\"" . $colors["err"] . "\">");
  $t->parse("item","itemblock",TRUE);

  # template set
  $t->set_var("item_name",lang("template_set"));
  $t->set_var("item_comment","");
  $select  = "<SELECT NAME=\"template_set\">";
  for ($i=0;$i<count($tpldir);$i++) {
    $select .= "<OPTION VALUE=\"" . $tpldir[$i] . "\"";
    if ($tpldir[$i] == $template_set) $select .= " SELECTED";
    $select .= ">" . ucfirst($tpldir[$i]) . "</OPTION>";
  }
  $select .= "</SELECT>";
  $t->set_var("item_input",$select);
  $t->parse("item","itemblock",TRUE);

  # complete color block
  $t->parse("list","listblock",TRUE);

  # complete the whole thing
  $t->set_var("update","<INPUT TYPE=\"SUBMIT\" NAME=\"update\" VALUE=\"" . lang("update") . "\">");
  $t->pparse("out","config");

  include($base_path . "inc/footer.inc");
?>