<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Delete an entry from DB                                                   *
 \***************************************************************************/

 /* $Id$ */

  if ($cancel) {
    include("inc/config.inc");
    header("Location: $base_url/edit.php?nr=" . urlencode("$nr") . "&cass_id=$cass_id&part=$part&mtype_id=$mtype_id");
    exit;
  }
  $page_id = "delete";
  include("inc/header.inc");
  $t = new Template($pvp->tpl_dir);
  $t->set_file(array("delete"=>"delete.tpl",
                     "yn"=>"delete_yn.tpl"));
  
  function kill($table,$id) {
    GLOBAL $colors, $details, $db;
    $details .= " ";
    if ( $db->delete_row($table,$id) ) {
      $details .= $colors["ok"] . lang("ok") . ".</Font><br>\n";
    } else {
      $details .= $colors["err"] . lang("not_ok") . "!</Font><br>\n";
    }
  }

  $t->set_var("listtitle",lang("deleting_entry",$nr));

  if (!$approved) { // sure to delete?
    $t->set_var("formtarget",basename(__FILE__));
    $t->set_var("nr",$nr);
    $t->set_var("cass_id",$cass_id);
    $t->set_var("part",$part);
    $t->set_var("mtype_id",$mtype_id);
    $t->set_var("delete_yn",$colors["err"] . lang("sure_to_delete",$nr) . "?");
    $t->set_var("no",strtoupper(lang("no")) . "!");
    $t->set_var("yes",lang("yes") . ".");
    $t->pparse("out","yn");
  } else { // here comes the real delete!
    # first obtain some data
    $id    = $db->get_movieid($mtype_id,$cass_id,$part);
    $movie = $db->get_movie($id);
    if ( !is_array($movie) ) die ($colors["err"] . "Something strange happened - the entry was not found in db!</Font></BODY></HTML>");
    $music_id = $movie[music_id]; $director_id = $movie[director_id];
    $actor_id[1] = $movie[actor1_id]; $actor_id[2] = $movie[actor2_id];
    $actor_id[3] = $movie[actor3_id]; $actor_id[4] = $movie[actor4_id];
    $actor_id[5] = $movie[actor5_id];
    # now we have to check if any other links to director, composer and/or actors exist
    if ($director_id) { // ignore id# 0
      $name = $db->get_director($director_id);
      $rec  = $db->get_movienamelist("directors",$name);
      if ( count($rec) < 2 ) {
        $firstname = $name[firstname]; $name = $name[name];
        $details = "<li>" . lang("nobody_named",lang("director_person"),$firstname,$name);
        kill("directors",$music_id);
      }
    }
    if ($music_id) { // ignore id# 0
      $name = $db->get_music($music_id);
      $rec  = $db->get_movienamelist("music",$name);
      if ( count($rec) < 2 ) {
        $firstname = $name[firstname]; $name = $name[name];
        $details = "<li>" . lang("nobody_named",lang("compose_person"),$firstname,$name);
        kill("music",$music_id);
      }
    }
    for ($i=1;$i<6;$i++) {
      $aid = $actor_id[$i];
      if ($aid) { // ignore id #0
        $name = $db->get_actor($aid);
        $rec  = $db->get_movienamelist("actors",$name);
        if ( count($rec) < 2 ) {
          $firstname = $name[firstname]; $name = $name[name];
          $details .= "<li>" . lang("nobody_named",lang("actor"),$firstname,$name);
          kill("actors",$aid);
        }
      }
    }
    # now we delete the movie entry from db
    $details .= "<li>" . lang("check_completed") . " - " . lang("delete_remaining") . ". ";
    kill("video",$id);
    # and finally we may have to correct the free space remaining on that medium (if rewritable)
    if ( $pvp->common->medium_is_rw($mtype_id) ) {
      $details .= "<li>" . lang("recalc_free"). ". ";
      if ( $db->update_freetime($cass_id,$mtype_id) ) {
	$time_left = $db->get_mediumfreetime($cass_id);
	if ( strlen($time_left) ) {
          $details .= lang("time_left",$time_left) . " " . $colors["ok"] . lang("ok") . ".</Font><BR>\n";
	} else {
	  $details .= $colors["err"] . lang("no_entry_in_tapelist") . "!</Font><br>\n";
	}
      } else {
        $details .= $colors["err"] . lang("tapelist_update_failed") . "!</Font><br>\n";
      }
    }
    # and that's all.
    $details .= "<b><i>" . lang("finnished") . ".</i></b>\n</TD></TR></TABLE>\n";
    $t->set_var("details",$details);
    $t->pparse("out","delete");
  }

  include("inc/footer.inc");

?>