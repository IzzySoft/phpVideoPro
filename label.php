<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 \***************************************************************************/

 /* $Id$ */

 $silent = TRUE;
 include("inc/header.inc");
 include("inc/label.inc");

 if (!$template) $template = "default"; 
 $query = "SELECT title,length FROM video"
        . " WHERE cass_id=$cass_id AND mtype_id=$mtype_id";
 $db->dbquery($query);
 $i = 0;
 while ( $db->next_record() ) {
   $title  = $db->f('title');
   $len = $db->f('length');
   $len_min = $len % 60; if ($len_min < 10) $len_min = "0" . $len_min;
   $length = floor($len / 60) . ":" . $len_min;
   $text[] = "$title   $length";
   ++$i;
 }

 $label  = new label($template);
 $label->write($cass_id,$text);
 $label->prn();
 $label->destroy();
 
 include("inc/footer.inc");

?>