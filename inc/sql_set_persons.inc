<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # prepare for db update: check wether all given actors/director etc. are in #
 # db and obtain their IDs, construct the SQL update statement as well as    #
 # debug output, and finally do the update                                   #
 #############################################################################

 /* $Id$ */

 $details = array("director_name","director_fname","composer_name","composer_fname");
 foreach ($details as $var) {
   ${$var} = $pvp->common->input2string(${$var});
   if ( ( bool ) !ini_get( 'magic_quotes_gpc' ) ) ${$var} = addslashes(${$var});
 }
 #------------------[ perform check: Was any staff member changed/removed? ]---
 $details = array("director","composer");
 foreach ($details as $var) {
    $old_name  = trim($_POST["old_${var}_name"]);
    $old_fname = trim($_POST["old_${var}_fname"]);
    if (($_POST[$var."_name"]!=$old_name || $_POST[$var."_fname"]!=$old_fname)
       && !empty($old_name) && !empty($old_fname)) {
     if ($var=="director") {
       $tname = $db->get_director($_POST["old_${var}_id"]);
       $trec  = $db->get_movienamelist("directors",$tname,TRUE);
       if (count($trec) <2) $db->delete_director($_POST["old_${var}_id"]);
     } else {
       $tname = $db->get_music($_POST["old_${var}_id"]);
       $trec  = $db->get_movienamelist("music",$tname,TRUE);
       if (count($trec) <2) $db->delete_composer($_POST["old_${var}_id"]);
     }
   }
 }
 for ($i=1;$i<=$max["actors"];++$i) {
   $old_name  = trim($_POST["old_actor${i}_name"]);
   $old_fname = trim($_POST["old_actor${i}_fname"]);
   if (($old_name!=$_POST["actor${i}_name"] || $old_fname!=$_POST["actor${i}_fname"])
      && !empty($old_name) && !empty($old_fname)) {
     $tname = $db->get_actor($movie["actor${i}_id"]);
     $trec  = $db->get_movienamelist("actors",$tname,TRUE);
     if (count($trec) <2) $db->delete_actor($movie["actor${i}_id"]);
   }
 }

 #-------------------------[ Insert staff members if they do not yet exist ]---
 $dmsg = "";
 $dmsg     .= "<SPAN CLASS='ok'><b>Preparing Update</b>:</SPAN><p>";
 $dmsg     .= "<ul>\n";
 $query     = "SELECT id FROM directors";
 $sub_query = "INSERT INTO directors";
 $dir_id    = insert_person("director",$query,$sub_query,$director_name,$director_fname);
 $query     = "SELECT id FROM music";
 $sub_query = "INSERT INTO music";
 $mus_id    = insert_person("composer",$query,$sub_query,$composer_name,$composer_fname);
 for ($i=1;$i<=$max["actors"];$i++) {
   $act       = "actor" . $i;
   $aname     = $act . "_name";
   $fname     = $act . "_fname";
   $aid       = "act" . $i . "_id";
   $query     = "SELECT id FROM actors";
   $sub_query = "INSERT INTO actors";
   if ( ( bool ) !ini_get( 'magic_quotes_gpc' ) ) {
     ${$aid}    = insert_person($act,$query,$sub_query,addslashes($pvp->common->input2string(${$aname})),addslashes($pvp->common->input2string(${$fname})));
   } else {
     ${$aid}    = insert_person($act,$query,$sub_query,$pvp->common->input2string(${$aname}),$pvp->common->input2string(${$fname}));
   }
 }
 $dmsg .= "</ul>\n";
 debug("S",$dmsg);
?>