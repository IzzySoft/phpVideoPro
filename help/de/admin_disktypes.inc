<? /* administration of categories */ ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
Die verschiedenen Disk-Typen unterstützen unterschiedliche Features (oder auch
Limitierungen), und diese lassen sich auf dieser Seite zuordnen. Die Handhabung
dieses Formulars ist äquivalent zu dem für die
<A HREF="{_SERVER["PHP_SELF"]}?topic=admin_cats">Kategorien</A>): vorhandene Einträge
können bearbeitet, neue hinzugefügt (letzteres über den freien Eintrag am
Ende der Tabelle), nicht (mehr) benötigte gelöscht werden (indem der Inhalt
des Feldes "*name#" für den betreffenden Eintrag geleert wird).

[title]
Felder

[text]
<b>*mediatype#:</b>
[text]
Jedem Medientyp können mehrere Disk-Typen zugeordnet werden. Eine VideoCD kann
beispielsweise eine "VCD" oder auch eine "SVCD" sein, und (wieder-) beschreibbare
Medien können unterschiedliche Kapazitäten aufweisen. Mit dieser Auswahl-Box
wird der Medientyp festgelegt, dem der betreffende Disk-Typ zugeordnet ist.
[text]
<b>*name#:</b>
[text]
Namen sind Schall und Rauch - ein Disk-Typ kann also frei nach Gusto benannt
werden. Eine Eingabe in diesem Feld ist allerdings notwendig, um den Eintrag
speichern zu können.
[text]
<b>*disk_size#:</b>
[text]
Der hiermit definierte Wert ist optional; gedacht ist, wie anhand der bereits
definierten Disk-Typen ersichtlich, an eine Größe in MB oder GB.
[text]
<b>*longplay# / *region_code#:</b>
[text]
Mithilfe dieser Check-Boxen wird angegeben, ob das betreffende "Feature" für
diesen Disk-Typ verfügbar ist.

[title]
Löschen eines Disk-Typs

[text]
Einen Disk-Typ zu löschen ist einfach - jedoch läßt sich diese Löschung nur
schwer rückgängig machen. Daher sei hier kurz erwähnt, was beim Löschen passiert:
[text]
Wird ein Disk-Typ gelöscht, der noch für das eine oder andere Medium gesetzt
ist, wird bei den betreffenden Medien diese Zuordnung aufgehoben (es steht dann
also anschließend dort nur noch "unbekannt"), anschließend wird die Definition
des betreffenden Disk-Typs gelöscht. Dies alles geschieht ohne eine Warnung.
Wie üblich ist es also auch diesbezüglich zu empfehlen, immer ein möglichst
aktuelles Backup bereit zu haben :-)

[title]
Updates

[text]
Wie auch bei den Kategorien bereits erwähnt, wenn auch an dieser Stelle etwas
unwahrscheinlicher, können veränderte/hinzugefügte Disk-Typ Definitionen beim
Update auf eine neuere Version von phpVideoPro überschrieben werden. Um dies
zu vermeiden (und überhaupt), sollten die Disk-Typen, an die ich nicht gedacht,
die aber benötigt werden, mir zur Sicherheit mitgeteilt werden - damit ich sie
für folgende Versionen berücksichtigen kann.

[eof]
