<? /* list of actors, directors, composers */ ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
Hier können Einstellungen für die PS Label Templates vorgenommen werden. Dabei
werden nicht die Templates selbst bearbeitet, sondern nur die technischen
Werte, die zu ihrer Verarbeitung benötigt werden. Im Einzelnen sind dies:
<UL>
 <LI>welche Templates verfügbar sind</LI>
 <LI>welchem Typ (z.B. Seiten- oder Top-Labels für VHS Kassetten) sie zugeordnet sind</LI>
 <LI>welche Bilddatei für den Hintergrund verwendet werden soll</LI>
 <LI>die Größe des Etikettes</LI>
 <LI>welche Kontroll-Datei (d.h. Template-Datei) die weiteren Einzelheiten für das Etikett beschreibt</LI>
</UL>

[title]
Die Liste

[text]
Die Verwaltung dieser Daten ist in zwei Teile untergliedert. Zunächst wird eine
Liste bereits verfügbarer Etiketten (mit den bei phpVideoPro in Listen üblichen
Navigations-Elementen) angezeigt. Diese ist alphabetisch nach dem Namen der
Templates sortiert. Von hier aus können Einträge gelöscht werden, oder aber man
gelangt zum nächsten Bildschirm, um ein neues Etikett hinzuzufügen bzw. ein
bereits existierendes zu bearbeiten. Für alle diese drei Aufgaben stehen
entsprechende Links bereit: zum Bearbeiten/Löschen unmittelbar neben dem
betroffenen Eintrag, zum Hinzufügen eines neuen Eintrags direkt im Tabellenkopf.

[title]
Der Editor

[text]
Hier wird der ausgewählte Eintrag bearbeitet (oder ein neuer hinzugefügt). Die
einzelnen Felder sollten "selbstredend" bezeichnet sein:

[text]
<table align="center" style="border:1px solid #000000;" width="95%">
 <tr><td><b>*pstpl_name#:</b></td>
     <td>der Name hat keinerlei technische Relevanz: die Templates können also
         frei nach Gusto benannt werden.</td></tr>
 <tr><td><b>*pstpl_type#:</b></td>
     <td>legt fest, auf welche "Label-Sheets" (Druckvorlagen) ein hiermit
         erstelltes Etikett passt, und in welcher Liste es somit angezeigt wird</td></tr>
 <tr><td><b>*graphic_file#:</b></td>
     <td>das zu verwendende Hintergrundbild (EPS-Format!)</td></tr>
 <tr><td><b>*template_file#:</b></td>
     <td>welche PS Template Datei die Struktur des Templates beschreibt (und
         z.B. auch, welche Daten wo auf selbigem erscheinen)</td></tr>
 <tr><td><b>*lower_left_corner#:</b></td>
     <td>die Koordinaten der unteren linken Ecke dieses Templates (normalerweise
         x=0 und y=0, also ganz unten links)</td></tr>
 <tr><td><b>*upper_right_corner#:</b></td>
     <td>Koordinaten der oberen rechten Ecke, d.h. der Abstand selbiger von der
         unteren linken Ecke in Punkten.</td></tr>
</table>

[text]
Wer sich jetzt über diese Maßangaben wundert: PostScript rechnet in Bildpunkten,
und beginnt eine Seite immer von unten links nach oben rechts aufzubauen. Und
wir haben hier schließlich <b><i>PS</i></b>Labels :-)

[text]
Sind alle Angaben gemacht, können diese mittels des Buttons "*update#" am Ende
des Formulars gespeichert werden. Geht alles gut, so wird das Formular neu
geladen, und mit einer entsprechenden Erfolgsmeldung versehen - wie es bereits
von der Bearbeitung der Film-Einträge her bekannt sein sollte.

[eof]
