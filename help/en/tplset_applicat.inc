<? /* list of actors, directors, composers */
 ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
phpVideoPro has a template driven frontend - this means, the look-and-feel can
be accustomized by adding a new template set or modifying an existing one. The
<I>Applicat</I> template set is the first one that benefits from this feature:
before it was added, only the default template set did exist.

[text]
Though the design of the forms does not differ that much from the <I>Default</I>
template set, <I>Applicat</I> looks much smarter plus offers additional
functionality: the title bar of each page contains some quick links, which
where only available by walking through the menus before. Even if these buttons
should be quite self-explaining, the following table will describe their
functionality, which sometimes is different depending on if you are in the
application or in the help section.

[title]
Button explanation

[text]
<TABLE ALIGN="center" WIDTH="90%">
 <COLGROUP><COL WIDTH="14"><COL WIDTH="1*"><COL WIDTH="1*"></COLGROUP>
 <TR><TD>&nbsp;</TD><TD><DIV ALIGN="center"><B>Application</B></DIV></TD>
     <TD><DIV ALIGN="center"><B>Help</B></DIV></TD></TR>
 <TR><TD><INPUT TYPE="image" NAME="button_back" CLASS="imgbut" SRC="{base_url}templates/applicat/images/win_back.gif" WIDTH="14" HEIGHT="13"
></TD>
     <TD><DIV ALIGN="center">-</DIV></TD>
     <TD>Go one step back in history (like the browsers back button)</TD></TR>
 <TR><TD><INPUT TYPE="image" NAME="button_close" CLASS="imgbut" SRC="{base_url}templates/applicat/images/win_close.gif" WIDTH="14" HEIGHT="13"
></TD>
     <TD>LogOff the application and go to the Login Screen</TD>
     <TD>Close the <I>*help#</I> window</TD></TR>
 <TR><TD><INPUT TYPE="image" NAME="button_help" CLASS="imgbut" SRC="{base_url}templates/applicat/images/win_help.gif" WIDTH="14" HEIGHT="13"
></TD>
     <TD>Open window with context help</TD>
     <TD><DIV ALIGN="center">-</DIV></TD></TR>
 <TR><TD><INPUT TYPE="image" NAME="button_home" CLASS="imgbut" SRC="{base_url}templates/applicat/images/win_home.gif" WIDTH="14" HEIGHT="13"
></TD>
     <TD>Go to the <I>*start_page#</I></TD>
     <TD>Go to the <I>*index#</I></TD></TR>
 <TR><TD><INPUT TYPE="image" NAME="button_search" CLASS="imgbut" SRC="{base_url}templates/applicat/images/win_search.gif" WIDTH="14" HEIGHT="13"
></TD>
     <TD>Go to the <I>*search_movie#</I> screen</TD>
     <TD><DIV ALIGN="center">-</DIV></TD></TR>
</TABLE>

[eof]

