<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Setup configuration options (display, languages, templates etc.)          #
 #############################################################################

 /* $Id$ */

 #=================================================[ Register global vars ]===
 while ( list($vn,$vv)=each($_POST) ) {
   $$vn = $vv;
 }

 #========================================================[ initial setup ]===
if (!isset($admin)) $admin = FALSE;
if ($menue) {
  $page_id = "configuration";
  if ($admin) $root = "../";
  include ($root . "inc/includes.inc");
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
  $url = $_SERVER["PHP_SELF"];
  if (isset($_POST["skip_intro"]))
    $pvp->preferences->set("skip_intro",$_POST["skip_intro"]);
  $pvp->preferences->set("lang",$_POST["default_lang"]);
  $pvp->preferences->set("template",$_POST["template_set"]);
  $pvp->preferences->set("imdb_url",$_POST["imdb_url"]);
  $pvp->preferences->set("imdb_url2",$_POST["imdb_url2"]);
  if (!isset($_POST["imdb_txwin_autoclose"])) $_POST["imdb_txwin_autoclose"] = 0;
  $pvp->preferences->set("imdb_txwin_autoclose",$_POST["imdb_txwin_autoclose"]);
  $pvp->preferences->set("page_length",$_POST["cpage_length"]);
  $pvp->preferences->set("display_limit",$_POST["cdisplay_limit"]);
  $pvp->preferences->set("date_format",$_POST["cdate_format"]);
  $pvp->preferences->set("default_movie_toneid",$_POST["movie_tone"]);
  $pvp->preferences->set("default_movie_colorid",$_POST["movie_color"]);
  $pvp->preferences->set("default_movie_langid",$_POST["movie_lang"]);
  $pvp->preferences->set("default_movie_pictid",$_POST["movie_pict"]);
  $pvp->preferences->set("default_vnorm_id",$_POST["movie_vnorm"]);
  if ($_POST["label_default"]) { $onlabel = "1"; } else { $onlabel = "0"; }
  $pvp->preferences->set("default_movie_onlabel",$onlabel);
  $pvp->preferences->set("printer_id",$_POST["cprinter_id"]);
  if (!isset($_POST["bubble_help_enable"])) $_POST["bubble_help_enable"] = 0;
  $pvp->preferences->set("bubble_help_enable",$_POST["bubble_help_enable"]);
  $mtypes = $db->get_mtypes();
  if ($admin) {
    unset($rw_media);
    for ($i=0;$i<count($mtypes);$i++) {
      $id    = $mtypes[$i]['id'];
      $mtype = "mtype_".$id;
      if (isset(${$mtype})) {
        if (isset($rw_media)) { $rw_media .= "," .$id; } else { $rw_media = $id; }
      }
    }
    if (!isset($_POST["http_cache_enable"])) $_POST["http_cache_enable"] = 0;
    $db->set_config("http_cache_enable",$_POST["http_cache_enable"]);
    if (!isset($_POST["imdb_cache_enable"])) $_POST["imdb_cache_enable"] = 0;
    $db->set_config("imdb_cache_enable",$_POST["imdb_cache_enable"]);
    if (!isset($_POST["imdb_cache_expire"])) $_POST["imdb_cache_expire"] = 0;
    $db->set_config("imdb_cache_expire",$_POST["imdb_cache_expire"]);
    if (!isset($_POST["imdb_cache_dir"])) $_POST["imdb_cache_dir"] = "";
    $db->set_config("imdb_cache_dir",$_POST["imdb_cache_dir"]);
    if (!isset($_POST["imdb_cache_use"])) $_POST["imdb_cache_enable"] = 0;
    $db->set_config("imdb_cache_use",$_POST["imdb_cache_use"]);
    $db->set_config("rw_media",$rw_media);
    if (!$_POST["remove_media"]) $remove_media = "0"; else $remove_media = "1";
    $db->set_config("remove_empty_media",$remove_media);
    if (!$_POST["enable_cookies"]) $enable_cookies = "0"; else $enable_cookies = "1";
    $db->set_config("enable_cookies",$enable_cookies);
    if (!$_POST["expire_cookies"]) $expire_cookies = "0"; else $expire_cookies = $_POST["expire_cookies"];
    $db->set_config("expire_cookies",$expire_cookies);
    if (!$_POST["session_purgetime"]) $session_purgetime = "0"; else $session_purgetime = $_POST["session_purgetime"];
    $db->set_config("session_purgetime",$session_purgetime);
    $db->set_config("site",$_POST["site_info"]);
    if (isset($_POST["install_lang"])) $install_lang = $_POST["install_lang"];
    else $install_lang = "";
    if ($install_lang && $install_lang != "-") {
      $sql_file = dirname(__FILE__) . "/lang_" . $install_lang . ".sql";
      queryf($sql_file,"Installation of additional language file",1);
    }
    $refresh_lang = $_POST["refresh_lang"];
    if ($refresh_lang && $refresh_lang != "-") {
      $db->delete_translations($refresh_lang);
      $sql_file = dirname(__FILE__) . "/lang_" . $refresh_lang . ".sql";
      queryf($sql_file,"Refresh of language phrases",1);
    }
    $delete_lang = $_POST["delete_lang"];
    if ($delete_lang && $delete_lang != "-" && $delete_lang != "en") {
      $db->delete_translations($delete_lang);
    }
  }
  #-----------------------------[ get available language files ]---
  if (isset($_POST["scan_langfile"]) && $_POST["scan_langfile"]) {
    chdir("$base_path/setup");
    $handle=opendir (".");
    while (false !== ($file = readdir ($handle))) {
      if ( substr($file,0,5) != "lang_" || substr($file,7) != ".sql") continue;
      $flang = substr($file,5,2);
      $db->lang_available($flang);
    }
    closedir($handle);
  }
  #-----------------------------[ IMDB Options ]---
  $imdb_tx = $db->imdb_tx_setup();
  foreach ($imdb_tx as $var=>$val) {
    if (isset ($_POST[$var])) $imdb_tx[$var] = 1; else $imdb_tx[$var] = 0;
  }
  $pvp->preferences->imdb_tx_set($imdb_tx);
  header("Location: " .$pvp->link->slink($url));
  exit;
}

 #========================================================[ get languages ]===
