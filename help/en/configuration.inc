<? /* configure */
 ?>
<? /* $Id$ */ ?>

<H2 Align=Center>Configure phpVideoPro</H2>

<Table Width=90% Align=Center>
 <TR><TD>
  <P Align=Justify>On this screen you set up global defaults for phpVideoPro,
   such as language specific settings, colors to use etc.</P>
  <H3>Language specific stuff</H3>
  <P Align=Justify><b>Language to install:</b> Of course, you only can install
   available languages - phpVideoPro does not belong to the category of AI and
   can't create new languages on the fly :) Which languages are available, is
   decided based on some database entries - we will discuss this later in the
   section on "Howto create a new language". For now it's enough to know,
   phpVideoPro looks up the database for available languages, and then for
   languages already installed. The latter are substracted from the first
   amount, and the difference is put into this select box. If you don't see
   any select box here (but a string telling you that there's no additional
   language available), the result of above formula was zero, and all
   available languages are already installed.</P>
  <P Align=Justify><b>Refresh language:</b> If you got a new language file
   for a language you already have installed, containing corrected and fresh
   added phrases, you need a way to replace the old phrases. This is e.g. the
   case when you update from a previous version of phpVideoPro. For the
   language you select here, all phrases are deleted from the database, and
   the new language file is imported instead. At some point in the future I
   may add a function to only add new phrases and not delete anything from
   the db - but that's not done yet.</P>
  <P Align=Justify><b>Primary language:</b> Amongst the installed
   languages, you can select your favorite one. If your native language is
   available, I guess you'ld prefer that :) For all phrases missing in your
   favorite languages file, there will be a "fall-back" to the English phrase.
   If the English phrase is missing as well (which should not happen, unless
   the import of the English lang file failed), there's some "debug phrase"
   displayed from which you can guess the content. If this should happen,
   and you are sure it's not your fault (e.g. since you removed the English
   phrases from the db manually ;) - please drop me a note, quoting the
   missing phrase and where the error occured.</P>
  <P Align=Justify><b>Charset</b>: since this affects the entire display, you
   should only change this setting if you now what you are doing. On the other
   hand, you can't do any harm with it - just the text displayed may look a
   bit strange if you entered some weird setting.<br>
   But if you created a new language file containing special characters, this
   is the switch for you to get them displayed. Since I never had the need for
   it, I'ld be interested in the results.</P>
  <H3>Colors</H3>
  <P Align=Justify><b>Page Background / Table Headers Background:</b> These
   settings are rendered into the (default) stylesheet, and the names are
   self explaining.</P>
  <P Align=Justify><b>Feedback "OK" / Feedback "Failure":</b> These settings
   are not rendered into any stylesheet. They are used for system responses
   on user request, i.e. statements like "entry created successfully" when
   creating a new entry in the database, or "Error &lt;some description&gt;"
   when something went wrong, to emphasize these messages in context to the
   regular form data they are displayed with.</P>
  <P Align=Justify>
</P>
  <P Align=Justify>
</P>
 </TD></TR>
</Table>

