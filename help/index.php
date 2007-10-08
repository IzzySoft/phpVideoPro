<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Help System: Display index or topic (depending on parameters)             #
 #############################################################################

 /* $Id$ */

#=========================================================[ initial setup ]===
include ("../inc/config.inc");
include ("../inc/config_internal.inc");
include ("../inc/common_funcs.inc");
require_once ("../inc/class.faq.inc");
$translations = $db->get_translations( $pvp->preferences->get("lang") );
if (isset($_GET["topic"])) $topic    = $_GET["topic"]; else $topic = "";
if (isset($_GET["ref"]))   $ref      = $_GET["ref"]; else $ref="";
if (isset($_GET["force_en"])) $force_en = $_GET["force_en"]; else $force_en = FALSE;
if ( !ini_get("register_globals") ) $PHP_SELF = $_SERVER["PHP_SELF"];

#=============================================[ Get the needed parameters ]===
/** Find the input file for the requested help topic
 * @package Help
 * @function helppage
 * @param string topic help topic to build the page for
 * @return array (desc,url,file) title, URL and full /path/file for the help
    page, where URL is the complete HTML &lt;A HREF...&lt/A&gt; string
 */
function helppage ($topic) {
  GLOBAL $pvp;
  $desc = lang($topic);
  if ( $GLOBALS["force_en"] ) {
    $lang = "en";
  } else {
    $lang = $pvp->preferences->get("lang");
  }
  $name = $topic . ".inc";
  $file = dirname(__FILE__) . "/" . $lang . "/" . $name;
  $default_file = dirname(__FILE__) . "/en/" . $name;
  $help->desc = $desc;
  if ( file_exists($file) ) {
    $help->url  = "<A HREF='".$_SERVER["PHP_SELF"]."?topic=$topic'>$desc</A>";
    $help->file = $file;
  } elseif ( file_exists($default_file) ) {
    $help->url  = "<A HREF='".$_SERVER["PHP_SELF"]."?topic=$topic'>$desc</A>";
    $help->file = $default_file;
  } else {
    $help->url  = FALSE;
    $help->file = FALSE;
  }
  return $help;
}
#===========================[ Print topic url (if available) or just name ]===
/** Adding a topic line to the index page. This uses the array created by
 *  helppage() and adds either the complete URL or, if this is empty, the
 *  topic to the global content variable
 * @package Help
 * @function print_url
 * @use content
 * @param string topic topic to be added
 */
function print_url($topic) {
  GLOBAL $content;
  $help = helppage($topic);
  if ($help->url) { $text = $help->url; } else { $text = $help->desc; }
  $content .= "$text\n";
}
/** Creating an sublevel item for the help index. Appends to the global content var.
 * @package Help
 * @function li
 * @use content
 * @param string topic topic to be added to the list
 * @param optional integer level sublevel of this item (i.e. how much to indent).
 *  This defaults to "1"
 */
function li($topic,$level=1) {
  GLOBAL $content;
  for ($i=0;$i<$level;$i++) {
    $content .= "&nbsp;&nbsp;";
  }
  print_url($topic);
  $content .= "<br>\n";
}
/** Creating a headline (toplevel item). Appends to the global content var.
 * @package Help
 * @function headline
 * @use content
 * @param string topic content of the headline to add
 * @param optional integer level sublevel (if any; see function li). Defaults to "0"
 */
function headline($topic,$level=0) {
  GLOBAL $content;
  for ($i=0;$i<$level;$i++) {
    $content .= "&nbsp;&nbsp;";
  }
  $content .= "<b>";
  print_url($topic);
  $content .= "</b><br>\n";
}
/** This keeps the content of the index page
 * @package Help
 * @variable string content
 */


#====================================================[ MAIN - HERE WE GO! ]===
$title = "phpVideoPro v$version @ $site - " . lang("help") . ": ";
if ($topic) { $title .= lang($topic); } else { $title .= lang("index"); }

header("Content-type: text/html; charset=$charset");
echo "<HTML><HEAD>\n";
echo " <TITLE>$title</TITLE>\n";
echo " <meta http-equiv='Content-Type' content='text/html; charset=$charset'>\n";
echo " <link href='".$pvp->tpl_url."/default.css' rel='stylesheet' type='text/css'>";
if ( file_exists($pvp->tpl_dir . "/top.js") )
  echo " <script type='text/javascript' language='JavaScript' src='". str_replace($base_path,$base_url,$pvp->tpl_dir) . "/top.js'></script>\n";
echo "</HEAD><BODY>\n";

$pm = new faq($pvp->tpl_dir,"help.tpl",0);
$pm->set_nav("back","<A HREF=\"JavaScript:history.back()\">" . lang("back") . "</A>");
if ( !$force_en && $pvp->preferences->get("lang")!="en" )
  $pm->set_nav("force","<A HREF='".$_SERVER["PHP_SELF"]."?topic=$topic&force_en=1'><IMG SRC='$base_url/templates/default/images/english.jpg' BORDER='0' ALT='English'></A>");
$pm->set_nav("index","<A HREF='".$_SERVER["PHP_SELF"]."\'>" . lang("index") . "</A>");
$pm->set_nav("close","<A HREF='JavaScript:window.close()'>" . lang("close") . "</A>");
$pm->set_nav("btn_index",lang("index"));
$pm->set_nav("btn_back",lang("back"));
$pm->set_nav("btn_close",lang("close"));
if ($topic) { // display specific help page
  if ($pos = strpos($topic,"#")) $topic = substr($topic,0,$pos);
  $help = helppage($topic);
  if ( !$help->file ) {
    $lang = $pvp->preferences->get("lang");
    $help->file = dirname(__FILE__) . "/" . $lang . "/no_topic.inc";
    if ( !file_exists($help->file) ) {
      $help->file = dirname(__FILE__) . "/en/no_topic.inc";
    }
  }
  $pm->parseInput($help->file,lang($topic));
  $pm->parseOutput();
} else { // display help index
  include("help_topics.php");
  $pm->t->set_var("listtitle",lang("index"));
  $pm->t->set_var("title","");
  $pm->t->set_var("text","$content");
  $pm->t->parse("textlist","textblock");
  $pm->t->parse("titlelist","titleblock");
  $pm->t->pparse("out","main");
}

include("../inc/footer.inc");
?>