<H2 ALIGN="center">{listtitle}</H2>
<CENTER>{save_result}</CENTER>
<FORM NAME="admin_movietech" METHOD="post" ACTION="{formtarget}">
<!-- BEGIN mainblock -->
<TABLE ALIGN="center" BORDER="0">
 <TR><TD>
   <TABLE ALIGN="center" BORDER="1">
    <TR><TH COLSPAN="3">{screen_title}</TH></TR>
    <TR><TD><DIV ALIGN="center"><B>{name}</B></DIV></TD>
        <TD><DIV ALIGN="center"><B>{sname}</B></DIV></TD>
	<TD>&nbsp;</TD></TR>
    <!-- BEGIN screenitemblock -->
    <TR><TD>{item_name}</TD><TD>{item_sname}</TD><TD>{edit} {trash}</TD></TR>
    <!-- END screenitemblock -->
    <TR><TD COLSPAN="3"><DIV ALIGN="center">{screen_add}</DIV></TD></TR>
   </TABLE>
 </TD><TD>
   <TABLE ALIGN="center" BORDER="1">
    <TR><TH COLSPAN="3">{color_title}</TH></TR>
    <TR><TD><DIV ALIGN="center"><B>{name}</B></DIV></TD>
        <TD><DIV ALIGN="center"><B>{sname}</B></DIV></TD>
	<TD></TD></TR>
    <!-- BEGIN coloritemblock -->
    <TR><TD>{item_name}</TD><TD>{item_sname}</TD><TD>{edit} {trash}</TD></TR>
    <!-- END coloritemblock -->
    <TR><TD COLSPAN="3"><DIV ALIGN="center">{color_add}</DIV></TD></TR>
   </TABLE>
 </TD></TR><TR><TD COLSPAN="2">
   <TABLE ALIGN="center" BORDER="1">
    <TR><TH COLSPAN="3">{mtype_title}</TH></TR>
    <TR><TD><DIV ALIGN="center"><B>{name}</B></DIV></TD>
        <TD><DIV ALIGN="center"><B>{sname}</B></DIV></TD>
	<TD></TD></TR>
    <!-- BEGIN mtypeitemblock -->
    <TR><TD>{item_name}</TD><TD>{item_sname}</TD><TD>{edit} {trash}</TD></TR>
    <!-- END mtypeitemblock -->
    <TR><TD COLSPAN="3"><DIV ALIGN="center">{mtype_add}</DIV></TD></TR>
   </TABLE>
 </TD></TR>
</TABLE>
<!-- END mainblock -->
<!-- BEGIN editblock -->
<TABLE ALIGN="center" BORDER="1">
 <TR><TH COLSPAN="2">{edit_title}</TH></TR>
 <TR><TH>{name_name}</TH><TD>{name}</TD></TR>
 <TR><TH>{sname_name}</TH><TD>{sname}</TD></TR>
 <TR><TD COLSPAN="2"><DIV ALIGN="center">{add}</DIV></TD></TR>
</TABLE>
<!-- END editblock -->
</FORM>
