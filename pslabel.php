<?php
 #############################################################################
 # pslabels for phpVideoPro (c) 2002 by Michael Hasselberg <mh@zonta.ping.de>#
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Label generator                                                           #
 #############################################################################

 /* $Id$ */

 $page_id = "pslabel";
 $labels_pp = 8; // how many labels per page
 include("inc/includes.inc");

 #=============================================================[ security ]===
 if (!$pvp->auth->browse) kickoff();
 vul_num("ltype_id");
 vul_alnum("layout");
 $vuls = array();
 for ($i=0;$i<$labels_pp;++$i) {
   if (isset($_REQUEST["mtype_id_$i"])) {
     vul_num("mtype_id_$i");
     ${"mtype_id_${i}"} = $_REQUEST["mtype_id_$i"];
   }
   if (isset($_REQUEST["label_$i"])) {
     vul_num("label_$i");
     ${"label_${i}"} = $_REQUEST["label_$i"];
   }
   if (!$pvp->common->req_is_num("medianr_$i")) $vuls[] = str_replace("\\n"," ",lang("medianr_is_nan"));
     else ${"medianr_$i"} = $_REQUEST["medianr_$i"];
 }
 if (!$pvp->common->req_is_num("maxfontsize")) $vuls[] = str_replace("\\n"," ",lang("fontsize_is_nan"));
 if ($vc=count($vuls)) {
   $msg = lang("input_errors_occured",$vc) . "<UL>\n";
   for ($i=0;$i<$vc;++$i) {
     $msg .= "<LI>".$vuls[$i]."</LI>\n";
   }
   $msg .= "</UL>";
   $pvp->common->die_error($msg);
 }

 #==============================================[ Register form variables ]===
 $postit = array("ltype_id","layout","create","maxfontsize");
 foreach ($postit as $var) {
   if (isset($_REQUEST[$var])) $$var = $_REQUEST[$var];
 }
 unset($postit);

 #========================================================[ initial setup ]===
 $silent = $cass_id || isset($create);
 include("inc/class.label.inc");
 $printer_id = $pvp->preferences->get("printer_id");

 #== Step 3 =====[ create a sheet of labels and output as PostScript ]===
