<H2 ALIGN="center">{listtitle}</H2>
<CENTER>{save_result}</CENTER>
<FORM NAME="admin_cats" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="1">
 <TR><TH><DIV ALIGN="center">{head_cat_id}</DIV></TH>
     <TH><DIV ALIGN="center">{head_cat_name}</DIV></TH>
     <TH><DIV ALIGN="center">{head_cat_trans}</DIV></TH>
     <TH>&nbsp;</TH></TR>
<!-- BEGIN catblock -->
 <TR><TD><DIV ALIGN="right">{cat_id}</DIV></TD>
     <TD><DIV ALIGN="center">{cat_name}</DIV></TD>
     <TD><DIV ALIGN="center">{cat_trans}</DIV></TD>
     <TD><DIV ALIGN="center">{cat_del}</DIV></TD></TR>
<!-- END catblock -->
 <TR><TD COLSPAN="4">{hidden}</TD></TR>
 <TR><TH COLSPAN="4"><DIV ALIGN="center">{update}</DIV></TH></TR>
</TABLE>
</FORM>
