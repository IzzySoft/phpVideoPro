<?
 ##############################################################################
 # phpVideoPro                               (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                           #
 # http://www.qumran.org/homes/izzy/                                          #
 # -------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it       #
 # under the terms of the GNU General Public License (see doc/LICENSE)        #
 # -------------------------------------------------------------------------- #
 # Change disk type of medium (dvd/vcd)                                       #
 ##############################################################################

 /* $Id$ */

 $page_id = "change_rc";
 include("inc/includes.inc");
 #=================================================[ Register global vars ]===
 $details = array ("change","o_disktype","n_disktype","rc");
 foreach ($details as $var) {
   $$var = $_POST[$var];
 }
 $details = array ("mtype_id","cass_id","part");
 foreach ($details as $var) {
   $$var = $_REQUEST[$var];
 }

 #==================================================[ Check authorization ]===
 if ( $change && !$pvp->auth->update) {
   kickoff();
 }

 #==================[ On submit: Do the changes & re-route to edit screen ]===
 if ( $change ) {
   if ($n_disktype) $db->set_disktype($cass_id,$mtype_id,$n_disktype);
   $rccount = count($rc);
   for ($i=0;$i<$rccount;++$i) {
     $rcn[$rc[$i]] = 1;
   }
   $db->set_rc($mtype_id,$cass_id,$rcn);
   header("location: " .$pvp->link->slink("edit.php?mtype_id=$mtype_id&cass_id=$cass_id&part=$part"));
   exit;
 }

 #============================[ Otherwise: Create the form for user input ]===
 $disks_id = $db->get_disktype_id($mtype_id,$cass_id);
 $mt = $db->get_mtypes("id=$mtype_id");
 $rc = $db->get_rc($mtype_id,$cass_id);
 $odt = $db->get_disktypes($mtype_id,$disks_id);
 include("inc/header.inc");

 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"change_rc.tpl"));
 $t->set_block("template","disktypeblock","disk");
 $t->set_var("listtitle",lang("change_rc_for",$mt[0][sname]. " $cass_id"));
 $t->set_var("form_target",$_SERVER["PHP_SELF"]);

 #---[ if disktype was not yet defined, we force the user to do so now ]---
 if (!$disks_id) {
   $t->set_var("orig",lang("orig_disktype"));
   $odtname = lang("unknown");
   $t->set_var("o_disktype","<INPUT TYPE='button' NAME='o_disktype' VALUE='$odtname'>");
   $t->set_var("new",lang("new_disktype"));
   $dt = $db->get_disktypes($mtype_id);
   $dtc = count ($dt);
   $dtsel = "<SELECT NAME='n_disktype'>";
   for ($i=0;$i<$dtc;++$i) {
     $dtsel .= "<OPTION VALUE='".$dt[$i]->id."'>".$dt[$i]->name;
     if ($dt[$i]->size) $dtsel .= " (".$dt[$i]->size.")";
     $dtsel .= "</OPTION>";
   }
   $dtsel .= "</SELECT>";
   $t->set_var("n_disktype",$dtsel);
   if (!$pvp->cookie->active) $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>";
   $t->parse("disk","disktypeblock");
 } else {
   $t->set_var("disk","");
 }

 #---[ Now we can go for the region code(s) ]---
 $t->set_var("rc_head",lang("region_code"));
 for ($i=0;$i<7;++$i) {
   $rcname .= "<INPUT TYPE='checkbox' NAME='rc[]' VALUE='$i' CLASS='checkbox'";
   if ($rc[$i]) $rcname .= " CHECKED";
   $rcname .= ">&nbsp;$i";
   if ($i<6) $rcname .= "&nbsp;";
 }
 $t->set_var("rc",$rcname);
 $hidden = "<INPUT TYPE='hidden' NAME='mtype_id' VALUE='$mtype_id'>"
         . "<INPUT TYPE='hidden' NAME='cass_id' VALUE='$cass_id'>"
         . "<INPUT TYPE='hidden' NAME='part' VALUE='$part'>";
 $t->set_var("hidden",$hidden);
 $change = "<INPUT CLASS='submit' TYPE='submit' NAME='change' VALUE='".lang("update")."'>";
 $t->set_var("change",$change);

 $t->pparse("out","template");

 include("inc/footer.inc");

?>