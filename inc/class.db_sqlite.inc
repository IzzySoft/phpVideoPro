<?php
###############################################################################
# Basic database methods for SQLite, compatible with the database classes of  #
# PHPLib                                                                      #
###############################################################################

/** Basic database methods for SQLite
 * @package Api
 * @class DB_Sql
 * @author Izzy (izzysoft AT qumran DOT org)
 * @copyright (c) 2009 by Itzchak Rehberg and IzzySoft
 */ 
class DB_Sql {
  var $Host     = ""; // Dummy for compatibility
  var $Database = ""; // Filename of the database file
  var $User     = ""; // Dummy for compatibility
  var $Password = ""; // Dummy for compatibility

  var $Link_ID  = 0;
  var $Query_ID = 0;
  var $Record   = array();
  var $Row;

  var $AdjustQuotes = TRUE; // replace escaped quotes by SQLite Quotes - e.g.
                            // "\'" by "''"? Needed to be conform with other DBs

  var $Halt_On_Error = "yes"; ## "yes" (halt with message), "no" (ignore errors quietly), "report" (ignore error, but spit a warning)

  var $Auto_Free = 0;     
  var $PConnect  = 0;     // Dummy for compatibility

  /** Initialization
   * @package Api
   * @constructor DB_Sql
   * @param optional string query query to run
   */
  function DB_Sql($query = "") {
    if($query) {
      $this->query($query);
    }
  }

  /** Connect to database
   * @class DB_Sql
   * @method connect
   * @return integer Link_ID on success, 0 otherwise
   */
  function connect() {
    if ( 0 == $this->Link_ID ) {
      $this->Link_ID = sqlite_open($this->Database);
      if (!$this->Link_ID) {
        $this->halt("connect ($this->Database) failed");
      }
    }
  }

  /** Disconnect from database
   * @class DB_Sql
   * @method disconnect
   */
  function disconnect() {
    sqlite_close($this->Link_ID);
    $this->Link_ID = 0;
  }

  /** Perform a query
   * @class DB_Sql
   * @method query
   * @param string Query_String SQL Query
   * @return integer Query_ID on success, 0 otherwise
   */
  function query($Query_String) {
    /* No empty queries, please, since PHP4 chokes on them. */
    if ($Query_String == "")
      /* The empty query string is passed on from the constructor,
       * when calling the class without a query, e.g. in situations
       * like these: '$db = new DB_Sql_Subclass;'
       */
      return 0;
    $this->connect();
    if ($this->AdjustQuotes) $Query_String = str_replace("\\'","''",str_replace('\\"','""',$Query_String));
    $this->Query_ID = sqlite_query($this->Link_ID,$Query_String);
    $this->Row   = 0;
    if (!$this->Query_ID) {
      $this->halt("Invalid SQL: ".$Query_String);
    }

    return $this->Query_ID;
  }

  /** Walk result set
   * @class DB_Sql
   * @method next_record
   * @return boolean success
   */
  function next_record() {
    $this->Record = sqlite_fetch_array($this->Query_ID);
    $this->Row   += 1;
    $stat = is_array($this->Record);
    return $stat;
  }

  /** Position in result set
   * @class DB_Sql
   * @method seek
   * @param optional integer pos Position to set the pointer to (result/row number)
   * @return boolean success
   */
  function seek($pos) {
    $status = sqlite_seek($this->Query_ID, $pos);
    if ($status)
      $this->Row = $pos;
    return;
  }

