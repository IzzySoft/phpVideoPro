<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2005 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Edit/View an entry                                                        #
 #############################################################################

 /* $Id$ */

 #=================================================[ Register global vars ]===
 $getit = array ("mtype_id","cass_id","part","nr");
 foreach ($getit as $var) {
   $$var = $_GET[$var];
 }
 unset($getit);
 while ( list($vn,$vv)=each($_POST) ) {
   $$vn = $vv;
 }
 if (!isset($new_entry)) $new_entry = FALSE;
 if (!isset($edit)) $edit = FALSE;
 if (!isset($update)) $update = FALSE;
 if (!isset($create)) $create = FALSE;

 #==========[ Initial setup: Target action (New|Edit|Delete or View only) ]===
 if (!$new_entry && !isset($_REQUEST["mtype_id"])) {
   header("Location: ".$base_url."index.php");
   exit;
 }
 if ($new_entry) {
   $page_id = "add_entry";
   $edit    = TRUE;
 } elseif ($edit) {
   $page_id = "edit";
 } elseif ($_POST["delete"]) {
   include("delete.php");
   exit;
 } else { $page_id = "view_entry"; }
 include("inc/includes.inc");

 #==================================================[ Check authorization ]===
 if ( ($new_entry && !$pvp->auth->add)
   || (!$new_entry && $edit && !$pvp->auth->update)
   || (!$new_entry && !$edit && !$pvp->auth->browse) ) {
   kickoff(); // kick-off unauthorized visitors
 }

 #===========================================[ JavaScript for IMDB LookUp ]===
 if ($edit) {
   $js = "<SCRIPT TYPE='text/javascript' LANGUAGE='JavaScript'>//<!--
   function lookup_imdb() {
     param = '';
     if (document.movieform.title.value != '') { param = '?name='+document.movieform.title.value; }
     url = '".$base_url."imdbsearch.php'+param;
     imdb=eval(\"window.open(url,'imdb','toolbar=no,location=no,titlebar=no,directories=no,status=yes,resizable=yes,scrollbars=yes,copyhistory=no,width=800,height=600')\");
   }
//--></SCRIPT>";
 }

 #=========================================================[ Helper Funcs ]===
 function vis_actors($num) {
   GLOBAL $edit,$vis_actor1,$vis_actor2,$vis_actor3,$vis_actor4,$vis_actor5;
   $visible = "vis_actor" . $num;
   if ($edit) {
     $output = "<INPUT TYPE='checkbox' NAME='vis_actor" . $num . "' VALUE='1' class='checkbox'";
     if (${$visible}) $output .= " CHECKED";
     $output .= ">";
   } else {
     $output = "<INPUT TYPE='button' NAME='" . ${$visible} . "' class='yesnobutton' VALUE='";
     if (${$visible}) { $output .= lang("yes") ."'>"; } else { $output .= lang("no") . "'>"; }
     $output .= "<INPUT TYPE='hidden' NAME='" . ${$visible} ."' VALUE='${$visible}'>";
   }
   return $output;
 }

 function vis_staff($name,$list) {
   GLOBAL $edit;
   $output  = "";
   if ($edit) {
     $output .= "<INPUT TYPE='checkbox' NAME='$name' VALUE='1' class='checkbox'";
     if ($list) $output .= " CHECKED";
     $output .= ">";
   } else {
     $output .= "<INPUT TYPE='button' NAME='$name' class='yesnobutton' VALUE='";
     if ($list) { $output .= lang("yes") . "'>"; } else { $output .= lang("no") . "'>"; }
     $output .= "<INPUT TYPE='hidden' NAME='$name' VALUE='$list'>";
   }
   return $output;
 }
  
 #===================================================[ some initial setup ]===
  if (!$nr) {
    while ( strlen($cass_id)<4 ) { $cass_id = "0" . $cass_id; }
    while ( strlen($part)<2)     { $part    = "0" . $part;    }
    $nr = $cass_id . "-" . $part;
#    $nr = $mediatype . " " . $cass_id . "-" . $part;
  }

  if ($edit) {
    $input = "INPUT SIZE='30'";
    $dinput = "INPUT";
    $mtypes = $db->get_mtypes();
    $ttypes = $db->get_tone();
    $cats   = $db->get_category("");
    $scolors = $db->get_color();
    for ($i=0;$i<count($scolors);$i++) {
     $scolors[$i]['name'] = lang($scolors[$i]['name']);
    }
    $picts = $db->get_pict();
    $commercials = $db->get_commercials();
    for ($i=0;$i<count($commercials);$i++) {
      $comm[$commercials[$i]['id']] = $commercials[$i]['name'];
      $comm_id[$i] = $commercials[$i]['id'];
    }
  } else {
    $input = $dinput = "INPUT TYPE='button'";
    // $input .= " readonly"; // HTML 4.0 - not supported by Netscape 4.x
  }

  function form_input($name,$value,$addons="") {
    GLOBAL $edit;
    if ($edit) {
      $type = " " . trim($addons) . " ";
    } else {
      if ( strlen(trim($value)) < 1 ) {
        $type = " TYPE='hidden' $addons";
      } else {
        $type = " TYPE='button' $addons";
      }
    }
    $field = "<INPUT" . $type . "NAME='$name' VALUE='$value'>";
    return $field;
  }
  
  function vform_input($name,$value,$maxchars,$vsize="") {
    GLOBAL $edit;
    if ($edit) {
      return "<INPUT SIZE='$maxchars' MAXLENGTH='$maxchars' NAME='$name' VALUE='$value'>";
    }
    if ($vsize) $width = $vsize; else $width = $maxchars*0.7."em";
    return "<DIV CLASS='virtual_button' STYLE='text-align:center;width:$width'>$value</DIV>";
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
	      "commercials","tone","tone_id","color","disktype","rc","audio","subtitle");
  foreach ($mdetails as $value) {
    $$value = $movie[$value];
  }
  $title = $pvp->common->string2input($movie['title']);
  $recdate = $movie['aq_date']; $src = $movie['source'];
  $vis_actor1 = $movie['actor1_list']; $vis_actor2 = $movie['actor2_list'];
  $vis_actor3 = $movie['actor3_list']; $vis_actor4 = $movie['actor4_list'];
  $vis_actor5 = $movie['actor5_list'];

  for ($i=1;$i<6;$i++) {
    $act_id  = "actor_$i";
    $actor[$i]['name']  = $pvp->common->string2input($movie[$act_id]['name']);
    $actor[$i]['fname'] = $pvp->common->string2input($movie[$act_id]['firstname']);
  }
  $director_name  = $pvp->common->string2input($movie['director_']['name']);
  $director_fname = $pvp->common->string2input($movie['director_']['firstname']);
  $composer_name  = $pvp->common->string2input($movie['music_']['name']);
  $composer_fname = $pvp->common->string2input($movie['music_']['firstname']);
  $pict_format = $movie['pict'];

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
  $mediatype = $mtypes[0]['sname']; $media_tname = $mtypes[0]['name'];
  ##########################################################################
  # set some useful defaults
  if ( empty($recdate) ) $recdate = $pvp->common->getRecDate("string");
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
?>
 <script TYPE="text/javascript" language="JavaScript"><!--
   function mklabel(labelconf) {
     if (labelconf != "-") {
       url = '<?=$base_url . "label.php?mtype_id=$mtype_id&cass_id=$cass_id&labelconf="?>' + labelconf;
       var pos = (screen.width/2)-400;
       campus  = eval("window.open(url,'label','toolbar=yes,location=no,titlebar=no,directories=no,status=yes,resizable=no,scrollbars=yes,copyhistory=no,width=800,height=600,top=0,left=" + pos + "')");
     }
   }
 //-->
 </script>
<?
  $t = new Template($pvp->tpl_dir);
  $t->set_file(array("edit"=>"edit.tpl"));
  $t->set_var("form_name","movieform");
  $t->set_var("form_target",$_SERVER["PHP_SELF"]);
  switch ( strtolower($page_id) ) {
    case "edit"      : $t->set_var("listtitle",lang("edit_entry",$movie['mtype_short']." ".$nr)); break;
    case "view_entry"      : $t->set_var("listtitle",lang("view_entry",$movie['mtype_short']." ".$nr)); break;
    case "add_entry" : $t->set_var("listtitle",lang("add_entry")); break;
    default          : break;
  }
  if (!isset($save_result)) $save_result = "";
  $t->set_var("save_result",$save_result);
  $t->set_block("edit","actorblock","actorlist");

  // actors block
  for ($i=1;$i<=$max["actors"];$i++) {
    $name = "actor" . $i . "_name"; $fname = "actor" . $i . "_fname";
    if ($page_id == "view_entry") { // set imdb info url for actor
      $formAddon = $form["addon_name"]." CLASS='namebutton'" . $pvp->link->formImdbPerson($actor[$i]['fname'],$actor[$i]['name'],"actors");
    } else { $formAddon = $form["addon_name"]." CLASS='nameinput'"; }
    if ($i==1) {
      $t->set_var("actor_name",lang("actors"));
    } else {
      $t->set_var("actor_name","&nbsp;");
    }
    if ( $edit || strlen($actor[$i]['name'] . $actor[$i]['fname']) ) {
      if ($new_entry) {
        $t->set_var("actor",form_input($name,"",$formAddon));
        $t->set_var("actor_f",form_input($fname,"",$formAddon));
      } else {
        $t->set_var("actor",form_input($name,$actor[$i]['name'],$formAddon));
        $t->set_var("actor_f",form_input($fname,$actor[$i]['fname'],$formAddon));
      }
      $t->set_var("actor_list",vis_actors($i));
    } else {
      $visible = "vis_actor" . $i;
      $t->set_var("actor",form_input($name,"&nbsp;",$formAddon));
      $t->set_var("actor_f",form_input($fname,"&nbsp;",$formAddon));
      $t->set_var("actor_list","<INPUT TYPE='button' NAME='" . ${$visible} . "' class='yesnobutton' VALUE='&nbsp;'");
    }
    if ($i>1) $t->parse("actorlist","actorblock",TRUE);
      else  $t->parse("actorlist","actorblock");
  }

  // main block
  #---[ Obtain disktype data ]---
  $mdisktype = $db->get_disktypes($mtype_id);
  $dtcount = 0;
  if ($new_entry) {
    $tdisktype = $db->disktypeGetForMedia($mtype_id,$cass_id);
    $disktype = $tdisktype->type;
    $rc = $tdisktype->rc;
    unset($tdisktype);
  }
  if (!empty($disktype)) {
    $disktypes = $db->get_disktypes($mtype_id,$disktype);
    $dtcount   = count($disktypes);
  } elseif ($edit) {
    $disktypes = $mdisktype;
    $dtcount   = count($disktypes);
  }
  
  #---[ navigation and title ]---
  if ($page_id == "view_entry") {
    $tpl_dir = str_replace($base_path,$base_url,$pvp->tpl_dir);
    if ($movie['previous']) {
      $lm = $db->get_firstmovienum(); $lmc = count($lm); $i=0;
      while ( ($lm[$i]["cass_id"]==0) && ($i < $lmc) ) {
        ++$i;
      } 
      $prev = "<A HREF='" .$pvp->link->slink($_SERVER["PHP_SELF"]."?mtype_id=".$lm[$i]["mtype_id"]
            . "&cass_id=".(int) $lm[$i]["cass_id"]."&part=".(int) $lm[$i]["part"])
            . "'><IMG SRC='".$tpl_dir."/images/first.gif' BORDER='0' ALT='&lt;&lt;'></A>";
      $prev .= "<A HREF='" .$pvp->link->slink($_SERVER["PHP_SELF"]."?mtype_id=".$movie['previous']->mtype_id
            . "&cass_id=".$movie['previous']->media_nr."&part=".$movie['previous']->part)
	    . "'><IMG SRC='".$tpl_dir."/images/left.gif' BORDER='0' ALT='&lt;'></A>";
    } else {
      $prev = "<IMG SRC='".$tpl_dir."/images/first-grey.gif' ALT=''>"
            . "<IMG SRC='".$tpl_dir."/images/left-grey.gif' ALT=''>";
    }
    $t->set_var("previous",$prev); unset($prev);
    if ($movie['next']) {
      $next = "<A HREF='" .$pvp->link->slink($_SERVER["PHP_SELF"]."?mtype_id=".$movie['next']->mtype_id
            . "&cass_id=".$movie['next']->media_nr."&part=".$movie['next']->part)
            . "'><IMG SRC='".$tpl_dir."/images/right.gif' BORDER='0' ALT='&gt;'></A>";
      $lm = $db->get_lastmovienum(); $lmc = count($lm);
      do {
        --$lmc;
      } while ( ($lm[$lmc]["cass_id"]==0) && ($lmc != 0) );
      $next .= "<A HREF='" .$pvp->link->slink($_SERVER["PHP_SELF"]."?mtype_id=".$lm[$lmc]["mtype_id"]
            . "&cass_id=".(int) $lm[$lmc]["cass_id"]."&part=".(int) $lm[$lmc]["part"])
            . "'><IMG SRC='".$tpl_dir."/images/last.gif' BORDER='0' ALT='&gt;&gt;'></A>";
    } else {
      $next = "<IMG SRC='".$tpl_dir."/images/right-grey.gif' ALT=''>"
            . "<IMG SRC='".$tpl_dir."/images/last-grey.gif' ALT=''>";
    }
    $t->set_var("next",$next); unset($next,$lm,$lmc);
  }
  if (isset($_SERVER["HTTP_REFERER"])) $referer = $_SERVER["HTTP_REFERER"];
    else $referer = "";
  $hiddenfields = <<<EndHiddenFields
<INPUT TYPE="hidden" NAME="cass_id" VALUE="$cass_id">
<INPUT TYPE="hidden" NAME="mtype_id" VALUE="$mtype_id">
<INPUT TYPE="hidden" NAME="referer" VALUE="$referer">
EndHiddenFields;
  if (!$new_entry) {
    $hiddenfields .= "\n<INPUT TYPE='hidden' NAME='part' VALUE='$part'>";
  }
  if ($page_id == "view_entry") { // set imdb info url for title
    $formAddon = $form["addon_title"]." CLASS='titlebutton'" . $pvp->link->formImdbTitle($title);
  } else {
    $formAddon = $form["addon_title"];
  }
  if (!isset($title)) $title = "";
  $mtitle = "<$dinput NAME='title' VALUE='$title' " . $formAddon . ">";
  $t->set_var("title",$mtitle);
  if ($edit) {
    $t->set_var("imdb","<IMG SRC='".$base_url."images/imdb_link.gif' BORDER='0' ALT='IMDB Lookup' onClick='lookup_imdb()' ALIGN='middle'>");
    $t->set_var("js",$js);
  }
  #---[ media data ]---
  $t->set_var("mtype_name",lang("mediatype"));
  if ($mdisktype[0]->rc) {
    $t->set_var("rc_name",lang("region_code"));
    if ($agent->name=="konqueror") $t->set_var("konq_fix"," STYLE='padding-right:10'");
    if ($new_entry && !$disktype) { // editable only for new DVDs
      $rcname = "";
      for ($i=0;$i<7;++$i) {
        $rcname .= "<INPUT TYPE='checkbox' NAME='rc[]' VALUE='$i' CLASS='checkbox'";
        if (isset($rc[$i]) && $rc[$i]) $rcname .= " CHECKED";
        $rcname .= ">&nbsp;$i";
        if ($i<6) $rcname .= "&nbsp;";
      }
    } else {
      if ( is_array($rc) ) {
        $rcname = "";
        for ($i=0;$i<7;++$i) {
          if (isset($rc[$i]) && $rc[$i]) $rcname .= "<INPUT TYPE='button' NAME='rc' VALUE='$i' CLASS='yesnobutton' onClick=\"window.location.href='change_rc.php?mtype_id=$mtype_id&cass_id=$cass_id&part=$part'\">";
        }
      }
      if (!isset($rcname)) $rcname = "";
      if (!$rcname) $rcname  = "<INPUT TYPE='button' NAME='rc' VALUE='".lang("unknown")."' CLASS='techbutton' onClick=\"window.location.href='change_rc.php?mtype_id=$mtype_id&cass_id=$cass_id&part=$part'\">";
    }
    $t->set_var("rc",$rcname);
  }
  if ($new_entry) {
    $field  = "<INPUT TYPE='button' NAME='media_tname' VALUE='$media_tname' CLASS='catbutton'>";
    $field .= "<INPUT TYPE='hidden' NAME='mtype_id' VALUE='$mtype_id'>";
    $last_part = $db->get_lastmovienum($mtype_id,$cass_id);
    $next_part = $last_part +1;
  } else {
    $field = "<DIV CLASS='virtual_button' STYLE='text-align:center;width:".CAT_BTN_WID."'>$media_tname</DIV>";
    $field .= "<INPUT TYPE='hidden' NAME='media_tname' VALUE='$media_tname'>";
  }
  $t->set_var("mtype",$field);
  $t->set_var("country_name",lang("country"));
  if(!isset($country)) $country = "";
  if ($edit) {
    $field = form_input("country",$country,$form["addon_country"]." CLASS='catinput'");
  } else {
    if (!$country) $country = lang("unknown");
    $field = vform_input("country",$country,COUNTRY_LEN,CAT_BTN_WID);
  }
  $t->set_var("country",$field);
  $t->set_var("medianr_name",lang("medianr"));
  if ($new_entry) {
    $field  = "<INPUT TYPE='button' NAME='cass_id' VALUE='$cass_id' " . $form["addon_cass_id"]." CLASS='medianrbutton'" . ">&nbsp;-&nbsp;<INPUT NAME='part' VALUE='$next_part' " . $form["addon_part"]." CLASS='partinput'" . ">";
    $field .= "&nbsp;&nbsp;&nbsp;" . lang("last_entry") . ":&nbsp;";
    $field .= "<INPUT TYPE='button' NAME='lastnum' VALUE='$last_part' CLASS='yesnobutton'>";
  } else {
    $field = "<INPUT TYPE='button' NAME='nr' VALUE='$nr' CLASS='medianrbutton' onClick=\"window.location.href='" .$pvp->link->slink("change_nr.php?id=$id") ."'\"><INPUT TYPE='hidden' NAME='nr' VALUE='$nr'>";
  }
  $t->set_var("medianr",$field);
  $t->set_var("year_name",lang("year"));
  if (!isset($year)) $year = "";
  if ($edit) {
    $field = form_input("year",$year,$form["addon_year"]." CLASS='yesnoinput'");
  } else {
    if (!$year) $year="&nbsp;";
    $field = vform_input("year",$year,4);
  }
  $t->set_var("year",$field);
  $t->set_var("length_name",lang("length"));
  if (!isset($length)) $length = "";
  if ($edit)
    $t->set_var("length",form_input("length",$length,$form["addon_filmlen"]." CLASS='yesnoinput'") . " " . lang("min"));
  else
    $t->set_var("length",vform_input("length","$length ".lang("min"),MOVIELEN_LEN+4));
  if ((isset($disktype[0]) && $disktype[0]->lp) || !$dtcount) {
    $t->set_var("longplay_name",lang("longplay"));
    if ($edit) { 
      $field = "<INPUT NAME='lp' TYPE='checkbox' VALUE='1' class='checkbox'";
      if ($lp) $field .= " CHECKED";
      $field .= ">";
    } else {
      if ($lp) $lp = lang("yes"); else $lp = lang("no");
      $field = vform_input("lp",$lp,"",YN_WIDTH);
    }
  } else {
    $t->set_var("longplay_name","");
    $field = "<INPUT TYPE='hidden' NAME='lp' VALUE='0'>";
  }
  $t->set_var("longplay",$field);
  #---[ Counter settings ]---
  if ($dtcount) {
    $t->set_var("counter_name",lang("disk_type"));
    if ($new_entry && empty($disktype)) {
      $dt = "<SELECT NAME='disktype' CLASS='techinput'>";
      for ($i=0;$i<$dtcount;++$i) {
        $dt .= "<OPTION VALUE='" .$disktypes[$i]->id ."'";
        if (isset($disktype) && $disktype==$disktypes[$i]->id) $dt .= " SELECTED";
        $dt .= ">" .$disktypes[$i]->name;
        if ($disktypes[$i]->size) $dt.= " (" .$disktypes[$i]->size. ")";
        $dt .= "</OPTION>";
      }
      $dt .= "</SELECT>";
    } else {
      $dttext = $disktypes[0]->name;
      if ($disktypes[0]->size) $dttext .= " (" .$disktypes[0]->size. ")";
      $dt = "<INPUT TYPE='button' NAME='disktype' VALUE='$dttext' CLASS='techbutton' onClick=\"window.location.href='" .$pvp->link->slink("change_disktype.php?mtype_id=$mtype_id&cass_id=$cass_id&part=$part"). "'\">";
    }
    $t->set_var("counter",$dt);
  } else {
    $field = "<DIV STYLE='margin-top:1px'>";
    if (!$edit) {
      if (empty($counter1)) $counter1 = "<font face='monospace'>&nbsp;&nbsp;&nbsp;&nbsp;</font>";
      if (empty($counter2)) $counter2 = "<font face='monospace'>&nbsp;&nbsp;&nbsp;&nbsp;</font>";
      $field .= "<SPAN CLASS='virtual_button' STYLE='text-align:center;width:".YN_WIDTH."'>$counter1</SPAN>"
             . " / <SPAN CLASS='virtual_button' STYLE='text-align:center;width:".YN_WIDTH."'>$counter2</SPAN>";
    } else {
      $field .= form_input("counter1",$counter1,"class='yesnoinput'") . " / "
             . form_input("counter2",$counter2,"class='yesnoinput'");
    }
    $field .= "</DIV>";
    $t->set_var("counter_name",lang("counter_start_stop"));
    $t->set_var("counter",$field);
  }

  # Label
  if ($new_entry) $label = $pvp->preferences->get("default_movie_onlabel");
  $t->set_var("label_name",lang("label"));
  $field = "<INPUT NAME='label'";
  if ($edit) { 
    $field .= " TYPE='checkbox' VALUE='1' class='checkbox'";
    if ($label) $field .= " CHECKED";
    $field .= ">";
  } else {
    if ($label) $f = lang("yes"); else $f = lang("no");
    $field = vform_input("label",$f,"",YN_WIDTH);
  }
  $t->set_var("label",$field);

  # Categories
  $t->set_var("category_name",lang("categories"));
  $field = "";
  for ($i=1;$i<=$max["categories"];$i++) {
   if ($edit) {
    $field .= "<SELECT NAME='cat" . $i . "_id' class='catinput'>";
    if ($i > 1) $field .= "<OPTION VALUE='-1'>- ".lang("none")." -</OPTION>";
    for ($k=0;$k<count($cats);$k++) {
      if ($cats[$k]['enabled']) {
        $field .= "<OPTION VALUE='" . $cats[$k]['id'] . "'";
        if (isset($cat) && $cats[$k]['name']==$cat[$i]) $field .= " SELECTED";
        $field .= ">" . $cats[$k]['name'] . " </OPTION>";
      }
    }
    $field .= "</SELECT>";
    if ( $i<$max["categories"] ) $field .= "<BR>";
   } else {
    if ( trim($cat[$i])=="" ) $f = "- ".lang("none")." -"; else $f = $cat[$i];
    if (!(($i>1) && ($f=="- ".lang("none")." -")))
      $field .= vform_input("cat".$i,$f,"",CAT_BTN_WID);
   }
  }
  $t->set_var("category",$field);

  # Commercials
  $t->set_var("commercial_name",lang("commercials"));
  if ($edit) {
    $field = "<SELECT NAME='commercials_id' class='techinput'>";
    for ($k=0;$k<count($comm);$k++) {
      $field .= "<OPTION VALUE='$comm_id[$k]'";
      if ($commercials==$comm[$k]) $field .= " SELECTED";
      $field .= ">" . $comm[$k] . " </OPTION>";
    }
    $field .= "</SELECT>";
  } else {
    $field = vform_input("commercials",$commercials,"",TECH_BTN_WID);
  }
  $t->set_var("commercial",$field);

  # Remaining free time
  if ($new_entry) {
    $t->set_var("mlength_free_name",lang("medialength"));
    $t->set_var("mlength_free","<INPUT NAME='mlength' VALUE='240' " . $form["addon_filmlen"]." CLASS='yesnoinput'" . "> " . lang("minute_abbrev"));
  } else { // hide free time for non-editable media
    if ($pvp->common->medium_is_rw($mtype_id)) {
      $t->set_var("mlength_free_name",lang("free"));
      $t->set_var("mlength_free","<INPUT TYPE='button' NAME='free' VALUE='$free' CLASS='yesnobutton' onClick=\"window.location.href='" .$pvp->link->slink("medialength.php?cass_id=$cass_id&mtype_id=$mtype_id"). "'\"> " . lang("minute_abbrev"));
    } else {
      $t->set_var("mlength_free_name","&nbsp;");
      $t->set_var("mlength_free","&nbsp;");
    }
  }
  
  # Date
  $t->set_var("date_name",lang("date_rec"));
  if ($recdate == lang("unknown")) {
    $tdate = vform_input("recdate",$recdate,"",TECH_BTN_WID);
  } else {
    $tdate = "";
    if ($edit) {
      $recdate_arr = $pvp->common->makeRecDateArr($recdate);
      $tdate .= "<$dinput NAME='recday' VALUE='" . $recdate_arr['mday'] . "' " . $form["addon_day"]." CLASS='partinput'" . ">.";
      $tdate .= "<$dinput NAME='recmon' VALUE='" . $recdate_arr['mon'] . "' " . $form["addon_month"]." CLASS='partinput'" . ">.";
      $tdate .= "<$dinput NAME='recyear' VALUE='" . $recdate_arr['year'] . "' " . $form["addon_year"]." CLASS='yesnoinput'" . ">";
    } else {
      $recdate = $pvp->common->formatDate($recdate);
      $tdate = vform_input("recdate",$recdate,"",TECH_BTN_WID);
    }
  }
  $t->set_var("date",$tdate);

  # Tone Format
  $t->set_var("tone_name",lang("tone"));
  if ($new_entry) $tone_id = $pvp->preferences->get("default_movie_toneid");
  if ($edit) {
    $field = "<SELECT NAME='tone_id'" . $form["addon_tech"] . ">";
    for ($i=0;$i<count($ttypes);$i++) {
      $field .= "<OPTION VALUE='" . $ttypes[$i]['id'] . "'";
      if ($ttypes[$i]['id']==$tone_id) $field .=  "SELECTED";
      $field .= ">" . $ttypes[$i]['name'] . " </OPTION>";
    }
    $field .= "</SELECT>";
  } else {
    $field = vform_input("tone",$tone,"",TECH_BTN_WID);
  }
  $t->set_var("tone",$field);
  $t->set_var("picture_name",lang("picture"));
  if ($edit) {
    $field = "<SELECT NAME='color_id'" . $form["addon_tech"] . ">";
    for ($i=0;$i<count($scolors);$i++) {
      $field .= "<OPTION VALUE='" . $scolors[$i]['id'] . "'";
      if ((isset($color) && $scolors[$i]['name']==$color) || ($new_entry && $scolors[$i]['id']==$defaults["scolor"]) ) $field .= " SELECTED";
      $field .= ">" . $scolors[$i]['name'] . " </OPTION>";
    }
    $field .= "</SELECT>";
  } else {
    $field = vform_input("color",$color,"",TECH_BTN_WID);
  }
  $t->set_var("picture",$field);
  $t->set_var("screen_name",lang("screen"));
  if ($new_entry) $pict_id = $pvp->preferences->get("default_movie_pictid");
  if ($edit) {
    $field = "<SELECT NAME='pict_id'" . $form["addon_tech"] . "><OPTION VALUE='-1'>" . lang("unknown") . "</OPTION>";
    for ($i=0;$i<count($picts);$i++) {
      $field .= "<OPTION VALUE='" . $picts[$i]['id'] . "'";
      if ($new_entry && $picts[$i]['id']==$pict_id) $field .= " SELECTED";
      if (isset($pict_format) && $picts[$i]['name']==$pict_format) $field .=  " SELECTED";
      $field .= ">" . $picts[$i]['name'] . " </OPTION>";
    }
    $field .= "</SELECT>";
  } else {
    if (!$pict_format) $pict_format = "unknown";
    $field = vform_input("pict_format",$pict_format,"",TECH_BTN_WID);
  }
  $t->set_var("screen",$field);
  $t->set_var("source_name",lang("source"));
  if (!isset($src)) $src = "";
  if ($edit) {
    $t->set_var("source",form_input("src",$src,$form["addon_src"]));
  } elseif (strlen(trim($src)) || $edit) {
    $t->set_var("source",vform_input("src",$src,SRC_LEN,TECH_BTN_WID));
  } else {
    $t->set_var("source",vform_input("dummy",lang("unknown"),SRC_LEN,TECH_BTN_WID));
  }
  $t->set_var("fsk_name",lang("fsk"));
  if (!isset($fsk)) $fsk = "";
  if ($edit) {
    $t->set_var("fsk",form_input("fsk",$fsk,$form["addon_fsk"]." CLASS='partinput'"));
  } else {
    if (!$fsk) $fsk="&nbsp;";
    $t->set_var("fsk",vform_input("fsk",$fsk,FSK_LEN));
  }
  #---[ Audio & Subtitles ]--
  $t->set_var("audio_name",lang("audio_ts"));
  $t->set_var("subtitle_name",lang("subtitle"));
  if ($edit) {
    $audio_langs = $db->get_avlang("audio");
    $audio_ts = "";
    if ($new_entry) $lang_id = $pvp->preferences->get("default_movie_langid");
    for ($i=0;$i<AUDIO_TS;++$i) {
      $atsname = "audio_ts".$i;
      $audio_ts .= "<SELECT NAME='$atsname' CLASS='techinput'><OPTION VALUE='-'>-</OPTION>";
      for ($k=0;$k<count($audio_langs);$k++) {
        $audio_ts .= "<OPTION VALUE='".$audio_langs[$k]->id."'";
        if ($i==0 && $new_entry && $lang_id==$audio_langs[$k]->id) $audio_ts .= " SELECTED";
        if ( isset($audio[$i]) && $audio_langs[$k]->id == $audio[$i] ) $audio_ts .= " SELECTED";
        $audio_ts .= ">".$audio_langs[$k]->name."</OPTION>";
      }
      $audio_ts .= "</SELECT>";
      if ( $agent->name=="msie" && !(($i+1)%3) ) $audio_ts .= "<BR>"; // work around IE bug
    }
    $t->set_var("audio",$audio_ts);
    $audio_langs = $db->get_avlang("subtitle");
    $sub_ts = "";
    for ($i=0;$i<SUBTITLES;++$i) {
      $atsname = "subtitle".$i;
      $sub_ts .= "<SELECT NAME='$atsname' CLASS='techinput'><OPTION VALUE='-'>-</OPTION>";
      for ($k=0;$k<count($audio_langs);$k++) {
        $sub_ts .= "<OPTION VALUE='".$audio_langs[$k]->id."'";
        if ( isset($subtitle[$i]) && $audio_langs[$k]->id == $subtitle[$i] ) $sub_ts .= " SELECTED";
        $sub_ts .= ">".$audio_langs[$k]->name."</OPTION>";
      }
      $sub_ts .= "</SELECT>";
      if ( $agent->name=="msie" && !(($i+1)%3) ) $sub_ts .= "<BR>"; // work around IE bug
    }
    $t->set_var("subtitle",$sub_ts);
  } else { // !$edit
    $audio_ts = "";
    for ($i=0;$i<count($audio);++$i) {
      if (isset($audio[$i]) && !empty($audio[$i])) $audio_ts .= ", ".lang("lang_".$audio[$i]);
    }
    $sub_ts = "";
    for ($i=0;$i<count($subtitle);++$i) {
      if (isset($subtitle[$i]) && !empty($subtitle[$i])) $sub_ts .= ", ".lang("lang_".$subtitle[$i]);
    }
    if (isset($audio_ts) && !empty($audio_ts)) $audio_ts = substr($audio_ts,2);
      else $audio_ts = "&nbsp;";
    if (isset($sub_ts) && !empty($sub_ts)) $sub_ts = substr($sub_ts,2);
      else $sub_ts = "&nbsp;";
    $t->set_var("audio","<DIV CLASS='virtual_button'>$audio_ts</DIV>");
    $t->set_var("subtitle","<DIV CLASS='virtual_button'>$sub_ts</DIV>");
  }
  $t->set_var("staff_name",lang("staff"));
  $t->set_var("name_name",lang("name"));
  $t->set_var("firstname_name",lang("first_name"));
  $t->set_var("inlist_name",lang("in_list"));
  $t->set_var("director_name",lang("director"));
  if ($page_id == "view_entry") {
    $formAddon = $form["addon_name"]." CLASS='namebutton'" . $pvp->link->formImdbPerson($director_fname,$director_name,"directors");
  } else { $formAddon = $form["addon_name"]." CLASS='nameinput'"; }
  if ( $edit || strlen($director_name . $director_fname) ) {
    if ($new_entry) {
      $t->set_var("director",form_input("director_name","",$formAddon));
      $t->set_var("director_f",form_input("director_fname","",$formAddon));
      $director_list = "";
    } else {
      $t->set_var("director",form_input("director_name",$director_name,$formAddon));
      $t->set_var("director_f",form_input("director_fname",$director_fname,$formAddon));
    }
    $t->set_var("director_list",vis_staff('director_list',$director_list));
  } else {
    $t->set_var("director",form_input("director_name","&nbsp;",$formAddon));
    $t->set_var("director_f",form_input("director_fname","&nbsp;",$formAddon));
    $t->set_var("director_list","<INPUT TYPE='button' NAME='director_list' class='yesnobutton' VALUE='&nbsp;'");
  }
  $t->set_var("composer_name",lang("composer"));
  if ($page_id == "view_entry") {
    $formAddon = $form["addon_name"]." CLASS='namebutton'" . $pvp->link->formImdbPerson($composer_fname,$composer_name,"composers");
  }
  if ( $edit || strlen($composer_name . $composer_fname) ) {
    if ($new_entry) {
      $t->set_var("composer",form_input("composer_name","",$formAddon));
      $t->set_var("composer_f",form_input("composer_fname","",$formAddon));
      $music_list = "";
    } else {
      $t->set_var("composer",form_input("composer_name",$composer_name,$formAddon));
      $t->set_var("composer_f",form_input("composer_fname",$composer_fname,$formAddon));
    }
    $t->set_var("composer_list",vis_staff('music_list',$music_list));
  } else {
    $t->set_var("composer",form_input("composer_name","&nbsp;",$formAddon));
    $t->set_var("composer_f",form_input("composer_fname","&nbsp;",$formAddon));
    $t->set_var("composer_list","<INPUT TYPE='button' NAME='music_list' class='yesnobutton' VALUE='&nbsp;'");
  }
  // actors are set up on top, in the "actors block"
  $t->set_var("comments_name",lang("comments"));
  if (!isset($comment)) $comment = "";
  if ($edit) {
    $t->set_var("comments","<DIV ALIGN=CENTER><TEXTAREA ROWS='5' COLS='120' NAME='comment'>$comment</TEXTAREA></DIV>");
  } else {
    $t->set_var("comments",$pvp->common->nl2br($comment));
  }
  $hiddenfields .= "<INPUT TYPE='hidden' NAME='nr' VALUE='$nr'>";
  if (!$pvp->cookie->active) $hiddenfields .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>";
  $t->set_var("hiddenfields",$hiddenfields);
  if ($new_entry) {
    $t->set_var("button_li","<INPUT CLASS='submit' TYPE='submit' NAME='cancel' VALUE='" . lang("cancel") . "'>");
    $t->set_var("button_re","<INPUT CLASS='submit' TYPE='submit' NAME='create' VALUE='" . lang("create") . "'>");
    $t->set_var("print_label","&nbsp;");
  } elseif ($edit) {
    $t->set_var("button_li","<INPUT CLASS='submit' TYPE='submit' NAME='cancel' VALUE='" . lang("cancel") . "'>");
    $t->set_var("button_re","<INPUT CLASS='submit' TYPE='submit' NAME='update' VALUE='" . lang("update") . "'>");
    $t->set_var("print_label","&nbsp;");
  } else {
    $labels = $pvp->common->get_filenames($base_path . "labels",".config");
    $labellist = "<SELECT NAME='labelconf' onChange='mklabel(this.options[this.selectedIndex].value)'><OPTION VALUE='-'>" . lang("print_label") . "</OPTION>";
    for ($i=0;$i<count($labels);$i++) {
      $confname = substr($labels[$i],0,strlen($labels[$i]) - 7);
      $labellist .= "<OPTION VALUE='$confname'>" . ucwords(str_replace("_"," ",$confname)) . "</OPTION>";
    }
    $labellist .= "</SELECT>";
    $t->set_var("button_li","<INPUT CLASS='submit' TYPE='submit' NAME='edit' VALUE='"   . lang("edit")   . "'>");
    $t->set_var("button_re","<INPUT CLASS='submit' TYPE='submit' NAME='delete' VALUE='" . lang("delete") . "'>");
    $t->set_var("print_label","$labellist");
  }
  $t->pparse("out","edit");

  include("inc/footer.inc");

?>