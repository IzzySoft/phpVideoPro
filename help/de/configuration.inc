# /* configure */
# /* $Id$ */

#==================================================================[ Intro ]===
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
phpVideoPro verwendet Cookies zur Verwaltung der Preferences (persönlichen
Einstellungen, wie Filter, Template-Set, Datensätze pro Seite bei Listen etc.).
Um diese Funktion zu nutzen, muss die Schaltfläche "*enable_cookies#" aktiviert
sein. Über das "*Admin#" Menü wird unter "*configuration#" die Konfiguration
verwaltet, und es werden die Default-Einstellungen für die Preferences hier
vorgenommen. Diese werden bei "neuen" Benutzern sodann aus der Datenbank
geladen. Änderungen, die der Benutzer sodann unter "*edit#" -&gt;
"*preferences#" vornimmt, werden in Cookies gespeichert und auch, sofern
gespeicherte Cookies vorhanden sind, aus diesen geladen. Die Standard Filter
Einstellungen werden über "*admin#" -&gt; "*admin_filter#" vorgenommen. Damit
nur authorisierte Benutzer Zugriff auf Konfiguration und Default-Einstellungen
haben, sind die entsprechenden Administrationsseiten über das Session-Management
geschützt: nur mit der "Admin" Berechtigung kann hier Zugriff erlangt werden.
Auch wenn das Administrationsmenü ohne diese Berechtigung überhaupt nicht
angezeigt wird, wird selbige auf den jeweiligen Seiten nochmals überprüft: sie
lässt sich also nicht einfach durch die direkte Angabe der URL umgehen.

#======================================================[ Language Settings ]===
[title|1|lang]
*language_settings#

[text]
<b>*scan_new_lang_files#:</b> Zur Speicherung der für das Übersetzungsmodul
benötigten Daten verwendet phpVideoPro seine Datenbank. Will man also eine
neue Sprache hinzufügen, muss die entsprechende Sprachdatei (eine Textdatei,
die die benötigten SQL Statements hierfür enthält) importiert werden. Dazu
muss diese dem System zunächst bekannt gemacht werden - dies geschieht durch
das Aktivieren dieser Box (und natürlich anschließendes Versenden des Formulars).
Die weiteren Schritte folgen unten. Wie eine neue Sprachdatei (z.B. für eine
neue Sprache, die bislang noch nicht von phpVideoPro unterstützt wird) erstellt
werden kann, findet sich in der Hilfe zum Punkt "<A HREF="{PHP_SELF}?topic=howto_lang">*howto_lang#</A>".

[text]
<b>*select_add_lang#:</b> Natürlich können hier nur verfügbare Sprachen
ausgewählt werden (das sind jene, zu denen bereits eine Sprachdatei existiert) -
phpVideoPro gehört nicht in die Kategorie "KI" und kann daher nicht mal eben
eine neue Sprache selbst erfinden :) Um die Übersetzungen für eine bereits
installierte Sprache zu aktualisieren, gibt es den nächsten Punkt.

[text]
<b>*refresh_lang#:</b> Steht eine neuere Version einer bereits installierten
Sprachdatei zur Verfügung (oder hat man selbst eine vorhandene Sprachdatei
angepasst), können hiermit die entsprechenden Einträge in der Datenbank
aktualisiert werden. Dabei werden alle bestehenden Einträge für die ausgewählte
Sprache zunächst aus der Datenbank gelöscht, und sodann die Einträge aus der
Sprachdatei importiert. Die Möglichkeit, bestehende Einträge beizubehalten, und
nur neue zu importieren, gibt es derzeit noch nicht.

[text]
<b>*delete_lang#:</b> Sei es zu Testzwecken, für eine Präsentation für
fremdsprachige Freunde/Bekannte, oder einfach nur so: manchmal kommt man an den
Punkt, einfach Übersetzungen für zu viele Sprachen installiert zu haben, und
möchte nun endlich wieder Ordnung schaffen. Dafür ist dies der richtige Platz:
Für die ausgewählte Sprache werden alle Übersetzungen aus der Datenbank entfernt,
wobei die Sprachdatei selbst nicht berührt wird. Sind Änderungen an den
jeweiligen Übersetzungen gemacht worden (z.B. mit Hilfe des eingebauten
Translation-Editors), sollten diese allerdings mit selbigem zuvor in eine
Datei gesichert werden. So läßt sich sicherstellen, die Übersetzungen zu einem
beliebigen zukünftigen Zeitpunkt wieder re-installieren zu können. Hinweis: die
Englischen Übersetzungen können nicht gelöscht werden - sie werden als "FallBack"
für alle anderen Sprachen benötigt.

