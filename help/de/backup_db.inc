<? /* administration of categories */ ?>
<? /* $Id$ */ ?>

[title]
*preferences#

[text]
phpVideoPro bietet verschiedene Backup-Typen:<ul>
 <li><b><i>"*backup_db_complete#"</i></b> sichert, wie der Name bereits
     vermuten lässt, die komplette Datenbank in eine <code>*.sql</code> Datei.
     Die Tabellenstrukturen werden in dieser Datei nicht mit gesichert, da sie
     ohnehin in den Installations-Skripten vorhanden sind.</li>
 <li><b><i>"*backup_db_movie_internal#"</i></b> sichert ausschließlich die für
     Filme relevanten Daten, die vom Benutzer erfasst wurden (also Filmtitel,
     Schauspieler, Regisseure, Kommentare etc.pp.).</li>
 <li><b><i>"*backup_db_sysconf#"</i></b> erstellt eine Sicherung der Daten, die
     im Menü <i>*admin# -&gt; *configuration#</i> verwaltet werden, sowie der
     Druckerkonfigurationen.</li>
</ul>

[text]
Während das Komplett-Backup als reine SQL-Datei erstellt wird, werden die
anderen Sicherungen in einem eigenen internen Format von phpVideoPro
(<code>*.pvp</code> Dateien) gespeichert. Auf diese Weise soll u.a. erreicht
werden, dass die Daten auch versions- und datenbankübergreifend verwendbar sind.
Es läßt sich also somit auch eine Migration der Daten zwischen MySQL und
PostgreSQL realisieren.

[title]
Backup

[text]
Hierfür ist einfach der gewünschte Typ (s.o.) auszuwählen. Optional ist noch
eine Kompression der Backup-Datei möglich, sofern die verwendete Installation
von PHP mit Unterstützung für <code>gzip</code> kompiliert wurde (einfach
ausprobieren - schlimmsten Falles gibt es halt eine Fehlermeldung). Nach einem
"Klick" auf den mit <i>"*button_backup#"</i> beschrifteten Button dauert es je
nach Größe der Datenbank und gewähltem Backup-Typ jetzt ein Weilchen, bis der
Browser zum Speichern der Datei auffordert.

[title]
Restore (nur für <code>*.pvp</code> Dateien)

[text]
Hierfür ist die Sicherungsdatei in dem in der Datei <code>inc/config.inc</code>
angegebenen Verzeichnis abzulegen. Die Dateierweiterung "<code>.pvp</code>" muss
beibehalten werden. Darüber hinaus muss sicher gestellt sein, dass der Webserver
für selbige über die nötige Leseberechtigung verfügt. Wird nun die Backup-Seite
geladen, sollte die Datei in der Auswahlliste erscheinen. Dort ist sie nun
zu selektieren, und anschließend der Button <i>"*button_restore#"</i> zu
betätigen. Nach einer von der Größe des verwendeten Backups abhängigen Zeit
sollte die Seite automatisch neu geladen werden, und der (Miß-) Erfolg lässt
sich an der Zeile direkt unterhalb der Überschrift ablesen.

[text]
phpVideoPro erkennt beim Laden der Datei den Datentyp (Film oder Konfiguration),
und ob die Daten komprimiert sind. Auch neue Kategorien werden automatisch
erkannt - d.h., wenn z.B. ein Backup von Filmdaten aus einer anderen
Datenbank, in der neue Kategorien hinzugefügt wurden, importiert wird, werden
diese in der aktuellen Datenbank auch automatisch angelegt. Die Entscheidung,
ob es sich um eine neue Kategorie handelt, wird auf Basis des
<i>*cat_internal_name#</i> getroffen (siehe
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

[text]
Enthält ein Film Tonspur(en) oder Untertitel in einer Sprache, die dafür (noch)
nicht aktiviert wurde, so trägt phpVideoPro auch dafür Sorge.

[title]
Ersetzen oder Anhängen?

[text]
Die CheckBox "<i>*clean_restore#</i>" bezieht sich nur auf Filmdaten. Auf die
Wiederherstellung eines System-Backups hat sie keinerlei Auswirkungen.

[text]
Sollen alle Einträge in der Datenbank komplett ersetzt werden (etwa, weil gerade
jemand mit phpVideoPro "gespielt" und alles gründlich durcheinander gebracht
hat), so ist einfach die mit "<i>*clean_restore#</i>" beschriftete Box zu
aktivieren. Ist die Box <i><b>nicht</b></i> aktiviert, werden alle Einträge
der importierten Datei an die bestehenden Daten <i><b>angehängt</b></i>. Das
heißt im Klartext:<ul>
<li>phpVideoPro sucht für jeden Medientyp die höchste vergebene Nummer aus
    der Datenbank. Beginnend mit der nächst höheren Nummer, werden allen
    importierten Filmen neue MediaNummern vergeben</li>
<li>Waren zwei Filme beim Export auf dem selben Medium, sind sie dies auch
    nach dem Import - die Prozedur läßt sich mit dem "Kopieren der Medien"
    vergleichen.</li>
<li>Eventuelle Lücken in der Nummerierung werden geschlossen, da "leere Medien"
    ja keine Filme enthalten, und demzufolge im Backup nicht erfasst sind.
    Wer also einfach mal "aufräumen" will: Neu installieren, und trotz leerer
    Datenbank so tun, als wolle man "hinzufügen".</li>
</ul>

[title]
Restore (komplett)

[text]
Dafür gibt es mindestens zwei Möglichkeiten. Auf jeden Fall ist für das Restore
eines Komplett-Backups (<i>"*backup_db_complete#"</i>) zunächst eine neue (leere)
Datenbank anzulegen, in welcher die Tabellen dann erstellt und gefüllt werden.
Anschließend kann dann ein beliebiges FrontEnd für die Zieldatenbank (z.B.
phpMyAdmin) verwendet werden, um das Script in dieser Zieldatenbank auszuführen.
Oder aber, wem das lieber ist: auch phpVideoPro selbst kann dafür benutzt werden.

[text]
In letzterem Falle ist das Script im <code>setup/</code> Verzeichnis unter dem
Namen <code>restore.sql</code> abzulegen. Abschließend ist zu verfahren, wie
bei jeder Neuinstallation von phpVideoPro - nur anstelle von <i>"create"</i> ist
entsprechend <i>"restore"</i> zu wählen.

[title]
Warum gibt es denn keinen Menüpunkt für die Wiederherstellung?

[text]
Diese Frage läßt sich einfach beantworten: er macht keinen Sinn. Ist die
Datenbank intakt, wird er nicht benötigt. Und ist sie nicht mehr intakt,
startet phpVideoPro nicht mehr richtig - und das Menü ist gar nicht da, kann
also auch nicht benutzt werden...

[eof]
