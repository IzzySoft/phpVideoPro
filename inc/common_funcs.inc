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

  function display_error($error) {
    GLOBAL $colors;
    echo $colors["err"] . "<H2 ALIGN=CENTER>WARNING</H2></Font>\n";
    echo "<Table Width=90% Align=Center>\n <TR><TD>";
    echo "<P ALIGN=JUSTIFY>$error</P>\n";
    echo " </TD></TR></TABLE>\n</BODY></HTML>";
  }

 ##############################################################################
 # check wether the specified date is valid
 function check_date($date) {
   if ( !(trim($date)=="" || trim($date)=="0000-00-00") ) {
     $month = substr($date,5,2);
     $day   = substr($date,8);
     $year  = substr($date,0,4);
     if ( !( checkdate($month,$day,$year) ) ) {
       $error = "The date of aquiration you specified (\"$date\") is invalid. When "
              . "entering a date here, please follow the syntax \"YYYY-MM-DD\", where "
              . "\"YYYY\" stands for the year (four-digit), \"MM\" for the month "
              . "and \"DD\" for the day (both two-digit). If you want no date in here, "
              . "just leave this field blank (or set it to \"0000-00-00\"). Please hit "
              . "the \"Back\" button of your browser and correct your input.";
     display_error($error);
     exit;
     }
   }
 }

?>