<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Common functions used throughout the whole application                    *
 \***************************************************************************/

 /* $Id$ */

 ##############################################################################
 # output debug message depending on configured debug level
 function debug($level,$msg) {
   GLOBAL $debug;
   if ( strpos(strtoupper($debug["log"]),strtoupper($level))===false ) return;
   echo $msg;
 }

 ##############################################################################
 # preset empty (table) fields with a hard space (to enforce table borders)
 function check_empty(&$field) {
   if ($field == "") $field = "&nbsp";
 }

 ##############################################################################
 # check wether the string contains only digits (and nothing else)
 function is_num($fvar) {
   $regnum = "/\D/";
   if (preg_match($regnum,$fvar)) return false;
   return true;
 }

 ##############################################################################
 # format and display an error message for unrecoverable error
 function display_error($error) {
   GLOBAL $colors;
   echo $colors["err"] . "<H2 ALIGN=CENTER>" . strtoupper(lang("warning")) . "</H2></Font>\n";
   echo "<Table Width=90% Align=Center>\n <TR><TD>";
   echo "<P ALIGN=JUSTIFY>$error</P>\n";
   echo " </TD></TR></TABLE>\n</BODY></HTML>";
 }

 ##############################################################################
 # check wether the specified date is valid
 # if FALSE or 0 are supplied as second parameter to this function, exact
 # comparision is disabled and relax mode activated. In relax mode, the date
 # only has to fulfill a few conditions: year must be > 1900, month < 13 and
 # day < 32 (which also allows "2000-00-00") - whereas in exact mode the given
 # date must really exist
 function check_date($date,$exact=1) {
   $correct = TRUE;
   if ( (substr($date,4,1)!="-") || (substr($date,7,1)!="-") ) $correct = FALSE;
   $month = substr($date,5,2);
   $day   = substr($date,8);
   $year  = substr($date,0,4);
   if ($exact && $correct) { $correct = checkdate($month,$day,$year);
   } elseif ($correct) { $correct = is_num($month . $day . $year) && ($month<13) && ($day<32) && ($year>1900); }
   if ( !(trim($date)=="" || trim($date)=="0000-00-00") ) {
     if ( !$correct ) {
       $error = lang("wrong_date",lang("of_aquiration"),$date);
       if (!$exact) $error .= " " . lang("incomplete_date");
       $error .= "<BR><BR>" . lang("hit_back_to_correct");
     display_error($error);
     exit;
     }
   }
 }

 ##############################################################################
 # get filter settings from db - real function moved to class preferences,
 # so this is just a wrapper until the change is done in all files
 function get_filters() {
  global $pvp;
  return $pvp->preferences->filter;
 }

 ##############################################################################
 # get translation
 function lang($key,$m1="",$m2="",$m3="",$m4="",$m5="",$m6="",$m7="",$m8="",$m9="",$m10="") {
   if (is_array($m1)){
     $vars = $m1;
   } else {
     $vars = array($m1,$m2,$m3,$m4,$m5,$m6,$m7,$m8,$m9,$m10);
   }
   return translate("$key",$vars);
 }

 # initiate the translations only once
 if (!$pvpinstall) $translations = $db->get_translations( $pvp->preferences->lang );

 function translate($key,$vars=FALSE) {
   GLOBAL $translations;
   $trans = $translations[strtolower($key)];
   if (!$trans) $trans = $key;
   if (!$vars) $vars=array();
   $ndx = 1;
   while ( list($k,$v)=each($vars) ) {
     $trans = preg_replace("/%$ndx/",$v,$trans);
     $ndx++;
   }
   return $trans;
 }

 include (dirname(__FILE__) . "/class.common.inc");
 $pvp->common = new common;
?>