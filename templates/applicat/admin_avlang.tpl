<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0" ALIGN="center"><TR><TD>
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
<FORM NAME="admin_avlang" METHOD="post" ACTION="{formtarget}">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
<TR><TD>

<CENTER>
<!-- BEGIN listblock -->
<TABLE BORDER="0" WIDTH="100%">
  <TR><TD>{first}{left}</TD><TD><DIV STYLE="margin:3;text-align:center">{save_result}</DIV></TD><TD><DIV ALIGN="right">{right}{last}</DIV></TD></TR>
</TABLE>
<TABLE ALIGN="center" BORDER="0" CLASS="data" STYLE="margin:3px;">
 <TR><TH><DIV ALIGN="center">{head_lang_id}</DIV></TH>
     <TH><DIV ALIGN="center">{head_lang_name}</DIV></TH>
     <!--TH><DIV ALIGN="center">{head_lang_charset}</DIV></TH -->
     <TH><DIV ALIGN="center">{head_lang_locale}</DIV></TH>
     <TH><DIV ALIGN="center">{head_lang_audio}</DIV></TH>
     <TH><DIV ALIGN="center">{head_lang_subtitle}</DIV></TH>
     <TH>&nbsp;</TH></TR>
<!-- BEGIN langblock -->
 <TR CLASS="content"><TD><DIV ALIGN="center">{lang_id}</DIV></TD>
     <TD><DIV ALIGN="center">{lang_name}</DIV></TD>
     <!--TD><DIV ALIGN="center">{lang_charset}</DIV></TD-->
     <TD><DIV ALIGN="center"><IMG SRC="{tpl_dir}images/{lang_locale}" ALT="{alt_lang_locale}"></DIV></TD>
     <TD><DIV ALIGN="center"><IMG SRC="{tpl_dir}images/{lang_audio}" ALT="{alt_lang_audio}"></DIV></TD>
     <TD><DIV ALIGN="center"><IMG SRC="{tpl_dir}images/{lang_subtitle}" ALT="{alt_lang_subtitle}"></DIV></TD>
     <TD><DIV ALIGN="center"><A HREF="{lang_edit}"><IMG SRC="{tpl_dir}images/edit.gif" ALT="Edit" BORDER="0"></A></DIV></TD></TR>
<!-- END langblock -->
</TABLE>
<!-- END listblock -->

<!-- BEGIN editblock -->
<TABLE ALIGN="center" BORDER="0" CLASS="data" STYLE="margin:3px;">
 <TR><TH COLSPAN="2"><DIV ALIGN="center">{lang_name} ({lang_id})</DIV></TH></TR>
 <TR><TH STYLE="vertical-align:middle">{head_lang_audio}</TH>
     <TD>{lang_audio}</TD></TR>
 <TR><TH STYLE="vertical-align:middle">{head_lang_subtitle}</TH>
     <TD>{lang_subtitle}</TD></TR>
 <TR><TH COLSPAN="2"><DIV STYLE="margin:3;text-align:center">{update}</DIV></TH></TR>
</TABLE>
<!-- END editblock -->

</CENTER>
{hidden}
</TD></TR>
</TABLE></FORM></TD></TR>

<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>

</TABLE>
</DIV>
</TD></TR></TABLE>