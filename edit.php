<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Edit/View an entry                                                        #
 #############################################################################

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
  include("inc/includes.inc");
  if ( ($new_entry && !$pvp->auth->add)
    || (!$new_entry && $edit && !$pvp->auth->update)
    || (!$new_entry && !$edit && !$pvp->auth->browse) ) {
    kickoff(); // kick-off unauthorized visitors
  }
?>
 <script language="JavaScript"><!--
   function mklabel(labelconf) {
     if (labelconf != "-") {
       url = '<?=$base_url . "label.php?mtype_id=$mtype_id&cass_id=$cass_id&labelconf="?>' + labelconf;
       var pos = (screen.width/2)-400;
       campus  = eval("window.open(url,'label','toolbar=yes,location=no,titlebar=no,directories=no,status=yes,resizable=no,scrollbars=yes,copyhistory=no,width=800,height=600,top=0,left=" + pos + "')");
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
  
  function sort_cats($c1,$c2) {
    if($c1[name]<$c2[name]) return -1;
      else if ($c1[name]>$c2[name]) return 1;
  }

  if (!$nr) {
    while ( strlen($cass_id)<4 ) { $cass_id = "0" . $cass_id; }
    while ( strlen($part)<2)     { $part    = "0" . $part;    }
    $nr = $cass_id . "-" . $part;
#    $nr = $mediatype . " " . $cass_id . "-" . $part;
  }

  if ($edit) {
    $input = "INPUT SIZE=\"30\"";
    $dinput = "INPUT";
    $mtypes = $db->get_mtypes();
    $ttypes = $db->get_tone();
    $cats   = $db->get_category("");
    usort($cats,"sort_cats"); reset ($cats);
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
  $mdetails = array ("title","label","length","year","country","fsk","lp",
              "comment","counter1","counter2","music_list","director_list",
	      "commercials","tone","tone_id","color");
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
  $pict_format = $movie[pict];

  for ($i=1;$i<4;$i++) {
    $cat_nr  = "cat$i";
    $cat[$i] = $movie[$cat_nr];
  }
  $free = "0";
  if ($pvp->common->medium_is_rw($mtype_id)) $free = $db->get_mediumfreetime($cass_id,$mtype_id);
 } else {
   $lastnum = $db->get_lastmovienum();
 } // end if (!$new_entry)

  $mtypes = $db->get_mtypes("id=$mtype_id");
  $mediatype = $mtypes[0][sname]; $media_tname = $mtypes[0][name];
  ##########################################################################
  # set some useful defaults
  if ( trim($recdate)=="" ) $recdate = $pvp->common->getRecDate("string");
  switch ( strtolower($page_id) ) {
    case "view_entry"      : if ( trim($recdate)=="0000-00-00" ) $recdate = lang("unknown"); break;
  }
  if ($create) {
    while ( strlen($cass_id)<4 ) { $cass_id = "0" . $cass_id; }
    while ( strlen($part)<2)     { $part    = "0" . $part;    }
#    $nr = $mediatype . " " . $cass_id . "-" . $part;
    $nr = $cass_id . "-" . $part;
  }

################################################################
# Form Start
  include("inc/header.inc");
  $t = new Template($pvp->tpl_dir);
  $t->set_file(array("edit"=>"edit.tpl"));
  $t->set_var("form_name","entryform");
  $t->set_var("form_target",$PHP_SELF);
  switch ( strtolower($page_id) ) {
    case "edit"      : $t->set_var("listtitle",lang("edit_entry",$movie[mtype_short]." ".$nr)); break;
    case "view_entry"      : $t->set_var("listtitle",lang("view_entry",$movie[mtype_short]." ".$nr)); break;
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
    if ($i==1) {
      $t->set_var("actor_name",lang("actors"));
    } else {
      $t->set_var("actor_name","&nbsp;");
    }
    if ( $edit || strlen($actor[$i][name] . $actor[$i][fname]) ) {
      $t->set_var("actor",form_input($name,$actor[$i][name],$formAddon));
      $t->set_var("actor_f",form_input($fname,$actor[$i][fname],$formAddon));
      $t->set_var("actor_list",vis_actors($i));
    } else {
      $visible = "vis_actor" . $i;
      $formAddon = $form["addon_name"];
      $t->set_var("actor",form_input($name,"&nbsp;",$formAddon));
      $t->set_var("actor_f",form_input($fname,"&nbsp;",$formAddon));
      $t->set_var("actor_list","<INPUT TYPE=\"button\" NAME=\"" . ${$visible} . "\" class=\"yesnobutton\" VALUE=\"&nbsp;\"");
    }
    $t->parse("actorlist","actorblock",TRUE);
  }

  // main block
  if ($page_id == "view_entry") {
    $tpl_dir = str_replace($base_path,$base_url,$pvp->tpl_dir);
    if ($movie[previous]) {
      $prev = "<A HREF='" .$pvp->link->slink("$PHP_SELF?mtype_id=".$movie[previous]->mtype_id
            . "&cass_id=".$movie[previous]->media_nr."&part=".$movie[previous]->part)
	    . "'><IMG SRC='".$tpl_dir."/images/left.gif' BORDER='0'></A>";
    } else {
      $prev = "<IMG SRC='".$tpl_dir."/images/left-grey.gif'>";
    }
    $t->set_var("previous",$prev); unset($prev);
    if ($movie[next]) {
      $next = "<A HREF='" .$pvp->link->slink("$PHP_SELF?mtype_id=".$movie[next]->mtype_id
            . "&cass_id=".$movie[next]->media_nr."&part=".$movie[next]->part)
            . "'><IMG SRC='".$tpl_dir."/images/right.gif' BORDER='0'></A>";
    } else {
      $next = "<IMG SRC='".$tpl_dir."/images/right-grey.gif'>";
    }
    $t->set_var("next",$next); unset($next);
  }
    $hiddenfields = <<<EndHiddenFields
<INPUT TYPE="hidden" NAME="cass_id" VALUE="$cass_id">
<INPUT TYPE="hidden" NAME="mtype_id" VALUE="$mtype_id">
EndHiddenFields;
  if (!$new_entry) {
    $hiddenfields .= "\n<INPUT TYPE='hidden' NAME='part' VALUE='$part'>";
  }
  if ($page_id == "view_entry") { // set imdb info url for title
    $formAddon = $form["addon_title"] . $pvp->link->formImdbTitle($title);
  } else {
    $formAddon = $form["addon_title"];
  }
  $t->set_var("title","<$input NAME=\"title\" VALUE=\"$title\" " . $formAddon . ">");
  $t->set_var("mtype_name",lang("mediatype"));
  if ($new_entry) {
    $field  = "<INPUT TYPE='button' NAME='media_tname' VALUE='$media_tname' CLASS='catinput'>";
    $field .= "<INPUT TYPE='hidden' NAME='mtype_id' VALUE='$mtype_id'>";
    $next_part = 1; $last_part = 0;
    for ($i=0;$i<count($lastnum);$i++) {
      if ($lastnum[$i][cass_id]==$cass_id) {
        $next_part = $lastnum[$i][$part] +1;
        $last_part = $lastnum[$i][$part];
      }
    }
  } else {
    $field  = "<INPUT TYPE=\"button\" NAME=\"media_tname\" VALUE=\"$media_tname\" onClick=\"window.location.href='" .$pvp->link->slink("change_nr.php?id=$id"). "'\">";
    $field .= "<INPUT TYPE='hidden' NAME='media_tname' VALUE='$media_tname'>";
  }
  $t->set_var("mtype",$field);
  $t->set_var("country_name",lang("country"));
  $t->set_var("country",form_input("country",$country,$form["addon_country"]));
  $t->set_var("medianr_name",lang("medianr"));
  if ($new_entry) {
    $field  = "<INPUT TYPE='button' NAME='cass_id' VALUE='$cass_id' " . $form["addon_cass_id"] . ">&nbsp;-&nbsp;<INPUT NAME='part' VALUE='$next_part' " . $form["addon_part"] . ">";
    $field .= "&nbsp;&nbsp;&nbsp;" . lang("last_entry") . ":&nbsp;";
    $field .= "<INPUT TYPE='button' NAME='lastnum' VALUE='$last_part' CLASS='yesnobutton'>";
  } else {
    $field = "<INPUT TYPE=\"button\" NAME=\"nr\" VALUE=\"$nr\" onClick=\"window.location.href='" .$pvp->link->slink("change_nr.php?id=$id") ."'\"><INPUT TYPE='hidden' NAME='nr' VALUE='$nr'>";
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
  # Label
  if ($new_entry) $label = $pvp->preferences->get("default_movie_onlabel");
  $t->set_var("label_name",lang("label"));
  $field = "<INPUT NAME=\"label\"";
  if ($edit) { 
    $field .= "TYPE=\"checkbox\" VALUE=\"1\" class=\"checkbox\"";
    if ($label) $field .= " CHECKED";
    $field .= ">";
  } else {
    $field .= "TYPE=\"button\" class=\"yesnobutton\" VALUE=\"";
    if ($label) { $field .= lang("yes") . "\">"; } else { $field .= lang("no") . "\">"; }
  }
  $t->set_var("label",$field);
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
  } else { // hide free time for non-editable media
    if ($pvp->common->medium_is_rw($mtype_id)) {
      $t->set_var("mlength_free_name",lang("free"));
      $t->set_var("mlength_free","<INPUT TYPE='button' NAME='free' VALUE='$free' onClick=\"window.location.href='" .$pvp->link->slink("medialength.php?cass_id=$cass_id&mtype_id=$mtype_id"). "'\"> " . lang("minute_abbrev"));
    } else {
      $t->set_var("mlength_free_name","&nbsp;");
      $t->set_var("mlength_free","&nbsp;");
    }
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
  if ($new_entry) $tone_id = $pvp->preferences->get("default_movie_toneid");
  if ($edit) {
    $field = "<SELECT NAME=\"tone_id\"" . $form["addon_tech"] . ">";
    for ($i=0;$i<count($ttypes);$i++) {
      $field .= "<OPTION VALUE=\"" . $ttypes[$i][id] . "\"";
      if ($ttypes[$i][id]==$tone_id) $field .=  "SELECTED";
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
  } else { $formAddon = $form["addon_name"]; }
  if ( $edit || strlen($director_name . $director_fname) ) {
    $t->set_var("director",form_input("director_name",$director_name,$formAddon));
    $t->set_var("director_f",form_input("director_fname",$director_fname,$formAddon));
    $t->set_var("director_list",vis_staff('director_list',$director_list));
  } else {
    $formAddon = $form["addon_name"];
    $t->set_var("director",form_input("director_name","&nbsp;",$formAddon));
    $t->set_var("director_f",form_input("director_fname","&nbsp;",$formAddon));
    $t->set_var("director_list","<INPUT TYPE=\"button\" NAME=\"director_list\" class=\"yesnobutton\" VALUE=\"&nbsp;\"");
  }
  $t->set_var("composer_name",lang("composer"));
  if ($page_id == "view_entry") {
    $formAddon = $form["addon_name"] . $pvp->link->formImdbPerson($composer_fname,$composer_name,"composers");
  } else { $formAddon = $form["addon_name"]; }
  if ( $edit || strlen($composer_name . $composer_fname) ) {
    $t->set_var("composer",form_input("composer_name",$composer_name,$formAddon));
    $t->set_var("composer_f",form_input("composer_fname",$composer_fname,$formAddon));
    $t->set_var("composer_list",vis_staff('music_list',$music_list));
  } else {
    $formAddon = $form["addon_name"];
    $t->set_var("composer",form_input("composer_name","&nbsp;",$formAddon));
    $t->set_var("composer_f",form_input("composer_fname","&nbsp;",$formAddon));
    $t->set_var("composer_list","<INPUT TYPE=\"button\" NAME=\"music_list\" class=\"yesnobutton\" VALUE=\"&nbsp;\"");
  }
  // actors are set up on top, in the "actors block"
  $t->set_var("comments_name",lang("comments"));
  if ($edit) {
    $t->set_var("comments","<DIV ALIGN=CENTER><TEXTAREA ROWS=\"5\" COLS=\"120\" NAME=\"comment\">$comment</TEXTAREA></DIV>");
  } else {
    $t->set_var("comments",nl2br($pvp->common->make_clickable($comment)));
  }
  $hiddenfields .= "<INPUT TYPE=\"hidden\" NAME=\"nr\" VALUE=\"$nr\">";
  if (!$pvp->config->enable_cookies) $hiddenfields .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='$sess_id'>";
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
    $labellist = "<SELECT NAME=\"labelconf\" onChange=\"mklabel(this.options[this.selectedIndex].value)\"><OPTION VALUE=\"-\">" . lang("print_label") . "</OPTION>";
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