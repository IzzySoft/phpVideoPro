<? // setup tables for phpVideoPro
  include ("../inc/config.inc");
  
  $title = "phpVideoPro v$version Setup";
?>
<HTML><HEAD>
 <TITLE><? echo $title ?></TITLE>
 <META http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</HEAD>
<BODY>
<H1 ALIGN=CENTER><? echo $title ?></H1>
<P ALIGN=JUSTIFY>At the moment, this is just a "quick'n'dirty" tool to setup the
 database. At some point in the future I may include more functions also here,
 but right now I focus on the main program to make it useful, and consider this
 setup more "cosmetical" (iow, it has a very low priority). So I just built it
 to make it easier for you, the users, to setup the database for now.</P>

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
     by PHP). At this time, only Netscape is tested to work with phpVideoPro
     (probably M$ Internet Exploder will work as well). Konqueror is known
     as <b>not</b> working (version 1.9.8 - higher versions may work but are
     not tested yet) - though it works for this setup program
</OL>

<H3 ALIGN=CENTER>Pre-Requisites</H3>
<P ALIGN=JUSTIFY>If this requirements are met, we can start setting up
 phpVideoPro. To do this, follow these steps:</P>
<OL>
 <LI>edit inc/config.inc to reflect your structures. Don't change anything
     below the hashed line, since these are only global internal settings
     (so if you change something here, you may "break" the program).
     Essential settings you <b>must</b> make sure to reflect your structures
     are:
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
 you can follow this link and <A HREF="create_tables.php">create</A> the tables
 and fill them with initial data (such as categories, sound types etc).
 With some luck (*grin*) you'll get no error message, and have the database
 ready to start with phpVideoPro then. So, if everything worked fine, you
 <b>then</b> can point your browser to phpVideoPro's <A HREF="../">start screen</A>.
 Good luck - and enjoy!</P>
</BODY></HTML>