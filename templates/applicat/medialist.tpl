<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER=0"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="3" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle">{listtitle}</TD>
     <TD ALIGN="right" CLASS="wintitle"><INPUT TYPE="image" NAME="button_close" CLASS="imgbut" SRC="{tpl_dir}images/win_close.gif" WIDTH="14" HEIGHT="13" onClick="window.location.href='{logoff_link}'"></TD></TR>
</TABLE></TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD>

<TABLE ALIGN=CENTER BORDER=0>
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
 <TR><TD COLSPAN=2>
  <TABLE ALIGN=Center BORDER=1>
   <TR><TH><A HREF="{scriptname}">{mtype}</A></TH>
       <TH><A HREF="{scriptname}">{nr}</A></TH>
       <TH><A HREF="{scriptname}?order=title">{title}</A></TH>
       <TH><A HREF="{scriptname}?order=length">{length}</A></TH>
       <TH><A HREF="{scriptname}?order=year">{year}</A></TH>
       <TH><A HREF="{scriptname}?order=date">{date}</A></TH>
       <TH><A HREF="{scriptname}?order=cat">{category}</A></TH>
   </TR>
   <!-- BEGIN mdatablock -->
   <TR CLASS="content"><TD>{mtype}</TD>
       <TD><A HRef={url}>{nr}</A></TD>
       <TD>{title}</TD>
       <TD>{length}</TD>
       <TD>{year}</TD>
       <TD>{date}</TD>
       <TD>{category}</TD>
   </TR>
   <!-- END mdatablock -->
   <!-- BEGIN emptyblock -->
   <TR CLASS="content"><TD COLSPAN="7"><DIV ALIGN="center">{no_data}</DIV></TD></TR>
   <!-- END emptyblock -->
  </Table>
 </TD></TR>
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
</TABLE>

</TD></TR></TABLE>
</DIV>
</TD></TR></TABLE>