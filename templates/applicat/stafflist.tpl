<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle"><DIV STYLE="margin:2">{listtitle}</DIV></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{home_title}" NAME="button_home" CLASS="imgbut" SRC="{tpl_dir}images/win_home.gif" STYLE="width:14;height:13;" onClick="window.location.href='{home_link}'"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{search_title}" NAME="button_search" CLASS="imgbut" SRC="{tpl_dir}images/win_search.gif" STYLE="width:14;height:13;" onClick="window.location.href='{search_link}'"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{help_title}" NAME="button_help" CLASS="imgbut" SRC="{tpl_dir}images/win_help.gif" STYLE="width:14;height:13;" onClick="{help_link}"></TD>
     <TD CLASS="wintitle" STYLE="vertical-align:middle;margin-right:3;"><DIV STYLE="width:18;">
      <INPUT TYPE="image" TITLE="{logoff_title}" NAME="button_close" CLASS="imgbut" SRC="{tpl_dir}images/win_close.gif" STYLE="width:14;height:13;" onClick="window.location.href='{logoff_link}'"></DIV></TD></TR>
</TABLE></TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD>

<DIV STYLE="margin:3">
<TABLE ALIGN="center" BORDER="0">
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="right">{right}{last}</DIV></TD></TR>
 <TR><TD COLSPAN="2">
  <TABLE ALIGN="center" BORDER="0" WIDTH="100%" CLASS="data">
   <TR><TH>{stafftype}</TH><TH>{title}</TH>
      <TH>{category}</TH><TH>{length}</TH>
      <TH WIDTH="85">{medianr}</TH></TR>
   <!-- BEGIN itemblock -->
   <TR CLASS="content"><TD>{name}{namesep}{firstname}</TD><TD>{title}</TD><TD>{category}</TD><TD>{length}</TD><TD><A HRef="{url}">{mtype} {nr}</A></TD></TR>
   <!-- END itemblock -->
   <!-- BEGIN notfoundblock -->
   <TR><TD COLSPAN="5">{not_found}</TD></TR>
   <!-- END notfoundblock -->
  </Table>
 </TD></TR>
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="right">{right}{last}</DIV></TD></TR>
</TABLE>
</DIV>

</TD></TR>
</TABLE>
</DIV>
</TD></TR></TABLE>