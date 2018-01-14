If you've got too many DVDs, VideoCDs and video tapes to handle, then you need
a better system! That's exactly why **phpVideoPro** was created. This program is
all you need to get your huge collection under control. It puts your
information at your fingertips.

phpVideoPro was inspired by Bernd Rickers' *VideoPro,* which was available in a
DOS-based clipper application (latest release in 1994) as well as in a Windows
version (starting from about 1993 - this was then known as Video-5). *phpVideoPro*
was designed using PHP because of the cross-platform abilities and the added
plus of having your information available anywhere at anytime.

For more details, please see the documentation in the projects wiki.


### Features
The program allows you to add and change entries as needed - on your request,
it utilizes the [IMDB](http://imdb.com/) (Internet Movie DataBase) to retrieve
information for this task, using the
[IMDBPHP](https://github.com/tboothman/imdbphp) class also available separately
(with *IMDBPHP* being restructured and further developed after the last changes
to *phpVideoPro* this feature might be broken meanwhile, though). *phpVideoPro*
can be configured to display your catalogue at will. You can view your items in
a list containing all of your entries or you can request the program to display
a list of available free space on your homemade video tapes. You can view
details of a specified entry, or display a list of all movies with a certain
actor. Moreover, you can have phpVideoPro printing labels for your media - just
to mention a few examples.

So you are able to keep track of what is what and what you're looking to add to
your closet of treasures! The filter functions help to sort through your
catalogue by creating subsets and finding special entries within your
ever-growing collection, while the statistics page tells you how much it has
already grown…

*phpVideoPro* is widely configurable. Making use of templates in almost all
places, it allows you to adjust its look and feel without any PHP knowledge
(some HTML knowledge is needed for this, however), or to create your own label
design. You can even have *phpVideoPro* talking to you in your own language (if
it not already does) by creating a special language file using the built-in
translation editor (don't forget to place it here afterwards to have it
included with future versions of *phpVideoPro* - and to be mentioned in the "Hall
of Fame").

The program does distinguish between DVDs, VideoCDs and Videotapes - new media
types can be added easily via the administration interface. While you may have
enough tapes and DVDs to open up your own version of Blockbuster, *phpVideoPro*
wasn't designed to cater to video shops. The current release wasn't made to log
multiple copies of the same item. However, multiple simultaneous users are served
together with their own preferences and permissions with the help of cookies
and a built-in session management.


### Requirements
* Database: MySQL and PostgreSQL are supported. Experiments have also been made
  with SQLite, and it seems to work.
* a Webserver with support for PHP (tested only with Apache)
* PHP (version 5 or higher) with support for the selected database


### Future
*phpVideoPro* is not actively developed at the currently. I *might* decide to
pick it up again at some point, but it's rather doubtful my time permits. This
is why I decided to move the code to Github and have the project „archived“
there; feel free to fork it and let me know about further development on your
end.