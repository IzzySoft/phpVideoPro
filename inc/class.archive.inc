<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2010 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Handling of archived files                                                #
 #############################################################################

/** Unpack .tar .gz .bz2 .tar.gz .tgz .tar.bz2 archives
 * @package Api
 * @class archive
 * @brief adapted from a collection of functions written by Dennis Wronka
 *  in his Tutorial at http://www.tutorials.de/forum/php-tutorials/215261-dekompression-mit-php.html
 * @version $Revision$ $Date$
 */
class archive {

  /** Constructor
   * @constructor archive
   * @param optional boolean quiet whether to log actions to screen
   * @param optional boolean log Format of logging: text|html
   */
  function archive($quiet=TRUE,$log="html") {
    $this->quiet = $quiet;
    $this->log   = $log;
    if (substr(php_uname(), 0, 7) == "Windows") $this->slash = "\\";
    else $this->slash = "/";
  }

  /** Alter the logging mode
   * @method logmode
   * @param string mode logmode (on|off|text|html)
   */
  function set_logmode($mode) {
    switch ($mode) {
      case "off"  : $this->quiet = TRUE; break;
      case "on"   : $this->quiet = FALSE; break;
      case "text" : $this->log = "text"; $this->quiet = FALSE; break;
      case "html" : $this->log = "html"; $this->quiet = FALSE; break;
    }
  }

  /** Action logging
   * @method private log
   * @param string msg What to log
   * @param optional boolean force forces output even if $quiet is TRUE (for error reporting)
   */
  function log($msg,$force=FALSE) {
    if ($this->quiet && !$force) return;
    switch ($this->log) {
      case "text" : echo "$msg\n"; break;
      case "html" : echo "$msg<br>"; break;
      default     : echo $msg; break;
    }
  }

  /** Check directory name syntax
   * @method private check_dirname
   * @param string dirname
   * @return string dirname
   */
  function check_dirname ($dir) {
    if (empty($dir)) return '';
    if ( strrpos($dir,$this->slash)!=strlen($dir)-1
       || strrpos($dir,$this->slash)===FALSE) $dir .= $this->slash;
    return $dir;
  }

  /** Untar the tarball
   * @method untar
   * @param string tarfile filename of the tarball to unpack
   * @param optional string dir Target dir to extract to (default: CWD)
   *   if this directory does not exist, we try to create it. If it cannot
   *   be created, the method returns FALSE
   * @return boolean success
   */
  function untar($tarfile,$dir="") {
    if (!empty($dir)) {
      if (!is_dir($dir)) {
        log("Creating target directory $dir");
        if (!mkdir($dir)) {
          log("Could not create target directory - abort!",TRUE);
          return FALSE;
        }
      }
      $dir = $this->check_dirname($dir);
    }
    $tarfile=@fopen($tarfile,"r");
    if (!$tarfile) return FALSE; // failed opening file
    $datainfo="";
    $data="";
    while (!feof($tarfile)) {
      $readdata=fread($tarfile,512);
      if (substr($readdata,257,5)=="ustar") {
        if (!empty($datainfo)) {
          $poscount=0;
          $name="";
          while (substr($datainfo,$poscount,1)!=chr(0)) {
            $name.=substr($datainfo,$poscount,1);
            $poscount++;
          }
          if (!empty($name)) {
            if (substr($name,-1)=="/") {
              $this->log("Creating ".$name);
              mkdir($dir.$name);
            } else {
              $this->log("Extracting ".$name);
              $datasize=strlen($data)-1;
              while ((substr($data,$datasize,1)==chr(0)) && ($datasize>-1)) {
                $datasize--;
              }
              $datasize++;
              $filedata="";
              for ($datacount=0;$datacount<$datasize;$datacount++) {
                $filedata.=substr($data,$datacount,1);
              }
              $file=fopen($dir.$name,"w");
              fwrite($file,$filedata);
              fclose($file);
            }
          }
          $datainfo=$readdata;
          $data="";
        } else {
          $datainfo=$readdata;
        }
      } else {
        $data.=$readdata;
      }
    }
    if (!empty($datainfo)) {
      $poscount=0;
      $name="";
      while (substr($datainfo,$poscount,1)!=chr(0)) {
        $name.=substr($datainfo,$poscount,1);
        $poscount++;
      }
      if (!empty($name)) {
        if (substr($name,-1)=="/") {
          $this->log("Creating ".$name);
          mkdir($dir.$name);
        } else {
          $this->log("Extracting ".$name);
          $datasize=strlen($data)-1;
          while ((substr($data,$datasize,1)==chr(0)) && ($datasize>-1)) {
            $datasize--;
          }
          $datasize++;
          $filedata="";
          for ($datacount=0;$datacount<$datasize;$datacount++) {
            $filedata.=substr($data,$datacount,1);
          }
          $file=fopen($dir.$name,"w");
          fwrite($file,$filedata);
          fclose($file);
        }
      }
      $datainfo=$readdata;
      $data="";
    }
    fclose($tarfile);
    return TRUE;
  }

