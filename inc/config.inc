<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # User's configuration file - the only one for the user to edit!            #
 #############################################################################

 /* $Id$ */

 #==========================================================[ directories ]===
 $backup_path= "testdata"; # where to look for backup files. If not given an
                           # absolute path, it will be relative to the PVP path

 #=============================================================[ database ]===
 $database["type"]      = "mysql";    # mysql|pgsql
 $database["host"]      = "localhost";     # your hosts name
 $database["database"]  = "videopro"; # what database holds the tables
 $database["user"]      = "video";     # db user with at least following
                                      # privileges on these tables:
				      # SELECT,UPDATE,INSERT,DELETE
 $database["password"]  = "";  # this users password for the db
?>
