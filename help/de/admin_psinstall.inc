<? /* PSLabelPack (de-)installation and (de)registration */ ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
Auf dieser Seite lassen sich einige Aktionen zum ausgewählen PSLabel Pack
ausführen. Welche der Aktionen verfügbar sind, hängt nicht zuletzt von der
vorhandenen Installation und Konfiguration ab. Einige Aktionen sind ggf. nicht
verfügbar - diese sind dann auch nicht verlinkt, und als solche klar zu erkennen.

[title|1|installation]
Installation

[text]
Abhängig von der vorhandenen Konfiguration, gibt es bis zu 3 verfügbare Links
für die Installation:
<ul>
 <li>Download des Archivs: Immer verfügbar</li>
 <li><A HREF="#autoinstall">Download und Install</A>: Abhängig von der Konfiguration</li>
 <li><A HREF="#manualinstall">Install</A>: Nur verfügbar, wenn das Archiv bereits heruntergeladen und in das <code>pslabels/</code> Verzeichnis entpackt wurde</li>
</ul>

[title|2|autoinstall]
Automatische Installation

[text]
Dies ist sicher der bequemste Weg für den Anwender: Mit einem einzigen Klick
wird die gesamte Prozedur des Herunterladens, entpackens und registrierens
durchgeführt. Dies setzt jedoch voraus, dass das Installationsverzeichnis
(das <code>pslabels/</code> Verzeichnis im phpVideoPro Verzeichnis) auch für
den Webserver schreibbar ist. Wem das ein zu großes Sicherheitsrisiko
darstellt, dem verbleibt dann nur die <A HREF="manualinstall">manuelle
Installation</A>.

[title|2|manualinstall]
Manuelle Installation

[text]
Wenn das Installationsverzeichnis für den Webserver nicht schreibbar ist
(siehe <A HREF="#autoinstall">oben</A>), bleibt noch der "Fußweg": Das Archiv
über den ersten Link herunterladen, in das <code>pslables/</code> Verzeichnis
entpacken, und dann hier den "*psinst_query_inst#" Link für die Registrierung
mit der Datenbank klicken.

[title|1|remove]
Remove a PSLabel Pack

[text]
Auch für die De-Installation eines PSLabel Packs gibt es wieder die automatische
und die manuelle Variante. Und auch hier funktioniert die automatische Version
nur, wenn der Webserver schreibberechtigt ist für das <code>pslabels/</code>
Verzeichnis. Andernfalls lässt sich das Pack hier nur aus der Datenbank
austragen - und die Dateien müssen manuell gelöscht werden. Welche Dateien
das sind, teilt der De-Registrierprozess freilich mit.

[eof]
