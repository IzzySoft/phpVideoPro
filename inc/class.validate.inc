<?php
 /***************************************************************************\
 * phpVideoPro                              (c) 2001,2002 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Verification/Validation of values (e.g. User Input)                       *
 \***************************************************************************/

  /* $Id$ */

  /** Verification/Validation of values (e.g. User Input)
   * @package Api
   * @class validate
   * @author Izzy (izzysoft@qumran.org)
   * @copyright (c) 2001,2002 by Itzchak Rehberg and IzzySoft
   */
  class validate {

    function validate() {
    }

    /** does $fvar contain only digits?
     * @class validate
     * @method num
     * @param string fvar
     * @return boolean state
     */
    function num($fvar) {
      $regnum = "/\D/";
      if (preg_match($regnum,$fvar)) return false;
      return true;
    }

    /** valid phone number: dial prefix (digits), separator ("-" or "/") and
        the number (digits)
     * @class validate
     * @method phone
     * @param string phone
     * @return boolean state
     */
    function phone($fvar) {
      if (substr($fvar,0,1) != "0") return false;
      $regnum = "/(\d)(-|\/)(\d)/";
      if (preg_match($regnum,$fvar,$matches)) return true;
      return false;
    }

    /** valid plz: must be numeric and $len chars of size
     * @class validate
     * @method plz
     * @param string plz
     * @param optional integer len
     * @return boolean state
     */
    function plz($fvar,$len=5) {
      if (!$this->num($fvar)) return false;
      if (strlen($fvar) != $len) return false;
      return true;
    }

    /** simple syntax ckeck for valid email address
     * @class validate
     * @method email
     * @param string address
     * @return boolean state
     */
    function email($address) {
      $rc1 = (ereg('^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+'.
             '@'.
	     '[-!#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+\.'.
	     '[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$',
	     $address));
      $rc2 = (preg_match('/.+\.\w\w+$/',$address));
      return ($rc1 && $rc2);
    }

    /** check if a date is incorrect (0), past (1), current (2) of future (3)
     * @class validate
     * @method date
     * @param integer month
     * @param integer day
     * @param integer year
     * @return integer state
     */
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