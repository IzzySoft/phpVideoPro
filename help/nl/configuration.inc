# /* configure */
# /* $Id$ */

[title]
Introductie

[text]
Binnen dit scherm kun je een aantal globale instellingen voor phpVideoPro maken,
zoals de taal, kleuren, etc.

[title]
*language_settings#

[text]
<b>*scan_new_lang_files#:</b> 
De verschillende talen worden opgeslagen in de database. Om een nieuwe
taal toe te voegen aan het systeem, moet deze taal dus worden toegevoegd
aan de database. Dit wordt gedaan door SQL-bestanden welke ik voor het gemak
'taal-bestanden' zal noemen van nu af aan. Een nieuw taal-bestand wordt 
ingelezen door dit aankruisvakje aan te vinken (en het formulier te versturen
uiteraard ;-). Zie ook 'Taal installeren' hieronder en 
"<A HREF="{PHP_SELF}?topic=howto_lang">*howto_lang#</A>".

[text]
<b>*select_add_lang#:</b> Natuurlijk kun je taal-bestanden installeren.
phpVideoPro beschikt niet over enige intelligentie en kan de teksten dus niet 
vertalen in de taal die jij toevallig spreekt. Om taal-bestanden bij te werken,
zie het volgende stukje.

[text]
<b>*refresh_lang#:</b> 
Indien je een nieuw taal-bestand hebt voor een taal die al bestaat, omdat er 
toevallig een woordje verkeerd is vertaald, dan moet het oude taal-bestand eerst worden
verwijderd uit de database en dan moet de nieuwe worden geladen. Dit kan 
bijvoorbeeld ook noodzakelijk zijn indien er een nieuwe versie van dit programma
uitkomt.
Ooit zal ik een functie man die alleen nieuwe zinnen toevoegt en waarbij het niet 
nodig is om de oude te verwijderen, maar dat is nog niet gedaan.

[text]
<b>*select_primary_lang#:</b> 
Uit de lijst met geïnstalleerde talen, kun je jouw favoriete taal instellen. Indien
jouw moedertaal aanwezig is in dit lijstje, dan denk ik dat je voor die taal zal 
kiezen ;-) Voor alle zinnen die ontbreken in je favoriete taal, zal de engelse zin
worden afgedrukt (wat niet zal gebeuren, tenzij deze taal ontbreekt om een of andere 
reden), dan zal er een soort van foutmelding komen, waarvan je de inhoud wel zal
kunnen raden. Indien dit gebeurt en als je er heel zeker van bent dat niet jouw schuld
is (dus niet als je de engelse zinnen met de hand uit de database hebt verwijderd), dan 
kun je <A HREF="mailto:izzysoft@qumran.org">mij</A> een mailtje sturen,
stuur dan wel de missende zin mee, tezamen met de plek waar de fout is verschenen.

[text]
<b>*use_charset#</b>: 
Aangezien dit het hele beeld veranderd, moet je dit alleen veranderen als je zeker
weet wat je aan het doen bent. Aan de andere kant kun je er niet veel schade mee
aanrichten. Slechts de weergegeven tekst kan er een beetje raar uit zien en de 
gegevens in de database zullen wellicht wat problemen geven op lange termijn ;-)<br>
Indien je een nieuw taal-bestand hebt geladen met enkele speciale karakters, dan
is het wellicht nodig om deze waarde te veranderen. Ik heb het echter nog nooit nodig 
gehad, dus ik ben erg benieuwd naar de resultaten.

[title]
*colors#

[text]
<b>*page_bg# / *table_bg# / *th_bg#:</b> 
Deze instellingen worden in de standaard stylesheet opgenomen en de velden zijn, 
denk ik, overduidelijk.

[text]
<b>*template_set#:</b> Vanaf versie 0.1.5 is phpVideoPro gebaseerd op templates.
Ik (de auteur) heb een template meegeleverd; zodra er nieuwe templates beschikbaar
komen (wat alleen zal gebeuren indien JIJ deze maakt, dan is er hier de mogelijkheid
om hier de template te selecteren.

[eof]

