<? /* administration of categories */
 ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
Different disk types support different features (or quirks), so here we can
define what is supported by which. Technically, this works like the management
of categories (see <A HREF="{PHP_SELF}?topic=admin_cats">there</A>): you can
edit entries simply using the form elements, add a new disk type using the last
row, and deleting elements by just emptying the respective name field.

[title]
Deleting a disk type

[text]
This is done very simple, but the results may be unwanted and somehow
"irreversible" - so be careful with this:
[text]
When you decide to delete a disk type, all disks that have this type set are
re-set to "unknown"; right now there's no check and no warning. The disk type
is then removed. Well, let me use the "common disclaimer" at this place again:
you should always have an up-to-date backup handy :-)

[title]
Updates

[text]
One remaining risk is, as with the categories, translations and whatever
technical data you may have edited, that with the next update of phpVideoPro
you might get lost of the changed/added data. As for disk types, this is very
unlikely - but although I'ld recommend you to send me the added data if you
feel I missed to add them. This way they may be included with the next release.

[eof]

