<script language="JavaScript" src="<? echo $base_url ?>inc/navcond.js"></script>
<script language="JavaScript">
  var myNavBar1 = new NavBar(0);
  var dhtmlMenu;

  //define menu items (first parameter of NavBarMenu specifies main category width, second specifies sub category width in pixels)
  //add more menus simply by adding more "blocks" of same code below

<? if ($pvp->auth->admin) { ?>
  dhtmlMenu = new NavBarMenu(80, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("admin")?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("admin_cats")?>", "<?=$pvp->link->slink($base_url.'admin/cats.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("admin_translations")?>", "<?=$pvp->link->slink($base_url.'admin/translations.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("admin_printers")?>", "<?=$pvp->link->slink($base_url.'admin/printers.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("admin_filter")?>", "<?=$pvp->link->slink($base_url.'admin/filters.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("admin_orphans")?>", "<?=$pvp->link->slink($base_url.'admin/orphans.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("backup_db")?>", "<?=$pvp->link->slink($base_url.'admin/backup_db.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("configuration")?>", "<?=$pvp->link->slink($base_url.'admin/configure.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("dl_pvp_latest")?>", "http://www.qumran.org/homes/izzy/software/get_update.php?program=pvp&version=<?=$version?>&info_url=http://<?=$SERVER_NAME?><?=$base_url?>info.php?action=update"));
  myNavBar1.addMenu(dhtmlMenu);

<? } ?>

  dhtmlMenu = new NavBarMenu(80, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("edit")?>", ""));
  <? if ($pvp->auth->add) { ?>
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("add_entry")?>", "<?=$pvp->link->slink($base_url.'new.php')?>"));
  <? } ?>
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("search_movie")?>", "<?=$pvp->link->slink($base_url.'search.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("preferences")?>", "<?=$pvp->link->slink($base_url.'configure.php')?>"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(80, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("filter")?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("set_filter")?>", "<?=$pvp->link->slink($base_url.'setfilter.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("unset_filter")?>", "<?=$pvp->link->slink($base_url.'setfilter.php?reset=1')?>"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(140, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("view")?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("start_page")?>", "<?=$pvp->link->slink($base_url.'index.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("medialist")?>", "<?=$pvp->link->slink($base_url?>medialist.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("actors")?>", "<?=$pvp->link->slink($base_url.'stafflist.php?stafftype=actors')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("directors")?>", "<?=$pvp->link->slink($base_url.'stafflist.php?stafftype=directors')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("composer")?>", "<?=$pvp->link->slink($base_url.'stafflist.php?stafftype=music')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("taperest_absolute")?>", "<?=$pvp->link->slink($base_url.'taperest.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("taperest_filtered")?>", "<?=$pvp->link->slink($base_url.'taperest.php?usefilter=1')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("dupes")?>", "<?=$pvp->link->slink($base_url.'dupes.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("db_stats")?>", "<?=$pvp->link->slink($base_url.'stats.php')?>"));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(62, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("", ""));
  myNavBar1.addMenu(dhtmlMenu);

  dhtmlMenu = new NavBarMenu(80, 140);
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("print")?>", ""));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("labels")?>", "<?=$pvp->link->slink($base_url.'label.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("labels")?> (PS)", "<?=$pvp->link->slink($base_url.'pslabel.php')?>"));
  dhtmlMenu.addItem(new NavBarMenuItem("<?=lang("lists")?>", "<?=$pvp->link->slink($base_url.'listgen.php')?>"));
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
