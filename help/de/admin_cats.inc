<? /* administration of categories */
 ?>
<? /* $Id$ */ ?>

[title]
Administration der Kategorien

[text]
Hier lassen sich die Kategorien editieren. Wenn also eine Übersetzung nicht
gefällt, kann sie in diesem Formular angepasst werden: einfach den entsprechenden
Wert in der Spalte "*category#" ändern. Soll eine Kategorie hinzugefügt werden,
sind die entsprechenden Daten einfach in die letzte (leere) Zeile einzutragen.
Zum Löschen einer Kategorie müssen die Daten für selbige aus den entsprechenden
Feldern gelöscht werden. Sollten einer zu löschenden Kategorie noch Filme
zugeordnet sein, wird diese nicht gelöscht. Stattdessen erscheint eine
Fehlermeldung. In diesem Fall müssen die Daten der entsprechenden Filme zuerst
angepasst werden, bevor die Kategorie gelöscht werden kann. Die Filterfunktion
hilft bei der Auffindung der betroffenen Datensätze.

[text]
Ein Risiko bleibt dabei: mit dem Update auf die nächste Version, oder auch nur
mit der Installation einer aktuelleren Sprachdatei sind die selbst erstellten
Übersetzungen wieder überschrieben. Um dies zu vermeiden, kann in der Spalte
"*cat_internal_name#" der interne Name der Kategorie ebenfalls angepasst werden.
Da dieser jedoch als "Schlüssel" für die Übersetzung dient, sollte sich hier
an die Regel gehalten werden, dass interne Kategorienamen immer mit "cat_"
beginnen müssen. Andernfalls besteht die Gefahr, dass es zu Konflikten mit
anderen Übersetzungen kommt. Das Resultat wäre ein fehlgeschlagenes Update:
entweder hier an dieser Stelle (falls bereits eine Übersetzung gleichen
"Schlüssels" existiert), oder bei einem späteren Update (wenn eine solche
Übersetzung von <B>mir</B> hinzugefügt werden sollte). Dieses Problem läßt sich
jedoch weitgehend vermeiden, wenn sich an meine Regeln gehalten wird :-)

[text]
Da bei der Aktualisierung von Übersetzungen bei einem Update bzw. über das
"*configuration#" Menü zunächst alle bestehenden Übersetzungen der betroffenen
Sprache gelöscht werden, ist es empfehlenswert, alle hier getätigten Änderungen
in einer separaten Datei zu speichern. Vor einem Update sollte der Inhalt dieser
Datei sodann der entsprechenden mitgelieferten Sprachdatei angehängt werden. Auf
diese Weise bleiben hier gemachte Änderungen erhalten.

[eof]

