<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
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

 #==================================================[ Check authorization ]===
 if ( !$pvp->auth->browse ) {
   kickoff(); // kick-off unauthorized visitors
 }

 #==================================[ check vulnerabilities / wrong input ]===
 $vuls = array();
 if (!$pvp->common->req_is_num("minlen") || !$pvp->common->req_is_num("maxlen"))
   $vuls[] = lang("len_is_nan");
 if (!$pvp->common->req_is_num("minfsk") || !$pvp->common->req_is_num("maxfsk"))
   $vuls[] = lang("fsk_is_nan");
 if (!$pvp->common->req_is_alnum("pname",1)) $vuls[] = lang("name_not_string");
 if (!$pvp->common->req_is_alnum("title",1)) $vuls[] = lang("title_not_string");
 if (!$pvp->common->req_is_alnum("comment",1)) $vuls[] = lang("comment_not_string");
 if ($vc=count($vuls)) {
   $msg = lang("input_errors_occured",$vc) . "<UL>\n";
   for ($i=0;$i<$vc;++$i) {
     $msg .= "<LI>".$vuls[$i]."</LI>\n";
   }
   $msg .= "</UL>";
   $pvp->common->die_error($msg);
 }

 #=================================================[ Register global vars ]===
 $postit = array ("submit","mtype_id","cat_id","audio_id","subtitle_id","ptype",
                  "pname","title","comment","minlen","maxlen","minfsk","maxfsk",
                  "minrat","maxrat","minchange","maxchange","start","order");
 foreach ($postit as $var) {
   if (isset($_REQUEST[$var])) $$var = $_REQUEST[$var]; else $$var = "";
 }
 unset($postit);

 #=============================================[ Setup special JavaScript ]===
 $fsk_nan = lang("fsk_is_nan");
 $len_nan = lang("len_is_nan");
 $rat_nan = lang("rating_is_nan");
 $js = "<script language='JavaScript' src='images/ts_picker.js'></script>
 <SCRIPT TYPE='text/javascript' LANGUAGE='JavaScript'>//<!--
   function check_rating() {
     dsf = document.searchform;
     if (isNaN(dsf.minrat.value) || dsf.minrat.value>10 || dsf.minrat.value <0) {
       dsf.minrat.value = '';
       alert('$rat_nan');
     }
     if (isNaN(dsf.maxrat.value || dsf.maxrat.value>10 || dsf.maxrat.value <0)) {
       dsf.maxrat.value = '';
       alert('$rat_nan');
     }
   }
   function check_fsk() {
     dsf = document.searchform;
     if (isNaN(dsf.minfsk.value)) {
       dsf.minfsk.value = '';
       alert('$fsk_nan');
     }
     if (isNaN(dsf.maxfsk.value)) {
       dsf.maxfsk.value = '';
       alert('$fsk_nan');
     }
   }
   function check_len() {
     dsf = document.searchform;
     if (isNaN(dsf.minlen.value)) {
       dsf.minlen.value = '';
       alert('$len_nan');
     }
     if (isNaN(dsf.maxlen.value)) {
       dsf.maxlen.value = '';
       alert('$len_nan');
     }
   }
