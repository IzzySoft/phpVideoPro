<? /* administration of categories */
 ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
Mit dieser Seite verhält es sich wie bei "*admin_cats#" - natürlich mit der
nicht unwesentlichen Abweichungen, dass hier <b><i>Drucker</i></b> bearbeitet
werden und keine Kategorien :-) Um einen Drucker zu entfernen, ist einfach das
Namensfeld zu leeren (und das Formular abzuschicken). Um die Einstellungen für
einen Drucker anzupassen, einfach die entsprechenden Werte verändern (und
ebenfalls den schönen Button am Ende der Seite drücken). Ein neuer Drucker
läßt sich in der letzten (leeren) Zeile hinzufügen.

[title]
Was ist ein Offset?

[text]
Der druckbare Bereich auf einem Blatt Papier stimmt nicht bei allen Druckern
überein: es mag Drucker geben, die an beliebiger Stelle auf dem Papier drucken
können. Die meisten Drucker benötigen zumindest einen schmalen Rand zur
Papierführung - aber auch hier sind sie sich nicht alle einig, wie schmal
"schmal" nun ist...

[text]
Wenn nun keine der vorhandenen Definitionen mit dem zu verwendenden Drucker
akkurat arbeitet, kann hier anhand der herausgefundenen Maße (Differenz der
Randeinstellungen bei einem Testdruck) ein neuer Drucker hinzugefügt, oder aber
auch ein bestehender angepasst werden.

[title]
Einheiten

[text]
In der Spalte "*units#" finden sich verschiedene Maßeinheiten, die vielleicht
nicht alle geläufig sind. Daher hier eine kurze Auflistung:
<TABLE ALIGN="center" BORDER="1" WIDTH="95%" STYLE="margin:5">
  <TR><TH CLASS="help">Einheit</TH><TH CLASS="help">Vergleich</TH><TH CLASS="help">Beschreibung</TH></TR>
  <TR><TD>pt</TD><TD>&nbsp;</TD><TD>Der "Punkt" ist die kleinste Einheit bei PostScript</TD></TR>
  <TR><TD>inch</TD><TD>72 pt</TD><TD>Alte britische Maßeinheit, der wohl auch unser "Zollstock" seinen Namen verdankt</TD></TR>
  <TR><TD>mm</TD><TD>2.83465 pt</TD><TD>Millimeter ist die kleinste metrische Maßeinheit, die in unserem Kontext einen Sinn ergibt</TD></TR>
  <TR><TD>cm</TD><TD>28.346 pt</TD><TD>Das gleiche wie 10 mm. Die Frage, ob PostScript nur 4 Stellen nach dem Komma unterstützt, geht an Michael (bis dahin am besten "mm" für genauere Angaben verwenden ;)</TD></TR>
</TABLE>

[title]
Eine letzte Anmerkung...

[text]
Hinzugefügte/geänderte Angaben können bei einem Update (oder einer Neuinstallation)
verloren gehen, daher sind...
<ol>
 <li>...Backups empfohlen (phpVideoPro bietet entsprechende Funktionen an)</li>
 <li>...Änderungen/Angaben für neue Drucker am besten an mich zu schicken, so
     dass Sie in neueren Versionen von phpVideoPro gleich mit enthalten sind.
     Dies stellt sicher, dass sie dann auch bei Updates bzw. Neuinstallationen
     erhalten bleiben ;)</li>
</ol>

[eof]

