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
     GLOBAL $pvp,$db,$sess_id;
     if ($pvp->config->enable_cookies) $sess_id = $pvp->cookie->get("sess_id");
     $user_id = $pvp->session->verify($sess_id);
     if (!$user_id) { // guest account requested
       $user = $db->get_logindata("guest");
       $user_id = $user->id;
     }
     $this->user = $db->get_users($user_id);
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

 /** User information (privileges etc.)
  * @class auth
  * @attribute user
  */
?>