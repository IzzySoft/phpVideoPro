<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2004 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft@qumran.org>                          #
 # http://www.qumran.org/homes/izzy/                                         #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # Controls for long lists split into parts based on user-specified limit    #
 #############################################################################

 /* $Id$ */

 /** Controls for long lists split into parts based on user-specified limit
  * @package Api
  * @class nextmatch
  * @author Izzy (izzysoft@qumran.org)
  * @copyright (c) 2002 by Itzchak Rehberg and IzzySoft
  */
 class nextmatch {
   VAR $totals, $start, $limit,      // total records, startpoint and limit
       $list,$listcount,             // array/count of retrieved data
       $first, $left, $right, $last, // controls
       $script,                      // target script name to link to
       $img_dir,                     // image directory for controls
       $prev_exists, $next_exists;   // is there a prev/next page?

   /** Constructor: initializes base properties plus creates all data
    *  (all other methods are private and not to be called directly,
    *  therefore they are not documented here ;)
    * @constructor nextmatch
    * @param string query SQL statement
    * @param string tpl_dir template directory
    * @param optional string script target script name to link to
    * @param optional integer start start with dataset x (skip all earlier)
    */
   function nextmatch($query,$tpl_dir,$script="",$start=0) { // init
     GLOBAL $db, $pvp, $base_path, $base_url;
     $this->list = eval("return($query);");
     $this->listcount = count($this->list) -1;
     $this->totals = $this->list['totals'];
     $this->start  = $start;
     $this->limit  = $pvp->preferences->get("display_limit");
     if (!strlen(trim($script))) $script = $_SERVER["PHP_SELF"];
     $this->script = $pvp->link->slink($script);
     if (!strpos($this->script,"?")) $this->script .= "?";
     $tpl_dir = str_replace($base_path,$base_url,$tpl_dir);
     $this->img_dir = $tpl_dir . "/images";
     $this->next_exists = $this->totals > $start + $this->limit;
     $this->prev_exists = $start;
     $this->create_controls();
   }

   ############################################################################
   # create the controls
   function create_controls() {
     if ($this->prev_exists) { // is there any previous page?
       $this->first_normal();
       $this->left_normal();
     } else {
       $this->first_grey();
       $this->left_grey();
     }
     if ($this->next_exists) { // is there any next page?
       $this->right_normal();
       $this->last_normal();
     } else {
       $this->right_grey();
       $this->last_grey();
     }
   }

   ############################################################################
   # "blind" controls
   function first_grey() {
     $this->first = "<IMG SRC='" . $this->img_dir . "/first-grey.gif' BORDER=0>";
   }
   function left_grey() {
     $this->left  = "<IMG SRC='" . $this->img_dir . "/left-grey.gif' BORDER=0>";
   }
   function right_grey() {
     $this->right  = "<IMG SRC='" . $this->img_dir . "/right-grey.gif' BORDER=0>";
   }
   function last_grey() {
     $this->last  = "<IMG SRC='" . $this->img_dir . "/last-grey.gif' BORDER=0>";
   }

   ############################################################################
   # functional controls
   function first_normal() {
     $this->first = "<A HREF='" . $this->script .
          "'><IMG SRC='" . $this->img_dir . "/first.gif' BORDER=0></A>";
   }
   function left_normal() {
     $start = $this->start - $this->limit;
     if ($start < 0) $start = 0;
     $url = $this->clean_url($this->script . "&start=$start");
     $this->left = "<A HREF='$url'><IMG SRC='" . $this->img_dir . "/left.gif' BORDER=0></A>";
   }
   function right_normal() {
     $url = $this->clean_url($this->script . "&start=" . ($this->start+$this->limit));
     $this->right = "<A HREF='$url'><IMG SRC='" . $this->img_dir . "/right.gif' BORDER=0></A>";
   }
   function last_normal() {
     $end = $this->totals % $this->limit;
     if (!$end) $end = $this->limit;
     $url = $this->clean_url($this->script . "&start=" . ($this->totals - $end));
     $this->last  = "<A HREF='$url'><IMG SRC='" . $this->img_dir . "/last.gif' BORDER=0></A>";
   }

   ############################################################################
   # cleanup URL (replace all "?&" accidentally created)
   function clean_url($url) {
     return str_replace("?&","?",$url);
   }

 } // end class nextmatch

 /** Total records found
  * @class nextmatch
  * @attribute integer totals
  */
 /** Startpoint of selected subset
  * @class nextmatch
  * @attribute integer start
  */
 /** Selection limit
  * @class nextmatch
  * @attribute integer limit
  */
 /** List of selected subset
  * @class nextmatch
  * @attribute array list
  */
 /** Count of selected subsets data
  * @class nextmatch
  * @attribute integer listcount
  */
 /** Controls: link to first page
  * @class nextmatch
  * @attribute integer first
  */
 /** Controls: link to previous page
  * @class nextmatch
  * @attribute integer left
  */
 /** Controls: link to next page
  * @class nextmatch
  * @attribute integer right
  */
 /** Controls: link to last page
  * @class nextmatch
  * @attribute integer last
  */
 /** Target script name to link to
  * @class nextmatch
  * @attribute integer script
  */
 /** Image directory for controls
  * @class nextmatch
  * @attribute integer img_dir
  */
 /** Is there a prev page?
  * @class nextmatch
  * @attribute integer prev_exists
  */
 /** Is there a next page?
  * @class nextmatch
  * @attribute integer next_exists
  */

?>