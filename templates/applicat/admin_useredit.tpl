<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="95%" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER=0" ALIGN="center"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle"><DIV STYLE="margin:2">{listtitle}</DIV></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" NAME="button_help" CLASS="imgbut" SRC="{tpl_dir}images/win_help.gif" WIDTH="14" HEIGHT="13" onClick="{help_link}"></TD>
     <TD CLASS="wintitle" STYLE="vertical-align:middle;"><DIV STYLE="width:20;text-align:center;">
      <INPUT TYPE="image" NAME="button_close" CLASS="imgbut" SRC="{tpl_dir}images/win_close.gif" WIDTH="14" HEIGHT="13" onClick="window.location.href='{logoff_link}'"></DIV></TD></TR>
</TABLE></TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD>

<DIV STYLE="margin:3;text-align:center">{save_result}</DIV>
<FORM NAME="admin_users" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="0" STYLE="margin:3"><TR><TD>
<TABLE WIDTH="100%" BORDER="1">
 <!-- COLGROUP><COL WIDTH="50%"><COL WIDTH="50%"></COLGROUP -->
 <TR><TH COLSPAN="2"><DIV ALIGN="center">{head_users}</DIV></TH></TR>
 <TR CLASS="content"><TD COLSPAN="2"><DIV ALIGN="right">{user_id}</DIV></TH></TR>
 <TR CLASS="content"><TD>{head_login}</TD><TD>{login}</TD></TR>
 <TR CLASS="content"><TD>{head_comment}</TD><TD>{comment}</TD></TR>
 <TR CLASS="content"><TD>{head_password}</TD><TD>{password}</TD></TR>
 <TR CLASS="content"><TD>{head_password2}</TD><TD>{password2}</TD></TR>
</TABLE></TD></TR><TR><TD>
<TABLE WIDTH="100%" BORDER="1">
 <!-- COLGROUP><COL WIDTH="80%"><COL WIDTH="20%"></COLGROUP -->
 <TR><TH COLSPAN="2"><DIV ALIGN="center">{head_access}</DIV></TH></TR>
 <TR CLASS="content"><TD>{head_browse}</TD><TD><DIV ALIGN="center">{browse}</DIV></TD></TR>
 <TR CLASS="content"><TD>{head_add}</TD><TD><DIV ALIGN="center">{add}</DIV></TD></TR>
 <TR CLASS="content"><TD>{head_upd}</TD><TD><DIV ALIGN="center">{upd}</DIV></TD></TR>
 <TR CLASS="content"><TD>{head_del}</TD><TD><DIV ALIGN="center">{del}</DIV></TD></TR>
 <TR CLASS="content"><TD>{head_isadmin}</TD><TD><DIV ALIGN="center">{isadmin}</DIV></TD></TR>
</TABLE></TD></TR><TR><TD>
</TD></TR>
{hidden}
</TABLE>

</TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD><TABLE WIDTH="100%" BORDER="0" STYLE="margin:3">
 <TR><TD><DIV ALIGN="center">{update}</DIV></TH>
     <TD><DIV ALIGN="center">{adduser}</DIV></TH></TR>
</TABLE></TR></TD>
</FORM>

</TABLE>
</DIV>
</TD></TR></TABLE>