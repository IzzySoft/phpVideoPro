 <link rel="stylesheet" type="text/css" href="<?=$base_url?>templates/applicat/menu/menu.css">
 <script type="text/javascript" src="<?=$base_url?>templates/applicat/menu/jsdomenu.js"></script>
 <script type="text/javascript" src="<?=$base_url?>templates/applicat/menu/jsdomenubar.js"></script>
 <script type="text/javascript">
function createjsDOMenu() {
//  menuBarActivateMode = "over"; // open menu on mouseOver (instead of click)
  menuBar = new jsDOMenuBar();
<?
 #============================================================[ Admin Menu ]===
 if ($pvp->auth->admin) {
?>
  adminMenu = new jsDOMenu();
  with (adminMenu) {
    //                      ShowName, IDName, URL
    addMenuItem(new menuItem("<?=lang("admin_cats")?>", "admin_cats", "<?=$pvp->link->slink($base_url."admin/cats.php")?>"));
    addMenuItem(new menuItem("<?=lang("admin_movietech")?>", "admin_movietech", "<?=$pvp->link->slink($base_url."admin/movietech.php")?>"));
    addMenuItem(new menuItem("<?=lang("admin_disktypes")?>", "admin_disktypes", "<?=$pvp->link->slink($base_url."admin/disktypes.php")?>"));
    addMenuItem(new menuItem("<?=lang("admin_translations")?>", "admin_translations", "<?=$pvp->link->slink($base_url."admin/translations.php")?>"));
    addMenuItem(new menuItem("<?=lang("admin_pstemplates")?>", "admin_pstemplates", "<?=$pvp->link->slink($base_url."admin/ps_templates.php")?>"));
    addMenuItem(new menuItem("<?=lang("admin_printers")?>", "admin_printers", "<?=$pvp->link->slink($base_url."admin/printers.php")?>"));
    addMenuItem(new menuItem("-"));
    addMenuItem(new menuItem("<?=lang("admin_users")?>", "admin_users", "<?=$pvp->link->slink($base_url."admin/users.php")?>"));
    addMenuItem(new menuItem("<?=lang("admin_sessions")?>", "admin_sessions", "<?=$pvp->link->slink($base_url."admin/sessions.php")?>"));
    addMenuItem(new menuItem("<?=lang("admin_filter")?>", "admin_filters", "<?=$pvp->link->slink($base_url."admin/filters.php")?>"));
    addMenuItem(new menuItem("-"));
    addMenuItem(new menuItem("<?=lang("admin_orphans")?>", "admin_orphans", "<?=$pvp->link->slink($base_url."admin/orphans.php")?>"));
    addMenuItem(new menuItem("<?=lang("admin_orphan_fs")?>", "admin_cleanFS", "<?=$pvp->link->slink($base_url."admin/clean_fs.php")?>"));
    addMenuItem(new menuItem("<?=lang("backup_db")?>", "admin_backupDB", "<?=$pvp->link->slink($base_url."admin/backup_db.php")?>"));
    addMenuItem(new menuItem("<?=lang("configuration")?>", "admin_config", "<?=$pvp->link->slink($base_url."admin/configure.php")?>"));
    addMenuItem(new menuItem("-"));
    addMenuItem(new menuItem("<?=lang("dl_pvp_latest")?>", "admin_dl", "http://projects.izzysoft.de/progs/get_update.php?program=pvp;version=<?=$version?>;info_url=http://<?=$_SERVER["SERVER_NAME"]?><?=$base_url?>info.php?action=update"));
  }
  menuBar.addMenuBarItem(new menuBarItem("<?=lang("admin")?>",adminMenu,"AdminMenu"));
  menuBar.items.AdminMenu.showIcon("admin");
  adminMenu.items.admin_cats.showIcon("cats");
  adminMenu.items.admin_movietech.showIcon("movie");
  adminMenu.items.admin_disktypes.showIcon("dvds");
  adminMenu.items.admin_translations.showIcon("translate");
  adminMenu.items.admin_pstemplates.showIcon("templates");
  adminMenu.items.admin_printers.showIcon("print");
  adminMenu.items.admin_users.showIcon("users");
  adminMenu.items.admin_sessions.showIcon("sessions");
  adminMenu.items.admin_filters.showIcon("filter");
  adminMenu.items.admin_orphans.showIcon("orphans");
  adminMenu.items.admin_cleanFS.showIcon("folderx");
  adminMenu.items.admin_backupDB.showIcon("backup");
  adminMenu.items.admin_config.showIcon("settings");
  adminMenu.items.admin_dl.showIcon("download");
<?
 }
 #=============================================================[ Edit Menu ]===
?>  
  editMenu = new jsDOMenu();
  with (editMenu) {
<? if ($pvp->auth->add) { ?>
    addMenuItem(new menuItem("<?=lang("new_movie_on")?>", "newMovie", ""));
<? }
   if (($pvp->auth->add && $pvp->config->user_backup_restore) || ($pvp->auth->browse && $pvp->config->user_backup_store)) { ?>
    addMenuItem(new menuItem("<?=lang("backup_menu")?>", "userBackup", ""));
<? } ?>
    addMenuItem(new menuItem("<?=lang("search_movie")?>", "edit_search", "<?=$pvp->link->slink($base_url."search.php")?>"));
    addMenuItem(new menuItem("<?=lang("preferences")?>", "edit_preferences", "<?=$pvp->link->slink($base_url."configure.php")?>"));
<? if ($pvp->auth->add) { ?>
    addMenuItem(new menuItem("<?=lang("user_grants")?>", "edit_usergrants", "<?=$pvp->link->slink($base_url."usergrants.php")?>"));
    editMenu.items.edit_usergrants.showIcon("lock");
<? } ?>
  }
  
<? if ($pvp->auth->add) {
 $lastnum = $db->get_lastmovienum();
?>
  newMovies = new jsDOMenu();
  with (newMovies) {
<?
  for ($i=0;$i<count($lastnum);++$i) {
    $smed = strtolower($lastnum[$i]['mtype']);
    echo "    addMenuItem(new menuItem(\"".$lastnum[$i]['mtype']."\",\"edit_new_$smed\"));\n";
  }
?>
  }
<?
  for ($i=0;$i<count($lastnum);++$i) {
    $smed = strtolower($lastnum[$i]['mtype']);
    echo "    newMovies.items.edit_new_$smed.showIcon(\"".$smed."_movie\");\n";
    echo "    newMovies.items.edit_new_$smed.actionOnClick = \"code:get_movienum('".lang("enter_new_medianr",$lastnum[$i]['mtype'])."',".(int)$lastnum[$i]['cass_id'].",'".$pvp->link->slink($base_url."new.php?mtype_id=".$lastnum[$i]['mtype_id'])."');\"\n";
  }
?>
  editMenu.items.newMovie.setSubMenu(newMovies);
<? } if (($pvp->auth->add && $pvp->config->user_backup_restore) || ($pvp->auth->browse && ($pvp->config->user_backup_store||$pvp->config->user_backup_download))) { ?>
  userBackups = new jsDOMenu();
<?   if ($pvp->auth->browse && $pvp->config->user_backup_store) { ?>
  userBackups.addMenuItem(new menuItem("<?=lang('user_backup_store')?>","store_backup","<?=$pvp->link->slink($base_url."backup.php?mode=save")?>"));
  userBackups.items.store_backup.showIcon("backup");
<? }  if ($pvp->auth->browse && $pvp->config->user_backup_download) { ?>
  userBackups.addMenuItem(new menuItem("<?=lang('user_backup_download')?>","download_backup","<?=$pvp->link->slink($base_url."backup.php?mode=download")?>"));
  userBackups.items.download_backup.showIcon("download");
<? }  if ($pvp->auth->add && $pvp->config->user_backup_restore) { ?>
  userBackups.addMenuItem(new menuItem("<?=lang('user_backup_restore')?>","restore_backup","<?=$pvp->link->slink($base_url."backup.php?mode=restore")?>"));
  userBackups.items.restore_backup.showIcon("restore");

<?   } ?>
  editMenu.items.userBackup.setSubMenu(userBackups);
  editMenu.items.userBackup.showIcon("backup");
<? } ?>
  editMenu.items.edit_search.showIcon("search");
  editMenu.items.edit_preferences.showIcon("settings");
  editMenu.items.newMovie.showIcon("new");
  menuBar.addMenuBarItem(new menuBarItem("<?=lang("edit")?>",editMenu,"EditMenu"));
  menuBar.items.EditMenu.showIcon("edit");
<?
 #===========================================================[ Filter Menu ]===
?>
  filterMenu = new jsDOMenu();
  with (filterMenu) {
    addMenuItem(new menuItem("<?=lang("set_filter")?>", "filter_set", "<?=$pvp->link->slink($base_url."setfilter.php")?>"));
    addMenuItem(new menuItem("<?=lang("unset_filter")?>", "filter_unset", "<?=$pvp->link->slink($base_url."setfilter.php?reset=1")?>"));
  }
  filterMenu.items.filter_set.showIcon("filter");
  filterMenu.items.filter_unset.showIcon("filter_new");
  menuBar.addMenuBarItem(new menuBarItem("<?=lang("filter")?>",filterMenu,"FilterMenu"));
  menuBar.items.FilterMenu.showIcon("filter");
<?
 #=============================================================[ View Menu ]===
?>
  viewMenu = new jsDOMenu();
  with (viewMenu) {
    addMenuItem(new menuItem("<?=lang("login_page")?>", "view_login", "<?=$pvp->link->slink($base_url."login.php?logout=1")?>"));
    addMenuItem(new menuItem("<?=lang("start_page")?>", "view_start", "<?=$pvp->link->slink($base_url."index.php")?>"));
    addMenuItem(new menuItem("-"));
    addMenuItem(new menuItem("<?=lang("medialist")?>", "view_medialist", "<?=$pvp->link->slink($base_url."medialist.php")?>"));
    addMenuItem(new menuItem("<?=lang("actors")?>", "view_actors", "<?=$pvp->link->slink($base_url."stafflist.php?stafftype=actors")?>"));
    addMenuItem(new menuItem("<?=lang("directors")?>", "view_directors", "<?=$pvp->link->slink($base_url."stafflist.php?stafftype=directors")?>"));
    addMenuItem(new menuItem("<?=lang("composer")?>", "view_music", "<?=$pvp->link->slink($base_url."stafflist.php?stafftype=music")?>"));
    addMenuItem(new menuItem("-"));
    addMenuItem(new menuItem("<?=lang("taperest_absolute")?>", "view_taperestAbsolut", "<?=$pvp->link->slink($base_url."taperest.php")?>"));
    addMenuItem(new menuItem("<?=lang("taperest_filtered")?>", "view_taperestFiltered", "<?=$pvp->link->slink($base_url."taperest.php?usefilter=1")?>"));
    addMenuItem(new menuItem("-"));
    addMenuItem(new menuItem("<?=lang("dupes")?>", "viewDupes", ""));
    addMenuItem(new menuItem("-"));
    addMenuItem(new menuItem("<?=lang("db_stats")?>", "view_stats", "<?=$pvp->link->slink($base_url."stats.php")?>"));
  }
  dupeMenu = new jsDOMenu();
  with (dupeMenu) {
    addMenuItem(new menuItem("<?=lang("all_topic")?>", "view_dupesAll", "<?=$pvp->link->slink($base_url."dupes.php")?>"));
    addMenuItem(new menuItem("<?=lang("dupes_strict")?>", "view_dupesStrict", "<?=$pvp->link->slink($base_url."dupes.php?strict=1")?>"));
    addMenuItem(new menuItem("<?=lang("dupes_own")?>", "", "<?=$pvp->link->slink($base_url."dupes.php?own=1")?>"));
    addMenuItem(new menuItem("<?=lang("dupes_own_strict")?>", "", "<?=$pvp->link->slink($base_url."dupes.php?own=1&strict=1")?>"));
  }
  viewMenu.items.viewDupes.setSubMenu(dupeMenu);
  viewMenu.items.viewDupes.showIcon("dupes");
  viewMenu.items.view_login.showIcon("exit");
  viewMenu.items.view_start.showIcon("start");
  viewMenu.items.view_medialist.showIcon("list");
  viewMenu.items.view_actors.showIcon("users");
  viewMenu.items.view_directors.showIcon("clapper");
  viewMenu.items.view_music.showIcon("music");
  viewMenu.items.view_taperestAbsolut.showIcon("time");
  viewMenu.items.view_taperestFiltered.showIcon("time");
  viewMenu.items.view_stats.showIcon("stats");
  menuBar.addMenuBarItem(new menuBarItem("<?=lang("view")?>",viewMenu,"ViewMenu"));
  menuBar.items.ViewMenu.showIcon("view");
<?
 #============================================================[ Print Menu ]===
?>
  printMenu = new jsDOMenu();
  with (printMenu) {
    addMenuItem(new menuItem("<?=lang("labels")?>", "print_label", "<?=$pvp->link->slink($base_url."label.php")?>"));
    addMenuItem(new menuItem("<?=lang("labels")?> (PS)", "print_pslabel", "<?=$pvp->link->slink($base_url."pslabel.php")?>"));
    addMenuItem(new menuItem("<?=lang("lists")?>", "print_lists", "<?=$pvp->link->slink($base_url."listgen.php")?>"));
  }
  printMenu.items.print_label.showIcon("labels");
  printMenu.items.print_pslabel.showIcon("labels");
  printMenu.items.print_lists.showIcon("list");
  menuBar.addMenuBarItem(new menuBarItem("<?=lang("print")?>",printMenu,"PrintMenu"));
  menuBar.items.PrintMenu.showIcon("print");
<?
 #=============================================================[ Help Menu ]===
?>
  helpMenu = new jsDOMenu();
  with (helpMenu) {
    addMenuItem(new menuItem("<?=lang("index")?>", "help_index", "JavaScript:open_help('')"));
    addMenuItem(new menuItem("<?=lang("about")?>", "help_about", "JavaScript:open_help('about')"));
    addMenuItem(new menuItem("<?=lang("history")?>", "help_history", "JavaScript:open_help('history')"));
    addMenuItem(new menuItem("<?=lang("pvp_homepage")?>", "help_project", "<?=$pvp->projectpage?>"));
<? if ($page_id) { ?>
    addMenuItem(new menuItem("-"));
    addMenuItem(new menuItem("Hilfe zum Thema '<?=lang($page_id)?>'", "help_topic"));
    items.help_topic.actionOnClick = "code:open_help('<?=$page_id?>')"
<? } ?>
  }
  helpMenu.items.help_index.showIcon("helpindex");
  helpMenu.items.help_about.showIcon("about");
  helpMenu.items.help_history.showIcon("history");
  helpMenu.items.help_project.showIcon("homepage");
  helpMenu.items.help_topic.showIcon("help2");
  menuBar.addMenuBarItem(new menuBarItem("<?=lang("help")?>",helpMenu,"HelpMenu"));
  menuBar.items.HelpMenu.showIcon("help");
}
<?
 #===================================================================[ End ]===
if (isset($_REQUEST["sess_id"])) {
 $login_info = lang("user").": ".$pvp->link->linkurl($base_url."admin/useredit.php?id=".$pvp->auth->user_id,$pvp->auth->user->login);
} else {
 $login_info = lang("not_logged_in");
}?>

 </script>
 <style type="text/css">
   body { margin-top: 25px; }
 </style>
</head><body onload="initjsDOMenu()">
<div id="pvp_menu" style="position:absolute;left:1px;top:1px;background-color:#efedde;width:100%;height:19px;border-bottom:1px solid black;">
 <span style="position:absolute;right:5px;font-size:12px"><?=$login_info?></span></div>
