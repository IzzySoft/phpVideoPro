<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Update an entry in the DB (with all needed checks etc.)                   #
 #############################################################################

 /* $Id$ */

 ##############################################################################
 # create a dump of posted data for debugging purposes and send them to the
 # debug output function
 $ddump = "Saving data:<p>\n<ul>";
 while (list($key, $val) = each($HTTP_POST_VARS)) {
   $ddump .= "<li>$key => $val<br>";
 }
 $ddump .= "</ul></TD><TD>\n";
 debug("V",$ddump);

 ##############################################################################
 # check if "fsk" (= pg, parental guide) is integer
 if ( !$valid->num($fsk) ) {
   $error = lang("fsk");
   $error = lang("invalid_fsk",$error) . "</P>\n";
   display_error($error);
   exit;
 }

 ##############################################################################
 # check wether the specified date is valid
 if (!$recday)  $recday  = "0";
 if (!$recmon)  $recmon  = "0";
 if (!$recyear) $recyear = "0";
 $recdate = $pvp->common->makeRecDateStr($recyear,$recmon,$recday);
 check_date($recdate,0);

 include("inc/sql_set_persons.inc");

 $idfields = array("pict_id","director_list","music_list","vis_actor1","vis_actor2",
             "vis_actor3","vis_actor4","vis_actor5","lp","cat2_id","cat3_id","label");
 foreach ($idfields as $field) {
   if (!$$field) $$field = 0;
 }

 $title   = $pvp->common->input2string($title);
 if ( ( bool ) !ini_get( 'magic_quotes_gpc' ) ) {
   $title   = addslashes($title);
   $comment = addslashes($comment);
   $source  = addslashes($source);
 }

 $title   = $pvp->common->safeinput($title);
 $source  = $pvp->common->safeinput($source);
 $comment = $pvp->common->safetextarea($comment);
 $fields   = array("country","year","length","src","fsk","counter1","counter2");
 foreach ($fields as $field) {
   ${$field} = $pvp->common->safeinput(${$field});
 }
 $update  = "UPDATE video SET title='$title',label=$label,country='$country',length=$length,year=$year,tone_id=$tone_id,"
          . "color_id=$color_id,aq_date='$recdate',source='$src',fsk=$fsk,comment='$comment',"
          . "actor1_list=$vis_actor1,actor2_list=$vis_actor2,actor3_list=$vis_actor3,"
          . "actor4_list=$vis_actor4,actor5_list=$vis_actor5,cat1_id=$cat1_id,cat2_id=$cat2_id,"
          . "cat3_id=$cat3_id,pict_id=$pict_id,director_id=$dir_id,music_id=$mus_id,"
          . "actor1_id=$act1_id,actor2_id=$act2_id,actor3_id=$act3_id,actor4_id=$act4_id,"
          . "actor5_id=$act5_id,lp=$lp,music_list=$music_list,director_list=$director_list,"
	  . "counter1='$counter1',counter2='$counter2',commercials_id=$commercials_id"
          . " WHERE cass_id=$cass_id AND part=$part AND mtype_id=$mtype_id";
 debug("S","<P CLASS='ok'><b>Executing Final Query:</b><br>$update</P>");
# die($update);
 if ( dbquery($update) ) {
   debug("S","<SPAN CLASS='ok'>Query completed successfully.</SPAN>\n");
   $save_result = "<SPAN CLASS='ok'>" .lang("update_success"). ".</SPAN><BR>\n";
 } else {
   debug("E","<SPAN CLASS='error'>Query failed to execute!</SPAN>\n");
   $save_result = "<SPAN CLASS='error'>" . lang("update_failed") . "!</SPAN><BR>\n";
 };
 ##############################################################################
 # updating free time on media for Recorded Video Tapes
 if ( $pvp->common->medium_is_rw($mtype_id) ) { // calc free space only for writable media
   $media_length = $db->get_mediaspace($cass_id,$mtype_id);
   $db->update_freetime($cass_id,$mtype_id);
 }
?>