<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER=0" ALIGN="center"><TR><TD>
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
<FORM NAME="admin_printers" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="1" STYLE="margin:3">
 <TR><TH><DIV ALIGN="center">{head_print_id}</DIV></TH>
     <TH><DIV ALIGN="center">{head_print_name}</DIV></TH>
     <TH><DIV ALIGN="center">{head_print_unit}</DIV></TH>
     <TH><DIV ALIGN="center">{head_print_top}</DIV></TH>
     <TH><DIV ALIGN="center">{head_print_left}</DIV></TH></TR>
<!-- BEGIN itemblock -->
 <TR CLASS="content"><TD><DIV ALIGN="right">{print_id}</DIV></TD>
     <TD><DIV ALIGN="center">{print_name}</DIV></TD>
     <TD><DIV ALIGN="center">{print_unit}</DIV></TD>
     <TD><DIV ALIGN="center">{print_top}</DIV></TD>
     <TD><DIV ALIGN="center">{print_left}</DIV></TD></TR>
<!-- END itemblock -->
 <TR><TD COLSPAN="5"><INPUT TYPE='hidden' NAME='lines' VALUE='{lines}'></TD></TR>
</TABLE>

<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD><DIV STYLE="margin:3;text-align:center">{update}</DIV></TH></TR>
</FORM>

</TD></TR>
</TABLE>
</DIV>
</TD></TR></TABLE>