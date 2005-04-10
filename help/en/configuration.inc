# /* configure */
# /* $Id$ */

#==================================================================[ Intro ]===
[title]
Introduction

[text]
On this screen you set up global defaults for phpVideoPro, such as language
specific settings, colors to use etc. Not all options described here are always
available - some of them are only reachable via the admin menue's
"*configuration#" menue since they should only be touched by an administrator -
while others are somehow "preferences" that should be based on an user's wishes.

[text]
phpVideoPro optionally can use cookies for the preferences management - which is
strongly recommended. For this, you set up defaults via the "*admin#" -&gt;
"*configuration#" menue (make sure to enable cookies here), and advice the users
to use the "*edit#" -&gt; "*preferences#" menue to set their preferences
(cookies then are used for filter settings as well). The files in the <code>admin/</code>
directory are protected by the session managment, i.e. users without the admin
privilege cannot access them via their browsers.

#======================================================[ Language Settings ]===
[title|1|lang]
*language_settings#

[text]
<b>*scan_new_lang_files#:</b> To manage the languages installed as well
as additional available, phpVideoPro uses its database. So to add a new
language, one has to import the corresponding language file (a plain text file
containing the required SQL statements). Therefore a new language file has to be
introduced to the system, which is done done by setting this checkbox (and
submitting the form, of course :). See "*select_add_lang#" below, as well as
"<A HREF="{PHP_SELF}?topic=howto_lang">*howto_lang#</A>" for details).

[text]
<b>*select_add_lang#:</b> Of course, you only can install available languages
- phpVideoPro does not belong to the category of AI and can't create new
languages on the fly :) To update already installed languages, see next item.

[text]
<b>*refresh_lang#:</b> If you got a new language file for a language you
already have installed, containing corrected and fresh added phrases, you need
a way to replace the old phrases. This is e.g. the case when you update from a
previous version of phpVideoPro. For the language you select here, all phrases
are deleted from the database, and the new language file is imported instead.
At some point in the future I may add a function to only add new phrases and
not delete anything from the db - but that's not done yet.

[text]
<b>*delete_lang#:</b> Maybe for testing, maybe for presentation to alien
visitors or maybe just for fun: sometimes you may have installed translations
for too many languages and now you want to clean up. This is the place for it:
Select the language you want to get rid of, and submit the form. It will only
delete all translations from the database and not touch any file; so if you
have the language file available, you can re-install it at any time. In case
you edited some translations e.g. with the built-in translation editor, you
may want to export these changes first (using the same) to have them available
lateron. Remark: English translations cannot be deleted: they are needed as
fall-back for other languages.

[text]
<b>*select_primary_lang#:</b> Amongst the installed languages, you can select
your favorite one. If your native language is available, I guess you'ld prefer
that :) For all phrases missing in your favorite languages file, there will be
a "fall-back" to the English phrase. If the English phrase is missing as well
(which should not happen, unless the import of the English lang file failed),
there's some "debug phrase" displayed from which you can guess the content.
If this should happen, and you are sure it's not your fault (e.g. since you
removed the English phrases from the db manually ;) - please drop me a note,
quoting the missing phrase and where the error occured.

#====================================================[ Media Configuration ]===
[title|1|media]
*config_media#

[text]
<b>*rw_media#:</b> For some media types, such as original video tapes or DVDs,
it makes no sense to display/edit the remaining free time - since there will
never be any. For others, such as self-recorded video tapes, it's essential.
Some people may have video cds on rewritables, while other's don't. And finally,
who knows: the one or other may already have rewritable DVDs. So this is the
place to tell phpVideoPro about your equipment concerning this: just mark the
media you want to manage remaining free time for as rewritable, and phpVideoPro
cares for it.

[text]
<b>*remove_empty_media#:</b> One wishes to keep empty media within the managment
of remaining free space, since there is free space on. The other, by deleting
the last entry from a medium, means to have given/thrown away that medium, so
there is <b><i>not</i></b> any remaining free time - so (s)he wishes to remove
it from the management. If you e.g. don't delete movies from your recordables,
but just overwrite them with new movies, this belongs to the second catagory,
too. So decide here what is to happen when you <b><i>delete</i></b> the last
item from a medium: check the box, and the medium will be removed from the
"freespace table", i.e. it won't be available for free-space search. Leave it
unchecked, and the medium's complete capacity will be considered as free and
thus available space.

[text]
<b>*movie_onlabel_default#:</b> Sometimes you have an huge amount of small
items on your media (this happens e.g. if someone fills up the last 10..20
minutes with video clips from MTV), but not all of the items should appear
on the label for this medium (to keep information clear). You can set this
for each and every movie entry. Decide here what default should be set for
new entries.

[text]
<b>*movie_tone_default#:</b> It's difficult to decide the most used sound
format for new entries of all users - so I leave that decision to you. The
previous default of "mono" will definitely be wrong for most of you... Set this
to the sound format most of your new entries will have, since that's what it's
preset to for them.

