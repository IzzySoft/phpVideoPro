<? /* change media nr or copy entry */
 ?>
<? /* $Id$ */ ?>

[title]
Why changing the media nr or copy the movie?

[text]
This page allows you to either copy or move a movie to a new medium. There are
several situations in which this makes sense:
<UL>
 <LI>You are going to enter data for a serial, e.g. "Babylon 5", "Star Trek",
     "Friends", since you just bought a box containing a couple of DVDs or
     tapes. I guess it's annoying to type in the same values again and again,
     since e.g. actors will be the same for all parts. So you enter all the
     data once, and then copy the entire entry. If you now go to edit the copy,
     you only have to change the needed facts.
 <LI>Your favorite movie now is available on DVD, and you bought it. You are
     so happy about this fact, that you give the original tape to your best
     friend as a present. Wow. But now, your database still says it's a tape,
     and you don't like it to lie - so you go to change the media nr.
 <LI>You are re-organizing your collection, since you threw away all your
     movies Bruce Willis acted in (Are you nuts?!? Had you told me before, I'ld
     given you my postal address to send ME those DVDs - so better don't tell
     me!!!)...
</UL>

[title]
Explanation of the fields

[text]
<B>*highest_db_entries#</B>: This is just a helper box you already may know
from the <i>*add_entry#</i> Form. It tells you the highest number you've ever
given to your DVDs, VideoCDs or tapes. It has absolutely no effect on the
action taken afterwards.

[text]
<B>*orig_medianr#</B>: Just to verify. If you've called this page by clicking
on the MediaType/MediaNr of a movie, it is preset by its values, and normally
you should not need to change the contents of these fields. If, however, you
plan to copy/move an entry different from this, you can do so here.

[text]
<B>*new_medianr#</B>: This is the target. It is preset to the very same value
as <i>*orig_medianr#</i>; so if you e.g. just deleted movie #2 on a VideoCD and thus
want to renumber #3 to #2, this should make it easy. Make sure to enter correct
values into these fields. However: phpVideoPro won't allow you to overwrite
existing data with this function - so if you accidentally enter an already
existing combination, you'll just get a warning.

[eof]

