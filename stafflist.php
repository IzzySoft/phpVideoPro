<? /* stafflist - call with ?stafftype=<director|actor|music> */
   /* $Id$ */

  $page_id = $stafftype;
//  $stafftable = $stafftype . "s";
  include("inc/header.inc");
  $filter = get_filters();

  function getStaffClause($i) {
    GLOBAL $staff,$stafftype;
    switch ($stafftype) {
      case "actors"     : $staff_clause = " (v.actor1_id='" . $staff[$i]->id ."'"
                                        . " AND v.actor1_list='1') OR"
					. " (v.actor2_id='" . $staff[$i]->id ."'"
                                        . " AND v.actor2_list='1') OR"
					. " (v.actor3_id='" . $staff[$i]->id ."'"
                                        . " AND v.actor3_list='1') OR"
					. " (v.actor4_id='" . $staff[$i]->id ."'"
                                        . " AND v.actor4_list='1') OR"
					. " (v.actor5_id='" . $staff[$i]->id ."'"
                                        . " AND v.actor5_list='1'))";
					break;
      case "directors" : $staff_clause = " (v.director_id='" . $staff[$i]->id ."'"
                                       . " AND v.director_list='1'))";
                         break;
      case "music"     : $staff_clause = " (v.music_id='" . $staff[$i]->id ."'"
                                       . " AND v.music_list='1'))";
                         break;
      default          : break;
    }
    return $staff_clause;
  }
  
  // retrieve all staff members
  dbquery("SELECT id,name,firstname FROM $stafftype ORDER BY name");
  $i = 0;
  while ( $db->next_record() ) {
    $staff[$i]->id        = $db->f('id');
    $staff[$i]->name      = $db->f('name');
    $staff[$i]->firstname = $db->f('firstname');
    $i++;
  }

  // draw table header
  echo "<H2 Align=Center>" . lang($page_id) . "</H2>\n";
  echo "<TABLE ALIGN=\"center\" BORDER=\"1\">\n";
  echo " <TR><TH>" . lang($stafftype) . "</TH><TH>" . lang("title") . "</TH>"
     . "<TH>" . lang("category") . "</TH><TH>" . lang("length") . "</TH>"
     . "<TH>" . lang("medianr") . "</TH></TR>\n";

  // now get & draw the list
  for ($i=0;$i<count($staff);$i++) {
    $query  = "SELECT v.cass_id,v.part,v.title,v.length,v.year,v.aq_date,c.name,m.sname,v.mtype_id,";
    switch ($stafftype) {
      case "actors"   : $query .= "v.actor1_id,v.actor2_id,v.actor3_id,v.actor4_id,v.actor5_id,"
                                . "v.actor1_list,v.actor2_list,v.actor3_list,v.actor4_list,v.actor5_list";
			break;
      case "directors": $query .= "v.director_id,v.director_list"; break;
      case "music"    : $query .= "v.music_id,v.music_list"; break;
      default         : break;
    }
    $query .= " FROM video v, cat c, mtypes m";
    $query .= " WHERE v.cat1_id = c.id AND v.mtype_id = m.id AND ("
            . getStaffClause($i);
/*
            . " (v.$stafftype"."1_id='" . $staff[$i]->id ."'"
	    . " AND v.$stafftype"."1_list='1') OR"
            . " (v.$stafftype"."2_id='" . $staff[$i]->id ."'"
	    . " AND v.$stafftype"."2_list='1') OR"
            . " (v.$stafftype"."3_id='" . $staff[$i]->id ."'"
	    . " AND v.$stafftype"."3_list='1') OR"
            . " (v.$stafftype"."4_id='" . $staff[$i]->id ."'"
	    . " AND v.$stafftype"."4_list='1') OR"
            . " (v.$stafftype"."5_id='" . $staff[$i]->id ."'"
	    . " AND v.$stafftype"."5_list='1'))";
*/
    if ( strlen($filter) ) $query .= " AND ($filter)";
//    $query .= " ORDER BY v.mtype_id DESC,v.cass_id";
    $same_name = FALSE;
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

     if ($same_name) {
       echo " <TR><TD>&nbsp;</TD>\n";
     } else {
       echo " <TR><TD>" . $staff[$i]->name . ", " . $staff[$i]->firstname . "</TD>\n";
     }
     echo "     <TD>$title</TD>\n"
        . "     <TD>$category</TD>\n"
	. "     <TD>$length</TD>\n"
	. "     <TD><A HRef=\"edit.php?nr=$movie_id&cass_id=$cass_id&part=$part&mtype_id=$mtype_id\">$mtype $nr</A></TD></TR>\n";
    $same_name = TRUE;
    }
  }
  echo "</Table>\n";

  include("inc/footer.inc");

?>