  /** Obtain table metadata
   * @method metadata
   * @param string table_name
   * @return array 0..n of array(table,name,type,len,position,flags)
   * @version the field position is only kept for compatibility and will always
   *  be empty. Flags may contain attributes such as "PRIMARY KEY", if they
   *  immediately followd the column description. This code is still experimental
   *  and may fail, listing constraints as columns. Please let me know the
   *  details if you encounter this, so the code can be updated and fixed.
   */
  function metadata($table) {
    $count = 0;
    $i     = 0;
    $res   = array();

    $this->connect(); 
    $this->query("SELECT sql FROM sqlite_master WHERE name='$table' AND type='table'");
    $count = $this->num_rows();
    if ($count==0) return array(); // nothing found

    $this->next_record();
    $sql = $this->f('sql');
    $pos_s = strpos($sql,"(") +1;
    $pos_e = strrpos($sql,")");
    $sql = substr($sql,$pos_s,$pos_e - $pos_s);
    $arr = explode(",",$sql);
    foreach($arr as $var) {
      if (strpos($sql,'UNIQUE')===0) continue; // constraint
      $var = str_replace("("," ",str_replace(")","",$var));
      $col = explode(" ",$var);
      $res[$i]["table"] = $table;
      $res[$i]["name"]  = $col[0];
      $res[$i]["type"]  = $col[1];
      $res[$i]["flags"] = "";
      $res[$i]["position"] = "";
      if (is_numeric($col[2])) {
        $res[$i]["len"] = $col[2];
        $flag_pos         = 3;
      } else {
        $flag_pos       = 2;
        $res[$i]["len"] = ""; // constraints like 'PRIMARY KEY' may follow the column name
      }
      while (!empty($col[$flag_pos])) {
        $res[$i]["flags"] .= " ".$col[$flag_pos];
        ++$flag_pos;
      }
      $res[$i]["flags"] = trim($res[$i]["flags"]);
      ++$i;
    }
    return $res;
  }

  /** Evaluate the result for DML operation
   * @class DB_Sql
   * @method affected_rows
   * @return integer affected rows
   */
  function affected_rows() {
    return sqlite_changes($this->Link_ID);
  }

  /** Evaluate the result for SELECT operation (row count)
   * @class DB_Sql
   * @method num_rows
   * @return integer number of rows in result set
   */
  function num_rows() {
    return sqlite_num_rows($this->Query_ID);
  }

  /** Evaluate the result for SELECT operation (fieldset count)
   * @class DB_Sql
   * @method num_fields
   * @return integer number of columns in result set
   */
  function num_fields() {
    return sqlite_num_fields($this->Query_ID);
  }

  function nf() {
    return $this->num_rows();
  }

  function np() {
    print $this->num_rows();
  }

  /** Retrieve the content of a field in the current record of the result set
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
  
  function halt($msg) {
    if ("no" == $this->Halt_On_Error)
      return;

    $this->haltmsg($msg);

    if ("report" != $this->Halt_On_Error)
      die("Session halted.");
  }
  
  function haltmsg($msg) {
    printf("<p><b>Database error:</b> %s<br>\n", $msg);
    printf("<b>SQLite Error</b></p>\n", $this->Error);
  }

  /** Retrieve all table names
   * @class DB_Sql
   * @method table_names
   * @return array table_name, tablespace_name (=Database), database
   */
  function table_names() {
    $this->query("SELECT name FROM SQLITE_MASTER WHERE type='table' ORDER BY name");
    $i=0;
    while ($info=sqlite_fetch_array($this->Query_ID))
     {
      $return[$i]["table_name"]= $info[0];
      $return[$i]["tablespace_name"]=$this->Database;
      $return[$i]["database"]=$this->Database;
      $i++;
     }
   return $return;
  }

  /** Table locking
   * @class DB_Sql
   * @method lock
   * @param mixed table table to lock (either string or array of strings)
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
    $res = @sqlite_query($this->Link_ID,$query);
    if (!$res) {
      $this->halt("lock($table, $mode) failed.");
      return 0;
    }
    return $res;
  }

  /** Unlock all tables
   * @class DB_Sql
   * @method unlock
   * @return boolean success
   */
  function unlock() {
    $this->connect();
    $res = @sqlite_query("unlock tables");
    if (!$res) {
      $this->halt("unlock() failed.");
      return 0;
    }
    return $res;
  }

}
?>
