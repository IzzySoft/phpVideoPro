<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
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
  * @author Izzy (izzysoft@qumran.org)
  * @copyright (c) 2001-2004 by Itzchak Rehberg and IzzySoft
  */
 class xfer {

  /** Initialization
   * @constructor xfer
   * @param string mode ("import" or "export")
   */
  function xfer($mode) {
    $this->compressionOff();
    $this->mode = $mode;
    switch ($mode) {
      case "import" : $this->initImport(); break;
      case "export" : $this->initExport(); break;
      default : die("Wrong mode for Xfer Module: '$mode'!");
    }
  }

 #====================================================[ Helpers (private!) ]===
  /** Initialize data arrays for imports
   * @class xfer
   * @method private initImport
   */
  function initImport() {
    GLOBAL $db;
    $this->data   = ""; // imported file (array of strings)
    $this->list   = "";
    $this->items  = 0;
    $this->errors = 0;
    $this->report = "";
    $this->avlTypes = array("audio","subtitle");
    $this->audio    = $this->mkavlang("audio");
    $this->subtitle = $this->mkavlang("subtitle");
    $this->mtypes   = $this->mkMtypes();
    $tcatlist = $db->get_category();
    $catcount = count($tcatlist);
    for ($i=0;$i<$catcount;++$i) {
      $this->catlist[$tcatlist[$i][internal]] = $tcatlist[$i][id];
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

  /** format error message
   * @class xfer
   * @methode private errorMsg
   * @param string msg
   * @return string formated msg
   */
  function errorMsg($msg) {
    return "<SPAN CLASS='error'>$msg</SPAN>";
  }

  /** format OK message
   * @class xfer
   * @methode private okMsg
   * @param string msg
   * @return string formated msg
   */
  function okMsg($msg) {
    return "<SPAN CLASS='ok'>$msg</SPAN>";
  }

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
       $id = $mt[$i][sname];
       $mtype[$id]->id   = $mt[$i][id];
       $mtype[$id]->name = $mt[$i][name];
     }
     return $mtype;
   }

  /** Read a file from disk
   * @class xfer
   * @method private fileRead
   * @param string file filename
   * @param optional string dir directory where the file resides
   * @return boolean success
   * @version on error, the formated error message is stored in xfer::readErr
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

  /** Store movies from xfer::data into DB
   * @class xfer
   * @method private moviePut
   * @param boolean append Whether we append to an existing or build a new DB
   * @return 
   * @version How many movies could not be imported is stored to xfer::errors,
   *  error details are stored in (appended to) xfer::report
   */
  function moviePut($append=TRUE) {
    if ($this->mode!="import") {
      $this->report .= "<li>".lang("xfer_wrong_mode","import",$this->mode);
      $this->errors = $this->items;
      return $this->items;
    }
    GLOBAL $db;
    for ($i=0;$i<$this->items;++$i) {
      $movie = unserialize(urldecode($this->data[$i]));
      if ($movie[director_id]) $movie[director_id] = $db->check_person($movie[director_][name],$movie[director_][firstname],"directors",TRUE);
      if ($movie[music_id]) $movie[music_id] = $db->check_person($movie[music_][name],$movie[music_][firstname],"music",TRUE);
      for ($k=1;$k<6;++$k) {
        $pset = "actor_$k"; $pid = "actor$k"."_id";
        if ($movie[$pid]) $movie[$pid] = $db->check_person($movie[$pset][name],$movie[$pset][firstname],"actors",TRUE);
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
      for ($k=0;$k<count($movie[audio]);++$k) { // check audio_ts
        if ( ($movie[audio][$k]) && !in_array($movie[audio][$k],$this->audio) ) {
          $db->set_avlang($movie[audio][$k],1,"audio");
          $this->audio[] = $movie[audio][$k];
        }
      }
      for ($k=0;$k<count($movie[subtitle]);++$k) { // check subtitles
        if ( ($movie[subtitle][$k]) && !in_array($movie[subtitle][$k],$this->subtitle) ) {
          $db->set_avlang($movie[subtitle][$k],1,"subtitle");
          $this->subtitle[] = $movie[subtitle][$k];
        }
      }
      #--[ if we add to existing entries: beware media numbers! ]--
      if ($append) {
        #--[ make sure the mtype exists ]--
        $mts = $movie[mtype_short];
        if ( $this->mtypes[$mts]->id ) {
          $movie[mtype_id] = $this->mtypes[$mts]->id;
          $movie[mtype]    = $this->mtypes[$mts]->name;
        } else {
          $db->set_mtypes($movie[mtype],$mts);
          $this->mtypes = $this->mkMtypes();
          $movie[mtype_id] = $this->mtypes[$mts]->id;
        }
        #--[ generate new media number: add after last ]--
        $cid = $movie[cass_id];
        if ( isset($newnum[$mts][$cid]) ) {
          $movie[cass_id] = $newnum[$mts][$cid];
        } else {
          $lastnum = $db->get_lastmovienum($this->mtypes[$mts]->id);
          $movie[cass_id] = ++$lastnum[0][cass_id];
          $newnum[$mts][$cid] = $movie[cass_id];
        }
      }
      #--[ finally: do the real import! ]--
      if (!$db->add_movie($movie)) ++$this->errors;
    }
    if (!$this->errors) return TRUE;
    return FALSE;
  } // end of method moviePut

  /** Retrieve movie data from DB and store them encoded into xfer::list
   * @class xfer
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

  /** Send the (encoded) data from xfer::list for download to the browser and
   *  reset the list
   * @class xfer
   * @method private fileSend
   * @param string filename filename to offer for d/l
   */
  function fileSend($filename) {
    header("content-type: application/octet-stream");
    header("Content-Disposition: attachment; filename=$filename");
    $this->list = "PVP Movie Backup: [".$this->items."] records\n".$this->list;
    if ($this->compress) echo gzencode($this->list);
      else echo $this->list;
    $this->list  = "";
    $this->items = 0;
  }

 #================================================[ Configuration (public) ]===
  /** Enable data compression
   * @class xfer
   * @method public compressionOn
   */
  function compressionOn() {
    $this->compress = TRUE;
  }

  /** Disable data compression
   * @class xfer
   * @method public compressionOff
   */
  function compressionOff() {
    $this->compress = FALSE;
  }

 #======================================================[ Actions (public) ]===
  /** Import data from a file
   * @class xfer
   * @method public fileImport
   * @param string file file name to import
   * @param optional dir directory where the file is located (if not already
   *  given with param file)
   * @param optional boolean append whether to append to existing DB (default)
   *  or starting with a cleanup (FALSE)
   * @return string save_result to display in browser
   */
  function fileImport($file,$dir="",$append=TRUE) {
    GLOBAL $pvp,$db;
    if ($this->mode!="import") return FALSE;
    if ( !$append ) {
      if ( !$pvp->auth->admin )
        return $this->errorMsg( lang("db_clean_admin_required") );
      if ( !$db->drop_all_movies() ) return $this->errorMsg( lang("movie_drop_failed") );
    }
    if (!empty($dir) && !empty($file)) {
      if (substr($dir,strlen($dir))=="/") $file = $dir.$file;
        else $file = $dir."/".$file;
    }
    if ( !$this->fileRead($file) ) return $this->readErr;
    switch ($this->fileType) {
      case "Movie"  :
        if ($this->moviePut($append)) {
          return $this->okMsg( lang("imp_success",$this->items) );
        } else {
          $msg = lang("imp_errors",$this->errors,$this->items);
          if ( debugLevel("R") ) $msg .= "<UL>".$this->report."</UL>";
          return $this->errorMsg($msg);
        }
        break;
      default       : return $this->errorMsg( lang("xfer_unknown_file_type") );
    }
  }

  /** Export data to file (and send file to browser for d/l)
   * @class xfer
   * @method public fileExport
   * @param string mode What to export: "Movie"[, "Config", "Prefs"]
   * @param optional integer id movie id (if not given, export all)
   */
  function fileExport($mode="Movie",$id="") {
    GLOBAL $db;
    $stamp = date('ymd');
    switch ($mode) {
      case "Movie"  :
      default       :
        $file = "movies_".$stamp.".pvp";
        if ($id) { $this->movieGet($id);
        } else {
          $mlist  = $db->get_movieids_all();
          $mcount = count($mlist);
          for ($i=0;$i<$mcount;++$i) {
            $this->movieGet($mlist[$i]);
          }
        }
    }
    $this->fileSend($file);
  }

 } // end class
?>