<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Setup configuration options (display, languages, templates etc.)          #
 #############################################################################

 /* $Id$ */

#========================================================[ initial setup ]===
if ($menue) {
  $page_id = "configuration";
  if ($admin) $root = "../";
#  if ($update) {
#    include ($root . "inc/config.inc");
#    include ($root . "inc/config_internal.inc");
#    include ($root . "inc/common_funcs.inc");
#  } else {
    include ($root . "inc/includes.inc");
#  }
} else {
  include ("../inc/config.inc");
  include ("../inc/config_internal.inc");
  include ("../inc/common_funcs.inc");
  include("../templates/default/default.css");
}

if ($admin) {
  if (!$pvp->auth->admin) kickoff();
  $pvp->preferences->admin();
}
#============================================[ On Submit: Update changes ]===
if ( isset($update) ) {
  $url = $PHP_SELF;
  $colors["ok"]               = $color_ok;
  $colors["err"]              = $color_err;
  $pvp->preferences->set("lang",$default_lang);
  $pvp->preferences->set("template",$template_set);
  $pvp->preferences->set("display_limit",$display_limit);
  $pvp->preferences->set("page_length",$page_length);
  $pvp->preferences->set("date_format",$date_format);
  $pvp->preferences->set("default_movie_toneid",$movie_tone);
  $pvp->preferences->set("default_movie_colorid",$movie_color);
  $pvp->preferences->set("default_movie_onlabel",$onlabel_default);
  $pvp->preferences->set("printer_id",$cprinter_id);
  $mtypes = $db->get_mtypes();
  if ($admin) {
    unset($rw_media);
    for ($i=0;$i<count($mtypes);$i++) {
      $id    = $mtypes[$i][id];
      $mtype = "mtype_".$id;
      if (${$mtype}) {
        if (strlen($rw_media)) { $rw_media .= "," .$id; } else { $rw_media = $id; }
      }
    }
    $db->set_config("rw_media",$rw_media);
    if (!$remove_media) $remove_media = "0";
    $db->set_config("remove_empty_media",$remove_media);
    if (!$enable_cookies) $enable_cookies = "0";
    $db->set_config("enable_cookies",$enable_cookies);
    if (!$expire_cookies) $expire_cookies = "0";
    $db->set_config("expire_cookies",$expire_cookies);
    $db->set_config("session_purgetime",$session_purgetime);
    if (!$session_purgetime) $session_purgetime = "0";
    $db->set_config("site",$site_info);
    if ($install_lang && $install_lang != "-") {
      $sql_file = dirname(__FILE__) . "/lang_" . $install_lang . ".sql";
      queryf($sql_file,"Installation of additional language file",1);
    }
    if ($refresh_lang && $refresh_lang != "-") {
      $db->delete_translations($refresh_lang);
      $sql_file = dirname(__FILE__) . "/lang_" . $refresh_lang . ".sql";
      queryf($sql_file,"Refresh of language phrases",1);
    }
  }
  $colorcode = rawurlencode( serialize($colors) );
  if ($admin) $pvp->preferences->set("colors",$colorcode);
  #-----------------------------[ get available language files ]---
  if ($scan_langfile) {
    chdir("$base_path/setup");
    $handle=opendir (".");
    while (false !== ($file = readdir ($handle))) {
      if ( substr($file,0,5) != "lang_" || substr($file,7) != ".sql") continue;
      $flang = substr($file,5,2);
      $db->lang_available($flang);
    }
    closedir($handle);
  }
  ?><HTML><HEAD>
      <meta http-equiv="refresh" content="0; URL=<? echo $url ?>">
    </HEAD></HTML><?
  exit;
}

#========================================================[ get languages ]===
$lang_avail = $db->get_languages(1);
for ($i=0;$i<count($lang_avail);$i++) {
  $langu[$lang_avail[$i]["id"]] = $lang_avail[$i]["name"];
}
if ($scan_langfile) $lang_unavail = $db->get_languages(0);
$lang_installed = $db->get_installedlang();

