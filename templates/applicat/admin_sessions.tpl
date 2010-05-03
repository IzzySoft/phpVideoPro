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

<DIV STYLE="margin:3">
<TABLE ALIGN="center" BORDER="0" STYLE="border:2px ridge;">
   <TR CLASS="content">
       <TD NOWRAP WIDTH="50%"><FORM NAME="old_sessions" METHOD="post" ACTION="{formtarget}" STYLE="margin-bottom:0;">{hidden}<DIV ALIGN="center">{old_sess} <INPUT CLASS="submit" TYPE="submit" NAME="submit" VALUE="{submit}"></DIV></FORM></TD>
       <TD NOWRAP WIDTH="50%"><FORM NAME="ended_sessions" METHOD="post" ACTION="{formtarget}" STYLE="margin-bottom:0;">{hidden}<DIV ALIGN="center">{ended_sess} <INPUT CLASS="submit" TYPE="submit" NAME="ended" VALUE="{submit}"></DIV></FORM></TD></TR>
</TABLE>
<BR>
 <TABLE BORDER="0" WIDTH="100%">
   <TR><TD>{first}{left}</TD><TD><DIV ALIGN="right">{right}{last}</DIV></TD></TR>
 </TABLE>
 <TABLE ALIGN="center" BORDER="0" STYLE="border:2px ridge;">
 <TR><TH><DIV ALIGN="center">{head_sess_id}</DIV></TH>
     <TH><DIV ALIGN="center">{head_sess_ip}</DIV></TH>
     <TH><DIV ALIGN="center">{head_sess_user}</DIV></TH>
     <TH><DIV ALIGN="center">{head_sess_start}</DIV></TH>
     <TH><DIV ALIGN="center">{head_sess_dla}</DIV></TH>
     <TH><DIV ALIGN="center">{head_sess_end}</DIV></TH>
     <TH><DIV ALIGN="center">{head_sess_action}</DIV></TH></TR>
<!-- BEGIN itemblock -->
 <TR CLASS="content"><TD><DIV ALIGN="right">{sess_id}</DIV></TD>
     <TD><DIV ALIGN="center">{sess_ip}</DIV></TD>
     <TD><DIV ALIGN="center">{sess_user}</DIV></TD>
     <TD><DIV ALIGN="center">{sess_start}</DIV></TD>
     <TD><DIV ALIGN="center">{sess_dla}</DIV></TD>
     <TD><DIV ALIGN="center">{sess_end}</DIV></TD>
     <TD><DIV ALIGN="center">{sess_action}</DIV></TD></TR>
<!-- END itemblock -->
</TABLE>
<TABLE BORDER="0" WIDTH="100%">
   <TR><TD>{first}{left}</TD><TD><DIV ALIGN="right">{right}{last}</DIV></TD></TR>
 </TABLE>
</DIV>

</TABLE>
</DIV>
</TD></TR></TABLE>