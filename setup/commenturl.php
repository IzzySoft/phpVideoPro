<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Administration: Update comments that contain URLs with [url] tags         #
 #############################################################################

 /* $Id$ */

 include("inc/includes.inc");
 include("inc/header.inc");

 $query = "SELECT id,comment,title FROM video WHERE"
        . " comment LIKE '%www.%' OR comment LIKE '%ftp.%'";
 $db->query($query);
 while ( $db->next_record() ) {
   $r->id      = $db->f('id');
   $r->comment = $db->f('comment');
   $r->title   = $db->f('title');
   $rec[]      = $r;
 }
 $rcount = count($rec);

 echo "<P><B>Found $rcount entries that seem to contain URLs:</B></P><UL>";
 $ucount = 0; $fcount = 0;
 for ($i=0;$i<$rcount;++$i) {
   $data  = $rec[$i]->comment;
   $movie = $rec[$i]->id;
   $title = $rec[$i]->title;
   if ( preg_match("/<img[^>]*http:[^>]*>/i",$data) ) {
     echo " <LI>\"$title\" contains an &lt;IMG&gt; tag with http: reference. Leaving untouched; please update manually.</LI>\n";
     continue;
   }
   if ( preg_match("/\[url\]\S+\[\/url\]/i",$data) ) {
     echo " <LI>\"$title\" already seems to be up-to-date with the [url] tag.</LI>\n";
     continue;
   }
   if ( preg_match("/\[href\]\S+\[\/href\]/i",$data) ) {
     echo " <LI>\"$title\" uses the undocumented [href] tag. Please use the [url] tag instead. Leaving this title untouched for now.</LI>\n";
     continue;
   }
   if ( preg_match("/\[img\]\S+\[\/img\]/i",$data) ) {
     echo " <LI>\"$title\" contains [img] tag, leaving it untouched.</LI>\n";
     continue;
   }
   if ( preg_match("/\[imgr\]\S+\[\/imgr\]/i",$data) ) {
     echo " <LI>\"$title\" contains [imgr] tag, leaving it untouched.</LI>\n";
     continue;
   }
   $lines = split("\n",$data);
   $rline = "";
   while ( list ($key,$line) = each ($lines)) {
     $line = eregi_replace("([ \t]|^)www\."," http://www.",$line);
     $line = eregi_replace("([ \t]|^)ftp\."," ftp://ftp.",$line);
     $line = eregi_replace("(http://[^ )\r\n]+)","[url]\\1[/url]",$line);
     $line = eregi_replace("(https://[^ )\r\n]+)","[url]\\1[/url]",$line);
     $line = eregi_replace("(ftp://[^ )\r\n]+)","[url]\\1[/url]",$line);
     $rline .= $line;
   }
   echo " <LI>Updating comment for \"$title\"... ";
   $rline = addslashes($rline);
   if ( $db->query("UPDATE video SET comment='$rline' WHERE id=$movie") ) {
     echo "<SPAN CLASS='ok'>Success.</SPAN></LI>\n"; ++$ucount;
   } else {
     echo "<SPAN CLASS='error'>Failed!</SPAN></LI>\n"; ++$fcount;
   }
 }
 echo "</UL>\n";
 echo "<P>Updated $ucount entries, $fcount updates failed.</P>\n";

 include("inc/footer.inc");
?>