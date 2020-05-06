# /* How to create a new label (set) */
# /* $Id$ */

[title]
*intro#

[text]
Das Folgende bezieht sich auf das <b>ALTE</b> Label-System, nicht auf die
PSLabels! Für letztere, <a
href='https://github.com/IzzySoft/phpVideoPro/wiki/CustomizingManual#ps-labels'
target='_new'>siehe hier</a>.
[text]
Etiketten werden im Verzeichnis "<code>labels/</code>" erstellt bzw.
konfiguriert. Hierbei gilt es zumindest zwei Dateien zu berücksichtigen: die
Konfigurationsdatei (<code>*.config</code>) und das optionale "leere Etikett"
als Grafik-Datei (<code>*.png</code>). Beide müssen den gleichen "Vornamen"
haben: heißt also die Konfigurationsdatei "<code>Favorit.config</code>", muss
die zugehörige Grafikdatei "<code>Favorit.png</code>" heißen. Ist keine
gleichnamige Grafikdatei vorhanden, wird einfach ein leeres Etikett (nur die
Rahmen auf weißem Grund) erzeugt und verwendet.
[text]
In der Konfigurationsdatei wird, wie der Name bereits vermuten läßt, das
Etikett konfiguriert. Es gilt sicherzustellen, dass die hier angegebenen
Maße mit der zu verwendenden Grafikdatei abgestimmt sind, sofern eine solche
beabsichtigt ist.
[text]
Da die Konfigurationsdatei einfach als PHP Datei in das Programm eingebunden
wird, ist hier auch die PHP Syntax zu berücksichtigen. Das heißt auf der
anderen Seite jedoch auch, dass z.B. die "include()" Direktive verwendet
werden kann – auf diese Weise lassen sich relativ einfach Sets von Etiketten
erstellen, welche den gleichen Aufbau verwenden und sich lediglich in den
Motiven unterscheiden.

[title]
Die Konfigurationsdatei

[text]
Hier also eine kurze Erklärung der zu verwendenden Variablen:
[text]
<b>width, height:</b> die Größe des Etiketts
[text]
<b>maxlines:</b> wie viele Textzeilen maximal auf dem Etikett Platz finden
(überzählige Zeilen werden dann einfach "abgeschnitten"). Eine sehr nützliche
Sache, wenn man (wie ich) hin und wieder den auf dem Videoband verbleibenden
kurzen Rest mit vielen VideoClips von MTV &amp; Co. auffüllt ;)
[text]
<b>nr_coord, main_coord, symb_coord:</b> Die Koordinaten der einzelnen Felder
im Format "x1,y1,x2,y2", wobei "x1,y1" die obere linke und "x2,y2" die untere
rechte Ecke des jeweiligen Feldes bezeichnen. Die zugehörigen Felder werden
dann gefüllt mit der *medianr# (ohne den MedienTyp), den Filmdaten und einem
Symbol – naja, letzteres wird nicht von phpVideoPro erstellt.
[text]
<b>entry</b>: Dies ist entweder ein String (wenn pro Film nur eine Zeile Text
gewünscht wird) oder ein Array von Strings. Die Strings können aus einfachem
Text bestehen, aber auch (durch geschweifte Klammern begrenzte) Variablen
enthalten, die sodann durch die Filmdaten ersetzt werden. Eine Liste hierfür
verfügbarer Variablen findet sich im nächsten Block.
[text]
Um eine Zeile des Datensatzes als "Überschrift" zu markieren, ist als erstes
Zeichen der Zeile ein "*" zu verwenden. Diese Zeile verwendet dann einen anderen
(größeren) Font.

[title]
Variablen für den Eintrag des Etiketts (entry)

[text]
<ul>
 <li>title: Der Filmtitel</li>
 <li>lenght: Filmlänge im Format hh:mm</li>
 <li>country, year: *country# und *year#</li>
 <li>counter1,counter2: *counter_start_stop#</li>
 <li>aq_date: *date_rec#</li>
 <li>source: *source#</li>
 <li>actor1,..,actor5: Schauspieler 1..5 (im Format "Vorname Nachname")</li>
 <li>actors12: Schauspieler 1+2 als Aufzählung ("Schauspieler 1, Schauspieler 2").
     Berücksichtigt auch nicht angegebene Schauspieler: falls also z.B.
     Schauspieler 2 gar nicht angegeben ist, ist actors12 das gleiche wie actor1.</li>
 <li>actors35: das gleiche wie actors12, nur für Schauspieler 3-5</li>
 <li>actors: das gleiche wie actors12, nur für alle Schauspieler (1-5)</li>
 <li>director: *director#</li>
 <li>music: Komponist des Soundtracks</li>
 <li>fsk: *fsk#</li>
 <li>cat1,cat2,cat3: die Kategorien</li>
 <li>comment: Inhalt des Kommentarfeldes</li>
 <li>mtype,mtype_short,cass_id,part: Medientyp/Abkürzung desselben/*medianr#
     sowie die relative Nummer des Films auf dem Medium</li>
 <li>color: s/w, Farbe oder 3D</li>
 <li>pict: 4:3 oder Widescreen?</li>
 <li>tone: Mono, Stereo, Dolby Digital 5.1, etc.</li>
 <li>tone_short: selbiges im Format "1.0", "2.0" .. "9.1"</li>
 <li>lp: *longplay# (*yes# / *no#)?</li>
 <li>commercials: Wird der Film durch Werbefetzen unterbrochen?</li>
</ul>

[eof]
