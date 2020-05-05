<?php
##############################################################################
# phpVideoPro                               (c) 2001-2020 by Itzchak Rehberg #
# written by Itzchak Rehberg <izzysoft AT qumran DOT org>                    #
# https://www.izzysoft.de/                                                   #
# -------------------------------------------------------------------------- #
# This program is free software; you can redistribute and/or modify it       #
# under the terms of the GNU General Public License (see doc/LICENSE)        #
# -------------------------------------------------------------------------- #
# Search IMDB for movie information                                          #
##############################################################################

#===============================================[ IMDB class configuration ]===
function config_dirs(&$inst) {
  GLOBAL $pvp,$base_path,$base_url,$db;
  /* disabled: cache is now configured via IMDBPHP's own config
   * (we need to remove the corresponding parts from PVP; only keep
   * store/usecache to override)
  $cachedir = $db->get_config("imdb_cache_dir");
  if ($pvp->config->os_slash == "\\") $cachedir = str_replace("\\","/",$cachedir);
  if (strpos($cachedir,"/")!==0) $cachedir = $base_path.$cachedir;
  if (strrpos($cachedir,"/")!=strlen($cachedir)-1) $cachedir .= "/";
  $inst->cachedir = $cachedir;
  $inst->cache_expire = $db->get_config("imdb_cache_expire");
  */
  $inst->storecache = $db->get_config("imdb_cache_enable");
  $inst->usecache = $db->get_config("imdb_cache_use");
  $inst->photodir = $pvp->config->imdb_photopath;
  $inst->photoroot = $pvp->config->imdb_photourl;
}

function config_imdb(&$inst) {
  GLOBAL $pvp;
  $imdbsite = $pvp->preferences->get("imdb_url");
  $url  = explode("/",$imdbsite);
  $inst->imdbsite = $url[count($url)-2];
  config_dirs($inst);
}

function match_genre(&$genre,$class) {
  static $imdb = array('Sci-Fi'=>'sf');
  if (in_array($genre,array_keys($imdb))) $genre = $imdb[$genre];
}

function get_data(&$movie) {
  $data = new stdClass();
  $data->title    = $movie->title();
  $data->akas     = $movie->alsoknow();
  $data->country  = $movie->country();
  $data->year     = $movie->year();
  $data->mpaa     = $movie->mpaa();
  $data->runtime  = $movie->runtime();
  $data->genres   = $movie->genres();
  $data->director = $movie->director();
  $data->cast     = $movie->cast();
  $data->rating   = $movie->rating();
  $data->photo    = $movie->photo_localurl();
  $data->plotoutline = $movie->plotoutline();
  $data->plot   = $movie->plot();
  $data->tagline  = $movie->tagline();
  return $data;
}

function merge_data(&$data1,$data2) {
  if ($data1->title != $data2->title) $data1->akas[] = array("title"=>$data2->title,"year"=>$data1->year,"country"=>"","comment"=>"");
  foreach ($data2->akas as $aka) if ( !in_array($aka,$data1->akas) ) $data1->akas[] = $aka;
  foreach ($data2->country as $country) if ( !in_array($country,$data1->country) ) $data1->country[] = $country;
  if ( empty($data1->year) ) $data1->year = $data2->year;
  // $data->mpaa does not need merge, since only available from IMDB
  if ( empty($data1->runtime) ) $data1->runtime = $data2->runtime;
  foreach ($data2->genres as $genre) if ( !in_array($genre,$data1->genres) ) $data1->genres[] = $genre;
  foreach ($data2->director as $dir) {
    $found = FALSE;
    foreach ($data1->director as $dir1) {
      if ( empty($dir['imdb']) ) {
        if ( $dir['name']==$dir1['name'] ) { $found = TRUE; break; }
      } else {
        if ( $dir['imdb'] == $dir1['imdb'] ) { $found = TRUE; break; }
      }
    }
    if ( !$found ) $data1->director[] = $dir;
  }
  foreach ($data2->cast as $cast) {
    $found = FALSE;
    foreach ($data1->cast as $cast1) {
      if ( empty($cast['imdb']) ) {
        if ( $cast['name'] == $cast1['name'] ) { $found = TRUE; break; }
      } else {
        if ( $cast['imdb'] == $cast1['imdb'] ) { $found = TRUE; break; }
      }
    }
    if ( !$found ) $data1->cast[] = $cast;
  }
  if ( empty($data1->rating) )  $data1->rating = $data2->rating;
  if ( empty($data1->photo) )   $data1->photo = $data2->photo;
  if ( empty($data1->plotoutline) ) $data1->plotoutline = $data2->plotoutline;
  foreach ($data2->plot as $plot) if ( !in_array($plot,$data1->plot) ) $data1->plot[] = $plot;
  if ( empty($data1->tagline) ) $data1->tagline = $data2->tagline;
}

