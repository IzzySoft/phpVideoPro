# /* add_entry */
# /* $Id$ */

[title]
*intro#

[text]
Starting with phpVideoPro v0.5.1, this menu item exists for each configured
media type separately. This was necessary in order to support the different
features supported by some of them, as e.g. *longplay# only for Tapes, or
region codes only for DVDs, and suppressing input fields for features not
supported by the given medium. And that's furthermore the reason, that not
all described fields are available for all media.
[text]
Using these menu items, you can insert a new entry into your video database.
Most fields in this form are self-explaining; but there are a few that require
some comment (beside the fact that the unnamed input box on top is intended to
keep the movies title ;):

[title]
IMDB

[text]
Next to the entry field for the movies title, you find a button for the
"Internet Movie DataBase" (IMDB) - which is a site on the internet where you can
retrieve details to (almost) all movies. If you are editing a (new) movie, a
"click" on that button opens a new window to query against that database. If
the requested movie is found, you can transfer available data from that new
window into this edit screen, which saves you some typing.

[title]
*medianr#

[text]
While the *mediatype# is now already set by the selected menu item (see
"*intro#" above), we still need to set the *medianr#. This is already partly
done by the box prompting you for the mediums number before reaching this
screen. So the only thing still needed is the part number (since each disk or
tape may contain more than one movie). Since v0.5.1, phpVideoPro already guesses
the right part number by checking the database for the latest one given and
assuming, this one will be the next (as is the suggestion concerning the
tape/disk number in the mentioned prompt). In both cases, you are given the
possibility to correct this for the presumably rare cases you need to do so.
The "*last_entry#" button tells you the highest given part number for the
selected medium (or nothing if you just created an entry for a new tape/disk).
[text]
At this place allow me some words on the concept for the media numbers in
phpVideoPro: Its first part stands for the physical media, e.g. tape or disk.
The second part applies to the movie on that medium. Let's say, you've recorded
two movies on tape # 20, so the first movie should be 20-1 and the second 20-2.
The combination of these numbers, i.e. the physical tape and the logical unit
on it, together with the MediaType, have to be unique throughout the entire
database. There is, e.g., only one DVD #1 in your collection, the next DVD
should be #2 then a.s.o.. This program is not intended for managing some video
store or commercial video tape library, but for private collections only :)

[title]
*disk_type# / *counter_start_stop#

[text]
The counter fields are mostly of interest for those of you having video
recorders without an index function (and are only displayed for tapes): you can
enter the counters from the beginning respective ending of your recording here.
Since the only format restriction is a length of 10 characters, it doesn't
matter if you enter plain numeric counter values, or even time codes here -
depending on how your recorder displays the time.
[text]
For all other media (VCD/DVD), you can select the *disk_type# instead. Details
on this are to be found <A HREF="{PHP_SELF}?topic=disktype_change">here</A>.

[title]
*label#

[text]
This is to define wether data for this movie should be printed on the label for
this medium.

[title]
*region_code#

[text]
Regional Codes are somehow specific to DVDs, so these checkboxes are only
available for DVDs. If you don't know what region code your DVD is limited to,
just check nothing here (it will then display "unknown" when you view this
entry later). For region-free DVDs, check the "0" only. For all others, check
the appropriate box(es).

[title]
*commercials#

[text]
Even if this field should be self explaining, some words on the values to
chose: you mark here wether the recording is interrupted by "commercial blocks"
("*yes#") or not ("*no#"), or if you cut those blocks off manually ("*cut_off#").
If you can't remember, you have even the possibility to state your unsureness
here by chosing "*unknown#".

[title]
*date_rec#

[text]
The date field is split in day, month and year fields. As for now, the order
is hardcoded to be day-month-year. Of course this may change with some future
version of phpVideoPro, to use the order configured with the date format
setting in the setup menue, to take country specific settings (or special user
preferences :) into account.

[title]
*audio_ts# / *subtitle#

[text]
Here you can enter the available language tracks for audio (i.e. what language
is <i>spoken</i> in the movie) and subtitles. Especially with DVDs, there can
be multiple tracks available - so we allow to enter multiple tracks here.

[text]
Since the number of available languages worldwide is not that small, but we
want to keep our application handsome, only a selected subset of languages will
show up in the selection boxes. You can customize these via the administration
dialogs (found in the administration menu).

[title]
*categories#

[text]
The category selected in the first box will be displayed along with the main
movie data in the lists. Nevertheless, if you are searching for an entry (for
now by using the filter function) specifying a category, all three categories
will be taken into account.

[title]
*staff#

[text]
Be careful to fill in the information into the right fields here: the first is
always for the family name, the second for the first name. Names of staff
members are not stored together with the movie data, but in a separate table.
With the movie data, there's only a reference stored - so if you later go to
list some entries for a specific person, you may run into trouble: on the
<A HREF="http://www.qumran.org/homes/izzy/software/pvp/demo" TARGET="_blank">demo site</A>,
I already saw entries keeping both name parts in one field, just to store two
persons into one entry. Of course you <i>can</i> do so - but it's not the way
it is intended. You will e.g. encounter problems in this case, when setting
filters: you won't be able to filter for one of the two persons entered, but
just for both of them at the same time in the same combination. Just to mention
one example.

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

[title]
*comments#

[text]
You may put any kind of comments for the movie here. Some special tags are
provided to your convinience: URLs enclosed by [url] and [/url] are made
"clickable", the link will open within a new window. Moreover there are
[img]image-url[/img] and [imgr]right-aligned-image-url[/imgr] tags that make
correct tags to display a given image either left- or right-aligned. You may
nest these tags to make images clickable, e.g. [url][img]picture[/img][/url].
[text]
Some more standard HTML tags are allowed in their original way, such as tags
for bold, underline, italics, linebreaks, paragraphs, lists and horizontal
rulers. All other HTML tags get stripped of - that is to protect your site from
malicious HTML code input.

[eof]
