<H2 Align=Center>{listtitle}</H2>
<CENTER>{save_result}</CENTER>
<FORM NAME="{form_name}" METHOD="post" ACTION="{form_target}">
{hiddenfields}
<Table Width="90%" Align="Center" Border="1">
 <TR><TH ColSpan=4>{title}</TH></TR>
 <TR>
  <TD Width=20%>{mtype_name}</TD><TD Width=30%>{mtype}</TD>
  <TD Width=20%>{country_name}</TD><TD Width=30%>{country}</TD></TR>
 <TR>
  <TD Width=20%>{medianr_name}</TD><TD Width=30%>{medianr}</TD>
  <TD>{year_name}</TD><TD>{year}</TD></TR>
 <TR>
  <TD>{length_name}</TD>
  <TD><TABLE WIDTH="100%" CellPadding=0 CellSpacing=0>
       <TR><TD>{length}</TD>
       <TD>{longplay_name}:&nbsp;{longplay}</TD></TR></TABLE>
  <TD>{category_name}</TD><TD>{category}</TD></TR>
 <TR>
  <TD ColSpan=2>
   <Table Width=100% Border=0 CellPadding=0 CellSpacing=0>
    <TR><TD>{mlength_free_name}</TD><TD>{mlength_free}</TD></TR>
    <TR><TD>{date_name}</TD><TD>{date}</TD></TR>
    <TR><TD ColSpan="2"><HR></TD></TR>
    <TR><TD WIDTH=30%>{tone_name}</TD><TD>{tone}</TD></TR>
    <TR><TD>{picture_name}</TD><TD>{picture}</TD></TR>
    <TR><TD Width=40%>{screen_name}</TD><TD Width=60%>{screen}</TD></TR>
    <TR><TD Width=40%>{source_name}</TD><TD Width=60%>{source}</TD></TR>
    <TR><TD>{fsk_name}</TD><TD>{fsk}</TD></TR>
   </Table></TD>
  <TD ColSpan=2>
   <Table Width=100%>
    <TR><TD><B>{staff_name}</B></TD><TD>{name_name}</TD><TD>{firstname_name}</TD><TD><DIV ALIGN="center">{inlist_name}</DIV></TD></TR>
    <TR><TD>{director_name}</TD><TD>{director}</TD><TD>{director_f}</TD><TD><div align=center>{director_list}</div></TD></TR>
    <TR><TD>{composer_name}</TD><TD>{composer}</TD><TD>{composer_f}</TD><TD><div align=center>{composer_list}</div></TD></TR>
    <TR><TD COLSPAN="4"><HR></TD></TR>
{actorlist}
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
