<? /* stafflist - call with ?stafftype=<director|actor|music> */
   /* $Id$ */

  $page_id = $stafftype;
  include("inc/header.inc");
  $t = new Template($pvp->tpl_dir);
  $t->set_file(array("list"=>"stafflist.tpl"));
  $t->set_block("list","itemblock","itemlist");
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
    if ( strlen($filter) ) $query .= " AND ($filter)";
    $same_name = FALSE;
    $row = 0;
    dbquery($query);
    $same_name = FALSE;
    while ($db->next_record()) {
     $mtype    = $db->f('sname');
     $mtype_id = $db->f('mtype_id');
     $cass_id  = $db->f('cass_id');
     $nr       = $cass_id;
     $part     = $db->f('part');
     while (strlen($nr)<4) { $nr = "0" . $nr; }
     $nr      .= "-";
     if (strlen($part)<2) {
       $nr .= "0" . $part;
     } else { $nr .= $part; }
     $movie_id = urlencode($mtype . " " . $nr);
     $title    = $db->f('title'); check_empty($title);
     $length   = $db->f('length'); check_empty($length);
     $year     = $db->f('year'); check_empty($year);
     $aq_date  = $db->f('aq_date');  check_empty($aq_date);
     $category = $db->f('name'); check_empty($category);

     if ($same_name) {
       $t->set_var("name","&nbsp;");
       $t->set_var("namesep","&nbsp;");
       $t->set_var("firstname","&nbsp;");
     } else {
       $t->set_var("name",$staff[$i]->name);
       $t->set_var("namesep",", ");
       $t->set_var("firstname",$staff[$i]->firstname);
     }
     $t->set_var("title",$title);
     $t->set_var("category",$category);
     $t->set_var("length",$length);
     $t->set_var("url","edit.php?nr=$movie_id&cass_id=$cass_id&part=$part&mtype_id=$mtype_id");
     $t->set_var("mtype",$mtype);
     $t->set_var("nr",$nr);
     $t->parse("itemlist","itemblock",TRUE);
     $same_name = TRUE;
    }
  }

  // draw table header
  $t->set_var("listtitle",lang($page_id));
  $t->set_var("stafftype",lang($stafftype));
  $t->set_var("title",lang("title"));
  $t->set_var("category",lang("category"));
  $t->set_var("length",lang("length"));
  $t->set_var("medianr",lang("medianr"));
  $t->pparse("out","list");

  include("inc/footer.inc");

?>