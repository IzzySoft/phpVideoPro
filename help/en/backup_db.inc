<? /* administration of categories */ ?>
<? /* $Id$ */ ?>

[title]
*preferences#

[text]
There are two types of backups possible: a full database backup
("*backup_db_complete#") will backup the entire database of phpVideoPro, i.e.
all data from all tables. The structure will <b><i>not</i></b> be backed up --
there's no need for since the structure is kept in the installation scripts.
[text]
A second backup type is to save the movie relevant data only
("*backup_db_movie_internal#"). This will only backup the data you entered for
your movies, i.e. the actors, directors, comments etc..
[text]
While the first type will result in a plain SQL command file, the latter will
store the data in a phpVideoPro internal format. This way it is possible to
even transfer data between different database types, e.g. to migrate from
PostgreSQL to MySQL or vice versa. For this type of data, the interface also
offers a "Restore" command ("*restore_db_movie_internal#").

[title]
Backup

[text]
Chose the type of backup you want to create. The checkbox "*backup_compress#"
tells phpVideoPro to compress the output file. This will only work if your
installation of PHP is compiled with <code>gzip</code> support. If this is not
the case, you will see an error when you try to enable it.

[text]
After having pressed the "*button_backup#" button, your browser will prompt
you for a location to save the backup file to. Until then, it may take a while,
depending on the size of your database.

[title]
Restore (movies)

[text]
To restore a movie backup, you first must place the backup file in the
directory you configured in the <code>inc/config.inc</code> file. Keep the files
extension to ".pvp" and make sure it is readable by your web server. When you
then load the page, the file should show up in the selection box: just select
it, press the "*button_restore#" button and wait until the restore process is
finnished (you will see the result just below the page title then).

[text]
phpVideoPro will automatically detect whether the backup file was compressed
and care for de-compression in that case. As for now, you will have to chose
the "*clean_restore#" checkbox (if your database isn't already empty), since
otherwise the restore would result in conflicts due to duplicate MediaNumbers.

[text]
The restore process will also detect new categories automatically. This means,
if you import a movie backup from a different installation, where new categories
may have been added, phpVideoPro takes care for this fact, too. Whether a
category is already available with your installation will be decided based on
the <i>*cat_internal_name#</i> (see <i><A HREF="{PHP_SELF}?topic=admin_cats">*admin_cats#</A></i>),
so make sure to not change this name for any existing category. If a new category
is detected, it will be added to the categories table with a new id and the
provided <i>*cat_internal_name#</i>. The translation provided with this
category will always be added to the <i><b>English</b></i> language - this is
not a bug but a feature: we always need an English translation for fallback,
so that users have a term available regardless of their prefered language setting.
You may edit the translation later using the translation editor (see
<i><A HREF="{PHP_SELF}?topic=admin_translations">*admin_translations#</A></i>).

[title]
Restore (full)

[text]
There are two ways to do the setup for backups created with the
("*backup_db_complete#") option. You first have to create the target database,
as always on a new installation. If you are done with this step, you can execute
the sql file via your servers sql shell in the created database (or use any
frontend to your database to do so, e.g. phpMyAdmin). Alternatively, you can
let phpVideoPro do this:

[text]
Put the SQL file into the setup/ directory. Rename it to "restore.sql". Finally,
act as if you where doing a fresh installation - just select "restore" instead
of "create". That's it.

[title]
Why is there no "Restore Database" menue item?

[text]
Easy to explain: of course I could put such an item there. But it wouldn't
help you much: if your database is intact, you will not need to restore, will
you? And if it is not intact, phpVideoPro wouldn't start up correctly - i.e.
you could not use this menue item...

[eof]
