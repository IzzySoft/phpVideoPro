<H2 ALIGN="center">{listtitle}</H2>
<CENTER>{save_result}</CENTER>
<FORM NAME="admin_users" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="0"><TR><TD>
<TABLE ALIGN="center" BORDER="1">
 <TR><TH COLSPAN="3"><DIV ALIGN="center">{head_users}</DIV></TH>
     <TH COLSPAN="4"><DIV ALIGN="center">{head_access}</DIV></TH>
     <TH><DIV ALIGN="center">{head_admin}</DIV></TH>
     <TH COLSPAN="2"><DIV ALIGN="center">{head_actions}</DIV></TH></TR>
 <TR><TH><DIV ALIGN="center">{head_id}</DIV></TH>
     <TH><DIV ALIGN="center">{head_login}</DIV></TH>
     <TH><DIV ALIGN="center">{head_comment}</DIV></TH>
     <TH><DIV ALIGN="center">{head_browse}</DIV></TH>
     <TH><DIV ALIGN="center">{head_add}</DIV></TH>
     <TH><DIV ALIGN="center">{head_upd}</DIV></TH>
     <TH><DIV ALIGN="center">{head_del}</DIV></TH>
     <TH><DIV ALIGN="center">{head_isadmin}</DIV></TH>
     <TH><DIV ALIGN="center">{head_edit}</DIV></TH>
     <TH><DIV ALIGN="center">{head_delete}</DIV></TH></TR>
<!-- BEGIN itemblock -->
 <TR><TD><DIV ALIGN="right">{user_id}</DIV></TD>
     <TD>{login}</TD>
     <TD>{comment}</TD>
     <TD><DIV ALIGN="center">{browse}</DIV></TD>
     <TD><DIV ALIGN="center">{add}</DIV></TD>
     <TD><DIV ALIGN="center">{upd}</DIV></TD>
     <TD><DIV ALIGN="center">{del}</DIV></TD>
     <TD><DIV ALIGN="center">{isadmin}</DIV></TD>
     <TD><DIV ALIGN="center">{edit}</DIV></TD>
     <TD><DIV ALIGN="center">{delete}</DIV></TD>
     </TR>
<!-- END itemblock -->
</TABLE></TD></TR><TR><TD>
<TABLE WIDTH="100%" BORDER="0">
 <TR><TH><DIV ALIGN="center">{update}</DIV></TH>
     <TH><DIV ALIGN="center">{adduser}</DIV></TH></TR>
</TABLE></TD></TR>
<INPUT TYPE='hidden' NAME='lines' VALUE='{lines}'>
</TABLE>
</FORM>
