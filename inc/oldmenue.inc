<script language="JavaScript" src="<? echo $base_url ?>inc/navcond.js"></script>
<script language="JavaScript">
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
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("start_page") ?>", "<? echo $base_url ?>index.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("medialist") ?>", "<? echo $base_url ?>medialist.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("actors") ?>", "<? echo $base_url ?>stafflist.php?stafftype=actors"));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("directors") ?>", "<? echo $base_url ?>stafflist.php?stafftype=directors"));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("composer") ?>", "<? echo $base_url ?>stafflist.php?stafftype=music"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("taperest_absolute") ?>", "<? echo $base_url ?>taperest.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("taperest_filtered") ?>", "<? echo $base_url ?>taperest.php?usefilter=1"));
  dhtmlMenu.addItem(new NavBarMenuItem("Duplicate", "<? echo $base_url ?>dupes.php"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(62, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(80, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("print") ?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("label") ?>", "<? echo $base_url ?>label.php"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(62, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("help") ?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("index") ?>", "JavaScript:open_help('')"));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("about") ?>", "JavaScript:open_help('about')"));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("history") ?>", "JavaScript:open_help('history')"));<?
if ($page_id) { ?>
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<? echo lang("help_about") . " '" . lang($page_id) . "'"  ?>", "JavaScript:open_help('<? echo $page_id ?>')"));<?
} ?>
  myNavBar1.addMenu(dhtmlMenu);

  //set menu colors
//myNavBar1.setColors("separator", "unselMenuTxt", "unselMenuBg", "selMenuTxt", "selMenuBg", "unselMenuItemTxt", "unselMenuItemBg", "selMenuItemTxt", "#selMenuItemBg")
  myNavBar1.setColors("#343434",   "#eeeeee",      "#60707C",     "#ffffff",    "#888888",   "#eeeeee",          "#60707C",         "#ffffff",        "#777777")
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
