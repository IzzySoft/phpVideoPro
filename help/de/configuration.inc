# /* configure */
# /* $Id$ */

[title]
Einleitung

[text]
In diesem Formular lassen sich generelle Einstellungen für phpVideoPro
vornehmen, wie z.B. Sprach- und Farbeinstellungen. Einige der hier beschriebenen
Optionen sind nur über den Aufruf des Konfigurations-Formulars über das "Admin"
Menü verfügbar, da es sich um Eigenschaften handelt, die nur der Administrator
bearbeiten sollte. Andere hingegen sind eher als benutzerabhängige Präferenzen
zu betrachten und daher auch über das Standard-Menü zu erreichen.

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

[title]
*colors#

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

[title]
*general#

[text]
<b>*rw_media#:</b> Für Medien wie z.B. Original-Videokassetten oder DVDs macht
es wenig Sinn, "Bandreste" zu verwalten - weil es einfach keine gibt. Bei
anderen Medien wiederum, wie z.B. selbst bespielten Videokassetten, gehört die
Verwaltung verbleibender freier Zeit zu den elementaren Funktionen, die von
einer Software wie phpVideoPro (mit Recht) erwartet werden. Manch einer erstellt
sich seine VideoCDs selbst, ein anderer kauft sie ausschließlich. In einigen
seltenen Fällen erstellen Anwender mittlerweile gar ihre DVDs selbst, und
benötigen daher auch für diese die Restzeit-Verwaltung. Um jedem gerecht zu
werden, ist daher seit v0.3.4 dieser Punkt konfigurierbar geworden. Es sind
hier also die Medien zu markieren, für die Restzeiten verwaltet (und angezeigt)
werden sollen.

[text]
<b>*remove_empty_media#:</b> Auch hier soll unterschiedlichen Vorgehensweisen
Rechnung getragen werden: Manch einer löscht keine Aufnahmen, sondern überspielt
sie allenfalls gelegentlich. Wenn dieser Mensch also Einträge aus der Datenbank
löscht, heißt das für ihn: das Medium existiert nicht mehr (verschenkt oder
weggeworfen). Ein anderer löscht hingegen die Einträge aus der Datenbank, damit
er bei nächster Gelegenheit die ungewünschte Aufnahme überspielen kann (weil
ihm die Restzeit-Anzeige sodann dieses Medium vorschlagen wird). Je nach
gewünschter Vorgehensweise kann hier also angegeben werden, was passieren soll,
wenn der letzte Eintrag für ein Medium entfernt wird: ist die Box markiert,
wird sodann auch das Medium aus der Restzeit-Tabelle entfernt (steht also für
die Restzeit-Suche nicht mehr zur Verfügung) - andernfalls wird für die
Restzeit-Suche die gesamte Kapazität des Mediums berücksichtigt.

[text]
<b>*movie_color_default#:</b> Heutzutage werden die meisten Filme in Farbe
ausgestrahlt - daher ist es natürlich auch sinnvoll, wenn dies die
Voreinstellung für neue Einträge ist. Andernfalls mag es unter den Anwendern
auch solche geben, die überwiegend Filme aus den Zwanziger Jahren sammeln,
welche freilich in schwarz/weiß sind. In diesem Fall wäre es natürlich
wünschenswert, die Voreinstellung entsprechend anzupassen. Dies kann hier
geschehen.

[text]
<b>*display_limit#:</b> Ältere Versionen von phpVideoPro zeigten Listen, wie
z.B. unter dem Menüpunkt *medialist# zu finden, stets in voller Länge, d.h.
mit allen Datensätzen an. Bei umfangreichen Datensammlungen führte dies nicht
nur zu langen Ladezeiten, sondern konnte durchaus auch recht unübersichtlich
werden. Mit Version 0.2.3 wurde daher eingeführt, diese Liste in mehrere
"Häppchen" unterteilen zu können. Die Größe dieser "Häppchen" läßt sich mit
diesem Punkt einstellen: er gibt an, wie viele Zeilen die jeweilige Tabelle
haben soll. Innerhalb der Listen läßt sich mit vier Buttons navigieren: diese
führen jeweils zur ersten/letzten bzw. vorigen/nächsten Seite.

[text]
Zugegebenermaßen scheint es bei den Besetzungslisten (Darsteller, Regisseure
etc.) zu kleinen Ungereimtheiten zu kommen, und die Anzahl der Zeilen kann
nicht nur vom eingestellten "*display_limit#" abweichen, sondern außerdem auch
von Seite zu Seite differieren. Dies liegt daran, dass hier die "Häppchen-Größe"
auf die Anzahl der Personen angewendet wird. Diese können aber durchaus auch als
"nicht anzuzeigen" erfaßt sein (Option "*in_list#" im "*edit#" Formular).

[text]
<b>*lines_per_page#:</b> Diese Angabe dient den Vorbereitungen für den
Listendruck und gibt an, wie viele Zeilen (reinen ASCII) Textes auf ein Blatt
Papier passen. Einmal an dieser Stelle festgelegt, wird dieser Wert bei jedem
Aufruf des Menüpunktes "*listgen#" (siehe <A HREF="{PHP_SELF}?topic=listgen">dort</A>)
als Standard vorgegeben, kann dort jedoch auch jedesmal angepasst werden.

[text]
<b>*date_format#:</b> In welchem Format sollen Datumsangaben präsentiert werden.
Dies ist erst seit phpVideoPro v0.2.6 konfigurierbar; bis zur v0.3.0 sollten
jedoch alle Menüs, Formulare und Listen entsprechen angepasst sein. Sollte
dennoch ein Punkt vergessen worden sein, bitte ich um einen kurzen Hinweis
(ich würde an dieser Stelle ja ein kostenloses Update als Preis anbieten - aber
angesichts der Lizenz dieses Produktes nähme das eh niemand ernst :)

[text]
<b>*site_info#:</b> Bis einschließlich v0.3.4 folgte die Titelzeile des
Web-Browsers für phpVideoPro dem Muster "phpVideoPro v&lt;Version&gt; [
&lt;Job&gt; ]". Seit v0.3.5 gibt es einen neuen, konfigurierbaren Teil dieser
Titelzeile, welcher zwischen der Version und dem Job eingefügt wird:
"@ site_info". Dies ist z.B. hilfreich, wenn man verschiedene Installationen
zur selben Zeit in verschiedenen Browser-Fenstern geöffnet hat.


[eof]