#======================================================[ get preferences ]===
$lang_preferred = $pvp->preferences->get("lang");
$colors         = $pvp->preferences->get("colors");
$template_set   = $pvp->preferences->get("template");
$display_limit  = $pvp->preferences->get("display_limit");
$page_length    = $pvp->preferences->get("page_length");
$date_format    = $pvp->preferences->get("date_format");
$movie_tone     = $pvp->preferences->get("default_movie_toneid");
$movie_color    = $pvp->preferences->get("default_movie_colorid");
$onlabel_default= $pvp->preferences->get("default_movie_onlabel");
$remove_media   = $db->get_config("remove_empty_media");
$enable_cookies = $db->get_config("enable_cookies");
$expire_cookies = $db->get_config("expire_cookies");
$session_purgetime = $db->get_config("session_purgetime");
$cprinter_id     = $pvp->preferences->get("printer_id");
$site_info      = $db->get_config("site");

#==========================================[ get available template sets ]===
chdir("$base_path/templates");
$handle=opendir (".");
$i = 0;
while (false !== ($file = readdir ($handle))) {
 if ( in_array (strtolower($file), array("cvs",".","..")) ) continue;
 if ( is_dir($file) ) $tpldir[$i] = $file;
}
closedir($handle);
chdir("$base_path/setup");


#====================================================[ Output page intro ]===
$title = "phpVideoPro v$version: " . lang("configuration");
if (!$menue) {
  echo "<HTML><HEAD>\n";
  echo " <META http-equiv=\"Content-Type\" content=\"text/html; charset=$charset\">\n";
  echo " <TITLE>$title</TITLE>\n</HEAD>\n<BODY>\n";
  include($base_path . "inc/class.template.inc");
}
$t = new Template($pvp->tpl_dir);
$t->set_file(array("config"=>"configure.tpl",
                   "configEnd"=>"config_end.tpl"));
$t->set_block("config","listblock","list");
$t->set_block("listblock","itemblock","item");

#------------------------------[ setup configEnd when invoked from Setup ]---
if (!$menue) {
  $t->set_var("pvp_start","<A HREF=\"../index.php\">" . lang("start_pvp") . "</A>");
  $t->parse("config_end","configEnd");
} else {
  $t->set_var("config_end","");
}

#===========================================[ generate the complete page ]===
$t->set_var("listtitle",$title);
$t->set_var("formtarget",$PHP_SELF);

#----------------------------------------[ setup block 1: language stuff ]---
$t->set_var("list_head",lang("language_settings"));

if ($admin) {
  #--[ scan for new language files? ]--
  $t->set_var("item_name",lang("scan_new_lang_files"));
  $t->set_var("item_comment",lang("scan_new_lang_comment"));
  $t->set_var("item_input","<INPUT TYPE=\"checkbox\" NAME=\"scan_langfile\" VALUE=\"1\">");
  $t->parse("item","itemblock");

  #--[ additional language to install? ]--
  $t->set_var("item_name",lang("select_add_lang"));
  $t->set_var("item_comment",lang("select_add_lang_comment"));
  $select = "<SELECT NAME=\"install_lang\">";
  $none = TRUE;
  for ($i=0;$i<count($lang_avail);$i++) {
    if ( in_array($lang_avail[$i]["id"],$lang_installed) ) continue;
    $select .= "<OPTION VALUE=\"" . $lang_avail[$i]["id"] . "\">" . $lang_avail[$i]["name"] . "</OPTION>";
    $none = FALSE;
  }
  if (!$none) $select .= "<OPTION VALUE=\"-\" SELECTED>-- " . lang("none") ." --</OPTION>";
  $select .= "</SELECT>";
  if ($none) $select = lang("no_add_lang");
  $t->set_var("item_input",$select);
  $t->parse("item","itemblock",TRUE);

  #--[ refresh an installed language? ]--
  $t->set_var("item_name",lang("refresh_lang"));
  $t->set_var("item_comment",lang("refresh_lang_comment"));
  $select  = "<SELECT NAME=\"refresh_lang\">";
  $select .= "<OPTION VALUE=\"-\">-- " . lang("none") . " --</OPTION>";
  for ($i=0;$i<count($lang_installed);$i++) {
    $select .= "<OPTION VALUE=\"" . $lang_installed[$i] . "\"";
    $select .= ">" . $langu[$lang_installed[$i]] . "</OPTION>";
  }
  $select .= "</SELECT>";
  $t->set_var("item_input",$select);
  $t->parse("item","itemblock",TRUE);
}

