# /* configure */
# /* $Id$ */

[title]
Introduction

[text]
On this screen you set up global defaults for phpVideoPro, such as language
specific settings, colors to use etc. Not all options described here are always
available - some of them are only reachable via the admin menue's
"*configuration#" menue since they should only be touched by an administrator -
while others are somehow "preferences" that should be based on an user's wishes.

[text]
Starting with v0.3.8, phpVideoPro optionally can use cookies for the preferences
management. In this case, you set up defaults via the "*admin#" -&gt;
"*configuration#" menue (make sure to enable cookies here), and advice the users
to use the "*edit#" -&gt; "*preferences#" menue to set their preferences
(cookies then are used for filter settings as well). You may then protect your
admin/ directory by an ".htaccess" file to give access to authorized users only.

[title]
*language_settings#

[text]
<b>*scan_new_lang_files#:</b> To manage the languages installed as well
as additional available, phpVideoPro uses its database. So to add a new
language, one has to update this. This is done using SQL files which I for
simplicity will call "language files" from now on. A new language file has to
be introduced to the system, which is done done by setting this checkbox (and
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
<b>*select_primary_lang#:</b> Amongst the installed languages, you can select
your favorite one. If your native language is available, I guess you'ld prefer
that :) For all phrases missing in your favorite languages file, there will be
a "fall-back" to the English phrase. If the English phrase is missing as well
(which should not happen, unless the import of the English lang file failed),
there's some "debug phrase" displayed from which you can guess the content.
If this should happen, and you are sure it's not your fault (e.g. since you
removed the English phrases from the db manually ;) - please drop
<A HREF="mailto:izzysoft@qumran.org">me</A> a note, quoting the missing phrase
and where the error occured.

[title]
*colors#

[text]
<b>*feedback_ok# / *feedback_err#:</b> These settings are not rendered into
any stylesheet. They are used for system responses on user request, i.e.
statements like "entry created successfully" when creating a new entry in the
database, or "Error &lt;some description&gt;" when something went wrong, to
emphasize these messages in context to the regular form data they are displayed
with.

[text]
<b>*template_set#:</b> starting with v0.1.5, phpVideoPro is based on templates.
I (the author) just provided an initial template set; but as soon as there are
additional template sets available (which will only happen when <b>YOU</b>
write them - I'm not a good designer), this is the place to make your choice.

[title]
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
for new movies with "*s/w#". Do this here.

[title]
*cookies#

[text]
<b>*enable_cookies#:</b> Without having this box checked, phpVideoPro won't
use any cookies at all, i.e. preferences will allways be saved to and loaded
from the database - thus overwriting the defaults, even if set from the "*edit#"
-&gt; "*preferences#" menue. So make sure to set this, if multiple users should
access your installation at the same time.

[title]
<b>*expire_cookies#:</b> Here you may define the lifetime of your cookies. If
setting this to "*session#", cookies are always deleted when the browser is
closed - and with a new session, the defaults are loaded from the database
again. In the other cases, cookies remain active for the time frame you set.

[title]
*general#

[text]
<b>*display_limit#:</b> Past versions of phpVideoPro displayed lists, e.g. with
the "*medialist#" menue item, always in full length, i.e. with all records found
in the database. Having a large collection, this not only lead to long loading
times for the page, but the long list could also be confusing for one or the
other person :-) Thus starting with version 0.2.3, phpVideoPro supplies the
possibility to show those lists in pieces whose size you can specify here:
How many lines do you wish to be displayed in those lists. Navigation is
provided by four buttons that bring you to the first/last resp. previous/next
page of the complete list.

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
<b>*date_format#:</b> Specifies the format the date should be presented in. This
is new with v0.2.6 of phpVideoPro, but meanwhile there should be no more
columns/fields ignoring this value (if you find any missings, please report them
to me!). It shall be used throughout the entire program for listings, forms and
anything that contains a date field.

[text]
<b>*site_info#:</b> Starting with v0.3.5, there's a user configurable additional
part of the browser's title bar. Up to v0.3.4, it always displayed
"phpVideoPro v&lt;version&gt; [ &lt;job&gt; ]". Now, in the place between the
version and the job, there's an "@ &lt;*site_info#&gt;" added. That's the part
you may configure here - it helps you to distinguish two different installations
you may have in open browser windows simultaneously.

[eof]

