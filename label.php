<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 \***************************************************************************/

 /* $Id$ */

 $silent = $cass_id || isset($create);
 $page_id = "label";
 $labels_pp = 5; // how many labels per page
 include("inc/header.inc");
 include("inc/label.inc");

 ############################################################################
 # create exactly one label and send it as image
 if ($cass_id) { // we directly go to create one label
   if (!$template) $template = "default"; 
   $query = "SELECT id FROM video"
          . " WHERE cass_id=$cass_id AND mtype_id=$mtype_id";
   $db->dbquery($query);
   while ( $db->next_record() ) {
     $id[] = $db->f('id');
   }

   $label  = new label($template);
   $text   = $label->make_text($id);
   $label->write($cass_id,$text);
   $label->prn();
   $label->destroy();
 ############################################################################
 # create multiple labels and output result as HTML via template
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
       $label = "<IMG SRC=\"" . $PHP_SELF . "?cass_id=$cass_id&mtype_id=" . ${$mtype_id} . "&template=" . ${$ltpl} . "\">";
       $t->set_var("image",$label);
       $t->parse("definitionlist","definitionblock",TRUE);
     }
   }
   $t->pparse("out","list");
 ############################################################################
 # query user input for multi-label-print
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
     $mtype   = "<SELECT NAME=\"mtype_id_$i\">$mtypelist</OPTION>";
     $medianr = "<INPUT NAME=\"medianr_$i\"" . $form["addon_tech"] . ">";
     $label   = "<SELECT NAME=\"label_$i\">$labellist</SELECT>";
     $t->set_var("mtype",$mtype);
     $t->set_var("medianr",$medianr);
     $t->set_var("label",$label);
     $t->parse("definitionlist","definitionblock",TRUE);
   }
   $t->set_var("mtype",lang("mediatype"));
   $t->set_var("medianr",lang("medianr"));
   $t->set_var("label",lang("label"));
   $t->set_var("listtitle",lang("print_label"));
   $t->set_var("form_target",$PHP_SELF);
   $t->set_var("create",lang("create"));
   $t->pparse("out","list");
 }
 
 include("inc/footer.inc");

?>