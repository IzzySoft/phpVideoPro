<H2 ALIGN="center">{listtitle}</H2>
<FORM NAME="deleform" METHOD="post" ACTION="{formtarget}">
 <INPUT TYPE="hidden" NAME="nr" VALUE="{nr}">
 <INPUT TYPE="hidden" NAME="cass_id" VALUE="{cass_id}">
 <INPUT TYPE="hidden" NAME="part" VALUE="{part}">
 <INPUT TYPE="hidden" NAME="mtype_id" VALUE="{mtype_id}">
 <TABLE WIDTH="90%" ALIGN="center" BORDER="0">
  <TR><TD COLSPAN="2"><B><DIV ALIGN="center">{delete_yn}</DIV></B></FONT></TD></TR>
  <TR><TD WIDTH="50%"><DIV ALIGN="center"><INPUT TYPE="submit" NAME="cancel" VALUE="{no}"></DIV></TD>
      <TD><DIV ALIGN="center"><INPUT TYPE="submit" NAME="approved" VALUE="{yes}"></DIV></TD>
 </TABLE>
</FORM>
