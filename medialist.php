<? /* Medialist */

  $page_id = "medialist";
  include("inc/header.inc");
  $filter = get_filters();

  switch($order) {
    case "title"  : $orderby = " ORDER BY v.title,v.mtype_id DESC,v.cass_id"; break;
    case "length" : $orderby = " ORDER BY v.length,v.mtype_id DESC,v.cass_id"; break;
    case "year"   : $orderby = " ORDER BY v.year,v.mtype_id DESC,v.cass_id"; break;
    case "date"   : $orderby = " ORDER BY v.aq_date,v.mtype_id DESC,v.cass_id"; break;
    case "cat"    : $orderby = " ORDER BY c.name,v.mtype_id DESC,v.cass_id"; break;
    default       : $orderby = " ORDER BY v.mtype_id DESC,v.cass_id";
  }

  echo "<H2 Align=Center>" . lang("medialist") . "</H2>\n";
  echo "<TABLE ALIGN=\"center\" BORDER=\"1\">\n";
  echo " <TR><TH><A HREF=\"$PHP_SELF\">" . lang("medium")
       . "</A></TH><TH><A HREF=\"$PHP_SELF\">" . lang("nr")
       . "</A></TH><TH><A HREF=\"$PHP_SELF?order=title\">" . lang("title")
       . "</A></TH><TH><A HREF=\"$PHP_SELF?order=length\">" . lang("length")
       . "</A></TH><TH><A HREF=\"$PHP_SELF?order=year\">" . lang("year")
       . "</A></TH><TH><A HREF=\"$PHP_SELF?order=date\">" . lang("date_rec")
       . "</A></TH><TH><A HREF=\"$PHP_SELF?order=cat\">" . lang("category") . "</A></TH></TR>\n";

  $query  = "SELECT v.cass_id,v.part,v.title,v.length,v.year,v.aq_date,c.name,m.sname,v.mtype_id";
  $query .= " FROM video v, cat c, mtypes m";
  $query .= " WHERE v.cat1_id = c.id AND v.mtype_id = m.id";
  if ( strlen($filter) ) $query .= " AND ($filter)";
  $query .= $orderby;
  dbquery($query);
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