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
  return $pvp->preferences->get_filters();
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
 function get_lang() {
   GLOBAL $db;
   dbquery("SELECT value FROM preferences WHERE name='lang'");
   if ( $db->next_record() ){
     $lang = $db->f('value');
   } else {
     $lang = "en";
   }
   return $lang;
 }

 # initiate the translations only once
 $translations = $db->get_translations( get_lang() );

 function translate($key,$vars=FALSE) {
   GLOBAL $db, $translations;
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

class common {

   var $date;

   function common() {
     $this->initDate();
   }
   #============================================[ date format functions ]===
   function initDate($date=0) {
     switch (strtolower(gettype($date))) {
       case "string"  : $tdate[year] = substr($date,0,4);
                        $tdate[mon]  = substr($date,5,2);
                        $tdate[mday] = substr($date,8,2);
			$tdate[string] = $date;
			$this->date = $tdate; break;
       case "array"   : $this->date = $date; break;
       default        : $this->date = getdate(); break;
     }
                        while (strlen($this->date[mon])<2) $this->date[mon] = "0" . $this->date[mon];
                        while (strlen($this->date[mday])<2) $this->date[mday] = "0" . $this->date[mday];
                        while (strlen($this->date[year])<4) $this->date[year] = "0" . $this->date[year];
                        $this->date[string] = $this->date[year] . "-" . $this->date[mon] . "-" . $this->date[mday];
   }

   function setRecDate($year,$month="",$day="") {
     if (strlen($month)) {
       $date = array(year=>$year,mon=>$month,mday=>$day);
     } else {
       $date = $year;
     }
     $this->initDate($date);
   }

   function getRecDate($format) {
     switch($format) {
       case "string" : return $this->date[string]; break;
       default       : return $this->date; break;
     }
   }
   
   function makeRecDateArr($year,$month="",$day="") {
     $this->setRecDate($year,$month,$day);
     return $this->getRecDate("array");
   }

   function makeRecDateStr($year,$month="",$day="") {
     $this->setRecDate($year,$month,$day);
     return $this->getRecDate("string");
   }
   
   function formatDate($year,$month="",$day="") {
     GLOBAL $pvp;
     $this->setRecDate($year,$month,$day);
     $sum = $this->date[mon] + $this->date[year] + $this->date[mday];
     if (!$sum) return lang("unknown");
     switch (strtolower($pvp->preferences->date_format)) {
       case "d/m/y" : return $this->date[mday] . "/" . $this->date[mon] . "/" . $this->date[year]; break;
       case "d.m.y" : return $this->date[mday] . "." . $this->date[mon] . "." . $this->date[year]; break;
       case "y-m-d" :
       default      : return $this->getRecDate("string"); break;
     }
   }

  #==========================================[ text formatting functions ]===
  // function make_clickable taken from text_to_links() in the SourceForge Snipplet Library
  // http://sourceforge.net/snippet/detail.php?type=snippet&id=100004
  function make_clickable($data) {
    if(empty($data)) {
      return $data;
    }
    $lines = split("\n",$data);
    while ( list ($key,$line) = each ($lines)) {
      $line = eregi_replace("([ \t]|^)www\."," http://www.",$line);
      $line = eregi_replace("([ \t]|^)ftp\."," ftp://ftp.",$line);
      $line = eregi_replace("(http://[^ )\r\n]+)","<A href=\"\\1\" target=\"_blank\">\\1</A>",$line);
      $line = eregi_replace("(https://[^ )\r\n]+)","<A href=\"\\1\" target=\"_blank\">\\1</A>",$line);
      $line = eregi_replace("(ftp://[^ )\r\n]+)","<A href=\"\\1\" target=\"_blank\">\\1</A>",$line);
      $newText .= "$line\n";
    }
    return $newText;
  }

  // fill a string with zeros until its length is $len , start from left
  function padzeros($num,$len) {
    while (strlen($num)<$len) {
      $num = "0$num";
    }
    return $num;
  }
 
  // fill a string with blanks until its length is $len , start from left
  function padblanks($str,$len) {
    while (strlen($str)<$len) $str = " $str";
    return $str;
  }

  // fill a string with blanks until its length is $len , start from right
  function fillblanks($str,$len) {
    while (strlen($str)<$len) $str .= " ";
    if (strlen($str)>$len) $str = substr($str,0,$len);
    return $str;
  }

  // center a string by adding spaces to the left and right
  function centerstr($str,$len) {
    while (strlen($str)<$len) $str = " $str ";
    if (strlen($str)>$len) $str = substr($str,0,$len);
    return $str;
  }

   #============================================[ file system functions ]===
  // get a list of files from within a given directory optionally using a mask
  // (where $mask is the file's extension)
  function get_filenames($dir,$mask="") {
    $thisdir = dir($dir);
    while($entry=$thisdir->read()) {
      if(($entry!='.')&&($entry!='..')) {
        if ($mask==substr($entry,strlen($entry)-strlen($mask))) {
          $result[] = $entry;
        }
      }
    }
    return $result;
   } // end function get_filenames()
 } // end class common
 
 $pvp->common = new common;
?>
<?

?>