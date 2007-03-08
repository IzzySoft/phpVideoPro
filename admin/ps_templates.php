<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Edit EPS templates                                                        #
 #############################################################################

 /* $Id$ */

 #========================================================[ initial setup ]==
 $page_id = "admin_pstemplates";
 include("../inc/includes.inc");

 #-------------------------------------------------[ Register global vars ]---
 if (isset($_GET["add"])) $add = $_GET["add"]; else $add = FALSE;
 if (isset($_GET["remove"])) $remove = $_GET["remove"]; else $remove = FALSE;
 if (isset($_GET["showpack"])) $showpack = $_GET["showpack"]; else $showpack = FALSE;
 if (isset($_GET["packdetails"])) $packdetails = $_GET["packdetails"]; else $packdetails = FALSE;
 if (isset($_REQUEST["edit"])) $edit = $_REQUEST["edit"]; else $edit = FALSE;
 if (isset($_REQUEST["start"])) $start = $_REQUEST["start"]; else $start = 0;
 if (isset($_POST["submit"])) $submit = $_POST["submit"]; else $submit = FALSE;
 $postit = array ("desc","type_id","eps_file","ps_file","llx","lly","urx","ury");
 foreach ($postit as $var) {
   if (isset($_POST[$var])) $$var = $_POST[$var]; else $$var = "";
 }
 unset($postit);

 #--------------------------------------------------[ Check authorization ]---
 if (!$pvp->auth->admin) kickoff();

 #--------------------------------------------------[ initialize template ]---
 include("../inc/class.nextmatch.inc");

 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"admin_pstemplates.tpl"));
 $t->set_block("template","listblock","list");
 $t->set_block("listblock","itemblock","item");
 $t->set_block("template","editblock","edps");
 $t->set_block("template","packlistblock","packlist");
 $t->set_block("packlistblock","packitemblock","packitem");
 $t->set_block("template","packviewblock","packview");
 $t->set_var("listtitle",lang($page_id));
 $t->set_var("formtarget",$_SERVER["PHP_SELF"]);

 #===================================================[ process user input ]===
 if ($submit) {
   if ($edit) $ps->id = $edit;
   $details = array("llx","lly","urx","ury");
   foreach ($details as $item) {
     if (!${$item}) ${$item} = 0;
   }
   $details = array ("type_id","desc","eps_file","ps_file","llx","lly","urx","ury");
   foreach ($details as $item) {
     $ps->$item = ${$item};
   }
   $edit = $db->set_pstemplate($ps);
   if ($edit) {
     $save_result = "<SPAN CLASS='ok'>" .lang("update_success"). "</SPAN>";
   } else {
     $save_result = "<SPAN CLASS='error'>" .lang("update_failed"). "</SPAN>";
   }
   $hidden = "<INPUT TYPE='hidden' NAME='edit' VALUE='$edit'>";
   if (!$pvp->cookie->active) $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>";
   $t->set_var("hidden",$hidden);
   $t->set_var("save_result",$save_result);
 } elseif ($remove) { $db->set_pstemplate((int)$remove); }

 #===========================================[ edit a single eps template ]===
 if ($edit) {
   $ps = $db->get_pstemplates($edit);
   $hidden = "<INPUT TYPE='hidden' NAME='edit' VALUE='$edit'>";
   if (!$pvp->cookie->active) $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>";
   $t->set_var("hidden",$hidden);
   $t->set_var("button",lang("update"));
 } elseif ($add) {

 #=====================================================[ add eps template ]===
   $t->set_var("button",lang("submit"));
 }

 function make_input($name,$value,$desc="",$type="techinput") {
   if ($desc) $input = "<b>$desc:</b> "; else $input = "";
   $input .= "<INPUT NAME='$name' VALUE='$value' CLASS='$type'>";
   return $input;
 }

 function type_select($name,$value,$desc) {
   GLOBAL $db;
   $types  = $db->get_labeltypes();
   $tcount = count($types);
   if ($desc) $select = "<b>$desc:</b> ";
   $select .= "<SELECT NAME='$name'>";
   for ($i=0;$i<$tcount;++$i) {
     $select .= "<OPTION VALUE='".$types[$i]->id."'";
     if ($types[$i]->id==$value) $select .= " SELECTED";
     $select .= ">".$types[$i]->desc."</OPTION>";
   }
   $select .= "</SELECT>";
   return $select;
 }

 include("../inc/header.inc");
 #===========================[ create the edit form for a single template ]===
 if ($edit || $add || $submit) {
   if (!isset($ps)) $ps[0]->desc = $ps[0]->type_id = $ps[0]->eps_file = $ps[0]->ps_file = $ps[0]->llx = $ps[0]->lly = $ps[0]->urx = $ps[0]->ury = $ps[0]->packname = "";
   $t->set_var("pack","<b>".lang("label_pack").": </b>".$ps[0]->packname);
   $t->set_var("desc",make_input("desc",$ps[0]->desc,lang("name")));
   $t->set_var("type",type_select("type_id",$ps[0]->type_id,lang("pstpl_type")));
   $t->set_var("gfx_file",make_input("eps_file",$ps[0]->eps_file,lang("graphic_file")));
   $t->set_var("dsn_file",make_input("ps_file",$ps[0]->ps_file,lang("template_file")));
   $ll = "<b>".lang("lower_left_corner").": </b>".make_input("llx",$ps[0]->llx,"","yesnoinput")
       . " / ".make_input("lly",$ps[0]->lly,"","yesnoinput");
   $t->set_var("lower_left",$ll);
   $ur = "<b>".lang("upper_right_corner").": </b>".make_input("urx",$ps[0]->urx,"","yesnoinput")
       . " / ".make_input("ury",$ps[0]->ury,"","yesnoinput");
   $t->set_var("upper_right",$ur);
   $t->parse("edps","editblock");
 } else {

 #==================================================[ display initial list ]==
?>
<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript">
 function delconfirm(url) {
  check = confirm("<?=lang("confirm_delete")?>");
  if (check == true) window.location.href=url;
 }
 function psinst(sname,rev) {
  window.open('ps_install.php?name='+sname+';rev='+rev,'psinst','toolbar=no,location=no,titlebar=no,directories=no,status=yes,resizable=yes,scrollbars=yes,copyhistory=no,width=600,height=400');
 }
</SCRIPT>
<?
   $tpl_dir = str_replace($base_path,$base_url,$pvp->tpl_dir);
   $edit_img  = $tpl_dir . "/images/edit.gif";
   $show_img  = $tpl_dir . "/images/show.gif";
   $trash_img = $tpl_dir . "/images/trash.gif";

   if ($showpack) { // show list of templates
 #------------------------------------------[ Label List of selected pack ]---
     $pack = $db->get_pspacks($showpack);
     $query = "\$db->get_pstemplates(\"\",$showpack,$start)";
     $nextmatch = new nextmatch ($query,$pvp->tpl_dir,$_SERVER["PHP_SELF"]."?showpack=$showpack",$start);
     $list = $nextmatch->list;
     for ($i=0;$i<$nextmatch->listcount;$i++) {
       $t->set_var("id",$list[$i]->id);
       $t->set_var("desc",$list[$i]->desc);
       $t->set_var("type",$list[$i]->type_desc);
       $t->set_var("edit",$pvp->link->linkurl($_SERVER["PHP_SELF"]."?edit=".$list[$i]->id,"<IMG SRC='$edit_img' BORDER='0' ALT='".lang("edit")."'>"));
       $url = $pvp->link->slink($_SERVER["PHP_SELF"]."?remove=".$list[$i]->id);
       $t->set_var("remove","<IMG SRC='$trash_img' BORDER='0' ALT='".lang("delete")."' onClick=\"delconfirm('$url')\">");
       if ($i) $t->parse("item","itemblock",TRUE);
         else $t->parse("item","itemblock");
     }
     $t->set_var("lname",lang("label_pack").": ".$pack["name"]);
     $t->set_var("add",$pvp->link->linkurl($_SERVER["PHP_SELF"]."?add=1",lang("add_entry")));
     $t->set_var("head_desc",lang("pstpl_name"));
     $t->set_var("head_type",lang("pstpl_type"));
     $t->set_var("first",$nextmatch->first);
     $t->set_var("left",$nextmatch->left);
     $t->set_var("right",$nextmatch->right);
     $t->set_var("last",$nextmatch->last);
     $t->parse("list","listblock");
   } elseif ($packdetails) {
 #------------------------------------------------------[ Label Pack Edit ]---
     $pack = $db->get_pspacks($packdetails);
     $t->set_var("tname",lang("name"));
     $t->set_var("name",$pack["name"]);
     $t->set_var("tcreator",lang("creator"));
     $t->set_var("creator",$pvp->common->make_clickable($pack["creator"]));
     $t->set_var("tdesc",lang("description"));
     $t->set_var("desc",$pack["descript"]);
     $t->set_var("trev",lang("pstplpack_rev1"));
     $t->set_var("rev",$pack["rev"]);
     $t->parse("packview","packviewblock");
#     $fields = array("id","rev","sname","name","descript","creator");
   } else { // show list of template packs
 #-----------------------------------------------------[ Label Packs List ]---
     $query = "\$db->get_pspacks(\"\",$start)";
     $nextmatch = new nextmatch ($query,$pvp->tpl_dir,$_SERVER["PHP_SELF"],$start);
     $list = $nextmatch->list;
#echo "<pre>";print_r($list);echo "</pre>";
#echo "Count: ".$nextmatch->listcount."<br>";
     for ($i=0;$i<$nextmatch->listcount;$i++) {
       if ($list[$i]["rev"]>0) {
         $pname = $pvp->link->linkurl($_SERVER["PHP_SELF"]."?showpack=".$list[$i]["id"],$list[$i]["name"]);
         $prev1 = $list[$i]["rev"];
       } else {
         $pname = $list[$i]["name"];
         $prev1 = "-";
       }
       $t->set_var("pname",$pname);
       $t->set_var("prev1",$list[$i]["rev"]);
       if ($list[$i]["rev2"]>0) {
         $prev2 = $list[$i]["rev2"]; // include link for update/install here
       } else {
         $prev2 = "?";
       }
       $t->set_var("prev2",$prev2);
       $t->set_var("edit",$pvp->link->linkurl($_SERVER["PHP_SELF"]."?packdetails=".$list[$i]["id"],"<IMG SRC='$show_img' BORDER='0' ALT='".lang("edit")."'>"));
       $url = $pvp->link->slink($_SERVER["PHP_SELF"]."?removepack=".$list[$i]["id"]);
       $t->set_var("remove","<IMG SRC='$edit_img' BORDER='0' ALT='".lang("edit")."' onClick=\"psinst('".$list[$i]["sname"]."',".$list[$i]["rev"].")\">");
       if ($i) $t->parse("packitem","packitemblock",TRUE);
         else $t->parse("packitem","packitemblock");
     }
     $t->set_var("lname",lang("label_packs"));
     $t->set_var("check_update",lang("check_update")); // include link here
     $t->set_var("add",$pvp->link->linkurl($_SERVER["PHP_SELF"]."?addpack=1",lang("add_entry")));
     $t->set_var("head_name",lang("pstplpack_name"));
     $t->set_var("head_rev1",lang("pstplpack_rev1"));
     $t->set_var("head_rev2",lang("pstplpack_rev2"));
     $t->set_var("first",$nextmatch->first);
     $t->set_var("left",$nextmatch->left);
     $t->set_var("right",$nextmatch->right);
     $t->set_var("last",$nextmatch->last);
     $t->parse("packlist","packlistblock");
   }
 }

 $t->pparse("out","template");
 include("../inc/footer.inc");

?>