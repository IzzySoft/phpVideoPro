<H2 Align=Center>{listtitle}</H2>
<!-- BEGIN resultblock -->
<TABLE ALIGN="center" BORDER="0" CELLSPACING="0" CELLPADDING="2" WIDTH="100%">
 <!-- BEGIN resitemblock -->
 <TR><TD><DIV ALIGN="center">{moviename}</DIV></TD>
     <TD><DIV ALIGN="justify">{links}</DIV></TD></TR>
 <!-- END resitemblock -->
</TABLE>
<!-- END resultblock -->

<!-- BEGIN movieblock -->
{js}
<FORM NAME="movieform" METHOD="post" ACTION="{formtarget}">
<INPUT TYPE="hidden" NAME="title" VALUE="{mtitle}">
<INPUT TYPE="hidden" NAME="country" VALUE="{mcountry}">
<INPUT TYPE="hidden" NAME="year" VALUE="{myear}">
<TABLE ALIGN="center" BORDER="0" CELLSPACING="0" CELLPADDING="2" WIDTH="100%">
 <TR><TH COLSPAN="2"><DIV ALIGN="center">{mtitle}</DIV></TH></TR>
 <TR><TD><B>{ncountry}</B></TD><TD>{mcountry}</TD></TR>
 <TR><TD><B>{nyear}:</B></TD><TD>{myear}</TD></TR>
 <TR><TD><B>{npg}:</B></TD>
   <TD><SELECT NAME="pg">
 <!-- BEGIN pgblock -->
    <OPTION VALUE="{pgval}">{mpg}</OPTION>
 <!-- END pgblock -->
   </SELECT></TD></TR>
 <TR><TD><B>{nruntime}:</B></TD><TD><INPUT NAME="runtime" CLASS="yesnoinput" VALUE="{mruntime}"> min</TD></TR>
 <TR><TD><B>{ngenre}:</B></TD><TD>{mgenre}<BR>
 <!-- BEGIN acatblock -->
   <SELECT NAME="cat{catnr}_id">
  <!-- BEGIN catblock -->
    <OPTION VALUE="{cid}"{csel}>{cname}</OPTION>
  <!-- END catblock -->
   </SELECT>
 <!-- END acatblock -->
  </TD></TR>
 <TR><TD><B>{ndir_name}:</B></TD>
   <TD><SELECT NAME="directors">
 <!-- BEGIN dirblock -->
    <OPTION VALUE="{dir_name}"{dsel}>{dir_name}</OPTION>
 <!-- END dirblock -->
   </SELECT></TD></TR>
 <TR><TD><B>{actors}:</B></TD>
   <TD><SELECT NAME="actors" SIZE="7" MULTIPLE CLASS="multiselect">
 <!-- BEGIN actblock -->
    <OPTION VALUE="{aname}"{asel}>{aname}</OPTION>
 <!-- END actblock -->
  </SELECT>
 </TD></TR>
 <TR><TD>{mfoto_pic}</TD><TD><TEXTAREA ROWS="10" COLS="95" NAME="comment">{mcomment}</TEXTAREA></TD></TR>
 <TR><TD COLSPAN="2"><DIV ALIGN="center"><INPUT TYPE="button" NAME="transfer" VALUE="{btransfer}" onClick="transfer_data();"></DIV></TD></TR>
</TABLE>
</FORM>
<!-- END movieblock -->

<!-- BEGIN queryblock -->
<FORM NAME="queryform">
<TABLE ALIGN="center" BORDER="0" CELLSPACING="0" CELLPADDING="2" WIDTH="100%">
 <TR><TD><INPUT NAME="name" CLASS="titleinput"></TD></TR>
 <TR><TD><DIV ALIGN="center"><INPUT TYPE="submit" NAME="submit" VALUE="{submit}"></DIV></TD></TR>
</TABLE>
</FORM>
<!-- END queryblock -->
