<BR STYLE="margin-top:30">
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER=0"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="3" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle">{listtitle}</TD>
     <TD ALIGN="right" CLASS="wintitle"><INPUT TYPE="image" NAME="button_close" CLASS="imgbut" SRC="{tpl_dir}images/win_close.gif" WIDTH="14" HEIGHT="13" onClick="window.location.href='{logoff_link}'"></TD></TR>
</TABLE></TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD>

<DIV STYLE="margin:3;text-align:center">{save_result}</DIV>

 <FORM NAME="medialength" METHOD="post" ACTION="{form_target}">
  {hidden_fields}
  <TABLE STYLE="margin:3;text-align:center" BORDER="1" WIDTH="400">
    <TR><TH STYLE="margin:5;text-align:center">{info}</TH></TR>
    <TR CLASS="content"><TD><DIV ALIGN="center">{input}</DIV></TD></TR>
  </TABLE>
 </FORM>

</TD></TR>
<TR><TD STYLE="text-align:center;margin:3;">{submit}</TD></TR>
</TABLE>
</DIV>
</TD></TR></TABLE>