[text]
<b>*movie_color_default#:</b> Today, most movies come in colored mode. So when
creating a new entry, you may feel fine to see this is already checked for you.
Nevertheless, there may be some fans of "oldies" out there who mostly record
movies from the 1920's which, of course, ship in black-and-white mode. Those
of you may want to change this behaviour and like to initiate the color mode
for new movies accordingly. Do this here.

#================================================================[ Cookies ]===
[title|1|cookies]
*cookies#

[text]
<b>*enable_cookies#:</b> Without having this box checked, phpVideoPro won't
use any cookies at all, i.e. preferences will allways be saved to and loaded
from the database (the defaults set from the "*edit#" -&gt; "*preferences#"
menue will not be overwritten by this, since for the user preferences a separate
table is used). Moreover, cookies are used for some data not stored to the
database, such as the session ID.

[text]
<b>*expire_cookies#:</b> Here you may define the lifetime of your cookies. If
setting this to "*session#", cookies are always deleted when the browser is
closed - and with a new session, the defaults are loaded from the database
again. In the other cases, cookies remain active for the time frame you set.

[text]
<b>*session_purgetime#:</b> If a user logs in into phpVidePro, he gains special
privileges you granted to his account, such as being able to edit/delete
entries. If e.g. the user leaves his workplace unattended without logging out,
your data may be in danger since other (unauthorized) people could manipulate
them. To minimize this risk, phpVideoPro gives you the option to time-out
sessions after a specified interval of user inactivity. This only affects the
logged-in session, not the personal configuration the user stored within his/her
cookies. After the timeout, the session falls back into guest mode.

#==========================================================[ IMDB Settings ]===
[title|1|imdb]
IMDB

[text]
<b>*imdb_url#:</b> You can lookup additional data for a selected movie (or staff
member) by clicking on its title (or name) button when viewing the movies entry.
Since the movie title for the same movie differs in different languages, and you
probably will not always have the "original" name of the movie in the title
but the one corresponding to the language version, you may quite often need to
search the IMDB manually. By selecting a better matching IMDB site here, chances
increase for a hit on the first click: if you e.g. have the German movie name
in the title in most cases, you should select the German site of the IMDB here
to reach this goal.<br>
Unfortunately, not all countries have their own IMDB site yet. The ones I know
are available as options. If there are other sites available <i>you</i> know of,
just drop me a note and I will add them asap!

[text]
<b>*imdb_url2#:</b> As nice as the fact of having localized IMDB sites is: Along
with the big advantage of being able to search for the movie title in the
countries language, there is a rub in it. All they translated (for now) is the
users interface - while the content seems to be exactly the same throughout all
IMDB instances. So if we would go to retrieve the details from the localized
IMDB instance, our parser had to be aware of all language variants for the
tokens we need to identify - without us being rewarded with language specific
information for this effort. Hence, once we got the ID for the movie in question,
phpVideoPro switches to an English site to retrieve the details.
[text]
This means of course, that you should be sure to select an <b><i>English</i></b>
site here - whether that is located in the UK or US, I leave up to you.

[text]
<b>*imdb_tx#:</b> These are only the <b><i>Defaults</i></b> for the setting of
the checkboxes on the <A HREF="{PHP_SELF}?topic=imdbsearch">IMDB details</A>
page. Which data are really transfered, you still can decide there by
en/disabling the checkboxes manually.
 
[text] 
<b>*imdb_txwin_autoclose#:</b> This option relates to the IMDB window which can
be opened on the <A HREF="{PHP_SELF}?topic=add_entry">*add_entry#</A> form. In
it, we query the IMDB for information on the movie we are just editing, and
finally get its details here (if found). At the end of this process, when the
user pushed the transfer button and thus transfered the wanted data to the edit
form, that window is no longer needed, and hence could be closed. Whether it is
closed automatically after a successful transfer or not, you can define here.

[text]
<b>*imdb_cache_enable#:</b> The IMDB caching functions actually are only of
interest for developers testing purposes. Once this cache is activated, all
documents retrieved from the IMDB site(s) are stored into the
<i>*imdb_cache_dir#</i> (see below). So if the IMDB LookUp seems to be broken
again, this gives the developer the chance to find out what the guys at
*.imdb.com changed again in their structures - and so we can adjust our code.
For the daily use of phpVideoPro, there are normally no advantages of using the
cache: Since the user stores the retrieved data into the local database, it is
very unlikely (s)he wishes to check for the same data again.

