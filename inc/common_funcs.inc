<?

 /* $Id$ */

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
   echo $colors["err"] . "<H2 ALIGN=CENTER>" . strtoupper(lang("warning")) . "</H2></Font>\n";
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
       $error = lang("wrong_date",lang("of_aquiration"),$date);
       if (!$exact) $error .= " " . lang("incomplete_date");
       $error .= "<BR><BR>" . lang("hit_back_to_correct");
     display_error($error);
     exit;
     }
   }
 }

 ##############################################################################
 # get filter settings from db
 function get_fquery(&$found,$fname,$tname="") {
  GLOBAL $db, $filter;
  if ( !strlen($tname) ) $tname=$fname;
  dbquery("SELECT id FROM $tname");
  while ( $db->next_record() ) {
    $id   = $db->f('id');
    if ($filter->$fname->$id) {
      if ($found) { $query .=  " OR v." . $fname . "_id='$id'";
      } else { $query = " v." . $fname . "_id='$id'"; }
      $found++;
    }
  }
  if ($found>1) $query = " (" . $query . " )";
  return $query;
 }

 function get_filters() {
  global $db, $filter;
  dbquery("SELECT value FROM preferences WHERE name='filter'");
  if ( $db->next_record() ) { // there are already filters defined
    $filter = unserialize ( rawurldecode( $db->f('value') ) );
    $i=0;
    if ($filter->length_min)  { $sql[$i] = " v.length>'" . $filter->length_min . "'"; $i++; }
    if ($filter->length_max)  { $sql[$i] = " v.length<'" . $filter->length_max . "'"; $i++; }
    if ($filter->aquired_min) { $sql[$i] = " v.aq_date>'" . $filter->aquired_min . "'"; $i++; }
    if ($filter->aquired_max) { $sql[$i] = " v.aq_date<'" . $filter->aquired_max . "'"; $i++; }
    if ($filter->fsk_min)     { $sql[$i] = " v.fsk>'" . $filter->fsk_min . "'"; $i++; }
    if ($filter->fsk_max)     { $sql[$i] = " v.fsk<'" . $filter->fsk_max . "'"; $i++; }
    if ($filter->title)       { $sql[$i] = " v.title like '%" . $filter->title . "%'"; $i++; }
    $found = 0;
    // -----------[ mtype ]---
    $temp = get_fquery($found,"mtype","mtypes");
    if ($found) { $sql[$i] = $temp; $found=0; $i++; }
    // -----------[ pict ]---
    $temp = get_fquery($found,"pict");
    if ($found) { $sql[$i] = $temp; $found=0; $i++; }
    // -----------[ color ]---
    $temp = get_fquery($found,"color","colors");
    if ($found) { $sql[$i] = $temp; $found=0; $i++; }
    // -----------[ tone ]---
    $temp = get_fquery($found,"tone");
    if ($found) { $sql[$i] = $temp; $found=0; $i++; }
    // -----------[ director ]---
    $temp = get_fquery($found,"director","directors");
    if ($found) { $sql[$i] = $temp; $found=0; $i++; }
    // -----------[ composer ]---
    dbquery("SELECT id FROM music");
    while ( $db->next_record() ) {
      $id   = $db->f('id');
      if ($filter->composer->$id) {
        if ($found) { $sql[$i] .=  " OR v.music_id='$id'";
        } else { $sql[$i] = " v.music_id='$id'"; }
        $found++;
      }
    }
    if ($found>1) $sql[$i] = " (" . $sql[$i] . " )";
    if ($found) { $found=0; $i++; }
    // -----------[ actor ]---
    dbquery("SELECT id FROM actors");
    while ( $db->next_record() ) {
      $id   = $db->f('id');
      if ($filter->actor->$id) {
        if ($found) { $sql[$i] .=  " OR v.actor1_id='$id' OR v.actor2_id='$id' OR v.actor3_id='$id' OR v.actor4_id='$id' OR v.actor5_id='$id'";
        } else { $sql[$i] = " v.actor1_id='$id' OR v.actor2_id='$id' OR v.actor3_id='$id' OR v.actor4_id='$id' OR v.actor5_id='$id'"; }
        $found++;
      }
    }
    if ($found>1) $sql[$i] = " (" . $sql[$i] . " )";
    if ($found) { $found=0; $i++; }
    // -----------[ category ]---
    dbquery("SELECT id FROM cat");
    while ( $db->next_record() ) {
      $id   = $db->f('id');
      if ($filter->cat->$id) {
        if ($found) { $sql[$i] .=  " OR v.cat1_id='$id' OR v.cat2_id='$id' OR v.cat3_id='$id'";
        } else { $sql[$i] = " v.cat1_id='$id' OR v.cat2_id='$id' OR v.cat3_id='$id'"; }
        $found++;
      }
    }
    if ($found>1) $sql[$i] = " (" . $sql[$i] . " )";
    if ($found) { $found=0; $i++; }
    // -----------[ finnished. ]---
    if ($i) {
      $i--;
      $where = $sql[0];
      for ($i=1;$i<count($sql);$i++) {
        $where .= " AND" . $sql[$i];
      }
      debug("V","<b>Where-Clause:</b> $where<br>");
      return $where;
    }
    debug("V","Empty filter<br>");
  }
  debug("V","No filter defined<br>");
  return "";
 }

 ##############################################################################
 # get translation
 function lang($key,$m1="",$m2="",$m3="",$m4="",$m5="",$m6="",$m7="",$m8="",$m9="",$m10="") {
   if (is_array($m1)){
     $vars = $m1;
   } else {
     $vars = array($m1,$m2,$m3,$m4,$m5,$m6,$m7,$m8,$m9,$m10);
   }
   return translate("$key",$vars);
 }
 function translate($key,$vars=FALSE) {
   GLOBAL $db;
   $trans = $key;
   if (!$vars) $vars=array();
   dbquery("SELECT value FROM preferences WHERE name='lang'");
   if ( $db->next_record() ){
     $lang = $db->f('value');
   } else {
     $lang = "en";
   }
   $lang = strtolower($lang);
   dbquery("SELECT message_id,lang,content FROM lang WHERE lang='$lang' OR lang='en'");
   while ( $db->next_record() ) {
     $msg_id = $db->f('message_id');
     $transi = $db->f('content');
     $langi  = $db->f('lang');
     if ( strtolower($key)==strtolower($msg_id) ) {
       $trans = $transi;
       if ( $lang==$langi) break;
     }
   }
   $ndx = 1;
   while ( list($k,$v)=each($vars) ) {
     $trans = preg_replace("/%$ndx/",$v,$trans);
     $ndx++;
   }
   return $trans;
 }
?>