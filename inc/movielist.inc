<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Display MovieList                                                         #
 #############################################################################

 /* $Id$ */

 #=======================================[ get movies and setup variables ]===
 $list = $nextmatch->list;
 for ($i=0;$i<$nextmatch->listcount;$i++) {
   $mtype[$i]    = $list[$i][mtype_short];
   $mtype_id[$i] = $list[$i][mtype_id];
   $cass_id[$i]  = $list[$i][cass_id];
   $nr[$i]       = $cass_id[$i];
   $part[$i]     = $list[$i][part];
   while (strlen($nr[$i])<4) { $nr[$i] = "0" . $nr[$i]; }
   $nr[$i]      .= "-";
   if (strlen($part[$i])<2) {
     $nr[$i] .= "0" . $part[$i];
   } else { $nr[$i] .= $part[$i]; }
#   $movie_id[$i] = urlencode($mtype[$i] . " " . $nr[$i]);
   $movie_id[$i] = urlencode($nr[$i]);
   $title[$i]    = $list[$i][title]; check_empty($title[$i]);
   $length[$i]   = $list[$i][length]; check_empty($length[$i]);
   $year[$i]     = $list[$i][year]; if (!$year[$i]) $year[$i] = ""; check_empty($year[$i]);
   $t_aq_date      = $list[$i][aq_date];  check_empty($t_aq_date);
   $aq_date[$i]  = $pvp->common->formatDate($t_aq_date);
   $category[$i] = $list[$i][cat1]; check_empty($category[$i]);
 }

 #======================================================[ create the list ]===
 include("inc/header.inc");
 #---------------------------------------------------------[ movies' data ]---
 if ( !count($mtype) ) {
   $t->set_var("no_data",lang("no_entries_found"));
   $t->parse("emptylist","emptyblock");
 }
 for ($i=0;$i<count($mtype);$i++) {
   $t->set_var("listtitle",lang("medialist"));
   $t->set_var("mtype",$mtype[$i]);
   $t->set_var("nr",$nr[$i]);
   $t->set_var("title",$title[$i]);
   $t->set_var("length",$length[$i]);
   $t->set_var("year",$year[$i]);
   $t->set_var("date",$aq_date[$i]);
   $t->set_var("category",$category[$i]);
   $t->set_var("url",$pvp->link->slink("edit.php?nr=$movie_id[$i]&cass_id=$cass_id[$i]&part=$part[$i]&mtype_id=$mtype_id[$i]"));
   $t->parse("mdatalist","mdatablock",TRUE);
 }
 #---------------------------------------------------------[ table header ]---
 $t->set_var("mtype",lang("medium"));
 $t->set_var("nr",lang("nr"));
 $t->set_var("title",lang("title"));
 $t->set_var("length",lang("length"));
 $t->set_var("year",lang("year"));
 $t->set_var("date",lang("date_rec"));
 $t->set_var("category",lang("category"));
 $t->set_var("scriptname",$PHP_SELF);
 $t->set_var("first",$nextmatch->first);
 $t->set_var("left",$nextmatch->left);
 $t->set_var("right",$nextmatch->right);
 $t->set_var("last",$nextmatch->last);

 $t->pparse("out","list");

?>