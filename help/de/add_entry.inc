# /* add_entry */
# /* $Id$ */

[title]
Einleitung

[text]
Über diesen Menüpunkt läßt sich ein neuer Eintrag in die Datenbank einfügen.
Die meisten Felder dieses Formulars erklären sich selbst, und so soll an dieser
Stelle nur auf die Punkte eingegangen werden, die aus meiner Sicht einer
Erklärung bedürfen:

[title]
*mediatype#

[text]
<IMG SRC="{base_url}help/img/mtype_nr.png" ALT="Editieren eines Eintrages: Medientyp" ALIGN="LEFT" HSPACE="5" BORDER="1">
Aus der Liste "*mediatype#" (im Bild rot markiert) läßt sich der gewünschte
Medientyp auswählen. Während ich diese Box sicher nicht näher erklären muß,
möchte ich an dieser Stelle jedoch auf zwei andere Dinge hinweisen: blau
markiert sind die beiden Eingabefelder für die Medien-Nummer. Der erste
(maximal vierstellige) Teil dieser Nummer bezeichnet (in Verbindung mit dem
Medientyp) das Medium selbst (mit RVT 68 ließe sich also eindeutig die
Videokassette Nummer 68 identifizieren), während der zweite (zweistellige) Teil
einen Film auf dem jeweiligen Medium meint. RVT 68-1 wäre somit also Film Nummer
1 auf dem selbst bespielten Videoband Nummer 68, 68-2 der zweite u.s.w..
Natürlich kann theoretisch jeder hier sein eigenes Schema hinterlegen - nur
wird phpVideoPro dann nicht unbedingt so reagieren, wie man es vielleicht
erwartet :-) Wichtig ist dieses Modell z.B. bei der Ermittlung von freien
Bandstellen über den Menüpunkt "<A HREF="{PHP_SELF}?topic=taperest_absolute">*taperest_absolute#</A>"
(bzw. "*taperest_filtered#"), da dieses auf der MediaNummer aufbaut. Unnötig
daher zu erwähnen, daß diese Nummern eindeutig sein müssen - es ist nicht
möglich, die gleiche Kombination aus Medientyp und Mediennummer mehrfach zu
speichern. Wer die gleiche DVD also zweimal hat, muß ihr entweder zwei
verschiedene Nummern geben - oder den entsprechenden Vermerk im Kommentarfeld
unterbringen.
[text]
Und nun ein kleines "Gimmik": Wer erinnert sich schon daran, welches die
nächste zu vergebende *medianr# ist, wenn er gerade ein neues Band aufgenommen
oder eine neue DVD gekauft hat? Okay, bei guter Beschriftung kann man u.U. im
Regal nachschauen - aber es geht auch wesentlich bequemer: die in der Abbildung
grün markierte Box enthält eine Liste der jeweils höchsten vergebenen
Mediennummern für jeden Medientyp, so daß man sich hier schnellstens informieren
kann. Eine in dieser Auswahlbox ggf. getroffenen Auswahl hat jedoch keinerlei
Bedeutung für die sodann gespeicherten Daten - das Feld wird vom
Aktualisierungs- bzw. Speicherprozeß ignoriert.
[text]

[title]
*date_rec#

[text]
Das Datum ist in drei Felder aufgeteilt, deren Reihenfolge derzeit statisch
auf Tag-Monat-Jahr festgelegt ist. In einer der nächsten Versionen wird ggf.
auch hierfür das im Konfigurationsmenü einstellbare Datumsformat Verwendung
finden, um den verschiedenen Länderpräferenzen Rechnung zu tragen.

[title]
*counter_start_stop#

[text]
Dieser Punkt ist in erster Linie für Besitzer älterer Videorekorder interessant,
welche noch nicht über eine Indexfunktion verfügen: diese können hier die
jeweiligen Zählerstände bei Beginn bzw. Ende der Aufzeichnung eintragen. Da das
Format der Eintragungen in diesen Feldern jedoch nicht festgelegt ist (mit
Ausnahme der Einschränkung auf maximal 10 Zeichen), kann es auch anderweitig
benutzt werden (z.B. können auch die jeweiligen Zeiten von Rekordern mit
Echtzeitzählwerk eingetragen werden).

[title]
*label#

[text]
Ist dieses Kästchen markiert, erscheinen Daten zu diesem Film auf dem Etikett
für dieses Medium - andernfalls werden diese bei Erstellung des Etiketts
unterdrückt.

[title]
*commercials#

[text]
Dieses Feld ist ja eigentlich selbsterklärend: es dient der Angabe, ob die
Aufzeichnung von Werbeblöcken unterbrochen wird ("*yes#"), ob dies nicht der
Fall ist ("*no#"), oder ob sie während der Aufnahme von Hand entfernt wurden
("*cut_off#"). Für den Fall allgemeiner Unsicherheit gibt es auch noch die
Möglichkeit, "*unknown#" auszuwählen.

[title]
Kategorien

[text]
Die in der ersten Box ausgewählte Kategorie wird als Hauptkategorie gewertet
und taucht in den Listen zusammen mit den wichtigsten Eckdaten des jeweiligen
Filmes auf. Unabhängig davon werden jedoch bei Suchen bzw. bei gesetzten
<A HREF="{PHP_SELF}?topic=set_filter">Filtern</A> auch die anderen beiden
(Unter-) Kategorien berücksichtigt.

[title]
*staff#

[text]
Etwas Achtsamkeit ist bei der Eingabe dieser Daten angebracht: das erste Feld
sollte den Namen, und das zweite den Vornamen enthalten. Auch hier kann
natürlich wieder jeder seinem Gusto frönen - was aber ggf. einige Funktionen
von phpVideoPro beeinflußt. Auf der
<A HREF="http://www.qumran.org/homes/izzy/">Demo-Site</A> habe ich bereits
einige Einträge gesehen, die sowohl im Namen als auch im Vornamen vollständige
Namen (also Vor- und Nachname) enthielten. Sucht man nun aber nach einem
bestimmten Darsteller, treten entsprechende Schwierigkeiten auf, wie sich
unschwer bei der Erstellung eines <A HREF="{PHP_SELF}?topic=set_filter">Filters</A>
feststellen lassen wird.

[text]
Zusätzlich gibt es zu jedem Namen eine Checkbox "*in_list#", die wiederum mit
einem netten Feature verbunden ist: Bei der Anzeige von Personenlisten, wie
z.B. der <A HREF="{PHP_SELF}?topic=actors">Schauspielerliste</A>, werden nur
die Einträge berücksichtigt, die hier ein "Häkchen" erhalten haben. Auf diese
Weise läßt sich die Anzeige eines Schauspielers für einen bestimmten Film
unterdrücken (wenn es einem z.B. peinlich ist, daß Sascha Hehn auch in einem
70ger Jahre P*rn* der eigenen Sammlung mitgespielt hat, und nicht nur in der
Schwarzwaldklinik :)

[eof]

