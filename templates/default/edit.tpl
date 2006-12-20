<style type="text/css"><!--
 ul {margin-left: 5; padding-left: 10px; margin-top: 0; margin-bottom:0; padding-top:0; padding-bottom:0;}
 li {margin-top: 0; margin-bottom:0;}
--></style>
<H2 Align=Center>{listtitle}</H2>
<CENTER>{save_result}</CENTER>
<FORM NAME="{form_name}" METHOD="post" ACTION="{form_target}">
{hiddenfields}
<Table Width="90%" Align="Center" Border="1" Style="table-layout:fixed">
 <COLGROUP>
  <COL WIDTH="50%">
  <COL WIDTH="50%">
 </COLGROUP>
 <TR><TH ColSpan="2">
   <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0">
     <TR><TH WIDTH="10%" VALIGN="top">{previous}</TH><TH WIDTH="80%"> {title}</TH>
         <TH WIDTH="10%" ALIGN="right" VALIGN="top">{next}</TH></TR>
   </TABLE>
 <TR>
  <TD>
   <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0">
    <COLGROUP><COL WIDTH="150"><COL WIDTH="*"></COLGROUP>
    <TR><TD>{mtype_name}</TD><TD>{mtype}</TD></TR>
    <TR><TD>{medianr_name}</TD><TD>
      <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0"><TR>
        <TD WIDTH="50%"{konq_fix}>{medianr}</TD><TD WIDTH="50%">{minfo_link}</TD></TR>
      </TABLE></TD></TR>
    <TR><TD>{counter_name}</TD><TD>
      <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0">
        <TD WIDTH="50%"{konq_fix}>{counter}</TD><TD WIDTH="25%">{label_name}</TD><TD WIDTH="25%">{label}</TD></TR>
      </TABLE></TD></TR>
    <TR><TD>{rc_name}</TD><TD>{rc}</TD></TR>
    <TR><TD>{commercial_name}</TD><TD>{commercial}</TD></TR>
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
    <COLGROUP><COL WIDTH="150"><COL WIDTH="*"></COLGROUP>
    <TR><TD>{length_name}</TD>
        <TD><TABLE WIDTH="100%" BORDER="0" CELLPADDING="0" CELLSPACING="0">
          <TD WIDTH="50%">{length}</TD>
          <TD WIDTH="25%">{longplay_name}</TD>
          <TD WIDTH="25%">{longplay}</TD></TR>
        </TABLE></TD></TR>
    <TR><TD>{mlength_free_name}</TD><TD>{mlength_free}</TD></TR>
    <TR><TD>{date_name}</TD><TD>{date}</TD></TR>
    <TR><TD>{tone_name}</TD><TD>{tone}</TD></TR>
    <TR><TD>{picture_name}</TD><TD>{picture}</TD></TR>
    <TR><TD>{screen_name}</TD><TD>
      <TABLE BORDER="0" CellPadding="0" CellSpacing="0">
        <TR><TD>{screen}</TD><TD>{vnorm}</TD></TR>
      </TABLE>
    </TD></TR>
    <TR><TD>{source_name}</TD><TD>{source}</TD></TR>
    <TR><TD>{fsk_name}</TD><TD>{fsk}</TD></TR>
    <TR><TD VALIGN="top">{audio_name}</TD><TD>{audio}</TD></TR>
    <TR><TD VALIGN="top">{subtitle_name}</TD><TD>{subtitle}</TD></TR>
   </TABLE>
  </TD>
  <TD>
   <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0">
    <COLGROUP><COL WIDTH="15%"><COL WIDTH="30%"><COL WIDTH="30%"><COL WIDTH="15%"></COLGROUP>
    <TR><TD><DIV ALIGN="center"><B>{staff_name}</B></DIV></TD>
        <TD><DIV ALIGN="center"><B>{name_name}</DIV></TD>
        <TD><DIV ALIGN="center"><B>{firstname_name}</DIV></TD>
	<TD><DIV ALIGN="center"><B>{inlist_name}</DIV></TD></TR>
    <TR><TD>{director_name}</TD><TD><DIV ALIGN="center">{director}</DIV></TD>
        <TD><DIV ALIGN="center">{director_f}</DIV></TD><TD><DIV ALIGN="center">{director_list}</DIV></TD></TR>
    <TR><TD>{composer_name}</TD><TD><DIV ALIGN="center">{composer}</DIV></TD>
        <TD><DIV ALIGN="center">{composer_f}</DIV></TD><TD><DIV ALIGN="center">{composer_list}</DIV></TD></TR>
    <TR><TD COLSPAN="4"><HR></TD></TR>
    <!-- BEGIN actorblock -->
    <TR><TD>{actor_name}</TD><TD><DIV ALIGN="center">{actor}</DIV></TD>
        <TD><DIV ALIGN="center">{actor_f}</DIV></TD><TD><DIV ALIGN="center">{actor_list}</DIV></TD></TR>
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
