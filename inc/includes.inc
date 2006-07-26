<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2006 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Include the commonly needed classes and configs                           #
 #############################################################################

 /* $Id$ */

  $inc_path = dirname(__FILE__);
  include($inc_path . "/vul_check.inc");
  include($inc_path . "/config.inc");
  include($inc_path . "/config_internal.inc");
  include($inc_path . "/common_funcs.inc");
  include($inc_path . "/class.link.inc");
  include($inc_path . "/class.template.inc");
  include($inc_path . "/class.validate.inc");
  include($inc_path . "/class.session.inc");
  include($inc_path . "/class.auth.inc");
  if (!isset($pvpinstall)) $translations = $db->get_translations( $pvp->preferences->get("lang") );
  $pagename = "phpVideoPro v$version @ $site";
  if (!isset($page_id)) $page_id = "";
  switch ( strtolower($page_id) ) {
    case ""              : break;
    case "actors"        : $pagename .= " [ " . lang("actors_list") . " ]"; break;
    case "delete"        : $pagename .= " [ " . lang("deleting_entry",$nr) . " ]"; break;
    case "directors"     : $pagename .= " [ " . lang("directors_list") . " ]"; break;
    case "edit"          : $mt = $db->get_mtypes("id=$mtype_id");
                           $pagename .= " [ " . lang("edit_entry",$mt[0]['sname']." ".$nr) . " ]";
			   unset($mt); break;
    case "filter"        : $pagename .= " [ " . lang("filter_setup") . " ]"; break;
    case "view"          : $pagename .= " [ " . lang("view_entry",$nr) . " ]"; break;
    case "music"         : $pagename .= " [ " . lang("music_list") . " ]"; break;
    case "taperest"      : $pagename .= " [ " . lang("free_space_title") . " ]"; break;
    case "stats"         : $pagename .= " [ " . lang("db_stats") . " ]"; break;
    case "view_entry"    : $mt = $db->get_mtypes("id=$mtype_id");
                           $pagename .= " [ " . lang("view_entry",$mt[0]['sname']." $cass_id-$part") . " ]";
			   unset($mt); break;
    default              : $pagename .= " [ " . lang("$page_id") . " ]"; break;
  }
?>