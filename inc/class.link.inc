<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2010 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Link related stuff: highlighting, linking targets etc.                    #
 #############################################################################

 /* $Id$ */

 /** Link to Internet Movie DataBase (IMDB)
  * @package Api
  * @class link
  * @author Izzy (izzysoft AT qumran DOT org)
  * @copyright (c) 2001-2009 by Itzchak Rehberg and IzzySoft
  */
 /** Base URL of the IMDB
  * @class link
  * @attribute string imdb
  */
 class link {
  var $imdb;

  /** Constructor: initialize base URL
   * @constructor link
   */
  function link() {
    GLOBAL $pvp;
    if (isset($pvp->preferences))
      $this->imdb = $pvp->preferences->get("imdb_url");
    else
      $this->imdb = "us.imdb.com";
  }

  ############################################################################
  /** Calculate URL path from absolute file path (inside PVP tree)
   * @method url_path
   * @param string path absolute path
   * @return string url_path absolute URL path including trailing slash
   */
  function url_path($path) {
    GLOBAL $base_path, $base_url;
    $path = str_replace($pvp->config->os_slash,"/",$base_path);
    $pos = strpos($base_path,$base_url);
    $url = substr($path,$pos)."/";
    return $url;
  }

  ############################################################################
  # Link to other PVP documents
  /** Provide a link with session info, if necessary
   * @class link
   * @method slink
   * @param string target url
   * @return string target url
   */
  function slink($target) {
    GLOBAL $pvp,$sess_id;
    if (!isset($pvp->cookie) || !$pvp->cookie->active) {
      if (!$sess_id) $sess_id = get_request("sess_id");
      $pos = strpos($target,"?");
      if ($pos) {
        $target .= "&sess_id=$sess_id";
      } else {
        $target .= "?sess_id=$sess_id";
      }
    }
    return $target;
  }

  /** Create a complete HREF for an URL and description
   * @class link
   * @method linkurl
   * @param string target url
   * @param string desc url-desc
   * @param string opt options for the HREF tag
   * @return string target complete href tag
   */
  function linkurl($target,$desc,$opt="") {
    $url = "<A HREF='" .$this->slink($target). "'";
    if ($opt) $url .= " $opt";
    $url .= ">$desc</A>";
    return $url;
  }

  /** Make a clickable image for context help
   * @method linkhelp
   * @param string topic
   * @return string link
   */
  function linkhelp($topic) {
    GLOBAL $pvp;
    if ($pvp->preferences->get("bubble_help_enable")) $title = " TITLE='".lang("help_for_block")."'";
    $link = "<A HREF=\"JavaScript:open_help('$topic');\"><IMG BORDER='0' ALT='".lang("help_for_block")."' SRC='"
          . $pvp->tpl_url."/images/info.gif'".$title." STYLE='cursor:help;'></A>";
    return $link;
  }

  ############################################################################
  # IMDB link creation
  /** Create url string to a persons entry in imdb (privat - called by formImdbPerson only)
   * @class link
   * @method ImdbPerson
   * @param string fname first name
   * @param string name family name
   * @param string occupation actor, director or what else
   * @param optional string imdb_id
   * @return string link link to detailled information in IMDB
   */
  function ImdbPerson($fname,$name,$occupation,$mid) {
    if (preg_match("|^\d{7}$|",$mid)) {
      $imdb = $this->imdb . "name/nm${mid}/";
      return $imdb;
    } elseif (strlen(trim($name))) {
      $imdb = $this->imdb . "Nsearch?name=";
      if (strlen(trim($fname))) {
        $imdb .= urlencode($fname) . "+";
      }
      $imdb .= urlencode($name) . "&type=substring&occupation=$occupation";
      return $imdb;
    } else { return ""; }
  } // end function ImdbPerson

  /** create form addon (to button) for link to a persons entry in imdb
   * @class link
   * @method formImdbPerson
   * @param string fname first name
   * @param string name family name
   * @param string occupation actor, director or what else
   * @param optional string imdb_id
   * @return string addon JavaScript handler for button to open new window
   *  with IMDB information
   */
  function formImdbPerson($fname,$name,$occupation,$mid="") {
    $imdb = $this->ImdbPerson($fname,$name,$occupation,$mid);
    if (strlen($imdb)) {
      return " onClick='window.open(\"$imdb\",\"imdb\")'";
    } else { return ""; }
  } // end function formImdbPerson

  /** Create url string to a titles entry in imdb (privat - called by formImdbTitle only)
   * @class link
   * @method ImdbTitle
   * @param string title movie title
   * @return string link link to detailled information in IMDB
   */
  function ImdbTitle($title) {
    if (strlen(trim($title))) {
      if (is_numeric($title) && strlen($title)==7) {
        $imdb = $this->imdb . "title/tt" .$title. "/";
      } else {
        $imdb = $this->imdb . "Tsearch?title=" . urlencode($title);
      }
      return $imdb;
    } else { return ""; }
  } // end function ImdbTitle

  /** create form addon (to button) for link to a titles entry in imdb
   * @class link
   * @method formImdbTitle
   * @param string title movie title
   * @return string addon JavaScript handler for button to open new window
   *  with IMDB information
   */
  function formImdbTitle($title) {
    $imdb = $this->ImdbTitle($title);
    if (strlen($imdb)) {
      return " onClick='window.open(\"$imdb\",\"imdb\")'";
    } else { return ""; }
  } // end function formImdbTitle

 } // end class link

 $pvp->link = new link;
?>