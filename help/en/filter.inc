# /* set_filter */
# /* $Id$ */

[title]
Introduction

[text]
Both menue items, "*set_filter#" as well as "*unset_filter#", are calling the
very same form - with one little difference: "*unset_filter#" will delete all
filters first, so you can start with a fresh form without anything being set.

[text]
If you called the form via the "*admin#" -&gt; "*admin_filter#" menue, you can
setup the user default filter in the database. Otherwise, if cookies are
enabled and the filter form is called via the "*filter#" menue, changes are
stored into cookies and thus don't overwrite the database default. By this
way it is ensured, that multiple users can work simultaneously, each one with
his very own filter settings.

[title]
Filter Rules

[text]
<H4>Items placed in one table cell together</H4>
<OL>
 <li><b>items containing min/max values</b><br>
     These items are connected by AND, so if you e.g. enter "Min 60" and
     "Max 90" for the Length field, this means: all movies with a length
     between 60 and 90 minutes. Of course, if just one value (i.e.: min
     OR max) is specified, only this will be considered.
 <li><b>title</b><br>
     here you may enter any <i>SubString</i> that is contained in the
     title(s) you wish to be displayed; entering "hard" would match the
     Beatles' "A Hard Day's Night" as well as "Die Hard"
 <li><b>other items</b><br>
     all other items are connected by OR, i.e.: checking the boxes RVT
     and OVT for MediaType results in all tapes, regardless if original
     (bought) video or self recorded.
</OL>

[text]
<H4>Combining table cell items</H4>
The single statements (where statement means contents of each table cell, one
cell building one statement) are connected by AND. Checking "DVD" as MediaType
and "Science Fiction" as category thus results in all DVDs with Science Fiction
movies on.

[eof]