[text]
<b>*select_primary_lang#:</b> Aus den vorhandenen Sprachen kann eine als
"Primärsprache" ausgewählt werden. Das heißt, phpVideoPro versucht alle
Bildschirmausgaben in dieser Sprache durchzuführen. Ist die Übersetzung für
eine Phrase nicht in der "Primärsprache" vorhanden, wird in den Englischen
Übersetzungen gesucht. Schlägt auch dies fehl, taucht ein "Sprachcode" des
Programmierers auf - sollte dies nicht auf einen Benutzerfehler (wie etwa eine
gelöschte Englische Sprache) zurückzuführen sein, erbitte ich eine
Nachricht an mich, damit ich den Fehler beheben kann!

#====================================================[ Media Configuration ]===
[title|1|media]
*config_media#

[text]
<b>*rw_media#:</b> Für Medien wie z.B. Original-Videokassetten oder DVDs macht
es wenig Sinn, "Bandreste" zu verwalten - weil es einfach keine gibt. Bei
anderen Medien wiederum, wie z.B. selbst bespielten Videokassetten, gehört die
Verwaltung verbleibender freier Zeit zu den elementaren Funktionen, die von
einer Software wie phpVideoPro (mit Recht) erwartet werden. Manch einer erstellt
sich seine VideoCDs selbst, ein anderer kauft sie ausschließlich. In einigen
mittlerweile gar nicht mehr so seltenen Fällen erstellen Anwender gar ihre DVDs
selbst, und benötigen daher auch für diese die Restzeit-Verwaltung. Um jedem
gerecht zu werden, ist dieser Punkt konfigurierbar. Es sind hier also die
Medien zu markieren, für die Restzeiten verwaltet (und angezeigt) werden sollen.

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
<b>*movie_tone_default#:</b> Bislang war das immer "Mono" - aber ich denke, das
ist kaum mehr der richtige Wert. Der hier eingestellte Wert wird als Vorgabe
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

#================================================================[ Cookies ]===
[title|1|cookies]
*cookies#

[text]
<b>*enable_cookies#:</b> Ist diese Schaltfläche nicht aktiviert, werden keine
Cookies verwendet. Die Benutzer-spezifischen Einstellungen werden stattdessen
in einer separaten Tabelle der Datenbank gespeichert (die globalen
Voreinstellungen werden dabei nicht  überschrieben). Gleiches gilt auch für die
Filtereinstellungen. Die Session-ID wird bei deaktivierten Cookies in der URL
mit übermittelt.

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

#==========================================================[ IMDB Settings ]===
[title|1|imdb]
IMDB

[text]
<b>*imdb_url#:</b> Die Internet Movie DataBase bietet umfangreiche Daten für
viele Filme. Diese können aus phpVideoPro heraus einfach abgerufen werden, indem
im Betrachtungsmodus eines Filmeintrages auf den Button des Titels oder des
Crew-Mitglieds geklickt wird. Während die Namen der Crewmitglieder sich für
gewöhnlich nicht ändern, kann der Filmtitel bei synchronisierten Fassungen
durchaus vom "Original-Titel" abweichen - was sodann eine manuelle Suche auf
der IMDB Site erforderlich macht. Eine höhere Trefferwahrscheinlichkeit lässt
sich daher erreichen, wenn hier eine Site ausgewählt wird, die mit der
häufigsten Sprachversion der in phpVideoPro gespeicherten Filmtitel überein
stimmt - für Deutschland wäre dies die deutsche IMDB Site.
[text]
Leider gibt es noch nicht für alle Sprachen eine eigene IMDB Site. Die mir
bekannten Sites sind bereits als Optionen verfügbar - wenn jemand weitere Sites
kennt, bitte ich um eine kurze Notiz, damit ich sie ebenfalls einpflegen kann!

[text]
<b>*imdb_url2#:</b> So schön die Tatsache ist, dass es "lokalisierte" IMDB Sites
u.a. auch für den deutschsprachigen Raum gibt, haben diese doch neben dem
großen Vorteil, dass hier auch nach dem landessprachlichen Filmtitel gesucht
werden kann, einen großen Haken: Das einzige, was hier "übersetzt" wurde, ist
(bislang) die Oberfläche. Der Inhalt ist ansonsten überall identisch. Wollten
wir jetzt also alle lokalisierten Sites unterstützen, müssten wir beim Parsen
der Seiten sämtliche verfügbaren Sprachen berücksichtigen - ohne dass wir für
diesen Aufwand auch mit landessprachlichen Informationen belohnt würden. Daher
wechselt phpVideoPro, sobald der Film eindeutig identifiziert ist, zu einer der
Englischen Instanzen der IMDB, um die Details von dort zu beziehen.
[text]
Es ist also zwingend notwendig, an dieser Stelle eine <b><i>Englische</i></b>
Site auszuwählen.

