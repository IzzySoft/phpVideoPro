# /* History */
# /*  $Id$ */

[title]
0.2.4 (June 12, 2002)
[text]
<ul>
 <li>$recdate in view_entry was not displayed correctly for "unknown dates"
 <li>fixed display of unknown dates in medialist
 <li>added simple label printing, accessible via the view_entry form.
     For now this just prints one label (for the selected medium); printing
     a range of labels may (or may not ;) follow later. Label opens in a new
     window for preview, use your browser's print function then.
</ul>

[title]
0.2.3 (June 5, 2002)
[text]
<ul>
 <li>added feature to walk through long lists in pieces of user-definable size
     (first/prev/next/last page of lists). Behaves a bit strange for staff
     lists (directors, artists etc.) if you have some skeletons in your closet
     (i.e. staff members with no movie assigned) or have some staff members
     not marked as "in list"
 <li>added French language support
 <li>reworked translation code - incredible speed gain!
 <li>forgot to update the version number in the installation script for
     v0.2.1 and v0.2.2 - so if you upgrade from a fresh installation of one of
     those, make sure to manually update the DB first ("UPDATE pvp_config SET
     VALUE='0.2.x' WHERE name='version'", where "x" is either 1 or two,
     depending on the version you've installed) -- or just truncate the
     concerning update scripts (setup/0-2-x_to_0-2-y.*), otherwise the update
     will fail. Sorry for that.
</ul>

[title]
0.2.2 (May 30, 2002)
[text]
<ul>
 <li>edit.tpl caused probs with NS 4.x (almost fixed - NS 4.x too stupid)
 <li>insert a person (staff) into db failed if only name OR firstname were
     specified (fixed)
 <li>added support for VideoCD (VCD)
 <li>some rework at the database functions/classes
 <li>setup now checks for existance and read permissions of sql files
     before trying to execute them and reports errors accordingly
</ul>

[title]
0.2.1 (September 30, 2001)
[text]
<ul>
 <li>made urls in commentfield (view entry) clickable
 <li>added IMDB support for staff members (view entry, click on name)
 <li>stafflist always displayed not_found (fixed)
 <li>added stylesheets for input and select boxes
 <li>some design update on edit/view entry screen (w/o effect for NS 4.x :)
 <li>added new fields for counter & commercials to edit/view entry page
 <li>help system displayed nonsense when topic not found (fixed)
 <li>added new help topic and updated some existing ones
</ul>

[title]
0.2.0 (September 23, 2001)
[text]
<ul>
 <li>if no matching entry was found, stafflist screen was messed up. Fixed.
 <li>completed German help files
 <li>order by MediaNr in MediaList ignored part nr. fixed.
 <li>reorganized sql statements in preparation of PostgreSQL support
 <li>added documentation header to most files
 <li>addition of language files for Norwegian, Polish, Dutch, Bulgarian
     and Italian (Thanx to Knut, Leszek, Tom, Tsveti and Alex!)
 <li>added possibility to directly go to an entry specified by MediaNr
 <li>fixed some translation stuff (e.g. color names in edit.php)
 <li>added basic PostgreSQL support - please report any errors/bugs/problems
 <li>charset is now maintained by the language files (and not accessible
     via the configuration screen any more)
 <li>fresh installation was broken (fixed)
 <li>splitted date field into day-month-year
 <li>remaining free space on tape was updated incorrectly when adding
     a new entry to an existing tape (fixed)
</ul>

[title]
0.1.7 (August 16, 2001)
[text]
another intermediate release due to internal changes (help system). Now I will
really go to "feature freeze" again, just creating the missing German help
files and fixing bugs - so if anybody finds any bug, please report! I want to
have the next release in Gamma state...
[text]
starting with v0.2.0, the digits of the version numbers should mean the
following to you:<br>
<li>last digit: beta state nr# or "0" if none<br>
<li>middle digit: gamma state nr# or "0" if none<br>
<li>first digit: final release nr# or "0" if none<br>
Alphas will only be internal and have a suffix added (p#, as to be seen on the
<A HREF="http://www.qumran.org/homes/izzy/">Demo-Site</A>).
[text]
<hr>Changes:
<ul>
 <li>made help system template driven
 <li>made help files easy to create/edit even for people without any
     knowledge of PHP and even HTML (see <A HREF="{PHP_SELF}?topic=howto_help">HowTo</A>
     on this)
 <li>added possibility for translation and variable usage to help templates
 <li>updated some help file content
 <li>added new German help files
</ul>

[title]
0.1.6 (August 14, 2001)
[text]
<ul>
  <li>updated help files
  <li>enhanced stylesheet: added table background color (adjustable
      via the configuration screen)
  <li>fixed a template parse bug in filter menue
  <li>some cosmetical fixes on view/edit and filter screen
  <li>update to "source" field went into the Nirwana - fixed.
  <li>made some forgotten pages template driven
  <li>update from a version &lt; 0.1.4 to &gt; 0.1.4 did not
      work by a single step - one had to call the update page twice. fixed.
  <li>added language and template support to configuration screen
  <li>updated help page design
  <li>added some German help files
  <li>added ToDo list to doc/ directory (doc/2do)
</ul>

[title]
0.1.5 (August 5, 2001): alpha-release "camouflage"
[text]
<ul>
  <li>re-sorting of medialist can now be done by simply
      clicking on the appropriate table header
  <li>moved to template-based design - now YOU can decide how phpVideoPro shall
      look like, without knowing anything about PHP: just edit plain HTML
      templates and create your own favorite "skin" (and then don't forget to
      send it to me to include it within the next release :)
  <li>added template selection to configuration page
  <li>added checkbox to configuration page: scan for new language files. You
      need to check this only, if you add a language file that was not present
      before (new language)
</ul>

[title]
0.1.4 (July 29, 2001)
[text]
<ul>
  <li>worked on the menue stuff. Menue should be "compatible" with most
      browsers. I've tested it successfully with Netscape 4.76, M$IEx 5.0,
      Mozilla 0.9.1. However, Konqueror 2.1.1, Opera 5.0 and M$IEx 4.01 still
      turned out to have problems: they show the menue, but it won't work.<BR>
      Using different menues for Netscape &lt;= 4 and the rest of the world to
      get all (or at least most) of them working.
  <li>Help menue now has an additional entry: help for the current page
  <li>added list of actors, list of directors, list of composers
  <li>updated help system accordingly
  <li>updated setup (and fixed a little bug there)
</ul>

[title]
0.1.3 (July 26, 2001)
[text]
<ul>
  <li>implemented help system and wrote English help files
  <li>out-sourced stylesheet for maybe planned template support
  <li>added sort criteria to media list: 1) MediaType, 2) MediaNr. For now this
      is static - some future version may add some dynamic to it to let the
      user decide about the sorting
  <li>fixed a small bug in config routine (language files were not found)
  <li>added possibility to refresh language phrases in db from new/modified
      language files (you will need this on every update :)
