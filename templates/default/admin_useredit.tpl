<H2 ALIGN="center">{listtitle}</H2>
<CENTER>{save_result}</CENTER>
<FORM NAME="admin_users" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="0"><TR><TD>
<TABLE WIDTH="100%" BORDER="1">
 <!-- COLGROUP><COL WIDTH="50%"><COL WIDTH="50%"></COLGROUP -->
 <TR><TH COLSPAN="2"><DIV ALIGN="center">{head_users}</DIV></TH></TR>
 <TR><TD COLSPAN="2"><DIV ALIGN="right">{user_id}</DIV></TH></TR>
 <TR><TD>{head_login}</TD><TD>{login}</TD></TR>
 <TR><TD>{head_comment}</TD><TD>{comment}</TD></TR>
 <TR><TD>{head_password}</TD><TD>{password}</TD></TR>
 <TR><TD>{head_password2}</TD><TD>{password2}</TD></TR>
</TABLE></TD></TR><TR><TD>
<TABLE WIDTH="100%" BORDER="1">
 <!-- COLGROUP><COL WIDTH="80%"><COL WIDTH="20%"></COLGROUP -->
 <TR><TH COLSPAN="2"><DIV ALIGN="center">{head_access}</DIV></TH></TR>
 <TR><TD>{head_browse}</TD><TD><DIV ALIGN="center">{browse}</DIV></TD></TR>
     <TD>{head_add}</TD><TD><DIV ALIGN="center">{add}</DIV></TD></TR>
     <TD>{head_upd}</TD><TD><DIV ALIGN="center">{upd}</DIV></TD></TR>
     <TD>{head_del}</TD><TD><DIV ALIGN="center">{del}</DIV></TD></TR>
     <TD>{head_isadmin}</TD><TD><DIV ALIGN="center">{isadmin}</DIV></TD></TR>
</TABLE></TD></TR><TR><TD>
<TABLE WIDTH="100%" BORDER="0">
 <TR><TH><DIV ALIGN="center">{update}</DIV></TH>
     <TH><DIV ALIGN="center">{adduser}</DIV></TH></TR>
</TABLE></TD></TR>
{hidden}
</TABLE>
</FORM>