  /** Get the name of the TAR file contained in the gz/bz archive
   * @method getuncompressedfilename
   * @param string compressedfilename
   * @return string uncompressedfilename
   * @brief If the compressedfilename starts with http:, https:, ftp:,
   *        or ftps:, uncompressedfilename will just be the filename, i.e.
   *        the path will be stripped off. Otherwise, the pathname will be
   *        kept intact. This means, when unpacking directly from the web,
   *        we do not write to the remote server (not supported with http).
   */
  function getuncompressedfilename($compressedfilename) {
    $compressedfilenameparts=explode(".",$compressedfilename);
    for ($count=0;$count<count($compressedfilenameparts)-1;$count++) {
      $uncompressedfilenameparts[]=$compressedfilenameparts[$count];
    }
    if ($compressedfilenameparts[count($compressedfilenameparts)-1]=="tgz") {
      $uncompressedfilenameparts[]="tar";
    }
    $uncompressedfilename=implode(".",$uncompressedfilenameparts);
    if (strpos($uncompressedfilename,"http:")===0
     || strpos($uncompressedfilename,"https:")===0
     || strpos($uncompressedfilename,"ftp:")===0
     || strpos($uncompressedfilename,"ftps:")===0) {
      $pos = strrpos($uncompressedfilename,$this->slash);
      $uncompressedfilename = substr($uncompressedfilename,$pos+1);
    }
    return $uncompressedfilename;
  }

  /** Unpack BZip2 Archive
   * @method unbzip2
   * @param string bz2file name of the archive
   * @return boolean success
   */
  function unbzip2($bz2file,$dir) {
    $content="";
    $file=@bzopen($bz2file,"r");
    if (!$file) return FALSE;
    while (!feof($file)) {
      $content.=bzread($file,1);
    }
    bzclose($file);
    $fname = $this->check_dirname($dir).$this->getuncompressedfilename($bz2file);
    $file=@fopen($fname,"w");
    if (!$file) return FALSE;
    fwrite($file,$content);
    fclose($file);
    return TRUE;
  }

  /** Upack GZip Archive
   * @method ungzip
   * @param string gzfile name of the archive to unpack
   * @param optional string dir target directory (default: CWD)
   * @return boolean success
   */
  function ungzip($gzfile,$dir="") {
    $content="";
    $file=@gzopen($gzfile,"r");
    if (!$file) return FALSE;
    while (!gzeof($file)) {
      $content.=gzread($file,1);
    }
    gzclose($file);
    $fname = $this->check_dirname($dir).$this->getuncompressedfilename($gzfile);
    $file=@fopen($fname,"w");
    if (!$file) return FALSE;
    fwrite($file,$content);
    fclose($file);
    return TRUE;
  }

  /** Obtain the archive type
   *  This method detects the archive type by the file extension
   * @method getarchivetype
   * @param string filename
   * @return string archivetype (gzip|bzip2|tar)
   */
  function getarchivetype($filename) {
    $archivetype="unknown";
    $filenameparts=explode(".",$filename);
    if (($filenameparts[count($filenameparts)-1]=="gz") || ($filenameparts[count($filenameparts)-1]=="tgz")) {
      $archivetype="gzip";
    } elseif ($filenameparts[count($filenameparts)-1]=="bz2") {
      $archivetype="bzip2";
    } elseif ($filenameparts[count($filenameparts)-1]=="tar") {
      $archivetype="tar";
    }
    return $archivetype;
  }

  /** Extract a given archive
   *  This is the main method which calls all others automatically when required.
   * @method unpack
   * @param string archive name of the archive
   * @param optional string dir target directory (default: CWD)
   * @return boolean success
   */
  function unpack($archive,$dir="") {
    $type = $this->getarchivetype($archive);
    if ($type!="unknown") {
      if ($type!="tar") {
        $this->log("Decompressing ".$archive);
        if ($type=="gzip") {
          if (!$this->ungzip($archive,$dir)) return FALSE;
        } elseif ($type=="bzip2") {
          if (!$this->unbzip2($archive,$dir)) return FALSE;
        }
        $uncompressedname = $this->check_dirname($dir).$this->getuncompressedfilename($archive);
        if ($this->getarchivetype($uncompressedname)=="tar") {
          $this->untar($uncompressedname,$dir);
          unlink($uncompressedname);
        } elseif (!empty($dir) && is_dir($dir)) {
#          copy($uncompressedname,$dir);
          unlink($uncompressedname);
        }
      } else {
        $this->untar($archive,$dir);
      }
    }
    return TRUE;
  }

}

?>