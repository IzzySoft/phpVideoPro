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
     $this->admin  = $this->user->admin;
     $this->browse = $this->user->browse;
     $this->add    = $this->user->add;
     $this->update = $this->user->upd;
     $this->delete = $this->user->del;
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
  * @attribute object user
  */
 /** Privileges for the actual user: admin
  * @class auth
  * @attribute boolean admin
  */
 /** Privileges for the actual user: browse (select)
  * @class auth
  * @attribute boolean browse
  */
 /** Privileges for the actual user: add entries
  * @class auth
  * @attribute boolean add
  */
 /** Privileges for the actual user: update (change) entries
  * @class auth
  * @attribute boolean update
  */
 /** Privileges for the actual user: delete entries
  * @class auth
  * @attribute boolean delete
  */
?>