# /* add_entry */
# /* $Id$ */

[title]
Introduktion

[text]
Genom att använda detta menyföremål, kan du lägga in en ny notering i din video-databas. De flesta
fälten i detta formulär är självförklarande; men det finns några som behöver kommenteras
litegrann (förutom det faktum att den ej namngivna input-rutan ovanpå har som syfte att hålla
kvar filmtiteln ;):

[title]
MediaTyp

[text]
<IMG SRC="{base_url}help/img/mtype_nr.png" ALT="bit av 'lägg till notering' meny: mediatyp" ALIGN=LEFT
HSPACE=5>
Rutan "MediaTyp" (röd-markerad i bilden som visas) ger dig en lista på
tillgängliga mediatyper att välja från. Denna ruta i sig självt, behöver ingen
förklaring, antar jag - men jag vill dra din uppmärksamhet mot dem andra två markeringarna:
det finns ett tvådelat MediaNr att skriva in (blå-markerat). Den första biten står för
den fysiska median, till exempel kassett eller disk. Den andra biten gäller filmen på den median. 
Låt oss säga, att du har spelat in två filmer på kassett # 20, så den första
filmen borde vara 20-1 och den andra 20-2.
[text]
Nu till funktionen: Låt oss föreställa oss, att vi just har spelat in 2 filmer på en tom kassett,
 och nu vill du skapa databas-noteringarna för dessa. Är du säker på
att du kom ihåg det sista (fysiska) MediaNr du tilldelat? Den grön-markerade rutan
hjälper dig i ditt sökande efter det högsta tilldelade numret <b>för varje mediatyp</b>!
Öppna det bara, för att visa alla dess innehåll. För skapandeprocessen, är det inte
ett problem för alla, vilket värde du valt - den grön-markerade rutan är för din information
endast, dess innehåll är inte sparat någonstans i databasen.
[text]
Men ett sista ord om blå-markerade MediaNr: kombinationen av nummer
inskrivna här, t.ex. den fysiska kassetten och den logiska enheten på det, tillsammans med
den valda MediaTypen, måste vara unik genom hela databasen. Det 
är, t.ex, bara en DVD #1 i din samling, nästa DVD ska vara #2, 
osv... Detta programs syfte är inte att användas till att hantera någon videobutik eller
kommersiellt videokassettbibliotek, utan för privata samlingar endast :)

[title]
*date_rec#

[text]
Datumfältet är uppdelat i "månader och år"-fält. Tills vidare, är ordningen
hårdkodad att vara dag-månad-år. Naturligtvis kommer detta att ändras i en av dem
följande versionerna av phpVideoPro, att använda ordningen konfigurerad med datumformat-inställningen
i setup-menyn och att läsa av landspecifika inställningar (eller
med special-användar-inställningar :) i åtanke.

[title]
*counter_start_stopp#

[text]
Dessa fält är mestadels av intresse för dem av er som har videobandspelare
utan indexeringsfunktion: du kan skriva in räknarna från början
respektive slutet av din inspelning här. Eftersom den enda format-restriktionen
är en längd på 10 tecken, spelar det ingen roll om du skriver in enkla numeriska
räknar-värden, eller t.om. tidskoder här - beroende på hur din videobandspelare
visar tiden.

[title]
*commercials#

[text]
Även fast detta fält borde vara självförklarande, är en del ord på värderna att
välja: du markerar här ifall inspelningen är avbruten av "reklamblock"
("*yes#") eller inte ("*no#"), eller om du klipper bort dessa  block manuellt ("*cut_off#").
Om du inte kan komma ihåg, så har du t.om. möjligheten att säga till om din osäkerhet
här genom att välja "*unknown#".

[title]
Kategorier

[text]
Den valda kategorin i den första rutan kommer att visas jämsides med huvudfilms-
datan i listorna. Inte nog med det: om du söker efter en notering (just
nu genom att använda filter-funktionen) och specifierar en kategori, kommer alla tre av kategorierna
att tas i åtanke.

[title]
Personal

[text]
Var försiktig med att fylla i informationen i dem högra fälten här: det första är
alltid för familjenamnet, det andra för det första namnet. Namn på personalmedlemmar 
är inte lagrade tillsammans med film-datan, utan i en separat tabell.
Med film-datan, finns det bara en referens lagrad - så om du senare vill gå till
listan med några noteringar för en specifik person, så kan du hamna i trubbel: på
<A HREF="http://www.qumran.org/homes/izzy/">demosajten</A>, såg jag redan
noteringar som håller båda namndelarna i ett fält, bara för att lagra två personer i
en notering. Självklart <i>kan</i> du göra så - men det är inte så jag planerat det,
och några framtida funktioner behöver inte nödvändigtvis tänkas få denna möjlighet.

[text]
Slutligen, finns det en checkruta fastklistrad till varje namn, märkt "i listan". Denna,
också, refererar till en najs funktion: det kommer att finnas en möjlighet till att lista upp,
t.ex. alla skådespelare tillsammans med titeln på filmerna dem spelade en roll i.
Genom att markera denna checkruta, kan du bestämma ifall att denna film skall visas för
denna skådespelare. Om, till exempel, din favoritskådespelare nu spelar väldigt seriösa roller -
men faktiskt spelade i några se*-filmer tidigare, vilka du bara spelade in för, humm, låt oss
säga "intresse", men ingen förutom du skall nu få veta om detta (medan läsning av dina utskrivna kassettlistor),
behöver du bara kryssa av rutan här och han/hon kommer då inte att dyka upp tillsammans med
denna films titel i skådespelarlistan.

[eof]

