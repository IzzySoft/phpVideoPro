<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # prepare for db update: check wether all given actors/director etc. are in #
 # db and obtain their IDs, construct the SQL update statement as well as    #
 # debug output, and finally do the update                                   #
 #############################################################################

 /* $Id$ */

 $details = array("director_name","director_fname","composer_name","composer_fname");
 foreach ($details as $var) {
   ${$var} = $pvp->common->input2string(${$var});
   if ( ( bool ) !ini_get( 'magic_quotes_gpc' ) ) ${$var} = addslashes(${$var});
 }
 $dmsg = "";
 $dmsg     .= "<SPAN CLASS='ok'><b>Preparing Update</b>:</SPAN><p>";
 $dmsg     .= "<ul>\n";
 $query     = "SELECT id FROM directors";
 $sub_query = "INSERT INTO directors";
 $dir_id    = insert_person("director",$query,$sub_query,$director_name,$director_fname);
 $query     = "SELECT id FROM music";
 $sub_query = "INSERT INTO music";
 $mus_id    = insert_person("composer",$query,$sub_query,$composer_name,$composer_fname);
 for ($i=1;$i<=$max["actors"];$i++) {
   $act       = "actor" . $i;
   $aname     = $act . "_name";
   $fname     = $act . "_fname";
   $aid       = "act" . $i . "_id";
   $query     = "SELECT id FROM actors";
   $sub_query = "INSERT INTO actors";
   if ( ( bool ) !ini_get( 'magic_quotes_gpc' ) ) {
     ${$aid}    = insert_person($act,$query,$sub_query,addslashes($pvp->common->input2string(${$aname})),addslashes($pvp->common->input2string(${$fname})));
   } else {
     ${$aid}    = insert_person($act,$query,$sub_query,$pvp->common->input2string(${$aname}),$pvp->common->input2string(${$fname}));
   }
 }
 $dmsg .= "</ul>\n";
 debug("S",$dmsg);
?>