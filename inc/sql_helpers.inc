<?php // SQL helpers

/* $Id$ */

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

 ##############################################################################
 # read a file containing sql statements and execute the statements one-by-one
 function get_sql($file) {
   if ( !file_exists($file) ) return 0;
   $array = file ($file);
   $sql   = ""; $ok = 1;
   for ($i=0;$i<count($array);$i++) {
     $pos  = strpos(" " . trim($array[$i]),"#");
     if ($pos<>1) {
       $sql .= $array[$i];
       $endpos = strpos($sql,";");
       if ($endpos) {
         $sql = substr($sql,0,$endpos);
         if ( !dbquery($sql) ) $ok = 0;
         $sql = "";
       }
     }
   }
   return $ok;
 }

 ##############################################################################
 # interface to get_sql()
 function queryf($file,$comment,$silent=0) {
   GLOBAL $colors;
   if ( get_sql($file) ) {
     if (!$silent) echo $colors["ok"] . " <li>$comment successful.</Font><BR>\n";
   } else {
     if (!$silent) echo $colors["err"] . " <li>$comment failed, process stopped.</Font><BR>\n";
     exit;
   }
 }

?>