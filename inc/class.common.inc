<?php
 /***************************************************************************\
 * phpVideoPro                              (c) 2001,2002 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Common functions used throughout the whole application                    *
 \***************************************************************************/

 /* $Id$ */

 /** Common functions used throughout the whole application
  * @package Api
  * @class common
  * @author Izzy (izzysoft@qumran.org)
  * @copyright (c) 2002 by Itzchak Rehberg and IzzySoft
  */

 /** Date formatted according to user preferences
  * @class common
  * @attribute string date
  */

class common {
   var $date;

   /** Constructor just calls initDate()
    * @constructor common
    */
   function common() {
     $this->initDate();
   }

   #============================================[ date format functions ]===
   /** Initialize the date property
    * @class common
    * @method initDate
    * @param optional mixed date date to format (either string or array)
    */
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

   /** setRecDate calls initDate with the date specified by the params
    * @class common
    * @method setRecDate
    * @param integer year
    * @param optional integer month
    * @param optional integer day
    */
   function setRecDate($year,$month="",$day="") {
     if (strlen($month)) {
       $date = array(year=>$year,mon=>$month,mday=>$day);
     } else {
       $date = $year;
     }
     $this->initDate($date);
   }

   /** Retrieve the (formatted) date
    * @class common
    * @method getRecDate
    * @param string format format to return the date ("string" or "array")
    * @return mixed date date formatted according to user preferences ("string") or as array
    */
   function getRecDate($format) {
     switch($format) {
       case "string" : return $this->date[string]; break;
       default       : return $this->date; break;
     }
   }

   /** Create a date array
    * @class common
    * @method makeRecDateArr
    * @param integer year
    * @param optional integer month
    * @param optional integer day
    * @return array date
    */
   function makeRecDateArr($year,$month="",$day="") {
     $this->setRecDate($year,$month,$day);
     return $this->getRecDate("array");
   }

   /** Create a date string
    * @class common
    * @method makeRecDateStr
    * @param integer year
    * @param optional integer month
    * @param optional integer day
    * @return string date date formatted according to user preferences
    */
   function makeRecDateStr($year,$month="",$day="") {
     $this->setRecDate($year,$month,$day);
     return $this->getRecDate("string");
   }
   
   /** Format a given date according to user preferences
    * @class common
    * @method formatDate
    * @param integer year
    * @param optional integer month
    * @param optional integer day
    * @return string date date formatted according to user preferences
    */
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
  /** Search a text block for URLs and make them clickable
   * @class common
   * @method make_clickable
   * @copyright function make_clickable taken from text_to_links() in the
       SourceForge Snipplet Library
       http://sourceforge.net/snippet/detail.php?type=snippet&id=100004
   * @param string data textblock to format
   * @return string newText formatted text block
   */
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

  /** Fill a string with zeros until its length is $len , start from left
   * @class common
   * @method padzeros
   * @param string num string to fill
   * @param integer len lenght of returned string
   * @return string num zero-padded string
   */
  function padzeros($num,$len) {
    while (strlen($num)<$len) {
      $num = "0$num";
    }
    return $num;
  }
 
  /** fill a string with blanks until its length is $len , start from left
   * @class common
   * @method padblanks
   * @param string str string to fill
   * @param integer len lenght of returned string
   * @return string str blank-padded string
   */
  function padblanks($str,$len) {
    while (strlen($str)<$len) $str = " $str";
    return $str;
  }

  /** fill a string with blanks until its length is $len , start from right
   * @class common
   * @method fillblanks
   * @param string str string to fill
   * @param integer len lenght of returned string
   * @return string str blank-padded string
   */
  function fillblanks($str,$len) {
    while (strlen($str)<$len) $str .= " ";
    if (strlen($str)>$len) $str = substr($str,0,$len);
    return $str;
  }

  /** center a string by adding spaces to the left and right
   * @class common
   * @method centerstr
   * @param string str string to center
   * @param integer len lenght of returned string
   * @return string str centered string
   */
  function centerstr($str,$len) {
    while (strlen($str)<$len) $str = " $str ";
    if (strlen($str)>$len) $str = substr($str,0,$len);
    return $str;
  }

   #============================================[ file system functions ]===
  /** get a list of files from within a given directory optionally using a mask
   *  (where $mask is the file's extension)
   * @class common
   * @method get_filenames
   * @param string dir directory to search in
   * @param optional string mask file extension to match
   * @return array result array of file names found
   */
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
 
?>