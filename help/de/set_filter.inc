<? /* set_filter */
 ?>
<? /* $Id$ */ ?>

<Table Width=90% Align=Center>
 <TR><TD>
  <P Align=Justify>Beide Menüpunkte - "<?=lang("set_filter")?>" wie auch
   "<?=lang("unset_filter")?>" - führen zum selben Formular, mit nur einem
   kleinen (wenn auch signifikanten) Unterschied: "<?=lang("unset_filter")?>"
   löscht zuvor alle gesetzten Filter, sodaß problemlos mit der Erstellung
   eines neuen Regelsets begonnen werden kann - ohne zuerst auf bestehende
   Regeln prüfen zu müssen.</P>
  <H3>Filterregeln</H3>
  <H4>in einer gemeinsamen Zelle gruppierte Filter</H4>
  <OL>
   <li><b>Filter mit min/max Werten</b><br>
       Diese werden mit UND verknüpft; gibt man also "min 60" und "max 90"
       für die Länge an, bedeutet dies: alle Filme mit 60-90 Minuten Länge.
       Wird nur einer der beiden Werte angegeben, findet natürlich auch nur
       dieser Berücksichtigung.
   <li><b>Titel</b><br>
       Ein beliebiger Teil des gewünschten Titels kann hier eingegeben
       werden; der Begriff "Mission" würde hier also sowohl auf den Film
       "James Bond: In tödlicher Mission" wie auch auf "Mission Impossible"
       zutreffen.
   <li><b>andere Filter</b><br>
       Alle anderen Filter werden mittels ODER verbunden; wird also z.B.
       als MedienTyp sowohl DVD als auch OVT aktiviert, heißt dies: sowohl
       DVDs als auch Originalbänder (wenn mir jemand ein Medium bringt,
       welches zugleich DVD und VHS-Tape ist, muß ich diese Regel nochmals
       überdenken :-)
  </OL>
  <H4>Verknüpfung der einzelnen Regeln</H4>
  <P Align=Justify>Die einzelnen Filterregeln werden nun wieder mit UND
   verbunden: "DVD" als Medientyp und "Science Fiction" als Kategorie
   resultiert daher in allen DVDs, welche Science Fiction Filme enthalten.</P>
 </TD></TR>
</Table>

