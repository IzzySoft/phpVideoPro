<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin" Style="table-layout:fixed"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="*" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER=0" ALIGN="center"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle"><DIV STYLE="margin:2">{listtitle}</DIV></TD>
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

<TABLE ALIGN="center" BORDER="0" WIDTH="100%" CELLPADDING="0" CELLSPACING="0" STYLE="margin:3">
 <FORM NAME="transform" METHOD="post" ACTION="{formtarget}" ACCEPT-CHARSET="{charset}">
 {hidden}
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
 <TR><TD COLSPAN=2><DIV STYLE="margin:3">
  <TABLE ALIGN="center" BORDER="1" CELLPADDING="2" CELLSPACING="2">
   <!-- BEGIN mtitleblock -->
   <COLGROUP><COL WIDTH="150 pt"><COL WIDTH="3*"><COL WIDTH="380 pt"><COL WIDTH="3*"></COLGROUP>
   <TR><TH>{code}</TH>
       <TH>{orig}</TH>
       <TH>{trans}</A></TH>
       <TH>{sample}</A></TH>
   </TR>
   <!-- END mtitleblock -->
   <!-- BEGIN mdatablock -->
   <TR CLASS="content"><TD>{code}</TD>
       <TD>{orig}</TD>
       <TD>{trans}</TD>
       <TD>{sample}</TD>
   </TR>
   <!-- END mdatablock -->
   <!-- BEGIN emptyblock -->
   <TR CLASS="content"><TH COLSPAN="3" STYLE="vertical-align:middle">{sel_lang_title}</TH><TD COLSPAN="1"><DIV ALIGN="center">{sel_lang}</DIV></TD></TR>
   <!-- END emptyblock -->
  </Table></DIV></TD></TR>
 <TR><TD COLSPAN="2" BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
 <TR><TD COLSPAN="2" BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
 <TR><TD COLSPAN="2" STYLE="vertical-align:middle"><DIV STYLE="margin:3;text-align:center">
   <INPUT TYPE="submit" CLASS="submit" NAME="{submit_name}" VALUE="{submit}"><BR><BR>{save}</DIV></TD></TR>
 <TR><TD>{first}{left}</TD>
     <TD><DIV ALIGN="RIGHT">{right}{last}</DIV></TD></TR>
 </FORM>
</TABLE>

</TD></TR>
</TABLE>
</DIV>
</TD></TR></TABLE>