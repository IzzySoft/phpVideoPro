# /* configure */
# /* $Id$ */

[title]
Introduktion

[text]
På denna skärm ställer du in globala defaults till phpVideoPro, som språk-
specifika inställningar, färger att använda etc. 
[title]
*language_settings#

[text]
<b>*scan_new_lang_files#:</b> För att hantera språken som är installerade
såväl som ytterligare tillgängliga, använder phpVideoPro dess egna
database. Så för att lägga till ett nytt språk, måste man
uppdatera detta. Detta är gjort med SQL-filer som jag för enkelhetens
skull kommer att kalla "språkfiler" framöver. En ny språkfil måste bli
introducerat till systemet, som görs med genom att kryssa i denna checkbox
(och
skicka formuläret, så klart :). Se "Språk att installera" nedan,
såväl som 
"<A HREF="{PHP_SELF}?topic=howto_lang">*howto_lang#</A>" för detaljer).

[text]
<b>*select_add_lang#:</b> Självklart, du kan bara installera tillgängliga 
språk - phpVideoPro tillhör inte kategorin av AI och kan inte skapa nya
språk "on the fly" :) För att uppdatera redan installerade språk, se
nästa föremål.

[text]
<b>*refresh_lang#:</b> Om du har en ny språkfil för ett språk du
redan har installerat, som innehåller korrigerade och fräscha tillagda fraser, 
behöver du ett sätt att byta ut dem gamla fraserna på. Detta är t.ex. i
det fallet när du uppdaterar från en
föregående version av phpVideoPro. För språket du valt här, tas alla fraser
bort från databasen och de nya språkfilerna importeras istället. Vid
något tillfälle i framtiden kanske jag lägger till en funktion för att
lägga till endast nya fraser och inte ta bort något
från databasen - Men det är inte gjort än. 
[text]
<b>*select_primary_lang#:</b> I mängden av installerade språk, kan
du välja din favorit. Om ditt modersmål finns med, antar jag
att du föredrar det :) För alla fraser som saknas i dina favorit-
språkfiler, kommer det att finnas
en "fall-back" till de engelska fraserna. Om den engelska frasen även den
saknas 
(vilket inte borde hända, såvida inte importeringen av den
engelska språkfilen misslyckades),
så finns det några "debug-fraser" som visas som du kan gissa dig till 
innehållet av.
Om detta skulle hända, och du vet att det inte är ditt egna fel
(till exempel eftersom du tog bort de engelska fraserna från databasen
manuellt ;) - var god upplys 
<A HREF="mailto:izzysoft@qumran.org">mig</A> om detta, där du
nämner den saknade frasen och vart felet uppstod.

[title]
*colors#

[text]
<b>*page_bg# / *table_bg# / *th_bg#:</b> Dessa inställningar renderas
inuti det eventuellt standard-valda stylesheet'et och namnen
är självförklarande.

[text]
<b>*template_set#:</b> med början från v0.1.5, är phpVideoPro baserat
på mallar.
Jag (författaren) bara stod till förfogande med ett initialt set av
mallar; men så fort det finns
ytterligare sets av mallar tillgängliga (som endast kommer att uppstå när
<b>DU</b>
skriver dem - Då jag inte är någon bra designer), är detta platsen att
göra ditt val på.

[title]
*general#

[text]
<b>*display_limit#:</b> Tidigare versioner av phpVideoPro visade listor,
till exempel med
*medialist# meny-föremålet, alltid i dess fulla längd, till exempel med
allt som är inskrivet som finns med i databasen. Har man en stor
samling, är detta inte bara något som leder till långa
väntetider för att ladda in sidan, men också den långa listan
skulle också kunna vara förvirrande för en eller 
annan person :-) Dock med början från version 0.2.3, tillhandahåller phpVideoPro
möjligheten att visa dessa listor i delar vars storlek du kan
specifiera här:
Hur många rader lines du önskar visas i dem listorna.
Navigering tillhandahålls av fyra knappar som flyttar dig till det
första/sista resp. föregående/nästa
sidan av den kompletta listan.

[text]
Jag måste erkänna att med personlistorna kan denna finess kanske 
fungera på ett skumt sätt: inte bara det att radräkningen skiljer sig från
det inskrivna 
"*display_limit#" - även kan det tillochmed skilja sig mellan sidor!
Anledningen är väldigt simpel: phpVideoPro anställer "*display_limit#"
på personalen här. Så skillnaden dyker upp när du markerat lite 
personalmedlemmar som inte ska visas 
(vid användning av valet "*in_list#" inom "*edit#" formuläret.

[text]
<b>*lines_per_page#:</b> Detta är för förberedelsen av "endast
text"-listor för utskrift (se <A
HREF="{PHP_SELF}?topic=listgen">*listgen#</A>) och specificerar det antal
rader som passar på ett ark papper. Efter dessa specificerade
antalet rader, blir en "form feed" insatt till att starta en ny sida. Du
kan överskrida
denna standard på *listgen# formuläret.

[text]
<b>*date_format#:</b> Specificerar formatet datumet borde presenteras
som. Detta
är en nyhet i v0.2.6 av phpVideoPro, så det kan vara ett par
kolumner/fält som ignorerar
detta värde (det kommer förhoppningsvis att inte vara något av detta i 
v0.3.0 and above - om
du hittar något som saknas sen, var god rapportera det till mig!). Det
skall användas
genom hela programmet för listningar, formulär och vad som än 
innehåller
ett datumfält.

[eof]

