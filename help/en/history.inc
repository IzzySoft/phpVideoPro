# /* History */
# /*  $Id$ */

[title]
0.3.7 (November 6, 2002)
[text]
<ul>
 <li>when a medium became empty (by removal of the last movie), it was always
     removed from the media table (and thus not available for free space
     searches). This is now configurable.
 <li>moved color settings (for page and table backgrounds) into template's
     stylesheet and removed them from config screen. They should only change
     with the selected theme. Modify there for your convenience ;)
 <li>moved parts from config.inc to config screen: rw_media, remove_empty,
     defaults[scolor] and site - so only absolut necessary items are still
     kept in this file
 <li>configuration form no appears twice: once in edit (where it has always
     been) and once in the admin menue. Reason: administrative items, such as
     which media may be written to, or should empty media be removed, are now
     only reachable via the admin menue, while the "traditional place" now
     only displays "preferences" that make sense on user base.<br>
     So to protect your installation, even if there's no user management for
     now, you just can place an .htaccess file into the admin/ directory. Well,
     this does not protect your movie entries from being overwritten - but
     every thing has its time, right?
 <li>added setting "label" to the edit form. This is to define wether a movie
     should appear on the label for its medium.
 <li>added default setting for tone format (was previously "mono" for new
     entries - now it is configurable)
</ul>

[title]
0.3.6 (November 3, 2002)
[text]
<ul>
 <li>added managment (i.e. search for and deletion of) orphaned entries in/from
     the staff tables
 <li>added database backup (humm, time for a separate admin menue, huh?)
 <li>added admin menue and moved all administrative items here (hm, now the
     edit menue looks quite empty ;)
 <li>added restore. Don't look for it in the menue - it's not there, but runs
     via the installation screens. See online help for details.
 <li>made some "visual improvements" for the installation screens. Look much
     better now - at least to me :)
 <li>added search for duplicate movie titles
</ul>

[title]
0.3.5 (Oktober 29, 2002)
[text]
<ul>
 <li>color name for movie (color, b/w or 3d) was not translated when viewing
     an entry. Fixed.
 <li>on the start page, when an entry was selected HTML header was created
     twice - which caused problems with Netscape 4.x. Fixed by Michael.
 <li>some browsers (including Opera) always displayed cached copies when e.g.
     changing some values on the configuration page. They shouldn't do so
     anymore (at least Opera does not :)
 <li>added site info (the "site" variable in config.inc) - that's what's now
     displayed within the title bar of your browser behind the "@" sign.
 <li>view/edit entry screens now show the complete movie number (including the
     media type) in title bar and headline, plus the form looks a bit better now
 <li>added prev/next buttons (next to the movie title) to the "view entry"
     form so you now can directly walk your collection
 <li>addition and removal of categories is now implemented
</ul>

[title]
0.3.4 (Oktober 24, 2002)
[text]
<ul>
 <li>when deleting the last movie from a r/w medium, the empty medium is now
     removed as well (cosmetical fix).
 <li>phpVideoPro should now be able to support multiple read/write media. Be
     careful using this function - and please report any strange behaviour
     immediately, since this new feature is not yet thouroughly tested. In
     order to enable it, edit the inc/config.inc file; you'll find more
     explanations at the end of this file within the "technical" block.
 <li>media capacity for (re)writable media is now editable. To use this
     feature, just click on the button for the remaining time ("*free#")
     when viewing an entry.
 <li>categories can now be edited. However, you can't add or remove categories
     yet - this features will be part of a future release.
 <li>cleaned up the comments so phpdocgen doesn't complain any more. Added
     some more comments, amongst others for the auto-generated api doc
</ul>

[title]
0.3.3 (Oktober 20, 2002)
[text]
<ul>
 <li>worked around a Netscape 4.x JavaScript bug with the label printing
     function in "*view_entry#" (thanx to Michael Hasselberg for providing
     this fix!)
 <li>taperest list now shows the movie's number (linked to the movies entry)
     within the contents column
 <li>now you can copy (duplicate) or move a movie's entry into a new record
     (i.e. to a new medium). To find this function, just click on the MediaNr
     or MediaType button. Btw: this is the "change medium / media number" feature
     some of you requested, just a bit enhanced :)
 <li>fixed some bug with freetime update when adding a new entry (possibly
     introduced with v0.3.2)
