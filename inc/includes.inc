<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
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
  // AutoLogin via HTTP_AUTH (if enabled)
  if ($pvp->config->use_http_auth && isset($_SERVER["PHP_AUTH_USER"])) {
    if (!$pvp->auth->user_id || $pvp->auth->user->login=="guest") {
      $sess_id = $pvp->session->create($_SERVER["PHP_AUTH_USER"],$_SERVER["PHP_AUTH_PW"]);
      if ($pvp->cookie->active) $pvp->cookie->set("sess_id",$sess_id);
    }
  }
?>