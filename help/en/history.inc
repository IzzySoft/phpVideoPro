# /* History */
# /*  $Id$ */

[title]
0.5.7 (January 28, 2004)
[text]
<ul>
 <li>some adjustments (and fixes) to the PostgreSQL code
 <li>fixed the "implode" error on staff list display with empty DB
 <li>improved order clause for staff lists
 <li>when the primary language is changed via the admin-&gt;configuration
     menu, the user is now asked for a confirmation (JavaScript confirm())
     to not accidentally change this here for ALL new users while intending
     to change it in his/her personal preferences
</ul>

[title]
0.5.6 (December 18, 2003)
[text]
<ul>
 <li>hopefully fixed stafflist crashing with SQL error when no staffmembers
     found (which is usually the case when starting with a fresh install)
 <li>hopefully fixed the other lists crashing on fresh database since no
     entries found
 <li>finally fixed problem in get_preventry(): sometimes MySQL seems to return
     an empty value instead of no result (this only happened if one entered
     a higher medianr than 1 as first medium of a type). Worked around this.
 <li>language file syntax had changed with v0.5.5 - but we forgot to update
     some language files to the new syntax (Ouch!) - done.
</ul>

[title]
0.5.5 (November 24, 2003)
[text]
<ul>
 <li>updated Spanish language file (tnx to Jaime)
 <li>some translations have been hardcoded (= not translated) - fixed.
 <li>disktype (e.g. DVD-9) was not displayed correctly when editing an
     existing entry - fixed.
 <li>updated Russian language file (tnx to masterr)
 <li>if a tape entry was copied into a dvd entry, region code could not be set
     - fixed.
 <li>copying a movie entry failed if comment contained single quote(s) - fixed
 <li>Translation editor now contains comments on the terms to be translated
     to help the editor understanding them better
</ul>

[title]
0.5.4 (November 2, 2003)
[text]
<ul>
 <li>available languages in select box on configuration screen are now ordered
     alphabetically
 <li>translations for a specific language (except English ;) can now be removed
     via the configuration screen (admin menu)
 <li>added check to disk type deletion. If you now try to delete a disk type
     that is still referenced by some media, it will not be deleted anymore.
     Instead, you will be presented with a list of these media and now can
     decide to change them and delete the disk type afterwards.
 <li>color settings have been moved to stylesheet and thus are now completely
     template dependant
 <li>in admin-&gt;configuration, date_format could not be changed - fixed.
</ul>

[title]
0.5.3 (September 29, 2003)
[text]
<ul>
 <li>added delete confirmations to some admin screens that were missing it
 <li>first-time installation missed two columns in cass table since v0.5.1 - fixed.
 <li>fixed endless loop in stats
 <li>fixed some SQL for updates on PostgreSQL (tnx to Peter Bieringer!)
</ul>

[title]
0.5.2 (August 7, 2003)
[text]
<ul>
 <li>finally fixed the menu for NS4 again
 <li>quotation characters should now be handled correctly for movie title
     and staff member names
 <li>RegionCode could not be unset - fixed.
 <li>movie technical data now can be edited/administrated (see new item in
     admin menu)
</ul>

[title]
0.5.1 (July 4, 2003)
[text]
<ul>
 <li>added support for disk types (such as CD-R[W], DVD-R[W] and DVD+R[W])
 <li>longplay is now only displayed for disk types that support it (i.e. right
     now only for tapes) or if no disk type is set (i.e. the same plus not
     updated DVD/VCD entries) - for all others it is automatically set to "No"
 <li>added support for region codes (DVDs only)
 <li>added administration page for disk types
 <li>updated help pages concerning these changes
 <li>hopefully worked around the register_globals problem (not tested, so please
     report to me if you use register_globals=off with phpVideoPro, which is the
     default since PHP v4.2)
 <li>applied some fix-ups for Netscape 4.x -- still not satisfying. Support
     for this old browser will stay limited with phpVideoPro; I encourage you
     to use some newer browser like Mozilla or what ever...
</ul>

[title]
0.5.0 (June 27, 2003)
[text]
<ul>
 <li>since some users experienced problems with the cookie and session
     management (mostly due to their machines setup), I decided to use
     different initial settings to be changed by the "admin" after successful
     installation and application verification: cookies expire with the
     browser session, phpVideoPro's session are set to never expire. You may
     change those values after the installation has completed, if your setup
     is fine (problems for these cases only arise if there are differences in
     the machines time between the server and your client). The setup program
     gives you more information about this.<BR>
     If you are still unable to log in after a completed installation, search
     this page for the string "register_globals", since this problem is most
     probably connected to that issue.
 <li>some improvements on the PS top labels
 <li>added Session management screen
 <li>on a correct login session was always created for admin (user ID 1) - fixed
 <li>movies could not be inserted/updated when a persons name contained single
     quotes - fixed
 <li>in some cases the media type was displayed twice in the media number - fixed.
 <li>on submission of some forms session was broken if cookies were disabled - fixed.
 <li>on updating configuration or preferences, unchanged values got duplicated
     in the database - fixed.
