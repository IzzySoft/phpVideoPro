<? /* page header */

/* $Id$ */

  $inc_path = dirname(__FILE__);
  include($inc_path . "/config.inc");
  include($inc_path . "/config_internal.inc");
  include($inc_path . "/common_funcs.inc");
  include($inc_path . "/sql_helpers.inc");
  $pagename = "phpVideoPro v$version";
  switch ( strtolower($page_id) ) {
    case "about"     : $pagename .= " [ " . lang("about") . " ]"; break;
    case "configure" : $pagename .= " [ " . lang("configuration") . " ]"; break;
    case "delete"    : $pagename .= " [ " . lang("deleting_entry",$nr) . " ]"; break;
    case "edit"      : $pagename .= " [ " . lang("edit_entry",$nr) . " ]"; break;
    case "filter"    : $pagename .= " [ " . lang("filter_setup") . " ]"; break;
    case "view"      : $pagename .= " [ " . lang("view_entry",$nr) . " ]"; break;
    case "history"   : $pagename .= " [ " . lang("history") . " ]"; break;
    case "medialist" : $pagename .= " [ " . lang("medialist") . " ]"; break;
    case "new_entry" : $pagename .= " [ " . lang("add_entry") . " ]"; break;
    case "taperest"  : $pagename .= " [ " . lang("free_space_title") . " ]"; break;
    default          : break;
  }
?>
<HTML><HEAD>
<Title><?echo $pagename ?></Title>
 <!--LINK REL=stylesheet type="text/css" HREF="<? echo $base_url ?>templates/default/default.css"-->
<? include($base_path . "templates/default/default.css") ?>
 <script language="JavaScript" src="<? echo $nav_script ?>"></script>
 <script language="JavaScript">

  function open_help() {
   var pos = (screen.width/2)-400;
   campus=eval("window.open('<? echo $base_url ?>help/index.php','<? echo lang("help") ?>','toolbar=no,location=no,titlebar=no,directories=no,status=yes,resizable=no,scrollbars=yes,copyhistory=no,width=800,height=600,top=0,left=" + pos + "')");
  }

  var myNavBar1 = new NavBar(0);
  var dhtmlMenu;

  //define menu items (first parameter of NavBarMenu specifies main category width, second specifies sub category width in pixels)
  //add more menus simply by adding more "blocks" of same code below

//  dhtmlMenu = new NavBarMenu(60, 120);
//  dhtmlMenu.addItem(new NavBarMenuItem("Home", "http://www.qumran.org/local/"));
//  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(80, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("edit") ?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("add_entry") ?>", "<? echo $base_url ?>new.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("Change Tape Nr", "<? echo $base_url ?>change_nr.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("configuration") ?>", "<? echo $base_url ?>configure.php"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(80, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("filter") ?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("set_filter") ?>", "<? echo $base_url ?>setfilter.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("unset_filter") ?>", "<? echo $base_url ?>setfilter.php?reset=1"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(140, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("view") ?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("medialist") ?>", "<? echo $base_url ?>medialist.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("taperest_absolute") ?>", "<? echo $base_url ?>taperest.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("taperest_filtered") ?>", "<? echo $base_url ?>taperest.php?usefilter=1"));
  dhtmlMenu.addItem(new NavBarMenuItem("Duplicate", "<? echo $base_url ?>dupes.php"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(62, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(62, 80);
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("help") ?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("general") ?>", "JavaScript:open_help()"));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("about") ?>", "<? echo $base_url ?>about.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("history") ?>", "<? echo $base_url ?>history.php"));
  myNavBar1.addMenu(dhtmlMenu);

  //set menu colors
  myNavBar1.setColors("#343434", "#eeeeee", "#60707C", "#ffffff", "#888888", "#eeeeee", "#60707C", "#ffffff", "#777777")
  myNavBar1.setFonts("Verdana", "Normal", "Normal", "10pt", "Verdana", "Normal", "Normal", "10pt");

  //uncomment below line to center the menu (valid values are "left", "center", and "right"
  //myNavBar1.setAlign("center")

  var fullWidth;

  function init() {

    // Get width of window, need to account for scrollbar width in Netscape.

    fullWidth = getWindowWidth() 
      - (isMinNS4 && getWindowHeight() < getPageHeight() ? 16 : 0);

//    myNavBar1.moveTo(10,36);
    myNavBar1.moveTo(10,0);
//    myNavBar1.resize(500 /*fullWidth*/);
    myNavBar1.resize(fullWidth);
    myNavBar1.setSizes(0,1,1);
    myNavBar1.create();
    myNavBar1.setzIndex(2);
  }

  </script>
</HEAD>
<BODY leftmargin="0" topmargin="0" marginwidth="0" marginheight="0" onLoad="init();" {body_tags}>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
 <tr>
  <td><img src="<? echo $base_url ?>images/menu_bar_left.gif" width="9" height="12"></td>
 </tr>
</table>