$lang_avail = $db->get_languages(1);
$langu = array();
for ($i=0;$i<count($lang_avail);$i++) {
  $langu[$lang_avail[$i]["id"]] = $lang_avail[$i]["name"];
}
if (isset($scan_langfile) && $scan_langfile) $lang_unavail = $db->get_languages(0);
$lang_installed = $db->get_installedlang();

#======================================================[ get preferences ]===
$lang_preferred = $pvp->preferences->get("lang");
$template_set   = $pvp->preferences->get("template");
$imdb_url       = $pvp->preferences->get("imdb_url");
$imdb_url2      = $pvp->preferences->get("imdb_url2");
$imdbtx         = $pvp->preferences->imdb_tx_get();
foreach ($imdbtx as $var=>$val) {
  ${$var} = $val;
}
$imdb_txwin_autoclose = $pvp->preferences->get("imdb_txwin_autoclose");
$imdb_cache_enable = $db->get_config("imdb_cache_enable");
$imdb_cache_expire = $db->get_config("imdb_cache_expire");
$imdb_cache_dir = $db->get_config("imdb_cache_dir");
$imdb_cache_use = $db->get_config("imdb_cache_use");
$cdisplay_limit = $pvp->preferences->get("display_limit");
$cpage_length   = $pvp->preferences->get("page_length");
$cdate_format   = $pvp->preferences->get("date_format");
$movie_tone     = $pvp->preferences->get("default_movie_toneid");
$movie_color    = $pvp->preferences->get("default_movie_colorid");
$movie_lang     = $pvp->preferences->get("default_movie_langid");
$movie_pict     = $pvp->preferences->get("default_movie_pictid");
$movie_vnorm    = $pvp->preferences->get("default_vnorm_id");
$label_default= $pvp->preferences->get("default_movie_onlabel");
$remove_media   = $db->get_config("remove_empty_media");
$enable_cookies = $db->get_config("enable_cookies");
$expire_cookies = $db->get_config("expire_cookies");
$session_purgetime = $db->get_config("session_purgetime");
$http_cache_enabled  = $db->get_config("http_cache_enable");
$bubble_help_enabled  = $pvp->preferences->get("bubble_help_enable");
$cprinter_id     = $pvp->preferences->get("printer_id");
$site_info      = $db->get_config("site");

