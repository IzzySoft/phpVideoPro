<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Administration: Edit disk types (e.g. CD-R, DVD+R, etc.)                  #
 #############################################################################

 /* $Id$ */

 $page_id = "admin_disktypes";
 include( dirname(__FILE__) . "/../inc/includes.inc");

 #=================================================[ Register global vars ]===
 $postit = array ("new_name","new_trans","new_id","new_mtype","new_size",
                  "new_lp","new_rc","lines");
 foreach ($postit as $var) {
   if (isset($_POST[$var])) $$var = $_POST[$var]; else $$var = "";
 }
 unset($postit);
 if (isset($_GET["delete"])) $delete = $_GET["delete"]; else $delete = FALSE;

 #==================================================[ Check authorization ]===
 if (!$pvp->auth->admin) kickoff();

 #-------------------------------------------------------[ process input ]---
 if ($delete) {
   $media = $db->get_mediaForDisktype($delete);
   if ( $mcount = count($media) ) {
     $save_result = "<SPAN CLASS='error'>".lang("disktype_contains_media")."<BR>";
     for ($i=0;$i<$mcount;++$i) {
       $mt = $db->get_mtypes("id=".$media[$i]->mtype_id);
       $sname = $mt[0]['sname'];
       $save_result .= " '".$pvp->link->linkurl("/change_disktype.php?mtype_id=".$media[$i]->mtype_id."&cass_id=".$media[$i]->cass_id,"$sname ".$media[$i]->cass_id)."'";
     }
     $save_result .= "</SPAN><BR>";
   } else {
     $db->delete_disktype($delete);
   }
   header("Location: ".$_SERVER["PHP_SELF"]);
   exit;
 } elseif (isset($_POST["submit"])) {
   for ($i=1;$i<=$lines;++$i) {
     $disk_id = "id_$i"; $mtype = "mtype_$i"; $name = "name_$i"; $size = "size_$i"; $lp = "lp_$i"; $rc = "rc_$i";
     if ( !strlen(trim($_POST[$name])) ) {
       die ( display_error(lang("disktype_name_empty",$_POST[$disk_id])) );
     } else {
       $postit = array("disk_id","mtype","name","size","lp","rc");
       foreach ($postit as $var) {
         if (isset($_POST[$$var])) $p[$var] = $_POST[$$var]; else $p[$var] = "";
       }
       if ( !$db->update_disktype($p["disk_id"],$p["mtype"],$p["name"],$p["size"],$p["lp"],$p["rc"]) )
         $upd_err .= $p["disk_id"] . ",";
     }
   }
   if ( strlen(trim($new_name)) ) {
      if ( !$db->update_disktype($new_id,$new_mtype,$new_name,$new_size,$new_lp,$new_rc) )
        $add_err .= ${$disk_id} . ",";
   }
   if (isset($add_err)) {
     $add_err = substr($add_err,0,strlen($add_err)-1);
     $save_result = "<SPAN CLASS='error'>".lang("disktype_add_failed")."</SPAN><BR>";
   }
   if (isset($upd_err)) {
     $upd_err = substr($upd_err,0,strlen($upd_err)-1);
     $save_result .= "<SPAN CLASS='error'>". lang("disktype_update_failed",$upd_err) . "</SPAN><BR>";
   }
   if ( !(isset($add_err) || isset($upd_err)) ) $save_result = "<SPAN CLASS='ok'>".lang("update_success")."</SPAN><BR>";
 }
 #-------------------------------------------------------[ build up page ]---
 $tpl_dir = str_replace($base_path,$base_url,$pvp->tpl_dir);
 $trash_img = $tpl_dir . "/images/trash.png";
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"admin_disktypes.tpl"));
 $t->set_block("template","diskblock","disks");

 $t->set_var("listtitle",lang("admin_disktypes"));
 if (!isset($save_result)) $save_result = "";
 $t->set_var("save_result",$save_result);
 $t->set_var("head_disk_id","ID");
 $t->set_var("head_mtype",lang("mediatype"));
 $t->set_var("head_disk_name",lang("name"));
 $t->set_var("head_size",lang("disk_size"));
 $t->set_var("head_lp",lang("longplay"));
 $t->set_var("head_rc",lang("region_code"));
 $t->set_var("update","<INPUT TYPE='submit' CLASS='submit' NAME='submit' VALUE='".lang("update")."'>");

 function make_input($name,$value,$type="text") {
   GLOBAL $form;
   switch($type) {
     case "hidden" : $input = "<INPUT TYPE='hidden' NAME='$name' VALUE='$value'>"; break;
     case "button" : $input = "<INPUT TYPE='button' NAME='$name' VALUE='$value' CLASS='yesnobutton'>"; break;
     default       : $input = "<INPUT NAME='$name' VALUE='$value' ".$form["addon_tech"].">"; break;
   }
   return $input;
 }

 function make_mtselect($name,$value) {
   GLOBAL $mtypes, $mcount;
   $input = "<SELECT NAME='$name'>";
   for ($i=0;$i<$mcount;++$i) {
     $input .= "<OPTION VALUE='" .$mtypes[$i]['id']. "'";
     if ( $value==$mtypes[$i]['id'] ) $input .= " SELECTED";
     $input .= ">" .$mtypes[$i]['sname']. "</OPTION>";
   }
   $input .= "</SELECT>";
   return $input;
 }

 $mtypes = $db->get_mtypes();
 $mcount = count($mtypes);
 $lines  = 0;
 for ($i=0;$i<$mcount;++$i) {
   $dt = $db->get_disktypes($mtypes[$i]['id']);
   $dtcount = count($dt);
   for ($k=0;$k<$dtcount;++$k) {
     if (!isset($dt[$k]->name)) continue;
     ++$lines;
     $t->set_var("mtype",make_mtselect("mtype_$lines",$mtypes[$i]['id']));
     $input = make_input("id_$lines",$dt[$k]->id,"button","yesnobutton");
     $input .= make_input("id_$lines",$dt[$k]->id,"hidden");
     $t->set_var("disk_id",$input);
     $t->set_var("disk_name",make_input("name_$lines",$dt[$k]->name));
     $t->set_var("size",make_input("size_$lines",$dt[$k]->size));
     $input = "<INPUT TYPE='checkbox' NAME='lp_$lines' VALUE='1'";
     if ($dt[$k]->lp) $input .= " CHECKED";
     $input .= ">";
     $t->set_var("lp",$input);
     $input = "<INPUT TYPE='checkbox' NAME='rc_$lines' VALUE='1'";
     if ($dt[$k]->rc) $input .= " CHECKED";
     $input .= ">";
     $t->set_var("rc",$input);
     $url = $pvp->link->slink($_SERVER["PHP_SELF"]."?delete=".$dt[$k]->id);
     $trash = "<IMG SRC='$trash_img' BORDER='0' onClick=\"delconfirm('$url')\">";
     $t->set_var("trash",$trash);
     if ($lines > 1) $t->parse("disks","diskblock",TRUE);
       else $t->parse("disks","diskblock");
   }
 }
 $t->set_var("mtype",make_mtselect("new_mtype",""));
 $input = make_input("new_id","?","button","yesnobutton");
 $t->set_var("disk_id",$input);
 $t->set_var("disk_name",make_input("new_name",""));
 $t->set_var("size",make_input("new_size",""));
 $input = "<INPUT TYPE='checkbox' NAME='new_lp' VALUE='1'>";
 $t->set_var("lp",$input);
 $input = "<INPUT TYPE='checkbox' NAME='new_rc' VALUE='1'>";
 $t->set_var("rc",$input);
 $t->parse("disks","diskblock",TRUE);
 $hidden = "<INPUT TYPE='hidden' NAME='lines' VALUE='$lines'>";
 if (!$pvp->cookie->active) $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>";
 $t->set_var("hidden",$hidden);
      
 include( dirname(__FILE__) . "/../inc/header.inc");
?>
<SCRIPT LANGUAGE="JavaScript">
 function delconfirm(url) {
  check = confirm("<?=lang("confirm_delete")?>");
  if (check == true) window.location.href=url;
 }
</SCRIPT>
<?
 $t->pparse("out","template");

 include( dirname(__FILE__) . "/../inc/footer.inc");
?>