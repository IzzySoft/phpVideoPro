<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
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

 (int) $cass_id;
 (int) $part;

 # region code settings
 if (isset($rc)) {
  $rccount = count($rc);
  if ($rccount) {
   for ($i=0;$i<$rccount;++$i) {
    $mrc[$rc[$i]] = 1;
   }
   $movie["rc"] = $mrc;
  }
 }

 # prepare the movie array
 $fields = array("mtype_id","cass_id","part","title","length","country","year",
                 "cat1_id","cat2_id","cat3_id","director_list","music_list",
		 "tone_id","pict_id","color_id","fsk","comment","lp",
		 "counter1","counter2","commercials_id","label","disktype",
                 "vnorm_id","imdb_id","rating");
 foreach ($fields as $value) {
   if (isset(${$value})) $movie[$value] = ${$value}; else $movie[$value] = "";
 }
 $movie["private"] = $is_private;
 $movie["title"] = $pvp->common->input2string($movie["title"]);
 $movie["aq_date"] = $recdate; $movie["source"] = $src; $movie["space"] = $mlength;
 $movie["director_id"] = $dir_id; $movie["music_id"] = $mus_id;
 for ($i=1;$i<6;++$i) {
   $id  = "actor".$i."_id"; $list = "actor".$i."_list";
   $ids = "act".$i."_id";  $lists = "vis_actor".$i;
   if (isset(${$ids})) $movie[$id] = ${$ids}; else $movie[$id] = "";
   if (isset(${$lists})) $movie[$list] = ${$lists}; else $movie[$list] = "";
 }

 for ($i=0;$i<SUBTITLES;++$i) {
   $subts = "subtitle".$i;
   $ats   = "audio_ts".$i;
   if (!empty(${$subts}) && ${$subts}!="-") $movie["subtitle"][] = ${$subts};
   if (!empty(${$ats}) && ${$ats} != "-")   $movie["audio"][] = ${$ats};
#   unset(${subts},${$ts});
 }

 # add the movie to DB
 if ( $db->add_movie($movie) ) {
   $save_result = "<SPAN CLASS='ok'>" .lang("create_success"). ".</SPAN><BR>\n";
 } else {
   $save_result = "<SPAN CLASS='error'>" . lang("update_failed") . "!</SPAN><BR>\n";
 };
 
?>