<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="*" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER=0" ALIGN="center"><TR><TD>
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

<DIV STYLE="margin:3;text-align:center">{save_result}</DIV>
<FORM NAME="admin_disks" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="1" STYLE="margin:3">
 <TR><TH><DIV ALIGN="center">{head_disk_id}</DIV></TH>
     <TH><DIV ALIGN="center">{head_mtype}</DIV></TH>
     <TH><DIV ALIGN="center">{head_disk_name}</DIV></TH>
     <TH><DIV ALIGN="center">{head_size}</DIV></TH>
     <TH><DIV ALIGN="center">{head_lp}</DIV></TH>
     <TH><DIV ALIGN="center">{head_rc}</DIV></TH>
     <TH>&nbsp;</TH></TR>
<!-- BEGIN diskblock -->
 <TR CLASS="content"><TD><DIV ALIGN="center">{disk_id}</DIV></TD>
     <TD><DIV ALIGN="center">{mtype}</DIV></TD>
     <TD><DIV ALIGN="center">{disk_name}</DIV></TD>
     <TD><DIV ALIGN="center">{size}</DIV></TD>
     <TD><DIV ALIGN="center">{lp}</DIV></TD>
     <TD><DIV ALIGN="center">{rc}</DIV></TD>
     <TD><DIV ALIGN="center">{trash}</DIV></TD></TR>
<!-- END diskblock -->
 <TR><TD COLSPAN="7">{hidden}</TD></TR>
</TABLE>

</TD></TR>

<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD><DIV STYLE="margin:3;text-align:center">{update}</DIV></TR>
</FORM>

</TABLE>
</DIV>
</TD></TR></TABLE>