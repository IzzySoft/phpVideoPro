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

  $page_id = "admin_disktypes";
  include( dirname(__FILE__) . "/../inc/includes.inc");
  if (!$pvp->auth->admin) kickoff();

  #-------------------------------------------------------[ process input ]---
  if ($submit) {
    for ($i=1;$i<=$lines;++$i) {
      $disk_id = "id_$i"; $mtype = "mtype_$i"; $name = "name_$i"; $size = "size_$i"; $lp = "lp_$i"; $rc = "rc_$i";
      if ( !strlen(trim(${$name})) ) {
        if ( !$db->delete_disktype(${$disk_id}) ) $upd_err .= ${$disk_id} . ",";
      } else {
        if ( !$db->update_disktype(${$disk_id},${$mtype},${$name},${$size},${$lp},${$rc}) )
          $upd_err .= ${$disk_id} . ",";
      }
    }
    if ( strlen(trim($new_name)) ) {
      if ( !$db->update_disktype($new_id,$new_mtype,$new_name,$new_size,$new_lp,$new_rc) )
        $add_err .= ${$disk_id} . ",";
    }
    if ($add_err) {
      $add_err = substr($add_err,0,strlen($add_err)-1);
      $save_result = $colors["err"].lang("disktype_add_failed")."</FONT><BR>";
    }
    if ($upd_err) {
      $upd_err = substr($upd_err,0,strlen($upd_err)-1);
      $save_result .= $colors["err"] . lang("disktype_update_failed",$upd_err) . "</FONT><BR>";
    }
    if ( !($add_err || $upd_err) ) $save_result = $colors["ok"].lang("update_success")."</FONT><BR>";
  }
  #-------------------------------------------------------[ build up page ]---
  $t = new Template($pvp->tpl_dir);
  $t->set_file(array("template"=>"admin_disktypes.tpl"));
  $t->set_block("template","diskblock","disks");

  $t->set_var("listtitle",lang("admin_disktypes"));
  $t->set_var("save_result",$save_result);
  $t->set_var("head_disk_id","ID");
  $t->set_var("head_mtype",lang("mediatype"));
  $t->set_var("head_disk_name",lang("name"));
  $t->set_var("head_size",lang("disk_size"));
  $t->set_var("head_lp",lang("longplay"));
  $t->set_var("head_rc",lang("region_code"));
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

  function make_mtselect($name,$value) {
    GLOBAL $mtypes, $mcount;
    $input = "<SELECT NAME='$name'>";
    for ($i=0;$i<$mcount;++$i) {
      $input .= "<OPTION VALUE='" .$mtypes[$i][id]. "'";
      if ( $value==$mtypes[$i][id] ) $input .= " SELECTED";
      $input .= ">" .$mtypes[$i][sname]. "</OPTION>";
    }
    $input .= "</SELECT>";
    return $input;
  }

  $mtypes = $db->get_mtypes();
  $mcount = count($mtypes);
  $lines  = 0;
  for ($i=0;$i<$mcount;++$i) {
    $dt = $db->get_disktypes($mtypes[$i][id]);
    $dtcount = count($dt);
    for ($k=0;$k<$dtcount;++$k) {
      ++$lines;
      $t->set_var("mtype",make_mtselect("mtype_$lines",$mtypes[$i][id]));
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
      $t->parse("disks","diskblock",TRUE);
    }
  }
  $t->set_var("mtype",make_mtselect("new_mtype",""));
  $input = make_input("new_id","?","button","yesnobutton");
  $t->set_var(disk_id,$input);
  $t->set_var("disk_name",make_input("new_name",""));
  $t->set_var("size",make_input("new_size",""));
  $input = "<INPUT TYPE='checkbox' NAME='new_lp' VALUE='1'>";
  $t->set_var("lp",$input);
  $input = "<INPUT TYPE='checkbox' NAME='new_rc' VALUE='1'>";
  $t->set_var("rc",$input);
  $t->parse("disks","diskblock",TRUE);
  $hidden = "<INPUT TYPE='hidden' NAME='lines' VALUE='$lines'>";
  if (!$pvp->config->enable_cookies) $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='$sess_id'>";
  $t->set_var("hidden",$hidden);
      
  include( dirname(__FILE__) . "/../inc/header.inc");
  $t->pparse("out","template");

  include( dirname(__FILE__) . "/../inc/footer.inc");

?>