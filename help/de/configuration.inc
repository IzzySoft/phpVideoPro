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

[text]
Seit Version 0.3.8 kann phpVideoPro Cookies zur Verwaltung der Preferences
(persönlichen Einstellungen, wie Filter, Template-Set, Datensätze pro Seite bei
Listen etc.) verwenden. Um diese Funktion zu nutzen, muss die Schaltfläche
"*enable_cookies#" aktiviert sein. Über das "*Admin#" Menü wird unter
"*configuration#" die Konfiguration verwaltet, und es werden die
Default-Einstellungen für die Preferences hier vorgenommen. Diese werden bei
"neuen" Benutzern sodann aus der Datenbank geladen. Änderungen, die der Benutzer
sodann unter "*edit#" -&gt; "*preferences#" vornimmt, werden in Cookies
gespeichert und auch, sofern gespeicherte Cookies vorhanden sind, aus diesen
geladen. Die Standard Filter Einstellungen werden über "*admin#" -&gt;
"*admin_filter#" vorgenommen. Es ist eine gute Idee, das admin/ Verzeichnis
sodann durch eine ".htaccess" Datei zu schützen, um nur authorisierten Benutzern
den Zugriff auf Konfiguration und Default-Einstellungen zu geben.

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
*config_media#

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
<b>*movie_onlabel_default#:</b> Wenn jemand die letzten 10..20 Minuten seiner
Videokassetten gern mit ein paar VideoClips von MTV füllt, möchte er diese
Clips nicht unbedingt auch auf dem Label stehen haben - sonst könnten diese
Label teilweise recht unübersichtlich werden. Daher läßt sich für jeden Eintrag
einstellen, ob dessen Informationen bei Generierung eines Labels für das
betreffende Medium eingeschlossen werden sollen. Hier läßt sich festlegen, wie
die Einstellung für neue Einträge vorbelegt sein soll.

[text]
<b>*movie_tone_default#:</b> Bislang war das immer "Mono" - aber ich denke,
das ist kaum der richtige Wert. Der hier eingestellte Wert wird als Vorgabe
für neue Einträge verwendet. Wer also ausschließlich (oder überwiegend) DVDs
mit Dolby 5.1 erwirbt, sollte hier auch Dolby 5.1 einstellen.

[text]
<b>*movie_color_default#:</b> Heutzutage werden die meisten Filme in Farbe
ausgestrahlt - daher ist es natürlich auch sinnvoll, wenn dies die
Voreinstellung für neue Einträge ist. Andernfalls mag es unter den Anwendern
auch solche geben, die überwiegend Filme aus den Zwanziger Jahren sammeln,
welche freilich in schwarz/weiß sind. In diesem Fall wäre es natürlich
wünschenswert, die Voreinstellung entsprechend anzupassen. Dies kann hier
geschehen.

[title]
*cookies#

[text]
<b>*enable_cookies#:</b> Ist diese Schaltfläche nicht aktiviert, werden keine
Cookies verwendet. Das heißt dann allerdings auch, das Änderungen, die ein
Benutzer im Menü "*edit#" -&gt; "*preferences#" vornimmt, ebenfalls in die
Datenbank geschrieben werden, und somit die Voreinstellungen überschreiben.
Gleiches gilt auch für die Filtereinstellungen. Mit anderen Worten: phpVideoPro
verhält sich damit wie in den vorangegangenen Versionen, und es kann zu
Problemen führen, sollten mehrere Benutzer dieselbe Installation simultan
verwenden. Für eine Einzelplatz-Installation kann jedoch genau dieses Verhalten
erwünscht sein.

[text]
<b>*expire_cookies#:</b> Hiermit wird definiert, nach welchem Zeitraum erstellte
Cookies auf dem System des Benutzers wieder gelöscht werden. Wird hier
"*session#" gewählt, verbleiben die Cookies nur solange auf dem System, bis der
Benutzer seinen Browser wieder schließt. In den anderen Fällen bleiben sie für
den jeweils angegebenen Zeitraum aktiv.

