<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2009 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Common SQL helper funcs used for most database accesses                   #
 #############################################################################

 /* $Id$ */

 /** Common SQL helper funcs used for most database accesses
  *  (extends DB_Sql fom PHPLIB)
  * @package Api
  * @class sql
  * @extends DB_Sql
  * @author Izzy (izzysoft AT qumran DOT org)
  * @copyright (c) 2001-2009 by Itzchak Rehberg and IzzySoft
  * @version $Revision$ $Date$
  */
 /** SQL substring to limit result sets to a certain number
  * @class sql
  * @attribute string limit
  */
 class sql extends DB_Sql {
   VAR $limit;

   /** Constructor: initialize base class, initialize limit property depending on database type
    * @constructor sql
    */
   function sql() { // init
     $this->DB_Sql(); // constructor of base class needs explicit call
   }

   ############################################################################
   # common stuff
   ############################################################################
   /** setup sql clause to limit result set (depending on database type)
    * @method private limit
    * @param optional integer start
    * @return string limit SQL limit clause for the configured database type
    */
   function limit($start=0) {
     GLOBAL $pvp;
     switch($pvp->config->db->type) {
       case "mysql" : $this->limit = " LIMIT $start," . $pvp->preferences->get("display_limit");
                      break;
       case "sqlite":
       case "pgsql" : $this->limit = " LIMIT " . $pvp->preferences->get("display_limit") . " OFFSET $start";
                      break;
       default      : $this->limit = ""; break;
     }
     return $this->limit;
   }

   /** replace empty values within SQL queries by NULL statement to keep query
    * syntactically correct
    * @method private clean_query
    * @param string query query to clean
    */
   function clean_query(&$query) {
     $query = str_replace ("''", "NULL", $query);
     $query = str_replace ("''", "NULL", $query);
     $query = str_replace (",,", ",NULL,", $query);
     $query = str_replace (",,", ",NULL,", $query);
     $query = str_replace ("=,", "=NULL,", $query);
     $query = str_replace ("= ", "=NULL ", $query);
     $query = str_replace ("(,", "(NULL,", $query);
     $query = str_replace (",)", ",NULL)", $query);
#     $query = str_replace ("\",", "\"NULL,", $query);
#     $query = str_replace (",\"", ",NULL\"", $query);
     if (substr($query,strlen($query)-1)=="=") $query .= "NULL";
   } // end clean_query()

   /** do a query on the db and provide debug output
    * @method dbquery
    * @param string query SQL statement to execute
    * @return boolean success
    */
   function dbquery($query) {
     debug("S","<SPAN CLASS='ok'>$query</SPAN><BR>\n");
     $this->clean_query($query);
     if ( $this->query($query) ) return 1;
     return 0;
   }

   /** Query db using the LIMIT clause. returns count of TOTAL datasets found
    *  (i.e. UNLIMITED query result count). $query must NOT contain any limit
    *  clause!!!
    * @method private lim_query
    * @param string query SQL statement to execute
    * @param optional integer start
    * @return integer totals (result set count)
    */
   function lim_query($query,$start=0,$dummy="") {
     if ( $this->dbquery($query) ) {
       $totals = $this->num_rows();
       $this->limit($start);
       $query .= $this->limit;
       $this->dbquery($query);
       return $totals;
     }
     return 0;
   }

   /** Delete a complete row from a table
    * @method private delete_row
    * @param string table table name
    * @param string id row id(s) to delete (multiple IDs must be separated by
    *  commata; row id is the value of the id column)
    * @return boolean success
    */
   function delete_row($table,$id) {
     return $this->dbquery("DELETE FROM $table WHERE id IN ($id)"); 
   }

   ############################################################################
   # translations
   ############################################################################
   /** Get languages available for audio/subtitle
    * @method get_avlang
    * @param string type ("audio"|"subtitle")
    * @return array langs array 0..n of object (id=lang_id,name=translated langname)
    */
   function get_avlang($type) {
     $this->query("SELECT lang_id FROM pvp_languages WHERE $type=1");
     while ($this->next_record()) {
       $lang[] = $this->f("lang_id");
     }
     $lc = count($lang);
     for ($i=0;$i<$lc;++$i) {
       $name[] = lang("lang_".$lang[$i]);
     }
     asort($name); reset($name); $i=0;
     while ( list($key,$val) = each($name) ) {
       $list[$i]->id   = $lang[$key];
       $list[$i]->name = $name[$key];
       ++$i;
     }
     return $list;
   }

   /** (Un)Set enabled flag for audio or subtitle
    * @method set_avlang
    * @param string lang_id language key like "de" or "en"
    * @param integer flag 0=disable, 1=enable
    * @param string type "audio" or "subtitle"
    * @return boolean success
    */
   function set_avlang($id,$flag,$type) {
     if ( ($flag < 0) || ($flag > 1) ) return FALSE;
     if ( (strtolower($type)!="audio") && (strtolower($type)!="subtitle") ) return FALSE;
     $query = "UPDATE pvp_languages SET $type=$flag WHERE lang_id='$id'";
     return $this->query($query);
   }

   /** Get list of all languages with all available settings from language table
    * @method get_langlist
    * @param optional string id lang_id
    * @param optional integer start for limited queries
    * @return mixed array [0..n] of objects (id,name,charset,available,audio,subtitle)
    *  or just one object if id is passed
    */
   function get_langlist($id="",$start="") {
     $query = "SELECT lang_id,lang_name,charset,available,audio,subtitle "
            . "FROM pvp_languages";
     if ($id!=="") $query .= " WHERE lang_id='$id'";
     if ($start==="") { $this->query($query);
     } else { $totals = $this->lim_query($query,$start); }
     $details = array("charset","available","audio","subtitle");
     while ( $this->next_record() ) {
       foreach ($details as $var) {
         $s->$var = $this->f($var);
       }
       $s->id   = $this->f("lang_id");
       $s->name = $this->f("lang_name");
       $list[]  = $s;
       unset($s);
     }
     if (!isset($totals)) $totals = 0;
     $list["totals"] = $totals;
     if ($id) return $list[0];
     return $list;
   }

   /** Get installed languages (both available and unavailable)
    * @method get_installedlang
    * @return array language names (lang)
    */
   function get_installedlang() {
     $this->dbquery("SELECT distinct lang FROM pvp_lang ORDER BY lang");
     while ( $this->next_record() ) {
       $lang[] = $this->f('lang');
     }
     return $lang;
   }

   /** Get (un)available|all languages
    * @method get_languages
    * @param optional integer avail available (1) or unavailable(0); default: both
    * @return array languages (id,name, charset, avail)
    */
   function get_languages($avail="") {
     switch ($avail) {
       case "0" : $where = "WHERE lower(available)='no'"; break;
       case "1" : $where = "WHERE lower(available)='yes'"; break;
       default  : $where = "";
     }
     $this->dbquery("SELECT lang_id,lang_name,charset,available FROM pvp_languages $where ORDER BY lang_name");
     $i=0; $lang = array();
     while ( $this->next_record() ) {
       $lang[$i]["id"]   = $this->f('lang_id');
       $lang[$i]["name"] = $this->f('lang_name');
       $lang[$i]["charset"] = $this->f('charset');
       if ( strtolower( $this->f('available') ) == "yes" ) {
         $lang[$i]["avail"]  = 1;
       } else {
         $lang[$i]["avail"]  = 0;
       }
       ++$i;
     }
     return $lang;
   }

   /** Make a language (un)available
    * @method lang_available
    * @param string lang language id
    * @param optional integer avail defaults to "1"
    */
   function lang_available($lang,$avail=1) {
     if ($avail) $this->dbquery("UPDATE pvp_languages SET available='yes' WHERE lang_id='$lang'");
     else $this->dbquery("UPDATE pvp_languages SET available='no' WHERE lang_id='$lang'");
   }

   /** delete translations for a specific language
    * @method delete_translations
    * @param string lang language id
    */
   function delete_translations($lang) {
     $this->dbquery("DELETE FROM pvp_lang WHERE lang='$lang'");
   }

   /** Get all translations and return them as array
    * @method get_translations
    * @param string pref_lang language id of preferred language
    * @return array translations (msg_id:=trans(msg_id))
    */
   function get_translations($pref_lang) {
     $def_lang = "en";
     $this->dbquery("SELECT message_id,content FROM pvp_lang WHERE lang='$def_lang'");
     while ( $this->next_record() ) { // initiate with fall-back
       $msg_id         = $this->f('message_id');
       $trans[$msg_id] = stripslashes($this->f('content'));
     }
     if ($pref_lang != $def_lang) {
       $this->dbquery("SELECT message_id,content FROM pvp_lang WHERE lang='$pref_lang'");
       while ( $this->next_record() ) { // overwrite with preferred (if exists)
         $msg_id         = $this->f('message_id');
         $trans[$msg_id] = stripslashes($this->f('content'));
       }
     }
     return $trans;
   }

   /** Get ALL translations for a given msgID (for backup)
    * @method get_trans_all
    * @param string message_id
    * @return array lang=&gt;translation
    */
   function get_trans_all($id) {
     $this->dbquery("SELECT lang,content FROM pvp_lang WHERE message_id='$id'");
     while ( $this->next_record() ) {
       $lang = $this->f('lang');
       $list[$lang] = $this->f('content');
     }
     return $list;
   }

   /** Set a translation: if $trans is empty, translation for the specified
    *  language and message $id will be removed. Otherwise the new translation
    *  will be updated or inserted
    * @method set_translation
    * @param string id translation identifier
    * @param string trans translated string
    * @param string lang language of the translation
    * @return boolean success
    */
   function set_translation($id,$trans,$lang) {
     if (!$trans) { // remove translation
       $this->query("DELETE FROM pvp_lang WHERE message_id='$id' AND lang='$lang'");
     } else {
       $trans = addslashes($trans);
       $this->query("SELECT * FROM pvp_lang WHERE message_id='$id' AND lang='$lang'");
       if ( $this->next_record() ) {
         $this->query("UPDATE pvp_lang SET content='$trans' WHERE lang='$lang' AND message_id='$id'");
       } else {
         $this->query("INSERT INTO pvp_lang (message_id,lang,content) VALUES ('$id','$lang','$trans')");
       }
     }
     return $this->affected_rows();
   }

   /** Get translations for the specified language only (for admin)
    * @method get_singletrans
    * @param string lang language to retrieve for
    * @param optional integer start (for lim_query)
    * @param optional string msgID single translation to catch
    * @param optional string key first letter of the first message_id to match
    * @return array of object translations (msgID = translation, xlist[] of msgIDs)
    */
   function get_singletrans($lang,$start="",$msg="",$key="") {
     $query = "SELECT message_id,content,comment FROM pvp_lang WHERE lang='$lang'";
     if ($key) { $query .= " AND message_id>'$key'"; }
     if ($msg) { $query .= " AND message_id='$msg'"; }
       else { $query .= " ORDER BY message_id"; }
     if ($start==="") { $this->dbquery($query); }
       else { $totals = $this->lim_query($query,$start); }
     while ( $this->next_record() ) {
       $msg = $this->f('message_id');
       $trans["$msg"] = stripslashes($this->f('content'));
       $trans["xcomment"]["$msg"] = stripslashes($this->f('comment'));
       $list[] = $msg;
     }
     if (isset($totals)) $trans['totals'] = $totals;
     if (isset($list)) $trans["xlist"] = $list;
     if (isset($trans)) return $trans;
     return array();
   }

   ############################################################################
   # options
   ############################################################################
   /** Get list of options
    * @method get_options
    * @param optional string name name of option to retrieve values for
    * @return array array of option arrays ($list['name'][$i]=value)
    */
   function get_options($name="") {
     $query = "SELECT name,value"
            . "  FROM pvp_options";
     if (strlen($name)) { $query .= " WHERE name='$name'"; }
     $this->query($query);
     $list = array();
     while ( $this->next_record() ) {
       $optname = $this->f('name');
       $list["$optname"][] = $this->f('value');
     }
     return $list;
   }

   /** Setup the imdb_tx option array
    * @method imdb_tx_setup
    * @param optional integer user_id
    * @return array (var:=val)
    */
   function imdb_tx_setup($user_id="") {
     if (empty($user_id) || !$user_id) $user_id = "";
     $opts = $this->get_options("imdb_tx");
     foreach ($opts["imdb_tx"] as $val) {
       $tx[$val] = $this->get_preferences($val,$user_id);
     }
     return $tx;
   }

   ############################################################################
   # preferences
   ############################################################################
   /** Get preferences from DB (used by class preferences; use that class to
    *  obtain preference settings!)
    * @method get_preferences
    * @param string name preference name
    * @param optional integer user_id
    * @return mixed setting of requested preference
    * @see preferences::filter
    */
   function get_preferences($name,$user_id="") {
     if ($user_id=="") {
       $preftab  = "pvp_preferences";
       $restrict = "";
     } else {
       $preftab  = "pvp_userprefs";
       $restrict = "AND user_id=$user_id";
     }
     $this->query("SELECT value FROM $preftab WHERE name='$name' $restrict");
     if ( $this->next_record() ) {
       return $this->f('value');
     } else {
       return "";
     }
   }

   /** Get ALL preferences from DB (for backup)
    * @method get_preferences_all
    * @param string type "default" or "user"
    * @return array preferences (name=&gt;value) or empty array for unknown type
    */
   function get_preferences_all($type) {
     switch ($type) {
       case "default" : $preftab = "pvp_preferences"; break;
       case "user"    : $preftab = "pvp_userprefs"; break;
       default        : return array(); break;
     }
     $this->query("SELECT name,value FROM $preftab");
     while ( $this->next_record() ) {
       $name = $this->f('name');
       $pref[$name] = $this->f('value');
     }
     return $pref;
   }

   /** Set preferences in DB (if exist: update, otherwise insert)
    *  Used by class preferences: use that class to modify settings!
    * @method set_preferences
    * @param string name
    * @param mixed value
    * @param optional integer user_id
    * @return integer success return value from sql::dbquery on update/insert
    * @see preferences::filter
    */
   function set_preferences($name,$value,$user_id="") {
     GLOBAL $pvp;
     $value = $pvp->common->safeinput($value);
     if ($user_id=="") {
       $preftab  = "pvp_preferences";
       $restrict = "";
       $insert   = "INSERT INTO $preftab (name,value) VALUES ('$name','$value')";
     } else {
       $preftab  = "pvp_userprefs";
       $restrict = "AND user_id=$user_id";
       $insert   = "INSERT INTO $preftab (user_id,name,value) VALUES ($user_id,'$name','$value')";
     }
     $this->query("SELECT value FROM $preftab WHERE name='$name' $restrict");
     if ( $this->next_record() ) {
       return $this->dbquery("UPDATE $preftab SET value='$value' WHERE name='$name' $restrict");
     } else {
       return $this->dbquery($insert);
     }
   }

   /** Remove preferences from DB
    *  Used by class preferences: use that class to modify settings!
    * @method unset_preferences
    * @param string name
    * @see preferences::filter
    */
   function unset_preferences($name) {
     $this->dbquery("DELETE FROM pvp_preferences WHERE name='filter'");
   }

   ############################################################################
   # configuration
   ############################################################################
   /** Get some config value
    * @method get_config
    * @param string name config vars name
    * @return string value
    */
   function get_config($name) {
     $this->query("SELECT value FROM pvp_config WHERE name='$name'");
     if ( $this->next_record() ) {
       return $this->f('value');
     } else {
       return "";
     }
   }

   /** Get all data from configuration table
    * @method get_config_all
    * @return array (name=>value)
    */
   function get_config_all() {
     $this->query("SELECT name,value FROM pvp_config");
     while ( $this->next_record() ) {
       $name = $this->f('name');
       $conf[$name] = $this->f('value');
     }
     return $conf;
   }

   /** Set some config value
    * @method set_config
    * @param string name config vars name
    * @return integer success return value from sql::dbquery on update/insert
    */
   function set_config($name,$value) {
     GLOBAL $pvp;
     $value = $pvp->common->safeinput($value);
     $this->query("SELECT value FROM pvp_config WHERE name='$name'");
     if ( $this->next_record() ) {
       return $this->dbquery("UPDATE pvp_config SET value='$value' WHERE name='$name'");
     } else {
       return $this->dbquery("INSERT INTO pvp_config (name,value) VALUES ('$name','$value')");
     }
   }

   ############################################################################
   # Session managment
   ############################################################################
   /** Create a session
    * @method create_session
    * @param string id session-id
    * @param string ip remote-ip
    * @param integer user_id
    * @param timestamp started
    * @return boolean success
    */
   function create_session($id,$ip,$user_id,$started) {
     $query = "INSERT INTO pvp_sessions (id,ip,user_id,started,dla) VALUES ("
            . "'$id','$ip',$user_id,'$started','$started')";
     return $this->query($query);
   }

   /** End a session
    * @method end_session
    * @param string sess_id
    * @param string ip
    * @param timestamp end
    */
   function end_session($sess_id,$ip,$end) {
     $this->query("UPDATE pvp_sessions SET ended='$end' WHERE id='$sess_id' AND ip='$ip'");
   }

   /** Verify (and update) a session
    * @method verify_session
    * @param string id session-id
    * @param string ip remote-ip
    * @return mixed integer user-id or FALSE
    */
   function verify_session($id,$ip) {
     GLOBAL $pvp;
     $query = "SELECT user_id FROM pvp_sessions "
            . "WHERE id='$id' AND ip='$ip' AND ended IS NULL";
     if (isset($pvp->config->session_purgetime) && $pvp->config->session_purgetime) {
       $dla = time()-$pvp->config->session_purgetime;
       $query .= " AND dla>'$dla'";
     }
     $this->query($query);
     if ( $this->next_record() ) {
       $user_id = $this->f('user_id');
       $this->dbquery("UPDATE pvp_sessions SET dla=".time()." WHERE id='$id' AND ip='$ip'");
       return $user_id;
     } else {
       return FALSE;
     }
   }

   /** Get list of registered sessions
    * @method get_sessions
    * @param optional integer start to limit queries
    * @return array array of session objects (sess_id,ip,user,start,dla,end)
    */
   function get_sessions($start="") {
     $query = "SELECT s.id AS sess_id,s.ip,s.started,s.dla,s.ended,u.login AS user"
            . "  FROM pvp_sessions s,pvp_users u"
	    . " WHERE s.user_id=u.id";
     if ($start==="") { $this->dbquery($query); }
       else { $totals = $this->lim_query($query,$start); }
     $details = array("sess_id","ip","started","dla","ended","user");
     while ( $this->next_record() ) {
       foreach ($details as $var) {
         $s[$var] = $this->f($var);
       }
       $list[] = $s;
     }
     if ($totals) $list['totals'] = $totals;
     return $list;
   }

   /** remove a session from DB
    * @method remove_session
    * @param optional string sess_id session identifier
    * @param optional integer days purge older than $days (give empty sess_id for this)
    * @return boolean success
    * @version if called without parameters, all ended sessions are removed
    */
   function remove_session($id="",$days="") {
     if ($days) {
       $pdate = time() - ($days * 86400);
       $query = "DELETE FROM pvp_sessions WHERE dla<'$pdate'";
     } elseif ($id) {
       $query = "DELETE FROM pvp_sessions WHERE id='$id'";
     } else {
       $query = "DELETE FROM pvp_sessions WHERE ended IS NOT NULL";
     }
     return $this->query($query);
   }

   ############################################################################
   # User managment
   ############################################################################
   /** Get users
    * @method get_users
    * @param optional integer user_id
    * @return mixed array users (array of objects;
    *  properties: id,login,pwd (md5 hash), admin,browse,ins,upd,del, comment)
    *  or FALSE if no users in DB
    */
   function get_users($user_id="") {
     $query = "SELECT id,login,pwd,admin,browse,ins,upd,del,comment FROM pvp_users";
     if ($user_id!=="") $query .= " WHERE id=$user_id";
     $this->query($query);
     $i=0;
     while ( $this->next_record() ) {
       $users[$i]->id     = $this->f('id');
       $users[$i]->login  = $this->f('login');
       $users[$i]->pwd    = $this->f('pwd');
       $users[$i]->admin  = $this->f('admin');
       $users[$i]->browse = $this->f('browse');
       $users[$i]->add    = $this->f('ins');
       $users[$i]->upd    = $this->f('upd');
       $users[$i]->del    = $this->f('del');
       $users[$i]->comment= $this->f('comment');
       ++$i;
     }
     if ($user_id!=="" && $i) {
       return $users[0];
     }
     if ($i) { return $users; } else { return FALSE; }
   }

   /** Get login data
    * @method get_logindata
    * @param string login user login
    * @return object user (properties: id,passwd)
    */
   function get_logindata($login) {
     $this->dbquery("SELECT id,pwd FROM pvp_users WHERE login='$login'");
     if ( $this->next_record() ) {
       $user->id     = $this->f('id');
       $user->passwd = $this->f('pwd');
       return $user;
     } else {
       return FALSE;
     }
   }

   /** Update user record
    * @method set_user
    * @param object user single user object (as defined as element of userlist array)
    * @return boolean success
    */
   function set_user($user) {
     GLOBAL $pvp;
     $ouser = $this->get_users($user->id);
     if (in_array(strtolower($ouser->login),$pvp->protected_users)) $login = $ouser->login;
     else $login   = $pvp->common->safeinput($user->login);
     $comment = $pvp->common->safeinput($user->comment);
     $query = "UPDATE pvp_users SET login='$login',admin=".$user->admin
            . ",browse=".$user->browse.",ins=".$user->add.",upd=".$user->upd
	    . ",del=".$user->del.",comment='$comment'";
     if (isset($user->pwd)) $query .= ",pwd='".md5($user->pwd)."'";
     $query .= " WHERE id=".$user->id;
     $this->dbquery($query);
     if ( $this->affected_rows() < 0 ) return FALSE;
     return TRUE;
   }

   /** Add user
    * @method add_user
    * @param object user single user object (as defined as element of userlist array)
    * @return boolean success
    */
   function add_user($user) {
     GLOBAL $pvp;
     $login   = $pvp->common->safeinput($user->login);
     $comment = $pvp->common->safeinput($user->comment);
     $query = "INSERT INTO pvp_users (login,admin,browse,ins,upd,del,comment";
     if (isset($user->pwd)) $query .= ",pwd";
     $query .= ") VALUES ('$login',".$user->admin.",".$user->browse.","
	      .$user->add.",".$user->upd.",".$user->del.",'$comment'";
     if (isset($user->pwd)) $query .= ",'".md5($user->pwd)."'";
     $query .= ")";;
     $this->dbquery($query);
     if ( $this->affected_rows() < 0 ) return FALSE;
     return TRUE;
   }

   /** Delete user
    * @method del_user
    * @param integer id id of user to delete
    * @return boolean success
    */
   function del_user($id) {
     GLOBAL $pvp;
     $user = $this->get_users($id);
     if (in_array(strtolower($user->login),$pvp->protected_users)) return FALSE; // never delete protected users
     $this->dbquery("SELECT count(*) AS count FROM pvp_media WHERE owner=$id");
     $this->next_record();
     if ($this->f('count')!=0) return FALSE; // still media associated with this user - use user_media_delete or _xfer first
     $this->dbquery("DELETE FROM pvp_usergrants WHERE grantee=$id OR grantor=$id");
     $this->dbquery("DELETE FROM pvp_users WHERE id=$id");
     if ( $this->affected_rows() < 0 ) return FALSE;
     return TRUE;
   }

   /** Set usergrants
    * @method set_usergrants
    * @param integer grantor user ID of grantor
    * @param integer grantee user ID of grantee
    * @param string grant grant level
    * @return boolean success
    */
   function set_usergrants($grantor,$grantee,$grant) {
     $this->dbquery("DELETE FROM pvp_usergrants WHERE grantor=$grantor AND grantee=$grantee");
     $query = "INSERT INTO pvp_usergrants (grantor,grantee,grants) VALUES (";
     switch ($grant) {
       case "DELETE" : $this->dbquery("$query $grantor,$grantee,'DELETE')");
       case "UPDATE" : $this->dbquery("$query $grantor,$grantee,'UPDATE')");
       case "INSERT" : $this->dbquery("$query $grantor,$grantee,'INSERT')");
       case "SELECT" : $this->dbquery("$query $grantor,$grantee,'SELECT')");
     }
     return TRUE;
   }

   /** Get list of usergrants
    * @method get_usergrants
    * @param optional array grantor array of INT (IDs)
    * @param optional array grantee array of INT (IDs)
    * @param optional array grant array of string (grants)
    * @return mixed grants
    * <pre>array[] of user_id when grantor/grantee and grant given
    *  array[] of grant when grantor and grantee given
    *  array[grantor][] of user_id (grantee) when only grants given
    *  array[grantor|grantee][] of grant when grantor or grantee given
    *  array[grantor][grantee][] of grant when no params given
    *  boolean when all params given</pre>
    */
   function get_usergrants($grantor=array(),$grantee=array(),$grant=array()) {
     if (empty($grant)) { // no grants specified
       if (empty($grantee)) { // no grantee given
         if (empty($grantor)) { // no param specified
           $this->query("SELECT grantor,grantee,grants FROM pvp_usergrants");
           while ($this->next_record()) {
             $grantor = $this->f('grantor');
             $grantee = $this->f('grantee');
             $list[$grantor][$grantee][] = $this->f('grants');
           }
         } else { // only grantor specified
           $glist = implode(",",$grantor);
           $this->query("SELECT grantee,grants FROM pvp_usergrants WHERE grantor IN ($glist)");
           while ($this->next_record()) {
             $grantee = $this->f('grantee');
             $list[$grantee][] = $this->f('grants');
           }
         }
       } else { // we have grantee and NO grant
         if (empty($grantor)) { // only grantee
           $grantees = implode(",",$grantee);
           $this->query("SELECT grantor,grants FROM pvp_usergrants WHERE grantee IN ($grantees)");
           while ($this->next_record()) {
             $grantor = $this->f('grantor');
             $list[$grantor][] = $this->f('grants');
           }
         } else { // grantor and grantee, but no grants
           $grantors = implode(",",$grantor);
           $grantee[] = 0; // if grantor gave to public, he gave to everybody
           $grantees = implode(",",$grantee);
           $this->query("SELECT grants FROM pvp_usergrants WHERE grantee IN ($grantees) AND grantor IN ($grantors)");
           while ($this->next_record()) {
             $list[] = $this->f('grants');
           }
         }
       }
     } else { // grants specified
       if (empty($grantee)) { // grants but NO grantee
         if (empty($grantor)) { // grants only
           $grants   = implode(",",$grant);
           $grants   = "'".str_replace(",","','",$grants)."'";
           $this->query("SELECT grantor,grantee FROM pvp_usergrants WHERE grants IN ($grants)");
           while ($this->next_record()) {
             $grantor = $this->f('grantor');
             $list[$grantor][] = $this->f('grantee');
           }
         } else { // grants and grantor, no grantee
           $grantors = @implode(",",$grantor);
           $grants   = @implode(",",$grant);
           $grants   = "'".str_replace(",","','",$grants)."'";
           $this->query("SELECT grantee FROM pvp_usergrants WHERE grantor IN ($grantors) AND grants IN ($grants)");
           while ($this->next_record()) {
             $list[] = $this->f('grantee');
           }
           $list = array_merge($list,$grantor); // everybody has grants to himself
           $list = array_values(array_unique($list));
         }
       } else { // we have grantee and grant
         if (empty($grantor)) { // only grantee and grant
           $grantees = @implode(",",$grantee);
           $grants   = @implode(",",$grant);
           $grants   = "'".str_replace(",","','",$grants)."'";
           $this->query("SELECT grantor FROM pvp_usergrants WHERE grantee IN ($grantees) AND grants IN ($grants)");
           while ($this->next_record()) {
             $list[] = $this->f('grantor');
           }
           $list[] = 0; // public gives to everybody
           $list = array_merge($list,$grantee); // everybody grants everything to himself
           $list = array_values(array_unique($list));
         } else { // all params given
           $grantors = implode(",",$grantor);
           $grantee[] = 0; // if grantor gave to public, he gave to everybody
           $grantees = implode(",",$grantee);
           $grants   = implode(",",$grant);
           $grants   = "'".str_replace(",","','",$grants)."'";
           $this->query("SELECT COUNT(*) AS gnum FROM pvp_usergrants WHERE grantor IN ($grantors) AND grantee IN ($grantees) AND grants IN ($grants)");
           $this->next_record();
           $gnum = $this->f('gnum');
           return ($gnum>0);
         }
       }
     }
     return $list;
   }

   ############################################################################
   # people and their names
   ############################################################################
   /** Format a names array
    * @method private format_name
    * @param array name
    * return array name (name,reverse,firstname,fullname,imdb_id)
    */
   function format_name($name) {
     $name['name'] = $name['reverse'] = trim($name['name']);
     $name['firstname'] = $name['fullname'] = trim($name['firstname']);
     if (strlen($name['fullname'])) {
       if (strlen($name['firstname'])) $name['fullname'] .= " " . $name['name'];
     } else {
       $name['fullname'] = $name['name'];
     }
     if (strlen($name['reverse'])) {
       if (strlen($name['firstname'])) $name['reverse'] .= ", " . $name['firstname'];
     } else {
       $name['reverse'] = $name['firstname'];
     }
     return $name;
   }

   /** Get all data for a person and return it as array
    * @method private get_person
    * @param integer id person id
    * @param string table tablename (actors, directors, etc)
    * @return array person data (formatted by sql::format_name)
    */
   function get_person($id,$table) {
     if ($id) {
       $this->dbquery("SELECT firstname,name,imdb_id FROM $table WHERE id=$id");
       if ( $this->next_record() ) {
         $person['id']   = trim($id);
         $person['name'] = $this->f('name');
         $person['firstname'] = $this->f('firstname');
	 $person['imdb_id']   = $this->f('imdb_id');
	 $person = $this->format_name($person);
       } else {
         $person['name'] = $person['firstname'] = $person['fullname'] = $person['reverse'] = $person['imdb_id'] = "";
       }
     } else {
       $this->dbquery("SELECT id,firstname,name,imdb_id FROM $table");
       $i=0;
       while ( $this->next_record() ) {
         $person[$i]['id']   = $this->f('id');
         $person[$i]['name'] = $this->f('name');
         $person[$i]['firstname'] = $this->f('firstname');
	 $person[$i]['imdb_id']   = $this->f('imdb_id');
	 $person[$i] = $this->format_name($person[$i]);
	 ++$i;
       }
     }
     return $person;
   }

   /** Get all data for an actor and return it as array (wrapper to get_person)
    * @method get_actor
    * @param integer id actor id
    * @return array actor data (formatted by format_name)
    */
   function get_actor($id) {
     return $this->get_person($id,"pvp_actors");
   }

   /** Get all data for a director and return it as array (wrapper to get_person)
    * @method get_director
    * @param integer id director id
    * @return array director data (formatted by format_name)
    */
   function get_director($id) {
     return $this->get_person($id,"pvp_directors");
   }

   /** Get all data for a componist and return it as array (wrapper to get_person)
    * @method get_music
    * @param integer id componist's id
    * @return array componist's data (formatted by format_name)
    */
   function get_music($id) {
     return $this->get_person($id,"pvp_music");
   }

   /** Get distinct staff ids from video table and return them as array
    * @method get_distinct_staffids
    * @param string field name of id field to search
    * @return array array of ids
    */
   function get_distinct_staffids($field) {
     $this->dbquery("SELECT DISTINCT $field FROM pvp_video");
     while ( $this->next_record() ) {
       $id[] = $this->f("$field");
     }
     return $id;
   }

   /** Setup the orphans array (helper to get_orphaned_staff)
    * @method private setup_orphan
    * @param string stafftype stafftype (director,composer,actor)
    * @param integer id PK to stafftype's table
    * @param string name name of orphaned staff member
    * @param string firstname firstname of orphaned staff member
    * @return object one element for the orphan's array
    * @see sql::get_orphaned_staff
    */
   function setup_orphan($stafftype,$id,$name,$firstname) {
     $orphan->stafftype = $stafftype;
     $orphan->id        = $id;
     $orphan->name      = $name;
     $orphan->firstname = $firstname;
     return $orphan;
   }

   /** Search the database for orphaned staff members. I.e. people who have an
    *  entry in one of the staff tables, but the video table does not refer to them
    * @method get_orphaned_staff
    * @return array of orphanes
    * @version the array has the format array[$i]->$item, where $item is one of
    *  stafftype,id,name,firstname - id being the PK to the staff table
    */
   function get_orphaned_staff() {
     $id = $this->get_distinct_staffids("director_id");
     $query = "SELECT id,name,firstname FROM pvp_directors"
            . " WHERE id NOT IN (" . implode(",",$id) . ")";
     $this->dbquery($query);
     while ( $this->next_record() ) {
       $orphan[] = $this->setup_orphan("director_person",$this->f('id'),$this->f('name'),$this->f('firstname'));
     }
     $id = $this->get_distinct_staffids("music_id");
     $query = "SELECT id,name,firstname FROM pvp_music"
            . " WHERE id NOT IN (" . implode(",",$id) . ")";
     $this->dbquery($query);
     while ( $this->next_record() ) {
       $orphan[] = $this->setup_orphan("compose_person",$this->f('id'),$this->f('name'),$this->f('firstname'));
     }
     $id = $this->get_distinct_staffids("actor1_id");
     $id = array_merge($id, $this->get_distinct_staffids("actor2_id"));
     $id = array_merge($id, $this->get_distinct_staffids("actor3_id"));
     $id = array_merge($id, $this->get_distinct_staffids("actor4_id"));
     $id = array_merge($id, $this->get_distinct_staffids("actor5_id"));
     $query = "SELECT id,name,firstname FROM pvp_actors"
            . " WHERE id NOT IN (" . implode(",",$id) . ")";
     $this->dbquery($query);
     while ( $this->next_record() ) {
       $orphan[] = $this->setup_orphan("actor",$this->f('id'),$this->f('name'),$this->f('firstname'));
     }
     if (isset($orphan)) return $orphan;
     return array();
   }

   /** Delete an actor from DB
    * @method delete_actor
    * @param mixed id either integer (id) or string (comma separated list of ids)
    * @return boolean success
    */
   function delete_actor($id) {
     return $this->delete_row("pvp_actors",$id);
   }

   /** Delete an director from DB
    * @method delete_director
    * @param mixed id either integer (id) or string (comma separated list of ids)
    * @return boolean success
    */
   function delete_director($id) {
     return $this->delete_row("pvp_directors",$id);
   }

   /** Delete an composer from DB
    * @method delete_composer
    * @param mixed id either integer (id) or string (comma separated list of ids)
    * @return boolean success
    */
   function delete_composer($id) {
     return $this->delete_row("pvp_music",$id);
   }

   ############################################################################
   # categories
   ############################################################################
   /** Get a categorys data
    * @method get_category
    * @param optional integer id category id
    * @param optional string order subclause for ORDER BY
    * @param optional integer in_use check if used (1) or not (0), default: no check
    * @return mixed string(catname) or array of categories (id,name,internal name, enabled used)
    */
   function get_category($id="",$order="",$inUse=0) {
     if ($id) {
       $this->query("SELECT name FROM pvp_cat WHERE id=$id");
       if ( $this->next_record() ) {
         return lang(trim($this->f('name')));
       } else {
         return "";
       }
     } else {
       if ($order=="") {
         $this->query("SELECT id,name,enabled FROM pvp_cat");
       } else {
         $this->query("SELECT id,name,enabled FROM pvp_cat ORDER BY $order");
       }
       $i=0;
       while ( $this->next_record() ) {
         $cat[$i]['id']   = $this->f('id');
         $cat[$i]['name'] = lang($this->f('name'));
	 $cat[$i]['internal'] = $this->f('name');
	 $cat[$i]['enabled'] = $this->f('enabled');
	 ++$i;
       }
       if ($inUse) {
         $catcount = count($cat);
	 for ($i=0;$i<$catcount;++$i) {
	   $catID = $cat[$i]['id'];
	   $this->dbquery("SELECT COUNT(*) AS used FROM pvp_video WHERE cat1_id='$catID' OR cat2_id='$catID' OR cat3_id='$catID'");
	   $this->next_record();
	   $cat[$i]['used'] = $this->f('used');
	 }
       }
       if ($order=="") {
         $compare = create_function('$a,$b','return strcmp($a["name"],$b["name"]);');
         usort($cat,$compare); reset($cat);
       }
       return $cat;
     }
   }

   /** get category ID by categories internal name
    * @method get_category_id
    * @param string iname internal name of category
    * @return integer cat_id
    */
   function get_category_id($iname) {
     $sql = "SELECT id FROM pvp_cat WHERE name='$iname'";
     $this->dbquery($sql);
     if ( $this->next_record() ) {
       return $this->f('id');
     } else {
       return 0;
     }
   }

   /** update a category
    * @method update_category
    * @param integer id category's id
    * @param string name category's name
    * @param optional integer enabled active (1) or not (0)
    * @return boolean success
    */
   function update_category($id,$name,$enabled=9) {
     GLOBAL $pvp;
     $name = $pvp->common->safeinput($name);
     $query = "UPDATE pvp_cat SET name='$name' ";
     if ($enabled!=9) $query .= ",enabled=$enabled ";
     $query .= "WHERE id=$id";
     $this->dbquery($query);
     if ( $this->affected_rows() < 0 ) return FALSE;
     return TRUE;
   }

   /** add a category
    * @method add_category
    * @param string name
    * @return boolean success
    */
   function add_category($name) {
     GLOBAL $pvp;
     $name = $pvp->common->safeinput($name);
     $this->dbquery("INSERT INTO pvp_cat (name) VALUES ('$name')");
     return $this->affected_rows();
   }

   /** remove a category
    * @method delete_category
    * @param integer id category ID (PK of table)
    * @return boolean success
    */
   function delete_category($id) {
     $this->dbquery("DELETE FROM pvp_cat WHERE id=$id");
     return $this->affected_rows();
   }

   ############################################################################
   # technical data
   ############################################################################
   /** Get Video Norms
    * @method get_vnorms
    * @return array vnorms (id,name)
    */
   function get_vnorms() {
     $this->dbquery("SELECT id,name FROM pvp_vnorms");
     while ($this->next_record()) {
       $v["id"]   = $this->f('id');
       $v["name"] = $this->f('name');
       $vnorms[]  = $v;
     }
     return $vnorms;
   }

   /** Get audio/video data and return it as array
    * @method private get_av
    * @param integer id ID of required data set
    * @param string table table name
    * @return array av (name,sname if id!="", i:id,i:name,i:sname otherwise)
    */
   function get_av($id,$table) {
     if ($id=="") {
       $this->query("SELECT id,name,sname FROM $table");
       $i=0;
       while ( $this->next_record() ) {
         $av[$i]['id']    = $this->f('id');
	 $av[$i]['name']  = $this->f('name');
	 $av[$i]['sname'] = $this->f('sname');
	 ++$i;
       }
     } else {
       $this->query("SELECT name,sname FROM $table WHERE id=$id");
       if ( $this->next_record() ) {
         $av['name']  = $this->f('name');
         $av['sname'] = $this->f('sname');
       } else {
         $av['name'] = $av['sname'] = "";
       }
     }
     return $av;
   }

   /** update technical audio/video data
    * @method private set_av
    * @param string table
    * @param string name
    * @param string sname
    * @param optional integer id
    * @return boolean success
    * @version if no $id is given, a new entry will be created. If $id is
    *  given, but $name and $sname are empty, the entry will be deleted.
    *  In all other cases, the entry with the given $id will be updated.
    */
   function set_av($table,$name,$sname,$id="") {
     if (!$id) {
       return $this->dbquery("INSERT INTO $table (name,sname) VALUES ('$name','$sname')");
     } else {
       if (!$name && !$sname) {
         return $this->dbquery("DELETE FROM $table WHERE id=$id");
       } else {
         return $this->dbquery("UPDATE $table SET name='$name',sname='$sname' WHERE id=$id");
       }
     }
     return FALSE;
   }

   /** Get all pict data and return it as array (wrapper to get_av)
    * @method get_pict
    * @param optional integer id
    * @return array (name,sname if id!="", i:id,i:name,i:sname otherwise)
    */
   function get_pict($id="") {
     return $this->get_av($id,"pvp_pict");
   }

   /** update pict data (wrapper to set_av)
    * @method set_pict
    * @param string name
    * @param string sname
    * @param optional integer id
    * @see set_av()
    */
   function set_pict($name,$sname,$id="") {
     return $this->set_av("pvp_pict",$name,$sname,$id);
   }

   /** Get all color data and return it as array (wrapper to get_av)
    * @method get_color
    * @param optional integer id
    * @return array (name,sname if id!="", i:id,i:name,i:sname otherwise)
    */
   function get_color($id="") {
     return $this->get_av($id,"pvp_colors");
   }

   /** update color data (wrapper to set_av)
    * @method set_color
    * @param string name
    * @param string sname
    * @param optional integer id
    * @see set_av()
    */
   function set_color($name,$sname,$id="") {
     return $this->set_av("pvp_colors",$name,$sname,$id);
   }

   /** Get all tone data and return it as array (wrapper to get_av)
    * @method get_tone
    * @param optional integer id
    * @return array (name,sname if id!="", i:id,i:name,i:sname otherwise)
    */
   function get_tone($id="") {
     return $this->get_av($id,"pvp_tone");
   }

   /** update tone data (wrapper to set_av)
    * @method set_tone
    * @param string name
    * @param string sname
    * @param optional integer id
    * @see set_av()
    */
   function set_tone($name,$sname,$id="") {
     return $this->set_av("pvp_tone",$name,$sname,$id);
   }

   /** get data for commercials
    * @method get_commercials
    * @param optional integer id
    * @return mixed (name if id!="", array of i:id,i:name otherwise)
    */
   function get_commercials($id="") {
     if ($id=="") {
       $this->query("SELECT id,name FROM pvp_commercials");
       $i=0;
       while ( $this->next_record() ) {
         $commercials[$i]['name'] = lang($this->f('name'));
	 $commercials[$i]['id']   = $this->f('id');
         ++$i;
       }
     } else {
       $this->query("SELECT name FROM pvp_commercials WHERE id=$id");
       if ( $this->next_record() ) {
         $commercials = $this->f('name');
         $commercials = lang($commercials);
       } else {
         $commercials = lang("unknown");
       }
     }
     return $commercials;
   }

   /** check tech tables for movie references
    * @method check_movietechref
    * @param string table
    * @param integer id
    * @return boolean is_referenced
    */
   function check_movietechref($table,$id) {
     switch($table) {
       case "pict"  : $restrict = "WHERE pict_id=$id"; break;
       case "color" : $restrict = "WHERE color_id=$id"; break;
       case "tone"  : $restrict = "WHERE tone_id=$id"; break;
       case "mtype" : $restrict = "WHERE mtype_id=$id"; break;
       default      :
     }
     $this->dbquery("SELECT COUNT(id) AS ref FROM pvp_video $restrict");
     if ( $this->next_record() ) {
       $ref = $this->f('ref');
     } else {
       $ref = 0;
     }
     return $ref;
   }

   ############################################################################
   # movie data
   ############################################################################
   /** Drop (delete) all movie data
    *  this is used to clean the db before doing a movie restore
    * @method drop_all_movies
    * @return boolean success
    */
   function drop_all_movies() {
     if (!$this->query("TRUNCATE TABLE pvp_video")) return FALSE;
     if (!$this->query("TRUNCATE TABLE pvp_media")) return FALSE;
     if (!$this->query("TRUNCATE TABLE pvp_music")) return FALSE;
     if (!$this->query("TRUNCATE TABLE pvp_directors")) return FALSE;
     if (!$this->query("TRUNCATE TABLE pvp_actors")) return FALSE;
     return TRUE;
   }

   /** Get movie ids
    * @method get_movieid
    * @param integer mtype_id media type id
    * @param integer cass_id media number
    * @param optional integer part movie number on medium
    * @return mixed either id (integer) or array of IDs
    */
   function get_movieid($mtype_id,$cass_id,$part="") {
     GLOBAL $pvp;
     $query  = "SELECT v.id AS id FROM pvp_video v, pvp_media m"
             . " WHERE v.media_id=m.id AND v.mtype_id=m.mtype_id"
             . "   AND v.mtype_id=$mtype_id AND v.media_id=$cass_id";
     if (!$pvp->auth->admin) {
       $gusers = implode(",",$this->get_usergrants(array(),array(0,$pvp->auth->user_id),array("SELECT")));
       $query .= " AND (m.owner=".$pvp->auth->user_id
              .  "  OR v.private=0 AND m.owner IN ($gusers))";
     }
     if ($part=="") {
       $id = array();
       $query .= " ORDER BY v.part";
       $this->query($query);
       while( $this->next_record() ) {
         $id[] = $this->f('id');
       }
       return $id;
     } else {
       $this->query($query . " AND v.part=$part");
       $this->next_record();
       return $this->f('id');
     }
   }

   /** Retrieve a list of all movie ids
    *  Needed for the backup procedure
    * @method get_movieids_all
    * @param optional integer owner_id
    * @return array id_list
    */
   function get_movieids_all($owner_id="") {
     (int) $owner_id;
     if ($owner_id=="") {
       $query = "SELECT id FROM pvp_video";
     } else {
       $query = "SELECT v.id FROM pvp_video v,pvp_media m WHERE v.media_id=m.id AND v.mtype_id=m.mtype_id AND m.owner=$owner_id";
     }
     $this->dbquery($query);
     while ($this->next_record()) {
       $list[] = $this->f('id');
     }
     return $list;
   }

   /** Get all data for a movie entry and return it as array
    * @method get_movie
    * @param integer id movie id
    * @return array array with detailled movie information
    * @version array description:<pre>
    *  Media data: id, mtype_id, mtype, mtype_short, cass_id, part,
    *              previous, next (see get_preventry/get_nextentry)
    *              owner_id, storeplace, lentto
    *  Tech  data: color, color_short, color_id, tone, tone_short, tone_id,
    *              pict, pict_short, pict_id, commercials, commercials_id,
    *              lp, label, vnorm_id, vnorm
    *  Movie data: title, length, country, year, counter1, counter2, aq_date
    *              source, fsk, comment, catX / catX_id (1..3), comment
    *  IMDB data:  imdb_id, rating, actorX_mid, director_mid, music_mid
    *  Staff data: director_list, music_list, actorX_list (where X is 1..5);
    *              director_id, music_id, actorX_id (where X is 1..5);
    *              director, music and actorX as fullname (see format_name);
    *              director_,music_ and actorX_ as array (see format_name);
    *              with _rev as reverse name (name, firstname);
    *              actors, actors12, actors35 as list of actorX</pre>
    */
   function get_movie($id="") {
     if ($id||$id===0) $where = " WHERE pvp_video.id=$id";
     $query = "SELECT pvp_video.id as vid,title,length,country,year,counter1,counter2,aq_date,source,"
            . "director_id,director_list,music_id,cat1_id,cat2_id,cat3_id,"
	    . "actor1_id,actor2_id,actor3_id,actor4_id,actor5_id,actor1_list,"
	    . "actor2_list,actor3_list,actor4_list,actor5_list,music_list,label,"
	    . "tone_id,color_id,pict_id,commercials_id,lp,fsk,audio,subtitle,"
            . "comment,pvp_video.mtype_id as mtype_id,"
	    . "d.name as dname,d.firstname as dfname,d.imdb_id as dmid,"
	    . "m.name as mname,m.firstname as mfname,m.imdb_id as mmid,"
	    . "a1.name as a1name,a1.firstname as a1fname,a1.imdb_id as a1mid,"
	    . "a2.name as a2name,a2.firstname as a2fname,a2.imdb_id as a2mid,"
	    . "a3.name as a3name,a3.firstname as a3fname,a3.imdb_id as a3mid,"
	    . "a4.name as a4name,a4.firstname as a4fname,a4.imdb_id as a4mid,"
	    . "a5.name as a5name,a5.firstname as a5fname,a5.imdb_id as a5mid,"
	    . "mt.name as mtname,mt.sname as mtsname,"
	    . "c.name as cname,c.sname as csname,"
	    . "t.name as tname,t.sname as tsname,"
	    . "cat1.name as cat1name,cat2.name as cat2name,cat3.name as cat3name,"
	    . "media_id,part,pm.owner as owner_id,pm.storeplace as storeplace, "
            . "pm.lentto AS lentto,vnorm_id,vn.name AS vnorm,private,pvp_video.imdb_id, "
            . "rating,lastchange "
	    . "FROM pvp_video "
	    . "LEFT JOIN pvp_directors d ON director_id=d.id "
	    . "LEFT JOIN pvp_music m ON music_id=m.id "
	    . "LEFT JOIN pvp_mtypes mt ON pvp_video.mtype_id=mt.id "
	    . "LEFT JOIN pvp_colors c ON color_id=c.id "
	    . "LEFT JOIN pvp_tone t ON tone_id=t.id "
	    . "LEFT JOIN pvp_cat cat1 ON cat1_id=cat1.id "
	    . "LEFT JOIN pvp_cat cat2 ON cat2_id=cat2.id "
	    . "LEFT JOIN pvp_cat cat3 ON cat3_id=cat3.id "
	    . "LEFT JOIN pvp_actors a1 ON actor1_id=a1.id "
	    . "LEFT JOIN pvp_actors a2 ON actor2_id=a2.id "
	    . "LEFT JOIN pvp_actors a3 ON actor3_id=a3.id "
	    . "LEFT JOIN pvp_actors a4 ON actor4_id=a4.id "
	    . "LEFT JOIN pvp_actors a5 ON actor5_id=a5.id "
            . "LEFT JOIN pvp_media pm ON (pvp_video.mtype_id=pm.mtype_id AND pvp_video.media_id=pm.id) "
            . "LEFT JOIN pvp_vnorms vn ON vnorm_id=vn.id"
            . $where;
     $this->query($query);
     $rc = $this->num_rows(); # somehow the while loop does not work here???
     for ( $rcc=0;$rcc<$rc;++$rcc ) {
       $this->next_record();
       $moviedetails = array("owner_id","title","label","length","country","year",
                     "counter1","counter2","aq_date","source","director_list",
		     "actor1_list","actor2_list","actor3_list","actor4_list",
		     "actor5_list","music_list","fsk","comment","part",
		     "mtype_id","tone_id","color_id","storeplace","lentto",
                     "vnorm_id","vnorm","private","imdb_id","rating","lastchange");
       foreach($moviedetails as $value) {
         $movie[$value] = $this->f("$value");
       }
       $movie['id']      = $this->f('vid');
       $movie['cass_id'] = $this->f('media_id');
       $movie['title']   = stripslashes($movie['title']);
       $movie['source']  = stripslashes($movie['source']);
       $taudio = $this->f("audio");
       $tsubt = $this->f("subtitle");
       $movie['audio']   = explode(",",substr($taudio,1,strlen($taudio)-2));
       $movie['subtitle']= explode(",",substr($tsubt,1,strlen($tsubt)-2));
       $movie['comment'] = stripslashes($movie['comment']);
       if (!$movie['length']) $movie['length'] = 0;
       $name = $this->format_name( array("name"=>$this->f('dname'),"firstname"=>$this->f('dfname')) );
       $movie['director'] = $name['fullname']; $movie['director_rev'] = $name['reverse'];
       $movie['director_'] = $name;
       $movie['director_mid'] = $this->f('dmid');
       $name = $this->format_name( array("name"=>$this->f('mname'),"firstname"=>$this->f('mfname')) );
       $movie['music'] = $name['fullname']; $movie['music_rev'] = $name['reverse'];
       $movie['music_'] = $name;
       $movie['music_mid'] = $this->f('mmid');
       for ($i=1;$i<6;$i++) { // actor 1..5: ['actor1'],[actor1_rev],[actor_1]...
         $dbname = "a$i" . "name"; $dbfname = "a$i" . "fname"; $dbmid = "a${i}mid";
         $tname  = stripslashes($this->f("$dbname"));
         $tfname = stripslashes($this->f("$dbfname"));
         $vname  = "actor$i"; $vrev = "actor$i" . "_rev"; $aname = "actor_$i";
         $name = $this->format_name( array("name"=>$tname,"firstname"=>$tfname) );
         $movie[$vname] = $name['fullname']; $movie[$vrev] = $name['reverse'];
         $movie[$aname] = $name;
	 $movie["${vname}_mid"] = $this->f($dbmid);
       }
       $movie['mtype'] = $this->f('mtname'); $movie['mtype_short'] = $this->f('mtsname');
       $movie['color'] = lang($this->f('cname')); $movie['color_short'] = $this->f('csname');
       $movie['tone'] = $this->f('tname'); $movie['tone_short'] = $this->f('tsname');
       $movie['cat1int'] = $this->f('cat1name'); $movie['cat2int'] = $this->f('cat2name'); $movie['cat3int'] = $this->f('cat3name');
       $movie['cat1'] = lang($movie['cat1int']); $movie['cat2'] = lang($movie['cat2int']); $movie['cat3'] = lang($movie['cat3int']);

       $moviedetails = array("actor1_id","actor2_id","actor3_id","actor4_id",
                     "actor5_id","director_id","music_id","cat1_id","cat2_id",
		     "cat3_id","pict_id","commercials_id","lp","mtype_id");
       foreach($moviedetails as $value) {
         $$value = $this->f("$value");
         $movie[$value] = $$value;
       }
       $movie['actors12'] = $movie['actor1'];
       if ( strlen($movie['actor2']) ) {
         if ( strlen($movie['actors12']) ) $movie['actors12'] .= ", ";
         $movie['actors12'] .= $movie['actor2'];
       }
       $movie['actors35'] = $movie['actor3'];
       for ($i=4;$i<6;$i++) {
         $actor = "actor$i";
         if ( strlen($movie[$actor]) ) {
           if ( strlen($movie['actors35']) ) $movie['actors35'] .= ", ";
	   $movie['actors35'] .= $movie[$actor];
         }
       }
       $movie['actors'] = $movie['actors12'];
       if ( strlen($movie['actors35']) ) {
         if ( strlen($movie['actors']) ) $movie['actors'] .= ", ";
         $movie['actors'] .= $movie['actors35'];
       }
       if ($pict_id) {
         $pict = $this->get_pict($pict_id);
         $movie['pict'] = $pict['name']; $movie['pict_short'] = $pict['sname'];
       } else {
         $movie['pict'] = $movie['pict_short'] = lang("unknown");
       }
       if ($commercials_id) {
         $movie['commercials'] = $this->get_commercials($commercials_id);
       } else {
         $movie['commercials'] = lang("unknown");
       }
       if ($lp) { $movie['lp'] = lang("longplay"); } else { $movie['lp'] = ""; }
       $movie['previous'] = $this->get_preventry($movie['mtype_id'],$movie['cass_id'],$movie['part']);
       $movie['next']     = $this->get_nextentry($movie['mtype_id'],$movie['cass_id'],$movie['part']);
       $movie['disktype'] = $this->get_disktype_id($movie['mtype_id'],$movie['cass_id']);
       $movie['rc']       = $this->get_rc($movie['mtype_id'],$movie['cass_id']);
       if ($id!=="") return $movie;
       $list[] = $movie;
     }
     return $list;
   }

   /** Get movie list as array of movies (see get_movie)
    * @method get_movielist
    * @param optional string order column to order the list by
    *  (title, lenght, year, date or cat)
    * @param optional string restrict definition of WHERE clause (without WHERE)
    * @param optional integer start (for use with LIMIT)
    * @param optional string dir sort direction (DESC or ASC; default: DESC)
    * @return array array of movies
    * @see sql::get_movie()
    */
   function get_movielist($order="",$restrict="",$start="",$dir="DESC") {
     GLOBAL $pvp;
     $filter = get_filters();
     $where  = "";
     ($dir=="DESC") ? $revdir = "ASC" : $revdir = "DESC";
     switch ($order) {
       case "title"  : $orderby = "v.title $revdir,v.mtype_id $dir,v.media_id"; break;
       case "fsk"    : $orderby = "v.fsk $revdir,v.mtype_id $dir,v.media_id"; break;
       case "length" : $orderby = "v.length $revdir,v.mtype_id $dir,v.media_id"; break;
       case "year"   : $orderby = "v.year $revdir,v.mtype_id $dir,v.media_id"; break;
       case "date"   : $orderby = "v.aq_date $revdir,v.mtype_id $dir,v.media_id"; break;
       case "cat"    : $orderby = "v.cat1_id $revdir,v.mtype_id $dir,v.media_id"; break;
       case "cat1_id,title" : $orderby = "v.cat1_id $revdir,v.title $revdir,v.mtype_id $dir,v.media_id"; break;
       case "rating" : $orderby = "v.rating $dir"; break;
       case "lastchange" : $orderby = "v.lastchange $dir"; break;
       default       : $orderby = "v.mtype_id DESC,v.media_id,v.part"; break;
     }
     if ($restrict) $where = " WHERE $restrict";
     $query = "SELECT v.id AS id FROM pvp_video v";
     if (strlen($filter)) {
       if (!empty($where)) {
         $where .= " AND $filter";
       } else {
         $where = " WHERE $filter";
       }
     }
     $showusers = $pvp->preferences->get_owner_filter();
     if ($pvp->auth->admin) { // which collections we may access?
       if (!empty($showusers)) {
         $query .= ", pvp_media m";
         if (empty($where)) $where = " WHERE"; else $where .= " AND";
         $where .= " m.owner IN ($showusers) AND v.media_id=m.id AND v.mtype_id=m.mtype_id";
       }
     } else {
       $grants = $this->get_usergrants(array(),array($pvp->auth->user_id,0),array("SELECT"));
       $owners = implode(",",$grants);
       $query .= ", pvp_media m";
       if (empty($where)) $where = " WHERE"; else $where .= " AND";
       $where .= " v.media_id=m.id AND v.mtype_id=m.mtype_id"
              .  " AND (m.owner=".$pvp->auth->user_id
              .  "  OR m.owner IN ($owners) AND v.private=0)";
       if (strlen($showusers)>0) {
         $where .= " AND m.owner IN ($showusers)";
       }
     }
     $query .= $where;
     $query .= " ORDER BY $orderby";
     if ($start==="") { $this->dbquery($query); }
       else { $totals = $this->lim_query($query,$start,"x"); }
     while ( $this->next_record() ) {
       $list[] = $this->f('id');
     }
     if (isset($list)) $len = count($list); else $len = 0;
     for ($i=0;$i<$len;$i++) {
       $movielist[] = $this->get_movie($list[$i]);
     }
     if (isset($totals) && $totals) $movielist['totals'] = $totals;
     if (!isset($movielist)) $movielist = array();
     return $movielist;
   }

   /** Search for movies and return as array of movies (see get_movie)
    * @method searchmovies
    * @param optional string order column to order the list by
    *  (title, lenght, year, date or cat)
    * @param optional integer start (for use with LIMIT)
    * @return array array of movies
    * @see sql::get_movie()
    * @version Since this is called via the nextmatch class, I found no way
    *  yet to pass it an array, so we have to set it global.
    *  * use searchmovievals
    */
   function searchmovies($order="",$start="") {
     GLOBAL $searchmovievals;
     $restrict = "";
     foreach ($searchmovievals as $key=>$val) {
       ${$key} = $val;
     }
     #---[ MediaTypes ]--
     $ccount = count($mtype_id);
     for ($i=0;$i<$ccount;++$i) {
       if (!$mtype_id[$i]) break;
       if ($i==0) { $restrict .= "("; } else { $restrict .= " OR "; }
       $restrict .= "v.mtype_id=".$mtype_id[$i]." ";
       if ($i+1==$ccount) $restrict .= ") ";
     }
     #---[ Categories ]--
     $ccount = count($cat_id);
     for ($i=0;$i<$ccount;++$i) {
       if (!$cat_id[$i]) break;
       $cat = $cat_id[$i];
       if ($i==0) { if ($restrict) $restrict .= "AND "; $restrict .= " ("; }
       $restrict .= "v.cat1_id=$cat OR v.cat2_id=$cat OR v.cat3_id=$cat ";
       if ($i+1<$ccount) { $restrict .= " OR "; } else { $restrict .= ") "; }
     }
     #---[ Audio_Lang ]--
     $ccount = count($audio_id);
     for($i=0;$i<$ccount;++$i) {
       if (!$audio_id[$i]) break;
       if ($i==0) { if ($restrict) $restrict .= "AND "; $restrict .= " ("; } else { $restrict .= " OR "; }
       $restrict .= "v.audio like '%,".$audio_id[$i].",%'";
       if ($i+1==$ccount) $restrict .= ") ";
     }
     #---[ Subtitles ]--
     $ccount = count($subtitle_id);
     for($i=0;$i<$ccount;++$i) {
       if (!$subtitle_id[$i]) break;
       if ($i==0) { if ($restrict) $restrict .= "AND "; $restrict .= " ("; } else { $restrict .= " OR "; }
       $restrict .= "v.subtitle like '%,".$subtitle_id[$i].",%'";
       if ($i+1==$ccount) $restrict .= ") ";
     }

     if ($restrict) $restrict .= "AND ";
     if (!empty($title)) $restrict .= "lower(v.title) LIKE '%".strtolower($title)."%' AND ";

     #---[ Staff ]--
     if ($pname) {
       switch ($ptype) {
         case director :
           $this->query("SELECT id FROM pvp_directors WHERE lower(firstname) LIKE '%".strtolower($pname)."%' OR lower(name) LIKE '%".strtolower($pname)."%'");
           while ( $this->next_record() ) {
             $pids .= ",".$this->f('id');
           }
           $pids = substr($pids,1);
           if (!empty($pids)) $restrict .= "director_id IN ($pids)";
	   break;
         default       : 
           $this->query("SELECT id FROM pvp_actors WHERE lower(firstname) LIKE '%".strtolower($pname)."%' OR lower(name) LIKE '%".strtolower($pname)."%'");
           while ( $this->next_record() ) {
             $pids .= ",".$this->f('id');
           }
           $pids = substr($pids,1);
           if (!empty($pids)) {
             for ($i=1;$i<6;++$i) {
               if ($i==1) $restrict .= "(";
               $restrict .= "v.actor$i"."_id IN ($pids)";
               if ($i<5) $restrict .= " OR ";
	     }
             $restrict .= ")";
           }
       }
       if (!empty($pids)) $restrict .= " AND ";
     }

     if (!empty($comment)) $restrict .= "v.comment LIKE '%$comment%'";
       else $restrict .= "1=1";
     if ($minlen) $restrict .= " AND length>=$minlen";
     if ($maxlen) $restrict .= " AND length<=$maxlen";
     if ($minfsk) $restrict .= " AND fsk>=$minfsk";
     if ($maxfsk) $restrict .= " AND fsk<=$maxfsk";
     if ($minrat) $restrict .= " AND rating>=$minrat";
     if ($maxrat) $restrict .= " AND rating<=$maxrat";
     if ($minchange) $restrict .= " AND lastchange>='$minchange'";
     if ($maxchange) $restrict .= " AND lastchange<='$maxchange'";
     return $this->get_movielist($order,$restrict,$start);
   }

   /** Get movie list for cat1 as array of movies (see get_movie)
    *  (wrapper to get_movielist)
    * @method get_moviecatlist
    * @param integer cat_id ID of category to get movies for
    * @return array array of movies
    * @see sql::get_movielist(), sql::get_movie()
    */
   function get_moviecatlist($cat) {
     return $this->get_movielist("cat1_id,title","cat1_id=$cat");
   }

   /** Get movie list for cat1..cat3 as array of movies (see get_movie)
    *  (wrapper to get_movielist)
    * @method get_moviecatlist3
    * @param integer cat_id ID of category to get movies for
    * @return array array of movies
    * @see sql::get_movielist(), sql::get_movie()
    */
   function get_moviecatlist3($cat) {
     return $this->get_movielist("$cat1_id,title","cat1_id=$cat OR cat2_id=$cat OR cat3_id=$cat");
   }

   /** Get movie list by staff member as array of movies (see get_movie)
    * @method get_movienamelist
    * @param string table table name for staff member
    * @param array name name as formatted by sql::format_name()
    * @param optional string filter filter restriction
    * @param optional boolean forceall override grants (default FALSE) needed for deletion process
    * @return array list of movies
    * @see sql::get_movie(), sql::get_movielist()
    */
   function get_movienamelist($table,$name,$filter="",$forceall=FALSE) {
     GLOBAL $pvp;
     switch ($table) {
       case "directors" : $restrict = "v.director_id=".$name['id']." AND v.director_list=1";
			  $revname = "director_rev"; $fullname = "director";
			  $firstname = "director_first"; $lastname = "director_last";
			  break;
       case "music"     : $restrict = "v.music_id=".$name['id']." AND v.music_list=1";
			  $revname = "music_rev"; $fullname = "music";
			  $firstname = "music_first"; $lastname = "music_last";
			  break;
       case "actors"    : $restrict = "((v.actor1_id=".$name['id']." AND v.actor1_list=1)"
                                    . " OR  (v.actor2_id=".$name['id']." AND v.actor2_list=1)"
                                    . " OR  (v.actor3_id=".$name['id']." AND v.actor3_list=1)"
                                    . " OR  (v.actor4_id=".$name['id']." AND v.actor4_list=1)"
                                    . " OR  (v.actor5_id=".$name['id']." AND v.actor5_list=1))";
			  $revname = "actor_rev"; $fullname = "actor";
			  $firstname = "actor_first"; $lastname = "actor_last";
			  break;
       default:
     }
     if (strlen($filter)) $restrict .= " AND ($filter)";
     $query = "SELECT v.title,v.length,v.media_id,v.part,v.lp,v.year,v.aq_date,"
	    . "v.mtype_id,mt.name as mtname,mt.sname as mtsname,"
	    . "cat1.name as cat1name, m.owner as owner_id, u.login as owner "
	    . "FROM pvp_video v, pvp_mtypes mt, pvp_cat cat1, pvp_media m, pvp_users u "
	    . "WHERE v.cat1_id=cat1.id AND v.mtype_id=mt.id "
            . "AND v.media_id=m.id AND v.mtype_id=m.mtype_id "
            . "AND m.owner=u.id "
	    . "AND $restrict";
     if (!$pvp->auth->admin && !$forceall) {
       $gusers = implode(",",$this->get_usergrants(array(),array(0,$pvp->auth->user_id),array("SELECT")));
       $query .= " AND (m.owner=".$pvp->auth->user_id
              .  "  OR (m.owner in ($gusers) AND v.private=0))";
     }
     $this->query($query);
     while ( $this->next_record() ) {
       $movie[$revname]   = $name['reverse'];
       $movie[$fullname]  = $name['fullname'];
       $movie[$lastname]  = $name['name'];
       $movie[$firstname] = $name['firstname'];
       $movie['mtype'] = $this->f('mtname'); $movie['mtype_short'] = $this->f('mtsname');
       $movie['cat1'] = lang($this->f('cat1name'));
       $movie['cass_id'] = $this->f('media_id');
       $moviedetails = array("title","length","part","lp","year","aq_date","mtype_id","owner");
       foreach($moviedetails as $value) {
         $movie[$value] = $this->f("$value");
       }
       $list[] = $movie;
     }
     if (isset($list)) return $list;
     return array();
   }

   /** Change category id for movie(s)
    * @method change_moviecat
    * @param integer fromID
    * @param integer toID
    * @param optional array movie_id
    * @return boolean success
    */
   function change_moviecat($from,$to,$id=array()) {
     if (!preg_match('|^\d+$|',$from) || !preg_match('|^\d+$|',$to)) return FALSE;
     if (is_array($id) && !empty($id)) {
       $restrict = " AND id IN ('".implode(",",$id)."')";
     }
     if (!$this->dbquery("UPDATE pvp_video SET cat1_id=$to WHERE cat1_id=$from $restrict")) return FALSE;
     if (!$this->dbquery("UPDATE pvp_video SET cat2_id=$to WHERE cat2_id=$from $restrict")) return FALSE;
     if (!$this->dbquery("UPDATE pvp_video SET cat3_id=$to WHERE cat3_id=$from $restrict")) return FALSE;
     return TRUE;
   }

   /** Get first movie numbers for each media type
    * @method get_firstmovienum
    * @param optional integer mtype_id
    * @param optional integer cass_id
    * @return mixed lastnum
    *  array lastnum if called w/o params (i:mtype, i:mtype_id, i:cass_id,
    *  i:part, i:entry; where i:entry = "mtype cass_id-part")
    *  integer part if called w/ both params
    */
   function get_firstmovienum($mtype_id="",$cass_id="") {
     GLOBAL $pvp;
     $gusers = implode(",",$this->get_usergrants(array(),array(0,$pvp->auth->user_id),array("SELECT")));
     if (is_numeric($mtype_id) && is_numeric($cass_id)) { // search on same medium
       $this->dbquery("SELECT MIN(part) AS min_part FROM pvp_video WHERE mtype_id=$mtype_id AND media_id=$cass_id");
       if ( $this->next_record() ) {
         return $this->f('min_part');
       } else {
         return 0;
       }
     }
     $mtypes = $this->get_mtypes();
     for ($i=0;$i<count($mtypes);$i++) { // search first medium
       $query = "SELECT MIN(v.media_id) AS min_id FROM pvp_video v,pvp_media m"
              . " WHERE v.media_id=m.id AND v.mtype_id=m.mtype_id"
              . "   AND v.mtype_id=".$mtypes[$i]['id'];
       if (!$pvp->auth->admin)
         $query .= "   AND (m.owner=".$pvp->auth->user_id." OR (m.owner IN ($gusers) AND v.private=0))";
       $this->dbquery($query);
       $this->next_record();
       $firstnum[$i]['mtype']   = $mtypes[$i]['sname'];
       $firstnum[$i]['mtype_id']= $mtypes[$i]['id'];
       $firstnum[$i]['cass_id'] = $this->f('min_id');
       while ( strlen($firstnum[$i]['cass_id'])<4 ) { $firstnum[$i]['cass_id'] = "0" . $firstnum[$i]['cass_id']; }
     }
     for ($i=0;$i<count($firstnum);$i++) { // search on preselected media
       $this->dbquery("SELECT MIN(part) as min_part FROM pvp_video WHERE media_id=" . $firstnum[$i]['cass_id'] . " AND mtype_id=" . $firstnum[$i]['mtype_id']);
       $this->next_record();
       $firstnum[$i]['part']    = $this->f('min_part');
       while ( strlen($firstnum[$i]['part'])<2 ) { $firstnum[$i]['part'] = "0" . $firstnum[$i]['part']; }
       $firstnum[$i]['entry'] = $firstnum[$i]['mtype'] . " " . $firstnum[$i]['cass_id'] . "-" . $firstnum[$i]['part'];
     }
     return $firstnum;
   }

   /** Get last movie numbers for each media type
    * @method get_lastmovienum
    * @param optional integer mtype_id
    * @param optional integer cass_id
    * @param optional boolean restrict_access honour ownership?
    * @return mixed lastnum
    *  array lastnum if called w/o params (i:mtype, i:mtype_id, i:cass_id,
    *  i:part, i:entry; where i:entry = "mtype cass_id-part")
    *  integer part if called w/ both params (only 1 entry when called w/ 1st)
    */
   function get_lastmovienum($mtype_id="",$cass_id="",$restrict_access=FALSE) {
     GLOBAL $pvp;
     $gusers = implode(",",$this->get_usergrants(array(),array(0,$pvp->auth->user_id),array("SELECT")));
     if (is_numeric($mtype_id) ) {
       if ( is_numeric($cass_id)) {
         $this->dbquery("SELECT MAX(part) AS max_part FROM pvp_video WHERE mtype_id=$mtype_id AND media_id=$cass_id");
         if ( $this->next_record() ) return $this->f('max_part');
           else return 0;
       } else {
         $mtypes = $this->get_mtypes();
         for ($i=0;$i<count($mtypes);++$i) {
           if ($mtypes[$i]['id']==$mtype_id) {
             $mt[0] = $mtypes[$i];
             $mtypes = $mt;
             unset($mt);
           }
         }
       }
     } else {
       $mtypes = $this->get_mtypes();
     }
     for ($i=0;$i<count($mtypes);++$i) { // search on all media
       $query = "SELECT MAX(v.media_id) AS max_id FROM pvp_video v,pvp_media m"
              . " WHERE v.media_id=m.id AND v.mtype_id=m.mtype_id"
              . "   AND v.mtype_id=".$mtypes[$i]['id'];
       if ($restrict_access && !$pvp->auth->admin)
         $query .= "   AND (m.owner=".$pvp->auth->user_id." OR (m.owner IN ($gusers) AND v.private=0))";
       $this->dbquery($query);
       $this->next_record();
       $lastnum[$i]['mtype']   = $mtypes[$i]['sname'];
       $lastnum[$i]['mtype_id']= $mtypes[$i]['id'];
       $lastnum[$i]['cass_id'] = $this->f('max_id');
       while ( strlen($lastnum[$i]['cass_id'])<4 ) { $lastnum[$i]['cass_id'] = "0" . $lastnum[$i]['cass_id']; }
     }
     for ($i=0;$i<count($lastnum);$i++) { // search on preselected media
       $this->dbquery("SELECT MAX(part) as max_part FROM pvp_video WHERE media_id=" . $lastnum[$i]['cass_id'] . " AND mtype_id=" . $lastnum[$i]['mtype_id']);
       $this->next_record();
       $lastnum[$i]['part']    = $this->f('max_part');
       while ( strlen($lastnum[$i]['part'])<2 ) { $lastnum[$i]['part'] = "0" . $lastnum[$i]['part']; }
       $lastnum[$i]['entry'] = $lastnum[$i]['mtype'] . " " . $lastnum[$i]['cass_id'] . "-" . $lastnum[$i]['part'];
     }
     return $lastnum;
   }

   /** Get the next entry
    * @method get_nextentry
    * @param integer mtype_id media type id of current entry
    * @param integer media_nr number of current medium
    * @param integer part part number of current entry
    * @return object next entry: mtype_id, media_rn, part
    */
   function get_nextentry($mtype_id,$media_nr,$part) {
     GLOBAL $pvp;
     $gusers = implode(",",$this->get_usergrants(array(),array(0,$pvp->auth->user_id),array("SELECT")));
     if (!(is_numeric($mtype_id) && is_numeric($media_nr) && is_numeric($part))) return FALSE;
     $next->mtype_id = $mtype_id;
     $next->media_nr = $media_nr;
     $this->query("SELECT MIN(part) AS part FROM pvp_video WHERE mtype_id=$mtype_id AND media_id=$media_nr AND part>$part");
     if ($this->next_record()) { // check on the same medium
       $next->part = $this->f('part');
       if($next->part) return $next;
     }
     $query = "SELECT MIN(v.media_id) AS medianr FROM pvp_video v,pvp_media m"
            . " WHERE v.media_id=m.id AND v.mtype_id=m.mtype_id"
            . "   AND v.mtype_id=$mtype_id AND v.media_id>$media_nr";
     if (!$pvp->auth->admin)
       $query .= "   AND (m.owner=".$pvp->auth->user_id." OR (m.owner IN ($gusers) AND v.private=0))";
     $this->query($query); // check for next valid medium
     if ($this->next_record()) {
       $next->media_nr = $this->f('medianr');
       if ($next->media_nr) { # Work around MySQL bug returning "Null" sometimes
         $this->query("SELECT MIN(part) AS part FROM pvp_video WHERE mtype_id=$mtype_id AND media_id=".$next->media_nr);
         $this->next_record();
         $next->part = $this->f('part');
         return $next;
       }
     }
     $mts   = $this->get_mtypes();
     $maxid = 0;
     for ($i=0;$i<count($mts);++$i) {
       $mtid = $mts[$i]['id'];
       $mt[$mtid] = 1;
       if ($mtid>$maxid) $maxid = $mtid;
     }
     do {
       ++$next->mtype_id;
     } while ( (!isset($mt[$next->mtype_id])) && ($next->mtype_id<$maxid) );
     $query = "SELECT MIN(v.media_id) AS medianr FROM pvp_video v,pvp_media m"
            . " WHERE v.media_id=m.id AND v.mtype_id=m.mtype_id"
            . "   AND v.mtype_id=".$next->mtype_id;
     if (!$pvp->auth->admin)
       $query .= "   AND (m.owner=".$pvp->auth->user_id." OR (m.owner IN ($gusers) AND v.private=0))";
     $this->query($query); // switch to next media type
     if ($this->next_record()) {
       $next->media_nr = $this->f('medianr');
       if ($next->media_nr) {
         $this->query("SELECT MIN(part) AS part FROM pvp_video WHERE mtype_id=".$next->mtype_id." AND media_id=".$next->media_nr);
         $this->next_record();
         $next->part = $this->f('part');
         return $next;
       }
     }
     return FALSE;
   }

   /** Get the previous entry
    * @method get_preventry
    * @param integer mtype_id media type id of current entry
    * @param integer media_nr number of current medium
    * @param integer part part number of current entry
    * @return object next entry: mtype_id, media_rn, part
    */
   function get_preventry($mtype_id,$media_nr,$part) {
     GLOBAL $pvp;
     $gusers = implode(",",$this->get_usergrants(array(),array(0,$pvp->auth->user_id),array("SELECT")));
     if (!(is_numeric($mtype_id) && is_numeric($media_nr) && is_numeric($part))) return FALSE;
     $prev->mtype_id = $mtype_id;
     $prev->media_nr = $media_nr;
     if ($part>1) { // check on the same medium
       $this->query("SELECT MAX(part) AS part FROM pvp_video WHERE mtype_id=$mtype_id AND media_id=$media_nr AND part<$part");
       if ($this->next_record()) {
         $prev->part = $this->f('part');
         if ($prev->part) return $prev; // MySQL sometimes returns empty rows
       }
     }
     if ($media_nr>1) { // check for previous medium
       $query = "SELECT MAX(v.media_id) AS medianr FROM pvp_video v,pvp_media m"
              . " WHERE v.media_id=m.id AND v.mtype_id=m.mtype_id"
              . "   AND v.mtype_id=$mtype_id AND v.media_id<$media_nr";
       if (!$pvp->auth->admin)
         $query .= "   AND (m.owner=".$pvp->auth->user_id." OR (m.owner IN ($gusers) AND v.private=0))";
       $this->query($query);
       if ($this->next_record()) {
         $prev->media_nr = $this->f('medianr');
         if (!is_numeric($prev->media_nr)) return FALSE;
         $this->query("SELECT MAX(part) AS part FROM pvp_video WHERE mtype_id=$mtype_id AND media_id=".$prev->media_nr);
         $this->next_record();
         $prev->part = $this->f('part');
         return $prev;
       }
     }
     $mts   = $this->get_mtypes();
     for ($i=0;$i<count($mts);++$i) {
       $mtid = $mts[$i]['id'];
       $mt[$mtid] = 1;
       if (!isset($minid)) $minid = $mtid;
         elseif ($mtid<$minid) $minid = $mtid;
     }
     do {
       --$prev->mtype_id;
     } while ( (!isset($mt[$prev->mtype_id])) && ($prev->mtype_id>$minid) );
     $last = $this->get_lastmovienum("","",TRUE);
     for ($i=0;$i<count($last);++$i) {
       if ($last[$i]['mtype_id']==$prev->mtype_id) {
         $prev->part = $last[$i]['part'];
	 $prev->media_nr = $last[$i]['cass_id'];
	 return $prev;
       }
     }
     return FALSE;
   }

   /** Add a movie to DB
    * @method add_movie
    * @param array movie movie array (for desc see get_movie)
    * @return boolean success
    */
   function add_movie($movie) {
     GLOBAL $pvp;
     foreach ($movie as $key => $value) {
       if ($key=="comment") {
         $comment = $pvp->common->safetextarea($value);
       } elseif ( is_string($value) ) {
         ${$key} = $pvp->common->safeinput($value);
       } else {
         ${$key} = $value;
       }
     }
     if ( $this->get_movieid($mtype_id,$cass_id,$part) ) {
       header('Content-type: text/html; charset=utf-8');
       echo "<HTML><HEAD>\n <meta http-equiv='Content-Type' content='text/html; charset=utf-8'>\n"
          . " <meta http-equiv='cache-control' content='no-cache'>\n <TITLE>Error</TITLE>\n"
          . "</HEAD><BODY>\n";
       display_error( lang("dupe_id_entered") );
       echo "</BODY></HTML>";
       exit;
     }
     if ( ( bool ) !ini_get('magic_quotes_gpc')
      || basename($_SERVER['PHP_SELF'])=="change_nr.php"
      || basename($_SERVER['PHP_SELF'])=="backup_db.php"
      || basename ($_SERVER['PHP_SELF'])=="backup.php" ) {
       $title  = addslashes($title);
       $comment= addslashes($comment);
       $source = addslashes($source);
     }
     $details = array("label","cat1_id","cat2_id","cat3_id","director_list",
                      "music_list","actor1_list","actor2_list","actor3_list",
                      "actor4_list","actor5_list","pict_id","commercials_id",
                      "lp","private","vnorm_id");
     foreach($details as $value) {
       if (${$value} == "") ${$value} = 0;
     }
     $details = array("length","director_id","music_id","year","actor1_id",
                      "actor2_id","actor3_id","actor4_id","actor5_id","tone_id",
                      "color_id","fsk");
     foreach($details as $value) {
       if (${$value} == "") ${$value} = "NULL";
     }
     if ($lp) { $lp = 1; } else { $lp = 0; }
     $audio_ts = ",".@implode(",",$movie['audio']).",";
     if (!empty($movie['subtitle'])) $subtitle = ",".@implode(",",$movie['subtitle']).",";
     if (empty($rating) && $rating !== 0) $rating = "NULL";
     $insert = "INSERT INTO pvp_video (mtype_id,media_id,part,title,label,length,aq_date,"
             . "source,director_id,director_list,music_id,music_list,country,"
	     . "year,cat1_id,cat2_id,cat3_id,actor1_id,actor2_id,actor3_id,"
	     . "actor4_id,actor5_id,actor1_list,actor2_list,actor3_list,"
	     . "actor4_list,actor5_list,tone_id,pict_id,color_id,fsk,comment,"
	     . "lp,counter1,counter2,commercials_id,audio,subtitle,lastchange,"
             . "vnorm_id,private,imdb_id,rating) "
	     . "VALUES ("
	     . "$mtype_id,$cass_id,$part,'$title',$label,$length,'$aq_date','$source',"
	     . "$director_id,$director_list,$music_id,$music_list,'$country',"
	     . "$year,$cat1_id,$cat2_id,$cat3_id,$actor1_id,$actor2_id,"
	     . "$actor3_id,$actor4_id,$actor5_id,$actor1_list,$actor2_list,"
	     . "$actor3_list,$actor4_list,$actor5_list,$tone_id,$pict_id,"
	     . "$color_id,$fsk,'$comment',$lp,'$counter1','$counter2',"
             . "$commercials_id,'$audio_ts','$subtitle','".date('Y-m-d H:i:s')."',"
             . "$vnorm_id,$private,'$imdb_id',$rating)";
     $success = $this->query($insert);
     if ( $pvp->common->medium_is_rw($mtype_id) ) {
       $this->insert_medium($cass_id,$mtype_id,$space);
       $this->update_freetime($cass_id,$mtype_id);
     }
     $this->set_disktype($cass_id,$mtype_id,$disktype,$owner_id,$storeplace,$lentto);
     if ( isset($rc) && count($rc) ) $this->set_rc($mtype_id,$cass_id,$rc);
     return $success;
   }

   /** Move a movie to a new place
    * @method move_movie
    * @param integer id movie id
    * @param integer mtype_id media type id
    * @param integer cass_id media_id
    * @param integer part part
    * @return boolean success
    */
   function move_movie($id,$mtype_id,$cass_id,$part) {
     GLOBAL $pvp,$valid;
     if ( !$valid->num($cass_id) || !$valid->num($part) ) return FALSE;
     if ( $this->get_movieid($mtype_id,$cass_id,$part) ) {
       header('Content-type: text/html; charset=utf-8');
       echo "<HTML><HEAD>\n <meta http-equiv='Content-Type' content='text/html; charset=utf-8'>\n"
          . " <meta http-equiv='cache-control' content='no-cache'>\n <TITLE>Error</TITLE>\n"
          . "</HEAD><BODY>\n";
       display_error( lang("dupe_id_entered") );
       echo "</BODY></HTML>";
       exit;
     }
     #-- collect some info first
     $movie = $this->get_movie($id);
     $space = $this->get_mediaspace($movie['cass_id'],$movie['mtype_id']);
     $this->dbquery("SELECT COUNT(part) AS nr FROM pvp_video WHERE mtype_id=".$movie['$mtype_id']." AND media_id=".$movie['cass_id']);
     $this->next_record();
     $source_movs = $this->f('nr');
     $this->dbquery("SELECT COUNT(part) AS nr FROM pvp_video WHERE mtype_id=$mtype_id AND media_id=$cass_id");
     $this->next_record();
     $target_movs = $this->f('nr'); ++$target_movs;
     #-- update pvp_video table
     $query = "UPDATE pvp_video SET mtype_id=$mtype_id,media_id=$cass_id,part=$part"
            . " WHERE id=$id";
     $success = $this->dbquery($query);
     #-- cater for pvp_media table
     if ($source_movs < 2) { // this was the last on old medium
       if ($target_movs < 2) { // this is the 1st on new medium => move_media
         $this->dbquery("UPDATE pvp_media SET id=$cass_id,mtype_id=$mtype_id WHERE id=".$movie['cass_id']." AND mtype_id=".$movie['mtype_id']);
       } else {
         if ($pvp->config->remove_empty_media) $this->delete_medium($movie['cass_id'],$movie['mtype_id']);
         else if ($pvp->common->medium_is_rw($movie['mtype_id']))
           $this->update_freetime($movie['cass_id'],$movie['mtype_id']); // update freetime of old medium
       }
     } else {
       if ($pvp->common->medium_is_rw($movie['mtype_id']))
         $this->update_freetime($movie['cass_id'],$movie['mtype_id']); // update freetime of old medium
     }
     if ( $pvp->common->medium_is_rw($mtype_id) ) { // is target r/w ?
       $this->update_freetime($cass_id,$mtype_id); // update freetime of new medium
     }
     return $success;
   }

   /** Get a list of duplicate titles
    * @method get_dupetitles
    * @param optional boolean strict if set to TRUE (default), a movie is not
    *  considered a duplicate if one of the following criteria is met:<ul>
    *    <li>different FSK (intended audience differs)</li>
    *    <li>different year (maybe a new version/remake)</li>
    *    <li>different audio tracks, and no movie covers all of the others</li>
    *  </ul>
    * @param optional boolean owner default TRUE - whether to restrict the
    *  check to the records owned by the logged-in user
    * @return array array of titles:
    *  array[$i]['title']; array[$i][$k]-&gt;id,mtype_id,cass_nr,part,len
    *  where $i counts the distinct titles, and $k the copies per title
    */
   function get_dupetitles($strict=1,$owner=1) {
     GLOBAL $pvp;
     if ($owner) { // only check for the owners records
       $valid_owners = array($pvp->auth->user_id);
     } elseif (!$pvp->auth->admin) {
       $valid_owners = $this->get_usergrants(array(),array(0,$pvp->auth->user_id),array('SELECT'));
     }
     $query  = "SELECT o.title as titel, o.id as o_id, o.mtype_id as o_mtypeid,"
             . " o.media_id as o_cassnr, o.part as o_part, o.length as o_len,"
             . " o.audio as o_audio, o.fsk as o_fsk, o.year as o_year,"
             . " d.id as d_id, d.mtype_id as d_mtypeid,"
             . " d.media_id as d_cassnr, d.part as d_part, d.length as d_len,"
             . " d.audio AS d_audio, d.fsk as d_fsk, d.year as d_year,"
             . " o.private AS o_private, d.private AS d_private"
             . " FROM pvp_video o, pvp_video d"
             . " WHERE o.title=d.title AND o.id<d.id"
             . " ORDER BY o_id ASC";
     $this->dbquery($query);
     $i = -1;
     while ( $this->next_record() ) {
       $title = $this->f('titel');
       if ($strict) {
         if ($this->f('o_fsk')!=$this->f('d_fsk')) continue;
         if ($this->f('o_year')!=$this->f('d_year')) continue;
       // now check if audio_lang is the same or one movie contains all
       // audio tracks of the other -- otherwise this is no dupe
         if(isset($audio_all)) unset($audio_all);
         $audio_str = substr($this->f('o_audio'),1,strlen($this->f('o_audio')-2));
         $audio_arr = explode(",",$audio_str); $ac1 = count($audio_arr);
         foreach ($audio_arr as $val) $audio_all[$val] = 1;
         $audio_str = substr($this->f('d_audio'),1,strlen($this->f('d_audio'))-2);
         $audio_arr = explode(",",$audio_str); $ac2 = count($audio_arr);
         foreach ($audio_arr as $val) $audio_all[$val] = 1; $ac3 = count($audio_all);
         if ( !($this->f('o_audio')=='' || $this->f('d_audio')=='') && !( $ac3==$ac1 || $ac3==$ac2 ) ) continue;
       }
       if ( $i==-1 || $dupes[$i]['title']!=$title ) {
         ++$i; $k=0;
         $dupes[$i]['title'] = $title;
         $dupes[$i][$k]->id       = $this->f('o_id');
         $dupes[$i][$k]->mtype_id = $this->f('o_mtypeid');
         $dupes[$i][$k]->cass_nr  = $this->f('o_cassnr');
         $dupes[$i][$k]->part     = $this->f('o_part');
         $dupes[$i][$k]->len      = $this->f('o_len');
         $dupes[$i][$k]->private  = $this->f('o_private');
       }
       ++$k;
       $dupes[$i][$k]->id       = $this->f('d_id');
       $dupes[$i][$k]->mtype_id = $this->f('d_mtypeid');
       $dupes[$i][$k]->cass_nr  = $this->f('d_cassnr');
       $dupes[$i][$k]->part     = $this->f('d_part');
       $dupes[$i][$k]->len      = $this->f('d_len');
       $dupes[$i][$k]->private  = $this->f('d_private');
     }
     $dc = count($dupes);
     for ($i=0;$i<$dc;++$i) { // check the owner
       $kc = count($dupes[$i]);
       $have_unset = FALSE;
       for ($k=0;$k<$kc;++$k) {
         if (!empty($dupes[$i][$k]->mtype_id)) {
           $query = "SELECT owner FROM pvp_media"
                  . " WHERE id=".$dupes[$i][$k]->cass_nr
                  . "   AND mtype_id=".$dupes[$i][$k]->mtype_id;
           $this->query($query);
           $this->next_record();
           $owner_id = $this->f('owner');
           if (!isset($valid_owners) || $owner_id==$pvp->auth->user_id
            || ( !$dupes[$i][$k]->private && in_array($owner_id,$valid_owners)) ) {
             $this->query("SELECT login FROM pvp_users WHERE id=".$owner_id);
             $this->next_record();
             $dupes[$i][$k]->owner = $this->f('login');
           } else {
             if (count($dupes[$i])>3) unset ($dupes[$i][$k]);
             else {
               unset($dupes[$i]);
               $have_unset = TRUE;
             }
           }
         }
       }
     }
     if ($have_unset) {
       for ($i=0;$i<$dc;++$i) {
         if (isset($dupes[$i])) $list[] = $dupes[$i];
       }
       return $list;
     }
     return $dupes;
   }
   
   ############################################################################
   # Media Specific Stuff
   ############################################################################

   /** Find orphaned movies
    *  Orphaned movies are movies which have no medium associated in the
    *  pvp_media table
    * @method get_orphaned_movies
    * @return array list (array of objects w/ prop: number, link, title, id, mtype_id
    */
   function get_orphaned_movies() {
     $list = array();
     $query = "SELECT mt.sname,v.mtype_id,v.media_id,v.part,v.title"
            . "  FROM pvp_video v"
            . "  LEFT JOIN pvp_media m ON (v.mtype_id=m.mtype_id AND v.media_id=m.id)"
            . "  JOIN pvp_mtypes mt ON (v.mtype_id=mt.id)"
            . " WHERE m.id IS NULL"
            . " ORDER BY v.media_id,v.part";
     $this->dbquery($query);
     while ($this->next_record()) {
       $item->number = $this->f('sname')." ".$this->f('media_id')."-".$this->f('part');
       $item->link   = "mtype_id=".$this->f('mtype_id')."&cass_id=".$this->f('media_id')."&part=".$this->f('part');
       $item->title  = $this->f('title');
       $item->id     = $this->f('media_id');
       $item->mtype_id = $this->f('mtype_id');
       $list[] = $item;
       unset($item);
     }
     return $list;
   }

   /** Fix orphaned movies
    * @method fix_orphaned_movie
    * @param integer id MediaID
    * @param integer mtype_id Media Type ID
    * @param integer owner OwnerID
    * @return boolean success
    */
   function fix_orphaned_movie($id,$mtype_id,$owner) {
     $query = "INSERT INTO pvp_media (id,mtype_id,owner) VALUES ($id,$mtype_id,$owner)";
     return $this->dbquery($query);
   }

   /** Get media information
    * @method get_mediainfo
    * @param integer mtype_id
    * @param integer id
    * @return object disk
    */
   function get_mediainfo($mtype_id,$id) {
     GLOBAL $pvp;
     if (empty($mtype_id) || empty($id)) return FALSE;
     $query = "SELECT disks_id,size,free,rc,owner,storeplace,lentto"
            . "  FROM pvp_media"
            . " WHERE id=$id AND mtype_id=$mtype_id";
     $this->dbquery($query);
     if ($this->next_record()) { // skip not existing media
       $disk->id         = $id;
       $disk->mtype_id   = $mtype_id;
       $disk->disks_id   = $this->f('disks_id');
       $disk->size       = $this->f('size');
       $disk->free       = $this->f('free');
       $disk->rc_str     = substr($this->f('rc'),1);
       if (!empty($disk->rc_str))
         $disk->rc_str = substr($disk->rc_str,0,strlen($disk->rc_str)-1);
       $disk->owner_id   = $this->f('owner');
       $disk->storeplace = $this->f('storeplace');
       $disk->lentto     = $this->f('lentto');
       $owner = $this->get_users($disk->owner_id);
       $disk->owner      = $owner->login;
       $dt = $this->get_disktypes("",$disk->disks_id);
       $disk->type       = $dt[0]->name;
       $disk->rcsupport  = $dt[0]->rc;
       if ($disk->rcsupport) $disk->rc = $this->get_rc($mtype_id,$id);
       if ($pvp->common->medium_is_rw($mtype_id)) { $disk->rw = lang("yes"); }
         else { $disk->rw = lang("no"); }
       return $disk;
     } else return FALSE;
   }

   /** Set media information (update changes)
    *  The object can be incomplete: Only the values set will be updated
    * @method set_mediainfo
    * @param integer mtype_id
    * @param integer id
    * @param object disk
    */
   function set_mediainfo($mtype_id,$id,$disk) {
     GLOBAL $pvp;
     $this->query("SELECT owner FROM pvp_media WHERE id=$id AND mtype_id=$mtype_id");
     $this->next_record();
     $add   = "";
     if ($this->f('owner')||$this->f('owner')==0) { // this is an update
       $query  = "UPDATE pvp_media ";
       if (isset($disk->disks_id)) { $add .= ",disks_id=".$disk->disks_id; }
       if (isset($disk->size)) { $add .= ",size=".$disk->size; }
       if (isset($disk->owner_id)) { $add .= ",owner=".$disk->owner_id; }
       $check = array("storeplace","lentto");
       foreach ($check as $val) {
         if (isset($disk->$val)) $add .= ",$val='".$disk->$val."'";
       }
       if (strlen($add)) {
         $query .= "SET ".substr($add,1)." WHERE id=$id AND mtype_id=$mtype_id";
         $this->dbquery($query);
       }
     } else { // no entry yet - go insert it!
       $query  = "INSERT INTO pvp_media (id,mtype_id";
       $add    = "VALUES ($id,$mtype_id";
       if (isset($disk->disks_id)) { $query .= ",disks_id"; $add .= ",".$disk->disks_id; }
       if (isset($disk->size)) { $query .= ",size"; $add .= ",".$disk->size; }
       if (isset($disk->free)) { $query .= ",free"; $add .= ",".$disk->free; }
       if (!isset($disk->owner_id)) $disk->owner_id = $pvp->auth->user_id;
       $query .= ",owner"; $add .= ",".$disk->owner_id;
       if (isset($disk->storeplace)) { $query .= ",storeplace"; $add .= ",'".$disk->storeplace."'"; }
       if (isset($disk->lentto)) { $query .= ",lentto"; $add .= ",'".$disk->lentto."'"; }
       $query .= ") $add)";
       $this->dbquery($query);
     }
     if (isset($disk->rc) && is_array($disk->rc))
       $this->set_rc($mtype_id,$id,$disk->rc);
   }

   /** Transfer ownership of media from one user to another for all
    *  of the first users media
    * @method user_media_xfer
    * @param integer from_user_id
    * @param integer to_user_id
    * @return boolean success
    */
   function user_media_xfer($fromid,$toid) {
     $query = "UPDATE pvp_media SET owner=$toid WHERE owner=$fromid";
     return $this->dbquery($query);
   }

   /** Delete all media owned by a given user (including content)
    * @method user_media_delete
    * @param integer owner_id
    * @return boolean success
    */
   function user_media_delete($owner_id) {
     $mid_list = "";
     $this->query("SELECT id FROM pvp_media WHERE owner=$owner_id");
     while ($this->next_record()) {
       $mid[] = $this->f('id');
       $mid_list .= ",".$this->f('id');
     }
     $mc = count($mid);
     if ($mc>0) {
       $mid_list = substr($mid_list,1); // strip leading comma
       for ($i=0;$i<$mc;++$i) { // delete the movies from affected media
         // check directors from affected videos
         $did_list = "";
         $query = "SELECT DISTINCT director_id FROM pvp_video WHERE media_id IN ($mid_list)";
         $this->query($query);
         while ($this->next_record()) {
           $dd = $this->f('director_id');
           if (!empty($dd)) $did_list = ",".$this->f('director_id');
         }
         if (!empty($did_list))
           $this->query("DELETE FROM pvp_directors WHERE id IN (".substr($did_list,1).")");
         // check for composers
         $did_list = "";
         $query = "SELECT DISTINCT music_id FROM pvp_video WHERE media_id IN ($mid_list)";
         $this->query($query);
         while ($this->next_record()) {
           $dd = $this->f('music_id');
           if (!empty($dd)) $did_list = ",".$this->f('music_id');
         }
         if (!empty($did_list))
           $this->query("DELETE FROM pvp_music WHERE id IN (".substr($did_list,1).")");
         // check for actors
         $did_list = "";
         $query = "SELECT DISTINCT actor1_id FROM pvp_video WHERE media_id IN ($mid_list)";
         $this->query($query);
         while ($this->next_record()) {
           $aid[] = $this->f('actor1_id');
           $did_list .= ",".$this->f('actor1_id');
         }
         for ($i=1;$i<6;++$i) {
           $query = "SELECT DISTINCT actor${i}_id FROM pvp_video WHERE media_id IN ($mid_list)";
           $this->query($query);
           while ($this->next_record()) {
             if (!in_array($this->f("actor${i}_id"),$aid)) {
               $aid[] = $this->f("actor${i}_id");
               $did_list .= ",".$this->f("actor${i}_id");
             }
           }
         }
         $ac = count($aid);
         for ($i=0;$i<$ac;++$i) {
           if (!empty($aid[$i])) {
             $query = "SELECT count(id) AS idc FROM pvp_video WHERE (actor1_id=".$aid[$i]
                    . " OR actor2_id=".$aid[$i]." OR actor3_id=".$aid[$i]
                    . " OR actor4_id=".$aid[$i]." OR actor5_id=".$aid[$i]
                    . ") AND media_id NOT IN ($mid_list)";
             $this->query($query);
             $this->next_record();
             if ($this->f('idc')==0) {
               $this->query("DELETE FROM pvp_actors WHERE id=".$aid[$i]);
             }
           }
         }
         // delete the movies
         $this->query("DELETE FROM pvp_video WHERE media_id IN ($mid_list)");
       }
     }
     return $this->query("DELETE FROM pvp_media WHERE owner=$owner_id");
   }

   /** Obtain all media numbers that have a certain disk type assigned
    * @method get_mediaForDisktype
    * @param integer id disktype-ID
    * @return array media (array of objects w/ properties mtype_id, cass_id)
    */
   function get_mediaForDisktype($id) {
     $this->dbquery("SELECT mtype_id,id FROM pvp_media WHERE disks_id=$id");
     while ( $this->next_record() ) {
       $m->cass_id  = $this->f('id');
       $m->mtype_id = $this->f('mtype_id');
       $media[] = $m;
       unset($m);
     }
     return $media;
   }

   /** Obtain all disk type for a given media type
    * @method get_disktypes
    * @param integer mtype_id Media Type ID
    * @param optional integer id ID for a specific entry
    * @return array disktypes (array of objects, properties:
    *   int id, string name, string size, int lp, array rc)
    */
   function get_disktypes($mtype_id,$id="") {
     $query = "SELECT name,id,size,lp,rc FROM pvp_disks WHERE ";
     if ($id) {
       $query .= "id=$id";
     } else {
       $query .= "mtype_id=$mtype_id";
     }
     $this->dbquery($query);
     while ( $this->next_record() ) {
       $type->id   = $this->f('id');
       $type->name = $this->f('name');
       $type->size = $this->f('size');
       $type->lp   = $this->f('lp');
       $type->rc   = $this->f('rc');
       $types[]    = $type;
       unset($type); // work around PHP5 bug always using references to $type here
     }
     if (isset($types)) return $types;
     return "";
   }

   /** Obtain disktype of a given medium
    * @method public disktypeGetForMedia
    * @param integer mtype_id Media Type ID
    * @param integer media_id Media ID (alias cass_id)
    * @return object disktype (properties: int(type) [=id],array(rc))
    */
   function disktypeGetForMedia($mtype_id,$media_id) {
     $mt->type = 0; $mt->rc = array();
     if (empty($mtype_id) || empty($media_id)) return $mt;
     $media_id = (int) $media_id;
     $this->dbquery("SELECT disks_id,rc FROM pvp_media WHERE mtype_id=$mtype_id AND id=$media_id");
     if (!$this->num_rows()) return $mt;
     $this->next_record();
     $mt->type = $this->f('disks_id');
     $rc = $this->f('rc');
     $trc = explode(",",substr($rc,1,strlen($rc)-2));
     foreach ($trc as $var) { $mt->rc[$var] = 1; }
     return $mt;
   }

   /** Delete a disktype from table disks
    * @method delete_disktype
    * @param integer id
    * @return boolean success
    */
   function delete_disktype($id) {
     if ( $this->dbquery("UPDATE pvp_media SET disks_id=NULL WHERE disks_id=$id") ) {
       return $this->dbquery("DELETE FROM pvp_disks WHERE id=$id");
     } else {
       return FALSE;
     }
   }

   /** Update a disktype in table disks
    * @method update_disktype
    * @param integer id
    * @param integer mtype_id
    * @param string name
    * @param string size
    * @param integer lp
    * @param integer rc
    * @return boolean success
    */
   function update_disktype($id,$mtype_id,$name,$size,$lp,$rc) {
     if ( $id ) {
       $query = "UPDATE pvp_disks SET "
              . "mtype_id=$mtype_id,name='$name',size='$size',lp=$lp,rc=$rc "
              . "WHERE id=$id";
     } else {
       $query = "INSERT INTO pvp_disks (mtype_id,name,size,lp,rc)"
              . " VALUES ($mtype_id,'$name','$size',lp,rc)";
     }
     return $this->dbquery($query);
   }

   /** Get a specific disktype id
    * @method get_disktype_id
    * @param integer mtype_id
    * @param integer cass_id
    * @return integer disktype_id
    */
   function get_disktype_id($mtype_id,$cass_id) {
     $this->dbquery("SELECT disks_id FROM pvp_media WHERE id=$cass_id AND mtype_id=$mtype_id");
     $this->next_record();
     return $this->f('disks_id');
   }

   /** Set disktype for a medium
    * @method set_disktype
    * @param integer cass_id
    * @param integer mtype_id
    * @param integer disktype_id
    * @return boolean success
    */
   function set_disktype($cass_id,$mtype_id,$disktype_id,$owner_id,$storeplace,$lentto) {
     GLOBAL $pvp;
     if ($owner_id == "") $owner_id = $pvp->auth->user_id;
     $this->dbquery("SELECT id FROM pvp_media WHERE id=$cass_id AND mtype_id=$mtype_id");
     $this->next_record();
     if ( $id = $this->f('id') ) {
       $set = "disks_id=$disktype_id,owner=$owner_id";
       if (!empty($storeplace)) $set .= ",storeplace='$storeplace'";
       if (!empty($lentto)) $set .= ",lentto='$lentto'";
       return $this->dbquery("UPDATE pvp_media SET $set WHERE id=$id AND mtype_id=$mtype_id");
     } else {
       $set  = "disks_id,owner";
       $data = "$disktype_id,$owner_id";
       if (!empty($storeplace)) { $set .= ",storeplace"; $data .=",'$storeplace'"; }
       if (!empty($lentto)) { $set .= ",lentto"; $data .=", '$lentto'"; }
       return $this->dbquery("INSERT INTO pvp_media (id,mtype_id,$set) VALUES($cass_id,$mtype_id".",$data)");
     }
   }

   /** Set region code(s) for a specific medium
    * @method set_rc
    * @param integer mtype_id
    * @param integer cass_id
    * @param array rc
    * @return boolean success
    */
   function set_rc($mtype_id,$cass_id,$rc) {
     GLOBAL $pvp;
     if ( count($rc) ) {
       $rcs = ",";
       for ($i=0;$i<7;++$i) {
         if (isset($rc[$i]) && $rc[$i]) $rcs .= $i . ",";
       }
     } else {
       $rcs = "";
     }
     $this->dbquery("SELECT id FROM pvp_media WHERE id=$cass_id AND mtype_id=$mtype_id");
     $this->next_record();
     if ( $id = $this->f('id') ) {
       return $this->dbquery("UPDATE pvp_media SET rc='$rcs' WHERE id=$id AND mtype_id=$mtype_id");
     } else {
       return $this->dbquery("INSERT INTO pvp_media (id,mtype_id,rc,owner) VALUES ($cass_id,$mtype_id,'$rcs',".$pvp->auth->user_id.")");
     }
   }

   /** Retrieve region code for a given medium
    * @method get_rc
    * @param integer mtype_id
    * @param integer cass_id
    * @return array rc
    */
   function get_rc($mtype_id,$cass_id) {
     $this->dbquery("SELECT rc FROM pvp_media WHERE id=$cass_id AND mtype_id=$mtype_id");
     $this->next_record();
     $rcs = $this->f('rc');
     if (!$rcs) return "";
     $rcs = substr( $rcs,1,strlen($rcs)-2 );
     $rct  = explode(",",$rcs);
     $rccount = count($rct);
     for ($i=0;$i<$rccount;++$i) {
       $rc[$rct[$i]] = 1;
     }
     return $rc;
   }

   /** Get all media types and return them as array
    * @method get_mtypes
    * @param optional string restrict WHERE clause
    * @return array array of media types (i:id, i:sname, i:name)
    */
   function get_mtypes($restrict="") {
     if ( strlen($restrict) ) {
       $where = " WHERE $restrict";
     } else {
       $where = "";
     }
     $this->dbquery("SELECT id,name,sname FROM pvp_mtypes $where ORDER BY id");
     $i = 0;
     while ( $this->next_record() ) {
       $mtypes[$i]['id'] = $this->f('id');
       $mtypes[$i]['sname'] = $this->f('sname');
       $mtypes[$i]['name'] = $this->f('name');
       ++$i;
     }
     return $mtypes;
   }

   /** update mtype data (wrapper to set_av)
    * @method set_mtypes
    * @param string name
    * @param string sname
    * @param optional integer id
    * @see set_av()
    */
   function set_mtypes($name,$sname,$id="") {
     return $this->set_av("pvp_mtypes",$name,$sname,$id);
   }

   /** Insert a medium into the media table (if not yet exists)
    * @method insert_medium
    * @param integer cass_id media id
    * @param integer mtype_id media type id
    * @param integer space complete space on media (media length)
    */
   function insert_medium($cass_id,$mtype_id,$space) {
     GLOBAL $pvp;
     # add the fields storeplace + lentto *!*
     $free = $this->get_mediaspace($cass_id,$mtype_id);
     if ($free=="") { // medium not yet in pvp_media table
       if (!$space) $space = 240;
       $this->dbquery("INSERT INTO pvp_media (id,mtype_id,size,free,owner) VALUES ($cass_id,$mtype_id,$space,0,".$pvp->auth->user_id.")");
     }
   }

   /** Delete a medium from the media table.
    *  Removes the entry from pvp_media table only if the medium is empty (or $force is set)
    * @method delete_medium
    * @param integer media_id media id
    * @param integer mtype_id media type id
    * @param optional boolean force force deletion even if not empty (default: no)
    * @return boolean wether deletion took place
    */
   function delete_medium($media_id,$mtype_id,$force=FALSE) {
     $this->dbquery("SELECT COUNT(id) as mcount FROM pvp_video WHERE media_id=$media_id AND mtype_id=$mtype_id");
     $this->next_record();
     if ( $this->f('mcount') < 1 ) $force = TRUE;
     if ($force) {
       $this->dbquery("DELETE FROM pvp_media WHERE id=$media_id AND mtype_id=$mtype_id");
       return TRUE;
     }
     return FALSE;
   }

   /** Get freetime of a given medium
    * @method get_mediumfreetime
    * @param integer id media id
    * @param integer mtype_id media type id
    * @return mixed either freetime (integer) or empty string
    */
   function get_mediumfreetime($id,$mtype_id) {
     $free  = $this->get_mediaspace($id,$mtype_id);
     if ( empty($free) ) return "";
     $query = "SELECT length,lp FROM pvp_video WHERE media_id=$id AND mtype_id=$mtype_id";
     $this->dbquery($query);
     $i=0;
     while ( $this->next_record() ) {
       ++$i;
       $length = $this->f('length');
       if ( $this->f('lp') ) $length /= 2;
       $free -= $length;
     }
     return $free;
   }

   /** Get space on a medium
    * @method get_mediaspace
    * @param integer id media id
    * @param integer mtype_id media type id
    * @param optional string field fieldname ("type" or "free", defaults to type)
    * @return mixed either freetime (integer) or empty string
    */
   function get_mediaspace($id,$mtype_id,$col="size") {
     $this->dbquery("SELECT $col FROM pvp_media WHERE id=$id AND mtype_id=$mtype_id");
     if ( $this->next_record() ) return $this->f("size");
     return "";
   }

   /** Set space on a medium
    * @method set_mediaspace
    * @param integer id media id
    * @param integer mtype_id media type id
    * @param integer space
    * @param optional string field fieldname ("type" or "free", defaults to type)
    * @return mixed either freetime (integer) or empty string
    */
   function set_mediaspace($id,$mtype_id,$space,$col="size") {
     GLOBAL $valid,$pvp;
     if ( !$valid->num($space) ) return FALSE;
     if ( $this->get_mediaspace($id,$mtype_id,$col) ) {
       $query = "UPDATE pvp_media SET $col=$space WHERE id=$id AND mtype_id=$mtype_id";
     } else {
       $query = "INSERT INTO pvp_media (id,mtype_id,$col,owner) VALUES ($id,$mtype_id,$space,".$pvp->auth->user_id.")";
     }
     if ( $this->dbquery($query) ) {
       return $this->update_freetime($id,$mtype_id);
     }
     return FALSE;
   }

   /** Update freetime on a medium. If $free is not specified, recalc freetime
    * @method update_freetime
    * @param integer id media id
    * @param optional integer mtype_id media type id (defaults to 1)
    * @param optional integer free free time
    * @return boolean success
    */
   function update_freetime($id,$mtype_id="1",$free="") {
     GLOBAL $valid;
     if ($free=="") {
       $free = $this->get_mediumfreetime($id,$mtype_id);
     } else {
       if ( !$valid->num($free) ) return FALSE;
     }
     return $this->dbquery("UPDATE pvp_media SET free=$free WHERE id=$id AND mtype_id=$mtype_id");
   }

   /** Get list of free space on media. If $start is set, the result set is
    *  limited based on $pvp->preferences->limit
    * @method get_freelist
    * @param integer minfree min amount of freetime to display
    * @param optional string filter filter restriction to apply
    * @param optional integer start (for use of LIMIT)
    * @return array freelist (i:id, i:free where i:id is the media ID)
    */
   function get_freelist($minfree,$filter="",$start="") {
     $restrict = "free>=$minfree";
     if ( strlen($filter) ) {
       $this->dbquery("SELECT media_id FROM pvp_video v WHERE $filter");
       $i=0;
       while ( $this->next_record() ) {
         if ($i) { $tapelist .= "," . $this->f('media_id'); }
	   else { $tapelist = $this->f('media_id'); ++$i; }
       }
       $restrict .=  " AND id IN ($tapelist)";
     }
     $query = "SELECT id,mtype_id,free FROM pvp_media WHERE $restrict ORDER BY free";
     if ($start==="") { $this->dbquery($query); $totals = $this->num_rows(); }
       else { $totals = $this->lim_query($query,$start); }
     $i=0;
     while ( $this->next_record() ) {
       $freelist[$i]['id']       = $this->f('id');
       $freelist[$i]['mtype_id'] = $this->f('mtype_id');
       $freelist[$i]['free']       = $this->f('free');
       ++$i;
     }
     $freelist['totals'] = $totals;
     return $freelist;
   }

   ############################################################################
   /** Get list of "visible" staff members If $start is set, the result set is
    *  limited based on $pvp->preferences->limit
    * @method get_visstafflist
    * @param string stafftype whether it is music, directors or actors
    * @param optional string filter filter restrictions
    * @param optional integer start (for use with LIMIT)
    * @return array stafflist (i:id (staff member ID), i:name
    *  (array formatted by sql::format_name())
    */
   function get_visstafflist($stafftype,$filter="",$start="") {
     GLOBAL $pvp;
     if (strlen($filter)) $restrict = "AND $filter";
     if (!$pvp->auth->admin) {
       $gusers = implode(",",$this->get_usergrants(array(),array(0,$pvp->auth->user_id),array("SELECT")));
       $from = "FROM pvp_video v, pvp_media m"
             . " WHERE v.media_id=m.id AND v.mtype_id=m.mtype_id"
             . " AND m.owner IN ($gusers) AND";
     } else {
       $from = "FROM pvp_video v WHERE";
     }
     switch ($stafftype) {
       case "music"     : $query[] = "SELECT DISTINCT music_id FROM pvp_video v WHERE music_list=1 $restrict"; $field[] = "music_id"; break;
       case "directors" : $query[] = "SELECT DISTINCT director_id FROM pvp_video v WHERE director_list=1 $restrict"; $field[] = "director_id"; break;
       case "actors"    : $query[] = "SELECT DISTINCT actor1_id $from actor1_list=1 $restrict"; $field[] = "actor1_id";
                          $query[] = "SELECT DISTINCT actor2_id $from actor2_list=1 $restrict"; $field[] = "actor2_id";
                          $query[] = "SELECT DISTINCT actor3_id $from actor3_list=1 $restrict"; $field[] = "actor3_id";
                          $query[] = "SELECT DISTINCT actor4_id $from actor4_list=1 $restrict"; $field[] = "actor4_id";
                          $query[] = "SELECT DISTINCT actor5_id $from actor5_list=1 $restrict"; $field[] = "actor5_id"; break;
     }
     for ($i=0;$i<count($query);$i++) {
       $this->dbquery($query[$i]);
       while ( $this->next_record() ) {
         $id[$i][] = $this->f("$field[$i]");
       }
       if ($i) { $ar = array_merge($ar,$id[$i]); }
         else { $ar = $id[$i]; }
     }
     if (is_array($ar)) {
       $list  = implode (",",$ar); // idlist of visible staff members
     } else {
       $list = FALSE;
     }
     if ($list) {
       $query = "SELECT id,name,firstname FROM $stafftype WHERE id IN ($list) ORDER BY name,firstname";
       if ($start==="") { $this->dbquery($query); $totals = $this->num_rows(); }
         else { $totals = $this->lim_query($query,$start); }
       $i=0;
       while ( $this->next_record() ) {
         $stafflist[$i]['id']   = $this->f('id');
         $name['firstname']     = $this->f('firstname');
         $name['name']          = $this->f('name');
         $name['id']            = $stafflist[$i]['id'];
         $stafflist[$i]['name'] = $this->format_name($name);
         ++$i;
       }
       $stafflist['totals'] = $totals;
     } else {
       $stafflist['totals'] = 0;
     }
     return $stafflist;
   }

   ############################################################################
   /** Check wether a given person exists in the db and aquire his/her id. If not
    *  found in db, insert him/her first. If a valid imdb_id was specified, just
    *  the imdb_id will compared - different name spellings are ignored. This
    *  also means, if the same person already exists in the DB but w/o imdb_id,
    *  a new entry would be added although (since we cannot tell if this really
    *  is the same person, or just has the same name).
    * @method private insert_person
    * @param string person stafftype
    * @param string query SQL query for SELECT statement
    * @param string sub_query SQL query for INSERT statement
    * @param optional string name family name of person
    * @param optional string fname first name of person
    * @param optional string imdb_id
    * @return integer id (person_id)
    */
   function insert_person($person,$query,$sub_query,$name="",$fname="",$imdb_id="") {
     GLOBAL $dmsg,$pvp;
     if ( strlen( trim($name . $fname) ) < 1) {
       $dmsg .=  "<li><SPAN CLASS='ok'>$person not specified, no action taken.</SPAN>\n";
       return 0;
     } else {
       $name  = $pvp->common->safeinput($name);
       $fname = $pvp->common->safeinput($fname);
       if (!empty($imdb_id) && !preg_match("|^\d{7}$|",$imdb_id)) {
         $dmsg .=  "<li><SPAN CLASS='ok'>Invalid IMDB ID '$imdb_id' - it must consist of exactly 7 digits. ID ignored and emptied.</SPAN>\n";
	 unset($imdb_id);
       }
       if (!empty($imdb_id)) {
         $query .= " WHERE imdb_id='$imdb_id'";
	 if (empty($fname)) {
	   $sub_query .= " (name,imdb_id) VALUES ('$name','$imdb_id')";
	 } elseif (empty($name)) {
	   $sub_query .= " (firstname,imdb_id) VALUES ('$fname','$imdb_id')";
	 } else {
	   $sub_query .= " (name,firstname,imdb_id) VALUES ('$name','$fname','$imdb_id')";
         }
       } elseif (empty($fname)) {
         $query .= " WHERE name='$name'";
         $sub_query .= " (name) VALUES ('$name')";
       } elseif (empty($name)) {
         $query .= " WHERE firstname='$fname'";
         $sub_query .= " (firstname) VALUES ('$fname')";
       } else {
         $query .= " WHERE name='$name' AND firstname='$fname'";
         $sub_query .= " (name,firstname) VALUES ('$name','$fname')";
       }
     }
     $dmsg  .= " <li><SPAN CLASS='ok'>" . stripslashes($query) . "</SPAN>";
     $this->dbquery($query);
     if ( $this->next_record() ) {
       $id = $this->f('id');
       $dmsg  .= " (Got: '$id')</Font>\n";
     } else {
       $dmsg  .= "<BR><SPAN CLASS='error'>$person not found in db! Trying to insert...</SPAN><BR>\n";
       if ( $this->dbquery($sub_query) ) {
         $this->dbquery($query);
         if ( $this->next_record() ) {
           $id = $this->f('id');
           $dmsg  .= "<SPAN CLASS='ok'>$person \"$name, $fname\" inserted into db (id: $id).</SPAN>\n";
         } else {
           $dmsg  .= "<SPAN CLASS='error'>Something strange happened: inserted $person \"$name, $fname\" into db, but could not find him/her afterwards!</SPAN>\n";
         }
       } else {
         $dmsg .= "<SPAN CLASS='error'>Insertion of $person \"$name, $fname\ into db failed!</SPAN>\n";
       }
     }
     return $id;
   } // end insert_person()

   /** Check wether a given person exists in the db and aquire his/her id. If not
    *  found in db, insert him/her first. If a valid imdb_id was specified, just
    *  the imdb_id will compared - different name spellings are ignored. This
    *  also means, if the same person already exists in the DB but w/o imdb_id,
    *  a new entry would be added although (since we cannot tell if this really
    *  is the same person, or just has the same name).
    * @method check_person
    * @param string name family name
    * @param string fname first name
    * @param string stafftype
    * @param optional boolean code call addslashes on the names?
    * @param optional integer mid IMDB ID
    * @return integer id
    */
   function check_person($name,$fname,$table,$code=FALSE,$mid="") {
     if (substr($table,0,3)!="pvp") $table = "pvp_".$table;
     if ($code) {
       $name = addslashes($name); $fname = addslashes($fname);
     }
     if (!preg_match('|\d{7}|',$mid)) $mid = "";
     if ( empty($mid) ) {
       $values = "NULL,";
     } else {
       $where  = "imdb_id='$mid'";
       $values = "'$mid',";
     } 
     if ( empty($name) ) {
       if (empty($mid)) $where  = "name IS NULL";
       $values .= "NULL,";
     } else {
       if (empty($mid)) $where  .= "name='$name'";
       $values .= "'$name',";
     }
     if ( !$fname ) {
       if (empty($mid)) $where  .= " AND firstname IS NULL";
       $values .= "NULL";
     } else {
       if (empty($mid)) $where  .= " AND firstname='$fname'";
       $values .= "'$fname'";
     }
     $get  = "SELECT id FROM $table WHERE $where";
     $this->dbquery($get);
     if ( $this->next_record() ) return $this->f('id');
     $this->dbquery("INSERT INTO $table (imdb_id,name,firstname) VALUES ($values)");
     $this->dbquery($get);
     $this->next_record();
     return $this->f('id');
   }

   ############################################################################
   /** Gather statistic informations from the database
    * @method get_stats
    * @return array stats
    */
   function get_stats() {
     GLOBAL $pvp;
     // ===[ counts ]===
     $details = array( array("name"=>"movies","sql"=>"SELECT count(id) AS movies FROM pvp_video"),
                       array("name"=>"actors","sql"=>"SELECT count(id) AS actors FROM pvp_actors"),
		       array("name"=>"directors","sql"=>"SELECT count(id) AS directors FROM pvp_directors"),
		       array("name"=>"composers","sql"=>"SELECT count(id) AS composers FROM pvp_music"),
		       array("name"=>"categories","sql"=>"SELECT count(id) AS categories FROM pvp_cat")
		     );
     foreach($details as $value) {
       $this->dbquery($value["sql"]);
       $this->next_record();
       $item = $value["name"];
       $stats[$item] = $this->f("$item");
     }
     $this->dbquery("SELECT DISTINCT mtype_id,media_id FROM pvp_video");
     $stats['media'] = $this->num_rows();
     $mt = $this->get_mtypes();
     $ct = count($mt);
     for ($i=0;$i<$ct;++$i) {
       $this->dbquery("SELECT DISTINCT media_id FROM pvp_video WHERE mtype_id=".$mt[$i]['id']);
       $ms['mcount'] = $this->num_rows();
       $ms['name']  = $mt[$i]['name'];
       $ms['sname'] = $mt[$i]['sname'];
       $stats['smedia'][] = $ms;
       unset($ms);
     }
     $this->dbquery("SELECT DISTINCT country FROM pvp_video");
     $stats['countries'] = $this->num_rows();
     for ($i=1;$i<4;++$i) {
       $cat = "cat" . $i . "_id";
       $this->dbquery("SELECT DISTINCT $cat FROM pvp_video");
       while ( $this->next_record() ) {
         ${$cat}[] = "a_" . $this->f("$cat"); // "a_" needed for array_merge to turn the integer into a string
       }
       if (is_array(${$cat})) ${$cat} = array_flip(${$cat});
     }
     if ( is_array($cat1_id) && is_array($cat2_id) && is_array($cat3_id) )
       $cats = array_merge($cat1_id,$cat2_id,$cat3_id);
     $stats['cats_used'] = count($cats);
     // ===[ ranks ]===
     $details = array( array("name"=>"country","sql"=>"SELECT count(id) AS rank, country AS item FROM pvp_video WHERE country IS NOT NULL GROUP BY country ORDER BY rank DESC"),
		       array("name"=>"director","sql"=>"SELECT count(id) AS rank, director_id AS item FROM pvp_video WHERE director_id>0 GROUP BY director_id ORDER BY rank DESC"),
		       array("name"=>"composer","sql"=>"SELECT count(id) AS rank, music_id AS item FROM pvp_video WHERE music_id>0 GROUP BY music_id ORDER BY rank DESC"),
		       array("name"=>"category","sql"=>"SELECT count(id) AS rank, cat1_id AS item FROM pvp_video GROUP BY cat1_id ORDER BY rank DESC")
                     );
     foreach($details as $value) {
       $this->dbquery($value["sql"]);
       $rankrecords = $this->num_rows();
       for ($i=1,$k=1;$k<4;++$i) {
         $this->next_record();
	 $item = $this->f('item');
	 $rank = "rank_" . $value["name"] . "_" . $k;
	 if (strlen( trim($item) )) ++$k; // do not count the "unknowns"
	 $stats[$rank] =  "$item (" . $this->f('rank') . ")";
         if ( $i==$rankrecords+1) break; // prevent endless loop on empty list
       }
     }
     for ($i=1;$i<4;++$i) {
       $rank  = "rank_country_" . $i;
       $count = $rank . "_count";
       $pos   = strpos($stats[$rank]," (");
       $stats[$count] = substr($stats[$rank],$pos+2,strlen($stats[$rank])-($pos+3));
       $stats[$rank]  = substr($stats[$rank],0,$pos);
     }
     $details = array ( array ("name"=>"director","func"=>"get_director"),
                        array ("name"=>"composer","func"=>"get_music"),
                        array ("name"=>"category","func"=>"get_category")
                      );
     foreach($details as $value) {
       for ($i=1;$i<4;++$i) {
         $sperson = "rank_" . $value["name"] . "_" . $i;
	 $count   = $sperson . "_count";
         $person  = $stats[$sperson];
         $pos = strpos($person," (");
         $person_id = substr($person,0,$pos);
         if (!strlen($person_id)) {
           $stats[$count] = "";
           $stats[$sperson] = "";
           continue;
         }
         $rank = substr($person,$pos+2,strlen($person)-($pos+3));
	 $func = $value["func"];
         $name = $this->$func($person_id);
	 switch($func) {
	   case "get_category" : $stats[$sperson] = $name; break;
	   default             : $stats[$sperson] = $name['fullname']; break;
	 }
	 $stats[$count] = $rank;
       }
     }
     // actors is a bit complicated - we have to consider 5 fields...
     for ($i=1;$i<6;++$i) {
       $id = "actor" . $i . "_id";
       $this->dbquery("SELECT COUNT($id) AS count,$id FROM pvp_video WHERE $id<>0 GROUP BY $id");
       while ( $this->next_record() ) {
         $actor_id         = $this->f("$id");
         ${$id}[$actor_id] = $this->f("count");
       }
     }
     $actors = $pvp->common->array_combine_sums($actor1_id,$actor2_id);
     $actors = $pvp->common->array_combine_sums($actors,$actor3_id);
     $actors = $pvp->common->array_combine_sums($actors,$actor4_id);
     $actors = $pvp->common->array_combine_sums($actors,$actor5_id);
     if (is_array($actors)) {
       arsort($actors);
       $i = 1;
       foreach ($actors as $key=>$value) {
         $name  = $this->get_actor($key);
         $act   = "rank_actor_" . $i;
         $count = $act . "_count";
         $stats[$act]   = $name['fullname'];
         $stats[$count] = $value;
         ++$i;
         if ($i>3) break;
       }
     }
     return $stats;
   }

   ############################################################################
   /** Execute the statements in the passed $array one-by-one, ignore comments
    * @method get_sql
    * @param array sql_array each line containing SQL code
    * @param optional boolean separate_statements separate at each ";" (default:Yes)
    * @return boolean success
    * @version right now only lines starting with a hash mark ("#") are
    *  recognized as comments (plus everything following the semi-colon at
    *  the end of an SQL statement)
    * @todo recognize other SQL comments like "--"
    * @todo handle ";" within field content correctly (and do not assume end
    *  of command here)
    */
   function get_sql($array,$separate_statements=1) {
     $sql   = ""; $ok = 1;
     $lines = count($array);
     for ($i=0;$i<$lines;$i++) {
       $pos  = strpos(" " . trim($array[$i]),"#");
       if ($pos<>1) { // this is no comment line, so we process it
         $sql .= $array[$i];
         $line  = trim($array[$i]);
         if ( ($separate_statements && (strrpos($line,";") +1)==strlen($line)) || empty($line) ) {
           $sql = trim($sql);
           $sql = substr($sql,0,strlen($sql) -1);
           if ( !empty($sql) && !$this->dbquery($sql) ) $ok = 0;
           $sql = "";
         } // end (if semicolon at end of line)
       }
     }
     return $ok;
   } // end get_sql()

   ############################################################################
   /** Interface to get_sql(): reads a file into an array and passes it to
    *  get_sql()
    * @method queryf
    * @param string file name of file containing the SQL code to execute
    * @param string comment description of the actions done by execute
    * @param optional boolean silent wether to (not) output advance information
    * @param optional boolean separate_statements separate at each ";" (default:Yes)
    * @return mixed string failure_reason (when $silent and error), else nothing
    */
   function queryf($file,$comment,$silent=0,$separate_statements=1) {
     if ( !file_exists($file) ) {
       $error = " <LI><SPAN CLASS='error'>$comment failed: missing SQL command file '$file', process stopped.</SPAN></LI>";
       if ($silent) return $error;
       else echo "$error<BR>\n";
       exit;
     }
     $array = file ($file);
     if ( !$array ) {
       $error = " <LI><SPAN CLASS='error'>$comment failed: we have no read permission for SQL command file '$file' (or this file is empty), process stopped.</SPAN></LI>";
       if (!$silent) echo "$error<BR>\n";
       else return $error;
       exit;
     }
     if ( $this->get_sql($array,$separate_statements) ) {
       $error = " <LI><SPAN CLASS='ok'>$comment successful.</SPAN></LI>";
       if (!$silent) echo "$error<BR>\n";
       if ($silent) return TRUE;
     } else {
       $error = " <LI><SPAN CLASS='error'>$comment failed, process stopped.</SPAN></LI>";
       if (!$silent) echo "$error<BR>\n";
       else return $error;
       exit;
     }
   } // end query_f()

 ############################################################################
 # PS-Label Specific Stuff
 ############################################################################

 /** get printer specifics
  * @method get_printer
  * @param optional integer id
  * @return mixed (array of object(s) with printer specifics)
  */
 function get_printer($id="") {
   $query = "SELECT id,name,unit_id,top_offset,left_offset FROM pvp_psprinters";
   if ($id) $query .= " WHERE id=$id";
   $this->dbquery($query);
   while ($this->next_record()) {
     $printer->id   = $this->f('id');
     $printer->name = $this->f('name');
     $printer->unit_id = $this->f('unit_id');
     $printer->top_offset = $this->f('top_offset');
     $printer->left_offset = $this->f('left_offset');
     $printerlist[] = $printer;
     unset($printer); // work around for PHP5 bug always using references here
   }
   return $printerlist;
 }

 /** replace all printers (restore from a backup)
  * @method printerReplace
  * @param array printerlist new list of printers
  * @return boolean success
  */
 function printerReplace($list) {
   if ( !$this->query("TRUNCATE TABLE pvp_psprinters") ) return FALSE;
   $pcount = count($list);
   $errors = 0;
   for ($i=0;$i<$pcount;++$i) {
     $query = "INSERT INTO pvp_psprinters (id,name,unit_id,top_offset,left_offset) "
            . "VALUES (".$list[$i]->id.",'".$list[$i]->name."',"
            . $list[$i]->unit_id.",".$list[$i]->top_offset.","
            . $list[$i]->left_offset.")";
     if (! $this->query($query) ) ++$errors;
   }
   if ($errors) return FALSE;
   return TRUE;
 }

 /** set printer specifics
  * @method set_printer
  * @param optional integer id printerID (if not set, new printer will be added)
  * @param optional string name printer name (if not set, printer will be deleted)
  * @param optional integer unit unit id (default: 0 = pt)
  * @param optional float top_offset top offset (defaults to 0)
  * @param optional float left_offset left offset (defaults to 0)
  * @return boolean success
  */
 function set_printer($id="",$name="",$unit=1,$top_offset=0,$left_offset=0) {
   if (!$id && !$name) return FALSE;
   if (!$name) { $query = "DELETE FROM pvp_psprinters WHERE id=$id"; }
     elseif (!$id) {
       $this->query("SELECT MAX(id) AS maxid FROM pvp_psprinters");
       $this->next_record();
       $id = $this->f('maxid') +1;
       $query = "INSERT INTO pvp_psprinters VALUES ($id,'$name',$unit,$top_offset,$left_offset)";
   } else {
     $query = "UPDATE pvp_psprinters SET name='$name',unit_id=$unit,"
            . "top_offset=$top_offset,left_offset=$left_offset "
            . "WHERE id=$id";
   }
   $rc = $this->dbquery($query);
   if ($rc<0) return FALSE;
   return TRUE;
 }

 /** get available units
  * @method get_units
  * @return mixed (array of id,unit,factor)
  */
 function get_units() {
     $this->query("SELECT id,unit,size FROM pvp_psunits");
     $i=0;
     while ( $this->next_record() ) {
       $units[$i]['id']     = $this->f('id');
       $units[$i]['unit']   = $this->f('unit');
       $units[$i]['factor'] = $this->f('size');
       ++$i;
     }
   return $units;
  }

 /** get available label forms
  * @method get_label_forms
  * @return mixed (array of i:id,i:vendor,i:product)
  */
 function get_label_forms() {
     $this->query("SELECT id,vendor,product FROM pvp_pslabelforms");
     $i=0;
     while ( $this->next_record() ) {
       $label_forms[$i]['product'] = $this->f('product');
       $label_forms[$i]['vendor']  = $this->f('vendor');
       $label_forms[$i]['id']      = $this->f('id');
       ++$i;
     }
   return $label_forms;
  }

 /** get number of rows and columns on sheet for $id
  * @method get_lsheet
  * @return mixed (rows,cols)
  */
 function get_lsheet($id) {
     $query="SELECT rows,cols,type FROM pvp_pslabelforms WHERE id=$id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $lsheet['rows'] = $this->f('rows');
         $lsheet['cols'] = $this->f('cols');
         $lsheet['type'] = $this->f('type');
         return $lsheet;
       }
     }
     return FALSE;
  }

 /** get all print format relevant infos for label form $id
  * @method get_lsheet_info
  * @return mixed ()
  */
 function get_lsheet_info($id,$printer_id) {
     $stat=0;

     $query="SELECT rows,cols,unit_id,h_dist,
     v_dist,width,heigth,leftm,topm,sheet_id 
     FROM pvp_pslabelforms WHERE id=$id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $lsheet['label_rows']  = $this->f('rows');
         $lsheet['label_cols']  = $this->f('cols');
         $lsheet['label_hdist'] = $this->f('h_dist');
         $lsheet['label_vdist'] = $this->f('v_dist');
         $lsheet['label_width'] = $this->f('width');
         $lsheet['label_heigth'] = $this->f('heigth');
         $lsheet['left_margin'] = $this->f('leftm');
         $lsheet['top_margin']  = $this->f('topm');
         $label_unit_id = $this->f('unit_id');
         $lsheet_sheet_id = $this->f('sheet_id');
	 $stat++;
       }
       $stat++;
     }

     $query="SELECT size FROM pvp_psunits WHERE id=$label_unit_id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $lsheet['label_unit_size'] = $this->f('size');
         $stat++;
       }
       $stat++;
     }

     $query="SELECT name,unit_id,width,length FROM pvp_pssheets WHERE id=$lsheet_sheet_id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $sheet_unit_id = $this->f('unit_id');
	 $lsheet['sheet_papersize'] = $this->f('name');
	 $lsheet['sheet_length']    = $this->f('length');
	 $lsheet['sheet_width']     = $this->f('width');
         ++$stat;
       }
       ++$stat;
     }

     $query="SELECT size FROM pvp_psunits WHERE id=$sheet_unit_id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $lsheet['sheet_unit_size'] = $this->f('size');
         $stat++;
       }
       $stat++;
     }

     $query="SELECT unit_id,top_offset,left_offset
     FROM pvp_psprinters WHERE id=$printer_id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $lsheet['pr_left'] = $this->f('left_offset');
         $lsheet['pr_top'] = $this->f('top_offset');
         $printer_unit_id = $this->f('unit_id');
         ++$stat;
       }
       ++$stat;
     }

     $query="SELECT size FROM pvp_psunits WHERE id=$printer_unit_id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $lsheet['pr_unit_size'] = $this->f('size');
         ++$stat;
       }
       ++$stat;
     }

     if ($stat) return $lsheet;
     return FALSE;
  }

 /** get eps template description for $type
  * @method get_epstemplates
  * @param integer type_id
  * @param optional integer pack_id restrict resultset by labelpack id
  * @return array [0..n] of array [id,description,filename] (filename w/o extension)
  */
 function get_epstemplates($type,$pack="") {
   $query="SELECT id,description,eps_filename filename FROM pvp_epstemplates WHERE type=$type";
   if ($pack!=="") $query.=" AND pack_id=$pack";
   $query.=" ORDER BY description";
   if ( $this->dbquery($query) ) {
     $i=0;
     while ( $this->next_record() ) {
       $eps_template[$i]['id'] = $this->f('id');
       $eps_template[$i]['description'] = $this->f('description');
       $eps_template[$i]['filename'] = substr($this->f('filename'),0,strlen($this->f('filename'))-4);
       ++$i;
     }
     return $eps_template;
   }
   return FALSE;
 }

 /** get eps image reference for $id
  * @method get_epsimage
  * @return mixed (eps_file,ps_file,llx,lly,urx,ury)
  */
 function get_epsimage($id) {
     $query="SELECT eps_filename,ps_filename,llx,lly,urx,ury
     FROM pvp_epstemplates WHERE id=$id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $eps_image['eps'] = $this->f('eps_filename');
         $eps_image['ps']  = $this->f('ps_filename');
         $eps_image['llx'] = $this->f('llx');
         $eps_image['lly'] = $this->f('lly');
         $eps_image['urx'] = $this->f('urx');
         $eps_image['ury'] = $this->f('ury');
       }
       return $eps_image;
     }
     return FALSE;
  }

 /** get eps template types
  * @method get_labeltypes
  * @return array labeltypes array of objects
  */
 function get_labeltypes() {
   $query = "SELECT id,type,description FROM pvp_pslabelforms";
   $this->dbquery($query);
   while ( $this->next_record() ) {
     $type->id = $this->f('id');
     $type->type = $this->f('type');
     $type->desc = $this->f('description');
     $label[] = $type;
     unset($type);
   }
   return $label;
 }

 /** get complete eps template description list
  * @method get_pstemplates
  * @param optional integer id eps template id
  * @param optional integer pack_id ID of label pack
  * @param optional integer start for limit queries
  * @return array templates array of objects
  */
 function get_pstemplates($id="",$pack_id="",$start="") {
   $this->query("SELECT type,description FROM pvp_pslabelforms");
   while ($this->next_record()) {
     $typedesc[$this->f('type')] = $this->f('description');
   }
   $query = "SELECT e.id,e.type,e.description,e.eps_filename,e.ps_filename,"
          . "e.llx,e.lly,e.urx,e.ury, p.name AS packname "
          . "FROM pvp_epstemplates e,pvp_pspacks p "
          . "WHERE e.pack_id=p.id";
   if ($id) $query .= " AND e.id=$id";
   elseif ($pack_id) $query .= " AND pack_id=$pack_id";
   $query .= " ORDER BY e.description";
   if ($start==="") { $this->dbquery($query); }
     else { $totals = $this->lim_query($query,$start); }
   while ( $this->next_record() ) {
     $tpl->id = $this->f('id');
     $tpl->type_id = $this->f('type');
     $tpl->packname = $this->f('packname');
     $tpl->type_desc = $typedesc[$tpl->type_id];
     $tpl->desc = $this->f('description');
     $tpl->eps_file = $this->f('eps_filename');
     $tpl->ps_file = $this->f('ps_filename');
     $tpl->llx = $this->f('llx');
     $tpl->lly = $this->f('lly');
     $tpl->urx = $this->f('urx');
     $tpl->ury = $this->f('ury');
     $template[] = $tpl;
     unset($tpl);
   }
   if (isset($totals)) $template['totals'] = $totals;
   return $template;
 }

 /** set ps template details
  * @method set_pstemplate
  * @param mixed pstemplate integer id to delete or object to update
  * @return boolean success
  */
 function set_pstemplate($ps) {
   if (is_int($ps)) {
     $query = "DELETE FROM pvp_epstemplates WHERE id=$ps";
   } elseif ($ps->id) {
     $id    = $ps->id;
     $query = "UPDATE pvp_epstemplates SET type=".$ps->type_id.",description='"
            . $ps->desc."',eps_filename='".$ps->eps_file."',ps_filename='"
            . $ps->ps_file."',llx=".$ps->llx.",lly=".$ps->lly.",urx="
            . $ps->urx.",ury=".$ps->ury." WHERE id=$id";
   } else {
     $this->query("SELECT MAX(id) AS maxid FROM pvp_epstemplates");
     $this->next_record();
     $id = $this->f('maxid') +1;
     $query = "INSERT INTO pvp_epstemplates (id,type,description,eps_filename,"
            . "ps_filename,llx,lly,urx,ury) VALUES ($id,"
            . $ps->type_id.",'".$ps->desc."','".$ps->eps_file."','"
            . $ps->ps_file."',".$ps->llx.",".$ps->lly.",".$ps->urx.",".$ps->ury.")";
   }
   $this->dbquery($query);
   if ($this->affected_rows()<0) return FALSE;
   return $id;
 }

 #=============================================[ PSLabel Pack Management ]===

 /** get a PSLabel Pack by name
  * @method get_pspack_by_name
  * @param string sname sname of the pack
  * @return array packinfo
  */
 function get_pspack_by_name($sname) {
   $this->dbquery("SELECT id,rev,sname,name,descript,creator FROM pvp_pspacks WHERE sname='$sname'");
   $this->next_record();
   $fields = array("id","rev","sname","name","descript","creator");
   foreach ($fields as $f) {
     $pack[$f] = $this->f($f);
   }
   return $pack;
 }

 /** get list of PSLabel Packs
  * @method get_pspacks
  * @param optional integer id
  * @param optional integer start for limit queries
  * @return array pspacks
  */
 function get_pspacks($id="",$start="") {
   $query = "SELECT id,rev,sname,name,descript,creator FROM pvp_pspacks";
   if ($id!="") $query .= " WHERE id=$id";
   else $query .= " ORDER BY name";
   if ($start==="") { $this->dbquery($query); }
     else { $totals = $this->lim_query($query,$start); }
   $fields = array("id","rev","sname","name","descript","creator");
   while ($this->next_record()) {
     foreach ($fields as $f) {
       $t[$f] = $this->f($f);
     }
     $pspacks[] = $t;
   }
   if ($id!="") return $pspacks[0];
   if (isset($totals)) $pspacks['totals'] = $totals;
   return $pspacks;
 }

 /** Register a PSLabel Pack with the DB
  * @method register_pslabel_pack
  * @param object pack PackInfo (properties: rev,sname,name,descript,creator)
  * @return integer pack_id
  */
 function register_pslabel_pack($pack) {
   if (!is_int($pack->rev) || empty($pack->rev) || empty($pack->sname)) return FALSE;
   $this->dbquery("SELECT id FROM pvp_pspacks WHERE sname='".$pack->sname."'");
   $this->next_record();
   $pack_id = $this->f('id');
   if ($pack_id) {
     $query = "UPDATE pvp_pspacks SET rev=".$pack->rev.",name='".$pack->name
            . "',descript='".$pack->descript."',creator='".$pack_creator
            . "' WHERE id=$pack_id";
     $this->dbquery($query);
   } else {
     $query = "INSERT INTO pvp_pspacks (rev,sname,name,descript,creator)"
            . " VALUES (".$pack->rev.",'".$pack->sname."','".$pack->name
            . "','".$pack->descript."','".$pack->creator."')";
     $this->dbquery($query);
     $this->dbquery("SELECT id FROM pvp_pspacks WHERE sname='".$pack->sname."'");
     $this->next_record();
     $pack_id = $this->f('id');
   }
   return $pack_id;
 }

 /** DeRegister a PSLabel Pack from the DB
  * @method deregister_pslabel_pack
  * @param integer pack_id ID of the label pack
  * @param optional boolean cascade default TRUE delete associated labels as well
  * @return boolean success
  */
 function deregister_pslabel_pack($pack_id,$cascade=TRUE) {
   if (empty($pack_id) || !is_numeric($pack_id)) return FALSE;
   if ($this->dbquery("DELETE FROM pvp_pspacks WHERE id=$pack_id")) {
     if ($cascade) return $this->dbquery("DELETE FROM pvp_epstemplates WHERE pack_id=$pack_id");
     return TRUE;
   } else return FALSE;
 }

 /** Get list of eps_files for a given PSLabel Pack
  * @method get_pspack_epsfiles
  * @param integer pack_id ID of the PSLabel Pack
  * @return array files
  */
 function get_pspack_epsfiles($pack_id) {
   $files = array();
   $this->dbquery("SELECT eps_filename FROM pvp_epstemplates WHERE pack_id=$pack_id");
   while ($this->next_record()) {
     $files[] = $this->f('eps_filename');
   }
   return $files;
 }

 /** Register a PSLabel with the DB
  * @method register_pslabel
  * @param object label (properties: pack_id,type,description,eps_filename,ps_filename,llx,lly,urx,ury)
  * @brief This method can be used to check whether a label is already registered:
  *        Simply leave at least one of the properties llx,lly,urx,ury empty. If
  *        this method still returns TRUE, the label is already registered.
  * @return boolean success
  */
 function register_pslabel($label) {
   // first we check whether the label is already registered
   if (! (is_int($label->type) && is_int($label->pack_id)) ) return FALSE;
   if (empty($label->eps_filename) || empty($label->ps_filename)) return FALSE;
   $query = "SELECT COUNT(*) AS zahl FROM pvp_epstemplates"
          . " WHERE pack_id=".$label->pack_id
          . "   AND type=".$label->type
          . "   AND eps_filename='".$label->eps_filename
          . "'  AND ps_filename='".$label->ps_filename."'";
   $this->query($query);
   $this->next_record();
   if ($this->f('zahl')>0) return TRUE;
   // label was not yet registered - make sure the entry will be valid
   if (! (is_int($label->llx) && is_int($label->lly)
       && is_int($label->urx) && is_int($label->ury)) )
      return FALSE;
   if (empty($label->pack_id) || empty($label->type) || empty($label->description)
      || (empty($label->llx) && $label->llx!=0) || (empty($label->lly) && $label->lly!=0)
      || (empty($label->urx) && $label->urx!=0) || (empty($label->ury) && $label->ury!=0))
      return FALSE;
   $query = "INSERT INTO pvp_epstemplates (type, pack_id, description,"
          . " eps_filename, ps_filename, llx, lly, urx, ury) VALUES ("
          . $label->type.",".$label->pack_id.",'".$label->description."','"
          . $label->eps_filename."','".$label->ps_filename."',"
          . $label->llx.",".$label->lly.",".$label->urx.",".$label->ury.")";
   return $this->dbquery($query);
 }

 /** DeRegister a PSLabel from the DB
  * @method deregister_pslabel
  * @param integer id LabelID
  * @return boolean success
  */
 function deregister_pslabel($id) {
   if (empty($id) || !is_int($id)) return FALSE;
   return $this->dbquery("DELETE FROM pvp_epstemplates WHERE id=$id");
 }

 ############################################################################
 # Misc Stuff
 ############################################################################

 /** Check whether an image file is refered to from DB
  * @method image_is_refered
  * @param string img
  * @return boolean
  */
 function image_is_refered($img) {
   $query = "SELECT count(id) AS refs FROM pvp_video WHERE comment LIKE '%$img%'";
   $this->query($query);
   $this->next_record();
   if ($this->f('refs')) return TRUE;
   return FALSE;
 }

 } // end class sql

 $db = new sql;

 ##############################################################################
 /** Execute a query and provide debug output
  * @package Api
  * @function dbquery
  * @param string query SQL statement
  * @return boolean success
  * @deprecated this is only a placeholder for backward compatibility.
  *  use sql::dbquery() directly instead.
  */
 function dbquery($query) {
   GLOBAL $db;
   return $db->dbquery($query);
 }
 /** Insert a person into DB
  * @package Api
  * @function insert_person
  * @param string person stafftype
  * @param string query SQL query for SELECT statement
  * @param string sub_query SQL query for INSERT statement
  * @param optional string name family name of person
  * @param optional string fname first name of person
  * @param optional string imdb_id
  * @return integer id (person_id)
  * @deprecated this is only a placeholder for backward compatibility.
  *  use sql::insert_person() directly instead.
  */
 function insert_person($person,$query,$sub_query,$name="",$fname="",$imdb_id="") {
   // only called from inc/sql_set_persons.inc
   GLOBAL $db;
   return $db->insert_person($person,$query,$sub_query,$name,$fname,$imdb_id);
 }
 /** Read a file into an array and passes it to sql::get_sql()
  * @package Api
  * @function queryf
  * @param string file name of file containing the SQL code to execute
  * @param string comment description of the actions done by execute
  * @param optional boolean silent wether to (not) output advance information
  * @deprecated this is only a placeholder for backward compatibility.
  *  use sql::queryf() directly instead.
  */
 function queryf($file,$comment,$silent=0) { // only used in setup/*
   GLOBAL $db;
   $db->queryf($file,$comment,$silent);
 }

?>