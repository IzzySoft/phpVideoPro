# /* set_filter */
# /* $Id$ */

[title]
Introduktion

[text]
Båda menyföremålen, "*set_filter#" så väl som "*unset_filter#",
anropar exakt samma formulär - med en liten skillnad:
"*unset_filter#" kommer att ta bort alla
filter först, så du kan starta med ett färskt formulär utan något
som blir inställt.

[title]
Filter-regler

[text]
<H4>Föremål placerade i en tabellcell tillsammans</H4>
<OL>
 <li><b>föremål som innehåller min/max värden</b><br>
     Dessa föremål är anslutna med OCH, så ifall du t.ex. skriver in 
     "Min 60" och
     "Max 90" för längd-fältet, betyder detta: alla filmer med en längd
     som är mellan 60 och 90 minuter. Självklart, ifall bara ett värde 
     (t.ex.: min ELLER max) är specificerat, kommer bara detta att finnas med.
 <li><b>title</b><br>
     här kan du skriva in någon <i>SubString</i> som innehålls i 
     titeln/titlarna du önskar visas; med "hard" inskrivet skulle
     du få matchningar av Beatles' "A Hard Day's Night" så väl som "Die Hard".
 <li><b>andra föremål</b><br>
     alla andra föremål är anslutna av ELLER, t.ex.: kryssa i rutan
     RVT och OVT för MediaTyp resulterar i alla kassetter, oavsett om det är
original(inköpta) videos eller självinspelade.
</OL>

[text]
<H4>Att kombinera tabellcell-föremål</H4>
Ensamma påståenden (där påståendena betyder innehållet av varje
tabellcell, ett bygge av celler, ett påstående) är anslutet till OCH.
Kryssa i "DVD" som MediaTyp
och "Science Fiction" som kategori resulterar dock i alla DVDs med
Science Fiction-filmer på.

[eof]

