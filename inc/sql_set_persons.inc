<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2009 by Itzchak Rehberg #
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

 #--------------------------------------------------[ safeguard variables ]---
 $details  = array("director_name","director_fname","composer_name","composer_fname",
                   "old_director_name","old_director_fname","old_composer_name","old_composer_fname");
 $idetails = array("director_imdbid","composer_imdbid");
 $ids = array("director_id","composer_id","old_director_id","old_composer_id");
 for ($i=1;$i<=$max["actors"];++$i) {
   $details    = array_merge($details,array("old_actor${i}_name","old_actor{$i}_fname","actor${i}_name","actor${i}_fname"));
   $idetails[] = "actor${i}_imdbid";
   $ids[]      = "actor${i}_id";
 }
 foreach ($details as $var) {
   ${$var} = $pvp->common->input2string(${$var});
   if ( ( bool ) !ini_get( 'magic_quotes_gpc' ) ) ${$var} = addslashes(${$var});
 }
 foreach($idetails as $var) { // IMDB ID: 7 digits
   if (!preg_match("|^\d{7}$|",${$var})) ${$var} = "";
 }
 foreach($ids as $var) { // ID: only digits
   if (!preg_match("|^\d*$|",${$var})) ${$var} = "";
 }
 #------------------[ perform check: Was any staff member changed/removed? ]---
 $details = array("director","composer");
 foreach ($details as $var) { // delete removed director/composer if not referenced anymore
    $old_name  = trim(${"old_${var}_name"});
    $old_fname = trim(${"old_${var}_fname"});
    if ((${"${var}_name"}!=$old_name || ${"${var}_fname"}!=$old_fname)
       && !empty($old_name) && !empty($old_fname)) {
     if ($var=="director") {
       $tname = $db->get_director(${"old_${var}_id"});
       $trec  = $db->get_movienamelist("directors",$tname,TRUE);
       if (count($trec) <2) $db->delete_director(${"old_${var}_id"});
     } else {
       $tname = $db->get_music(${"old_${var}_id"});
       $trec  = $db->get_movienamelist("music",$tname,TRUE);
       if (count($trec) <2) $db->delete_composer(${"old_${var}_id"});
     }
   }
 }
 for ($i=1;$i<=$max["actors"];++$i) { // delete removed actor if not referenced anymore
   $old_name  = trim(${"old_actor${i}_name"});
   $old_fname = trim(${"old_actor${i}_fname"});
   if (($old_name!=${"actor${i}_name"} || $old_fname!=${"actor${i}_fname"})
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
 $query     = "SELECT id FROM pvp_directors";
 $sub_query = "INSERT INTO pvp_directors";
 $dir_id    = insert_person("director",$query,$sub_query,$director_name,$director_fname,$director_imdbid);
 $query     = "SELECT id FROM pvp_music";
 $sub_query = "INSERT INTO pvp_music";
 $mus_id    = insert_person("composer",$query,$sub_query,$composer_name,$composer_fname,$music_imdbid);
 for ($i=1;$i<=$max["actors"];$i++) {
   $act       = "actor" . $i;
   $aname     = $act . "_name";
   $fname     = $act . "_fname";
   $aid       = "act" . $i . "_id";
   $iid       = "actor${i}_imdbid";
   $query     = "SELECT id FROM pvp_actors";
   $sub_query = "INSERT INTO pvp_actors";
   ${$aid}    = insert_person($act,$query,$sub_query,${$aname},${$fname},${$iid});
 }
 $dmsg .= "</ul>\n";
 debug("S",$dmsg);
?>