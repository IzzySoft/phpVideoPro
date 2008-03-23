<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2008 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Installation/Update/Removal of PSLabel Packs                              #
 #############################################################################

 /* $Id$ */

 #========================================================[ initial setup ]==
 $page_id = "admin_psinstall";
 $nomenue = 1;
 $dl_base_url = "http://www.izzysoft.de/ftp/net/div/izzysoft/";
 $info_url = "http://projects.izzysoft.de/progs/phpvideopro/inc/pspacks.txt";
 include("../inc/includes.inc");
 $install_dir = $base_path."pslabels";
 $nolog = FALSE; // suppress log output for installation progress

 #-------------------------------------------------[ Register global vars ]---
 # Permanent vars: name, rev
 # action-based: download, install, remove
 if (is_numeric($_REQUEST["rev"])) $rev = (int) $_REQUEST["rev"]; else $rev = 0;
 if ($pvp->common->req_is_alnum("name")) $name = $_REQUEST["name"];

 if (isset($_REQUEST["download"])) $download = TRUE; else $download = FALSE;
 if (isset($_REQUEST["install"]))  $install = TRUE;  else $install = FALSE;
 if (isset($_REQUEST["remove"]))   $remove = TRUE;   else $remove = FALSE;
 if (isset($_REQUEST["remove_files"])) $remove_files = TRUE; else $remove_files = FALSE;
 if (isset($_REQUEST["noinst"]))   $noinst = TRUE;   else $noinst = FALSE;

 #--------------------------------------------------[ Check authorization ]---
 if (!$pvp->auth->admin) kickoff();
 $save_result = "";

 #------------------------------------------------[ Check Name & Revision ]---
 if (!$noinst&&$download||$install||$remove) {
   include("../inc/header.inc");
   echo "<BR><TABLE CLASS='window' ALIGN='center'><TR><TD>\n";
 }

 if (empty($name)) { // if no pspack specified, go (back) to overview
    header("Location: ".$pvp->link->url_path(dirname(__FILE__))."ps_templates.php");
    exit;
 }
 if (empty($rev)) { // get latest revision if not given
   olog(lang("psinst_search_rev",$name));
   $file  = @file($info_url);
   $lines = count($file);
   if (empty($file) || empty($lines)) {
     display_error(lang("psinst_no_rev_file_found"));
     exit;
   }
   for ($i=0;$i<$lines;++$i) {
     $line = trim($file[$i]);
     if (!strlen($line)) continue; // skip empty lines
     if (strpos($line,"#")===0) continue; // skip comments
     $arg = explode(':',$line);
     if ($arg[0]==$name) {
       if (!empty($arg[2])) $arg[1].=$arg[2]; // URL in creator may contain ':'
       $arr = explode(';',$arg[1]);
       $rev = $arr[0];
       break;
     }
   }
   if (empty($rev)) { // no revision given, and none found online
     display_error(lang("psinst_no_rev_found",$name));
     exit;
   }
   olog(lang("psinst_found_rev",$rev));
 }
 $pack_name = $name.$rev;
 $pack_info_file = $name.".pvlp";

 #==================================================[ process the changes ]===
 function olog($msg,$lev="-") {
   GLOBAL $nolog;
   if ($nolog) return;
   if ($lev=="!") echo "<SPAN CLASS='error'>! $msg</SPAN><BR>\n";
   else echo "<SPAN CLASS='ok'>$lev $msg</SPAN><BR>\n";
   flush();
 }

 #----------------------------------------[ unpack tarball from websource ]---
 if ($download) {
   if ($noinst) {
     header("Location: ".$dl_base_url.$pack_name.".tgz");
     exit;
   }
   if (!is_writable($install_dir)) {
     display_error(lang("psinst_target_not_rw"));
     exit;
   }
   include("../inc/class.archive.inc");
   $arc = new archive;
   olog(lang("psinst_log_unpack",$pack_name.".tgz"));
   if (!$arc->unpack($dl_base_url.$pack_name.".tgz",$install_dir)) {
     display_error(lang("psinst_unpack_archive_failed"));
     exit;
   }
   $install = TRUE;
 }

 #-------------[ parse the pspack info file and register the pack with DB ]---
 if ($install) {
   $pack_full_filename = $install_dir."/".$pack_info_file;
   if (!file_exists($pack_full_filename)) {
     display_error(lang("psinst_packinfo_not_found",$pack_info_file));
     exit;
   }
   $file = @file($pack_full_filename);
   if (empty($file)) {
     display_error(lang("psinst_packinfo_empty",$pack_info_file));
     exit;
   }
   olog(lang("psinst_log_read_packinfo"));
   $lines = count($file);
   $k = 0;
   for ($i=0;$i<$lines;++$i) {
     $line = trim($file[$i]);
     if (!strlen($line)) continue; // skip empty lines
     if (strpos($line,"#")===0) continue; // skip comments
     $arg = explode(':',$line);
     switch ($arg[0]) {
       case "rev"  : $pack->rev     = (int) $arg[1]; break;
       case "pack" : $arr = explode(';',$arg[1]);
                     $pack->sname   = $arr[1];
                     $pack->name    = $arr[2];
                     $pack->descript= $arr[3];
                     $pack->creator = $arr[4];
                     $pack_id = $db->register_pslabel_pack($pack);
                     break;
       case "file" : $arr = explode(';',$arg[1]);
                     $label[$k]->pack_id = (int) $pack_id;
                     $label[$k]->type    = (int) $arr[0];
                     $label[$k]->description = $arr[1];
                     $label[$k]->eps_filename= $arr[2];
                     $label[$k]->ps_filename = $arr[3];
                     $label[$k]->llx         = (int) $arr[4];
                     $label[$k]->lly         = (int) $arr[5];
                     $label[$k]->urx         = (int) $arr[6];
                     $label[$k]->ury         = (int) $arr[7];
                     ++$k; break;
     } // end switch
   } // end lines
   if (!$pack_id) {
     display_error(lang("psinst_pack_reg_failed"));
     exit;
   }
   if (!isset($pack->sname) || !isset($label[0]->eps_filename)) {
     display_error(lang("psinst_packinfo_invalid",$pack_info_file));
     exit;
   }
   olog(lang("psinst_log_reg_epsfiles"));
   $files = count($label);
   $reg_fail = array();
   for ($i=0;$i<$files;++$i) {
     if (!$db->register_pslabel($label[$i])) $reg_fail[] = $label[$i]->eps_filename;
   }
   $errors = count($reg_fail);
   if ($errors) {
     olog(lang("psinst_log_regged_epsfiles",$errors),"!");
     for ($i=0;$i<$errors;++$i) {
       olog($reg_fail[$i],"!");
     }
   } else {
     olog(lang("psinst_log_regged_epsfiles",$errors));
   }
 } // end install

 #--------------------[ Unregister PSPack and optionally remove its files ]---
 if ($remove) {
   // Get the pack id by re-registering a dummy
   $pack->rev = $rev; $pack->sname = $name;
   $ipack = $db->get_pspack_by_name($name);
   $pack_id = $ipack["id"];
   olog(lang("psinst_log_remove_pack",$name,$pack_id));
   $file = $db->get_pspack_epsfiles($pack_id);
   $files = count($file);
   for ($i=0;$i<$files;++$i) { // check for thumbnails
     $thumb = "thumbs/".str_replace(".eps",".jpg",$file[$i]);
     if (file_exists($install_dir.$pvp->config->os_slash.$thumb)) $file[] = $thumb;
   }
   if (file_exists($install_dir.$pvp->config->os_slash."thumbs".$pvp->config->os_slash.$pack->sname."_preview.jpg"))
     $file[] = "thumbs".$pvp->config->os_slash.$pack->sname."_preview.jpg";
   $files = count($file);
   if ($_REQUEST["remove_files"]) {
     if (is_writable($install_dir)) {
       olog(lang("psinst_log_remove_files"));
       $reg_fail = array();
       for ($i=0;$i<$files;++$i) {
         if (!@unlink($install_dir.$pvp->config->os_slash.$file[$i]))
           $reg_fail[] = $file[$i];
       }
     } else {
       olog(lang("psinst_unreg_norw"),"!");
       for ($i=0;$i<$files;++$i) olog($file[$i],"!");
     }
   } else {
     olog(lang("psinst_unreg_norw"));
     for ($i=0;$i<$files;++$i) olog($file[$i]);
   }
   olog(lang("psinst_deregister_pspack"));
   $success = $db->deregister_pslabel_pack($pack_id,TRUE);
   $errors = count($reg_fail);
   if ($errors && $success) olog(lang("psinst_unregd_pspack",$name,$errors),"!");
   elseif (!$success) olog(lang("psinst_unreg_pspack_failed",$name),"!");
   else olog(lang("psinst_unregd_pspack",$name,$errors));
 }

 #-----------------------------------------------------[ End Installation ]---
 if ($install||$remove) {
   olog(lang("psinst_log_finished"));
   echo "</TD></TR></TABLE>\n";
   include("../inc/footer.inc");
   exit;
 }

 #===================================================[ build initial form ]===
 include("../inc/header.inc");
 $pack = $db->get_pspack_by_name($name);
