<?
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Setup program: Recode all database content to UTF-8                       #
 #############################################################################

 /* $Id$ */

 # ======================================[ Set up the encoding environment ]===
 if ( function_exists("mb_convert_encoding") ) {
   function str2utf8($str) {
     GLOBAL $enc;
     return mb_convert_encoding($str,"UTF-8",$enc);
   }
 } elseif ( function_exists("recode_string") ) {
   function str2utf8($str) {
     GLOBAL $enc;
     return recode_string("$enc..utf8",$str);
   }
 } elseif ( function_exists("iconv") ) {
   function str2utf8($str) {
     GLOBAL $enc;
     return iconv($enc,"UTF-8",$str);
   }
 } else {
   $enc_noavail = 1;
 }

 # =======================================================[ Convert tables ]===
 function convert_staff($table) {
   GLOBAL $db,$enc;
   echo "<li>Converting table <code>$table</code> from '$enc' to 'UTF-8'... ";
   $db->query("SELECT id,name,firstname FROM $table");
   while ( $db->next_record() ) {
     $id    = $db->f('id');
     $name  = addslashes(str2utf8($db->f('name')));
     $fname = addslashes(str2utf8($db->f('firstname')));
     $sql[] = "UPDATE $table SET name='$name',firstname='$fname' WHERE id=$id";
   }
   $qc = count($sql);
   echo "<span class='ok'>$qc records...</span> ";
   for ($i=0;$i<$qc;++$i) {
     $db->query($sql[$i]);
   }
   echo "Done.<br>\n";
 }

 function convert_video() {
   GLOBAL $db,$enc;
   echo "<LI>Converting table <code>video</code> from '$enc' to 'UTF-8'... ";
   $details = array("title","source","country","comment","counter1","counter2","aq_date");
   $db->query("SELECT id,title,source,country,comment,counter1,counter2,aq_date FROM video");
   while ( $db->next_record() ) {
     $id    = $db->f('id');
     $query = "UPDATE video SET";
     foreach ($details as $item) {
       $query .= " $item='".addslashes(str2utf8($db->f($item)))."',";
     }
     $query .= "id=$id WHERE id=$id";
     $sql[] = $query;
   }
   $qc = count($sql);
   echo "<span class='ok'>$qc records...</span> ";
   for ($i=0;$i<$qc;++$i) {
     $db->query($sql[$i]);
   }
   echo "Done.</LI>";
 }

 function convert_lang() {
   GLOBAL $db,$enc;
   $db->query("SELECT lang_id,lang_name,charset FROM languages WHERE charset!='utf-8' AND available='yes'");
   while ( $db->next_record() ) {
     $l["id"]   = $db->f('lang_id');
     $l["name"] = $db->f('lang_name');
     $l["charset"] = $db->f('charset');
     $lang[]    = $l;
   }
   $lc = count($lang);
   echo "Converting $lc languages:<UL STYLE='margin-top:0'>";
   for ($i=0;$i<$lc;++$i) {
     echo "<LI>".$lang[$i]["name"]." (".$lang[$i]["id"].", ".$lang[$i]["charset"]."): ";
     unset($sql);
     $enc = $lang[$i]["charset"];
     if ($enc=="iso-8859-8-i" || $enc=="koi8-r") {
       echo "<span class='error'>unable to convert; please re-import language file via the configuration screen.</span> ";
     } else {
       $db->query("SELECT message_id,content,comment FROM lang WHERE lang='".$lang[$i]["id"]."'");
       while ( $db->next_record() ) {
         $sql[] = "UPDATE lang SET content='".addslashes(str2utf8($db->f('content')))
                ."',comment='".addslashes(str2utf8($db->f('comment')))."' WHERE lang='"
                .$lang[$i]["id"]."' AND message_id='".$db->f('message_id')."'";
       }
       $sql[] = "UPDATE languages SET charset='UTF-8' WHERE lang_id='".$lang[$i]["id"]."'";
     }
     $tc = count($sql);
     echo "<span class='ok'>$tc entries...</span> ";
     for ($k=0;$k<$tc;++$k) {
       $db->query($sql[$k]);
     }
     echo "Done.</LI>";
   }
   echo "</UL>\n";
 }

 #===========================================================[ HTML Header ]===
 function openHTML($title,$step) {
 header('Content-type: text/html; charset=utf-8');
?>
<HTML><HEAD>
 <TITLE><?=$title?></TITLE>
 <META http-equiv="Content-Type" content="text/html; charset=utf-8">
<? include("../templates/default/default.css"); ?>
</HEAD>
<BODY>
<FORM NAME="coding" METHOD="post" ACTION="<?=$PHP_SELF?>">
<INPUT TYPE="hidden" NAME="step" VALUE="<?=$step?>">
<TABLE BORDER="1" WIDTH="90%" ALIGN="center" STYLE="margin-top:10">
 <TR><TH><?=$title?></TH></TR><TR><TD>&nbsp;</TD></TR>
<?
 }

 function closeHTML() {
   echo "\n</TABLE></FORM>\n</BODY></HTML>\n";
 }


 # =====================================[ Set up phpVideoPro configuration ]===
 include ("../inc/includes.inc");
 $title = "phpVideoPro Setup: Converting database entries to UTF-8";

 #-----------------------------------------------------------------------------
 #-------------------------------------------------| Display Initial Infos |---
 #-----------------------------------------------------------------------------
 if ( empty($_POST["submit"]) ) {
   openHTML($title,0);
?>
 <TR><TD><P ALIGN="justify">
  With the different languages supported by phpVideoPro, we found that they
  sometimes rise a problem: A visitor selecting a language which uses a
  character set different from the one used to insert the data into the
  database, could have a messed up page as result. In the best case, only
  certain characters are affected (e.g. German "Umlauts" viewed with a
  Russian encoding), since the basic 7Bit ASCII is common to most charsets.
  But with e.g. Russian content in the DB browsed with Latin-1, the whole
  thing was unreadable.
 </P><P ALIGN="justify">
  In order to solve this problem finally, we decided to convert everything to
  UTF-8 - a character set that supports all languages. For the user this should
  be transparent, since browser and webserver do the conversion of the input.
  But in order to be able to use this, we must convert all existing database
  content - which we are about to do now.
 </P></TD></TR>
 <TR><TD><P ALIGN="justify">
  Converting large databases can lead us to another trouble: due to the maximum
  execution time of your PHP setup (and the maximum time the browser will wait
  for an answer from the server before deciding the connection died), we split
  the process into several pieces:
 </P><OL>
  <LI>Converting the <code>video</code> table (i.e. titles, comments...)</LI>
  <LI>Converting staff member names (i.e. actors, directors, componists)</LI>
  <LI>Converting all installed languages (i.e. the translation system)</LI>
 </OL>
 </TD></TR>
<?
   if ($enc_noavail) {
?>
 <TR><TD ALIGN="center"><FONT COLOR="#FF3030">Sorry - but your PHP installation
   supports no charset conversion. This means, you either have to update your
   PHP to support either the <code>recode_string()</code>, the <code>iconv()</code>
   or the <code>mb_*()</code> functions - or you have to do the conversion
   manually by using your database's export functions, running your OSs
   <code>recode</code> utility and the import the result again.</TD></TR>
<?
   } else {
?>
  <TR><TD>
   <P ALIGN="center">
    If you are ready to start: Press the button!
   </P>
  </TD></TR><TR><TD>&nbsp;</TD></TR><TR><TD>
    <P ALIGN="center"><INPUT TYPE="submit" NAME="submit" VALUE="Next"></P>
  </TD></TR>
<?
   }
   closeHTML();
   exit;
 }


