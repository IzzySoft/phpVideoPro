<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2003 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Administration: Clean up pvp_config and preferences table                 #
 # included by update.php for updates from versions <= 0.4.8                 #
 #############################################################################

 /* $Id$ */

 ####################################################[ CleanUp pvp_config ]###
 echo $colors["ok"] . " <LI>Cleaning up config table:";
 $rows = 0;
 $details = array ("rw_media","remove_empty_media","site","enable_cookies",
                   "expire_cookies","session_purgetime");
 foreach ($details as $var) {
   $db->query("SELECT MIN(id) AS min FROM pvp_config WHERE name='$var'");
   if ( $db->next_record() ) $id = $db->f('min');
   if ($id) {
     $db->query("DELETE FROM pvp_config WHERE name='$var' AND id>$id");
     if ( $db->affected_rows() ) ++$rows;
   }
 }
 echo " Found and removed duplicates for $rows entries.</FONT><BR>\n";

 ###################################################[ CleanUp preferences ]###
 echo $colors["ok"] . " <LI>Cleaning up preferences table:";
 $rows = 0;
 $details = array ("lang","template","display_limit","date_format",
                   "page_length","default_movie_colorid","default_movie_onlabel",
                   "default_movie_toneid","printer_id","colors");
 foreach ($details as $var) {
   $db->query("SELECT MIN(id) AS min FROM preferences WHERE name='$var'");
   if ( $db->next_record() ) $id = $db->f('min');
   if ($id) {
     $db->query("DELETE FROM preferences WHERE name='$var' AND id>$id");
     if ( $db->affected_rows() ) ++$rows;
   }
 }
 echo " Found and removed duplicates for $rows entries.</FONT><BR>\n";

?>