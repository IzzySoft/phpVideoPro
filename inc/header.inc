<? /* page header */

/* $Id$ */

  include("inc/config.inc");
  include("inc/common_funcs.inc");
  include("inc/sql_helpers.inc");
  include("inc/db_mysql.inc");
  $db = new DB_Sql;
  $db->Host     = $database["host"];
  $db->Database = $database["database"];
  $db->User     = $database["user"];
  $db->Password = $database["password"];
  if ( !strpos(strtoupper($debug["log"]),"D")===false ) $db->Debug = 1;
  $pagename = "phpVideoPro v$version";
  switch ( strtolower($page_id) ) {
    case "about"     : $pagename .= " [ About ]"; break;
    case "edit"      : $pagename .= " [ Editing entry $nr ]"; break;
    case "filter"    : $pagename .= " [ Filter Setup ]"; break;
    case "view"      : $pagename .= " [ Viewing entry $nr ]"; break;
    case "history"   : $pagename .= " [ History ]"; break;
    case "medialist" : $pagename .= " [ MediaList ]"; break;
    case "new_entry" : $pagename .= " [ Add entry ]"; break;
    case "taperest"  : $pagename .= " [ Free space on media ]"; break;
    default          : break;
  }
?>
<HTML><HEAD>
<Title><?echo $pagename ?></Title>
 <STYLE type="text/css">
   a { text-decoration:none; }
   <!--
     A:link{ text-decoration:none }
     A:visted{ text-decoration:none }
     A:active{ text-decoration:none }
     body { margin-top: 0px; margin-right: 0px; margin-left: 0px; background-color: <? echo $colors["page_background"] ?> }
     .tablink { color: #000000; }
     TH { background-color:<? echo $colors["th_background"] ?>; }
   -->
 </STYLE>
 <script language="JavaScript" src="<? echo $nav_script ?>"></script>
 <script language="JavaScript">

  var myNavBar1 = new NavBar(0);
  var dhtmlMenu;

  //define menu items (first parameter of NavBarMenu specifies main category width, second specifies sub category width in pixels)
  //add more menus simply by adding more "blocks" of same code below

//  dhtmlMenu = new NavBarMenu(60, 120);
//  dhtmlMenu.addItem(new NavBarMenuItem("Home", "http://www.qumran.org/local/"));
//  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(60, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("Edit", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("Add new Entry", "<? echo $base_url ?>new.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("Change Tape Nr", "<? echo $base_url ?>change_nr.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("Delete Entry", "<? echo $base_url ?>delete.php"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(60, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("Filter", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("Set Filter", "<? echo $base_url ?>setfilter.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("UnSet Filter", "<? echo $base_url ?>setfilter.php?reset=1"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(140, 120);
  dhtmlMenu.addItem(new NavBarMenuItem("View", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("Medialist", "<? echo $base_url ?>medialist.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("Taperest", "<? echo $base_url ?>taperest.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("Duplicate", "<? echo $base_url ?>dupes.php"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(62, 120);
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(62, 120);
  dhtmlMenu.addItem(new NavBarMenuItem("Help", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("General", "<? echo $base_url ?>help.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("About", "<? echo $base_url ?>about.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("History", "<? echo $base_url ?>history.php"));
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

