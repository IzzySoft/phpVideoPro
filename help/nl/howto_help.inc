# /* How to create a help file */
# /* $Id$ */

[title]
Hoe maak ik mijn eigen helppagina's?

[text]
Dit is zelfs makkelijker dan de creatie van een nieuw taal-bestand. Vooral
sinds de wijzigingen die ik in versie 0.2 heb gemaakt. Sindsdien zijn de help
pagina's op een template gebaseerd, zodat kennis van HTML niet langer noodzakelijk
is, je kunt nu een simpel tekst bestand aanpassen, welke misschien wat macro- of 
HTML-code bevat, maar niets schokkends:

[text]
<OL>
 <LI>Ga naar de help directory, open help_topics.php met je favoriete tekstverwerker.
De structuur van dit bestand is overduidelijk. Een regel die start met 'headline' 
is een kop, een onderwerp start met 'li'. Het eerste woord in de brackets is het
help onderwerp. Kijk naar de naam van het onderwerp waar je het help-bestand 
voor wilt maken. 
<LI>Indien er geen enkel help-bestand is voor de taal waarin je het wilt vertalen, 
dan moet je een directory aanmaken voor deze taal. Je kunt de taal-code voor
deze taal vinden in "<A HREF="{PHP_SELF}?topic=howto_lang">*howto_lang#</A>". 
Dus maak een directory 'lang/fi' voor de Finse help bestanden.
<LI>Maak nu een bestand aan <onderwerp>.inc in deze directory of kopieer dit bestand
uit een andere taal, zodat je een voorbeeld hebt hou het zou moeten.
<LI>Open dit bestand in je favoriete tekstverwerker en vertaal dit onderwerp. Het formaat
van dit bestand staat hier beneden beschreven
<LI>Klaar. phpVideoPro zal dit help-bestand vanzelf vinden. Maak je niet druk over 
het feit dat je wellicht niet alle bestanden hebt vertaald. Indien het bestand
niet gevonden wordt in de geselecteerde taal, dan zal automatisch het Engelstalige
bestand gebruikt worden.
</OL>

[title]
Bestandsformaat

[text]
Het formaat van een help-bestand is erg simpel: elke regel die begint met een 
hekje ('#') wordt beschouwd als commentaar (wordt dus volledig genegeerd). The
eerste regel waarnaar gekeken wordt is de regel met de [title]. De laatste regel
is de regel die [eof] bevat. Er is ook nog een [text] gedeelte. [text] moet, solitair,
op een aparte regel staan. Maar moet er in deze gedeeltes worden ingevuld?
[text]
<ul>
 <li><b>[title]</b> geeft een kop aan. Alles wat hierop volgt (tot aan de start van het
volgende gedeelte wordt beschouwd als kop voor het [text]-blok dat er op moet volgen.
 <li><b>[text]</b> start het tekst gedeelte, hierin komt de gedetailleerde informatie.
Om meerdere alinea's te maken kun je meerdere [text]-gedeelten onder elkaar plaatsen.
 <li><b>[eof]</b> staat voor "End Of File" (einde van het bestand) en geeft aan dat
de informatie afgedrukt kan gaan worden.
</ul>
[text]
Je kunt de gerust de volgende HTML-code gebruiken om bepaalde woorden of zinnen
te benadrukken (of vanwege andere redenen): &lt;B&gt;Vet&lt;/B&gt; of om lijsten te 
genereren kun je &lt;UL&gt;-gebruiken, gebruik van tabellen, plaatjes, etc kan gedaan 
worden door standaard HTML. Koop een boek over HTML voor alle details. Nogmaals, het hoeft
niet, maar het mag wel

[title]
Macro's

[text]
Er zijn enkele macro's beschikbaar binnen de helpbestanden. Deze kunnen verdeeld
worden in twee categorieën: variabelen en vertaal-tags. Indien je een beetje bekend
bent met PHP (en met de code van phpVideoPro), dan kun je deze gebruiken.

[text]
Alles wat je plaatst tussen brackets wordt vervangen door de globale variabele met
die naam (indien beschikbaar). Deze variabele moet bijvoorbeeld geen spaties oid bevatten.
(koop een boek over PHP voor alle details.

[text]
Alles wat geplaatst is in de Duitse BTX-style, dus geplaatst tussen een asterisk (*) en een
hekje (#), ook weer zonder spaties en dergelijke, geeft aan dat deze tekst vertaald moet worden zoals deze is opgenomen in 
de taal-bestanden. Dit moet uiteraard wel voldoen aan de phpVideoPro taal regels.

[eof]
