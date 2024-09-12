function ajax_test() {
  var ids = new Array();
  $("input[name=chkService]:checked").each(
    function() {
      ids.push($(this).val());
  });
}

function group_action(cmd) {
  $('#mainForm').attr('action', "/Service/GroupCommand/" + cmd);
  $('#mainForm').submit();
}