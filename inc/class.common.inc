<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Common functions used throughout the whole application                    #
 #############################################################################

 /* $Id$ */

 /** Common functions used throughout the whole application
  * @package Api
  * @class common
  * @author Izzy (izzysoft@qumran.org)
  * @copyright (c) 2002-2004 by Itzchak Rehberg and IzzySoft
  */

class common {
  /** Keeping the formatted date in various forms - do not directly access!
   * @package Api
   * @class common
   * @attribute array date
   */
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
      case "string"  : $tdate['year'] = substr($date,0,4);
                       $tdate['mon']  = substr($date,5,2);
                       $tdate[mday] = substr($date,8,2);
                       $tdate['string'] = $date;
                       $this->date = $tdate; break;
      case "array"   : $this->date = $date; break;
      default        : $this->date = getdate(); break;
    }
    while (strlen($this->date['mon'])<2) $this->date['mon'] = "0" . $this->date['mon'];
    while (strlen($this->date['mday'])<2) $this->date['mday'] = "0" . $this->date['mday'];
    while (strlen($this->date['year'])<4) $this->date['year'] = "0" . $this->date['year'];
    $this->date['string'] = $this->date['year'] . "-" . $this->date['mon'] . "-" . $this->date['mday'];
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
      case "string" : return $this->date['string']; break;
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
    $sum = $this->date['mon'] + $this->date['year'] + $this->date['mday'];
    if (!$sum) return lang("unknown");
    switch (strtolower($pvp->preferences->get("date_format"))) {
      case "d/m/y" : return $this->date['mday'] . "/" . $this->date['mon'] . "/" . $this->date['year']; break;
      case "d.m.y" : return $this->date['mday'] . "." . $this->date['mon'] . "." . $this->date['year']; break;
      case "y-m-d" :
      default      : return $this->getRecDate("string"); break;
    }
  }

  #==========================================[ text formatting functions ]===
   /** Recode a string between two character sets
    * @class common
    * @method recode
    * @param string string to recode
    * param optional encoding (defaults to utf-8..lat1)
    * @return string recoded string
    * @version supports only "lat1..utf-8" and vice versa for now; the recode
    *  definition has to be set in the this::recode property. Usage of an own
    *  recoding method was due to recode() and iconv() functions of PHP need
    *  special requirements (such as libraries and modules) which are not
    *  available on most systems by default.
    */
   function recode ($string,$encoding="utf-8..lat1") {
     switch ($encoding) {
       case "utf-8..lat1" :
         return preg_replace("/([\xC2\xC3])([\x80-\xBF])/e",
	     "chr(ord('\\1')<<6&0xC0|ord('\\2')&0x3F)",
	     $string); break;
       case "lat1..utf-8" :
         return preg_replace("/([\x80-\xFF])/e",
             "chr(0xC0|ord('\\1')>>6).chr(0x80|ord('\\1')&0x3F)",
	     $string); break;
       default: return($string);
     }
   }

  /** Search a text block for URLs & cater for the [img],[imgr] and [href] tags
   * @class common
   * @method make_clickable
   * @param string data textblock to format
   * @return string newText formatted text block
   */
  function make_clickable($data) {
    if(empty($data)) {
      return $data;
    }
    $lines = split("\n",$data);
    while ( list ($key,$line) = each ($lines)) {
      if ( preg_match_all("/\[href\]\S+\[\/href\]/i",$line,$matches) ) {
        for ($i=0;$i<count($matches[0]);++$i) {
          $sub  = eregi_replace("\[href\](.*)\[\/href\]","<A HREF=\"\\1\" TARGET=\"_blank\">\\1</A>",$matches[0][$i]);
          $line = str_replace($matches[0][$i],$sub,$line);
        }
      }
      if ( preg_match_all("/\[url\]\S+\[\/url\]/i",$line,$matches) ) {
        for ($i=0;$i<count($matches[0]);++$i) {
          if ( preg_match("/\[img\]\S+\[\/img\]/i",$matches[0][$i]) ) {
            $imgurl = eregi_replace("\[url\]\[img\](.*)\[\/img\]\[\/url\]","\\1",$matches[0][$i]);
          } elseif ( preg_match("/\[imgr\]\S+\[\/imgr\]/i",$matches[0][$i]) ) {
            $imgurl = eregi_replace("\[url\]\[imgr\](.*)\[\/imgr\]\[\/url\]","\\1",$matches[0][$i]);
          } else {
            $imgurl = "\\1";
          }
          $sub  = eregi_replace("\[url\](.*)\[\/url\]","<A HREF=\"$imgurl\" TARGET=\"_blank\">\\1</A>",$matches[0][$i]);
          $line = str_replace($matches[0][$i],$sub,$line);
        }
      }
      if ( preg_match_all("/\[img\]\S+\[\/img\]/i",$line,$matches) ) {
        for ($i=0;$i<count($matches[0]);++$i) {
          $sub  = eregi_replace("\[img\](.*)\[\/img\]","<IMG ALIGN=\"left\" STYLE=\"margin-right:4\" SRC=\"\\1\">",$matches[0][$i]);
          $line = str_replace($matches[0][$i],$sub,$line);
        }
      }
      if ( preg_match_all("/\[imgr\]\S+\[\/imgr\]/i",$line,$matches) ) {
        for ($i=0;$i<count($matches[0]);++$i) {
          $sub  = eregi_replace("\[imgr\](.*)\[\/imgr\]","<IMG ALIGN=\"right\" STYLE=\"margin-left:4\" SRC=\"\\1\">",$matches[0][$i]);
          $line = str_replace($matches[0][$i],$sub,$line);
        }
      }
      $line = eregi_replace("\[imgr\](.*)\[\/img\]","<IMG ALIGN=\"right\" SRC=\"\\1\">",$line);
      $newText .= "$line\n";
    }
    return $newText;
  }

  /** Format the input from plain text files (improved nl2br)
   * @class common
   * @method nl2br
   * @param string input
   * @param optional boolean tagreplace
   *  Whether to automatically run the tagreplace (default: TRUE)
   * @param optional boolean br Replace ALL nl with BR? (default: FALSE)
   * @return string formated input
   * @version based on the enhanced autop() function by Photo Matt
   *  (see http://photomatt.net/scripts.php/autop)
   */
  function nl2br($pee, $tagreplace=1, $br=0) {
    if ( empty($pee) ) return $pee;
    if ($tagreplace) $pee = $this->make_clickable($pee);
    $pee = $pee . "\n"; // just to make things a little easier, pad the end
    $pee = preg_replace('|<br />\s*<br />|', "\n\n", $pee);
    $pee = preg_replace('!(<(?:table|ul|ol|li|pre|form|blockquote|h[1-6])[^>]*>)!', "\n$1", $pee); // Space things out a little
    $pee = preg_replace('!(</(?:table|ul|ol|li|pre|form|blockquote|h[1-6])>)!', "$1\n", $pee); // Space things out a little
    $pee = preg_replace("/(\r\n|\r)/", "\n", $pee); // cross-platform newlines 
    $pee = preg_replace("/\n\n+/", "\n\n", $pee); // take care of duplicates
    $pee = preg_replace('/\n?(.+?)(?:\n\s*\n|\z)/s', "<p>$1</p>\n", $pee); // make paragraphs, including one at the end 
    $pee = preg_replace('|<p>\s*?</p>|', '', $pee); // under certain strange conditions it could create a P of entirely whitespace 
    $pee = preg_replace("|<p>(<li.+?)</p>|", "$1", $pee); // problem with nested lists
    $pee = preg_replace('|<p><blockquote([^>]*)>|i', "<blockquote$1><p>", $pee);
    $pee = str_replace('</blockquote></p>', '</p></blockquote>', $pee);
    $pee = preg_replace('!<p>\s*(</?(?:table|tr|td|th|div|ul|ol|li|pre|select|form|blockquote|p|h[1-6])[^>]*>)!', "$1", $pee);
    $pee = preg_replace('!(</?(?:table|tr|td|th|div|ul|ol|li|pre|select|form|blockquote|p|h[1-6])[^>]*>)\s*</p>!', "$1", $pee); 
    if ($br) $pee = preg_replace('|(?<!<br />)\s*\n|', "<br />\n", $pee); // optionally make line breaks
    $pee = preg_replace('!(</?(?:table|tr|td|th|div|dl|dd|dt|ul|ol|li|pre|select|form|blockquote|p|h[1-6])[^>]*>)\s*<br />!', "$1", $pee);
    $pee = preg_replace('!<br />(\s*</?(?:p|li|div|th|pre|td|ul|ol)>)!', '$1', $pee);
    $pee = preg_replace('/&([^#])(?![a-z]{1,8};)/', '&#038;$1', $pee);
    $pee = str_replace("<p><hr></p>","<hr>",$pee);
    $pee = preg_replace("/<p>(<[p|P])/","$1",$pee); // remove double P produced when textblock already started with P
#    $pee = "<DIV CLASS='notes'>$pee</DIV>";
    return $pee; 
  }

  /** Fill a string with zeros until its length is $len , start from left
   * @class common
   * @method padzeros
   * @param string num string to fill
   * @param integer len lenght of returned string
   * @return string num zero-padded string
   */
  function padzeros($num,$len) {
    return sprintf("%'0$len"."d",$num);
  }
 
  /** fill a string with blanks until its length is $len , start from left
   * @class common
   * @method padblanks
   * @param string str string to fill
   * @param integer len lenght of returned string
   * @return string str blank-padded string
   */
  function padblanks($str,$len) {
    return sprintf("%$len"."s",$str);
  }

  /** fill a string with blanks until its length is $len , start from right
   * @class common
   * @method fillblanks
   * @param string str string to fill
   * @param integer len lenght of returned string
   * @return string str blank-padded string
   */
  function fillblanks($str,$len) {
    $str = sprintf("%-$len"."s",$str);
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

  /** remove unwanted HTML tags to safeguard the site
   * @class common
   * @method safehtml
   * @param string string string to clean up
   * @param optional string allowed tags to permit (defaults to "b|i|u|center")
   * @param optional boolean addstring add $allowed to the defaults (TRUE) or replace (FALSE)?
   * @param optional string keep tags to keep entirely intact (needed for e.g. "a|img"; default: "")
   * @return string cleaned string
   * @version Everything enclosed by &lt;script&gt;, &lt;iframe&gt; and
   *  &lt;head&gt; tags is completely removed with those tags respective. All
   *  other non-allowed tags are removed, but the enclosed text is kept intact.
   */
  function safehtml($str,$allowed="",$add=FALSE,$keep="") {
    $trusted = "b|i|u|center";
    if ($allowed==="") { $allowed = $trusted; } else {
      if ($add) $allowed = $trusted . "|" .$allowed;
    }
    if ($keep) {
      if ($allowed) { $ignored = $allowed . "|" . $keep; }
        else { $ignored = $keep; }
    } else { $ignored = $allowed; }
    $str = preg_replace("'<script[^>]*?>.*?</script>'si", "", $str);
    $str = preg_replace("'<iframe[^>]*?>.*?</iframe>'si", "", $str);
    $str = preg_replace("'<head[^>]*?>.*?</head>'si", "", $str);
    $str = preg_replace("/<((?!\/?($ignored)\b)[^>]*>)/xis", "", $str);
    $str = preg_replace("/<($allowed)\s.*?>/i", "<\\1>", $str);
    return $str;
  }

  /** remove unwanted HTML tags from input fields (wrapper to safehtml())
   * @class common
   * @method safeinput
   * @param string string string to clean up
   * @return string cleaned string
   * @see safehtml() for details
   */
  function safeinput($str) {
    return $this->safehtml($str);
  }

  /** remove unwanted HTML tags from textareas. This wrapper to safehtml()
   *  allows some more tags that may be needed for formatting issues
   * @class common
   * @method safetextarea
   * @param string string string to clean up
   * @return string cleaned string
   * @see safehtml() for details
   */
  function safetextarea($str) {
    return $this->safehtml($str,"block|pre|br|hr",TRUE,"ul|ol|li|p");
  }

  /** prepare a string containing quotes for form input fields
   * @class common
   * @method string2input
   * @param string string to convert
   * @return string converted string
   */
  function string2input($string) {
    $string = str_replace("'","&lsquo;",$string);
    $string = str_replace('"',"&quot;",$string);
    return $string;
  }

  /** reverse convert input string
   * @class common
   * @method input2string
   * @param string string to convert
   * @return string converted string
   * @see string2input
   */
  function input2string($string) {
    $string = str_replace("&quot;",'"',$string);
    $string = str_replace("&lsquo;","'",$string);
    return $string;
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

   #==================================================[ array functions ]===
  /** combine two arrays that contain "statistics", i.e. the values are the
   *  count for their keys
   * @class common
   * @method array_combine_sums
   * @param array ar1 array to append to
   * @param array ar2 array to be appended to ar1
   * @return array ar1 updated with values from ar2
   */
  function array_combine_sums($ar1,$ar2) {
    if (empty($ar1)) return $ar2;
    if (empty($ar2)) return $ar1;
    foreach ($ar1 as $key=>$value) {
      if ( isset($ar2[$key]) ) {
        $ar1[$key] += $ar2[$key];
	unset($ar2[$key]);
      }
    }
    $ar1 += $ar2;
    return $ar1;
  }

   #===================================================[ form functions ]===
  /** Build &lt;SELECT&gt; box for MediaTypes
   * @class common
   * @method make_mtype_selectbox
   * @param string name name for the &lt;SELECT&gt; object
   * @param optional integer selected which mtype_id should be marked selected
   * @param optional boolean short wether to use the short name of mtype (default)
   * @return string the complete HTML code for the &lt;SELECT&gt; box
   */
  function make_mtype_selectbox($name,$selected=1,$short=TRUE) {
    GLOBAL $db;
    if ($short) { $type = "sname"; } else { $type = "name"; }
    $select = "<SELECT NAME='$name'>";
    $mtypes = $db->get_mtypes();
    for ($i=0;$i<count($mtypes);++$i) {
      $select .= "<OPTION VALUE='" . $mtypes[$i][id] . "'";
      if ( $mtypes[$i][id] == $selected ) $select .= " SELECTED";
      $select .= ">" . $mtypes[$i][$type] . "</OPTION>";
    }
    $select .= "</SELECT>";
    return $select;
  }

  /** Build &lt;SELECT&gt; box for LastMovieNum
   * @class common
   * @method make_lastnum_selectbox
   * @param string name name for the &lt;SELECT&gt; object
   * @return string the complete HTML code for the &lt;SELECT&gt; box
   */
   function make_lastnum_selectbox($name) {
    GLOBAL $db;
    $select = "<SELECT NAME='$name'>";
    $lastnum = $db->get_lastmovienum();
    for ($i=0;$i<count($lastnum);++$i) {
      $select .= "<OPTION>" . $lastnum[$i][entry] . "</OPTION>";
    }
    $select .= "</SELECT>";
    return $select;
   }

  /** Build a CheckBox and set its defaults
   * @class common
   * @method make_checkbox
   * @param string name name for the form field
   * @param boolean checked whether it should be marked CHECKED
   * @param optional boolean condition mark it CHECKED only if this is TRUE as well
   * @return string checkbox form string
   */
  function make_checkbox($name,$checked,$confirm=2) {
    if ($confirm==2) $confirm = $checked;
    $checkbox = "<INPUT TYPE='checkbox' NAME='$name'";
    if ($checked && $confirm) $checkbox .= " CHECKED";
    $checkbox .= ">";
    return $checkbox;
  }

   #===================================================[ misc functions ]===
  /** check wether a medium is (re)writeable (as e.g. RVT) or not (e.g. DVD)
   * @class common
   * @method medium_is_rw
   * @param integer id mtype_id
   * @return boolean TRUE if medium is writeable
   */
  function medium_is_rw($id) {
    GLOBAL $rw_media;
    $rw = explode(",",$rw_media);
    if ( in_array($id,$rw) ) return TRUE;
    return FALSE;
  }

 } // end class common
 
?>