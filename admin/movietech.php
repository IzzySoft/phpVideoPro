<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Administration: Management of technical movie data (media types etc.)     #
 #############################################################################

 /* $Id$ */

 $page_id = "admin_movietech";
 include("../inc/includes.inc");

 #=================================================[ Register global vars ]===
 $postit = array ("name","sname","id");
 foreach ($postit as $var) {
   if (isset($_POST[$var])) $$var = $_POST[$var]; else $$var = FALSE;
 }
 $postit = array ("type","delete","edit","add");
 foreach ($postit as $var) {
   if (isset($_REQUEST[$var])) $$var = $_REQUEST[$var]; else $$var = FALSE;
 }
 unset($postit);

 #==================================================[ Check authorization ]===
 if (!$pvp->auth->admin) kickoff();

 #==================================================[ process the changes ]===
 if (isset($_POST["update"])) {
   switch($type) {
     case "pict"  : $success = $db->set_pict($name,$sname,$id); break;
     case "color" : $success = $db->set_color($name,$sname,$id); break;
     case "mtype" : $success = $db->set_mtypes($name,$sname,$id); break;
     case "tone"  : $success = $db->set_tone($name,$sname,$id); break;
     default      :
   }
   if ($success) {
     $save_result = "<SPAN CLASS='ok'>" .lang("update_success") . ".</SPAN><BR>\n";
   } else {
     echo "<p><br></p>Inserting Name($name), sName($sname), ID($id)<br>\n";
   }
 }

 #=======================================================[ build the form ]===
 include("../inc/header.inc");
 #-------------------------------------------------------[ init templates ]---
 $tpl_dir = str_replace($base_path,$base_url,$pvp->tpl_dir);
 $edit_img  = $tpl_dir . "/images/edit.png";
 $trash_img = $tpl_dir . "/images/trash.png";
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"admin_movietech.tpl"));
 $t->set_block("template","mainblock","main");
 $t->set_block("template","mlinkblock","mlink");
 $t->set_block("mainblock","screenitemblock","screen");
 $t->set_block("mainblock","coloritemblock","color");
 $t->set_block("mainblock","mtypeitemblock","mtype");
 $t->set_block("mainblock","toneitemblock","tone");
 $t->set_block("template","editblock","edit");

 #----------------------------------------------------------[ edit screen ]---
 if ($edit) {
   switch($type) {
     case "pict"  : $t->set_var("edit_title",lang("screen"));
                    $item = $db->get_pict($edit);
                    break;
     case "color" : $t->set_var("edit_title",lang("picture"));
                    $item = $db->get_color($edit);
                    break;
     case "mtype" : $t->set_var("edit_title",lang("mediatype"));
                    $titem = $db->get_mtypes("id=".$edit);
                    $item = $titem[0]; unset($titem);
                    break;
     case "tone"  : $t->set_var("edit_title",lang("tone"));
                    $item = $db->get_tone($edit);
                    break;
     default      :
   }
   $t->set_var("name_name",lang("name"));
   $t->set_var("name",$item['name']);
   $t->set_var("sname_name",lang("sname"));
   $t->set_var("sname",$item['sname']);
   $t->set_var("type",$type);
   $t->set_var("id",$edit);
   $t->set_var("add",lang("update"));
   $t->set_var("main",""); # disable list
   $t->parse("edit","editblock");
 } elseif ($add) {
   switch($add) {
     case "pict"   : $t->set_var("edit_title",lang("screen"));
                     break;
     case "color"  : $t->set_var("edit_title",lang("picture"));
                     break;
     case "mtype"  : $t->set_var("edit_title",lang("mediatype"));
                     break;
     case "tone"   : $t->set_var("edit_title",lang("tone"));
                     break;
     default       :
   }
   $t->set_var("name_name",lang("name"));
   $t->set_var("sname_name",lang("sname"));
   $t->set_var("type",$add);
   $t->set_var("add",lang("create"));
   $t->set_var("main",""); # disable list
   $t->parse("edit","editblock");
 } else {
   if ($delete) {
     $ref = $db->check_movietechref($type,$delete);
     if ($ref) {
       echo "<SCRIPT LANGUAGE='JavaScript'>alert('"
            .lang("movies_left_reference",$ref)."');</SCRIPT>";
       $success = FALSE;
     } else {
       switch($type) {
         case "pict"  : $success = $db->set_pict("","",$delete); break;
         case "color" : $success = $db->set_color("","",$delete); break;
         case "mtype" : $success = $db->set_mtypes("","",$delete); break;
         case "tone"  : $success = $db->set_tone("","",$delete); break;
         default      :
       }
     }
     if ($success) {
       $save_result = "<SPAN CLASS='ok'>" .lang("update_success"). ".</SPAN><BR>\n";
     } else {
       $save_result = "<SPAN CLASS='error'>" .lang("update_failed"). "</SPAN><BR>\n";
     }
   }

   #-------------------------------------------------------[ screen block ]---
   $picts = $db->get_pict();
   $pictcount = count($picts);
   for ($i=0;$i<$pictcount;++$i) {
     $t->set_var("item_name",$picts[$i]['name']);
     $t->set_var("item_sname",$picts[$i]['sname']);
     $edit  = $pvp->link->linkurl($_SERVER["PHP_SELF"]."?type=pict&edit=" .$picts[$i]['id'],"<IMG SRC='$edit_img' BORDER='0'>");
     $url   = $pvp->link->slink($_SERVER["PHP_SELF"]."?type=pict&delete=".$picts[$i]['id']);
     $trash = "<IMG SRC='$trash_img' BORDER='0' onClick=\"delconfirm('$url')\">";
     $t->set_var("edit",$edit);
     $t->set_var("trash",$trash);
     if ($i) $t->parse("screen","screenitemblock",TRUE);
       else $t->parse("screen","screenitemblock");
   }
   $t->set_var("screen_title",lang("screen"));
   $t->set_var("screen_add",$pvp->link->linkurl($_SERVER["PHP_SELF"]."?add=pict",lang("add_entry")));

   #--------------------------------------------------------[ color block ]---
   $colors = $db->get_color();
   $colorcount = count($colors);
   for ($i=0;$i<$colorcount;++$i) {
     $t->set_var("item_name",$colors[$i]['name']);
     $t->set_var("item_sname",$colors[$i]['sname']);
     $edit  = $pvp->link->linkurl($_SERVER["PHP_SELF"]."?type=color&edit=" .$colors[$i]['id'],"<IMG SRC='$edit_img' BORDER='0'>");
     $url   = $pvp->link->slink($_SERVER["PHP_SELF"]."?type=color&delete=".$colors[$i]['id']);
     $trash = "<IMG SRC='$trash_img' BORDER='0' onClick=\"delconfirm('$url')\">";
     $t->set_var("edit",$edit);
     $t->set_var("trash",$trash);
     if ($i) $t->parse("color","coloritemblock",TRUE);
       else $t->parse("color","coloritemblock");
   }
   $t->set_var("color_title",lang("picture"));
   $t->set_var("color_add",$pvp->link->linkurl($_SERVER["PHP_SELF"]."?add=color",lang("add_entry")));

   #-------------------------------------------------------[ mtypes block ]---
   $mtypes = $db->get_mtypes();
   $mtypecount = count($mtypes);
   for ($i=0;$i<$mtypecount;++$i) {
     $t->set_var("item_name",$mtypes[$i]['name']);
     $t->set_var("item_sname",$mtypes[$i]['sname']);
     $edit  = $pvp->link->linkurl($_SERVER["PHP_SELF"]."?type=mtype&edit=" .$mtypes[$i]['id'],"<IMG SRC='$edit_img' BORDER='0'>");
     $url   = $pvp->link->slink($_SERVER["PHP_SELF"]."?type=mtype&delete=".$mtypes[$i]['id']);
     $trash = "<IMG SRC='$trash_img' BORDER='0' onClick=\"delconfirm('$url')\">";
     $t->set_var("edit",$edit);
     $t->set_var("trash",$trash);
     if ($i) $t->parse("mtype","mtypeitemblock",TRUE);
       else $t->parse("mtype","mtypeitemblock");
   }
   $t->set_var("mtype_title",lang("mediatype"));
   $t->set_var("mtype_add",$pvp->link->linkurl($_SERVER["PHP_SELF"]."?add=mtype",lang("add_entry")));

   #---------------------------------------------------------[ tone block ]---
   $tones = $db->get_tone();
   $tonecount = count($tones);
   for ($i=0;$i<$tonecount;++$i) {
     $t->set_var("item_name",$tones[$i]['name']);
     $t->set_var("item_sname",$tones[$i]['sname']);
     $edit  = $pvp->link->linkurl($_SERVER["PHP_SELF"]."?type=tone&edit=" .$tones[$i]['id'],"<IMG SRC='$edit_img' BORDER='0'>");
     $url   = $pvp->link->slink($_SERVER["PHP_SELF"]."?type=tone&delete=".$tones[$i]['id']);
     $trash = "<IMG SRC='$trash_img' BORDER='0' onClick=\"delconfirm('$url')\">";
     $t->set_var("edit",$edit);
     $t->set_var("trash",$trash);
     if ($i) $t->parse("tone","toneitemblock",TRUE);
       else $t->parse("tone","toneitemblock");
   }
   $t->set_var("tone_title",lang("tone"));
   $t->set_var("tone_add",$pvp->link->linkurl($_SERVER["PHP_SELF"]."?add=tone",lang("add_entry")));

   $t->set_var("name",lang("name"));
   $t->set_var("sname",lang("sname"));
   $t->parse("main","mainblock");
 
   $t->set_var("edit",""); # remove editblock
   $t->set_var("admin_avlang",$pvp->link->linkurl("avlang.php",lang("admin_avlang")));
   $t->parse("mlink","mlinkblock");
?>
<SCRIPT LANGUAGE="JavaScript">
 function delconfirm(url) {
  check = confirm("<?=lang("confirm_delete")?>");
  if (check == true) window.location.href=url;
 }
</SCRIPT>
<?
 } // end "else" for edit/add/delete

 $t->set_var("listtitle",lang("admin_movietech"));
 $t->set_var("formtarget",$_SERVER["PHP_SELF"]);
 if (!isset($save_result)) $save_result = "";
 $t->set_var("save_result",$save_result);

 $hidden = "";
 if (!$pvp->cookie->active) $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_REQUEST["sess_id"]."'>";
 $t->set_var("hidden",$hidden);
 $t->pparse("out","template");

 include("../inc/footer.inc");
?>