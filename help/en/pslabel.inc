<? /* list of actors, directors, composers */
 ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
As an alternative to the PHP based label generator, which just puts plain text
on some PNG images, the PS Label Generator was introduced by Michael Hasselberg,
who wrote and maintains the code for this "plug-in". Based on PostScript
templates, this gives much more powerful design abilities, not to mention the
added flexibility.

[text]
As pre-requisite to be able of using this powerful engine, you must have a
PostScript processor (and viewer) installed on your (client) machine. For us
Linux users this is no question: I know of no distribution that doesn't ship
with GhostScript (and GhostView) included. On Windows (and some other OS) based
systems, you may need to install this separately. If you want to use the
PostScript Label system, just make sure you have some PS viewer installed on
your client machine.

[title]
*labeltype#

[text]
When invoking the PS Label Creator from the menue, this will be the first thing
you are asked for. The labels created by this engine are proposed to fit on
self-adhesive labels which are available in Computer Stores. The select box
gives you detailed data on the name where you can buy those label sheets (not
the name of the store, but of the label sheets ;). Of course, you can also
print the labels on plain paper and cut and glue them manually. Additionally,
the select box tells you where those labels are supposed to be attached to,
e.g. the side or the top of a VHS video tape. Make your selection, and then
press the "*layout_label#" button to continue to the next step.

[title]
*print_label#

[text]
On this screen you are to enter the media numbers you want to create the label
for. For each medium, you may select a design. While on the previous screen the
<b><i>size</i></b> of the label was defined, here we arrange the "look": what
colors and images should be used. Although most of these designs are named
after categories, this is <b><i>not</i></b> automatically selected by the
category of movies on the requested medium for two reasons: first, you may have
multiple movies of different categories on the same medium, second: when
entering this screen, phpVideoPro doesn't yet know what media numbers you will
enter. Of course, we could work around the second reason with some JavaScript;
but I want to use as less JavaScript as possible in this application ;)

[text]
When you've entered the required media numbers, hit the "*create#" button to
finally create the labels. Don't care for the empty fields, they won't be
printed at all. Not only, as you may notice when experimenting a bit with this,
empty fields will not be "printed", but the "free space" will be exactly at
the same position of the resulting PostScript document, where you left it blank
in the form! This gives you the ability to use the same label sheet another
time, when you didn't print all its labels on the first time.

[eof]

