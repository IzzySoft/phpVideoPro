<? /* Search IMDB and transfer results to edit screen */ ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
Die "Internet Movie DataBase" (IMDB) ist eine Website, auf der sich zu (fast)
allen Filmen Daten abrufen lassen. phpVideoPro kann diese Datenbank benutzen,
um beim Hinzufügen eines neuen Films (oder auch beim Bearbeiten eines bereits
gespeicherten) einiges von der lästigen Tipparbeit zu ersparen. Dies geschieht
an dieser Stelle.

[title]
Start der Suche

[text]
Wurde der Filmtitel bereits vor dem "Klick" auf den IMDB-Button im
<A HREF="{PHP_SELF}?topic=add_entry">*add_entry#</A> Formular eingegeben, wird
diese Seite übersprungen und mit dem <a href="#found">nächsten Schritt</a>
fortgefahren.

[text]
Andernfalls ist im Eingabefeld auf dieser Seite der Name des gesuchten Filmes
einzugeben, und anschließend der "<i>*submit#</i>" Button zu betätigen.
phpVideoPro nimmt dann Kontakt zur IMDB auf, und versucht selbigen aufzufinden.
Abhängig von der Geschwindigkeit des verfügbaren Internet-Zugangs (und der
Reaktionszeit der IMDB) kann dies ein kleines Weilchen dauern.

[title|1|found]
Gefundene Filme

[text]
Mit ein wenig Glück, wird der gesuchte Film auch gefunden (was in der Regel der
Fall ist). Nicht selten kommt es allerdings vor, dass die IMDB gleich mehrere
Einträge (= verschiedene Filme) vorschlägt. Diese werden auf dieser Seite
aufgelistet. Für den Zweifelsfall öffnet ein "Klick" auf den auch hier wieder
verfügbaren IMDB-Button ein neues Fenster, in welches die zugehörige Seite
direkt bei der IMDB geöffnet wird.

[text]
Ist der richtige Eintrag identifiziert, klickt man nun den entsprechenden
Namen direkt an - und gelangt so auf die phpVideoPro-Seite mit den aus der
IMDB bezogenen Details. Auch hier kann der Ladevorgang wieder ein Weilchen
dauern, da wir erneut die Seiten der IMDB (diesmal für die Details) abfragen
müssen.

[title|1|details]
Details zum Film

[text]
Wer hier angekommen ist, konnte den gewünschten Film erfolgreich in der IMDB
ausfindig machen. Jetzt gilt es, die Details auszuwählen, die in die Datenbank
von phpVideoPro übernommen werden sollen. Einzelne Details lassen sich daher
mittels der Checkboxen gezielt (ab)wählen. Die Voreinstellungen für diese
Checkboxen können im Menü <A HREF="{PHP_SELF}?topic=configuration">*preferences#</A>
festgelegt werden.

[text]
Das Land und Jahr der Produktion sollten eindeutig korrekt sein, also gibt es
hier auch keine Änderungs-/Auswahlmöglichkeiten. Anders sieht es hingegen
für die restlichen Daten aus: Manche Filme haben "Alternativtitel", daher gibt
es für den Titel eine Auswahlbox. Der erste Eintrag in dieser Liste ist der
"offizielle" Filmtitel, alle weiteren Einträge sind "Alternativtitel".

[text]
Abhängig vom "Heimatland", sind von der jeweiligen "<b><i>FSK</i></b>"
("<i>Freiwillige SelbstKontrolle</i>") andere "Mindest-Alter" für den Konsum
des Filmmaterials vorgesehen. Hier kann der zutreffende Wert ausgewählt werden,
welcher sich natürlich auf der "<i>*add_entry#</i>" Seite auch manuell ändern
lässt. Die <b><i>Länge</i></b> des Filmes kann (z.B. aufgrund von Werbefetzen
oder Kürzungen seitens der Sendeanstalt) vom Original abweichen, und lässt sich
daher hier korrigieren.

[text]
Was die <b><i>Kategorien</i></b> betrifft, so versucht phpVideoPro zu den
Vorschlägen der IMDB die korrespondierenden Werte aus der eigenen Datenbank zu
finden. Das klappt leider (noch) nicht immer; die Auswahl-Boxen lassen daher
eine Korrektur vornehmen. Ähnliches gilt auch für den <b><i>Regisseur</i></b>:
hier waren gelegentlich "mehrere Köche" am Werk - doch phpVideoPro kann nur
einen davon übernehmen. Welcher das sein soll, bleibt dem Anwender überlassen.
Soll es am Ende gar keiner sein, steht auch ein "leerer Eintrag" in der Liste
zur Verfügung.

[text]
Kommen wir zu den <b><i>Schauspielern</i></b>, die am betreffenden Film
mitgewirkt haben. In der Regel liefert uns die IMDB hierfür eine Liste, die auch
bei guter Bildschirmauflösung zum "Scrollen" einlädt - doch phpVideoPro
speichert bekanntlich nur fünf, und übernimmt daher auch nur die ersten fünf
markierten Einträge aus dieser Liste. Da die "wichtigsten" Namen zuerst gelistet
sein sollten, müsste die Auswahl in den meisten Fällen zutreffend sein - kann
aber bei Bedarf geändert werden. Eine Auswahl mehrerer Einträge lässt sich
erreichen, indem man die jeweiligen Namen bei gedrückter "&lt;Strg&gt;" Taste
mit der Maus anklickt.

[text]
Und zu guter Letzt haben wir meistens auch noch ein <b><i>Bild</i></b> sowie
eine <b><i>Zusammenfassung</i></b> der Story des Filmes zur Verfügung. Das Bild
wird automatisch von der IMDB auf den "lokalen" Rechner (d.h. auf den Rechner,
auf dem phpVideoPro installiert ist) übertragen und dort abgespeichert. Es
entstehen daher also keine "längeren Ladezeiten", wenn wir das Bild mit zu
unserem Eintrag hinzufügen. Wer das allerdings dennoch nicht möchte, löscht
einfach die Zeichenkette "[img]...[/img]" aus der Textbox heraus. Auch der Rest
des Textes lässt sich natürlich nach Belieben anpassen - leider gibt uns die
IMDB hier, unabhängig vom gewählen Server, (fast?) ausschließlich englische
Informationen, was nicht jedermanns Sache ist...

[eof]
