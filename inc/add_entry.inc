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
 # check wether a valid media number can be constructed from user input
 if ( $mtype_id<1 || trim($cass_id)=="" || trim($part)=="" || !((int)$cass_id) || !((int)$part) ) {
   $error = "The MediaNr you specified is either incomplete or invalid. "
         . "You must specify a <b>number</b> in <b>both</b> MediaNr fields.</P>\n";
   display_error($error);
   exit;
 }

 ##############################################################################
 # check wether there already is an entry with the given Movie ID
 $query = "SELECT id FROM video"
        . " WHERE mtype_id='$mtype_id' AND cass_id='$cass_id' AND part='$part'";
 dbquery($query);
 if ( $db->next_record() ) {
   $error = "There is already an entry in the database for the "
          . "entered media ID. Please hit the \"Back\" button of your browser "
          . "and correct your input. Hint: There is a Select-Box next to the "
          . "input box you specified the media number in. This select box tells "
          . "you the highest existing movie id. Normally it is a good choice for "
          . "a new media to increase the first (four-digit) number by one, or for "
          . "a new movie on the same media, increase the second (two-digit) number "
          . "by one.";
   display_error($error);
   exit;
 }

 ##############################################################################
 # check wether the specified date is valid
 check_date($recdate);

 include("inc/sql_set_persons.inc");

 if ($cat2_id < 0) $cat2_id="";
 if ($cat3_id < 0) $cat3_id="";
 if ($pict_id < 0) $pict_id="";
 (int) $cass_id;
 (int) $part;

 $insert  = "INSERT INTO video (mtype_id,cass_id,part,title,length,aq_date,source,director_id,director_list,"
          . "music_id,music_list,country,year,cat1_id,cat2_id,cat3_id,actor1_id,actor2_id,actor3_id,"
          . "actor4_id,actor5_id,actor1_list,actor2_list,actor3_list,actor4_list,actor5_list,tone_id,"
          . "pict_id,color_id,fsk,comment,lp) "
          . "VALUES ("
          . "'$mtype_id','$cass_id','$part','$title','$length','$recdate','$src','$dir_id','$director_list',"
          . "'$mus_id','$music_list','$country','$year','$cat1_id','$cat2_id','$cat3_id','$act1_id','$act2_id','$act3_id',"
          . "'$act4_id','$act5_id','$vis_actor1','$vis_actor2','$vis_actor3','$vis_actor4','$vis_actor5','$tone_id',"
          . "'$pict_id','$color_id','$fsk','$comment','$lp')";
 debug("S",$colors["ok"] . "<p><b>Executing Final Query:</b><br>$insert</p></Font>");
 if ( dbquery($insert) ) {
   $save_result = $colors["ok"] . "Entry created successfully.</Font><BR>\n";
 } else {
   $save_result = $colors["err"] . "Failed to update entry!</Font><BR>\n";
 };
 ##############################################################################
 # updating free time on media for Recorded Video Tapes
 if ($lp) $length /= 2;
 $free = $mlength - $length;
 $query = "SELECT sname FROM mtypes WHERE id='$mtype_id'";
 dbquery($query);
 if ( !$db->next_record() ) {
   debug("E",$colors["err"] . "Could not obtain media type for mtype_id '$mtype_id'!</Font><BR>\n");
 } elseif ( strtolower($db->f('sname'))=="rvt" ) { // calc free space only for recorded video tapes
   $query = "SELECT type FROM cass WHERE id='$cass_id'";
   dbquery($query);
   if ( !$db->next_record() ) {
     $query = "INSERT INTO cass (id,type,free) VALUES ('$cass_id','$mlength','$free')";
     dbquery($query);
   } else {
     $query = "UPDATE cass SET free='$free' WHERE id='$cass_id'";
     dbquery($query);
   }
 }
 
?>