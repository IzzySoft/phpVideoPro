<?
  /* $Id$ */

################################################################################
# internals - don't edit below this unless you exactly know what you are doing!

// retrieve browser information
include($base_path . "inc/browser.inc");
$browser = new browser;
$agent->name    = strtolower($browser->getbrowser());
$agent->major   = $browser->getMajor();
$agent->minor   = $browser->getMinor();
$agent->version = $browser->getVer();
echo "<!-- detected " . $agent->name . " version " . $agent->version . " ($HTTP_USER_AGENT) -->\n";
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

// set some technical values
$rw_media   = "1";
$max["actors"]         =  5;
$max["categories"]     =  3;
$max["name_chars"]     = 30;
$max["country_chars"]  = 30;
$max["filmlen_chars"]  =  3;
$max["srclen_chars"]   = 15;
$min["media_size"]     = 10; // min length of recordable media in minutes
$form["addon_country"] = "SIZE=\"30\" MAXLENGTH=\"" . $max["country_chars"] . "\"";
$form["addon_name"]    = "SIZE=\"30\" MAXLENGTH=\"" . $max["name_chars"] . "\"";
$form["addon_year"]    = "SIZE=\"4\" MAXLENGTH=\"4\"";
$form["addon_month"]   = "SIZE=\"2\" MAXLENGTH=\"2\"";
$form["addon_day"]     = "SIZE=\"2\" MAXLENGTH=\"2\"";
$form["addon_fsk"]     = "SIZE=\"2\" MAXLENGTH=\"2\"";
$form["addon_filmlen"] = "SIZE=\"" . $max["filmlen_chars"] . "\" MAXLENGTH=\"" . $max["filmlen_chars"] . "\"";
$form["addon_src"]     = "SIZE=\"" . $max["srclen_chars"] . "\" MAXLENGTH=\"" . $max["srclen_chars"] . "\"";
$form["addon_cass_id"] = "SIZE=\"4\" MAXLENGTH=\"4\"";
$form["addon_part"]    = "SIZE=\"2\" MAXLENGTH=\"2\"";
$form["addon_title"]   = "SIZE=\"50\" MAXLENGTH=\"60\"";

#----------------------------------------[ read preferences from DB ]---
$pvp->db_include = dirname(__FILE__) . "/db_" . $database["type"] . ".inc";
include ($pvp->db_include);
$db = new DB_Sql;
$db->Host     = $database["host"];
$db->Database = $database["database"];
$db->User     = $database["user"];
$db->Password = $database["password"];
if ( !strpos(strtoupper($debug["log"]),"D")===false ) $db->Debug=1;

if (!$pvpinstall) {
 $db->query("SELECT value FROM preferences WHERE name='colors'");
 $db->next_record();
 $colors   = unserialize ( rawurldecode( $db->f('value') ) );
 $colors["ok"]  = "<FONT COLOR=\"" . $colors["ok"] . "\">";
 $colors["err"] = "<FONT COLOR=\"" . $colors["err"] . "\">";
 $db->query("SELECT value FROM pvp_config WHERE name='version'");
 $db->next_record();
 $version  = $db->f('value');
 $pre      = "p7";
 if ($pre) $version .= $pre;
 if ($runupdate) {
  $charset = 'iso-8859-1';
 } else {
  $db->query("SELECT value FROM preferences WHERE name='lang'");
  $db->next_record();
  $plang  = $db->f('value');
  $db->query("SELECT charset FROM languages WHERE lang_id='$plang'");
  $db->next_record();
  $charset  = $db->f('charset');
  if (!strlen($charset)) $charset = 'iso-8859-1';
  unset ($plang);
 }
 $db->query("SELECT value FROM preferences WHERE name='template'");
 $db->next_record();
 $pvp->tpl_dir = $base_path . "templates/" . $db->f('value');
}
#--------------------------------------------------[ debug settings ]---
// which actions to log. Empty string turns off debug feature. Otherwise each letter
// represents an action to debug:
// D - Database actions (this enables Debug for the database class only and may cause
//     duplicate error messages if used together with "S")
// E - Errors
// S - SQL statements
// V - Variables set
// W - Warnings
// $debug["log"]  = "EW";
$debug["log"]  = "EW";

?>