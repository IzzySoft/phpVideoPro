<? /* Movie Search Page */ ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
Wer schon einmal in seiner phpVideoPro Datenbank nach einem bestimmten Film
gesucht hat (und dafür bis einschließlich v0.4.4 lediglich die
<A HREF="{PHP_SELF}?topic=set_filter">Filter-Einstellungen</A> zur Verfügung
hatte, wird sicher bereits das eine oder andere Mal fast wahnsinnig geworden
sein. Um dem für die Zukunft vorzubeugen, gibt es seit v0.4.5 nun dieses
Formular. Es funktioniert ähnlich dem oben erwähnten für die Filter, mit einem
wesentlichen Unterschied: die "Filter" hier gelten nur für die aktuelle Suche,
während sie "dort" permanent (oder bis das Cookie expiriert) gespeichert
werden.

[text]
Tatsächlich werden zusätzlich zu den hier eingegebenen Kriterien auch noch die
Filter für die Suche mit heran gezogen - was nicht zuletzt daran liegt, dass
es sich hier sozusagen um eine "zweite Tür" zur Medienliste handelt (ein sog.
"Wrapper"). Daher sollten die o.g. Filter-Einstellungen nur so restriktiv
gesetzt werden, dass generell unerwünschte Einträge ausgeblendet sind - und eine
spezielle Suche dann über dieses Formular hier erfolgt.

[title]
Suchkriterien und "Treffer"

[text]
Die Eingabe hier folgt den gleichen Regeln wie bei den nun bereits mehrfach
angesprochenen Filtern: Mehrfachauswahlen in Feldern wie z.B. bei
"*mediatype#", werden mit "ODER" verknüpft; d.h. eine Auswahl von DVD und
VCD schließt beide Medientypen mit ein. Mehrere Felder werden mit "UND"
verbunden: eine Auswahl von z.B. "DVD" als Medientyp und "*cat_action#" als
Kategorie wählt ausschließlich die DVDs aus, die auch dieser Kategorie zugeordnet
sind. Das gilt auch für Felder, welche einen Minimum und ein Maximum erlauben,
wie dies bei "*length#" und "*fsk#" der Fall ist: sind beide Werte angegeben,
werden auch beide ausgewertet. Nicht selektierte Felder hingegen werden auch
nicht ausgewertet - bleibt also z.B. der Titel leer, werden alle Titel ausgewählt,
welche den übrigen Kriterien entsprechen.

[text]
Noch ein Wort zu den Text-Feldern "*comments#", Namen und "*title#": hier
erfolgt die Suche ohne Berücksichtigung von Groß- und Kleinschreibung auf
Wort-Bestandteile. Das heißt, eine Eingabe von "babylon" als Titel trifft
sowohl auf "Babylon 5" zu wie auch auf "The Rivers of Babylon" oder "Das
babylonische Exil". Dies gilt jedoch <b><i>nicht</i></b> für die Felder
"*length#" und "*fsk#" - hier werden die Eingaben strikt ausgewertet.

[title]
Suchergebnisse

[text]
Die Suchergebnisse werden auf die gleiche Art präsentiert, wie man es bereits
von der <A HREF="{PHP_SELF}?topic=medialist">*medialist#</A> gewohnt ist - und
die Navigation in selbigen erfolgt auch auf die von dort bekannte Art und Weise.

[eof]
