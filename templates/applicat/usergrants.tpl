<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0" ALIGN="center"><TR><TD>
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
<FORM NAME="admin_users" METHOD="post" ACTION="{formtarget}">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
<TR><TD>

<DIV STYLE="margin:3;text-align:center">{save_result}</DIV>
<TABLE BORDER="1" STYLE="margin-left:auto; margin-right:auto;margin-bottom:5px;">
 <TR><TH><DIV ALIGN="center">{head_users}</DIV></TH>
     <TH COLSPAN="4"><DIV ALIGN="center">{head_access}</DIV></TH>
     <TH><DIV ALIGN="center">{head_actions}</DIV></TH></TR>
 <TR><TH><DIV ALIGN="center">{head_login}</DIV></TH>
     <TH><DIV ALIGN="center">{head_browse}</DIV></TH>
     <TH><DIV ALIGN="center">{head_add}</DIV></TH>
     <TH><DIV ALIGN="center">{head_upd}</DIV></TH>
     <TH><DIV ALIGN="center">{head_del}</DIV></TH>
     <TH><DIV ALIGN="center">{head_delete}&nbsp;</DIV></TH></TR>
<!-- BEGIN itemblock -->
 <TR CLASS="content">
     <TD>{user_id}{login}</TD>
     <TD><DIV ALIGN="center">{browse}</DIV></TD>
     <TD><DIV ALIGN="center">{add}</DIV></TD>
     <TD><DIV ALIGN="center">{upd}</DIV></TD>
     <TD><DIV ALIGN="center">{del}</DIV></TD>
     <TD><DIV ALIGN="center">{delete}</DIV></TD>
     </TR>
<!-- END itemblock -->
</TABLE></TD></TR>

<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD><TABLE WIDTH="100%" BORDER="0" STYLE="margin:3">
 <TR><TD STYLE="text-align:center;">{update}</TD></TR>
</TABLE>

{hidden}
</TD></TR></TABLE>
</FORM></TD></TR>
</TABLE>
</DIV>
</TD></TR></TABLE>