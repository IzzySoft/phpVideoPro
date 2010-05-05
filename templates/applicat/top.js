// make sure that the "application window" covers not more than 95% of the
// browsers window
function adjustAppWin() {
  var refObj   = document.getElementById("appWin");
  var wwid     = document.documentElement.offsetWidth * 0.93;
  var owid     = refObj.offsetWidth;
  if (owid > wwid) refObj.width = wwid;
}
