<? /* description of the Applicat template set */ ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
phpVideoPro hat ein Template-gesteuertes Frontend - was heisst, dass das
"Look-and-feel" der Anwendung relativ einfach an die eigenen Bedürfnisse
angepasst werden kann, indem man ein neues Template-Set hinzufügt bzw. ein
bereits bestehendes ändert. Das <I>Applicat</I> Template-Set ist das erste,
welches von dieser Funktionalität profitiert: bevor es der Anwendung hinzu
gefügt wurde, existierte lediglich das <I>Default</I> Template-Set.

[text]
Und obwohl <I>Applicat</I> sich hinsichtlich des Design der Formulare nicht 
wesentlich vom <I>Default</I> Template-Set unterscheidet, erscheint es
bedeutend klarer und bietet sogar zusätzliche Funktionalität: Die "TitleBar"
jeder Seite enthält einige "QuickLinks" zu wichtigen Funktionen, die bislang
nur durch teilweise mühsames Hangeln durch die Menüs erreichbar waren. Und
auch wenn diese Buttons intuitiv und selbsterklärend sein sollten, sind sie
in der folgenden Tabelle aufgeschlüsselt: ihre Funktion unterscheidet sich
teilweise geringfügig, abhängig davon, ob man sich in der Applikation selbst
oder im Hilfe-System befindet.

[title]
Beschreibung der Buttons

[text]
<TABLE ALIGN="center" WIDTH="90%" BORDER="1">
 <COLGROUP><COL WIDTH="14"><COL WIDTH="1*"><COL WIDTH="1*"></COLGROUP>
 <TR><TD></TD><TD><DIV ALIGN="center"><B>Applikation</B></DIV></TD>
     <TD><DIV ALIGN="center"><B>Hilfe-System</B></DIV></TD></TR>
 <TR><TD><INPUT TYPE="image" NAME="button_back" CLASS="imgbut" SRC="{base_url}templates/applicat/images/win_back.gif" STYLE="width:14;height:13;"></TD>
     <TD><DIV ALIGN="center">-</DIV></TD>
     <TD>Gehe einen Schritt in der History zurück (analog dem <I>Zurück</I> Button des Browsers)</TD></TR>
 <TR><TD><INPUT TYPE="image" NAME="button_close" CLASS="imgbut" SRC="{base_url}templates/applicat/images/win_close.gif" STYLE="width:14;height:13;"></TD>
     <TD>Abmelden und zurück zum Login Screen</TD>
     <TD><I>*help#</I> Fenster schließen</TD></TR>
 <TR><TD><INPUT TYPE="image" NAME="button_help" CLASS="imgbut" SRC="{base_url}templates/applicat/images/win_help.gif" STYLE="width:14;height:13;"></TD>
     <TD>Fenster mit Kontext-bezogener Hilfe öffnen</TD>
     <TD><DIV ALIGN="center">-</DIV></TD></TR>
 <TR><TD><INPUT TYPE="image" NAME="button_home" CLASS="imgbut" SRC="{base_url}templates/applicat/images/win_home.gif" STYLE="width:14;height:13;"></TD>
     <TD>Zur <I>*start_page#</I> gehen</TD>
     <TD>Zum <I>*index#</I> gehen</TD></TR>
 <TR><TD><INPUT TYPE="image" NAME="button_search" CLASS="imgbut" SRC="{base_url}templates/applicat/images/win_search.gif" STYLE="width:14;height:13;"></TD>
     <TD>Gehe zum <I>*search_movie#</I> Formular</TD>
     <TD><DIV ALIGN="center">-</DIV></TD></TR>
</TABLE>

[title]
Einstellungen

[text]
Für das <I>Applicat</I> Template-Set sind keine besonderen Einstellungen nötig.
Es kann über das Menü <I><A HREF="{_SERVER["PHP_SELF"]}?topic=configuration">*configuration#</A></I>
(de)aktiviert werden.

[eof]

