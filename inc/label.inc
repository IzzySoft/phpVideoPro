<?php
 /***************************************************************************\
 * phpVideoPro                             (c) 2001, 2002 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Class to create labels for your media                                     *
 \***************************************************************************/

 /* $Id$ */

 /** Class to create labels for your media
  * @package Api
  * @class label
  * @author Izzy (izzysoft@qumran.org)
  * @copyright (c) 2002 by Itzchak Rehberg and IzzySoft
  */
 class label {

   VAR $width, $height, $textcolor, $font, $color, $maxlines, $label,
       $nr_coord, $main_coord, $symb_coord, $mm_conv, $entry, $titleline;

   /** Constructor: initializes with config values, then calls all
    *  necessary (private) functions to create the label.
    * @constructor label
    * @param string config base name of config file to use (without path and
    *  extension)
    */
   function label($config) {
     GLOBAL $base_path;
     $config = $base_path . "labels/$config";
     include ($config . ".config");
     $this->colors();
     $this->mm_conv = 3.42;
     $this->maxlines = $maxlines;
     $this->width  = $width * $this->mm_conv;
     $this->height = $height * $this->mm_conv;
     if (!is_array($entry)) {
      $this->entry = array("$entry");
     } else { $this->entry  = $entry; }
     $this->nr_coord   = $this->convert_coord($nr_coord);
     $this->main_coord = $this->convert_coord($main_coord);
     $this->symb_coord = $this->convert_coord($symb_coord);
     $this->textcolor = $this->color[$textcolor];
     $this->font   = 5;
     $template = $config . ".png";
     if (file_exists($template)) {
       $this->copy_tpl($template);
     } else {
       $this->create_new();
     }
   } // end function label()

   function convert_coord($coord) {
     $arr = explode(",", $coord);
     for ($i=0;$i<count($arr);$i++) {
       $arr[$i] = $arr[$i] * $this->mm_conv;
     }
     return $arr;
   }

   ###########################################################################
   # create blank label from template image
   function copy_tpl($template) {
     $im_info = getimagesize("$template"); // label size
     $this->width  = $im_info[0];
     $this->height = $im_info[1];
     $ima = imageCreateFromPng("$template");     // open input png
     $im  = imageCreate($this->width,$this->height); // create img in desired size
     ImageRectangle($im,0,0,$this->width,$this->height,$uglybg);
     $dummy = imagecopyresized($im,$ima,0,0,0,0,$this->width,$this->height,$im_info[0],$im_info[1]);
     ImageDestroy($ima);
     if ($dummy == "") {
       ImageDestroy($im);
       $this->create_new();
       return;
     }
     $this->make_transparent($im);
     $this->label = $im;
   } // end function copy_tpl()

   ###########################################################################
   # create blank label without template image
   function create_new() {
     $im  = imageCreate($this->width,$this->height); // create img in desired size
     $bgcolor = explode(",", $this->color[white]);
     $fgcolor = explode(",", $this->color[blue]);
     $bg  = ImageColorAllocate($im, $bgcolor[0], $bgcolor[1], $bgcolor[2]);
     $fg  = ImageColorAllocate($im, $fgcolor[0], $fgcolor[1], $fgcolor[2]);
     ImageRectangle($im,0,0,$this->width - 1,$this->height - 1,$fg);
     ImageRectangle($im,$this->nr_coord[0],$this->nr_coord[1],$this->nr_coord[2] - 1,$this->nr_coord[3] - 1,$fg);
     ImageRectangle($im,$this->main_coord[0],$this->main_coord[1],$this->main_coord[2] - 1,$this->main_coord[3] - 1,$fg);
     ImageRectangle($im,$this->symb_coord[0],$this->symb_coord[1],$this->symb_coord[2] - 1,$this->symb_coord[3] - 1,$fg);
     $this->label = $im;
   }

   ###########################################################################
   # provide image transparency
   function make_transparent(&$img) {
     $uglybg = ImageColorAllocate($img,0xf4,0xb2,0xe5); // transparent bg
     ImageColorTransparent($img,$uglybg);
   }

   ###########################################################################
   # define some colors to use
   function colors() {
     $this->color[white] = "255,255,255";
     $this->color[black] = "0,0,0";
     $this->color[blue]  = "0,11,255";
   }

   ###########################################################################
   # calculate position of the text on the label field
   function get_textpos($text,$field,$font) {
     $length = strlen($text);
     $fieldwidth = $field[2] - $field[0];
     do { // calculate position of the text on the label
       $textwidth = $length * imagefontwidth($font);
       $x = ceil( ($fieldwidth - $textwidth) / 2 );
       --$font;
     } while (($x < 0) && ($font > 0));
     $x += + $field[0];
     return $x;
   }

   ###########################################################################
   # write text to a label field
   function write_text($text,$field) {
     $font = $this->font;
     for ($i=0;$i<count($text),$font>0;$i++) { // find longest line
       $tfont = $font;
       $x[$i] = $this->get_textpos($text[$i],$field,&$tfont);
       if ($tfont < $font) $font = $tfont;
     }
     ++$font;
     $vmidth = ceil($field[3] - $field[1]) / 2;
     $lines = count($text); if ($lines>$this->maxlines) $lines = $this->maxlines;
     $textcolor_array = explode(",", $this->textcolor);
     $color = ImageColorAllocate($this->label, $textcolor_array[0], $textcolor_array[1], $textcolor_array[2]);
     $movielines = count($this->entry);
     if ( isset($this->titleline) && $movielines < 3 && font < 5) { // at least half of the lines use fontsize +1
       $y = $vmidth - (imagefontheight($font +1) * $lines / 2) + $field[1];
     } else {
       $y = $vmidth - (imagefontheight($font) * $lines / 2) + $field[1];
     }
     for ($i=0;$i<$lines;$i++) {
       $mod = $i % $movielines;
       if (isset($this->titleline) && $i % $movielines == $this->titleline) {
         if ($font < 5) { 
           $usefont = $font +1;
           $x[$i] = $this->get_textpos($text[$i],$field,$usefont);
	 }
       } else {
         $usefont = $font;
         $x[$i] = $this->get_textpos($text[$i],$field,$font);
       }
       imagestring($this->label, $usefont, $x[$i], $y, "$text[$i]", $color);
       $y += imagefontheight($usefont);
     }
   }

   ###########################################################################
   # wrapper to put data on the label
   function write($nr,$text) {
     while ( substr($nr,0,1)=="0" ) {
       $nr = substr($nr,1);
     }
     $nr = explode(",",$nr);
     $this->write_text($nr,$this->nr_coord);
     $this->write_text($text,$this->main_coord);
   }

   ###########################################################################
   # prepare the text array with data from the movies listed in array $movie
   function make_text($movies) {
     GLOBAL $db;
     $moviecount = count($movies);
     for ($i=0;$i<$moviecount;$i++) {
       $movie = $db->get_movie($movies[$i]);
       for ($lines=0;$lines<count($this->entry);$lines++) {
         if ( substr($this->entry[$lines],0,1) == "*" ) {
	   $this->entry[$lines] = substr($this->entry[$lines],1);
	   $this->titleline = $lines;
	 }
         preg_match_all("/\{\S+\}/",$this->entry[$lines],$matches);
         $matchcount = count($matches[0]);
         $ttext = $this->entry[$lines];
         for ($k=0;$k<$matchcount;$k++) { // replace placeholders
           $var  = substr($matches[0][$k],1,strlen($matches[0][$k])-2);
	   $rvar = $movie[$var];
           if ($var == "length") { // convert to hh:mm
             $minutes = $rvar % 60; if ($minutes<10) $minutes = "0$minutes";
	     $hours   = floor($rvar / 60);
	     $rvar    = "$hours:$minutes";
	   }
	   $ttext = preg_replace("/\{$var\}/",$rvar,$ttext);
         }
         $text[] = $ttext;
       } // for $lines
     }
     return $text;
   }

   ###########################################################################
   # send the image to the browser
   function prn() {
     header( "Content-type: image/png");
     ImagePng($this->label);
   }

   ###########################################################################
   # free memory
   function destroy() {
     ImageDestroy( $this->label() );
   }

 /** Label width
  * @class label
  * @attribute integer width
  */
 /** Label height
  * @class label
  * @attribute integer height
  */
 /** Color used for the font
  * @class label
  * @attribute string textcolor
  */
 /** Font to use
  * @class label
  * @attribute integer font font number as used by PHPs imaging methods
  */
 /** Available colors
  * @class label
  * @attribute array color available colors to be addressed by their names
  */
 /** Max text lines to fit on a label
  * @class label
  * @attribute integer maxlines
  */
 /** Label handler
  * @class label
  * @attribute mixed label
  */
 /** Coordinates of media number
  * @class label
  * @attribute string nr_coord
  */
 /** Coordinates of label main field
  * @class label
  * @attribute string main_coord
  */
 /** Coordinates of (category) symbol
  * @class label
  * @attribute string symb_coord
  */
 /** Conversion unit (points to millimeters)
  * @class label
  * @attribute integer mm_conv
  */
 /** Label text template
  * @class label
  * @attribute array entry
  */
 /** Titleline (to be printed bold)
  * @class label
  * @attribute integer titleline
  */

 } // end class label

?>