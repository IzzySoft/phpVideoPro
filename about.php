<? /* About */

  include("inc/config.inc");
  include("inc/header.inc");

?>

<table width="100%" border="0" cellspacing="0" cellpadding="0">
 <tr> 
  <td width="7"><img src="<? echo $base_url ?>images/menu_bar_left.gif" width="7" height="24"></td>
  <td background="<? echo $base_url ?>images/menu_bar_bg.gif" width="100%">&nbsp;</td>
  <td width="9"><img src="<? echo $base_url ?>images/menu_bar_right.gif" width="9" height="24"></td>
 </tr>
</table>

<H2 Align=Center>About phpVideoPro</H2>

<Table Width=90% Align=Center>
 <TR><TD>
  <P Align=Justify>This is phpVideoPro version <? echo $version ?>, (c) 2001 by
   Itzchak Rehberg, all rights reserved. It's my try to port the best video
   management software I've ever found, VideoPro (c) Bernd Rickers, to a platform
   independant application, while adding some new features that were not to think
   of at that time (last available version of VideoPro is from 1994, so that time
   Bernd didn't think of the now wide-spread DVD media, for example, or of features
   like Digital Dolby Surround and others) and dropping
 things I think not needed
   (as e.g. his phone book - when phpVideoPro is
 plugged into phpGroupWare, you'll
   have everything there :-)</P>
  <P Align=Justify>So now I hope I will have some working version very soon. Right
   now I kept the structure of the tables 100% compatible with Bernds Clipper
   based stuff - as soon as phpVideoPro is able to replace VideoPros main
   functions, I will no longer need VideoPro for editing my database and thus can
   rework table structures, which I certainly will do. But that may take a while,
   so stay tuned...</P>
  <P Align=Right>Itzchak Rehberg, January 2001</P>
 </TD></TR>
</Table>

<?

  include("inc/footer.inc");

?>