<? /* administration of categories */
 ?>
<? /* $Id$ */ ?>

[title]
Backup und Restore der Datenbank

[text]
Wie bereits in dem Formular zu lesen war, wird mittels selbigem ein SQL Script
generiert, welches dann z.B. für eine Neuinstallation verwendet werden kann.
Hier kommt nun die Erklärung für das Einspielen dieses Backups.

[text]
Dafür gibt es mindestens zwei Möglichkeiten. Auf jeden Fall ist zunächst eine
neue (leere) Datenbank anzulegen, in welcher die Tabellen dann erstellt und
gefüllt werden. Anschließend kann dann ein beliebiges FrontEnd für die
Zieldatenbank (z.B. phpMyAdmin) verwendet werden, um das Script in dieser
Zieldatenbank auszuführen. Oder aber, wem das lieber ist: auch phpVideoPro
selbst kann dafür benutzt werden.

[text]
In letzterem Falle sind jedoch noch ein paar Vorbereitungen nötig: zunächst
ist das Script im setup/ Verzeichnis unter dem Namen "tech_data.sql" abzulegen
(die vorhandene Datei ist dabei zu überschreiben). Dann müssen die beiden
Dateien "categories.sql" und "lang_en.sql" geleert und anschließend mit
mindestens zwei Zeilen, die jeweils mit einem "#" beginnen, wieder gefüllt
werden (andernfalls kommt es zu Fehlermeldungen). Abschließend ist zu
verfahren, wie bei jeder Neuinstallation von phpVideoPro.

[title]
Warum gibt es denn keinen Menüpunkt für die Wiederherstellung?

[text]
Diese Frage läßt sich einfach beantworten: er macht keinen Sinn. Ist die
Datenbank intakt, wird er nicht benötigt. Und ist sie nicht mehr intakt,
startet phpVideoPro nicht mehr richtig - und das Menü ist gar nicht da, kann
also auch nicht benutzt werden...

[eof]

