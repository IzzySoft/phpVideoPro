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

$tpl_url = str_replace($base_path,$base_url,$pvp->tpl_dir)."/default.css";

if (!$silent) {
?>
<HTML><HEAD>
 <meta http-equiv="Content-Type" content="text/html; charset=<?=$charset?>">
 <meta http-equiv="cache-control" content="no-cache">
 <meta http-equiv="content-language" content="<?=$pvp->preferences->get("lang")?>">
 <Title><?=$pagename?></Title>
<? if ( $page_id != "login" ) { ?>
 <script language="JavaScript" src="<?=$base_url?>inc/common.js"></script>
<?
 include($nav_script);
 include($pvp->tpl_dir ."/default.css");
 if ($oldmenue) echo "</HEAD><BODY onLoad=\"init();\">";
 if (!$silent) echo "<!-- detected " . $agent->name . " version " . $agent->version . " ($HTTP_USER_AGENT) -->\n";
?>

<table width="100%" border="0" cellspacing="0" cellpadding="0">
 <tr>
  <td><? if ($oldmenue) { ?><img src="<?=$base_url?>images/menu_bar_left.gif" width="9" height="12"><? } else { ?>&nbsp;<? } ?></td>
 </tr>
</table>
<?
} else {
 include($pvp->tpl_dir ."/default.css");
 echo "</HEAD><BODY>\n";
} // !login
} // not silent ?>