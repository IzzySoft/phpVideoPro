# /* How to create a new language file */
# /* $Id$ */

[title]
Wie erstelle ich eine Sprachdatei für meine Muttersprache?

[text]
Dies ist leichter, als mancher denken mag - es sind nur wenige Schritte nötig:
[text]
<OL>
 <LI>Am Ende der Datei "setup/tech_data.sql" findet sich eine Liste der Sprachen
     und ihrer Kürzel. Hier ist das Kürzel für die Zielsprache zu ermitteln. An
     einem Beispiel veranschaulicht: möchte jemand eine Finnische Sprachdatei
     erstellen, so erkennt er an der Zeile
     <code>INSERT INTO languages VALUES ('fi','Finnish','No');</code>, daß
     das gesuchte Kürzel "fi" heißt.
 <LI>Nun nimmt man sich am besten eine bereits existierende Sprachdatei einer
     Sprache, deren man mächtig ist - als Beispiel möchte ich an dieser Stelle
     Deutsch wählen (schließlich ist dieser Text ja auf Deutsch. Allgemein
     empfehle ich hierfür entweder die Deutsche oder die Englische Sprachdatei,
     da diese meist die aktuellsten sind). Sprachdateien haben das Namensformat
     "lang_??.sql", wobei die beiden Fragezeichen für das jeweilige Sprachkürzel
     stehen. Die Deutsche Sprachdatei heißt also "lang_de.sql". Diese kopieren
     wir nun in die Finnische Sprachdatei, die folgerichtig "lang_fi.sql" heißt.
 <LI>Jetzt öffnen wir unsere neue Sprachdatei ("lang_fi.sql") mit unserem
     Lieblingseditor (es handelt sich um eine reine Textdatei - als solche
     sollte sie auch wieder gespeichert werden) und passen die Übersetzungen
     an: Nur der dritte in der Klammer stehende Wert sollte hierzu verändert
     werden. Wieder am Beispiel:
     <code>INSERT INTO lang VALUES('year','de','Jahr');</code> - hier ist es
     der Begriff "Jahr", der in's Finnische übersetzt werden muß - alles
     andere in dieser Zeile sollte unberührt bleiben (abgesehen natürlich
     vom Sprachcode: 'en' sollte in unserem Beispiel durch 'fi' ersetzt werden).
 <LI>Sobald der vorige Schritt für alle Werte abgeschlossen ist, sollte
     die Sprachdatei phpVideoPro bekannt gemacht werden. Dies geschieht
     wiederum im Menü "*edit# -&gt; *configuration#": hier ist die CheckBox
     "*scan_new_lang_files#" zu aktivieren und der Button "*update#" zu
     betätigen. Wenige Sekunden später steht die Finnische Sprache zur Auswahl
     bereit, und kann mit "*select_add_lang#" in die Datenbank importiert
     werden. Anschließend können wir sie über "*select_primary_lang#" zu unserer
     "Primärsprache" erklären - und phpVideoPro sollte nun Finnisch "sprechen"
     (vorausgesetzt, die in Schritt 3 gemachten Übersetzungen waren korrekt).
</OL>

[title]
Die vorhandenen Übersetzungen für meine Sprache gefallen mir nicht...

[text]
Kein Problem. Entweder wir wählen einfach eine andere Sprache - oder aber
passen einfach die Sprachdatei an (siehe oben, Schritt 3). Anschließend wird
im Menü "*edit# -&gt; *configuration#" die Sprache im Punkt "*refresh_lang#"
ausgewählt, und der Button "*update#" betätigt - und schon ist das Problem
behoben.

[eof]