if ($lang_preferred=='iw') $initial_input = "<span dir='LTR'>&nbsp;</span>";
else $initial_input = "";

#==========================================[ get available template sets ]===
chdir("$base_path/templates");
$handle=opendir (".");
while (false !== ($file = readdir ($handle))) {
 if ( in_array (strtolower($file), array("cvs",".","..")) ) continue;
 if ( is_dir($file) ) $tpldir[] = $file;
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
$t->set_var("formtarget",$_SERVER["PHP_SELF"]);

#----------------------------------------[ setup block 1: language stuff ]---
$t->set_var("list_head",lang("language_settings"));
$t->set_var("help_icon",$pvp->link->linkhelp($page_id."#lang"));

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
#    $select .= "<OPTION VALUE=\"" . $lang_avail[$i]["id"] . "\">" . $lang_avail[$i]["name"] . "</OPTION>";
#    $select .= "<OPTION VALUE=\"" . $lang_avail[$i]["id"] . "\">" . lang("lang_".$lang_avail[$i]["id"]) . "</OPTION>";
    $select .= "<OPTION VALUE=\"" . $lang_avail[$i]["id"] . "\">" . $lang_avail[$i]["name"] . " (".lang("lang_".$lang_avail[$i]["id"]).")</OPTION>";
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
#    $select .= ">" . $langu[$lang_installed[$i]] . "</OPTION>";
#    $select .= ">" . lang("lang_".$lang_installed[$i]) . "</OPTION>";
    $select .= ">" . $langu[$lang_installed[$i]] . " (".lang("lang_".$lang_installed[$i]).")</OPTION>";
  }
  $select .= "</SELECT>";
  $t->set_var("item_input",$select);
  $t->parse("item","itemblock",TRUE);

  #--[ remove an installed language? ]--
  $t->set_var("item_name",lang("delete_lang"));
  $t->set_var("item_comment",lang("delete_lang_comment"));
  $select  = "<SELECT NAME=\"delete_lang\">";
  $select .= "<OPTION VALUE=\"-\">-- " . lang("none") . " --</OPTION>";
  for ($i=0;$i<count($lang_installed);$i++) {
    if ($lang_installed[$i]=="en") continue;
    $select .= "<OPTION VALUE=\"" . $lang_installed[$i] . "\"";
#    $select .= ">" . $langu[$lang_installed[$i]] . "</OPTION>";
#    $select .= ">" . lang("lang_".$lang_installed[$i]) . "</OPTION>";
    $select .= ">" . $langu[$lang_installed[$i]] . " (".lang("lang_".$lang_installed[$i]).")</OPTION>";
  }
  $select .= "</SELECT>";
  $t->set_var("item_input",$select);
  $t->parse("item","itemblock",TRUE);
}

