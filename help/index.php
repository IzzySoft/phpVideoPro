<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
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
include ("../inc/class.template.inc");
#=============================================[ Get the needed parameters ]===
/** Find the input file for the requested help topic
 * @package Help
 * @function helppage
 * @param string topic help topic to build the page for
 * @return array (desc,url,file) title, URL and full /path/file for the help
    page, where URL is the complete HTML &lt;A HREF...&lt/A&gt; string
 */
function helppage ($topic) {
  GLOBAL $pvp,$PHP_SELF;
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

#====================================================[ Build page content ]===
/** Help page creator
 * @package Help
 * @class pagemaker
 */
class pagemaker {

 VAR $t,       // template class
     $block;   // active block

 /** Constructor: Setting up the templates
  * @constructor pagemaker
  */
 function pagemaker() {
  global $pvp;
  $this->t = new Template($pvp->tpl_dir);
  $this->t->set_file(array("main"=>"help.tpl"));
  $this->t->set_block("main","titleblock","titlelist");
  $this->t->set_block("titleblock","textblock","textlist");
  $this->block->name = "";
 }

 /** Replacing placeholders for variables and translations within the
  *  input files current block, then add it to the content to parse into
  *  the templates
  * @package Help
  * @class pagemaker
  * @method add_block
  * @param string content content block to parse
  */
 function add_block($content) {
  if (!$this->block->name) return;
  if ( preg_match_all("/\{\S+\}/",$content,$matches) ) { // replace variables
   $var = substr($matches[0],1,strlen($matches[0])-2);
   for ($i=0;$i<count($matches[0]);$i++) {
     $var = substr($matches[0][$i],1,strlen($matches[0][$i])-2);
     $pos = strpos($var,"->");
     if ($pos) {
      $obj = substr($var,0,$pos); $prop = substr($var,$pos+2);
      GLOBAL $$obj;
      $rvar = $$obj->$prop;
     } else { $rvar = $GLOBALS[$var]; }
     $content = preg_replace("/\{$var\}/",$rvar,$content);
   }
  }
 if ( preg_match_all("/\*\S+\#/",$content,$matches) ) { // replace translations
   $var = substr($matches[0],1,strlen($matches[0])-2);
   for ($i=0;$i<count($matches[0]);$i++) {
     $var  = substr($matches[0][$i],1,strlen($matches[0][$i])-2);
     $rvar = lang($var);
     $content = preg_replace("/\*$var\#/",$rvar,$content);
   }
  }
  $this->block->content .= $content;
 }

 /** Parse the current block into the template
  * @package Help
  * @class pagemaker
  * @method parse_block
  */
 function parse_block($keep=1) {
  if (!$this->block->name) return;
  $list   = $this->block->name . "list";
  $pblock = $this->block->name . "block";
  $this->t->set_var($this->block->name,trim($this->block->content));
  $this->t->parse($list,$pblock,$this->block->append);
  if (!$this->block->append) $this->block->append = 1;
  $this->block->content = "";
 }

 /** Close the current block. This means, next block won't be appended, but
  *  a new block will be started
  * @package Help
  * @class pagemaker
  * @method close_block
  */
 function close_block () {
  if (!$this->block->name) return;
  $this->parse_block();
  $this->block->append  = 0;
 }

 /** Set template variables. Wrapper around pagemaker::t::set_var
  * @package Help
  * @class pagemaker
  * @method set_nav
  * @param string name name of template variable
  * @param string content value of template variable
  */
 function set_nav($name,$content) {
   $this->t->set_var($name,$content);
 }

 /** Main method - and the only one that should be called from the public.
  *  This will build the page from the given file, using the given title
  *  for the headers, and send it to the browser
  * @package Help
  * @class pagemaker
  * @method make_page
  * @param string title page title
  * @param string file input file
  */
 function make_page($title,$file) {
  $input = file($file);
  if (substr(trim($input[0]),0,1)=="!") { // "symbolic link"
    $file = dirname($file) . "/" . trim(substr($input[0],1));
    $input = file($file);
  }
  $line  = 0;
  while ( $line<count($input) ) {
   switch ( trim(strtolower($input[$line])) ) {
    case "[title]"   : if ($this->block->name) {
                        if ($this->block->name=="title") {
                         $this->close_block();
                        } else {
			 $this->close_block();
                         $this->block->name = "title";
                         $this->add_block($this->block->title);
			 $this->block->append  = 1;
			 $this->close_block();
			 $this->block->content = "";
			}
		       }
                       $this->block->name = "title";
		       ++$line;
                       continue;
		       break;
    case "[text]"    : if ($this->block->name) {
                        if ($this->block->name=="text") {
                         $this->parse_block();
                        } else {
                         $this->block->title   = $this->block->content;
			 $this->block->content = "";
                        }
		       }
                       $this->block->name = "text";
		       ++$line;
                       continue;
		       break;
    case "[eof]"     : $eof = TRUE; break;
    default          : break;
   }
   if ($eof) {
    $this->close_block();
    $this->block->name = "title";
    $this->add_block($this->block->title);
    $this->block->append  = 1;
    $this->close_block();
    break;
   }
   if ( substr(trim($input[$line]),0,1) == "#" ) { // comment line
     $line++;
     continue;
   }
   switch ($this->block->name) {
    case "title"   : $this->block->content .= $input[$line]; break;
    default        : //$this->block->title  = "";
                     $this->add_block($input[$line]);
		     break;
   }
   $line++;
  }
  $this->t->set_var("listtitle",$title);
  $this->t->pparse("out","main");
 } // end function make_page

 /** Template Class to built up pages
  * @package Help
  * @class pagemaker
  * @attribute object t
  */
 /** Active block we work on
  * @package Help
  * @class pagemaker
  * @attribute object block
  */

} // end class pagemaker


###################==================================[ MAIN - HERE WE GO! ]===
$title = "phpVideoPro v$version @ $site - " . lang("help") . ": ";
if ($topic) { $title .= lang($topic); } else { $title .= lang("index"); }

echo "<HTML><HEAD>\n";
echo " <TITLE>$title</TITLE>\n";
echo " <meta http-equiv=\"Content-Type\" content=\"text/html; charset=$charset\">\n";
include($base_path . "templates/default/default.css");
echo "</HEAD><BODY>\n";

$pm = new pagemaker;
$pm->set_nav("back","<A HREF=\"JavaScript:history.back()\">" . lang("back") . "</A>");
if ( !$force_en && $pvp->preferences->get("lang")!="en" )
  $pm->set_nav("force","<A HREF='$PHP_SELF?topic=$topic&force_en=1'><IMG SRC='$base_url/templates/default/images/english.jpg'></A>");
$pm->set_nav("index","<A HREF=\"$PHP_SELF\">" . lang("index") . "</A>");
$pm->set_nav("close","<A HREF=\"JavaScript:window.close()\">" . lang("close") . "</A>");
if ($topic) { // display specific help page
  $help = helppage($topic);
  if ( !$help->file ) {
    $lang = $pvp->preferences->get("lang");
    $help->file = dirname(__FILE__) . "/" . $lang . "/no_topic.inc";
    if ( !file_exists($help->file) ) {
      $help->file = dirname(__FILE__) . "/en/no_topic.inc";
    }
  }
  $pm->make_page(lang($topic),$help->file);
} else { // display help index
  include("help_topics.php");
  $pm->t->set_var("listtitle",lang(index));
  $pm->t->set_var("title","");
  $pm->t->set_var("text","$content");
  $pm->t->parse("textlist","textblock");
  $pm->t->parse("titlelist","titleblock");
  $pm->t->pparse("out","main");
}

include("../inc/footer.inc");
?>