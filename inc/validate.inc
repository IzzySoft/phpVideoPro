<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Verification/Validation of values (e.g. User Input)                       *
 \***************************************************************************/

  /* $Id$ */

  class validate {

    function validate() {
    }

    function num($fvar) { // does $fvar contain only digits
      $regnum = "/\D/";
      if (preg_match($regnum,$fvar)) return false;
      return true;
    }

    // dial prefix (digits), separator ("-" or "/") and the number (digits)
    function phone($fvar) {
      if (substr($fvar,0,1) != "0") return false;
      $regnum = "/(\d)(-|\/)(\d)/";
      if (preg_match($regnum,$fvar,$matches)) return true;
      return false;
    }

    // ckeck for valid plz: must be numeric and $len chars of size
    function plz($fvar,$len=5) {
      if (!$this->num($fvar)) return false;
      if (strlen($fvar) != $len) return false;
      return true;
    }

    // ckeck for valid email address
    function email($address) {
      $rc1 = (ereg('^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+'.
             '@'.
	     '[-!#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+\.'.
	     '[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$',
	     $address));
      $rc2 = (preg_match('/.+\.\w\w+$/',$address));
      return ($rc1 && $rc2);
    }

    // check if a date is incorrect (0), past (1), current (2) of future (3)
    function date($month,$day,$year) {
      if ( !checkdate($month,$day,$year) ) return 0;
      $today = getdate();
      if ($year  - $today[year] < 0) return 1;
      if ($year  - $today[year] > 0) return 3;
      if ($month - $today[mon]  < 0) return 1;
      if ($month - $today[mon]  > 0) return 3;
      if ($day   - $today[mday] < 0) return 1;
      if ($day   - $today[mday] > 0) return 3;
      return 2;
    }

  } // end class validate
  
  $valid = new validate;

?>