<?
  function debug($level,$msg) {
    GLOBAL $debug;
    if ( strpos(strtoupper($debug["log"]),strtoupper($level))===false ) return;
    echo $msg;
  }
  function check_empty(&$field) {
    if ($field == "") $field = "&nbsp";
  }
  function check_empty_name(&$field) {
    if (trim($field) == ",") $field = "";
  }
?>