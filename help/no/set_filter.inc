# /* set_filter */
# /* $Id$ */

[title]
Introduksjon

[text]
Begge meny valgene, "*set_filter#" samt "*unset_filter#" framviser samme
skjerm - med n liten forskjell: "*unset_filter#" vil slette alle filter
settinger f°rst, s du kan starte p nytt.

[title]
Filter regler

[text]
<H4>Valg som er samlet i tabellen</H4>
<OL>
 <li><b>valg som inneholder min/max verdier</b><br>
     Disse valgene er logisk koblet sammen som OG, slik at dersom du
     f.eks. skriver "Min 60" og "Max 90" for lengde feltene, betyr dette
     alle filmer som er mellom 60 og 90 minutter. Dersom kun n er spesifisert
     vil self°lgelig kun dette bli vurdert.
 <li><b>tittel</b><br>
     Her kan du skrive inn en <i>del-tekst</i> som titlene du °nsker  framvise
     skal inneholde; ved  skrive inn "hard" vil du finne bde Beetles 
     "A hard days night" samt "Die hard"
 <li><b>andre verdier</b><br>
     alle andre verdier er logisk koblet sammen som ELLER, f.eks. vil det at
     boksen RVT og OVT for MediaType resulterer i at alle kassetter, uansett
     om de er kj°pte eller egene opptak.
</OL>

[text]
<H4>Kombinering av tabell valg</H4>
De enkelte tabell elementene er koblet sammen med den logiske operasjonen OG.
Ved  velge "DVD" som MediaType samt "Science Fiction" som kategori velger man
dermed alle DVD filmer med filmer av typen "Science Fiction".

[eof]