[text]
<b>*session_purgetime#:</b> Wenn sich ein Benutzer bei phpVideoPro anmeldet,
werden ihm/ihr zusätzliche Rechte eingeräumt, die dem entsprechenden Konto
zugewiesen wurden - dies kann z.B. das Bearbeiten und/oder Löschen von Daten
beinhalten. Verläßt dieser Benutzer nun z.B. seinen Arbeitsplatz, ohne sich
zuvor abzumelden, besteht die Gefahr, dass jemand anderes seine Sitzung benutzt
und Daten manipuliert. Um dieses Risiko möglichst gering zu halten, bietet
phpVideoPro die Option, eine inaktive Sitzung nach einem definierten Zeitraum
zu löschen. Die vom Benutzer in seinen "Keksen" gespeicherten Einstellungen
sind hiervon nicht betroffen: er/sie wird lediglich vom System abgemeldet, und
verfügt somit (bis zu einer erneuten Anmeldung) lediglich noch über die Rechte
des Gast-Kontos.

[title]
*general#

[text]
<b>*printer#:</b> Um eine exakte Positionierung der Etiketten auf den zu
verwendenden Label-Sheets gewährleisten zu können, müssen die genauen
Seitenränder des zu verwendenden Druckers bekannt sein. Ist der gewünschte
Drucker in der Liste nicht enthalten, kann zunächst einer der vorhandenen
"getestet" werden: manche Drucker sind bezüglich Ihrer "Rand-Einstellungen"
kompatibel (so viele Möglichkeiten gibt es ja auch nicht). Ist ein "kompatibler"
Drucker dabei, wäre eine Nachricht an <A HREF="mailto:izzysoft@qumran.org">mich</A>
hilfreich mit Angabe des genutzten und des ausgewählten Druckers. Zukünftige
Versionen von phpVideoPro könnten dann eine "Drucker-Kompatibilitäts-Liste"
enthalten.<BR>
Passt keine der vorhandenen Druck-Einstellungen, muss Wohl oder Übel ein neuer
Drucker in die Datenbank eingetragen werden. Erfahrene Anwender können hierzu
die Tabelle "printers" anpassen: entscheidend sind hier lediglich die Einträge
in den Spalten "top_offset" und "left_offset" (vielleicht erstelle ich ja mal
ein FrontEnd hierfür ;). <b><i>ACHTUNG:</i></b> an dieser Tabelle vorgenommene
Änderungen können beim nächsten Update verloren gehen! Ist daher die korrekte
Einstellung gefunden, diese bitte mit zugehörigem Drucker-Namen an
<A HREF="mailto:izzysoft@qumran.org">mich</A> schicken, damit sie permanenten
Eingang in die Liste finden!

[text]
<b>*display_limit#:</b> Ältere Versionen von phpVideoPro zeigten Listen, wie
z.B. unter dem Menüpunkt "*medialist#" zu finden, stets in voller Länge, d.h.
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
Dies ist erst seit phpVideoPro v0.2.6 konfigurierbar; mittlerweile sollten
jedoch alle Menüs, Formulare und Listen entsprechen angepasst sein. Habe ich
dennoch einen Punkt übersehen, bitte ich um einen kurzen Hinweis (ich würde an
dieser Stelle ja ein kostenloses Update als Preis anbieten - aber angesichts der
Lizenz dieses Produktes nähme das eh niemand ernst :)

[text]
<b>*site_info#:</b> Bis einschließlich v0.3.4 folgte die Titelzeile des
Web-Browsers für phpVideoPro dem Muster "phpVideoPro v&lt;Version&gt; [
&lt;Job&gt; ]". Seit v0.3.5 gibt es einen neuen, konfigurierbaren Teil dieser
Titelzeile, welcher zwischen der Version und dem Job eingefügt wird:
"@ site_info". Dies ist z.B. hilfreich, wenn man verschiedene Installationen
zur selben Zeit in verschiedenen Browser-Fenstern geöffnet hat.


[eof]

