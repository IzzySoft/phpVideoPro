<?
  function debug($level,$msg) {
    GLOBAL $debug;
    if ( strpos(strtoupper($debug["log"]),strtoupper($level))===false ) return;
    echo $msg;
  }
?>