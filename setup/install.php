<? // setup tables for phpVideoPro

/* $Id$ */

  include ("../inc/config.inc");
  
  $title = "phpVideoPro Setup: Fresh Installation";
?>
<HTML><HEAD>
 <TITLE><? echo $title ?></TITLE>
 <META http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</HEAD>
<BODY>
<H1 ALIGN=CENTER><? echo $title ?></H1>

<H3 ALIGN=CENTER>Requirements</H3>
<P ALIGN=JUSTIFY>There are a few things you have to make sure first (without
 them the whole program, including this setup, won't work at all):</P>
<OL>
 <LI>have a webserver running (I just tested it with Apache)
 <LI>have PHP running, at least v4.0b3 (a version less than this won't work;
     I recommend using Apache with PHP as loadable module, and that's
     the only combination I've tested)
 <LI>make sure your PHP has MySQL support built in! (if requirements
     1, 2 and 4 are met, click <A HREF="phpinfo.php">here</A> to see what
     features are supported by your PHP setup)
 <LI>point your browser to this page via http (so that this page is parsed
     by PHP). Due to JavaScript problems caused by the menue used for now,
     there are problems with some browsers. So I found following products
     not working properly with it: Konqueror, Opera, Mozilla, and probably
     all other Gecko-based browsers as well (Netscape 6). However, Netscape
     4.7x seems to work fine, and M$ Internet Exploder will probably do this
     job as well. But if you happen to know some good replacement for the
     menue that works with all browsers (and is so nice and easy to handle
     as the one used for now), please tell me - and I'll replace it!<br>
     However, since this setup programm does not make any use of the menu,
     any browser will work for this :)
</OL>

<H3 ALIGN=CENTER>Pre-Requisites</H3>
<P ALIGN=JUSTIFY>If this requirements are met, we can start setting up
 phpVideoPro. To do this, follow these steps:</P>
<OL>
 <LI>edit inc/config.inc to reflect your structures. There are not many
     settings you <b>must</b> check, so this is done fast:
     <ul>
      <li>$base_url : the root directory of your phpVideoPro copy.
          make sure it has a leading slash (i.e. it has to be the complete
          path starting with your web servers document root) as well as a
          trailing slash.
      <li>$database : settings for the database (host running the db server,
          database name, user and password to access the database).
     </ul>
     The other settings you can leave unchanged, they have suitable defaults.
     you may change them in the future if you feel any need to :)
 <LI>create the database with the name you specified in inc/config.inc as
     $database["database"] on the host you configured there. Make sure the
     configured user has at least following privileges for this database:
     Select, Insert, Update, Delete, Create. For future versions (updates),
     the privileges Alter, Drop and References may also be needed.
</OL>

<H3 ALIGN=CENTER>Create the tables</H3>
<P ALIGN=JUSTIFY>If all above mentioned requirements pre-requisites are met,
 you can follow this link to <A HREF="create_tables.php">create</A> the tables
 and fill them with initial data (such as categories, sound types etc).
 With some luck (*grin*) you'll get no error message, and have the database
 ready to start with phpVideoPro then. So, if everything worked fine, you
 <b>then</b> can point your browser to phpVideoPro's <A HREF="../">start screen</A>.
 Good luck - and enjoy!</P>
</BODY></HTML>