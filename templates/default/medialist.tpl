<H2 Align=Center>{listtitle}</H2>
<TABLE ALIGN=CENTER BORDER=0>
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
 <TR><TD COLSPAN=2>
  <TABLE ALIGN=Center BORDER=1>
   <TR><TH><A HREF="{scriptname}">{mtype}</A></TH>
       <TH><A HREF="{scriptname}">{nr}</A></TH>
       <TH><A HREF="{scriptname}?order=title">{title}</A></TH>
       <TH><A HREF="{scriptname}?order=length">{length}</A></TH>
       <TH><A HREF="{scriptname}?order=year">{year}</A></TH>
       <TH><A HREF="{scriptname}?order=date">{date}</A></TH>
       <TH><A HREF="{scriptname}?order=cat">{category}</A></TH>
   </TR>
   <!-- BEGIN mdatablock -->
   <TR><TD>{mtype}</TD>
       <TD><A HRef={url}>{nr}</A></TD>
       <TD>{title}</TD>
       <TD>{length}</TD>
       <TD>{year}</TD>
       <TD>{date}</TD>
       <TD>{category}</TD>
   </TR>
   <!-- END mdatablock -->
  </Table>
 </TD></TR>
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
</TABLE>
