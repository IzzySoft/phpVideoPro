<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Administration: Manage Orphans                                            #
 #############################################################################

 /* $Id$ */

# $page_id = "admin_orphans";
 include("../inc/includes.inc");
 if (!$pvp->auth->admin) kickoff();

 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"admin_orphans.tpl"));
 $t->set_block("template","itemblock","item");

 if (isset($_POST["delete"])) {
  $t->set_var("button","");
 } else {
  $t->set_var("formtarget",$_SERVER["PHP_SELF"]);
  $t->set_var("button","<INPUT TYPE='submit' CLASS='submit' NAME='delete' VALUE='" . lang("delete"). "'>");
  $t->set_var("title",lang("intro"));
  $t->set_var("details",lang("desc_admin_orphans"));
  $t->parse("item","itemblock");
 }

 $orphan  = $db->get_orphaned_staff();
 $orphans = count($orphan);
 for ($i=0;$i<$orphans;++$i) {
  $staff = $orphan[$i]->stafftype;
  $details .= lang($staff) ." \"". $orphan[$i]->firstname ." ". $orphan[$i]->name ."\"";
  if ($delete) {
    switch($staff) {
      case "compose_person"  : $rc = $db->delete_composer($orphan[$i]->id); break;
      case "director_person" : $rc = $db->delete_director($orphan[$i]->id); break;
      case "actor"           : $rc = $db->delete_actor($orphan[$i]->id); break;
      default                : break;
    }
    if ($rc) { $details .= "<SPAN CLASS='ok'> " .lang("ok") ."</SPAN>";
    } else { $details .= "<SPAN CLASS='error'> " .lang("not_ok") ."</SPAN>"; }
  }
  $details .= "<br>\n";
 }
 if (!isset($details)) {
   $details = lang("no_orphans_found");
   $t->set_var("button","");
 }

 if (isset($delete) && $orphans) {
   $t->set_var("title",lang("delete_orphans",$orphans));
 } else {
   $t->set_var("title",lang("orphans_found",$orphans));
 }
 $t->set_var("details",$details);
 $t->parse("item","itemblock",TRUE);

 $t->set_var("listtitle",lang("admin_orphans"));
 if (!$pvp->cookie->active) $t->set_var("hidden","<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>");
 include("../inc/header.inc");
 $t->pparse("out","template");

 include("../inc/footer.inc");
?>