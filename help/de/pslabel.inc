<? /* list of actors, directors, composers */ ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
Als Alternative zum PHP basierten Label-Generator, welcher einfach nur "plain
Text" auf PNG Bilder setzt, hat Michael Hasselberg den PS Label Generator
erstellt (und wartet auch den Code hierfür). Aufbauend auf PostScript-Templates
ergeben sich hier wesentlich bessere und umfangreichere Möglichkeiten des
Designs - von der zusätzlichen Flexibilität einmal ganz zu schweigen.

[text]
Als Voraussetzung für die Benutzung dieses Label-Generators muss auf dem
(Client-) System ein PostScript Prozessor (und Betrachter) installiert sein.
Für Linux (und andere *nix) basierte Systeme bedarf dies keiner besonderen
Erwähnung: mir ist keine Distribution bekannt, die nicht bereits mit
GhostScript einher kommt. Für Windows (und andere Betriebssysteme) kann es
jedoch notwendig sein, einen solchen separat zu installieren - was jedoch in
den seltensten Fällen ein Problem darstellen sollte. Wer das PostScript Label
System benutzen möchte, sollte halt lediglich sicher stellen, das ein solcher
Prozessor/Viewer installiert ist.

[title]
*labeltype#

[text]
Wird "PS Label" über das Menü aufgerufen, muss zunächst ein Label Typ festgelegt
werden. Die Engine ist so konzipiert, dass der Druck auf fertigen Label-Sheets
(mit selbstklebenden Labels) erfolgen kann - aber natürlich nicht muss: er kann
durchaus auf einfachem Papier erfolgen, und die erzeugten Etiketten können dann
von Hand ausgeschnitten und mit Pritt-Stift o.a. auf die Tapes geklebt werden.

[text]
Die Auswahl-Box auf dieser Seite gibt den Label-Typ an (unter diesem Namen
können die Label-Sheets im einschlägigen Fachhandel bezogen werden) und zeigt
zusätzlich auf, wohin die erzeugten Etiketten anschließend geklebt werden
sollen: z.B. auf die Seite oder das Top einer VHS Kassette. Nach getroffener
Auswahl führt, wer hätte das gedacht, der "*layout_label#" Button zum zweiten
Schritt:

[title]
*print_label#

[text]
Hier sind die Nummern der Medien einzugeben, für die ein Etikett generiert
werden soll. Während wir im vorigen Punkt die <b><i>Maße</i></b> des Etiketts
festgelegt haben, geht es hier um das Design: welche Farben und Grafiken sollen
benutzt werden. Auch wenn die Namen der Designs zumeist an Kategorien erinnern
(auf diesen basieren die von mir erzeugten Vorlagen auch), werden sie aus zwei
Gründen <b><i>nicht</i></b> automatisch ausgewählt: erstens können auf dem
jeweiligen Medium durchaus mehrere Filme verschiedener Kategorien sein, und
zweitens weiß phpVideoPro beim Aufruf dieser Seite ja noch gar nicht, für
welche Medien Etiketten erzeugt werden sollen. Sicher ließe sich für den
zweiten Punkt irgend was mit JavaScript machen - aber JavaScript vermeide ich
für phpVideoPro lieber, soweit dies möglich ist ;)

[text]
Sind alle nötigen Angaben gemacht, werden die gewünschten Etiketten nach
Betätigen des *create# Buttons erzeugt. Keine Sorge bezüglich nicht ausgefüllter
Felder: ist für ein Feld keine Nummer eingetragen, wird hier auch kein Etikett
generiert. Und dies gilt nicht nur für die Anzahl, sondern auch die Position:
dadurch ist es möglich, einen nicht vollständig aufgebrauchten Bogen auch
vollständig aufzubrauchen.

[eof]
