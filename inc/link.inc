<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Link related stuff: highlighting, linking targets etc.                    *
 \***************************************************************************/

 /* $Id$ */

 class link {
  var $imdb;
  
  function link() {
    $this->imdb = "http://us.imdb.com/";
  }

  ############################################################################
  # IMDB link creation
  // create url string to a persons entry in imdb
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

  // create form addon (to button) for link to a persons entry in imdb
  function formImdbPerson($fname,$name,$occupation) {
    $imdb = $this->ImdbPerson($fname,$name,$occupation);
    if (strlen($imdb)) {
      return " onClick=window.open(\"$imdb\",\"imdb\")";
    } else { return ""; }
  } // end function formImdbPerson

 } // end class link

 $pvp->link = new link;
?>