 <link href="<? echo $base_url ?>inc/newmenue.css" rel="stylesheet" type="text/css">
 <script type="text/javascript" src="<?=$base_url?>inc/newmenue.js">></script>
</head><body>

<!-- Tags for the menu bar. -->
<div class="fixme">
<div id="menuBar">
<? if ($pvp->auth->admin) { ?>
 <a class="menuButton"
    href=""
    onclick="return buttonClick(this, 'adminMenu');"
    onmouseover="buttonMouseover(this, 'adminMenu');"
    ><? echo lang("admin") ?></a>
<? } ?>
 <a class="menuButton"
    href=""
    onclick="return buttonClick(this, 'editMenu');"
    onmouseover="buttonMouseover(this, 'editMenu');"
    ><? echo lang("edit") ?></a>
 <a class="menuButton"
    href=""
    onclick="return buttonClick(this, 'filterMenu');"
    onmouseover="buttonMouseover(this, 'filterMenu');"
    ><? echo lang("filter") ?></a>
 <a class="menuButton"
    href=""
    onclick="return buttonClick(this, 'viewMenu');"
    onmouseover="buttonMouseover(this, 'viewMenu');"
    ><? echo lang("view") ?></a>
 <a class="menuButton"
    href=""
    onclick="return buttonClick(this, 'printMenu');"
    onmouseover="buttonMouseover(this, 'printMenu');"
    ><? echo lang("print") ?></a>
 <a class="menuButton"
    href=""
    onclick="return buttonClick(this, 'helpMenu');"
    onmouseover="buttonMouseover(this, 'helpMenu');"
    ><? echo lang("help") ?></a>
</div>

<!-- Tags for the drop down menus. -->
<div id="adminMenu" class="menu">
<?
 echo $pvp->link->linkurl($base_url."admin/cats.php",lang("admin_cats"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."admin/movietech.php",lang("admin_movietech"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."admin/disktypes.php",lang("admin_disktypes"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."admin/translations.php",lang("admin_translations"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."admin/ps_templates.php",lang("admin_pstemplates"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."admin/printers.php",lang("admin_printers"),"class='menuItem'") ."\n";
 echo "<div class='menuItemSep'></div>\n";
 echo $pvp->link->linkurl($base_url."admin/users.php",lang("admin_users"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."admin/sessions.php",lang("admin_sessions"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."admin/filters.php",lang("admin_filter"),"class='menuItem'") ."\n";
 echo "<div class='menuItemSep'></div>\n";
 echo $pvp->link->linkurl($base_url."admin/orphans.php",lang("admin_orphans"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."admin/backup_db.php",lang("backup_db"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."admin/configure.php",lang("configuration"),"class='menuItem'") ."\n";
?>
<div class='menuItemSep'></div>
<a class="menuItem" href="http://www.qumran.org/homes/izzy/software/get_update.php?program=pvp&version=<?=$version?>&info_url=http://<?=$SERVER_NAME?><?=$base_url?>info.php?action=update"><?=lang("dl_pvp_latest") ?></a>
</div>

<div id="editMenu" class="menu">
<?
 if ($pvp->auth->add) {
  $lastnum = $db->get_lastmovienum();
  for ($i=0;$i<count($lastnum);++$i) {
    echo "<A HREF=\"JavaScript:get_movienum('".lang("enter_new_medianr",$lastnum[$i][mtype])."',".(int)$lastnum[$i][cass_id].",'".$pvp->link->slink($base_url."new.php?mtype_id=".$lastnum[$i][mtype_id])."')\" class='menuItem'>".lang("new_movie_on",$lastnum[$i][mtype])."</A>\n";
  }
 }
 echo "<div class='menuItemSep'></div>\n";
 echo $pvp->link->linkurl($base_url."search.php",lang("search_movie"),"class='menuItem'") ."\n";
 echo "<div class='menuItemSep'></div>\n";
 echo $pvp->link->linkurl($base_url."configure.php",lang("preferences"),"class='menuItem'") ."\n";
?>
</div>

<div id="filterMenu" class="menu">
<?
 echo $pvp->link->linkurl($base_url."setfilter.php",lang("set_filter"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."setfilter.php?reset=1",lang("unset_filter"),"class='menuItem'") ."\n";
?>
</div>

<div id="viewMenu" class="menu">
<?
 echo $pvp->link->linkurl($base_url."index.php",lang("start_page"),"class='menuItem'") ."\n";
 echo "<div class='menuItemSep'></div>\n";
 echo $pvp->link->linkurl($base_url."medialist.php",lang("medialist"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."stafflist.php?stafftype=actors",lang("actors"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."stafflist.php?stafftype=directors",lang("directors"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."stafflist.php?stafftype=music",lang("composer"),"class='menuItem'") ."\n";
 echo "<div class='menuItemSep'></div>\n";
 echo $pvp->link->linkurl($base_url."taperest.php",lang("taperest_absolute"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."taperest.php?usefilter=1",lang("taperest_filtered"),"class='menuItem'") ."\n";
 echo "<div class='menuItemSep'></div>\n";
 echo $pvp->link->linkurl($base_url."dupes.php",lang("dupes"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."stats.php",lang("db_stats"),"class='menuItem'") ."\n";
?>
</div>

<div id="printMenu" class="menu">
<?
 echo $pvp->link->linkurl($base_url."label.php",lang("labels"),"class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."pslabel.php",lang("labels")." (PS)","class='menuItem'") ."\n";
 echo $pvp->link->linkurl($base_url."listgen.php",lang("lists"),"class='menuItem'") ."\n";
?>
</div>

<div id="helpMenu" class="menu">
<a class="menuItem" href="JavaScript:open_help('')"><?=lang("index") ?></a>
<a class="menuItem" href="JavaScript:open_help('about')"><?=lang("about") ?></a>
<a class="menuItem" href="JavaScript:open_help('history')"><?=lang("history") ?></a>
<? if ($page_id) {
?><div class="menuItemSep"></div>
<a class="menuItem" href="JavaScript:open_help('<?=$page_id ?>')"><?=lang("help_about") . " \"" . lang($page_id) . "\"" ?></a>
<? }
?></div>

</div>