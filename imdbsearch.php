<?
 ##############################################################################
 # phpVideoPro                               (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                           #
 # http://www.qumran.org/homes/izzy/                                          #
 # -------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it       #
 # under the terms of the GNU General Public License (see doc/LICENSE)        #
 # -------------------------------------------------------------------------- #
 # Search IMDB for movie information                                          #
 ##############################################################################

 /* $Id$ */

# $page_id = "search_imdb";
 include("inc/includes.inc");
 include("inc/header.inc");
 require_once ("inc/class.imdb.inc");
 $usecache = TRUE;

 #========================================================[ Template setup ]===
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"imdbsearch.tpl"));
 $t->set_block("template","resultblock","resultlist");
 $t->set_block("resultblock","resitemblock","resultitem");

 $t->set_block("template","movieblock","movie");
 $t->set_block("movieblock","pgblock","pglist");
 $t->set_block("movieblock","dirblock","dirlist");
 $t->set_block("movieblock","actblock","actlist");

 $t->set_var("listtitle",lang("imdb_title_search"));

 if (isset($_REQUEST["name"])) {
 #=================================================[ Get IMDB ID for movie ]===
  $search = new imdbsearch ();
  $search->usecache   = $usecache;
  $search->storecache = $usecache;
  $search->setsearchname ($HTTP_GET_VARS["name"]);
  $results = $search->results ();
  $open = FALSE;
  foreach ($results as $res) {
    $t->set_var("movie",$res->title()." (".$res->year().")");
    $links = "<a href='".$_SERVER["PHP_SELF"]."?mid=".$res->imdbid()."'>Details</a>"
           . "&nbsp;"
           . "<a href='http://".$search->imdbsite."/title/tt".$res->imdbid()
           . "'>imdb page</a>";
    $t->set_var("links",$links);
    $t->parse("resultitem","resitemblock",$open);
    $open = TRUE;
  }
  $t->parse("resultlist","resultblock");
  $t->pparse("out","template");
 } elseif (isset($_REQUEST["mid"])) {
 #==============================================[ Get movie data from IMDB ]===
   $movieid = $_REQUEST["mid"];
   $movie = new imdb ($movieid);
   $movie->imdbsite="us.imdb.com"; // IMDB parse is fixed to English
   $movie->usecache   = $usecache;
   $movie->storecache = $usecache;
   $movie->setid ($movieid);
   $t->set_var("mtitle",$movie->title());
   $t->set_var("nyear",lang("year"));
   $t->set_var("myear",$movie->year());
   if (($photo_url = $movie->photo_localurl() ) == FALSE) {
     $photo_url = "";
   } else {
     $photo_url = substr($photo_url,strlen($base_url));
#     $t->set_var("mfoto",$photo_url);
     $t->set_var("mfoto_pic","<IMG SRC='$photo_url' ALT='cover' ALIGN='left'>");
   }
   $aka = "";
   foreach ( $movie->alsoknow() as $ak) {
     $aka .= $ak["title"].": ".$ak["year"].", ".$ak["country"]." (".$ak["comment"].")<BR>";
   }
   $t->set_var("maka",$aka);
   $t->set_var("nruntime",lang("length"));
   $t->set_var("mruntime",$movie->runtime());
#   $t->set_var("mrating",$movie->rating());
#   $t->set_var("mvotes",$movie->votes());
#   $t->set_var("mlanguage",$movie->language());
   $acountry = $movie->country(); $cc = count($acountry); $country = "";
   for ($i=0;$i+1<$cc;++$i) {
     $country .= $acountry[$i].", ";
   }
   $country .= $acountry[$i];
   $t->set_var("ncountry",lang("country"));
   $t->set_var("mcountry",$country);
   $t->set_var("npg",lang("fsk"));
   $pga = $movie->mpaa(); $open = FALSE;
   foreach ($pga as $var=>$val) {
     $t->set_var("pgval",$val);
     $t->set_var("mpg","$val ($var)");
     $t->parse("pglist","pgblock",$open);
     $open = TRUE;
   }
   $t->set_var("ngenre",lang("categories"));
   $t->set_var("mgenre",$movie->genre());
#   $gen = $movie->genres(); // split up array and fit into template
#   $col = $movie->colors(); // what to do with them?
#   $snd = $movie->sound();  // does not match our formats
#   $t->set_var("mtagline",$movie->tagline());
#   $tag = $movie->taglines(); // array again - do we need this?
   $t->set_var("ndir_name",lang("director"));
   $dir = $movie->director(); // array again - need to select
   $cc = count($dir); $open = FALSE;
   for ($i=0;$i<$cc;++$i) {
    $t->set_var("dir_name",$dir[$i]["name"]); // we also have "imdb" and "role"
    if ($i==0) $t->set_var("dsel"," SELECTED"); else $t->set_var("dsel","");
    $t->parse("dirlist","dirblock",$open);
    $open = TRUE;
   }
   $t->set_var("dir_name","");
   $t->set_var("dsel","");
   $t->parse("dirlist","dirblock",$open);
#   $wrt = $movie->writing(); // writing credits - array 0..n like director
#   $prod = $movie->producer(); // same as $wrt
   $cast = $movie->cast(); // here come the actors
   $cc = count($cast);
   $open = FALSE;
   $t->set_var("actors",lang("actors"));
   for ($i=0;$i<$cc;++$i) {
     $t->set_var("aname",$cast[$i]["name"]); // we also have "imdb"
     if ($i<5) $t->set_var("asel"," SELECTED"); else $t->set_var("asel","");
     $t->parse("actlist","actblock",$open);
     $open = TRUE;
   }
   $plot = $movie->plot(); $cc = count($plot);
   if (!empty($photo_url)) $comment = "[img]".$photo_url."[/img]";
     else $comment = "";
   for ($i=0;$i<$cc;++$i) { $comment .= $plot[$i]."<BR>\n"; }
   $t->set_var("mcomment",$comment);
   $t->parse("movie","movieblock");
   $t->pparse("out","template");
 } else {
 #=================================================[ Nothing to do for us! ]===
   echo "<P><BR></P>Got NO DATA - nothing to do<br>";
 }

 include("inc/footer.inc");
?>
