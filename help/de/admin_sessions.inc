<? /* $Id$ */ ?>

[title]
*intro#

[text]
Hier werden alle bei phpVideoPro registrierten Sitzungen aufgelistet. Ferner
hat der Administrator auf dieser Seite die M�glichkeit, registrierte Sitzungen
nach ausgew�hlten Kriterien zu entfernen und damit auch gleichzeitig zu beenden.

[text]
Wird eine Sitzung gel�scht/entfernt/beended, ist sie nicht l�nger g�ltig. Das
hei�t mit anderen Worten auch, dass ein User, der gerade mit einer solchen
Sitzung arbeitet, sich erneut anmelden (einloggen) muss; dies kann besonders
�rgerlich sein, wenn gerade umfangreiche Daten eingegeben, aber noch nicht
gespeichert wurden, da in diesem Fall eine komplette Neueingabe erforderlich ist.
Daher ist zu empfehlen, mit dieser Funktion vorsichtig umzugehen.

[title]
L�schen beendeter Sitzungen

[text]
Hiermit kann man niemandem weh tun: es werden lediglich die Sitzungen gel�scht,
bei denen der jeweilige User sich ohnehin bereits abgemeldet hat. Ein solcher
Eintrag hat nur noch statistischen Wert. Ist phpVideoPro entsprechend
konfiguriert, ist dieser Job unn�tig: phpVideoPro kann automatisch "alte"
Eintr�ge aus der Datenbank entfernen. Die entsprechende Einstellung ist auf
der <A HREF="{PHP_SELF}?topic=configuration">Konfigurations-Seite</A>
vorzunehmen (siehe dort).

[title]
L�schen �lterer Sitzungen

[text]
Die eben beschriebene automatische Reinigung greift auch hier: sofern
eingerichtet, werden automatisch alle Eintr�ge aus der "Session Table" gel�scht,
die nicht auf eine g�ltige Sitzung verweisen. Ist sie jedoch nicht aktiviert
(der TimeOut also auf "nie" gestellt), ist eine Aufr�umaktion von Zeit zu Zeit
sinnvoll, sofern man die �bersicht behalten will.

[title]
Beenden einer spezifischen Sitzung

[text]
Dies ist recht einfach m�glich, indem der zugeh�rige "*delete#" Link benutzt
wird. Hierbei wird nur die angegebene Sitzung entfernt, alle anderen bleiben
davon unbeeinflusst.

[eof]
