<? /* administration of categories */
 ?>
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
("*backup_db_movies#"). This will only backup the data you entered for your
movies, i.e. the actors, directors, comments etc.. As a variant of this,
"*backup_db_moviedel#" will insert a "DELETE" statement for each table first,
so you can "restore" the so created backup into a running database e.g. via
the MySQL/PSQL command line interface. A future version of phpVideoPro might
have an interface for this as well.
[text]
The result of both backup types will be a plain text file containing SQL
commands.

[title]
Database Backup and Restore

[text]
As you already have read on the main screen, via this form a SQL script will
be generated, which you then can use to setup a fresh installation. Here comes
the explanation on how to do this setup.

[text]
There are two ways to do the setup for backups created with the
("*backup_db_complete#") option (for the other options, see above). For both of
them, you first have to create the target database, as always on a new
installation. If you are done with this step, you can use the sql file via your
servers sql shell and execute it there in the created database (or use any
frontend to your database to do so, e.g. phpMyAdmin). Alternatively, you can
let phpVideoPro do this.

[text]
In the latter case, you have to put the SQL file into the setup/ directory.
Rename it to "restore.sql". Finally, act as if you where doing a fresh
installation - just select "restore" instead of "create". That's it.

[title]
Why is there no "Restore Database" menue item?

[text]
Easy to explain: of course I could put such an item there. But it wouldn't
help you much: if your database is intact, you will not need to restore, will
you? And if it is not intact, phpVideoPro wouldn't start up correctly - i.e.
you could not use this menue item...<BR>
This does in fact not concern "movie only" backups - so there might be some
interface for this with some future version of phpVideoPro, as mentioned above.

[eof]

