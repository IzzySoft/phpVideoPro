<H2 Align=Center>{listtitle}</H2>
<TABLE ALIGN=CENTER BORDER=0>
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
 <TR><TD COLSPAN=2>
  <TABLE ALIGN="center" BORDER="1">
   <TR><TH><A HREF="{scriptname}{crits}">{mtype}</A></TH>
       <TH><A HREF="{scriptname}{crits}">{nr}</A></TH>
       <TH><A HREF="{scriptname}?order=title{torder}{ocrits}">{title}</A></TH>
       <TH><A HREF="{scriptname}?order=fsk{forder}{ocrits}">{fsk}</A></TH>
       <TH><A HREF="{scriptname}?order=length{lorder}{ocrits}">{length}</A></TH>
       <TH><A HREF="{scriptname}?order=year{yorder}{ocrits}">{year}</A></TH>
       <TH><A HREF="{scriptname}?order=date{dorder}{ocrits}">{date}</A></TH>
       <TH><A HREF="{scriptname}?order=cat{corder}{ocrits}">{category}</A></TH>
       <TH><A HREF="{scriptname}?order=rating{corder}{ocrits}">{rating}</A></TH>
       <TH><A HREF="{scriptname}?order=lastchange{lcorder}{ocrits}">{lastchange}</A></TH>
   </TR>
   <!-- BEGIN mdatablock -->
   <TR CLASS="content"><TD STYLE="text-align:center;">{mtype}</TD>
       <TD><A HRef="{url}">{nr}</A></TD>
       <TD>{title}</TD>
       <TD STYLE="text-align:right;">{fsk}</TD>
       <TD STYLE="text-align:right;">{length}</TD>
       <TD STYLE="text-align:center;">{year}</TD>
       <TD STYLE="text-align:center;">{date}</TD>
       <TD>{category}</TD>
       <TD>{rating}</TD>
       <TD>{lastchange}</TD>
   </TR>
   <!-- END mdatablock -->
   <!-- BEGIN emptyblock -->
   <TR><TD COLSPAN="8"><DIV ALIGN="center">{no_data}</DIV></TD></TR>
   <!-- END emptyblock -->
  </Table>
 </TD></TR>
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
</TABLE>
