# /* add_entry */
# /* $Id$ */

[title]
Introduction

[text]
Using this menu item, you can insert a new entry into your video database. Most
fields in this form are self-explaining; but there are a few that require some
comment (beside the fact that the unnamed input box on top is intended to keep
the movies title ;):

[title]
MediaType

[text]
<IMG SRC="{base_url}help/img/mtype_nr.png" ALT="piece of 'add entry' menue: mediatype" ALIGN=LEFT HSPACE=5>
The box "MediaType" (marked red in the image displayed) offers you a list of
available media types to select from. This box itself won't need any
explanation, I guess - but I want to draw your attention to the other two marks:
there is a two-part MediaNr to be entered (marked blue). The first part stands
for the physical media, e.g. tape or disk. The second part applies to the movie
on that medium. Let's say, you've recorded two movies on tape # 20, so the first
movie should be 20-1 and the second 20-2.
[text]
Now for the feature: Let's assume you've just recorded two movies on an empty
tape, and now you want to create the database entries for them. Are you sure
you remember the last (physical) MediaNr you assigned? The green marked box
assists you in finding out the last assigned number <b>for each media type</b>!
Just open it to view all its content. For the creation process, it doesn't
matter at all what value you've selected - the green marked box is for your
information only, its content is not stored anywhere in the database.
[text]
But a last word on the blue marked MediaNr: the combination of the numbers
entered here, i.e. the physical tape and the logical unit on it, together with
the selected MediaType, have to be unique throughout the entire database. There
is, e.g., only one DVD #1 in your collection, the next DVD should be #2 then
a.s.o.. This program is not intended for managing some video store or
commercial video tape library, but for private collections only :)

[title]
*date_rec#

[text]
The date field is split in day, month and year fields. As for now, the order
is hardcoded to be day-month-year. Of course this will change in one of the
following versions of phpVideoPro, and this format will be adjustable via the
confirguration menue as well to take country specific settings (or special user
preferences :) into account.

[title]
*counter_start_stop#

[text]
These fields are mostly of interest for those of you having video recorders
without an index function: you can enter the counters from the beginning
respective ending of your recording here. Since the only format restriction
is a length of 10 characters, it doesn't matter if you enter plain numeric
counter values, or even time codes here - depending on how your recorder
displays the time.

[title]
*commercials#

[text]
Even if this field should be self explaining, some words on the values to
chose: you mark here wether the recording is interrupted by "commercial blocks"
("*yes#") or not ("*no#"), or if you cut those blocks off manually ("*cut_off#").
If you can't remember, you have even the possibility to state your unsureness
here by chosing "*unknown#".

[title]
Categories

[text]
The category selected in the first box will be displayed along with the main
movie data in the lists. Nevertheless, if you are searching for an entry (for
now by using the filter function) specifying a category, all three categories
will be taken into account.

[title]
Staff

[text]
Be careful to fill in the information into the right fields here: the first is
always for the family name, the second for the first name. Names of staff
members are not stored together with the movie data, but in a separate table.
With the movie data, there's only a reference stored - so if you later go to
list some entries for a specific person, you may run into trouble: on the
<A HREF="http://www.qumran.org/homes/izzy/">demo site</A>, I already saw
entries keeping both name parts in one field, just to store two persons into
one entry. Of course you <i>can</i> do so - but it's not the way I planned it,
and some future features may not consider this possibility.

[text]
Additionally, there's a checkbox attached to each name, titled "In List". This,
too, refers to a nice feature: there will be the possibility to list up,
e.g., all actors together with the title of the movies they played a role in.
By marking this checkbox, you can decide if this movie shall be displayed for
this actor. If, for example, your favorite actor now plays very serious roles -
but did play in some se* movies before which you just recorded for, humm, let's
say "interest", but nobody but you shall now (when reading your printed tape
lists), you just uncheck the box here and (s)he will not appear together with
this films title in the actors list.

[eof]

