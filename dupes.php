<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2005 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Find (possible) dupes by movie title                                      #
 #############################################################################

 /* $Id$ */

# $page_id = "dupes";
 include("inc/includes.inc");
 #==================================================[ Check authorization ]===
 if (!$pvp->auth->browse) kickoff();

 #==================================================[ Initialize Template ]===
 include("inc/header.inc");
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"dupes.tpl"));
 $t->set_block("template","itemblock","item");

 #====================================================[ Generate the List ]===
 $mtypelist = $db->get_mtypes();
 for ($i=0;$i<count($mtypelist);++$i) {
   $id = $mtypelist[$i]['id'];
   $mtypes[$id]['sname'] = $mtypelist[$i]['sname'];
 }
 if ($_REQUEST["strict"]==1) $strict = 1; else $strict = 0;
 $dupes  = $db->get_dupetitles($strict);
 $dupecount = count($dupes);

 for ($i=0;$i<$dupecount;++$i) {
   $copies = count($dupes[$i]) -1;
   for ($k=0;$k<$copies;++$k) {
     $mtype_id = $dupes[$i][$k]->mtype_id;
     $mtype    = $mtypes[$mtype_id]['sname'];
     $cass_id  = $dupes[$i][$k]->cass_nr;
     $part     = $dupes[$i][$k]->part;
     while ( strlen($cass_id)<4 ) { $cass_id = "0" . $cass_id; }
     while ( strlen($part)<2)     { $part    = "0" . $part;    }
     $nr = $cass_id . "-" . $part;
     if ($k) { $details .= ", "; } else { $details = ""; }
     $details .= "<A HREF='edit.php?mtype_id=$mtype_id&cass_id=$cass_id&part=$part&nr=$nr'>";
     $details .= "$mtype $cass_id" .  "-" . $part . "</A> ("
              . $dupes[$i][$k]->len . " min)";
   }
   $t->set_var("title",$dupes[$i]['title']);
   $t->set_var("details",$details);
   if ($i) $t->parse("item","itemblock",TRUE);
     else $t->parse("item","itemblock");
 }

 $t->set_var("listtitle",lang("dupe_titles_found",$dupecount));
 $t->pparse("out","template");

 include("inc/footer.inc");
?>