#==========================================================[ General setup ]===
$page_id = "imdbsearch";
$nomenue = 1;
require_once("inc/includes.inc");
require_once("inc/header.inc");
$imdbapi_gen = imdbapi_ver();
$mdb_use = $pvp->preferences->get('mdb_use');
if ($imdbapi_gen<1) {
  display_error( lang("imdbapi_not_installed") );
  exit;
} elseif ($mdb_use<1) {
  display_error( lang("imdbapi_disabled") );
  exit;
}
$imdb_lang = $pvp->preferences->get("imdb_lang");

#===============================================================[ VulCheck ]===
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

#=========================================================[ Template setup ]===
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

#==========================================================[ IMDBAPI setup ]===
$imdb_tx_prefs = $pvp->preferences->imdb_tx_get();
$autoclose = $pvp->preferences->get("imdb_txwin_autoclose");
if (empty($autoclose)) $autoclose = 0;
foreach ($imdb_tx_prefs as $var=>$val) {
  ${$var} = $val;
}

if (!empty($_REQUEST["name"]) && !empty($_REQUEST["nsubmit"])) {
#==================================================[ Get IMDB ID for movie ]===
  require_once($pvp->config->imdb_api_path . '/bootstrap.php');
  $iconfig = new \Imdb\Config();
  if ( !empty($imdb_lang) ) $iconfig->language = $imdb_lang;
  $search = new \Imdb\TitleSearch($iconfig);
  config_imdb($search);
  if ($_REQUEST["epsearch"]) $search->search_episodes(TRUE);
  $results = $search->search($_REQUEST["name"]);
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
      $mid = $res->imdbid();
      $moviename = "<a href='".$_SERVER["PHP_SELF"]."?mid=$mid'>"
             . $res->title()." (".$res->year().")"."</a>";
      $t->set_var("moviename",$moviename);
      $link  = "<a href='http://".$search->imdbsite."/title/tt${mid}"
             . "' target='_blank'><img src='".$base_url."images/imdb_movie.gif' "
             . "border='0' alt='Open IMDB page'></a>";
      $t->set_var("links",$link);
      $t->parse("resultitem","resitemblock",$open);
      $open = TRUE;
      $url1 = $pvp->preferences->get("imdb_url");
      $url2 = $pvp->preferences->get("imdb_url2");
      if ($url1 != $url2) { // Cached version may have language != EN (parse probs!)
        $cachefile = $search->cachedir."${mid}.Title";
        if (file_exists($cachefile)) unlink($cachefile);
      }
    }
  }
  $t->parse("resultlist","resultblock");
  $t->pparse("out","template");

} elseif (!empty($_REQUEST["mid"])) {
#================================================[ Get movie data from MDB ]===
# $mdb_use: 0 = None, 1 = IMDB (in the past also: 2 = MoviePilot, 3 = both)
  $movieid = $_REQUEST["mid"];
  if ( $mdb_use==1 && $imdbapi_gen>0 ) {
    require_once($pvp->config->imdb_api_path . '/bootstrap.php');
    $iconfig = new \Imdb\Config();
    if ( !empty($imdb_lang) ) $iconfig->language = $imdb_lang;
    $movie = new \Imdb\Title($movieid,$config); // !*!
    config_imdb($movie);
    $imdbsite = $pvp->preferences->get("imdb_url2");
    $url = explode("/",$imdbsite);
    $movie->imdbsite = $url[count($url)-2]; // IMDB parse is fixed to English
    $data = get_data($movie);
  }
  if ( $mdb_use==3 ) merge_data($data,$data1);
  $t->set_var("mid",$movieid);
  $hiddenvals = "";
  #-=[ Title incl. Also Known As ]=-
  $title  = "<SELECT NAME='title'>";
  $title .= "<OPTION VALUE='".$data->title."'>".$data->title."</OPTION>";
  if (!empty( $data->akas )) foreach ( $data->akas as $ak) {
    $style = "";
    $akatitle = $ak["title"];
    if (!empty($ak["year"]))    $akatitle .= ": ".$ak["year"];
    if (!empty($ak["country"])) $akatitle .= ", ".$ak["country"];
    if (empty($ak["lang"])) { if (!empty($ak["comment"])) $akatitle .= " (".$ak["comment"].")"; }
    else {
      if (!empty($ak["comment"])) $akatitle .= ", ".$ak["comment"];
      $akatitle .= " [".$ak["lang"]."]";
      if ($ak["lang"]==$pvp->preferences->get("lang")) $style="STYLE='background-color:#ddf;'";
    }
    $title .= "<OPTION VALUE='".$ak["title"]."' $style>$akatitle</OPTION>";
  }
  $title .= "</SELECT>";
  $t->set_var("mtitle",$title);
  $t->set_var("title_chk",$pvp->common->make_checkbox("title_chk",$imdb_tx_title));
  #-=[ Country ]=-
  $cc = count($data->country); $country = "";
  for ($i=0;$i+1<$cc;++$i) {
    $country .= $data->country[$i].", ";
  }
  $country .= $data->country[$i];
  $t->set_var("ncountry",lang("country"));
  $t->set_var("mcountry",$country);
  $t->set_var("country_chk",$pvp->common->make_checkbox("country_chk",$imdb_tx_country));
  #-=[ Year ]=-
  $t->set_var("nyear",lang("year"));
  $t->set_var("myear",$data->year);
  $t->set_var("year_chk",$pvp->common->make_checkbox("year_chk",$imdb_tx_year));
  #-=[ FSK / PG ]=-
  $t->set_var("npg",lang("fsk"));
  $t->set_var("fsk_help","&nbsp;" . $pvp->link->linkhelp("imdbsearch#details"));
  $open = FALSE;
  foreach ($data->mpaa as $var=>$val) {
    $t->set_var("pgval",$val);
    $t->set_var("mpg","$val ($var)");
    $t->parse("pglist","pgblock",$open);
    $open = TRUE;
  }
  $t->set_var("pg_chk",$pvp->common->make_checkbox("pg_chk",$imdb_tx_pg));
  #-=[ Length ]=-
  $t->set_var("nruntime",lang("length"));
  $t->set_var("mruntime",$data->runtime);
  $t->set_var("length_chk",$pvp->common->make_checkbox("length_chk",$imdb_tx_length));
  #-=[ Categories ]=-
  $cats = array();
  $t->set_var("ngenre",lang("categories"));
  $gen = $data->genres; // split up array and fit into template
  $cc = count($gen); $genre = "";
   for ($i=0;$i<$cc;++$i) {
     $genre .= $gen[$i].", ";
     if ($gen[$i]=="Sci-Fi") $gen[$i] = "sf";
     //match_genre($gen[$i],get_class($movie));
     $cat_id=$db->get_category_id("cat_".strtolower($gen[$i]));
     if (!empty($cat_id)) $cats[]=$cat_id;
  }
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
  $dir = $data->director; // array again - need to select
  $cc = count($dir); $open = FALSE;
  for ($i=0;$i<$cc;++$i) {
    $t->set_var("dir_name",$dir[$i]["name"]); // we also have "imdb" and "role"
    if ($i==0) $t->set_var("dsel"," SELECTED"); else $t->set_var("dsel","");
    $t->parse("dirlist","dirblock",$open);
    $hiddenvals .= "<INPUT TYPE='hidden' NAME='director_mid_$i' VALUE='".$dir[$i]["imdb"]."'>";
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
    $hiddenvals .= "<INPUT TYPE='hidden' NAME='music_mid_$i' VALUE='".$music[$i]["imdb"]."'>";
    $open = TRUE;
  }
  $t->set_var("music_chk",$pvp->common->make_checkbox("music_chk",$imdb_tx_music));
  #-=[ Actors ]=-
  $cast = $data->cast; // here come the actors
  $cc = count($cast);
  $open = FALSE;
  $t->set_var("actors",lang("actors"));
  for ($i=0;$i<$cc;++$i) {
    $t->set_var("aname",$cast[$i]["name"]); // we also have "imdb"
    if ($i<5) $t->set_var("asel"," SELECTED"); else $t->set_var("asel","");
    $t->parse("actlist","actblock",$open);
    $hiddenvals .= "<INPUT TYPE='hidden' NAME='actor_mid_$i' VALUE='".$cast[$i]["imdb"]."'>";
    $open = TRUE;
  }
  $t->set_var("actor_chk",$pvp->common->make_checkbox("actor_chk",$imdb_tx_actor));
  #-=[ Ratings and Votings ]=-
  $t->set_var("rating_chk",$pvp->common->make_checkbox("rating_chk",$imdb_tx_rating));
  $t->set_var("nrating",lang("rating"));
  $t->set_var("mrating",$data->rating);
#  $t->set_var("mvotes",$movie->votes());
#  $t->set_var("mlanguage",$movie->language());
  #-=[ Misc stuff - maybe for the future ]=-
#  $col = $movie->colors(); // what to do with them?
#  $snd = $movie->sound();  // does not match our formats
#  $tag = $movie->taglines(); // array again - do we need this?
#  $wrt = $movie->writing(); // writing credits - array 0..n like director
#  $prod = $movie->producer(); // same as $wrt
  #-=[ Foto ]=-
  if (($data->photo ) == FALSE) {
    $photo_url = "";
  } else {
    $photo_url = substr($data->photo,strlen($base_url));
#    $t->set_var("mfoto",$photo_url);
    $t->set_var("mfoto_pic","<IMG SRC='$photo_url' ALT='cover' ALIGN='left'>");
  }
  #-=[ Plot = Comments ]=-
  $plotoutline = $data->plotoutline;
  $plot = $data->plot; $cc = count($plot);
  if (!empty($photo_url)) $comment = "[img]".$photo_url."[/img]";
    else $comment = "";
  $tagline = trim($data->tagline);
  if (!empty($tagline)) $comment .= "<B>$tagline</B><BR>\n";
  if (!empty($plotoutline)) $comment .= "$plotoutline<BR>\n";
  for ($i=0;$i<$cc;++$i) { $comment .= $plot[$i]."<BR>\n"; }
  $t->set_var("mcomment",$comment);
  $t->set_var("comments_chk",$pvp->common->make_checkbox("comments_chk",$imdb_tx_comments));
  $t->set_var("btransfer",lang("imdb_transfer2edit"));
  $fskNaN = lang("fsk_is_nan");
  $ratNaN = lang("rating_is_nan");
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
   if (dmf.rating_chk.checked) {
     if (isNaN(dmf.rating.value)) {
       alert('$ratNaN');
       exit;
     } else {
       omf.rating.value = dmf.rating.value;
     }
   }

   if (omf.useEditor[0].checked) {
     opener.MyNic.removeInstance('comment');
     editorSwitched = 1;
   } else {
     editorSwitched = 0;
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
   var pidx = 0;
   if (dmf.director_chk.checked) {
     name = dmf.directors.value;
     omf.director_name.value  = name_split(dmf.directors.value);
     omf.director_fname.value = fname_split(dmf.directors.value);
     eval('omf.director_imdbid.value = dmf.director_mid_' + dmf.directors.selectedIndex + '.value');
     if (dmf.directors.value != '') omf.director_list.checked=1;
   }
   if (dmf.music_chk.checked) {
     name = dmf.music.value;
     omf.composer_name.value  = name_split(dmf.music.value);
     omf.composer_fname.value = fname_split(dmf.music.value);
     eval('omf.composer_imdbid.value = dmf.music_mid_' + dmf.music.selectedIndex + '.value');
     if (dmf.music.value != '') omf.music_list.checked=1;
   }
   if (dmf.actor_chk.checked) {
     k = 1;
     for (i=0;i<dmf.actors.length;++i) {
       if (dmf.actors.options[i].selected) {
         curr  = dmf.actors.options[i].text;
         switch(k) {
           case 1: omf.actor1_name.value = name_split(curr); omf.actor1_fname.value = fname_split(curr); omf.vis_actor1.checked=1; eval('omf.actor1_imdbid.value=dmf.actor_mid_' + i + '.value'); break;
           case 2: omf.actor2_name.value = name_split(curr); omf.actor2_fname.value = fname_split(curr); omf.vis_actor2.checked=1; eval('omf.actor2_imdbid.value=dmf.actor_mid_' + i + '.value'); break;
           case 3: omf.actor3_name.value = name_split(curr); omf.actor3_fname.value = fname_split(curr); omf.vis_actor3.checked=1; eval('omf.actor3_imdbid.value=dmf.actor_mid_' + i + '.value'); break;
           case 4: omf.actor4_name.value = name_split(curr); omf.actor4_fname.value = fname_split(curr); omf.vis_actor4.checked=1; eval('omf.actor4_imdbid.value=dmf.actor_mid_' + i + '.value'); break;
           case 5: omf.actor5_name.value = name_split(curr); omf.actor5_fname.value = fname_split(curr); omf.vis_actor5.checked=1; eval('omf.actor5_imdbid.value=dmf.actor_mid_' + i + '.value'); break;
           default: break;
         }
         ++k;
       }
     }
   }

   if (editorSwitched==1) {
     opener.loadEditor();
   }
   if ($autoclose) self.close();
  }
//--></SCRIPT>";
  $t->set_var("js",$js);
  $t->set_var("hiddenvals",$hiddenvals);
  $t->parse("movie","movieblock");
  $t->pparse("out","template");
} else {
#==================================================[ Nothing to do for us! ]===
#-----------------------------------------------[ Setup special JavaScript ]---
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
  $t->set_var("epname",lang("episode"));
  $t->set_var("submit",lang("submit"));
  $t->parse("query","queryblock");
  $t->pparse("out","template");
}

include("inc/footer.inc");
?>
