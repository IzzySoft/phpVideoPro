<? /* About */

  $page_id = "about";
  include("inc/header.inc");

?>

<H2 Align=Center>About phpVideoPro</H2>

<Table Width=90% Align=Center>
 <TR><TD>
  <P Align=Justify>This is phpVideoPro version <? echo $version ?>, (c) 2001 by
   Itzchak Rehberg, all rights (and links) reserved. It's my try to port the best video
   management software I've ever found, VideoPro (c) Bernd Rickers, to a platform
   independant application, while adding some new features that were not to think
   of at that time (last available version of VideoPro is from 1994, so that time
   Bernd didn't think of the now wide-spread DVD media, for example, or of features
   like Digital Dolby Surround and others) and dropping
 things I think not needed
   (as e.g. his phone book - when phpVideoPro is
 plugged into phpGroupWare, you'll
   have everything there :-)</P>
  <P Align=Justify>Starting with Version 0.0.3 the program came to a state where it is
   usable not only by me (since I already have a database, which I manually converted
   from Bernds VideoPro), but by everybody who has a PHP powered web server with MySQL
   running: even if it's not that comfortable for now, you can add and change entries,
   display a list containing all entries or display a list of available free space on
   your video tapes - and phpVideoPro distinguishes between DVD, Original VideoTapes (OVT
   - these are the ones you bought or got as a present) and Recorded VideoTapes (RVT -
   these are the ones you recorded yourself).</P>
  <P Align=Justify>New features are planned <b>after</b> releasing the first public
   Beta, which shall provide almost stable code with the functionality of v0.0.3, but
   have the bugs of that version fixed and some documentation added; that is v0.1.0.
   What functions are already planned, you can see in the menue items :) With some luck,
   there will be a second beta having some or even all of those features already this
   summer. But (my "standard disclaimer"): Since this is only a hobby, I can't promise
   anything - and just again ask you to stay tuned...</P>
  <P Align=Right>Itzchak Rehberg, June 2001</P>
 </TD></TR>
</Table>

<?

  include("inc/footer.inc");

?>