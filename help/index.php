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
  echo "$text\n";
}
function li($topic,$level=1) {
  for ($i=0;$i<$level;$i++) {
    echo "&nbsp;&nbsp;";
  }
  print_url($topic);
  echo "<br>\n";
}
function headline($topic,$level=0) {
  for ($i=0;$i<$level;$i++) {
    echo "&nbsp;&nbsp;";
  }
  echo "<b>";
  print_url($topic);
  echo "</b><br>\n";
}

$title = "phpVideoPro v$version - " . lang("help") . ": ";
if ($topic) { $title .= lang($topic); } else { $title .= lang("index"); }

echo "<HTML><HEAD>\n";
echo " <TITLE>$title</TITLE>\n";
include($base_path . "templates/default/default.css");
echo "</HEAD><BODY>\n";

if ($topic) { // display specific help page
  echo "<TABLE WIDTH=100%><TR><TD COLSPAN=2>&nbsp;</TD></TR>"
     . "<TD><A HREF=\"JavaScript:history.back()\">" . lang("back")
     . "</A></TD><TD ALIGN=RIGHT><A HREF=\"$PHP_SELF\">" . lang("index") . "</A></TD></TR></TABLE>\n";
  $help = helppage($topic);
  if ( $help->file ) {
    include($help->file);
  } else {
    include(dirname(__FILE__)) . "/no_topic.inc";
  }
} else { // display help index
  echo "<H3>" . lang("index") . "</H3>\n";
  include("help_topics.php");
}
echo "<P ALIGN=CENTER><A HREF=\"JavaScript:window.close()\">" . lang("close") . "</A></P>\n";

include("../inc/footer.inc");
?>