 <H2 ALIGN="center">{listtitle}</H2>
{js}
 <FORM NAME="medianr" METHOD="post" ACTION="{form_target}">
  <TABLE ALIGN="center" BORDER="0" WIDTH="400">
    <TR><TH COLSPAN="3"><DIV ALIGN="center">{latest}</DIV></TH></TR>
    <TR><TD COLSPAN="3"><DIV ALIGN="center">{latest_box}</DIV></TD></TR>
    <TR><TD COLSPAN="3">&nbsp;</TD></TR>
    <TR><TH WIDTH="45%"><DIV ALIGN="center">{orig}</DIV></TH>
        <TD WIDTH="10%">&nbsp;</TD>
        <TH WIDTH="45%"><DIV ALIGN="center">{new}</DIV></TD></TR>
    <TR><TD WIDTH="45%"><DIV ALIGN="center">{o_mtype} {o_medianr}-{o_part}</DIV></TD>
        <TD WIDTH="10%">&nbsp;</TD>
        <TD WIDTH="45%"><DIV ALIGN="center">{n_mtype} {n_medianr}-{n_part}</DIV></TD></TR>
    <TR><TD COLSPAN="3">&nbsp;</TD></TR>
    <TR><TD COLSPAN="3"><HR></TD></TR>
    <TR><TD COLSPAN="3">
        <TABLE ALIGN="center" BORDER="0" WIDTH="100%">
          <TD WIDTH="50%"><DIV ALIGN="center">{copy}</DIV></TD>
          <TD WIDTH="50%"><DIV ALIGN="center">{change}</DIV></TD></TR>
	</TABLE></TD></TR>
  </TABLE>
 </FORM>