#--[ select primary language ]--
$t->set_var("item_name",lang("select_primary_lang"));
$t->set_var("item_comment",lang("select_primary_lang_comment"));
$select  = "<SELECT NAME=\"default_lang\" ID='prilang'";
if ($admin) $select .= " onChange='pri_lang()'";
$select .= ">";
for ($i=0;$i<count($lang_installed);$i++) {
  $select .= "<OPTION VALUE=\"" . $lang_installed[$i] . "\"";
  if ( $lang_installed[$i]==$lang_preferred ) $select .= " SELECTED";
  $select .= ">" . $langu[$lang_installed[$i]] . " (".lang("lang_".$lang_installed[$i]).")</OPTION>";
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

#-----------------------------------------[ setup block 3: movies & media ]---
$t->set_var("list_head",lang("config_media"));
$t->set_var("help_icon",$pvp->link->linkhelp($page_id."#media"));

if ($admin) {
  #--[ rw_media ]--
  $t->set_var("item_name",lang("rw_media"));
  $t->set_var("item_comment",lang("rw_media_comment"));
  unset ($id,$name);
  $input = $initial_input;
  $mtypes = $db->get_mtypes();
  for ($i=0;$i<count($mtypes);$i++) {
    $id[$i]   = $mtypes[$i]['id'];
    $name[$i] = $mtypes[$i]['sname'];
    if ($pvp->common->medium_is_rw($id[$i])) { $checked[$i] = " CHECKED"; } else { $checked[$i] = ""; }
    $input .= "<INPUT TYPE=\"checkbox\" NAME=\"mtype_" . $id[$i] . "\" $checked[$i] class=\"checkbox\">&nbsp;$name[$i]&nbsp;";
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
#if ($onlabel_default) {
if ($pvp->preferences->get("default_movie_onlabel")) {
  $t->set_var("item_input","<INPUT TYPE=\"checkbox\" NAME=\"label_default\" VALUE=\"1\" CHECKED>");
} else {
  $t->set_var("item_input","<INPUT TYPE=\"checkbox\" NAME=\"label_default\" VALUE=\"1\">");
}
if ($admin) {
  $t->parse("item","itemblock",TRUE);
} else {
  $t->parse("item","itemblock");
}

#--[ movie_tone_default ]--
$t->set_var("item_name",lang("movie_tone_default"));
$t->set_var("item_comment",lang("movie_tone_default_comment"));
unset($id);
$input = $initial_input;
$pict = $db->get_tone();
for ($i=0;$i<count($pict);$i++) {
  $id     = $pict[$i]['id'];
  $name   = lang($pict[$i]['name']);
  $input .= "<INPUT TYPE='radio' NAME='movie_tone' VALUE='$id'";
  if ($pvp->preferences->get("default_movie_toneid")==$id) {
    $input .= " CHECKED>$name &nbsp;"; } else { $input .= ">$name &nbsp;"; }
}
$t->set_var("item_input",$input);
$t->parse("item","itemblock",TRUE);

#--[ movie_color_default ]--
$t->set_var("item_name",lang("movie_color_default"));
$t->set_var("item_comment",lang("movie_color_default_comment"));
unset($id);
$input = $initial_input;
$pict = $db->get_color();
for ($i=0;$i<count($pict);$i++) {
  $id     = $pict[$i]['id'];
  $name   = lang($pict[$i]['name']);
  $input .= "<INPUT TYPE='radio' NAME='movie_color' VALUE='$id'";
  if ($pvp->preferences->get("default_movie_colorid")==$id) {
    $input .= " CHECKED>$name &nbsp;"; } else { $input .= ">$name &nbsp;"; }
}
$t->set_var("item_input",$input);
$t->parse("item","itemblock",TRUE);

#--[ movie_pict_default ]--
$t->set_var("item_name",lang("movie_pict_default"));
$t->set_var("item_comment",lang("movie_pict_default_comment"));
unset($id);
$input = $initial_input;
$pict = $db->get_pict();
$add['id'] = 0;
$add['name'] = "unknown";
$pict[] = $add;
unset ($add);
for ($i=0;$i<count($pict);$i++) {
  $id     = $pict[$i]['id'];
  $name   = lang($pict[$i]['name']);
  $input .= "<INPUT TYPE='radio' NAME='movie_pict' VALUE='$id'";
  if ($pvp->preferences->get("default_movie_pictid")==$id) {
    $input .= " CHECKED>$name &nbsp;"; } else { $input .= ">$name &nbsp;"; }
}
$t->set_var("item_input",$input);
$t->parse("item","itemblock",TRUE);

#--[ movie_vnorm_default ]--
$t->set_var("item_name",lang("movie_vnorm_default"));
$t->set_var("item_comment",lang("movie_vnorm_default_comment"));
$input = $initial_input;
$vnorms = $db->get_vnorms();
for ($i=0;$i<count($vnorms);++$i) {
  $input .= "<INPUT TYPE='radio' NAME='movie_vnorm' VALUE='".$vnorms[$i]["id"]."'";
  if ($movie_vnorm==$vnorms[$i]["id"]) $input .= " CHECKED";
  $input .= ">".$vnorms[$i]["name"]." &nbsp;";
}
$t->set_var("item_input",$input);
$t->parse("item","itemblock",TRUE);

#--[ movie_lang_default ]--
$t->set_var("item_name",lang("movie_lang_default"));
$t->set_var("item_comment",lang("movie_lang_default_comment"));
unset($id);
$pict = $db->get_avlang("audio");
unset ($add);
$select  = "<SELECT NAME=\"movie_lang\">";
$select .= "<OPTION VALUE=\"\">-- " . lang("none") . " --</OPTION>";
for ($i=0;$i<count($pict);$i++) {
  $select .= "<OPTION VALUE=\"" . $pict[$i]->id . "\"";
  if ($movie_lang==$pict[$i]->id)  $select .= " SELECTED";
  $select .= ">" .$pict[$i]->name. "</OPTION>";
}
$select .= "</SELECT>";
$t->set_var("item_input",$select);
$t->parse("item","itemblock",TRUE);

#--[ complete media block ]--
$t->parse("list","listblock",TRUE);

#------------------------------------------------[ setup block 4: cookies ]---
if ($admin) {
  $t->set_var("list_head",lang("cookies"));
  $t->set_var("help_icon",$pvp->link->linkhelp($page_id."#cookies"));

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
  if ($expire_cookies=="604800") $select .= " SELECTED";
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

#------------------------------------------[ setup block 5: imdb defaults ]---
$t->set_var("list_head","IMDB");
$t->set_var("help_icon",$pvp->link->linkhelp($page_id."#imdb"));

#--[ imdb_url ]--
$t->set_var("item_name",lang("imdb_url"));
$t->set_var("item_comment",lang("imdb_url_comment"));
$select  = "<SELECT NAME=\"imdb_url\">";
$imdburls = $db->get_options("imdb_url");
for ($i=0;$i<count($imdburls["imdb_url"]);++$i) {
  $select .= "<OPTION VALUE=\"" . $imdburls["imdb_url"][$i] . "\"";
  if ($imdburls["imdb_url"][$i] == $imdb_url) $select .= " SELECTED";
  $select .= ">" . $imdburls["imdb_url"][$i] . "</OPTION>";
}
$select .= "</SELECT>";
$t->set_var("item_input",$select);
$t->parse("item","itemblock");

#--[ imdb_url2 ]--
$t->set_var("item_name",lang("imdb_url2"));
$t->set_var("item_comment",lang("imdb_url2_comment"));
$select  = "<SELECT NAME=\"imdb_url2\">";
$imdburls = $db->get_options("imdb_url2");
for ($i=0;$i<count($imdburls["imdb_url2"]);++$i) {
  $select .= "<OPTION VALUE=\"" . $imdburls["imdb_url2"][$i] . "\"";
  if ($imdburls["imdb_url2"][$i] == $imdb_url2) $select .= " SELECTED";
  $select .= ">" . $imdburls["imdb_url2"][$i] . "</OPTION>";
}
$select .= "</SELECT>";
$t->set_var("item_input",$select);
$t->parse("item","itemblock",TRUE);

#--[ IMDB Transfer ]--
$t->set_var("item_name",lang("imdb_tx"));
$t->set_var("item_comment",lang("imdb_tx_comment"));
$select = "";
$imdbtx = $db->get_options("imdb_tx"); $count = count($imdbtx["imdb_tx"]);
for ($i=0;$i<$count;++$i) {
  $select .= "<INPUT TYPE='checkbox' CLASS='checkbox' NAME='".$imdbtx["imdb_tx"][$i]."'";
  if (${$imdbtx["imdb_tx"][$i]}) $select .= " CHECKED";
  $select .= ">".lang($imdbtx["imdb_tx"][$i])."&nbsp;";
}
$t->set_var("item_input",$select);
$t->parse("item","itemblock",TRUE);

#--[ Auto-close TX window ]--
$t->set_var("item_name",lang("imdb_txwin_autoclose"));
$t->set_var("item_comment",lang("imdb_txwin_autoclose_comment"));
$input = "<INPUT TYPE='radio' NAME='imdb_txwin_autoclose' VALUE='0'";
if (!$imdb_txwin_autoclose) $input .= " CHECKED";
$input .= ">".lang("no")."&nbsp;<INPUT TYPE='radio' NAME='imdb_txwin_autoclose' VALUE='1'";
if ($imdb_txwin_autoclose) $input .= " CHECKED";
$input .= ">".lang("yes");
$t->set_var("item_input",$input);
$t->parse("item","itemblock",TRUE);

if ($admin) {
  #--[ Enable Caching ]--
  $t->set_var("item_name",lang("imdb_cache_enable"));
  $t->set_var("item_comment",lang("imdb_cache_enable_comment"));
  $input = "<INPUT TYPE='radio' NAME='imdb_cache_enable' VALUE='0'";
  if (!$imdb_cache_enable) $input .= " CHECKED";
  $input .= ">".lang("no")."&nbsp;<INPUT TYPE='radio' NAME='imdb_cache_enable' VALUE='1'";
  if ($imdb_cache_enable) $input .= " CHECKED";
  $input .= ">".lang("yes");
  $t->set_var("item_input",$input);
  $t->parse("item","itemblock",TRUE);

  #--[ expiration time for cache ]==
  $t->set_var("item_name",lang("imdb_cache_expire"));
  $t->set_var("item_comment",lang("imdb_cache_expire_comment"));
  $select = "<SELECT NAME='imdb_cache_expire'><OPTION VALUE='0'";
  if (!$imdb_cache_expire) $select .= " SELECTED";
  $select .= ">" . lang("never") . "</OPTION><OPTION VALUE='86400'";
  if ($imdb_cache_expire=="86400") $select .= " SELECTED";
  $select .= ">1 " . lang("day") . "</OPTION><OPTION VALUE='604800'";
  if ($imdb_cache_expire=="604800") $select .= " SELECTED";
  $select .= ">1 " . lang("week") . "</OPTION><OPTION VALUE='2592000'";
  if ($imdb_cache_expire=="2592000") $select .= " SELECTED";
  $select .= ">1 " . lang("month") . "</OPTION><OPTION VALUE='31536000'";
  if ($imdb_cache_expire=="31536000") $select .= " SELECTED";
  $select .= ">1 " . lang("year") . "</OPTION></SELECT>";
  $t->set_var("item_input",$select);
  $t->parse("item","itemblock",TRUE);

  #--[ Cache directory ]--
  $t->set_var("item_name",lang("imdb_cache_dir"));
  $t->set_var("item_comment",lang("imdb_cache_dir_comment"));
  $t->set_var("item_input","<INPUT SIZE='20' NAME='imdb_cache_dir' VALUE='$imdb_cache_dir'>");
  $t->parse("item","itemblock",TRUE);

  #--[ Use the Cache for new requests? ]--
  $t->set_var("item_name",lang("imdb_cache_use"));
  $t->set_var("item_comment",lang("imdb_cache_use_comment"));
  $input = "<INPUT TYPE='radio' NAME='imdb_cache_use' VALUE='0'";
  if (!$imdb_cache_enable) $input .= " CHECKED";
  $input .= ">".lang("no")."&nbsp;<INPUT TYPE='radio' NAME='imdb_cache_use' VALUE='1'";
  if ($imdb_cache_enable) $input .= " CHECKED";
  $input .= ">".lang("yes");
  $t->set_var("item_input",$input);
  $t->parse("item","itemblock",TRUE);
}

#--[ complete imdb block ]--
$t->parse("list","listblock",TRUE);

#---------------------------------------------[ setup block 6: misc stuff ]---
$t->set_var("list_head",lang("general"));
$t->set_var("help_icon",$pvp->link->linkhelp($page_id."#general"));
$color_input = "<INPUT SIZE=\"7\" MAXLENGTH=\"7\"";

#--[ template set ]--
$t->set_var("item_name",lang("template_set"));
$t->set_var("item_comment","");
$select  = "<SELECT NAME=\"template_set\">";
for ($i=0;$i<count($tpldir);++$i) {
  $select .= "<OPTION VALUE=\"" . $tpldir[$i] . "\"";
  if ($tpldir[$i] == $template_set) $select .= " SELECTED";
  $select .= ">" . ucfirst($tpldir[$i]) . "</OPTION>";
}
$select .= "</SELECT>";
$t->set_var("item_input",$select);
$t->parse("item","itemblock");

#--[ bubble help ]--
$t->set_var("item_name",lang("bubble_help_enable"));
$t->set_var("item_comment",lang("bubble_help_enable_comment"));
$input = "<INPUT TYPE='radio' NAME='bubble_help_enable' VALUE='0'";
if (!$bubble_help_enabled) $input .= " CHECKED";
$input .= ">".lang("no")."&nbsp;<INPUT TYPE='radio' NAME='bubble_help_enable' VALUE='1'";
if ($bubble_help_enabled) $input .= " CHECKED";
$input .= ">".lang("yes");
$t->set_var("item_input",$input);
$t->parse("item","itemblock",TRUE);

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
$t->parse("item","itemblock",TRUE);

if ($admin) {
#--[ cache ]--
  $t->set_var("item_name",lang("cache_enable"));
  $t->set_var("item_comment",lang("cache_enable_comment"));
  $input = "<INPUT TYPE='radio' NAME='http_cache_enable' VALUE='0'";
  if (!$http_cache_enabled) $input .= " CHECKED";
  $input .= ">".lang("no")."&nbsp;<INPUT TYPE='radio' NAME='http_cache_enable' VALUE='1'";
  if ($http_cache_enabled) $input .= " CHECKED";
  $input .= ">".lang("yes");
  $t->set_var("item_input",$input);
  $t->parse("item","itemblock",TRUE);
} else {
#--[ skip the intro? ]--
  $t->set_var("item_name",lang("skip_intro"));
  $t->set_var("item_comment",lang("skip_intro_comment"));
  if ($pvp->preferences->get("skip_intro")) {
    $t->set_var("item_input","<INPUT TYPE=\"checkbox\" NAME=\"skip_intro\" VALUE=\"1\" CHECKED>");
  } else {
   $t->set_var("item_input","<INPUT TYPE=\"checkbox\" NAME=\"skip_intro\" VALUE=\"1\">");
  }
  $t->parse("item","itemblock",TRUE);
}

#--[ display_limit ]--
$t->set_var("item_name",lang("display_limit"));
$t->set_var("item_comment",lang("display_limit_comment"));
$t->set_var("item_input",$color_input . " NAME=\"cdisplay_limit\" VALUE=\"$cdisplay_limit\">");
$t->parse("item","itemblock",TRUE);

#--[ lines per page ]--
$t->set_var("item_name",lang("lines_per_page"));
$t->set_var("item_comment",lang("lines_per_page_comment"));
$t->set_var("item_input",$color_input . " NAME=\"cpage_length\" VALUE=\"$cpage_length\">");
$t->parse("item","itemblock",TRUE);

#--[ date_format ]--
$select  = "<SELECT NAME='cdate_format'><OPTION"; if ($cdate_format=="y-m-d") $select.=" SELECTED";
$select .= ">y-m-d</OPTION><OPTION"; if ($cdate_format=="d.m.y") $select .=" SELECTED";
$select .= ">d.m.y</OPTION><OPTION"; if ($cdate_format=="d/m/y") $select .=" SELECTED";
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
if (!$pvp->cookie->active) $t->set_var("sess_id","<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>");
$t->set_var("update","<INPUT TYPE=\"SUBMIT\" CLASS=\"submit\" NAME=\"update\" VALUE=\"" . lang("update") . "\">");
if ($menue && !(isset($update))) {
  include ($base_path . "inc/header.inc");
  if ($admin) {
?>
<script TYPE="text/javascript" language="JavaScript">//<!--
 function pri_lang() {
  var chk=window.confirm('<?=lang("confirm_prilang")?>');
  lang = document.getElementById('prilang');
  if (lang && !chk) {
    lang.value = '<?=$lang_preferred?>';
  }
 }
//--></script>
<?
  }
}
$t->pparse("out","config");
include($base_path . "inc/footer.inc");
?>