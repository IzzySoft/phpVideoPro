<?php
 #############################################################################
 # phpVideoPro                              (c) 2001,2002 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Cookie managment                                                          #
 #############################################################################

 /* $Id$ */

 /** Cookie Managment
  * @package Api
  * @class cookie
  * @author Izzy (izzysoft@qumran.org)
  * @copyright (c) 2001,2002 by Itzchak Rehberg and IzzySoft
  */
 class cookie {

   /** Initialize the expiration time
    * @constructor cookie
    * @param integer expire expiration timestamp (unix time)
    */
   function cookie($expire) {
     $this->expire = $expire;
   }

   /** Set a cookie
    * @class cookie
    * @method set
    * @param string name name of the cookie
    * @param string value value of the cookie variable
    * @return boolean success
    */
   function set($name,$value) {
     if (!$this->expire) { $expire = 0; }
       else { $expire = time() + $this->expire; }
     return setcookie($name,$value,$expire);
   }

   /** Get a cookie's content
    * @class cookie
    * @method get
    * @param string name name of the cookie to read
    * @return string content of the cookie
    */
   function get($name) {
     GLOBAL $_COOKIE;
     return $_COOKIE["$name"];
   }

  /** Delete a cookie
   * @class cookie
   * @method delete
   * @param string name name of the cookie to delete
   */
  function delete($name) {
    return $this->set($name,"");
  }

 } // end class cookie

 $pvp->cookie = new cookie($pvp->config->expire_cookies);
?>