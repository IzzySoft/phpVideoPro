<?php
 #############################################################################
 # phpVideoPro                              (c) 2001,2002 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Session managment                                                         #
 #############################################################################

 /* $Id$ */

 /** Session Managment
  * @package Api
  * @class cookie
  * @author Izzy (izzysoft@qumran.org)
  * @copyright (c) 2001,2002 by Itzchak Rehberg and IzzySoft
  */
 class session {

   var $id,$user_id,$ip,$started,$login;

   /** Initialize the expiration time
    * @constructor session
    */
   function session() {
   }

  /** Create a random session id
   * @class session
   * @method randomstring
   * @param optional integer size length of random string to create (default: 10)
   * @return string randomly created string
   */
  function randomstring($size=10) {
    $s = "";
    srand((double)microtime()*1000000);
    $random_char = array('0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f',
                         'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
			 'w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L',
			 'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z');
    for ($i=0;$i<$size;++$i) {
      $s .= $random_char[rand(1,61)];
    }
    return $s;
  }

  /** Cleanup session table
   * @class session
   * @method clean_db
   */
  function clean_db() {
    GLOBAL $db,$pvp;
    if ($pvp->config->session_purgetime) {
      $db->dbquery("DELETE FROM pvp_sessions WHERE dla<".time()-$pvp->config->session_purgetime);
    }
  }

  /** Create a session
   * @class session
   * @method create
   * @param string login
   * @param string passwd
   * @return string id session identifier
   */
  function create($login,$passwd) {
    GLOBAL $db,$pvp,$REMOTE_ADDR;
    $this->login = $login;
    $this->clean_db();
    if ( $user_id = $pvp->auth->verify_login($login,$passwd) ) {
      $id = md5( $this->randomstring() );
      $ip = $REMOTE_ADDR;
      $started = time();
      if ( $db->create_session($id,$ip,$user_id,$started) ) {
        return $id;
      } else { return FALSE; }
    } else {
      return FALSE;
    }
  }

  /** Verify a session
   * @class session
   * @method verify
   * @param string id identifier of the session to verify
   * @return integer user-id
   */
  function verify($id) {
    GLOBAL $db,$REMOTE_ADDR;
    return $db->verify_session($id,$REMOTE_ADDR);
  }

  /** Destroy a session
   * @class session
   * @method destroy
   * @param string id identifier of the session to destroy
   */
  function destroy($id) {
  }

 } // end class auth

 $pvp->session = new session();
?>