<H2 Align=Center>{listtitle}</H2>
<CENTER>{save_result}</CENTER>
<FORM NAME="{form_name}" METHOD="post" ACTION="{form_target}">
{hiddenfields}
<Table Width="90%" Align="Center" Border="1">
 <TR><TH ColSpan=4>{title}</TH></TR>
 <TR>
  <TD Width=20%>{mtype_name}</TD><TD Width=30%>&nbsp;{mtype}</TD>
  <TD Width=20%>{country_name}</TD><TD Width=30%>&nbsp;{country}</TD></TR>
 <TR>
  <TD Width=20%>{medianr_name}</TD><TD Width=30%>&nbsp;{medianr}</TD>
  <TD>{year_name}</TD><TD>&nbsp;{year}</TD></TR>
 <TR>
  <TD ColSpan=2><TABLE WIDTH="100%" CellPadding=0 CellSpacing=0>
       <TR><TD>{length_name}</TD><TD>&nbsp;{length}</TD>
       <TD>{longplay_name}:&nbsp;{longplay}</TD></TR>
       <TR><TD>{counter_name}<TD>&nbsp;{counter_1}</TD>
       <TD>{counter_2}</TD></TR>
       <TR><TD>{commercial_name}<TD ColSpan=2>&nbsp;{commercial}</TD></TR>
      </TABLE></TD>
  <TD>{category_name}</TD><TD>{category}</TD></TR>
 <TR>
  <TD ColSpan=2>
   <Table Width=100% Border=0 CellPadding=0 CellSpacing=0>
    <TR><TD>{mlength_free_name}</TD><TD>&nbsp;{mlength_free}</TD></TR>
    <TR><TD>{date_name}</TD><TD>&nbsp;{date}</TD></TR>
    <TR><TD ColSpan="2"><HR></TD></TR>
    <TR><TD WIDTH=30%>{tone_name}</TD><TD>&nbsp;{tone}</TD></TR>
    <TR><TD>{picture_name}</TD><TD>&nbsp;{picture}</TD></TR>
    <TR><TD Width=40%>{screen_name}</TD><TD Width=60%>&nbsp;{screen}</TD></TR>
    <TR><TD Width=40%>{source_name}</TD><TD Width=60%>&nbsp;{source}</TD></TR>
    <TR><TD>{fsk_name}</TD><TD>&nbsp;{fsk}</TD></TR>
   </Table></TD>
  <TD ColSpan=2>
   <Table Width=100% Border=0 CellPadding=0 CellSpacing=0>
    <TR><TD><B>{staff_name}</B></TD><TD>{name_name}</TD><TD>{firstname_name}</TD><TD><DIV ALIGN="center">{inlist_name}</DIV></TD></TR>
    <TR><TD>{director_name}</TD><TD>{director}</TD><TD>{director_f}</TD><TD><div align=center>{director_list}</div></TD></TR>
    <TR><TD>{composer_name}</TD><TD>{composer}</TD><TD>{composer_f}</TD><TD><div align=center>{composer_list}</div></TD></TR>
    <TR><TD COLSPAN="4"><HR></TD></TR>
    <!-- BEGIN actorblock -->
    <TR><TD>{actor_name}</TD><TD>{actor}</TD><TD>{actor_f}</TD><TD><div align=center>{actor_list}</div></TD></TR>
    <!-- END actorblock -->
   </Table>
  </TD></TR>
 <TR><TD ColSpan=4 Align=Center>
   <TABLE WIDTH="100%" BORDER="0">
     <TR><TH><HR>{comments_name}<HR></TH></TR>
     <TR><TD>{comments}</TD></TR>
   </TABLE>
 <TR><TD ColSpan=4>
   <Table Width="100%">
    <TR><TD Width="50%">{button_li}</TD>
        <TD Width="50%"><div align=right>{button_re}</div></TD></TR>
   </TABLE>
 </TD></TR>
</Table>
</FORM>
