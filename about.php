<? /* About */

  $page_id = "about";
  include("inc/config.inc");
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
  <P Align=Justify>So now I hope I will have some working version very soon. While
   at the beginning (Version 0.0.1) I kept the structure of the tables 100% compatible
   with Bernds Clipper
based stuff, I changed that with version 0.0.2 to a structure
   that seemed more suitable to me. So table structures as well as field names are
   almost completely reworked by now, new tables are added, and more will come.
   Starting with version 0.0.3 (which I hope to finnish before the summer break) there
   will be a first usable program code, allowing to create new entries as well as
   update/delete existing ones. But since this is only a hobby, I can't promise
   anything - and just again ask you to stay tuned...</P>
  <P Align=Right>Itzchak Rehberg, June 2001</P>
 </TD></TR>
</Table>

<?

  include("inc/footer.inc");

?>