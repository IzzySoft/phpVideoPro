# /* How to create a new language file */
# /* $Id$ */

[title]
Hoe kan ik een taal-bestand aanmaken voor mijn taal?

[text]
Het is niet zo moeilijk als dat je misschien denkt en er zijn slechts enkele
stappen voor nodig:

[text]
<OL>
<LI>Ga naar de setup-directory, open texh_data.sql met je favoriete tekstverwerker
(het is een plat tekst bestand). Aan het eind van dit bestand, vind je een lijst
van alle talen met hun eigen code. Om een voorbeeld te geven kun je in dit bestand
de volgende regel vinden:
<code>INSERT INTO languages VALUES ('fi','Finnish','No');</code>
Dit geeft aan dat de Fins de taalcode 'fi' heeft. Zoek de taal waarin je het geheel
wilt vertalen en onthoud de code van de taal.
<LI>Blijf in de setup directory (of ga er naar terug ;-)). Hier vind je een aantal 
taal-bestanden die al beschikbaar zijn. U kunt deze herkennen aan de bestandsnaam welke
de volgende structuur heeft "lang_??.sql", waar "??" staat voor de taal-code. 
Waarschijnlijk bestaat er nog geen bestand met de taal-code die je nu wilt gaan maken
(waarom zou je immers dan nog gaan vertalen?). Kopieer dit bestand nu en geef het de naam
met de juiste landcode. Kopieer altijd het engelse bestand, omdat dit altijd het meest 
recent is.
<LI>Open dit bestand en vertaal de zinnen, iedere regel start met een SQL commando, kom hier 
niet aan. Het enige wat je moet wijzigen is het laatste deel, wat tussen quotes staat,
tussen haakjes en de landcode in het midden.
<LI>Indien je hiermee klaar bent, dan moet je dit even duidelijk maken aan phpVideoPro.
Start phpVideoPro en ga naar het configuratie menu ("*admin# -&gt; *configuration#"), 
vink het vakje "*scan_new_lang_files#" aan en klik op de "*update#" knop. Een aantal 
seconden later zal in het menu de taal beschikbaar moeten zijn bij de optie
"*select_add_lang#".
<LI>Selecteer de taal die je wilt installeren en klik nogmaals op "*update#", hierna is het 
mogelijk om deze taal als primaire taal te selecteren en je bent klaar!
</OL>

[title]
De zinnen zinnen mij niet...

[text]
Als de vertaling je niet aanstaat, dan mag je uiteraard het taal-bestand wijzigen.
Dit kan er alleen voor zorgen dat er bij updates van de software problemen ontstaan,
waardoor je de wijzigingen dan opnieuw moet maken. Na het aanbrengen van de wijzigingen
moet je het bestand weer laden in phpVideoPro. Selecteer de taal in het 
<A HREF="{PHP_SELF}?topic=configuration">configuratie menu</A> en het "*refresh_lang#" 
aankruisvakje en klik op "*update#". Op dat moment worden de zinnen van die taal 
verwijderd en de nieuwe geladen.
[eof]
