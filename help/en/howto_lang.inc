# /* How to create a new language file */
# /* $Id$ */

[title]
How can I create a language file for my native language?

[text]
It is not that difficult as you might think, and requires only a few steps:
[text]
<OL>
 <LI>go to the setup directory, open tech_data.sql with your favorite file
     viewer (it is a plain text file). At the very end of this file, you'll find
     a list of languages together with their code. To pick an example: the line
     <code>INSERT INTO languages VALUES ('fi','Finnish','No');</code>
     lets you know, that Finnish has the language code "fi". Look for the
     language you want to create a language file for, and pick its code.
 <LI>stay with the setup directory. Here you'll also find a couple of language
     files already available. You can recognize them by their file name, which
     follows the mask "lang_??.sql" - where "??" represents the two letter
     language code. Most probably, there's no language file for your language
     yet (would you like to create one otherwise?), so you can pick one of the
     available language files (I recommend the English one, lang_en.sql, since
     this is in most cases the most up-to-date language file - besides the
     German, which will be as up-to-date), and copy it to your language file -
     with above example for Finnish, this would be "lang_fi.sql".
 <LI>Now open your new language file ("lang_fi.sql" in the above example) with
     your favorite editor and edit the translation phrases. Each line starts
     with the SQL statement to INSERT - don't touch this ;) The only thing you
     have to edit is the last statement in the brackets (there are 3 statements
     in each bracket, each one enclosed by single quotes): translate this to
     your language. Of course, the language code has to be changed as well,
     so in our example 'en' has to be replaced by 'fi'.
 <LI>Once you are done with this, you can go and tell phpVideoPro that there's
     a new sheriff in town: start your web browser and open phpVideoPro, then
     go to the configuration menue ("*admin# -&gt; *configuration#"), check the
     box to "*scan_new_lang_files#" and hit the "*update#" button. A few seconds
     later, the configuration menue should reappear and list your language in
     "*select_add_lang#".
 <LI>Select to install your language and hit "*update#" again, then you can also
     select this as your primary language - and you are done!
</OL>

[title]
The phrases for my language seem not suitable to me...

[text]
You may, of course, add/change phrases in your language file. This may only
lead to some complications on updates, where you (at least for now) would have
to check all the phrases again manually. After making changes to the language
file (or receiving an update to it), you need to update it into phpVideoPro:
Just select your language in the <A HREF="{PHP_SELF}?topic=configuration">configuration
menue</A> item "*refresh_lang#" box and hit "*update#" again - all old phrases
(for the selected language only, of course) are then deleted from the database
and will be replaced by the phrases from within your language file.

[eof]
