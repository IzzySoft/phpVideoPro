<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2005 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Display Database Statistics                                               #
 #############################################################################

 /* $Id$ */

 $page_id = "stats";
 include("inc/includes.inc");

 #==================================================[ Check authorization ]===
 if ( !$pvp->auth->browse ) {
   kickoff(); // kick-off unauthorized visitors
 }

 include("inc/header.inc");
 $t = new Template($pvp->tpl_dir);

 $stats = $db->get_stats();

 $t->set_file(array("stat"=>"stats.tpl"));
 $t->set_block("stat","listblock","list");
 $t->set_block("listblock","itemblock","item");

 $indent = "&nbsp;&nbsp;";

 #-=[ Sums ]=-
 $t->set_var("listtitle",lang("db_stats"));
 $t->set_var("list_head",lang("stat_counts"));
 $t->set_var("item_name","<b>" . lang("movies") . "</b>");
 $t->set_var("item_input",$stats['movies']);
 $t->parse("item","itemblock");
 $t->set_var("item_name","<b>" . lang("director_persons") . "</b>");
 $t->set_var("item_input",$stats['directors']);
 $t->parse("item","itemblock",TRUE);
 $t->set_var("item_name","<b>" . lang("actor_persons") . "</b>");
 $t->set_var("item_input",$stats['actors']);
 $t->parse("item","itemblock",TRUE);
 $t->set_var("item_name","<b>" . lang("compose_persons") . "</b>");
 $t->set_var("item_input",$stats['composers']);
 $t->parse("item","itemblock",TRUE);
 $t->set_var("item_name","<b>" . lang("stat_categories") . "</b>");
 $t->set_var("item_input",$stats['cats_used'] . "/" . $stats['categories']);
 $t->parse("item","itemblock",TRUE);
 $t->set_var("item_name","<b>" . lang("media") . "</b>");
 $t->set_var("item_input",$stats['media']);
 $t->parse("item","itemblock",TRUE);
 $mc = count($stats['smedia']);
 for ($i=0;$i<$mc;++$i) {
   $t->set_var("item_name",$indent.$stats['smedia'][$i]['name']." (".$stats['smedia'][$i]['sname'].")");
   $t->set_var("item_input",$stats['smedia'][$i]['mcount']);
   $t->parse("item","itemblock",TRUE);
 }
 $t->set_var("item_name","<b>" . lang("countries") . "</b>");
 $t->set_var("item_input",$stats['countries']);
 $t->parse("item","itemblock",TRUE);
 $t->parse("list","listblock");

 #-=[ Rankings ]=-
 $t->set_var("list_head",lang("stat_ranks"));
 $t->set_var("item_name","<b>" . lang("countries") . "</b>");
 $t->set_var("item_input","");
 $t->parse("item","itemblock");
 for ($i=1;$i<4;++$i) {
   $rank = "rank_country_" . $i;
   $count = $rank . "_count";
   $t->set_var("item_name","$indent $stats[$rank]");
   $t->set_var("item_input",$stats[$count]);
   $t->parse("item","itemblock",TRUE);
 }
 $t->set_var("item_name","<b>" . lang("director_persons") . "</b>");
 $t->set_var("item_input","");
 $t->parse("item","itemblock",TRUE);
 for ($i=1;$i<4;++$i) {
   $rank = "rank_director_" . $i;
   $count = $rank . "_count";
   $t->set_var("item_name","$indent $stats[$rank]");
   $t->set_var("item_input",$stats[$count]);
   $t->parse("item","itemblock",TRUE);
 }
 $t->set_var("item_name","<b>" . lang("compose_persons") . "</b>");
 $t->set_var("item_input","");
 $t->parse("item","itemblock",TRUE);
 for ($i=1;$i<4;++$i) {
   $rank = "rank_composer_" . $i;
   $count = $rank . "_count";
   $t->set_var("item_name","$indent $stats[$rank]");
   $t->set_var("item_input",$stats[$count]);
   $t->parse("item","itemblock",TRUE);
 }
 $t->set_var("item_name","<b>" . lang("actor_persons") . "</b>");
 $t->set_var("item_input","");
 $t->parse("item","itemblock",TRUE);
 for ($i=1;$i<4;++$i) {
   $rank = "rank_actor_" . $i;
   $count = $rank . "_count";
   $t->set_var("item_name","$indent $stats[$rank]");
   $t->set_var("item_input",$stats[$count]);
   $t->parse("item","itemblock",TRUE);
 }
 $t->set_var("item_name","<b>" . lang("categories") . "</b>");
 $t->set_var("item_input","");
 $t->parse("item","itemblock",TRUE);
 for ($i=1;$i<4;++$i) {
   $rank = "rank_category_" . $i;
   $count = $rank . "_count";
   $t->set_var("item_name","$indent $stats[$rank]");
   $t->set_var("item_input",$stats[$count]);
   $t->parse("item","itemblock",TRUE);
 }
 $t->parse("list","listblock",TRUE);

 $t->pparse("out","stat");

 include("inc/footer.inc");
?>