<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2009 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Data Transfer                                                             #
 #############################################################################

 /* $Id$ */

 /** Data Transfer
  * @package Api
  * @class xfer
  * @author Izzy (izzysoft AT qumran DOT org)
  * @copyright (c) 2001-2009 by Itzchak Rehberg and IzzySoft
  */
 class xfer {

  /** Initialization
   * @constructor xfer
   * @param string mode ("import" or "export")
   * @param boolean lock_db Whether to lock all tables during import/export (default: FALSE)
   */
  function xfer($mode,$lock_db=FALSE) {
    $this->compressionOff();
    $this->backupSend();
    $this->mode = $mode;
    switch ($mode) {
      case "import" : $this->initImport(); break;
      case "export" : $this->initExport(); break;
      default : die("Wrong mode for Xfer Module: '$mode'!");
    }
    $this->lock_db = $lock_db;
  }

 #====================================================[ Helpers (private!) ]===
 #---------------------------------------------------------[ Table Locking ]---
 /** Lock all tables for a consistent export/import
  * @method lockDB
  * @return boolean success
  */
 function lockDB() {
   GLOBAL $db;
   if (!$this->lock_db) return TRUE;
   $tables = $db->table_names();
   $tablecount = count($tables);
   $success = TRUE;
   for ($i=0;$i<$tablecount;++$i) {
     $name = $tables[$i]["table_name"];
     if (!$db->lock($name)) {
       $success = FALSE;
       $this->unlockDB();
       break;
     }
   }
   return $success;
 }

 /** UnLock all tables
  * @method unlockDB
  * @return boolean success
  */
 function unlockDB() {
   GLOBAL $db;
   if (!$this->lock_db) return TRUE;
   return $db->unlock();
 }

 /** Unlock and return message
  * @method ureturn
  * @param string msg
  * @return string msg
  */
 function ureturn($msg) {
   $this->unlockDB();
   return $msg;
 }

 #--------------------------------------------------------[ Initialization ]---
  /** Initialize data arrays for imports
   * @class xfer
   * @method private initImport
   */
  function initImport() {
    GLOBAL $db;
    $this->data   = array(); // imported file (array of strings)
    $this->list   = ""; // movies (one per line)
    $this->items  = 0;  // count of movies in xfer::list
    $this->errors = 0;  // count of errors occured
    $this->report = ""; // detailed report for debug level R
    $this->avlTypes = array("audio","subtitle");
    $this->audio    = $this->mkavlang("audio");
    $this->subtitle = $this->mkavlang("subtitle");
    $this->mtypes   = $this->mkMtypes();
    $tcatlist = $db->get_category();
    $catcount = count($tcatlist);
    for ($i=0;$i<$catcount;++$i) {
      $this->catlist[$tcatlist[$i]['internal']] = $tcatlist[$i]['id'];
    }
  }

  /** Initialize data arrays for exports
   * @class xfer
   * @method private initExport
   */
  function initExport() {
    $this->list  = "";
    $this->items = 0;
  }

 #-----------------------------------------------------[ Message Formating ]---
  /** Formating error message for display as save_result in form
   * @methode private errorMsg
   * @param string msg
   * @return string formated msg
   */
  function errorMsg($msg) {
    return "<SPAN CLASS='error'>$msg</SPAN>";
  }

  /** format OK message
   * @methode private okMsg
   * @param string msg
   * @return string formated msg
   */
  function okMsg($msg) {
    return "<SPAN CLASS='ok'>$msg</SPAN>";
  }

 #-----------------------------------[ Import helper for Audio + Subtitles ]---
  /** Retrieve list of available languages for audio/subtitle
   * @class xfer
   * @method private mkavlang
   * @param string type ("audio" or "subtitle")
   * @return array [0..n] of language ids (ISO) or empty array if type invalid
   */
   function mkavlang($type) {
     GLOBAL $db;
     if (!in_array($type,$this->avlTypes)) return array();
     $avl = $db->get_avlang($type);
     $lc = count($avl);
     for ($i=0;$i<$lc;++$i) {
       $lang[] = $avl[$i]->id;
     }
     return $lang;
   }

  /** Retrieve list of available media types
   * @class xfer
   * @method private mkMtypes
   * @return array [0..n] of language ids (ISO)
   */
   function mkMtypes() {
     GLOBAL $db;
     $mt = $db->get_mtypes();
     $mc = count($mt);
     for ($i=0;$i<$mc;++$i) {
       $id = $mt[$i]['sname'];
       $mtype[$id]->id   = $mt[$i]['id'];
       $mtype[$id]->name = $mt[$i]['name'];
     }
     return $mtype;
   }

 #--------------------------------------------------------[ File Functions ]---
  /** Read a file from disk.
   *  On errors, the formated error message is stored in xfer::readErr
   * @method private fileRead
   * @param string file filename
   * @param optional string dir directory where the file resides
   * @return boolean success
   */
  function fileRead($file,$dir="") {
    if ($this->mode!="import") return FALSE;
    if (!empty($dir) && !empty($file)) {
      if (substr($dir,strlen($dir))=="/") $file = $dir.$file;
        else $file = $dir."/".$file;
    }
    if ( empty($file) || !file_exists($file) ) {
      $this->readErr = $this->errorMsg( lang("no_restore_file") );
      return FALSE;
    }
    if ( !is_readable($file) ) {
      $this->readErr = $this->errorMsg( lang("backup_file_unreadable") );
      return FALSE;
    }
    $data = @file_get_contents($file);
    if (substr($data,0,3)!="PVP") {
      if ( ( !$data = @gzinflate(substr($data,10)) ) || (substr($data,0,3)!="PVP") ) {
        $this->readErr = $this->errorMsg( lang("backup_file_corrupt") );
        return FALSE;
      }
    }
    $pos  = strpos($data,"\n");
    $head = explode(" ",substr($data,0,$pos-1));
    $this->fileType = $head[1];
    $this->items = substr($head[3],1,strlen($head[3])-2);
    $this->data  = explode("\n",substr($data,$pos+1)); // kick off the header
    unset ($this->data[$this->items]); // kick off the empty last line
    return TRUE;
  }

  /** Send the (encoded) data from xfer::list for download to the browser and
   *  reset the list
   * @method private fileSend
   * @param string filename filename to offer for d/l
   * @param string type DataType ("Movie","SysConf")
   */
  function fileSend($filename,$type) {
    header("content-type: application/octet-stream");
    header("Content-Disposition: attachment; filename=$filename");
    $this->list = "PVP $type Backup: [".$this->items."] records\n".$this->list;
    if ($this->compress) echo gzencode($this->list);
      else echo $this->list;
    $this->list  = "";
    $this->items = 0;
    exit;
  }

  /** Store the (encoded) data to a file
   * @method fileStore
   * @param string filename filename to offer for d/l
   * @param string type DataType ("Movie","SysConf")
   * @return int bytes bytes stored (or FALSE on failure)
   */
  function fileStore($filename,$type) {
    if (!strlen($this->items)) return FALSE; // nothing to store
    $this->list = "PVP $type Backup: [".$this->items."] records\n".$this->list;
    $filename = $GLOBALS["backup_path"]."/".$filename;
    if ($this->compress) $rc = file_put_contents($filename,gzencode($this->list));
    else $rc = file_put_contents($filename,$this->list);
    $this->list  = "";
    $this->items = 0;
    return $rc;
  }

 #----------------------------------------------------------------[ Movies ]---
  /** Store movies from xfer::data into DB.
   *  How many movies could not be imported is stored to xfer::errors,
   *  error details are stored in (appended to) xfer::report
   * @method private moviePut
   * @param optional boolean append Whether we append to an existing or build a new DB
   * @param optional integer from_owner Only import movies owned by the given user
   * @param optional integer to_owner Let all imported movies be owned by the
   *  given user
   * @return boolean all_success (TRUE if all entries are imported sucessfully,
   *  FALSE otherwise)
   */
  function moviePut($append=TRUE,$from_owner="",$to_owner="") {
    if ($this->mode!="import") {
      $this->report .= "<li>".lang("xfer_wrong_mode","import",$this->mode);
      $this->errors = $this->items;
      return FALSE;
    }
    GLOBAL $db;
    $users = $db->get_users(); $uc = count($users);
    for ($i=0;$i<$uc;++$i) $owner[$users[$i]->id] = $users[$i]->login;
    $admin_id = array_search("admin",$owner);
    for ($i=0;$i<$this->items;++$i) {
      $movie = unserialize(urldecode($this->data[$i]));
      #--[ handle ownership ]--
      if ($from_owner!="" && $movie['owner_id']!=$from_owner) continue;
      if ($to_owner!="") $movie['owner_id'] = $to_owner;
      else {
        if (!array_key_exists($movie['owner_id'],$owner) && $admin_id!==FALSE) $movie['owner_id'] = $admin_id; // prevent orphans - own them to admin
      }
      #-- [ add staff members when necessary ]--
      if ($movie['director_id']) $movie['director_id'] = $db->check_person($movie['director_']['name'],$movie['director_']['firstname'],"directors",TRUE,$movie['director_mid']);
      if ($movie['music_id']) $movie['music_id'] = $db->check_person($movie['music_']['name'],$movie['music_']['firstname'],"music",TRUE,$movie['music_mid']);
      for ($k=1;$k<6;++$k) {
        $pset = "actor_$k"; $pid = "actor$k"."_id";
        if ($movie[$pid]) $movie[$pid] = $db->check_person($movie[$pset]['name'],$movie[$pset]['firstname'],"actors",TRUE,$movie['actor${i}_mid']);
      }
      #--[ add new cats if necessary ]--
      for ($k=1;$k<4;++$k) {
        $tcat = "cat$k"."int"; $tcatid = "cat$k"."_id";
        if (!empty($movie[$tcat]) && !$this->catlist[$movie[$tcat]]>0) {
          $db->add_category($movie[$tcat]);
          $db->set_translation($movie[$tcat],$movie["cat$k"],"en");
	  $movie[$tcatid] = $db->get_category_id($movie[$tcat]);
          $this->catlist[$movie[$tcat]] = $movie[$tcatid];
	  $this->report .= "<li>added category '".$movie[$tcat]."' (".$movie["cat$k"].")";
	}
      }
      #--[ take care for new audio and subtitle languages ]--
      for ($k=0;$k<count($movie['audio']);++$k) { // check audio_ts
        if ( ($movie['audio'][$k]) && !in_array($movie['audio'][$k],$this->audio) ) {
          $db->set_avlang($movie['audio'][$k],1,"audio");
          $this->audio[] = $movie['audio'][$k];
        }
      }
      for ($k=0;$k<count($movie['subtitle']);++$k) { // check subtitles
        if ( ($movie['subtitle'][$k]) && !in_array($movie['subtitle'][$k],$this->subtitle) ) {
          $db->set_avlang($movie['subtitle'][$k],1,"subtitle");
          $this->subtitle[] = $movie['subtitle'][$k];
        }
      }
      #--[ if we add to existing entries: beware media numbers! ]--
      if ($append) {
        #--[ make sure the mtype exists ]--
        $mts = $movie['mtype_short'];
        if ( $this->mtypes[$mts]->id ) {
          $movie['mtype_id'] = $this->mtypes[$mts]->id;
          $movie['mtype']    = $this->mtypes[$mts]->name;
        } else {
          $db->set_mtypes($movie['mtype'],$mts);
          $this->mtypes = $this->mkMtypes();
          $movie['mtype_id'] = $this->mtypes[$mts]->id;
        }
        #--[ generate new media number: add after last ]--
        $cid = $movie['cass_id'];
        if ( isset($newnum[$mts][$cid]) ) {
          $movie['cass_id'] = $newnum[$mts][$cid];
        } else {
          $lastnum = $db->get_lastmovienum($this->mtypes[$mts]->id);
          $movie['cass_id'] = ++$lastnum[0]['cass_id'];
          $newnum[$mts][$cid] = $movie['cass_id'];
        }
      }
      #--[ finally: do the real import! ]--
      if (!$db->add_movie($movie)) ++$this->errors;
    }
    if (!$this->errors) return TRUE;
    return FALSE;
  } // end of method moviePut

  /** Retrieve movie data from DB and store them encoded into xfer::list
   * @method private movieGet
   * @param integer id movie_id
   */
  function movieGet($id) {
    if ($this->mode!="export") return;
    GLOBAL $db;
    $movie = $db->get_movie($id);
    if ( !empty($movie) ) {
      $this->list .= urlencode(serialize($movie))."\n";
      ++$this->items;
    }
  }

 #---------------------------------------------------------------[ SysConf ]---
  /** Update system config and default preferences from backup file.
   *  Possible errors are logged to xfer::report, plus xfer::errors is
   *  incremented
   * @method private configPut
   * @return boolean success
   */
  function configPut() {
    GLOBAL $db;
    if ($this->mode!="import") {
      $this->report .= "<li>".lang("xfer_wrong_mode","import",$this->mode);
      $this->errors = $this->items;
      return FALSE;
    }
    for ($i=0;$i<$this->items;++$i) {
      $item = unserialize(urldecode($this->data[$i]));
      switch ($item->type) {
        case "config"  :
          unset($item->data["version"]);
          $err = 0;
          foreach ($item->data as $var=>$val) {
            if ( !$db->set_config($var,$val) ) ++$err;
          }
          if ($err) {
            ++$this->errors;
            $this->report .= "<li>".lang("configuration")."</li>";
          }
          break;
        case "syspref" :
          $err = 0;
          foreach ($item->data as $var=>$val) {
            if ( !$db->set_preferences($var,$val) ) ++$err;
          }
          if ($err) {
            ++$this->errors;
            $this->report .= "<li>".lang("preferences")."</li>";
          }
          break;
        case "printer" :
          if ( !$db->printerReplace($item->data) ) {
            $this->report .= "<li>".lang("printer")."</li>";
            ++$this->errors;
          }
          break;
        default        : continue; // skip unknown type
      }
    }
    return TRUE;
  }

  /** Retrieve Config from DB and store it into xfer::list
   * @method private configGet
   */
  function configGet() {
    GLOBAL $db;
    #--[ pvp_config ]--
    $conf = $db->get_config_all();
    $list->type = "config";
    $list->data = $conf;
    $this->list = urlencode(serialize($list))."\n";
    ++$this->items;
    #--[ preferences ]--
    $conf = $db->get_preferences_all("default");
    $list->type = "syspref";
    $list->data = $conf;
    $this->list .= urlencode(serialize($list))."\n";
    ++$this->items;
    #--[ printers ]--
    $conf = $db->get_printer();
    $list->type = "printer";
    $list->data = $conf;
    $this->list .= urlencode(serialize($list))."\n";
    ++$this->items;
  }

 #------------------------------------------------------------[ Categories ]---
  /** Update category data from backup.
   *  Possible errors are logged to xfer::report, plus xfer::errors is
   *  incremented
   * @method private catSet
   * @param boolean replace whether to replace existing data (TRUE) or just
   *  append new categories/translations (FALSE)
   * @return boolean success
   */
  function catPut($replace) {
    GLOBAL $db;
    if ($this->mode!="import") {
      $this->report .= "<li>".lang("xfer_wrong_mode","import",$this->mode);
      $this->errors = $this->items;
      return FALSE;
    }
    #--[ get available languages ]--
    $tlangs = $db->get_languages(1);
    $lc = count($tlangs);
    for ($i=0;$i<$lc;++$i) {
      $langs[$i] = $tlangs[$i]["id"];
    }
    unset($tlangs,$lc);
    for ($i=0;$i<$this->items;++$i) {
      $cat = unserialize(urldecode($this->data[$i]));
      #--[ add cat if not exists ]--
      if ( !$cid = $db->get_category_id($cat['internal']) ) {
        if ( !$db->add_category($cat['internal']) ) {
          $this->report .= "<li>failed adding category '".$cat['internal']."'</li>";
          ++$this->errors;
          continue;
        }
        $cid = $db->get_category_id($cat['internal']);
      }
      #--[ add/replace translations ]--
      $tcount = count($cat['trans']);
      foreach ($cat['trans'] as $var=>$val) {
        if ( in_array($var,$langs) ) { // only update installed langs
          $trans = $db->get_singletrans($var,"",$val);
          if ( empty($trans) || $replace ) {
            $db->set_translation($cat['internal'],$var,$val);
          }
        }
      }
    }
    if ($this->errors) return FALSE;
    return TRUE;
  }

  /** Retrieve Categories from DB and store them into xfer::list
   * @method private catGet
   */
  function catGet() {
    GLOBAL $db;
    $cats = $db->get_category();
    $ccount = count($cats);
    for ($i=0;$i<$ccount;++$i,++$this->items) {
      $cats[$i]['trans'] = $db->get_trans_all($cats[$i]['internal']);
      $this->list .= urlencode(serialize($cats[$i]))."\n";
    }
  }

 #================================================[ Configuration (public) ]===
  /** Enable data compression
   * @method public compressionOn
   */
  function compressionOn() {
    if (function_exists('gzencode'))
      $this->compress = TRUE;
    else $this->compressionOff();
  }

  /** Disable data compression
   * @method public compressionOff
   */
  function compressionOff() {
    $this->compress = FALSE;
  }

  /** Configure backups to be stored on disk
   * @method backupStore
   * @return boolean success
   */
  function backupStore() {
    if (is_writable($GLOBALS["backup_path"])) {
      $this->storeOnDisk = TRUE;
    } else {
      $this->storeOnDisk = FALSE;
    }
    return $this->storeOnDisk;
  }

  /** Configure backups to be sent to the browser
   * @method backupSend
   */
  function backupSend() {
    $this->storeOnDisk = FALSE;
  }

 #======================================================[ Actions (public) ]===
  /** Import data from a file
   * @method public fileImport
   * @param string file file name to import
   * @param optional string dir directory where the file is located (if not already
   *  given with param file)
   * @param optional boolean append whether to append to existing DB (default)
   *  or starting with a cleanup (FALSE)
   * @param optional integer from_owner Only import movies owned by the given user
   *  (only considered for filetype "Movie")
   * @param optional integer to_owner Let all imported movies be owned by the
   *  given user (only considered for filetype "Movie")
   * @return string save_result to display in browser
   */
  function fileImport($file,$dir="",$append=TRUE,$from_owner="",$to_owner="") {
    GLOBAL $pvp,$db;
    if ($from_owner!="" && preg_match('|[^0-9]|',$from_owner)) $from_owner="";
    if ($to_owner!="" && preg_match('|[^0-9]|',$to_owner)) $to_owner="";
    if ($this->mode!="import") return FALSE;
    if (!$this->lockDB()) // Lock DB before import
      return $this->errorMsg( lang("db_lock_failed") );

    if ( !$append ) { // we have to purge first
      if ( $pvp->auth->admin ) { // admin may purge everything
        if ( $to_owner==="" ) {
          if ( !$db->drop_all_movies() ) return $this->ureturn( $this->errorMsg( lang("movie_drop_failed") ) );
        } else {
          if ( !$db->user_media_delete($to_owner) )
            return $this->ureturn( $this->errorMsg ( lang("movie_drop_failed") ) );
        }
      } else { // user has only permission on own records here
        if ( $to_owner==="" || $to_owner != $pvp->auth->user_id ) {
          return $this->ureturn( $this->errorMsg( lang("db_clean_admin_required") ) );
        } else {
          if ( !$db->user_media_delete($pvp->auth->user_id ) )
            return $this->ureturn( $this->errorMsg ( lang("movie_drop_failed") ) );
        }
      }
    } // end purge

    if (!empty($dir) && !empty($file)) {
      if (substr($dir,strlen($dir))=="/") $file = $dir.$file;
        else $file = $dir."/".$file;
    }
    if ( !$this->fileRead($file) ) return $this->readErr;
    switch ($this->fileType) {
      case "SysConf" :
        if ($this->configPut()) $this->ureturn( $this->okMsg( lang("imp_success",$this->items) ) );
          else {
          $msg = lang("imp_errors",$this->errors,$this->items);
          if ( debugLevel("R") ) $msg .= "Errors:<UL>".$this->report."</UL>";
          return $this->ureturn( $this->errorMsg($msg) );
        }
        break;
      case "Cats"    :
        if ($this->catPut(!$append)) {
          return $this->ureturn( $this->okMsg( lang("imp_success",$this->items) ) );
        } else {
          $msg = lang("imp_errors",$this->errors,$this->items);
          if ( debugLevel("R") ) $msg .= "Errors:<UL>".$this->report."</UL>";
          return $this->ureturn( $this->errorMsg($msg) );
        }
        break;
      case "Movie"   :
        if ($this->moviePut($append,$from_owner,$to_owner)) {
          return $this->ureturn( $this->okMsg( lang("imp_success",$this->items) ) );
        } else {
          $msg = lang("imp_errors",$this->errors,$this->items);
          if ( debugLevel("R") ) $msg .= "<UL>".$this->report."</UL>";
          return $this->ureturn( $this->errorMsg($msg) );
        }
        break;
      default       : return $this->ureturn( $this->errorMsg( lang("xfer_unknown_filetype") ) );
    }
  }

  /** Export data to file (and send file to browser for d/l)
   * @method public fileExport
   * @param string mode What to export: "Movie"[, "Config", "Prefs"]
   * @param optional integer id movie id (if not given, export all)
   * @param optional integer owner_id (if not given, export for all)
   * @return int bytes (only when storing to disk)
   */
  function fileExport($mode,$id="",$owner_id="") {
    GLOBAL $db;
    if (!$this->lockDB()) // Lock DB before export
      return $this->errorMsg( lang("db_lock_failed") );
    $stamp = date('ymd');
    switch ($mode) {
      case "SysConf": $this->configGet(); $name="sysconf"; break;
      case "Cats"   : $this->catGet(); $name="cats"; break;
      case "Movie"  :
      default       :
        if ($id) {
          $this->movieGet($id);
        } else {
          $mlist  = $db->get_movieids_all($owner_id);
          $mcount = count($mlist);
          for ($i=0;$i<$mcount;++$i) {
            $this->movieGet($mlist[$i]);
          }
        }
        $name = "movies";
        break;
    }
    $this->unlockDB();
    if ($owner_id=="")
      $file = $name."_".$stamp.".pvp";
    else {
      $users = $db->get_users($owner_id);
      $file = $name."_".$users->login."_".$stamp.".pvp";
    }
    if ($this->storeOnDisk) return $this->fileStore($file,$mode);
    else $this->fileSend($file,$mode);
  }

  /** List up available user backups
   * @method listUserBackups
   * @param string login the users login
   * @return array files array of filenames from the backup directory
   */
  function listUserBackups($user) {
    $files = array();
    $dir = dir($GLOBALS["backup_path"]);
    while ( $file=$dir->read() ) {
      if (strpos($file,"movies_${user}")===0) $files[] = $file;
    }
    return($files);
  }

 } // end class
?>