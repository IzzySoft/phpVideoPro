<? /* administration of categories */
 ?>
<? /* $Id$ */ ?>

[title]
Database Backup and Restore

[text]
As you already have read on the main screen, via this form a SQL script will
be generated, which you then can use to setup a fresh installation. Here comes
the explanation on how to do this setup.

[text]
There are two ways to do the setup. For both of them, you first have to create
the target database, as always on a new installation. If you are done with this
step, you can use the sql file via your servers sql shell and execute it there
in the created database (or use any frontend to your database to do so, e.g.
phpMyAdmin). Alternatively, you can let phpVideoPro do this.

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
Moreover, anybody with access to this menue item could overwrite your database
then. I guess, that's not in your interest.

[eof]

