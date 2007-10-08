<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Register Global Vars                                                      #
 #############################################################################

 /* $Id$ */

 while ( list($vn,$vv)=each($_ENV) ) {
   if ( !isset($$vn) ) $$vn = $vv;
 }
 while ( list($vn,$vv)=each($_SERVER) ) {
   if ( !isset($$vn) ) $$vn = $vv;
 }
 while ( list($vn,$vv)=each($_POST) ) {
   if ( !isset($$vn) ) $$vn = $vv;
 }
 while ( list($vn,$vv)=each($_GET) ) {
   if ( !isset($$vn) ) $$vn = $vv;
 }

# $_COOKIES does not need to be globalized (is referred to directly in
#           class.cookie.inc)
# $_REQUEST does just list up all $_GET, $_POST and $_COOKIE vars
# $_FILES is not used (yet?) in this application so we don't need it either
# $_SESSION is not needed since we use our own session management

?>