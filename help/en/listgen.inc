<? /* medialist */
 ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
Even though you find this function within the print menue, phpVideoPro does no
printing on its own. There were different ways I thought about printing lists:
first I wanted to realize it via PostScript - no problem for all Unix/Linux
users, but the Windows people probably wouldn't be that happy with it (even
though they could install GhostScript ;) I could use the label function,
declaring the list a huge multi-page label - but this would result in huge
graphic files, and in these hot days the printer wouldn't be happy about that ;)

[title]
How it works

[text]
So here comes the final decision: You may export the generated lists in CSV
style (all fields are separated by tabulators, first line contains field names),
and then import it into your favorite application - either word processing or
spreadsheet. With that application you can do all the formatting (maybe you
create your own template there), and print the resulting file.

[text]
Alternatively, you can chose "ASCII" as output type and open the received file
with some simple text editor (or save it to disk), and just print it from
there - it does not look that fine as the above result may look, but it's
at least somehow formatted plus you get your data on paper in a fast way.

[eof]

