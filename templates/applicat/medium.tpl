<BR STYLE="margin-top:50">
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER=0" ALIGN="center"><TR><TD>
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

 <FORM NAME="mediaform" METHOD="post" ACTION="{form_target}">
  <TABLE CLASS="data" STYLE="margin:3px;text-align:center" BORDER="0">
    <TR><TH>{techdata}</TH><TH>{moviedata}</TH></TR>
    <TR CLASS="content"><TD STYLE='vertical-align:middle'><TABLE BORDER="0">
<!-- BEGIN techblock -->
        <TR><TD><DIV ALIGN="right">{tname}</DIV></TD>
            <TD><DIV ALIGN="right">{tdata}</DIV></TD><TD>{tunit}</TD></TR>
<!-- END techblock -->
        </TABLE></TD><TD STYLE='vertical-align:middle'><TABLE BORDER="0">
<!-- BEGIN movieblock -->
        <TR><TD STYLE='text-align:right'>{mlink}</TD><TD>{mdata}</TD></TR>
<!-- END movieblock -->
        </TABLE></TD></TR>
  </TABLE>
  <DIV ALIGN="center">{formactions}</DIV>
 </FORM>

</TD></TR>
</TABLE>
</DIV>
</TD></TR></TABLE>