# /* add_entry */
# /* $Id$ */

[title]
Introductie

[text]
Bij dit menu item is het mogelijk om een nieuwe video op te nemen in de database.
De meeste velden spreken voor zich; maar er zijn er een aantal die meer uitleg
nodig hebben (los van het (naamloze) bovenste invulveld welke de naam van de film moet 
bevatten ;-)):

[title]
MediaType

[text]
<IMG SRC="{base_url}help/img/mtype_nr.png" ALT="piece of 'add entry' menue: mediatype" ALIGN=LEFT HSPACE=5>
Het 'MediaType'-veld (rood gemarkeerd in het screendump) geeft een lijst van
beschikbaar mediatypes waar uit gekozen kan worden. De lijst zelf behoeft geen
uitleg denk ik, maar ik wil even de aandacht richten op de twee andere gemarkeerde
delen: er is een tweedelig medianummer (blauw). Het eerste deel staat voor het fysieke 
medium, bijvoorbeeld de videoband of DVD. Het tweede deel staat voor de film op het
medium. Laten we zeggen dat er twee film zijn opgenomen op band nummer 20. De eerste
film krijgt dan als nummer 20-1 en de tweede film 20-2.
  
[text]
Laten we eens aannemen dat er twee films op een lege band zijn opgenomen. Dan moeten we 
deze noteren in de database, maar nu is de vraag welk medianummer er als laatste is
gebruikt. De groene cirkel op het plaatje geeft de plek aan waar dit terug te vinden is 
<b>voor elk mediatype</b>!
Klik op het boxje om de volledige inhoud te zien. Voor het invoeren is deze box verder
niet van belang waar deze box op staat, het is puur ter informatie. De groen omcirkelde
waarde wordt dus niet in de database opgeslagen.

[text]
Nog even iets over het blauw omcirkelde medianummer: De combinatie van nummer die
hier ingevoerd wordt, bijvoorbeeld het fysieke medium en het nummer daarbij, samen met 
het geselecteerde mediatype, moet uniek zijn in de volledige database. Er is dus maar 
één DVD nummer 1 in de collectie, de volgende DVD moet dan nummer 2 zijn, en zo verder.
Het programma is dus niet bedoeld voor het beheer van een videoverhuurwinkel of voor
een commerciële videobanden bibliotheek, maar wel voor uw privé collectie.

[title]
Aanschafdatum

[text]
Op dit moment moet de datum als volgt worden ingevuld: vier getallen voor het jaar,
minteken, twee getallen voor de maand, minteken en twee getallen voor de dag
(Dit resulteert dus in: JJJJ-MM-DD). Indien je een nieuwe film aan het invoeren bent,
dan wordt er standaard de datum van vandaag ingevuld. Dit veld blijft voorlopig zoals
het nu is, voor mij voldoet het en zolang niemand klaagt.... ;-)

[title]
Categorieën

[text]
De categorie die geselecteerd is in het eerste veld zal worden weergegeven in 
de standaardoverzichten binnen het systeem. Indien je zoekt naar een film 
(voorlopig door het gebruik van de filter functie) door het aangeven van een
categorie, zal er worden gezocht in alle drie de categorieën.

[title]
Staf

[text]
Let even op bij het invullen van de gegevens in de velden aan de rechterkant. Het
eerste veld is de achternaam, het tweede veld is voor de voornaam. Namen 
worden opgeslagen in een aparte tabel, er wordt bij de filmgegevens alleen een verwijzing naar 
deze tabel opgenomen. Indien je dit niet zo invult, dan kun je later in problemen komen.
Op de <A HREF="http://www.qumran.org/homes/izzy/">demo site</A>, was er al te zien,
dat iemand twee namen in één veld had neergezet. Dit kun je wel doen, maar dat betekent
dat als je later een overzicht wilt hebben van alle films waarin een persoon voorkomt,
dit natuurlijk niet gaat lukken. 

[text]
Daarnaast is er een aankruisvakje bij iedere naam, getiteld 'In lijst'. Dit is, ook,
een leuke optie. Er zal de mogelijkheid zijn om een lijst te maken van alle acteurs, 
tezamen met de naam van de film waarin zij gespeeld hebben.
Door dit aankruisvakje aan te vinken, geef je aan of deze film getoond moet worden
bij deze acteur. Indien, bijvoorbeeld, jouw favoriete acteur op dit moment erg
serieuze rollen speelt, maar vroeger in enkele se* films (die je alleen maar voor, 
laten we zeggen, het verhaal hebt opgenomen), dan kun je er voor kiezen om het 
vakje niet aan te vinken. Op deze manier zal niemand in de lijsten zien dat deze acteur
in deze film heeft gespeeld.
[eof]