</ul>

[title]
0.4.8 (May 1, 2003)
[text]
<ul>
 <li>Printers can now be edited (see admin menu)
 <li>Templates for PSLabels now have a frontend to be managed with (admin menu)
 <li>there was a possibility to access the translation editor w/o admin privs (fixed)
 <li>fix from Michael for the PS Side labels: movie length no longer gets
     overwritten by ultra-long movie titles
 <li>Michael also supplied more details upon the top labels, as you may know
     them from the old label system
 <li>applied some corrections plus clean-up to the PS Label images
 <li>updated Russian language file
</ul>

[title]
0.4.7 (April 25, 2003)
[text]
<ul>
 <li>Made editing for translations easy by a new form in admin menu. If you've
     added/updated some entries, you may save them to a file and then send them
     to me for inclusion with future versions!<br>
     To use this new editor your machine must be set to use the same charset
     as is used by the language you want to edit (or at least it must have the
     target language's charset as subset, as e.g. US-ASCII is a subset of
     ISO-8859-1).
 <li>Matzah was cleaned up with the leaven: almost no tags where allowed in the
     comment field of a movie. Fixed: Now Bold, Underline, Italics and Center
     work again.
 <li>Added "Overview per Medium": on the initial page, when selecting a media
     type and entering a media number <b><i>without a part</i></b>, there's now
     a page displaying all movies on that medium together with some data
 <li>Introducing basic Hebrew support (many thanx to Shalom Pollack for his
     patient work). This is still experimental, since we've encountered some
     problems with BiDi in mixed phrases (Hebrew phrases containing English
     words) etc. that have to be solved.
 <li>A bit database cleanup took place: removed two obsolete tables that
     remained from the conception phase of PSLabels.
 <li>Added initial Russian support (thank you, Denis!) - completion on this
     hopefully follows soon :-)
 <li>Did some cleanup on all ISO-8859-1 language files (wiped out entries that
     equaled the English fallback value). Wow, that's done easily now with the
     new translation editor!
 <li>Michael supplied some fixes for the PSLabel system: Long lines are now
     wrapped to fit on the label, for example
</ul>

[title]
0.4.6 (April 19, 2003)
[text]
<ul>
 <li>media statistics just reported count of r/w media instead of all media -
     fixed
 <li>hopefully fixed the stupid issue that no semi-colon could be used in field
     content on imported files, since db::get_sql assumed end-of-sql-command then
 <li>in database backup, semi-colons are no longer replaced by colons now since
     import of those is fixed by now
 <li>enhanced backup function (see admin menu): alternatively to a complete
     database backup, there are two more options now: backup movie relevant
     data only, and the same plus having the old data purged before execution
     on a restore
 <li>on the help pages, you may now force to display the English files. I felt
     this necessary since help files are not up-to-date for some languages, so
     some new features may not be described there. Switch to the English help
     file by clicking on the flag when you feel there's something missing in
     your language's file. If you are right, feel free to update your language's
     file and send it to me :-)
 <li>nesting of [url][img]picture[/img][/url] tags now possible in the way
     displayed here (not vice-versa ;)
</ul>

[title]
0.4.5 (April 11, 2003)
[text]
This is the "Passover" version for this year: now we clean up with the "Chametz"
possibly entered by some users (see first and second item below):
<ul>
 <li>Added support for several special tags within the comment field: You now
     may easily add thumbnails by using the [img] and [imgr] tags (the first
     just puts the image on the lefthand, the latter on the righthand side). To
     add an URL to an external reference, you may now use the [href] tag. In
     all three cases, enclose the target by opening and closing tags, e.g.:
     [url]http://www.izzysoft.de/[/url]. Until now, phpVideoPro automatically
     converted all strings that look like an URL into the [url] format (for
     output only). For that reason, the image links could only refer to
     <b>local</b> images and not to other systems, since otherwise those links
     would be broken. To prevent this (and make you able to use images from
     whatever source), I provided a script to update your comments and dropped
     the former behaviour. I suggest you to run that script - the update page
     will provide you with the necessary link.<br>One more note: the [url] and
     [img]/[imgr] tags must <b>not</b> be nested.
 <li>Protected user input against malicious HTML code: now there are only a few
     HTML tags allowed within the fields (see
     "<A HREF="{PHP_SELF}?topic=add_entry">*add_entry#</A>" for details)
 <li>Fixed syntax error in Spanish language file - now Spanish should install
     fine.
 <li>Added Search function (to be found via the *edit# menue). Filter settings
     are added to the conditions entered into this form for the search. See
     help on <A HREF="{PHP_SELF}?topic=search_movie">*search_movie#</A> for
     details.
 <li>Fixed some problems with the configuration/preferences update (some
     settings could not be changed)
</ul>

[title]
0.4.4 (April 4, 2003)
[text]
<ul>
 <li>fixed another cookie-overwritten var on the configuration page which made
     change of printer impossible with cookies enabled
 <li>added printer specification for Canon S520 to PSLabel system
 <li>created final work-around for a Konqueror Cookie bug affecting the prefered
     language setting (see second item of v0.4.3 below), which means we handle
     the given cookie correctly (no Bulgarian-fallback at this place anymore,
     but fallback to the language set by phpMyAdmin as long as Konqueror remains
     within its ignorance and gives us that despite of the wrong path)
 <li>When walking through your collection on the "*view_entry#" screen using the
     previous/next icons (left resp. right to the movie title), gaps (holes in
     part/media numbers) are now handled as expected. Up to now, we considered
     the "end of the world" instead and jumped to the previous/next medium resp.
     media type when hitting a gap ;)
 <li>Spanish language support added - thanks to Pablo!
