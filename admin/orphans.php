<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
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
 $t->set_block("template","movieblock","movielist");
 $t->set_block("movieblock","movieitem","movie");
 $t->set_block("movieblock","nomovieitem","nomovie");
 $t->set_block("movieblock","havemovieitem","havemovie");

 if (isset($_POST["delete"])) {
  $t->set_var("button","");
 } else {
  $t->set_var("formtarget",$_SERVER["PHP_SELF"]);
  $t->set_var("ititle",lang("intro"));
  $t->set_var("idetails",lang("desc_admin_orphans"));
  $t->set_var("button","<INPUT TYPE='submit' CLASS='submit' NAME='delete' VALUE='" . lang("delete"). "'>");
#  $t->parse("item","itemblock");
 }

#=========================================================[ orpaned movies ]===
 $orphan  = $db->get_orphaned_movies();
 $orphans = count($orphan);
 #---------------------------------------------[ run the fixing procedures ]---
 if ($_POST["fix"]) {
   for ($i=0;$i<$orphans;++$i) {
     if (isset($_POST["owner_$i"])) {
       $rc = $db->fix_orphaned_movie($orphan[$i]->id,$orphan[$i]->mtype_id,$_POST["owner_$i"]);
     }
   }
   $orphan  = $db->get_orphaned_movies();
   $orphans = count($orphan);
 }
 #--------------------------------------------------------[ prepare output ]---
 $users = $db->get_users();
 $uc = count($users);
 $sel = "";
 for ($i=0;$i<$uc;++$i) {
   $sel .= "<option value='".$users[$i]->id."'";
   if ($users[$i]->id==$pvp->auth->user_id) $sel .= " SELECTED";
   $sel .= "'>".ucfirst($users[$i]->login)."</option>";
 }
 for ($i=0;$i<$orphans;++$i) {
   $detail[$i]->sel  = "<select name='owner_$i'>$sel</select>";
   $detail[$i]->item = $pvp->link->linkurl($base_url."edit.php?".$orphan[$i]->link,$orphan[$i]->number)." ".$orphan[$i]->title;
 }
 if (empty($detail)) {
   $t->set_var("details",lang("no_orphans_found"));
   $t->parse("nomovie","nomovieitem");
 } else {
   $t_id  = 0;
   $t_mid = 0;
   for ($i=0;$i<$orphans;++$i) {
     if ($t_id != $orphan[$i]->id || $t_mid != $orphan[$i]->mtype_id) {
       $t_id = $orphan[$i]->id; $t_mid = $orphan[$i]->mtype_id;
       $t->set_var("owner",$detail[$i]->sel);
     } else {
       $t->set_var("owner","&nbsp;");
     }
     $t->set_var("owner_name",lang("owner"));
     $t->set_var("movie_name",lang("movies"));
     $t->set_var("imovie",$detail[$i]->item);
     $t->parse("movie","movieitem",$i);
   }
   $details = "<INPUT TYPE='submit' CLASS='submit' NAME='fix' VALUE='".lang("update")."'>"
            . "</div></form>";
   $t->set_var("mbutton",$details);
   $t->parse("havemovie","havemovieitem");
 }
 $t->set_var("mtitle",lang("orphan_movies_found",$orphans));
# $t->set_var("details",$details);
 $t->parse("movielist","movieblock");
 unset($details);

#==========================================================[ orpaned staff ]===
 $orphan  = $db->get_orphaned_staff();
 $orphans = count($orphan);
 $details = "";
 for ($i=0;$i<$orphans;++$i) {
  $staff = $orphan[$i]->stafftype;
  $details .= lang($staff) ." \"". $orphan[$i]->firstname ." ". $orphan[$i]->name ."\"";
  if (isset($_POST["delete"])) {
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
 if (empty($details)) {
   $details = lang("no_orphans_found");
   $t->set_var("button","");
 }

 if (isset($delete) && $orphans) {
   $t->set_var("title",lang("delete_orphans",$orphans));
 } else {
   $t->set_var("title",lang("orphans_found",$orphans));
 }
 $t->set_var("details",$details);
 $t->parse("item","itemblock");

 $t->set_var("listtitle",lang("admin_orphans"));
 if (!$pvp->cookie->active) $t->set_var("hidden","<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>");
 include("../inc/header.inc");
 $t->pparse("out","template");

 include("../inc/footer.inc");
?>