# /* How to create a new label (set) */
# /* $Id$ */

[title]
*intro#

[text]
The following applies to the <b>OLD</b> label system - not to the PSLabels! For
the latter, please <a
href='https://github.com/IzzySoft/phpVideoPro/wiki/CustomizingManual#ps-labels'
target='_blank'>see here</a>.

[text]
Labels are created/configured within the "<code>labels/</code>" directory.
There are (at least) two files to consider. One is the configuration file
(<code>*.config</code>), and one (optional file) is the "empty" label image
(the label as it should look like, just except the data on it - <code>*.png</code>).
Both have to have the same name – if you e.g. call the config file
<code>my_favorite.config</code>, the graphics file to use with this config has
to be called <code>my_favorite.png</code>. If there's no <code>*.png</code> file
available for the <code>*.config</code> file, that's no problem: an empty
template will be created having white background, and the fields specified in
the <code>*.config</code> will be drawn with lines.
[text]
In the <code>*.config</code> file, as you may have guessed, you configure how
the label should look like. Make sure the values you enter here (i.e. width,
height and the coordinates for the fields) match your "empty" label image if
you want to use one.
[text]
Since the config file is included as PHP source, you may use e.g. the PHP
include() command to base a set of labels on the same dimensions. This eases
creation of large sets of labels, using the same size and position of fields
but just differ in motives.

[title]
The configuration file

[text]
So here comes an explanation of the configuration variables you have to use:
[text]
<b>width, height:</b> the size of the label
[text]
<b>maxlines:</b> how many lines of text should be put on the label in maximum.
Useful if you are used to fill the remaining space on tapes with a lot of
VideoClips from MTV :)
[text]
<b>nr_coord, main_coord, symb_coord:</b> the coordinates of the fields using
the "x1,y1,x2,y2" format, where "x1,y1" represents the upper-left and "x2,y2"
the lower-right corner of the field. In the first field we’ll place the medium’s
number (without the media type), the second one holds all the data (see "entry"
below), and the third one is a symbol’s place like I use to have on my labels
(that ship with phpVideoPro). This symbol field is not filled by phpVideoPro
itself.
[text]
<b>entry</b>: this is either a string (if you just need one line of text per
movie, e.g. for VideoTapes side labels) or an array. You can place plain text
in it (will stay the same on all labels), plus use variables to be replaced
by the movies data. Variables are to be marked by curly braces. The next
block contains a list of available variables.
[text]
You can mark one line of the array to hold the title, i.e. using a font
different from the other lines, by making its first character a "*".<br>

[title]
Variables that may be used in the "entry" variable

[text]
<ul>
 <li>title: the movie’s title</li>
 <li>lenght: length of the movie (hh:mm format)</li>
 <li>country, year: *country# and *year#</li>
 <li>counter1,counter2: *counter_start_stop#</li>
 <li>aq_date: *date_rec#</li>
 <li>source: *source#</li>
 <li>actor1,..,actor5: the actors 1..5 (format "firstname lastname")</li>
 <li>actors12: enumeration of actor1 and actor2 ("actor1, actor2"). This
     considers undefined actors as well - so if e.g. actor2 is not set, it
     would be the same as actor1 above. This rule applies to actors35 and
     actors variables as well.</li>
 <li>actors35: same as actors12 but for actor3, actor4, actor5</li>
 <li>actors: same as actor12, but enumerates all (set) actors</li>
 <li>director: *director#</li>
 <li>music: composer of the movie’s soundtrack</li>
 <li>fsk: *fsk#</li>
 <li>cat1,cat2,cat3: the categories</li>
 <li>comment: *comment#</li>
 <li>mtype,mtype_short,cass_id,part: Media type/type abbreviation/number
     and the movie’s relative number on the medium</li>
 <li>color: is it colored or b/w</li>
 <li>pict: 4:3 or widescreen?</li>
 <li>tone: Mono, Stereo, Dolby Digital 5.1, etc.</li>
 <li>tone_short: same in the format "1.0", "2.0" .. "9.1"</li>
 <li>lp: is it *longplay# (*yes# / *no#)?</li>
 <li>commercials: is the movie interrupted by commercials?</li>
</ul>

[eof]