[text]
<b>*imdb_cache_dir#:</b> This is the directory phpVideoPro goes to store the
cached data into. Since for this action the webserver needs to read and write
data here, it needs to have the necessary permissions. The IMDB data are freely
available to everybody, so usually we do not need to be too much concerned about
security and can give these permissions (change into the directory, read and
write files) to everybody with a valid account on the machine. On Linux/Unix,
this would be done by issuing the following command:
<code>chmod 0777 <i>DirectoryName</i></code> (note that you need to be
<code>root</code> to do this). But if you are concerned, you can give these
permissions to the webserver only, which would look like this:<br>
<code>chown wwwrun.www <i>DirectoryName</i><br>chmod 0700 <i>DirectoryName</i></code><br>
Of course you need to replace the user (wwwrun), group (www), and directory
name (DirectoryName) dummies of the example by their real values.

[text]
<b>*imdb_cache_use#:</b> How the IMDB caching in phpVideoPro works, we already
explained above (at <i>*imdb_cache_enable#</i>). But that item just controls
the <b><i>storing</i></b> part of the process. If you <b><i>additionally</i></b>
enable this option, the cache is also used for look-ups: Data already found in
the cache will not again be requested from the IMDB site, but taken from here.

#=======================================================[ General Settings ]===
[title|1|general]
*general#

[text]
<b>*template_set#:</b> phpVideoPros look-and-feel is based on templates. This
offers you some feature you may know as "skins" from XMMS or WinAmp. Here you
can decide which skin to use.

[text]
<b>*imdb_url#:</b> You can lookup additional data for a selected movie (or staff
member) by clicking on its title (or name) button when viewing the movies entry.
Since the movie title for the same movie differs in different languages, and you
probably will not always have the "original" name of the movie in the title
but the one corresponding to the language version, you may quite often need to
search the IMDB manually. By selecting a better matching IMDB site here, chances
increase for a hit on the first click: if you e.g. have the German movie name
in the title in most cases, you should select the German site of the IMDB here
to reach this goal.<br>
Unfortunately, not all countries have their own IMDB site yet. The ones I know
are available as options. If there are other sites available <i>you</i> know of,
just drop me a note and I will add them asap!

[text]
<b>*printer#:</b> To guarantee the exact position of generated labels on the
sheets, we need to know the accurate offset of the printer to use. If your
printer is not in the list, you may first try one of the provided printers:
many of them are compatible according to this issue (and there are not so many
possibilities). When you've found one of them working, please report this to me:
future versions of phpVideoPro may have a compatibility list included then.<BR>
If, however, you find no compatible printer here, you have to create a new one.
For this issue, there are forms available at the <i>*admin_printers#</i> item
in the admin menu (see <i><A HREF="{PHP_SELF}?topic=admin_printers">here</A></i>
for more details).

[text]
<b>*cache_enable#</b>: With special informations in the so-called "Header" of
an HTML document (which is a non-visable area to normal users), proxies as well
as browsers can be adviced to keep a page in cache for a certain time - or not
at all. Is the page contained in the cache, and the "life-time" is still valid,
it will not be requested from the server again on a second call, but taken
from the cache. Especially with dynamic pages (as generated by phpVideoPro),
this certainly is not the wanted behaviour. Moreover, some browsers (e.g. the
MSIE) sometimes take the page from cache even if the user is expressively
requesting a reload using the "Reload" button - which can be quite nasty.
[text]
So with this option you can define what advices phpVideoPro is to send.


[text]
<b>*display_limit#:</b> The very first versions of phpVideoPro displayed lists,
e.g. with the "*medialist#" menue item, always in full length, i.e. with all
records found in the database. Having a large collection, this not only lead to
long loading times for the page, but the long list could also be confusing for
one or the other person :-) Thus phpVideoPro now supplies the possibility to
show those lists in pieces whose size you can specify here: How many lines do
you wish to be displayed in those lists. Navigation is provided by four buttons
that bring you to the first/last resp. previous/next page of the complete list.

[text]
I have to admit that with the staff lists, this feature may seem to work in a
strange way: not only that the line count differs from the entered
"*display_limit#" - additionally it may even vary between pages! The reason
is very simple: phpVideoPro employs the "*display_limit#" on the staff members
here. So the difference comes up when you marked some stuff members as not to
display (using the option "*in_list#" within the "*edit#" form.

[text]
<b>*lines_per_page#:</b> This is for the preparation of plain-text lists for
printing (see "<A HREF="{PHP_SELF}?topic=listgen">*listgen#</A>") and specifies
the amount of lines that fit on one sheet of paper. After the here specified
number of lines, a form feed is inserted to start a new page. You can override
this default on the "*listgen#" form.

[text]
<b>*date_format#:</b> Specifies the format the date should be presented in.
There may still be some forms/pages remaining that do not honour this. If you
find one, please report to me for correction.

[text]
<b>*site_info#:</b> Starting with v0.3.5, there's a user configurable additional
part of the browser's title bar. Up to v0.3.4, it always displayed
"phpVideoPro v&lt;version&gt; [ &lt;job&gt; ]". Now, in the place between the
version and the job, there's an "@ &lt;*site_info#&gt;" added. That's the part
you may configure here - it helps you to distinguish two different installations
you may have in open browser windows simultaneously.

[eof]

