<? /* medialist */
 ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
Auch wenn dieser Punkt im Menü "*print#" zu finden ist, werden hier lediglich
Daten für den Druck vorbereitet. Ich hatte zunächst verschiedene Varianten von
Ausgabeformaten in Erwägung gezogen. An erster Stelle stand PostScript: damit
wären zwar alle Unix/Linux Benutzer wunderbar klar gekommen (verwendet doch
hier nahezu jeder "Druckertreiber" PostScript als Eingabeformat) - jedoch unsere
armen M$-Abhängigen (Windoze Benutzer) wären darüber sicher nicht besonders
glücklich gewesen (auch wenn sie zur Verarbeitung GhostScript installieren
könnten). Als Alternative bot sich an, die Listen als riesige, mehrseitige
Etiketten zu betrachten - da dies jedoch ebenso riesige Grafikdateien zum
Ergebnis hätte, kämen zum einen die Drucker anständig in's Schwitzen, und zum
anderen würde der Druck damit auch recht lange dauern...

[title]
Wie funktioniert es nun?

[text]
Also entschloss ich mich, die Listenaufbereitung auf unterschiedliche Weise
vonstatten gehen zu lassen: Die Listen entweder als reiner (ASCII) Text
erstellt, der sich sodann direkt (nach dem Speichern im Dateisystem und/oder
Öffnen mit einem beliebigen Texteditor wie [k]write) drucken läßt.<br>Zur
Alternative steht ein Export im CSV Format (die einzelnen Spalten sind mittels
Tabulatoren (Tab-Stops) getrennt, die erste Zeile enthält die Tabellenüberschriften),
bzw. eine HTML Tabelle, wobei sich das Resultat dann in eine beliebige
Textverarbeitung (Word, OpenOffice/StarOffice etc.), Tabellenkalkulation (Excel,
OpenOffice/StarOffice) bzw. einen HTML Editor (Netscape Composer, DreamWeaver,
Quanta) importieren und mittels dieser nachbereiten läßt.<br>
Ich empfehle für letzteres die Erstellung einer Dokumentvorlage, in der alle
gewünschten Tabellen- und Textformatierungen (Schriftart und -größe,
Hintergrundfarben z.B. für den Tabellenkopf, Kopfzeilen der Seiten mit Überschrift
und Seitenzahlen etc.) bereits festgelegt sind. Besonders, wenn häufiger Listen
gedruckt werden sollen, hilft dies, den Zeitaufwand ein wenig zu begrenzen.

[title]
Formularfelder

[text]
<b>*list#:</b> Welche Liste erstellt werden soll (erklärt sich selbst)
<b>*format#:</b> <b><i>ASCII</i></b> bezeichnet eine formatierte Liste (etwas
spartanisch, eher für "Faule" gedacht, die sich nicht den Aufwand der
Nachbearbeitung machen wollen), die zum direkten Ausdruck gedacht ist (siehe
oben). <b><i>HTML</i></b> auch im ASCII Format *grins*, erzeugt eine einfache
HTML Tabelle ohne speziellere Formatierung. Eignet sich besonders zur schnellen
Nachbearbeitung z.B. mit OpenOffice, da sich hier die nötigen Format-Korrekturen,
zumal bei Verwendung einer geeigneten Dokumentvorlage, doch stark in Grenzen
halten. <b><i>CSV</i></b> ebenfalls im ASCII Format, jedoch sind hier alle Felder
lediglich mit Tabulatoren getrennt, um anschließend in eine Tabelle umgewandelt
und dort weiter bearbeitet werden zu können (abermals siehe oben).<br>
<b>*line_count#</b>: Wie viele Zeilen reinen (ASCII) Textes auf eine Seite
Papier passen (dies kann je nach Drucker unterschiedlich sein). Der Vorgabewert
wird aus den Voreinstellungen (siehe
"<A HREF="{PHP_SELF}?topic=configuration">*configuration#</A>") übernommen, kann
jedoch hier überschrieben werden. Für CSV und HTML Listen wird der Inhalt dieses
Feldes freilich ignoriert.

[eof]

