<? /* How to create a new language file */
 ?>
<? /* $Id$ */ ?>

<H2 Align=Center>How to create a new language file</H2>

<Table Width=90% Align=Center>
 <TR><TD>
  <P Align=Justify>It is not that difficult as you might think, and requires
   only a few steps:</P>
  <OL>
   <LI>go to the setup directory, open tech_data.sql with your favorite
       file viewer (it is a plain text file). At the very end of this file,
       you'll find a list of languages together with their code. To pick an
       example: the line
       <code>INSERT INTO languages VALUES ('fi','Finnish','No');</code>
       lets you know, that Finnish has the language code "fi". Look for
       the language you want to create a language file for, and pick its code.
   <LI>stay with the setup directory. Here you'll also find a couple of language
       files already available. You can recognize them by their file name,
       which follows the mask "lang_??.sql" - where "??" represents the
       two letter language code. Most probably, there's no language file
       for your language yet (would you like to create one otherwise?), so
       you can pick one of the available language files (I recommend the
       English one, lang_en.sql, since this is in most cases the most up-to-date
       language file - besides the German, which will be as up-to-date), and
       copy it to your language file - with above example for Finnish, this
       would be "lang_fi.sql".
   <LI>Now open your new language file ("lang_fi.sql" in the above example)
       with your favorite editor and edit the translation phrases. Each line
       starts with the SQL statement to INSERT - don't touch this ;) The only
       thing you have to edit is the last statement in the brackets (there
       are 3 statements in each bracket, each one enclosed by single quotes):
       translate this to your language.
   <LI>Once you are done with this, you can go and tell phpVideoPro that there's
       a new sheriff in town: start your web browser and open phpVideoPro, then
       go to the configuration menue (Edit -> Configuration), check the box to
       "scan for new language files" and hit "Update" button. A few seconds
       later, the configuration menue should reappear and list your language
       in "Select additional language to install".
   <LI>Select to install your language and hit "Update" again, then you can
       also select this as your primary language - and you are done!
  </OL>
  <P Align=Justify>If you later add/change phrases in your language file and
   need to update it into phpVideoPro, just select it in the configuration
   menue item "Refresh language" box and hit "Update" again - all old phrases
   (for the selected language only, of course) are then deleted from the
   database and will be replaced by the phrases from within your language file.</P>
 </TD></TR>
</Table>

