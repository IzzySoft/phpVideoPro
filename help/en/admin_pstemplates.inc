<? /* list of actors, directors, composers */ ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
This is to edit the settings for the PS Label Templates. You do not edit the
templates themselves here, but you are to administrate their settings. This
includes the following items:
<UL>
 <LI>what label packs/templates are available</LI>
 <LI>what type (e.g. side labels for VHS types or top labels) do they belong to</LI>
 <LI>what image file is to use</LI>
 <LI>what is the dimension (i.e. size) of this label</LI>
 <LI>what control file (i.e. template file) describes the label</LI>
</UL>

[title|1|packlist]
Label Packs

[text]
The PSLabels are organized in so called Label Packs. This makes it easy for the
user to only install the labels (s)he needs and wants. If someone does not use
VHS video tapes, it makes no sense to install them - just leave this package
out, to tell one example.

[text]
This module makes it possible to install, edit and remove label packs. The
introductionary (first) page lists up all PSLabel Packs installed and, after
clicking on the "*check_update#" link, also those available and not yet
installed. The icons displayed along lead you to additional information on the
pack, to the list of templates contained (which you may edit then, see <A
HREF="#templates">below</A>), plus to the action window, where you can download,
install or remove PSLabel packs (see <A HREF="{PHP_SELF}?topic=admin_psinstall">here</A>).

[title|1|templates]
The template list

[text]
The work on managing the templates is split into two parts: first you are
presented with a list of available labels with the usual controls to walk
through the collection. To your convinience this list is sorted by the labels
name. Here you may decide to add a new label, to edit or to delete an existing
one. Just use the links provided for this tasks. But remember that your changes
will be lost once you removed the complete label pack. The main reason of this
managment/editing capabilities is to help you solve simple problems such as
positioning yourself, in case they occur - and then send a detailed report to
the author for fixes.

[title]
The editor

[text]
This is the place to edit a label. You reach this either via one of the "*edit#"
links next to the items displayed in the above mentioned list (in this case you
are about to edit an already existing label), or via the "*add_entry#" link
provided in the table header (which means you are adding a new one).

[text]
The items to edit should be quite self-explaining: The "<b>*pstpl_name#</b>" has
no technical relevance at all, you can name an entry as you like. Important are
the other items:
[text]
<table align="center" style="border:1px solid #000000;margin:5" width="95%">
 <tr><td><b>*pstpl_type#:</b></td>
     <td>defines in which list the label appears and what kind of label sheets
         it fits on</td></tr>
 <tr><td><b>*graphic_file#:</b></td>
     <td>what image file is used as background for this label</td></tr>
 <tr><td><b>*template_file#:</b></td>
     <td>what PS template file describes the structure of this template (e.g.
         if and where the media number is printed, and what other details
	 appear on this label)</td></tr>
 <tr><td><b>*lower_left_corner#:</b></td>
     <td>the coordinates of the lower left corner on this templates. Usually it
         starts at the very beginning, i.e. x=0 and y=0</td></tr>
 <tr><td><b>*upper_right_corner#:</b></td>
     <td>coordinates of the upper right corner, i.e. the distance from the
         lower left corner in points.</td></tr>
</table>

[text]
If you wonder about these measures: PostScript starts the pages bottom-up, so
"0x0" is the lowest left point of a page (or frame).

[text]
Once you are done, hit the "*update#" button at the end of the form. Normally,
the form should be re-displayed and give you some information on the success of
your operation - as you may already know this from editing movie entries.

[eof]
