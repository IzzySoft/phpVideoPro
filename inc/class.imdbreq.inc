<?php
 #############################################################################
 # phpVideoPro                              (c) 2001-2007 by Itzchak Rehberg #
 # written by Itzchak Rehberg <izzysoft AT qumran DOT org>                   #
 # http://www.izzysoft.de/                                                   #
 # ------------------------------------------------------------------------- #
 # This program is free software; you can redistribute and/or modify it      #
 # under the terms of the GNU General Public License (see doc/LICENSE)       #
 # ------------------------------------------------------------------------- #
 # IMDB handling                                                             #
 # ------------------------------------------------------------------------- #
 # Taken from IMDBPHP, (c) by Giorgos Giagas                                 #
 #############################################################################

 /* $Id$ */

 require_once (dirname(__FILE__)."/class.browseremu.inc");
 require_once (dirname(__FILE__)."/class.imdbconf.inc");

 #=========================================================[ IMDB_Request ]===
 /** The request class
  *  Here we emulate a browser accessing the IMDB site. You don't need to
  *  call any of its method directly - they are rather used by the IMDB classes.
  * @package Api
  * @class IMDB_Request
  */
 class IMDB_Request extends BrowserEmulator {
   var $maxsize = 100000;
   /** Constructor: Initialize the BrowserEmulator
    *  No need to call this.
    * @constructor IMDB_Request
    */
   function IMDB_Request($url){
     $this->BrowserEmulator();
     $this->urltoopen = $url;
   }
   /** Send a request to the IMDB site
    * @method sendRequest
    */
   function sendRequest(){
     $this->fpopened = $this->fopen($this->urltoopen);
   }
   /** Get the Response body
    * @method getResponseBody
    */
   function getResponseBody(){
     $page = "";
     while (!feof ($this->fpopened)) {
       $page .= fread ($this->fpopened, 1024);
     }
     return $page;
   }
   /** Set the URL we need to parse
    * @method setURL
    */
   function setURL($url){
     $this->urltoopen = $url;
   }
   /** Obtain the response body
    * @method getresponseheader
    * @param optional string header
    */
   function getresponseheader($header = false){
     $headers = $this->getLastResponseHeaders();
     foreach ($headers as $head){
       if ( is_integer(strpos ($head, $header) )){
         $hstart = strpos ($head, ": ");
         $head = trim(substr($head,$hstart+2,100));
         return $head;
       }
     }
   }
 } // end class IMDB_Request

?>
