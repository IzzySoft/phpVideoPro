<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Edit/View an entry                                                        *
 \***************************************************************************/

 /* $Id$ */

  if ($new_entry) {
    $page_id = "add_entry";
    $edit    = TRUE;
  } elseif ($edit) {
    $page_id = "edit";
  } elseif ($delete) {
    include("delete.php");
    exit;
  } else { $page_id = "view_entry"; }
  include("inc/header.inc");
?>
 <script language="JavaScript"><!--
   function label() {
     if (document.entryform.labelconf.value != "-") {
       url = '<?=$base_url . "label.php?mtype_id=$mtype_id&cass_id=$cass_id&template="?>' + document.entryform.labelconf.value;
       var pos = (screen.width/2)-400;
       campus  = eval("window.open(url,'<?=lang("print_label")?>','toolbar=yes,location=no,titlebar=no,directories=no,status=yes,resizable=no,scrollbars=yes,copyhistory=no,width=800,height=600,top=0,left=" + pos + "')");
     }
   }
 //-->
 </script>
<?php

  function vis_actors($num) {
    GLOBAL $edit,$vis_actor1,$vis_actor2,$vis_actor3,$vis_actor4,$vis_actor5;
    $visible = "vis_actor" . $num;
    $output  = "";
    if ($edit) {
      $output .= "<INPUT TYPE=\"checkbox\" NAME=\"vis_actor" . $num . "\" VALUE=\"1\" class=\"checkbox\"";
      if (${$visible}) $output .= " CHECKED";
      $output .= ">";
    } else {
      $output .= "<INPUT TYPE=\"button\" NAME=\"" . ${$visible} . "\" class=\"yesnobutton\" VALUE=\"";
      if (${$visible}) { $output .= lang("yes") ."\">"; } else { $output .= lang("no") . "\">"; }
      $output .= "<INPUT TYPE=\"hidden\" NAME=\"" . ${$visible} ."\" VALUE=\"${$visible}\">";
    }
    return $output;
  }

  function vis_staff($name,$list) {
    GLOBAL $edit;
    $output  = "";
    if ($edit) {
      $output .= "<INPUT TYPE=\"checkbox\" NAME=\"$name\" VALUE=\"1\" class=\"checkbox\"";
      if ($list) $output .= " CHECKED";
      $output .= ">";
    } else {
      $output .= "<INPUT TYPE=\"button\" NAME=\"$name\" class=\"yesnobutton\" VALUE=\"";
      if ($list) { $output .= lang("yes") . "\">"; } else { $output .= lang("no") . "\">"; }
      $output .= "<INPUT TYPE=\"hidden\" NAME=\"$name\" VALUE=\"$list\">";
    }
    return $output;
  }

  if ($edit) {
    $input = "INPUT SIZE=\"30\"";
    $dinput = "INPUT";
    $mtypes = $db->get_mtypes();
    $ttypes = $db->get_tone();
    $cats   = $db->get_category("");
    $scolors = $db->get_color();
    for ($i=0;$i<count($scolors);$i++) {
     $scolors[$i][name] = lang($scolors[$i][name]);
    }
    $picts = $db->get_pict();
    $commercials = $db->get_commercials();
    for ($i=0;$i<count($commercials);$i++) {
      $comm[$commercials[$i][id]] = $commercials[$i][name];
      $comm_id[$i] = $commercials[$i][id];
    }
  } else {
    $input = $dinput = "INPUT TYPE=\"button\"";
    // $input .= " readonly"; // HTML 4.0 - not supported by Netscape 4.x
  }

  function form_input($name,$value,$addons="") {
    GLOBAL $edit;
    if ($edit) {
      $type = " " . trim($addons) . " ";
    } else {
      if ( strlen(trim($value)) < 1 ) {
        $type = " TYPE=\"hidden\" ";
      } else {
        $type = " TYPE=\"button\" ";
      }
    }
    $field = "<INPUT" . $type . "NAME=\"$name\" VALUE=\"$value\" $addons>";
    return $field;
  }
  
  if ($update) { include("inc/update.inc"); }
  elseif ($create) { include("inc/add_entry.inc"); }

  ##########################################################################
  # get all needed data from db (if not $new_entry ;)
 if (!$new_entry) {
  $id    = $db->get_movieid($mtype_id,$cass_id,$part);
  $movie = $db->get_movie($id);

  // values:
  $mdetails = array ("title","length","year","country","fsk","lp","comment",
              "counter1","counter2","music_list","director_list","commercials",
	      "tone","color");
  foreach ($mdetails as $value) {
    $$value = $movie[$value];
  }
  $recdate = $movie[aq_date]; $src = $movie[source];
  $vis_actor1 = $movie[actor1_list]; $vis_actor2 = $movie[actor2_list];
  $vis_actor3 = $movie[actor3_list]; $vis_actor4 = $movie[actor4_list];
  $vis_actor5 = $movie[actor5_list];

  for ($i=1;$i<6;$i++) {
    $act_id  = "actor_$i";
    $actor[$i][name]  = $movie[$act_id][name];
    $actor[$i][fname] = $movie[$act_id][firstname];
  }
  $director_name  = $movie[director_][name];
  $director_fname = $movie[director_][firstname];
  $composer_name  = $movie[music_][name];
  $composer_fname = $movie[music_][firstname];

  $mtypes = $db->get_mtypes("id=$mtype_id");
  $mediatype = $mtypes[0][sname]; $media_tname = $mtypes[0][name];
  $pict_format = $movie[pict];

  for ($i=1;$i<4;$i++) {
    $cat_nr  = "cat$i";
    $cat[$i] = $movie[$cat_nr];
  }
  $free = "0";
  if ($mediatype == "RVT") {
    $query = "SELECT free FROM cass WHERE id=$cass_id";
    dbquery($query); $db->next_record();
    $free  = $db->f('free');
  }
 } else {
   $lastnum = $db->get_lastmovienum();
 } // end if (!$new_entry)
  ##########################################################################
  # set some useful defaults
  if ( trim($recdate)=="" ) $recdate = $pvp->common->getRecDate("string");
  switch ( strtolower($page_id) ) {
    case "view_entry"      : if ( trim($recdate)=="0000-00-00" ) $recdate = lang("unknown"); break;
  }
  if ($create) {
    while ( strlen($cass_id)<4 ) { $cass_id = "0" . $cass_id; }
    while ( strlen($part)<2)     { $part    = "0" . $part;    }
    $nr = $mediatype . " " . $cass_id . "-" . $part;
  }

