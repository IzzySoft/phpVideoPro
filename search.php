<?php
 #############################################################################
 # phpVideoPro                               (c) 200-2003 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Search for movies by specified criteria                                   #
 #############################################################################

 /* $Id$ */

 $page_id = "search_movie";
 include("inc/includes.inc");

 #######################################################[ Display Results ]###
 if ($start||$submit) {
   include("inc/class.nextmatch.inc");
   $t = new Template($pvp->tpl_dir);
   $t->set_file(array("list"=>"medialist.tpl"));
   $t->set_block("list","mdatablock","mdatalist");
   if (!$start) $start = 0;
   $values = array ("mtype_id"=>$mtype_id,"cat_id"=>$cat_id,"ptype"=>$ptype,
                    "pname"=>$pname,"title"=>$title,"comment"=>$comment,
                    "minlen"=>$minlen,"maxlen"=>$maxlen,"minfsk"=>$minfsk,
                    "maxfsk"=>$maxfsk);
   $searchmovievals = $values;
   if ( is_array($mtype_id) ) {
     unset($values["mtype_id"]);
     $values["mtype_id"] = implode(",",$mtype_id);
   } else {
     unset($searchmovievals["mtype_id"]);
     $searchmovievals["mtype_id"] = explode(",",$mtype_id);
   }
   if ( is_array($cat_id) ) {
     unset($values["cat_id"]);
     $values["cat_id"]   = implode(",",$cat_id);
   } else {
     unset($searchmovievals["cat_id"]);
     $searchmovievals["cat_id"]   = explode(",",$cat_id);
   }
   $query  = "\$db->searchmovies(\"$order\",$start)";
   $par = "?order=$order";
   foreach ($values as $key=>$val) {
     $par .= "&$key=$val";
   }
   $nextmatch = new nextmatch($query,$pvp->tpl_dir,$PHP_SELF.$par,$start);
   unset ($title); # messes up the movie list else
   include ("inc/movielist.inc");
   include ("inc/footer.inc");
   exit;
 }

 ###########################################################[ Search Form ]###
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"search.tpl"));
 $t->set_var("listtitle",lang("search_movie"));
 $t->set_var("submit",lang("search"));
 $t->set_var("mtype_name",lang("mediatype"));
 $mtypes = $db->get_mtypes();
 $mtype_field = "<SELECT NAME='mtype_id[]' SIZE='7' MULTIPLE CLASS='multiselect'>";
 for ($i=0;$i<count($mtypes);++$i) {
   $mtype_field .= "<OPTION VALUE='".$mtypes[$i][id]."'>".$mtypes[$i][sname]." (".$mtypes[$i][name].")</OPTION>";
 }
 $mtype_field .= "</SELECT>";
 $t->set_var("mtype_field",$mtype_field);
 $t->set_var("cat_name",lang("category"));
 $cats = $db->get_category(); $ccount = count($cats);
 $cat_field = "<SELECT NAME='cat_id[]' SIZE='7' MULTIPLE CLASS='multiselect'>";
 for ($i=0;$i<$ccount;++$i) {
   $cat_field .= "<OPTION VALUE='".$cats[$i][id]."'>".lang($cats[$i][internal])."</OPTION>";
 }
 $cat_field .= "</SELECT>";
 $t->set_var("cat_field",$cat_field);
 $t->set_var("person_field","<SELECT NAME='ptype'><OPTION NAME='actor'>".lang("actor")."</OPTION><OPTION NAME='director'>".lang("director_person")."</OPTION></SELECT>");
 $t->set_var("name_field","<INPUT NAME='pname' ".$form["addon_name"].">");
 $t->set_var("title_name",lang("title"));
 $t->set_var("title_field","<INPUT NAME='title' ".$form["addon_name"].">");
 $t->set_var("comment_name",lang("comments"));
 $t->set_var("comment_field","<INPUT NAME='comment' ".$form["addon_name"].">");
 $t->set_var("length_name",lang("length"));
 $t->set_var("length_min","<INPUT NAME='minlen' ".$form["addon_fsk"].">");
 $t->set_var("length_max","<INPUT NAME='maxlen' ".$form["addon_fsk"].">");
 $t->set_var("min",lang("minute_abbrev"));
 $t->set_var("fsk_name",lang("fsk"));
 $t->set_var("fsk_min","<INPUT NAME='minfsk' ".$form["addon_fsk"].">");
 $t->set_var("fsk_max","<INPUT NAME='maxfsk' ".$form["addon_fsk"].">");
 include("inc/header.inc");
 $t->pparse("out","template");

 include("inc/footer.inc");
?>