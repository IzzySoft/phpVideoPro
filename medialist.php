<? /* Medialist */

  $page_id = "medialist";
  include("inc/config.inc");
  include("inc/header.inc");
  $filter = get_filters();

  echo "<H2 Align=Center>" . lang("medialist") . "</H2>\n";
  echo "<TABLE ALIGN=\"center\" BORDER=\"1\">\n";
  echo " <TR><TH>" . lang("medium") . "</TH><TH>" . lang("nr")
       . "</TH><TH>" . lang("title") . "</TH><TH>" . lang("length")
       . "</TH><TH>" . lang("year") . "</TH><TH>" . lang("date_rec")
       . "</TH><TH>" . lang("category") . "</TH></TR>\n";

  $query  = "SELECT v.cass_id,v.part,v.title,v.length,v.year,v.aq_date,c.name,m.sname,v.mtype_id";
  $query .= " FROM video v, cat c, mtypes m";
  $query .= " WHERE v.cat1_id = c.id AND v.mtype_id = m.id";
  if ( strlen($filter) ) $query .= " AND ($filter)";
  $db->query($query);
  while ($db->next_record()) {
   $mtype    = $db->f('sname');
   $mtype_id = $db->f('mtype_id');
   $cass_id  = $db->f('cass_id');
   $nr       = $cass_id;
   $part     = $db->f('part');
   while (strlen($nr)<4) { $nr = "0" . $nr; }
   $nr      .= "-";
   if (strlen($part)<2) { $nr .= "0" . $part; } else { $nr .= $part; }
   $movie_id = urlencode($mtype . " " . $nr);
   $title    = $db->f('title'); check_empty($title);
   $length   = $db->f('length'); check_empty($length);
   $year     = $db->f('year'); check_empty($year);
   $aq_date  = $db->f('aq_date');  check_empty($aq_date);
   $category = $db->f('name'); check_empty($category);
   echo " <TR>\n";
   echo "  <TD>$mtype</TD><TD><A HRef=\"edit.php?nr=$movie_id&cass_id=$cass_id&part=$part&mtype_id=$mtype_id\">$nr</A></TD>\n  <TD>$title</TD>\n  <TD>$length</TD>\n";
   echo "  <TD>$year</TD>\n  <TD>$aq_date</TD>\n  <TD>$category</TD>\n";
   echo " </TR>\n";
  }
  echo "</Table>\n";

  include("inc/footer.inc");

?>