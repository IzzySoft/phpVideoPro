<? /* administration of categories */
 ?>
<? /* $Id$ */ ?>

[title]
*preferences#

[text]
phpVideoPro bietet zwei verschiedene Backup-Typen: ein Backup der kompletten
Datenbank ("*backup_db_complete#") sowie ein Backup ausschließlich von für die
Filme relevanten Daten, die vom Benutzer erfasst wurden (also Filmtitel,
Schauspieler, Regisseure, Kommentare etc.pp.). Die Sicherung erfolgt in SQL
Datendateien -- also reine Textdateien, welche SQL Kommandos enthalten.
Datenbank-Strukturen werden <b><i>nicht</i></b> mit gesichert -- diese sind
ohnehin in den Installations-Skripten verankert.
[text]
In einer Variante des zweiten Backup-Typs ("*backup_db_moviedel#") werden in der
SQL-Datei zusätzlich Löschbefehle aufgezeichnet, die vor dem Einfügen der neuen
Daten die Zieltabellen leeren.

[title]
Backup und Restore der Datenbank

[text]
Wie bereits zu lesen war, wird mittels selbigem ein SQL Script generiert,
welches dann z.B. für eine Neuinstallation verwendet werden kann. Hier kommt
nun die Erklärung für das Einspielen dieses Backups.

[text]
Dafür gibt es mindestens zwei Möglichkeiten. Auf jeden Fall ist für das Restore
eines Komplett-Backups ("*backup_db_complete#") zunächst eine neue (leere)
Datenbank anzulegen, in welcher die Tabellen dann erstellt und gefüllt werden.
Anschließend kann dann ein beliebiges FrontEnd für die Zieldatenbank (z.B.
phpMyAdmin) verwendet werden, um das Script in dieser Zieldatenbank auszuführen.
Oder aber, wem das lieber ist: auch phpVideoPro selbst kann dafür benutzt werden.

[text]
In letzterem Falle ist das Script im setup/ Verzeichnis unter dem Namen
"restore.sql" abzulegen. Abschließend ist zu verfahren, wie bei jeder
Neuinstallation von phpVideoPro - nur anstelle von "create" ist halt "restore"
zu wählen.

[text]
Für das Wiederherstellen der Daten aus einem "Teil-Backup" (mit nur
Film-relevanten Daten) muss derzeit noch auf die eigenen FrontEnds der genutzten
Datenbank selbst (also MySQL/PostgreSQL) verwiesen werden. Eine zukünftige
Version von phpVideoPro wird evtl. dafür eine Schnittstelle anbieten.

[title]
Warum gibt es denn keinen Menüpunkt für die Wiederherstellung?

[text]
Diese Frage läßt sich einfach beantworten: er macht keinen Sinn. Ist die
Datenbank intakt, wird er nicht benötigt. Und ist sie nicht mehr intakt,
startet phpVideoPro nicht mehr richtig - und das Menü ist gar nicht da, kann
also auch nicht benutzt werden...<BR>
Außerdem könnte jeder, der Zugriff auf diesen Menüpunkt hat, die Datenbank
überschreiben. Keine gute Idee - eher ein Sicherheitsrisiko.

[eof]

