<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" STYLE="table-layout:fixed;" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER=0" ALIGN="center"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle"><DIV STYLE="margin:2">{listtitle}</DIV></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{home_title}" NAME="button_home" CLASS="imgbut" SRC="{tpl_dir}images/win_home.gif" STYLE="width:14;height:13;" onClick="window.location.href='{home_link}'"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{help_title}" NAME="button_help" CLASS="imgbut" SRC="{tpl_dir}images/win_help.gif" STYLE="width:14;height:13;" onClick="{help_link}"></TD>
     <TD CLASS="wintitle" STYLE="vertical-align:middle;margin-right:3;"><DIV STYLE="width:18;">
      <INPUT TYPE="image" TITLE="{logoff_title}" NAME="button_close" CLASS="imgbut" SRC="{tpl_dir}images/win_close.gif" STYLE="width:14;height:13;" onClick="window.location.href='{logoff_link}'"></DIV></TD></TR>
</TABLE></TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD>

<FORM NAME="searchform" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="1" STYLE="margin:3">
 <COLGROUP><COL WIDTH="50%"><COL WIDTH="50%"></COLGROUP>
 <TR CLASS="content"><TD><DIV ALIGN="center">{mtype_name}<BR>{mtype_field}</DIV></TD>
     <TD><DIV ALIGN="center">{cat_name}<BR>{cat_field}</DIV></TD></TR>
 <TR CLASS="content"><TD><DIV ALIGN="center">{audio_name}<BR>{audio_field}</DIV></TD>
     <TD><DIV ALIGN="center">{subtitle_name}<BR>{subtitle_field}</DIV></TD></TR>
 <TR CLASS="content"><TD><DIV ALIGN="center">{person_field}</DIV></TD>
     <TD><DIV ALIGN="center">{name_field}</DIV></TD></TR>
 <TR CLASS="content"><TD><DIV ALIGN="center">{title_name}</DIV></TD><TD><DIV ALIGN="center">{title_field}</DIV></TD></TR>
 <TR CLASS="content" ALIGN="center"><TD><DIV ALIGN="center">{comment_name}</DIV></TD><TD><DIV ALIGN="center">{comment_field}</DIV></TD></TR>
 <TR CLASS="content" ALIGN="center"><TD><DIV ALIGN="center">{length_name}</DIV></TD><TD><DIV ALIGN="center">{length_min} - {length_max} {min}</DIV></TD></TR>
 <TR CLASS="content" ALIGN="center"><TD><DIV ALIGN="center">{fsk_name}</DIV></TD><TD><DIV ALIGN="center">{fsk_min} - {fsk_max}</DIV></TD></TR>
</TABLE>
<!-- resultblock = medialist.tpl -->
{hidden}
</TD></TR>

<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD><DIV STYLE="margin:3;text-align:center;"><INPUT CLASS="submit" TYPE="submit" NAME="submit" VALUE="{submit}"></DIV></TD></TR>
</FORM>

</TABLE>
</DIV>
</TD></TR></TABLE>