<?
include ("../inc/config.inc");
include ("../inc/config_internal.inc");
include ("../inc/common_funcs.inc");
include ("../inc/sql_helpers.inc");
// include("../inc/header.inc");
##############################################################################
# Get the topic description - if possible with link to helpfile (if exist)
function helppage ($topic) {
  $desc = lang($topic);
  $lang = get_lang();
  $name = $topic . ".inc";
  $file = dirname(__FILE__) . "/" . $lang . "/" . $name;
  $default_file = dirname(__FILE__) . "/en/" . $name;
  $help->desc = $desc;
  if ( file_exists($file) ) {
    $help->url  = "<A HREF=\"$PHP_SELF?topic=$topic\">$desc</A>";
    $help->file = $file;
  } elseif ( file_exists($default_file) ) {
    $help->url  = "<A HREF=\"$PHP_SELF?topic=$topic\">$desc</A>";
    $help->file = $default_file;
  } else {
    $help->url  = FALSE;
    $help->file = FALSE;
  }
  return $help;
}
##############################################################################
# Print topic url (if available) or just name (otherwise)
function print_url($topic) {
  $help = helppage($topic);
  if ($help->url) { $text = $help->url; } else { $text = $help->desc; }
  echo "$text<br>\n";
}

$title = "phpVideoPro v$version - " . lang("help") . ": ";
if ($topic) { $title .= lang($topic); } else { $title .= lang("help_index"); }

echo "<HTML><HEAD>\n";
echo " <TITLE>$title</TITLE>\n";
include($base_path . "templates/default/default.css");
echo "</HEAD><BODY>\n";

if ($topic) { // display specific help page
  $help = helppage($topic);
  if ( $help->file ) {
    include($help->file);
  } else {
    include(dirname(__FILE__)) . "/no_topic.inc";
  }
} else { // display help index
  echo "<H3>HelpIndex</H3>\n";
  print_url("about");
  print_url("view");
}

include("../inc/footer.inc");
?>