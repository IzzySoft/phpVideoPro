# /* add_entry */
# /* $Id$ */

[title]
*intro#

[text]
Seit phpVideoPro v0.5.1, existiert dieser Menüpunkt für jeden konfigurierten
Medientyp separat. Dieser Schritt war nötig, um den verschiedenen Features
Rechnung zu tragen, die jeweils nur für einige der Medientypen verfügbar sind
(wie z.B. Regionalcodes für DVDs, LongPlay für Kassetten etc.), und die Felder
für Features, die vom gerade bearbeiteten Medium nicht unterstützt werden,
auch gar nicht erst einzublenden.
[text]
Über diese Menüpunkte läßt sich nun ein neuer Eintrag in die Datenbank einfügen.
Die meisten Felder dieses Formulars erklären sich selbst, und so soll an dieser
Stelle nur auf die Punkte eingegangen werden, die aus meiner Sicht einer
Erklärung bedürfen:

[title]
*medianr#

[text]
Während der Medientyp nun bereits durch die Auswahl aus dem Menü bekannt ist,
und die Nummer des physikalische Mediums durch den Prompt ermittelt wurde, ist
hier nun lediglich noch die "logische" Nummer des Films auf dem Medium zu
erfassen. Wie auch bereits bei dem erwähnten Prompt, wird auch hierfür die
höchste vergebene Nummer aus der Datenbank ermittelt und mitgeteilt (hier durch
den Button "*last_entry#"), und die Folgenummer als Vorschlag bereits
vorgegeben. In der Regel sollten diese Angaben stimmen; im Bedarfsfall können
sie freilich angepasst werden.
[text]
An dieser Stelle ein paar Worte zum Aufbau der *medianr#: Der erste
(maximal vierstellige) Teil dieser Nummer bezeichnet (in Verbindung mit dem
Medientyp) das Medium selbst (mit RVT 68 ließe sich also eindeutig die
Videokassette Nummer 68 identifizieren), während der zweite (zweistellige) Teil
einen Film auf dem jeweiligen Medium meint. RVT 68-1 wäre somit also Film Nummer
1 auf dem selbst bespielten Videoband Nummer 68, 68-2 der zweite u.s.w..
Natürlich kann theoretisch jeder hier sein eigenes Schema hinterlegen - nur
wird phpVideoPro dann nicht unbedingt so reagieren, wie man es vielleicht
erwartet :-) Wichtig ist dieses Modell z.B. bei der Ermittlung von freien
Bandstellen über den Menüpunkt <i><A HREF="{_SERVER["PHP_SELF"]}?topic=taperest_absolute">*taperest_absolute#</A></i>
(bzw. <i>*taperest_filtered#</i>), da dieses auf der MediaNummer aufbaut. Unnötig
daher zu erwähnen, daß diese Nummern eindeutig sein müssen - es ist nicht
möglich, die gleiche Kombination aus Medientyp und Mediennummer mehrfach zu
speichern. Wer die gleiche DVD also zweimal hat, muß ihr entweder zwei
verschiedene Nummern geben - oder den entsprechenden Vermerk im Kommentarfeld
unterbringen.

[title]
*disk_type# / *counter_start_stop#

[text]
Die Zähler-Einstellungen sind in erster Linie für Besitzer älterer Videorekorder
interessant, welche noch nicht über eine Indexfunktion verfügen (sie sind auch
nur für Kassetten verfügbar): diese können hier die jeweiligen Zählerstände bei
Beginn bzw. Ende der Aufzeichnung eintragen. Da das Format der Eintragungen in
diesen Feldern jedoch nicht festgelegt ist (mit Ausnahme der Einschränkung auf
maximal 10 Zeichen), kann es auch anderweitig benutzt werden (z.B. können auch
die jeweiligen Zeiten von Rekordern mit Echtzeitzählwerk eingetragen werden).
[text]
Für alle anderen Medien (DVD/VCD) kann an dieser Stelle der *disk_type#
eingetragen werden. Details dazu finden sich auf
<A HREF="{_SERVER["PHP_SELF"]}?topic=disktype_change">dieser Seite</A>.

[title]
*label#

[text]
Ist dieses Kästchen markiert, erscheinen Daten zu diesem Film auf dem Etikett
für dieses Medium - andernfalls werden diese bei Erstellung des Etiketts
unterdrückt.

[title]
*region_code#

[text]
RegionalCodes sind ein DVD-spezifisches "Feature" (auf das wir auch liebend
gern verzichten würden), daher taucht dieser Punkt auch nur für DVDs auf (es
sei denn, jemand hat dieses "Feature" auch für einen anderen Medien-Typen
freigeschaltet - siehe <i><a href="{_SERVER["PHP_SELF"]}?topic=admin_disktypes">*admin_disktypes#</a></i>).
Ist der Regionalcode der bearbeiteten DVD unbekannt, sollte hier einfach
keinerlei Auswahl getroffen werden: bei der Anzeige des Datensatzes erscheint
in diesem Fall der Hinweis "unbekannt". Für RegionCode-freie DVDs ist lediglich
die "0" auszuwählen, und für alle anderen die entsprechende(n) Checkbox(en).

[title]
*commercials#

[text]
Dieses Feld ist ja eigentlich selbsterklärend: es dient der Angabe, ob die
Aufzeichnung von Werbeblöcken unterbrochen wird ("*yes#"), ob dies nicht der
Fall ist ("*no#"), oder ob sie während der Aufnahme von Hand entfernt wurden
("*cut_off#"). Für den Fall allgemeiner Unsicherheit gibt es auch noch die
Möglichkeit, "*unknown#" auszuwählen.

[title]
*date_rec#

[text]
Das Datum ist in drei Felder aufgeteilt, deren Reihenfolge derzeit statisch auf
Tag-Monat-Jahr festgelegt ist. In einer späteren Version wird ggf. auch hierfür
das im Konfigurationsmenü einstellbare Datumsformat Verwendung finden, um den
verschiedenen Länderpräferenzen Rechnung zu tragen.

[title]
*audio_ts# / *subtitle#

[text]
Hier kann eingetragen werden, in welchen Sprachen der Film abgefasst ist. Dies
betrifft zum einen die Ton-Spuren, d.h. die gesprochene Sprache des Filmes, und
zum anderen die Untertitel. Insbesondere bei DVDs können hier in beiden Feldern
mehrere Sprachen verfügbar sein - daher lassen sich auch mehrere Sprachen
auswählen.

[text]
Da es eine doch recht große Anzahl an möglichen Sprachen gibt - auf der anderen
Seite jedoch die Übersichtlichkeit und Bedienbarkeit gewahrt bleiben soll, steht
hier jeweils nur eine Auswahl von Sprachen zur Verfügung - die jedoch
konfigurierbar ist. Das entsprechende Formular findet sich im Administrationsmenü.

[title]
*categories#

[text]
Die in der ersten Box ausgewählte Kategorie wird als Hauptkategorie gewertet
und taucht in den Listen zusammen mit den wichtigsten Eckdaten des jeweiligen
Filmes auf. Unabhängig davon werden jedoch bei Suchen bzw. bei gesetzten
<A HREF="{_SERVER["PHP_SELF"]}?topic=filter">Filtern</A> auch die anderen beiden
(Unter-) Kategorien berücksichtigt.

[title]
*staff#

[text]
Etwas Achtsamkeit ist bei der Eingabe dieser Daten angebracht: das erste Feld
sollte den Namen, und das zweite den Vornamen enthalten. Auch hier kann
natürlich wieder jeder seinem Gusto frönen - was aber ggf. einige Funktionen
von phpVideoPro beeinflußt. Auf der
<A HREF="http://www.qumran.org/homes/izzy/software/pvp/demo" TARGET="_blank">Demo-Site</A>
habe ich bereits einige Einträge gesehen, die sowohl im Namen als auch im
Vornamen vollständige Namen (also Vor- und Nachname) enthielten. Sucht man nun
aber nach einem bestimmten Darsteller, treten entsprechende Schwierigkeiten auf,
wie sich unschwer bei der Erstellung eines <A HREF="{_SERVER["PHP_SELF"]}?topic=filter">Filters</A>
feststellen lassen wird.

[text]
Zusätzlich gibt es zu jedem Namen eine Checkbox "*in_list#", die wiederum mit
einem netten Feature verbunden ist: Bei der Anzeige von Personenlisten, wie
z.B. der <A HREF="{_SERVER["PHP_SELF"]}?topic=actors">Schauspielerliste</A>, werden nur
die Einträge berücksichtigt, die hier ein "Häkchen" erhalten haben. Auf diese
Weise läßt sich die Anzeige eines Schauspielers für einen bestimmten Film
unterdrücken (wenn es einem z.B. peinlich ist, daß Sascha Hehn auch in einem
70ger Jahre P*rn* der eigenen Sammlung mitgespielt hat, und nicht nur in der
Schwarzwaldklinik :)

[title]
*comments#

[text]
Hier können beliebige Kommentare zum Film erfasst werden. Einige spezielle Tags
werden zur Unterstützung angeboten: so lassen sich [url]URLs[/url] verlinkbar
machen (sie werden dann in einem separaten Browser-Fenster geöffnet), sowie
[img]Grafiken[/img] auch [imgr]rechtsbündig[/imgr] einbinden. Um ein Bild zu
verlinken, können die Tags wie folgt verschachtelt werden:
[url][img]Bild-URL[/img][/url].
[text]
Desweiteren ist die Verwendung einiger "normaler" HTML Tags für die Formatierung
erlaubt: dies sind B,I,U,CENTER sowie BLOCK,PRE,BR,P,HR und Listen. Alle anderen
Tags werden gnadenlos entfernt - dies dient dem Schutz der Site gegen
"bösartigen" HTML Code.

[eof]

