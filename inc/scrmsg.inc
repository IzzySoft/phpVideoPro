<?php

  /* $Id$ */

  /***************************************************************************\
  * ScrMsg  (Screen Message funcs for PHP)   (c) 2001 by eInsurance AG Munich *
  * written by Itzchak Rehberg <itzchak.rehberg@einsurance.de>                *
  * ---------------------------------------------------                       *
  * common functions needed in many applications, souch as colored output     *
  * generator, debug functions a.s.o.                                         *
  *****************************************************************************
  * Functions available                                                       *
  * -------------------                                                       *
  * scrmsg([$debuglevel])  : The constructor takes one optional parameter to  *
  *                          set up the debug levels supported. This string   *
  *                          is just an arbitrary combination of chars, where *
  *                          each char represents one debug level. If you     *
  *                          ommit this parameter, default setting is "E" for *
  *                          "errors". Suggestion: "W" for "warnings", "D"    *
  *                          for "database"... All given debuglevels will use *
  *                          color type "err" as output color - you can change*
  *                          this by calling scrmsg->debugcolor for each      *
  *                          affected debug level.                            *
  * scrmsg->debuglevel([$level]) : Read or set the debug levels supported. If *
  *                          you ommit the optional parameter, the function   *
  *                          returns the string of supported debug levels. If *
  *                          you pass it a string ($level), the list of debug *
  *                          levels are set to it (see constructor above).    *
  *                          As the constructor does, this method sets the    *
  *                          output color of newly added debug levels to color*
  *                          type err. Debug color values that already existed*
  *                          before calling this function are not overwritten.*
  * scrmsg->color($type[,$color]) : reads or sets a color. Per default, there *
  *                          are following colors set ($type=$color):         *
  *                          err=#FF0000 (red), default=#0000FF (blue). You   *
  *                          can set up as much colors as you want, e.g. to   *
  *                          use them with function output, see below.        *
  * scrmsg->debugcolor     : as described for function color, but for debug   *
  *                          function. $type must equal the debug level it is *
  *                          assigned to - so debugcolor("e","#00FF00") would *
  *                          cause all messages for debuglevel "e" to be put  *
  *                          on screen in light green color. By default, the  *
  *                          color for each debug level is set to             *
  *                          scrmsg->color("err").                            *
  * scrmsg->output($msg[,$color]) : outputs (echoes) string $msg using above  *
  *                          discussed default color or, if optional argument *
  *                          $color specified, by the color $color previously *
  *                          defined with above discussed color() function.   *
  *                          If an undefined color is specified, $msg is      *
  *                          echoed without any color specifications.         *
  * scrmsg->debug($level,$msg) : checks if $level is contained in the list of *
  *                          defined debug levels. If so, $msg is put out     *
  *                          using the color assigned to the debug level.     *
  *                          Otherwise, no action is taken. An example: if    *
  *                          you define debuglevel("esw") and then call       *
  *                          debug("s","Some SQL error appeared"), this $msg  *
  *                          would be put to screen with debugcolor("s"). But *
  *                          if you call debug("v","Variable not set!) - this *
  *                          call is simply "ignored" and nothing put out.    *
  \***************************************************************************/

  class scrmsg {
  
    VAR $debuglevel, $colors, $debugcolors;

    ###########################################################################
    # constructor - set up defaults
    function scrmsg($debuglevel="") {
      if ( $debuglevel ) { $this->debuglevel = $debuglevel; } else { $this->debuglevel = "E"; }
      $this->color("err","#FF0000");
      $this->color("default","#0000FF");
      $this->init_debuglevels($debuglevel);
    }
    
    ###########################################################################
    # init colors for debuglevels
    function init_debuglevels($debuglevel) {
      for ($i=0;$i<strlen($debuglevel);$i++) {
        $level = substr($debuglevel,$i,1);
        if ( strlen($this->debugcolor($level)) ) continue; // do not overwrite "manually" set colors
        $this->debugcolor($level,$this->colors->err);
      }
    }

    ###########################################################################
    # debuglevel - read or set the debug level
    function debuglevel($level="") {
      if ( $level=="" ) { return $this->debuglevel;
      } else {
        $this->debuglevel = $level;
        $this->init_debuglevels($level);
      }
    }

    ###########################################################################
    # color - read or change the default colors
    function color($type,$color="") {
      if ( $color=="" ) {
        return $this->colors->$type;
      } else {
        $this->colors->$type = $color;
        return;
      }
    }

    ###########################################################################
    # debugcolor - read or change the debug colors
    function debugcolor($type,$color="") {
      $type = strtolower($type);
      if ( $color=="" ) {
        return $this->debugcolors->$type;
      } else {
        $this->debugcolors->$type = $color;
        return;
      }
    }

    ###########################################################################
    # output - output formatted msg string
    function output($msg,$color="") {
      if ( $color=="" ) { $color = $this->colors->default;
      } else { $color = $this->colors->$color; }
      if ( $color=="" ) { //still not set - since undefined color specified
        echo $msg;
      } else {
        echo "<FONT COLOR=\"$color\">$msg</FONT>";
      }
    }

    ###########################################################################
    # putmsg - output formatted msg string
    function putmsg($msg,$color) {
      echo "<FONT COLOR=\"$color\">$msg</FONT>";
    }

    ###########################################################################
    # debug - generate debug output depending on debug level
    function debug($level,$msg) {
      $level = strtolower($level);
      if ( strpos(strtolower($this->debuglevel),$level)===false ) return;
      $msg .= "<BR>\n";
      if ($this->debugcolors->$level) { $color = $this->debugcolors->$level;
      } else { $color = $this->colors->default; }
      $this->putmsg($msg,$color);
      return;
    }

  }

?>