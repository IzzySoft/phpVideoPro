<?

$base_url   = "/local/phpvideo/";
$nav_script = $base_url . "inc/navcond.js";
$version    = "0.0.1";

// colors - mainly for debug messages
$colors["ok"]  = "<Font Color=\"#0000ff\">";
$colors["err"] = "<Font Color=\"#ff0000\">";

// *** configuration of debugging ***
// which actions to log. Empty string turns off debug feature. Otherwise each letter
// represents an action to debug:
// D - Database actions
// E - Errors
// S - SQL statements
// V - Variables set
// $debug["log"]  = "SV";
$debug["log"]  = "ES";

// internals - don't edit below this unless you exactly know what you are doing!
$max["actors"]         =  5;
$max["name_chars"]     = 30;
$max["country_chars"]  = 30;
$max["filmlen_chars"]  =  3;
$max["srclen_chars"]   = 15;
$form["addon_country"] = "SIZE=\"30\" MAXLENGTH=\"" . $max["country_chars"] . "\"";
$form["addon_name"]    = "SIZE=\"30\" MAXLENGTH=\"" . $max["name_chars"] . "\"";
$form["addon_year"]    = "SIZE=\"4\" MAXLENGTH=\"4\"";
$form["addon_fsk"]     = "SIZE=\"2\" MAXLENGTH=\"2\"";
$form["addon_filmlen"] = "SIZE=\"" . $max["filmlen_chars"] . "\" MAXLENGTH=\"" . $max["filmlen_chars"] . "\"";
$form["addon_src"]     = "SIZE=\"" . $max["srclen_chars"] . "\" MAXLENGTH=\"" . $max["srclen_chars"] . "\"";

?>