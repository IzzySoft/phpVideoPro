<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Taken from PHPLIB                                                         #
 # Copyright (c) 1998-2000 NetUSE AG                                         #
 #                    Boris Erdmann, Kristian Koehntopp                      #
 #############################################################################

 /* $Id$ */

 /** Basic Database Methods for MySQL (extended by class sql)
  * @package Api
  * @class DB_Sql
  */
class DB_Sql {
  
  # public: connection parameters
  var $Host     = "";
  var $Database = "";
  var $User     = "";
  var $Password = "";

  # public: configuration parameters
  var $Auto_Free     = 0;     ## Set to 1 for automatic mysql_free_result()
  var $Debug         = 0;     ## Set to 1 for debugging messages.
  var $Halt_On_Error = "yes"; ## "yes" (halt with message), "no" (ignore errors quietly), "report" (ignore errror, but spit a warning)
  var $Seq_Table     = "db_sequence";

  # public: result array and current row number
  var $Record   = array();
  var $Row;

  # public: current error number and error text
  var $Errno    = 0;
  var $Error    = "";

  # public: this is an api revision, not a CVS revision.
  var $type     = "mysql";
  var $revision = "1.2";

  # private: link and query handles
  var $Link_ID  = 0;
  var $Query_ID = 0;
  

  /** constructor
   * @package Api
   * @class DB_Sql
   * @constructor DB_Sql
   * @param optional string query query to run
   */
  function DB_Sql($query = "") {
      $this->query($query);
  }

  /** Retrieve the link_id
   * @package Api
   * @class DB_Sql
   * @method link_id
   * @return integer link_id
   */
  function link_id() {
    return $this->Link_ID;
  }

  /** Retrieve the query_id
   * @package Api
   * @class DB_Sql
   * @method query_id
   * @return integer query_id
   */
  function query_id() {
    return $this->Query_ID;
  }

  /** Connection management
   * @package Api
   * @class DB_Sql
   * @method connect
   * @param optional string Database database to connect to (defaults to this::Database)
   * @param optional string Host Machine hosting the DB (defaults to this::Host)
   * @param optional string User Username to connect with (defaults to this::User)
   * @param optional string Password User's Pwd (defaults to this::Password)
   * @return integer Link_ID on success, 0 otherwise
   */
  function connect($Database = "", $Host = "", $User = "", $Password = "") {
    # Handle defaults
    if ("" == $Database)
      $Database = $this->Database;
    if ("" == $Host)
      $Host     = $this->Host;
    if ("" == $User)
      $User     = $this->User;
    if ("" == $Password)
      $Password = $this->Password;
      
    # establish connection, select database
    if ( 0 == $this->Link_ID ) {
      $this->Link_ID=mysql_pconnect($Host, $User, $Password);
      if (!$this->Link_ID) {
        $this->halt("pconnect($Host, $User, \$Password) failed.");
        return 0;
      }
      if (!@mysql_select_db($Database,$this->Link_ID)) {
        $this->halt("cannot use database ".$this->Database);
        return 0;
      }
    }
    return $this->Link_ID;
  }

  /** Discard the query result
   * @package Api
   * @class DB_Sql
   * @method free
   */
  function free() {
      @mysql_free_result($this->Query_ID);
      $this->Query_ID = 0;
  }

  /** Perform a query
   * @package Api
   * @class DB_Sql
   * @method query
   * @param string Query_String SQL Query
   * @return integer Query_ID on success, 0 otherwise
   */
  function query($Query_String) {
    # No empty queries, please, since PHP4 chokes on them.
    if ($Query_String == "")
      # The empty query string is passed on from the constructor,
      # when calling the class without a query, e.g. in situations
      # like these: '$db = new DB_Sql_Subclass;'
      return 0;

    if (!$this->connect()) {
      return 0; /* we already complained in connect() about that. */
    };

    # New query, discard previous result.
    if ($this->Query_ID) {
      $this->free();
    }

    if ($this->Debug)
      printf("Debug: query = %s<br>\n", $Query_String);

    $this->Query_ID = @mysql_query($Query_String,$this->Link_ID);
    $this->Row   = 0;
    $this->Errno = mysql_errno();
    $this->Error = mysql_error();
    if (!$this->Query_ID) {
      $this->halt("Invalid SQL: ".$Query_String);
    }

    # Will return nada if it fails. That's fine.
    return $this->Query_ID;
  }

  /** Walk result set
   * @package Api
   * @class DB_Sql
   * @method next_record
   * @return boolean success
   */
  function next_record() {
    if (!$this->Query_ID) {
      $this->halt("next_record called with no query pending.");
      return 0;
    }

    $this->Record = @mysql_fetch_array($this->Query_ID);
    $this->Row   += 1;
    $this->Errno  = mysql_errno();
    $this->Error  = mysql_error();

    $stat = is_array($this->Record);
    if (!$stat && $this->Auto_Free) {
      $this->free();
    }
    return $stat;
  }

