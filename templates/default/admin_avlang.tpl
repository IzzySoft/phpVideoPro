<CENTER>
<H2>{listtitle}</H2>
<!-- BEGIN listblock -->
<FORM NAME="admin_avlang" METHOD="post" ACTION="{formtarget}">
<TABLE BORDER="1" STYLE="margin:3">
 <TR><TD COLSPAN="6">
    <TABLE BORDER="0" WIDTH="100%">
      <TR><TD>{first}{left}</TD><TD><DIV STYLE="margin:3;text-align:center">{save_result}</DIV></TD><TD><DIV ALIGN="right">{right}{last}</DIV></TD></TR>
    </TABLE>
   </TD></TR>
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
     <TD><DIV ALIGN="center"><A HREF="{lang_edit}"><IMG SRC="{tpl_dir}images/edit.png" ALT="Edit" BORDER="0"></A></DIV></TD></TR>
<!-- END langblock -->
</TABLE>
<!-- END listblock -->

<!-- BEGIN editblock -->
<FORM NAME="admin_avlang" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="1" STYLE="margin:3">
 <TR><TH COLSPAN="2"><DIV ALIGN="center">{lang_name} ({lang_id})</TH></TR>
 <TR><TH STYLE="vertical-align:middle">{head_lang_audio}</TH>
     <TD>{lang_audio}</TD></TR>
 <TR><TH STYLE="vertical-align:middle">{head_lang_subtitle}</TH>
     <TD>{lang_subtitle}</TD></TR>
 <TR><TH COLSPAN="2"><DIV STYLE="margin:3;text-align:center">{update}</DIV></TH></TR>
</TABLE>
<!-- END editblock -->

</TD></TR>

<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0"></TD></TR>
{hidden}
</FORM></CENTER>
