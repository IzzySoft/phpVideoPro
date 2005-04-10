<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2005 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Administration: Cleanup orphaned files                                    #
 #############################################################################

 /* $Id$ */

# $page_id = "admin_orphan_fs";
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
  $t->set_var("details",lang("desc_admin_orphan_fs"));
  $t->parse("item","itemblock");
 }

 #=======================================[ Find orphaned IMDB image files ]===
 if (is_dir($pvp->config->imdb_photopath))  {
   $orphan  = array();
   $reldir  = substr($pvp->config->imdb_photopath,strlen($base_path));
   $thisdir = dir($pvp->config->imdb_photopath);
   while( $file=$thisdir->read() ) {
     if ($file!="." && $file!="..") {
       $fname = $reldir . $file;
       if (!$db->image_is_refered($fname)) $orphan[] = $fname;
     }
   }
 }
 $orphans = count($orphan);

 #======================================[ Find other orphaned image files ]===
 if (is_dir($pvp->config->photopath))  {
   $orphan2 = array();
   $reldir  = substr($pvp->config->photopath,strlen($base_path));
   $thisdir = dir($pvp->config->photopath);
   while( $file=$thisdir->read() ) {
     if ($file!="." && $file!="..") {
       $fname = $reldir . $file;
       if (!$db->image_is_refered($fname)) $orphan2[] = $fname;
     }
   }
 }
 $orphans2 = count($orphan2);

 #====================[ Prepare the display and optionally do the cleanup ]===
 #-----------------------------------------------------[ IMDB image files ]---
 $details = "";
 for ($i=0;$i<$orphans;++$i) {
  $details .= $pvp->link->linkurl($base_url.$orphan[$i],$orphan[$i]);
  if ($delete) {
    $rc = unlink($base_path.$orphan[$i]);
    if ($rc) { $details .= "<SPAN CLASS='ok'> " .lang("ok") ."</SPAN>";
    } else { $details .= "<SPAN CLASS='error'> " .lang("not_ok") ."</SPAN>"; }
  } else {
    $mid = substr($orphan[$i],strrpos($orphan[$i],"/")+1);
    $mid = substr($mid,0,strlen($mid)-4);
    $imdbsite = $pvp->preferences->get("imdb_url");
    $details .= "&nbsp;<A HREF='".$imdbsite."title/tt".$mid."' TARGET='_blank'><IMG SRC='".$base_url."images/imdb_link.gif' BORDER='0' ALT='Open IMDB page'></A>";
  }
  $details .= "<br>\n";
 }
 if (!empty($details))
   $details = "<B>$orphans ".lang("imdb_image_files").":</B><BR>" . $details;
 #----------------------------------------------------[ other image files ]---
 $details2 = "";
 for ($i=0;$i<$orphans2;++$i) {
  $details2 .= $pvp->link->linkurl($base_url.$orphan2[$i],$orphan2[$i]);
  if ($delete) {
    $rc = unlink($base_path.$orphan2[$i]);
    if ($rc) { $details2 .= "<SPAN CLASS='ok'> " .lang("ok") ."</SPAN>";
    } else { $details2 .= "<SPAN CLASS='error'> " .lang("not_ok") ."</SPAN>"; }
  } else {
    $mid = substr($orphan2[$i],strrpos($orphan2[$i],"/")+1);
    $mid = substr($mid,0,strlen($mid)-4);
    $imdbsite = $pvp->preferences->get("imdb_url");
  }
  $details2 .= "<br>\n";
 }
 if (!empty($details2))
   $details .= "<B>$orphans2 ".lang("local_image_files").":</B><BR>".$details2;

 #=======================================================[ Prepare output ]===
 if (empty($details)) {
   $details = lang("no_orphans_found");
   $t->set_var("button","");
 }

 if (isset($delete) && $orphans) {
   $t->set_var("title",lang("delete_orphans",$orphans+$orphans2));
 } else {
   $t->set_var("title",lang("orphans_found",$orphans+$orphans2));
 }
 $t->set_var("details",$details);
 $t->parse("item","itemblock",TRUE);

 $t->set_var("listtitle",lang("admin_orphan_fs"));
 if (!$pvp->cookie->active) $t->set_var("hidden","<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>");
 include("../inc/header.inc");
 $t->pparse("out","template");

 include("../inc/footer.inc");
?>