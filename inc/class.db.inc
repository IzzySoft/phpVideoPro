<?php
 #############################################################################
 # phpVideoPro                              (c) 2001,2002 by Itzchak Rehberg #
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
  * @copyright (c) 2001,2002 by Itzchak Rehberg and IzzySoft
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
       case "mysql" : $this->limit = " LIMIT $start," . $pvp->preferences->display_limit;
                      break;
       case "pgsql" : $this->limit = " LIMIT " . $pvp->preferences->display_limit . ",$start";
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
     $query = str_replace ("\",", "\"NULL,", $query);
     $query = str_replace (",\"", ",NULL\"", $query);
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
     GLOBAL $colors;
     debug("S",$colors["ok"] . "$query</Font><BR>\n");
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
     return $lang;
   }

   /** Get (un)available|all languages
    * @class sql
    * @method get_languages
    * @param optional integer avail available (1) or unavailable(0); default: both
    * @return array languages (id,name)
    */
   function get_languages($avail="") {
     switch ($avail) {
       case "0" : $where = "WHERE available='no'"; break;
       case "1" : $where = "WHERE available='yes'"; break;
     }
     $this->dbquery("SELECT lang_id,lang_name,available FROM languages $where");
     $i=0;
     while ( $this->next_record() ) {
       $lang[$i]["id"]   = $this->f('lang_id');
       $lang[$i]["name"] = $this->f('lang_name');
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
       $trans[$msg_id] = $this->f('content');
     }
     $this->dbquery("SELECT message_id,content FROM lang WHERE lang='$pref_lang'");
     while ( $this->next_record() ) { // overwrite with preferred (if exists)
       $msg_id         = $this->f('message_id');
       $trans[$msg_id] = $this->f('content');
     }
     return $trans;
   }

   /** set a translation
    * @class sql
    * @method set_translation
    * @param string id translation identifier
    * @param string trans translated string
    * @param string lang language of the translation
    * @return boolean success
    */
   function set_translation($id,$trans,$lang) {
     if (!$trans) { // remove translation
       $query = "DELETE FROM lang WHERE message_id='$id' AND lang='$lang'";
     } else {
       $this->query("SELECT content FROM lang WHERE lang='$lang' AND message_id='$id'");
       if ( $this->next_record() ) {
         $query = "UPDATE lang SET content='$trans' WHERE lang='$lang' AND message_id='$id'";
       } else {
         $query = "INSERT INTO lang (message_id,lang,content) VALUES ('$id','$lang','$trans')";
       }
     }
     $this->dbquery($query);
     return $this->affected_rows();
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
     $this->dbquery("SELECT value FROM preferences WHERE name='$name'");
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
   # people and their names
   ############################################################################
   /** Format a name's array (private! just an internal helper func)
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

   /** Get all pict data and return it as array (wrapper to get_av)
    * @class sql
    * @method get_pict
    * @param optional integer id
    * @return array (name,sname if id!="", i:id,i:name,i:sname otherwise)
    */
   function get_pict($id="") {
     return $this->get_av($id,"pict");
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

   /** Get all tone data and return it as array (wrapper to get_av)
    * @class sql
    * @method get_tone
    * @param optional integer id
    * @return array (name,sname if id!="", i:id,i:name,i:sname otherwise)
    */
   function get_tone($id="") {
     return $this->get_av($id,"tone");
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

   ############################################################################
   # movie data
   ############################################################################
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
    *              lp
    *  Movie data: title, length, country, year, counter1, counter2, aq_date
    *              source, fsk, comment, catX / catX_id (1..3), comment
    *  Staff data: director_list, music_list, actorX_list (where X is 1..5);
    *              director_id, music_id, actorX_id (where X is 1..5);
    *              director, music and actorX as fullname (see format_name);
    *              director_,music_ and actorX_ as array (see format_name);
    *              with _rev as reverse name (name, firstname);
    *              actors, actors12, actors35 as list of actorX</pre>
    */
   function get_movie($id) {
     if (!$id) return "";
     $query = "SELECT title,length,country,year,counter1,counter2,aq_date,source,"
            . "director_id,director_list,music_id,cat1_id,cat2_id,cat3_id,"
	    . "actor1_id,actor2_id,actor3_id,actor4_id,actor5_id,actor1_list,"
	    . "actor2_list,actor3_list,actor4_list,actor5_list,music_list,"
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
	    . "LEFT JOIN actors a5 ON actor5_id=a5.id "
	    . "WHERE video.id=$id";
     $this->query($query);
     $this->next_record();
     $moviedetails = array("title","length","country","year","counter1",
                     "counter2","aq_date","source","director_list",
		     "actor1_list","actor2_list","actor3_list","actor4_list",
		     "actor5_list","music_list","fsk","comment","cass_id","part",
		     "mtype_id","tone_id","color_id");
     foreach($moviedetails as $value) {
       $movie[$value] = $this->f("$value");
     }
     $name = $this->format_name( array(name=>$this->f('dname'),firstname=>$this->f('dfname')) );
     $movie[director] = $name[fullname]; $movie[director_rev] = $name[reverse];
     $movie[director_] = $name;
     $name = $this->format_name( array(name=>$this->f('mname'),firstname=>$this->f('mfname')) );
     $movie[music] = $name[fullname]; $movie[music_rev] = $name[reverse];
     $movie[music_] = $name;
     for ($i=1;$i<6;$i++) { // actor 1..5: [actor1],[actor1_rev],[actor_1]...
       $dbname = "a$i" . "name"; $dbfname = "a$i" . "fname";
       $vname  = "actor$i"; $vrev = "actor$i" . "_rev"; $aname = "actor_$i";
       $name = $this->format_name( array(name=>$this->f("$dbname"),firstname=>$this->f("$dbfname")) );
       $movie[$vname] = $name[fullname]; $movie[$vrev] = $name[reverse];
       $movie[$aname] = $name;
     }
     $movie[mtype] = $this->f('mtname'); $movie[mtype_short] = $this->f('mtsname');
     $movie[color] = lang($this->f('cname')); $movie[color_short] = $this->f('csname');
     $movie[tone] = $this->f('tname'); $movie[tone_short] = $this->f('tsname');
     $movie[cat1] = lang($this->f('cat1name')); $movie[cat2] = lang($this->f('cat2name')); $movie[cat3] = lang($this->f('cat3name'));

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
     $movie[actor35] = $movie[actor3];
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
     return $movie;
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
     $query = "SELECT DISTINCT v.id FROM video v,cat c";
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
    * @return array lastnum (i:mtype, i:mtype_id, i:cass_id, i:part, i:entry;
    *  where i:entry = "mtype cass_id-part")
    */
   function get_lastmovienum() {
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
    * @todo does not handle holes on media (e.g. medium with 3 movies, #2
    *  deleted) nor holes in media number (e.g. medium #5 deleted, but 6 exists)
    */
   function get_nextentry($mtype_id,$media_nr,$part) {
     $next->mtype_id = $mtype_id;
     $next->media_nr = $media_nr;
     $next->part     = ++$part;
     if ( $this->get_movieid($mtype_id,$media_nr,$next->part) ) {
       return $next;
     }
     $next->part = 1; ++$next->media_nr;
     if ( $this->get_movieid($mtype_id,$next->media_nr,$next->part) )
       return $next;
     ++$next->mtype_id; $next->media_nr = 1;
     if ( $this->get_movieid($next->mtype_id,$next->media_nr,$next->part) )
       return $next;
     return FALSE;
   }

   /** Get the previous entry
    * @class sql
    * @method get_preventry
    * @param integer mtype_id media type id of current entry
    * @param integer media_nr number of current medium
    * @param integer part part number of current entry
    * @return object next entry: mtype_id, media_rn, part
    * @todo does not handle holes on media (e.g. medium with 3 movies, #2
    *  deleted) nor holes in media number (e.g. medium #5 deleted, but 6 exists)
    */
   function get_preventry($mtype_id,$media_nr,$part) {
     $prev->mtype_id = $mtype_id;
     $prev->media_nr = $media_nr;
     $prev->part     = --$part;
     if ( $prev->part && $id=$this->get_movieid($mtype_id,$media_nr,$prev->part) )
       return $prev;
     --$prev->media_nr; $prev->part = 1;
     if ( $this->get_movieid($mtype_id,$prev->media_nr,$prev->part) )
       return $prev;
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
       ${$key} = $value;
     }
     if ( $this->get_movieid($mtype_id,$cass_id,$part) ) {
       display_error( lang("dupe_id_entered") );
       exit;
     }
     $insert = "INSERT INTO video (mtype_id,cass_id,part,title,length,aq_date,"
             . "source,director_id,director_list,music_id,music_list,country,"
	     . "year,cat1_id,cat2_id,cat3_id,actor1_id,actor2_id,actor3_id,"
	     . "actor4_id,actor5_id,actor1_list,actor2_list,actor3_list,"
	     . "actor4_list,actor5_list,tone_id,pict_id,color_id,fsk,comment,"
	     . "lp,counter1,counter2,commercials_id) "
	     . "VALUES ("
	     . "$mtype_id,$cass_id,$part,'$title',$length,'$aq_date','$source',"
	     . "$director_id,$director_list,$music_id,$music_list,'$country',"
	     . "$year,$cat1_id,$cat2_id,$cat3_id,$actor1_id,$actor2_id,"
	     . "$actor3_id,$actor4_id,$actor5_id,$actor1_list,$actor2_list,"
	     . "$actor3_list,$actor4_list,$actor5_list,$tone_id,$pict_id,"
	     . "$color_id,$fsk,'$comment',$lp,'$counter1','$counter2',$commercials_id)";
     $success = $this->dbquery($insert);
     if ( $pvp->common->medium_is_rw($mtype_id) ) {
       $this->insert_medium($cass_id,$mtype_id,$space);
       $this->update_freetime($cass_id,$mtype_id);
     }
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
     GLOBAL $pvp;
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
   
   ############################################################################
   # Media Specific Stuff
   ############################################################################

   /** Get all media types and return them as array
    * @class sql
    * @method get_mtypes
    * @param optional string restrict WHERE clause
    * @return array array of media types
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
    */
   function update_freetime($id,$mtype_id="1",$free="") {
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
     $query = "SELECT id,mtype_id,free FROM cass WHERE $restrict ORDER BY free DESC";
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
     $list  = implode (",",$ar); // idlist of visible staff members
     $query = "SELECT id,name,firstname FROM $stafftype WHERE id IN ($list)";
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
     GLOBAL $dmsg,$colors;
     if ( strlen( trim($name . $fname) ) < 1) {
       $dmsg .=  $colors["ok"] . "<li>$person not specified, no action taken.</Font>\n";
       return 0;
     } else {
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
     $dmsg  .= $colors["ok"] . " <li>" . stripslashes($query) . "</Font>";
     $this->dbquery($query);
     if ( $this->next_record() ) {
       $id = $this->f('id');
       $dmsg  .= " (Got: '$id')</Font>\n";
     } else {
       $dmsg  .= "<BR>" . $colors["err"] . "$person not found in db! Trying to insert...</Font><BR>\n";
       if ( $this->dbquery($sub_query) ) {
         $this->dbquery($query);
         if ( $this->next_record() ) {
           $id = $this->f('id');
           $dmsg  .= $colors["ok"] . "$person \"$name, $fname\" inserted into db (id: $id).</Font>\n";
         } else {
           $dmsg  .= $colors["err"] . "Something strange happened: inserted $person \"$name, $fname\" into db, but could not find him/her afterwards!</Font>\n";
         }
       } else {
         $dmsg .= $colors["err"] . "Insertion of $person \"$name, $fname\ into db failed!</Font>\n";
       }
     }
     return $id;
   } // end insert_person()

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
		       array("name"=>"categories","sql"=>"SELECT count(id) AS categories FROM cat"),
		       array("name"=>"media","sql"=>"SELECT count(id) AS media FROM cass")
		     );
     foreach($details as $value) {
       $this->dbquery($value["sql"]);
       $this->next_record();
       $item = $value["name"];
       $stats[$item] = $this->f("$item");
     }
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
       for ($i=1;$i<4;++$i) {
         $this->next_record();
	 $item = $this->f('item');
	 $rank = "rank_" . $value["name"] . "_" . $i;
	 if (!strlen( trim($item) )) $item = lang("unknown");
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
    * @todo handle multi-line commands
    */
   function get_sql($array) {
     $sql   = ""; $ok = 1;
     for ($i=0;$i<count($array);$i++) {
       $pos  = strpos(" " . trim($array[$i]),"#");
       if ($pos<>1) {
         $sql .= $array[$i];
         $endpos = strpos($sql,";");
         if ($endpos) {
           $sql = substr($sql,0,$endpos);
           if ( !$this->dbquery($sql) ) $ok = 0;
           $sql = "";
         }
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
     GLOBAL $colors;
     if ( !file_exists($file) ) {
       if (!$silent) echo $colors["err"] . " <li>$comment failed: missing SQL command file '$file', process stopped.</Font><BR>\n";
       exit;
     }
     $array = file ($file);
     if ( !$array ) {
       if (!$silent) echo $colors["err"] . " <li>$comment failed: we have no read permission for SQL command file '$file', process stopped.</Font><BR>\n";
       exit;
     }
     if ( $this->get_sql($array) ) {
       if (!$silent) echo $colors["ok"] . " <li>$comment successful.</Font><BR>\n";
     } else {
       if (!$silent) echo $colors["err"] . " <li>$comment failed, process stopped.</Font><BR>\n";
       exit;
     }
   } // end query_f()

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