//--></SCRIPT>";

 #======================================================[ Display Results ]===
 if ($start||$submit||$order) {
   include("inc/class.nextmatch.inc");
   $t = new Template($pvp->tpl_dir);
   $t->set_file(array("list"=>"medialist.tpl"));
   $t->set_block("list","mdatablock","mdatalist");
   $t->set_block("list","emptyblock","emptylist");
   if (!$start) $start = 0;
   $values = array ("mtype_id"=>$mtype_id,"cat_id"=>$cat_id,"audio_id"=>$audio_id,
                    "subtitle_id"=>$subtitle_id,"ptype"=>$ptype,
                    "pname"=>$pname,"title"=>$title,"comment"=>$comment,
                    "minlen"=>$minlen,"maxlen"=>$maxlen,"minfsk"=>$minfsk,
                    "maxfsk"=>$maxfsk,"minrat"=>$minrat,"maxrat"=>$maxrat,
                    "minchange"=>$minchange,"maxchange"=>$maxchange);
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
   if ( is_array($audio_id) ) {
     unset($values["audio_id"]);
     $values["audio_id"] = implode(",",$audio_id);
   } else {
     unset($searchmovievals["audio_id"]);
     $searchmovievals["audio_id"] = explode(",",$audio_id);
   }
   if ( is_array($subtitle_id) ) {
     unset($values["subtitle_id"]);
     $values["subtitle_id"] = implode(",",$subtitle_id);
   } else {
     unset($searchmovievals["subtitle_id"]);
     $searchmovievals["subtitle_id"] = explode(",",$subtitle_id);
   }
   $query  = "\$db->searchmovies(\"$order\",$start)";
   $par = "?order=$order";
   $scrits = "";
   foreach ($values as $key=>$val) {
     if (!empty($val)) {
       $par .= "&$key=$val";
       $scrits .= "&$key=$val";
     }
   }
   $scrits = substr($scrits,1);
   $t->set_var("ocrits","&$scrits");
   $t->set_var("crits","?$scrits");
   $nextmatch = new nextmatch($query,$pvp->tpl_dir,$_SERVER["PHP_SELF"].$par,$start);
   unset ($title); # messes up the movie list else
   include ("inc/movielist.inc");
   include ("inc/footer.inc");
   exit;
 }

 #==========================================================[ Search Form ]===
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"search.tpl"));
 $t->set_var("js",$js);
 $t->set_var("listtitle",lang("search_movie"));
 $t->set_var("formtarget",$_SERVER["PHP_SELF"]);
 $t->set_var("submit",lang("search"));
 $t->set_var("mtype_name",lang("mediatype"));
 #----------------------------------------------------------[ Media Types ]---
 $mtypes = $db->get_mtypes();
 $mtype_field = "<SELECT NAME='mtype_id[]' SIZE='7' MULTIPLE CLASS='multiselect'>";
 for ($i=0;$i<count($mtypes);++$i) {
   $mtype_field .= "<OPTION VALUE='".$mtypes[$i]['id']."'>".$mtypes[$i]['sname']." (".$mtypes[$i]['name'].")</OPTION>";
 }
 $mtype_field .= "</SELECT>";
 $t->set_var("mtype_field",$mtype_field);
 #-----------------------------------------------------------[ Categories ]---
 $t->set_var("cat_name",lang("category"));
 $cats = $db->get_category(); $ccount = count($cats);
 $cat_field = "<SELECT NAME='cat_id[]' SIZE='7' MULTIPLE CLASS='multiselect'>";
 for ($i=0;$i<$ccount;++$i) {
   if ($cats[$i]['enabled'])
     $cat_field .= "<OPTION VALUE='".$cats[$i]['id']."'>".lang($cats[$i]['internal'])."</OPTION>";
 }
 $cat_field .= "</SELECT>";
 $t->set_var("cat_field",$cat_field);
 #------------------------------------------------------[ Audio Languages ]---
 $t->set_var("audio_name",lang("audio_ts"));
 $langs = $db->get_avlang("audio"); $lc = count($langs);
 $lang_field = "<SELECT NAME='audio_id[]' SIZE='4' MULTIPLE CLASS='multiselect'>";
 for ($i=0;$i<$lc;++$i) {
   $lang_field .= "<OPTION VALUE='".$langs[$i]->id."'>".$langs[$i]->name."</OPTION>";
 }
 $lang_field .= "</SELECT>";
 $t->set_var("audio_field",$lang_field);
 #---------------------------------------------------[ Subtitle Languages ]---
 $t->set_var("subtitle_name",lang("subtitle"));
 $langs = $db->get_avlang("subtitle"); $lc = count($langs);
 $lang_field = "<SELECT NAME='subtitle_id[]' SIZE='4' MULTIPLE CLASS='multiselect'>";
 for ($i=0;$i<$lc;++$i) {
   $lang_field .= "<OPTION VALUE='".$langs[$i]->id."'>".$langs[$i]->name."</OPTION>";
 }
 $lang_field .= "</SELECT>";
 $t->set_var("subtitle_field",$lang_field);
 #---------------------------------[ Inputs (Actors, title, comment etc.) ]---
 $t->set_var("person_field","<SELECT NAME='ptype'><OPTION VALUE='actor'>".lang("actor")."</OPTION><OPTION VALUE='director'>".lang("director_person")."</OPTION></SELECT>");
 $t->set_var("name_field","<INPUT NAME='pname' ".$form["addon_name"].">");
 $t->set_var("title_name",lang("title"));
 $t->set_var("title_field","<INPUT NAME='title' ".$form["addon_name"].">");
 $t->set_var("comment_name",lang("comments"));
 $t->set_var("comment_field","<INPUT NAME='comment' ".$form["addon_name"].">");
 $t->set_var("length_name",lang("length"));
 $t->set_var("length_min","<INPUT NAME='minlen' ".$form["addon_year"]."onChange='check_len();'>");
 $t->set_var("length_max","<INPUT NAME='maxlen' ".$form["addon_year"]."onChange='check_len();'>");
 $t->set_var("min",lang("minute_abbrev"));
 $t->set_var("fsk_name",lang("fsk"));
 $t->set_var("fsk_min","<INPUT NAME='minfsk' ".$form["addon_fsk"]."onChange='check_fsk();'>");
 $t->set_var("fsk_max","<INPUT NAME='maxfsk' ".$form["addon_fsk"]."onChange='check_fsk();'>");
 $t->set_var("rating_name",lang("rating"));
 $t->set_var("rating_min","<INPUT NAME='minrat' ".$form["addon_year"]."onChange='check_rating();'>");
 $t->set_var("rating_max","<INPUT NAME='maxrat' ".$form["addon_year"]."onChange='check_rating();'>");
 $t->set_var("lastchange_name",lang("last_change"));
 $t->set_var("lastchange_min","<input name='minchange' class='medianrinput'>&nbsp;<img src='images/cal.gif' onClick=\"show_calendar('document.searchform.minchange');\">");
 $t->set_var("lastchange_max","<input name='maxchange' class='medianrinput'>&nbsp;<img src='images/cal.gif' onClick=\"show_calendar('document.searchform.maxchange');\">");
 if (!$pvp->cookie->active) $t->set_var("hidden","<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>");
 include("inc/header.inc");
 $t->pparse("out","template");

 include("inc/footer.inc");
?>