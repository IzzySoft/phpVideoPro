# /* configure */
# /* $Id$ */

[title]
Einleitung

[text]
In diesem Formular lassen sich generelle Einstellungen für phpVideoPro
vornehmen, wie z.B. Sprach- und Farbeinstellungen.

[title]
*language_settings#

[text]
<b>*scan_new_lang_files#:</b> Zur Speicherung der für das Übersetzungsmodul
benötigten Daten verwendet phpVideoPro seine Datenbank. Will man also eine
neue Sprache hinzufügen, muß diese aktualisiert werden. Dies geschieht über
SQL Dateien, die ich im Folgenden der Einfachheit halber "Sprachdateien"
nennen möchte. Eine neue Sprachdatei muß dem System zunächst bekannt gemacht
werden - dies geschieht durch das Aktivieren dieser Box (und natürlich
anschließendes Versenden des Formulars). Die weiteren Schritte folgen unten.
Wie eine neue Sprachdatei erstellt werden kann, findet sich in der Hilfe zum
Punkt "<A HREF="{PHP_SELF}?topic=howto_lang">*howto_lang#</A>".

[text]
<b>*select_add_lang#:</b> Natürlich können hier nur verfügbare Sprachen
ausgewählt werden (das sind jene, zu denen bereits eine Sprachdatei existiert) -
phpVideoPro gehört nicht in die Kategorie "KI" und kann daher nicht mal eben
eine neue Sprache selbst erfinden :) Um die Übersetzungen für eine bereits
installierte Sprache zu aktualisieren, gibt es den nächsten Punkt.

[text]
<b>*refresh_lang#:</b> Steht eine neuere Version einer bereits installierten
Sprachdatei zur Verfügung (oder hat man selbst eine vorhandene Sprachdatei
angepaßt), können hiermit die entsprechenden Einträge in der Datenbank
aktualisiert werden. Dabei werden alle bestehenden Einträge für die ausgewählte
Sprache zunächst aus der Datenbank gelöscht, und sodann die Einträge aus der
Sprachdatei importiert. Die Möglichkeit, bestehende Einträge beizubehalten, und
nur neue zu importieren, gibt es derzeit noch nicht.

[text]
<b>*select_primary_lang#:</b> Aus den vorhandenen Sprachen kann eine als
"Primärsprache" ausgewählt werden. Das heißt, phpVideoPro versucht alle
Bildschirmausgaben in dieser Sprache durchzuführen. Ist die Übersetzung für
eine Phrase nicht in der "Primärsprache" vorhanden, wird in den Englischen
Übersetzungen gesucht. Schlägt auch dies fehl, taucht ein "Sprachcode" des
Programmierers auf - sollte dies nicht auf einen Benutzerfehler (wie etwa eine
gelöschte Englische Sprache) zurückzuführen sein, erbitte ich eine
<A HREF="mailto:izzysoft@qumran.org">Nachricht</A> an mich, damit ich den
Fehler beheben kann!

[text]
<b>*use_charset#</b>: dies Beeinflußt die Darstellung insbesondere von
Sonderzeichen (wie etwa den deutschen Umlauten) und sollte daher nur geändert
werden, wenn man wirklich weiß, was man tut :) Nötig kann dies z.B. werden,
wenn man als "Primärsprache" Französisch wählt und eine Sprachdatei erstellt,
die wiederum über andere Sonderzeichen verfügt (in diesem Fall wäre ich
natürlich an dieser Datei ebenfalls interessiert, um sie ggf. der nächsten
Release mit bei zu fügen!). Eine falsche Einstellung kann zu einer etwas
verwirrenden Anzeige führen (und bei der Datenerfassung auch Langzeit-Wirkung
haben), ist aber ansonsten nicht tragisch.

[title]
*colors#

[text]
<b>*page_bg# / *table_bg# / *th_bg#:</b> Diese Einstellungen werden in das
StyleSheet mit eingepflegt - die Namen sprechen ja für sich.

[text]
<b>*feedback_ok# / *feedback_err#:</b> Im Unterschied zum vorigen Punkt werden
diese Einstellungen in kein StyleSheet eingepaßt. Sie dienen Rückmeldungen vom
System, z.B. bei Aktualisierungen der Datenbank, um den jeweiligen Status
sofort erfaßbar zu machen. "*feedback_ok#" meint hier also die Textfarbe für
eine positive Rückmeldung, während "*feedback_err#" die Textfarbe für eine
Fehlermeldung darstellt.

[text]
<b>*template_set#:</b> Seit Version 0.1.5 basiert phpVideoPro auf Templates
(das Design betreffend). Als Autor habe ich lediglich ein einziges Set solcher
Templates der Distribution beigefügt; sobald jedoch weitere Templatesets
verfügbar sind (d.h., sobald jemand ein solches erstellt und mir zugeschickt
hat - ich selber werde wahrscheinlich zumindest in absehbarer Zeit kein
weiteres erstellen :), lassen diese sich hier auswählen, und phpVideoPro erhält
auf diese Weise eine "neue Haut" ("Skins", wie sie auch von Programmen wie
XMMS bzw. WinAmp bekannt sein dürften).

[eof]

