<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2009 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Users configuration file - the only one for the user to edit!             #
 #############################################################################

 /* $Id$ */

 #==========================================================[ directories ]===
 $backup_path= "testdata"; # where to look for backup files. If not given an
                           # absolute path, it will be relative to the PVP path

 #=============================================================[ database ]===
 $database["type"]      = "mysql";     # mysql|pgsql|sqlite
 $database["host"]      = "localhost"; # your hosts name (SQLite: Ignored)
 $database["database"]  = "videopro";  # what database holds the tables
                                       # (SQLite: name of the datafile)
 $database["user"]      = "video";     # db user with at least following
                                       # privileges on these tables:
				       # SELECT,UPDATE,INSERT,DELETE
				       # (SQLite: Ignored)
 $database["password"]  = "c3p0";      # this users password for the db
                                       # (SQLite: Ignored)
?>
