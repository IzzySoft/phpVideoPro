<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Display Informations                                                      #
 #############################################################################

 /* $Id$ */

 include("inc/includes.inc");
 $action = $_REQUEST["action"];
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("info"=>"info.tpl"));

 switch ($action) {
   case "update": $title   = lang("info_update");
                  $details = lang("info_noupdate",$version);
                  break;
   default      : $title   = lang("info_common");
                  $details = lang("info_common_info",$version,$_SERVER["SERVER_NAME"]);
                  break;
 }

 include("inc/header.inc");
 $t->set_var("listtitle",$title);
 $t->set_var("details",$details);
 $t->pparse("out","info");

 include("inc/footer.inc");
?>