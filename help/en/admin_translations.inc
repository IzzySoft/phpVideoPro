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
we create a whole new set at this place. The character set used will be the
most common for the selected language, as long as we have some iso-8859-* type
of character set here.

[title]
*admin_translations#

[text]
If we found no character set defined for the selected language, phpVideoPro
assumes iso-8859-1, which might look strange when you e.g. entered Japanese and
then see the results. In such a case, I recommend to just export the result-file
right on this page (even without translations), edit the one-and-only SQL line
in that file to have it reflecting the character set you intend to use, and then
go to the "*admin# -&gt; *configuration#" page and reload your new created file.

[text]
Now we are ready to proceed. Should be quite easy on this page: you only can
edit the translations for the selected language. Before switching to the next
page using the control elements you already might now from various other screens,
e.g. from the "*medialist#", make sure to save any changes/additions you've
made here using the "*update#" button.

[text]
One more hint: it will be hard to edit a language you are not currently using
as your default language when it uses a different character set. In this case I
recommend you to first make it your default language, so all characters are
displayed correctly.

[title]
Finnished editing?

[text]
So now it's time to save your work to disk. For this, you should use the link
provided next to the "*update#" button at the very end of the page, labelled
"*save_lang_file#". This way you have your work ready for new installations.
At this place it would be a nice guesture to send a copy to me, the
<A HREF="mailto:izzysoft@qumran.org">author</A> of phpVideoPro. You participate
free from the development of the program - so here's an easy way to say
"thank you" :-)

[eof]
