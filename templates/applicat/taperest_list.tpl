<BR STYLE="margin-top:50">
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0" ALIGN="center"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle"><DIV STYLE="margin:2">{freespace}</DIV></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" NAME="button_help" CLASS="imgbut" SRC="{tpl_dir}images/win_help.gif" WIDTH="14" HEIGHT="13" onClick="{help_link}"></TD>
     <TD CLASS="wintitle" STYLE="vertical-align:middle;"><DIV STYLE="width:20;text-align:center;">
      <INPUT TYPE="image" NAME="button_close" CLASS="imgbut" SRC="{tpl_dir}images/win_close.gif" WIDTH="14" HEIGHT="13" onClick="window.location.href='{logoff_link}'"></DIV></TD></TR>
</TABLE></TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD>

<DIV STYLE="margin:3;">
<TABLE ALIGN="center" BORDER="0">
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
 <TR><TD COLSPAN=2>
  <TABLE ALIGN="center" BORDER="1" WIDTH="100%">
   <TR><TH>{medium}</TH><TH>{nr}</TH><TH>{free}</TH><TH>{content}</TH></TR>
   <!-- BEGIN itemblock --> 
   <TR CLASS="content"><TD>{mtype}</TD><TD>{id}</TD><TD>{free}</TD><TD><UL>                       
     <!-- BEGIN movieblock -->                                                      
     <LI>{movies}                                                               
     <!-- END movieblock -->                                                        
   </UL></TD></TR>                                                                
   <!-- END itemblock -->	 
  </Table>
 </TD></TR>
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
</TABLE>
</DIV>

</TD></TR>
</TABLE>
</DIV>
</TD></TR></TABLE>