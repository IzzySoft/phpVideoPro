<H2 Align=Center>{listtitle}</H2>
<CENTER>{save_result}</CENTER>
<FORM NAME="{form_name}" METHOD="post" ACTION="{form_target}">
{hiddenfields}
<Table Width="90%" Align="Center" Border="1">
 <COLGROUP>
  <COL WIDTH="50%">
  <COL WIDTH="50%">
 </COLGROUP>
 <TR><TH ColSpan="2">{title}</TH></TR>
 <TR>
  <TD>
   <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0">
    <COLGROUP><COL WIDTH="40%"><COL WIDTH="60%"></COLGROUP>
    <TR><TD>{mtype_name}</TD><TD>{mtype}</TD></TR>
    <TR><TD>{medianr_name}</TD><TD>{medianr}</TD></TR>
   </TABLE>
   <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0">
    <COLGROUP><COL WIDTH="40%"><COL WIDTH="30%"><COL WIDTH="30%"></COLGROUP>
    <TR><TD>{length_name}</TD><TD>{length}</TD>
        <TD>{longplay_name}:&nbsp;{longplay}</TD></TR>
    <TR><TD>{counter_name}</TD><TD>{counter_1}</TD>
        <TD>{counter_2}</TD></TR>
    <TR><TD>{commercial_name}</TD><TD ColSpan="2">{commercial}</TD></TR>
   </TABLE>
  </TD>
  <TD>
   <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0">
    <COLGROUP><COL WIDTH="40%"><COL WIDTH="60%"></COLGROUP>
    <TR><TD>{country_name}</TD><TD>{country}</TD></TR>
    <TR><TD>{year_name}</TD><TD>{year}</TD></TR>
    <TR><TD>{category_name}</TD><TD>{category}</TD></TR>
   </TABLE>
  </TD></TR>
 <TR>
  <TD>
   <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0">
    <COLGROUP><COL WIDTH="40%"><COL WIDTH="60%"></COLGROUP>
    <TR><TD>{mlength_free_name}</TD><TD>{mlength_free}</TD></TR>
    <TR><TD>{date_name}</TD><TD>{date}</TD></TR>
    <TR><TD>{tone_name}</TD><TD>{tone}</TD></TR>
    <TR><TD>{picture_name}</TD><TD>{picture}</TD></TR>
    <TR><TD>{screen_name}</TD><TD>{screen}</TD></TR>
    <TR><TD>{source_name}</TD><TD>{source}</TD></TR>
    <TR><TD>{fsk_name}</TD><TD>{fsk}</TD></TR>
   </TABLE>
  </TD>
  <TD>
   <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0">
    <COLGROUP><COL WIDTH="15%"><COL WIDTH="30%"><COL WIDTH="30%"><COL WIDTH="15%"></COLGROUP>
    <TR><TD><DIV ALIGN="center"><B>{staff_name}</B></DIV></TD>
        <TD><DIV ALIGN="center"><B>{name_name}</DIV></TD>
        <TD><DIV ALIGN="center"><B>{firstname_name}</DIV></TD>
	<TD><DIV ALIGN="center"><B>{inlist_name}</DIV></TD></TR>
    <TR><TD>{director_name}</TD><TD>{director}</TD>
        <TD>{director_f}</TD><TD><DIV ALIGN="center">{director_list}</DIV></TD></TR>
    <TR><TD>{composer_name}</TD><TD>{composer}</TD>
        <TD>{composer_f}</TD><TD><DIV ALIGN="center">{composer_list}</DIV></TD></TR>
    <TR><TD COLSPAN="4"><HR></TD></TR>
    <!-- BEGIN actorblock -->
    <TR><TD>{actor_name}</TD><TD>{actor}</TD>
        <TD>{actor_f}</TD><TD><DIV ALIGN="center">{actor_list}</DIV></TD></TR>
    <!-- END actorblock -->
   </TABLE>
  </TD></TR>
 <TR><TD COLSPAN="2" Align="center">
   <TABLE WIDTH="100%" BORDER="0">
     <TR><TH><HR>{comments_name}<HR></TH></TR>
     <TR><TD>{comments}</TD></TR>
   </TABLE>
 <TR><TD COLSPAN="2">
   <Table Width="100%">
    <TR><TD Width="33%">{button_li}</TD>
        <TD Width="34%"><DIV ALIGN="center">{print_label}</DIV></TD>
        <TD Width="33%"><div align="right">{button_re}</div></TD></TR>
   </TABLE>
 </TD></TR>
</Table>
</FORM>
