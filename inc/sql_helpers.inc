<?php // SQL helpers

 ##############################################################################
 # query db and provide debug output
  function dbquery($query) {
    GLOBAL $db,$colors;
    debug("S",$colors["ok"] . "$query</Font><BR>\n");
    if ( $db->query($query) ) return 1;
    return 0;
  }

 ##############################################################################
 # check wether a given person exists in the db and aquire his/her id. If not
 # found in db, insert him/her first
 function insert_person($person,$query,$sub_query,$name="",$fname="") {
   GLOBAL $db,$dmsg,$colors;
   if ( strlen( trim($name . $fname) ) < 1) {
     $dmsg .=  $colors["ok"] . "<li>$person not specified, no action taken.</Font>\n";
    return 0;
   }
   $dmsg  .= $colors["ok"] . " <li>" . stripslashes($query) . "</Font>";
   dbquery($query);
   if ( $db->next_record() ) {
     $id = $db->f('id');
     $dmsg  .= " (Got: '$id')</Font>\n";
   } else {
     $dmsg  .= "<BR>" . $colors["err"] . "$person not found in db! Trying to insert...</Font><BR>\n";
     if ( dbquery($sub_query) ) {
       dbquery($query);
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
?>