#--[ select primary language ]--
$t->set_var("item_name",lang("select_primary_lang"));
$t->set_var("item_comment",lang("select_primary_lang_comment"));
$select  = "<SELECT NAME=\"default_lang\">";
for ($i=0;$i<count($lang_installed);$i++) {
  $select .= "<OPTION VALUE=\"" . $lang_installed[$i] . "\"";
  if ( $lang_installed[$i]==$lang_preferred ) $select .= " SELECTED";
  $select .= ">" . $langu[$lang_installed[$i]] . "</OPTION>";
}
$select .= "</SELECT>";
$t->set_var("item_input",$select);
if ($admin) {
  $t->parse("item","itemblock",TRUE);
} else {
  $t->parse("item","itemblock");
}

#--[ complete language block ]--
$t->parse("list","listblock");

#-------------------------------------------[ setup block 2: color stuff ]---
$t->set_var("list_head",lang("colors"));
$color_input = "<INPUT SIZE=\"7\" MAXLENGTH=\"7\"";

if ($admin) { // this color array has probs with cookies
  #--[ feedback "ok" ]--
  $t->set_var("item_name",lang("feedback_ok"));
  $t->set_var("item_comment","");
  $t->set_var("item_input",$color_input . " NAME=\"color_ok\" VALUE=\"" . $colors["ok"] . "\">");
  $t->parse("item","itemblock");

  #--[ feedback "err" ]--
  $t->set_var("item_name",lang("feedback_err"));
  $t->set_var("item_comment","");
  $t->set_var("item_input",$color_input . " NAME=\"color_err\" VALUE=\"" . $colors["err"] . "\">");
  $t->parse("item","itemblock",TRUE);
}

#--[ template set ]--
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
if ($admin) {
  $t->parse("item","itemblock",TRUE);
} else {
  $t->parse("item","itemblock");
}

#--[ complete color block ]--
$t->parse("list","listblock",TRUE);

#-----------------------------------------[ setup block 3: movies & media ]---
$t->set_var("list_head",lang("config_media"));

if ($admin) {
  #--[ rw_media ]--
  $t->set_var("item_name",lang("rw_media"));
  $t->set_var("item_comment",lang("rw_media_comment"));
  unset ($id,$name,$input);
  $mtypes = $db->get_mtypes();
  for ($i=0;$i<count($mtypes);$i++) {
    $id[$i]   = $mtypes[$i][id];
    $name[$i] = $mtypes[$i][sname];
    if ($pvp->common->medium_is_rw($id[$i])) { $checked[$i] = " CHECKED"; } else { $checked[$i] = ""; }
    $input .= "<INPUT TYPE=\"checkbox\" NAME=\"mtype_" . $id[$i] . "\" . $checked[$i] class=\"checkbox\">&nbsp;$name[$i]&nbsp;";
  }
  $t->set_var("item_input",$input);
  $t->parse("item","itemblock");

  #--[ remove_empty_media ]--
  $t->set_var("item_name",lang("remove_empty_media"));
  $t->set_var("item_comment",lang("remove_empty_media_comment"));
  if ($remove_media) {
    $t->set_var("item_input","<INPUT TYPE=\"checkbox\" NAME=\"remove_media\" VALUE=\"1\" CHECKED>");
  } else {
    $t->set_var("item_input","<INPUT TYPE=\"checkbox\" NAME=\"remove_media\" VALUE=\"1\">");
  }
  $t->parse("item","itemblock",TRUE);
}

