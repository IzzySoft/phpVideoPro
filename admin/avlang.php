<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Edit Audio and Subtitle settings                                          #
 #############################################################################

 /* $Id$ */

 #========================================================[ initial setup ]==
# $page_id = "admin_avlang";
 include("../inc/includes.inc");
 if (!$pvp->auth->admin) kickoff();
 if ( isset($_GET["start"]) ) {
   $start = $_GET["start"];
 } elseif ( isset($_POST["start"]) ) {
   $start = $_POST["start"];
 }
 $edit  = $_GET["edit"];
 if (!$start) $start = 0;
 include("../inc/class.nextmatch.inc");

 #===================================================[ initialize template ]==
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"admin_avlang.tpl"));
 $t->set_block("template","listblock","list");
 $t->set_block("template","editblock","edit");
 $t->set_block("listblock","langblock","detail");
 $t->set_var("listtitle",lang($page_id));
 $t->set_var("formtarget",$PHP_SELF ."\" enctype=\"multipart/form-data");

 $t->set_var("head_lang_id","ID");
 $t->set_var("head_lang_charset",lang("charset"));
 $t->set_var("head_lang_name",lang("name"));
 $t->set_var("head_lang_locale",lang("locale"));
 $t->set_var("head_lang_audio",lang("audio_ts"));
 $t->set_var("head_lang_subtitle",lang("subtitle"));

 #====================================================[ edit lang settings ]==
 if ($edit) {
   $lang  = $db->get_langlist($edit);
   $t->set_var("lang_id",$lang->id);
   $t->set_var("lang_name",$lang->name);
   $audio = "<INPUT TYPE='radio' NAME='audio' VALUE='0' CLASS='checkbox'";
   if (!$lang->audio) $audio .= " CHECKED";
   $audio .= ">".lang("state_inactive")."<BR>"
          . "<INPUT TYPE='radio' NAME='audio' VALUE='1' CLASS='checkbox'";
   if ($lang->audio) $audio .= " CHECKED";
   $audio .= ">".lang("state_active");
   $t->set_var("lang_audio",$audio);
   $audio = "<INPUT TYPE='radio' NAME='subtitle' VALUE='0' CLASS='checkbox'";
   if (!$lang->subtitle) $audio .= " CHECKED";
   $audio .= ">".lang("state_inactive")."<BR>"
          . "<INPUT TYPE='radio' NAME='subtitle' VALUE='1' CLASS='checkbox'";
   if ($lang->subtitle) $audio .= " CHECKED";
   $audio .= ">".lang("state_active");
   $t->set_var("lang_subtitle",$audio);
   $t->set_var("update","<INPUT TYPE='submit' NAME='update' VALUE='".lang("update")."'>");
   $hidden = "<INPUT TYPE='hidden' NAME='lang_id' VALUE='".$lang->id."'>";
   if (!$pvp->config->enable_cookies) $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='$sess_id'>";
   if ($start) $hidden .= "<INPUT TYPE='hidden' NAME='start' VALUE='$start'>";
   $t->set_var("hidden",$hidden);
   $t->parse("edit","editblock",TRUE);
   include("../inc/header.inc");
   $t->pparse("out","template");
   include("../inc/footer.inc");
   exit;
 }

 #====================================================[ process form input ]==
 if ( isset($_POST["update"]) ) {
   $success = @$db->set_avlang("$lang_id",$audio,"audio");
   if ($success) $success = @$db->set_avlang("$lang_id",$subtitle,"subtitle");
   if ($success) $save_result = "<SPAN CLASS='ok'>".lang("update_success")."</SPAN>";
     else $save_result = "<SPAN CLASS='error'>".lang("update_failed")."</SPAN>";
   $t->set_var("save_result",$save_result);
 }

 #====================================[ get languages and setup variables ]===
 $query = "\$db->get_langlist('',$start)";
 $nextmatch = new nextmatch ($query,$pvp->tpl_dir,$PHP_SELF,$start);

 $list = $nextmatch->list;
 $details = array ("id","name","charset");
 $yesno["no"]  = $yesno[0] = "not_ok.gif";
 $yesno["yes"] = $yesno[1] = "ok.gif";
 for ($i=0;$i<$nextmatch->listcount -1;++$i) {
   foreach ($details as $var) {
     $t->set_var("lang_".$var,$list[$i]->$var);
   }
   $t->set_var("lang_locale",$yesno[strtolower($list[$i]->available)]);
   $t->set_var("lang_audio",$yesno[$list[$i]->audio]);
   $t->set_var("lang_subtitle",$yesno[$list[$i]->subtitle]);
   $t->set_var("lang_edit","$PHP_SELF"."?edit=".$list[$i]->id."&start=$start");
   $t->parse("detail","langblock",TRUE);
 }
# if ($update) $db->lang_available($targetlang,1);
 $hidden = "";
 if ($start) $hidden .= "<INPUT TYPE='hidden' NAME='start' VALUE='$start'>";
 if (!$pvp->config->enable_cookies) $hidden .= "<INPUT TYPE='hidden' NAME='sess_id' VALUE='$sess_id'>";
 $t->set_var("hidden",$hidden);
 $t->set_var("first",$nextmatch->first);
 $t->set_var("left",$nextmatch->left);
 $t->set_var("right",$nextmatch->right);
 $t->set_var("last",$nextmatch->last);
 $t->parse("list","listblock");

 include("../inc/header.inc");
 $t->pparse("out","template");
 include("../inc/footer.inc");
?>