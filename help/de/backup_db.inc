<? /* administration of categories */
 ?>
<? /* $Id$ */ ?>

[title]
Backup und Restore der Datenbank

[text]
Wie bereits in dem Formular zu lesen war, wird mittels selbigem ein SQL Script
generiert, welches dann z.B. f�r eine Neuinstallation verwendet werden kann.
Hier kommt nun die Erkl�rung f�r das Einspielen dieses Backups.

[text]
Daf�r gibt es mindestens zwei M�glichkeiten. Auf jeden Fall ist zun�chst eine
neue (leere) Datenbank anzulegen, in welcher die Tabellen dann erstellt und
gef�llt werden. Anschlie�end kann dann ein beliebiges FrontEnd f�r die
Zieldatenbank (z.B. phpMyAdmin) verwendet werden, um das Script in dieser
Zieldatenbank auszuf�hren. Oder aber, wem das lieber ist: auch phpVideoPro
selbst kann daf�r benutzt werden.

[text]
In letzterem Falle ist das Script im setup/ Verzeichnis unter dem Namen
"restore.sql" abzulegen. Abschlie�end ist zu verfahren, wie bei jeder
Neuinstallation von phpVideoPro - nur anstelle von "create" ist halt "restore"
zu w�hlen.

[title]
Warum gibt es denn keinen Men�punkt f�r die Wiederherstellung?

[text]
Diese Frage l��t sich einfach beantworten: er macht keinen Sinn. Ist die
Datenbank intakt, wird er nicht ben�tigt. Und ist sie nicht mehr intakt,
startet phpVideoPro nicht mehr richtig - und das Men� ist gar nicht da, kann
also auch nicht benutzt werden...

[eof]