switch ($_POST["step"]) {
 case 0 :

 #-----------------------------------------------------------------------------
 #-----------------------------------------------| Step 0: Getting started |---
 #-----------------------------------------------------------------------------
 $lang = $pvp->preferences->lang;
 $db->query("SELECT charset,lang_name FROM languages WHERE lang_id='$lang'");
 $db->next_record();
 $charset = $db->f('charset');
 $plang   = $db->f('lang_name');
 $langAvail = $db->get_languages(1);
 $la["id"]   = 0;
 $la["name"] = "No conversion";
 $la["charset"] = "UTF-8";
 $langAvail[] = $la;
 $title .= " -- Step 1: Converting the VIDEO table";

 openHTML($title,1);

?>
 <TR><TD STYLE="background-color:#ff7070">
  <P ALIGN="justify"><B>BEWARE! The following procedure affects your entire
   phpVideoPro database. All the data you have been collecting must be converted
   to UTF-8. If this procedure somehow fails (i.e. due to too large execution
   time if you have a large data collection), it may leave your data in an
   undefined state. So make sure you have a backup of your database before you
   continue!</P>
 </TD></TR><TR><TD>&nbsp;</TD></TR><TR><TD>
<P ALIGN="justify">Please select the encoding you used to record your data.
 <B>Note</B>: if different encodings have been used, the conversion process may
 mess up your comments/titles/names. So either don't convert (and change
 manually) or, if possible, select the encoding that is compatible to all
 others (e.g. if you used ISO-8859-1, US7ASCII and ISO-8859-15, select the
 ISO-8859-15 charset since it includes all characters from the other two
 charsets as well). If you used the UFT-8 charset, no conversion is needed. So
 if you chose to not automatically convert your data, just select a language
 using the UTF-8 charset to skip this step.</P><HR><BR>
<P ALIGN="center">
 <b>Source encoding:</B><BR><BR><SELECT NAME="encoding">
<?
 $lc = count($langAvail);
 for ($i=0;$i<$lc;++$i) {
   if ( empty($langAvail[$i]["charset"]) ) continue;
   echo "   <OPTION VALUE='".$langAvail[$i]["charset"]."'";
   if ($plang == $langAvail[$i]["name"]) echo " SELECTED";
   echo ">".$langAvail[$i]["name"]." (".$langAvail[$i]["charset"].")</OPTION>\n";
 }
?>
 </SELECT></P><BR>
 </TD></TR><TR><TD>
  <P ALIGN="center"><INPUT TYPE="submit" NAME="submit" VALUE="Next"></P>
