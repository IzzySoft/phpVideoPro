# /* $Id$ */

[title]
*intro#

[text]
Viele Filme sind in den verschiedensten Sprachen verfügbar – sowohl was die
Synchronisation der gesprochenen Sprache, als auch was die Untertitel betrifft.
Und speziell mit DVDs/BDs, kann ein Film über mehrere Spuren für beides verfügen.
phpVideoPro hält für Tonspuren und Untertitel je ein Feld bereit, um diese
Informationen zu verwalten.

[text]
Wenn es jetzt jedoch an das Bearbeiten eines Eintrages geht, stoßen wir auf ein
Problem: Wie gehen wir mit den vielen Sprachen um? Mehr als hundert davon
stehen zur Verfügung - alle aufzuführen, würde in einer langen und unhandlichen
Liste resultieren! Doch unter normalen Umständen, und selbst mit einer größeren
Filmsammlung, ist die Anzahl der tatsächlich verwendeten Sprachen wesentlich
geringer: ungefähr 10 verschiedene Sprachen für Audio und vielleicht 20 für
Untertitel finden tatsächlich Verwendung. Wir können die Liste also
einschränken, so dass sie (halbwegs) handlich bleibt.

[text]
Dennoch lässt sich die Frage, welche Sprachen denn nun verwendet werden, nicht
allgemeingültig beantworten: Die Antwort hängt nicht zuletzt vom Anwender ab,
wo er wohnt, welche Sprachen er spricht bzw. bei Kauf/Aufnahme von Filmen
bevorzugt, usw.. Also bleibt die Auswahl wieder einmal dem Anwender (bzw. in
diesem Falle besser dem Administrator) vorbehalten.

[title]
Die Liste

[text]
Einmal auf diese Seite gekommen, werden zunächst alle verfügbaren Sprachen mit
einigen Informationen dazu aufgelistet. Was heißen die Felder im einzelnen?
<ul>
 <li><b>ID</b>: der internationale Code für diese Sprache</li>
 <li><b>*name#</b>: der Name der Sprache</li>
 <li><b>*locale#</b>: Sind die Übersetzungen für phpVideoPros Dialoge, Menüs,
     usw. installiert?</li>
 <li><b>*audio_ts#</b>: Steht diese Sprache für Tonspuren zur Verfügung?</li>
 <li><b>*subtitle#</b>: Steht diese Sprache für Untertitel zur Verfügung?</li>
</ul>
Das Ikon in der letzten Spalte dient zum Editieren der ausgewählten Sprache
hinsichtlich ihrer Verfügbarkeit für Tonspuren und Untertitel. Ein "Klick"
darauf führt zum…

[title]
Bearbeitungs-Formular

[text]
Jeweils ein paar Radio-Buttons erlauben das (de)aktivieren einer Sprache für
Tonspuren bzw. Untertitel. Nach der gewünschten Anpassung der Einstellungen
dieser Buttons werden die Werte mit einem "Klick" auf den "<i>*update#</i>"
Button gespeichert, und der Anwender gelangt zurück zur o.g. Liste - und zwar
auf die gleiche Seite, die er zum Editieren des Eintrags verlassen hat.

[eof]
