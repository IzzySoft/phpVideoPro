<? /* Edit an entry */

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
    }
    $output .= "</CENTER>";
    return $output;
  }

  if ($edit) {
    $input = "INPUT SIZE=\"30\"";
    $db->query("SELECT name,id FROM mtypes");
    $i = 0;
    while ( $db->next_record() ){
     $mtypes[$i][id]   = $db->f('id');
     $mtypes[$i][name] = $db->f('name');
     $i++;
    }
    $db->query("SELECT name,id FROM tone");
    $i = 0;
    while ( $db->next_record() ){
     $ttypes[$i][id]   = $db->f('id');
     $ttypes[$i][name] = $db->f('name');
     $i++;
    }
    $db->query("SELECT name,id FROM cat");
    $i = 0;
    while ( $db->next_record() ){
     $cats[$i][id]   = $db->f('id');
     $cats[$i][name] = $db->f('name');
     $i++;
    }
    $db->query("SELECT name,id FROM colors");
    $i = 0;
    while ( $db->next_record() ){
     $colors[$i][id]   = $db->f('id');
     $colors[$i][name] = $db->f('name');
     $i++;
    }
    $db->query("SELECT name,id FROM pict");
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
  
?>

<table width="100%" border="0" cellspacing="0" cellpadding="0">
 <tr> 
  <td width="7"><img src="<? echo $base_url ?>images/menu_bar_left.gif" width="7" height="24"></td>
  <td background="<? echo $base_url ?>images/menu_bar_bg.gif" width="100%">&nbsp;</td>
  <td width="9"><img src="<? echo $base_url ?>images/menu_bar_right.gif" width="9" height="24"></td>
 </tr>
</table>

<? if ($save) { include("inc/save.inc"); exit; } ?>

<H2 Align=Center>Edit an entry</H2>
<?
  $cass_id = (int) substr($nr,0,4); $part = (int) substr($nr,6);
  $query   = "SELECT title,length,year,aq_date,source,director_id,music_id,country,"
           . "cat1_id,cat2_id,cat3_id,actor1_id,actor2_id,actor3_id,actor4_id,actor5_id,"
           . "actor1_list,actor2_list,actor3_list,actor4_list,actor5_list,lp,fsk,comment,mtype_id,"
           . "color_id,tone_id,pict_id"
           . " FROM video"
           . " WHERE cass_id=$cass_id AND part=$part";
  $db->query($query);
  $db->next_record();

  // values:
  $title = $db->f('title'); $length = $db->f('length'); $year = $db->f('year');
  $recdate = $db->f('aq_date'); $src = $db->f('source'); $country = $db->f('country');
  $vis_actor1 = $db->f('actor1_list'); $vis_actor2 = $db->f('actor2_list');
  $vis_actor3 = $db->f('actor3_list'); $vis_actor4 = $db->f('actor4_list');
  $vis_actor5 = $db->f('actor5_list');
  $fsk = $db->f('fsk'); $comment = $db->f('comment'); $lp = $db->f('lp');
  // helper:
  $music_id  = $db->f('music_id'); $cat1_id = $db->f('cat1_id'); $cat2_id = $db->f('cat2_id');
  $cat3_id   = $db->f('cat3_id'); $actor1_id = $db->f('actor1_id'); $actor2_id = $db->f('actor2_id');
  $actor3_id = $db->f('actor3_id'); $actor4_id = $db->f('actor4_id'); $actor5_id = $db->f('actor5_id');
  $mtype_id  =  $db->f('mtype_id'); $color_id = $db->f('color_id'); $tone_id = $db->f('tone_id');
  $director_id = $db->f('director_id'); $pict_id = $db->f('pict_id');
  // sub-queries
  for ($i=1;$i<6;$i++) {
    $act_id  = "actor" . $i . "_id";
    $query   = "SELECT name,firstname FROM actors WHERE id=\"${$act_id}\"";
    $db->query($query); $db->next_record();
    $actor[$i][name]  = $db->f('name');
    $actor[$i][fname] = $db->f('firstname');
  }
  $db->query("SELECT name,sname FROM mtypes WHERE id=$mtype_id");
  $db->next_record();
  $mediatype = $db->f('sname'); $media_tname = $db->f('name');
  $db->query("SELECT name,firstname FROM directors WHERE id=$director_id");
  $db->next_record();
  $director_name = $db->f('name'); $director_fname = $db->f('firstname');
  $db->query("SELECT name,firstname FROM music WHERE id=$music_id");
  $db->next_record();
  $composer_name = $db->f('name'); $composer_fname = $db->f('firstname');
  $db->query("SELECT name FROM tone WHERE id=$tone_id");
  $db->next_record();
  $tone = $db->f('name');
  $db->query("SELECT name FROM colors WHERE id=$color_id");
  $db->next_record();
  $color = $db->f('name');
  $db->query("SELECT name FROM pict WHERE id=$pict_id");
  $db->next_record();
  $pict_format = $db->f('name');
  $pict_format = trim($pict_format);
  if (strlen($pict_format)<1) $pict_format = "unknown";
  for ($i=1;$i<4;$i++) {
    $cat_nr  = "cat" . $i . "_id";
    $query   = "SELECT name FROM cat WHERE id=\"${$cat_nr}\"";
    $db->query($query); $db->next_record();
    $cat[$i] = $db->f('name');
  }
  $free = "0";
  if ($mediatype == "RVT") {
    $query = "SELECT free FROM cass WHERE id='$cass_id'";
    $db->query($query); $db->next_record();
    $free  = $db->f('free');
  }
?>
<FORM NAME="entryform" METHOD="post" ACTION="<? echo $PHP_SELF ?>">
<Table Width="90%" Align="Center" Border="1">
 <TR><TH>Title</TH><TH ColSpan=3><? echo "<$input NAME=\"title\" VALUE=\"$title\">" ?></TH></TR>
 <TR>
  <TD Width=20%>MediaType</TD><TD Width=30%><?
  if ($edit) {
    echo "<SELECT NAME=\"media_tid\">";
    for ($i=0;$i<count($mtypes);$i++) {
      echo "<OPTION VALUE=\"" . $mtypes[$i][id] . "\"";
      if ($mtypes[$i][name]==$media_tname) echo " SELECTED";
      echo ">" . $mtypes[$i][name] . "</OPTION>";
    }
    echo "</SELECT>";
  } else {
    echo "<$input NAME=\"media_tname\" VALUE=\"$media_tname\">";
  } ?></TD>
  <TD Width=20%>Country</TD><TD Width=30%><? echo "<$input NAME=\"country\" VALUE=\"$country\">" ?></TD></TR>
 <TR>
  <TD Width=20%>MediaNr</TD><TD Width=30%><? echo "<$input NAME=\"nr\" VALUE=\"$nr\">" ?></TD>
  <TD>Director</TD><TD><? check_empty_name($director); echo "<$input NAME=\"director_name\" VALUE=\"$director_name\">&nbsp;<$input NAME=\"director_fname\" VALUE=\"$director_fname\">"; ?></TD></TR>
 <TR>
  <TD>Length</TD><TD><? echo "<$input NAME=\"length\" VALUE=\"$length\">" ?> min</TD>
  <TD>Composer</TD><TD><? check_empty_name($composer); echo "<$input NAME=\"composer_name\" VALUE=\"$composer_name\">&nbsp;<$input NAME=\"composer_fname\" VALUE=\"$composer_fname\">" ?></TD></TR>
 <TR>
  <TD>Free</TD><TD><? echo "<INPUT TYPE=\"button\" NAME=\"free\" VALUE=\"$free\"> min" ?></TD>
  <TD>Year</TD><TD><? echo "<$input NAME=\"year\" VALUE=\"$year\">" ?></TD></TR>
 <TR>
  <TD>Tone</TD><TD><?
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
  } ?></TD>
  <TD>Category 1</TD><TD><?
  if ($edit) {
    echo "<SELECT NAME=\"cat1_id\">";
    for ($i=0;$i<count($cats);$i++) {
      echo "<OPTION VALUE=\"" . $cats[$i][id] . "\"";
      if ($cats[$i][name]==$cat[1]) echo " SELECTED";
      echo ">" . $cats[$i][name] . " </OPTION>";
    }
    echo "</SELECT>";
  } else {
    echo "<$input NAME=\"cat1\" VALUE=\"" . $cat[1] . "\">";
  }
  ?></TD></TR>
 <TR>
  <TD>Picture</TD><TD><?
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
  ?></TD>
  <TD>Category 2</TD><TD><?
  if ($edit) {
    echo "<SELECT NAME=\"cat2_id\"><OPTION VALUE=\"-1\">- None -</OPTION>";
    for ($i=0;$i<count($cats);$i++) {
      echo "<OPTION VALUE=\"" . $cats[$i][id] . "\"";
      if ($cats[$i][name]==$cat[2]) echo " SELECTED";
      echo ">" . $cats[$i][name] . " </OPTION>";
    }
    echo "</SELECT>";
  } else {
    echo "<$input NAME=\"cat2\" VALUE=\"" . $cat[2] . "\">";
  }
  ?></TD></TR>
 <TR>
  <TD>Acquired</TD><TD><? echo "<$input NAME=\"recdate\" VALUE=\"$recdate\">" ?></TD>
  <TD>Category 3</TD><TD><?
  if ($edit) {
    echo "<SELECT NAME=\"cat3_id\"><OPTION VALUE=\"-1\">- None -</OPTION>";
    for ($i=0;$i<count($cats);$i++) {
      echo "<OPTION VALUE=\"" . $cats[$i][id] . "\"";
      if ($cats[$i][name]==$cat[3]) echo " SELECTED";
      echo ">" . $cats[$i][name] . " </OPTION>";
    }
    echo "</SELECT>";
  } else {
    echo "<$input NAME=\"cat3\" VALUE=\"" . $cat[3] . "\">";
  }
  ?></TD></TR>
 <TR>
  <TD ColSpan=2>
   <Table Width=100%>
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
    <TR><TD Width=40%>Source</TD><TD Width=60%><? echo "<$input NAME=\"src\" VALUE=\"$src\">" ?></TD></TR>
    <TR><TD>FSK</TD><TD><? echo "<$input NAME=\"fsk\" VALUE=\"$fsk\">" ?></TD></TR>
   </Table></TD>
  <TD ColSpan=2>
   <Table Width=100%>
    <TR><TD><B>Actor</B></TD><TD>Name</TD><TD>First Name</TD><TD ALIGN="center">in List</TD></TR>
    <TR><TD>1</TD><TD><? echo "<$input NAME=\"actor1_name\" VALUE=\"" . $actor[1][name] . "\">" ?></TD><TD><? echo "<$input NAME=\"actor1_fname\" VALUE=\"" . $actor[1][fname] . "\">" ?></TD><TD><? echo vis_actors(1) ?></TD></TR>
    <TR><TD>2</TD><TD><? echo "<$input NAME=\"actor2_name\" VALUE=\"" . $actor[2][name] . "\">" ?></TD><TD><? echo "<$input NAME=\"actor2_fname\" VALUE=\"" . $actor[2][fname] . "\">" ?></TD><TD><? echo vis_actors(2) ?></TD></TR>
    <TR><TD>3</TD><TD><? echo "<$input NAME=\"actor3_name\" VALUE=\"" . $actor[3][name] . "\">" ?></TD><TD><? echo "<$input NAME=\"actor3_fname\" VALUE=\"" . $actor[3][fname] . "\">" ?></TD><TD><? echo vis_actors(3) ?></TD></TR>
    <TR><TD>4</TD><TD><? echo "<$input NAME=\"actor4_name\" VALUE=\"" . $actor[4][name] . "\">" ?></TD><TD><? echo "<$input NAME=\"actor4_fname\" VALUE=\"" . $actor[4][fname] . "\">" ?></TD><TD><? echo vis_actors(4) ?></TD></TR>
    <TR><TD>5</TD><TD><? echo "<$input NAME=\"actor5_name\" VALUE=\"" . $actor[5][name] . "\">" ?></TD><TD><? echo "<$input NAME=\"actor5_fname\" VALUE=\"" . $actor[5][fname] . "\">" ?></TD><TD><? echo vis_actors(5) ?></TD></TR>