  /** Position in result set
   * @package Api
   * @class DB_Sql
   * @method seek
   * @param optional integer pos Position to set the pointer to
   * @return boolean success
   */
  function seek($pos = 0) {
    $status = @mysql_data_seek($this->Query_ID, $pos);
    if ($status)
      $this->Row = $pos;
    else {
      $this->halt("seek($pos) failed: result has ".$this->num_rows()." rows");

      # half assed attempt to save the day, 
      # but do not consider this documented or even
      # desireable behaviour.
      @mysql_data_seek($this->Query_ID, $this->num_rows());
      $this->Row = $this->num_rows;
      return 0;
    }

    return 1;
  }

  /** Table locking
   * @package Api
   * @class DB_Sql
   * @method lock
   * @param string table table to lock
   * @param optional string mode locking mode (defaults to "write")
   * @return boolean success
   */
  function lock($table, $mode="write") {
    $this->connect();
    
    $query="lock tables ";
    if (is_array($table)) {
      while (list($key,$value)=each($table)) {
        if ($key=="read" && $key!=0) {
          $query.="$value read, ";
        } else {
          $query.="$value $mode, ";
        }
      }
      $query=substr($query,0,-2);
    } else {
      $query.="$table $mode";
    }
    $res = @mysql_query($query, $this->Link_ID);
    if (!$res) {
      $this->halt("lock($table, $mode) failed.");
      return 0;
    }
    return $res;
  }

  /** Unlock all tables
   * @package Api
   * @class DB_Sql
   * @method unlock
   * @return boolean success
   */
  function unlock() {
    $this->connect();
    $res = @mysql_query("unlock tables");
    if (!$res) {
      $this->halt("unlock() failed.");
      return 0;
    }
    return $res;
  }


  /** Evaluate the result for DML operation
   * @package Api
   * @class DB_Sql
   * @method affected_rows
   * @return integer affected rows
   */
  function affected_rows() {
    return @mysql_affected_rows($this->Link_ID);
  }

  /** Evaluate the result for SELECT operation
   * @package Api
   * @class DB_Sql
   * @method num_rows
   * @return integer number of rows in result set
   */
  function num_rows() {
    return @mysql_num_rows($this->Query_ID);
  }

  /** Evaluate the result for SELECT operation
   * @package Api
   * @class DB_Sql
   * @method num_fields
   * @return integer number of columns in result set
   */
  function num_fields() {
    return @mysql_num_fields($this->Query_ID);
  }

  # public: shorthand notation
  function nf() {
    return $this->num_rows();
  }

  function np() {
    print $this->num_rows();
  }

  /** Retrieve the content of a field in the current record of the result set
   * @package Api
   * @class DB_Sql
   * @method f
   * @return string content of field
   */
  function f($Name) {
    return $this->Record[$Name];
  }

  function p($Name) {
    print $this->Record[$Name];
  }

  /** Sequence numbers
   * @package Api
   * @class DB_Sql
   * @method nextid
   * @param string seq_name name of the sequence
   * @return integer next id (or 0 if none)
   */
  function nextid($seq_name) {
    $this->connect();
    if ($this->lock($this->Seq_Table)) {
      # get sequence number (locked) and increment
      $q  = sprintf("select nextid from %s where seq_name = '%s'",
                $this->Seq_Table,
                $seq_name);
      $id  = @mysql_query($q, $this->Link_ID);
      $res = @mysql_fetch_array($id);
      
      # No current value, make one
      if (!is_array($res)) {
        $currentid = 0;
        $q = sprintf("insert into %s values('%s', %s)",
                 $this->Seq_Table,
                 $seq_name,
                 $currentid);
        $id = @mysql_query($q, $this->Link_ID);
      } else {
        $currentid = $res["nextid"];
      }
      $nextid = $currentid + 1;
      $q = sprintf("update %s set nextid = '%s' where seq_name = '%s'",
               $this->Seq_Table,
               $nextid,
               $seq_name);
      $id = @mysql_query($q, $this->Link_ID);
      $this->unlock();
    } else {
      $this->halt("cannot lock ".$this->Seq_Table." - has it been created?");
      return 0;
    }
    return $nextid;
  }

