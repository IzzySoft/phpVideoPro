<? /* administration of categories */ ?>
<? /* $Id$ */ ?>

[title]
Backup

[text]
phpVideoPro bietet verschiedene Backup-Typen:<ul>
 <li><b><i>"*backup_db_complete#"</i></b> sichert, wie der Name bereits
     vermuten lässt, die komplette Datenbank in eine <code>*.sql</code> Datei.
     Die Tabellenstrukturen werden in dieser Datei nicht mit gesichert, da sie
     ohnehin in den Installations-Skripten vorhanden sind.</li>
 <li><b><i>"*backup_db_movie_internal#"</i></b> sichert ausschließlich die für
     Filme relevanten Daten, die vom Benutzer erfasst wurden (also Filmtitel,
     Schauspieler, Regisseure, Kommentare etc.pp.).</li>
 <li><b><i>"*backup_db_cats#"</i></b> legt eine Sicherung der installierten
     Kategorien an, in der auch alle in der Datenbank verfügbaren Übersetzungen der
     Kategorienamen enthalten sind.</li>
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
PostgreSQL realisieren. Sicherungen in diesem Format lassen sich auch mit
diesem Frontent wieder herstellen (<i>"*restore_db_internal#"</i>).

[text]
Mit der Aktivierung der Checkbox <b><i>"*backup_compress#"</b></i> ist optional
eine Kompression der Backup-Datei möglich, sofern die verwendete Installation
von PHP mit Unterstützung für <code>gzip</code> kompiliert wurde (einfach
ausprobieren - schlimmsten Falles gibt es halt eine Fehlermeldung). Nach einem
"Klick" auf den mit <i>"*button_backup#"</i> beschrifteten Button dauert es je
nach Größe der Datenbank und gewähltem Backup-Typ jetzt ein Weilchen, bis der
Browser zum Speichern der Datei auffordert.

[title]
Allgemeines zum "Restore"

[text]
Für die Wiederherstellung von Einstellungen/Daten aus einer Sicherungsdatei ist
selbige in dem in der Datei <code>inc/config.inc</code> angegebenen Verzeichnis
abzulegen. Die Dateierweiterung "<code>.pvp</code>" muss beibehalten werden.
Darüber hinaus muss sicher gestellt sein, dass der Webserver für die Datei über
die nötige Leseberechtigung verfügt. Wird nun die Backup-Seite geladen, sollte
die Datei in der Auswahlliste erscheinen. Dort ist sie nun zu selektieren, und
anschließend der Button <i>"*button_restore#"</i> zu betätigen. Nach einer von
der Größe des verwendeten Backups abhängigen Zeit sollte die Seite automatisch
neu geladen werden, und der (Miß-) Erfolg lässt sich an der Zeile direkt
unterhalb der Überschrift ablesen.

[text]
Den Typ der in der ausgewählten Sicherungsdatei enthaltenen Daten (ob also z.B.
Filmdaten oder Kategorien enthalten sind) erkennt phpVideoPro automatisch beim
Laden der Datei. Ebenso wird automatisch erkannt, ob die Datei im komprimierten
Format vorliegt; in diesem Fall werden die Daten natürlich auch automatisch
entpackt - sofern die verwendete PHP Installation dies unterstützt (siehe oben).

[title]
Filmdaten aus einem <code>*.pvp</code> Backup wieder herstellen

[text]
Hier gilt es zunächst zu entscheiden, ob die Daten aus der Sicherungsdatei den
vorhandenen Daten hinzugefügt, oder ob die vorhandenen Daten ersetzt werden
sollen.

[text]
Sollen alle Einträge in der Datenbank komplett ersetzt werden (etwa, weil gerade
jemand mit phpVideoPro "gespielt" und alles gründlich durcheinander gebracht
hat), so ist einfach die mit "<b><i>*clean_restore#</i></b>" beschriftete Box zu
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

[text]
Neue Kategorien werden automatisch erkannt - d.h., wird z.B. ein Backup von
Filmdaten aus einer anderen Datenbank importiert, in der neue Kategorien
hinzugefügt wurden, werden diese in der aktuellen Datenbank auch automatisch
angelegt. Die Entscheidung, ob es sich um eine neue Kategorie handelt, wird auf
Basis des <i>*cat_internal_name#</i> getroffen (siehe
<i><A HREF="{PHP_SELF}?topic=admin_cats">*admin_cats#</A></i>) - daher sollte
sicher gestellt werden, dass dieser für vorhandene Kategorien nicht geändert
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
Kategorien aus einem <code>*.pvp</code> Backup wieder herstellen

[text]
Dies fügt alle im Backup, aber nicht in der Datenbank enthaltenen Kategorien
der Datenbank hinzu, wobei die Einstellungen der Kategorien (z.B. ob sie
ausgeblendet werden sollen) nicht verändert werden. Außerdem werden die
Übersetzungen der Kategorienamen, sofern im Backup enthalten, für alle
installierten Sprachen ergänzt. Ist die Box "<b><i>*clean_restore#</i></b>"
aktiviert, werden auch bereits vorhandene Übersetzungen überschrieben.

[title]
Wiederherstellen eines System-Backups aus einer <code>*.pvp</code> Datei

[text]
Hierbei werden die Einstellungen in der Datenbank mit denen aus dem Backup
überschrieben. Die Checkbox "<i>*clean_restore#</b>" hat an dieser Stelle
keine Bedeutung.

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
