// make sure that the "application window" covers not more than 95% of the
// browsers window
function adjustAppWin() {
  refObj   = document.getElementById("appWin");
  wwid     = document.documentElement.offsetWidth * 0.93;
  owid     = refObj.offsetWidth;
  if (owid > wwid) refObj.width = wwid;
}
