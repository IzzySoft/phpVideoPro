<? /* Medialist */

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

<H2 Align=Center>Medialist</H2>

<Table Witdh=90% Align=Center Border=1>
 <TR><TH>Nr</TH><TH>Title</TH><TH>Length</TH><TH>Year</TH><TH>Date Rec.</TH><TH>category</TH><TR>

<?
  $query  = "SELECT filmnr,titel,laenge,jahr,datum,kat";
  $query .= " FROM video";
  $db->query($query);
  while ($db->next_record()) {
   $nr       = $db->f('filmnr');
   $title    = $db->f('titel'); check_empty($title);
   $length   = $db->f('laenge'); check_empty($length);
   $year     = $db->f('jahr'); check_empty($year);
   $recdate  = $db->f('datum');  check_empty($datum);
   $category = $db->f('kat'); check_empty($kat);
   echo " <TR>\n";
   echo "  <TD><A HRef=\"edit.php?nr=$nr\">$nr</A></TD>\n  <TD>$title</TD>\n  <TD>$length</TD>\n";
   echo "  <TD>$year</TD>\n  <TD>$recdate</TD>\n  <TD>$category</TD>\n";
   echo " </TR>\n";
  }
  echo "</Table>\n";

  include("inc/footer.inc");

?>