<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER=0" ALIGN="center"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle"><DIV STYLE="margin:2">{listtitle}</DIV></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" NAME="button_home" CLASS="imgbut" SRC="{tpl_dir}images/win_home.gif" WIDTH="14" HEIGHT="13" onClick="window.location.href='{home_link}'"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" NAME="button_search" CLASS="imgbut" SRC="{tpl_dir}images/win_search.gif" WIDTH="14" HEIGHT="13" onClick="window.location.href='{search_link}'"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" NAME="button_help" CLASS="imgbut" SRC="{tpl_dir}images/win_help.gif" WIDTH="14" HEIGHT="13" onClick="{help_link}"></TD>
     <TD CLASS="wintitle" STYLE="vertical-align:middle;margin-right:3;"><DIV STYLE="width:18;">
      <INPUT TYPE="image" NAME="button_close" CLASS="imgbut" SRC="{tpl_dir}images/win_close.gif" WIDTH="14" HEIGHT="13" onClick="window.location.href='{logoff_link}'"></DIV></TD></TR>
</TABLE></TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD>

<DIV STYLE="margin:3;text-align:center">{save_result}</DIV>
<FORM NAME="admin_movietech" METHOD="post" ACTION="{formtarget}">
<!-- BEGIN mainblock -->
<TABLE ALIGN="center" BORDER="0">
 <TR><TD>
   <TABLE ALIGN="center" BORDER="1">
    <TR><TH COLSPAN="3">{screen_title}</TH></TR>
    <TR CLASS="content"><TD><DIV ALIGN="center"><B>{name}</B></DIV></TD>
        <TD><DIV ALIGN="center"><B>{sname}</B></DIV></TD>
	<TD>&nbsp;</TD></TR>
    <!-- BEGIN screenitemblock -->
    <TR CLASS="content"><TD>{item_name}</TD><TD>{item_sname}</TD><TD>{edit} {trash}</TD></TR>
    <!-- END screenitemblock -->
    <TR CLASS="content"><TD COLSPAN="3"><DIV ALIGN="center">{screen_add}</DIV></TD></TR>
   </TABLE>
 </TD><TD>
   <TABLE ALIGN="center" BORDER="1">
    <TR><TH COLSPAN="3">{color_title}</TH></TR>
    <TR CLASS="content"><TD><DIV ALIGN="center"><B>{name}</B></DIV></TD>
        <TD><DIV ALIGN="center"><B>{sname}</B></DIV></TD>
	<TD>&nbsp;</TD></TR>
    <!-- BEGIN coloritemblock -->
    <TR CLASS="content"><TD>{item_name}</TD><TD>{item_sname}</TD><TD>{edit} {trash}</TD></TR>
    <!-- END coloritemblock -->
    <TR CLASS="content"><TD COLSPAN="3"><DIV ALIGN="center">{color_add}</DIV></TD></TR>
   </TABLE>
 </TD></TR><TR><TD>
   <TABLE ALIGN="center" BORDER="1">
    <TR><TH COLSPAN="3">{mtype_title}</TH></TR>
    <TR CLASS="content"><TD><DIV ALIGN="center"><B>{name}</B></DIV></TD>
        <TD><DIV ALIGN="center"><B>{sname}</B></DIV></TD>
	<TD>&nbsp;</TD></TR>
    <!-- BEGIN mtypeitemblock -->
    <TR CLASS="content"><TD>{item_name}</TD><TD>{item_sname}</TD><TD>{edit} {trash}</TD></TR>
    <!-- END mtypeitemblock -->
    <TR CLASS="content"><TD COLSPAN="3"><DIV ALIGN="center">{mtype_add}</DIV></TD></TR>
   </TABLE>
 </TD><TD>
   <TABLE ALIGN="center" BORDER="1">
    <TR><TH COLSPAN="3">{tone_title}</TH></TR>
    <TR CLASS="content"><TD><DIV ALIGN="center"><B>{name}</B></DIV></TD>
        <TD><DIV ALIGN="center"><B>{sname}</B></DIV></TD>
	<TD>&nbsp;</TD></TR>
    <!-- BEGIN toneitemblock -->
    <TR CLASS="content"><TD>{item_name}</TD><TD>{item_sname}</TD><TD>{edit} {trash}</TD></TR>
    <!-- END toneitemblock -->
    <TR CLASS="content"><TD COLSPAN="3"><DIV ALIGN="center">{tone_add}</DIV></TD></TR>
   </TABLE>
 </TD></TR>
</TABLE>
<!-- END mainblock -->
<!-- BEGIN editblock -->
<DIV STYLE="margin:3">
<TABLE ALIGN="center" BORDER="1">
 <TR><TH COLSPAN="2">{edit_title}</TH></TR>
 <TR><TH>{name_name}</TH><TD><INPUT NAME="name" VALUE="{name}" CLASS="techinput"></TD></TR>
 <TR><TH>{sname_name}</TH><TD><INPUT NAME="sname" VALUE="{sname}" CLASS="techinput"></TD></TR>
 <INPUT TYPE="hidden" NAME="type" VALUE="{type}">
 <INPUT TYPE="hidden" NAME="id" VALUE="{id}">
</TABLE>
</DIV>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD><DIV STYLE="margin:3;text-align:center"><INPUT TYPE="submit" CLASS="submit" NAME="update" VALUE="{add}" CLASS="techinput"></DIV></TR>
</FORM>
<!-- END editblock -->


</TABLE>
</DIV>
</TD></TR></TABLE>