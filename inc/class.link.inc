<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
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
  * @author Izzy (izzysoft@qumran.org)
  * @copyright (c) 2001,2002 by Itzchak Rehberg and IzzySoft
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
    $this->imdb = $pvp->preferences->get("imdb_url");
  }

  /** Provide a link with session info, if necessary
   * @class link
   * @method slink
   * @param string target url
   * @return string target url
   */
  function slink($target) {
    GLOBAL $pvp,$sess_id;
    if (!$pvp->config->enable_cookies) {
      if (!$sess_id) $sess_id = $_REQUEST["sess_id"];
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

  ############################################################################
  # IMDB link creation
  /** Create url string to a persons entry in imdb (privat - called by formImdbPerson only)
   * @class link
   * @method ImdbPerson
   * @param string fname first name
   * @param string name family name
   * @param string occupation actor, director or what else
   * @return string link link to detailled information in IMDB
   */
  function ImdbPerson($fname,$name,$occupation) {
    if (strlen(trim($name))) {
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
   * @return string addon JavaScript handler for button to open new window
   *  with IMDB information
   */
  function formImdbPerson($fname,$name,$occupation) {
    $imdb = $this->ImdbPerson($fname,$name,$occupation);
    if (strlen($imdb)) {
      return " onClick=window.open(\"$imdb\",\"imdb\")";
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
      $imdb = $this->imdb . "Tsearch?title=" . urlencode($title);
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
      return " onClick=window.open(\"$imdb\",\"imdb\")";
    } else { return ""; }
  } // end function formImdbTitle

 } // end class link

 $pvp->link = new link;
?>