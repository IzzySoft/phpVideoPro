<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # insert an entry into the database                                         #
 #############################################################################

 /* $Id$ */

 # check wether a valid media number can be constructed from user input
 if ( !$valid->medianr($mtype_id,$cass_id,$part) ) {
   die ( display_error ( lang("invalid_media_nr") . "</P>\n") );
 }

 # check if "fsk" (= pg, parental guide) is integer
 if ( !$valid->num($fsk) ) {
   die ( display_error( lang("invalid_fsk",$fsk) . "</P>\n") );
 }

 # check wether the specified date is valid
 if (!$recday)  $recday  = "0";
 if (!$recmon)  $recmon  = "0";
 if (!$recyear) $recyear = "0";
 $recdate = $pvp->common->makeRecDateStr($recyear,$recmon,$recday);
 check_date($recdate,0);

 include("inc/sql_set_persons.inc");

 if ($cat2_id < 0) $cat2_id="0";
 if ($cat3_id < 0) $cat3_id="0";
 if ($pict_id < 0) $pict_id="0";
 (int) $cass_id;
 (int) $part;

 # no *_list field shall be NULL
 $idfields = array("label","director_list","music_list","vis_actor1","vis_actor2",
             "vis_actor3","vis_actor4","vis_actor5","lp","cat2_id","cat3_id");
 foreach ($idfields as $field) {
   if (!$$field) $$field = 0;
 }

 # region code settings
 $rccount = count($rc);
 if ($rccount) {
   for ($i=0;$i<$rccount;++$i) {
     $mrc[$rc[$i]] = 1;
   }
   $movie[rc] = $mrc;
 }

 # prepare the movie array
 $fields = array("mtype_id","cass_id","part","title","length","country","year",
                 "cat1_id","cat2_id","cat3_id","director_list","music_list",
		 "tone_id","pict_id","color_id","fsk","comment","lp",
		 "counter1","counter2","commercials_id","label","disktype");
 foreach ($fields as $value) {
   $movie[$value] = ${$value};
 }
 $movie[aq_date] = $recdate; $movie[source] = $src; $movie[space] = $mlength;
 $movie[director_id] = $dir_id; $movie[music_id] = $mus_id;
 for ($i=1;$i<6;++$i) {
   $id  = "actor".$i."_id"; $list = "actor".$i."_list";
   $ids = "act".$i."_id";  $lists = "vis_actor".$i;
   $movie[$id] = ${$ids}; $movie[$list] = ${$lists};
 }

 # add the movie to DB
 if ( $db->add_movie($movie) ) {
   $save_result = $colors["ok"] . lang("create_success") . ".</Font><BR>\n";
 } else {
   $save_result = $colors["err"] . lang("update_failed") . "!</Font><BR>\n";
 };
 
?>