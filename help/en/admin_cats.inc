<? /* administration of categories */
 ?>
<? /* $Id$ */ ?>

[title]
Column explanation

[text]
<TABLE ALIGN="center" BORDER="1">
  <TR><TD><B>ID</B></TD>
      <TD>Serial Number (no function)</TD></TR>
  <TR><TD><B>*cat_internal_name#</B></TD>
      <TD>program internal name of the category</TD></TR>
  <TR><TD><B>*category#</B></TD>
      <TD>Name of the categorie in the selected language</TD></TR>
  <TR><TD><B>&nbsp;</B></TD>
      <TD>Delete or suppress a category</TD></TR>
</TABLE>

[title]
Add a category

[text]
If you want to add a new category, just fill in your data into the last (empty)
line of the table. The value in the column <i>*cat_internal_name#</i> should
always start with the string "cat_".

[title]
Remove a category

[text]
For this issue use the trashcan icon. To prevent accidental deletion, a popup
will require you for confirmation. If there's any movie in your database
belonging to that category, you can't remove it - in this case you will get an
error message telling you so, and you have to adjust the movies' settings first.
Use the filters to find the affected movies.

[title]
(De-) Activate a category

[text]
Using the checkbox, you can disable unused categories without deleting them. If
you did so, this page will be the only one you can see those categories: they
will, as long as they stay disabled (unchecked), never appear in the
<i>*edit_entry#</i>, <i>*set_filter#</i> or <i>*search_movie#</i> forms. This
way you may achieve more clearness while still keeping the data.

[title]
Adjust translation

[text]
If you don't like the translation, just enter a different one into the
"*category#" column. 

[text]
One remaining risk is, that with the next update of phpVideoPro you might get
lost of those translations. To prevent this, at this time there's only a
work-around: use the translation editor to save all translations, and before
an update, merge the relevant lines with the new language file. If you stayed
with above mentioned rule to start all entries in the <i>*cat_internal_name#</i>
column with "cat_", they should be easy to identify.

[eof]

