<? /* Edit an entry */

  if ($edit) { $page_id = "edit"; } else { $page_id = "view"; }
  include("inc/config.inc");
  include("inc/header.inc");

  function vis_actors($num) {
    GLOBAL $edit,$vis_actor1,$vis_actor2,$vis_actor3,$vis_actor4,$vis_actor5;
    $visible = "vis_actor" . $num;
    $output  = "<CENTER>";
    if ($edit) {
      $output .= "<INPUT TYPE=\"checkbox\" NAME=\"vis_actor" . $num . "\" VALUE=\"1\"";
      if (${$visible}) $output .= " CHECKED";
      $output .= ">";
    } else {
      $output .= "<INPUT TYPE=\"button\" NAME=\"" . ${$visible} . "\" VALUE=\"";
      if (${$visible}) { $output .= "Yes\">"; } else { $output .= "No\">"; }
      $output .= "<INPUT TYPE=\"hidden\" NAME=\"" . ${$visible} ."\" VALUE=\"${$visible}\">";
    }
    $output .= "</CENTER>";
    return $output;
  }

  function vis_staff($name,$list) {
    GLOBAL $edit;
    $output  = "<CENTER>";
    if ($edit) {
      $output .= "<INPUT TYPE=\"checkbox\" NAME=\"$name\" VALUE=\"1\"";
      if ($list) $output .= " CHECKED";
      $output .= ">";
    } else {
      $output .= "<INPUT TYPE=\"button\" NAME=\"$name\" VALUE=\"";
      if ($list) { $output .= "Yes\">"; } else { $output .= "No\">"; }
      $output .= "<INPUT TYPE=\"hidden\" NAME=\"$name\" VALUE=\"$list\">";
    }
    $output .= "</CENTER>";
    return $output;
  }

  if ($edit) {
    $input = "INPUT SIZE=\"30\"";
    dbquery("SELECT name,id FROM mtypes");
    $i = 0;
    while ( $db->next_record() ){
     $mtypes[$i][id]   = $db->f('id');
     $mtypes[$i][name] = $db->f('name');
     $i++;
    }
    dbquery("SELECT name,id FROM tone");
    $i = 0;
    while ( $db->next_record() ){
     $ttypes[$i][id]   = $db->f('id');
     $ttypes[$i][name] = $db->f('name');
     $i++;
    }
    dbquery("SELECT name,id FROM cat");
    $i = 0;
    while ( $db->next_record() ){
     $cats[$i][id]   = $db->f('id');
     $cats[$i][name] = $db->f('name');
     $i++;
    }
    dbquery("SELECT name,id FROM colors");
    $i = 0;
    while ( $db->next_record() ){
     $colors[$i][id]   = $db->f('id');
     $colors[$i][name] = $db->f('name');
     $i++;
    }
    dbquery("SELECT name,id FROM pict");
    $i = 0;
    while ( $db->next_record() ){
     $picts[$i][id]   = $db->f('id');
     $picts[$i][name] = $db->f('name');
     $i++;
    }
  } else {
    $input = "INPUT TYPE=\"button\"";
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
    $field = "<INPUT" . $type . "NAME=\"$name\" VALUE=\"$value\">";
    echo $field;
  }
  
?>

<? if ($update) { include("inc/update.inc"); } ?>

