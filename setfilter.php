<? /* Set filter(s) */

/* $Id$ */

  $page_id = "filter";
  include("inc/config.inc");
  include("inc/header.inc");

  echo "<H2 Align=Center>Filter Setup</H2>\n\n";

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
    $save = serialize($filter);
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
  function mtype() {
    GLOBAL $filter, $db;
    dbquery("SELECT id,sname FROM mtypes");
    echo "<TABLE WIDTH=\"100%\" BORDER=\"0\"><TR>";
    while ( $db->next_record() ) {
      $id   = $db->f('id');
      $name = $db->f('sname');
      echo "<TD><INPUT TYPE=\"checkbox\" NAME=\"mtype_$id\"";
      if ($filter->mtype->$id) echo " CHECKED";
      echo ">&nbsp;$name</TD>";
    }
    echo "</TD></TABLE>";
  }
  function length() {
    GLOBAL $filter, $db, $form;
    echo "<TABLE WIDTH=\"100%\" BORDER=\"0\"><TR>";
    echo "<TD>min:&nbsp;<INPUT NAME=\"length_min\"";
    if ( isset($filter->length_min) ) echo " VALUE=\"" . $filter->length_min . "\"";
    echo $form["addon_filmlen"] . "></TD><TD>max:&nbsp;<INPUT NAME=\"length_max\"";
    if ( isset($filter->length_max) ) echo " VALUE=\"" . $filter->length_max . "\"";
    echo $form["addon_filmlen"] . "></TD></TR></TABLE>";
  }
  function aquired() {
    GLOBAL $filter, $db;
    $addon = "SIZE=\"10\" MAXLENGTH=\"10\"";
    echo "<TABLE WIDTH=\"100%\" BORDER=\"0\"><TR>";
    echo "<TD>min:&nbsp;<INPUT NAME=\"aquired_min\"";
    if ( isset($filter->aquired_min) ) echo " VALUE=\"" . $filter->aquired_min . "\"";
    echo "$addon></TD><TD>max:&nbsp;<INPUT NAME=\"aquired_max\"";
    if ( isset($filter->aquired_max) ) echo " VALUE=\"" . $filter->aquired_max . "\"";
    echo "$addon></TD></TR></TABLE>";
  }
  function screen() {
    GLOBAL $filter, $db;
    echo "<TABLE WIDTH=\"100%\" BORDER=\"0\"><TR>";
    dbquery("SELECT id,name FROM pict");
    while ( $db->next_record() ) {
      $id   = $db->f('id');
      $name = $db->f('name');
      echo "<TD><INPUT TYPE=\"checkbox\" NAME=\"pict_$id\"";
      if ($filter->pict->$id) echo " CHECKED";
      echo ">&nbsp;$name</TD>";
    }
    echo "</TR></TABLE>";
  }
  function picture() {
    GLOBAL $filter, $db;
    echo "<TABLE WIDTH=\"100%\" BORDER=\"0\"><TR>";
    dbquery("SELECT id,name FROM colors");
    while ( $db->next_record() ) {
      $id   = $db->f('id');
      $name = $db->f('name');
      echo "<TD><INPUT TYPE=\"checkbox\" NAME=\"color_$id\"";
      if ($filter->color->$id) echo " CHECKED";
      echo ">&nbsp;$name</TD>";
    }
    echo "</TR></TABLE>";
  }
  function tone() {
    GLOBAL $filter, $db;
    echo "<TABLE WIDTH=\"100%\" BORDER=\"0\"><TR>";
    dbquery("SELECT id,name FROM tone");
    $i=0;
    while ( $db->next_record() ) {
      $id[$i]   = $db->f('id');
      $name[$i] = $db->f('name');
      echo "<TD ALIGN=\"center\">" . $name[$i] . "</TD>";
      $i++;
    }
    echo "</TR><TR>";
    for ($i=0;$i<count($name);$i++) {
      echo "<TD ALIGN=\"center\"><INPUT TYPE=\"checkbox\" NAME=\"tone_" . $id[$i] . "\"";
      if ($filter->tone->$id[$i]) echo " CHECKED";
      echo "></TD>";
    }
    echo "</TR></TABLE>";
  }
  function longplay() {
    GLOBAL $filter, $db;
    echo "<INPUT TYPE=\"checkbox\" NAME=\"lp\"";
    if ($filter->lp) echo " CHECKED";
    echo ">";
  }
  function fsk() {
    GLOBAL $filter, $db, $form;
    echo "<TABLE WIDTH=\"100%\" BORDER=\"0\"><TR>";
    echo "<TD>min:&nbsp;<INPUT NAME=\"fsk_min\"";
    if ( isset($filter->fsk_min) ) echo " VALUE=\"" . $filter->fsk_min . "\"";
    echo $form["addon_fsk"] . "></TD>";
    echo "<TD>max:&nbsp;<INPUT NAME=\"fsk_max\"";
    if ( isset($filter->fsk_max) ) echo " VALUE=\"" . $filter->fsk_max . "\"";
    echo $form["addon_fsk"] . "></TD>";
    echo "</TR></TABLE>";
  }
  // -----------------------------------------------------------------[ right side ]------
  function title() {
    GLOBAL $filter, $db, $form;
    echo "<INPUT NAME=\"title\"";
    if ( isset($filter->title) ) echo " VALUE=\"" . $filter->title . "\"";
    echo $form["addon_title"] . ">";
  }
  function category() {
    GLOBAL $filter, $db;
    echo "<SELECT NAME=\"cat_id[]\" SIZE=\"7\" MULTIPLE>";
    dbquery("SELECT id,name FROM cat ORDER BY name");
    while ( $db->next_record() ) {
      $id        = $db->f('id');
      $name      = $db->f('name');
      echo "<OPTION VALUE=\"$id\"";
      if ($filter->cat->$id) echo " SELECTED";
      echo ">$name</OPTION>";
    }
    echo "</SELECT>";
  }
  function actor() {
    GLOBAL $filter, $db;
    echo "<SELECT NAME=\"act_id[]\" SIZE=\"7\" MULTIPLE>";
    dbquery("SELECT id,name,firstname FROM actors ORDER BY name");
    while ( $db->next_record() ) {
      $id        = $db->f('id');
      $name      = $db->f('name');
      $firstname = $db->f('firstname');
      echo "<OPTION VALUE=\"$id\"";
      if ($filter->actor->$id) echo " SELECTED";
      echo ">$name, $firstname</OPTION>";
    }
    echo "</SELECT>";
  }
  function director() {
    GLOBAL $filter, $db;
    echo "<SELECT NAME=\"dir_id[]\" SIZE=\"7\" MULTIPLE>";
    dbquery("SELECT id,name,firstname FROM directors ORDER BY name");
    while ( $db->next_record() ) {
      $id        = $db->f('id');
      $name      = $db->f('name');
      $firstname = $db->f('firstname');
      echo "<OPTION VALUE=\"$id\"";
      if ($filter->director->$id) echo " SELECTED";
      echo ">$name, $firstname</OPTION>";
    }
    echo "</SELECT>";
  }
  function composer() {
    GLOBAL $filter, $db;
    echo "<SELECT NAME=\"mus_id[]\" SIZE=\"7\" MULTIPLE>";
    dbquery("SELECT id,name,firstname FROM music ORDER BY name");
    while ( $db->next_record() ) {
      $id        = $db->f('id');
      $name      = $db->f('name');
      $firstname = $db->f('firstname');
      echo "<OPTION VALUE=\"$id\"";
      if ($filter->composer->$id) echo " SELECTED";
      echo ">$name, $firstname</OPTION>";
    }
    echo "</SELECT>";
  }
