<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Common SQL helper funcs used for most database accesses                   *
 \***************************************************************************/

 /* $Id$ */

 class sql extends DB_Sql {
   VAR $limit;

   function sql() { // init
     $this->DB_Sql; // constructor of base class needs explicit call
     $this->limit();
   }

   ############################################################################
   # setup sql clause to limit result set
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

   ############################################################################
   # replace empty values within SQL queries by NULL statement to keep query
   # syntactically correct
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

   ############################################################################
   # query db and provide debug output
   function dbquery($query) {
     GLOBAL $colors;
     debug("S",$colors["ok"] . "$query</Font><BR>\n");
     $this->clean_query($query);
     if ( $this->query($query) ) return 1;
     return 0;
   }

   ############################################################################
   # query db using the LIMIT clause. returns count of TOTAL datasets found
   # (i.e. UNLIMITED query result count). $query must NOT contain any limit
   # clause!!!
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

   ############################################################################
   # get all media types and return them as array
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

   ############################################################################
   # get all translations and return them as array
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

   ############################################################################
   # get preferences
   function get_preferences($name) {
     $this->query("SELECT value FROM preferences WHERE name='$name'");
     if ( $this->next_record() ) {
       return $this->f('value');
     } else {
       return "";
     }
   }

   ############################################################################
   # set preferences
   function set_preferences($name,$value) {
     $this->query("SELECT value FROM preferences WHERE name='$name'");
     if ( $this->next_record() ) {
       $this->query("UPDATE preferences SET value='$value' WHERE name='$name'");
     } else {
       $this->query("INSERT INTO preferences (name,value) VALUES ('$name','$value'");
     }
   }

   ############################################################################
   # format a name's array
   function format_name($name) {
     $newname[name] = $newname[reverse] = trim($name[name]);
     $newname[firstname] = $newname[fullname] = trim($name[firstname]);
     if (strlen($newname[fullname])) {
       if (strlen($newname[firstname])) $newname[fullname] .= " " . $newname[name];
     } else {
       $newname[fullname] = $newname[name];
     }
     if (strlen($newname[reverse])) {
       if (strlen($newname[firstname])) $newname[reverse] .= ", " . $newname[firstname];
     } else {
       $newname[reverse] = $newname[firstname];
     }
     return $newname;
   }

   ############################################################################
   # get all data for a person and return it as array
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
         $person[$i][id]   = trim($this->f('id'));
         $person[$i][name] = $this->f('name');
         $person[$i][firstname] = $this->f('firstname');
	 $person[$i] = $this->format_name($person[$i]);
	 ++$i;
       }
     }
     return $person;
   }

   ############################################################################
   # get all data for an actor and return it as array
   function get_actor($id) {
     return $this->get_person($id,"actors");
   }

   ############################################################################
   # get all data for a director and return it as array
   function get_director($id) {
     return $this->get_person($id,"directors");
   }

   ############################################################################
   # get all data for a componist and return it as array
   function get_music($id) {
     return $this->get_person($id,"music");
   }

   ############################################################################
   # get a category's data
   function get_category($id,$order="") {
     if ($id) {
       $this->query("SELECT name FROM cat WHERE id=$id");
       if ( $this->next_record() ) {
         return trim($this->f('name'));
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
         $cat[$i][name] = $this->f('name');
	 ++$i;
       }
       return $cat;
     }
   }

   ############################################################################
   # get audio/video data and return it as array
   function get_av($id,$table) {
     $this->query("SELECT name,sname FROM $table WHERE id=$id");
     if ( $this->next_record() ) {
       $av[name]  = $this->f('name');
       $av[sname] = $this->f('sname');
     } else {
       $av[name] = $av[sname] = "";
     }
     return $av;
   }

   ############################################################################
   # get all pict data and return it as array
   function get_pict($id) {
     return $this->get_av($id,"pict");
   }

   ############################################################################
   # get all color data and return it as array
   function get_color($id) {
     return $this->get_av($id,"colors");
   }

   ############################################################################
   # get all tone data and return it as array
   function get_tone($id) {
     return $this->get_av($id,"tone");
   }

   ############################################################################
   # get data for commercials
   function get_commercials($id) {
     $this->query("SELECT name FROM commercials WHERE id=$id");
     if ( $this->next_record() ) {
       $commercials = $this->f('name');
       $commercials = lang($commercials);
     } else {
       $commercials = lang("unknown");
     }
     return $commercials;
   }

   ############################################################################
   # get all data for a movie entry and return it as array
   function get_movie($id) {
     $query = "SELECT title,length,country,year,counter1,counter2,aq_date,source,"
            . "director_id,director_list,music_id,cat1_id,cat2_id,cat3_id,"
	    . "actor1_id,actor2_id,actor3_id,actor4_id,actor5_id,actor1_list,"
	    . "actor2_list,actor3_list,actor4_list,actor5_list,tone_id,"
	    . "color_id,pict_id,commercials_id,lp,fsk,comment,mtype_id,"
	    . "d.name as dname,d.firstname as dfname,"
	    . "m.name as mname,m.firstname as mfname,"
	    . "mt.name as mtname,mt.sname as mtsname,"
	    . "c.name as cname,c.sname as csname,"
	    . "t.name as tname,t.sname as tsname,"
	    . "cass_id,part "
	    . "FROM video "
	    . "LEFT JOIN directors d ON director_id=d.id "
	    . "LEFT JOIN music m ON music_id=m.id "
	    . "LEFT JOIN mtypes mt ON mtype_id=mt.id "
	    . "LEFT JOIN colors c ON color_id=c.id "
	    . "LEFT JOIN tone t ON tone_id=t.id "
	    . "WHERE video.id=$id";
     $this->query($query);
     $this->next_record();
     $moviedetails = array("title","length","country","year","counter1",
                     "counter2","aq_date","source","director_list",
		     "actor1_list","actor2_list","actor3_list","actor4_list",
		     "actor5_list","fsk","comment","cass_id","part");
     foreach($moviedetails as $value) {
       $movie[$value] = $this->f("$value");
     }
     $name = $this->format_name( array(name=>$this->f('dname'),firstname=>$this->f('dfname')) );
     $movie[director] = $name[fullname];
     $name = $this->format_name( array(name=>$this->f('mname'),firstname=>$this->f('mfname')) );
     $movie[music] = $name[fullname];
     $movie[mtype] = $this->f('mtname'); $movie[mtype_short] = $this->f('mtsname');
     $movie[color] = $this->f('cname'); $movie[color_short] = $this->f('csname');
     $movie[tone] = $this->f('tname'); $movie[tone_short] = $this->f('tsname');

     $moviedetails = array("actor1_id","actor2_id","actor3_id","actor4_id",
                     "actor5_id","director_id","music_id","cat1_id","cat2_id",
		     "cat3_id","pict_id","commercials_id","lp");
     foreach($moviedetails as $value) {
       $$value = $this->f("$value");
     }
     $moviedetails = array("actor1_id","actor2_id","actor3_id","actor4_id","actor5_id");
     foreach($moviedetails as $value) {
       $name = substr($value,0,6);
       if (${$value}) {
	 $actor = $this->get_actor(${$value});
	 $movie[$name] = $actor[fullname];
       } else {
         $movie[$name] = "";
       }
       $$value = $this->f("$value");
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
     if ( strlen($movie[$actors35]) ) {
       if ( strlen($movie[actors]) ) $movie[actors] .= ", ";
       $movie[actors] .= $movie[actors35];
     }
     $moviedetails = array("cat1_id","cat2_id","cat3_id");
     foreach($moviedetails as $value) {
       $name = substr($value,0,4);
       if (${$value}) {
         $movie[$name] = $this->get_category(${$value});
       } else {
         $movie[$name] = "";
       }
       $$value = $this->f("$value");
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
     return $movie;
   }

   ############################################################################
   # get movie list as array of movies (see get_movie)
   function get_movielist($order="",$restrict="") {
     $filter = get_filters();
     switch ($order) {
       case "title" : $orderby = "title"; break;
       default      : $orderby = "mtype_id DESC,cass_id,part"; break;
     }
     if ($restrict) $where = " WHERE $restrict";
     $query = "SELECT id FROM video v";
     if (strlen($filter)) {
       if (strlen($where)) {
         $where .= " AND $filter";
       } else {
         $where = " WHERE $filter";
       }
     }
     $query .= $where;
     $query .= " ORDER BY $orderby";
     $this->dbquery($query);
     while ( $this->next_record() ) {
       $list[] = $this->f('id');
     }
     $len = count($list);
     for ($i=0;$i<$len;$i++) {
       $movielist[] = $this->get_movie($list[$i]);
     }
     return $movielist;
   }

   ############################################################################
   # get movie list for cat1 as array of movies (see get_movie)
   function get_moviecatlist($cat) {
     return $this->get_movielist("$cat1_id,title","cat1_id=$cat");
   }

   ############################################################################
   # check wether a given person exists in the db and aquire his/her id. If not
   # found in db, insert him/her first
   function insert_person($person,$query,$sub_query,$name="",$fname="") {
     GLOBAL $db,$dmsg,$colors;
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
   # execute the statements in the passed $array one-by-one
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
   # interface to get_sql(): reads a file into an array and passes it to get_sql()
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
 # placeholder(s) for backward compatibility
 function dbquery($query) {
   GLOBAL $db;
   return $db->dbquery($query);
 }
 function insert_person($person,$query,$sub_query,$name="",$fname="") {
   // only called from inc/sql_set_persons.inc
   GLOBAL $db;
   return $db->insert_person($person,$query,$sub_query,$name,$fname);
 }
 function queryf($file,$comment,$silent=0) { // only used in setup/*
   GLOBAL $db;
   $db->queryf($file,$comment,$silent);
 }

?>