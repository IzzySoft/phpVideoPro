<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * User's configuration file - the only one for the user to edit!            *
 \***************************************************************************/

 /* $Id$ */

$base_url   = "/local/phpvideo/";
// the root directory of phpVideoPro
$base_path  = "/usr/src/cvs/website/local/phpvideo/";

// database settings
$database["host"]      = "linux";
//$database["host"]      = "localhost";
$database["database"]  = "video_demo";
$database["database"]  = "videopro";
$database["user"]      = "guest";
$database["password"]  = "";

// some default settings
$defaults["scolor"] = 2; // 1=b/w, 2=color, 3=3d - if you didn't change sth. :)
?>