<? /* $Id$ */ ?>

[title]
*intro#

[text]
This screen lists up all sessions registered with phpVideoPro and allows you
certain ways of manipulation - right now this is only to delete sessions
according to certain criteria.

[text]
If you delete a session, it will no longer be valid. If the user running this
session is still logged in, deleting his session requires him to re-login; this
may be very awful if he e.g. just entered a lot of data and is going to submit
them - he needs to re-enter everything unsaved after the login, so be careful
with this.

[title]
Deleting ended sessions

[text]
You can hurt noone by this, because it affects only old sessions where the
user already has logged off - but it may be required from time to time to
clean up your database if you do not use the automatic session purge feature
(just to bring it back into your mind: on the <A HREF="{PHP_SELF}?topic=configuration">configuration</A>
screen you can set up phpVideoPro to automatically purge invalid sessions from
the database).

[title]
Deleting older sessions

[text]
If you enabled the automatic purge function mentioned above not only those
sessions where the user logged off are removed, but as well those older than
the specified limit. So if you are using that automatic purge function, you
probably never need to use this manual purge function here.

[title]
Cancelling a single session

[text]
By using the "*delete#" link next to a specific session you are able to cancel
it without affecting other sessions.

[eof]

