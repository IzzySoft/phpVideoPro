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

   VAR $width, $height, $vmidth, $textcolor, $font, $color, $maxlines, $label;

   function label($config) {
     GLOBAL $base_path;
     $config = $base_path . "labels/$config";
     include ($config . ".config");
     $this->colors();
     $this->maxlines = 4;
     $this->width  = $width * 3.41;
     $this->height = $height * 3.41;
     $this->textcolor = $this->color[$textcolor];
     $this->font   = 5;
     $template = $config . ".png";
     if (file_exists($template)) {
       $this->copy_tpl($template);
     } else {
       $this->create_new();
     }
     $this->vmidth = ceil($this->height / 2);
   } // end function label()

   function copy_tpl($template) { // create blank label from template image
     $im_info = getimagesize("$template.png"); // label size
     $this->width  = $im_info[0];
     $this->height = $im_info[1];
     $ima = imageCreateFromPng("$template.png");     // open input png
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
     $this->label = $im;
   }

   function make_transparent(&$img) {
     $uglybg = ImageColorAllocate($im,0xf4,0xb2,0xe5); // transparent bg
     ImageColorTransparent($img,$uglybg);
   }

   function colors() {
     $this->color[white] = "255,255,255";
     $this->color[black] = "0,0,0";
     $this->color[blue]  = "0,11,255";
   }

   function write_text($text) {
     for ($i=0;$i<count($text);$i++) { // find longest line
       $length = strlen($text[$i]);
       $font[$i] = $this->font;
       do { // calculate position of the text on the label
         $textwidth = $length * imagefontwidth($font[$i]);
         $x[$i] = ($this->width - $textwidth) / 2; $x[$i] = ceil($x[$i]);
         --$font[$i];
       } while (($x[$i] < 0) && ($font[$i] > 0));
       ++$font[$i];
     }
     $lines = count($text); if ($lines>$this->maxlines) $lines = $this->maxlines;
     $y = $this->vmidth - (imagefontheight($this->font) * $lines / 2);
     $textcolor_array = explode(",", $this->textcolor);
     $color = ImageColorAllocate($this->label, $textcolor_array[0], $textcolor_array[1], $textcolor_array[2]);
     for ($i=0;$i<count($text),$i<4;$i++) {
       imagestring($this->label, $font[$i], $x[$i], $y, "$text[$i]", $color);
       $y += imagefontheight($this->font);
     }
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