################################################################
# Form Start
  $t = new Template($pvp->tpl_dir);
  $t->set_file(array("edit"=>"edit.tpl"));
  $t->set_var("form_name","entryform");
  $t->set_var("form_target",$PHP_SELF);
  switch ( strtolower($page_id) ) {
    case "edit"      : $t->set_var("listtitle",lang("edit_entry",$nr)); break;
    case "view_entry"      : $t->set_var("listtitle",lang("view_entry",$nr)); break;
    case "add_entry" : $t->set_var("listtitle",lang("add_entry")); break;
    default          : break;
  }
  $t->set_var("save_result",$save_result);
  $t->set_block("edit","actorblock","actorlist");

  // actors block
  for ($i=1;$i<=$max["actors"];$i++) {
    $name = "actor" . $i . "_name"; $fname = "actor" . $i . "_fname";
    if ($page_id == "view_entry") { // set imdb info url for actor
      $formAddon = $form["addon_name"] . $pvp->link->formImdbPerson($actor[$i][fname],$actor[$i][name],"actors");
    } else { $formAddon = $form["addon_name"]; }
    $t->set_var("actor_name",lang("actor") . " $i");
    $t->set_var("actor",form_input($name,$actor[$i][name],$formAddon));
    $t->set_var("actor_f",form_input($fname,$actor[$i][fname],$formAddon));
    $t->set_var("actor_list",vis_actors($i));
    $t->parse("actorlist","actorblock",TRUE);
  }

  // main block
  if (!$new_entry) {
    $hiddenfields = <<<EndHiddenFields
<INPUT TYPE="hidden" NAME="cass_id" VALUE="$cass_id">
<INPUT TYPE="hidden" NAME="part" VALUE="$part">
<INPUT TYPE="hidden" NAME="mtype_id" VALUE="$mtype_id">
EndHiddenFields;
  }
  $t->set_var("title","<$input NAME=\"title\" VALUE=\"$title\" " . $form["addon_title"] . ">");
  $t->set_var("mtype_name",lang("mediatype"));
  if ($new_entry) {
    $field = "<SELECT NAME=\"mtype_id\">";
    for ($i=0;$i<count($mtypes);$i++) {
      $field .= "<OPTION VALUE=\"" . $mtypes[$i][id] . "\"";
      if ($mtypes[$i][name]==$media_tname) $field .= " SELECTED";
      $field .= ">" . $mtypes[$i][name] . "</OPTION>";
    }
    $field .= "</SELECT>";
  } else {
    $field  = "<INPUT TYPE=\"button\" NAME=\"media_tname\" VALUE=\"$media_tname\">";
    $field .= "<INPUT TYPE=\"hidden\" NAME=\"media_tname\" VALUE=\"$media_tname\">";
  }
  $t->set_var("mtype",$field);
  $t->set_var("country_name",lang("country"));
  $t->set_var("country",form_input("country",$country,$form["addon_country"]));
  $t->set_var("medianr_name",lang("medianr"));
  if ($new_entry) {
    $field  = "<INPUT NAME=\"cass_id\" " . $form["addon_cass_id"] . ">&nbsp;-&nbsp;<INPUT NAME=\"part\" " . $form["addon_part"] . ">";
    $field .= "&nbsp;&nbsp;&nbsp;" . lang("highest_db_entries") . ":&nbsp;<SELECT>";
    for ($i=0;$i<count($lastnum);$i++) {
      $field .= "<OPTION NAME=\"lastnum\" VALUE=\"\">" . $lastnum[$i][entry] . "</OPTION>";
    }
    $field .= "</SELECT>";
  } else {
    $field = "<INPUT TYPE=\"button\" NAME=\"nr\" VALUE=\"$nr\"><INPUT TYPE=\"hidden\" NAME=\"nr\" VALUE=\"$nr\">";
  }
  $t->set_var("medianr",$field);
  $t->set_var("year_name",lang("year"));
  $t->set_var("year",form_input("year",$year,$form["addon_year"]));
  $t->set_var("length_name",lang("length"));
  $t->set_var("length",form_input("length",$length,$form["addon_filmlen"]) . " " . lang("min"));
  $t->set_var("longplay_name",lang("longplay"));
  $field = "<INPUT NAME=\"lp\"";
  if ($edit) { 
    $field .= "TYPE=\"checkbox\" VALUE=\"1\" class=\"checkbox\"";
    if ($lp) $field .= " CHECKED";
    $field .= ">";
  } else {
    $field .= "TYPE=\"button\" class=\"yesnobutton\" VALUE=\"";
    if ($lp) { $field .= lang("yes") . "\">"; } else { $field .= lang("no") . "\">"; }
  }
  $t->set_var("longplay",$field);
  # Counter settings
  if (!$edit) {
    if (empty($counter1)) $counter1 = "&nbsp;";
    if (empty($counter2)) $counter2 = "&nbsp;";
  }
  $t->set_var("counter_name",lang("counter_start_stop"));
  $t->set_var("counter_1",form_input("counter1",$counter1,"class=\"yesnobutton\""));
  $t->set_var("counter_2",form_input("counter2",$counter2,"class=\"yesnobutton\""));
  # Categories
  $t->set_var("category_name",lang("category") . " 1-2-3");
  $field = "";
  for ($i=1;$i<=$max["categories"];$i++) {
   if ($edit) {
    $field .= "<SELECT NAME=\"cat" . $i . "_id\" class=\"catinput\">";
    if ($i > 1) $field .= "<OPTION VALUE=\"-1\">- None -</OPTION>";
    for ($k=0;$k<count($cats);$k++) {
      $field .= "<OPTION VALUE=\"" . $cats[$k][id] . "\"";
      if ($cats[$k][name]==$cat[$i]) $field .= " SELECTED";
      $field .= ">" . $cats[$k][name] . " </OPTION>";
    }
    $field .= "</SELECT>";
   } else {
    $field .= "<$input NAME=\"cat" . $i . "\" class=\"catinput\" VALUE=\"";
    if ( trim($cat[$i])=="" ) { $field .= "- None -"; } else { $field .= $cat[$i]; }
    $field .= "\">";
   }
   if ( $i<$max["categories"] ) $field .= "<BR>";
  }
  $t->set_var("category",$field);
  # Commercials
  $t->set_var("commercial_name",lang("commercials"));
  if ($edit) {
    $field = "<SELECT NAME=\"commercials_id\" class=\"techinput\">";
    for ($k=0;$k<count($comm);$k++) {
      $field .= "<OPTION VALUE=\"$comm_id[$k]\"";
      if ($commercials==$comm[$k]) $field .= " SELECTED";
      $field .= ">" . $comm[$k] . " </OPTION>";
    }
    $field .= "</SELECT>";
  } else {
    $field  = "<$input NAME=\"commercials\" class=\"techinput\" VALUE=\"$commercials\">";
  }
  $t->set_var("commercial",$field);
  # Remaining free time
  if ($new_entry) {
    $t->set_var("mlength_free_name",lang("medialength"));
    $t->set_var("mlength_free","<INPUT NAME=\"mlength\" VALUE=\"240\" " . $form["addon_filmlen"] . "> " . lang("minute_abbrev"));
  } else {
    $t->set_var("mlength_free_name",lang("free"));
    $t->set_var("mlength_free","<INPUT TYPE=\"button\" NAME=\"free\" VALUE=\"$free\"> " . lang("minute_abbrev"));
  }
  $t->set_var("date_name",lang("date_rec"));
  if ($recdate == lang("unknown")) {
    $tdate .= "<$dinput NAME=\"recdate\" VALUE=\"$recdate\"" . $form["addon_tech"] . ">";
  } else {
    $recdate_arr = $pvp->common->makeRecDateArr($recdate);
    $tdate .= "<$dinput NAME=\"recday\" VALUE=\"" . $recdate_arr[mday] . "\" " . $form["addon_day"] . ">.";
    $tdate .= "<$dinput NAME=\"recmon\" VALUE=\"" . $recdate_arr[mon] . "\" " . $form["addon_month"] . ">.";
    $tdate .= "<$dinput NAME=\"recyear\" VALUE=\"" . $recdate_arr[year] . "\" " . $form["addon_year"] . ">";
  }

  $t->set_var("date",$tdate);
  $t->set_var("tone_name",lang("tone"));
  if ($edit) {
    $field = "<SELECT NAME=\"tone_id\"" . $form["addon_tech"] . ">";
    for ($i=0;$i<count($ttypes);$i++) {
      $field .= "<OPTION VALUE=\"" . $ttypes[$i][id] . "\"";
      if ($ttypes[$i][name]==$tone) $field .=  "SELECTED";
      $field .= ">" . $ttypes[$i][name] . " </OPTION>";
    }
    $field .= "</SELECT>";
  } else {
    $field = "<$input NAME=\"tone\" VALUE=\"$tone\"" . $form["addon_tech"] . ">";
  }
  $t->set_var("tone",$field);
  $t->set_var("picture_name",lang("picture"));
  if ($edit) {
    $field = "<SELECT NAME=\"color_id\"" . $form["addon_tech"] . ">";
    for ($i=0;$i<count($scolors);$i++) {
      $field .= "<OPTION VALUE=\"" . $scolors[$i][id] . "\"";
      if ($scolors[$i][name]==$color || ($new_entry && $scolors[$i][id]==$defaults["scolor"]) ) $field .= " SELECTED";
      $field .= ">" . $scolors[$i][name] . " </OPTION>";
    }
    $field .= "</SELECT>";
  } else {
    $field = "<$input NAME=\"color\" VALUE=\"$color\"" . $form["addon_tech"] . ">";
  }
  $t->set_var("picture",$field);
  $t->set_var("screen_name",lang("screen"));
  if ($edit) {
    $field = "<SELECT NAME=\"pict_id\"" . $form["addon_tech"] . "><OPTION VALUE=\"-1\">" . lang("unknown") . "</OPTION>";
    for ($i=0;$i<count($picts);$i++) {
      $field .= "<OPTION VALUE=\"" . $picts[$i][id] . "\"";
      if ($picts[$i][name]==$pict_format) $field .=  "SELECTED";
      $field .= ">" . $picts[$i][name] . " </OPTION>";
    }
    $field .= "</SELECT>";
  } else {
    $field = "<$input NAME=\"pict_format\" VALUE=\"" . lang($pict_format) . "\"" . $form["addon_tech"] . ">";
  }
  $t->set_var("screen",$field);
  $t->set_var("source_name",lang("source"));
  if (strlen(trim($src)) || $edit) {
    $t->set_var("source",form_input("src",$src,$form["addon_src"]));
  } else {
    $t->set_var("source",form_input("dummy",lang("unknown"),$form["addon_src"]));
  }
  $t->set_var("fsk_name",lang("fsk"));
  $t->set_var("fsk",form_input("fsk",$fsk,$form["addon_fsk"]));
  $t->set_var("staff_name",lang("staff"));
  $t->set_var("name_name",lang("name"));
  $t->set_var("firstname_name",lang("first_name"));
  $t->set_var("inlist_name",lang("in_list"));
  $t->set_var("director_name",lang("director"));
  if ($page_id == "view_entry") {
    $formAddon = $form["addon_name"] . $pvp->link->formImdbPerson($director_fname,$director_name,"directors");
  } else { $formaddon = $form["addon_name"]; }
  $t->set_var("director",form_input("director_name",$director_name,$formAddon));
  $t->set_var("director_f",form_input("director_fname",$director_fname,$formAddon));
  $t->set_var("director_list",vis_staff('director_list',$director_list));
  $t->set_var("composer_name",lang("composer"));
  if ($page_id == "view_entry") {
    $formAddon = $form["addon_name"] . $pvp->link->formImdbPerson($composer_fname,$composer_name,"composers");
  } else { $formaddon = $form["addon_name"]; }
  $t->set_var("composer",form_input("composer_name",$composer_name,$formAddon));
  $t->set_var("composer_f",form_input("composer_fname",$composer_fname,$formAddon));
  $t->set_var("composer_list",vis_staff('music_list',$music_list));
  // actors are set up on top, in the "actors block"
  $t->set_var("comments_name",lang("comments"));
  if ($edit) {
    $t->set_var("comments","<DIV ALIGN=CENTER><TEXTAREA ROWS=\"5\" COLS=\"120\" NAME=\"comment\">$comment</TEXTAREA></DIV>");
  } else {
    $t->set_var("comments",nl2br($pvp->common->make_clickable($comment)));
  }
  $hiddenfields .= "<INPUT TYPE=\"hidden\" NAME=\"nr\" VALUE=\"$nr\">";
  $t->set_var("hiddenfields",$hiddenfields);
  if ($new_entry) {
    $t->set_var("button_li","<INPUT TYPE=\"submit\" NAME=\"cancel\" VALUE=\"" . lang("cancel") . "\">");
    $t->set_var("button_re","<INPUT TYPE=\"submit\" NAME=\"create\" VALUE=\"" . lang("create") . "\">");
    $t->set_var("print_label","&nbsp;");
  } elseif ($edit) {
    $t->set_var("button_li","<INPUT TYPE=\"submit\" NAME=\"cancel\" VALUE=\"" . lang("cancel") . "\">");
    $t->set_var("button_re","<INPUT TYPE=\"submit\" NAME=\"update\" VALUE=\"" . lang("update") . "\">");
    $t->set_var("print_label","&nbsp;");
  } else {
    $labels = $pvp->common->get_filenames($base_dir . "labels",".config");
    $labellist = "<SELECT NAME=\"labelconf\" onChange=\"label()\"><OPTION VALUE=\"-\">" . lang("print_label") . "</OPTION>";
    for ($i=0;$i<count($labels);$i++) {
      $confname = substr($labels[$i],0,strlen($labels[$i]) - 7);
      $labellist .= "<OPTION VALUE=\"$confname\">" . ucwords(str_replace("_"," ",$confname)) . "</OPTION>";
    }
    $labellist .= "</SELECT>";
    $t->set_var("button_li","<INPUT TYPE=\"submit\" NAME=\"edit\" VALUE=\""   . lang("edit")   . "\">");
    $t->set_var("button_re","<INPUT TYPE=\"submit\" NAME=\"delete\" VALUE=\"" . lang("delete") . "\">");
    $t->set_var("print_label","$labellist");
  }
  $t->pparse("out","edit");

  include("inc/footer.inc");

?>