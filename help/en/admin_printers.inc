<? /* administration of categories */
 ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
This page behaves much like the "*admin_cats#" screen - of course except the
fact you're editing <b><i>printers</i></b> here and not categories :-) To
remove a printer, simply empty its name and submit the form. To update values
for a printer, edit them and submit. To add a new printer, use the empty row
at the end of the table.

[title]
What is a Offset?

[text]
Not all printers share the same "printable area" on paper sheets: some may be
able to print everywhere on the sheet, others may require some space for the
"feed" (paper transport) they can't print on. And this space is not necessarily
of the same size for each printer available. If you found out none of the
printer definitions in the list match your printer: find the closest one, get a
ruler, measure the differences, calculate the correct offsets, and add a new
printer here (or modify an existing printer you won't ever need).

[title]
Units

[text]
There are different measurement units to be found in the "*units#" column, you
may not be familiar with each of them: so here's a short explanation plus
comparision for all of them:
<TABLE ALIGN="center" BORDER="1" WIDTH="95%" STYLE="margin:5">
  <TR><TH CLASS="help">Unit</TH><TH CLASS="help">Comparision</TH><TH CLASS="help">Description</TH></TR>
  <TR><TD>pt</TD><TD>&nbsp;</TD><TD>"Point" is the smallest unit for PostScript</TD></TR>
  <TR><TD>inch</TD><TD>72 pt</TD><TD>Old Imperial measuring unit</TD></TR>
  <TR><TD>mm</TD><TD>2.83465 pt</TD><TD>Millimeter is the smalles metric unit used here (smaller ones make no sense in our context)</TD></TR>
  <TR><TD>cm</TD><TD>28.346 pt</TD><TD>The same as 10 mm. Ask Michael whether PostScript only supports 4 digits after the comma (or better use mm for more accuracy ;)</TD></TR>
</TABLE>

[title]
A last word...

[text]
If you added/modified printer(s) these values may be overwritten on an update,
or be lost on a new installation, so let me point you to two things:
<ol>
 <li>make a backup (you may use phpVideoPro's backup function for this)</li>
 <li>send me the modified data so I may include it with future versions of
     phpVideoPro. This way you can be sure they are available when you're
     updating or making a fresh installation next time :-)</li>
</ol>

[eof]

