<?
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # ! internals - don't edit anything in this files - unless you exactly know #
 # ! what you are doing!                                                     #
 #############################################################################

  /* $Id$ */

 #=========================================[ retrieve browser information ]===
 include($base_path . "inc/class.browser.inc");
 $browser = new browser;
 $agent->name    = strtolower($browser->getbrowser());
 $agent->major   = $browser->getMajor();
 $agent->minor   = $browser->getMinor();
 $agent->version = $browser->getVer();
 if (!$silent) echo "<!-- detected " . $agent->name . " version " . $agent->version . " ($HTTP_USER_AGENT) -->\n";

 #======================================[ setup menu depending on browser ]===
 if ($agent->name == "netscape") {
  if ($agent->version < 5) {
   $oldmenue = TRUE;
  }
 } else {
  $oldmenue = FALSE;
 }
 if ($oldmenue) {
  $nav_script = $base_path . "inc/oldmenue.inc";
 } else {
  $nav_script = $base_path . "inc/newmenue.inc";
 }

 #============================================[ set some technical values ]===
 $max["actors"]         =  5;
 $max["categories"]     =  3;
 $max["name_chars"]     = 30;
 $max["country_chars"]  = 30;
 $max["filmlen_chars"]  =  3;
 $max["srclen_chars"]   = 15;
 $min["media_size"]     = 10; // min length of recordable media in minutes
 $form["addon_country"] = "SIZE=\"30\" MAXLENGTH=\"" . $max["country_chars"] . "\"";
 $form["addon_name"]    = "SIZE=\"30\" MAXLENGTH=\"" . $max["name_chars"] . "\" class=\"nameinput\"";
 $form["addon_year"]    = "SIZE=\"4\" MAXLENGTH=\"4\"";
 $form["addon_month"]   = "SIZE=\"2\" MAXLENGTH=\"2\"";
 $form["addon_day"]     = "SIZE=\"2\" MAXLENGTH=\"2\"";
 $form["addon_fsk"]     = "SIZE=\"2\" MAXLENGTH=\"2\"";
 $form["addon_filmlen"] = "SIZE=\"" . $max["filmlen_chars"] . "\" MAXLENGTH=\"" . $max["filmlen_chars"] . "\"";
 $form["addon_src"]     = "SIZE=\"" . $max["srclen_chars"] . "\" MAXLENGTH=\"" . $max["srclen_chars"] . "\" class=\"techinput\"";
 $form["addon_cass_id"] = "SIZE=\"4\" MAXLENGTH=\"4\"";
 $form["addon_part"]    = "SIZE=\"2\" MAXLENGTH=\"2\"";
 $form["addon_title"]   = "SIZE=\"50\" MAXLENGTH=\"60\"";
 $form["addon_tech"]    = "class=\"techinput\"";

 #=============================================[ read preferences from DB ]===
 $pvp->db_include = dirname(__FILE__) . "/class.db_" . $database["type"] . ".inc";
 include ($pvp->db_include);
 include (dirname(__FILE__) . "/class.db.inc");
 $pvp->config->db->type = strtolower($database["type"]);
 $db->Host     = $pvp->config->db->host     = $database["host"];
 $db->Database = $pvp->config->db->database = $database["database"];
 $db->User     = $pvp->config->db->user     = $database["user"];
 $db->Password = $pvp->config->db->password = $database["password"];
 if ( !strpos(strtoupper($debug["log"]),"D")===false ) $db->Debug=1;

 if (!$pvpinstall) {
  include (dirname(__FILE__) . "/class.preferences.inc");
  $pvp->preferences = new preferences;
  $db->query("SELECT value FROM pvp_config WHERE name='version'");
  $db->next_record();
  $version  = $db->f('value');
  if ($pre) $version .= $pre;
  if ($runupdate) {
   $charset = 'iso-8859-15';
  } else {
   $plang  = $pvp->preferences->lang;
   $db->query("SELECT charset FROM languages WHERE lang_id='$plang'");
   $db->next_record();
   $charset  = $db->f('charset');
   if (!strlen($charset)) $charset = 'iso-8859-15';
   unset ($plang);
  }
  $pvp->tpl_dir = $base_path . "templates/" . $pvp->preferences->template;
 }

 #=======================================================[ debug settings ]===
 # which actions to log. Empty string turns off debug feature. Otherwise each
 # letter represents an action to debug:
 # D - Database actions (this enables Debug for the database class only and may cause
 #     duplicate error messages if used together with "S")
 # E - Errors
 # S - SQL statements
 # V - Variables set
 # W - Warnings
 $debug["log"]  = "EW";

?>