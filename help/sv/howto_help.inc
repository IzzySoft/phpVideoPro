# /* How to create a help file */
# /* $Id$ */

[title]
Hur generar jag mina egna hjälpsidor?

[text]
Det är tillochmed enklare än skapandet av en ny språkfil -
speciellt efter
ändringarna som gjordes i v0.2 när hjälpsidorna började drivas av mallar.
Nu behöver du inte ens kunna HTML - du behöver bara ändra en enkel
textfil som <b>kan</b> innehålla lite makro/HTML-kod, men behöver inte det:
[text]
<OL>
 <LI>gå till hjälp-katalogen, öppna help_topics.php med din
     favorit-viewer för text (än en gång, detta är ren text). Strukturen
     på denna fil är självförklarande: 
     en rad börjar med "headline" som markerar en headline, ett ämne
     börjar med "li". Den första saken inom måsvingar är hjälp-rubriken.
     Titta efter namnet på rubriken du vill skapa en hjälpfil för.
 <LI>Om det inte finns en enda hjälpfil tillgängligt för ditt språk än,
     får du lov att skapa den korrekta katalogen för ditt språk först.
     Hitta språkkoden för ditt språk (se
     "<A HREF="{PHP_SELF}?topic=howto_lang">*howto_lang#</A>" på hur man
gör detta), och skapa katalogen med namnet på språkkoden nedan
     hjälpkatalogen - t.ex. "help/fi" för finska.
 <LI>Nu: antingen skapa en ny fil med namnet <topic>.inc i din språk-
     katalog (e.g. "help/fi/about.inc" för det finska "About"-ämnet), eller
     kopiera det från det engelska trädet (help/en) som en mall.
 <LI>Öppna din nya hjälpfil ("help/fi/about.inc" i ovanstående exempel) med
     med din favorit-editor och översätt/skapa hjälprubriken. Formatet på
     en sådan fil förklaras nedan.
 <LI>Det är allt - du är klar! phpVideoPro kommer automatiskt hitta och använda
     hjälpfilen till det definierade förstahandsspråket först. Oroa dig inte om du
     saknar <b>vissa</b> hjälpfiler för ditt språk: om phpVideoPro
     inte kan hitta en hjälpfil i ditt förstahandsspråk, visas den
     engelska som standard.
  </OL>

[title]
Filformat
[text]
Det generella formatet som används för hjälpfilerna är väldigt enkelt: varje rad startar
med en brädgård ("#") som tolkas som kommentar (t.ex. ett som helt ignoreras). Den första raden
tolken börjar med måste vara en rad som innehåller enbart [title] 
tagg (inledande/avslutande blanktecken ignoreras). Tolken stannar på [eof]-
taggen och sen (och bara sen) skickas hjälpfilen till webbläsaren. Den tredje
taggen som är ett måste är [text]-taggen. Taggar <b>måste</b> placeras på separata
rader för att identifieras (än en gång, inledande/avslutande blanktecken ignoreras)!<br>So
sen då, vad menas?
[text]
<ul>
 <li><b>[title]</b> markerar en headline. Allt som följer denna tagg (upp till 
     nästa tagg, som i de flesta fall [text]) ses som en headline för
     det följande ([text]) blocket.
 <li><b>[text]</b> startar ett till textblock - här är all information med
     detaljer. För att uppnå flera "paragrafer", bara starta flera [text]-
     block en efter en.
 <li><b>[eof]</b> betyder "End Of File" och säger till tolken att nu verkligen
     generera utdatan. Den säger också till den att det inte är av något mer
     intresse för honom :)
</ul>
[text]
Du kan använda HTML-formateringskod som t.ex. för att understryka fraser med 
&lt;B&gt;bold&lt;/B&gt; markeringar, generera listor med &lt;UL&gt;, placera ut tabeller,
grafik, etc. Jag förklarar inte hur man gör det - det finns bättre manualer
tillgängliga inom detta ämne. Än en gång, du <b>måste</b> inte använda detta, men du
<b>kan</b>.

[title]
Makron

[text]
Det finns några makron tillgängliga i hjälpfilerna. De kan delas in i två kategorier:
variabler och översättare. Om du är en aning mer van vid PHP (och tillochmed koden för phpVideoPro),
så borde du vilja använda dessa.
[text]
Allting som sätts därimellan {måsvingar} ersätts med global
variabel med sitt namn (om det är tillgängligt). Denna variabel måste t.ex. INTE innehålla några
blanksteg, etc. (se PHP-manualen för detta).
[text]
Allt som är i tysk BTX-stil insatt mellan en *asterisk och en #brädgårds-
markering (än en gång, inga blanksteg!) indikerar till tolken att det måste översättas
genom att använda the fraserna definierade av språkfilerna. Självklart så följer den reglerna av phpVideoPros översättningssystem.

[eof]