[text]
<b>*imdb_tx#:</b> Dies ist lediglich eine Voreinstellung für die Checkboxen
auf der <A HREF="{PHP_SELF}?topic=imdbsearch">IMDB Suchseite</A>. Natürlich
können später bei Bedarf gezielt andere Werte verwendet werden, ohne dies erst
hier wieder anzupassen.

[text]
<b>*imdb_txwin_autoclose#:</b> Diese Angabe bezieht sich auf das IMDB-Fenster,
welches sich aus dem Formular <A HREF="{PHP_SELF}?topic=add_entry">*add_entry#</A>
öffnen lässt. In diesem Fenster wird sodann die IMDB zu Informationen über den
gerade bearbeiteten Film abgefragt. Sind die gewünschten Informationen
schließlich gefunden, und der Anwender hat den Button zur Datenübernahme
betätigt, wird dieses Fenster nicht länger benötigt, und kann daher geschlossen
werden. Mit diesem Punkt in der Konfiguration läßt sich festlegen, ob dies
geschehen soll.

[text]
<b>*imdb_cache_enable#:</b> Die IMDB Caching Funktionen sind eigentlich nur für
Testzwecke interessant: Ist der Cache aktiviert, werden die von der IMDB-Site
bezogenen Details zum Film (also Schauspieler, Plot, etc.) in selbigem abgelegt.
Genau genommen heißt das: phpVideoPro legt von den entsprechenden HTML-Dokumenten
eine Kopie im IMDB Cache Verzeichnis ab. Sollte also wieder einmal etwas mit
dem IMDB LookUp fehlschlagen, können die Entwickler auf diese Weise schneller
feststellen, welche Spezifikationen auf der IMDB-Site wieder einmal verändert
wurden, und dann den Code der IMDB Klassen entsprechend anpassen. Für den
täglichen Umgang mit phpVideoPro bringt dies kaum Vorteile, da der Anwender die
aus der IMDB bezogenen Daten ja in die eigene Datenbank kopiert, und den selben
Film kaum ein zweites Mal abrufen wird.

[text]
<b>*imdb_cache_dir#:</b> In diesem Verzeichnis werden die IMDB-Daten bei
aktiviertem IMDB-Cache (s.o.) gespeichert. Da sowohl die Lese- als auch die
Schreibzugriffe vom Prozess des Webservers durchgeführt werden, muss dieser
auch Lese- und Schreibrechte auf das hier angegebene Verzeichnis besitzen. Da
die Daten der IMDB ohnehin für jeden einsehbar sind, kann eine entsprechende
Berechtigung unter Linux/Unix am einfachsten mit dem Befehl
<code>chmod 0777 <i>Verzeichnisname</i></code> erteilt werden (was kurz gesagt
heißt: Jeder Benutzer des lokalen Systems darf in dieses Verzeichnis wechseln,
sich den Inhalt anzeigen lassen, sowie Dateien lesen und schreiben). Wer dennoch
Sicherheitsbedenken hat, übereignet das Verzeichnis dem Benutzer des Webservers
und gibt nur diesem die entsprechenden Rechte. Das könnte z.B. so aussehen:<br>
<code>chown wwwrun.www <i>Verzeichnisname</i><br>chmod 0700 <i>Verzeichnisname</i></code>

