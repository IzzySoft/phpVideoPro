<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Administration: Edit categories                                           #
 #############################################################################

 /* $Id$ */

  $page_id = "admin_cats";
  include( dirname(__FILE__) . "/../inc/includes.inc");

  #-------------------------------------------------------[ process input ]---
  if ($submit) {
    for ($i=0;$i<$lines;++$i) {
      $cat_id = "cat".$i."_id"; $cat_name = "cat".$i."_name"; $cat_trans = "cat".$i."_trans";
      if ( !strlen(trim(${$cat_name})) && !strlen(trim(${$cat_trans})) ) {
        $catlist = $db->get_moviecatlist3(${$cat_id});
	$totals = count($catlist);
	if ($totals) {
	  $catname = $db->get_category(${$cat_id});
	  die ( display_error(lang("movies_left_in_cat",$catname,$totals)) );
	} else {
	  $db->delete_category(${$cat_id});
	}
      } else {
        $db->set_translation(${$cat_name},"",$pvp->preferences->get("lang"));
        if ( !$db->update_category(${$cat_id},${$cat_name}) ) $cat .= "$i,";
        if ( !$db->set_translation(${$cat_name},${$cat_trans},$pvp->preferences->get("lang")) ) $trans .= "$i,";
      }
    }
    if ( strlen(trim($new_name)) && strlen(trim($new_trans)) ) {
      if ( !$db->add_category($new_name) ) $cat .= "?,";
      if ( !$db->set_translation($new_name,$new_trans,$pvp->preferences->get("lang")) ) $trans .= "$i,";
    }
    if ($cat) {
      $cat = substr($cat,0,strlen($cat)-1);
      $save_result = $colors["err"].lang("cat_update_failed",$cat)."</FONT><BR>";
    }
    if ($trans) {
      $trans = substr($trans,0,strlen($trans)-1);
      $save_result .= $colors["err"] . lang("cat_trans_update_failed",$trans) . "</FONT><BR>";
    }
    if ( !($cat || $trans) ) $save_result = $colors["ok"].lang("update_success")."</FONT><BR>";
    $translations = $db->get_translations( $pvp->preferences->get("lang") );
  }

  #-------------------------------------------------------[ build up page ]---
  $t = new Template($pvp->tpl_dir);
  $t->set_file(array("template"=>"admin_cats.tpl"));
  $t->set_block("template","catblock","cats");

  $t->set_var("listtitle",lang("admin_cats"));
  $t->set_var("save_result",$save_result);
  $t->set_var("head_cat_id","ID");
  $t->set_var("head_cat_name",lang("cat_internal_name"));
  $t->set_var("head_cat_trans",lang("category"));
  $t->set_var("update","<INPUT TYPE='submit' NAME='submit' VALUE='".lang("update")."'>");

  function make_input($name,$value,$type="text") {
    GLOBAL $form;
    switch($type) {
      case "hidden" : $input = "<INPUT TYPE='hidden' NAME='$name' VALUE='$value'>"; break;
      case "button" : $input = "<INPUT TYPE='button' NAME='$name' VALUE='$value' CLASS='yesnobutton'>"; break;
      default       : $input = "<INPUT NAME='$name' VALUE='$value' ".$form["addon_tech"].">"; break;
    }
    return $input;
  }

  $cats = $db->get_category();
  $catcount = count($cats);
  for ($i=0;$i<$catcount;++$i) {
    $cat_id = "cat".$i."_id"; $cat_name = "cat".$i."_name"; $cat_trans = "cat".$i."_trans";
    $t->set_var("cat_id",make_input($cat_id,$cats[$i][id],"button").make_input($cat_id,$cats[$i][id],"hidden"));
    $t->set_var("cat_name",make_input($cat_name,$cats[$i][internal]));
    $t->set_var("cat_trans",make_input($cat_trans,$cats[$i][name]));
    $t->parse("cats","catblock",TRUE);
  }
  $t->set_var("cat_id",make_input("new_id","?","button").make_input("new_id","?","hidden"));
  $t->set_var("cat_name",make_input("new_name",""));
  $t->set_var("cat_trans",make_input("new_trans",""));
  $t->parse("cats","catblock",TRUE);
  $t->set_var("lines",$catcount);

  include( dirname(__FILE__) . "/../inc/header.inc");
  $t->pparse("out","template");

  include( dirname(__FILE__) . "/../inc/footer.inc");

?>