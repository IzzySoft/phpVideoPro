 <H2 ALIGN="center">{listtitle}</H2>

 <FORM NAME="label" METHOD="post" ACTION="{form_target}">
  <INPUT TYPE=HIDDEN NAME="ltype_id" VALUE="{ltype}">
  {sess_id}
  <TABLE ALIGN="center">
    <TR><TH>{hmtype_0}</TH>
        <TH>{hmedianr_0}</TH>
        <TH>{hlabel_0}</TH>
        <TH>{hmtype_1}</TH>
        <TH>{hmedianr_1}</TH>
        <TH>{hlabel_1}</TH>
        <TH>{hmtype_2}</TH>
        <TH>{hmedianr_2}</TH>
        <TH>{hlabel_2}</TH></TR>
    <!-- BEGIN definitionblock -->
    <TR><TD><DIV ALIGN="center">{mtype_0}</DIV></TD>
        <TD><DIV ALIGN="center">{medianr_0}</DIV></TD>
        <TD><DIV ALIGN="center">{label_0}</DIV></TD>
        <TD><DIV ALIGN="center">{mtype_1}</DIV></TD>
        <TD><DIV ALIGN="center">{medianr_1}</DIV></TD>
        <TD><DIV ALIGN="center">{label_1}</DIV></TD>
        <TD><DIV ALIGN="center">{mtype_2}</DIV></TD>
        <TD><DIV ALIGN="center">{medianr_2}</DIV></TD>
        <TD><DIV ALIGN="center">{label_2}</DIV></TD></TR>
    <!-- END definitionblock -->
    <TR><TD COLSPAN=3><DIV ALIGN="center"><INPUT TYPE="submit" NAME="create" VALUE="{create}"></DIV></TD></TR>
  </TABLE>
 </FORM>