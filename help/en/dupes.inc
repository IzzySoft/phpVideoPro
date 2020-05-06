# /* dupe checks */
# /* $Id$ */

[title]
*intro#

[text]
phpVideoPro provides you different levels of duplicate checks. In the menu,
you find them listed as<UL>
 <LI>*dupes#</LI>
 <LI>*dupes_strict#</LI>
 <LI>*dupes_own#</LI>
 <LI>*dupes_own_strict#</LI>
</UL>

[text]
The following paragraphs will describe what these different types can do for
you.

[title]
*dupes#

[text]
Duplicate entries simply means, you possible have some movie(s) twice in your
collection. So how we find out about this? The simplest way is to check for
movies having the same name. This is what is done here - nothing else.

[title]
*dupes_strict#

[text]
But as there are so many movies around, it will easily happen that two movies
have the same name, but still are completely different. How we can find out
about these? For obvious reasons, it is not enough to check the name and,
maybe, the length of the movie - since movies are often cut differently, this
may mean nothing. So we use some other indicators. This is not a 100% guarantee,
but we come quit close to what we look for. So for phpVideoPro, when using
"*dupes_strict#", a movie is not considered a duplicate, if one of the following
criteria is met:

[text]
<UL>
 <LI>different *fsk# (this is at least a different version of the movie)</LI>
 <LI>different year (either a remake or really a completely different movie)</LI>
 <LI>different audio tracks, and no movie covers all of the others
     (if you have e.g. your favorite movie in your and in the original
     language on two different media, you would not consider these duplicates,
     would you?)</LI>
</UL>

[title]
*dupes_own# / *dupes_own_strict#

[text]
With phpVideoPro v0.8.1 a new level of multi-user-capability was added: Now
every user has his/her own set of records. But it is possible, that other
users can access your collection - if you gave this permission. If that is the
case, the dupe checks above would consider it a duplicate, if you own the
same movie as your friend does. Well, that <b><i>may</i></b> be fine to find
out which movies both of you own, but is possibly not the wanted behaviour if
you intend to cleanup <b><i>your</i></b> collection.

[text]
So while in the first two items discussed above, phpVideoPro takes all those
records into consideration you have permission to access - here we have the
two functions which do the same, but are restricted to the movies in your own
collection only.

[eof]
