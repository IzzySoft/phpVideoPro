<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="*" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER=0" ALIGN="center"><TR><TD>
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
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD>

<TABLE BORDER="0" WIDTH="100%">
  <TR><TD>{first}{left}</TD><TD><DIV STYLE="margin:3;text-align:center">{save_result}</DIV></TD><TD><DIV ALIGN="right">{right}{last}</DIV></TD></TR>
</TABLE>
<FORM NAME="admin_avlang" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="1" STYLE="margin:3">
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
     <TD><DIV ALIGN="center"><IMG SRC="{tpl_dir}images/{lang_locale}"></DIV></TD>
     <TD><DIV ALIGN="center"><IMG SRC="{tpl_dir}images/{lang_audio}"></DIV></TD>
     <TD><DIV ALIGN="center"><IMG SRC="{tpl_dir}images/{lang_subtitle}"></DIV></TD>
     <TD><DIV ALIGN="center"><A HREF="{lang_edit}"><IMG SRC="{tpl_dir}images/edit.png"></A></DIV></TD></TR>
<!-- END langblock -->
 {hidden}
</TABLE>

</TD></TR>

<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<!--TR><TD><DIV STYLE="margin:3;text-align:center">{update}</DIV></TR-->
</FORM>

</TABLE>
</DIV>
</TD></TR></TABLE>