<? /* How to create a help file */
 ?>
<? /* $Id$ */ ?>

<Table Width=90% Align=Center>
 <TR><TD>
  <P Align=Justify>It's even easier than the creation of a new language file:</P>
  <OL>
   <LI>go to the help directory, open help_topics.php with your favorite
       file viewer (again, this is a plain text file). The structure of this
       file is self explaining: a line starting with "headline" marks a
       headline, a topic starts with "li". The first item within the brackets
       is the help topic. Look for the name of the topic you want to create
       a help file for.
   <LI>If there is not a single help file available for your language yet,
       you have to create the appropriate directory for your language first.
       Find the language code for your language (see "<A HREF="<?
       echo "$PHP_SELF?topic=howto_lang\">" . lang("howto_lang") ?></A>" on
       how to do this), and create the directory with the name of the
       language code below the help directory - e.g. "lang/fi" for Finnish.
   <LI>Now either create a new file with the name <topic>.inc in your languages
       directory (e.g. "lang/fi/about.inc" for the Finnish "About" topic),
       or copy it from the English tree (lang/en) as a template.
   <LI>Open your new help file ("lang/fi/about.inc" in the above example)
       with your favorite editor and translate/create the help topic. If you
       want to start with a blank file, please browse the English help files
       first to see the format used (especially, the content of the help
       file (which is HTML) starts <b>after</b> the &lt;BODY&gt; tag and
       ends <b>before</b> the closing &lt;/BODY&gt; tag).
   <LI>That's all - you are done! phpVideoPro will automatically find and
       use the help file of the defined primary language first. Don't worry
       if you have not <b>all</b> help files available for your language:
       if phpVideoPro can't find a help file in your primary language, it
       will display the English one by default.
  </OL>
 </TD></TR>
</Table>

