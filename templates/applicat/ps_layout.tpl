<BR STYLE="margin-top:50">
<TABLE STYLE="table-layout:fixed;" ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<FORM NAME="label" METHOD="post" ACTION="{form_target}">
<TABLE WIDTH="*" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0" ALIGN="center"><TR><TD>
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

 <DIV WIDTH="100%">
 <TABLE Style="text-align:center;margin:3;"><TR><TD>
  <INPUT TYPE=HIDDEN NAME="ltype_id" VALUE="{ltype}">
  {sess_id}
  <TABLE ALIGN="center">
    <TR><TH>{hmtype_0}</TH>
        <TH>{hmedianr_0}</TH>
        <TH>{hlabel_0}</TH>
        <TH>{hmtype_1}</TH>
        <TH>{hmedianr_1}</TH>
        <TH>{hlabel_1}</TH>
        <!--TH>{hmtype_2}</TH>
        <TH>{hmedianr_2}</TH>
        <TH>{hlabel_2}</TH></TR-->
    <!-- BEGIN definitionblock -->
    <TR CLASS="content"><TD><DIV ALIGN="center">{mtype_0}</DIV></TD>
        <TD><DIV ALIGN="center">{medianr_0}</DIV></TD>
        <TD><DIV ALIGN="center">{label_0}</DIV></TD>
        <TD><DIV ALIGN="center">{mtype_1}</DIV></TD>
        <TD><DIV ALIGN="center">{medianr_1}</DIV></TD>
        <TD><DIV ALIGN="center">{label_1}</DIV></TD>
        <!--TD><DIV ALIGN="center">{mtype_2}</DIV></TD>
        <TD><DIV ALIGN="center">{medianr_2}</DIV></TD>
        <TD><DIV ALIGN="center">{label_2}</DIV></TD></TR-->
    <!-- END definitionblock -->
  </TABLE></TD></TR><TR><TD><TABLE ALIGN="center" WIDTH="100%">
    <TR CLASS="content"><TD><DIV STYLE="margin:3;text-align:center">{max_fontsize_desc} {max_fontsize}</DIV></TD></TR>
  </TABLE>
 </TD></TR></TABLE></DIV>

</TD></TR>

<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD><DIV STYLE="text-align:center;margin:3;"><INPUT CLASS="submit" TYPE="submit" NAME="create" VALUE="{create}"></DIV></TD></TR>

</TABLE>
</FORM>
</DIV>
</TD></TR></TABLE>