<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
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
   if (!isset($ps)) $ps[0]->desc = $ps[0]->type_id = $ps[0]->eps_file = $ps[0]->ps_file = $ps[0]->llx = $ps[0]->lly = $ps[0]->urx = $ps[0]->ury = "";
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
<SCRIPT LANGUAGE="JavaScript">
 function delconfirm(url) {
  check = confirm("<?=lang("confirm_delete")?>");
  if (check == true) window.location.href=url;
 }
</SCRIPT>
<?
   $tpl_dir = str_replace($base_path,$base_url,$pvp->tpl_dir);
   $edit_img  = $tpl_dir . "/images/edit.png";
   $trash_img = $tpl_dir . "/images/trash.png";
   $query = "\$db->get_pstemplates(\"\",$start)";
   $nextmatch = new nextmatch ($query,$pvp->tpl_dir,$_SERVER["PHP_SELF"],$start);
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
   $t->set_var("add",$pvp->link->linkurl($_SERVER["PHP_SELF"]."?add=1",lang("add_entry")));
   $t->set_var("head_desc",lang("pstpl_name"));
   $t->set_var("head_type",lang("pstpl_type"));
   $t->set_var("first",$nextmatch->first);
   $t->set_var("left",$nextmatch->left);
   $t->set_var("right",$nextmatch->right);
   $t->set_var("last",$nextmatch->last);
   $t->parse("list","listblock");
 }

 $t->pparse("out","template");
 include("../inc/footer.inc");

?>