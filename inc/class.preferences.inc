<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Maintain the (DB-stored) user preferences                                 *
 \***************************************************************************/

 /* $Id$ */

 class preferences {
  var $colors, $filter, $lang, $template,
      $display_limit, $date_format, $page_length;
  
  ############################################################################
  # constructor: read all values from DB
  function preferences() {
    GLOBAL $db;
    $pnames = array ("lang","template","display_limit","date_format",
              "page_length");
    foreach ($pnames as $var) {
      $this->$var = $db->get_preferences($var);
    }
    $colors = $db->get_preferences('colors');
    if ($colors) {
      $colors = unserialize( rawurldecode($colors) );
      $this->colors = $colors;
      $colors["ok"] = "<FONT COLOR=\"" . $colors["ok"] . "\">";
      $colors["err"] = "<FONT COLOR=\"" . $colors["err"] . "\">";
      $GLOBALS['colors'] = $colors;
    }
    $this->filter = $this->get_filters();
  }

  ############################################################################
  # set a preference
  function set($name,$value) {
    GLOBAL $db;
    $db->set_preferences($name,$value);
  }

  ##############################################################################
  # get id for a filter part (helper to get_filters())
  function get_fquery(&$found,$fname,$tname="") {
   GLOBAL $db, $filter;
   if ( !strlen($tname) ) $tname=$fname;
   $db->query("SELECT id FROM $tname");
   while ( $db->next_record() ) {
     $id   = $db->f('id');
     if ($filter->$fname->$id) {
       if ($found) { $query .=  " OR v." . $fname . "_id='$id'";
       } else { $query = " v." . $fname . "_id='$id'"; }
       $found++;
     }
   }
   if ($found>1) $query = " (" . $query . " )";
   return $query;
  }

  ##############################################################################
  # get filter settings from db
  function get_filters() {
   global $db, $filter;
   $db->query("SELECT value FROM preferences WHERE name='filter'");
   if ( $db->next_record() ) { // there are already filters defined
     $filter = unserialize ( rawurldecode( $db->f('value') ) );
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
     $temp = $this->get_fquery($found,"mtype","mtypes");
     if ($found) { $sql[$i] = $temp; $found=0; $i++; }
     // -----------[ pict ]---
     $temp = $this->get_fquery($found,"pict");
     if ($found) { $sql[$i] = $temp; $found=0; $i++; }
     // -----------[ color ]---
     $temp = $this->get_fquery($found,"color","colors");
     if ($found) { $sql[$i] = $temp; $found=0; $i++; }
     // -----------[ tone ]---
     $temp = $this->get_fquery($found,"tone");
     if ($found) { $sql[$i] = $temp; $found=0; $i++; }
     // -----------[ director ]---
     $temp = $this->get_fquery($found,"director","directors");
     if ($found) { $sql[$i] = $temp; $found=0; $i++; }
     // -----------[ composer ]---
     $db->query("SELECT id FROM music");
     while ( $db->next_record() ) {
       $id   = $db->f('id');
       if ($filter->composer->$id) {
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
       if ($filter->actor->$id) {
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
       if ($filter->cat->$id) {
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

 } // end class preferences

?>
