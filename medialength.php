<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Change media length                                                       *
 \***************************************************************************/

 /* $Id$ */

#  $page_id = "stats";
  include("inc/header.inc");

  if ($update) {
    if ( $db->set_mediaspace($cass_id,$mtype_id,$mlength) ) {
      $save_result = $colors["ok"] . lang("update_success") . ".</Font><BR>\n";
    } else {
      $save_result = $colors["err"] . lang("update_failed") . "!</Font><BR>\n";
    }
  }

  $t = new Template($pvp->tpl_dir);
  $t->set_file(array("template"=>"medialength.tpl"));

  $medium  = $db->get_mtypes("id=$mtype_id");
  $medianr = $cass_id;
  while ( strlen($medianr)<4 ) { $medianr = "0".$medianr; }
  $medianr = $medium[0][sname] . " $medianr";
  $mlength = $db->get_mediaspace($cass_id,$mtype_id);

  $hidden = "<INPUT TYPE='hidden' NAME='mtype_id' VALUE='$mtype_id'>"
          . "<INPUT TYPE='hidden' NAME='cass_id' VALUE='$cass_id'>";

  $t->set_var("listtitle",lang("change_media_length"));
  $t->set_var("save_result",$save_result);
  $t->set_var("hidden_fields",$hidden);
  $t->set_var("info",lang("change_media_length_for",$medianr));
  $input = "<INPUT NAME='mlength' VALUE='$mlength' ".$form["addon_filmlen"].">";
  $t->set_var("input",$input);
  $input = "<INPUT TYPE='submit' NAME='update' VALUE='".lang("update")."'>";
  $t->set_var("submit",$input);

  $t->pparse("out","template");

  include("inc/footer.inc");

?>