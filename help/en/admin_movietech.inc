<? /* administration of categories */ ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
This screen is to edit technical data available for movies, such as "*screen#",
"*picture#", "*mediatype#" and "*tone#". You can add your own specifications
here as well as modify existing ones or delete unneeded types.

[title]
Edit existing entries

[text]
To edit an existing entry, simply click on the edit icon for the corresponding
entry. This will lead you to a screen that lets you edit its values. Feel free
to rename/change the value provided for the "*name#". The "sname" you should
leave untouched: first, this value was used to evaluate certain capabilities
with older versions of phpVideoPro, and I'm not sure whether I removed all
references to that in the code - and second it will be needed on importing data
from a different installation to determine e.g. the media type, since the ID
might be different depending on the order of addition to the DB.

[title]
Adding a new entry

[text]
Just click on "*add_entry#" at the bottom of the table you want to add an entry
to. This will lead you to the same screen as the edit above - but the difference
is that a new entry will be created. For new entries, the warning regarding
"*sname#" above does not apply. But you should use a sname you thing others
would chose as well (e.g. "mDV" for the "mini DV tapes" of camcorders), for the
same above mentioned reasons.

[title]
Deleting an entry

[text]
To delete an entry, for each entry there's a trashcan icon available. If you
click on this, you will next have to confirm the delete. However, if there are
still movies refering to this special technical data field, phpVideoPro will
not allow the deletion to take place; instead, a warning is displayed to you
informing you about details. This is to prevent you from accidental deletions;
I hope it's effective enough ;)

[eof]
