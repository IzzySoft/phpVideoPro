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
 $query = "SELECT id,title,length FROM video"
        . " WHERE cass_id=$cass_id AND mtype_id=$mtype_id";
 $db->dbquery($query);
 while ( $db->next_record() ) {
   $id[] = $db->f('id');
 }

 $label  = new label($template);
 $text   = $label->make_text($id);
 $label->write($cass_id,$text);
 $label->prn();
 $label->destroy();
 
 include("inc/footer.inc");

?>