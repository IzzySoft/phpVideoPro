<? /* Delete an entry */

  /* $Id$ */

  include("inc/config.inc");
  if ($cancel) {
    header("Location: $base_url/edit.php?nr=" . urlencode("$nr") . "&cass_id=$cass_id&part=$part&mtype_id=$mtype_id");
    exit;
  }
  $page_id = "delete";
  include("inc/header.inc");

  echo "<H2 ALIGN=\"center\">Deleting entry $nr</H2>\n";

  if (!$approved) { ?>
<FORM NAME="deleform" METHOD="post" ACTION="<? echo basename(__FILE__) ?>">
 <INPUT TYPE="hidden" NAME="nr" VALUE="<? echo $nr ?>">
 <INPUT TYPE="hidden" NAME="cass_id" VALUE="<? echo $cass_id ?>">
 <INPUT TYPE="hidden" NAME="part" VALUE="<? echo $part ?>">
 <INPUT TYPE="hidden" NAME="mtype_id" VALUE="<? echo $mtype_id ?>">
 <TABLE WIDTH="90%" ALIGN="center" BORDER="0">
  <TR><TD ALIGN="center" COLSPAN="2"><? echo $colors["err"] ?>Are you sure you want to delete all data for <?php echo $nr ?>?</FONT></TD></TR>
  <TR><TD ALIGN="center"><INPUT TYPE="submit" NAME="cancel" VALUE="NO!"></TD>
      <TD ALIGN="center"><INPUT TYPE="submit" NAME="approved" VALUE="Yes."></TD>
 </TABLE>
</FORM>
<?
  } else { // here comes the real delete!
    echo "<TABLE WIDTH=\"90%\" ALIGN=\"center\"><TR><TD>\n";
    # first obtain some data
    $query = "SELECT id,music_id,director_id,actor1_id,actor2_id,actor3_id,actor4_id,actor5_id"
           . " FROM video WHERE cass_id='$cass_id' AND part='$part' AND mtype_id='$mtype_id'";
    dbquery($query);
    if ( !$db->next_record() ) die ($colors["err"] . "Something strange happened - the entry was not found in db!</Font></BODY></HTML>");
    $id = $db->f('id'); $music_id = $db->f('music_id'); $director_id = $db->f('director_id');
    $actor_id[1] = $db->f('actor1_id'); $actor_id[2] = $db->f('actor2_id');
    $actor_id[3] = $db->f('actor3_id'); $actor_id[4] = $db->f('actor4_id');
    $actor_id[5] = $db->f('actor5_id');
    # now we have to check if any other links to director, composer and/or actors exist
    dbquery("SELECT id FROM video WHERE music_id='$music_id' AND id<>'$id'");
    if ( !$db->next_record() ) {
      dbquery("SELECT name,firstname FROM music WHERE id='$music_id'");
      $db->next_record();
      echo "<li>There's no other movie with music composed by " . $db->f('firstname') . " " . $db->f('name')
           . " in this db, so I remove this entry from the composers table.<br>";
    }
    dbquery("SELECT id FROM video WHERE director_id='$director_id' AND id<>'$id'");
    if ( !$db->next_record() ) {
      dbquery("SELECT name,firstname FROM directors WHERE id='$director_id'");
      $db->next_record();
      echo "<li>There's no other movie directed by " . $db->f('firstname') . " " . $db->f('name')
           . " in this db, so I remove this entry from the directors table.<br>";
    }
    for ($i=1;$i<6;$i++) {
      $aid = $actor_id[$i];
      dbquery("SELECT id FROM video WHERE (actor1_id='$aid' OR actor2_id='$aid'"
             . " OR actor3_id='$aid' OR actor4_id='$aid' OR actor5_id='$aid') AND id<>'$id'");
      if ( !$db->next_record() ) {
        dbquery("SELECT name,firstname FROM actors WHERE id='$aid'");
        $db->next_record();
        echo "<li>There's no other movie with the actor " . $db->f('firstname') . " " . $db->f('name')
             . " in this db, so I remove this entry from the actors table.<br>";
      }
    }
    # now we delete the movie entry from db
    echo "<li>Check completed - now deleting the other movie data from db.<br>";
    # and finally we may have to correct the free space remaining on that medium
    echo "<li>Re-calculating remaining free space on this medium.<br>";
    # and that's all.
    echo "\n</TD></TR></TABLE>\n";
  }

  include("inc/footer.inc");

?>