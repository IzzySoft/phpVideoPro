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
