<H2 ALIGN="center">{listtitle}</H2>
<FORM NAME="deleform" METHOD="post" ACTION="{formtarget}">
 <INPUT TYPE="hidden" NAME="delete" VALUE="{delete}">
 <TABLE ALIGN="center" BORDER="0">
  <TR><TD COLSPAN="2"><B><DIV ALIGN="center">{delete_yn}</DIV></B></FONT></TD></TR>
  <TR><TD WIDTH="50%"><DIV ALIGN="center"><INPUT TYPE="submit" NAME="cancel" VALUE="{no}"></DIV></TD>
      <TD WIDTH="50%"><DIV ALIGN="center"><INPUT TYPE="submit" NAME="confirmed" VALUE="{yes}"></DIV></TD></TR>
 {hidden}
 </TABLE>
</FORM>
