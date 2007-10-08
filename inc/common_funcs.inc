<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Common functions used throughout the whole application                    #
 #############################################################################

 /* $Id$ */

 ##############################################################[ Debugging ]###
 /** output debug message depending on configured debug level
  * @package Api
  * @author Izzy (izzysoft AT qumran DOT org)
  * @copyright (c) 2001-2007 by Itzchak Rehberg and IzzySoft
  * @function debug
  * @param string level debug level (1 char only)
  * @param string msg debug message
  */
 function debug($level,$msg) {
   GLOBAL $debug;
   if ( strpos(strtoupper($debug["log"]),strtoupper($level))===false ) return;
   echo $msg;
 }

 /** check whether the given debug level is set
  * @package Api
  * @author Izzy (izzysoft AT qumran DOT org)
  * @copyright (c) 2001-2007 by Itzchak Rehberg and IzzySoft
  * @function debugLevel
  * @param string level debug level (1 char only)
  * @return boolean TRUE if set, FALSE if not
  */
 function debugLevel($level) {
   GLOBAL $debug;
   if ( strpos(strtoupper($debug["log"]),strtoupper($level))===false ) return FALSE;
   return TRUE;
 }

 #########################################################[ Error Handling ]###
 /** format and display an error message for unrecoverable error
  * @package Api
  * @author Izzy (izzysoft AT qumran DOT org)
  * @copyright (c) 2001-2007 by Itzchak Rehberg and IzzySoft
  * @function display_error
  * @param string error error message to display
  */
 function display_error($error) {
   echo "<SPAN CLASS='error'><H2 ALIGN=CENTER>" . strtoupper(lang("warning")) . "</H2></SPAN>\n";
   echo "<Table Width=90% Align=Center>\n <TR><TD>";
   echo "<P ALIGN=JUSTIFY>$error</P>\n";
   echo " </TD></TR></TABLE>\n</BODY></HTML>";
 }

 ###############################################################[ Checking ]###
 /** preset empty (table) fields with a hard space (to enforce table borders)
  * @package Api
  * @author Izzy (izzysoft AT qumran DOT org)
  * @copyright (c) 2001-2007 by Itzchak Rehberg and IzzySoft
  * @function check_empty
  * @param string field field to check
  */
 function check_empty(&$field) {
   if ($field == "") $field = "&nbsp";
 }

 /** check wether the string contains only digits (and nothing else)
  * @package Api
  * @author Izzy (izzysoft AT qumran DOT org)
  * @copyright (c) 2001-2007 by Itzchak Rehberg and IzzySoft
  * @function is_num
  * @param string var var to check
  */
 function is_num($fvar) {
   $regnum = "/\D/";
   if (preg_match($regnum,$fvar)) return false;
   return true;
 }

 /** check wether the specified date is valid
  *  if FALSE or 0 are supplied as second parameter to this function, exact
  *  comparision is disabled and relax mode activated. In relax mode, the date
  *  only has to fulfill a few conditions: year must be > 1900, month < 13 and
  *  day < 32 (which also allows "2000-00-00") - whereas in exact mode the given
  *  date must really exist
  * @package Api
  * @author Izzy (izzysoft AT qumran DOT org)
  * @copyright (c) 2001-2007 by Itzchak Rehberg and IzzySoft
  * @function check_date
  * @param string date date to check (format: YYYY-MM-DD)
  * @param optional integer exact whether the date has to be valid; otherwise "00" is counted as a valid day/month and "0000" as a valid year as well (defaults to "1")
  */
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

 ################################################################[ Filters ]###
 /** get filter settings from db - real function moved to class preferences,
  *  so this is just a wrapper until the change is done in all files
  * @package Api
  * @author Izzy (izzysoft AT qumran DOT org)
  * @copyright (c) 2001-2007 by Itzchak Rehberg and IzzySoft
  * @function get_filters
  */
 function get_filters() {
  global $pvp;
  return $pvp->preferences->get_filters();
 }

 ###########################################################[ Translations ]###
 /** get translation
  *  if no translation is found, the content of the passed param $key is returned instead
  * @package Api
  * @author Izzy (izzysoft AT qumran DOT org)
  * @copyright (c) 2001-2007 by Itzchak Rehberg and IzzySoft
  * @function lang
  * @param string key translation key
  * @param optional array m1 replace placeholder (%1..%10 in translations)
  * @param optional string m2 instead of $m1 being an array, all 10 replacements may be passed separately as strings
  */
 function lang($key,$m1="",$m2="",$m3="",$m4="",$m5="",$m6="",$m7="",$m8="",$m9="",$m10="") {
   if (is_array($m1)){
     $vars = $m1;
   } else {
     $vars = array($m1,$m2,$m3,$m4,$m5,$m6,$m7,$m8,$m9,$m10);
   }
   return translate("$key",$vars);
 }

 /** build the translations (helper func to function lang)
  * @package Api
  * @author Izzy (izzysoft AT qumran DOT org)
  * @copyright (c) 2001-2007 by Itzchak Rehberg and IzzySoft
  * @function translate
  * @param string key translation key
  * @param optional array vars array of replacement strings (see function lang)
  */
 function translate($key,$vars=FALSE) {
   if (empty($key)) return $key;
   GLOBAL $translations;
   if (isset($translations[strtolower($key)])) $trans = $translations[strtolower($key)];
   if (!isset($trans)) $trans = $key;
   if (!$vars) $vars=array();
   $ndx = 1;
   while ( list($k,$v)=each($vars) ) {
     $trans = preg_replace("/%$ndx/",$v,$trans);
     $ndx++;
   }
   return $trans;
 }

 ###########################################################[ (No-)Session ]###
 /** kick-off unauthorized visitor
  * @package Api
  * @author Izzy (izzysoft AT qumran DOT org)
  * @copyright (c) 2001-2007 by Itzchak Rehberg and IzzySoft
  * @function kickoff
  */
 function kickoff() {
   GLOBAL $base_url;
   $from = $_SERVER['HTTP_REFERER'];
   header("Location: $base_url"."login.php?login_hint=login_required&redir="
          .urlencode($from));
   exit;
 }

 ###############################################################[ PHP >4.1 ]###
 # backwards compatibility to older PHP versions
 if (!function_exists("file_get_contents")) {
   function file_get_contents($filename, $use_include_path = 0) {
    $data = ""; // just to be safe. Dunno, if this is really needed
    $file = @fopen($filename, "rb", $use_include_path);
    if ($file) {
      while (!feof($file)) $data .= fread($file, 1024);
      fclose($file);
    }
    return $data;
   }
 }
 

 include (dirname(__FILE__) . "/class.common.inc");
 $pvp->common = new common;
?>