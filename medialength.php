<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2006 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Change media length                                                       #
 #############################################################################

 /* $Id$ */

 #=================================================[ Register global vars ]===
 $mtype_id = $_GET["mtype_id"];
 $cass_id  = $_GET["cass_id"];
 while ( list($vn,$vv)=each($_POST) ) {
   $$vn = $vv;
 }

 #========================================================[ initial setup ]===
 include("inc/includes.inc");
 vul_alnum("update");
 if (!$pvp->auth->update) kickoff();
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"medialength.tpl"));

 #========================================================[ do the update ]===
 if ($_POST["update"]) {
   if ( $db->set_mediaspace($_POST["cass_id"],$_POST["mtype_id"],$_POST["mlength"]) ) {
     $save_result = "<SPAN CLASS='ok'>" .lang("update_success"). ".</SPAN><BR>\n";
   } else {
     $save_result = "<SPAN CLASS='error'>" .lang("update_failed"). "!</SPAN><BR>\n";
   }
 }

 #=============================================[ Setup special JavaScript ]===
 $mlength = $db->get_mediaspace($cass_id,$mtype_id);
 $len_nan = lang("len_is_nan");
 $js = "<SCRIPT TYPE='text/javascript' LANGUAGE='JavaScript'>//<!--
   function check_len() {
     dsf = document.medialength;
     if (isNaN(dsf.mlength.value)) {
       dsf.mlength.value = '$mlength';
       alert('$len_nan');
     }
   }
//--></SCRIPT>";

 #=======================================================[ setup the form ]===
 $medium  = $db->get_mtypes("id=$mtype_id");
 $medianr = $cass_id;
 while ( strlen($medianr)<4 ) { $medianr = "0".$medianr; }
 $medianr = $medium[0][sname] . " $medianr";

 $hidden = "<INPUT TYPE='hidden' NAME='mtype_id' VALUE='$mtype_id'>"
         . "<INPUT TYPE='hidden' NAME='cass_id' VALUE='$cass_id'>";
 if (!$pvp->cookie->active) $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>";

 $t->set_var("listtitle",lang("change_media_length"));
 $t->set_var("js",$js);
 $t->set_var("save_result",$save_result);
 $t->set_var("hidden_fields",$hidden);
 $t->set_var("info",lang("change_media_length_for",$medianr));
 $input = "<INPUT NAME='mlength' VALUE='$mlength' ".$form["addon_filmlen"]." onChange='check_len();'>";
 $t->set_var("input",$input);
 $input = "<INPUT CLASS='submit' TYPE='submit' NAME='update' VALUE='".lang("update")."'>";
 $t->set_var("submit",$input);

 include("inc/header.inc");
 $t->pparse("out","template");

 include("inc/footer.inc");
?>