<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2003 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Edit Translations                                                         #
 #############################################################################

 /* $Id$ */

 #========================================================[ initial setup ]==
 $page_id = "admin_translations";
 include("../inc/includes.inc");
 if (!$pvp->auth->browse) kickoff();
 $filter = get_filters();
 if (!$start) $start = 0;
 include("../inc/class.nextmatch.inc");

 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("list"=>"admin_translations.tpl"));
 $t->set_block("list","mtitleblock","mtitlelist");
 $t->set_block("list","mdatablock","mdatalist");
 $t->set_block("list","emptyblock","emptylist");
 $t->set_var("listtitle",lang($page_id));

 #======================================================[ init target lang ]==
 if (!$targetlang) {
   $sel_lang = "<SELECT NAME='targetlang'>";
   $langs    = $db->get_languages();
   $lcount   = count($langs);
   for ($i=0;$i<$lcount;++$i) {
     $sel_lang .= "<OPTION VALUE='".$langs[$i]["id"]."'>".$langs[$i]["name"]."</OPTION>";
   }
   $sel_lang .= "</SELECT>";
   $t->set_var("sel_lang_title",lang("sel_target_lang"));
   $t->set_var("sel_lang",$sel_lang);
   $t->parse("emptylist","emptyblock");
   $t->set_var("submit",lang("submit"));
   include("../inc/header.inc");
   $t->pparse("out","list");
   include("../inc/footer.inc");
   exit;
 }

 #========================================================[ save lang file ]==
 if ($savelang) {
   $langs = $db->get_languages();
   $lcount = count($langs);
   for($i=0;$i<$lcount;++$i) {
     if ($langs[$i]["id"] == $targetlang) {
       $tlang = $langs[$i]["name"];
       $tchar = $langs[$i]["charset"];
       break;
     }
   }
   if (!$tchar) $tchar = "iso-8859-15";
   $trans = $db->get_singletrans($targetlang);
   $totals = count($trans["xlist"]);
   $sql   = "# ========================================================\n"
          . "# $tlang Language File created by phpVideoPro v".$version."\n"
          . "# ========================================================\n\n"
          . "UPDATE languages SET charset='$tchar' WHERE lang_id='$targetlang';\n";
   for ($i=0;$i<$totals;++$i) {
     $msgid = $trans["xlist"][$i];
     $sql .= "INSERT INTO lang VALUES ('$msgid','$targetlang','".addslashes($trans[$msgid])."');\n";
   }
   header("Content-type: application/octet-stream");
   header("Content-Disposition: attachment; filename=lang_".$targetlang.".sql");
   echo $sql;
   exit;
 }

 #=======================================[ get movies and setup variables ]===
 $query = "\$db->get_singletrans(\"en\",$start)";
 $nextmatch = new nextmatch ($query,$pvp->tpl_dir,$PHP_SELF."?targetlang=$targetlang",$start);

 $list = $nextmatch->list;
 for ($i=0;$i<$nextmatch->listcount -1;$i++) {
   $msgid  = $list["xlist"][$i];
   if ($submit) $db->set_translation($msgid,${$msgid."_trans"},$targetlang);
   $orig   = $list["$msgid"];
   $target = $db->get_singletrans($targetlang,"",$msgid);
   if ($target[$msgid]) $target[$msgid] = htmlentities($target[$msgid]);
   if ($orig) $orig = htmlentities($orig);
   $t->set_var("code",$msgid);
   $t->set_var("orig",$orig);
   $rows  = ceil( strlen($orig)/40 ) +1;
   $input = "<TEXTAREA NAME='$msgid"."_trans' COLS='50' ROWS='$rows'>".$target[$msgid]."</TEXTAREA>";
   $t->set_var("trans",$input);
   $t->set_var("sample","");
   $t->parse("mdatalist","mdatablock",TRUE);
 }
 if ($submit) $db->lang_available($targetlang,1);
 $hidden = "<INPUT TYPE='hidden' NAME='targetlang' VALUE='$targetlang'>";
 if ($start) $hidden .= "<INPUT TYPE='hidden' NAME='start' VALUE='$start'>";
 $t->set_var("code",lang("trans_code"));
 $t->set_var("orig",lang("orig_trans","en"));
 $t->set_var("trans",lang("target_trans",$targetlang));
 $t->set_var("sample",lang("trans_sample"));
 $t->set_var("submit",lang("update"));
 $t->set_var("save","<A HREF='$PHP_SELF?targetlang=$targetlang&savelang=1'>".lang("save_lang_file")."</A>");
 $t->set_var("hidden",$hidden);
 $t->set_var("first",$nextmatch->first);
 $t->set_var("left",$nextmatch->left);
 $t->set_var("right",$nextmatch->right);
 $t->set_var("last",$nextmatch->last);
 $t->parse("mtitlelist","mtitleblock");

 include("../inc/header.inc");
 $t->pparse("out","list");
 include("../inc/footer.inc");

?>