<H2 Align=Center>{listtitle}</H2>
<FORM NAME="filter" METHOD="post" ACTION="{form_target}">
 <TABLE Width="90%" Align="Center" Border="1">
  <TR><TD WIDTH="50%"><!-- ====================================== Left side ============ !>
    <TABLE WIDTH="100%" BORDER="1">
     <TR><TD WIDTH="15%">{mtype_name}</TD><TD>{mtype}</TD></TR>
     <TR><TD WIDTH="15%">{length_name}</TD><TD>{length}</TD></TR>
     <TR><TD WIDTH="15%">{date_name}</TD><TD>{date}</TD></TR>
     <TR><TD WIDTH="15%">{screen_name}</TD><TD>{screen}</TD></TR>
     <TR><TD WIDTH="15%">{picture_name}</TD><TD>{picture}</TD></TR>
     <TR><TD WIDTH="15%">{tone_name}</TD><TD>{tone}</TD></TR>
     <TR><TD WIDTH="15%">{longplay_name}</TD><TD>{longplay}</TD></TR>
     <TR><TD WIDTH="15%">{fsk_name}</TD><TD>{fsk}</TD></TR>
    </TABLE></TD>
   <TD WIDTH="50%"><!-- ===================================== Right side ============ !>
    <TABLE WIDTH="100%" BORDER="1">
     <TR><TD WIDTH="10%">{title_name}</TD><TD COLSPAN="3">{title}</TD></TR>
     <TR><TD WIDTH="10%">{category_name}</TD><TD WIDTH="40%">{category}</TD>
         <TD WIDTH="10%">{actor_name}</TD><TD WIDTH="40%">{actor}</TD></TR>
     <TR><TD WIDTH="10%">{director_name}</TD><TD WIDTH="40%">{director}</TD>
         <TD WIDTH="10%">{composer_name}</TD><TD WIDTH="40%">{composer}</TD></TR>
    </TABLE></TD>
  </TR>
 </TABLE>
 <TABLE Width="90%" Align="Center" Border="0" class="navtable">
  <TR>
   <TD><P ALIGN="left"><INPUT TYPE="submit" NAME="reset" VALUE="Reset"></P></TD>
   <TD><P ALIGN="right"><INPUT TYPE="submit" NAME="save" VALUE="Save"></P></TD>
  </TR>
 </TABLE>
</FORM>
