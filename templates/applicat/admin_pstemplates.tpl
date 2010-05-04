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
<FORM NAME="admin_epstemplates" METHOD="post" ACTION="{formtarget}">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
<TR><TD>

<!-- BEGIN packlistblock -->
<TABLE ALIGN="center" BORDER="0" STYLE="margin:3">
 <TR><TD COLSPAN="4"><TABLE WIDTH="100%" BORDER="0">
     <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="center">{lname}</DIV></TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR></TABLE></TD></TR>
  <TR><TH><DIV ALIGN="center">{head_name}</DIV></TH>
      <TH><DIV ALIGN="center">{head_rev1}</DIV></TH>
      <TH><DIV ALIGN="center">{head_rev2}</DIV></TH>
      <TH><DIV ALIGN="center">{add}</DIV></TH></TR>
<!-- BEGIN packitemblock -->
  <TR CLASS="content"><TD>{pname}</TD>
      <TD><DIV ALIGN="center">{prev1}</DIV></TD>
      <TD><DIV ALIGN="center">{prev2}</DIV></TD>
      <TD><TABLE ALIGN="center"><TR><TD WIDTH="23">{info}</TD><TD WIDTH="23">{edit}</TD><TD WIDTH="23">{actions}</TD></TR></TABLE></TR>
<!-- END packitemblock -->
 <TR><TD COLSPAN="4"><TABLE WIDTH="100%" BORDER="0">
     <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="center">{check_update}</DIV></TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR></TABLE></TD></TR>
</TABLE>
<!-- END packlistblock -->
<!-- BEGIN packviewblock -->
<TABLE ALIGN="center" BORDER="0" CLASS="data" STYLE="margin:3px;">
  <TR CLASS="content"><TH><DIV ALIGN="center">{tname}</DIV></TH><TD>{name}</TD></TR>
  <TR CLASS="content"><TH><DIV ALIGN="center">{tcreator}</DIV></TH><TD>{creator}</TD></TR>
  <TR CLASS="content"><TH><DIV ALIGN="center">{tdesc}</DIV></TH><TD>{desc}</TD></TR>
  <TR CLASS="content"><TH><DIV ALIGN="center">{trev}</DIV></TH><TD>{rev}</TD></TR>
  <TR CLASS="content"><TD COLSPAN="2"><DIV ALIGN="center">{preview}</DIV></TD></TR>
</TABLE>
<!-- END packviewblock -->

<!-- BEGIN listblock -->
<TABLE ALIGN="center" BORDER="0" STYLE="margin:3">
 <TR><TD COLSPAN="4"><TABLE WIDTH="100%" BORDER="0">
     <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="center">{lname}</DIV></TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR></TABLE></TD></TR>
 <TR><TD COLSPAN="2"><TABLE ALIGN="center" BORDER="0" CLASS="data">
  <TR><TH><DIV ALIGN="center">{head_desc}</DIV></TH>
      <TH><DIV ALIGN="center">{head_type}</DIV></TH>
      <TH><DIV ALIGN="center">{add}</DIV></TH></TR>
<!-- BEGIN itemblock -->
  <TR CLASS="content"><TD>{desc}</TD>
      <TD><DIV ALIGN="center">{type}</DIV></TD>
      <TD><DIV ALIGN="center">{edit}&nbsp;{remove}</DIV></TR>
<!-- END itemblock -->
 </TABLE></TD></TR>
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
</TABLE>
<!-- END listblock -->
<!-- BEGIN editblock -->
<DIV STYLE="margin:3;text-align:center">{save_result}</DIV>
<TABLE ALIGN="center" BORDER="0" CLASS="data" STYLE="table-layout:fixed;margin:3px;">
  <COLGROUP><COL WIDTH="50%"><COL WIDTH="50%"></COLGROUP>
  <TR CLASS="content"><TH COLSPAN="2"><DIV ALIGN="center">{pack}</DIV></TH></TR>
  <TR CLASS="content"><TD><DIV ALIGN="center">{desc}</DIV></TD><TD><DIV ALIGN="center">{type}</DIV></TD></TR>
  <TR CLASS="content"><TD><DIV ALIGN="center">{gfx_file}</DIV></TD><TD><DIV ALIGN="center">{dsn_file}</DIV></TD></TR>
  <TR CLASS="content"><TD><DIV ALIGN="center">{lower_left}</DIV></TD><TD><DIV ALIGN="center">{upper_right}</DIV></TD></TR>
</TABLE>
  <TR><TD BGCOLOR="#AAAAAA" COLSPAN="2"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
  <TR><TD BGCOLOR="#FFFFFF" COLSPAN="2"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
  <TR><TD COLSPAN="2"><DIV STYLE="margin:3;text-align:center"><INPUT CLASS="submit" TYPE="submit" NAME="submit" VALUE="{button}"></DIV></TD></TR>
<!-- END editblock -->

</TABLE>
{hidden}
</FORM></TD></TR>
</TABLE>
</DIV>
</TD></TR></TABLE>