</ul>

[title]
0.4.3 (March 25, 2003)
[text]
<ul>
 <li>Fixed problem in DB Setup for PSLabel tables: some MySQL versions
     take "DEFAULT ''" as "DEFAULT NULL" which stands in contradiction to the
     "NOT NULL" constraint.
 <li>Fixed a problem with Cookies: if you use phpMyAdmin on the same server
     as phpVideoPro, the first was overwriting the "lang" cookie of the latter
     when using Konqueror as browser (at least verified with Konqueror 3.0.4).
     This does still happen with the mentioned version of Konqueror since it
     ignores the cookie path setting, but now should not happen anymore with
     any browser that does <b>not</b> ignore the cookies path.
 <li>With cookies enabled and user-defined preferences stored within cookies,
     the selected label configuration variable got overwritten by the cookies
     value (since both had the same name) when printing a label using the "old"
     label system called from the "*view_entry#" page
</ul>

[title]
0.4.2 (February 23, 2003)
[text]
<ul>
 <li>made session_purgetime (inactivity timeout for logged-in sessions) user
     configurable
 <li>cookies are no longer a "must" in order for sessions (user authentification)
     to work. Even though, I encourage you to use the cookie option - not only
     for the session id to not appear within the url lines, but the user's
     preferences still need them (or some of your db saved "default" preferences
     get overwritten by them from time to time ;).<br>
     However: if you decide to use cookies in your config, but the user refuses
     to accept them: (S)he won't be able to log in, and it's not your fault.
 <li>thought about the "register_globals=On" issue: this limit will remain since
     I won't have the time to go over it all in the near future. But to help
     you living with it (if the problem affects you), I recommend visiting
     <A HREF="http://www.php.net/manual/en/security.registerglobals.php"
     TARGET="_blank">this page</A> (part of the PHP online documentation) to
     find a solution suitable to you.
 <li>added a new label engine using PostScript to create labels (thanx to
     Michael Hasselberg who created this module!). Be aware that this new
     engine is not yet completed and thus still experimental.
 <li>added some new labels for the new PS engine. Side labels already look
     really great (and work great as well)!
 <li>fixed a problem with cookies: when set-up to expire at end of session,
     they expired immediately when set
 <li>when a session has expired, there's an appropriate hint now on the login
     page - and the initial page in that case doesn't display a "logged in as
     guest" anymore
</ul>

[title]
0.4.1 (February 5, 2003)
[text]
<ul>
 <li>removed the "unknown" entries from the ranking list on the statistics page
 <li>added user and session management - for certain activities you *must* login
     now!
</ul>

[title]
0.4.0 (November 20, 2002)
[text]
<ul>
 <li>brought help files up-to-date
 <li>fixed a minor bug concerning label's content
 <li>some minor fixes for PostgreSQL and the installation pages
</ul>

[title]
0.3.8 (November 10, 2002)
[text]
<ul>
 <li>now using cookies for user based preferences. Defaults are taken from
     the DB as usual. DB preferences (= defaults) are managed via the
     admin-&gt;configuration menue, while edit-&gt;configuration manages
     the user preferences, i.e. by cookies.
 <li>renamed the "configuration" item in edit menue to "preferences" - this
     reflects the issue much better ;)
 <li>filters are now working via cookies as well - so multiple users now can
     use different filter settings simultaneously!
 <li>there were some problems with quote signs (and some others) in title,
     source and comment field texts. Hopefully fixed.
 <li>going to feature freeze for v0.4.0 now...
</ul>

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
