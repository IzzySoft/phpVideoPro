<? /* About */

/* $Id$ */

  $page_id = "history";
  include("inc/config.inc");
  include("inc/header.inc");

?>

<H2 Align=Center>phpVideoPro History</H2>

<Table Width=90% Align=Center>
 <TR><TD><UL>
  <LI><b>0.1.2 (July 2001)</b><br>
      alpha release "freedom":
      <ul>
       <li>taperest list showed up wrong media names (and movie titles):
           Media Type specification in sql statement was incomplete :)
       <li>added translation functionality - now phpVideoPro can go
           multi-language! FallBack to default language (en) implemented
           for non-existing phrases. If no translation exists at all,
           the coders info appears :)
       <li>added new tables to db: some for the translation stuff, and
           one to store configuration settings. This will make updates
           easier (for now we can determine the previously installed
           version easily) and as well prepares the way to some better
           setup tool at some future point
       <li>started "internationalization process" by making the pages
           using the translation code (and adding required translations
           to lang_en.sql and lang_de.sql). (Hopefully) finnished for
           most pages (tell me if I forgot something :).
      </ul>
  <LI><b>0.1.1 (July 4, 2001)</b><br>
      alpha release "independence day":
      <ul>
       <li>(un)setting of filters now implemented
       <li>for now filters follow this rule: multiple selected items of the
           same type (e.g. categories) are combined with "OR" (except those
           with "min" and "max" values - they are combined with "AND"), different
           types are combined with "AND". An example: setting the filter on
           category_a, category_b, mediatype_a and mediatype_b would produce
           the filter "(category_a OR category_b) AND (mediatype_a OR mediatype_b)".
           I plan to extend this, and make AND/OR selectable for those fields it
           makes sense with (e.g. it makes no sense with the colors to combine them
           with AND - since a movie is either s/w or color).
       <li>implemented filters into medialist - seems to work :)
       <li>when updating an entry, where another one with same number but different
           media existed, both entries were updated with the same data. fixed.
       <li>added functionality to delete an existing entry. DB should be reorganized
           during this process (e.g. actors deleted from actors table if no other
           db entry is referring to them).
       <li>added filtered taperest list (list of remaining time on tapes which only
           includes tapes that match the filter criteria)
       <li>small updates to the README (update process, latest version URL)
      </ul>
  <LI><b>0.1.0 (June 29, 2001)</b><br>
      Since feature freeze is in effect, there are only bugfixes and works
      on the documentation:
      <ul>
       <li>added README (with hints for installation and notes on
           copyright and license)
       <li>while outsourcing some functions used in more than one file,
           update was broken (duplicate function declaration), fixed.
       <li>when adding a new entry it was possible to get duplicate or
           invalid media IDs. Added some check to prevent this.
       <li>preset "Aquired" date to current date when adding a new entry
       <li>added check for valid date on adding new and changing existing entry
       <li>relaxed date check. Now providing an "incomplete" date is possible.
           This is useful, if one e.g. does not remember the exact date of
           aquiration, and so is just able to enter the year (or year and month).
           Missing data are to be substituted by zeros (e.g. "2000-05-00")
       <li>remaining time on video tape was miscalculated, if other medium (e.g. DVD)
           with the same number existed. Fixed.
      </ul>
      This is the first public beta version - didn't think it went that fast :)
  <LI><b>0.0.3 (June 27, 2001)</b><br>
      started adding new features:
      <ul>
       <li>action processed (e.g. "editing entry RVT 0089-02") is now
           displayed in the browsers title bar
       <li>"free time on media" list now working
       <li>"free time on media" was not updated when updating an entry. fixed.
       <li>added page with instructions how to setup phpVideoPro
       <li>added setup script for database
       <li>adding a new entry is now possible! So this fine piece of software
           should now be useful even for people other than me :)
      </ul>
      Going to feature freeze (now the product has all its "main functions"
      and can, as mentioned above, be used by "the public") and check for
      bugs (guess I'll have to force myself to this step - since there are some
      functions I am dying to implement ;). If no bugs are found within the next
      days (or the ones found are fixed), version number will change to 0.1.0 as
      first public beta (wow!)
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