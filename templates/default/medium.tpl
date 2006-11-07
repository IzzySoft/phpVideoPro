 <H2 ALIGN="center">{listtitle}</H2>

 <FORM NAME="mediaform" METHOD="post" ACTION="{form_target}">
  <TABLE ALIGN="center" BORDER="1">
    <TR><TH>{techdata}</TH><TH>{moviedata}</TH></TR>
    <TR><TD STYLE='vertical-align:middle'><TABLE BORDER="0">
<!-- BEGIN techblock -->
        <TR><TD><DIV ALIGN="right">{tname}</DIV></TD>
            <TD><DIV ALIGN="right">{tdata}</DIV></TD><TD>{tunit}</TD></TR>
<!-- END techblock -->
        </TABLE></TD><TD STYLE='vertical-align:middle'><TABLE BORDER="0">
<!-- BEGIN movieblock -->
        <TR><TD STYLE='text-align:right'>{mlink}</TD><TD>{mdata}</TD></TR>
<!-- END movieblock -->
        </TABLE></TD></TR>
  </TABLE>
  <DIV ALIGN="center">{formactions}</DIV>
 </FORM>
