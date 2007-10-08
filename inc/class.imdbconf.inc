<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # IMDB handling - configuration                                             #
 # ------------------------------------------------------------------------- #
 # Taken from IMDBPHP, (c) by Giorgos Giagas                                 #
 #############################################################################

 /* $Id$ */

 #==========================================================[ IMDB_config ]===
 /** Configuration for IMDB access
  * @package Api
  * @class imdb_config
  */
 class imdb_config {
  var $imdbsite;
  var $cachedir;
  var $usecache;
  var $storecache;
  var $cache_expire;
  var $photodir;
  var $photoroot;

  /** Initialization
   * @constructor imdb_config
   */	
  function imdb_config(){
   GLOBAL $pvp,$base_path,$base_url,$db;
   $imdbsite = $pvp->preferences->get("imdb_url");
   $url  = explode("/",$imdbsite);
   $this->imdbsite = $url[count($url)-2];
   $cachedir = $db->get_config("imdb_cache_dir");
   if ($pvp->config->os_slash == "\\") $cachedir = str_replace("\\","/",$cachedir);
   if (strpos($cachedir,"/")!==0) $cachedir = $base_path.$cachedir;
   if (strrpos($cachedir,"/")!=strlen($cachedir)-1) $cachedir .= "/";
   $this->cachedir = $cachedir;
   $this->storecache = $db->get_config("imdb_cache_enable");
   $this->usecache = $db->get_config("imdb_cache_use");
   $this->cache_expire = $db->get_config("imdb_cache_expire");
   $this->photodir = $pvp->config->imdb_photopath;
   $this->photoroot = $pvp->config->imdb_photourl;
  }
 }

?>
