<link href="<? echo $base_url ?>inc/newmenue.css" rel="stylesheet" type="text/css">
<style type="text/css">

body {
  margin: 0px;
}

#menuBar {
  background-color: #c0c0c0;
  border-style: solid;
  border-width: 0px;
  border-top-color: #f0f0f0;
  border-top-width: 2px;
  border-bottom-color: #909090;
  border-bottom-width: 2px;
  color: #000000;
  padding: 0px;
  padding-top: 2px;
  padding-bottom: 2px;
  position: absolute;
  left: 0px;
  top: 0px;
  text-align: left;
  width: 100%;
  z-index: 100;
}

a.menuButton, a.menuButtonActive {
  border-style: solid;
  border-width: 1px;
  border-color: #c0c0c0;
  color: #000000;
  cursor: default;
  font-family: "MS Sans Serif", Arial, Tahoma, sans-serif;
  font-size: 8pt;
  font-style: normal;
  font-weight: normal;
  padding: 2px;
  padding-left: 6px;
  padding-right: 6px;
  position: relative;
  left: 0px;
  top: 0px;
  text-decoration: none;
}

a.menuButton:hover {
  border-color: #f0f0f0 #505050 #505050 #f0f0f0;
  color: #000000;
}

a.menuButtonActive, a.menuButtonActive:hover {
  background-color: #909090;
  border-color: #505050 #f0f0f0 #f0f0f0 #505050;
  color: #ffffff;
  left: 1px;
  top: 1px;
}

.menu {
  background-color: #c0c0c0;
  border-style: solid;
  border-width: 2px;
  border-top-color: #f0f0f0;
  border-right-color: #909090;
  border-bottom-color: #909090;
  border-left-color: #f0f0f0;
  padding: 0px;
  position: absolute;
  text-align: left;
  visibility: hidden;
  z-index: 101;
}

a.menuItem {
  color: #000000;
  cursor: default;
  display: block;
  font-family: "MS Sans Serif", Arial, Tahoma,sans-serif;
  font-size: 8pt;
  font-style: normal;
  font-weight: normal;
  margin: 0px;
  padding: 2px;
  padding-left: 12px;
  padding-right: 12px;
  text-decoration: none;
}

a.menuItem:hover {
  background-color: #000080;
  color: #ffffff;
}

.menuItemSep {
  border-bottom: 1px solid #f0f0f0;
  border-top: 1px solid #909090;
  margin: 3px 2px 3px 2px;
}

</style>
<script type="text/javascript">

// Determine browser type (Netscape 6 or IE 5.5/6.0).
var isIE5 = (navigator.userAgent.indexOf("MSIE 5.5") > 0  |
             navigator.userAgent.indexOf("MSIE 6.0") > 0) ? 1 : 0;
var isNS6 = (navigator.userAgent.indexOf("Gecko")    > 0) ? 1 : 0;
// var isNS6 = (navigator.userAgent.indexOf("Mozilla")    > 0) ? 1 : 0;
// var isNS6 = 0;
// var isIE5 = 1;

// For IE, adjust menu bar styling.
if (isIE5) {
  document.styleSheets[document.styleSheets.length - 1].addRule("#menuBar", "padding-top:4px");
  document.styleSheets[document.styleSheets.length - 1].addRule("#menuBar", "padding-bottom:3px");
}

// Global variable for tracking the currently active button.
var activeButton = null;

// Capture mouse clicks on the page so any active button can be deactivated.
if (isIE5)
  document.onmousedown = pageMousedown;
if (isNS6)
  document.addEventListener("mousedown", pageMousedown, true);

function pageMousedown(event) {
  var className;

  // If the object clicked on was not a menu button or item, close any active
  // menu.
  if (isIE5)
    className = window.event.srcElement.className;
  if (isNS6)
    className = (event.target.className ?
      event.target.className : event.target.parentNode.className);

  if (className != "menuButton"  && className != "menuItem" &&
      className != "menuItemSep" && activeButton)
    resetButton(activeButton);
}

function buttonClick(button, menuName) {

  // Blur focus from the link to remove that annoying outline.
  button.blur();

  // Associate the named menu to this button if not already done.
  if (!button.menu)
    button.menu = document.getElementById(menuName);

  // Reset the currently active button, if any.
  if (activeButton && activeButton != button)
    resetButton(activeButton);

  // Toggle the button's state.
  if (button.isDepressed)
    resetButton(button);
  else
    depressButton(button);

  return false;
}

function buttonMouseover(button, menuName) {

  // If any other button menu is active, deactivate it and activate this one.
  // Note: if this button has no menu, leave the active menu alone.
  if (activeButton && activeButton != button) {
    resetButton(activeButton);
    if (menuName)
      buttonClick(button, menuName);
  }
}

