<?php
 #############################################################################
 # phpVideoPro                                   (c) 2001 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Setup Program                                                             #
 #############################################################################

 /* $Id$ */

  include ("../inc/config.inc");
  include("css.inc");
  $title = "phpVideoPro Setup";

?>
<HTML><HEAD>
 <TITLE><?=$title?></TITLE>
 <META http-equiv="Content-Type" content="text/html; charset=iso-8859-15">
</HEAD>
<BODY>
<H1 ALIGN=CENTER><?=$title?></H1>
<TABLE ALIGN="CENTER" WIDTH="90%" BORDER="0">
 <TR><TH>Welcome to the Setup Unit of phpVideoPro!</TH></TR>
 <TR><TD><DIV ALIGN="center"><P><BR>Please select what you are going to do:</P>
     <TABLE WIDTH="90%" BORDER="1">
      <COLGROUP><COL WIDTH="33%" ALIGN="center"><COL WIDTH="34%"><COL WIDTH="33%"></COLGROUP>
      <TR><TD ALIGN="center"><A HREF="install.php">Fresh Installation/Restore</A></TD>
          <TD ALIGN="center"><A HREF="update.php">Update existing installation</A></TD>
          <TD ALIGN="center"><A HREF="configure.php">Configure existing installation</A></TD></TR>
     </TABLE></DIV></TD></TR>
</TABLE></BODY></HTML>