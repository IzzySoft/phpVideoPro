# /* view entry */
# /* $Id$ */

[title]
Introduction

[text]
This form displays all available details of the selected entry. Normally there
should be no explanation necessary, since you should now the meaning of all
data you entered yourself (if you didn't, you may want to have a look at the
help page for "<A HREF="{PHP_SELF}?topic=add_entry">*add_entry#</A>"), but...

[title]
IMDB information

[text]
If you want to obtain closer information about an actor, director or composer:
just click on the button holding his/her name (or first name, doesn't matter).
This will open a new browser window which links to the Internet Movie DataBase
(IMDB) handing over the name, first name and occupation information from
phpVideoPro. If this information is unambiguous (i.e. it matches exactly one
person in the IMDB), this will bring you directly to the page with the desired
information. Otherwise, the IMDB site will prompt you for additional
information: this may be a list of people that matched your request, or
something else if e.g. nothing was found.
[text]
Since the IMDB is an independent service/product, phpVideoPro can't affect the
information available there - i.e. we are not responsible for this, and we
won't change the information there :-) But some of us felt it may be a nice
feature to bring you these informations on just a single mouse click...

[title]
Label printing

[text]
The selection box titled "*print_label#" allows you to print a label for the
selected medium. It contains a number of templates available, and will print
title and time of <b>all</b> movies on the selected medium (if you are e.g.
displaying "RVT 1234-2", and the tape 1234 additionally contains parts 1 and
3, the label contains all three movies), but is at this time (v0.2.4) limited
to a number of 4 lines, i.e. movies per medium. This may be made configurable
lateron.

[text]
To create your own labels, simply put them into the "labels/" directory. The
.config file is needed always and describes the size of the labels plus the
size and position of the contained areas. If a .png file with the same name
exists, it will be used - otherwise a plain (white) template is created (and
labeled, of course). For details, see <A HREF="{PHP_SELF}?topic=howto_label">*howto_label#</A>.

[eof]

