<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Common header for almost all pages (except some setup specials)           *
 \***************************************************************************/

 /* $Id$ */

  $inc_path = dirname(__FILE__);
  include($inc_path . "/config.inc");
  include($inc_path . "/config_internal.inc");
  include($inc_path . "/common_funcs.inc");
  include($inc_path . "/link.inc");
  include($inc_path . "/db.inc");
  include($inc_path . "/template.inc");
  include($inc_path . "/validate.inc");
  $pagename = "phpVideoPro v$version";
  switch ( strtolower($page_id) ) {
    case "about"         : $pagename .= " [ " . lang("about") . " ]"; break;
    case "actors"        : $pagename .= " [ " . lang("actors_list") . " ]"; break;
    case "configuration" : $pagename .= " [ " . lang("configuration") . " ]"; break;
    case "delete"        : $pagename .= " [ " . lang("deleting_entry",$nr) . " ]"; break;
    case "directors"     : $pagename .= " [ " . lang("directors_list") . " ]"; break;
    case "edit"          : $pagename .= " [ " . lang("edit_entry",$nr) . " ]"; break;
    case "filter"        : $pagename .= " [ " . lang("filter_setup") . " ]"; break;
    case "view"          : $pagename .= " [ " . lang("view_entry",$nr) . " ]"; break;
    case "history"       : $pagename .= " [ " . lang("history") . " ]"; break;
    case "medialist"     : $pagename .= " [ " . lang("medialist") . " ]"; break;
    case "music"         : $pagename .= " [ " . lang("music_list") . " ]"; break;
    case "add_entry"     : $pagename .= " [ " . lang("add_entry") . " ]"; break;
    case "taperest"      : $pagename .= " [ " . lang("free_space_title") . " ]"; break;
    default              : break;
  }
?>
<HTML><HEAD>
 <meta http-equiv="Content-Type" content="text/html; charset=<?=$charset?>">
 <Title><?echo $pagename ?></Title>
 <!--LINK REL=stylesheet type="text/css" HREF="<? echo $base_url ?>templates/default/default.css"-->
 <script language="JavaScript">

  function open_help(topic) {
   if (topic!='') { help_topic = '?topic=' + topic; } else { help_topic = ''; }
   url = '<? echo $base_url ?>help/index.php' + help_topic;
   var pos = (screen.width/2)-400;
   campus=eval("window.open(url,'<? echo lang("help") ?>','toolbar=no,location=no,titlebar=no,directories=no,status=yes,resizable=no,scrollbars=yes,copyhistory=no,width=800,height=600,top=0,left=" + pos + "')");
  }

 </script>
 <? include($nav_script);
    include($base_path . "templates/default/default.css") ?>
</HEAD>
<BODY leftmargin="0" topmargin="0" marginwidth="0" marginheight="0"<?
if ($oldmenue) echo " onLoad=\"init();\"" ?><!-- {body_tags}-->

<table width="100%" border="0" cellspacing="0" cellpadding="0">
 <tr>
  <td><? if ($oldmenue) { ?><img src="<? echo $base_url ?>images/menu_bar_left.gif" width="9" height="12"><? } else { ?>&nbsp;<? } ?></td>
 </tr>
</table>
