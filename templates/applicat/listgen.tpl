 <H2 ALIGN="center">{listtitle}</H2>

 <FORM NAME="listgen" METHOD="post" ACTION="{form_target}">
  <TABLE ALIGN="center">
    <TR><TH>{liste}</TH>
        <TH>{format}</TH>
        <TH>{lines}</TH></TR>
    <!-- BEGIN definitionblock -->
    <TR><TD><DIV ALIGN="center">{liste}</DIV></TD>
        <TD><DIV ALIGN="center">{format}</DIV></TD>
        <TD><DIV ALIGN="center">{lines}</DIV></TD></TR>
    <!-- END definitionblock -->
    <TR><TD COLSPAN=3><DIV ALIGN="center"><INPUT TYPE="submit" NAME="create" VALUE="{create}"></DIV></TD></TR>
  </TABLE>
 </FORM>
