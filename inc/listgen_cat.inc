<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Create a list of all movies                                               #
 #############################################################################

 /* $Id$ */

 if (!isset($linestart)) $linestart = "";
 if (!isset($lineend)) $lineend = "";
 if (!isset($blockstart)) $blockstart = "";
 if (!isset($blockend)) $blockend = "";
 #=============================================[ get movielist by catalog ]===
 $catlist   = $db->get_category("","name");
 $catcount  = count($catlist);
 foreach ($catlist as $cat) {
   $m = $db->get_moviecatlist($cat['id']);
   if (isset($movielist) && is_array($movielist)) {
     $movielist = array_merge($movielist,$m);
   } else {
     $movielist = $m;
   }
 }
 $listlength = count($movielist);

 #===============================================[ setup the lists header ]===
 if ($align) {
   $listheader = $pvp->common->centerstr(lang("medium"),12) . $sep
               . $pvp->common->centerstr(lang("title"),55) . $sep
               . $pvp->common->centerstr(lang("category") . " 2",17) . $sep
               . $pvp->common->centerstr(lang("length"),5) . $sep
               . $pvp->common->centerstr("LP",4);
 } else {
   if ($outputtype=="html") $fullrow = "<TR><TD COLSPAN=\"5\">";
   $listheader = $blockstart . $linestart
               . lang("medium") . $sep
               . lang("title") . $sep
               . lang("category") . " 2" . $sep
               . lang("length") . $sep
               . "LP" . $lineend;
 }
 $underline = "";
 for ($i=0;$i<$pagewidth;$i++) {
   $underline .= "-";
 }
 $pagelength -= 4; // we need 4 lines for the title & header
 $pages = ceil(($listlength + $catcount *3) / $pagelength); $page = 0;

 #=======================================================[ build the list ]===
 if (!$multipage) $out = "$listheader\n"; else $out = "";
 if (!isset($fullrow)) $fullrow = ""; // ? what was that for ?
 for ($i=0,$k=0;$i<$listlength;$i++,$k++) {
   if ($multipage && !($k % $pagelength)) { // new page
     set_time_limit(0);
     ++$page;
     if ($i) $out .= "\x0C"; // no formfeed on the first page
     $out .= listtitle($page,$pages) . "\n";
     $out .= "\n$listheader\n$underline\n";
   }
   if (!isset($recentcat)) $recentcat = "";
   if ($recentcat != $movielist[$i]['cat1']) {
     $recentcat = $movielist[$i]['cat1'];
     $out .= "\n" . $fullrow . lang("category") . " $recentcat\n\n" . $lineend;
     $k +=3;
   }
   if (strlen($movielist[$i]['lp'])) { $lp = lang("yes"); } else { $lp = lang("no"); }
   if ($align) {
     $title  = $pvp->common->fillblanks($movielist[$i]['title'],55);
     $cat    = $pvp->common->centerstr($movielist[$i]['cat2'],17);
     $length = $pvp->common->padblanks($movielist[$i]['length'],5);
     $lp     = $pvp->common->centerstr($lp,4);
   } else {
     $title  = $movielist[$i]['title'];
     $cat    = $movielist[$i]['cat2'];
     $length = $movielist[$i]['length'];
   }
   $line = $linestart . $movielist[$i]['mtype_short'] . " "
         . $pvp->common->padzeros($movielist[$i]['cass_id'],4) . "-"
         . $pvp->common->padzeros($movielist[$i]['part'],2) . $sep
         . $title . $sep
         . $cat . $sep
         . $length . $sep
         . $lp . $lineend;
   $out .= "$line\n";
 }
 $out .= $blockend;
?>