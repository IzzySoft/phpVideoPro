<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE WIDTH="95%" CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0" ALIGN="center"><TR><TD>
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
 <TR><TD NOWRAP WIDTH="100%" CLASS="wintitle"><DIV STYLE="margin:2">{listtitle}</DIV></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{home_title}" NAME="button_home" CLASS="imgbut" SRC="{tpl_dir}images/win_home.gif" STYLE="width:14;height:13;" onClick="window.location.href='{home_link}'"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{search_title}" NAME="button_search" CLASS="imgbut" SRC="{tpl_dir}images/win_search.gif" STYLE="width:14;height:13;" onClick="window.location.href='{search_link}'"></TD>
     <TD ALIGN="right" CLASS="wintitle" STYLE="vertical-align:middle;">
      <INPUT TYPE="image" TITLE="{help_title}" NAME="button_help" CLASS="imgbut" SRC="{tpl_dir}images/win_help.gif" STYLE="width:14;height:13;" onClick="{help_link}"></TD>
     <TD CLASS="wintitle" STYLE="vertical-align:middle;margin-right:3;"><DIV STYLE="width:18;">
      <INPUT TYPE="image" TITLE="{logoff_title}" NAME="button_close" CLASS="imgbut" SRC="{tpl_dir}images/win_close.gif" STYLE="width:14;height:13;" onClick="window.location.href='{logoff_link}'"></DIV></TD></TR>
</TABLE></TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD>
{js}
<FORM NAME="filter" METHOD="post" ACTION="{form_target}">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
<TR><TD>

<DIV STYLE="margin:3">
 <TABLE Align="Center" Border="0">
  <TR><TD WIDTH="50%"><!-- ====================================== Left side ============ -->
    <TABLE WIDTH="100%" BORDER="0" CLASS="data">
     <TR CLASS="content"><TH WIDTH="15%">{mtype_name}</TH><TD>{mtype}</TD></TR>
     <TR CLASS="content"><TH WIDTH="15%">{length_name}</TH><TD>{length}</TD></TR>
     <TR CLASS="content"><TH WIDTH="15%">{date_name}</TH><TD>{date}</TD></TR>
     <TR CLASS="content"><TH WIDTH="15%">{screen_name}</TH><TD>{screen}</TD></TR>
     <TR CLASS="content"><TH WIDTH="15%">{picture_name}</TH><TD>{picture}</TD></TR>
     <TR CLASS="content"><TH WIDTH="15%">{tone_name}</TH><TD>{tone}</TD></TR>
     <TR CLASS="content"><TH WIDTH="15%">{longplay_name}</TH><TD>{longplay}</TD></TR>
     <TR CLASS="content"><TH WIDTH="15%">{fsk_name}</TH><TD>{fsk}</TD></TR>
    </TABLE></TD>
   <TD WIDTH="50%"><!-- ===================================== Right side ============ -->
    <TABLE WIDTH="100%" BORDER="0" CLASS="data">
     <TR CLASS="content"><TH WIDTH="10%">{title_name}</TH><TD COLSPAN="3">{title}</TD></TR>
     <TR CLASS="content"><TH WIDTH="10%">{category_name}</TH><TD WIDTH="40%">{category}</TD>
         <TH WIDTH="10%">{actor_name}</TH><TD WIDTH="40%">{actor}</TD></TR>
     <TR CLASS="content"><TH WIDTH="10%">{director_name}</TH><TD WIDTH="40%">{director}</TD>
         <TH WIDTH="10%">{composer_name}</TH><TD WIDTH="40%">{composer}</TD></TR>
    </TABLE></TD>
  </TR>
  <TR><TD COLSPAN="2"><!-- ============================= Lower side ================ -->
    <TABLE BORDER="0" ALIGN="center" CLASS="data">
      <TR CLASS="content"><TH>{grant_desc}</TH>
        <TD><SELECT NAME="{grant_sel_name}[]" MULTIPLE CLASS="multiselect">
<!-- BEGIN grantblock -->
              <OPTION VALUE="{gval}"{gselected}>{gname}</OPTION>
<!-- END grantblock -->
            </SELECT></TD></TR>
    </TABLE>
  </TD></TR>
 </TABLE>
</DIV>
</TD></TR>

<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD><DIV STYLE="margin:3">
 <TABLE WIDTH="90%" Align="Center" Border="0">
  <TR>{sess_id}
   <TD><P ALIGN="left"><INPUT CLASS="submit" TYPE="submit" NAME="reset" VALUE="{reset}"></P></TD>
   <TD><P ALIGN="right"><INPUT CLASS="submit" TYPE="submit" NAME="save" VALUE="{update}"></P></TD>
  </TR>
 </TABLE>
 </DIV>
</TD></TR>

</TABLE>
</FORM></TD></TR>
</TABLE>
</DIV>
</TD></TR></TABLE>