# /* configure */
# /* $Id$ */

[title]
Introduksjon

[text]
P† denne skjermen kan du sette overordnede konfigurerings opsjoner for
phpVideoPro, slik som spr†k spesifike opsjoner, farge valg, etc.

[title]
*language_settings#

[text]
<b>*scan_new_lang_files#:</b> For † administrere installerte spr†k benytter
phpVideoPro sin database. S† for † legge til et nytt spr†k m† man oppdatere
denne. Dette gj°res ved † benytte SQL filer som jeg for enkelthets skyld vil
betegne som 'spr†kfiler' for enkelthets skyld. En ny spr†kfil m† bli lagt inn
i systemet, som blir gjort ved † krysse av i denne boksen (samt aktivering av
opsjonen selvf°lgelig :). Se "Installasjon av spr†k" nedenfor, samt 
"<A HREF="{PHP_SELF}?topic=howto_lang">*howto_lang#</A>" for detaljer.

[text]
<b>*select_add_lang#:</b> Du kan selvf°lgelig kun installere tilgjengelige
spr†k - phpVideoPro tilh°rer ikke kategorien av kunstig intelligens programmer
og kan ikke lage et nytt spr†k p† sparket :) For † oppdatere eksisterende spr†k,
se neste punkt.

[text]
<b>*refresh_lang#:</b> Dersom du har en ny spr†k fil for et spr†k du allerede
har installert, som inneholder oppdaterte og nye fraser, trenger du en m†te †
erstatte de eksisterende frasene. Dette er f.eks. tilfelle n†r du oppgraderer
fra en tidligere versjon av phpVideoPro. For det spr†ket du velger her vil alle
frasene bli sletet fra databasen, og den nye spr†kfilen vil bli importert. I
framtiden er det mulig at jeg vil legge til en funksjon for kun a legge til nye
fraser, og ikke slette noe fra databasen, men dette er ikke implementert enda.

[text]
<b>*select_primary_lang#:</b> Du kan velge ditt foretrukkede spr†k blandt de
installerte spr†kene. Dersom ditt morsm†l er tilgjengelig vil du sikkert velge
dette :) Alle fraser som manger blir erstattet med engelske fraser. Dersom ogs†
den engelske frasen mangler vil du se en "debug frase" vist, og du kan gjette
meningen ut fra dette. Dersom dette skjer og du er sikker p† at det ikke er din
feil (ved at du f.eks. har manuelt fjernet de engelske frasene fra databasen ;) -
vil det vµre fint om du kan gi <A HREF="mailto:izzysoft@qumran.org">meg</a>
beskjed om dette, og referer til den manglende frasen og hvor feilen har oppst†tt.

[text]
<b>*use_charset#</b>: da dette p†virker hele utseende av skjermen, b°r du kun
modifisere dette dersom du vet hva du gj°r. Til gjengjeld kan du ikke gj°re noe
skade ved dette - du vil kun gj°re teksten litt merkelig dersom du velger en rar
opsjon, og data lagret i databasen under bruk av en ukorrekt opsjon kan ha effekt
over lang tid.<br>
Men dersom du laget en ny spr†kfil som inneholder spesielle bokstaver, kan du
benytte denne opsjonen til † vise dem korrekt. Da jeg ikke har benyttet dette er
jeg interesert i † f† vite om resultene.

[title]
*colors#

[text]
<b>*page_bg# / *table_bg# / *th_bg#:</b> Disse opsjonene blir lagt inn i malene,
og navnene forklarer seg selv.

[text]
<b>*feedback_ok# / *feedback_err#:</b> Disse opsjonene blir ikke lagt inn i noen
maler. De er brukt n†r systemet ber om svar fra brukeren, f.eks. utsagn som
"Elementet ble opprettet." ved opprettelse av et nytt element i databasen, eller
"Feil &lt;feilbeskrivelse&gt;" n†r noe g†r galt, for † forsterke meldingene i
kontrast til den vanlige informasjonen.

[text]
<b>*template_set#:</b> fra v0.1.5, er phpVideoPro basert p† maler.
Jeg (utvikleren) har laget en mal; man s† snart andre maler er tilgjelgelig
(som kun vil skje n†r <b>DU</b> lager dem - jeg er ikke god til design), kan du
gj°re dine valg her.

[eof]

