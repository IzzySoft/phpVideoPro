<BR><DIV ALIGN="right"><FONT SIZE="-1">{login_info}&nbsp;&nbsp;</FONT></DIV>
<H2><DIV ALIGN="center">{listtitle}</DIV></H2>
<!-- BEGIN introblock -->
 <TABLE ALIGN="center" BORDER="1">
  <TR><TH><DIV ALIGN="center">{intro_head}</DIV></TH></TR>
  <TR><TD>{intro_text}</TD></TR>
 </TABLE>
<!-- END introblock -->
 <FORM NAME="space" METHOD="post" ACTION="{form_target}">
  <TABLE ALIGN="center">
    <TR><TH COLSPAN="2">{goto_entry}</TH></TR>
    <TR><TD COLSPAN=3>&nbsp;</TD></TR>
    <TR><TD><DIV ALIGN="center" STYLE="margin-right:5">{mtype}</DIV></TD>
        <TD><DIV ALIGN="center" STYLE="margin-left:5">{cass_id}</DIV></TD>
    <TR><TD><DIV ALIGN="center">{sel_mtype}</DIV></TD>
        <TD><DIV ALIGN="center"><INPUT NAME="cass_id" {add_cass}>-<INPUT NAME="part" {add_part}></DIV></TD></TR>
    <TR><TD COLSPAN=3><DIV ALIGN="center"><INPUT TYPE="submit" NAME="sel_entry" VALUE="{display}"></DIV></TR>
  </TABLE>
 </FORM>
