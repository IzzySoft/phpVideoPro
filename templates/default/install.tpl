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

<TABLE WIDTH="90%" ALIGN="center" BORDER="0" CLASS="beam"><TR CLASS="beam">
  <COLGROUP><COL WIDTH="20%"><COL WIDTH="20%"><COL WIDTH="20%"><COL WIDTH="20%"><COL WIDTH="20%"></COLGROUP>
  <TD COLSPAN="{beamspan}" CLASS="beam"><IMG SRC="{tpl_dir}images/blank.gif" HEIGHT="1"></TD>
  <TD COLSPAN="{nobeamspan}" CLASS="nobeam"><IMG SRC="{tpl_dir}images/blank.gif" HEIGHT="1"></TD>
</TR></TABLE>

<DIV ALIGN="center">
 <INPUT TYPE="hidden" NAME="{submit_name}" VALUE="1">
 <A HREF="JavaScript:document.configform.submit();"><IMG BORDER="0" SRC="{submit_button}"></A>
<!-- BEGIN skipblock -->
 <INPUT TYPE="hidden" NAME="{submit_name}_skip" VALUE="0">
 <A HREF="JavaScript:document.configform.{submit_name}_skip.value=1;document.configform.submit();"><IMG BORDER="0" SRC="{skip_button}"></A>
<!-- END skipblock -->
</DIV>

</FORM>
