<?
 ##############################################################################
 # phpVideoPro                               (c) 2001,2002 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                           #
 # http://www.qumran.org/homes/izzy/                                          #
 # -------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it       #
 # under the terms of the GNU General Public License (see doc/LICENSE)        #
 # -------------------------------------------------------------------------- #
 # Change number and/or type of medium (tape/dvd/vcd)                         #
 ##############################################################################

 /* $Id$ */

 function make_nr($cass,$part) {
   while ( strlen($cass)<4 ) { $cass = "0".$cass; }
   if ( strlen($part)<2 ) { $part = "0".$part; }
   return $cass . "-" . $part;
 }

 $page_id = "media_change";

 include("inc/includes.inc");
 if ( ($copy && !$pvp->auth->add) || ($change && !$pvp->auth->update) ) {
   kickoff(); // kick-off unauthorized visitors
 }
 if ( $copy || $change ) {
   if ( !$valid->medianr($new_mtype,$new_cass_id,$new_part) ) {
     $error = lang("invalid_media_nr") . "</P>\n";
     display_error($error);
     exit;
   }
  
 $movie_id = $db->get_movieid($old_mtype,$old_cass_id,$old_part);
  
 $movie = $db->get_movie($movie_id);
 } else {
   include("inc/header.inc");
 }

 if ( $change ) {
   $db->move_movie($movie_id,$new_mtype,$new_cass_id,$new_part);
   $new_nr = make_nr($new_cass_id,$new_part);
   header("location: edit.php?mtype_id=$new_mtype&cass_id=$new_cass_id&part=$new_part&nr=$new_nr");
 } elseif ( $copy ) {
   $movie[space]    = $db->get_mediaspace($movie[cass_id],$movie[mtype_id]);
   $movie[mtype_id] = $new_mtype;
   $movie[cass_id]  = $new_cass_id;
   $movie[part]     = $new_part;
   if ( !$movie[lp] ) $movie[lp] = 0;
   $db->add_movie($movie);
   $new_nr = make_nr($new_cass_id,$new_part);
   header("location: edit.php?mtype_id=$new_mtype&cass_id=$new_cass_id&part=$new_part&nr=$new_nr");
   exit;
 }


 $movie = $db->get_movie($id);

 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"change_nr.tpl"));
 $t->set_var("listtitle",lang("change_nr",$movie[mtype_short]. " " .$movie[cass_id]. "-" .$movie[part]));
 $t->set_var("form_target",$PHP_SELF);
 $t->set_var("latest",lang("highest_db_entries"));
 $t->set_var("latest_box",$pvp->common->make_lastnum_selectbox("lastnum"));
 $t->set_var("orig",lang("orig_medianr"));
 $t->set_var("o_mtype",$pvp->common->make_mtype_selectbox("old_mtype",$movie[mtype_id]));
 $t->set_var("o_medianr","<INPUT NAME='old_cass_id' ".$form["addon_cass_id"]."  VALUE='".$movie[cass_id]."'>");
 $t->set_var("o_part","<INPUT NAME='old_part' ".$form["addon_part"]." VALUE='".$movie[part]."'>");
 $t->set_var("new",lang("new_medianr"));
 $t->set_var("n_mtype",$pvp->common->make_mtype_selectbox("new_mtype",$movie[mtype_id]));
 $t->set_var("n_medianr","<INPUT NAME='new_cass_id' ".$form["addon_cass_id"]."  VALUE='".$movie[cass_id]."'>");
 $t->set_var("n_part","<INPUT NAME='new_part' ".$form["addon_part"]." VALUE='".$movie[part]."'>");
 $t->set_var("cancel","<INPUT TYPE='cancel' NAME='cancel' VALUE='".lang("cancel")."'>");
 $t->set_var("copy","<INPUT TYPE='submit' NAME='copy' VALUE='".lang("media_copy")."'>");
 $t->set_var("change","<INPUT TYPE='submit' NAME='change' VALUE='".lang("media_change")."'>");

 $t->pparse("out","template");

 include("inc/footer.inc");

?>