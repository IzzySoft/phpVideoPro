<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Create a list of all movies                                               *
 \***************************************************************************/

 /* $Id$ */


   $movielist = $db->get_movielist($order);
   $listlength = count($movielist);
   if ($align) {
     $listheader = $pvp->common->centerstr(lang("medium"),12) . $sep
                 . $pvp->common->centerstr(lang("title"),55) . $sep
                 . $pvp->common->centerstr(lang("category"),17) . $sep
                 . $pvp->common->centerstr(lang("length"),5) . $sep
	         . $pvp->common->centerstr("LP",4);
   } else {
     $listheader = $blockstart . $linestart
                 . lang("medium") . $sep
                 . lang("title") . $sep
                 . lang("category") . $sep
                 . lang("length") . $sep
	         . "LP" . $lineend;
   }
   for ($i=0;$i<$pagewidth;$i++) {
     $underline .= "-";
   }
   $pagelength -= 4; // we need 4 lines for the title & header
   $pages = ceil($listlength / $pagelength); $page = 0;

   // build the list
   if (!$multipage) $out = "$listheader\n";
   for ($i=0;$i<$listlength;$i++) {
     if ($multipage && !($i % $pagelength)) { // new page
       ++$page;
       if ($i) $out .= "\x0C"; // no formfeed on the first page
       $out .= listtitle($page,$pages) . "\n";
       $out .= "\n$listheader\n$underline\n";
     }
     if (strlen($movielist[$i][lp])) { $lp = lang("yes"); } else { $lp = lang("no"); }
     if ($align) {
       $title  = $pvp->common->fillblanks($movielist[$i][title],55);
       $cat    = $pvp->common->centerstr($movielist[$i][cat1],17);
       $length = $pvp->common->padblanks($movielist[$i][length],5);
       $lp     = $pvp->common->centerstr($lp,4);
     } else {
       $title  = $movielist[$i][title];
       $cat    = $movielist[$i][cat1];
       $length = $movielist[$i][length];
     }
     $line = $linestart . $movielist[$i][mtype_short] . " "
           . $pvp->common->padzeros($movielist[$i][cass_id],4) . "-"
           . $pvp->common->padzeros($movielist[$i][part],2) . $sep
	   . $title . $sep
	   . $cat . $sep
	   . $length . $sep
	   . $lp . $lineend;
     $out .= "$line\n";
   }
   $out .= $blockend;
?>