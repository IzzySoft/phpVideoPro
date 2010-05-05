<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2010 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Common header for almost all pages (except some setup specials)           #
 #############################################################################

 /* $Id$ */

header('Content-type: text/html; charset=$charset');
if (!$pvp->config->http_cache_enable) { // turn off all caches
  header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");    # Date from the past
  header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT"); # up-to-date
  header("Cache-Control: no-store, no-cache, must-revalidate");  # HTTP/1.1
  header("Cache-Control: post-check=0, pre-check=0", false);
  header("Pragma: no-cache");                          # HTTP/1.0
}

$tpl_url = str_replace($base_path,$base_url,$pvp->tpl_dir)."/default.css";
if (isset($pvp->preferences))
  $contentlang = $pvp->preferences->get("lang");
else
  $contentlang = "en";
if (!isset($pagename)) $pagename = "phpVideoPro";
if ( !( (isset($silent)) && $silent) ) {
echo '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
   "http://www.w3.org/TR/html4/loose.dtd">';
  if (!isset($nomenue) && $pvp->preferences->get("lang")=='iw') echo "<HTML DIR='RTL'>";
  else echo "<HTML>";
?>
<HEAD>
 <meta http-equiv="Content-Type" content="text/html; charset=<?php echo $charset?>">
 <meta http-equiv="cache-control" content="no-cache">
 <meta http-equiv="content-language" content="<?php echo $contentlang?>">
 <Title><?php echo $pagename?></Title>
<? 
 if ( file_exists($pvp->tpl_dir . "/top.js") )
   echo " <script type='text/javascript' language='JavaScript' src='". str_replace($base_path,$base_url,$pvp->tpl_dir) . "/top.js'></script>\n";
 if ($page_id=="add_entry"||$page_id=="edit")
   echo "<script src='http://js.nicedit.com/nicEdit-latest.js' type='text/javascript'></script>\n"
      . "<script src='${base_url}templates/editEntry.js' type='text/javascript'></script>\n";
?>
 <script type='text/javascript' language='JavaScript'>//<!--
  function open_help(topic) {
    if (topic=='history') { url = '<?php echo $pvp->histpage?>'; } else {
      if (topic!='') { help_topic = '?topic=' + topic; } else { help_topic = ''; }
      url = '<?php echo $base_url?>help/index.php' + help_topic;
    }
    var pos = (screen.width/2)-400;
    campus=eval("window.open(url,'<?php echo lang("help")?>','toolbar=no,location=no,titlebar=no,directories=no,status=yes,resizable=no,scrollbars=yes,copyhistory=no,width=800,height=600,top=0,left=" + pos + "')");
  }
  //--></script>
<? if ( !isset($nomenue) ) { ?>
 <script type='text/javascript' language='JavaScript'>//<!--
  function get_movienum(mtype,last_nr,url) {
    nr = last_nr + 1;
    new_nr = prompt(mtype + "\n" + "<?php echo lang("last_medianr")?> " + last_nr,nr);
    if (new_nr != "" && new_nr != null)
      window.location.href = url + "&cass_id=" + new_nr;
  }
  //--></script>
 <link href="<?php echo $pvp->tpl_url?>/default.css" rel="stylesheet" type="text/css">
<?
   include($base_path . "inc/newmenue.inc");
   if ( !(isset($silent) && $silent) ) echo "<!-- detected " . $agent->name . " version " . $agent->version . " (".$_SERVER["HTTP_USER_AGENT"].") -->\n";
 } else { // page_id != "login" ?>
 <link href="<?php echo $pvp->tpl_url?>/default.css" rel="stylesheet" type="text/css">
<?
   echo "</HEAD><BODY>\n";
 } // !login
} // !silent ?>