<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle"><DIV STYLE="margin:2;">{listtitle}</DIV></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{home_title}" NAME="button_home" CLASS="imgbut" SRC="{tpl_dir}images/win_home.gif" STYLE="width:14;height:13;" onClick="window.location.href='{home_link}'"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{search_title}" NAME="button_search" CLASS="imgbut" SRC="{tpl_dir}images/win_search.gif" STYLE="width:14;height:13;" onClick="window.location.href='{search_link}'"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{help_title}" NAME="button_help" CLASS="imgbut" SRC="{tpl_dir}images/win_help.gif" STYLE="width:14;height:13;" onClick="{help_link}"></TD>
     <TD CLASS="wintitle" STYLE="vertical-align:middle;margin-right:3;"><DIV STYLE="width:18;">
      <INPUT TYPE="image" TITLE="{logoff_title}" NAME="button_close" CLASS="imgbut" SRC="{tpl_dir}images/win_close.gif" STYLE="width:14;height:13;" onClick="window.location.href='{logoff_link}'"></DIV></TD></TR>
</TABLE></TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD>

<TABLE ALIGN="center" BORDER="0">
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="right">{right}{last}</DIV></TD></TR>
 <TR><TD COLSPAN="2">
  <TABLE ALIGN="center" BORDER="1">
   <TR><TH><A HREF="{scriptname}{crits}">{mtype}</A></TH>
       <TH><A HREF="{scriptname}{crits}">{nr}</A></TH>
       <TH><A HREF="{scriptname}?order=title{torder}{ocrits}">{title}</A></TH>
       <TH><A HREF="{scriptname}?order=fsk{forder}{ocrits}">{fsk}</A></TH>
       <TH><A HREF="{scriptname}?order=length{lorder}{ocrits}">{length}</A></TH>
       <TH><A HREF="{scriptname}?order=year{yorder}{ocrits}">{year}</A></TH>
       <TH><A HREF="{scriptname}?order=date{dorder}{ocrits}">{date}</A></TH>
       <TH><A HREF="{scriptname}?order=cat{corder}{ocrits}">{category}</A></TH>
       <TH><A HREF="{scriptname}?order=rating{corder}{ocrits}">{rating}</A></TH>
       <TH><A HREF="{scriptname}?order=lastchange{lcorder}{ocrits}">{lastchange}</A></TH>
   </TR>
   <!-- BEGIN mdatablock -->
   <TR CLASS="content"><TD STYLE="text-align:center;">{mtype}</TD>
       <TD><A HRef="{url}">{nr}</A></TD>
       <TD>{title}</TD>
       <TD STYLE="text-align:right;">{fsk}</TD>
       <TD STYLE="text-align:right;">{length}</TD>
       <TD STYLE="text-align:center;">{year}</TD>
       <TD STYLE="text-align:center;">{date}</TD>
       <TD>{category}</TD>
       <TD>{rating}</TD>
       <TD>{lastchange}</TD>
   </TR>
   <!-- END mdatablock -->
   <!-- BEGIN emptyblock -->
   <TR CLASS="content"><TD COLSPAN="10"><DIV ALIGN="center">{no_data}</DIV></TD></TR>
   <!-- END emptyblock -->
  </Table>
 </TD></TR>
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="right">{right}{last}</DIV></TD></TR>
</TABLE>

</TD></TR></TABLE>
</DIV>
</TD></TR></TABLE>