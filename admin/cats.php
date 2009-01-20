<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2009 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Administration: Edit categories                                           #
 #############################################################################

 /* $Id$ */

 $page_id = "admin_cats";
 include( dirname(__FILE__) . "/../inc/includes.inc");

 #=================================================[ Register global vars ]===
 $postit = array ("new_name","new_trans","lines");
 foreach ($postit as $var) {
   if (isset($_POST[$var]) && !preg_match("/[^\w\s-\+\pL]/u",$_POST[$var])) $$var = $_POST[$var]; else $$var = "";
 }
 unset($postit);
 if (isset($_GET["delete"]) && !preg_match("/[^\d]/",$_REQUEST["delete"])) $delete = $_GET["delete"]; else $delete = FALSE;

 #==================================================[ Check authorization ]===
 if (!$pvp->auth->admin) kickoff();

 #=====================================================[ Prepare template ]===
 include( dirname(__FILE__) . "/../inc/header.inc");
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"admin_cats.tpl"));
 $t->set_block("template","delchoiceblock","delchoice");
 $t->set_block("template","listblock","list");
 $t->set_block("listblock","catblock","cats");
 $t->set_block("template","individualblock","individual");
 $t->set_block("individualblock","itemblock","item");

 #==========================================================[ Do the Job ]===
 #-------------------------------------------------------[ process input ]---
 if (isset($_POST['delcat'])) {
   switch($_POST['rename']) {
     case "single" :
        $catlist = $db->get_moviecatlist3($_POST["delete"]);
        $totals = count($catlist);
        if ($totals) {
          $catname = $db->get_category($_POST["delete"]);
          $t->set_var("listtitle",lang("delete_cat",$catname));
	  $t->set_var("msg",lang("sel_new_cat"));
          $t->set_var("update","<INPUT TYPE='submit' CLASS='submit' NAME='singlecat' VALUE='".lang("submit")."'>");
          $t->set_var("formtarget",$_SERVER["PHP_SELF"]);
	  $t->set_var("delete",$_POST["delete"]);
          $cats = $db->get_category("","",1);
          $catcount = count($cats);
          $catsel = "";
          for ($i=0;$i<$catcount;++$i) {
            $catsel .= "<OPTION VALUE='".$cats[$i]['id']."'";
	    if ($cats[$i]['id']==$_POST["delete"]) $catsel .= " SELECTED";
	    $catsel .= ">".$cats[$i]['name']."</OPTION>";
          }
	  for($i=0;$i<$totals;++$i) {
	    $selcat = "<SELECT NAME='newcat$i'>$catsel</SELECT>";
	    $t->set_var("title",$catlist[$i]['title']);
	    $t->set_var("newcat",$selcat);
	    $t->parse("item","itemblock",$i);
	  }
	  $t->parse("individual","individualblock");
	  $t->pparse("out","template");
          include( dirname(__FILE__) . "/../inc/footer.inc");
	  exit;
	}
	break;
     case "global" :
        if ($db->change_moviecat($_POST["delete"],$_POST["newcat"])) {
          $delete = $_POST["delete"];
        } else {
          $save_result = "<SPAN CLASS='error'>".lang("cat_update_failed",$cat)."</SPAN><BR>";
        }
        break;
     case "none"   :
     default       : $save_result = "<SPAN CLASS='ok'>".lang("action_canceled")."</SPAN><BR>"; break;
   }
 } elseif (isset($_POST["singlecat"])) {
   $catlist = $db->get_moviecatlist3($_POST["delete"]);
   $totals = count($catlist);
   $ok = TRUE;
   for ($i=0;$i<$totals;++$i) {
     $ok = $ok && $db->change_moviecat($_POST["delete"],$_POST["newcat$i"],array($catlist[$i]["id"]));
   }
   $delete = $_POST["delete"];
 }
 if ($delete) {
   $catlist = $db->get_moviecatlist3($delete);
   $totals = count($catlist);
   if ($totals) {
     $catname = $db->get_category($delete);
     $t->set_var("listtitle",lang("delete_cat",$catname));
     $t->set_var("formtarget",$_SERVER["PHP_SELF"]);
     $t->set_var("update","<INPUT TYPE='submit' CLASS='submit' NAME='delcat' VALUE='".lang("submit")."'>");
     $cats = $db->get_category("","",1);
     $catcount = count($cats);
     $catsel = "<SELECT NAME='newcat'>";
     for ($i=0;$i<$catcount;++$i) {
       $catsel .= "<OPTION VALUE='".$cats[$i]['id']."'";
       if ($cats[$i]['id']==$delete) $catsel .= " SELECTED";
       $catsel .= ">".$cats[$i]['name']."</OPTION>";
     }
     $catsel .= "</SELECT>";
     $global     = "<INPUT TYPE='radio' NAME='rename' VALUE='global' CLASS='checkbox'>&nbsp;".lang("del_cat_global_rename",$catsel);
     $individual = "<INPUT TYPE='radio' NAME='rename' VALUE='single' CLASS='checkbox'>&nbsp;".lang("del_cat_individual_rename");
     $no_rename  = "<INPUT TYPE='radio' NAME='rename' VALUE='none' CLASS='checkbox' CHECKED>&nbsp;".lang("del_cat_no_rename");
     $t->set_var("delete",$delete);
     $t->set_var("upd_all",$global);
     $t->set_var("upd_individual",$individual);
     $t->set_var("upd_none",$no_rename);
     $t->set_var("msg",lang("movies_left_in_cat",$catname,$totals));
     $t->parse("delchoice","delchoiceblock");
     $t->pparse("out","template");
     include( dirname(__FILE__) . "/../inc/footer.inc");
     exit;
   } else {
     if ($db->delete_category($delete)) {
       $save_result = "<SPAN CLASS='ok'>".lang("update_success")."</SPAN><BR>";
     } else {
       $save_result = "<SPAN CLASS='error'>".lang("cat_update_failed",$cat)."</SPAN><BR>";
     }
   }
 } elseif (isset($_POST["submit"])) {
   for ($i=0;$i<$lines;++$i) {
     $cat_id = "cat".$i."_id"; $cat_name = "cat".$i."_name"; $cat_trans = "cat".$i."_trans"; $cat_enabled = "cat".$i."_dis";
     if ( !strlen(trim($_POST[$cat_name])) ) {
       die ( display_error(lang("cat_handle_empty",$_POST[$cat_id])) );
     } else {
       $db->set_translation($_POST[$cat_name],"",$pvp->preferences->get("lang"));
       if (isset($_POST[$cat_enabled])) $catXenabled = $_POST[$cat_enabled]; else $catXenabled = 0;
       if ( !$db->update_category($_POST[$cat_id],$_POST[$cat_name],$catXenabled) ) $cat .= "$i,";
       if ( !$db->set_translation($_POST[$cat_name],$_POST[$cat_trans],$pvp->preferences->get("lang")) ) $trans .= "$i,";
     }
   }
   if ( strlen(trim($new_name)) && strlen(trim($new_trans)) ) {
     if ( !$db->add_category($new_name) ) $cat .= "?,";
     if ( !$db->set_translation($new_name,$new_trans,$pvp->preferences->get("lang")) ) $trans .= "$i,";
     if ($pvp->preferences->get("lang")!="en") $db->set_translation($new_name,$new_trans,"en");
   }
   if (isset($cat)) {
     $cat = substr($cat,0,strlen($cat)-1);
     $save_result = "<SPAN CLASS='error'>".lang("cat_update_failed",$cat)."</SPAN><BR>";
   }
   if (isset($trans)) {
     $trans = substr($trans,0,strlen($trans)-1);
     $save_result .= "<SPAN CLASS='error'>" .lang("cat_trans_update_failed",$trans) . "</SPAN><BR>";
   }
   if ( !(isset($cat) || isset($trans)) ) $save_result = "<SPAN CLASS='ok'>".lang("update_success")."</SPAN><BR>";
   $translations = $db->get_translations( $pvp->preferences->get("lang") );
 }

 #-------------------------------------------------------[ build up page ]---
 $tpl_dir = str_replace($base_path,$base_url,$pvp->tpl_dir);
 $trash_img = $tpl_dir . "/images/trash.gif";

 $t->set_var("listtitle",lang("admin_cats"));
 $t->set_var("head_cat_id","ID");
 $t->set_var("head_cat_name",lang("cat_internal_name"));
 $t->set_var("head_cat_trans",lang("category"));
 $t->set_var("hide_cat",lang("hide_cat"));
 $t->set_var("remove_cat",lang("remove_cat"));
 $t->set_var("update","<INPUT TYPE='submit' CLASS='submit' NAME='submit' VALUE='".lang("update")."'>");

 function make_input($name,$value,$type="text") {
   GLOBAL $form;
   switch($type) {
     case "hidden" : $input = '<INPUT TYPE="hidden" NAME="'.$name.'" VALUE="'.$value.'">'; break;
     case "button" : $input = '<INPUT TYPE="button" NAME="'.$name.'" VALUE="'.$value.'" CLASS="yesnobutton">'; break;
     default       : $input = '<INPUT NAME="'.$name.'" VALUE="'.$value.'" '.$form['addon_tech'].'>'; break;
   }
   return $input;
 }

 $cats = $db->get_category("","",1);
 $catcount = count($cats);
 for ($i=0;$i<$catcount;++$i) {
   $cat_id = "cat".$i."_id"; $cat_name = "cat".$i."_name"; $cat_trans = "cat".$i."_trans";
   $t->set_var("cat_id",make_input($cat_id,$cats[$i]['id'],"button").make_input($cat_id,$cats[$i]['id'],"hidden"));
   $t->set_var("cat_name",make_input($cat_name,$cats[$i]['internal']));
   $t->set_var("cat_trans",make_input($cat_trans,$cats[$i]['name']));
   $url = $pvp->link->slink($_SERVER["PHP_SELF"]."?delete=".$cats[$i]['id']);
   $trash = "<IMG SRC='$trash_img' BORDER='0' ALT='".lang("delete")."' onClick=\"delconfirm('$url')\">";
   $t->set_var("cat_del",$trash);
   if ($cats[$i]['used'] == 0) {
     $checkbox = "<INPUT TYPE='checkbox' NAME='cat".$i."_dis' VALUE='1'";
     if ($cats[$i]['enabled'] == 1) {
       $checkbox .= " CHECKED>";
     } else { $checkbox .= ">"; }
     $t->set_var("cat_dis",$checkbox);
   } else {
     $checkbox = make_input("cat".$i."_dis","9","hidden");
     $t->set_var("cat_dis","&nbsp;".$checkbox);
   }
   if ($i) $t->parse("cats","catblock",TRUE);
     else $t->parse("cats","catblock");
 }
 $t->set_var("cat_dis","&nbsp;");
 $t->set_var("cat_id",make_input("new_id","?","button").make_input("new_id","?","hidden"));
 $t->set_var("cat_name",make_input("new_name",""));
 $t->set_var("cat_trans",make_input("new_trans",""));
 $t->parse("cats","catblock",TRUE);
 if (!isset($save_result)) $save_result = "";
 $t->set_var("save_result",$save_result);
 $t->set_var("formtarget",$_SERVER["PHP_SELF"]);
 $hidden = "<INPUT TYPE='hidden' NAME='lines' VALUE='$catcount'>";
 if (!$pvp->cookie->active) $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>";
 $t->set_var("hidden",$hidden);
      
?>
<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript">
 function delconfirm(url) {
  check = confirm("<?=lang("confirm_delete")?>");
  if (check == true) window.location.href=url;
 }
</SCRIPT>
<?
 $t->parse("list","listblock");
 $t->pparse("out","template");

 include( dirname(__FILE__) . "/../inc/footer.inc");
?>