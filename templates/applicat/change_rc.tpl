<BR STYLE="margin-top:30">
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0" ALIGN="center"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle"><DIV STYLE="margin:2">{listtitle}</DIV></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" NAME="button_home" CLASS="imgbut" SRC="{tpl_dir}images/win_home.gif" WIDTH="14" HEIGHT="13" onClick="window.location.href='{home_link}'"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" NAME="button_search" CLASS="imgbut" SRC="{tpl_dir}images/win_search.gif" WIDTH="14" HEIGHT="13" onClick="window.location.href='{search_link}'"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" NAME="button_help" CLASS="imgbut" SRC="{tpl_dir}images/win_help.gif" WIDTH="14" HEIGHT="13" onClick="{help_link}"></TD>
     <TD CLASS="wintitle" STYLE="vertical-align:middle;margin-right:3;"><DIV STYLE="width:18;">
      <INPUT TYPE="image" NAME="button_close" CLASS="imgbut" SRC="{tpl_dir}images/win_close.gif" WIDTH="14" HEIGHT="13" onClick="window.location.href='{logoff_link}'"></DIV></TD></TR>
</TABLE></TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD>

 <TABLE STYLE="margin:3;text-align:center" BORDER="1"><TR CLASS="content"><TD>
 <FORM NAME="rcChange" METHOD="post" ACTION="{form_target}">
  <TABLE ALIGN="center" BORDER="0" WIDTH="400">
    {hidden}
<!-- BEGIN disktypeblock -->
    <TR><TH WIDTH="45%"><DIV ALIGN="center">{orig}</DIV></TH>
        <TD WIDTH="10%">&nbsp;</TD>
        <TH WIDTH="45%"><DIV ALIGN="center">{new}</DIV></TD></TR>
    <TR><TD WIDTH="45%"><DIV ALIGN="center">{o_disktype}</DIV></TD>
        <TD WIDTH="10%">&nbsp;</TD>
        <TD WIDTH="45%"><DIV ALIGN="center">{n_disktype}</DIV></TD></TR>
    <TR><TD COLSPAN="3">&nbsp;</TD></TR>
    <TR><TD COLSPAN="3"><HR></TD></TR>
<!-- END disktypeblock -->
    <TR><TH COLSPAN="3">{rc_head}</TH></TR>
    <TR><TD COLSPAN="3"><DIV ALIGN="center">{rc}</DIV></TD></TR>
  </TABLE>
 </TD></TR></TABLE>

</TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD><DIV STYLE="margin:3;text-align:center">{change}</DIV></TD></TR>
</TABLE></FORM>
</DIV>
</TD></TR></TABLE>