function depressButton(button) {

  // Change the button's style class to make it look like it's depressed.
  button.className = "menuButtonActive";

  // For IE, force first menu item to the width of the parent menu,
  // this causes mouseovers work for all items even when cursor is
  // not over the link text.
  if (isIE5 && !button.menu.firstChild.style.width)
    button.menu.firstChild.style.width =
      button.menu.offsetWidth + "px";

  // Position the associated drop down menu under the button and
  // show it. Note that the position must be adjusted according to
  // browser, styling and positioning.
  x = getPageOffsetLeft(button);
  y = getPageOffsetTop(button) + button.offsetHeight;
  if (isIE5)
    y += 2;
  if (isNS6) {
    x--;
    y--;
  }
  button.menu.style.left = x + "px";
  button.menu.style.top  = y + "px";
  button.menu.style.visibility = "visible";

  // Set button state and let the world know which button is
  // active.
  button.isDepressed = true;
  activeButton = button;
}

function resetButton(button) {

  // Restore the button's style class.
  button.className = "menuButton";

  // Hide the button's menu.
  if (button.menu)
    button.menu.style.visibility = "hidden";

  // Set button state and clear active menu global.
  button.isDepressed = false;
  activeButton = null;
}

function getPageOffsetLeft(el) {

  // Return the true x coordinate of an element relative to the page.
  return el.offsetLeft + (el.offsetParent ? getPageOffsetLeft(el.offsetParent) : 0);
}

function getPageOffsetTop(el) {

  // Return the true y coordinate of an element relative to the page.
  return el.offsetTop + (el.offsetParent ? getPageOffsetTop(el.offsetParent) : 0);
}

</script>
</head>
<body>

<!-- Tags for the menu bar. -->

<div id="menuBar">
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

<div id="editMenu" class="menu">
<a class="menuItem" href="<? echo $base_url ?>new.php"><? echo lang("add_entry") ?></a>
<div class="menuItemSep"></div>
<a class="menuItem" href="<? echo $base_url ?>configure.php"><? echo lang("configuration") ?></a>
<div class="menuItemSep"></div>
<a class="menuItem" href="http://www.qumran.org/ftp/net/div/izzysoft/phpvideopro.tgz"><? echo lang("dl_pvp_latest") ?></a>
</div>

<div id="filterMenu" class="menu">
<a class="menuItem" href="<? echo $base_url ?>setfilter.php"><? echo lang("set_filter") ?></a>
<a class="menuItem" href="<? echo $base_url ?>setfilter.php?reset=1"><? echo lang("unset_filter") ?></a>
</div>

<div id="viewMenu" class="menu">
<a class="menuItem" href="<? echo $base_url ?>index.php"><? echo lang("start_page") ?></a>
<div class="menuItemSep"></div>
<a class="menuItem" href="<? echo $base_url ?>medialist.php"><? echo lang("medialist") ?></a>
<a class="menuItem" href="<? echo $base_url ?>stafflist.php?stafftype=actors"><? echo lang("actors") ?></a>
<a class="menuItem" href="<? echo $base_url ?>stafflist.php?stafftype=directors"><? echo lang("directors") ?></a>
<a class="menuItem" href="<? echo $base_url ?>stafflist.php?stafftype=music"><? echo lang("composer") ?></a>
<div class="menuItemSep"></div>
<a class="menuItem" href="<? echo $base_url ?>taperest.php"><? echo lang("taperest_absolute") ?></a>
<a class="menuItem" href="<? echo $base_url ?>taperest.php?usefilter=1"><? echo lang("taperest_filtered") ?></a>
<div class="menuItemSep"></div>
<a class="menuItem" href="<? echo $base_url ?>stats.php"><? echo lang("db_stats") ?></a>
</div>

<div id="printMenu" class="menu">
<a class="menuItem" href="<? echo $base_url ?>label.php"><? echo lang("labels") ?></a>
<a class="menuItem" href="<? echo $base_url ?>listgen.php"><? echo lang("lists") ?></a>
</div>

<div id="helpMenu" class="menu">
<a class="menuItem" href="JavaScript:open_help('')"><? echo lang("index") ?></a>
<a class="menuItem" href="JavaScript:open_help('about')"><? echo lang("about") ?></a>
<a class="menuItem" href="JavaScript:open_help('history')"><? echo lang("history") ?></a>
<? if ($page_id) {
?><div class="menuItemSep"></div>
<a class="menuItem" href="JavaScript:open_help('<? echo $page_id ?>')"><? echo lang("help_about") . " \"" . lang($page_id) . "\"" ?></a>
<? }
?></div>

<!-- div id="demoBox" style="margin:24px;position:relative;top:48px;">
</div -->
