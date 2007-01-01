<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="90%" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0" ALIGN="center"><TR><TD>
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
<TR><TD><DIV ALIGN="center">

<TABLE ALIGN="center" STYLE="margin:3">
 <TR><TH>{ititle}</TH></TR>
 <TR CLASS="content"><TD STYLE="text-align:justify">{idetails}</TD></TR>
</TABLE>

<TABLE ALIGN="center" STYLE="margin:3">
 <TR><TH>{mtitle}</TH></TR>
 <!-- BEGIN movieblock -->
 <!-- BEGIN nomovieitem -->
 <TR CLASS="content"><TD CLASS="content">{details}</TD></TR>
 <!-- END nomovieitem -->
 <!-- BEGIN havemovieitem -->
 <TR CLASS="content"><TD>
   <FORM ACTION="{formtarget}"' METHOD="post" NAME="orphaned_movies">
   <DIV ALIGN="center"><TABLE ALIGN="center" BORDER="0">
     <TR><TH>{owner_name}</TH><TH>{movie_name}</TH>
     <!-- BEGIN movieitem -->
     <TR><TD>{owner}</TD><TD>{imovie}</TD></TR>
     <!-- END movieitem -->
     <TR><TD COLSPAN="2"><DIV ALIGN="center">{mbutton}</DIV></TD></TR>
   </TABLE></DIV>
   </FORM>
 </TD></TR>
 <!-- END havemovieitem -->
 <!-- END movieblock -->
</TABLE>

<TABLE ALIGN="center" STYLE="margin:3">
 <!-- BEGIN itemblock -->
 <TR><TH>{title}</TH></TR>
 <TR CLASS="content"><TD STYLE="text-align:justify">{details}</TD></TR>
 <!-- END itemblock -->
</TABLE>

</DIV>
</TD></TR>

<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD>
<FORM NAME='admin_orphans' METHOD='post' ACTION='{formtarget}'>{hidden}
 <DIV STYLE="margin:3;text-align:center">{button}</DIV>
</FORM>
</TD></TR>

</TABLE>
</DIV>
</TD></TR></TABLE>