<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
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
  * @copyright (c) 2001-2004 by Itzchak Rehberg and IzzySoft
  */
 class cookie {

   var $active;

   /** Initialize the expiration time
    * @constructor cookie
    * @param integer expire expiration timestamp (unix time)
    * @version the first try will always fail (for users who never visited
    *  this installation), since there is no way to set a cookie and read it
    *  back at the same time (cookies are sent in the HTML header). But this
    *  is not important, since for the logon we first send the form (+ cookie),
    *  and with the logon data we know the result (read cookie). Same applies
    *  to guests and preferences (first empty form + cookie, then result + cookie).
    */
   function cookie($expire) {
     $this->expire = $expire;
     $this->check_cookie();
   }

   /** Can we use cookies?
    * @class cookie
    * @method check_active
    */
   function check_cookie() {
     GLOBAL $pvp;
     if ($pvp->config->enable_cookies) {
       $accept = $this->get("accept_cookies");
       if (empty($accept)) { // if user accepts cookie we find out next time
         $this->set("accept_cookies","1");
         $this->active = FALSE;
       } else {
         $this->active = TRUE;
       }
     } else {
       $this->active = FALSE;
     }
   }

   /** Set a cookie
    * @class cookie
    * @method set
    * @param string name name of the cookie
    * @param string value value of the cookie variable
    * @return boolean success
    */
   function set($name,$value) {
     GLOBAL $base_url;
     if (!$this->expire) { $expire = 0; }
       else { $expire = time() + $this->expire; }
     return setcookie($name,$value,$expire,$base_url);
   }

   /** Get a cookie's content
    * @class cookie
    * @method get
    * @param string name name of the cookie to read
    * @return string content of the cookie
    */
   function get($name) {
     GLOBAL $_COOKIE;
     if (isset($_COOKIE["$name"])) return $_COOKIE["$name"];
     return "";
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

 /** Does this session use cookies?
  * @class cookie
  * @attribute boolean active
  */
?>