?>
<SCRIPT TYPE="text/javascript" LANGUAGE="JavaScript">
 function delconfirm(url) {
  check = confirm("<?=lang("confirm_delete")?>");
  if (check == true) window.location.href=url;
 }
</SCRIPT>
<?
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"delete.tpl"));

 $details = "<H3>".lang("psinst_action_select")."</H3>\n<UL>";
 // Download
 $details .= "<LI>".$pvp->link->linkurl($_SERVER["PHP_SELF"]."?name=$name;rev=$rev;download=1;noinst=1",lang("psinst_query_download",$name))."</LI>\n";
 // Download & Install
 if (is_writable($install_dir))
   $details .= "<LI>".$pvp->link->linkurl($_SERVER["PHP_SELF"]."?name=$name;download=1",lang("psinst_query_dlinst",$name))."</LI>\n";
 else $details .= "<LI CLASS='greytext'>".lang("psinst_query_dlinst",$name)."</LI>\n";
 // Install
 if (file_exists("$install_dir/$pack_info_file"))
   $details .= "<LI>".$pvp->link->linkurl($_SERVER["PHP_SELF"]."?name=$name;rev=$rev;install=1",lang("psinst_query_inst",$name,$rev))."</LI>\n";
 else $details .= "<LI CLASS='greytext'>".lang("psinst_query_inst",$name,$rev)."</LI>\n";
 // UnRegister
 if (!empty($pack["rev"]))
   $details .= "<LI>".$pvp->link->linkurl($_SERVER["PHP_SELF"]."?name=$name;rev=$rev;remove=1",lang("psinst_query_remove",$name))."</LI>\n";
 else $details .= "<LI CLASS='greytext'>".lang("psinst_query_remove",$name)."</LI>\n";
 // UnInstall
 if (!empty($pack["rev"])&&is_writable($install_dir))
   $details .= "<LI>".$pvp->link->linkurl($_SERVER["PHP_SELF"]."?name=$name;rev=$rev;remove=1;remove_files=1",lang("psinst_query_remove_files",$name))."</LI>\n";
 else $details .= "<LI CLASS='greytext'>".lang("psinst_query_remove_files",$name)."</LI>\n";
 $details .= "</UL>\n";

 $t->set_var("listtitle",lang("psinst_title"));
 $t->set_var("details",$details);
 $t->pparse("out","template");

 include("../inc/footer.inc");
?>