<BR STYLE="margin-top:30">
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0" ALIGN="center"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle"><DIV STYLE="margin:2">{listtitle}</DIV></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{home_title}" NAME="button_home" CLASS="imgbut" SRC="{tpl_dir}images/win_home.gif" WIDTH="14" HEIGHT="13" onClick="window.location.href='{home_link}'"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{search_title}" NAME="button_search" CLASS="imgbut" SRC="{tpl_dir}images/win_search.gif" WIDTH="14" HEIGHT="13" onClick="window.location.href='{search_link}'"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{help_title}" NAME="button_help" CLASS="imgbut" SRC="{tpl_dir}images/win_help.gif" WIDTH="14" HEIGHT="13" onClick="{help_link}"></TD>
     <TD CLASS="wintitle" STYLE="vertical-align:middle;margin-right:3;"><DIV STYLE="width:18;">
      <INPUT TYPE="image" TITLE="{logoff_title}" NAME="button_close" CLASS="imgbut" SRC="{tpl_dir}images/win_close.gif" WIDTH="14" HEIGHT="13" onClick="window.location.href='{logoff_link}'"></DIV></TD></TR>
</TABLE></TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD>

<DIV STYLE="margin:3;text-align:center">{save_result}</DIV>

 <FORM NAME="medialength" METHOD="post" ACTION="{form_target}">
  {hidden_fields}
  <TABLE STYLE="margin:3;text-align:center" BORDER="1" WIDTH="400">
    <TR><TH STYLE="margin:5;text-align:center">{info}</TH></TR>
    <TR CLASS="content"><TD><DIV ALIGN="center">{input}</DIV></TD></TR>
  </TABLE>

</TD></TR>
<TR><TD><DIV STYLE="text-align:center;margin:3;">{submit}</DIV></TD></TR>
</TABLE></FORM>

</DIV>
</TD></TR></TABLE>