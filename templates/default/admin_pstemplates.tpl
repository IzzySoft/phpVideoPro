<H2 ALIGN="center">{listtitle}</H2>
<!-- BEGIN packlistblock -->
<TABLE ALIGN="center" BORDER="0" STYLE="margin:3">
 <TR><TD COLSPAN="4"><TABLE WIDTH="100%" BORDER="0">
     <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="center">{lname}</DIV></TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR></TABLE></TD></TR>
  <TR><TH><DIV ALIGN="center">{head_name}</DIV></TH>
      <TH><DIV ALIGN="center">{head_rev1}</DIV></TH>
      <TH><DIV ALIGN="center">{head_rev2}</DIV></TH>
      <TH><DIV ALIGN="center">{add}</DIV></TH></TR>
<!-- BEGIN packitemblock -->
  <TR CLASS="content"><TD>{pname}</TD>
      <TD><DIV ALIGN="center">{prev1}</DIV></TD>
      <TD><DIV ALIGN="center">{prev2}</DIV></TD>
      <TD><TABLE ALIGN="center"><TR><TD WIDTH="23">{info}</TD><TD WIDTH="23">{edit}</TD><TD WIDTH="23">{actions}</TD></TR></TABLE></TR>
<!-- END packitemblock -->
 <TR><TD COLSPAN="4"><TABLE WIDTH="100%" BORDER="0">
     <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="center">{check_update}</DIV></TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR></TABLE></TD></TR>
</TABLE>
<!-- END packlistblock -->
<!-- BEGIN packviewblock -->
<TABLE ALIGN="center" BORDER="1" Style="margin:3">
  <TR CLASS="content"><TD><DIV ALIGN="center"><b>{tname}</b></DIV></TD><TD>{name}</TD></TR>
  <TR CLASS="content"><TD><DIV ALIGN="center"><b>{tcreator}</b></DIV></TD><TD>{creator}</TD></TR>
  <TR CLASS="content"><TD><DIV ALIGN="center"><b>{tdesc}</b></DIV></TD><TD>{desc}</TD></TR>
  <TR CLASS="content"><TD><DIV ALIGN="center"><b>{trev}</b></DIV></TD><TD>{rev}</TD></TR>
</TABLE>
<!-- END packviewblock -->

<!-- BEGIN listblock -->
<TABLE ALIGN="center" BORDER="0" STYLE="margin:3">
 <TR><TD COLSPAN="4"><TABLE WIDTH="100%" BORDER="0">
     <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="center">{lname}</DIV></TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR></TABLE></TD></TR>
 <TR><TD COLSPAN="2"><TABLE ALIGN="center" BORDER="1">
  <TR><TH><DIV ALIGN="center">{head_desc}</DIV></TH>
      <TH><DIV ALIGN="center">{head_type}</DIV></TH>
      <TH><DIV ALIGN="center">{add}</DIV></TH></TR>
<!-- BEGIN itemblock -->
  <TR CLASS="content"><TD>{desc}</TD>
      <TD><DIV ALIGN="center">{type}</DIV></TD>
      <TD><DIV ALIGN="center">{edit}&nbsp;{remove}</DIV></TR>
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