#--[ default_movie_onlabel ]--
$t->set_var("item_name",lang("movie_onlabel_default"));
$t->set_var("item_comment",lang("movie_onlabel_default_comment"));
if ($onlabel_default) {
  $t->set_var("item_input","<INPUT TYPE=\"checkbox\" NAME=\"onlabel_default\" VALUE=\"1\" CHECKED>");
} else {
  $t->set_var("item_input","<INPUT TYPE=\"checkbox\" NAME=\"onlabel_default\" VALUE=\"1\">");
}
if ($admin) {
  $t->parse("item","itemblock",TRUE);
} else {
  $t->parse("item","itemblock");
}

#--[ movie_tone_default ]--
$t->set_var("item_name",lang("movie_tone_default"));
$t->set_var("item_comment",lang("movie_tone_default_comment"));
unset($id,$input);
$pict = $db->get_tone();
for ($i=0;$i<count($pict);$i++) {
  $id     = $pict[$i][id];
  $name   = $pict[$i][name];
  $input .= "<INPUT TYPE='radio' NAME='movie_tone' VALUE='$id'";
  if ($pvp->preferences->get("default_movie_toneid")==$id) {
    $input .= " CHECKED>$name &nbsp;"; } else { $input .= ">$name &nbsp;"; }
}
$t->set_var("item_input",$input);
$t->parse("item","itemblock",TRUE);

#--[ movie_color_default ]--
$t->set_var("item_name",lang("movie_color_default"));
$t->set_var("item_comment",lang("movie_color_default_comment"));
unset($id,$input);
$pict = $db->get_color();
for ($i=0;$i<count($pict);$i++) {
  $id     = $pict[$i][id];
  $name   = $pict[$i][name];
  $input .= "<INPUT TYPE='radio' NAME='movie_color' VALUE='$id'";
  if ($pvp->preferences->get("default_movie_colorid")==$id) {
    $input .= " CHECKED>$name &nbsp;"; } else { $input .= ">$name &nbsp;"; }
}
$t->set_var("item_input",$input);
$t->parse("item","itemblock",TRUE);

#--[ complete media block ]--
$t->parse("list","listblock",TRUE);

#------------------------------------------------[ setup block 4: cookies ]---
if ($admin) {
  $t->set_var("list_head",lang("cookies"));

  #--[ enable_cookies ]--
  $t->set_var("item_name",lang("enable_cookies"));
  $t->set_var("item_comment",lang("enable_cookies_comment"));
  if ($enable_cookies) {
    $t->set_var("item_input","<INPUT TYPE=\"checkbox\" NAME=\"enable_cookies\" VALUE=\"1\" CHECKED>");
  } else {
    $t->set_var("item_input","<INPUT TYPE=\"checkbox\" NAME=\"enable_cookies\" VALUE=\"1\">");
  }
  $t->parse("item","itemblock");

  #--[ expiration time for cookies ]==
  $t->set_var("item_name",lang("expire_cookies"));
  $t->set_var("item_comment",lang("expire_cookies_comment"));
  $select = "<SELECT NAME='expire_cookies'><OPTION VALUE='0'";
  if (!$expire_cookies) $select .= " SELECTED";
  $select .= ">" . lang("session") . "</OPTION><OPTION VALUE='86400'";
  if ($expire_cookies=="86400") $select .= " SELECTED";
  $select .= ">1 " . lang("day") . "</OPTION><OPTION VALUE='604800'";
  if ($expire_cookies=="604000") $select .= " SELECTED";
  $select .= ">1 " . lang("week") . "</OPTION><OPTION VALUE='2592000'";
  if ($expire_cookies=="2592000") $select .= " SELECTED";
  $select .= ">1 " . lang("month") . "</OPTION><OPTION VALUE='31536000'";
  if ($expire_cookies=="31536000") $select .= " SELECTED";
  $select .= ">1 " . lang("year") . "</OPTION></SELECT>";
  $t->set_var("item_input",$select);
  $t->parse("item","itemblock",TRUE);

  #--[ session purgetime (timeout) ]--
  $t->set_var("item_name",lang("session_purgetime"));
  $t->set_var("item_comment",lang("session_purgetime_comment"));
  $select = "<SELECT NAME='session_purgetime'><OPTION VALUE='0'";
  if (!$session_purgetime) $select .= " SELECTED";
  $select .= ">" . lang("never") . "</OPTION><OPTION VALUE='3600'";
  if ($session_purgetime=="3600") $select .= " SELECTED";
  $select .= ">1 " . lang("hour") . "</OPTION><OPTION VALUE='7200'";
  if ($session_purgetime=="7200") $select .= " SELECTED";
  $select .= ">2 " . lang("hours") . "</OPTION><OPTION VALUE='21600'";
  if ($session_purgetime=="21600") $select .= " SELECTED";
  $select .= ">6 " . lang("hours") . "</OPTION><OPTION VALUE='43200'";
  if ($session_purgetime=="43200") $select .= " SELECTED";
  $select .= ">12 " . lang("hours") . "</OPTION><OPTION VALUE='86400'";
  if ($session_purgetime=="86400") $select .= " SELECTED";
  $select .= ">1 " . lang("day") . "</OPTION><OPTION VALUE='604800'";
  if ($session_purgetime=="604800") $select .= " SELECTED";
  $select .= ">1 " . lang("week") . "</OPTION></SELECT>";
  $t->set_var("item_input",$select);
  $t->parse("item","itemblock",TRUE);

  #--[ complete cookie block ]--
  $t->parse("list","listblock",TRUE);
}

