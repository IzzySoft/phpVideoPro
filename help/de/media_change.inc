<? /* change media nr or copy entry */ ?>
<? /* $Id$ */ ?>

[title]
Gibt es einen guten Grund, die MediaNr zu ändern?

[text]
Auf dieser Seite kann die MediaNr oder auch der MediaType für einen Film
geändert werden - oder auch ein Film auf ein anderes Medium (oder einfach
an eine Stelle auf dem gleichen) "kopiert" werden. Es gibt einige gute Gründe,
die diese Funktion sinnvoll erscheinen lassen:
<UL>
 <LI>Es sollen Daten für mehrere DVDs oder Kassetten einer Serie (z.B.
     "Babylon 5", "Star Trek" oder "Friends") erfasst werden, da diese gerade
     als "Set" erworben wurden. Die gleichen Daten wieder und wieder
     einzutippen, macht allenfalls auf einer Schreibmaschine Sinn. Also
     geben wir die Daten einmalig ein, und kopieren sodann den kompletten
     Datensatz. In der Kopie brauchen dann nur noch die wenigen Daten
     angepasst werden, die sich von Teil zu Teil ändern (z.B. der Titel der
     Folge).
 <LI>Der Lieblingsfilm ist jetzt endlich auf DVD verfügbar. Vor lauter
     Freude über dieses unverhoffte Glück erwerben wir also diese DVD, und
     verschenken die Original-Kassette an unseren besten Freund. Ärgerlich nur,
     dass unsere Datenbank noch immer meint, wir hätten eine Kassette.
     Anstatt jetzt aber alle Daten neu einzutippen, ändern wir einfach
     die MediaNr und den MediaType, und passen den Datensatz bzgl. der
     Tonspur (Ah! Endlich in Dolby 5.1 :) an.
 <LI>Die ganze Sammlung soll reorganisiert werden, weil alle Bruce Willis
     DVDs in die Tonne gewandert sind. Ja, seid Ihr denn wahnsinnig? Hätte
     mir das jemand rechtzeitig mitgeteilt, hätte ich sofort meine Postadresse
     mitgeteilt, damit die Sammlung bei mir landet! Dass mir also niemand so
     etwas erzählt...
</UL>

[title]
Erklärung der Felder

[text]
<B>*highest_db_entries#</B>: Nur eine Hilfestellung, die keinerlei Einfluss
auf die Verarbeitung der Daten hat. Wir kennen sie ja bereits vom Formular
"*add_entry#". Es teilt uns lediglich die höchste vergebene Nummer für jeden
MediaType mit, um uns die Orientierung zu erleichtern.

[text]
<B>*orig_medianr#</B>: Nur, um nochmal sicher zu gehen. Wurde diese Seite durch
den Klick auf einen der Buttons "*mediatype#" oder "*medianr#" von der Seite
"*view_entry#" aufgerufen, ist es mit den Werten dieses Films vorbelegt. Eine
Änderung dieser Daten ist also nur angebracht, wenn ein ganz anderer Film
angepasst werden soll. Dies ist normalerweise nicht der Fall.

[text]
<B>*new_medianr#</B>: Dies ist die neue Nummer, die der Film erhalten soll.
Voreingestellt ist hier der gleiche Wert wie für "*orig_medianr#" - hier ist
also auf jeden Fall eine Anpassung nötig. Auch wenn darauf geachtet werden
sollte, hier die richtigen Werte einzugeben: phpVideoPro würde es nicht
zulassen, bestehende Daten zu überschreiben. Die Eingabe einer bereits
vergebenen Nummer sollte also lediglich zu einer Warnung führen, und nicht
zu einem Datenverlust.

[eof]
