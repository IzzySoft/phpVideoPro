# /* How to create a new template set */
# /* $Id$ */

[title]
Hvordan kan jeg lage mine egene maler?

[text]
Som med hjelpe og sprk filer, er dette igjen kun et sp°rsml om  opprette
en underkatalog og kopiere/redigere filer: 
[text]
<OL>
 <LI>finn et velegnet navn for den nye malen du °nsker  lage. For 
     ha et godt eksempel for  illustrere dette velger vi navnet "babylon5" :)
 <LI>finn mal katalogen (templates/) og opprett en katalog med dette navnet.
     I vrt eksempel vil det bli "templates/babylon5"
 <LI>kopier filene fra "templates/default" til denne katalogen, og modifiser
     dem slik du °nsker det. De delene som er i &#123;kr°ll-paranteser&#125; er
     stedfortredere for den data som blir parset inn i malene, s disse skal
     helt sikkert komme fram i dine nye maler :-) Alt annet kan bli fjernet/erstattet
     som du °nsker.
 <LI>N som du er ferdig med  opprette malene, °nsker du gjerne  pne
     konfigurasjons siden (Edit -&gt; Configuration) og aktiver den: phpVideoPro
     oppdager den installerte mal settet ved  analysere mal katalogen for eksisterende 

     finds out about the installed template sets by parsing the templates
     directory for existing sub directories, so your new template set will be
     found automagically.
</OL>

[eof]

