<script language="JavaScript" src="<? echo $base_url ?>inc/navcond.js"></script>
<script language="JavaScript">
  var myNavBar1 = new NavBar(0);
  var dhtmlMenu;

  //define menu items (first parameter of NavBarMenu specifies main category width, second specifies sub category width in pixels)
  //add more menus simply by adding more "blocks" of same code below

  dhtmlMenu = new NavBarMenu(80, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("admin")?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("admin_cats")?>", "<?=$base_url?>admin/cats.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("admin_orphans")?>", "<?=$base_url?>admin/orphans.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("backup_db")?>", "<?=$base_url?>admin/backup_db.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("configuration")?>", "<?=$base_url?>admin/configure.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("dl_pvp_latest")?>", "http://www.qumran.org/homes/izzy/software/get_update.php?program=pvp&version=<?=$version?>&info_url=http://<?=$SERVER_NAME?><?=$base_url?>info.php?action=update"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(80, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("edit")?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("add_entry")?>", "<?=$base_url?>new.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("preferences")?>", "<?=$base_url?>configure.php"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(80, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("filter")?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("set_filter")?>", "<?=$base_url?>setfilter.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("unset_filter")?>", "<?=$base_url?>setfilter.php?reset=1"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(140, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("view")?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("start_page")?>", "<?=$base_url?>index.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("medialist")?>", "<?=$base_url?>medialist.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("actors")?>", "<?=$base_url?>stafflist.php?stafftype=actors"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("directors")?>", "<?=$base_url?>stafflist.php?stafftype=directors"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("composer")?>", "<?=$base_url?>stafflist.php?stafftype=music"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("taperest_absolute")?>", "<?=$base_url?>taperest.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("taperest_filtered")?>", "<?=$base_url?>taperest.php?usefilter=1"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("dupes")?>", "<?=$base_url?>dupes.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("db_stats")?>", "<?=$base_url?>stats.php"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(62, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(80, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("print")?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("labels")?>", "<?=$base_url?>label.php"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("lists")?>", "<?=$base_url?>listgen.php"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(62, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("help")?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("index")?>", "JavaScript:open_help('')"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("about")?>", "JavaScript:open_help('about')"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("history")?>", "JavaScript:open_help('history')"));<?
if ($page_id) { ?>
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("help_about") . " '" . lang($page_id) . "'"  ?>", "JavaScript:open_help('<? echo $page_id ?>')"));<?
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
