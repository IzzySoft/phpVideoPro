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
Fields

[text]
<b>*mediatype#:</b>
[text]
Each media type can have multiple disk types, i.e. a VideoCD can be either
VCD or SVCD, and (re-)writable CDs/DVDs can have different capacities. Use this
select box to define the *mediatype# you want to specify the *disk_type# for.
[text]
<b>*name#:</b>
[text]
You are free to decide by what name you want to refer to this disk type, so
name it as you like. The "*name#" field is mandatory.
[text]
<b>*disk_size#:</b>
[text]
This is the capacity of the medium. The value to fill in here is optional and
for now just used as information represented to you, so you could fill in any
string you like. Recommended is something like a size in MB/GB, as you can see
with the disk types already defined.
[text]
<b>*longplay# / *region_code#:</b>
[text]
These checkboxes are to define whether the mentioned feature/quirk applies to
the specified disk type.

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

