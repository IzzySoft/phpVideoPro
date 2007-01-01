<H2 ALIGN="center">{listtitle}</H2>

<DIV ALIGN="center">

<TABLE ALIGN="center" STYLE="margin:3">
 <TR><TH>{ititle}</TH></TR>
 <TR CLASS="content"><TD STYLE="text-align:justify">{idetails}</TD></TR>
</TABLE>

<TABLE ALIGN="center" STYLE="margin:3">
 <TR><TH>{mtitle}</TH></TR>
 <!-- BEGIN movieblock -->
 <!-- BEGIN nomovieitem -->
 <TR CLASS="content"><TD CLASS="content">{details}</TD></TR>
 <!-- END nomovieitem -->
 <!-- BEGIN havemovieitem -->
 <TR CLASS="content"><TD>
   <FORM ACTION="{formtarget}"' METHOD="post" NAME="orphaned_movies">
   <DIV ALIGN="center"><TABLE ALIGN="center" BORDER="0">
     <TR><TH>{owner_name}</TH><TH>{movie_name}</TH>
     <!-- BEGIN movieitem -->
     <TR><TD>{owner}</TD><TD>{imovie}</TD></TR>
     <!-- END movieitem -->
     <TR><TD COLSPAN="2"><DIV ALIGN="center">{mbutton}</DIV></TD></TR>
   </TABLE></DIV>
   </FORM>
 </TD></TR>
 <!-- END havemovieitem -->
 <!-- END movieblock -->
</TABLE>

<TABLE ALIGN="center" STYLE="margin:3">
 <!-- BEGIN itemblock -->
 <TR><TH>{title}</TH></TR>
 <TR CLASS="content"><TD STYLE="text-align:justify">{details}</TD></TR>
 <!-- END itemblock -->
</TABLE>

</DIV>
<BR>
<FORM NAME='admin_orphans' METHOD='post' ACTION='{formtarget}'>{hidden}
 <DIV ALIGN='center'>{button}</DIV>
</FORM>