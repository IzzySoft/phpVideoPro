// nicEdit for edit_entry

var MyNic;
function loadEditor() {
  MyNic = new nicEditor({buttonList : ['bold','italic','underline','left','center','justify','right','ol','ul','subscript','superscript','strikethrough','indent','outdent','hr','forecolor','bgcolor','removeformat','fontFormat','fontFamily','fontSize']}).panelInstance('comment');
}
bkLib.onDomLoaded(function() {
  if (document.movieform.useEditor[0].checked) loadEditor();
});
function changeEditor() {
  if (document.movieform.useEditor[1].checked) { MyNic.nicInstances[0].saveContent(); MyNic.removeInstance('comment'); }
  else { loadEditor(); }
}
