<H2 Align=Center>{listtitle}</H2>
<TABLE ALIGN=CENTER BORDER=0 WIDTH="90%">
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
 <TR><TD COLSPAN=2>
  <TABLE ALIGN=Center BORDER="1" WIDTH="100%">
   <TR><TH>{stafftype}</TH><TH>{title}</TH>
      <TH>{category}</TH><TH>{length}</TH>
      <TH WIDTH="85">{medianr}</TH></TR>
   <!-- BEGIN itemblock -->
   <TR><TD>{name}{namesep}{firstname}</TD><TD>{title}</TD><TD>{category}</TD><TD>{length}</TD><TD><A HRef="{url}">{mtype} {nr}</A></TD></TR>
   <!-- END itemblock -->
   <!-- BEGIN notfoundblock -->
   <TR><TD COLSPAN=5>{not_found}</TD></TR>
   <!-- END notfoundblock -->
  </Table>

 </TD></TR>
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
</TABLE>
