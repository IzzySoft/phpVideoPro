<H2 ALIGN="center">{title}</H2>
 <FORM NAME="space" METHOD="post" ACTION="{form_target}">
  <INPUT TYPE="hidden" NAME="usefilter" VALUE="{use_filter}">{sess_id}
  <TABLE WIDTH="400" ALIGN="center" BORDER="0">
    <TR><TH COLSPAN="2">{min_free}</TH></TR>
    <TR><TD WIDTH="50%"><DIV ALIGN="right"><INPUT NAME="minfree" MAXLENGTH="4" CLASS="yesnoinput">&nbsp;</DIV></TD>
        <TD WIDTH="50%">&nbsp;<INPUT TYPE="submit" NAME="getrest" VALUE="{display}"></TD></TR>
  </TABLE>
 </FORM>
