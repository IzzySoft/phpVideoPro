<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Label generator                                                           #
 #############################################################################

 /* $Id$ */

 #=================================================[ Register global vars ]===
 while ( list($vn,$vv)=each($_POST) ) {
   $$vn = $vv;
 }

 #========================================================[ initial setup ]===
 $silent = $cass_id || isset($create);
 $page_id = "label";
 $labels_pp = 8; // how many labels per page
 include("inc/includes.inc");
 if (!$pvp->auth->browse) kickoff();
 include("inc/class.label.inc");

 #========================[ create exactly one label and send it as image ]===
 if ($cass_id) { // we directly go to create one label
   if (!$labelconf) $labelconf = "default";
   $id = $db->get_movieid($mtype_id,$cass_id);
   $label  = new label($labelconf);
   $text   = $label->make_text($id);
   $label->write($cass_id,$text);
   $label->prn();
   $label->destroy();
 #===============[ create multiple labels and output as HTML via template ]===
 } elseif (isset($create)) { // we have to create multiple labels
   $t = new Template($pvp->tpl_dir);
   $t->set_file(array("list"=>"label_list.tpl"));
   $t->set_block("list","definitionblock","definitionlist");
   for ($i=0;$i<$labels_pp;$i++) {
     $cass_id = "medianr_$i";
     $cass_id = ${$cass_id};
     if ($cass_id && $valid->num($cass_id)) {
       $mtype_id = "mtype_id_$i";
       $ltpl     = "label_$i";
       $label = "<IMG SRC=\"" . $_SERVER["PHP_SELF"] . "?cass_id=$cass_id&mtype_id=" . ${$mtype_id} . "&labelconf=" . ${$ltpl} . "\">";
       $t->set_var("image",$label);
       $t->parse("definitionlist","definitionblock",TRUE);
     }
   }
   include("inc/header.inc");
   $t->pparse("out","list");
 #===============================[ query user input for multi-label-print ]===
 } else { // no arguments - so we have to prompt for them
   $t = new Template($pvp->tpl_dir);
   $t->set_file(array("list"=>"label_init.tpl"));
   $t->set_block("list","definitionblock","definitionlist");
   $mtypes = $db->get_mtypes();
   for ($i=0;$i<count($mtypes);$i++) {
     $mtypelist .= "<OPTION VALUE=\"" . $mtypes[$i][id] . "\">" . $mtypes[$i][sname] . "</OPTION>";
   }
   $labels = $pvp->common->get_filenames($base_dir . "labels",".config");
   for ($i=0;$i<count($labels);$i++) {
     $confname = substr($labels[$i],0,strlen($labels[$i]) - 7);
     $labellist .= "<OPTION VALUE=\"$confname\">" . ucwords(str_replace("_"," ",$confname)) . "</OPTION>";
   }
   for ($i=0;$i<$labels_pp;$i++) {
     $mtype   = "<SELECT NAME=\"mtype_id_$i\">$mtypelist</SELECT>";
     $medianr = "<INPUT NAME=\"medianr_$i\"" . $form["addon_tech"] . ">";
     $label   = "<SELECT NAME=\"label_$i\">$labellist</SELECT>";
     $t->set_var("mtype",$mtype);
     $t->set_var("medianr",$medianr);
     $t->set_var("label",$label);
     $t->parse("definitionlist","definitionblock",TRUE);
   }
   include("inc/header.inc");
   $t->set_var("mtype",lang("mediatype"));
   $t->set_var("medianr",lang("medianr"));
   $t->set_var("label",lang("label"));
   $t->set_var("listtitle",lang("print_label"));
   $t->set_var("form_target",$_SERVER["PHP_SELF"]);
   $t->set_var("create",lang("create"));
   if (!$pvp->cookie->active) $t->set_var("sess_id","<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>");
   $t->pparse("out","list");
 }
 
 include("inc/footer.inc");
?>