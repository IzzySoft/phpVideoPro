  <SCRIPT TYPE="text/javascript"> //<!--
    function blockToggle(what) {
      ico = what+'ico';
      if (document.getElementById(what).style.visibility == "hidden") {
        document.getElementById(what).style.visibility = "visible";
        document.getElementById(what).style.display = "";
        document.getElementById(ico).src = "{base_dir}images/minus.gif";
      } else {
        document.getElementById(what).style.visibility = "hidden";
        document.getElementById(what).style.display = "none";
        document.getElementById(ico).src = "{base_dir}images/plus.gif";
      }
    }
    // -->
  </SCRIPT>
<BR>
<TABLE WIDTH="95%" ALIGN="center" CELLPADDING="0" CELLSPACING="0" BORDER="0" id="appWin"><TR><TD>
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
<FORM NAME="config_form" METHOD="post" ACTION="{formtarget}">
<TABLE WIDTH="100%" CELLPADDING="0" CELLSPACING="0" BORDER="0">
<TR><TD>

<TABLE ALIGN="center" WIDTH="99%" CLASS="data" STYLE="margin:5px;">
<!-- BEGIN listblock -->
 <TR onClick="blockToggle('{block_id}')"><TH><IMG SRC="{base_dir}/images/plus.gif" ID="{block_id}ico" STYLE="margin-right:1em;" ALT=''>{list_head}<DIV ALIGN="right" STYLE="float:right;">{help_icon}</DIV></TH></TR>
 <TR CLASS="content" ID="{block_id}" STYLE="visibility:hidden;display:none;"><TD>
  <TABLE WIDTH="100%">
  <!-- BEGIN itemblock -->
   <TR><TD WIDTH="70%"><b>{item_name}</b><br>{item_comment}</TD>
    <TD WIDTH="30%">{item_input}</TD></TR>
  <!-- END itemblock -->
  </TABLE></TD></TR>
  {sess_id}
<!-- END listblock -->
</TABLE>

</TD></TR>
<TR><TD BGCOLOR="#AAAAAA"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>
<TR><TD BGCOLOR="#FFFFFF"><IMG SRC="{tpl_dir}images/0.gif" WIDTH="1" HEIGHT="1" BORDER="0" ALT=""></TD></TR>

 <TR><TD><DIV STYLE="margin:3;text-align:center">{update}</DIV></TD></TR>
{config_end}

</TABLE>
</FORM></TD></TR>
</TABLE>
</DIV>
</TD></TR></TABLE>