# /* How to create a new language file */
# /* $Id$ */

[title]
How can I create a language file for my native language?

[text]
It is not that difficult as you might think (in fact, it got quite easy since
v0.4.6), and requires only a few steps:
[text]
<OL>
 <LI>Log in as administrator</LI>
 <LI>Via the menu, go to "*admin# -&gt; *admin_translations#"</LI>
 <LI>Select the language you want to edit and click on "*submit#"</LI>
 <LI>Edit the phrases on the following pages. Make sure to hit the
     "*update#" button on each page when you changed anything or added some new
     translation.</LI>
 <LI>When you're finally done with the last page, you may want to save your
     results to disk. Look at the first SQL statement in that file (starting
     with "UPDATE") and compare the mentioned character set if it matches the
     one you have set on your system. If not, correct it here, go to the
     "*admin# -&gt; *configuration#" page and reload your language file in
     order to sync the charset with the database.</LI>
</OL>

[text]
Now I would appreciate if you send me the resulting file to include it with
future versions of phpVideoPro!

[title]
The phrases for my language seem not suitable to me...

[text]
See above - the steps are exactly the same :-)

[eof]
