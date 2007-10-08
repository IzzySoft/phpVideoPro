<?
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # ! internals - don't edit anything in this files - unless you exactly know #
 # ! what you are doing (or advised by the author ;) !                       #
 #############################################################################

  /* $Id$ */

 #=======================================================[ debug settings ]===
 # which actions to log. Empty string turns off debug feature. Otherwise each
 # letter represents an action to debug:
 # D - Database actions (this enables Debug for the database class only and may cause
 #     duplicate error messages if used together with "S")
 # E - Errors
 # S - SQL statements
 # V - Variables set
 # W - Warnings
 # R - detailed Reports on failures (if available)
 # N - notifies from PHP itself (PHP error reporting)
 $debug["log"]  = "EW";

 #-----------------------------------------------------[ set up debugging ]---
 if ( !strpos(strtoupper($debug["log"]),"D")===false ) $db->Debug=1;
 error_reporting(0); // initially turn all off
 function set_phpdebug($level) {
   $pdbug = error_reporting();
   error_reporting($pdbug | $level);
 }
 if ( strpos(strtoupper($debug["log"]),"E")!==false ) set_phpdebug(E_ERROR);
 if ( strpos(strtoupper($debug["log"]),"W")!==false ) set_phpdebug(E_WARNING);
 if ( strpos(strtoupper($debug["log"]),"N")!==false ) set_phpdebug(E_NOTICE);

 #=====================================================[ setup path names ]===
 $pvp->projectpage = "http://projects.izzysoft.de/?topic=progs;subject=phpvideopro";
# $base_path = dirname(dirname(__FILE__))."/"; # !!! __FILE__ resolves symlinks
 $bp = dirname($_SERVER['SCRIPT_FILENAME']);
 if (is_file($bp."/medialist.php")) $base_path = "$bp/";
 else $base_path = dirname($bp) . "/";
 if (substr(php_uname(), 0, 7) == "Windows") {
   $pvp->config->os_slash = "\\";
   $base_path = str_replace("\\","/",$base_path);
 } else {
   $pvp->config->os_slash = "/";
 }
 $base_url = substr($base_path,strlen($_SERVER["DOCUMENT_ROOT"]));
 if (strpos($base_url,"/")!==0) $base_url = "/".$base_url;
 if ( (substr($backup_path,0,1)!="/") && (substr($backup_path,0,1)!="\\") )
   $backup_path = $base_path.$backup_path;
 $pvp->config->photopath = $base_path."moviepic/";
 $pvp->config->imdb_photopath = $base_path."moviepic/imdb/";
 $pvp->config->imdb_photourl  = $base_url."moviepic/imdb/";

 #=========================================[ retrieve browser information ]===
 include($base_path . "inc/class.browser.inc");
 $browser = new browser;
 $agent->name    = strtolower($browser->getbrowser());
 $agent->major   = $browser->getMajor();
 $agent->minor   = $browser->getMinor();
 $agent->version = $browser->getVer();

 #============================================[ set some technical values ]===
 $max["actors"]         =  5;
 $max["categories"]     =  3;
 $max["name_chars"]     = 30;
 $max["country_chars"]  = 30;
 $max["filmlen_chars"]  =  3;
 $max["srclen_chars"]   = 25;
 $min["media_size"]     = 10; // min length of recordable media in minutes
 $form["addon_country"] = "SIZE='30' MAXLENGTH='" . $max["country_chars"] . "'";
 $form["addon_name"]    = "SIZE='30' MAXLENGTH='" . $max["name_chars"] . "'";
 $form["addon_year"]    = "SIZE='4' MAXLENGTH='4'";
 $form["addon_month"]   = "SIZE='2' MAXLENGTH='2'";
 $form["addon_day"]     = $form["addon_month"];
 $form["addon_fsk"]     = "SIZE='2' MAXLENGTH='2'";
 $form["addon_filmlen"] = "SIZE='" . $max["filmlen_chars"] . "' MAXLENGTH='" . $max["filmlen_chars"] . "'";
 $form["addon_src"]     = "SIZE='" . $max["srclen_chars"] . "' MAXLENGTH='" . $max["srclen_chars"] . "' class='catinput'";
 $form["addon_cass_id"] = "SIZE='4' MAXLENGTH='4'";
 $form["addon_part"]    = "SIZE='2' MAXLENGTH='2'";
 $form["addon_title"]   = "SIZE='50' MAXLENGTH='60'";
 $form["addon_tech"]    = "class='techinput'";
 define("COUNTRY_LEN",30);
 define("CAT_BTN_WID",180);
 define("MOVIELEN_LEN",3); // max chars for movie length
 define("YN_WIDTH",40);   // width of Yes/No buttons
 define("SRC_LEN",25);    // max chars for source
 define("TECH_BTN_WID",120); // width for the virtual button of e.g. source
 define("FSK_LEN",2);     // max digits for FSK
 define("AUDIO_TS",6);    // max audio tracks for a movie
 define("SUBTITLES",9);   // max subtitle tracks for a movie

 #=============================================[ read preferences from DB ]===
 $pvp->config->db->type = strtolower($database["type"]);
 $pvp->db_include = dirname(__FILE__) . "/class.db_" . $database["type"] . ".inc";
 include ($pvp->db_include);
 include (dirname(__FILE__) . "/class.db.inc");
 $db->Host     = $pvp->config->db->host     = $database["host"];
 $db->Database = $pvp->config->db->database = $database["database"];
 $db->User     = $pvp->config->db->user     = $database["user"];
 $db->Password = $pvp->config->db->password = $database["password"];

 $charset = 'utf-8';
 if (!isset($pvpinstall)) {
  $pvp->config->enable_cookies = $db->get_config("enable_cookies");
  $pvp->config->expire_cookies = $db->get_config("expire_cookies");
  $pvp->config->session_purgetime = $db->get_config("session_purgetime");
  $pvp->config->http_cache_enable = $db->get_config("http_cache_enable");
  $pvp->config->use_http_auth = $db->get_config("use_http_auth");
  include (dirname(__FILE__) . "/class.cookie.inc");
  include (dirname(__FILE__) . "/class.preferences.inc");
  $pvp->preferences = new preferences;
  $db->limit();
  $site     = $db->get_config("site");
  $version  = $db->get_config("version");
  $rw_media = $db->get_config("rw_media");
  if ( isset($pre) ) $version .= $pre;
  $pvp->tpl_dir = $base_path . "templates/" . $pvp->preferences->get("template");
  $pvp->tpl_url = $base_url . "templates/" . $pvp->preferences->get("template");
  $pvp->pstpl_dir = $base_path . "pslabels";
  $pvp->backup_dir = $backup_path;
  $pvp->config->remove_empty_media = $db->get_config("remove_empty_media");
  $defaults["scolor"] = $pvp->preferences->get("default_movie_colorid");
 }

?>