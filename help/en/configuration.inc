# /* configure */
# /* $Id$ */

[title]
Introduction

[text]
On this screen you set up global defaults for phpVideoPro, such as language
specific settings, colors to use etc.

[title]
*language_settings#

[text]
<b>*scan_new_lang_files#:</b> To manage the languages installed as well
as additional available, phpVideoPro uses its database. So to add a new
language, one has to update this. This is done using SQL files which I for
simplicity will call "language files" from now on. A new language file has to
be introduced to the system, which is done done by setting this checkbox (and
submitting the form, of course :). See "Language to install" below, as well as
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
<b>*page_bg# / *table_bg# / *th_bg#:</b> These settings are rendered into the
(default) stylesheet, and the names are self explaining.

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

[eof]

