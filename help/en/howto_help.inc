# /* How to create a help file */
# /* $Id$ */

[title]
How do I generate my own help pages?

[text]
It's even easier than the creation of a new language file - especially after
the changes made for v0.2 when the help pages became template driven. Now you
don't even need to know HTML - you can just edit a simple text file which
<b>may</b> contain some makro/HTML code, but doesn't have to:
[text]
<OL>
 <LI>go to the help directory, open help_topics.php with your favorite file
     viewer (again, this is a plain text file). The structure of this file is
     self explaining: a line starting with "headline" marks a headline, a topic
     starts with "li". The first item within the brackets is the help topic.
     Look for the name of the topic you want to create a help file for.
 <LI>If there is not a single help file available for your language yet, you
     will have to create the appropriate directory for your language first.
     Find the language code for your language (see
     "<A HREF="{PHP_SELF}?topic=howto_lang">*howto_lang#</A>" on how to do
     this), and create the directory with the name of the language code below
     the help directory - e.g. "lang/fi" for Finnish.
 <LI>Now either create a new file with the name <topic>.inc in your languages
     directory (e.g. "lang/fi/about.inc" for the Finnish "About" topic), or
     copy it from the English tree (lang/en) as a template.
 <LI>Open your new help file ("lang/fi/about.inc" in the above example) with
     your favorite editor and translate/create the help topic. The format of
     such a file is explained below.
 <LI>That's all - you are done! phpVideoPro will automatically find and use the
     help file of the defined primary language first. Don't worry if you have
     not <b>all</b> help files available for your language: if phpVideoPro
     can't find a help file in your primary language, it will display the
     English one by default.
  </OL>

[title]
File format
[text]
The general format used for the help files is very simple: every line starting
with a hash mark ("#") is treated as comment (i.e. is completely ignored). The
first line the parser starts with has to be a line containing only the [title]
tag
 (leading and trailing spaces are ignored). The parser stops at the [eof]
tag and then (and only then) sends the help file to your browser. The third
tag that's a must is the [text] tag. Tags <b>must</b> be placed on separate
lines to be identified (again, leading and trailing spaces are ignored)!<br>So
now, what do they mean?
[text]
<ul>
 <li><b>[title]</b> marks a headline. Everything following this tag (up to the
     next tag, which in most cases will be [text]) is treated as headline for
     the following ([text]) block.
 <li><b>[text]</b> starts a text block - here goes the information with all its
     details. To achieve several "paragraphs", just start several [text]
     blocks one following the other.
 <li><b>[eof]</b> means "End Of File" and tells the parser to now really
     generate the output. It furthermore tells it that there's nothing more of
     any interest to him :)
</ul>
[text]
You may use any HTML formatting code e.g. to emphasize phrases with the
&lt;B&gt;bold&lt;/B&gt; mark, generate lists with &lt;UL&gt;, place tables,
graphics etc. I don't explain how to do that - there are better manuals
available on this topic. Again, you don't <b>have</b> to use this, but you
<b>may</b>.

[title]
Makros

[text]
There are some makros available within the help files. They can be devided into
two categories: variables and translators. If you are a bit more familiar with
PHP (and even with the code of phpVideoPro), you may want to use these.
[text]
Everything put between {curly braces} is replaced by the global
variable with this name (if available). This variable must e.g. not contain any
blanks etc. (see PHP manual on this).
[text]
Everything that is in German BTX style put between an *asterisk and an #hash
mark (again, no spaces!) indicates to the parser that it has to be translated
using the phrases defined by the language files. Of course, it follows the
rules of phpVideoPros translation system.

[eof]
