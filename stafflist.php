<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # stafflist - call with ?stafftype=<director|actor|music>                   #
 #############################################################################

 /* $Id$ */

 #========================================================[ initial setup ]===
 $stafftype = $_GET["stafftype"];
 $start     = $_GET["start"];
 $page_id = $stafftype;
 include("inc/includes.inc");
 if (!$pvp->auth->browse) kickoff();
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("list"=>"stafflist.tpl"));
 $t->set_block("list","itemblock","itemlist");
 $t->set_block("list","notfoundblock","notfoundlist");
 $filter = get_filters();
 if (!$start) $start = 0;
 include("inc/class.nextmatch.inc");

 #===========================================[ retrieve all staff members ]===
 $query = "\$db->get_visstafflist(\"$stafftype\",\"$filter\",$start)";
 $nextmatch = new nextmatch ($query,$pvp->tpl_dir,$_SERVER["PHP_SELF"]."?stafftype=$stafftype",$start);
 $staff = $nextmatch->list;

 #==============================================[ now get & draw the list ]===
 $row = 0;
 for ($i=0;$i<$nextmatch->listcount;$i++) {
   $movies = $db->get_movienamelist($stafftype,$staff[$i]['name'],$filter);
   $moviecount = count($movies);
   $same_name = FALSE;
   for ($k=0;$k<$moviecount;++$k) {
    $row++;
    $mtype    = $movies[$k]['mtype_short'];
    $mtype_id = $movies[$k]['mtype_id'];
    $cass_id  = $movies[$k]['cass_id'];
    $nr       = $cass_id;
    $part     = $movies[$k]['part'];
    while (strlen($nr)<4) { $nr = "0" . $nr; }
    $nr      .= "-";
    if (strlen($part)<2) {
      $nr .= "0" . $part;
    } else { $nr .= $part; }
    $movie_id = urlencode($mtype . " " . $nr);
    $title    = $movies[$k]['title']; check_empty($title);
    $length   = $movies[$k]['length']; check_empty($length);
    $year     = $movies[$k]['year']; check_empty($year);
    $aq_date  = $movies[$k]['aq_date'];  check_empty($aq_date);
    $category = $movies[$k]['cat1']; check_empty($category);
    debug("D","Got '$nr' ($title), RowCount now: '$row'.<br>");

    if ($same_name) {
      $t->set_var("name","&nbsp;");
      $t->set_var("namesep","&nbsp;");
      $t->set_var("firstname","&nbsp;");
    } else {
      $t->set_var("name",$staff[$i]['name']['name']);
      $t->set_var("namesep",", ");
      $t->set_var("firstname",$staff[$i]['name']['firstname']);
    }
    $t->set_var("title",$title);
    $t->set_var("category",$category);
    $t->set_var("length",$length);
    $t->set_var("url",$pvp->link->slink("edit.php?nr=$movie_id&cass_id=$cass_id&part=$part&mtype_id=$mtype_id"));
    $t->set_var("mtype",$mtype);
    $t->set_var("nr",$nr);
    if ($row>1) $t->parse("itemlist","itemblock",TRUE);
      else  $t->parse("itemlist","itemblock");
    $same_name = TRUE;
   }
 }
 debug("D","RowCount: '$row'<br>");
 if ($row) {
   $t->set_var("not_found","");
   $t->parse("notfoundlist","notfoundblock");
 } else {
   $t->set_var("not_found","<DIV ALIGN=CENTER>" . lang("no_entries_found") . "</DIV>");
   $t->parse("notfoundlist","notfoundblock");
   $t->set_var("itemlist","");
 }

 #====================================================[ draw table header ]===
 include("inc/header.inc");
 $t->set_var("listtitle",lang($page_id));
 $t->set_var("stafftype",lang($stafftype));
 $t->set_var("title",lang("title"));
 $t->set_var("category",lang("category"));
 $t->set_var("length",lang("length"));
 $t->set_var("medianr",lang("medianr"));
 $t->set_var("first",$nextmatch->first);
 $t->set_var("left",$nextmatch->left);
 $t->set_var("right",$nextmatch->right);
 $t->set_var("last",$nextmatch->last);
 $t->pparse("out","list");

 include("inc/footer.inc");
?>