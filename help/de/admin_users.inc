<? /* administration of categories */ ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
Hier lassen sich die Benutzerkonten verwalten. Diese werden benötigt, um die
Daten vor unbefugtem Zugriff zu schützen: vor Manipulation, oder sogar vor
Einsicht.

[title]
Wie phpVideoPro Accounts verwendet

[text]
Defaultmäßig verwendet phpVideoPro den <i>guest</i> Account. Damit dieser
Standard funktionieren kann, darf dieser Account weder gelöscht, noch mit einem
Passwort versehen werden. Sollen &quot;Gäste&quot; komplett vom System
ausgeschlossen werden, sind von daher lediglich diesem Account alle Rechte zu
entziehen. Eine empfohlene gute Einstellung für dieses Gast-Konto ist, es
ausschließlich mit dem "Browse" Privileg zu versehen. Aber dies kann je nach
Einsatz von phpVideoPro variieren.

[text]
So lange sich der Besucher nicht angemeldet (eingeloggt) hat, verwendet
phpVideoPro das o.g. Gast-Konto. Die ebenfalls o.g. Einstellungen voraus
gesetzt, kann ein Besucher also keinerlei Daten ändern. Sobald dies nun
versucht wird (z.B. durch Betätigen des *edit# Buttons in der Datensatz-
Anzeige), wird nun nicht die gewünschte Seite (in diesem Fall zum Editieren
des Datensatzes) geladen, sondern der Besucher wird auf die &quot;Login&quot;
Seite weiter geleitet, damit er sich anmelden kann. Desweiteren sind einige
Menüs bereits ausgeblendet, sofern der (nicht) angemeldete Benutzer die
notwendigen Berechtigungen nicht besitzt (so z.B. das Administrations-Menü).

[title]
Einstellungen

[text]
Einige Einstellungen lassen sich direkt auf dieser Seite verändern, indem die
entsprechenden Checkboxen (nicht) gesetzt werden und anschließend der
&quot;*update#&quot; Button betätigt wird:
[text]
<table align='center' border='1' style='margin:5'>
 <tr><td><b>*read_access_short#</b></td>
     <td>Soll der Benutzer Daten betrachten können? Dies schließt die Anzeige
         von Listen sowie einzelnen Datensätzen ein, darüber hinaus jedoch auch
	 die Möglichkeit, Labels zu generieren.</td></tr>
 <tr><td><b>*add_access_short#</b></td>
     <td>Soll der Benutzer <b><i>neue</i></b> Einträge hinzufügen können? Dieses
         Privileg schließt das Ändern bereits existierender Einträge <b><i>nicht</i></b>
	 mit ein.</td></tr>
 <tr><td><b>*upd_access_short#</b></td>
     <td>Soll der Benutzer vorhandene Einträge verändern können? Erlaubt nicht
         auch das Hinzufügen neuer Einträge (siehe voriger Punkt).</td></tr>
 <tr><td><b>*del_access_short#</b></td>
     <td>Soll der Benutzer Einträge löschen können?</td></tr>
 <tr><td><b>*admin_access_short#</b></td>
     <td>Soll der Benutzer Zugriff auf die administrativen Seiten haben? Mit
         dieser Berechtigung kann sich ein Benutzer sämtliche Rechte selbst
	 zuweisen, Konten erstellen/löschen/modifizieren sowie beliebige
	 Einstellungen der Konfiguration ändern. Daher ist mit dieser
	 Berechtigung vorsichtig um zu gehen!</td></tr>
</table>

[text]
Um neue Benutzerkonten hinzuzufügen, oder weitere Details an bereits vorhandenen
Konten zu ändern, sind entsprechende Links vorhanden.

[eof]
