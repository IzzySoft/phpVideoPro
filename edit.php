<? /* Edit an entry */

  include("inc/config.inc");
  include("inc/header.inc");

?>

<table width="100%" border="0" cellspacing="0" cellpadding="0">
 <tr> 
  <td width="7"><img src="<? echo $base_url ?>images/menu_bar_left.gif" width="7" height="24"></td>
  <td background="<? echo $base_url ?>images/menu_bar_bg.gif" width="100%">&nbsp;</td>
  <td width="9"><img src="<? echo $base_url ?>images/menu_bar_right.gif" width="9" height="24"></td>
 </tr>
</table>

<H2 Align=Center>Edit an entry</H2>
<?
  $query  = "SELECT titel,laenge,jahr,datum,quelle,regisseur,musik,land,";
  $query .= "kat1,kat2,kat3,spl1,spl2,spl3,spl4,spl5,sp1,sp2,sp3,sp4,sp5,";
  $query .= "stereo,farbe,lp,fsk,bemerk01,bemerk02,bemerk03";
  $query .= " FROM video";
  $query .= " WHERE filmnr='$nr'";
  $db->query($query);
  $db->next_record();
  
  function v_actor($actor) {
    if ($actor == "T") return TRUE;
    return FALSE;
  }
  $mediatype = "RVT"; // at this moment only support for "Recorded Video Tapes"
                      // Future will add: OVT (Original Video Tape) and DVD
  switch ($mediatype) {
    case "RVT" : $media_tname = "Recorded Video Tape"; break;
    case "OVT" : $media_tname = "Original Video Tape"; break;
    case "DVD" : $media_tname = "Digital Versatile Disc"; break;
  }
  $title = $db->f('titel'); $length = $db->f('laenge'); $year = $db->f('jahr');
  $recdate = $db->f('datum'); $src = $db->f('quelle'); $director = $db->f('regisseur');
  $composer = $db->f('musik'); $country = $db->f('land');
  $cat1 = $db->f('kat1'); $cat2 = $db->f('kat2'); $cat3 = $db->f('kat3');
  $actor1 = $db->f('sp1'); $actor2 = $db->f('sp2'); $actor3 = $db->f('sp3');
  $actor4 = $db->f('sp4'); $actor5 = $db->f('sp5');
  $vis_actor1 = v_actor('spl1'); $vis_actor2 = v_actor('spl2');
  $vis_actor3 = v_actor('spl3'); $vis_actor4 = v_actor('spl4');
  $vis_actor5 = v_actor('spl5');
  $tone_short = $db->f('stereo'); $color = $db->f('farbe'); $lp = $db->f('lp');
  $fsk = $db->f('fsk'); $comment1 = $db->f('bemerk01');
  $comment2 = $db->f('bemerk02'); $comment3 = $db->f('bemerk03');
  
  switch ($tone_short) {
    case "MO" : $tone = "Mono"; break;
    case "20" : $tone = "Dolby 2.0"; break;
    case "30" : $tone = "Dolby Surround"; break;
    case "50" : $tone = "Dolby 5.0"; break;
    case "51" : $tone = "Dolby 5.1"; break;
    case "61" : $tone = "DTS 6.1"; break;
    default   : $tone = "Stereo";
  }
  if ($color == "J") { $color = TRUE; } else { $color = FALSE; }
  $free = "0";
  if ($mediatype == "RVT") {
    $pos   = strpos($nr,"-"); $tape = substr($nr,0,$pos); $tape++; $tape--;
    $query = "SELECT frei FROM cass WHERE cassnr='$tape'";
    $db->query($query); $db->next_record();
    $free  = $db->f('frei');
  }
  $free .= " min";
?>
<Table Widht=90% Align=Center Border=1>
 <TR><TH>Title</TH><TH ColSpan=3><? echo $title ?></TH></TR>
 <TR>
  <TD Width=20%>MediaType</TD><TD Width=30%><? echo $media_tname ?></TD>
  <TD Width=20%>Country</TD><TD Width=30%><? echo $country ?></TD></TR>
 <TR>
  <TD Width=20%>MediaNr</TD><TD Width=30%><? echo $nr ?></TD>
  <TD>Director</TD><TD><? echo $director ?></TD></TR>
 <TR>
  <TD>Length</TD><TD><? echo $length ?> min</TD>
  <TD>Composer</TD><TD><? echo $composer ?></TD></TR>
 <TR>
  <TD>Free</TD><TD><? echo $free ?></TD>
  <TD>Year</TD><TD><? echo $year ?></TD></TR>
 <TR>
  <TD>Tone</TD><TD><? echo $tone ?></TD>
  <TD>Category 1</TD><TD><? echo $cat1 ?></TD></TR>
 <TR>
  <TD>Color</TD><TD><? if ($color) { echo "Yes"; } else { echo "No"; } ?></TD>
  <TD>Category 2</TD><TD><? echo $cat2 ?></TD></TR>
 <TR>
  <TD>Acquired</TD><TD><? echo $recdate ?></TD>
  <TD>Category 3</TD><TD><? echo $cat3 ?></TD></TR>
 <TR>
  <TD ColSpan=2>
   <Table Width=100%>
    <TR><TD Width=40%>Source</TD><TD Width=60%><? echo $src ?></TD></TR>
    <TR><TD>FSK</TD><TD><? echo $fsk ?></TD></TR>
   </Table></TD>
  <TD ColSpan=2>
   <Table Width=100%>
   <TD>Actor</TD><TD>1</TD><TD><? echo $actor1 ?></TD><TD><? if ($vis_actor1) echo "vis" ?></TD></TR>
   <TD>&nbsp;</TD><TD>2</TD><TD><? echo $actor2 ?></TD><TD><? if ($vis_actor2) echo "vis" ?></TD></TR>
   <TD>&nbsp;</TD><TD>3</TD><TD><? echo $actor3 ?></TD><TD><? if ($vis_actor3) echo "vis" ?></TD></TR>
   <TD>&nbsp;</TD><TD>4</TD><TD><? echo $actor4 ?></TD><TD><? if ($vis_actor4) echo "vis" ?></TD></TR>
   <TD>&nbsp;</TD><TD>5</TD><TD><? echo $actor5 ?></TD><TD><? if ($vis_actor5) echo "vis" ?></TD></TR>
   </Table>
  </TD></TR>
 <TR><TD ColSpan=4><HR></TD></TR>
 <TR><TD ColSpan=4 Align=Center>Comments</TD></TR>
 <TR><TD ColSpan=4><HR></TD></TR>
 <TR><TD ColSpan=4><? echo $comment1 ?></TD></TR>
 <TR><TD ColSpan=4><? echo $comment2 ?></TD></TR>
 <TR><TD ColSpan=4><? echo $comment3 ?></TD></TR>
</Table>
<?

  include("inc/footer.inc");

?>