<H2 Align=Center><? if ($edit) { echo "Edit"; } else { echo "View";} echo " entry $nr"; ?></H2>
<?
  echo "<CENTER>$save_result</CENTER>";
  $query   = "SELECT title,length,year,aq_date,source,director_id,director_list,music_id,music_list,country,"
           . "cat1_id,cat2_id,cat3_id,actor1_id,actor2_id,actor3_id,actor4_id,actor5_id,"
           . "actor1_list,actor2_list,actor3_list,actor4_list,actor5_list,lp,fsk,comment,"
           . "color_id,tone_id,pict_id"
           . " FROM video"
           . " WHERE cass_id=$cass_id AND part=$part AND mtype_id=$mtype_id";
  dbquery($query);
  $db->next_record();

  // values:
  $title = $db->f('title'); $length = $db->f('length'); $year = $db->f('year');
  $recdate = $db->f('aq_date'); $src = $db->f('source'); $country = $db->f('country');
  $vis_actor1 = $db->f('actor1_list'); $vis_actor2 = $db->f('actor2_list');
  $vis_actor3 = $db->f('actor3_list'); $vis_actor4 = $db->f('actor4_list');
  $vis_actor5 = $db->f('actor5_list');
  $fsk = $db->f('fsk'); $comment = $db->f('comment'); $lp = $db->f('lp');
  // helper:
  $music_id  = $db->f('music_id'); $music_list = $db->f('music_list'); $cat1_id = $db->f('cat1_id');
  $cat2_id = $db->f('cat2_id'); $cat3_id   = $db->f('cat3_id'); $actor1_id = $db->f('actor1_id');
  $actor2_id = $db->f('actor2_id'); $actor3_id = $db->f('actor3_id'); $actor4_id = $db->f('actor4_id');
  $actor5_id = $db->f('actor5_id'); $color_id = $db->f('color_id'); $tone_id = $db->f('tone_id');
  $director_id = $db->f('director_id'); $director_list = $db->f('director_list'); $pict_id = $db->f('pict_id');
  // sub-queries
  for ($i=1;$i<6;$i++) {
    $act_id  = "actor" . $i . "_id";
    $query   = "SELECT name,firstname FROM actors WHERE id=\"${$act_id}\"";
    dbquery($query); $db->next_record();
    $actor[$i][name]  = $db->f('name');
    $actor[$i][fname] = $db->f('firstname');
  }
  dbquery("SELECT name,sname FROM mtypes WHERE id=$mtype_id");
  $db->next_record();
  $mediatype = $db->f('sname'); $media_tname = $db->f('name');
  dbquery("SELECT name,firstname FROM directors WHERE id='$director_id'");
  $db->next_record();
  $director_name = $db->f('name'); $director_fname = $db->f('firstname');
  dbquery("SELECT name,firstname FROM music WHERE id='$music_id'");
  $db->next_record();
  $composer_name = $db->f('name'); $composer_fname = $db->f('firstname');
  dbquery("SELECT name FROM tone WHERE id=$tone_id");
  $db->next_record();
  $tone = $db->f('name');
  dbquery("SELECT name FROM colors WHERE id=$color_id");
  $db->next_record();
  $color = $db->f('name');
  dbquery("SELECT name FROM pict WHERE id=$pict_id");
  $db->next_record();
  $pict_format = $db->f('name');
  $pict_format = trim($pict_format);
  if (strlen($pict_format)<1) $pict_format = "unknown";
  for ($i=1;$i<4;$i++) {
    $cat_nr  = "cat" . $i . "_id";
    $query   = "SELECT name FROM cat WHERE id=\"${$cat_nr}\"";
    dbquery($query); $db->next_record();
    $cat[$i] = $db->f('name');
  }
  $free = "0";
  if ($mediatype == "RVT") {
    $query = "SELECT free FROM cass WHERE id='$cass_id'";
    dbquery($query); $db->next_record();
    $free  = $db->f('free');
  }
