<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
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
 vul_num("start");
 if (!in_array($_GET["orderdir"],array("DESC","ASC",""))) vul_kick("orderdir");
 if (!$pvp->auth->browse) kickoff();
 $filter = get_filters();
 if (isset($_GET["start"])) $start = $_GET["start"];
 if (isset($_GET["order"])) $order = $_GET["order"];
 if (isset($_GET["orderdir"])) $orderdir = $_GET["orderdir"];
 if (empty($orderdir)) $orderdir="DESC";
 if (!isset($start)) $start = 0;
 if (!isset($order)) $order = "";
 include("inc/class.nextmatch.inc");

 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("list"=>"medialist.tpl"));
 $t->set_block("list","mdatablock","mdatalist");
 $t->set_block("list","emptyblock","emptylist");

 #=======================================[ get movies and setup variables ]===
 $query = "\$db->get_movielist(\"$order\",\"\",$start,\"$orderdir\")";
 $nextmatch = new nextmatch ($query,$pvp->tpl_dir,$_SERVER["PHP_SELF"]."?order=$order",$start);

 include("inc/movielist.inc");
 include("inc/footer.inc");
?>