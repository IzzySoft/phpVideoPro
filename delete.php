<? /* Delete an entry */

  /* $Id$ */

  if ($cancel) {
    include("inc/config.inc");
    header("Location: $base_url/edit.php?nr=" . urlencode("$nr") . "&cass_id=$cass_id&part=$part&mtype_id=$mtype_id");
    exit;
  }
  $page_id = "delete";
  include("inc/header.inc");
  
  function kill($table,$id) {
    GLOBAL $colors;
    echo " ";
    if ( dbquery("DELETE FROM $table WHERE id='$id'") ) {
      echo $colors["ok"] . lang("ok") . ".</Font><br>\n";
    } else {
      echo $colors["err"] . lang("not_ok") . "!</Font><br>\n";
    }
  }

  echo "<H2 ALIGN=\"center\">" . lang("deleting_entry",$nr) . "</H2>\n";

  if (!$approved) { ?>
<FORM NAME="deleform" METHOD="post" ACTION="<? echo basename(__FILE__) ?>">
 <INPUT TYPE="hidden" NAME="nr" VALUE="<? echo $nr ?>">
 <INPUT TYPE="hidden" NAME="cass_id" VALUE="<? echo $cass_id ?>">
 <INPUT TYPE="hidden" NAME="part" VALUE="<? echo $part ?>">
 <INPUT TYPE="hidden" NAME="mtype_id" VALUE="<? echo $mtype_id ?>">
 <TABLE WIDTH="90%" ALIGN="center" BORDER="0">
  <TR><TD ALIGN="center" COLSPAN="2"><? echo $colors["err"] . lang("sure_to_delete",$nr); ?>?</FONT></TD></TR>
  <TR><TD ALIGN="center" WIDTH="50%"><INPUT TYPE="submit" NAME="cancel" VALUE="<? echo strtoupper(lang("no")) ?>!"></TD>
      <TD ALIGN="center"><INPUT TYPE="submit" NAME="approved" VALUE="<? echo lang("yes") ?>."></TD>
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
      $firstname = $db->f('firstname'); $name = $db->f('name');
      echo "<li>" . lang("nobody_named",lang("compose_person"),$firstname,$name);
      kill("music",$music_id);
    }
    dbquery("SELECT id FROM video WHERE director_id='$director_id' AND id<>'$id'");
    if ( !$db->next_record() ) {
      dbquery("SELECT name,firstname FROM directors WHERE id='$director_id'");
      $db->next_record();
      $firstname = $db->f('firstname'); $name = $db->f('name');
      echo "<li>" . lang("nobody_named",lang("director_person"),$firstname,$name);
      kill("directors",$director_id);
    }
    for ($i=1;$i<6;$i++) {
      $aid = $actor_id[$i];
      dbquery("SELECT id FROM video WHERE (actor1_id='$aid' OR actor2_id='$aid'"
             . " OR actor3_id='$aid' OR actor4_id='$aid' OR actor5_id='$aid') AND id<>'$id'");
      if ( !$db->next_record() ) {
        dbquery("SELECT name,firstname FROM actors WHERE id='$aid'");
        $db->next_record();
        $firstname = $db->f('firstname'); $name = $db->f('name');
        echo "<li>" . lang("nobody_named",lang("actor"),$firstname,$name);
        kill("actors",$aid);
      }
    }
    # now we delete the movie entry from db
    echo "<li>" . lang("check_completed") . " - " . lang("delete_remaining") . ". ";
    if ( dbquery("DELETE FROM video WHERE cass_id='$cass_id' AND part='$part' AND mtype_id='$mtype_id'") ) {
      echo $colors["ok"] . lang("ok") . ".</Font><br>\n";
    } else {
      echo $colors["err"] . lang("not_ok") . "!</Font><br>\n";
    }
    # and finally we may have to correct the free space remaining on that medium
    if ( $mtype_id == 1 ) { // RVT
      echo "<li>" . lang("recalc_free"). ". ";
      dbquery("SELECT type FROM cass WHERE id='$cass_id'");
      if ( $db->next_record() ) {
        $time_left = $db->f('type');
        dbquery("SELECT length,lp FROM video WHERE cass_id='$cass_id' AND mtype_id='$mtype_id'");
        while ( $db->next_record() ) {
          $lp = $db->f('lp');
          if ($db->f('lp') ) {
            $time_left -= $db->f('length') / 2;
          } else {
            $time_left -= $db->f('length');
          }
        }
        if ( dbquery("UPDATE cass SET free='$time_left' WHERE id='$cass_id'") ) {
          echo lang("time_left",$time_left) . $colors["ok"] . lang("ok") . ".</Font><BR>\n";
        } else {
          echo $colors["err"] . lang("tapelist_update_failed") . "!</Font><br>\n";
        }
      } else {
        echo $colors["err"] . lang("no_entry_in_tapelist") . "!</Font><br>\n";
      }
    }
    # and that's all.
    echo "<b><i>" . lang("finnished") . ".</i></b>\n</TD></TR></TABLE>\n";
  }

  include("inc/footer.inc");

?>