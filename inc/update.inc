<?
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
 # check wether the specified date is valid
 check_date($recdate);

 include("inc/sql_set_persons.inc");

 if ($cat2_id < 0) $cat2_id="";
 if ($cat3_id < 0) $cat3_id="";
 if ($pict_id < 0) $pict_id="";
 $update  = "UPDATE video SET title='$title',country='$country',length='$length',year='$year',tone_id='$tone_id',"
          . "color_id='$color_id',aq_date='$recdate',source='$src',fsk='$fsk',comment='$comment',"
          . "actor1_list='$vis_actor1',actor2_list='$vis_actor2',actor3_list='$vis_actor3',"
          . "actor4_list='$vis_actor4',actor5_list='$vis_actor5',cat1_id='$cat1_id',cat2_id='$cat2_id',"
          . "cat3_id='$cat3_id',pict_id='$pict_id',director_id='$dir_id',music_id='$mus_id',"
          . "actor1_id='$act1_id',actor2_id='$act2_id',actor3_id='$act3_id',actor4_id='$act4_id',"
          . "actor5_id='$act5_id',lp='$lp',music_list='$music_list',director_list='$director_list'"
          . " WHERE cass_id='$cass_id' AND part='$part'";
 debug("S",$colors["ok"] . "<p><b>Executing Final Query:</b><br>$update</p></Font>");
 if ( $db->query($update) ) {
   debug("S",$colors["ok"] . "Query completed successfully.</Font>\n");
   $save_result = $colors["ok"] . "Entry updated successfully.</Font><BR>\n";
 } else {
   debug("E",$colors["err"] . "Query failed to execute!</Font>\n");
   $save_result = $colors["err"] . "Failed to update entry!</Font><BR>\n";
 };
 ##############################################################################
 # updating free time on media for Recorded Video Tapes
 $query = "SELECT sname FROM mtypes WHERE id='$mtype_id'";
 debug("S",$colors["ok"] . "$query</Font><BR>\n");
 $db->query($query);
 if ( !$db->next_record() ) {
   debug("E",$colors["err"] . "Could not obtain media type for mtype_id '$mtype_id'!</Font><BR>\n");
 } elseif ( strtolower($db->f('sname'))=="rvt" ) { // calc free space only for recorded video tapes
   $query = "SELECT type FROM cass WHERE id='$cass_id'";
   debug("S",$colors["ok"] . "$query</Font><BR>\n");
   $db->query($query);
   if ( !$db->next_record() ) {
     debug("E",$colors["err"] . "Could not obtain media info for cass_id '$cass_id'!</Font><BR>\n");
   } else {
     $media_length = $db->f('type');
     if ( $media_length<$min["media_size"] ) debug("W",$colors["err"] . "Invalid Media size '$media_length' (should be at least '" . $min["media_size"] . "')!</Font><BR>\n");
     $query = "SELECT length,lp FROM video WHERE cass_id='$cass_id'";
     debug("S",$colors["ok"] . "$query</Font><BR>\n");
     $db->query($query);
     $i=0;
     while ( $db->next_record() ) {
       $i++;
       $mlength = $db->f('length');
       if ( $db->f('lp') ) $mlength /= 2;
       $media_length -= $mlength;
     }
     if ($i==0) debug("W",$colors["err"] . "No items found on media '$cass_id', so tape must be empty. If so, you'ld better delete it instead of updating without contents. Otherwise, there may be a problem!</Font><BR>\n");
     $query = "UPDATE cass SET free='$media_length' WHERE id='$cass_id'";
     debug("S",$colors["ok"] . "$query</Font><BR>\n");
     $db->query($query);
   }
 }
 
?>