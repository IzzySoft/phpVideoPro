<? /* administration of categories */
 ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
This screen helps you to manage the user accounts. These are needed to protect
your data against unauthorized access, whereby &quot;access&quot; can have
different meanings: you may forbid users to manipulate your data, or even to
view them.

[title]
How phpVideoPro makes use of accounts

[text]
By default, phpVideoPro uses the <i>guest</i> account. For this fallback to
work, you should neither delete this account, nor protect it with a password.
If you want to exclude guests as well, just withdraw all privileges. A good
idea, and most suitable setting for the <i>guest</i> account, is to grant him
the browse status only. But of course this depends on your needs and your idea
on the usage of phpVideoPro.

[text]
As long as the user has not logged in, the guest account is used. Provided the
above recommended settings, (s)he must not add or update entries. So as soon
as such a feature is requested by the user (e.g. by pushing the edit button),
instead of reaching the requested page, the browser gets relocated to the login
page: to use features not granted to the guest user, a login is required.
Furthermore, certain menue items (e.g. the administration menue) are hidden as
long as the logged-in user lacks the appropriate privileges.

[title]
Settings

[text]
Some settings may be directly modified on this page, and you can do so by
(un)checking the available checkboxes and pushing the *update# button:
[text]
<table align='center' border='1'>
 <tr><td><b>*read_access_short#</b></td>
     <td>wether the user should be able to browse your data. This includes
         lists and records as well as labels.</td></tr>
 <tr><td><b>*add_access_short#</b></td>
     <td>wether the user may <b><i>add new</i></b> entries. This privilege
         does not allow her/him to modify existing entries.</td></tr>
 <tr><td><b>*upd_access_short#</b></td>
     <td>wether the user may update existing entries. Does not provide the
         ability to add new ones.</td></tr>
 <tr><td><b>*del_access_short#</b></td>
     <td>wether the user should be able to delete records.</td></tr>
 <tr><td><b>*admin_access_short#</b></td>
     <td>wether the user may access administrative pages. Giving this
         privilege to an account, the user may give his own account any
	 privilege (s)he wants, may create/drop/modify other accounts
	 and change all your default configuration. So be careful with this!</td></tr>
</table>

[text]
Links are provided to add new users or modify their accounts.

[eof]