<!--
    <TD>&nbsp;</TD><TD>2</TD><TD><? check_empty_name($actor[2]); echo "<$input NAME=\"actor_2\" VALUE=\"" . $actor[2] . "\">" ?></TD><TD><? echo vis_actors(2) ?></TD></TR>
    <TD>&nbsp;</TD><TD>3</TD><TD><? check_empty_name($actor[3]); echo "<$input NAME=\"actor_3\" VALUE=\"" . $actor[3] . "\">" ?></TD><TD><? echo vis_actors(3) ?></TD></TR>
    <TD>&nbsp;</TD><TD>4</TD><TD><? check_empty_name($actor[4]); echo "<$input NAME=\"actor_4\" VALUE=\"" . $actor[4] . "\">" ?></TD><TD><? echo vis_actors(4) ?></TD></TR>
    <TD>&nbsp;</TD><TD>5</TD><TD><? check_empty_name($actor[5]); echo "<$input NAME=\"actor_5\" VALUE=\"" . $actor[5] . "\">" ?></TD><TD><? echo vis_actors(5) ?></TD></TR>
-->
   </Table>
  </TD>
  </TR>
 <TR><TH ColSpan=4 Align=Center><HR>Comments<HR></TH></TR>
 <TR><TD ColSpan=4><?
 if ($edit) {
   echo "<CENTER><TEXTAREA ROWS=\"5\" COLS=\"120\" NAME=\"comment\">$comment</TEXTAREA></CENTER>";
 } else {
   echo $comment;
 }
 ?></TD></TR>
 <TR><TD ColSpan=4>
   <INPUT TYPE="hidden" NAME="nr" VALUE="<?php echo $nr ?>">
   <Table Width="100%"><? if ($edit) { ?>
    <TR><TD Width="50%"><INPUT TYPE="submit" NAME="cancel" VALUE="Cancel"></TD>
        <TD Width="50%" ALIGN="right"><INPUT TYPE="submit" NAME="save" VALUE="Save"></TD></TR><? } else { ?>
    <TR><TD Width="50%"><INPUT TYPE="submit" NAME="edit" VALUE="Edit"></TD>
        <TD Width="50%" ALIGN="right"><INPUT TYPE="submit" NAME="delete" VALUE="Delete"></TD></TR><? } ?>
   </TABLE>
 </TD></TR>
</Table>
</FORM>
<?

  include("inc/footer.inc");

?>