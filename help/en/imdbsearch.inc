# /* Search IMDB and transfer results to edit screen */
# /* $Id$ */

[title]
*intro#

[text]
The "Internet Movie DataBase" (IMDB) is a site on the internet where you can
retrieve details to (almost) all movies. phpVideoPro can use that site to
gather some data for you, thus saving you some typing work. This is done here.

[title]
Initial screen

[text]
If you already entered the movie title on the edit screen before clicking on the
IMDB button, this screen will be skipped. Instead, phpVideoPro proceeds with
the <a href="#found">next step</a>.

[text]
Otherwise, just enter the name of the movie you are editing into the input
field, and click the associated "<i>*submit#</i>" button. phpVideoPro then will
contact the IMDB and tries to find the requested movie. This may take a while,
depending on the speed of your internet connection (and the response time of
the IMDB).

[text]
In most cases you will be much faster if you know the IMDB ID of the movie.
Enter this in the second field given in this form, and press the associated
button – this will definitively skip the list of movies, and directly lead you
to the <A HREF="#details">details</A> page.

[text]
Hint: You also may enter the IMDB ID into the movie title field on the
<A HREF="{PHP_SELF}?topic=add_entry">*add_entry#</A> form. In this case,
phpVideoPro considers all plain numeric statements longer than 5 digits as
representing an IMDB ID.

[title|1|found]
Movies found

[text]
If we had some luck, our movie was found. If we had much luck, we just found
the correct movie – but there may also be a list of movies found, in case there
is more than one movie with the given name. If you are in doubt, you may click
on some of the IMDB buttons of this screen, which will again open a new window
with the movies page on the IMDB site, so you can check out.

[text]
If you’ve got the right movie, just click on its name. This will bring you to
the next screen with the details we could retrieve from the IMDB. Again, some
patience may be needed - since we have to query the IMDB one more time.

[title|1|details]
Movie details

[text]
If you got here, you’ve obviously been lucky enough to find the information you
were looking for. Now you can select what information you want to use in your
database. You can in/exclude details by (de)activating the associated checkboxes
(how these are set by default, you can define via the
<A HREF="{PHP_SELF}?topic=configuration">*preferences#</A> menu).

[text]
Country and year of production will need no changes, so we take this information
as-is. Concerning the movies title, however, there are sometimes alternatives
presented by the IMDB - so in the title drop-down list, these are added
<b><i>after</i></b> the official title.

[text]
Depending on the country you are living in, the "<b><i>PG</i></b>"
("<i>Parental Guide</i>" – meaning the minimum age of the audience to watch
this movie) may be different. In addition to that, some countries use the same
"ratings" but mean different things: e.g. the rating "PG" can mean everything
between 6 and 12 years, depending on the rating authority. Since someone
visiting your phpVideoPro site does not necessarily know what local authority
to apply to <i>your</i> values, phpVideoPro only supports <i>numeric values</i>
– which also makes it possible to search for PG ranges, without depending on
the country stuff. So if you live in a country using non-numeric PG values, you
may be able to find out a suitable value by comparing the numeric values given
by other countries’ authorities, and by using some common sense. I hope I do
not need any legal disclaimer here – I am not responsible for any data
entered. When in doubt, please consult your local authority :-)

[text]
Next, the recorded <b><i>lenght</i></b> of the movie may be different from the
original one (e.g. due to commercials or cuttings of the TV station), so you
can edit that here as well.

[text]
As for the <b><i>categories</i></b>, phpVideoPro tries to find the matching
values from your DB. This may not always be successful – so use the select boxes
to correct these values if needed. Same applies to the <b><i>director</i></b>:
Sometimes there is more than one director given, but phpVideoPro only handles
one of them – you may have to select the one to use (or select the empty entry
if you do not want to use that information at all).

[text]
Now we come to the <b><i>actors</i></b>. Here the IMDB usually provides us with
a large list of crew members. However, phpVideoPro only can store five of them
at maximum. Again, it is up to you to select which five actors you want to store
with your movie. Holding down the &lt;Ctrl&gt; key of your keyboard while
clicking on the names allows you to (un)select multiple names. In case you mark
more than five names, only the first five marked names will be used.

[text]
Last but not least, we may have a <b><i>picture</i></b> and a <b><i>plot</i></b>.
The picture is automatically transfered from the IMDB and stored on the computer
hosting the phpVideoPro application, so you certainly may want to use it. If
not, just remove the "[img]...[/img]" string from the textarea, and the image
will not show up (it will, however, stay stored on the computer). You may also
decide to remove some or all information from the textarea to your convenience.

[eof]
