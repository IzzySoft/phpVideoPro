# /* How to create a help file */
# /* $Id$ */

[title]
Hvordan lager jeg egene hjelpesider?

[text]
Det er til og med lettere enn  lage en ny sprkfil -  spesielt etter endringene
som ble lager for v0.2 da hjelpefilene ble basert p maler. N trenger du til og
med ikke  kunne HTML - du trenger kun  redigere en tekst fil som <b>kan</b>
inneholde noen makroer/HTML kode, men beh°ver det ikke:
[text]
<OL>
 <LI>finn katalogen der hjelpefilene ligger, pne help_topics.php med det
     programmet du °nsker  benytte til  redigere filen (igjen, filen er en ren
     tekst fil). Strukturen p filen er selvforklarende: en linje som starter med
     "headline" markerer en overskrift, et tema begynner med "li". Det f°rste
     ordet i paranteset er emnet. Let etter det temaet du °nsker  lage hjelpefil
     for.
 <LI>Dersom det ikke er en hjelpefil tilgjengelig for ditt sprk enda, m du
     opprette en katalog for ditt sprk f°rst. Finn sprkkoden for ditt sprk
     (se "<A HREF="{PHP_SELF}?topic=howto_lang">*howto_lang#</A>" for  lµre
     hvordan du kan gj°re dette), og opprett denne katalogen under hjelpekatalogen
     - m.a.o. "lang/fi" for Finsk.
 <LI>N kan du enter lage en ny fil med avnet <emne>.inc i din sprk katalog
     (f.eks. "lang/fi/about.inc" for en Finsk "about" emne), eller kopier det
     fra den engelske katalogen ("lang/en") og bruk denne som en mal.
 <LI>Bruk det redigeringsvert°yet du har valgt til  pne filen ("lang/fi/about.inc"
     i eksemplet vi valgte) og oversett/opprett emnet. Formatet p en slik fil
     er beskrever under.
 <LI>Det er alt - du er ferdig! phpVidePro vil automatisk finne og bruke
     hjelpefilene i det sprket brukeren har valgt. Ikke bekymre deg for om
     du ikke har <b>alle</b> filene tilgjengelig for ditt sprk: dersom
     phpVideoPro ikke har en hjelpefil tilgjengelig i ditt sprk, vil den
     Engelske versjonen bli vist.
  </OL>

[title]
Fil format
[text]
Det generelle formatet for hjelpefiler er meget enkel: hver linje starter med
et '#' tegn blir ansett som en kommentar (m.a.o. blir ignorert). Den f°rste
linjen som blir behandlet m vµre merket med '[title]' (mellomrom blir ignorert).
Filen blir lest inn inntil '[eof]' merket blir funnet, og f°rst da blir hjelpefilen
sendt til din nettleser. Det tredje merket som er pkrevd er '[text]'. Merker
<b>m</b> vµre plasert p separate linjer (igjen bli mellomrom ignorert)!<br>
S, hve betyr merkene?
[text]
<ul>
 <li><b>[title]</b> markerer en overskrift. Alt som f°lger dette merket (fram
     til neste merke, som i de fleste tilfeller vil vµre '[text]') er behandlet
     som en overskrift for den pf°lgende blokk.
 <li><b>[text]</b> begynner en blokk - her legges all informasjonen inn med alle
     detaljer. For  benytte mange paragrafer kan du legge inn mange '[text]'
     blokker etter hverandre.
 <li><b>[eof]</b> betyr "End Of File" og forteller at innlesningen kan stoppe,
     og framvisningen starte. Det forteller ogs at det ikke eksister mer av
     interesse i filen :)
</ul>
[text]
Du kan benytte alle HTML formaterings koder f.eks. til  framheve fraser
med &lt;B&gt;bold&lt;/B&gt; HTML-merker, lage lister med &lt;UL&gt;,
plasere tabeller, grafikk etc. Jeg vil ikke forklare hvordan man kan gj°re
dette - det finnes bedre beskrivelser tilgjengelig om dette. Igjen, du <b>m</b>
ikke benytte dette, men du <b>kan</b>.

[title]
Makroer

[text]
Det er noen makroer tilgjengelig i hjelpefilene. Di kan bli delt inn i to
kategorier: variabler og oversettere. Dersom du er litt fortrolig med PHP (og
muligens ogs med koden i phpVideoPro), s kan du benytte disse.
[text]
Alt som plaseres mellom {kr°ll-paranteser} er erstattet med innholdet av den
globale variablen med dette navnet dersom denne eksisterer). Denne variablen
m f.eks. ikke inneholder noen mellomrom etc. (Referer til en PHP manual for
dette).
[text]
Alt som er i Tysk BTX stil mellom et '*' og et '#' tegn (igjen ingen mellomrom)
indikerer til leseren at det skal bli oversatt ved bruk av fraser som er definert
i sprkfilene. Selvf°lgelig f°lger det reglene for oversettelse av phpVideoPro.

[eof]
