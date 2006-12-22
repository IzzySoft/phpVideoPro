<?
 ##############################################################################
 # phpVideoPro                               (c) 2001-2006 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                           #
 # http://www.qumran.org/homes/izzy/                                          #
 # -------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it       #
 # under the terms of the GNU General Public License (see doc/LICENSE)        #
 # -------------------------------------------------------------------------- #
 # Search IMDB for movie information                                          #
 ##############################################################################

 /* $Id$ */

 #=========================================================[ General setup ]===
 $page_id = "imdbsearch";
 $nomenue = 1;
 include("inc/includes.inc");
 include("inc/header.inc");
 require_once ("inc/class.imdb.inc");
 $imdb_tx_prefs = $pvp->preferences->imdb_tx_get();
 $autoclose = $pvp->preferences->get("imdb_txwin_autoclose");
 if (empty($autoclose)) $autoclose = 0;
 foreach ($imdb_tx_prefs as $var=>$val) {
   ${$var} = $val;
 }
 $vuls = array();
 # Was the movie name given on the main form?
 if (empty($_REQUEST["nsubmit"]) && empty($_REQUEST["isubmit"]) && !empty($_REQUEST["name"])) {
   $auto_search = TRUE;
   if (is_numeric($_REQUEST["name"]) && strlen($_REQUEST["name"])>5) {
     $_REQUEST["mid"] = $_REQUEST["name"];
     $_REQUEST["isubmit"] = 1;
   } else {
     if (!$pvp->common->req_is_alnum("name")) $vuls[] = lang("name_not_string");
     $_REQUEST["nsubmit"] = 1;
   }
 } else {
   vul_alnum("isubmit");
   vul_alnum("nsubmit");
   vul_alnum("reset");
   if (!$pvp->common->req_is_num("mid"))
     $vuls[] = str_replace("\\n"," ",lang("id_is_nan"));
 }
 if ($vc=count($vuls)) {
   $msg = lang("input_errors_occured",$vc) . "<UL>\n";
   for ($i=0;$i<$vc;++$i) {
     $msg .= "<LI>".$vuls[$i]."</LI>\n";
   }
   $msg .= "</UL>";
   $pvp->common->die_error($msg);
 }

 #========================================================[ Template setup ]===
 $t = new Template($pvp->tpl_dir);
 $t->set_file(array("template"=>"imdbsearch.tpl"));
 $t->set_block("template","resultblock","resultlist");
 $t->set_block("resultblock","resitemblock","resultitem");

 $t->set_block("template","movieblock","movie");
 $t->set_block("movieblock","pgblock","pglist");
 $t->set_block("movieblock","acatblock","acatlist");
 $t->set_block("acatblock","catblock","catlist");
 $t->set_block("movieblock","dirblock","dirlist");
 $t->set_block("movieblock","musblock","muslist");
 $t->set_block("movieblock","actblock","actlist");

 $t->set_block("template","queryblock","query");

 $t->set_var("listtitle",lang("imdb_title_search"));
 $t->set_var("formtarget",$_SERVER["PHP_SELF"]);

 if (!empty($_REQUEST["name"]) && !empty($_REQUEST["nsubmit"])) {
 #=================================================[ Get IMDB ID for movie ]===
  $search = new imdbsearch ();
  $search->setsearchname ($_REQUEST["name"]);
  $results = $search->results ();
  $open = FALSE;
  if (empty($results)) { // found nothing on IMDB?
    if ($auto_search) {
      $t->set_var("links","&nbsp;");
    } else {
      $t->set_var("links","<A HREF='JavaScript:history.back()'>".lang("back")."</A>");
    }
    $t->set_var("moviename",lang("imdb_search_empty_result"));
    $t->parse("resultitem","resitemblock");
  } else { // successful search - display result list
    foreach ($results as $res) {
      $moviename = "<a href='".$_SERVER["PHP_SELF"]."?mid=".$res->imdbid()."'>"
             . $res->title()." (".$res->year().")"."</a>";
      $t->set_var("moviename",$moviename);
      $link  = "<a href='http://".$search->imdbsite."/title/tt".$res->imdbid()
             . "' target='_blank'><img src='".$base_url."images/imdb_movie.gif' "
             . "border='0' alt='Open IMDB page'></a>";
      $t->set_var("links",$link);
      $t->parse("resultitem","resitemblock",$open);
      $open = TRUE;
    }
  }
  $t->parse("resultlist","resultblock");
  $t->pparse("out","template");
 } elseif (!empty($_REQUEST["mid"])) {
 #==============================================[ Get movie data from IMDB ]===
   $movieid = $_REQUEST["mid"];
   $movie = new imdb ($movieid);
   $imdbsite = $pvp->preferences->get("imdb_url2");
   $url  = explode("/",$imdbsite);
   $movie->imdbsite = $url[count($url)-2]; // IMDB parse is fixed to English
   $movie->setid ($movieid);
   $t->set_var("mid",$movieid);
   #-=[ Title incl. Also Known As ]=-
   $title  = "<SELECT NAME='title'>";
   $title .= "<OPTION VALUE='".$movie->title()."'>".$movie->title()."</OPTION>";
   foreach ( $movie->alsoknow() as $ak) {
     $akatitle = $ak["title"];
     if (!empty($ak["year"]))    $akatitle .= ": ".$ak["year"];
     if (!empty($ak["country"])) $akatitle .= ", ".$ak["country"];
     if (!empty($ak["comment"])) $akatitle .= " (".$ak["comment"].")";
     $title .= "<OPTION VALUE='".$ak["title"]."'>$akatitle</OPTION>";
   }
   $title .= "</SELECT>";
   $t->set_var("mtitle",$title);
   $t->set_var("title_chk",$pvp->common->make_checkbox("title_chk",$imdb_tx_title));
   #-=[ Country ]=-
   $acountry = $movie->country(); $cc = count($acountry); $country = "";
   for ($i=0;$i+1<$cc;++$i) {
     $country .= $acountry[$i].", ";
   }
   $country .= $acountry[$i];
   $t->set_var("ncountry",lang("country"));
   $t->set_var("mcountry",$country);
   $t->set_var("country_chk",$pvp->common->make_checkbox("country_chk",$imdb_tx_country));
   #-=[ Year ]=-
   $t->set_var("nyear",lang("year"));
   $t->set_var("myear",$movie->year());
   $t->set_var("year_chk",$pvp->common->make_checkbox("year_chk",$imdb_tx_year));
   #-=[ FSK / PG ]=-
   $t->set_var("npg",lang("fsk"));
   $t->set_var("fsk_help","&nbsp;" . $pvp->link->linkhelp("imdbsearch#details"));
   $pga = $movie->mpaa(); $open = FALSE;
   foreach ($pga as $var=>$val) {
     $t->set_var("pgval",$val);
     $t->set_var("mpg","$val ($var)");
     $t->parse("pglist","pgblock",$open);
     $open = TRUE;
   }
   $t->set_var("pg_chk",$pvp->common->make_checkbox("pg_chk",$imdb_tx_pg));
   unset($tpg);
   #-=[ Length ]=-
   $t->set_var("nruntime",lang("length"));
   $t->set_var("mruntime",$movie->runtime());
   $t->set_var("length_chk",$pvp->common->make_checkbox("length_chk",$imdb_tx_length));
   #-=[ Categories ]=-
   $cats = array();
   $t->set_var("ngenre",lang("categories"));
   $gen = $movie->genres(); // split up array and fit into template
   $cc = count($gen); $genre = "";
   for ($i=0;$i+1<$cc;++$i) {
     $genre .= $gen[$i].", ";
     if (strtolower($gen[$i])=="sci-fi") $gen[$i] = "sf";
     if ($cat_id=$db->get_category_id("cat_".strtolower($gen[$i]))) $cats[]=$cat_id;
   }
   $genre .= $gen[$i];
   if (strtolower($gen[$i])=="sci-fi") $gen[$i] = "sf";
   if ($cat_id=$db->get_category_id("cat_".strtolower($gen[$i]))) $cats[]=$cat_id;
   $t->set_var("mgenre",$genre);
   $catlist = $db->get_category(); $cc = count($catlist); $open=FALSE; $done=-1;
   for ($k=0;$k<3;++$k) {
    $t->set_var("catnr",$k+1);
    $t->set_var("cid","");
    $t->set_var("csel","");
    $t->set_var("cname","- ".lang("none")." -");
    $t->parse("catlist","catblock");
    for ($i=0;$i<$cc;++$i) {
      $t->set_var("cid",$catlist[$i]["id"]);
      if (in_array($catlist[$i]["id"],$cats) && $done!=$k) {
        $t->set_var("csel"," SELECTED");
        foreach ($cats as $var=>$val) {
          if ($val==$catlist[$i]["id"]) unset ($cats[$var]);
        }
        $done = $k;
      } else {
        $t->set_var("csel","");
      }
      $t->set_var("cname",$catlist[$i]["name"]);
      $t->parse("catlist","catblock",TRUE);
    }
    $t->parse("acatlist","acatblock",$open);
    $open = TRUE;
   }
   $t->set_var("cat_chk",$pvp->common->make_checkbox("cat_chk",$imdb_tx_cat));
   #-=[ Directors ]=-
   $t->set_var("ndir_name",lang("director"));
   $dir = $movie->director(); // array again - need to select
   $cc = count($dir); $open = FALSE;
   for ($i=0;$i<$cc;++$i) {
    $t->set_var("dir_name",$dir[$i]["name"]); // we also have "imdb" and "role"
    if ($i==0) $t->set_var("dsel"," SELECTED"); else $t->set_var("dsel","");
    $t->parse("dirlist","dirblock",$open);
    $open = TRUE;
   }
   $t->set_var("director_chk",$pvp->common->make_checkbox("director_chk",$imdb_tx_director));
   #-=[ Composer ]=-
   $t->set_var("nmus_name",lang("composer"));
   $music = $movie->composer();
   $cc = count($music);
   $open = FALSE;
   for ($i=0;$i<$cc;++$i) {
    $t->set_var("mus_name",$music[$i]["name"]); // we also have "imdb"
    if ($i==0) $t->set_var("dsel"," SELECTED"); else $t->set_var("dsel","");
    $t->parse("muslist","musblock",$open);
    $open = TRUE;
   }
   $t->set_var("music_chk",$pvp->common->make_checkbox("music_chk",$imdb_tx_music));
   #-=[ Actors ]=-
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
   $t->set_var("actor_chk",$pvp->common->make_checkbox("actor_chk",$imdb_tx_actor));
   #-=[ Ratings and Votings ]=-
#   $t->set_var("mrating",$movie->rating());
#   $t->set_var("mvotes",$movie->votes());
#   $t->set_var("mlanguage",$movie->language());
   #-=[ Misc stuff - maybe for the future ]=-
#   $col = $movie->colors(); // what to do with them?
#   $snd = $movie->sound();  // does not match our formats
#   $tag = $movie->taglines(); // array again - do we need this?
#   $wrt = $movie->writing(); // writing credits - array 0..n like director
#   $prod = $movie->producer(); // same as $wrt
   #-=[ Foto ]=-
   if (($photo_url = $movie->photo_localurl() ) == FALSE) {
     $photo_url = "";
   } else {
     $photo_url = substr($photo_url,strlen($base_url));
#     $t->set_var("mfoto",$photo_url);
     $t->set_var("mfoto_pic","<IMG SRC='$photo_url' ALT='cover' ALIGN='left'>");
   }
   #-=[ Plot = Comments ]=-
   $plot = $movie->plot(); $cc = count($plot);
   if (!empty($photo_url)) $comment = "[img]".$photo_url."[/img]";
     else $comment = "";
   $tagline = trim($movie->tagline());
   if (!empty($tagline)) $comment .= "<B>$tagline</B><BR>";
   for ($i=0;$i<$cc;++$i) { $comment .= $plot[$i]."<BR>\n"; }
   $t->set_var("mcomment",$comment);
   $t->set_var("comments_chk",$pvp->common->make_checkbox("comments_chk",$imdb_tx_comments));
   $t->set_var("btransfer",lang("imdb_transfer2edit"));
   $fskNaN = lang("fsk_is_nan");
   $js = "<SCRIPT TYPE='text/javascript' LANGUAGE='JavaScript'>//<!--
  function name_split(name) {
    pos = name.lastIndexOf(' ');
    if (pos==-1) return name;
    return name.substr(pos+1,500);
  }
  function fname_split(name) {
    pos = name.lastIndexOf(' ');
    if (pos==-1) return '';
    return name.substring(0,pos);
  }
  function transfer_data() {
   omf = opener.document.movieform;
   dmf = document.movieform;
   omf.imdb_id.value = dmf.mid.value;
   if (dmf.pg_chk.checked) {
     if (isNaN(dmf.pg.value)) {
       alert('$fskNaN');
       exit;
     } else {
       omf.fsk.value = dmf.pg.value;
     }
   }
   if (dmf.title_chk.checked)    omf.title.value   = dmf.title.value;
   if (dmf.length_chk.checked)   omf.length.value  = dmf.runtime.value;
   if (dmf.country_chk.checked)  omf.country.value = dmf.country.value;
   if (dmf.year_chk.checked)     omf.year.value    = dmf.year.value;
   if (dmf.comments_chk.checked) omf.comment.value = dmf.comment.value;
   if (dmf.cat_chk.checked) {
     for (i=0;i<omf.cat1_id.length;++i) {
       if (omf.cat1_id.options[i].value==dmf.cat1_id.value) { omf.cat1_id.options[i].selected=1; }
       if (omf.cat2_id.options[i].value==dmf.cat2_id.value) { omf.cat2_id.options[i].selected=1; }
       if (omf.cat3_id.options[i].value==dmf.cat3_id.value) { omf.cat3_id.options[i].selected=1; }
     }
   }
   if (dmf.director_chk.checked) {
     name = dmf.directors.value;
     omf.director_name.value  = name_split(dmf.directors.value);
     omf.director_fname.value = fname_split(dmf.directors.value);
     if (dmf.directors.value != '') omf.director_list.checked=1;
   }
   if (dmf.music_chk.checked) {
     name = dmf.music.value;
     omf.composer_name.value  = name_split(dmf.music.value);
     omf.composer_fname.value = fname_split(dmf.music.value);
     if (dmf.music.value != '') omf.music_list.checked=1;
   }
   if (dmf.actor_chk.checked) {
     k = 1;
     for (i=0;i<dmf.actors.length;++i) {
       if (dmf.actors.options[i].selected) {
         curr  = dmf.actors.options[i].text;
         switch(k) {
           case 1: omf.actor1_name.value = name_split(curr); omf.actor1_fname.value = fname_split(curr); omf.vis_actor1.checked=1; break;
           case 2: omf.actor2_name.value = name_split(curr); omf.actor2_fname.value = fname_split(curr); omf.vis_actor2.checked=1; break;
           case 3: omf.actor3_name.value = name_split(curr); omf.actor3_fname.value = fname_split(curr); omf.vis_actor3.checked=1; break;
           case 4: omf.actor4_name.value = name_split(curr); omf.actor4_fname.value = fname_split(curr); omf.vis_actor4.checked=1; break;
           case 5: omf.actor5_name.value = name_split(curr); omf.actor5_fname.value = fname_split(curr); omf.vis_actor5.checked=1; break;
           default: break;
         }
         ++k;
       }
     }
   }
   if ($autoclose) self.close();
  }
//--></SCRIPT>";
   $t->set_var("js",$js);
   $t->parse("movie","movieblock");
   $t->pparse("out","template");
 } else {
 #=================================================[ Nothing to do for us! ]===
 #---------------------------------------------[ Setup special JavaScript ]---
 $nr_nan = lang("id_is_nan");
 $js = "<SCRIPT TYPE='text/javascript' LANGUAGE='JavaScript'>//<!--
   function check_nr(nr) {
     if (isNaN(nr.value)) {
       nr.value = '';
       alert('$nr_nan');
     }
   }
//--></SCRIPT>";
   $t->set_var("js",$js);
   $t->set_var("reset",lang("reset"));
   $t->set_var("mname",lang("imdb_tx_title"));
   $t->set_var("mid",lang("imdb_movie_id"));
   $t->set_var("submit",lang("submit"));
   $t->parse("query","queryblock");
   $t->pparse("out","template");
 }

 include("inc/footer.inc");
?>
