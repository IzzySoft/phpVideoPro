# /* How to create a help file */
# /* $Id$ */

[title]
Wie erstelle ich meine eigenen Hilfe-Seiten?

[text]
Das ist die einfachste der "Wie erstelle ich..." Sachen - insbesondere, nachdem
mit v0.1.7 auch das Hilfesystem templatebasiert ist. Jetzt sind für diesen
Punkt weder PHP noch HTML Kenntnisse erforderlich - auch wenn man selbige bei
Bedarf einsetzen <b>kann</b>. Die zu bearbeitenden/erstellenden Dateien sind
reine Textdateien, die HTML/Makro Code enthalten <b>können</b>, aber nicht
müssen:
[text]
<OL>
 <LI>Im "/help" Verzeichnis findet sich die Datei "help_topics.php". Das
     Format dieser Datei ist recht einfach: "headline(thema)" steht für eine
     Überschrift mit dem Namen "thema", "li(thema)" für einen "Punkt" namens
     "thema". Der optionale Wert hinter dem Thema steht für die Anzahl der
     Einrückungen (Default: keine bei der Überschrift, eine bei einem "Punkt").
     Existiert eine Datei "help/*/thema.inc" (wobei der "*" für die verwendete
     Sprache bzw. für "en" als Default steht), wird der "Punkt" als Link
     gesetzt und mit dieser verbunden.<br>
     Unschwer zu erraten: diese Datei erstellt den Hilfe-Index.
 <LI>Ist für die gewünschte Zielsprache noch keine einzige Hilfedatei verfügbar,
     muß zunächst das Verzeichnis für diese angelegt werden: "help/??", wobei
     "??" wiederum für das Sprachkürzel steht (siehe
     "<A HREF="{PHP_SELF}?topic=howto_lang">*howto_lang#</A>").
 <LI>Jetzt kann in diesem Verzeichnis entweder eine neue Datei mit dem Namen
     thema.inc (also z.B. "lang/fi/about.inc" für den Finnischen "About" Text)
     angelegt, oder die entsprechende Datei z.B. aus dem Englischen Verzeichnis
     kopiert und bearbeitet werden. Das Format der Hilfedateien ist unten im
     Detail erklärt.
 <LI>Das war's dann auch schon - phpVideoPro findet und benutzt diese Hilfedatei
     automatisch (entsprechende Spracheinstellungen im Menü "*edit# -&gt;
     *configuration#" vorausgesetzt). Keine Panik, wenn nicht alle Hilfedateien
     für eine Sprache zur Verfügung stehen - in diesem Fall wird per Default
     auf die Englische Version zurückgegriffen.
</OL>

[title]
Dateiformat
[text]
Die wichtigsten das Format betreffenden Dinge sind sehr einfach. Es gibt vier
verschiedene Formatierungen:
[text]
<ul>
 <li><b>[Tags]</b>: dies sind die einzigen Formatierungen, die in einer
     Hilfedatei vorhanden sein müssen. Um vom Parser erkannt zu werden, muß ein
     Tag allein auf einer Zeile stehen - wobei Leerzeichen davor und dahinter
     ignoriert werden. eine Liste der Tags folgt weiter unten.
 <li><b>&#123;Variablen&#125;</b>: Optionale Platzhalter, die durch globale
     Variablen von phpVideoPro ersetzt werden. Ein Beispiel: &#123;version&#125;
     wird durch die aktuelle Version (hier: {version}) ersetzt.
 <li><b>&#042;Translators#</b>: Übersetzen einen Begriff mittels des
     Übersetzungsmoduls von phpVideoPro. Entsprechende Übersetzungen müssen
     natürlich vorhanden sein; Leerzeichen in den zu übersetzenden Begriffen
     sind nicht erlaubt.
</ul>

[title]
Tags
[text]
Hiervon gibt es nur drei:
<ul>
 <li><b>[title]</b> bezeichnet eine Überschrift.
 <li><b>[text]</b> startet einen Textblock - hier kommen alle Details zur
     vorhergehenden Überschrift hinein. Es können einer Überschrift mehrere
     Textblöcke folgen, jeder einzelne stellt sozusagen einen Absatz dar.
 <li><b>[eof]</b> heißt: hier ist die Datei zu Ende. Alles, was diesem Tag
     folgt, wird vom Parser ignoriert - ebenso wie alles, was dem ersten
     [title] Tag einer Hilfedatei voran geht.
</ul>
[text]
Sowohl in den Überschriften wie auch in den Textblöcken kann mit HTML Codes
gearbeitet werden (etwa um einen Begriff mit Fettdruck hervorzuheben, oder
eine Tabelle oder Liste einzufügen) - es muß aber nicht. Für die Darstellung
des Textes in ansprechendem Format sorgt das zugeordnete Template.

[eof]
