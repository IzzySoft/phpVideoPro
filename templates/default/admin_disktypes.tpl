<H2 ALIGN="center">{listtitle}</H2>
<CENTER>{save_result}</CENTER>
<FORM NAME="admin_disks" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="1">
 <TR><TH><DIV ALIGN="center">{head_disk_id}</DIV></TH>
     <TH><DIV ALIGN="center">{head_mtype}</DIV></TH>
     <TH><DIV ALIGN="center">{head_disk_name}</DIV></TH>
     <TH><DIV ALIGN="center">{head_size}</DIV></TH>
     <TH><DIV ALIGN="center">{head_lp}</DIV></TH>
     <TH><DIV ALIGN="center">{head_rc}</DIV></TH>
     <TH>&nbsp;</TH></TR>
<!-- BEGIN diskblock -->
 <TR><TD><DIV ALIGN="center">{disk_id}</DIV></TD>
     <TD><DIV ALIGN="center">{mtype}</DIV></TD>
     <TD><DIV ALIGN="center">{disk_name}</DIV></TD>
     <TD><DIV ALIGN="center">{size}</DIV></TD>
     <TD><DIV ALIGN="center">{lp}</DIV></TD>
     <TD><DIV ALIGN="center">{rc}</DIV></TD>
     <TD><DIV ALIGN="center">{trash}</DIV></TD></TR>
<!-- END diskblock -->
 <TR><TD COLSPAN="7">{hidden}</TD></TR>
 <TR><TH COLSPAN="7"><DIV ALIGN="center">{update}</DIV></TH></TR>
</TABLE>
</FORM>
