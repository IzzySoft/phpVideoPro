# /* How to create a new language file */
# /* $Id$ */

[title]
Wie erstelle ich eine Sprachdatei für meine Muttersprache?

[text]
Dies ist leichter, als mancher denken mag (seit v0.4.6 sogar sehr einfach, dank
des neuen Editors für Übersetzungen) - es sind nur wenige Schritte nötig:
[text]
<OL>
 <LI>Zunächst ist ein LogIn als Administrator erforderlich.</LI>
 <LI>Nun ist im Menü der Punkt "*admin# -&gt; *admin_translations#"
     auszuwählen...</LI>
 <LI>...und hier die gewünschte Zielsprache. Ein "Klick" auf "*submit#" führt
     dann direkt zur Bearbeitung der Übersetzungen.</LI>
 <LI>Sofern auf einer Seite Änderungen erfolgt sind, müssen diese (pro Seite)
     mittels des "*update#" Buttons gespeichert werden.</LI>
 <LI>Alles fertig? Dann gilt es, die Übersetzungen in eine Datei zu sichern.
     In dieser ist nochmals zu prüfen, ob der eingetragene Zeichensatz mit dem
     verwendeten übereinstimmt. Dies läßt sich anhand des ersten SQL Kommandos
     ("UPDATE...") ermitteln. Sollte dies nicht der Fall sein, muss es noch
     in der Datei angepasst und diese sodann über die "*admin# -&gt; *configuration#"
     Seite neu eingeladen werden, um die Datenbank entsprechend zu synchronisieren.</LI>
</OL>

[text]
So, und jetzt würde ich mich freuen, eine Kopie dieser Datei zu erhalten, um sie
in zukünftigen Versionen von phpVideoPro verwenden zu können!

[title]
Die vorhandenen Übersetzungen für meine Sprache gefallen mir nicht...

[text]
Kein Problem. Siehe oben - gleiche Prozedur :-)

[eof]