################################################################
# Form Start
?>
<FORM NAME="entryform" METHOD="post" ACTION="<? echo $PHP_SELF ?>">
<INPUT TYPE="hidden" NAME="cass_id" VALUE="<? echo $cass_id ?>">
<INPUT TYPE="hidden" NAME="part" VALUE="<? echo $part ?>">
<INPUT TYPE="hidden" NAME="mtype_id" VALUE="<? echo $mtype_id ?>">
<Table Width="90%" Align="Center" Border="1">
 <TR><TH>Title</TH><TH ColSpan=3><? echo "<$input NAME=\"title\" VALUE=\"$title\">" ?></TH></TR>
 <TR>
  <TD Width=20%>MediaType</TD><TD Width=30%><?
  if ($new_entry) {
    echo "<SELECT NAME=\"media_tid\">";
    for ($i=0;$i<count($mtypes);$i++) {
      echo "<OPTION VALUE=\"" . $mtypes[$i][id] . "\"";
      if ($mtypes[$i][name]==$media_tname) echo " SELECTED";
      echo ">" . $mtypes[$i][name] . "</OPTION>";
    }
    echo "</SELECT>";
  } else {
    echo "<INPUT TYPE=\"button\" NAME=\"media_tname\" VALUE=\"$media_tname\">";
    echo "<INPUT TYPE=\"hidden\" NAME=\"media_tname\" VALUE=\"$media_tname\">";
  } ?></TD>
  <TD Width=20%>Country</TD><TD Width=30%><? form_input("country",$country,$form["addon_country"]); ?></TD></TR>
 <TR>
  <TD Width=20%>MediaNr</TD><TD Width=30%><? echo "<INPUT TYPE=\"button\" NAME=\"nr\" VALUE=\"$nr\"><INPUT TYPE=\"hidden\" NAME=\"nr\" VALUE=\"$nr\">" ?></TD>
  <TD>Year</TD><TD><? form_input("year",$year,$form["addon_year"]); ?></TD></TR>
 <TR>
  <TD>Length</TD><TD><TABLE WIDTH="100%" CellPadding=0 CellSpacing=0><TR><TD><? form_input("length",$length,$form["addon_filmlen"]); ?> min</TD><TD>LongPlay:&nbsp;<INPUT NAME="lp" <?
  if ($edit) { ?>TYPE="checkbox" VALUE="1"<? if ($lp) echo " CHECKED"; echo ">"; } else { ?>TYPE="button" VALUE="<? if ($lp) { echo "Yes\">"; } else { echo "No\">"; } } ?></TD></TR></TABLE>
  <TD>Category 1-2-3</TD><TD><?
  for ($i=1;$i<=$max["categories"];$i++) {
   if ($edit) {
    echo "<SELECT NAME=\"cat" . $i . "_id\">";
    if ($i > 1) echo "<OPTION VALUE=\"-1\">- None -</OPTION>";
    for ($k=0;$k<count($cats);$k++) {
      echo "<OPTION VALUE=\"" . $cats[$k][id] . "\"";
      if ($cats[$k][name]==$cat[$i]) echo " SELECTED";
      echo ">" . $cats[$k][name] . " </OPTION>";
    }
    echo "</SELECT>";
   } else {
    echo "<$input NAME=\"cat" . $i . "\" VALUE=\"";
    if ( trim($cat[$i])=="" ) { echo "- None -"; } else { echo $cat[$i]; }
    echo "\">";
   }
   if ( $i<$max["categories"] ) echo "&nbsp;-&nbsp;";
  }
  ?></TD></TR>
 <TR>
  <TD ColSpan=2>
   <Table Width=100% Border=0 CellPadding=0 CellSpacing=0>
    <TR><TD>Free</TD><TD><? echo "<INPUT TYPE=\"button\" NAME=\"free\" VALUE=\"$free\"> min" ?></TD></TD>
    <TR><TD>Acquired</TD><TD><? echo "<$input NAME=\"recdate\" VALUE=\"$recdate\">" ?></TD></TR>
    <TR><TD ColSpan="2"><HR></TD></TR>
    <TR><TD WIDTH=30%>Tone</TD><TD><?
    if ($edit) {
      echo "<SELECT NAME=\"tone_id\">";
      for ($i=0;$i<count($ttypes);$i++) {
        echo "<OPTION VALUE=\"" . $ttypes[$i][id] . "\"";
        if ($ttypes[$i][name]==$tone) echo  "SELECTED";
        echo ">" . $ttypes[$i][name] . " </OPTION>";
      }
      echo "</SELECT>";
    } else {
      echo "<$input NAME=\"tone\" VALUE=\"$tone\">";
    } ?></TD></TR>
    <TR><TD>Picture</TD><TD><?
    if ($edit) {
      echo "<SELECT NAME=\"color_id\">";
      for ($i=0;$i<count($colors);$i++) {
        echo "<OPTION VALUE=\"" . $colors[$i][id] . "\"";
        if ($colors[$i][name]==$color) echo " SELECTED";
        echo ">" . $colors[$i][name] . " </OPTION>";
      }
      echo "</SELECT>";
    } else {
      echo "<$input NAME=\"color\" VALUE=\"$color\">";
    }
    ?></TD></TR>
    <TR><TD Width=40%>Screen</TD><TD Width=60%><?
    if ($edit) {
      echo "<SELECT NAME=\"pict_id\"><OPTION VALUE=\"-1\">unknown</OPTION>";
      for ($i=0;$i<count($picts);$i++) {
        echo "<OPTION VALUE=\"" . $picts[$i][id] . "\"";
        if ($picts[$i][name]==$pict_format) echo  "SELECTED";
        echo ">" . $picts[$i][name] . " </OPTION>";
      }
      echo "</SELECT>";
    } else {
      echo "<$input NAME=\"pict_format\" VALUE=\"$pict_format\">";
    }
    ?></TD></TR>
    <TR><TD Width=40%>Source</TD><TD Width=60%><? form_input("src",$src,$form["addon_src"]); ?></TD></TR>
    <TR><TD>FSK</TD><TD><? form_input("fsk",$fsk,$form["addon_fsk"]); ?></TD></TR>
   </Table></TD>
  <TD ColSpan=2>
   <Table Width=100%>
    <TR><TD><B>Staff</B></TD><TD>Name</TD><TD>First Name</TD><TD ALIGN="center">in List</TD></TR>
    <TR><TD>Director</TD><TD><? form_input("director_name",$director_name,$form["addon_name"]); ?></TD>
        <TD><? form_input("director_fname",$director_fname,$form["addon_name"]); ?></TD>
        <TD><? echo vis_staff('director_list',$director_list); ?></TD></TR>
    <TR><TD>Composer</TD><TD><? form_input("composer_name",$composer_name,$form["addon_name"]); ?></TD>
        <TD><? form_input("composer_fname",$composer_fname,$form["addon_name"]); ?></TD>
        <TD><? echo vis_staff('music_list',$music_list); ?></TD></TR>
    <TR><TD COLSPAN="4"><HR></TD></TR>
    <?php for ($i=1;$i<=$max["actors"];$i++) {
      $name = "actor" . $i . "_name"; $fname = "actor" . $i . "_fname";
      echo "<TR><TD>Actor $i</TD><TD>";
      form_input($name,$actor[$i][name],$form["addon_name"]);
      echo "</TD><TD>";
      form_input($fname,$actor[$i][fname],$form["addon_name"]);
      echo "</TD><TD>" . vis_actors($i) . "</TD></TR>\n";
    } ?>
   </Table>
  </TD>
  </TR>
 <TR><TD ColSpan=4 Align=Center>
   <TABLE WIDTH="100%" BORDER="0">
     <TR><TH><HR>Comments<HR></TH></TR>
     <TR><TD><?
     if ($edit) {
       echo "<CENTER><TEXTAREA ROWS=\"5\" COLS=\"120\" NAME=\"comment\">$comment</TEXTAREA></CENTER>";
     } else {
       echo $comment;
     }
     ?></TD></TR>
   </TABLE>
 <TR><TD ColSpan=4>
   <INPUT TYPE="hidden" NAME="nr" VALUE="<?php echo $nr ?>">
   <Table Width="100%"><? if ($edit) { ?>
    <TR><TD Width="50%"><INPUT TYPE="submit" NAME="cancel" VALUE="Cancel"></TD>
        <TD Width="50%" ALIGN="right"><INPUT TYPE="submit" NAME="update" VALUE="Update"></TD></TR><? } else { ?>
    <TR><TD Width="50%"><INPUT TYPE="submit" NAME="edit" VALUE="Edit"></TD>
        <TD Width="50%" ALIGN="right"><INPUT TYPE="submit" NAME="delete" VALUE="Delete"></TD></TR><? } ?>
   </TABLE>
 </TD></TR>
</Table>
</FORM>
<?

  include("inc/footer.inc");

?>