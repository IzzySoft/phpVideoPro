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
<TR><TD style="text-align:center">

 <TABLE STYLE="margin:3;text-align:center;" BORDER="1" ALIGN="center"><TR CLASS="content"><TD>
 <FORM NAME="medianr" METHOD="post" ACTION="{form_target}">
  <TABLE ALIGN="center" BORDER="0" WIDTH="400">
    <TR><TH COLSPAN="3"><DIV ALIGN="center">{latest}</DIV></TH></TR>
    <TR CLASS="content"><TD COLSPAN="3"><DIV ALIGN="center">{latest_box}</DIV></TD></TR>
    <TR CLASS="content"><TD COLSPAN="3">&nbsp;</TD></TR>
    <TR CLASS="content"><TH WIDTH="45%"><DIV ALIGN="center">{orig}</DIV></TH>
        <TD WIDTH="10%">&nbsp;</TD>
        <TH WIDTH="45%"><DIV ALIGN="center">{new}</DIV></TH></TR>
    <TR CLASS="content"><TD WIDTH="45%"><DIV ALIGN="center">{o_mtype} {o_medianr}-{o_part}</DIV></TD>
        <TD WIDTH="10%">&nbsp;</TD>
        <TD WIDTH="45%"><DIV ALIGN="center">{n_mtype} {n_medianr}-{n_part}</DIV></TD></TR>
  </TABLE>
 </TD></TR></TABLE>

</TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD><DIV STYLE="margin:3">
 <TABLE ALIGN="center" BORDER="0">
  <TD WIDTH="50%" STYLE="text-align:left">{copy}</TD>
  <TD WIDTH="50%" STYLE="text-align:right">{change}</TD></TR>
 </TABLE></DIV></FORM>
</TR></TD>
</TABLE>
</DIV>
</TD></TR></TABLE>