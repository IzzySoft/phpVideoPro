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
 <TR><TH>Medium</TH><TH>Nr</TH><TH>Title</TH><TH>Length</TH><TH>Year</TH><TH>Date Rec.</TH><TH>category</TH><TR>

<?
  $query  = "SELECT v.cass_id,v.part,v.title,v.length,v.year,v.aq_date,c.name,m.sname";
  $query .= " FROM video v, cat c, mtypes m";
  $query .= " WHERE v.cat1_id = c.id AND v.mtype_id = m.id";
  $db->query($query);
  while ($db->next_record()) {
   $mtype    = $db->f('sname');
   $nr       = $db->f('cass_id');
   $part     = $db->f('part');
   while (strlen($nr)<4) { $nr = "0" . $nr; }
   if (strlen($part)<2) $part = "0" . $part;
   $nr      .= "-" . $part;
   $title    = $db->f('title'); check_empty($title);
   $length   = $db->f('length'); check_empty($length);
   $year     = $db->f('year'); check_empty($year);
   $aq_date  = $db->f('aq_date');  check_empty($aq_date);
   $category = $db->f('name'); check_empty($category);
   echo " <TR>\n";
   echo "  <TD>$mtype</TD><TD><A HRef=\"edit.php?nr=$nr\">$nr</A></TD>\n  <TD>$title</TD>\n  <TD>$length</TD>\n";
   echo "  <TD>$year</TD>\n  <TD>$aq_date</TD>\n  <TD>$category</TD>\n";
   echo " </TR>\n";
  }
  echo "</Table>\n";

  include("inc/footer.inc");

?>