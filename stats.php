<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Display Database Statistics                                               *
 \***************************************************************************/

 /* $Id$ */

  $page_id = "stats";
  include("inc/header.inc");
  $t = new Template($pvp->tpl_dir);

  $stats = $db->get_stats();

  $t->set_file(array("stat"=>"stats.tpl"));
  $t->set_block("stat","listblock","list");
  $t->set_block("listblock","itemblock","item");

  $t->set_var("listtitle",lang("db_stats"));
  $t->set_var("list_head",lang("stat_counts"));
  $t->set_var("item_name",lang("movies"));
  $t->set_var("item_input",$stats[movies]);
  $t->parse("item","itemblock");
  $t->set_var("item_name",lang("director_persons"));
  $t->set_var("item_input",$stats[directors]);
  $t->parse("item","itemblock",TRUE);
  $t->set_var("item_name",lang("actor_persons"));
  $t->set_var("item_input",$stats[actors]);
  $t->parse("item","itemblock",TRUE);
  $t->set_var("item_name",lang("compose_persons"));
  $t->set_var("item_input",$stats[composers]);
  $t->parse("item","itemblock",TRUE);
  $t->set_var("item_name",lang("stat_categories"));
  $t->set_var("item_input",$stats[cats_used] . "/" . $stats[categories]);
  $t->parse("item","itemblock",TRUE);
  $t->set_var("item_name",lang("media"));
  $t->set_var("item_input",$stats[media]);
  $t->parse("item","itemblock",TRUE);
  $t->set_var("item_name",lang("countries"));
  $t->set_var("item_input",$stats[countries]);
  $t->parse("item","itemblock",TRUE);
  $t->parse("list","listblock");

  $t->set_var("list_head",lang("stat_ranks"));
  $t->set_var("item_name",lang("countries"));
  $rank = "$stats[rank_country_1]<BR>$stats[rank_country_2]<BR>$stats[rank_country_3]";
  $t->set_var("item_input","$rank");
  $t->parse("item","itemblock");
  $t->set_var("item_name",lang("director_persons"));
  $rank = "$stats[rank_director_1]<BR>$stats[rank_director_2]<BR>$stats[rank_director_3]";
  $t->set_var("item_input","$rank");
  $t->parse("item","itemblock",TRUE);
  $t->set_var("item_name",lang("compose_persons"));
  $rank = "$stats[rank_composer_1]<BR>$stats[rank_composer_2]<BR>$stats[rank_composer_3]";
  $t->set_var("item_input","$rank");
  $t->parse("item","itemblock",TRUE);
  $t->set_var("item_name",lang("categories"));
  $rank = "$stats[rank_category_1]<BR>$stats[rank_category_2]<BR>$stats[rank_category_3]";
  $t->set_var("item_input","$rank");
  $t->parse("item","itemblock",TRUE);
  $t->parse("list","listblock",TRUE);

  $t->pparse("out","stat");

  include("inc/footer.inc");

?>