</ul>

[title]
0.3.2 (Oktober 14, 2002)
[text]
<ul>
 <li>added functionality for d/l of latest version (new item in "*edit#" menue)
 <li>freetime update was broken - fixed.
 <li>filter could not be edited when no actor, director or componist was
     in DB - fixed.
 <li>some more code cleanup (to produce new bugs ;)
 <li>in edit/view entry, remaining free time now is displayed for editable
     media only (e.g. not for DVD or Original Video Tapes), i.e. at this
     time for RVT only (until I've added support for more than one mtype here).
     Analogue to that, the "*in_list#" button for an actor does not show
     "*yes# / *no#" information any more in "*view_entry#", when the actor is not
     set. Same applies to director and composer.
</ul>

[title]
0.3.1 (Oktober 2, 2002)
[text]
<ul>
 <li>movie title button now also links to IMDB information (as names do)
 <li>movielist: order by category didn't work. Fixed.
 <li>added statistics page
 <li>help system ignored language settings (did nobody notice this?) - fixed.
</ul>

[title]
0.3.0 (September 24, 2002)
[text]
<ul>
 <li>first-time installation failed: we tried to read from tables which
     did not yet exist
 <li>started adding comments for javadoc style api doc generation
 <li>added most of the Swedish help files (thank you, Tony!)
 <li>some code cleanup
 <li>added instructions to doc/README on how to remove unneeded language
     support files
</ul>

[title]
0.2.8 (July 29, 2002)
[text]
<ul>
 <li>categories are now translated (if you miss translations for your language,
     see the "HowTo" section on how to create them, then create them, and send
     them to me :)
 <li>added Swedish language file (thanks to Tony!)
 <li>Now filters can be REALLY edited (found out that up to v0.2.7 one could
     only reset or add to filters - but unsetting/changing just a single item
     was not possible)
 <li>fixed PG constraint update problem (update from v0.2.6 to v0.2.7 failed -
     why didn't anybody tell me? Nobody using PG?)
 <li>fixed a few bugs concerning NULL values for add_entry and update
     introduced with v0.2.7
</ul>

[title]
0.2.7 (July 4, 2002)
[text]
<ul>
 <li>updated German and English help files to reflect latest changes. Still need
     people who do the same for the other languages already available with
     phpVideoPro.
 <li>removed obsolet SQL update files in setup/ (which just increased the
     version number). Updates from "ancient versions" do still work.
 <li>absolut taperest list was broken (fixed filters)
 <li>Bulgarian language file updated (thanx to Tsveti!)
 <li>fixed wrong movie grouping in taperest list
 <li>moved almost all SQL code into db.inc (lots of methods added/rewritten)
</ul>

[title]
0.2.6 (June 26, 2002)
[text]
<ul>
 <li>added list printing functionality. Right now, it prepares the lists for
     either directly being printed (spartanic ASCII version) or exported to
     your favorite word processor / spread sheet for further processing
     (HTML and CSV version)
 <li>made date format configurable (right now just used with the list printing,
     everything else will follow)
 <li>added/updated some help pages
 <li>some work on the db class in preparation for code cleanup (all direct
     db queries should only be here: "abstraction layer" to ease changes to db),
     same for preferences (to be continued ;)
 <li>$db-&gt;get_movie() now uses outer joins (speeds up list building by at
     least factor 2!). Side effect: you have to make sure your DB type supports
     this (e.g. PostgreSQL 7.0 does NOT, here it was added with 7.1 afaik).
     With this release, only label and list generation are affected; but with
     the next versions, all pages will switch to the new db-class layout.
</ul>

[title]
0.2.5 (June 17, 2002)
[text]
<ul>
 <li>made label configs based on defaults by including default configs
     to ease modification of label sets
 <li>fixed vertical align of text on label
 <li>max number of lines to fit on label now configurable with the label's
     config
 <li>text (and db fields) to put on label are now configurable - even
     multiple text lines per movie are supported
 <li>toolbar is now displayed for labels to allow easier access to the print
     function (no effect on Konqueror whyever - but works fine with Mozilla)
 <li>added HowTo on creation/configuration of label templates (in help system)
 <li>added ability to print multiple labels on one page
 <li>added help on label printing
</ul>

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
