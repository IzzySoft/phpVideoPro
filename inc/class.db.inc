<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
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
  * @author Izzy (izzysoft@qumran.org)
  * @copyright (c) 2001-2004 by Itzchak Rehberg and IzzySoft
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
     $this->DB_Sql; // constructor of base class needs explicit call
     $this->limit();
   }

   ############################################################################
   # common stuff
   ############################################################################
   /** setup sql clause to limit result set (depending on database type)
    * @class sql
    * @method limit
    * @param optional integer start
    * @return string limit SQL limit clause for the configured database type
    */
   function limit($start=0) {
     GLOBAL $pvp;
     switch($pvp->config->db->type) {
       case "mysql" : $this->limit = " LIMIT $start," . $pvp->preferences->get("display_limit");
                      break;
       case "pgsql" : $this->limit = " LIMIT " . $pvp->preferences->get("display_limit") . "OFFSET $start";
                      break;
       default      : $this->limit = ""; break;
     }
     return $this->limit;
   }

   /** replace empty values within SQL queries by NULL statement to keep query
    * syntactically correct
    * @class sql
    * @method clean_query
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

   /** Query db and provide debug output
    * @class sql
    * @method dbquery
    * *variable array colors
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
    * @class sql
    * @method lim_query
    * @param string query SQL statement to execute
    * @param optional integer start
    * @return integer totals (result set count)
    */
   function lim_query($query,$start=0) {
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
    * @class sql
    * @method delete_row
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
   /** Get installed languages (both available and unavailable)
    * @class sql
    * @method get_installedlang
    * @return array language names (lang)
    */
   function get_installedlang() {
     $this->dbquery("SELECT distinct lang FROM lang");
     while ( $this->next_record() ) {
       $lang[] = $this->f('lang');
     }
     $langs = "'" . implode("','",$lang) . "'";
     $this->dbquery("SELECT lang_id FROM languages WHERE lang_id IN ($langs) ORDER BY lang_name");
     while ( $this->next_record() ) {
       $langres[] = $this->f('lang_id');
     }
     return $langres;
   }

   /** Get (un)available|all languages
    * @class sql
    * @method get_languages
    * @param optional integer avail available (1) or unavailable(0); default: both
    * @return array languages (id,name, charset, avail)
    */
   function get_languages($avail="") {
     switch ($avail) {
       case "0" : $where = "WHERE available='no'"; break;
       case "1" : $where = "WHERE available='yes'"; break;
     }
     $this->dbquery("SELECT lang_id,lang_name,charset,available FROM languages $where ORDER BY lang_name");
     $i=0;
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
    * @class sql
    * @method lang_available
    * @param string lang language id
    * @param optional integer avail defaults to "1"
    */
   function lang_available($lang,$avail=1) {
     if ($avail) $this->dbquery("UPDATE languages SET available='yes' WHERE lang_id='$lang'");
     else $this->dbquery("UPDATE languages SET available='no' WHERE lang_id='$lang'");
   }

   /** delete translations for a specific language
    * @class sql
    * @method delete_translations
    * @param string lang language id
    */
   function delete_translations($lang) {
     $this->dbquery("DELETE FROM lang WHERE lang='$lang'");
   }

   /** Get all translations and return them as array
    * @class sql
    * @method get_translations
    * @param string pref_lang language id of preferred language
    * @return array translations (msg_id:=trans(msg_id))
    */
   function get_translations($pref_lang) {
     $def_lang = "en";
     $this->dbquery("SELECT message_id,content FROM lang WHERE lang='$def_lang'");
     while ( $this->next_record() ) { // initiate with fall-back
       $msg_id         = $this->f('message_id');
       $trans[$msg_id] = stripslashes($this->f('content'));
     }
     if ($pref_lang != $def_lang) {
       $this->dbquery("SELECT message_id,content FROM lang WHERE lang='$pref_lang'");
       while ( $this->next_record() ) { // overwrite with preferred (if exists)
         $msg_id         = $this->f('message_id');
         $trans[$msg_id] = stripslashes($this->f('content'));
       }
     }
     return $trans;
   }

   /** Set a translation: if $trans is empty, translation for the specified
    *  language and message $id will be removed. Otherwise the new translation
    *  will be updated or inserted
    * @class sql
    * @method set_translation
    * @param string id translation identifier
    * @param string trans translated string
    * @param string lang language of the translation
    * @return boolean success
    */
   function set_translation($id,$trans,$lang) {
     if (!$trans) { // remove translation
       $this->query("DELETE FROM lang WHERE message_id='$id' AND lang='$lang'");
     } else {
       if ( ( bool ) !ini_get( 'magic_quotes_gpc' ) ) {
         $trans = addslashes($trans);
       }
       $this->query("SELECT * FROM lang WHERE message_id='$id' AND lang='$lang'");
       if ( $this->next_record() ) {
         $this->query("UPDATE lang SET content='$trans' WHERE lang='$lang' AND message_id='$id'");
       } else {
         $this->query("INSERT INTO lang (message_id,lang,content) VALUES ('$id','$lang','$trans')");
       }
     }
     return $this->affected_rows();
   }

   /** Get translations for the specified language only (for admin)
    * @class sql
    * @method get_singletrans
    * @param string lang language to retrieve for
    * @param optional integer start (for lim_query)
    * @param optional string msgID single translation to catch
    * @return object translations (msgID = translation, xlist[] of msgIDs)
    */
   function get_singletrans($lang,$start="",$msg="") {
     $query = "SELECT message_id,content,comment FROM lang WHERE lang='$lang'";
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
     if ($totals) $trans[totals] = $totals;
     $trans["xlist"] = $list;
     return $trans;
   }

   ############################################################################
   # options
   ############################################################################
   /** Get list of options
    * @class sql
    * @method get_options
    * @param optional string name name of option to retrieve values for
    * @return array array of option arrays ($list[name][$i]=value)
    */
   function get_options($name="") {
     $query = "SELECT name,value"
            . "  FROM pvp_options";
     if (strlen($name)) { $query .= " WHERE name='$name'"; }
     $this->query($query);
     while ( $this->next_record() ) {
       $optname = $this->f('name');
       $list["$optname"][] = $this->f('value');
     }
     return $list;
   }

   ############################################################################
   # preferences
   ############################################################################
   /** Get preferences from DB (used by class preferences; use that class to
    *  obtain preference settings!)
    * @class sql
    * @method get_preferences
    * @param string name preference name
    * @return mixed setting of requested preference
    * @see preferences::filter
    */
   function get_preferences($name) {
     $this->query("SELECT value FROM preferences WHERE name='$name'");
     if ( $this->next_record() ) {
       return $this->f('value');
     } else {
       return "";
     }
   }

   /** Set preferences in DB (if exist: update, otherwise insert)
    *  Used by class preferences: use that class to modify settings!
    * @class sql
    * @method set_preferences
    * @param string name
    * @param mixed value
    * @see preferences::filter
    */
   function set_preferences($name,$value) {
     GLOBAL $pvp;
     $value = $pvp->common->safeinput($value);
     $this->query("SELECT value FROM preferences WHERE name='$name'");
     if ( $this->next_record() ) {
       $this->dbquery("UPDATE preferences SET value='$value' WHERE name='$name'");
     } else {
       $this->dbquery("INSERT INTO preferences (name,value) VALUES ('$name','$value')");
     }
   }

   /** Remove preferences from DB
    *  Used by class preferences: use that class to modify settings!
    * @class sql
    * @method unset_preferences
    * @param string name
    * @see preferences::filter
    */
   function unset_preferences($name) {
     $this->dbquery("DELETE FROM preferences WHERE name='filter'");
   }

   ############################################################################
   # configuration
   ############################################################################
   /** Get some config value
    * @class sql
    * @method get_config
    * @param string name config var's name
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

   /** Set some config value
    * @class sql
    * @method set_config
    * @param string name config var's name
    */
   function set_config($name,$value) {
     GLOBAL $pvp;
     $value = $pvp->common->safeinput($value);
     $this->query("SELECT value FROM pvp_config WHERE name='$name'");
     if ( $this->next_record() ) {
       $this->dbquery("UPDATE pvp_config SET value='$value' WHERE name='$name'");
     } else {
       $this->dbquery("INSERT INTO pvp_config (name,value) VALUES ('$name','$value')");
     }
   }

   ############################################################################
   # Session managment
   ############################################################################
   /** Create a session
    * @class sql
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
    * @class sql
    * @method end_session
    * @param string sess_id
    * @param string ip
    * @param timestamp end
    */
   function end_session($sess_id,$ip,$end) {
     $this->query("UPDATE pvp_sessions SET ended='$end' WHERE id='$sess_id' AND ip='$ip'");
   }

   /** Verify (and update) a session
    * @class sql
    * @method verify_session
    * @param string id session-id
    * @param string ip remote-ip
    * @return integer user-id
    */
   function verify_session($id,$ip) {
     GLOBAL $pvp;
     $query = "SELECT user_id FROM pvp_sessions "
            . "WHERE id='$id' AND ip='$ip' AND ended IS NULL";
     if ($pvp->config->session_purgetime) {
       $dla = time()-$pvp->config->session_purgetime;
       $query .= " AND dla>$dla";
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
    * @class sql
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
     if ($totals) $list[totals] = $totals;
     return $list;
   }

   /** remove a session from DB
    * @class sql
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
    * @class sql
    * @method get_users
    * @param optional integer user_id
    * @return mixed array users (array of objects;
    *  properties: id,login,pwd (md5 hash), admin,browse,ins,upd,del, comment)
    *  or FALSE if no users in DB
    */
   function get_users($user_id=0) {
     $query = "SELECT id,login,pwd,admin,browse,ins,upd,del,comment FROM pvp_users";
     if ($user_id) $query .= " WHERE id=$user_id";
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
     if ($user_id && $i) {
       return $users[0];
     }
     if ($i) { return $users; } else { return FALSE; }
   }

   /** Get login data
    * @class sql
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
    * @class sql
    * @method set_user
    * @param object user single user object (as defined as element of userlist array)
    * @return boolean success
    */
   function set_user($user) {
     GLOBAL $pvp;
     $login   = $pvp->common->safeinput($user->login);
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
    * @class sql
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
    * @class sql
    * @method del_user
    * @param integer id id of user to delete
    * @return boolean success
    */
   function del_user($id) {
     $this->dbquery("DELETE FROM pvp_users WHERE id=$id");
     $this->dbquery($query);
     if ( $this->affected_rows() < 0 ) return FALSE;
     return TRUE;
   }

   ############################################################################
   # people and their names
   ############################################################################
   /** Format a names array (private! just an internal helper func)
    * @class sql
    * @method format_name
    * @param array name
    * return array name
    */
   function format_name($name) {
     $name[name] = $name[reverse] = trim($name[name]);
     $name[firstname] = $name[fullname] = trim($name[firstname]);
     if (strlen($name[fullname])) {
       if (strlen($name[firstname])) $name[fullname] .= " " . $name[name];
     } else {
       $name[fullname] = $name[name];
     }
     if (strlen($name[reverse])) {
       if (strlen($name[firstname])) $name[reverse] .= ", " . $name[firstname];
     } else {
       $name[reverse] = $name[firstname];
     }
     return $name;
   }

   /** Get all data for a person and return it as array (privat! internal helper)
    * @class sql
    * @method get_person
    * @param integer id person id
    * @param string table tablename (actors, directors, etc)
    * @return array person data (formatted by sql::format_name)
    */
   function get_person($id,$table) {
     if ($id) {
       $this->dbquery("SELECT firstname,name FROM $table WHERE id=$id");
       if ( $this->next_record() ) {
         $person[id]   = trim($id);
         $person[name] = $this->f('name');
         $person[firstname] = $this->f('firstname');
	 $person = $this->format_name($person);
       } else {
         $person[name] = $person[firstname] = $person[fullname] = $person[reverse] = "";
       }
     } else {
       $this->dbquery("SELECT id,firstname,name FROM $table");
       $i=0;
       while ( $this->next_record() ) {
         $person[$i][id]   = $this->f('id');
         $person[$i][name] = $this->f('name');
         $person[$i][firstname] = $this->f('firstname');
	 $person[$i] = $this->format_name($person[$i]);
	 ++$i;
       }
     }
     return $person;
   }

   /** Get all data for an actor and return it as array (wrapper to get_person)
    * @class sql
    * @method get_actor
    * @param integer id actor id
    * @return array actor data (formatted by format_name)
    */
   function get_actor($id) {
     return $this->get_person($id,"actors");
   }

   /** Get all data for a director and return it as array (wrapper to get_person)
    * @class sql
    * @method get_director
    * @param integer id director id
    * @return array director data (formatted by format_name)
    */
   function get_director($id) {
     return $this->get_person($id,"directors");
   }

   /** Get all data for a componist and return it as array (wrapper to get_person)
    * @class sql
    * @method get_music
    * @param integer id componist's id
    * @return array componist's data (formatted by format_name)
    */
   function get_music($id) {
     return $this->get_person($id,"music");
   }

   /** Get distinct staff ids from video table and return them as array
    * @class sql
    * @method get_distinct_staffids
    * @param string field name of id field to search
    * @return array array of ids
    */
   function get_distinct_staffids($field) {
     $this->dbquery("SELECT DISTINCT $field FROM video");
     while ( $this->next_record() ) {
       $id[] = $this->f("$field");
     }
     return $id;
   }

   /** Setup the orphans array (helper to get_orphaned_staff)
    * @class sql
    * @method setup_orphan
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
    *  entry in one of the staff tables, but the video table doesn't refer to them
    * @class sql
    * @method get_orphaned_staff
    * @return mixed array of orphanes or FALSE
    * @version the array has the format array[$i]->$item, where $item is one of
    *  stafftype,id,name,firstname - id being the PK to the staff table
    */
   function get_orphaned_staff() {
     $id = $this->get_distinct_staffids("director_id");
     $query = "SELECT id,name,firstname FROM directors"
            . " WHERE id NOT IN (" . implode(",",$id) . ")";
     $this->dbquery($query);
     while ( $this->next_record() ) {
       $orphan[] = $this->setup_orphan("director_person",$this->f('id'),$this->f('name'),$this->f('firstname'));
     }
     $id = $this->get_distinct_staffids("music_id");
     $query = "SELECT id,name,firstname FROM music"
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
     $query = "SELECT id,name,firstname FROM actors"
            . " WHERE id NOT IN (" . implode(",",$id) . ")";
     $this->dbquery($query);
     while ( $this->next_record() ) {
       $orphan[] = $this->setup_orphan("actor",$this->f('id'),$this->f('name'),$this->f('firstname'));
     }
     return $orphan;
   }

   /** Delete an actor from DB
    * @class sql
    * @method delete_actor
    * @param mixed id either integer (id) or string (comma separated list of ids)
    * @return boolean success
    */
   function delete_actor($id) {
     return $this->delete_row("actors",$id);
   }

   /** Delete an director from DB
    * @class sql
    * @method delete_director
    * @param mixed id either integer (id) or string (comma separated list of ids)
    * @return boolean success
    */
   function delete_director($id) {
     return $this->delete_row("directors",$id);
   }

   /** Delete an composer from DB
    * @class sql
    * @method delete_composer
    * @param mixed id either integer (id) or string (comma separated list of ids)
    * @return boolean success
    */
   function delete_composer($id) {
     return $this->delete_row("music",$id);
   }

   ############################################################################
   # categories
   ############################################################################
   /** Get a category's data
    * @class sql
    * @method get_category
    * @param optional integer id category id
    * @param optional string order subclause for ORDER BY
    * @return mixed string(catname) or array of categories (id,name,internal name)
    */
   function get_category($id="",$order="") {
     if ($id) {
       $this->query("SELECT name FROM cat WHERE id=$id");
       if ( $this->next_record() ) {
         return lang(trim($this->f('name')));
       } else {
         return "";
       }
     } else {
       if ($order=="") {
         $this->query("SELECT id,name FROM cat");
       } else {
         $this->query("SELECT id,name FROM cat ORDER BY $order");
       }
       $i=0;
       while ( $this->next_record() ) {
         $cat[$i][id]   = $this->f('id');
         $cat[$i][name] = lang($this->f('name'));
	 $cat[$i][internal] = $this->f('name');
	 ++$i;
       }
       return $cat;
     }
   }

   /** update a category
    * @class sql
    * @method update_category
    * @param integer id category's id
    * @param string name category's name
    * @return boolean success
    */
   function update_category($id,$name) {
     GLOBAL $pvp;
     $name = $pvp->common->safeinput($name);
     $this->dbquery("UPDATE cat SET name='$name' WHERE id=$id");
     if ( $this->affected_rows() < 0 ) return FALSE;
     return TRUE;
   }

   /** add a category
    * @class sql
    * @method add_category
    * @param string name
    * @return boolean success
    */
   function add_category($name) {
     GLOBAL $pvp;
     $name = $pvp->common->safeinput($name);
     $this->dbquery("INSERT INTO cat (name) VALUES ('$name')");
     return $this->affected_rows();
   }

   /** remove a category
    * @class sql
    * @method delete_category
    * @param integer id category ID (PK of table)
    * @return boolean success
    */
   function delete_category($id) {
     $this->dbquery("DELETE FROM cat WHERE id=$id");
     return $this->affected_rows();
   }

   ############################################################################
   # technical data
   ############################################################################
   /** Get audio/video data and return it as array (privat! internal helper)
    * @class sql
    * @method get_av
    * @param integer id ID of required data set
    * @param string table table name
    * @return array av (name,sname if id!="", i:id,i:name,i:sname otherwise)
    */
   function get_av($id,$table) {
     if ($id=="") {
       $this->query("SELECT id,name,sname FROM $table");
       $i=0;
       while ( $this->next_record() ) {
         $av[$i][id]    = $this->f('id');
	 $av[$i][name]  = $this->f('name');
	 $av[$i][sname] = $this->f('sname');
	 ++$i;
       }
     } else {
       $this->query("SELECT name,sname FROM $table WHERE id=$id");
       if ( $this->next_record() ) {
         $av[name]  = $this->f('name');
         $av[sname] = $this->f('sname');
       } else {
         $av[name] = $av[sname] = "";
       }
     }
     return $av;
   }

   /** update technical audio/video data
    * @class sql
    * @method set_av
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
    * @class sql
    * @method get_pict
    * @param optional integer id
    * @return array (name,sname if id!="", i:id,i:name,i:sname otherwise)
    */
   function get_pict($id="") {
     return $this->get_av($id,"pict");
   }

   /** update pict data (wrapper to set_av)
    * @class sql
    * @method set_pict
    * @param string name
    * @param string sname
    * @param optional integer id
    * @see set_av()
    */
   function set_pict($name,$sname,$id="") {
     return $this->set_av("pict",$name,$sname,$id);
   }

   /** Get all color data and return it as array (wrapper to get_av)
    * @class sql
    * @method get_color
    * @param optional integer id
    * @return array (name,sname if id!="", i:id,i:name,i:sname otherwise)
    */
   function get_color($id="") {
     return $this->get_av($id,"colors");
   }

   /** update color data (wrapper to set_av)
    * @class sql
    * @method set_color
    * @param string name
    * @param string sname
    * @param optional integer id
    * @see set_av()
    */
   function set_color($name,$sname,$id="") {
     return $this->set_av("colors",$name,$sname,$id);
   }

   /** Get all tone data and return it as array (wrapper to get_av)
    * @class sql
    * @method get_tone
    * @param optional integer id
    * @return array (name,sname if id!="", i:id,i:name,i:sname otherwise)
    */
   function get_tone($id="") {
     return $this->get_av($id,"tone");
   }

   /** update tone data (wrapper to set_av)
    * @class sql
    * @method set_tone
    * @param string name
    * @param string sname
    * @param optional integer id
    * @see set_av()
    */
   function set_tone($name,$sname,$id="") {
     return $this->set_av("tone",$name,$sname,$id);
   }

   /** get data for commercials
    * @class sql
    * @method get_commercials
    * @param optional integer id
    * @return mixed (name if id!="", array of i:id,i:name otherwise)
    */
   function get_commercials($id="") {
     if ($id=="") {
       $this->query("SELECT id,name FROM commercials");
       $i=0;
       while ( $this->next_record() ) {
         $commercials[$i][name] = lang($this->f('name'));
	 $commercials[$i][id]   = $this->f('id');
         ++$i;
       }
     } else {
       $this->query("SELECT name FROM commercials WHERE id=$id");
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
    * @class sql
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
     $this->dbquery("SELECT COUNT(id) AS ref FROM video $restrict");
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
    * @class sql
    * @method drop_all_movies
    * @return boolean success
    */
   function drop_all_movies() {
     if (!$this->query("DELETE FROM video")) return FALSE;
     if (!$this->query("DELETE FROM cass")) return FALSE;
     if (!$this->query("DELETE FROM music")) return FALSE;
     if (!$this->query("DELETE FROM directors")) return FALSE;
     if (!$this->query("DELETE FROM actors")) return FALSE;
   }

   /** Get movie ids
    * @class sql
    * @method get_movieid
    * @param integer mtype_id media type id
    * @param integer cass_id media number
    * @param optional integer part movie number on medium
    * @return mixed either id (integer) or array of IDs
    */
   function get_movieid($mtype_id,$cass_id,$part="") {
     $query = "SELECT id FROM video WHERE mtype_id=$mtype_id AND cass_id=$cass_id";
     if ($part=="") {
       $query .= " ORDER BY part";
       $this->query($query);
       while( $this->next_record() ) {
         $id[] = $this->f('id');
       }
       return $id;
     } else {
       $this->query($query . " AND part=$part");
       $this->next_record();
       return $this->f('id');
     }
   }

   /** Retrieve a list of all movie ids (unfiltered)
    *  Needed for the backup procedure
    * @class sql
    * @method get_movieids_all
    * @return array id_list
    */
   function get_movieids_all() {
     $query = "SELECT id FROM video";
     $this->dbquery($query);
     while ($this->next_record()) {
       $list[] = $this->f('id');
     }
     return $list;
   }

   /** Get all data for a movie entry and return it as array
    * @class sql
    * @method get_movie
    * @param integer id movie id
    * @return array array with detailled movie information
    * @version array description:<pre>
    *  Media data: mtype_id, mtype, mtype_short, cass_id, part,
    *              previous, next (see get_preventry/get_nextentry)
    *  Tech  data: color, color_short, color_id, tone, tone_short, tone_id,
    *              pict, pict_short, pict_id, commercials, commercials_id,
    *              lp, label
    *  Movie data: title, length, country, year, counter1, counter2, aq_date
    *              source, fsk, comment, catX / catX_id (1..3), comment
    *  Staff data: director_list, music_list, actorX_list (where X is 1..5);
    *              director_id, music_id, actorX_id (where X is 1..5);
    *              director, music and actorX as fullname (see format_name);
    *              director_,music_ and actorX_ as array (see format_name);
    *              with _rev as reverse name (name, firstname);
    *              actors, actors12, actors35 as list of actorX</pre>
    */
   function get_movie($id="") {
     if ($id) $where = " WHERE video.id=$id";
     $query = "SELECT title,length,country,year,counter1,counter2,aq_date,source,"
            . "director_id,director_list,music_id,cat1_id,cat2_id,cat3_id,"
	    . "actor1_id,actor2_id,actor3_id,actor4_id,actor5_id,actor1_list,"
	    . "actor2_list,actor3_list,actor4_list,actor5_list,music_list,label,"
	    . "tone_id,color_id,pict_id,commercials_id,lp,fsk,comment,mtype_id,"
	    . "d.name as dname,d.firstname as dfname,"
	    . "m.name as mname,m.firstname as mfname,"
	    . "a1.name as a1name,a1.firstname as a1fname,"
	    . "a2.name as a2name,a2.firstname as a2fname,"
	    . "a3.name as a3name,a3.firstname as a3fname,"
	    . "a4.name as a4name,a4.firstname as a4fname,"
	    . "a5.name as a5name,a5.firstname as a5fname,"
	    . "mt.name as mtname,mt.sname as mtsname,"
	    . "c.name as cname,c.sname as csname,"
	    . "t.name as tname,t.sname as tsname,"
	    . "cat1.name as cat1name,cat2.name as cat2name,cat3.name as cat3name,"
	    . "cass_id,part "
	    . "FROM video "
	    . "LEFT JOIN directors d ON director_id=d.id "
	    . "LEFT JOIN music m ON music_id=m.id "
	    . "LEFT JOIN mtypes mt ON mtype_id=mt.id "
	    . "LEFT JOIN colors c ON color_id=c.id "
	    . "LEFT JOIN tone t ON tone_id=t.id "
	    . "LEFT JOIN cat cat1 ON cat1_id=cat1.id "
	    . "LEFT JOIN cat cat2 ON cat2_id=cat2.id "
	    . "LEFT JOIN cat cat3 ON cat3_id=cat3.id "
	    . "LEFT JOIN actors a1 ON actor1_id=a1.id "
	    . "LEFT JOIN actors a2 ON actor2_id=a2.id "
	    . "LEFT JOIN actors a3 ON actor3_id=a3.id "
	    . "LEFT JOIN actors a4 ON actor4_id=a4.id "
	    . "LEFT JOIN actors a5 ON actor5_id=a5.id" . $where;
     $this->query($query);
     $rc = $this->num_rows(); # somehow the while loop does not work here???
     for ( $rcc=0;$rcc<$rc;++$rcc ) {
       $this->next_record();
       $moviedetails = array("title","label","length","country","year","counter1",
                     "counter2","aq_date","source","director_list",
		     "actor1_list","actor2_list","actor3_list","actor4_list",
		     "actor5_list","music_list","fsk","comment","cass_id","part",
		     "mtype_id","tone_id","color_id");
       foreach($moviedetails as $value) {
         $movie[$value] = $this->f("$value");
       }
       $movie[title]   = stripslashes($movie[title]);
       $movie[source]  = stripslashes($movie[source]);
       $movie[comment] = stripslashes($movie[comment]);
       if (!$movie[length]) $movie[length] = 0;
       $name = $this->format_name( array(name=>$this->f('dname'),firstname=>$this->f('dfname')) );
       $movie[director] = $name[fullname]; $movie[director_rev] = $name[reverse];
       $movie[director_] = $name;
       $name = $this->format_name( array(name=>$this->f('mname'),firstname=>$this->f('mfname')) );
       $movie[music] = $name[fullname]; $movie[music_rev] = $name[reverse];
       $movie[music_] = $name;
       for ($i=1;$i<6;$i++) { // actor 1..5: [actor1],[actor1_rev],[actor_1]...
         $dbname = "a$i" . "name"; $dbfname = "a$i" . "fname";
         $tname  = stripslashes($this->f("$dbname"));
         $tfname = stripslashes($this->f("$dbfname"));
         $vname  = "actor$i"; $vrev = "actor$i" . "_rev"; $aname = "actor_$i";
         $name = $this->format_name( array(name=>$tname,firstname=>$tfname) );
         $movie[$vname] = $name[fullname]; $movie[$vrev] = $name[reverse];
         $movie[$aname] = $name;
       }
       $movie[mtype] = $this->f('mtname'); $movie[mtype_short] = $this->f('mtsname');
       $movie[color] = lang($this->f('cname')); $movie[color_short] = $this->f('csname');
       $movie[tone] = $this->f('tname'); $movie[tone_short] = $this->f('tsname');
       $movie[cat1int] = $this->f('cat1name'); $movie[cat2int] = $this->f('cat2name'); $movie[cat3int] = $this->f('cat3name');
       $movie[cat1] = lang($movie[cat1int]); $movie[cat2] = lang($movie[cat2int]); $movie[cat3] = lang($movie[cat3int]);

       $moviedetails = array("actor1_id","actor2_id","actor3_id","actor4_id",
                     "actor5_id","director_id","music_id","cat1_id","cat2_id",
		     "cat3_id","pict_id","commercials_id","lp","mtype_id");
       foreach($moviedetails as $value) {
         $$value = $this->f("$value");
         $movie[$value] = $$value;
       }
       $movie[actors12] = $movie[actor1];
       if ( strlen($movie[actor2]) ) {
         if ( strlen($movie[actors12]) ) $movie[actors12] .= ", ";
         $movie[actors12] .= $movie[actor2];
       }
       $movie[actors35] = $movie[actor3];
       for ($i=4;$i<6;$i++) {
         $actor = "actor$i";
         if ( strlen($movie[$actor]) ) {
           if ( strlen($movie[actors35]) ) $movie[actors35] .= ", ";
	   $movie[actors35] .= $movie[$actor];
         }
       }
       $movie[actors] = $movie[actors12];
       if ( strlen($movie[actors35]) ) {
         if ( strlen($movie[actors]) ) $movie[actors] .= ", ";
         $movie[actors] .= $movie[actors35];
       }
       if ($pict_id) {
         $pict = $this->get_pict($pict_id);
         $movie[pict] = $pict[name]; $movie[pict_short] = $$pict[sname];
       } else {
         $movie[pict] = $movie[pict_short] = lang("unknown");
       }
       if ($commercials_id) {
         $movie[commercials] = $this->get_commercials($commercials_id);
       } else {
         $movie[commercials] = lang("unknown");
       }
       if ($lp) { $movie[lp] = lang("longplay"); } else { $movie[lp] = ""; }
       $movie[previous] = $this->get_preventry($movie[mtype_id],$movie[cass_id],$movie[part]);
       $movie[next]     = $this->get_nextentry($movie[mtype_id],$movie[cass_id],$movie[part]);
       $movie[disktype] = $this->get_disktype_id($movie[mtype_id],$movie[cass_id]);
       $movie[rc]       = $this->get_rc($movie[mtype_id],$movie[cass_id]);
       if ($id) return $movie;
       $list[] = $movie;
     }
     return $list;
   }

   /** Get movie list as array of movies (see get_movie)
    * @class sql
    * @method get_movielist
    * @param optional string order column to order the list by
    *  (title, lenght, year, date or cat)
    * @param optional string restrict definition of WHERE clause (without WHERE)
    * @param optional integer start (for use with LIMIT)
    * @return array array of movies
    * @see sql::get_movie()
    */
   function get_movielist($order="",$restrict="",$start="") {
     $filter = get_filters();
     switch ($order) {
       case "title"  : $orderby = "v.title,v.mtype_id DESC,v.cass_id"; break;
       case "length" : $orderby = "v.length,v.mtype_id DESC,v.cass_id"; break;
       case "year"   : $orderby = "v.year,v.mtype_id DESC,v.cass_id"; break;
       case "date"   : $orderby = "v.aq_date,v.mtype_id DESC,v.cass_id"; break;
       case "cat"    : $orderby = "v.cat1_id,v.mtype_id DESC,v.cass_id"; break;
       default       : $orderby = "v.mtype_id DESC,v.cass_id,v.part"; break;
     }
     if ($restrict) $where = " WHERE $restrict";
     $query = "SELECT v.id FROM video v";
     if (strlen($filter)) {
       if (strlen($where)) {
         $where .= " AND $filter";
       } else {
         $where = " WHERE $filter";
       }
     }
     $query .= $where;
     $query .= " ORDER BY $orderby";
     if ($start==="") { $this->dbquery($query); }
       else { $totals = $this->lim_query($query,$start); }
     while ( $this->next_record() ) {
       $list[] = $this->f('id');
     }
     $len = count($list);
     for ($i=0;$i<$len;$i++) {
       $movielist[] = $this->get_movie($list[$i]);
     }
     if ($totals) $movielist[totals] = $totals;
     return $movielist;
   }

   /** Search for movies and return as array of movies (see get_movie)
    * @class sql
    * @method searchmovies
    * @use searchmovievals
    * @param optional string order column to order the list by
    *  (title, lenght, year, date or cat)
    * @param optional integer start (for use with LIMIT)
    * @return array array of movies
    * @see sql::get_movie()
    * @version Since this is called via the nextmatch class, I found no way
    *  yet to pass it an array, so we have to set it global.
    */
   function searchmovies($order="",$start="") {
     GLOBAL $searchmovievals;
     foreach ($searchmovievals as $key=>$val) {
       ${$key} = $val;
     }
     $ccount = count($mtype_id);
     for ($i=0;$i<$ccount;++$i) {
       if (!$mtype_id[$i]) break;
       if ($i==0) { $restrict .= "("; } else { $restrict .= " OR "; }
       $restrict .= "v.mtype_id=".$mtype_id[$i]." ";
       if ($i+1==$ccount) $restrict .= ") ";
     }
     $ccount = count($cat_id);
     for ($i=0;$i<$ccount;++$i) {
       if (!$cat_id[$i]) break;
       $cat = $cat_id[$i];
       if ($i==0) { if ($restrict) $restrict .= "AND "; $restrict .= " ("; }
       $restrict .= "v.cat1_id=$cat OR v.cat2_id=$cat OR v.cat3_id=$cat ";
       if ($i+1<$ccount) { $restrict .= " OR "; } else { $restrict .= ") "; }
     }
     if ($restrict) $restrict .= "AND ";
     $restrict .= "v.title LIKE '%$title%' AND ";
     if ($pname) {
       switch ($ptype) {
         case director :
           $this->query("SELECT id FROM directors WHERE firstname LIKE '%$pname%' OR name LIKE '%$pname%'");
           while ( $this->next_record() ) {
             $pids .= ",".$this->f('id');
           }
           $pids = substr($pids,1);
           $restrict .= "director_id IN ($pids) AND"; break;
         default       : 
           $this->query("SELECT id FROM actors WHERE firstname LIKE '%$pname%' OR name LIKE '%$pname%'");
           while ( $this->next_record() ) {
             $pids .= ",".$this->f('id');
           }
           $pids = substr($pids,1);
           for ($i=1;$i<6;++$i) {
             if ($i==1) $restrict .= "(";
             $restrict .= "v.actor$i"."_id IN ($pids)";
             if ($i<5) $restrict .= " OR ";
           }
       }
       $restrict .= ") AND ";
     }
     $restrict .= "comment LIKE '%$comment%'";
     if ($minlen) $restrict .= " AND length>=$minlen";
     if ($maxlen) $restrict .= " AND length<=$maxlen";
     if ($minfsk) $restrict .= " AND fsk>=$minfsk";
     if ($maxfsk) $restrict .= " AND fsk<=$maxfsk";
     return $this->get_movielist($order,$restrict,$start);
   }

   /** Get movie list for cat1 as array of movies (see get_movie)
    *  (wrapper to get_movielist)
    * @class sql
    * @method get_moviecatlist
    * @param integer cat_id ID of category to get movies for
    * @return array array of movies
    * @see sql::get_movielist(), sql::get_movie()
    */
   function get_moviecatlist($cat) {
     return $this->get_movielist("$cat1_id,title","cat1_id=$cat");
   }

   /** Get movie list for cat1..cat3 as array of movies (see get_movie)
    *  (wrapper to get_movielist)
    * @class sql
    * @method get_moviecatlist3
    * @param integer cat_id ID of category to get movies for
    * @return array array of movies
    * @see sql::get_movielist(), sql::get_movie()
    */
   function get_moviecatlist3($cat) {
     return $this->get_movielist("$cat1_id,title","cat1_id=$cat OR cat2_id=$cat OR cat3_id=$cat");
   }

   /** Get movie list by staff member as array of movies (see get_movie)
    * @class sql
    * @method get_movienamelist
    * @param string table table name for staff member
    * @param array name name as formatted by sql::format_name()
    * @param optional string filter filter restriction
    * @return array list of movies
    * @see sql::get_movie(), sql::get_movielist()
    */
   function get_movienamelist($table,$name,$filter="") {
     switch ($table) {
       case "directors" : $restrict = "v.director_id=$name[id] AND v.director_list=1";
			  $revname = "director_rev"; $fullname = "director";
			  $firstname = "director_first"; $lastname = "director_last";
			  break;
       case "music"     : $restrict = "v.music_id=$name[id] AND v.music_list=1";
			  $revname = "music_rev"; $fullname = "music";
			  $firstname = "music_first"; $lastname = "music_last";
			  break;
       case "actors"    : $restrict = "((v.actor1_id=$name[id] AND v.actor1_list=1)"
                                    . " OR  (v.actor2_id=$name[id] AND v.actor2_list=1)"
                                    . " OR  (v.actor3_id=$name[id] AND v.actor3_list=1)"
                                    . " OR  (v.actor4_id=$name[id] AND v.actor4_list=1)"
                                    . " OR  (v.actor5_id=$name[id] AND v.actor5_list=1))";
			  $revname = "actor_rev"; $fullname = "actor";
			  $firstname = "actor_first"; $lastname = "actor_last";
			  break;
       default:
     }
     if (strlen($filter)) $restrict .= " AND ($filter)";
     $query = "SELECT v.title,v.length,v.cass_id,v.part,v.lp,v.year,v.aq_date,"
	    . "v.mtype_id,mt.name as mtname,mt.sname as mtsname,"
	    . "cat1.name as cat1name "
	    . "FROM video v, mtypes mt, cat cat1 "
	    . "WHERE v.cat1_id=cat1.id AND v.mtype_id=mt.id "
	    . "AND $restrict";
     $this->query($query);
     while ( $this->next_record() ) {
       $movie[$revname]   = $name[reverse];
       $movie[$fullname]  = $name[fullname];
       $movie[$lastname]  = $name[name];
       $movie[$firstname] = $name[firstname];
       $movie[mtype] = $this->f('mtname'); $movie[mtype_short] = $this->f('mtsname');
       $movie[cat1] = lang($this->f('cat1name')); $movie[cat2] = lang($this->f('cat2name')); $movie[cat3] = lang($this->f('cat3name'));
       $moviedetails = array("title","length","cass_id","part","lp","year","aq_date","mtype_id");
       foreach($moviedetails as $value) {
         $movie[$value] = $this->f("$value");
       }
       $list[] = $movie;
     }
     return $list;
   }

   /** Get last movie numbers for each media type
    * @class sql
    * @method get_lastmovienum
    * @param optional integer mtype_id
    * @param optional integer cass_id
    * @return mixed lastnum
    *  array lastnum if called w/o params (i:mtype, i:mtype_id, i:cass_id,
    *  i:part, i:entry; where i:entry = "mtype cass_id-part")
    *  integer part if called w/ both params
    */
   function get_lastmovienum($mtype_id="",$cass_id="") {
     if (is_numeric($mtype_id) && is_numeric($cass_id)) {
       $this->dbquery("SELECT MAX(part) AS max_part FROM video WHERE mtype_id=$mtype_id AND cass_id=$cass_id");
       if ( $this->next_record() ) {
         return $this->f('max_part');
       } else {
         return 0;
       }
     }
     $mtypes = $this->get_mtypes();
     for ($i=0;$i<count($mtypes);$i++) {
       $this->dbquery("SELECT MAX(cass_id) as max_id FROM video WHERE mtype_id=" . $mtypes[$i][id]);
       $this->next_record();
       $lastnum[$i][mtype]   = $mtypes[$i][sname];
       $lastnum[$i][mtype_id]= $mtypes[$i][id];
       $lastnum[$i][cass_id] = $this->f('max_id');
       while ( strlen($lastnum[$i][cass_id])<4 ) { $lastnum[$i][cass_id] = "0" . $lastnum[$i][cass_id]; }
     }
     for ($i=0;$i<count($lastnum);$i++) {
       $this->dbquery("SELECT MAX(part) as max_part FROM video WHERE cass_id=" . $lastnum[$i][cass_id] . " AND mtype_id=" . $lastnum[$i][mtype_id]);
       $this->next_record();
       $lastnum[$i][part]    = $this->f('max_part');
       while ( strlen($lastnum[$i][part])<2 ) { $lastnum[$i][part] = "0" . $lastnum[$i][part]; }
       $lastnum[$i][entry] = $lastnum[$i][mtype] . " " . $lastnum[$i][cass_id] . "-" . $lastnum[$i][part];
     }
     return $lastnum;
   }

   /** Get the next entry
    * @class sql
    * @method get_nextentry
    * @param integer mtype_id media type id of current entry
    * @param integer media_nr number of current medium
    * @param integer part part number of current entry
    * @return object next entry: mtype_id, media_rn, part
    */
   function get_nextentry($mtype_id,$media_nr,$part) {
     if (!(is_numeric($mtype_id) && is_numeric($media_nr) && is_numeric($part))) return FALSE;
     $next->mtype_id = $mtype_id;
     $next->media_nr = $media_nr;
     $this->query("SELECT MIN(part) AS part FROM video WHERE mtype_id=$mtype_id AND cass_id=$media_nr AND part>$part");
     if ($this->next_record()) {
       $next->part = $this->f('part');
       if($next->part) return $next;
     }
     $this->query("SELECT MIN(cass_id) AS medianr FROM video WHERE mtype_id=$mtype_id AND cass_id>$media_nr");
     if ($this->next_record()) {
       $next->media_nr = $this->f('medianr');
       if ($next->media_nr) { # Work around MySQL bug returning "Null" sometimes
         $this->query("SELECT MIN(part) AS part FROM video WHERE mtype_id=$mtype_id AND cass_id=".$next->media_nr);
         $this->next_record();
         $next->part = $this->f('part');
         return $next;
       }
     }
     ++$next->mtype_id;
     $this->query("SELECT MIN(cass_id) AS medianr FROM video WHERE mtype_id=".$next->mtype_id);
     if ($this->next_record()) {
       $next->media_nr = $this->f('medianr');
       if ($next->media_nr) {
         $this->query("SELECT MIN(part) AS part FROM video WHERE mtype_id=".$next->mtype_id." AND cass_id=".$next->media_nr);
         $this->next_record();
         $next->part = $this->f('part');
         return $next;
       }
     }
     return FALSE;
   }

   /** Get the previous entry
    * @class sql
    * @method get_preventry
    * @param integer mtype_id media type id of current entry
    * @param integer media_nr number of current medium
    * @param integer part part number of current entry
    * @return object next entry: mtype_id, media_rn, part
    */
   function get_preventry($mtype_id,$media_nr,$part) {
     if (!(is_numeric($mtype_id) && is_numeric($media_nr) && is_numeric($part))) return FALSE;
     $prev->mtype_id = $mtype_id;
     $prev->media_nr = $media_nr;
     if ($part>1) {
       $this->query("SELECT MAX(part) AS part FROM video WHERE mtype_id=$mtype_id AND cass_id=$media_nr AND part<$part");
       if ($this->next_record()) {
         $prev->part = $this->f('part');
         return $prev;
       }
     }
     if ($media_nr>1) {
       $this->query("SELECT MAX(cass_id) AS medianr FROM video WHERE mtype_id=$mtype_id AND cass_id<$media_nr");
       if ($this->next_record()) {
         $prev->media_nr = $this->f('medianr');
         if (!is_numeric($prev->media_nr)) return FALSE;
         $this->query("SELECT MAX(part) AS part FROM video WHERE mtype_id=$mtype_id AND cass_id=".$prev->media_nr);
         $this->next_record();
         $prev->part = $this->f('part');
         return $prev;
       }
     }
     --$prev->mtype_id;
     $last = $this->get_lastmovienum();
     for ($i=0;$i<count($last);++$i) {
       if ($last[$i][mtype_id]==$prev->mtype_id) {
         $prev->part = $last[$i][part];
	 $prev->media_nr = $last[$i][cass_id];
	 return $prev;
       }
     }
     return FALSE;
   }

   /** Add a movie to DB
    * @class sql
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
       display_error( lang("dupe_id_entered") );
       exit;
     }
     if ( ( bool ) !ini_get('magic_quotes_gpc')
      || basename($GLOBALS['PHP_SELF'])=="change_nr.php"
      || basename($GLOBALS['PHP_SELF'])=="backup_db.php" ) {
       $title  = addslashes($title);
       $comment= addslashes($comment);
       $source = addslashes($source);
     }
     $details = array("label","cat1_id","cat2_id","cat3_id","director_list",
                      "music_list","actor1_list","actor2_list","actor3_list",
                      "actor4_list","actor5_list","pict_id","commercials_id","lp");
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
     $insert = "INSERT INTO video (mtype_id,cass_id,part,title,label,length,aq_date,"
             . "source,director_id,director_list,music_id,music_list,country,"
	     . "year,cat1_id,cat2_id,cat3_id,actor1_id,actor2_id,actor3_id,"
	     . "actor4_id,actor5_id,actor1_list,actor2_list,actor3_list,"
	     . "actor4_list,actor5_list,tone_id,pict_id,color_id,fsk,comment,"
	     . "lp,counter1,counter2,commercials_id) "
	     . "VALUES ("
	     . "$mtype_id,$cass_id,$part,'$title',$label,$length,'$aq_date','$source',"
	     . "$director_id,$director_list,$music_id,$music_list,'$country',"
	     . "$year,$cat1_id,$cat2_id,$cat3_id,$actor1_id,$actor2_id,"
	     . "$actor3_id,$actor4_id,$actor5_id,$actor1_list,$actor2_list,"
	     . "$actor3_list,$actor4_list,$actor5_list,$tone_id,$pict_id,"
	     . "$color_id,$fsk,'$comment',$lp,'$counter1','$counter2',$commercials_id)";
     $success = $this->query($insert);
     if ( $pvp->common->medium_is_rw($mtype_id) ) {
       $this->insert_medium($cass_id,$mtype_id,$space);
       $this->update_freetime($cass_id,$mtype_id);
     }
     if ($disktype) $this->set_disktype($cass_id,$mtype_id,$disktype);
     if ( count($rc) ) $this->set_rc($mtype_id,$cass_id,$rc);
     return $success;
   }

   /** Move a movie to a new place
    * @class sql
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
     if ( $pvp->common->medium_is_rw($mtype_id) ) {
       $movie = $this->get_movie($id);
       $space = $this->get_mediaspace($movie[cass_id],$movie[mtype_id]);
     }
     $query = "UPDATE video SET mtype_id=$mtype_id,cass_id=$cass_id,part=$part"
            . " WHERE id=$id";
     $success = $this->dbquery($query);
     if (is_array($movie)) $this->insert_medium($cass_id,$mtype_id,$space);
     $this->update_freetime($cass_id,$mtype_id);
     if ( $pvp->common->medium_is_rw($movie[mtype_id]) && $movie[cass_id]!=$cass_id ) {
       $this->dbquery("SELECT id FROM video WHERE cass_id=".$movie[cass_id]." AND mtype_id=".$movie[mtype_id]);
       if ( $this->next_record() ) {
         $this->update_freetime($movie[cass_id],$movie[mtype_id]);
       } else {
         $this->delete_medium($movie[cass_id],$movie[mtype_id]);
       }
     }
     return $success;
   }

   /** Get a list of duplicate titles
    * @class sql
    * @method get_dupetitles
    * @return array array of titles:
    *  array[$i][title]; array[$i][$k]-&gt;id,mtype_id,cass_nr,part,len
    *  where $i counts the distinct titles, and $k the copies per title
    */
   function get_dupetitles() {
     $query  = "SELECT o.title as titel, o.id as o_id, o.mtype_id as o_mtypeid,"
             . " o.cass_id as o_cassnr, o.part as o_part, o.length as o_len,"
             . " d.id as d_id, d.mtype_id as d_mtypeid, d.cass_id as d_cassnr,"
             . " d.part as d_part, d.length as d_len"
             . " FROM video o, video d"
             . " WHERE o.title=d.title AND o.id<d.id"
             . " ORDER BY o_id ASC";
     $this->dbquery($query);
     $i = -1;
     while ( $this->next_record() ) {
       $title = $this->f('titel');
       if ( $i==-1 || $dupes[$i][title]!=$title ) {
         ++$i; $k=0;
         $dupes[$i][title] = $title;
         $dupes[$i][$k]->id       = $this->f('o_id');
         $dupes[$i][$k]->mtype_id = $this->f('o_mtypeid');
         $dupes[$i][$k]->cass_nr  = $this->f('o_cassnr');
         $dupes[$i][$k]->part     = $this->f('o_part');
         $dupes[$i][$k]->len      = $this->f('o_len');
       }
       ++$k;
       $dupes[$i][$k]->id       = $this->f('d_id');
       $dupes[$i][$k]->mtype_id = $this->f('d_mtypeid');
       $dupes[$i][$k]->cass_nr  = $this->f('d_cassnr');
       $dupes[$i][$k]->part     = $this->f('d_part');
       $dupes[$i][$k]->len      = $this->f('d_len');
     }
     return $dupes;
   }
   
   ############################################################################
   # Media Specific Stuff
   ############################################################################

   /** Obtain all media numbers that have a certain disk type assigned
    * @class sql
    * @method get_mediaForDisktype
    * @param integer id disktype-ID
    * @return array media (array of objects w/ properties mtype_id, cass_id)
    */
   function get_mediaForDisktype($id) {
     $this->dbquery("SELECT mtype_id,id FROM cass WHERE disks_id=$id");
     while ( $this->next_record() ) {
       $m->cass_id  = $this->f('id');
       $m->mtype_id = $this->f('mtype_id');
       $media[] = $m;
     }
     return $media;
   }

   /** Obtain all disk type for a given media type
    * @class sql
    * @method get_disktypes
    * @param integer mtype_id Media Type ID
    * @param optional integer id ID for a specific entry
    * @return array disktypes (array of objects, properties:
    *   int id, string name, string size, int lp, array rc)
    */
   function get_disktypes($mtype_id,$id="") {
     $query = "SELECT name,id,size,lp,rc FROM disks WHERE ";
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
     }
     return $types;
   }

   /** Delete a disktype from table disks
    * @class sql
    * @method delete_disktype
    * @param integer id
    * @return boolean success
    */
   function delete_disktype($id) {
     if ( $this->dbquery("UPDATE cass SET disks_id=NULL WHERE disks_id=$id") ) {
       return $this->dbquery("DELETE FROM disks WHERE id=$id");
     } else {
       return FALSE;
     }
   }

   /** Update a disktype in table disks
    * @class sql
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
       $query = "UPDATE disks SET "
              . "mtype_id=$mtype_id,name='$name',size='$size',lp=$lp,rc=$rc "
              . "WHERE id=$id";
     } else {
       $query = "INSERT INTO disks (mtype_id,name,size,lp,rc)"
              . " VALUES ($mtype_id,'$name','$size',lp,rc)";
     }
     return $this->dbquery($query);
   }

   /** Get a specific disktype id
    * @class sql
    * @method get_disktype_id
    * @param integer mtype_id
    * @param integer cass_id
    * @return integer disktype_id
    */
   function get_disktype_id($mtype_id,$cass_id) {
     $this->dbquery("SELECT disks_id FROM cass WHERE id=$cass_id AND mtype_id=$mtype_id");
     $this->next_record();
     return $this->f('disks_id');
   }

   /** Set disktype for a medium
    * @class sql
    * @method set_disktype
    * @param integer cass_id
    * @param integer mtype_id
    * @param integer disktype_id
    * @return boolean success
    */
   function set_disktype($cass_id,$mtype_id,$disktype_id) {
     $this->dbquery("SELECT id FROM cass WHERE id=$cass_id AND mtype_id=$mtype_id");
     $this->next_record();
     if ( $id = $this->f('id') ) {
       return $this->dbquery("UPDATE cass SET disks_id=$disktype_id WHERE id=$id AND mtype_id=$mtype_id");
     } else {
       return $this->dbquery("INSERT INTO cass (id,mtype_id,disks_id) VALUES($cass_id,$mtype_id,$disktype_id)");
     }
   }

   /** Set region code(s) for a specific medium
    * @class sql
    * @method set_rc
    * @param integer mtype_id
    * @param integer cass_id
    * @param array rc
    * @return boolean success
    */
   function set_rc($mtype_id,$cass_id,$rc) {
     if ( count($rc) ) {
       $rcs = ",";
       for ($i=0;$i<7;++$i) {
         if ($rc[$i]) $rcs .= $i . ",";
       }
     } else {
       $rcs = "";
     }
     $this->dbquery("SELECT id FROM cass WHERE id=$cass_id AND mtype_id=$mtype_id");
     $this->next_record();
     if ( $id = $this->f('id') ) {
       return $this->dbquery("UPDATE cass SET rc='$rcs' WHERE id=$id AND mtype_id=$mtype_id");
     } else {
       return $this->dbquery("INSERT INTO cass (id,mtype_id,rc) VALUES ($cass_id,$mtype_id,'$rcs')");
     }
   }

   /** Retrieve region code for a given medium
    * @class sql
    * @method get_rc
    * @param integer mtype_id
    * @param integer cass_id
    * @return array rc
    */
   function get_rc($mtype_id,$cass_id) {
     $this->dbquery("SELECT rc FROM cass WHERE id=$cass_id AND mtype_id=$mtype_id");
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
    * @class sql
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
     $this->dbquery("SELECT id,name,sname FROM mtypes $where ORDER BY id");
     $i = 0;
     while ( $this->next_record() ) {
       $mtypes[$i][id] = $this->f('id');
       $mtypes[$i][sname] = $this->f('sname');
       $mtypes[$i][name] = $this->f('name');
       ++$i;
     }
     return $mtypes;
   }

   /** update mtype data (wrapper to set_av)
    * @class sql
    * @method set_mtypes
    * @param string name
    * @param string sname
    * @param optional integer id
    * @see set_av()
    */
   function set_mtypes($name,$sname,$id="") {
     return $this->set_av("mtypes",$name,$sname,$id);
   }

   /** Insert a medium into the media table (if not yet exists)
    * @class sql
    * @method insert_medium
    * @param integer cass_id media id
    * @param integer mtype_id media type id
    * @param integer space complete space on media (media length)
    */
   function insert_medium($cass_id,$mtype_id,$space) {
     $free = $this->get_mediaspace($cass_id,$mtype_id);
     if ($free=="") { // medium not yet in cass table
       if (!$space) $space = 240;
       $this->dbquery("INSERT INTO cass (id,mtype_id,type,free) VALUES ($cass_id,$mtype_id,$space,0)");
     }
   }

   /** Delete a medium from the media table.
    *  Removes the entry from cass table only if the medium is empty (or $force is set)
    * @class sql
    * @method delete_medium
    * @param integer cass_id media id
    * @param integer mtype_id media type id
    * @param optional boolean force force deletion even if not empty (default: no)
    * @return boolean wether deletion took place
    */
   function delete_medium($cass_id,$mtype_id,$force=FALSE) {
     $this->dbquery("SELECT COUNT(id) as mcount FROM video WHERE cass_id=$cass_id AND mtype_id=$mtype_id");
     $this->next_record();
     if ( $this->f('mcount') < 1 ) $force = TRUE;
     if ($force) {
       $this->dbquery("DELETE FROM cass WHERE id=$cass_id");
       return TRUE;
     }
     return FALSE;
   }

   /** Get freetime of a given medium
    * @class sql
    * @method get_mediumfreetime
    * @param integer id media id
    * @param integer mtype_id media type id
    * @return mixed either freetime (integer) or empty string
    */
   function get_mediumfreetime($id,$mtype_id) {
     $this->query("SELECT free FROM cass WHERE id=$id AND mtype_id=$mtype_id");
     if ( $this->next_record() ) return $this->f('free');
       else return "";
   }

   /** Get space on a medium
    * @class sql
    * @method get_mediaspace
    * @param integer id media id
    * @param integer mtype_id media type id
    * @param optional string field fieldname ("type" or "free", defaults to type)
    * @return mixed either freetime (integer) or empty string
    */
   function get_mediaspace($id,$mtype_id,$field="type") {
     $this->dbquery("SELECT $field FROM cass WHERE id=$id AND mtype_id=$mtype_id");
     if ( $this->next_record() ) return $this->f("$field");
     return "";
   }

   /** Set space on a medium
    * @class sql
    * @method set_mediaspace
    * @param integer id media id
    * @param integer mtype_id media type id
    * @param integer space
    * @param optional string field fieldname ("type" or "free", defaults to type)
    * @return mixed either freetime (integer) or empty string
    */
   function set_mediaspace($id,$mtype_id,$space,$field="type") {
     GLOBAL $valid;
     if ( !$valid->num($space) ) return FALSE;
     if ( $this->get_mediaspace($id,$mtype_id) ) {
       $query = "UPDATE cass SET $field=$space WHERE id=$id AND mtype_id=$mtype_id";
     } else {
       $query = "INSERT INTO cass (id,mtype_id,$field) VALUES ($id,$mtype_id,$space)";
     }
     if ( $this->dbquery($query) ) {
       return $this->update_freetime($id,$mtype_id);
     }
     return FALSE;
   }

   /** Update freetime on a medium. If $free is not specified, recalc freetime
    * @class sql
    * @method update_freetime
    * @param integer id media id
    * @param optional integer mtype_id media type id (defaults to 1)
    * @param optional integer free free time
    * @return boolean success
    */
   function update_freetime($id,$mtype_id="1",$free="") {
     GLOBAL $valid;
     if ($free=="") {
       $free  = $this->get_mediaspace($id,$mtype_id);
       $query = "SELECT length,lp FROM video WHERE cass_id=$id AND mtype_id=$mtype_id";
       $this->dbquery($query);
       $i=0;
       while ( $this->next_record() ) {
         ++$i;
	 $length = $this->f('length');
	 if ( $this->f('lp') ) $length /= 2;
	 $free -= $length;
       }
     } else {
       if ( !$valid->num($free) ) return FALSE;
     }
     return $this->dbquery("UPDATE cass SET free=$free WHERE id=$id AND mtype_id=$mtype_id");
   }

   /** Get list of free space on media. If $start is set, the result set is
    *  limited based on $pvp->preferences->limit
    * @class sql
    * @method get_freelist
    * @param integer minfree min amount of freetime to display
    * @param optional string filter filter restriction to apply
    * @param optional integer start (for use of LIMIT)
    * @return array freelist (i:id, i:free where i:id is the media ID)
    */
   function get_freelist($minfree,$filter="",$start="") {
     $restrict = "free>=$minfree";
     if ( strlen($filter) ) {
       $this->dbquery("SELECT cass_id FROM video v WHERE $filter");
       $i=0;
       while ( $this->next_record() ) {
         if ($i) { $tapelist .= "," . $this->f('cass_id'); }
	   else { $tapelist = $this->f('cass_id'); ++$i; }
       }
       $restrict .=  " AND id IN ($tapelist)";
     }
     $query = "SELECT id,mtype_id,free FROM cass WHERE $restrict ORDER BY free";
     if ($start==="") { $this->dbquery($query); $totals = $this->num_rows(); }
       else { $totals = $this->lim_query($query,$start); }
     $i=0;
     while ( $this->next_record() ) {
       $freelist[$i][id]         = $this->f('id');
       $freelist[$i][mtype_id]   = $this->f('mtype_id');
       $freelist[$i][free]       = $this->f('free');
       ++$i;
     }
     $freelist[totals] = $totals;
     return $freelist;
   }

   ############################################################################
   /** Get list of "visible" staff members If $start is set, the result set is
    *  limited based on $pvp->preferences->limit
    * @class sql
    * @method get_visstafflist
    * @param string stafftype wether it is music, directors or actors
    * @param optional string filter filter restrictions
    * @param optional integer start (for use with LIMIT)
    * @return array stafflist (i:id (staff member ID), i:name
    *  (array formatted by sql::format_name())
    */
   function get_visstafflist($stafftype,$filter="",$start="") {
     if (strlen($filter)) $restrict = "AND $filter";
     switch ($stafftype) {
       case "music"     : $query[] = "SELECT DISTINCT music_id FROM video v WHERE music_list=1 $restrict"; $field[] = "music_id"; break;
       case "directors" : $query[] = "SELECT DISTINCT director_id FROM video v WHERE director_list=1 $restrict"; $field[] = "director_id"; break;
       case "actors"    : $query[] = "SELECT DISTINCT actor1_id FROM video v WHERE actor1_list=1 $restrict"; $field[] = "actor1_id";
                          $query[] = "SELECT DISTINCT actor2_id FROM video v WHERE actor2_list=1 $restrict"; $field[] = "actor2_id";
                          $query[] = "SELECT DISTINCT actor3_id FROM video v WHERE actor3_list=1 $restrict"; $field[] = "actor3_id";
                          $query[] = "SELECT DISTINCT actor4_id FROM video v WHERE actor4_list=1 $restrict"; $field[] = "actor4_id";
                          $query[] = "SELECT DISTINCT actor5_id FROM video v WHERE actor5_list=1 $restrict"; $field[] = "actor5_id"; break;
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
         $stafflist[$i][id]   = $this->f('id');
         $name[firstname]     = $this->f('firstname');
         $name[name]          = $this->f('name');
         $name[id]            = $stafflist[$i][id];
         $stafflist[$i][name] = $this->format_name($name);
         ++$i;
       }
       $stafflist[totals] = $totals;
     } else {
       $stafflist[totals] = 0;
     }
     return $stafflist;
   }

   ############################################################################
   /** Check wether a given person exists in the db and aquire his/her id. If not
    *  found in db, insert him/her first (privat! internal helper func)
    * @class sql
    * @method insert_person
    * @param string person stafftype
    * @param string query SQL query for SELECT statement
    * @param string sub_query SQL query for INSERT statement
    * @param optional string name family name of person
    * @param optional string fname first name of person
    * @return integer id (person_id)
    */
   function insert_person($person,$query,$sub_query,$name="",$fname="") {
     GLOBAL $dmsg,$pvp;
     if ( strlen( trim($name . $fname) ) < 1) {
       $dmsg .=  "<li><SPAN CLASS='ok'>$person not specified, no action taken.</SPAN>\n";
       return 0;
     } else {
       $name  = $pvp->common->safeinput($name);
       $fname = $pvp->common->safeinput($fname);
       if (empty($fname)) {
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

   function check_person($name,$fname,$table,$code=FALSE) {
     if ($code) {
       $name = addslashes($name); $firstname = addslashes($firstname);
     }
     $get  = "SELECT id FROM $table WHERE name='$name' AND firstname='$fname'";
     $this->dbquery($get);
     if ( $this->next_record() ) return $this->f('id');
     $this->dbquery("INSERT INTO $table (name,firstname) VALUES ('$name','$fname')");
     $this->dbquery($get);
     $this->next_record();
     return $this->f('id');
   }

   ############################################################################
   /** Gather statistic informations from the database
    * @class sql
    * @method get_stats
    * @return array stats
    */
   function get_stats() {
     GLOBAL $pvp;
     // ===[ counts ]===
     $details = array( array("name"=>"movies","sql"=>"SELECT count(id) AS movies FROM video"),
                       array("name"=>"actors","sql"=>"SELECT count(id) AS actors FROM actors"),
		       array("name"=>"directors","sql"=>"SELECT count(id) AS directors FROM directors"),
		       array("name"=>"composers","sql"=>"SELECT count(id) AS composers FROM music"),
		       array("name"=>"categories","sql"=>"SELECT count(id) AS categories FROM cat")
		     );
     foreach($details as $value) {
       $this->dbquery($value["sql"]);
       $this->next_record();
       $item = $value["name"];
       $stats[$item] = $this->f("$item");
     }
     $this->dbquery("SELECT DISTINCT mtype_id,cass_id FROM video");
     $stats[media] = $this->num_rows();
     $this->dbquery("SELECT DISTINCT country FROM video");
     $stats[countries] = $this->num_rows();
     for ($i=1;$i<4;++$i) {
       $cat = "cat" . $i . "_id";
       $this->dbquery("SELECT DISTINCT $cat FROM video");
       while ( $this->next_record() ) {
         ${$cat}[] = "a_" . $this->f("$cat"); // "a_" needed for array_merge to turn the integer into a string
       }
       ${$cat} = array_flip(${$cat});
     }
     $cats = array_merge($cat1_id,$cat2_id,$cat3_id);
     $stats[cats_used] = count($cats);
     // ===[ ranks ]===
     $details = array( array("name"=>"country","sql"=>"SELECT count(id) AS rank, country AS item FROM video WHERE country IS NOT NULL GROUP BY country ORDER BY rank DESC"),
		       array("name"=>"director","sql"=>"SELECT count(id) AS rank, director_id AS item FROM video WHERE director_id>0 GROUP BY director_id ORDER BY rank DESC"),
		       array("name"=>"composer","sql"=>"SELECT count(id) AS rank, music_id AS item FROM video WHERE music_id>0 GROUP BY music_id ORDER BY rank DESC"),
		       array("name"=>"category","sql"=>"SELECT count(id) AS rank, cat1_id AS item FROM video GROUP BY cat1_id ORDER BY rank DESC")
                     );
     foreach($details as $value) {
       $this->dbquery($value["sql"]);
       for ($i=1,$k=1;$k<4;++$i) {
         $this->next_record();
	 $item = $this->f('item');
	 $rank = "rank_" . $value["name"] . "_" . $k;
	 if (strlen( trim($item) )) ++$k; // do not count the "unknowns"
	 $stats[$rank] =  "$item (" . $this->f('rank') . ")";
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
         $rank = substr($person,$pos+2,strlen($person)-($pos+3));
	 $func = $value["func"];
         $name = $this->$func($person_id);
	 switch($func) {
	   case "get_category" : $stats[$sperson] = $name; break;
	   default             : $stats[$sperson] = $name[fullname]; break;
	 }
	 $stats[$count] = $rank;
       }
     }
     // actors is a bit complicated - we have to consider 5 fields...
     for ($i=1;$i<6;++$i) {
       $id = "actor" . $i . "_id";
       $this->dbquery("SELECT COUNT($id) AS count,$id FROM video WHERE $id<>0 GROUP BY $id");
       while ( $this->next_record() ) {
         $actor_id         = $this->f("$id");
         ${$id}[$actor_id] = $this->f("count");
       }
     }
     $actors = $pvp->common->array_combine_sums($actor1_id,$actor2_id);
     $actors = $pvp->common->array_combine_sums($actors,$actor3_id);
     $actors = $pvp->common->array_combine_sums($actors,$actor4_id);
     $actors = $pvp->common->array_combine_sums($actors,$actor5_id);
     arsort($actors);
     $i = 1;
     foreach ($actors as $key=>$value) {
       $name  = $this->get_actor($key);
       $act   = "rank_actor_" . $i;
       $count = $act . "_count";
       $stats[$act]   = $name[fullname];
       $stats[$count] = $value;
       ++$i;
       if ($i>3) break;
     }
     return $stats;
   }

   ############################################################################
   /** Execute the statements in the passed $array one-by-one, ignore comments
    * @class sql
    * @method get_sql
    * @param array sql_array each line containing SQL code
    * @return boolean success
    * @version right now only lines starting with a hash mark ("#") are
    *  recognized as comments (plus everything following the semi-colon at
    *  the end of an SQL statement)
    * @todo recognize other SQL comments like "--"
    * @todo handle ";" within field content correctly (and do not assume end
    *  of command here)
    */
   function get_sql($array) {
     $sql   = ""; $ok = 1;
     $lines = count($array);
     for ($i=0;$i<$lines;$i++) {
       $pos  = strpos(" " . trim($array[$i]),"#");
       if ($pos<>1) { // this is no comment line, so we process it
         $sql .= $array[$i];
         $line  = trim($array[$i]);
         if ( (strrpos($line,";") +1)==strlen($line) ) {
           $sql = trim($sql);
           $sql = substr($sql,0,strlen($sql) -1);
           if ( !$this->dbquery($sql) ) $ok = 0;
           $sql = "";
         } // end (if semicolon at end of line)
       }
     }
     return $ok;
   } // end get_sql()

   ############################################################################
   /** Interface to get_sql(): reads a file into an array and passes it to
    *  get_sql()
    * @class sql
    * @method queryf
    * @param string file name of file containing the SQL code to execute
    * @param string comment description of the actions done by execute
    * @param optional boolean silent wether to (not) output advance information
    */
   function queryf($file,$comment,$silent=0) {
     if ( !file_exists($file) ) {
       if (!$silent) echo " <li><SPAN CLASS='error'>$comment failed: missing SQL command file '$file', process stopped.</SPAN><BR>\n";
       exit;
     }
     $array = file ($file);
     if ( !$array ) {
       if (!$silent) echo " <li><SPAN CLASS='error'>$comment failed: we have no read permission for SQL command file '$file' (or this file is empty), process stopped.</SPAN><BR>\n";
       exit;
     }
     if ( $this->get_sql($array) ) {
       if (!$silent) echo " <li><SPAN CLASS='ok'>$comment successful.</SPAN><BR>\n";
     } else {
       if (!$silent) echo " <li><SPAN CLASS='error'>$comment failed, process stopped.</SPAN><BR>\n";
       exit;
     }
   } // end query_f()

 ############################################################################
 # PS-Label Specific Stuff
 ############################################################################

 /** get printer specifics
  * @class sql
  * @method get_printer
  * @param optional integer id
  * @return mixed (array of object(s) with printer specifics)
  */
 function get_printer($id="") {
   $query = "SELECT id,name,unit_id,top_offset,left_offset FROM printers";
   if ($id) $query .= " WHERE id=$id";
   $this->dbquery($query);
   while ($this->next_record()) {
     $printer->id   = $this->f('id');
     $printer->name = $this->f('name');
     $printer->unit_id = $this->f('unit_id');
     $printer->top_offset = $this->f('top_offset');
     $printer->left_offset = $this->f('left_offset');
     $printerlist[] = $printer;
   }
   return $printerlist;
 }

 /** set printer specifics
  * @class sql
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
   if (!$name) { $query = "DELETE FROM printers WHERE id=$id"; }
     elseif (!$id) {
       $this->query("SELECT MAX(id) AS maxid FROM printers");
       $this->next_record();
       $id = $this->f('maxid') +1;
       $query = "INSERT INTO printers VALUES ($id,'$name',$unit,$top_offset,$left_offset)";
   } else {
     $query = "UPDATE printers SET name='$name',unit_id=$unit,"
            . "top_offset=$top_offset,left_offset=$left_offset "
            . "WHERE id=$id";
   }
   $rc = $this->dbquery($query);
   if ($rc<0) return FALSE;
   return TRUE;
 }

 /** get available units
  * @class sql
  * @method get_units
  * @return mixed (array of id,unit,factor)
  */
 function get_units() {
     $this->query("SELECT id,unit,size FROM units");
     $i=0;
     while ( $this->next_record() ) {
       $units[$i][id]   = $this->f('id');
       $units[$i][unit] = $this->f('unit');
       $units[$i][factor] = $this->f('size');
       ++$i;
     }
   return $units;
  }

 /** get available label forms
  * @class sql
  * @method get_label_forms
  * @return mixed (array of i:id,i:vendor,i:product)
  */
 function get_label_forms() {
     $this->query("SELECT id,vendor,product FROM label_forms");
     $i=0;
     while ( $this->next_record() ) {
       $label_forms[$i][product] = $this->f('product');
       $label_forms[$i][vendor] = $this->f('vendor');
       $label_forms[$i][id]   = $this->f('id');
       ++$i;
     }
   return $label_forms;
  }

 /** get number of rows and columns on sheet for $id
  * @class sql
  * @method get_lsheet
  * @return mixed (rows,cols)
  */
 function get_lsheet($id) {
     $query="SELECT rows,cols,type FROM label_forms WHERE id=$id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $lsheet[rows] = $this->f('rows');
         $lsheet[cols] = $this->f('cols');
         $lsheet[type] = $this->f('type');
         return $lsheet;
       }
     }
     return FALSE;
  }

 /** get all print format relevant infos for label form $id
  * @class sql
  * @method get_lsheet_info
  * @return mixed ()
  */
 function get_lsheet_info($id,$printer_id) {
     $stat=0;

     $query="SELECT rows,cols,unit_id,h_dist,
     v_dist,width,heigth,leftm,topm,sheet_id 
     FROM label_forms WHERE id=$id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $lsheet[label_rows] = $this->f('rows');
         $lsheet[label_cols] = $this->f('cols');
         $lsheet[label_hdist] = $this->f('h_dist');
         $lsheet[label_vdist] = $this->f('v_dist');
         $lsheet[label_width] = $this->f('width');
         $lsheet[label_heigth] = $this->f('heigth');
         $lsheet[left_margin] = $this->f('leftm');
         $lsheet[top_margin] = $this->f('topm');
         $label_unit_id = $this->f('unit_id');
         $lsheet_sheet_id = $this->f('sheet_id');
	 $stat++;
       }
       $stat++;
     }

     $query="SELECT size FROM units WHERE id=$label_unit_id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $lsheet[label_unit_size] = $this->f('size');
         $stat++;
       }
       $stat++;
     }

     $query="SELECT name,unit_id,width,length FROM sheets WHERE id=$lsheet_sheet_id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $sheet_unit_id = $this->f('unit_id');
	 $lsheet[sheet_papersize] = $this->f('name');
	 $lsheet[sheet_length] = $this->f('length');
	 $lsheet[sheet_width] = $this->f('width');
         $stat++;
       }
       $stat++;
     }

     $query="SELECT size FROM units WHERE id=$sheet_unit_id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $lsheet[sheet_unit_size] = $this->f('size');
         $stat++;
       }
       $stat++;
     }

     $query="SELECT unit_id,top_offset,left_offset
     FROM printers WHERE id=$printer_id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $lsheet[pr_left] = $this->f('left_offset');
         $lsheet[pr_top] = $this->f('top_offset');
         $printer_unit_id = $this->f('unit_id');
         $stat++;
       }
       $stat++;
     }

     $query="SELECT size FROM units WHERE id=$printer_unit_id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $lsheet[pr_unit_size] = $this->f('size');
         $stat++;
       }
       $stat++;
     }

     if ($stat) return $lsheet;
     return FALSE;
  }

 /** get eps template description for $type
  * @class sql
  * @method get_epstemplates
  * @return mixed (id,description)
  */
 function get_epstemplates($type) {
     $query="SELECT id,description FROM eps_templates WHERE type=$type";
     if ( $this->dbquery($query) ) {
       $i=0;
     while ( $this->next_record() ) {
         $eps_template[$i][id] = $this->f('id');
         $eps_template[$i][description] = $this->f('description');
         ++$i;
       }
       return $eps_template;
     }
     return FALSE;
  }

 /** get eps image reference for $id
  * @class sql
  * @method get_epsimage
  * @return mixed (eps_file,ps_file,llx,lly,urx,ury)
  */
 function get_epsimage($id) {
     $query="SELECT eps_filename,ps_filename,llx,lly,urx,ury
     FROM eps_templates WHERE id=$id";
     if ( $this->dbquery($query) ) {
       if ( $this->next_record() ) {
         $eps_image[eps] = $this->f('eps_filename');
         $eps_image[ps] = $this->f('ps_filename');
         $eps_image[llx] = $this->f('llx');
         $eps_image[lly] = $this->f('lly');
         $eps_image[urx] = $this->f('urx');
         $eps_image[ury] = $this->f('ury');
       }
       return $eps_image;
     }
     return FALSE;
  }

 /** get eps template types
  * @class sql
  * @method get_labeltypes
  * @return array labeltypes array of objects
  */
 function get_labeltypes() {
   $query = "SELECT id,type,description FROM label_forms";
   $this->dbquery($query);
   while ( $this->next_record() ) {
     $type->id = $this->f('id');
     $type->type = $this->f('type');
     $type->desc = $this->f('description');
     $label[] = $type;
   }
   return $label;
 }

 /** get complete eps template description list
  * @class sql
  * @method get_pstemplates
  * @param optional integer id eps template id
  * @param optional integer start for limit queries
  * @return array templates array of objects
  */
 function get_pstemplates($id="",$start="") {
   $query = "SELECT e.id,e.type,e.description,e.eps_filename,e.ps_filename,"
          . "e.llx,e.lly,e.urx,e.ury,l.description AS typedesc "
          . "FROM eps_templates e,label_forms l "
          . "WHERE e.type=l.type";
   if ($id) $query .= " AND e.id=$id";
   $query .= " ORDER BY e.description";
   if ($start==="") { $this->dbquery($query); }
     else { $totals = $this->lim_query($query,$start); }
   while ( $this->next_record() ) {
     $tpl->id = $this->f('id');
     $tpl->type_id = $this->f('type');
     $tpl->type_desc = $this->f('typedesc');
     $tpl->desc = $this->f('description');
     $tpl->eps_file = $this->f('eps_filename');
     $tpl->ps_file = $this->f('ps_filename');
     $tpl->llx = $this->f('llx');
     $tpl->lly = $this->f('lly');
     $tpl->urx = $this->f('urx');
     $tpl->ury = $this->f('ury');
     $template[] = $tpl;
   }
   if ($totals) $template[totals] = $totals;
   return $template;
 }

 /** set ps template details
  * @class sql
  * @method set_pstemplate
  * @param mixed pstemplate integer id to delete or object to update
  * @return boolean success
  */
 function set_pstemplate($ps) {
   if (is_int($ps)) {
     $query = "DELETE FROM eps_templates WHERE id=$ps";
   } elseif ($ps->id) {
     $id    = $ps->id;
     $query = "UPDATE eps_templates SET type=".$ps->type_id.",description='"
            . $ps->desc."',eps_filename='".$ps->eps_file."',ps_filename='"
            . $ps->ps_file."',llx=".$ps->llx.",lly=".$ps->lly.",urx="
            . $ps->urx.",ury=".$ps->ury." WHERE id=$id";
   } else {
     $this->query("SELECT MAX(id) AS maxid FROM eps_templates");
     $this->next_record();
     $id = $this->f('maxid') +1;
     $query = "INSERT INTO eps_templates (id,type,description,eps_filename,"
            . "ps_filename,llx,lly,urx,ury) VALUES ($id,"
            . $ps->type_id.",'".$ps->desc."','".$ps->eps_file."','"
            . $ps->ps_file."',".$ps->llx.",".$ps->lly.",".$ps->urx.",".$ps->ury.")";
   }
   $this->dbquery($query);
   if ($this->affected_rows()<0) return FALSE;
   return $id;
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
  * @return integer id (person_id)
  * @deprecated this is only a placeholder for backward compatibility.
  *  use sql::insert_person() directly instead.
  */
 function insert_person($person,$query,$sub_query,$name="",$fname="") {
   // only called from inc/sql_set_persons.inc
   GLOBAL $db;
   return $db->insert_person($person,$query,$sub_query,$name,$fname);
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