<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Display free (remaining) space on tapes                                   *
 \***************************************************************************/

 /* $Id$ */

  $page_id = "taperest";
  include("inc/header.inc");
  $t = new Template($pvp->tpl_dir);
  if ($usefilter) $filter = $pvp->preferences->filter; else $filter = "";
  if (!$start) $start = 0;
  include("inc/class.nextmatch.inc");

  if (!$minfree) {
    $t->set_file(array("taperest_init"=>"taperest_init.tpl"));
    $t->set_var("form_target",$PHP_SELF);
    $t->set_var("use_filter",$usefilter);
    $t->set_var("min_free",lang("enter_min_free"));
    $t->set_var("display",lang("display"));
    $t->pparse("out","taperest_init");
    include("inc/footer.inc");
    exit;
  }

  // init templates
  $t->set_file(array("taperest_list"=>"taperest_list.tpl",
		     "taperest_empty"=>"taperest_empty.tpl"));
  $t->set_block("taperest_list","itemblock","itemlist");
  $t->set_block("itemblock","movieblock","movielist");

  $query = "\$db->get_freelist($minfree,\"$filter\",$start)";
  $nextmatch = new nextmatch ($query,$pvp->tpl_dir,$PHP_SELF."?minfree=$minfree",$start);

  if (!$nextmatch->listcount) {
    $t->set_var("title",lang("no_entries_found"));
    $t->set_var("msg",lang("no_space_of",$minfree));
    $t->pparse("out","taperest_empty");
    include("inc/footer.inc");
    exit;
  }

  $mlist = $nextmatch->list;
  # $mlist[][id|free]; id = $cass_id

  for ($i=0;$i<$nextmatch->listcount;$i++) {
    $movie_id = $db->get_movieid(1,$mlist[$i][id]);
    $mid_count = count($movie_id);
    for ($k=0;$k<$mid_count;$k++) {
      $movie = $db->get_movie($movie_id[$k]);
      $mlist[$i][$k]    = $movie[title] . " (" . $movie[cat1] . ")";
      $mlist[$i][mtype] = $movie[mtype_short];
      debug("V","<TR><TD colspan=4>Title: '". $mlist[$i][$k] . "', Type: '" . $mlist[$i]["mtype"] . "'</TD></TR>\n");
      $t->set_var("movies",$mlist[$i][$k]);
      if (!$k) {
        $t->parse("movielist","movieblock");
      } else {
        $t->parse("movielist","movieblock",TRUE);
      }
    }
    $t->set_var("mtype",$mlist[$i]["mtype"]);
    $t->set_var("id",$mlist[$i]["id"]);
    $t->set_var("free",$mlist[$i][free]);
    $t->parse("itemlist","itemblock",TRUE);
  }
  $t->set_var("freespace",lang("free_space_on_media",$minfree));
  $t->set_var("medium",lang("medium"));
  $t->set_var("nr",lang("nr"));
  $t->set_var("free",lang("free"));
  $t->set_var("content",lang("content"));
  $t->set_var("first",$nextmatch->first);
  $t->set_var("left",$nextmatch->left);
  $t->set_var("right",$nextmatch->right);
  $t->set_var("last",$nextmatch->last);
  $t->pparse("out","taperest_list");

  include("inc/footer.inc");

?>