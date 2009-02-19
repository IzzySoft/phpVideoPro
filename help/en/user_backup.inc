# /* absolute taperest */
# /* $Id$ */

[title]
Backup and Restore of your own movie data

[text]
There is not much to do on this page, since it only displays the results of the
executed action. But if there comes an error, you may want to know what you can
do.

[text]
Probably nothing.

[text]
But the admin may be able to resolve your problem, so let that person know.
Nevertheless, here are a few hints to help you out:

[text]
<UL>
 <LI><b><i>*user_backup_store#</i></b> failed: Either the disk is full, or the
     backup directory is write protected. These are the most likely reasons,
     though there may be others.</LI>
 <LI><b><i>*user_backup_download#</i></b> failed: Oi gevalt! I cannot think of
     any reason at the moment. This probably needs deeper investigation.</LI>
 <LI><b><i>*user_backup_restore#</i></b> failed: Are you sure you previously
     created a backup? If there is none, or the file is empty, there is nothing
     to restore from.</LI>
</UL>

[text]
This list is all but complete - there could as well be other reasons for an error.
If neither you nor the admin can resolve this issue, you may have to open a ticket
on the <A HREF="{pvp->projectpage}" TARGET="_blank">project site</A> - or try to
find help in our IRC channel (#izzysoft on FreeNode).

[text]
One last remark: While your restore will always run from your most recent backup,
the admin may have access to the previous ones. Just in case.

[eof]

