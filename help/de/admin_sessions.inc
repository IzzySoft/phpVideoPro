<? /* $Id$ */ ?>

[title]
*intro#

[text]
Hier werden alle bei phpVideoPro registrierten Sitzungen aufgelistet. Ferner
hat der Administrator auf dieser Seite die Möglichkeit, registrierte Sitzungen
nach ausgewählten Kriterien zu entfernen und damit auch gleichzeitig zu beenden.

[text]
Wird eine Sitzung gelöscht/entfernt/beended, ist sie nicht länger gültig. Das
heißt mit anderen Worten auch, dass ein User, der gerade mit einer solchen
Sitzung arbeitet, sich erneut anmelden (einloggen) muss; dies kann besonders
ärgerlich sein, wenn gerade umfangreiche Daten eingegeben, aber noch nicht
gespeichert wurden, da in diesem Fall eine komplette Neueingabe erforderlich ist.
Daher ist zu empfehlen, mit dieser Funktion vorsichtig umzugehen.

[title]
Löschen beendeter Sitzungen

[text]
Hiermit kann man niemandem weh tun: es werden lediglich die Sitzungen gelöscht,
bei denen der jeweilige User sich ohnehin bereits abgemeldet hat. Ein solcher
Eintrag hat nur noch statistischen Wert. Ist phpVideoPro entsprechend
konfiguriert, ist dieser Job unnötig: phpVideoPro kann automatisch "alte"
Einträge aus der Datenbank entfernen. Die entsprechende Einstellung ist auf
der <A HREF="{PHP_SELF}?topic=configuration">Konfigurations-Seite</A>
vorzunehmen (siehe dort).

[title]
Löschen älterer Sitzungen

[text]
Die eben beschriebene automatische Reinigung greift auch hier: sofern
eingerichtet, werden automatisch alle Einträge aus der "Session Table" gelöscht,
die nicht auf eine gültige Sitzung verweisen. Ist sie jedoch nicht aktiviert
(der TimeOut also auf "nie" gestellt), ist eine Aufräumaktion von Zeit zu Zeit
sinnvoll, sofern man die Übersicht behalten will.

[title]
Beenden einer spezifischen Sitzung

[text]
Dies ist recht einfach möglich, indem der zugehörige "*delete#" Link benutzt
wird. Hierbei wird nur die angegebene Sitzung entfernt, alle anderen bleiben
davon unbeeinflusst.

[eof]
