<H2 ALIGN="center">{listtitle}</H2>
<!-- BEGIN listblock -->
<TABLE ALIGN="center" BORDER="0">
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
 <TR><TD COLSPAN="2"><TABLE ALIGN="center" BORDER="1">
  <TR><TH><DIV ALIGN="center">{head_desc}</DIV></TH>
      <TH><DIV ALIGN="center">{head_type}</DIV></TH>
      <TH><DIV ALIGN="center">{add}</DIV></TH></TR>
<!-- BEGIN itemblock -->
  <TR><TD>{desc}</TD>
      <TD><DIV ALIGN="center">{type}</DIV></TD>
      <TD><DIV ALIGN="center">{edit}&nbsp;{remove}</TR>
<!-- END itemblock -->
 </TABLE></TD></TR>
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
</TABLE>
<!-- END listblock -->
<!-- BEGIN editblock -->
<CENTER>{save_result}</CENTER>
<FORM NAME="admin_epstemplates" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="1" Style="table-layout:fixed">
  <COLGROUP><COL WIDTH="50%"><COL WIDTH="50%"></COLGROUP>
  {hidden}
  <TR><TD><DIV ALIGN="center">{desc}</DIV></TD><TD><DIV ALIGN="center">{type}</DIV></TD></TR>
  <TR><TD><DIV ALIGN="center">{gfx_file}</DIV></TD><TD><DIV ALIGN="center">{dsn_file}</DIV></TD></TR>
  <TR><TD><DIV ALIGN="center">{lower_left}</DIV></TD><TD><DIV ALIGN="center">{upper_right}</DIV></TD></TR>
  <TR><TD COLSPAN="2"><DIV ALIGN="center"><INPUT TYPE="submit" NAME="submit" VALUE="{button}"></DIV></TD></TR>
</TABLE>
</FORM>
<!-- END editblock -->
