<?

$base_url   = "/local/phpvideo/";
// the root directory of phpVideoPro

// colors
$colors["page_background"] = "#ffffff";
$colors["th_background"]   = "#eeeeee";
// for debug messages
$colors["ok"]  = "<Font Color=\"#0000ff\">";
$colors["err"] = "<Font Color=\"#ff0000\">";

// *** configuration of debugging ***
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

// database settings
$database["host"]      = "linux";
//$database["host"]      = "localhost";
$database["database"]  = "video_demo";
//$database["database"]  = "videopro";
$database["user"]      = "guest";
$database["password"]  = "";

// some default settings
$defaults["scolor"] = "Farbe"; // most movies today have more than two colors ;)

################################################################################
# internals - don't edit below this unless you exactly know what you are doing!
$version    = "0.1.0";
$nav_script = $base_url . "inc/navcond.js";
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
$form["addon_fsk"]     = "SIZE=\"2\" MAXLENGTH=\"2\"";
$form["addon_filmlen"] = "SIZE=\"" . $max["filmlen_chars"] . "\" MAXLENGTH=\"" . $max["filmlen_chars"] . "\"";
$form["addon_src"]     = "SIZE=\"" . $max["srclen_chars"] . "\" MAXLENGTH=\"" . $max["srclen_chars"] . "\"";
$form["addon_cass_id"] = "SIZE=\"4\" MAXLENGTH=\"4\"";
$form["addon_part"]    = "SIZE=\"2\" MAXLENGTH=\"2\"";

?>