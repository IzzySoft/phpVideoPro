<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Administration: Edit printers                                             #
 #############################################################################

 /* $Id$ */

 $page_id = "admin_printers";
 include( dirname(__FILE__) . "/../inc/includes.inc");

 #=================================================[ Register global vars ]===
 $postit = array ("new_name","new_unit","new_top","new_left","lines");
 foreach ($postit as $var) {
   $$var = $_POST[$var];
 }
 unset($postit);

 #==================================================[ Check authorization ]===
 if (!$pvp->auth->admin) kickoff();

 #========================================================[ process input ]===
 if ($_POST["submit"]) {
   for ($i=0;$i<$lines;++$i) {
     $print_id = "print".$i."_id"; $print_name = "print".$i."_name";
     $print_unit = "print".$i."_unit"; $print_top = "print".$i."_top";
     $print_left = "print".$i."_left";
     if ( !strlen(trim($_POST[$print_name])) ) {
       $db->set_printer($_POST[$print_id]);
     } else {
       if (!$_POST[$print_top])  ${$print_top}  = 0; else ${$print_top} = $_POST[$print_top];
       if (!$_POST[$print_left]) ${$print_left} = 0; else ${$print_left} = $_POST[$print_left];
       if (!$db->set_printer($_POST[$print_id],$_POST[$print_name],$_POST[$print_unit],${$print_top},${$print_left})) {
         $upd .= ",".$_POST[$print_name];
       }
     }
   }
   if ($upd) {
     $upd = substr($upd,1);
     $save_result = "<SPAN CLASS='error'>".lang("printer_upd_failed",$upd)."</SPAN><BR>";
   } else {
     $save_result = "<SPAN CLASS='ok'>".lang("update_success")."</SPAN><BR>";
   }
   if ( strlen(trim($new_name)) ) {
     if (!$new_top)  $new_top  = 0;
     if (!$new_left) $new_left = 0;
     if ( !$db->set_printer("",$new_name,$new_unit,$new_top,$new_left) ) {
       $save_result .= "<SPAN CLASS='error'>".lang("printer_add_failed")."</SPAN><BR>";
     } else {
       $save_result .= "<SPAN CLASS='ok'>".lang("printer_add_success")."</SPAN><BR>";
     }
   }
 }

 #========================================================[ build up page ]===
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"admin_printers.tpl"));
 $t->set_block("template","itemblock","item");

 $t->set_var("listtitle",lang("admin_printers"));
 $t->set_var("save_result",$save_result);
 $t->set_var("head_print_id","ID");
 $t->set_var("head_print_name",lang("printer_name"));
 $t->set_var("head_print_unit",lang("unit"));
 $t->set_var("head_print_top",lang("top_offset"));
 $t->set_var("head_print_left",lang("left_offset"));
 $t->set_var("update","<INPUT TYPE='submit' CLASS='submit' NAME='submit' VALUE='".lang("update")."'>");
 $t->set_var("formtarget",$_SERVER["PHP_SELF"]);

 function make_input($name,$value,$type="text",$class="yesnobutton") {
   switch($type) {
     case "hidden" : $input = "<INPUT TYPE='hidden' NAME='$name' VALUE='$value'>"; break;
     case "button" : $input = "<INPUT TYPE='button' NAME='$name' VALUE='$value' CLASS='yesnobutton'>"; break;
     default       : $input = "<INPUT NAME='$name' VALUE='$value' CLASS='$class'>"; break;
   }
   return $input;
 }

 function make_unit($name,$value) {
   GLOBAL $db;
   static $units, $ucount;
   if (!$units) {
     $units  = $db->get_units();
     $ucount = count($units);
   }
   $select = "<SELECT NAME='$name'>";
   for ($i=0;$i<$ucount;++$i) {
     $select .= "<OPTION VALUE='".$units[$i][id]."'";
     if ($units[$i][id]==$value) $select .= " SELECTED";
     $select .= ">".$units[$i][unit]."</OPTION>";
   }
   $select .= "</SELECT>";
   return $select;
 }

 $printers = $db->get_printer();
 $pcount = count($printers);
 for ($i=0;$i<$pcount;++$i) {
   $print_id = "print".$i."_id"; $print_name = "print".$i."_name";
   $print_unit = "print".$i."_unit"; $print_top = "print".$i."_top";
   $print_left = "print".$i."_left";
   $t->set_var("print_id",make_input($print_id,$printers[$i]->id,"button").make_input($print_id,$printers[$i]->id,"hidden"));
   $t->set_var("print_name",make_input($print_name,$printers[$i]->name,"text","catinput"));
   $t->set_var("print_unit",make_unit($print_unit,$printers[$i]->unit_id));
   $t->set_var("print_top",make_input($print_top,$printers[$i]->top_offset));
   $t->set_var("print_left",make_input($print_left,$printers[$i]->left_offset));
   $t->parse("item","itemblock",TRUE);
 }
 $t->set_var("print_id",make_input("new_id","?","button").make_input("new_id","","hidden"));
 $t->set_var("print_name",make_input("new_name","","text","catinput"));
 $t->set_var("print_unit",make_unit("new_unit",""));
 $t->set_var("print_top",make_input("new_top",""));
 $t->set_var("print_left",make_input("new_left",""));
 $t->parse("item","itemblock",TRUE);
 $hidden = "<INPUT TYPE='hidden' NAME='lines' VALUE='$pcount'>";
 if (!$pvp->config->enable_cookies)
   $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='".$_GET["sess_id"]."'>";
 $t->set_var("hidden",$hidden);

 include( dirname(__FILE__) . "/../inc/header.inc");
 $t->pparse("out","template");

 include( dirname(__FILE__) . "/../inc/footer.inc");
?>