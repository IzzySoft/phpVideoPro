# /* How to create a new template set */
# /* $Id$ */

[title]
Wie kann ich mein eigenes TemplateSet erstellen?

[text]
Wie auch bei den Hilfe- und Sprachdateien geschieht auch dies einfach durch
das Erstellen eines Verzeichnisses und das Kopieren/Anlegen/Editieren einiger
Dateien. Im Gegensatz zu den Hilfe- und Sprachdateien muß hier jedoch darauf
geachtet werden, daß <b>alle</b> Dateien vollzählig sind - fehlende Templates
werden hier nicht durch ein Default-Template ersetzt!

[title]
Vorgehensweise:
[text]
<OL>
 <LI>Zuerst wird ein möglichst aussagekräftiger Name für das TemplateSet
     benötigt. Um ein Beispiel zu haben, nenne ich es hier einmal "babylon5".
 <LI>Im Template-Verzeichnis ("templates/") ist nun ein Verzeichnis mit diesem
     Namen anzulegen ("templates/babylon5").
 <LI>Jetzt können entweder die Templates aus "templates/default" als Vorlage
     in das neue Template-Verzeichnis kopiert und sodann angepaßt werden (auf
     diese Weise hat man zumindest sogleich eine vollständige Liste der im
     jeweiligen Template verwendeten &#123;Platzhalter&#125; zur Hand - diese
     sollten auf jedem Fall wieder im neuen template auftauchen, da sie vom
     Parser durch die eigentlichen Daten ersetzt werden), oder man erstellt
     "einfach" neue Dateien mit dem entsprechenden Namen.
 <LI>Ist der vorige Schritt für alle Dateien abgeschlossen, bietet sich die
     Aktivierung des neuen TemplateSets an - dies geschieht im Menü
     "*edit# -&gt; *configuration#". Das neu verfügbare TemplateSet wird,
     wenn alle obigen Schritte beachtet wurden, von phpVideoPro automatisch
     erkannt und zur Auswahl angeboten.
</OL>

[text]
Wird JavaScript Code auf allen Seiten benötigt, so kann dieser in zwei speziellen
Dateien untergebracht werden. Eine Datei namens <I>top.js</I> wird, sofern sie
im Verzeichnis des Template-Sets vorhanden ist, in den HTML Header jeder Seite
eingebunden. Gleiches gilt für eine <I>foot.js</I>, die entsprechend am Ende
der Seiten verankert wird.

[eof]
