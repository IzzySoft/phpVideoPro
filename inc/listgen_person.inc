<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Create a list of all movies sorted by director/actor/componist            *
 \***************************************************************************/

 /* $Id$ */

   function sort_names($ar1,$ar2) {
     if ($ar1[reverse]<$ar2[reverse]) return -1;
      else if ($ar1[reverse]>$ar2[reverse]) return 1;
   }

   $namelist = $db->get_director("");
   uasort($namelist,"sort_names");
   reset($namelist);
   foreach ($namelist as $name) {
     $m = $db->get_movienamelist("directors",$name[id]);
     if (is_array($movielist)) {
       $movielist = array_merge($movielist,$m);
     } else {
       $movielist = $m;
     }
   }

   $listlength = count($movielist);
   if ($align) {
     $listheader = $pvp->common->centerstr(lang("director"),25) . $sep
                 . $pvp->common->centerstr(lang("title"),36) . $sep
                 . $pvp->common->centerstr(lang("category"),15) . $sep
                 . $pvp->common->centerstr(lang("length"),5)
		 . $pvp->common->centerstr(lang("medium"),12);
   } else {
     if ($outputtype=="html") $fullrow = "<TR><TD COLSPAN=\"5\">";
     $listheader = $blockstart . $linestart
                 . lang("director") . $sep
                 . lang("title") . $sep
                 . lang("category") . $sep
                 . lang("length") . $sep
                 . lang("medium") . $lineend;
   }
   for ($i=0;$i<$pagewidth;$i++) {
     $underline .= "-";
   }
   $pagelength -= 4; // we need 4 lines for the title & header
   $pages = ceil($listlength / $pagelength); $page = 0;

   // build the list
   if (!$multipage) $out = "$listheader\n";
   for ($i=0,$k=0;$i<$listlength;$i++,$k++) {
     if ($multipage && !($k % $pagelength)) { // new page
       ++$page;
       if ($i) $out .= "\x0C"; // no formfeed on the first page
       $out .= listtitle($page,$pages) . "\n";
       $out .= "\n$listheader\n$underline\n";
     }
#     if (strlen($movielist[$i][lp])) { $lp = lang("yes"); } else { $lp = lang("no"); }
     if ($align) {
       $title  = $pvp->common->fillblanks($movielist[$i][title],36);
       $cat    = $pvp->common->centerstr($movielist[$i][cat1],15);
       $length = $pvp->common->padblanks($movielist[$i][length],5);
       $name   = $pvp->common->fillblanks($movielist[$i][director_rev],25);
#       $lp     = $pvp->common->centerstr($lp,4);
     } else {
       $title  = $movielist[$i][title];
       $cat    = $movielist[$i][cat1];
       $length = $movielist[$i][length];
       $name   = $movielist[$i][director_rev];
     }
     $line = $linestart . $name . $sep
	   . $title . $sep
	   . $cat . $sep
	   . $length . $sep
#	   . $lp . $sep
           . $movielist[$i][mtype_short] . " "
           . $pvp->common->padzeros($movielist[$i][cass_id],4) . "-"
           . $pvp->common->padzeros($movielist[$i][part],2)
	   . $lineend;
     $out .= "$line\n";
   }
   $out .= $blockend;
?>