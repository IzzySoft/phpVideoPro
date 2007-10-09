<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Add a new entry into database                                             #
 #############################################################################

 /* $Id$ */

 if (!isset($_REQUEST["part"])) $new_entry=TRUE;
 if ($_POST["cancel"]) {
   header("Location: ".$_POST["referer"]);
   exit;
 }
 include("edit.php");

?>