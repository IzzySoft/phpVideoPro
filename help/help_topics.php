<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Help System: Create the Help Index                                        *
 \***************************************************************************/

 /* $Id$ */

  headline("intro");
   li("about");
   li("history");
  headline("menues");
   li("edit");
    li("add_entry",2);
    li("configuration",2);
   li("filter");
    li("set_filter",2);
    li("unset_filter",2);
   li("view");
    li("medialist",2);
    li("actors",2);
    li("directors",2);
    li("music",2);
    li("taperest_absolute",2);
    li("taperest_filtered",2);
   li("print");
    li("label",2);
  headline("other_pages");
   li("view_entry");
  headline("howto");
   li("howto_lang");
   li("howto_help");
   li("howto_templates");
   li("howto_label");
?>