# /* How to create a new language file */
# /* $Id$ */

[title]
*intro#

[text]
Nicht zufrieden mit den vorhandenen Übersetzungen? Sind sie unvollständig? Oder
fehlen sie gar allesamt? Hier ist nun endlich der richtige Platz, um diesem
Problem relativ bequem bei zu kommen. phpVideoPro führt einfach durch die
notwendigen Schritte - und zum Schluss gipfelt das ganze in einer Sprachdatei
für phpVideoPro, die dann bitte an mich zu schicken ist :-)

[title]
Voraussetzungen

[text]
Das System des Arbeitsrechners muss so konfiguriert sein, dass es den
Zeichensatz der zu bearbeitenden Sprache oder einen solchen, der diesen
Zeichensatz als Untermenge enthält (z.B. ist US-ASCII eine Untermenge von
ISO-8859-1 und ISO-8859-1 wiederum eine Untermenge von ISO-8859-15) benutzt.
Desweiteren muss die als "primäre Sprache" ausgewählte Sprache ebenfalls diesen
Anforderungen entsprechen. Letzteres ist insbesondere unter Umständen dann nicht
möglich, wenn eine Sprache bearbeitet werden soll, die in phpVideoPro noch nicht
eingerichtet wurde; hierzu siehe weiter unten.

[title]
*sel_target_lang#

[text]
Auf dieser ersten Seite ist die Sprache auszuwählen, deren Übersetzungen
bearbeitet werden sollen. Sind für diese Sprache bereits Übersetzungen in der
Datenbank vorhanden, werden diese auf den folgenden Seiten mit geladen. Mit der
Sprache wird auch der zu verwendende Zeichensatz ausgewählt, sofern er phpVideoPro
bekannt ist (er ist dann in Klammern unmittelbar neben dem Namen der jeweiligen
Sprache aufgeführt) - andernfalls wird "ISO-8859-1" (= Latin-1) angenommen.

[title]
*admin_translations#

[text]
Handelt es sich bei der zu bearbeitenden Sprache um eine, die einen abweichenden
Zeichensatz verwendet, sollte auf dieser Seite zunächst über den Link
"*save_lang_file#" am Ende der Seite die (unfertige) Sprachdatei gesichert, der
Zeichensatz in selbiger korrigiert (in der Zeile, die mit "UPDATE" beginnt) und
über die Seite "*admin# -&gt; *configuration#" neu eingelesen werden. Gleiches
gilt auch für den Fall, dass einfach ein neuer Satz an Übersetzungen für eine
Sprache angelegt werden soll, für die bereits Übersetzungen vorhanden sind -
jedoch für diesen neuen Satz ein anderer Zeichensatz verwendet werden soll (wer
das nicht für möglich hält: für Russisch gibt es z.B. allein drei <b><i>Standard-</i></b>
Zeichensätze und darüber hinaus noch eine Reihe weiterer). In diesem Falle
sollten ggf. auch alle auf die "UPDATE" Zeile folgenden Zeilen aus der Datei
entfernt werden, bevor diese neu importiert wird.

[text]
Nun kann mit der Bearbeitung der Übersetzungen begonnen werden. Vor dem Wechsel
auf die nächste Seite (mittels der bereits von anderen Listen, wie z.B. der
"*medialist#", bekannten Steuerelemente) sollte nicht vergessen werden, etwaige
Änderungen mittels des "*update#" Buttons zu speichern.

[title]
Fertig?

[text]
Dann wird es Zeit, die vollbrachte Arbeit in eine Datei zu sichern (wiederum
über den Link "*save_lang_file#" am Ende der Seite). Damit steht sie nun auch
für neue Installationen zur Verfügung. Eine nette Geste wäre es an dieser Stelle
überdies, eine Kopie der Datei an den Autor von phpVideoPro, zu schicken (EMail
Adresse siehe <code>doc/README</code>): wer an meiner Arbeit so kostengünstig
teilhaben kann, hat so eine einfache Möglichkeit, "Dankeschön" zu sagen - und
andere Benutzer von phpVideoPro wird es sicher freuen, aktuelle Übersetzungen
in der nächsten Release vor zu finden :-)

[eof]
