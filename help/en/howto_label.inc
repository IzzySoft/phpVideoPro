# /* How to create a new label (set) */
# /* $Id$ */

[title]
How can I design my own labels?

[text]
Concerning labels, there are (at least) two files to consider. One is the
configuration file (*.config), and one (optional file) is the "empty" label
image (the label as it should look like, just except the data on it - *.png).
Both have to have the same name - if you e.g. call the config file
my_favorite.config, the graphics file to use with this config has to be called
my_favorite.png. If there's no *.png file available for the *.config file,
that's no problem: an empty template will be created having white background,
and the fields specified in the *.config will be drawn with lines.

[text]
In the *.config file, as you may have guessed, you configure how the label
should look like. Make sure the values you enter here (i.e. width, height and
the coordinates for the fields) match your "empty" label image if you want to
use one.<br>
Since the config file is included as PHP source, you may use e.g. the PHP
include() command to base a set of labels on the same dimensions. This eases
creation of large sets of labels, using the same size and position of fields
but just differ in motives.

[title]
The configuration file

[text]
So here comes an explanation of the configuration variables you have to use:<br>
<b>width, height:</b> the size of the label<br>
<b>maxlines:</b> how many lines of text should be put on the label in maximum.
Useful if you are used to fill the remaining space on tapes with a lot of
VideoClips from MTV :)<br>
<b>nr_coord, main_coord, symb_coord:</b> the coordinates of the fields. In the
first we'll place the mediums number (without the media type), the second one
holds all the data (see "entry" below), and the third one is a symbol's place
like I use to have on my labels (that ship with phpVideoPro). This symbol field
is not (yet) filled by phpVideoPro itself.<br>
<b>entry</b>: this is either a string (if you just need one line of text per
movie, e.g. for VideoTapes side labels) or an array. You can place plain text
in it (will stay the same on all labels), plus use variables to be replaced
by the movie's data. Variables are to be marked by curly braces. Below is a list
of available variables.<br>

[title]
Variables to use in the configuration file

[text]
<ul>
 <li>title: the movie's title</li>
 <li>lenght: length of the movie (hh:mm format)</li>
 <li>country, year: *country# and *year#</li>
 <li>counter1,counter2: *counter_start_stop#</li>
 <li>aq_date: *date_rec#</li>
 <li>source: *source#</li>
 <li>actor1,..,actor5: the actors 1..5 (format "firstname lastname")</li>
 <li>director: *director#</li>
 <li>music: composer of the movie's soundtrack</li>
 <li>fsk: *fsk#</li>
 <li>cat1,cat2,cat3: the categories</li>
 <li>comment: *comment#</li>
 <li>mtype,mtype_short,cass_id,part: Media type/type abbreviation/number
     and the movie's relative number on the medium</li>
 <li>color: is it colored or b/w</li>
 <li>pict: 4:3 or widescreen?</li>
 <li>tone: Mono, Stereo, Dolby Digital 5.1, etc.</li>
 <li>tone_short: same in the format "1.0", "2.0" .. "6.1"</li>
 <li>lp: is it *longplay# (*yes# / *no#)?</li>
 <li>is the movie interrupted by commecials?</li>
</ul>

[eof]

