<? /* Taperest (free space on tapes) */

  $page_id = "taperest";
  include("inc/config.inc");
  include("inc/header.inc");
  if ($usefilter) $filter = get_filters();

  if (!$minfree) { ?>
    <FORM NAME="space" METHOD="post" ACTION="<? echo $PHP_SELF ?>">
      <INPUT TYPE="hidden" NAME="usefilter" VALUE="<? echo $usefilter ?>">
      <TABLE WIDTH="70%" ALIGN="center">
        <TR><TD>Enter minimum of free space on medium to display:</TD>
            <TD><INPUT NAME="minfree"></TD>
            <TD><INPUT TYPE="submit" NAME="getrest" VALUE="Display"></TR>
      </TABLE>
    </FORM> <?
    exit;
  }

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
  $i = 0;
  while ( $db->next_record() ) {
    $i++;
    $mlist[$i]["id"]   = $db->f('id');
    $mlist[$i]["free"] = $db->f('free');
  }
?>

<H2 Align=Center>Free space on media</H2>

<Table Witdh=90% Align=Center Border=1>
 <TR><TH>Medium</TH><TH>Nr</TH><TH>Free</TH><TH>Contains</TH><TR><?

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
    echo " <TR><TD>" . $mlist[$i]["mtype"] . "</TD><TD>" . $mlist[$i]["id"] . "</TD><TD>" . $mlist[$i]["free"] . "</TD><TD><UL>";
    for ($l=1;$l<=$k;$l++) {
      echo "<LI>" . $mlist[$i][$l];
    }
    echo "</UL></TD></TR>\n";
  }
  echo "</Table>\n";

  include("inc/footer.inc");

?>