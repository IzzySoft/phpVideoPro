<? /* administration of categories */ ?>
<? /* $Id$ */ ?>

[title]
*preferences#

[text]
phpVideoPro bietet zwei verschiedene Backup-Typen: ein Backup der kompletten
Datenbank ("*backup_db_complete#") sowie ein Backup ausschließlich von für die
Filme relevanten Daten, die vom Benutzer erfasst wurden (also Filmtitel,
Schauspieler, Regisseure, Kommentare etc.pp.). Datenbank-Strukturen werden bei
<b><i>keinem</i></b> der beiden Typen mit gesichert -- diese sind ohnehin in
den Installations-Skripten verankert.

[text]
Während das Komplett-Backup als reine SQL-Datei erstellt wird, erfolgt das
"Film-Backup" in einem eigenen internen Format von phpVideoPro. Auf diese
Weise soll u.a. erreicht werden, dass die Daten auch versions- und
datenbankübergreifend verwendbar sind. Es läßt sich also somit auch eine
Migration der Daten zwischen MySQL und PostgreSQL realisieren.

[title]
Backup

[text]
Hierfür ist einfach der gewünschte Typ (s.o.) auszuwählen. Optional ist noch
eine Kompression der Backup-Datei möglich, sofern die verwendete Installation
von PHP mit Unterstützung für <code>gzip</code> kompiliert wurde (einfach
ausprobieren - schlimmsten Falles gibt es halt eine Fehlermeldung). Nach einem
"Klick" auf den mit "*button_backup#" beschrifteten Button dauert es je nach
Größe der Datenbank jetzt  ein Weilchen, bis der Browser zum Speichern der Datei
auffordert.

[title]
Restore (Filmdaten)

[text]
Hierfür ist die Sicherungsdatei in dem in der Datei <code>inc/config.inc</code>
angegebenen Verzeichnis abzulegen. Die Dateierweiterung ".pvp" muss beibehalten
werden. Darüber hinaus muss sicher gestellt sein, dass der Webserver für
selbige über die nötige Leseberechtigung verfügt. Wird nun die Backup-Seite
geladen, sollte die Datei in der Auswahlliste erscheinen. Dort ist sie nun
zu selektieren, und anschließend der Button "*button_restore#" zu betätigen.
Nach einer von der Größe des verwendeten Backups abhängigen Zeit sollte die
Seite automatisch neu geladen werden, und der (Miß-) Erfolg läßt sich an der
Zeile direkt unterhalb der Überschrift ablesen.

[text]
phpVideoPro erkennt beim Laden der Datei, ob diese komprimiert ist, und entpackt
sie gegebenenfalls. Die Checkbox "*clean_restore#" muss derzeit auf jeden Fall
angewählt sein - andernfalls kommt es ziemlich schnell zu dem Fehler, dass eine
duplikate MediaNr auftritt.

[text]
Der Restore-Prozess erkennt auch automatisch neue Kategorien. D.h., wenn z.B.
ein Backup von Filmdaten aus einer anderen Datenbank, in der neue Kategorien
hinzugefügt wurden, importiert wird, werden diese in der aktuellen Datenbank
auch automatisch angelegt. Die Entscheidung, ob es sich um eine neue Kategorie
handelt, wird auf Basis des <i>*cat_internal_name#</i> getroffen (siehe
<i><A HREF="{PHP_SELF}?topic=admin_cats">*admin_cats#</A></i>) - daher sollte
sicher gestellt werden, dass dieser für vorhandene Einträge nicht geändert
wird. Wird eine neue Kategorie gefunden, so wird diese mit einer neuen ID und
dem gegebenen <i>*cat_internal_name#</i> in die Kategorien-Tabelle eingefügt.
Die ebenfalls im Datensatz gespeicherte Übersetzung wird immer der
<i><b>Englischen</b></i> Sprache zugeordnet - dies ist kein Bug, sondern ein
Feature: Eine Englische Übersetzung wird generell als "FallBack" benötigt,
damit jedem Benutzer - unabhängig von der von ihm gewählten Sprache - eine
Übersetzung zur Verfügung steht. Natürlich können diese Übersetzungen später
unter Zuhilfenahme des Translation Editors (siehe <i><A HREF="{PHP_SELF}?topic=admin_translations">*admin_translations#</A></i>;
zu finden im Administrations-Menü) bearbeitet werden.

[title]
Restore (komplett)

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

[title]
Warum gibt es denn keinen Menüpunkt für die Wiederherstellung?

[text]
Diese Frage läßt sich einfach beantworten: er macht keinen Sinn. Ist die
Datenbank intakt, wird er nicht benötigt. Und ist sie nicht mehr intakt,
startet phpVideoPro nicht mehr richtig - und das Menü ist gar nicht da, kann
also auch nicht benutzt werden...

[eof]