[text]
<b>*imdb_cache_use#:</b> Die Funktion des IMDB Cache in phpVideoPro wurde bereits
weiter oben (unter <i>*imdb_cache_enable#</i>) beschrieben. Dort ging es
allerdings nur um das <b><i>Speichern</i></b> der Cachedaten. Wird zusätzlich
die Funktion <i>*imdb_cache_use#</i> aktiviert, wird der Cache auch bei LookUps
verwendet - d.h., wenn für einen Film bereits alle Daten im Cache abgelegt sind,
wird die IMDB für diesen nicht mehr kontaktiert. Stattdessen werden die
entsprechenden Daten dem Cache entnommen.


#=======================================================[ General Settings ]===
[title|1|general]
*general#

[text]
<b>*template_set#:</b> Das Design betreffend basiert phpVideoPro auf Templates.
Hier lässt sich das gewünschte Template-Set auswählen, und phpVideoPro erhält
auf diese Weise eine "neue Haut" ("Skins", wie sie auch von Programmen wie
XMMS bzw. WinAmp bekannt sein dürften).


[text]
<b>*printer#:</b> Um eine exakte Positionierung der Etiketten auf den zu
verwendenden Label-Sheets gewährleisten zu können, müssen die genauen
Seitenränder des zu verwendenden Druckers bekannt sein. Ist der gewünschte
Drucker in der Liste nicht enthalten, kann zunächst einer der vorhandenen
"getestet" werden: manche Drucker sind bezüglich Ihrer "Rand-Einstellungen"
kompatibel (so viele Möglichkeiten gibt es ja auch nicht). Ist ein "kompatibler"
Drucker dabei, wäre eine Nachricht an mich hilfreich mit Angabe des genutzten
und des ausgewählten Druckers. Zukünftige Versionen von phpVideoPro könnten
dann eine "Drucker-Kompatibilitäts-Liste" enthalten.<BR>
Passt keine der vorhandenen Druck-Einstellungen, muss Wohl oder Übel ein neuer
Drucker in die Datenbank eingetragen werden. Das hierfür zu verwendende Formular
findet sich im Administrations-Menü unter dem Punkt <i>*admin_printers#</i>
(näheres siehe <i><A HREF="{PHP_SELF}?topic=admin_printers">hier</A></i>).

[text]
<b>*cache_enable#</b>: Mittels spezieller Informationen im sogenannten "Header"
einer HTML-Datei (das ist ein für den normalen Anwender unsichtbarer Bereich)
lassen sich sowohl Proxies (Zwischenspeicher) als auch Browser (Mozilla &amp;
Co) anweisen, eine Seite für eine bestimmte Zeit im Cache zu halten - oder
halt nicht. Ist die Seite im Cache vorhanden, und das "Haltbarkeitsdatum" noch
nicht überschritten, wird sie bei einem erneuten Aufruf nicht neu vom Server
angefordert, sondern aus dem Cache bezogen. Gerade bei dynamischen Seiten (wie
sie bei phpVideoPro der Fall sind), ist dies nicht immer unbedingt erwünscht.
Hinzu kommt, dass manche Browser (u.a. der MSIE) die Seiten teilweise selbst
dann noch aus dem Cache beziehen, wenn der Anwender explizit den Button für
"Seite neu laden" betätigt - was recht nervig sein kann.
[text]
Ob also eine Seite in den Cache wandern soll - oder eben nicht, läßt sich mit
dieser Option festlegen. phpVideoPro sendet dann die jeweils nötigen Anweisungen
an den Proxy bzw. Browser.

[text]
<b>*display_limit#:</b> Ältere Versionen von phpVideoPro zeigten Listen, wie
z.B. unter dem Menüpunkt "*medialist#" zu finden, stets in voller Länge, d.h.
mit allen Datensätzen an. Bei umfangreichen Datensammlungen führte dies nicht
nur zu langen Ladezeiten, sondern konnte durchaus auch recht unübersichtlich
werden. Daher lassen sich diese Listen nun in mehrere "Häppchen" unterteilen.
Die Größe dieser "Häppchen" lässt sich mit diesem Punkt einstellen: er gibt an,
wie viele Zeilen die jeweilige Tabelle haben soll. Innerhalb der Listen ist eine
Navigation mittels vier Buttons möglich: diese führen jeweils zur ersten/letzten
bzw. vorigen/nächsten Seite.

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
Möglicherweise wird dieses Format noch nicht in allen Menüs, Formulare und
Listen berücksichtigt. Sollte dies jemandem auffallen, bitte ich um einen kurzen
Hinweis zwecks Korrektur (ich würde an dieser Stelle ja ein kostenloses Update
als Preis anbieten - aber angesichts der Lizenz dieses Produktes nähme das
ohnehin niemand ernst :)

[text]
<b>*site_info#:</b> Während der Beginn der Titelzeile des Browserfensters
generell dem Muster "phpVideoPro v&lt;Version&gt;" und das Ende derselben " [
&lt;Job&gt; ]" folgt, lässt sich der Teil dazwischen an dieser Stelle
konfigurieren: "@ &lt;site_info&gt;" wird sodann dazwischen eingefügt. Dies ist
z.B. hilfreich zur Orientierung, wenn man verschiedene Installationen zur
selben Zeit in verschiedenen Browser-Fenstern geöffnet hat.

[eof]
