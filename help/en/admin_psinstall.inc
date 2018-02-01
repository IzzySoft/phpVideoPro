<? /* PSLabelPack (de-)installation and (de)registration */ ?>
<? /* $Id$ */ ?>

[title]
*intro#

[text]
This page allows you several actions concerning the selected PSLabel pack. Which
actions are available, depends on your installation and configuration. Some
actions may not be available - these are not linked but grayed. So if you
wonder about these - that is the reason.

[title|1|installation]
Installation

[text]
Depending on your configuration, you may have up to 3 choices concerning the
installation:
<ul>
 <li>Download the archive: This will always be available</li>
 <li><A HREF="#autoinstall">Download and install</A>: Depends on your configuration</li>
 <li><A HREF="#manualinstall">Install</A>: Only available if you already downloaded and unpacked the archive</li>
</ul>

[title|2|autoinstall]
Automatic installation

[text]
This is the most convenient way for the user, since with a single click the
entire action of download, unpack and register can be performed. However, this
requires the installation directory (the <code>pslabels/</code> directory in
your phpVideoPro installation) to be writable by the webserver (otherwise the
files cannot be installed there). If that is fine for you, you may do so. If
you see any security risk with this, you still have the option of manually
downloading the archive and unpack it into the <code>pslabels/</code> directory,
and return to this page for the <A HREF="#manualinstall">registration</A> with
the database.

[title|2|manualinstall]
Manual installation

[text]
If your installation directory is not writable for the web server (see <A
HREF="#autoinstall">above</A>), you have to manually download the archive,
and extract it to the <code>pslabels/</code> directory. Once the files are
located there, you can use the "*psinst_query_inst#" link to register them with
the database and such make them usable by the application.

[title|1|remove]
Remove a PSLabel Pack

[text]
The other two links are provided to unregister/remove an installed PSLabel Pack.
Again you can go the most user-friendly way of auto-uninstall only if your
<code>pslabels/</code> directory is writable by the web server. If that is not
the case, you must manually remove the files in the end. Do not worry: The
application will tell you which files you have to remove.

[eof]
