<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Maintain the (DB-stored) user preferences                                 *
 \***************************************************************************/

 /* $Id$ */

 class preferences {
  var $colors, $lang, $template, $display_limit, $date_format, $page_length;
  
  ############################################################################
  # constructor: read all values from DB
  function preferences() {
    GLOBAL $db;
    $pnames = array ("lang","template","display_limit","date_format",
              "page_length");
    foreach ($pnames as $var) {
      $this->$var = $db->get_preferences($var);
    }
    $colors = $db->get_preferences('colors');
    if ($colors) {
      $colors = unserialize( rawurldecode($colors) );
      $colors["ok"] = "<FONT COLOR=\"" . $colors["ok"] . "\">";
      $colors["err"] = "<FONT COLOR=\"" . $colors["err"] . "\">";
      $GLOBALS['colors'] = $colors;
    }
  }

  ############################################################################
  # set a preference
  function set($name,$value) {
    GLOBAL $db;
    $db->set_preferences($name,$value);
  }

 } // end class preferences

?>