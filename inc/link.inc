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

  function linkImdbPerson($fname,$name,$occupation) {
    if (strlen(trim($name))) {
      $imdb = $this->imdb . "Nsearch?name=";
      if (strlen(trim($fname))) {
        $imdb .= $fname . "+";
      }
      $imdb .= $name . "&type=substring&occupation=$occupation";
      return " onClick=window.open(\"$imdb\",\"imdb\")";
    } else { return ""; }
  } // end function linkImdbPerson
 } // end class link
?>