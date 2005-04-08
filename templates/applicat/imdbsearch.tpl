<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" Style="table-layout:fixed" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0" ALIGN="center"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle"><DIV STYLE="margin:2">{listtitle}</DIV></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" NAME="button_home" CLASS="imgbut" SRC="{tpl_dir}images/win_home.gif" STYLE="width:14;height:13;" onClick="window.location.href='index.php'" TITLE="{btn_index}"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" NAME="button_back" CLASS="imgbut" SRC="{tpl_dir}images/win_back.gif" STYLE="width:14;height:13;" onClick="history.back()" TITLE="{btn_back}"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{help_title}" NAME="button_help" CLASS="imgbut" SRC="{tpl_dir}images/win_help.gif" STYLE="width:14;height:13;" onClick="{help_link}"></TD>
     <TD CLASS="wintitle" STYLE="vertical-align:middle;margin-right:3;"><DIV STYLE="width:18;">
      <INPUT TYPE="image" NAME="button_close" CLASS="imgbut" SRC="{tpl_dir}images/win_close.gif" STYLE="width:14;height:13;" onClick="window.close()" TITLE="{btn_close}"></DIV></TD></TR>
</TABLE></TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD>

<DIV STYLE="margin:5;text-align:center">
<TABLE ALIGN="center" BORDER="0" CELLSPACING="0" CELLPADDING="2">
<TR CLASS="content"><TD>

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
<INPUT TYPE="hidden" NAME="country" VALUE="{mcountry}">
<INPUT TYPE="hidden" NAME="year" VALUE="{myear}">
<TABLE ALIGN="center" BORDER="0" CELLSPACING="0" CELLPADDING="2" WIDTH="100%">
 <TR><TH>{title_chk}</TH><TH COLSPAN="2"><DIV ALIGN="center">{mtitle}</DIV></TH></TR>
 <TR><TD>{country_chk}</TD><TD><B>{ncountry}</B></TD><TD>{mcountry}</TD></TR>
 <TR><TD>{year_chk}</TD><TD><B>{nyear}:</B></TD><TD>{myear}</TD></TR>
 <TR><TD>{pg_chk}</TD><TD><B>{npg}:</B></TD>
   <TD><SELECT NAME="pg">
 <!-- BEGIN pgblock -->
    <OPTION VALUE="{pgval}">{mpg}</OPTION>
 <!-- END pgblock -->
   </SELECT></TD></TR>
 <TR><TD>{length_chk}</TD><TD><B>{nruntime}:</B></TD><TD><INPUT NAME="runtime" CLASS="yesnoinput" VALUE="{mruntime}"> min</TD></TR>
 <TR><TD>{cat_chk}</TD><TD><B>{ngenre}:</B></TD><TD>{mgenre}<BR>
 <!-- BEGIN acatblock -->
   <SELECT NAME="cat{catnr}_id">
  <!-- BEGIN catblock -->
    <OPTION VALUE="{cid}"{csel}>{cname}</OPTION>
  <!-- END catblock -->
   </SELECT>
 <!-- END acatblock -->
  </TD></TR>
 <TR><TD>{director_chk}</TD><TD><B>{ndir_name}:</B></TD>
   <TD><SELECT NAME="directors">
 <!-- BEGIN dirblock -->
    <OPTION VALUE="{dir_name}"{dsel}>{dir_name}</OPTION>
 <!-- END dirblock -->
   </SELECT></TD></TR>
 <TR><TD>{music_chk}</TD><TD><B>{nmus_name}:</B></TD>
   <TD><SELECT NAME="music">
 <!-- BEGIN musblock -->
    <OPTION VALUE="{mus_name}"{dsel}>{mus_name}</OPTION>
 <!-- END musblock -->
   </SELECT></TD></TR>
 <TR><TD>{actor_chk}</TD><TD><B>{actors}:</B></TD>
   <TD><SELECT NAME="actors" SIZE="7" MULTIPLE CLASS="multiselect">
 <!-- BEGIN actblock -->
    <OPTION VALUE="{aname}"{asel}>{aname}</OPTION>
 <!-- END actblock -->
  </SELECT>
 </TD></TR>
 <TR><TD>{comments_chk}</TD><TD>{mfoto_pic}</TD><TD><TEXTAREA ROWS="10" COLS="88" NAME="comment">{mcomment}</TEXTAREA></TD></TR>
 <TR><TD COLSPAN="3"><DIV ALIGN="center"><INPUT TYPE="button" NAME="transfer" VALUE="{btransfer}" onClick="transfer_data();"></DIV></TD></TR>
</TABLE>
</FORM>
<!-- END movieblock -->

<!-- BEGIN queryblock -->
<FORM NAME="queryform" METHOD="post" ACTION="{formtarget}">
<TABLE ALIGN="center" BORDER="0" CELLSPACING="0" CELLPADDING="2" WIDTH="100%">
 <TR><TD>{mname}</TD><TD><INPUT NAME="name" CLASS="titleinput"></TD>
     <TD><DIV ALIGN="center"><INPUT TYPE="submit" NAME="nsubmit" VALUE="{submit}"></DIV></TD></TR>
 <TR><TD>{mid}</TD><TD><INPUT NAME="mid" CLASS="titleinput"></TD>
     <TD><DIV ALIGN="center"><INPUT TYPE="submit" NAME="isubmit" VALUE="{submit}"></DIV></TD></TR>
 <TR><TD COLSPAN="3"><DIV ALIGN="center"><INPUT TYPE="reset" NAME="reset" VALUE="{reset}"></DIV></TD></TR>
</TABLE>
</FORM>
<!-- END queryblock -->

</TD></TR></TABLE>
</DIV>

</TD></TR>
</TABLE>
</DIV>
</TD></TR></TABLE>