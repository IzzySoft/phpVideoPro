<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
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
 $base_url   = "/local/phpvideo/";
 # path relative to web server's DOCUMENT_ROOT
 $base_path  = "/usr/src/local/cvs/website/local/phpvideo/"; # absolute file systems path

 #=============================================================[ database ]===
 $database["type"]      = "mysql";    # mysql|pgsql
 $database["host"]      = "zion";     # your hosts name
 $database["database"]  = "videopro"; # what database holds the tables
 $database["user"]      = "izzy";     # db user with at least following
                                      # privileges on these tables:
				      # SELECT,UPDATE,INSERT,DELETE
 $database["password"]  = "chumash";  # this users password for the db
?>
