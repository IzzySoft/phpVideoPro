<H2 ALIGN="center">{listtitle}</H2>
<CENTER>{save_result}</CENTER>
<!-- BEGIN listblock -->
<FORM NAME="admin_cats" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="1">
 <TR><TH><DIV ALIGN="center">{head_cat_id}</DIV></TH>
     <TH><DIV ALIGN="center">{head_cat_name}</DIV></TH>
     <TH><DIV ALIGN="center">{head_cat_trans}</DIV></TH>
     <TH COLSPAN="2">&nbsp;</TH></TR>
<!-- BEGIN catblock -->
 <TR><TD><DIV ALIGN="right">{cat_id}</DIV></TD>
     <TD><DIV ALIGN="center">{cat_name}</DIV></TD>
     <TD><DIV ALIGN="center">{cat_trans}</DIV></TD>
     <TD><DIV ALIGN="center">{cat_del}</DIV></TD>
     <TD><DIV ALIGN="center">{cat_dis}</DIV></TD></TR>
<!-- END catblock -->
 <TR><TD COLSPAN="4">{hidden}</TD></TR>
 <TR><TH COLSPAN="4"><DIV ALIGN="center">{update}</DIV></TH></TR>
</TABLE>
<!-- END listblock -->
<!-- BEGIN delchoiceblock -->
<FORM NAME="admin_cats" METHOD="post" ACTION="{formtarget}">
<INPUT TYPE="hidden" NAME="delete" VALUE="{delete}">
<TABLE ALIGN="center" BORDER="1" STYLE="margin:3">
 <TR><TH ALIGN="center">{msg}</TH></TR>
 <TR CLASS="content"><TD>{upd_all}<BR>{upd_individual}<BR>{upd_none}</TD></TR>
 <TR><TH><DIV ALIGN="center">{update}</DIV></TH></TR>
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
 <TR><TH COLSPAN="2"><DIV ALIGN="center">{update}</DIV></TH></TR>
</TABLE>
<!-- END individualblock -->
</FORM>
