# /* How to create a new language file */
# /* $Id$ */

[title]
*intro#

[text]
Whether you are not satisfied with the translations supplied for your language,
whether the according translation file is incomplete or missing at all: here's
the place to fix it! phpVideoPro will guide you through all necessary steps, so
finally you have the chance not only to have translations as you like them, but
moreover to be part of the team by sending the resulting language file back to
me, the author of phpVideoPro, having it included with future releases.

[title]
Requirements

[text]
Your machine must be set up to use the same character set as specified with the
language you want to edit, or a character set that has it included as a subset
(if you e.g. would like to edit the English language using US-ASCII, your
machine should be set up to use either US-ASCII or ISO-8859-1, which has US-ASCII
as a subset).

[text]
Second, you must go to "*edit# -&gt; *preferences#" and change your primary
language to the one you want to edit (at least if the current primary language
uses a different character set than the one to edit - if both use the same, you
may skip this item). Of course you won't be able to do so if there are no
translations exist yet for the target language - for this case, see below.

[title]
*sel_target_lang#

[text]
The first step is to select the language we want to edit. If there are already
translations available within the database, these are loaded then. Otherwise,
we create a whole new set at this place (and all text areas to edit will be
initially empty). To determine the character set used for the target language,
it is displayed next to the language's name in this drop-down box. For languages
that have not yet any translations, this is intended as a hint: you may of course
decide for a different character set (see below), but the iso-* sets are
prefered.

[title]
*admin_translations#

[text]
If we found no character set defined for the selected language, phpVideoPro
assumes iso-8859-1, which might look strange when you e.g. entered Japanese and
then see the results. In such a case, I recommend to just export the result-file
right on this page (without any translations being made), edit the one-and-only
SQL line in that file to have it reflecting the character set you intend to use,
and then go to the "*admin# -&gt; *configuration#" page and reload your new
created file. The same applies if you want to start with a complete new set of
translations for an existing language, using a different character set: in this
case, additionally delete all translations in that file and just leave the first
SQL statement in.

[text]
Now we are ready to proceed. Should be quite easy on this page: you only can
edit the translations for the selected language. Before switching to the next
page using the control elements you already might now from various other screens,
e.g. from the "*medialist#", make sure to save any changes/additions you've
made here using the "*update#" button.

[text]
One more word: you must <b><i>not</i></b> add a translation if it is the same
as the English phrase displayed in the "*orig_trans#" column -- if there's no
translation found for your language, that value is used either.

[title]
Finnished editing?

[text]
So now it's time to save your work to disk. For this, you should use the link
provided next to the "*update#" button at the very end of the page, labeled
"*save_lang_file#". This way you have your work ready for new installations.
At this place it would be a nice guesture to send a copy to the author of
phpVideoPro (for the EMail address, see the <code>doc/README</code> file). You
participate free from the development of the program - so here's an easy way to say
"thank you" :-)

[eof]
