<H2 ALIGN="center">{listtitle}</H2>
<FORM NAME="configform" METHOD="post" ACTION="{form_target}">

<!-- BEGIN infoblock -->
<TABLE WIDTH="90%" ALIGN="center" BORDER="1">
 <TR><TH>{info_head}</TH></TR>
 <TR><TD><DIV ALIGN="justify">{info_body}</DIV></TD></TR>
</TABLE>
<!-- END infoblock -->
<!-- BEGIN formblock -->
<TABLE WIDTH="90%" ALIGN="center" BORDER="1">
 <!-- BEGIN formitemblock -->
 <TR><TH COLSPAN="2">{descript}</TH></TR>
 <TR><TD><B>{field}</B></TD><TD>{content}</TD></TR>
 <!-- END formitemblock -->
</TABLE>
<!-- END formblock -->

<DIV ALIGN="center">
 <INPUT TYPE="hidden" NAME="{submit_name}" VALUE="1">
 <INPUT TYPE="image" NAME="{submit_name}" SRC="{submit_button}" onClick="submit();">
</DIV>

</FORM>
