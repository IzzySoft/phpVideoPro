<? /* administration of categories */
 ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
Disk-Typen und RegionCodes beziehen sich immer auf das gesamte Medium, daher
können sie in phpVideoPro auch nicht gemeinsam mit den Film-Daten bearbeitet
werden. Entweder werden diese Daten zusammen mit denen des ersten Filmes eines
neuen Mediums erfasst - oder halt später über diese Seite ergänzt/korrigiert.

[title]
*disk_type#

[text]
Ein Disk-Typ besteht aus einem oder zwei Teilen: immer enthalten ist der
eigentliche Disk-Typ selbst, und in vielen Fällen kommt die Größe des Mediums
hinzu. Diese beiden Angaben helfen heraus zu finden, ob sich die betreffende
Disk auf einem bestimmten DVD-Player wiedergeben läßt (so mancher Player
unterstützt z.B. keine DVD-R oder gar überhaupt nichts selbst gebranntes), ob
ein Backup mittels einer einfachen 1:1 Kopie möglich ist, und mehr. Darüber
hinaus sind verschiedene Features (wie z.B. Regional-Codes) nur für bestimmte
Disk-Typen (in diesem Falle DVDs) verfügbar.

[title]
*region_code#

[text]
Für die Anzahl der gleichzeitig erfassbaren RegionalCodes gibt es eigentlich
kein Limit (außer, dass es nur die Codes 0..6 gibt). Eine Mehrfach-Auswahl ist
hier möglich, da ich bereits von ein paar DVDs gehört habe, die mehr als einen
(aber dennoch nicht alle) RegionalCodes unterstützen. Für RC-freie DVDs sollten
dennoch nicht alle Felder markiert werden: der Code "0" steht für "code-free"
und sollte in diesem speziellen Fall als einziger verwendet werden. Natürlich
steht es jedem frei, trotzdem alle Häkchen zu machen - das ist aber wirklich
nicht nötig :-)

[eof]

