# /* view entry */
# /* $Id$ */

[title]
Introduktion

[text]
Detta formulär visar alla tillgängliga detaljer om den valda noteringen.
Normalt sett ska det inte behövas någon förklaring, eftersom du borde känna tillt allt om
all data du skrivit själv (Om inte, kanske följande hjälpsida intresserar dig
angående "<A HREF="{PHP_SELF}?topic=add_entry">*add_entry#</A>"), men...

[title]
IMDB information

[text]
Om du vill ha tag i närmare info om en skådespelare, regissör eller kompositör:
bara klicka på knappen som det står hans/hennes namn på (eller förnamn, spelar ingen roll).
Detta kommer att öppna ett nytt webbläsarfönster vilket länkar till Internet Movie DataBase
(IMDB) som du överlämnar efternamn, förnamn och det personen i fråga sysslar med, med info taget från
phpVideoPro. Om denna information är entydig (alltså att det matchar IMDB's info), 
kommer detta att leda dig till sidan med infon du ville ha. Annars, kommer IMDB-sajten att fråga dig efter ytterligare
information: Detta kan vara en lista på folk som passade in på förfrågningen, eller
nånting om att den inte hittade informationen du ville ha.
[text]
Efter IMDB är en oberoende service/produkt, så kan inte phpVideoPro påverka informationen tillgänglig där - 
t.ex. så är vi inte ansvariga för detta, och vi kommer inte att ändra informationen där :-) 
Men vissa av oss kände, att det kunde vara en najs funktion att ge dig denna info med bara ett enda musklick...

[title]
Etikettutskrift

[text]
Valrutan titelerad "*print_label#" låter dig skriva ut en etikett för valda mediumet.
Det innehåller ett antal templates (mallar), och ska skriva ut titel och tid på <b>alla</b> filmer på det valda mediumet (om du t.ex.
visar "RVT 1234-2", och kassetten 1234 dessutom innehåller del 1 och
3, innehåller etiketten alla tre filmerna), men det är vid det här laget (v0.2.4) begränsat 
till ett antal av totalt 4 rader, i.e. movies per medium. Detta kan kanske göras tillgängligt i en senare version.

[text]
För att skapa dina egna etiketter, bara lägg dem i "labels/"-katalogen.
.config-filen behövs alltid och beskriver storleken på etiketterna
plus storleken och position på dem innehållande avsnitten. Om en .png-fil med samma namn
existerar, kommer det att användas - annars skapas en enkel (vit) mall (och med etikett, förstås). För detaljer, ta en titt på <A HREF="{PHP_SELF}?topic=howto_label">*howto_label#</A>.

[eof]