#---------------------------------------------[ setup block 5: misc stuff ]---
$t->set_var("list_head",lang("general"));

#--[ printer_id ]--
$t->set_var("item_name",lang("printer"));
$t->set_var("item_comment",lang("printer_comment"));
$printers = $db->get_printer();
$select = "<SELECT NAME='cprinter_id'>";
for ($i=0;$i<count($printers);++$i) {
  $select .= "<OPTION VALUE='" .$printers[$i]->id . "'";
  if ($cprinter_id==$printers[$i]->id) $select .= " SELECTED";
  $select .= ">" .$printers[$i]->name. "</OPTION>";
}
$select .= "</SELECT>";
$t->set_var("item_input",$select);
$t->parse("item","itemblock");

#--[ display_limit ]--
$t->set_var("item_name",lang("display_limit"));
$t->set_var("item_comment",lang("display_limit_comment"));
$t->set_var("item_input",$color_input . " NAME=\"display_limit\" VALUE=\"$display_limit\">");
$t->parse("item","itemblock",TRUE);

#--[ lines per page ]--
$t->set_var("item_name",lang("lines_per_page"));
$t->set_var("item_comment",lang("lines_per_page_comment"));
$t->set_var("item_input",$color_input . " NAME=\"page_length\" VALUE=\"$page_length\">");
$t->parse("item","itemblock",TRUE);

#--[ date_format ]--
$select  = "<SELECT NAME='date_format'><OPTION"; if ($date_format=="y-m-d") $select.=" SELECTED";
$select .= ">y-m-d</OPTION><OPTION"; if ($date_format=="d.m.y") $select .=" SELECTED";
$select .= ">d.m.y</OPTION><OPTION"; if ($date_format=="d/m/y") $select .=" SELECTED";
$select .= ">d/m/y</OPTION></SELECT>";
$t->set_var("item_name",lang("date_format"));
$t->set_var("item_comment",lang("date_format_comment"));
$t->set_var("item_input",$select);
$t->parse("item","itemblock",TRUE);

#--[ site info ]--
if ($admin) {
  $t->set_var("item_name",lang("site_info"));
  $t->set_var("item_comment",lang("site_info_comment"));
  $t->set_var("item_input","<INPUT SIZE='20' NAME='site_info' VALUE='$site_info'>");
  $t->parse("item","itemblock",TRUE);
}

#--[ complete misc block ]--
$t->parse("list","listblock",TRUE);


#--[ complete the whole thing ]--
if (!$pvp->config->enable_cookies) $t->set_var("sess_id","<INPUT TYPE='hidden' NAME='sess_id' VALUE='$sess_id'>");
$t->set_var("update","<INPUT TYPE=\"SUBMIT\" NAME=\"update\" VALUE=\"" . lang("update") . "\">");
if ($menue && !$update) include ($base_path . "inc/header.inc");
$t->pparse("out","config");

include($base_path . "inc/footer.inc");
?>