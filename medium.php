<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Display data for a given medium                                           #
 #############################################################################

 /* $Id$ */

# $page_id = "admin_cats";
 include("inc/includes.inc");
 $mtype_id = $_REQUEST["mtype_id"];
 $cass_id  = $_REQUEST["cass_id"];
 $mtype  = $db->get_mtypes("id=$mtype_id");
 $medium = $mtype[0]["sname"] ." ". $cass_id;
 $mid    = $db->get_movieid($mtype_id,$cass_id);

 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"medium.tpl"));
 $t->set_block("template","techblock","tech");
 $t->set_block("template","movieblock","movie");
 $t->set_var("listtitle",lang("medium_overview",$medium));
 $t->set_var("techdata",lang("techdata"));
 $t->set_var("moviedata",lang("movies"));
 $t->set_var("form_target",$_SERVER["PHP_SELF"]);

 function techbutton ($name,$value,$onclick="") {
   GLOBAL $pvp;
   $field  = "<INPUT TYPE='button' NAME='name' VALUE='$value' CLASS='yesnobutton'";
   if ($onclick) $field .= " onClick=\"window.location.href='"
     . $pvp->link->slink($onclick) . "'\";
   $field .= >";
   return $field;
 }

 #=============================================[ obtain media information ]===
 $type = $db->get_mediaspace($cass_id,$mtype_id,"type");
 $free = $db->get_mediaspace($cass_id,$mtype_id,"free");
 if ($pvp->common->medium_is_rw($mtype_id)) { $rw = lang("yes"); }
   else { $rw = lang("no"); }
 $t->set_var("tname",lang("medialength").":&nbsp;");
 $t->set_var("tunit",lang("minute_abbrev"));
 $t->set_var("tdata",techbutton("type",$type,"medialength.php?cass_id=$cass_id&mtype_id=$mtype_id"));
 $t->parse("tech","techblock");
 $t->set_var("tname",lang("free").":&nbsp;");
 $t->set_var("tdata",techbutton("free",$free));
 $t->parse("tech","techblock",TRUE);
 $t->set_var("tname",lang("is_rw").":&nbsp;");
 $t->set_var("tunit","&nbsp;");
 $t->set_var("tdata",techbutton("rw",$rw));
 $t->parse("tech","techblock",TRUE);

 #=============================================[ obtain movie information ]===
 $mcount = count($mid);
 for ($i=0;$i<$mcount;++$i) {
   $movie = $db->get_movie($mid[$i]);
   $url   = $base_url ."index.php?sel_entry=1&mtype_id=$mtype_id&cass_id=$cass_id&part=".$movie['part'];
   $mlink = $pvp->link->linkurl($url,$movie['part']."&nbsp;");
   $mdata = $movie['title']." (".$movie['cat1']. ", ".$movie['length']." ".lang("minute_abbrev").")";
   $t->set_var("mlink",$mlink);
   $t->set_var("mdata",$mdata);
   if ($i) $t->parse("movie","movieblock",TRUE);
     else $t->parse("movie","movieblock");
 }

 include("inc/header.inc");
 $t->pparse("out","template");

 include("inc/footer.inc");
?>