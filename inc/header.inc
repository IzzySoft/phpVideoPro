<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Common header for almost all pages (except some setup specials)           #
 #############################################################################

 /* $Id$ */

header('Content-type: text/html; charset=$charset');

$tpl_url = str_replace($base_path,$base_url,$pvp->tpl_dir)."/default.css";

if ( !( (isset($silent)) && $silent) ) {
?>
<HTML><HEAD>
 <meta http-equiv="Content-Type" content="text/html; charset=<?=$charset?>">
 <meta http-equiv="cache-control" content="no-cache">
 <meta http-equiv="content-language" content="<?=$pvp->preferences->get("lang")?>">
 <Title><?=$pagename?></Title>
<? 
 if ( file_exists($pvp->tpl_dir . "/top.js") )
   echo " <script type='text/javascript' language='JavaScript' src='". str_replace($base_path,$base_url,$pvp->tpl_dir) . "/top.js'></script>\n";
 if ( $page_id != "login" ) { ?>
 <script type='text/javascript' language='JavaScript'>//<!--
  function open_help(topic) {
    if (topic!='') { help_topic = '?topic=' + topic; } else { help_topic = ''; }
    url = '<?=$base_url?>help/index.php' + help_topic;
    var pos = (screen.width/2)-400;
    campus=eval("window.open(url,'<?=lang("help")?>','toolbar=no,location=no,titlebar=no,directories=no,status=yes,resizable=no,scrollbars=yes,copyhistory=no,width=800,height=600,top=0,left=" + pos + "')");
  }
  function get_movienum(mtype,last_nr,url) {
    nr = last_nr + 1;
    new_nr = prompt(mtype + "\n" + "<?=lang("last_medianr")?> " + last_nr,nr);
    if (new_nr != "" && new_nr != null)
      window.location.href = url + "&cass_id=" + new_nr;
  }
  //-->
 </script>
 <link href="<?=$pvp->tpl_url?>/default.css" rel="stylesheet" type="text/css">
<?
 include($nav_script);
 if ($oldmenue) echo "</HEAD><BODY onLoad=\"init();\">";
 if ( !(isset($silent) && $silent) ) echo "<!-- detected " . $agent->name . " version " . $agent->version . " (".$_SERVER["HTTP_USER_AGENT"].") -->\n";
?>

<table width="100%" border="0" cellspacing="0" cellpadding="0">
 <tr>
  <td><? if ($oldmenue) { ?><img src="<?=$base_url?>images/menu_bar_left.gif" width="9" height="12"><? } else { ?>&nbsp;<? } ?></td>
 </tr>
</table>
<?
 } else { // page_id != "login"
   include($pvp->tpl_dir ."/default.css");
   echo "</HEAD><BODY>\n";
 } // !login
} // !silent ?>