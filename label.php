<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Label generator (libGD)                                                   #
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
 include("inc/class.label.inc");

 #=======================================================[ security check ]===
 if (!$pvp->auth->browse) kickoff();
 vul_alnum("create");
 $vuls = 0;
 if (isset($mtype_id_0)) { // form submit
   for ($i=0;$i<$labels_pp;++$i) {
     vul_num("mtype_id_$i");
     vul_alnum("label_$i");
     if (!$pvp->common->req_is_num("medianr_$i")) ++$vuls;
   }
 }
 if ($vuls>0) $pvp->common->die_error(lang("input_errors_occured",$vuls)
   ."<UL>\n<LI>".str_replace("\\n"," ",lang("medianr_is_nan"))."</LI>\n</UL>");

 #========================[ create exactly one label and send it as image ]===
 if (isset($cass_id)) { // we directly go to create one label
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
       if ($i) $t->parse("definitionlist","definitionblock",TRUE);
         else $t->parse("definitionlist","definitionblock");
     }
   }
   include("inc/header.inc");
   $t->pparse("out","list");

 #===============================[ query user input for multi-label-print ]===
 } else { // no arguments - so we have to prompt for them
 #---------------------------------------------[ Setup special JavaScript ]---
 $nr_nan = lang("medianr_is_nan");
 $js = "<SCRIPT TYPE='text/javascript' LANGUAGE='JavaScript'>//<!--
   function check_nr(nr) {
     if (isNaN(nr.value)) {
       nr.value = '';
       alert('$nr_nan');
     }
   }
//--></SCRIPT>";
 #----------------------------------------------------------[ create form ]---
   $t = new Template($pvp->tpl_dir);
   $t->set_file(array("list"=>"label_init.tpl"));
   $t->set_block("list","definitionblock","definitionlist");
   $mtypes = $db->get_mtypes();
   $mtypelist = "";
   for ($i=0;$i<count($mtypes);$i++) {
     $mtypelist .= "<OPTION VALUE=\"" . $mtypes[$i]['id'] . "\">" . $mtypes[$i]['sname'] . "</OPTION>";
   }
   $labels = $pvp->common->get_filenames($base_path . "labels",".config");
   $labellist = "";
   for ($i=0;$i<count($labels);$i++) {
     $confname = substr($labels[$i],0,strlen($labels[$i]) - 7);
     $labellist .= "<OPTION VALUE=\"$confname\">" . ucwords(str_replace("_"," ",$confname)) . "</OPTION>";
   }
   for ($i=0;$i<$labels_pp;$i++) {
     $mtype   = "<SELECT NAME=\"mtype_id_$i\">$mtypelist</SELECT>";
     $medianr = "<INPUT NAME=\"medianr_$i\"" . $form["addon_tech"] . " onChange='check_nr(this);'>";
     $label   = "<SELECT NAME=\"label_$i\">$labellist</SELECT>";
     $t->set_var("mtype",$mtype);
     $t->set_var("medianr",$medianr);
     $t->set_var("label",$label);
     if ($i) $t->parse("definitionlist","definitionblock",TRUE);
       else $t->parse("definitionlist","definitionblock");
   }
   include("inc/header.inc");
   $t->set_var("js",$js);
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