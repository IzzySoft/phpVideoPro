<? /* Set filter(s) */

/* $Id$ */

  $page_id = "filter";
  include("inc/header.inc");
  // init templates
  $t = new Template($pvp->tpl_dir);
  $t->set_file(array("t_list"=>"setfilter_list.tpl",
                     "t_item"=>"setfilter_item.tpl",
//                     "tone_item"=>"setfilter_tone_item.tpl",
                     "tone_list"=>"setfilter_tone_list.tpl",
		     "t_input"=>"setfilter_item_input.tpl"));
  $t->set_block("tone_list","listblock","listlist");
  $t->set_block("listblock","itemblock","itemlist");

  ##############################################################################
  # create a dump of posted data for debugging purposes and send them to the
  # debug output function
  $ddump = "Saving data:<p>\n<ul>";
  while (list($key, $val) = each($HTTP_POST_VARS)) {
    $ddump .= "<li>$key => $val<br>";
  }
  $ddump .= "</ul></TD><TD>\n";
  debug("V",$ddump);

  if ($reset) { // user wants to unset all filter
    dbquery ("DELETE FROM preferences WHERE name='filter'");
  } elseif ($save) { // new filter values were submitted
    dbquery("SELECT id FROM mtypes");
    while ( $db->next_record() ) {
      $id    = $db->f('id');
      $field = "mtype_" . $id;
      if (${$field}) $filter->mtype->$id = TRUE;
    }
    $filter->length_min  = $length_min;
    $filter->length_max  = $length_max;
    $filter->aquired_min = $aquired_min;
    $filter->aquired_max = $aquired_max;
    dbquery("SELECT id FROM pict");
    while ( $db->next_record() ) {
      $id    = $db->f('id');
      $field = "pict_" . $id;
      if (${$field}) $filter->pict->$id = TRUE;
    }
    dbquery("SELECT id,name FROM colors");
    while ( $db->next_record() ) {
      $id    = $db->f('id');
      $field = "color_" . $id;
      if (${$field}) $filter->color->$id = TRUE;
    }
    dbquery("SELECT id,name FROM tone");
    while ( $db->next_record() ) {
      $id    = $db->f('id');
      $field = "tone_" . $id;
      if (${$field}) $filter->tone->$id = TRUE;
    }
    $filter->lp = $lp;
    $filter->fsk_min = $fsk_min;
    $filter->fsk_max = $fsk_max;
    $filter->title   = $title;
    for ($i=0;$i<count($cat_id);$i++) {
      $filter->cat->$cat_id[$i] = TRUE;
    }
    for ($i=0;$i<count($act_id);$i++) {
      $filter->actor->$act_id[$i] = TRUE;
    }
    for ($i=0;$i<count($dir_id);$i++) {
      $filter->director->$dir_id[$i] = TRUE;
    }
    for ($i=0;$i<count($mus_id);$i++) {
      $filter->composer->$mus_id[$i] = TRUE;
    }
    $save = rawurlencode( serialize($filter) );
    dbquery("SELECT value FROM preferences WHERE name='filter'");
    if ( $db->next_record() ) {
      dbquery("UPDATE preferences SET value='$save' WHERE name='filter'");
    } else {
      dbquery("INSERT INTO preferences (name,value) VALUES ('filter','$save')");
    }
  }

  dbquery("SELECT value FROM preferences WHERE name='filter'");
  if ( $db->next_record() ) { // there are already filters defined
    $filter = unserialize ( rawurldecode( $db->f('value') ) );
  }
  ########################################################################################
  # Create the Form Fields
  // ------------------------------------------------------------------[ left side ]------
  # mtype
    dbquery("SELECT id,sname FROM mtypes");
    $i=0;
    while ( $db->next_record() ) {
      $id[$i]   = $db->f('id');
      $name[$i] = $db->f('sname');
      if ($filter->mtype->$id) { $checked = " CHECKED"; } else { $checked = ""; }
      $i++;
    }
    $t->set_var("item","");
    for ($k=0;$k<count($id);$k++) {
      $t->set_var("input","<INPUT TYPE=\"checkbox\" NAME=\"mtype_" . $id[$k] . "$checked\">&nbsp;$name[$k]</TD>");
      $t->parse("item","t_input",TRUE);
    }
    $t->parse("mtype","t_item");

    # length
    $input = lang("min") . ":&nbsp;<INPUT NAME=\"length_min\"";
    if ( isset($filter->length_min) ) $input .= " VALUE=\"" . $filter->length_min . "\"";
    $input .= $form["addon_filmlen"] . ">";
    $t->set_var("input",$input);
    $t->parse("item","t_input");
    $input = lang("max") . ":&nbsp;<INPUT NAME=\"length_max\"";
    if ( isset($filter->length_max) ) $input .= " VALUE=\"" . $filter->length_max . "\"";
    $input .= $form["addon_filmlen"] . ">";
    $t->set_var("input",$input);
    $t->parse("item","t_input",TRUE);
    $t->parse("length","t_item");

    # date
    $addon = "SIZE=\"10\" MAXLENGTH=\"10\"";
    $input = lang("min") . ":&nbsp;<INPUT NAME=\"aquired_min\"";
    if ( isset($filter->aquired_min) ) $input .= " VALUE=\"" . $filter->aquired_min . "\"";
    $input .= "$addon>";
    $t->set_var("input",$input);
    $t->parse("item","t_input");
    $input = lang("max") . ":&nbsp;<INPUT NAME=\"aquired_max\"";
    if ( isset($filter->aquired_max) ) $input .= " VALUE=\"" . $filter->aquired_max . "\"";
    $input .= "$addon>";
    $t->set_var("input",$input);
    $t->parse("item","t_input",TRUE);
    $t->parse("date","t_item");

    # screen
    dbquery("SELECT id,name FROM pict");
    $i=0;
    while ( $db->next_record() ) {
      $id[$i]   = $db->f('id');
      $name[$i] = $db->f('name');
      $i++;
    }
    $t->set_var("item","");
    for ($k=0;$k<count($id);$k++) {
      if ($filter->pict->$id) { $checked = " CHECKED"; } else { $checked = ""; }
      $t->set_var("input","<INPUT TYPE=\"checkbox\" NAME=\"pict_" . $id[$k] . "\"$checked>&nbsp;$name[$k]");
      $t->parse("item","t_input",TRUE);
    }
    $t->parse("screen","t_item");

    # picture
    dbquery("SELECT id,name FROM colors");
    $i=0;
    while ( $db->next_record() ) {
      $id[$i]   = $db->f('id');
      $name[$i] = $db->f('name');
      $i++;
    }
    $t->set_var("item","");
    for ($k=0;$k<$i;$k++) {
      $input = "<INPUT TYPE=\"checkbox\" NAME=\"color_$id[$k]\"";
      if ($filter->color->$id[$k]) $input .= " CHECKED";
      $input .= ">&nbsp;" . lang("$name[$k]");
      $t->set_var("input",$input);
      $t->parse("item","t_input",TRUE);
    }
    $t->parse("picture","t_item");

    # tone
    dbquery("SELECT id,name FROM tone");
    $i=0;
    while ( $db->next_record() ) {
      $id[$i]   = $db->f('id');
      $name[$i] = $db->f('name');
      $i++;
    }
    $t->set_var("itemlist","");
    for ($i=0;$i<count($name);$i++) {
      $t->set_var("input",$name[$i]);
      $t->parse("itemlist","itemblock",TRUE);
    }
    $t->parse("listlist","listblock");
    $t->set_var("itemlist","");
    for ($i=0;$i<count($name);$i++) {
      $input = "<INPUT TYPE=\"checkbox\" NAME=\"tone_" . $id[$i] . "\"";
      if ($filter->tone->$id[$i]) $input .= " CHECKED";
      $input .= ">";
      $t->set_var("input",$input);
      $t->parse("itemlist","itemblock",TRUE);
    }
    $t->parse("listlist","listblock",TRUE);
    $t->parse("tone","tone_list");

    # longplay
    if ($filter->lp) { $checked = " CHECKED"; } else { $checked = ""; }
    $t->set_var("longplay","<INPUT TYPE=\"checkbox\" NAME=\"lp\"$checked>");

    # fsk
    $input = lang("min") . ":&nbsp;<INPUT NAME=\"fsk_min\"";
    if ( isset($filter->fsk_min) ) $input .= " VALUE=\"" . $filter->fsk_min . "\"";
    $input .= $form["addon_fsk"] . ">";
    $t->set_var("input",$input);
    $t->parse("item","t_input");
    $input = lang("max") . ":&nbsp;<INPUT NAME=\"fsk_max\"";
    if ( isset($filter->fsk_max) ) $input .= " VALUE=\"" . $filter->fsk_max . "\"";
    $input .= $form["addon_fsk"] . ">";
    $t->set_var("input",$input);
    $t->parse("item","t_input",TRUE);
    $t->parse("fsk","t_item");

  // -----------------------------------------------------------------[ right side ]------
    # title
    $input = "<INPUT NAME=\"title\"";
    if ( isset($filter->title) ) $input .= " VALUE=\"" . $filter->title . "\"";
    $input .= $form["addon_title"] . ">";
    $t->set_var("title",$input);

    # category
    dbquery("SELECT id,name FROM cat ORDER BY name");
    $option = "";
    while ( $db->next_record() ) {
      $id        = $db->f('id');
      $name      = $db->f('name');
      $option .= "<OPTION VALUE=\"$id\"";
      if ($filter->cat->$id) $option .= " SELECTED";
      $option .= ">$name</OPTION>";
    }
    $t->set_var("category","<SELECT NAME=\"cat_id[]\" SIZE=\"7\" MULTIPLE>$option</SELECT>");

    # actor
    dbquery("SELECT id,name,firstname FROM actors ORDER BY name");
    $option = "";
    while ( $db->next_record() ) {
      $id        = $db->f('id');
      $name      = $db->f('name');
      $firstname = $db->f('firstname');
      $option .= "<OPTION VALUE=\"$id\"";
      if ($filter->actor->$id) $option .= " SELECTED";
      $option .= ">$name, $firstname</OPTION>";
    }
    $t->set_var("actor","<SELECT NAME=\"act_id[]\" SIZE=\"7\" MULTIPLE>$option</SELECT>");

    # director
    dbquery("SELECT id,name,firstname FROM directors ORDER BY name");
    $option = "";
    while ( $db->next_record() ) {
      $id        = $db->f('id');
      $name      = $db->f('name');
      $firstname = $db->f('firstname');
      $option .= "<OPTION VALUE=\"$id\"";
      if ($filter->director->$id) $option .= " SELECTED";
      $option .= ">$name, $firstname</OPTION>";
    }
    $t->set_var("director","<SELECT NAME=\"dir_id[]\" SIZE=\"7\" MULTIPLE>$option</SELECT>");

    # composer
    dbquery("SELECT id,name,firstname FROM music ORDER BY name");
    $option = "";
    while ( $db->next_record() ) {
      $id        = $db->f('id');
      $name      = $db->f('name');
      $firstname = $db->f('firstname');
      $option .= "<OPTION VALUE=\"$id\"";
      if ($filter->composer->$id) $option .= " SELECTED";
      $option .= ">$name, $firstname</OPTION>";
    }
    $t->set_var("composer","<SELECT NAME=\"mus_id[]\" SIZE=\"7\" MULTIPLE>$option</SELECT>");

# build target
$t->set_var("form_target",$PHP_SELF);
$t->set_var("listtitle",lang("filter_setup"));
$t->set_var("mtype_name",lang("mediatype"));
$t->set_var("length_name",lang("length"));
$t->set_var("date_name",lang("date_rec"));
$t->set_var("screen_name",lang("screen"));
$t->set_var("picture_name",lang("picture"));
$t->set_var("tone_name",lang("tone"));
$t->set_var("longplay_name",lang("longplay"));
$t->set_var("fsk_name",lang("fsk"));
$t->set_var("title_name",lang("title"));
$t->set_var("category_name",lang("category"));
$t->set_var("actor_name",lang("actor"));
$t->set_var("director_name",lang("director"));
$t->set_var("composer_name",lang("composer"));
$t->pparse("out","t_list");

include("inc/footer.inc");
?>