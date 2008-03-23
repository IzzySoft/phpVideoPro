<H2 Align=Center>{listtitle}</H2>
<FORM NAME="transform" METHOD="post" ACTION="{formtarget}" ACCEPT-CHARSET="{charset}">
<TABLE ALIGN="center" BORDER="0" WIDTH="95%">
 {hidden}
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="center">{abc}</DIV></TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
 <TR><TD COLSPAN="3">
  <TABLE ALIGN="center" BORDER="1" CELLPADDING="2" CELLSPACING="2" WIDTH="100%" Style="table-layout:fixed">
   <!-- BEGIN mtitleblock -->
   <COLGROUP><COL WIDTH="150 pt"><COL WIDTH="*"><COL WIDTH="380 pt"><COL WIDTH="*"></COLGROUP -->
   <TR><TH>{code}</TH>
       <TH>{orig}</TH>
       <TH>{trans}</A></TH>
       <TH>{sample}</A></TH>
   </TR>
   <!-- END mtitleblock -->
   <!-- BEGIN mdatablock -->
   <TR><TD>{code}</TD>
       <TD>{orig}</TD>
       <TD>{trans}</TD>
       <TD>{sample}</TD>
   </TR>
   <!-- END mdatablock -->
   <!-- BEGIN emptyblock -->
   <TR><TH COLSPAN="3">{sel_lang_title}</TH><TD COLSPAN="2"><DIV ALIGN="center">{sel_lang}</DIV></TD></TR>
   <!-- END emptyblock -->
   <TR><TH COLSPAN="3"><DIV ALIGN="center">{save}</DIV></TH>
       <TH COLSPAN="3"><DIV ALIGN="center"><INPUT TYPE="submit" NAME="{submit_name}" VALUE="{submit}"></DIV></TH>
   </TR>
  </Table>
 </TD></TR>
 <TR><TD>{first}{left}</TD>
     <TD>&nbsp;</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
</TABLE>
 </FORM>
