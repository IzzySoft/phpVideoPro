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
   $error = lang("invalid_media_nr") . "</P>\n";
   display_error($error);
   exit;
 }

 # check wether there already is an entry with the given Movie ID
 if ( $db->get_movieid($mtype_id,$cass_id,$part) ) {
   $error = lang("dupe_id_entered");
   display_error($error);
   exit;
 }

 # check if "fsk" (= pg, parental guide) is integer
 if ( !$valid->num($fsk) ) {
   $error = lang("fsk");
   $error = lang("invalid_fsk",$error) . "</P>\n";
   display_error($error);
   exit;
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
 $idfields = array("director_list","music_list","vis_actor1","vis_actor2",
             "vis_actor3","vis_actor4","vis_actor5","lp","cat2_id","cat3_id");
 foreach ($idfields as $field) {
   if (!$$field) $$field = 0;
 }

 $insert  = "INSERT INTO video (mtype_id,cass_id,part,title,length,aq_date,source,director_id,director_list,"
          . "music_id,music_list,country,year,cat1_id,cat2_id,cat3_id,actor1_id,actor2_id,actor3_id,"
          . "actor4_id,actor5_id,actor1_list,actor2_list,actor3_list,actor4_list,actor5_list,tone_id,"
          . "pict_id,color_id,fsk,comment,lp,counter1,counter2,commercials_id) "
          . "VALUES ("
          . "$mtype_id,$cass_id,$part,'$title',$length,'$recdate','$src',$dir_id,$director_list,"
          . "$mus_id,$music_list,'$country',$year,$cat1_id,$cat2_id,$cat3_id,$act1_id,$act2_id,$act3_id,"
          . "$act4_id,$act5_id,$vis_actor1,$vis_actor2,$vis_actor3,$vis_actor4,$vis_actor5,$tone_id,"
          . "$pict_id,$color_id,$fsk,'$comment',$lp,'$counter1','$counter2',$commercials_id)";
 if ( dbquery($insert) ) {
   $save_result = $colors["ok"] . lang("create_success") . ".</Font><BR>\n";
 } else {
   $save_result = $colors["err"] . lang("update_failed") . "!</Font><BR>\n";
 };
 ##############################################################################
 # updating free time on media for (Re)Writable Media
 if ( $pvp->common->medium_is_rw($mtype_id) ) { // calc free space only for writable media
   $db->update_freetime($cass_id,$mtype_id);
 }
 
?>