<?php
 /***************************************************************************\
 * phpVideoPro                                   (c) 2001 by Itzchak Rehberg *
 * written by Itzchak Rehberg <izzysoft@qumran.org>                          *
 * http://www.qumran.org/homes/izzy/                                         *
 * --------------------------------------------------------------------------*
 * This program is free software; you can redistribute and/or modify it      *
 * under the terms of the GNU General Public License (see doc/LICENSE)       *
 * --------------------------------------------------------------------------*
 * Setup Program                                                             *
 \***************************************************************************/

 /* $Id$ */

  include ("../inc/config.inc");
  
  $title = "phpVideoPro Setup";
?>
<HTML><HEAD>
 <TITLE><? echo $title ?></TITLE>
 <META http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</HEAD>
<BODY>
<H1 ALIGN=CENTER><? echo $title ?></H1>
<P ALIGN=JUSTIFY>Welcome to the Setup Unit of phpVideoPro! Right at the moment,
 this may not look as if it was designed by Armani - but I focussed mainly on
 functionality for now. So I beg your pardon for now - and if I will have some
 spare time in the future, I may go to make a neat design for this :)</P>
<P ALIGN=JUSTIFY>Please select what you are going to do:</P>
<TABLE ALIGN=CENTER WIDTH=90% BORDER=0>
 <TR><TD ALIGN=CENTER WIDTH=33%><A HREF="install.php">Fresh Installation</A></TD>
     <TD ALIGN=CENTER WIDTH=34%><A HREF="update.php">Update existing installation</A></TD>
     <TD ALIGN=CENTER WIDTH=33%><A HREF="configure.php">Configure existing installation</A></TD>
 </TR>
</TABLE>
</BODY></HTML>