?>

<FORM NAME="filter" METHOD="post" ACTION="<? echo $PHP_SELF ?>">
 <TABLE Width="90%" Align="Center" Border="1">
  <TR><TD WIDTH="50%"><!-- ====================================== Left side ============ !>
    <TABLE WIDTH="100%" BORDER="1">
     <TR><TD WIDTH="15%">MediaType</TD><TD><? mtype() ?></TD></TR>
     <TR><TD WIDTH="15%">Length</TD><TD><? length() ?></TD></TR>
     <TR><TD WIDTH="15%">Aquired</TD><TD><? aquired() ?></TD></TR>
     <TR><TD WIDTH="15%">Screen</TD><TD><? screen() ?></TD></TR>
     <TR><TD WIDTH="15%">Picture</TD><TD><? picture() ?></TD></TR>
     <TR><TD WIDTH="15%">Tone</TD><TD><? tone() ?></TD></TR>
     <TR><TD WIDTH="15%">LongPlay</TD><TD><? longplay() ?></TD></TR>
     <TR><TD WIDTH="15%">FSK</TD><TD><? fsk() ?></TD></TR>
    </TABLE></TD>
   <TD WIDTH="50%"><!-- ===================================== Right side ============ !>
    <TABLE WIDTH="100%" BORDER="1">
     <TR><TD WIDTH="10%">Title</TD><TD COLSPAN="3"><? title() ?></TD></TR>
     <TR><TD WIDTH="10%">Category</TD><TD WIDTH="40%"><? category() ?></TD>
         <TD WIDTH="10%">Actor</TD><TD WIDTH="40%"><? actor() ?></TD></TR>
     <TR><TD WIDTH="10%">Director</TD><TD WIDTH="40%"><? director() ?></TD>
         <TD WIDTH="10%">Composer</TD><TD WIDTH="40%"><? composer() ?></TD></TR>
    </TABLE></TD>
  </TR>
 </TABLE>
 <TABLE Width="90%" Align="Center" Border="0">
  <TR>
   <TD ALIGN="left"><INPUT TYPE="submit" NAME="reset" VALUE="Reset"></TD>
   <TD ALIGN="right"><INPUT TYPE="submit" NAME="save" VALUE="Save"></TD>
  </TR>
 </TABLE>
</FORM>

<?
  include("inc/footer.inc");
?>