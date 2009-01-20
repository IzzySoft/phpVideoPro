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
<!-- BEGIN listblock -->
<FORM NAME="admin_cats" METHOD="post" ACTION="{formtarget}">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
<TR><TD>

<DIV STYLE="margin:3;text-align:center">{save_result}</DIV>
<TABLE ALIGN="center" BORDER="1" STYLE="margin:3">
 <TR><TH><DIV ALIGN="center">{head_cat_id}</DIV></TH>
     <TH><DIV ALIGN="center">{head_cat_name}</DIV></TH>
     <TH><DIV ALIGN="center">{head_cat_trans}</DIV></TH>
     <TH><DIV ALIGN="center"><IMG SRC="{tpl_dir}images/trash.gif" ALT="Remove" TITLE="{remove_cat}"></DIV></TH>
     <TH><DIV ALIGN="center"><IMG SRC="{tpl_dir}images/hide.gif" WIDTH="16" ALT="Hide" TITLE="{hide_cat}"></DIV></TH></TR>
<!-- BEGIN catblock -->
 <TR CLASS="content"><TD><DIV ALIGN="right">{cat_id}</DIV></TD>
     <TD><DIV ALIGN="center">{cat_name}</DIV></TD>
     <TD><DIV ALIGN="center">{cat_trans}</DIV></TD>
     <TD><DIV ALIGN="center">{cat_del}</DIV></TD>
     <TD><DIV ALIGN="center">{cat_dis}</DIV></TD></TR>
<!-- END catblock -->
 <TR><TD COLSPAN="4">{hidden}</TD></TR>
</TABLE>
<!-- END listblock -->
<!-- BEGIN delchoiceblock -->
<FORM NAME="admin_cats" METHOD="post" ACTION="{formtarget}">
<INPUT TYPE="hidden" NAME="delete" VALUE="{delete}">
<TABLE ALIGN="center" BORDER="1" STYLE="margin:3">
 <TR><TH ALIGN="center">{msg}</TH></TR>
 <TR CLASS="content"><TD>{upd_all}<BR>{upd_individual}<BR>{upd_none}</TD></TR>
</TABLE>
<!-- END delchoiceblock -->
<!-- BEGIN individualblock -->
<FORM NAME="admin_cats" METHOD="post" ACTION="{formtarget}">
<INPUT TYPE="hidden" NAME="delete" VALUE="{delete}">
<TABLE ALIGN="center" BORDER="1" STYLE="margin:3">
 <TR><TH ALIGN="center" COLSPAN="2">{msg}</TH></TR>
<!-- BEGIN itemblock -->
 <TR CLASS="content"><TD>{title}</TD><TD>{newcat}</TD></TR>
<!-- END itemblock -->
</TABLE>
<!-- END individualblock -->
</TD></TR>

<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD><DIV STYLE="margin:3;text-align:center">{update}</DIV></TD></TR>

</TABLE>
</FORM></TD></TR>
</TABLE>
</DIV>
</TD></TR></TABLE>