<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Display MediaList                                                         *
 \***************************************************************************/

 /* $Id$ */

  $page_id = "medialist";
  include("inc/header.inc");
  $t = new Template($pvp->tpl_dir);
  $filter = get_filters();

  switch($order) {
    case "title"  : $orderby = " ORDER BY v.title,v.mtype_id DESC,v.cass_id"; break;
    case "length" : $orderby = " ORDER BY v.length,v.mtype_id DESC,v.cass_id"; break;
    case "year"   : $orderby = " ORDER BY v.year,v.mtype_id DESC,v.cass_id"; break;
    case "date"   : $orderby = " ORDER BY v.aq_date,v.mtype_id DESC,v.cass_id"; break;
    case "cat"    : $orderby = " ORDER BY c.name,v.mtype_id DESC,v.cass_id"; break;
    default       : $orderby = " ORDER BY v.mtype_id DESC,v.cass_id,v.part";
  }

  $t->set_file(array("list"=>"medialist.tpl"));
  $t->set_block("list","mdatablock","mdatalist");

  $query  = "SELECT v.cass_id,v.part,v.title,v.length,v.year,v.aq_date,c.name,m.sname,v.mtype_id";
  $query .= " FROM video v, cat c, mtypes m";
  $query .= " WHERE v.cat1_id=c.id AND v.mtype_id=m.id";
  if ( strlen($filter) ) $query .= " AND ($filter)";
  $query .= $orderby;
  dbquery($query);
  $row=0;
  while ($db->next_record()) {
   $mtype[$row]    = $db->f('sname');
   $mtype_id[$row] = $db->f('mtype_id');
   $cass_id[$row]  = $db->f('cass_id');
   $nr[$row]       = $cass_id[$row];
   $part[$row]     = $db->f('part');
   while (strlen($nr[$row])<4) { $nr[$row] = "0" . $nr[$row]; }
   $nr[$row]      .= "-";
   if (strlen($part[$row])<2) {
     $nr[$row] .= "0" . $part[$row];
   } else { $nr[$row] .= $part[$row]; }
   $movie_id[$row] = urlencode($mtype[$row] . " " . $nr[$row]);
   $title[$row]    = $db->f('title'); check_empty($title[$row]);
   $length[$row]   = $db->f('length'); check_empty($length[$row]);
   $year[$row]     = $db->f('year'); check_empty($year[$row]);
   $aq_date[$row]  = $db->f('aq_date');  check_empty($aq_date[$row]);
   $category[$row] = $db->f('name'); check_empty($category[$row]);
   $row++;
  }
  for ($i=0;$i<count($mtype);$i++) {
   $t->set_var("listtitle",lang("medialist"));
   $t->set_var("mtype",$mtype[$i]);
   $t->set_var("nr",$nr[$i]);
   $t->set_var("title",$title[$i]);
   $t->set_var("length",$length[$i]);
   $t->set_var("year",$year[$i]);
   $t->set_var("date",$aq_date[$i]);
   $t->set_var("category",$category[$i]);
   $t->set_var("url","edit.php?nr=$movie_id[$i]&cass_id=$cass_id[$i]&part=$part[$i]&mtype_id=$mtype_id[$i]");
   $t->parse("mdatalist","mdatablock",TRUE);
  }
  $t->set_var("mtype",lang("medium"));
  $t->set_var("nr",lang("nr"));
  $t->set_var("title",lang("title"));
  $t->set_var("length",lang("length"));
  $t->set_var("year",lang("year"));
  $t->set_var("date",lang("date_rec"));
  $t->set_var("category",lang("category"));
  $t->set_var("scriptname",$PHP_SELF);
  $t->pparse("out","list");

  include("inc/footer.inc");

?>