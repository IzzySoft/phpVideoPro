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

 $page_id = "disktype_change";
 include("inc/includes.inc");
 #=================================================[ Register global vars ]===
 $details = array ("change","o_disktype","n_disktype","submit");
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
   $db->set_disktype($cass_id,$mtype_id,$n_disktype);
   header("location: " .$pvp->link->slink("edit.php?mtype_id=$mtype_id&cass_id=$cass_id&part=$part"));
   exit;
 }

 #============================[ Otherwise: Create the form for user input ]===
 $disks_id = $db->get_disktype_id($mtype_id,$cass_id);
 $mt = $db->get_mtypes("id=$mtype_id");
 include("inc/header.inc");

 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"change_disktype.tpl"));
 $t->set_var("listtitle",lang("change_disktype",$mt[0][sname]. " $cass_id"));
 $t->set_var("form_target",$_SERVER["PHP_SELF"]);
 $t->set_var("orig",lang("orig_disktype"));
 if ($disks_id) {
   $odt = $db->get_disktypes($mtype_id,$disks_id);
   $odtname = $odt[0]->name;
   if ($odt[0]->size) $odtname .= " (".$odt[0]->size.")";
 } else {
   $odtname = lang("unknown");
 }
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
 $hidden = "<INPUT TYPE='hidden' NAME='mtype_id' VALUE='$mtype_id'>"
         . "<INPUT TYPE='hidden' NAME='cass_id' VALUE='$cass_id'>"
         . "<INPUT TYPE='hidden' NAME='part' VALUE='$part'>";
 if (!$pvp->config->enable_cookies) $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>";
 $t->set_var("hidden",$hidden);
 $change = "<INPUT CLASS='submit' TYPE='submit' NAME='change' VALUE='".lang("update")."'>";
 $t->set_var("change",$change);

 $t->pparse("out","template");

 include("inc/footer.inc");

?>