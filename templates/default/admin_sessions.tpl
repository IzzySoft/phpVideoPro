<H2 ALIGN="center">{listtitle}</H2>
<FORM NAME="admin_sessions" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="1">
 <TR><TD COLSPAN="7"><TABLE BORDER="0" WIDTH="100%">
   <TR><TD COLSPAN="2"><DIV ALIGN="center">{del_old_sess} <INPUT TYPE="submit" NAME="submit" VALUE="{submit}"></DIV><BR>&nbsp;</TD></TR>
   <TR><TD>{first}{left}</TD><TD><DIV ALIGN="right">{right}{last}</DIV></TD></TR>
 </TABLE></TD></TR>
 <TR><TH><DIV ALIGN="center">{head_sess_id}</DIV></TH>
     <TH><DIV ALIGN="center">{head_sess_ip}</DIV></TH>
     <TH><DIV ALIGN="center">{head_sess_user}</DIV></TH>
     <TH><DIV ALIGN="center">{head_sess_start}</DIV></TH>
     <TH><DIV ALIGN="center">{head_sess_dla}</DIV></TH>
     <TH><DIV ALIGN="center">{head_sess_end}</DIV></TH>
     <TH><DIV ALIGN="center">{head_sess_action}</DIV></TH></TR>
<!-- BEGIN itemblock -->
 <TR><TD><DIV ALIGN="right">{sess_id}</DIV></TD>
     <TD><DIV ALIGN="center">{sess_ip}</DIV></TD>
     <TD><DIV ALIGN="center">{sess_user}</DIV></TD>
     <TD><DIV ALIGN="center">{sess_start}</DIV></TD>
     <TD><DIV ALIGN="center">{sess_dla}</DIV></TD>
     <TD><DIV ALIGN="center">{sess_end}</DIV></TD>
     <TD><DIV ALIGN="center">{sess_action}</DIV></TD></TR>
<!-- END itemblock -->
 <TR><TD COLSPAN="7"><TABLE BORDER="0" WIDTH="100%">
   <TR><TD>{first}{left}</TD><TD><DIV ALIGN="right">{right}{last}</DIV></TD></TR>
 </TABLE></TD></TR>
</TABLE>
</FORM>
