<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Display MediaList                                                         #
 #############################################################################

 /* $Id$ */

 #========================================================[ initial setup ]==
 $page_id = "medialist";
 include("inc/includes.inc");
 if (!$pvp->auth->browse) kickoff();
 $filter = get_filters();
 if (isset($_GET["start"])) $start = $_GET["start"];
 if (isset($_GET["order"])) $order = $_GET["order"];
 if (!isset($start)) $start = 0;
 if (!isset($order)) $order = "";
 include("inc/class.nextmatch.inc");

 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("list"=>"medialist.tpl"));
 $t->set_block("list","mdatablock","mdatalist");
 $t->set_block("list","emptyblock","emptylist");

 #=======================================[ get movies and setup variables ]===
 $query = "\$db->get_movielist(\"$order\",\"\",$start)";
 $nextmatch = new nextmatch ($query,$pvp->tpl_dir,$_SERVER["PHP_SELF"]."?order=$order",$start);

 include("inc/movielist.inc");
 include("inc/footer.inc");
?>