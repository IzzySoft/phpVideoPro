<H2 ALIGN="center">{listtitle}</H2>{js}
<FORM NAME="searchform" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="1" STYLE="table-layout:fixed" WIDTH="70%">
 <COLGROUP><COL WIDTH="50%"><COL WIDTH="50%"></COLGROUP>
 <TR><TD><DIV ALIGN="center">{mtype_name}<BR>{mtype_field}</DIV></TD>
     <TD><DIV ALIGN="center">{cat_name}<BR>{cat_field}</DIV></TD></TR>
 <TR><TD><DIV ALIGN="center">{audio_name}<BR>{audio_field}</DIV></TD>
     <TD><DIV ALIGN="center">{subtitle_name}<BR>{subtitle_field}</DIV></TD></TR>
 <TR><TD><DIV ALIGN="center">{person_field}</DIV></TD>
     <TD><DIV ALIGN="center">{name_field}</DIV></TD></TR>
 <TR><TD><DIV ALIGN="center">{title_name}</DIV></TD><TD><DIV ALIGN="center">{title_field}</DIV></TD></TR>
 <TR ALIGN="center"><TD><DIV ALIGN="center">{comment_name}</DIV></TD><TD><DIV ALIGN="center">{comment_field}</DIV></TD></TR>
 <TR ALIGN="center"><TD><DIV ALIGN="center">{length_name}</DIV></TD><TD><DIV ALIGN="center">{length_min} - {length_max} {min}</DIV></TD></TR>
 <TR ALIGN="center"><TD><DIV ALIGN="center">{fsk_name}</DIV></TD><TD><DIV ALIGN="center">{fsk_min} - {fsk_max}</DIV></TD></TR>
 <TR ALIGN="center"><TH COLSPAN="2"><INPUT TYPE="submit" NAME="submit" VALUE="{submit}"></TH></TR>
 <TR CLASS="content" ALIGN="center"><TD><DIV ALIGN="center"><B>{rating_name}</B></DIV></TD><TD><DIV ALIGN="center">{rating_min} - {rating_max}</DIV></TD></TR>
 <TR CLASS="content" ALIGN="center"><TD><DIV ALIGN="center"><B>{lastchange_name}</B></DIV></TD><TD><DIV ALIGN="center">{lastchange_min} - {lastchange_max}</DIV></TD></TR>
</TABLE>
{hidden}
</FORM>
<!-- resultblock = medialist.tpl -->
