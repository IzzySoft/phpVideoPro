# /* view entry */
# /* $Id$ */

[title]
Einleitung

[text]
In diesem Formular werden alle verfügbaren Informationen zum ausgewählten
Datensatz angezeigt. Normalerweise sollte dies keiner Erklärung bedürfen, da
der Anwender diese Informationen zumeist selbst erfaßt hat und somit ihre
Bedeutung kennen sollte (ist dies nicht der Fall, hilft ein Blick auf
die Hilfeseite für den Menüpunkt "<A HREF="{PHP_SELF}?topic=add_entry">*add_entry#</A>"),
aber...

[title]
Durchstöbern der Sammlung

[text]
Sicher kann man die virtuelle Videothek mit Hilfe des Formulares unter
"*view#" -&gt; "*start_page#" durchwandern. Aber in manchen Situationen wirkt
dieser Weg ein wenig umständlich. Daher habe ich jeweils links und rechts vom
Filmtitel einen Button zum Blättern hinzu gefügt, der jeweils mit dem vorigen
bzw. nächsten Eintrag verlinkt ist. Sollte er einmal nicht verlinkt sein, dann
gibt es gerade keinen weiteren Eintrag in dieser Richtung.

[title]
Kopieren bzw. verschieben eines Eintrags, Anpassen der Länge eines Mediums

[text]
Hin und wieder kann es nötig werden, einen Eintrag zu kopieren bzw. verschieben.
Dies ist z.B. der Fall, wenn mehrere Teile einer Serie erfasst werden (die nur
minimale Unterschiede in den Daten haben), oder ein bislang auf Kassette
vorhandener Film nun als DVD erworben wurde. Die dafür notwendige Funktion
versteckt sich hinter den Buttons "*mediatype#" und "*medianr#". Mehr darüber
läßt sich auf der Hilfeseite für das Formular
"<A HREF="{PHP_SELF}?topic=media_change">*media_change#</A>" erfahren.
[text]
In gleicher Form läßt sich das Formular zum Anpassen der Länge eines Mediums
erreichen, indem auf den Button für die Restzeit ("*Free#") geklickt wird.
Diese Funktion kann nicht nur nötig sein, wenn ein Eintrag auf ein anderes
Medium unterschiedlicher Länge verschoben bzw. kopiert wird. Sie wird auch
gebraucht, wenn gerade ein Medientyp neu als "(wieder)beschreibbar" deklariert
wurde, der vorher nur "lesbar" war. In diesem Fall muss ggf. für alle betroffenen
Medien auf diese Weise die Länge erfasst werden.

[title]
IMDB Informationen

[text]
Ein nettes Gimmik ist meiner Meinung nach der Gedanke, nähere Informationen
über einen Film, einen Schauspieler, Regisseur oder Komponisten mit nur einem
Mausklick verfügbar zu haben. Und so öffnet ein solcher Mausklick auf den Button
des entsprechenden Namens bzw. Vornamens (beide Buttons sind mit der gleichen
Funktion belegt) dann auch ein neues Fenster, in welchem die Informationen
über Name, Vorname und "Rolle" (also Schauspieler, Regisseur bzw. Komponist)
an die "Internet Movie DataBase" (kurz: IMDB) weitergereicht wird. Sind diese
Informationen eindeutig (d.h. sie identifizieren genau eine Person in der
IMDB), erscheint sogleich die gewünschte Seite mit biografischen und
filmografischen Daten. Andernfalls werden von der IMDB Site nähere Informationen
abgefragt (im Normalfall heißt dies: Anzeige einer Liste möglicher Namen, in
der man sodann auf den richtigen klicken muß).
[text]
Da es sich bei der IMDB um einen eigenständigen Service (bzw. ein eigenständiges
Produkt) handelt, hat phpVideoPro keinerlei Einfluß auf die dort verfügbaren
Informationen. D.h., wir sind weder für diese Informationen verantwortlich,
noch werden wir sie in irgendeiner Weise verändern :-) Wir dachten uns lediglich,
es wäre nett, diese auf Mausklick mit verfügbar zu haben.

[title]
Druck von Etiketten

[text]
Die mit "*print_label#" bezeichnete Auswahl-Box ermöglicht den Druck eines
Etiketts für das ausgewählte Medium. Es listet alle verfügbaren Vorlagen auf
und startet die Anzeige eines Etiketts für das gesamte Medium (also eines,
welches Titel und Laufzeit aller auf dem Medium verfügbaren Filme enthält).
Je nach Größe und Format eines Etikettes, ist die Anzahl der auf selbigem
verfügbaren Zeilen unterschiedlich: d.h. es können unter Umständen nicht alle
Informationen untergebracht werden. Wie viele Zeilen verfügbar sind, ist in der
Konfigurationsdatei des jeweiligen Etikettes festgelegt (siehe
"<A HREF="{PHP_SELF}?topic=howto_label">*howto_label#</A>").

[text]
Um selbsterstellte Etikett-Vorlagen zu verwenden, sind diese einfach in das
Verzeichnis "labels/" zu kopieren. Eine ".config" Datei wird zwingend benötigt;
diese enthält die notwendigen Angaben über Größe und Position der einzelnen
Felder. Ist darüber hinaus eine ".png" Datei gleichen Namens vorhanden, wird
diese dem Etikett zugrunde gelegt - andernfalls wird ein leeres (weißes)
Etikett erstellt (und natürlich beschriftet). Details sind der Seite
<A HREF="{PHP_SELF}?topic=howto_label">*howto_label#</A> zu entnehmen.

[eof]

