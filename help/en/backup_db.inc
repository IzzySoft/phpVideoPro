<? /* administration of categories */ ?>
<? /* $Id$ */ ?>

[title]
*preferences#

[text]
There are different types of backups possible:<ul>
 <li><b><i>"*backup_db_complete#"</i></b> will backup the entire database of
     phpVideoPro, i.e. all data from all tables and store the SQL statements
     in a <code>*.sql</code> file. The structure will <b><i>not</i></b> be
     backed up -- there is no need for since the structure is kept in the
     installation scripts.</li>
 <li><b><i>"*backup_db_movie_internal#"</i></b> will only backup the data you
     entered for your movies, i.e. the actors, directors, comments etc.</li>
 <li><b><i>"*backup_db_sysconf#"</i></b> backs up all data you maintain via
     the menu <i>*admin# -&gt; *configuration#</i>, i.e. the system
     configuration and default preferences.</li>
</ul>

[text]
While the first type, as mentioned, will result in a plain SQL command
(<code>*.sql</code>) file, the other backups are storing their data in a
phpVideoPro internal format (<code>*.pvp</code> files). This way it is possible
to even transfer data between different database types, e.g. to migrate from
PostgreSQL to MySQL or vice versa. For this type of data, the interface also
offers a "Restore" command (<i>"*restore_db_internal#"</i>).

[title]
Backup

[text]
Chose the type of backup you want to create. The checkbox <i>"*backup_compress#"</i>
tells phpVideoPro to compress the output file. This will only work if your
installation of PHP is compiled with <code>gzip</code> support. If this is not
the case, you will see an error when you try to enable it.

[text]
After having pressed the <i>"*button_backup#"</i> button, your browser will
prompt you for a location to save the backup file to. Until then, it may take a
while, depending on the size of your database and the type of backup chosen.

[title]
Restore from a <code>*.pvp</code> backup

[text]
To restore from a <code>*.pvp</code> backup, you first must place the backup
file in the directory you configured in the <code>inc/config.inc</code> file.
Keep the files extension to "<code>.pvp</code>" and make sure it is readable by
your web server. When you then load the page, the file should show up in the
selection box: just select it, press the <i>"*button_restore#"</i> button and
wait until the restore process is finnished (you will see the result just below
the page title then).

[text]
phpVideoPro will automatically detect the backup type (movies/system config) and
whether the backup file was compressed. For movies, it will also detect
new categories automatically. This means, if you import a movie backup from a
different installation, where new categories may have been added, phpVideoPro
takes care for this fact, too. Whether a category is already available with
your installation will be decided based on the <i>*cat_internal_name#</i> (see
<i><A HREF="{PHP_SELF}?topic=admin_cats">*admin_cats#</A></i>), so make sure to
not change this name for any existing category. If a new category is detected,
it will be added to the categories table with a new id and the provided
<i>*cat_internal_name#</i>. The translation provided with this category will
always be added to the <i><b>English</b></i> language - this is not a bug but a
feature: we always need an English translation for fallback, so that users have
a term available regardless of their prefered language setting. You may edit
the translation later using the translation editor (see
<i><A HREF="{PHP_SELF}?topic=admin_translations">*admin_translations#</A></i>).

[text]
Moreover, if any imported movie contains an audio or subtitle channel for a
language you did not (yet) activate for audio/subtitle: do not worry -
phpVideoPro takes care for that, too.

[title]
Replace or Append?

[text]
This checkbox only affects the restore of movies. If you restore a system
config backup, the setting of "<i>*clean_restore#</i>" will not be considered
at all.

[text]
If you "screwed up" your database and want to replace all entries, just check
the "<i>*clean_restore#</i>" box. This will first remove all entries from the
database, and then import the new data from your backup file. If you just want
to import an entire database from a different machine as duplicate, do the same.

[text]
If you uncheck this box, all movies from the backup file will be <i><b>appended</b></i>
to your database. This means, phpVideoPro will look up the highest *medianr#
for each media type, increment it by 1, and then starting to add new entries
as if you just copied all the media as well (i.e., movies that have been on the
same medium on the export/backup will stay on the same medium). This also means
that, if you started with a fresh installation, all "gaps" in the *medianr#
resulting from removed media will be closed, and you will start with a straight
line from 1 to n without "gaps" (and, of course, with a lower "highest entry"
number).

[title]
Restore (full)

[text]
There are two ways to do the setup for backups created with the
<i>"*backup_db_complete#"</i> option. You first have to create the target
database, as always on a new installation. If you are done with this step, you
can execute the sql file via your servers sql shell in the created database (or
use any frontend to your database to do so, e.g. phpMyAdmin). Alternatively,
you can let phpVideoPro do this:

[text]
Put the SQL file into the setup/ directory. Rename it to <code>restore.sql</code>.
Finally, act as if you where doing a fresh installation - just select
"<i>restore</i>" instead of "<i>create</i>". That's it.

[title]
Why is there no "<i>Restore Database</i>" menue item?

[text]
Easy to explain: of course I could put such an item there. But it wouldn't
help you much: if your database is intact, you will not need to restore, will
you? And if it is not intact, phpVideoPro wouldn't start up correctly - i.e.
you could not use this menue item...

[eof]
