<BR STYLE="margin-top:50">
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0" ALIGN="center"><TR><TD>
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

{title}
 <FORM NAME="space" METHOD="post" ACTION="{form_target}">
  <INPUT TYPE="hidden" NAME="usefilter" VALUE="{use_filter}">{sess_id}
  <DIV STYLE="margin:3">
  <TABLE WIDTH="400" ALIGN="center" BORDER="0">
    <TR CLASS="content"><TD>{min_free}</TD>
      <TD><DIV ALIGN="right"><INPUT NAME="minfree" MAXLENGTH="4" CLASS="yesnobutton">&nbsp;</DIV></TD></TR>
  </TABLE>
  </DIV>

</TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD><DIV STYLE="margin:3;text-align:center;"><INPUT TYPE="submit" NAME="getrest" VALUE="{display}"></DIV></TD></TR>
</FORM>
</TABLE>
</DIV>
</TD></TR></TABLE>