  /** Get table metadata
   * @package Api
   * @class DB_Sql
   * @method metadata
   * @param optional string table table to retrieve MetaData for
   * @param optional boolean full wheter to retrieve all MetaData or short version
   * @return array MetaData
   */
  function metadata($table='',$full=false) {
    $count = 0;
    $id    = 0;
    $res   = array();

     # Due to compatibility problems with Table we changed the behavior
     # of metadata();
     # depending on $full, metadata returns the following values:
     
     # - full is false (default):
     # $result[]:
     #   [0]["table"]  table name
     #   [0]["name"]   field name
     #   [0]["type"]   field type
     #   [0]["len"]    field length
     #   [0]["flags"]  field flags
     #
     # - full is true
     # $result[]:
     #   ["num_fields"] number of metadata records
     #   [0]["table"]  table name
     #   [0]["name"]   field name
     #   [0]["type"]   field type
     #   [0]["len"]    field length
     #   [0]["flags"]  field flags
     #   ["meta"][field name]  index of field named "field name"
     #   The last one is used, if you have a field name, but no index.
     #   Test:  if (isset($result['meta']['myfield'])) { ...

    // if no $table specified, assume that we are working with a query
    // result
    if ($table) {
      $this->connect();
      $id = @mysql_list_fields($this->Database, $table);
      if (!$id)
        $this->halt("Metadata query failed.");
    } else {
      $id = $this->Query_ID; 
      if (!$id)
        $this->halt("No query specified.");
    }
 
    $count = @mysql_num_fields($id);

    // made this IF due to performance (one if is faster than $count if's)
    if (!$full) {
      for ($i=0; $i<$count; $i++) {
        $res[$i]["table"] = @mysql_field_table ($id, $i);
        $res[$i]["name"]  = @mysql_field_name  ($id, $i);
        $res[$i]["type"]  = @mysql_field_type  ($id, $i);
        $res[$i]["len"]   = @mysql_field_len   ($id, $i);
        $res[$i]["flags"] = @mysql_field_flags ($id, $i);
      }
    } else { // full
      $res["num_fields"]= $count;
    
      for ($i=0; $i<$count; $i++) {
        $res[$i]["table"] = @mysql_field_table ($id, $i);
        $res[$i]["name"]  = @mysql_field_name  ($id, $i);
        $res[$i]["type"]  = @mysql_field_type  ($id, $i);
        $res[$i]["len"]   = @mysql_field_len   ($id, $i);
        $res[$i]["flags"] = @mysql_field_flags ($id, $i);
        $res["meta"][$res[$i]["name"]] = $i;
      }
    }
    
    // free the result only if we were called on a table
    if ($table) @mysql_free_result($id);
    return $res;
  }

  # private: error handling
  function halt($msg) {
    $this->Error = @mysql_error($this->Link_ID);
    $this->Errno = @mysql_errno($this->Link_ID);
    if ($this->Halt_On_Error == "no")
      return;

    $this->haltmsg($msg);

    if ($this->Halt_On_Error != "report")
      die("Session halted.");
  }

  function haltmsg($msg) {
    printf("</td></tr></table><P><BR></P><b>Database error:</b> %s<br>\n", $msg);
    printf("<b>MySQL Error</b>: %s (%s)<br>\n",
      $this->Errno,
      $this->Error);
  }

  /** Retrieve all table names
   * @package Api
   * @class DB_Sql
   * @method table_names
   * @return array table_name, tablespace_name (=Database), database
   */
  function table_names() {
    $this->query("SHOW TABLES");
    $i=0;
    while ($info=mysql_fetch_row($this->Query_ID))
     {
      $return[$i]["table_name"]= $info[0];
      $return[$i]["tablespace_name"]=$this->Database;
      $return[$i]["database"]=$this->Database;
      $i++;
     }
   return $return;
  }

#================================================[ api ref for attributes ]===
/** Machine that runs the Database to connect to
 * @package Api
 * @class DB_Sql
 * @attribute string Host
 */
/** Database to connect to
 * @package Api
 * @class DB_Sql
 * @attribute string Database
 */
/** Database user with sufficient priviledges
 * @package Api
 * @class DB_Sql
 * @attribute string User
 */
/** Password for the User to connect to the DB
 * @package Api
 * @class DB_Sql
 * @attribute string Password
 */
/** Automatically free result set? Defaults to "0"
 * @package Api
 * @class DB_Sql
 * @attribute boolean $Auto_Free
 */
/** Enable Debug output? Defaults to "0"
 * @package Api
 * @class DB_Sql
 * @attribute boolean $Debug
 */
/** How to handle severe errors. Defaults to "yes". Possible values:
 *  "yes" (halt with message), "no" (ignore errors quietly), "report"
 *  (ignore errror, but spit a warning)
 * @package Api
 * @class DB_Sql
 * @attribute string $Halt_On_Error = "yes";
 */
/** Error reporting - error number
 * @package Api
 * @class DB_Sql
 * @attribute integer Errno
 */
/** Error reporting - the error description
 * @package Api
 * @class DB_Sql
 * @attribute string $Error
 */

} // end class DB_Sql
?>