</TD></TR>
<?

   closeHTML();
   exit;
   break;

 case 1: 
   $enc = $_POST["encoding"];
   if ( strtolower($enc) == "utf-8" ) { // no data conversion needed - goto lang
     $title .= " -- Skipping data conversion";
     openHTML($title,3);
?>
  <TR><TD>
   <P ALIGN="justify">
    You selected a language which already uses the UTF-8 character set. This
    means, if you used this language while editing your data, we don't need
    to convert your movie data but can skip directly to the language part. If
    this is correct, just push the button below - otherwise use your browsers
    "Back" button and correct your input on the previous page.
   </P>
  </TD></TR><TR><TD>
  <P ALIGN="center"><INPUT TYPE="submit" NAME="submit" VALUE="Next"></P>
  </TD></TR>
<?   } else {

 #-----------------------------------------------------------------------------
 #----------------------------------------| Step 1: Converting table VIDEO |---
 #-----------------------------------------------------------------------------
       $title .= " -- Converting the staff tables";
       openHTML($title,2);
       echo "<INPUT TYPE='hidden' NAME='encoding' VALUE='$enc'>\n";
       echo "  <TR><TD>\n   Conversion process for <code>VIDEO</code> table:<BR>\n";
       convert_video();
       echo "  </TR></TD>\n";
?>
  <TR><TD>
   <P ALIGN="justify">
    If you find no errors reported above, the conversion of your <code>VIDEO</code>
    table has been successfully completed and we can proceed with the next step:
    Converting the staff table, containing the names of the actors, directors,
    and composers. Push the button when you are ready ;)
   </P>
  </TD></TR><TR><TD>
   <P ALIGN="center"><INPUT TYPE="submit" NAME="submit" VALUE="Next"></P>
  </TR></TD>
<?
   }
   closeHTML();
   exit;
   break;


 case 2:
   $enc = $_POST["encoding"];

 #-----------------------------------------------------------------------------
 #---------------------------------------| Step 2: Converting staff tables |---
 #-----------------------------------------------------------------------------
   $title .= " -- Converting the translations";
   openHTML($title,3);
   echo "<INPUT TYPE='hidden' NAME='encoding' VALUE='$enc'>\n";
   echo "  <TR><TD>\n   Conversion process for the staff tables:<BR>\n";
   convert_staff("actors");
   convert_staff("directors");
   convert_staff("music");
   echo "  </TR></TD>\n";
?>
  <TR><TD>
   <P ALIGN="justify">
    If you find no errors reported above, the conversion of your staff tables
    has been successfully completed and we can proceed with the next step:
    Converting the installed languages. Push the button when you are ready ;)
   </P>
  </TD></TR><TR><TD>
   <P ALIGN="center"><INPUT TYPE="submit" NAME="submit" VALUE="Next"></P>
  </TR></TD>
<?
   closeHTML();
   exit;
   break;

 case 3:
   $enc = $_POST["encoding"];
 
 #-----------------------------------------------------------------------------
 #------------------------------------------| Step 3: Converting languages |---
 #-----------------------------------------------------------------------------
   $title .= " -- Finishing";
   openHTML($title,4);
   echo "<INPUT TYPE='hidden' NAME='encoding' VALUE='$enc'>\n";
   $db->query("UPDATE languages SET charset='UTF-8' WHERE available='no'");
   $db->query("SELECT COUNT(*) AS langs FROM languages WHERE available='yes' AND charset!='utf-8'");
   $db->next_record();
   $lc = $db->f('langs');
   if ( $lc > 0 ) {
     echo "  <TR><TD>\n";
     convert_lang();
     echo "  </TR></TD>\n";
?>
  <TR><TD>
   <P ALIGN="justify">
    If you find no errors reported above, the conversion of the translations
    has been successfully completed. This was the last step in the UTF-8
    conversion process - so you are finished with this!
   </P>
  </TD></TR><TR><TD>
<?
   } else {
?>
  <TR><TD>
   <P ALIGN="justify">
    There are no installed languages that need to be converted. This means,
    you are finished with the UTF-8 conversion now!
   </P>
  </TD></TR><TR><TD>
<?
   }
?>
   <P ALIGN="justify">
    If you were brought here by the database update process, press the button
    a last time to complete the update. Otherwise you don't need to, but simply
    can continue using the application!
   </P>
  </TD></TR><TR><TD>
   <P ALIGN="center"><INPUT TYPE="submit" NAME="submit" VALUE="Next"></P>
  </TR></TD>
<?
   closeHTML();
   exit;
   break;

 case 4:
   $enc = $_POST["encoding"];
   $db->query("SELECT value FROM pvp_config WHERE name='version'");
   $db->next_record();
   $ver = $db->f('value');
   if ( $ver == "0.6.2" ) {
#     echo "DB version: '$ver'<br>\n";
#     $db->query("UPDATE pvp_config SET value='0.6.3' WHERE name='version'");
     header("Location: update.php?oldversion=0.6.3");
   } else {
     header("Location: $base_url");
     exit;
   }
   exit; // Finished conversion
   break;
}
?>
