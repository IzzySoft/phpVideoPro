<? /* Taperest (free space on tapes) */
   /* $Id$ */

  $page_id = "taperest";
  include("inc/header.inc");
  $t = new Template($pvp->tpl_dir);
  if ($usefilter) $filter = get_filters();

  if (!$minfree) {
    $t->set_file(array("taperest_init"=>"taperest_init.tpl"));
    $t->set_var("form_target",$PHP_SELF);
    $t->set_var("use_filter",$usefilter);
    $t->set_var("min_free",lang("enter_min_free"));
    $t->set_var("display",lang("display"));
    $t->pparse("out","taperest_init");
    include("inc/footer.inc");
    exit;
  }

  // init templates
  $t->set_file(array("taperest_list"=>"taperest_list.tpl",
                     "taperest_item"=>"taperest_item.tpl",
		     "taperest_movie"=>"taperest_movie.tpl",
		     "taperest_empty"=>"taperest_empty.tpl"));
  $where = "WHERE free>='$minfree'";
  if ( strlen($filter) ) {
    dbquery("SELECT cass_id FROM video v WHERE $filter");
    $i=0;
    while ( $db->next_record() ) {
      if ($i) { $tapelist .= "," . $db->f('cass_id'); } else { $tapelist = $db->f('cass_id'); }
    }
    $where .= " AND id IN ($tapelist)";
  }
  dbquery("SELECT id,free FROM cass $where ORDER BY free DESC");
  if (!$db->num_rows()) {
    $t->set_var("title",lang("no_entries_found"));
    $t->set_var("msg",lang("no_space_of",$minfree));
    $t->pparse("out","taperest_empty");
    include("inc/footer.inc");
    exit;
  }
  $i = 0;
  while ( $db->next_record() ) {
    $i++;
    $mlist[$i]["id"]   = $db->f('id');
    $mlist[$i]["free"] = $db->f('free');
  }

  for ($i=1;$i<=count($mlist);$i++) {
    $query = "SELECT v.title,m.sname,c.name FROM video v,mtypes m,cat c WHERE cass_id='" . $mlist[$i]["id"] . "' AND v.mtype_id=m.id AND v.cat1_id=c.id AND v.mtype_id IN ($rw_media)";
    debug("S","<TR><TD colspan=4>" . $colors["ok"] . "$query</Font></TD></TR>\n");
    $db->query($query);
    $k = 0;
    while ( $db->next_record() ) {
      $k++;
      $mlist[$i][$k]      = $db->f('title') . " (" . $db->f('name') . ")";
      $mlist[$i]["mtype"] = $db->f('sname');
      debug("V","<TR><TD colspan=4>Title: '". $mlist[$i][$k] . "', Type: '" . $mlist[$i]["mtype"] . "'</TD></TR>\n");
    }
    for ($l=1;$l<=$k;$l++) {
      $t->set_var("movies",$mlist[$i][$l]);
      if ($l==1) {
        $t->parse("movie_list","taperest_movie");
      } else {
        $t->parse("movie_list","taperest_movie",TRUE);
      }
    }
    $t->set_var("mtype",$mlist[$i]["mtype"]);
    $t->set_var("id",$mlist[$i]["id"]);
    $t->set_var("free",$mlist[$i]["free"]);
    $t->parse("item_list","taperest_item",TRUE);
  }
  $t->set_var("freespace",lang("free_space_on_media",$minfree));
  $t->set_var("medium",lang("medium"));
  $t->set_var("nr",lang("nr"));
  $t->set_var("free",lang("free"));
  $t->set_var("content",lang("content"));
  $t->pparse("out","taperest_list");

  include("inc/footer.inc");

?>