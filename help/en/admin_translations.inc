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
*sel_target_lang#

[text]
The first step is to select the language we want to edit. If there are already
translations available within the database, these are loaded then. Otherwise,
we create a whole new set at this place (and all text areas to edit will be
initially empty). Right now, all languages use the UTF-8 character set - do not
worry about this, your browser and web server take care for the conversions from
your local character set.

[title]
*admin_translations#

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