</ul>

[title]
0.1.2 (July 17, 2001): alpha release "freedom"
[text]
<ul>
  <li>taperest list showed up wrong media names (and movie titles): Media Type
      specification in sql statement was incomplete :)
  <li>added translation functionality - now phpVideoPro can go multi-language!
      FallBack to default language (en) implemented for non-existing phrases.
      If no translation exists at all, the coders info appears :)
  <li>added new tables to db: some for the translation stuff, and one to store
      configuration settings. This will make updates easier (for now we can
      determine the previously installed version easily) and as well prepared
      the way to some better setup tool (see below)
  <li>"internationalized" phpVideoPro by making the pages using the translation
      code (and adding required translations to lang_en.sql and lang_de.sql).
      (Hopefully) finnished for most pages (tell me if I forgot something :).
  <li>setup now autodetects version of already installed database when updating
  <li>renewed setup tool - now it contains a configuration page as well
  <li>moved main part of inc/config.inc into db for easier maintenance by new
      configuration page
  <li>some minor bugfixes/cosmetical changes
</ul>

[title]
0.1.1 (July 4, 2001): alpha release "independence day"
[text]
<ul>
  <li>(un)setting of filters now implemented
  <li>for now filters follow this rule: multiple selected items of the same
      type (e.g. categories) are combined with "OR" (except those with "min"
      and "max" values - they are combined with "AND"), different types are
      combined with "AND". An example: setting the filter on category_a,
      category_b, mediatype_a and mediatype_b would produce the filter
      "(category_a OR category_b) AND (mediatype_a OR mediatype_b)". I plan to
      extend this, and make AND/OR selectable for those fields it makes sense
      with (e.g. it makes no sense with the colors to combine them with AND -
      since a movie is either s/w or color).
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

[title]
0.1.0 (June 29, 2001)
[text]
Since feature freeze is in effect, there are only bugfixes and works on the
documentation:
[text]
<ul>
  <li>added README (with hints for installation and notes on copyright and
      license)
  <li>while outsourcing some functions used in more than one file, update was
      broken (duplicate function declaration), fixed.
  <li>when adding a new entry it was possible to get duplicate or invalid media
      IDs. Added some check to prevent this.
  <li>preset "Aquired" date to current date when adding a new entry
  <li>added check for valid date on adding new and changing existing entry
  <li>relaxed date check. Now providing an "incomplete" date is possible. This
      is useful, if one e.g. does not remember the exact date of aquiration,
      and so is just able to enter the year (or year and month). Missing data
      are to be substituted by zeros (e.g. "2000-05-00")
  <li>remaining time on video tape was miscalculated, if other medium (e.g. DVD)
      with the same number existed. Fixed.
</ul>
This is the first public beta version - didn't think it went that fast :)

[title]
0.0.3 (June 27, 2001)
[text]
started adding new features:
<ul>
  <li>action processed (e.g. "editing entry RVT 0089-02") is now displayed in
      the browsers title bar
  <li>"free time on media" list now working
  <li>"free time on media" was not updated when updating an entry. fixed.
  <li>added page with instructions how to setup phpVideoPro
  <li>added setup script for database
  <li>adding a new entry is now possible! So this fine piece of software
      should now be useful even for people other than me :)
</ul>
[text]
Going to feature freeze (now the product has all its "main functions" and can,
as mentioned above, be used by "the public") and check for bugs (guess I'll have
to force myself to this step - since there are some functions I am dying to
implement ;). If no bugs are found within the next days (or the ones found are
fixed), version number will change to 0.1.0 as first public beta (wow!)

[title]
0.0.2 (June 24, 2001)
[text]
database completely reworked and restructured to what I felt to be suitable to
fit the new requirements. Detail view largely improved (but still not satisfying
me :). New available functions:
[text]
<ul>
  <li>improved Detail View (old one dropped :)
  <li>possibility to change existing movie data
  <li>LongPlay now selectable, also wether to include director/composer of
      current movie when listing up directors/composers
  <li>added (this) history page
</ul>

[title]
0.0.1 (January 2001)
[text]
initial version - just allowed browsing of existing data, no changes are made
to data. Features available:
[text]
<ul>
  <li>MediaList
  <li>Detail View
  <li>About
</ul>

[eof]
