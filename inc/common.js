// JavaScript functions used on all pages
function open_help(topic) {
  if (topic!='') { help_topic = '?topic=' + topic; } else { help_topic = ''; }
  url = '<?=$base_url?>help/index.php' + help_topic;
  var pos = (screen.width/2)-400;
  campus=eval("window.open(url,'<?=lang("help")?>','toolbar=no,location=no,titlebar=no,directories=no,status=yes,resizable=no,scrollbars=yes,copyhistory=no,width=800,height=600,top=0,left=" + pos + "')");
}
function get_movienum(mtype,last_nr,url) {
  nr = last_nr + 1;
  new_nr = prompt(mtype + "\n" + "<?=lang("last_medianr")?> " + last_nr,nr);
  window.location.href = url + "&cass_id=" + new_nr;
}