if (isset($create)) { // we have to create label sheet
  $ltypes = $db->get_lsheet_info($ltype_id,$printer_id); // all label sheet definitions

  header("Content-Disposition: attachment; filename=pslabels.ps");
  header("Content-type: application/postscript"); // text/plain will be displayed inline, so we fool the browser

  $t = new Template($pvp->pstpl_dir);
  $t->set_file(array("list"=>"header.tpl"));

#
# get data for ps file header
#
  $t->set_var("_pr_unit_size_",$ltypes['pr_unit_size']);
  $t->set_var("_pr_left_",$ltypes['pr_left']);
  $t->set_var("_pr_top_",$ltypes['pr_top']);
  $t->set_var("_sheet_papersize_",$ltypes['sheet_papersize']);
  $t->set_var("_sheet_unit_size_",$ltypes['sheet_unit_size']);
  $t->set_var("_label_unit_size_",$ltypes['label_unit_size']);
  $t->set_var("_sheet_length_",$ltypes['sheet_length']);
  $t->set_var("_sheet_width_",$ltypes['sheet_width']);
  $t->set_var("_left_margin_",$ltypes['left_margin']);
  $t->set_var("_top_margein_",$ltypes['top_margin']);
  $t->set_var("_label_width_",$ltypes['label_width']);
  $t->set_var("_label_height_",$ltypes['label_heigth']);
  $t->set_var("_label_vdist_",$ltypes['label_vdist']);
  $t->set_var("_label_hdist_",$ltypes['label_hdist']);
  $t->set_var("_label_cols_",$ltypes['label_cols']);
  $t->set_var("_label_rows_",$ltypes['label_rows']);

  $t->set_var("_lang_director_",$pvp->common->recode(lang("director")));
  $t->set_var("_lang_actor_",$pvp->common->recode(lang("actor")));
  $t->set_var("_lang_composer_",$pvp->common->recode(lang("composer")));

  $t->pparse("out","list");
#
# ps header generated, now come the labels
#

#
# include a list of all known units
#
  $all_units = $db->get_units();
  for ($i=0; $i<count($all_units); $i++) {
    printf("/%s { %f mul } bdef\n",$all_units[$i]['unit'],$all_units[$i]['factor']);
  } 

# for all labels on sheet 
  for ($row=0; $row<$ltypes['label_rows']; ++$row) {
    printf("gsave\n");
    for ($col=0; $col<$ltypes['label_cols']; $col++) {
      $i = $row * $ltypes['label_cols'] + $col;
      $mtype_id = ${"mtype_id_$i"};
      $medianr  = ${"medianr_$i"};
      $label    = ${"label_$i"};

      if ($medianr) {
        $eps_file = $db->get_epsimage($label);
#   get eps image for (mtype,label) and put in outputfile
#
# make bounding box
#
        $eps_llx=$eps_file['llx'];
        $eps_lly=$eps_file['lly'];
        $eps_urx=$eps_file['urx'];
        $eps_ury=$eps_file['ury'];
#
# print eps header
#
      printf("save\n/showpage { } def\n/llx { %d } def\n/lly { %d } def\n
/urx { %d } def\n/ury { %d } def\nlabel_width urx llx sub div \n
label_height ury lly sub div scale \nllx neg lly neg translate\n
llx lly moveto urx lly lineto \nurx ury lineto llx ury lineto \n
closepath clip \n",$eps_llx, $eps_lly, $eps_urx, $eps_ury);
#
# now print epsfile 
# DEBUG-PS: indicate which eps file is used
        echo "%% FILE: ".$pvp->pstpl_dir."/".$eps_file['eps']."\n";
        readfile($pvp->pstpl_dir . "/" . $eps_file['eps']); 

# and restore system state
        echo "restore\n";

#   get all movies on media(medianr) and put in outputfile using 'text' template
# create label entries
        $movies = $db->get_movieid($mtype_id,$medianr);

# DEBUG-PS indicate which ps template is used
  echo "%% FILE: ".$pvp->pstpl_dir."/".$eps_file['ps']."\n";

  $pslabel =  file($pvp->pstpl_dir . "/" . $eps_file['ps']);
### NEW
  # get switches and values from ps template into this engine
  # such as maximum number of text lines or maximum
  # usable area size (x and y) for printing and line feed control
  # maybe this should better go into the database as a property
  # of the eps template
  for ($lines=0;$lines<count($pslabel);$lines++) {
    preg_match_all("/\{\!\S+\!\}/",$pslabel[$lines],$lswitches);
    $matchcount = count($lswitches[0]);
    for ($k=0;$k<$matchcount;$k++) { // replace placeholders
      # make clean name of var for data base lookup
      $var  = substr($lswitches[0][$k],2,strlen($lswitches[0][$k])-4);
      # now lookup var in data base and get value in $rvar
      # $rvar = 
      }
    }
### END NEW
  $t = new Template($pvp->pstpl_dir);
  $t->set_file(array("label"=>$eps_file['ps']));
  $t->set_block("label","definitionblock","definitionlist");
  $moviecount  = count($movies);
  $lmoviecount = 0;
     for ($i=0;$i<$moviecount;++$i) {
       $movie = $db->get_movie($movies[$i]);
       if (!$movie['label']) continue;
       ++$lmoviecount;
       for ($lines=0;$lines<count($pslabel);$lines++) {
         preg_match_all("/\{_\S+_\}/",$pslabel[$lines],$matches);
         $matchcount = count($matches[0]);
         for ($k=0;$k<$matchcount;$k++) { // replace placeholders
           # make clean name of var for data base lookup
           $var  = substr($matches[0][$k],2,strlen($matches[0][$k])-4);
           # make name pattern for substitution
           $svar  = substr($matches[0][$k],1,strlen($matches[0][$k])-2);
	   # now lookup var in data base and get value in $rvar
           if (isset($movie[$var])) $rvar = $pvp->common->recode($movie[$var]);
	   # deal with special vars like length
           if ($var == "length") { // convert to hh:mm
             $minutes = $rvar % 60; if ($minutes<10) $minutes = "0$minutes";
             $hours   = floor($rvar / 60);
             $rvar    = "$hours:$minutes";
           }
           if (!isset($rvar)) $rvar = "";
           $t->set_var($svar, $rvar);
         }
       } // for $lines
       if ($lmoviecount>1) $t->parse("definitionlist","definitionblock",TRUE);
         else $t->parse("definitionlist","definitionblock");
     } // for $i
# fill in header information and overwrite any garbage
    $t->set_var("_cass_id_", $medianr);
    $t->set_var("_side_lines_",$lmoviecount);
    $t->set_var("_top_lines_",$lmoviecount);
    $t->set_var("_max_fontsize_",$maxfontsize);
    $t->pparse("out","label");
#
     } // if medianr
#   advance to next label printing position within row
    echo "label_hdist 0 translate\n";
    }
# advance to next label row
  printf("grestore\n");
  echo "0 label_vdist neg translate\n";
  }
# endfor
  
#print page footer
echo "showpage\n";
#
 #== Step 2 =====================[ query user input for multi-label-print ]===
 } elseif  (isset($layout)) { // we have to get layout details
 #---------------------------------------------[ Setup special JavaScript ]---
 $nr_nan = lang("medianr_is_nan");
 $fontsize_nan = lang("fontsize_is_nan");
 $js = "<SCRIPT TYPE='text/javascript' LANGUAGE='JavaScript'>//<!--
   function check_nr(nr) {
     if (isNaN(nr.value)) {
       nr.value = '';
       alert('$nr_nan');
     }
   }
   function check_fontsize(nr) {
     if (isNaN(nr.value)) {
       nr.value = '12';
       alert('$fontsize_nan');
     }
   }
//--></SCRIPT>";
 include("inc/header.inc");
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("list"=>"ps_layout.tpl"));
 $t->set_block("list","errorblock","errorlist");
 $t->set_block("list","definitionblock","definitionlist");
 $t->set_block("list","submitblock","submitlist");
 $t->set_var("js",$js);
 $t->set_var("listtitle",lang("print_label"));
 $t->set_var("form_target",$_SERVER["PHP_SELF"]);
 $t->set_var("ltype",$ltype_id);
 if (!$pvp->cookie->active) $t->set_var("sess_id","<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>");
 $ltypes = $db->get_lsheet($ltype_id); // get no. of rows and cols on label sheet and label type
#== TODO: Abgleich label - sheet - template - layout etc
 $mtypes  = $db->get_mtypes();
 $mtypelist = "";
 for ($i=0;$i<count($mtypes);$i++) {
   $mtypelist .= "<OPTION VALUE=\"" . $mtypes[$i]['id'] . "\">" . $mtypes[$i]['sname'] . "</OPTION>";
 }
#== make selection for EPS templates
 $epstemplates = $db->get_epstemplates($ltypes['type']);
 $etcount = count($epstemplates);
 if (empty($etcount)) {
   $t->set_var("error_msg",lang("pspack_install_required"));
   $t->parse("errorlist","errorblock");
   $t->pparse("out","list");
 } else {
   $epslist = "";
   for ($i=0;$i<$etcount;$i++) {
     $epslist .= "<OPTION VALUE=\"" . $epstemplates[$i]['id'] . "\">" . $epstemplates[$i]['description'] . "</OPTION>";
   }
#==
   for ($row=0; $row<$ltypes['rows']; ++$row) {
     if (!isset($format)) $format = "";
     for ($col=0; $col<$ltypes['cols']; ++$col) {
       $i = $row * $ltypes['cols'] + $col;
       $mtype   = "<SELECT NAME=\"mtype_id_$i\">$mtypelist</SELECT>";
       $medianr = "<INPUT NAME=\"medianr_$i\" onChange='check_nr(this);' " . $form["addon_tech"] . ">";
       $label   = "<SELECT NAME=\"label_$i\">$epslist</SELECT>";
       $t->set_var("mtype_$col",$mtype);
       $t->set_var("medianr_$col",$medianr);
       $t->set_var("label_$col",$label);
       $t->set_var("format_$col",$format);
     }
     if ($row) $t->parse("definitionlist","definitionblock",TRUE);
       else $t->parse("definitionlist","definitionblock");
   }
   for ($col=0; $col<$ltypes['cols']; $col++) {
     $t->set_var("hmtype_$col",lang("mediatype"));
     $t->set_var("hmedianr_$col",lang("medianr"));
     $t->set_var("hlabel_$col",lang("label"));
     $t->set_var("hformat_$col",lang("format"));
   }
   $t->set_var("create",lang("create"));
   $ifontsize = "<INPUT NAME='maxfontsize' VALUE='12' onChange='check_fontsize(this);' " .$form["addon_fsk"]. ">";
   $t->set_var("max_fontsize",$ifontsize);
   $t->set_var("max_fontsize_desc",lang("max_fontsize"));
   $t->parse("submitlist","submitblock");
   $t->pparse("out","list");
 }
include("inc/footer.inc");
#== Step 1=====================[ query user input for multi-label-print ]===
 } else { // no arguments -- we have to ask for label type
   $t = new Template($pvp->tpl_dir);
   $t->set_file(array("list"=>"pslabel_init.tpl"));
   $t->set_block("list","definitionblock","definitionlist");
   $ltypes = $db->get_label_forms();
   $ltypelist = "";
   for ($i=0;$i<count($ltypes);$i++) {
     $ltypelist .= "<OPTION VALUE=\"" . $ltypes[$i]['id'] . "\">" . $ltypes[$i]['vendor'] . "," . $ltypes[$i]['product'] . "</OPTION>";
   }
   $ltype   = "<SELECT NAME=\"ltype_id\">$ltypelist</SELECT>";
   include("inc/header.inc");
   $t->set_var("listtitle",lang("print_label"));
   $t->set_var("ltype",$ltype);
   $t->parse("definitionlist","definitionblock");
   $t->set_var("lselect",lang("labeltype"));
   $t->set_var("layout",lang("layout_label"));
   $t->set_var("form_target",$_SERVER["PHP_SELF"]);
   if (!$pvp->cookie->active) $t->set_var("sess_id","<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>");
   $t->pparse("out","list");

include("inc/footer.inc");
 }
?>