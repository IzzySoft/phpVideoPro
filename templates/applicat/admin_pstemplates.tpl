<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER=0" ALIGN="center"><TR><TD>
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

<!-- BEGIN listblock -->
<TABLE ALIGN="center" BORDER="0" STYLE="margin:3">
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
 <TR><TD COLSPAN="2"><TABLE ALIGN="center" BORDER="1">
  <TR><TH><DIV ALIGN="center">{head_desc}</DIV></TH>
      <TH><DIV ALIGN="center">{head_type}</DIV></TH>
      <TH><DIV ALIGN="center">{add}</DIV></TH></TR>
<!-- BEGIN itemblock -->
  <TR CLASS="content"><TD>{desc}</TD>
      <TD><DIV ALIGN="center">{type}</DIV></TD>
      <TD><DIV ALIGN="center">{edit}&nbsp;{remove}</TR>
<!-- END itemblock -->
 </TABLE></TD></TR>
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
</TABLE>
<!-- END listblock -->
<!-- BEGIN editblock -->
<DIV STYLE="margin:3;text-align:center">{save_result}</DIV>
<FORM NAME="admin_epstemplates" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="1" Style="table-layout:fixed;margin:3">
  <COLGROUP><COL WIDTH="50%"><COL WIDTH="50%"></COLGROUP>
  {hidden}
  <TR CLASS="content"><TD><DIV ALIGN="center">{desc}</DIV></TD><TD><DIV ALIGN="center">{type}</DIV></TD></TR>
  <TR CLASS="content"><TD><DIV ALIGN="center">{gfx_file}</DIV></TD><TD><DIV ALIGN="center">{dsn_file}</DIV></TD></TR>
  <TR CLASS="content"><TD><DIV ALIGN="center">{lower_left}</DIV></TD><TD><DIV ALIGN="center">{upper_right}</DIV></TD></TR>
</TABLE>
  <TR><TD BGCOLOR="#AAAAAA" COLSPAN="2"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
  <TR><TD BGCOLOR="#FFFFFF" COLSPAN="2"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
  <TR><TD COLSPAN="2"><DIV STYLE="margin:3;text-align:center"><INPUT CLASS="submit" TYPE="submit" NAME="submit" VALUE="{button}"></DIV></TD></TR>
 </FORM>
<!-- END editblock -->

</TD></TR>
</TABLE>
</DIV>
</TD></TR></TABLE>