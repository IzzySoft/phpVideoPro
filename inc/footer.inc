<? /* page footer */
 if ( file_exists($pvp->tpl_dir . "/foot.js") )
   echo "\n<script type='text/javascript' language='JavaScript' src='". str_replace($base_path,$base_url,$pvp->tpl_dir) . "/foot.js'></script>\n";
?>
</BODY></HTML>