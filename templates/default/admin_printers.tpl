<H2 ALIGN="center">{listtitle}</H2>
<CENTER>{save_result}</CENTER>
<FORM NAME="admin_printers" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="1">
 <TR><TH><DIV ALIGN="center">{head_print_id}</DIV></TH>
     <TH><DIV ALIGN="center">{head_print_name}</DIV></TH>
     <TH><DIV ALIGN="center">{head_print_unit}</DIV></TH>
     <TH><DIV ALIGN="center">{head_print_top}</DIV></TH>
     <TH><DIV ALIGN="center">{head_print_left}</DIV></TH></TR>
<!-- BEGIN itemblock -->
 <TR><TD><DIV ALIGN="right">{print_id}</DIV></TD>
     <TD><DIV ALIGN="center">{print_name}</DIV></TD>
     <TD><DIV ALIGN="center">{print_unit}</DIV></TD>
     <TD><DIV ALIGN="center">{print_top}</DIV></TD>
     <TD><DIV ALIGN="center">{print_left}</DIV></TD></TR>
<!-- END itemblock -->
 <TR><TD COLSPAN="5">{hidden}</TD></TR>
 <TR><TH COLSPAN="5"><DIV ALIGN="center">{update}</DIV></TH></TR>
</TABLE>
</FORM>
