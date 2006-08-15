 <H2 ALIGN="center">{listtitle}</H2>
{js}
 <FORM NAME="label" METHOD="post" ACTION="{form_target}">
  <TABLE ALIGN="center">
    <TR><TH>{mtype}</TH>
        <TH>{medianr}</TH>
        <TH>{label}</TH></TR>
    <!-- BEGIN definitionblock -->
    <TR><TD><DIV ALIGN="center">{mtype}</DIV></TD>
        <TD><DIV ALIGN="center">{medianr}</DIV></TD>
        <TD><DIV ALIGN="center">{label}</DIV></TD></TR>
    <!-- END definitionblock -->
    <TR>{sess_id}<TD COLSPAN=3><DIV ALIGN="center"><INPUT TYPE="submit" NAME="create" VALUE="{create}"></DIV></TD></TR>
  </TABLE>
 </FORM>
