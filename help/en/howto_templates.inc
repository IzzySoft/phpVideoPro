# /* How to create a new template set */
# /* $Id$ */

[title]
How can I design my own template set?

[text]
As with the help and language files, this is again just an act of creating some
subdir and copying/editing or creating files:
[text]
<OL>
 <LI>guess a good name for the new template set you are going to create. To
     have an example to explain, let's call it "babylon5" here :)
 <LI>go to the templates dir and create a directory with that name. For our
     example, it would be "<code>templates/babylon5</code>".
 <LI>copy the files from "<code>templates/default</code>" to this new directory,
     and then modify them as you want. The tokens in &#123;brazes&#125; are
     place holders for the data to be parsed into the templates, so these
     should appear in your new templates for sure :-) Everything else can be
     removed/replaced as you like.
 <LI>Now that you are done with the creation, you may want to go to the
     configuration page ("*edit# -&gt; *configuration#") and activate it:
     phpVideoPro finds out about the installed template sets by parsing the
     templates directory for existing sub directories, so your new template set
     will be found automagically.
</OL>

[text]
If your new template set needs some JavaScript code to be present for all pages,
there are two special files that can be used: if there's a file called
<code>top.js</code> present in the templates directory, it will be linked into
the page header. A file named <code>foot.js</code> in the same place will be
linked to the end of each page.

[eof]
