<?php
 #############################################################################
 # phpVideoPro                              (c) 2001,2002 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # User authorization managment                                              #
 #############################################################################

 /* $Id$ */

 /** User Authorization Managment
  * @package Api
  * @class auth
  * @author Izzy (izzysoft@qumran.org)
  * @copyright (c) 2001,2002 by Itzchak Rehberg and IzzySoft
  */
 class auth {

   /** Initialize the expiration time
    * @constructor auth
    */
   function auth() {
   }

   /** Verify login data
    * @class auth
    * @method verify_login
    * @param string login
    * @param string passwd
    * @return boolean success
    */
   function verify_login($login,$passwd) {
     GLOBAL $db;
     $user = $db->get_logindata($login);
     if ( $user->passwd == md5($passwd) ) return TRUE;
     return FALSE;
   }

 } // end class auth

 $pvp->auth = new auth();
?>