<? /* administration of categories */ ?>
<? /* $Id$ */ ?>

[title]
Beschreibung der Spalten

[text]
<TABLE ALIGN="center" BORDER="1">
  <TR><TD><B>ID</B></TD>
      <TD>Fortlaufende Nummer (keine Funktion)</TD></TR>
  <TR><TD><B>*cat_internal_name#</B></TD>
      <TD>programminterner Name der Kategorie</TD></TR>
  <TR><TD><B>*category#</B></TD>
      <TD>Bezeichnung der Kategorie in der aktuellen Sprache</TD></TR>
  <TR><TD><B>&nbsp;</B></TD>
      <TD>Löschen bzw. unterdrücken einer Kategorie</TD></TR>
</TABLE>

[title]
Hinzufügen einer Kategorie

[text]
Soll eine Kategorie hinzugefügt werden, sind die entsprechenden Daten einfach
in die letzte (leere) Zeile einzutragen. Der Wert in der Spalte <i>*cat_internal_name#</i>
sollte dabei immer mit "cat_" beginnen.

[title]
Löschen einer Kategorie

[text]
Hierfür ist das Icon mit der Mülltonne gedacht. Damit man den Löschvorgang nicht
versehentlich auslöst, erfolgt zunächst noch eine Sicherheitsabfrage. Sollten
einer zu löschenden Kategorie noch Filme zugeordnet sein, wird diese nicht
gelöscht. Stattdessen erscheint eine Fehlermeldung. In diesem Fall müssen die
Daten der entsprechenden Filme zuerst angepasst werden, bevor die Kategorie
gelöscht werden kann. Die Filterfunktion hilft bei der Auffindung der
betroffenen Datensätze.

[title]
(De-) Aktivieren einer Kategorie

[text]
Mit dem Checkbutton lassen sich unbenutzte Kategorien ausblenden: sie werden
dann lediglich noch auf dieser Seite, nicht jedoch beim Editieren von
Datensätzen, Filtern oder im Suchbildschirm angezeigt. Somit kann man für
ein wenig mehr Übersichtlichkeit sorgen, indem man nur die benötigten Kategorien
aktiv lässt - ohne die anderen zu löschen, so dass man diese bei Bedarf schnell
wieder verfügbar hat.

[title]
Übersetzungen anpassen

[text]
Wenn also eine Übersetzung nicht gefällt, kann sie in diesem Formular angepasst
werden: einfach den entsprechenden Wert in der Spalte "*category#" ändern.

[text]
Ein Risiko bleibt dabei: mit dem Update auf die nächste Version, oder auch nur
mit der Installation einer aktuelleren Sprachdatei sind die selbst erstellten
Übersetzungen wieder überschrieben. Um dies zu vermeiden, hilft derzeit nur
ein kleiner "work-around": über den Menüpunkt zur Bearbeitung der Übersetzungen
alle Übersetzungen in eine Datei sichern, und vor dem nächsten Update die
entsprechenden Zeilen mit der neuen Sprachdatei verbinden. Hat man sich an o.g.
Regel gehalten, und alle Einträge in der Spalte <i>*cat_internal_name#</i>
beginnen mit "cat_", so sollten die entsprechenden Zeilen in der Sprachdatei
schnell aufgefunden sein.

[eof]
