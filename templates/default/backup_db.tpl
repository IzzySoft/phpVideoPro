<H2 ALIGN="center">{listtitle}</H2>
<CENTER>{save_result}</CENTER>
<FORM NAME='backup_db' METHOD='post' ACTION='{formtarget}'>
<TABLE WIDTH="90%" ALIGN="center">
 <!-- BEGIN itemblock -->
 <TR><TH>{title}</TH></TR>
 <!-- BEGIN settingsblock -->
 <TR><TD><TABLE ALIGN="center" BORDER="1" WIDTH="95%>
   <COLGROUP><COL WIDTH="50%"><COL WIDTH="50%"></COLGROUP>
   <TR CLASS="help"><TD><TABLE WIDTH="100%" BORDER="0"><TR><TD WIDTH="20">{lhelp_icon}</TD><TD STYLE="text-align:center">{hleft}</TD><TD WIDTH="20">&nbsp;</TD></TR></TABLE></TD>
     <TD><TABLE WIDTH="100%" BORDER="0"><TR><TD WIDTH="20">&nbsp;</TD><TD STYLE="text-align:center">{hright}</TD><TD WIDTH="20" STYLE="text-align:right;">{rhelp_icon}</TD></TR></TABLE></TD></TR>
   <TR><TD>{dleft}</TD><TD>{dright}</TD></TR>
 </TABLE></TD></TR>
 <!-- END settingsblock -->
 <!-- BEGIN descblock -->
 <TR><TD>{details}</TD></TR>
 <!-- END descblock -->
 <!-- END itemblock -->
 {hidden}
</TABLE>
<BR>
<DIV ALIGN='center'>{button}</DIV>
</FORM>