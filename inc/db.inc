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