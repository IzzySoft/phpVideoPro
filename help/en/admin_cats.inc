<? /* administration of categories */
 ?>
<? /* $Id$ */ ?>

[title]
Administration of categories

[text]
Here you can edit the categories. If you don't like the translation, just
enter a different one into the "*category#" column. If you want to add a new
category, just fill in your data into the last (empty) line of the table. In
order to remove a category, wipe out all it's data and submit the form. If
there's any movie in your database belonging to that category, you can't remove
it - in this case you will get an error message telling you so, and you have
to adjust the movies' settings first. Use the filters to find the affected
movies.

[text]
One remaining risk is, that with the next update of phpVideoPro you might get
lost of those translations. To prevent this, edit the internal name in the
"*cat_internal_name#" column. It's always a good idea to stay to the rule that
an internal category name has to start with "cat_". However, you theoretically
may enter whatever you like - but then it may conflict with some other
translations, and your update may fail (either the category update on this
screen, since a similiar "key" already exists within the translations table,
or sometime later when you upgrade to a newer version, since <B>I</B>
decided to use the same term). Thus you prevent trouble if you follow my rules :)

[text]
Since on update of a language first all translations belonging to it are removed
from the database, I recommend you to record your changes into a separate
language file. Before updating your language, make sure to add the contents of
this file to the language file shipped, so your changes will remain.

[eof]

