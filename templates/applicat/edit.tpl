<style type="text/css"><!--
 ul {margin-left: 5; padding-left: 10px; margin-top: 0; margin-bottom:0; padding-top:0; padding-bottom:0;}
 li {margin-top: 0; margin-bottom:0;}
--></style>
{js}
<BR>
<TABLE ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" Style="table-layout:fixed" id="appWin"><TR><TD>
<DIV STYLE="display:inline">
<TABLE CELLPADDING="0" CELLSPACING="0" CLASS="window" BORDER="0" ALIGN="center"><TR><TD>
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
<FORM NAME="{form_name}" METHOD="post" ACTION="{form_target}">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
<TR><TD>

<DIV STYLE="margin:3;text-align:center">{save_result}</DIV>
{hiddenfields}
<DIV STYLE="margin:3">

<Table Align="Center" Border="1">
 <COLGROUP>
  <COL WIDTH="50%">
  <COL WIDTH="50%">
 </COLGROUP>
 <TR><TH ColSpan="2">
   <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0">
     <TR><TH STYLE="width:22px;vertical-align:middle;">{previous}</TH><TH WIDTH="80%" STYLE="text-align:center"> {title} {imdb}</TH>
         <TH STYLE="width:22px;vertical-align:middle;text-align:right">{next}</TH></TR>
   </TABLE>
 <TR CLASS="content">
  <TD>
   <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0">
    <COLGROUP><COL WIDTH="150"><COL WIDTH="*"></COLGROUP>
    <TR><TD>{mtype_name}</TD><TD>{mtype}</TD></TR>
    <TR><TD>{medianr_name}</TD><TD>
      <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0"><TR>
        <TD WIDTH="50%"{konq_fix}>{medianr}</TD><TD WIDTH="50%">{minfo_link}</TD></TR>
      </TABLE></TD></TR>
    <TR><TD>{counter_name}</TD><TD>
      <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0"><TR>
        <TD WIDTH="50%"{konq_fix}>{counter}</TD><TD WIDTH="25%">{label_name}</TD><TD WIDTH="25%">{label}</TD></TR>
      </TABLE></TD></TR>
    <TR><TD>{rc_name}</TD><TD>{rc}</TD></TR>
    <TR><TD>{commercial_name}</TD><TD>
      <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0"><TR>
        <TD WIDTH="50%"{konq_fix}>{commercial}</TD><TD WIDTH="25%">{hide_name}</TD><TD WIDTH="25%">{hide}</TD></TR>
      </TABLE></TD></TR>
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
 <TR CLASS="content">
  <TD>
   <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0">
    <COLGROUP><COL WIDTH="150"><COL WIDTH="*"></COLGROUP>
    <TR><TD>{length_name}</TD>
        <TD><TABLE WIDTH="100%" BORDER="0" CELLPADDING="0" CELLSPACING="0"><TR>
          <TD WIDTH="50%">{length}</TD>
          <TD WIDTH="25%">{longplay_name}</TD>
          <TD WIDTH="25%">{longplay}</TD></TR>
        </TABLE></TD></TR>
    <TR{vis_mlength_free}><TD>{mlength_free_name}</TD><TD>{mlength_free}</TD></TR>
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
    <TR><TD>{rating_name}</TD><TD>{rating}</TD></TR>
    <TR><TD VALIGN="top">{audio_name}</TD><TD>{audio}</TD></TR>
    <TR><TD VALIGN="top">{subtitle_name}</TD><TD>{subtitle}</TD></TR>
   </TABLE>
  </TD>
  <TD>
   <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0">
    <COLGROUP><COL WIDTH="15%"><COL WIDTH="30%"><COL WIDTH="30%"><COL WIDTH="15%"></COLGROUP>
    <TR><TD><DIV ALIGN="center"><B>{staff_name}</B></DIV></TD>
        <TD><DIV ALIGN="center"><B>{name_name}</B></DIV></TD>
        <TD><DIV ALIGN="center"><B>{firstname_name}</B></DIV></TD>
	<TD><DIV ALIGN="center"><B>{inlist_name}</B></DIV></TD></TR>
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
 <TR CLASS="content"><TD COLSPAN="2" Align="center">
   <TABLE WIDTH="100%" BORDER="0" CellPadding="0" CellSpacing="0">
     <TR><TH><DIV STYLE="vertical-align:middle;text-align:center;font-weight:bold;margin:2;">{comments_name}</DIV></TH></TR>
   </TABLE>
 </TD></TR><TR CLASS="content"><TD COLSPAN="2" Align="center">
   <TABLE WIDTH="100%" BORDER="0" id="commentTab">
     <TR><TD>{comments}</TD></TR>
   </TABLE></TD></TR>
</Table>
</DIV>

</TD></TR>

<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD>
   <Table Width="100%" STYLE="margin:3">
    <TR><TD Width="33%">{button_li}</TD>
        <TD Width="34%"><DIV ALIGN="center">{print_label}</DIV></TD>
        <TD Width="33%"><div align="right">{button_re}</div></TD></TR>
   </TABLE>
</TD></TR>

</TABLE>
</FORM></TD></TR>
</TABLE></DIV>
</TD></TR></TABLE>
