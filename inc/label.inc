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

 class label {

   VAR $width, $height, $textcolor, $font, $color, $maxlines, $label,
       $nr_coord, $main_coord, $symb_coord, $mm_conv;

   function label($config) {
     GLOBAL $base_path;
     $config = $base_path . "labels/$config";
     include ($config . ".config");
     $this->colors();
     $this->mm_conv = 3.42;
     $this->maxlines = 4;
     $this->width  = $width * $this->mm_conv;
     $this->height = $height * $this->mm_conv;
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

   function copy_tpl($template) { // create blank label from template image
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

   function create_new() { // create blank label without template image
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

   function make_transparent(&$img) {
     $uglybg = ImageColorAllocate($img,0xf4,0xb2,0xe5); // transparent bg
     ImageColorTransparent($img,$uglybg);
   }

   function colors() {
     $this->color[white] = "255,255,255";
     $this->color[black] = "0,0,0";
     $this->color[blue]  = "0,11,255";
   }

   # calculate position of the text on the label field
   function get_textpos($text,$field,$font) {
     $length = strlen($text);
     $fieldwidth = $field[2] - $field[0];
     do { // calculate position of the text on the label
       $textwidth = $length * imagefontwidth($font);
       $x = ($fieldwidth - $textwidth) / 2; $x = ceil($x) + $field[0];
       --$font;
     } while (($x < 0) && ($font > 0));
     return $x;
   }

   function write_text($text,$field) {
     $font = $this->font;
     for ($i=0;$i<count($text);$i++) { // find longest line
       $tfont = $font;
       $x[$i] = $this->get_textpos($text[$i],$field,&$tfont);
       if ($tfont < $font) $font = $tfont;
     }
     ++$font;
     for ($i=0;$i<count($text);$i++) { // now position the text
       $x[$i] = $this->get_textpos($text[$i],$field,$font);
     }
     $vmidth = ceil($field[3] - $field[1]) / 2;
     $lines = count($text); if ($lines>$this->maxlines) $lines = $this->maxlines;
     $y = $vmidth - (imagefontheight($font) * $lines / 2);
     $textcolor_array = explode(",", $this->textcolor);
     $color = ImageColorAllocate($this->label, $textcolor_array[0], $textcolor_array[1], $textcolor_array[2]);
     for ($i=0;$i<count($text),$i<4;$i++) {
       imagestring($this->label, $font, $x[$i], $y, "$text[$i]", $color);
       $y += imagefontheight($font);
     }
   }

   function write($nr,$text) {
     while ( substr($nr,0,1)=="0" ) {
       $nr = substr($nr,1);
     }
     $nr = explode(",",$nr);
     $this->write_text($nr,$this->nr_coord);
     $this->write_text($text,$this->main_coord);
   }

   function prn() {
     header( "Content-type: image/png");
     ImagePng($this->label);
   }

   function destroy() {
     ImageDestroy( $this->label() );
   }

 } // end class label

?>