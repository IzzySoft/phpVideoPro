<?
 $dmsg = "";
 function insert_person($person,$query,$sub_query,$name="",$fname="") {
   GLOBAL $db,$dmsg,$colors;
   if ( strlen( trim($name . $fname) ) < 1) {
     $dmsg .=  $colors["ok"] . "<li>$person not specified, no action taken.</Font>\n";
    return "";
   }
   $db->query($query);
   if ( $db->next_record() ) {
     $id = $db->f('id');
     $dmsg  .= $colors["ok"] . " <li>" . stripslashes($query) . " (Got: '$id')</Font>\n";
   } else {
     $dmsg  .= $colors["err"] . " <li>" . stripslashes($query) . " ($person not found in db! Trying to insert...)</Font><BR>\n";
     if ( $db->query($sub_query) ) {
       $db->query($query);
       if ( $db->next_record() ) {
         $id = $db->f('id');
         $dmsg  .= $colors["ok"] . "$person \"$name, $fname\" inserted into db (id: $id).</Font>\n";
       } else {
         $dmsg  .= $colors["err"] . "Something strange happened: inserted $person \"$name, $fname\" into db, but could not find him/her afterwards!</Font>\n";
       }
     } else {
       $dmsg .= $colors["err"] . "Insertion of $person \"$name, $fname\ into db failed!</Font>\n";
     }
   }
   return $id;
 }
 // *** creating data dump ***
 $ddump = "Saving data:<p>\n<ul>"
    . " <li>Title: '$title'"
    . " <li>MediaType: '$media_tid'"
    . " <li>Country: '$country'"
    . " <li>MediaNr: '$nr'"
    . " <li>Director: '$director_name, $director_fname'"
    . " <li>Length: '$length'"
    . " <li>Composer: '$composer_name, $composer_fname'"
    . " <li>Year: '$year'"
    . " <li>ToneID: '$tone_id'"
    . " <li>Cat1_ID: '$cat1_id'"
    . " <li>Cat2_ID: '$cat2_id'"
    . " <li>Cat3_ID: '$cat3_id'"
    . " <li>ColorID: '$color_id'"
    . " <li>Aquired: '$recdate'"
    . " <li>ScreenID: '$pict_id'"
    . " <li>Source: '$src'"
    . " <li>FSK: '$fsk'"
    . " <li>Actor1: '$actor1_name, $actor1_fname'"
    . " <li>Actor2: '$actor2_name, $actor2_fname'"
    . " <li>Actor3: '$actor3_name, $actor3_fname'"
    . " <li>Actor4: '$actor4_name, $actor4_fname'"
    . " <li>Actor5: '$actor5_name, $actor5_fname'"
    . " <li>Visible1: '$vis_actor1'"
    . " <li>Visible2: '$vis_actor2'"
    . " <li>Visible3: '$vis_actor3'"
    . " <li>Visible4: '$vis_actor4'"
    . " <li>Visible5: '$vis_actor5'"
    . " <li>Comment: '$comment'"
    . "</ul>";
 debug("V",$ddump);
 $dmsg     .= $colors["ok"] . "<b>Preparing Update</b>:</Font><p>";
 $dmsg     .= "<ul>\n";
 $query     = "SELECT id FROM directors WHERE name='$director_name' AND firstname='$director_fname'";
 $sub_query = "INSERT INTO directors (name,firstname) VALUES ('$director_name','$director_fname')";
 $dir_id    = insert_person("director",$query,$sub_query,$director_name,$director_fname);
 $query     = "SELECT id FROM music WHERE name='$composer_name' AND firstname='$composer_fname'";
 $sub_query = "INSERT INTO music (name,firstname) VALUES ('$composer_name','$composer_fname')";
 $mus_id    = insert_person("composer",$query,$sub_query,$composer_name,$composer_fname);
 for ($i=1;$i<=$max["actors"];$i++) {
   $act       = "actor" . $i;
   $aname     = $act . "_name";
   $fname     = $act . "_fname";
   $aid       = "act" . $i . "_id";
   $query     = "SELECT id FROM actors WHERE name='" . ${$aname} . "' AND firstname='" . ${$fname} . "'";
   $sub_query = "INSERT INTO actors (name,firstname) VALUES ('" . ${$aname} . "','" . ${$fname} . "')";
   ${$aid}    = insert_person($act,$query,$sub_query,${$aname},${$fname});
 }
 $dmsg .= "</ul>\n";
 debug("S",$dmsg);
 if ($cat2_id < 0) $cat2_id="";
 if ($cat3_id < 0) $cat3_id="";
 if ($pict_id < 0) $pict_id="";
 $cass_id = (int) substr($nr,0,4); $part = (int) substr($nr,6);
 $update  = "UPDATE video SET title='$title',country='$country',length='$length',year='$year',tone_id='$tone_id',"
          . "color_id='$color_id',aq_date='$recdate',source='$src',fsk='$fsk',comment='$comment',"
          . "actor1_list='$vis_actor1',actor2_list='$vis_actor2',actor3_list='$vis_actor3',"
          . "actor4_list='$vis_actor4',actor5_list='$vis_actor5',cat1_id='$cat1_id',cat2_id='$cat2_id',"
          . "cat3_id='$cat3_id',pict_id='$pict_id',director_id='$dir_id',music_id='$mus_id',"
          . "actor1_id='$act1_id',actor2_id='$act2_id',actor3_id='$act3_id',actor4_id='$act4_id',"
          . "actor5_id='$act5_id',mtype_id='$media_tid' WHERE cass_id='$cass_id' AND part='$part'";
 debug("S",$colors["ok"] . "<p><b>Executing Final Query:</b><br>$update</p></Font>");
 if ( $db->query($update) ) {
   debug("S",$colors["ok"] . "Query completed successfully.</Font>\n");
 } else {
   debug("E",$colors["err"] . "Query failed to execute!</Font>\n");
 };
?>