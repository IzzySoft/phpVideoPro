<? /* administration of categories */ ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
Unter diesem Menüpunkt können die für Filme verfügbaren technischen Daten, wie
"*screen#", "*picture#", "*mediatype#" und "*tone#" bearbeitet werden. Es lassen
sich eigene Typen hinzufügen, wie auch vorhandene bearbeiten oder löschen.

[title]
Vorhandene Einträge bearbeiten

[text]
Um einen vorhandenen Eintrag anzupassen, ist auf das Edit-Icon in der selben
Zeile zu klicken. Dies führt sodann zu einer Maske, in der die zugehörigen Daten
bearbeitet werden können. So kann z.B. der ausführliche Name ("*name#") für
einen Typen geändert werden. Vorsicht geboten ist jedoch bzgl. des Kurznamens
("*sname#"): in älteren Versionen von phpVideoPro wurde dieser genutzt, um
verschiedene Prüfungen durchzuführen - und ich bin nicht sicher, ob ich alle
diesbezüglichen Referenzen im Code bereits angepasst habe...

[title]
Einen neuen Eintrag hinzufügen

[text]
Hierfür ist einfach auf "*add_entry#" in der letzten Zeile der Tabelle zu
klicken, zu der der gewünschte Eintrag hinzugefügt werden soll. Es erscheint
dann die gleiche Maske wie beim Bearbeiten oben - der Unterschied ist jedoch,
dass ein neuer Datensatz hinzugefügt (also ein zusätzlicher Typ verfügbar) wird,
für den die Warnungen hinsichtlich des "*sname#" (s.o.) natürlich nicht gelten.

[title]
Löschen eines Eintrags

[text]
Für diesen Zweck ist das Mülltonnen-Icon gedacht. Nach einem Klick auf selbiges
erscheint zunächst eine Aufforderung zur Bestätigung - falls man versehentlich
daneben geklickt hat (und z.B. eigentlich bearbeiten wollte). Hat man die
Löschung bestätigt, wird zunächst noch eine Integritätsprüfung durchgeführt:
Es sollte somit nicht möglich sein, einen Typ zu löschen, der noch von mindestens
einem Film referenziert wird.

[eof]
