<? /* add_entry */
 ?>
<? /* $Id$ */ ?>

<Table Width=90% Align=Center>
 <TR><TD>
  <P Align=Justify>Using this menu item, you can insert a new entry into your
   video database. Most fields in this form are self-explanatory; but there
   are a few that require some comment (beside the fact that the unnamed input
   box on top is intended to keep the movies title ;):</P>
  <H3>MediaType</H3>
  <P Align=Justify><IMG SRC="<? echo $base_url ?>help/img/mtype_nr.png"
   ALT="piece of 'add entry' menue: mediatype" ALIGN=LEFT HSPACE=5>The box "MediaType" (marked red
   in the image displayed) offers you a list of available media types to select
   from. This box itself won't need any explanation, I guess - but I want to
   draw your attention to the other two marks: there is a two-part MediaNr to
   be entered (marked blue). The first part stands for the physical media, e.g.
   tape or disk. The second part applies to the movie on that medium. Let's
   say, you've recorded two movies on tape # 20, so the first movie should be
   20-1 and the second 20-2.</P>
  <P Align=Justify>Now for the feature: Let's assume you've just recorded
   two movies on an empty tape, and now you want to create the database
   entries for them. Are you sure you remember the last (physical) MediaNr
   you assigned? The green marked box assists you in finding out the last
   assigned number <b>for each media type</b>! Just open it to view all its
   content. For the creation process, it doesn't matter at all what value
   you've selected - the green marked box is for your information only, its
   content is not stored anywhere in the database.</P>
  <P Align=Justify>But a last word on the blue marked MediaNr: the combination
   of the numbers entered here, i.e. the physical tape and the logical unit
   on it, together with the selected MediaType, have to be unique throughout
   the entire database. There is, e.g., only one DVD #1 in your collection,
   the next DVD should be #2 then a.s.o.. This program is not intended for
   managing some video store or commercial video tape library, but for
   private collections only :)</P>
  <H3>Aquiration date</H3>
  <P Align=Justify>As for now, the date fields follow this format: four digit
   year, minus-sign, two digit month, minus sign and two digit day (resulting
   in the scheme YYYY-MM-DD). For a new entry, this field is pre-set with the
   recent date. I leave the scheme in this state for now, since it is
   sufficient to me - and as long as no one asks me for a change, I'll not
   be changing it :)</P>
  <H3>Categories</H3>
  <P Align=Justify>The category selected in the first box will be displayed
   along with the main movie data in the lists. Nevertheless, if you are
   searching for an entry (for now by using the filter function) specifying
   a category, all three categories will be taken into account.</P>
  <H3>Staff</H3>
  <P Align=Justify>Be careful to fill in the information into the right
   fields here: the first is always for the family name, the second for the
   first name. Names of staff members are not stored together with the
   movie data, but in a separate table. With the movie data, there's only a
   reference stored - so if you later go to list some entries for a specific
   person (with a function not available <b>yet</b>), you may run into
   trouble: on the demo site, I already saw entries keeping both name parts
   in one field, just to store two persons into one entry. Of course you
   <i>can</i> do so - but it's not the way I planned it, and some future
   features may not consider this possibility.</P>
  <P Align=Justify>Additionally, there's a checkbox attached to each name,
   titled "In List". This, too, refers to a planned feature: there will be
   the possibility to list up, e.g., all actors together with the title of
   the movies they played a role in. By marking this checkbox, you can
   decide if this movie shall be displayed for this actor. If, for example,
   your favorite actor now plays very serious roles - but did play in some
   se* movies before which you just recorded for, humm, let's say "interest",
   but nobody but you shall now (when reading your printed tape lists), you
   just uncheck the box here and (s)he will not appear together with this
   films title in the actors list.</P>
 </TD></TR>
</Table>

