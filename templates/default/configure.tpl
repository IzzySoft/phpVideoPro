<H2 ALIGN=CENTER>{listtitle}</H2>
<FORM NAME="config_form" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN=CENTER WIDTH=90% BORDER=1>
<!-- BEGIN listblock -->
 <TR><TH>{list_head}</TH></TR>
 <TR><TD>
  <TABLE WIDTH=100%>
  <!-- BEGIN itemblock -->
   <TR><TD WIDTH=70%><b>{item_name}</b><br>{item_comment}</TD>
    <TD WIDTH=30%>{item_input}</TD></TR>
  <!-- END itemblock -->
  </TABLE></TD></TR>
  {sess_id}
<!-- END listblock -->
 <TR><TD><DIV ALIGN=CENTER>{update}</DIV></TD></TR>
</FORM>
{config_end}
</TABLE>
