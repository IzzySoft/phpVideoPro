<? /* How to create a new template set */
 ?>
<? /* $Id$ */ ?>

<H2 Align=Center>How to create a new template set</H2>

<Table Width=90% Align=Center>
 <TR><TD>
  <P Align=Justify>As with the help and language files, this is again
   just an act of creating some subdir and copying/editing or creating
   files:</P>
  <OL>
   <LI>guess a good name for the new template set you are going to create.
       To have an example to explain, let's call it "babylon5" here :)
   <LI>go to the templates dir and create a directory with that name.
       For our example, it would be "templates/babylon5".
   <LI>copy the files from "templates/default" to this new directory,
       and then modify them as you want. The tokens in {brazes} are
       place holders for the data to be parsed into the templates, so
       these should appear in your new templates for sure :-) Everything
       else can be removed/replaced as you like.
   <LI>Now that you are done with the creation, you may want to go to the
       configuration page (Edit -&gt; Configuration) and activate it:
       phpVideoPro finds out about the installed template sets by parsing
       the templates directory for existing sub directories, so your new
       template set will be found automagically.
 </TD></TR>
</Table>

