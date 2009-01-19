<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2009 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Maintain the (DB-stored) user preferences                                 #
 #############################################################################

 /* $Id$ */

 /** Maintain the (DB-stored) user's preferences
  * @package Api
  * @class preferences
  * @author Izzy (izzysoft AT qumran DOT org)
  * @copyright (c) 2001-2009 by Itzchak Rehberg and IzzySoft
  */

 class preferences {
  var $admin, $colors, $filter, $lang, $template,
      $display_limit, $date_format, $page_length;
  
  ############################################################################
  /** Constructor: reads all values from DB
   * @constructor preferences
   */
  function preferences() {
    GLOBAL $db,$pvp;
    $pnames = array ("lang","template","display_limit","date_format",
              "page_length","default_movie_colorid","default_movie_onlabel",
	      "default_movie_toneid","printer_id","imdb_url","imdb_url2",
              "imdb_tx_title","imdb_tx_year","imdb_tx_pg","imdb_tx_length",
              "imdb_tx_cat","imdb_tx_director","imdb_tx_actor","imdb_tx_comments",
              "imdb_tx_country","imdb_txwin_autoclose","imdb_tx_music",
              "default_movie_langid","default_movie_pictid","bubble_help_enable",
              "showuser","default_vnorm_id","default_pstemplate_id");
    foreach ($pnames as $var) {
      $this->$var = $db->get_preferences($var);
    }
    $this->filter = $this->get_filters();
  }

  ############################################################################
  /** (un)set the admin mode
   * @class preferences
   * @method admin
   * @param optional boolean mode admin mode
   */
  function admin($mode=1) {
    $this->admin = $mode;
  }

  #################################################[ set/get preferences ]####
  /** Set a preference
   * @class preferences
   * @method set
   * @param string name preference to set
   * @param mixed value
   */
  function set($name,$value) {
    GLOBAL $db, $pvp;
    if ($this->admin) {
      $db->set_preferences($name,$value);
    } else {
      if ($pvp->cookie->active) {
        $pvp->cookie->set($name,$value);
      } else {
        $db->set_preferences($name,$value,$pvp->auth->user_id);
      }
    }
  }

  /** Get a preference
   * @class preferences
   * @method get
   * @param string name preference to set
   */
  function get($name) {
    GLOBAL $pvp,$db;
    if ($this->admin) {
      return $this->$name;
    } else {
      if ($pvp->cookie->active) {
        $pref = $pvp->cookie->get($name);
        if (strlen($pref)) {
          if ($name=="lang") $pref = substr($pref,0,2); # Work around Konqueror Cookie bug
          return($pref); 
        } else {
          if (isset($pvp->auth->user_id))
            $pref = $db->get_preferences($name,$pvp->auth->user_id);
          if (isset($pref) && strlen($pref)) {
            if ($name=="lang") $pref = substr($pref,0,2); # Work around Konqueror Cookie bug
            return($pref); 
	  } else {
           if (isset($this->$name)) return $this->$name;
           return FALSE;
          }
	}
      } else {
          if (isset($pvp->auth->user_id))
	    $pref = $db->get_preferences($name,$pvp->auth->user_id);
          if (isset($pref) && strlen($pref)) {
            if ($name=="lang") $pref = substr($pref,0,2); # Work around Konqueror Cookie bug
            return($pref); 
	  } else { return $this->$name; }
      }
    }
  }


  ##############################################[ set/get imdb_tx options ]###
  /** Set imdb_tx preferences
   * @method imdb_tx_set
   * @param array imdb_arr (name:=value)
   */
  function imdb_tx_set($imdb_arr) {
    GLOBAL $pvp,$db;
    if ($this->admin) {
      foreach ($imdb_arr as $var=>$val) {
        $db->set_preferences($var,$val);
      }
    } else {
      if ($pvp->cookie->active) {
        $pvp->cookie->set("imdb_tx",rawurlencode(serialize($imdb_arr)));
      } else {
        foreach ($imdb_arr as $var=>$val) {
          $db->set_preferences($var,$val,$pvp->auth->user_id);
        }
      }
    }
  }

  /** Get imdb_tx preferences
   * @method imdb_tx_get
   * @return array imdb_tx (var:=value)
   */
  function imdb_tx_get() {
    GLOBAL $pvp,$db;
    if ($this->admin) {
      return $db->imdb_tx_setup();
    } else {
      if ($pvp->cookie->active) {
        $raw = $pvp->cookie->get("imdb_tx");
        if (empty($raw)) return $db->imdb_tx_setup();
        return unserialize( rawurldecode( $raw ) );
      } else {
        return $db->imdb_tx_setup($pvp->auth->user_id);
      }
    }
  }

  ##############################################################[ filters ]###
  /** get id for a filter part (helper to get_filters())
   * @class preferences
   * @method get_id
   * @param integer found counter
   * @param string fname filter name
   * @param string tname table name
   * @return string SQL filter part for WHERE clause
   */
  function get_fquery(&$found,$fname,$tname="") {
   GLOBAL $db, $filter;
   if ( !strlen($tname) ) $tname=$fname;
   $db->query("SELECT id FROM $tname");
   $query = "";
   while ( $db->next_record() ) {
     $id   = $db->f('id');
     if ( isset($filter->$fname->$id) && $filter->$fname->$id ) {
       if ($found) { $query .=  " OR v." . $fname . "_id='$id'";
       } else { $query = " v." . $fname . "_id='$id'"; }
       $found++;
     }
   }
   if ($found>1) $query = " (" . $query . " )";
   return $query;
  }

  /** Retrieve the filter object either from cookie or DB (helper to get_filters())
   * @class preferences
   * @method retrieve_filter
   * @return object filter (urlencoded and serialized)
   */
  function retrieve_filter($user_id="") {
    GLOBAL $pvp,$db;
    if ($pvp->cookie->active && !$this->admin) {
      $pref = $pvp->cookie->get("filter");
      if (strlen($pref)) { return($pref); }
        else { return $db->get_preferences("filter",$user_id); }
    } else {
      return $db->get_preferences("filter",$user_id);
    }
  }

  /** get filter settings from db
   * @class preferences
   * @method get_filters
   * @return string SQL filter part for WHERE clause
   */
  function get_filters() {
   global $db, $filter;
   $filter = $this->retrieve_filter();
   if ( strlen($filter) ) { // there are already filters defined
     $filter = unserialize ( rawurldecode($filter) );
     $i=0;
     if ($filter->length_min)  { $sql[$i] = " v.length>'" . $filter->length_min . "'"; $i++; }
     if ($filter->length_max)  { $sql[$i] = " v.length<'" . $filter->length_max . "'"; $i++; }
     if ($filter->aquired_min) { $sql[$i] = " v.aq_date>'" . $filter->aquired_min . "'"; $i++; }
     if ($filter->aquired_max) { $sql[$i] = " v.aq_date<'" . $filter->aquired_max . "'"; $i++; }
     if ($filter->fsk_min)     { $sql[$i] = " v.fsk>'" . $filter->fsk_min . "'"; $i++; }
     if ($filter->fsk_max)     { $sql[$i] = " v.fsk<'" . $filter->fsk_max . "'"; $i++; }
     if ($filter->title)       { $sql[$i] = " v.title like '%" . $filter->title . "%'"; $i++; }
     $found = 0;
     // -----------[ mtype ]---
     $temp = $this->get_fquery($found,"mtype","pvp_mtypes");
     if ($found) { $sql[$i] = $temp; $found=0; $i++; }
     // -----------[ pict ]---
     $temp = $this->get_fquery($found,"pict","pvp_pict");
     if ($found) { $sql[$i] = $temp; $found=0; $i++; }
     // -----------[ color ]---
     $temp = $this->get_fquery($found,"color","pvp_colors");
     if ($found) { $sql[$i] = $temp; $found=0; $i++; }
     // -----------[ tone ]---
     $temp = $this->get_fquery($found,"tone","pvp_tone");
     if ($found) { $sql[$i] = $temp; $found=0; $i++; }
     // -----------[ director ]---
     $temp = $this->get_fquery($found,"director","directors");
     if ($found) { $sql[$i] = $temp; $found=0; $i++; }
     // -----------[ composer ]---
     $db->query("SELECT id FROM music");
     while ( $db->next_record() ) {
       $id   = $db->f('id');
       if ( isset($filter->composer->$id) && $filter->composer->$id) {
         if ($found) { $sql[$i] .=  " OR v.music_id='$id'";
         } else { $sql[$i] = " v.music_id='$id'"; }
         $found++;
       }
     }
     if ($found>1) $sql[$i] = " (" . $sql[$i] . " )";
     if ($found) { $found=0; $i++; }
     // -----------[ actor ]---
     $db->query("SELECT id FROM actors");
     while ( $db->next_record() ) {
       $id   = $db->f('id');
       if ( isset($filter->actor->$id) && $filter->actor->$id) {
         if ($found) { $sql[$i] .=  " OR v.actor1_id='$id' OR v.actor2_id='$id' OR v.actor3_id='$id' OR v.actor4_id='$id' OR v.actor5_id='$id'";
         } else { $sql[$i] = " v.actor1_id='$id' OR v.actor2_id='$id' OR v.actor3_id='$id' OR v.actor4_id='$id' OR v.actor5_id='$id'"; }
         $found++;
       }
     }
     if ($found>1) $sql[$i] = " (" . $sql[$i] . " )";
     if ($found) { $found=0; $i++; }
     // -----------[ category ]---
     $db->query("SELECT id FROM cat");
     while ( $db->next_record() ) {
       $id   = $db->f('id');
       if ( isset($filter->cat->$id) && $filter->cat->$id) {
         if ($found) { $sql[$i] .=  " OR v.cat1_id='$id' OR v.cat2_id='$id' OR v.cat3_id='$id'";
         } else { $sql[$i] = " v.cat1_id='$id' OR v.cat2_id='$id' OR v.cat3_id='$id'"; }
         $found++;
       }
     }
     if ($found>1) $sql[$i] = " (" . $sql[$i] . " )";
     if ($found) { $found=0; $i++; }
     // -----------[ finnished. ]---
     if ($i) {
       $i--;
       $where = $sql[0];
       for ($i=1;$i<count($sql);$i++) {
         $where .= " AND" . $sql[$i];
       }
       return $where;
     }
     // if we get here, the filter is empty
   }
   // if we get here, there's no filter defined
   return "";
  } // end get_filters()

  /** Which collections the user wants to see?
   * @method get_owner_filter
   * @return string owner_ids for WHERE..IN clause or empty string
   */
  function get_owner_filter() {
   $filter = $this->retrieve_filter();
   if ( strlen($filter) ) { // there are already filters defined
     $filter = unserialize ( rawurldecode($filter) );
     if (empty($filter->showuser)) return "";
     return implode(",",$filter->showuser);
    }
  }

 /** Color settings for HTML code
  * @class preferences
  * @attribute array colors
  */
 /** Filter settings for DB queries
  * @class preferences
  * @attribute object filter
  * @version object description:<pre>
  * $filter->mtype       (Array of $id)
  * $filter->length_min  (int)
  * $filter->length_max  (int)
  * $filter->aquired_min (int)
  * $filter->aquired_max (int)
  * $filter->pict        (Array of $id)
  * $filter->color       (Array of $id)
  * $filter->tone        (Array of $id)
  * $filter->lp          (Boolean)
  * $filter->fsk_min     (int)
  * $filter->fsk_max     (int)
  * $filter->title       (String)
  * $filter->cat         (Array of $id)
  * $filter->actor       (Array of $id)
  * $filter->director    (Array of $id)
  * $filter->composer    (Array of $id)</pre>
  */
 /** Default language for translation system
  * @class preferences
  * @attribute string lang
  */
 /** Default template directory
  * @class preferences
  * @attribute string template
  */
 /** Datasets per page
  * @class preferences
  * @attribute integer display_limit
  */
 /** Date format to use
  * @class preferences
  * @attribute string date_format
  */
 /** Lines per page (for printing)
  * @class preferences
  * @attribute integer page_length
  */

 } // end class preferences

?>
