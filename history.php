<? /* About */

  $page_id = "history";
  include("inc/config.inc");
  include("inc/header.inc");

?>

<H2 Align=Center>phpVideoPro History</H2>

<Table Width=90% Align=Center>
 <TR><TD><UL>
  <LI><b>0.0.3 (June 2001)</b><br>
      started adding new features:
      <ul>
       <li>action processed (e.g. "editing entry RVT 0089-02") is now
           displayed in the browsers title bar
       <li>free time on media list now working
      </ul>
  <LI><b>0.0.2 (June 24, 2001)</b><br>
      database completely reworked and restructured to what I felt to be
      suitable to fit the new requirements. Detail view largely improved
      (but still not satisfying me :). New available functions:
      <ul>
       <li>improved Detail View (old one dropped :)
       <li>possibility to change existing movie data
       <li>LongPlay now selectable, also wether to include director/composer
           of current movie when listing up directors/composers
       <li>added (this) history page
      </ul>
  <LI><b>0.0.1 (January 2001)</b><br>
      initial version - just allowed browsing of existing data, no changes
      are made to data. Features available:
      <ul>
       <li>MediaList
       <li>Detail View
       <li>About
      </ul>
 </UL></TD></TR>
</Table>

<?

  include("inc/footer.inc");

?>