# /* How to create a new language file */
# /* $Id$ */

[title]
Hvordan kan jeg opprette en spr†kfil for mitt spr†k?

[text]
Det er enklere en det du tror, og krever kun noen f† skritt:

[text]
<OL>
 <LI>finn setup katalogen, †pne filen tech_data.sql med en tekst leser
     (filen er ren tekst). P† slutten av denne filen  vil du finne en liste
     av spr†k sammen med deres spr†kkoder. For † gi et eksempel: linjen 
     <code>INSERT INTO languages VALUES ('fi','Finnish','No');</code>
     lar deg vite at Finsk har spr†kkoden "fi". Se etter spr†ket du °nsker
     † oversette til, og velg denne koden.
 <LI>I setup katalogen vil do ogs† finne et par spr†kfiler som allerede er
     tilgjengelig. Du kan kjenne dem igjen ved filnavnet som benytter formatet
     "lang_??.sql" - der "??" er den spr†kkoden som representerer spr†ket.
     Mest sannsynlig er det enda ingen spr†kfiler for ditt spr†k (ville du ha
     laget et da?), s† du kan velge en av di tilgjengelige spr†kfilene (jeg
     anbefaler den Engelske, lang_en.sql, da denne vanligvis er den mest
     oppdaterte spr†kfilene, med unntak av den tyske som vil vµre tilsvarende
     oppdatert), og kopier denne til din spr†kfil - i v†rt tilfelle er dette
     "lang_fi.sql".
 <LI>Benytt det verkt°yet du foretrekker † redigere filen med og oversett
     frasene. Hver linje begynner med SQL setningen som sier INSERT - ikke
     r°r denne delen ;) Det eneste du trenger † redigere er den siste av de
     3 delene du finner i paranteset. Oversett denne delen til ditt spr†k.
 <LI>N†r du er ferdig med dette, kan du fortelle phpVideoPro at det nye
     spr†ket er tilgjengelig. Start phpVideoPro og velg konfigurering fra
     menyen (*admin# -&gt; *configuration#), sett et merke i boksen for "S°k
     etter nye spr†kfiler?" og velg "Oppdater". Noen sekunder senere konfigurerings
     menyen komme tilbake og liste ditt spr†k i "Velg hvilket spr†k som skal
     installeres"
 <LI>Velg ditt nye spr†k og velg "Oppdater" p† nytt. Du kan da ogs† velge det
     nye spr†ket for bruk i phpVideoPro - og du er ferdig!
</OL>

[title]
Frasene passer ikke til mitt spr†k...

[text]
Du kan, selvf°lgelig, legge til og endre fraser i din spr†kfil. Dette kan f°re
til komplikasjoner ved oppgraderinger, der du (for n† i alle fall) m† manuelt
m† skjekke frasene. Etter at du har endret spr†k filen (eller mottatt en
oppdatering til den, m† du oppdatere den i phpVideoPro: Velg ditt spr†k i 
<A HREF="{PHP_SELF}?topic=configuration">konfigurasjons menyen.</A> Velg
"Oppdater spr†k" og deretter "Oppdater" p† nytt - alle gamle fraser (for det
valgte spr†ket) blir slettet fra databasen, og vil bli erstattet med frasene
fra din spr†kfil.

[eof]
