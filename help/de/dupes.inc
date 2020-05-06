# /* dupe checks */
# /* $Id$ */

[title]
*intro#

[text]
phpVideoPro kennt verschiedene Stufen bei der Suche nach Duplikaten. Im Menü
finden sich die entsprechenden Einträge:
 <LI>*dupes#</LI>
 <LI>*dupes_strict#</LI>
 <LI>*dupes_own#</LI>
 <LI>*dupes_own_strict#</LI>
</UL>

[text]
Die folgenden Abschnitte beschreiben, wie phpVideoPro nach Duplikaten sucht,
und wie sich die einzelnen "Such-Typen" unterscheiden.

[title]
*dupes#

[text]
"Duplikate Einträge" bedeuten eigentlich nichts anderes, als dass der gleiche
Film mehrfach in der Sammlung vorhanden ist. Aber wie lässt sich das
feststellen? Der einfachste Weg ist der, nach Filmen mit identischen Titeln
zu suchen. Genau das passiert hier.

[title]
*dupes_strict#

[text]
Doch die obige Art zu suchen, stösst sehr schnell an ihre Grenzen: Es gibt
schon so viele Filme, und nicht selten verbergen sich hinter einem Namen nicht
nur "Neuauflagen", sondern grundverschiedene Filme. Wie lässt es sich nun
vermeiden, dass solche fälschlich als Duplikate "erkannt" werden? Da reicht es
auch nicht aus, die Länge des Filmes mit einzubeziehen, da das "Rohmaterial"
oft auf verschiedene Längen geschnitten wird (und das nicht nur von den
Sendern, die mehr Werbung unterbringen wollen). Es müssen andere Kriterien
her - und phpVideoPro nutzt sie. Auch wenn das noch keine Garantie gegen
"Fehlerkennungen" darstellt, klappt es in der Regel recht gut. Bei der Suche
mit "*dupes_strict#" wird ein Film as mögliches Duplikat ausgeschlossen, wenn
eines der folgenden Kriterien zutrifft:

[text]
<UL>
 <LI>Unterschiedlicher FSK (hier handelt es sich mindestens um eine andere
     Fassung des Filmes)</LI>
 <LI>Unterschiedliches Jahr (dies ist entweder ein Remake, oder ein komplett
     anderer Film)</LI>
 <LI>Unterschiedliche Audio-Tracks, und keiner der beiden Kandidaten umfasst
     alle Tracks des anderen (z.B. soll ein Film, der auf verschiedenen
     Datenträgern einmal in der Landessprache und einmal im O-Ton gespeichert
     ist, sicher nicht als Duplikat angesehen werden, oder?)</LI>
</UL>

[title]
*dupes_own# / *dupes_own_strict#

[text]
Mit Version 0.8.1 hat phpVideoPro eine neue Stufe der "Mehrbenutzer
Unterstützung" erklommen: Jetzt verwaltet jeder User seine eigene Kollektion.
Dennoch ist es möglich, auf die Sammlung anderer User zuzugreifen - sofern
diese den Zugriff gewähren. In diesem Fall finden die obigen Methoden auch
dann Duplikate, wenn sich der gleiche Film in verschiedenen Sammlungen (also
z.B. einmal in der von Peter, und einmal in der von Klaus) befinden.

[text]
Das kann man zwar als "tolles Feature" bezeichnen, da es einem ermöglicht,
gemeinsame Interessen (äh, Filme) aufzustöbern. Daher wurde diese Möglichkeit
auch beibehalten. Doch um Duplikate in der eigenen Kollektion aufzuspüren,
taugt das nicht wirklich. Daher stellen diese beiden Punkte das Äquivalent
zu den beiden zuvor besprochenen dar - mit dem Unterschied, dass die Suche
auf die eigenen Einträge begrenzt wird.

[eof]
