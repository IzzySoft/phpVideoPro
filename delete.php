<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2009 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Delete an entry from DB                                                   #
 #############################################################################

 /* $Id$ */

 #=================================================[ Register global vars ]===
 $postit = array ("mtype_id","cass_id","part","nr","approved","cancel","delete");
 foreach ($postit as $var) {
   if (isset($_POST[$var])) $$var = $_POST[$var];
   else $$var = '';
 }
 $page_id = "delete";
 include("inc/includes.inc");

 #==================================================[ Kick-back on Cancel ]===
 if ($cancel) {
   header("Location: ".$pvp->link->url_path(dirname(__FILE__))."edit.php?nr=" . urlencode("$nr") . "&cass_id=$cass_id&part=$part&mtype_id=$mtype_id");
   exit;
 }

 #==================================================[ Check authorization ]===
 if (!$pvp->auth->delete) kickoff();

 include("inc/header.inc");
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("delete"=>"delete.tpl",
                    "yn"=>"delete_yn.tpl"));
 $t->set_var("listtitle",lang("deleting_entry",$nr));

 $minfo = $db->get_mediainfo($mtype_id,$cass_id);
 if ($minfo->owner_id!=$pvp->auth->user_id
   && !$db->get_usergrants(array($minfo->owner_id),array(0,$pvp->auth->user_id),array("DELETE"))) {
   // logged-in user has no permission on this medium
   $t->set_var("details",lang("no_delete_permission"));
   $t->pparse("out","delete");
   include("inc/footer.inc");
   exit;
 }

 #=========================================================[ Helper Funcs ]===
 function kill($table,$id) {
   GLOBAL $details, $db;
   $details .= " ";
   if ( $db->delete_row("pvp_$table",$id) ) {
     $details .= "<SPAN CLASS='ok'>" .lang("ok"). ".</SPAN><br>\n";
   } else {
     $details .= "<SPAN CLASS='error'>" .lang("not_ok"). "!</SPAN><br>\n";
   }
 }

 #============[ Process input from the EDIT screen - ask for confirmation ]===
 if (!$approved) {
   $t->set_var("formtarget",basename(__FILE__));
   $t->set_var("nr",$nr);
   $t->set_var("cass_id",$cass_id);
   $t->set_var("part",$part);
   $t->set_var("mtype_id",$mtype_id);
   $t->set_var("delete_yn","<SPAN CLASS='error'>" .lang("sure_to_delete",$nr) . "?</SPAN>");
   $t->set_var("no",strtoupper(lang("no")) . "!");
   $t->set_var("yes",lang("yes") . ".");
   if (!$pvp->cookie->active) $t->set_var("sess_id","<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>");
   $t->pparse("out","yn");
 #======================[ Process input from DELETE screen - go for real! ]===
 } else {
   # first obtain some data
   $id    = $db->get_movieid($mtype_id,$cass_id,$part);
   $movie = $db->get_movie($id);
   if ( !is_array($movie) ) die ("<SPAN CLASS='error'>Something strange happened - the entry was not found in db!</SPAN></BODY></HTML>");
   $music_id = $movie["music_id"]; $director_id = $movie["director_id"];
   $actor_id[1] = $movie["actor1_id"]; $actor_id[2] = $movie["actor2_id"];
   $actor_id[3] = $movie["actor3_id"]; $actor_id[4] = $movie["actor4_id"];
   $actor_id[5] = $movie["actor5_id"];
   # now we have to check if any other links to director, composer and/or actors exist
   if ($director_id) { // ignore id# 0
     $name = $db->get_director($director_id);
     $rec  = $db->get_movienamelist("directors",$name,"",TRUE);
     if ( count($rec) < 2 ) {
       $firstname = $name["firstname"]; $name = $name["name"];
       $details = "<li>" . lang("nobody_named",lang("director_person"),$firstname,$name);
       kill("directors",$director_id);
     }
   }
   if ($music_id) { // ignore id# 0
     $name = $db->get_music($music_id);
     $rec  = $db->get_movienamelist("music",$name,"",TRUE);
     if ( count($rec) < 2 ) {
       $firstname = $name["firstname"]; $name = $name["name"];
       $details = "<li>" . lang("nobody_named",lang("compose_person"),$firstname,$name);
       kill("music",$music_id);
     }
   }
   for ($i=1;$i<6;$i++) {
     $aid = $actor_id[$i];
     if ($aid) { // ignore id #0
       $name = $db->get_actor($aid);
       $rec  = $db->get_movienamelist("actors",$name,"",TRUE);
       if ( count($rec) < 2 ) {
         $firstname = $name["firstname"]; $name = $name["name"];
         $details .= "<li>" . lang("nobody_named",lang("actor"),$firstname,$name);
         kill("actors",$aid);
       }
     }
   }
   # now we delete the movie entry from db
   if (!isset($details)) $details = "";
   $details .= "<li>" . lang("check_completed") . " - " . lang("delete_remaining") . ". ";
   kill("video",$id);
   # and finally we may have to correct the free space remaining on that medium (if rewritable)
   if ( $pvp->common->medium_is_rw($mtype_id) || $movie["disktype"] ) {
     $details .= "<li>" . lang("check_media_delete"). ". ";
     if ( $pvp->config->remove_empty_media && $db->delete_medium($cass_id,$mtype_id) ) {
       $details .= "<SPAN CLASS='ok'>" .lang("medium_deleted"). "</SPAN><BR>";
     } else {
       $details .= "<SPAN CLASS='ok'>" .lang("medium_not_deleted"). "</SPAN><BR>";
       $details .= "<li>" . lang("recalc_free"). ". ";
       if ( $db->update_freetime($cass_id,$mtype_id) ) {
         $time_left = $db->get_mediumfreetime($cass_id,$mtype_id);
         if ( strlen($time_left) ) {
           $details .= lang("time_left",$time_left). " <SPAN CLASS='ok'>" .lang("ok") . ".</SPAN><BR>\n";
         } else {
           $details .= "<SPAN CLASS='error'>" .lang("no_entry_in_tapelist"). "!</SPAN><br>\n";
         }
       } else {
         $details .= "<SPAN CLASS='error'>" .lang("tapelist_update_failed"). "!</SPAN><br>\n";
       }
     }
   }
   # and that's all.
   $details .= "<b><i>" . lang("finnished") . ".</i></b>\n</TD></TR></TABLE>\n";
   $t->set_var("details",$details);
   $t->pparse("out","delete");
 }

 include("inc/footer.inc");

?>