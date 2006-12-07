<FORM NAME="admin_users" METHOD="post" ACTION="{formtarget}">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
<TR><TD>

<H2>{listtitle}</H2>
<DIV STYLE="margin:3;text-align:center">{save_result}</DIV>
<TABLE ALIGN="center" BORDER="0" STYLE="margin:3" CELLPADDING="0" CELLSPACING="0"><TR><TD>
<TABLE ALIGN="center" BORDER="1">
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
</TABLE></TD></TR><TR><TD>

<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD><TABLE WIDTH="100%" BORDER="0" STYLE="margin:3">
 <TR><TD><DIV ALIGN="center">{update}</DIV></TD></TR>
</TABLE></TD></TR>
</TABLE>

{hidden}
</FORM>
</TD></TR></TABLE>
