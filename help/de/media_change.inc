<? /* change media nr or copy entry */
 ?>
<? /* $Id$ */ ?>

[title]
Gibt es einen guten Grund, die MediaNr zu �ndern?

[text]
Auf dieser Seite kann die MediaNr oder auch der MediaType f�r einen Film
ge�ndert werden - oder auch ein Film auf ein anderes Medium (oder einfach
an eine Stelle auf dem gleichen) "kopiert" werden. Es gibt einige gute Gr�nde,
die diese Funktion sinnvoll erscheinen lassen:
<UL>
 <LI>Es sollen Daten f�r mehrere DVDs oder Kassetten einer Serie (z.B.
     "Babylon 5", "Star Trek" oder "Friends") erfasst werden, da diese gerade
     als "Set" erworben wurden. Die gleichen Daten wieder und wieder
     einzutippen, macht allenfalls auf einer Schreibmaschine Sinn. Also
     geben wir die Daten einmalig ein, und kopieren sodann den kompletten
     Datensatz. In der Kopie brauchen dann nur noch die wenigen Daten
     angepasst werden, die sich von Teil zu Teil �ndern (z.B. der Titel der
     Folge).
 <LI>Der Lieblingsfilm ist jetzt endlich auf DVD verf�gbar. Vor lauter
     Freude �ber dieses unverhoffte Gl�ck erwerben wir also diese DVD, und
     verschenken die Original-Kassette an unseren besten Freund. �rgerlich nur,
     dass unsere Datenbank noch immer meint, wir h�tten eine Kassette.
     Anstatt jetzt aber alle Daten neu einzutippen, �ndern wir einfach
     die MediaNr und den MediaType, und passen den Datensatz bzgl. der
     Tonspur (Ah! Endlich in Dolby 5.1 :) an.
 <LI>Die ganze Sammlung soll reorganisiert werden, weil alle Bruce Willis
     DVDs in die Tonne gewandert sind. Ja, seid Ihr denn wahnsinnig? H�tte
     mir das jemand rechtzeitig mitgeteilt, h�tte ich sofort meine Postadresse
     mitgeteilt, damit die Sammlung bei mir landet! Dass mir also niemand so
     etwas erz�hlt...
</UL>

[title]
Erkl�rung der Felder

[text]
<B>*highest_db_entries#</B>: Nur eine Hilfestellung, die keinerlei Einfluss
auf die Verarbeitung der Daten hat. Wir kennen sie ja bereits vom Formular
"*add_entry#". Es teilt uns lediglich die h�chste vergebene Nummer f�r jeden
MediaType mit, um uns die Orientierung zu erleichtern.

[text]
<B>*orig_medianr#</B>: Nur, um nochmal sicher zu gehen. Wurde diese Seite durch
den Klick auf einen der Buttons "*mediatype#" oder "*medianr#" von der Seite
"*view_entry#" aufgerufen, ist es mit den Werten dieses Films vorbelegt. Eine
�nderung dieser Daten ist also nur angebracht, wenn ein ganz anderer Film
angepasst werden soll. Dies ist normalerweise nicht der Fall.

[text]
<B>*new_medianr#</B>: Dies ist die neue Nummer, die der Film erhalten soll.
Voreingestellt ist hier der gleiche Wert wie f�r "*orig_medianr#" - hier ist
also auf jeden Fall eine Anpassung n�tig. Auch wenn darauf geachtet werden
sollte, hier die richtigen Werte einzugeben: phpVideoPro w�rde es nicht
zulassen, bestehende Daten zu �berschreiben. Die Eingabe einer bereits
vergebenen Nummer sollte also lediglich zu einer Warnung f�hren, und nicht
zu einem Datenverlust.

[eof]
