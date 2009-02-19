# /* absolute taperest */
# /* $Id$ */

[title]
Backup und Restore der eigenen Filmdaten

[text]
Auf dieser Seite gibt es eigentlich nicht viel zu tun, da sie lediglich die
Ergebnisse der angestoßenen Aktion ausgibt. Dennoch, im Falle eines Fehlers
können ein paar Hinweise zu möglichen Ursachen nicht schaden:

[text]
<UL>
 <LI><b><i>*user_backup_store#</i></b> schlug fehl: Hier ist die wahrscheinlichste
     Ursache, dass das Backup-Verzeichnis schreibgeschützt (oder die Platte voll)
     ist. Andere Ursachen sind natürlich nicht ausgeschlossen.</LI>
 <LI><b><i>*user_backup_download#</i></b> fehlgeschlagen: Oi weh! Da fällt mir
     kein allgemeingültiger plausibler Grund ein...</LI>
 <LI><b><i>*user_backup_restore#</i></b> nicht möglich: Das kann durchaus daran
     liegen, dass zuvor noch gar kein Backup erstellt wurde. Auch wenn selbiges
     vorhanden, aber leer ist, lässt sich schlecht etwas daraus beziehen...</LI>
</UL>

[text]
Die Liste ist natürlich alles andere als vollständig - wie bei Computern (und
Murphy) üblich, gibt es immer ausreichend verschiedene Möglichkeiten, etwas
schief gehen zu lassen. Wer das Problem daher nicht selbst in den Griff bekommt,
schaut am besten im IRC (#izzysoft auf FreeNode) vorbei, oder erstellt auf der
<A HREF="{pvp->projectpage}" TARGET="_blank">Projekt-Site</A> ein entsprechendes
Ticket.

[text]
Noch eine Anmerkung: Die Wiederherstellung erfolgt hier immer aus dem aktuellsten
verfügbaren Backup. Der Admin hat jedoch ggf. die Möglichkeit, auch auf ältere
Sicherungsdateien zurückzugreifen.

[eof]

