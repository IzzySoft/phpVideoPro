<?
 ##############################################################################
 # output debug message depending on configured debug level
 function debug($level,$msg) {
   GLOBAL $debug;
   if ( strpos(strtoupper($debug["log"]),strtoupper($level))===false ) return;
   echo $msg;
 }

 ##############################################################################
 # preset empty (table) fields with a hard space (to enforce table borders)
 function check_empty(&$field) {
   if ($field == "") $field = "&nbsp";
 }

 ##############################################################################
 # check wether the string contains only digits (and nothing else)
 function is_num($fvar) {
   $regnum = "/\D/";
   if (preg_match($regnum,$fvar)) return false;
   return true;
 }

 ##############################################################################
 # format and display an error message for unrecoverable error
 function display_error($error) {
   GLOBAL $colors;
   echo $colors["err"] . "<H2 ALIGN=CENTER>WARNING</H2></Font>\n";
   echo "<Table Width=90% Align=Center>\n <TR><TD>";
   echo "<P ALIGN=JUSTIFY>$error</P>\n";
   echo " </TD></TR></TABLE>\n</BODY></HTML>";
 }

 ##############################################################################
 # check wether the specified date is valid
 # if FALSE or 0 are supplied as second parameter to this function, exact
 # comparision is disabled and relax mode activated. In relax mode, the date
 # only has to fulfill a few conditions: year must be > 1900, month < 13 and
 # day < 32 (which also allows "2000-00-00") - whereas in exact mode the given
 # date must really exist
 function check_date($date,$exact=1) {
   $correct = TRUE;
   if ( (substr($date,4,1)!="-") || (substr($date,7,1)!="-") ) $correct = FALSE;
   $month = substr($date,5,2);
   $day   = substr($date,8);
   $year  = substr($date,0,4);
   if ($exact && $correct) { $correct = checkdate($month,$day,$year);
   } elseif ($correct) { $correct = is_num($month . $day . $year) && ($month<13) && ($day<32) && ($year>1900); }
   if ( !(trim($date)=="" || trim($date)=="0000-00-00") ) {
     if ( !$correct ) {
       $error = "The date of aquiration you specified (\"$date\") is invalid. When "
              . "entering a date here, please follow the syntax \"YYYY-MM-DD\", where "
              . "\"YYYY\" stands for the year (four-digit), \"MM\" for the month "
              . "and \"DD\" for the day (both two-digit). If you want no date in here, "
              . "just leave this field blank (or set it to \"0000-00-00\"). ";
       if (!$exact) $error .= "If you do not know the exact date, but - for example - "
              . "only that you aquired it in the year 2000, substitute zeros for the "
              . "unknown data - in our example the date should look like \"2000-00-00\". ";
       $error .= "<BR><BR>Please hit the \"Back\" button of your browser and correct your input.";
     display_error($error);
     exit;
     }
   }
 }

?>