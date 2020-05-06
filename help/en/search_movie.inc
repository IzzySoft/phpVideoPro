# /* Movie Search Page */

[title]
*intro#

[text]
Movie Search works similiar to <A HREF="{PHP_SELF}?topic=set_filter">filter
settings</A> – with one big difference: the "filters" here are applied only
once for your actual search, while the others are saved permanently (or until
your cookie expired).

[text]
In fact, when you run this search the criteria you entered are evaluated
together with the filters (that is for this page is just some wrapper to the
complete media list). So you should set up your filters now just to hide
items generally unwanted, and when looking for something special, come back
here.

[title]
Search criteria and matches

[text]
As with the above discussed filter settings, the criteria here follow the
same rule: fields that allow multiple selections, as e.g. the *mediatype#, are
connected with "OR" -- i.e. if you selected DVD and VCD, both will be evaluated.
Multiple fields are connected with "AND" -- i.e. if you selected DVD and a min
PG of 16, only DVDs rated PG 16 and above are within the result set. Same if
you select e.g. min PG AND max PG -- in this case, BOTH criteria must match.
If you entered nothing into a field, this criteria is not evaluated.

[text]
One more word on those fields you can put in text manually, the "*comments#",
name and "*title#" field: here we search for <b><i>SubStrings</i></b>, and these
are <b><i>case insensitive</i></b>. So the term "babylon" entered into the
"*title#" field matches "Babylon 5" as well as "On the Rivers of Babylon". Be
aware that this is <b>not</b> the case for the "*length#" and "*fsk#" fields.

[title]
Search results

[text]
The result set is displayed in the same manner as the
<A HREF="{PHP_SELF}?topic=medialist">*medialist#</A>, so you may navigate here
as you do there.

[eof]

