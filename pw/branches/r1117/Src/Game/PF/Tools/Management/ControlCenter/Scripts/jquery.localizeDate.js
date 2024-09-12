var GLOBAL_TIMEZONE = 3;
//var GLOBAL_TIMEZONE = -new Date().getTimezoneOffset() / 60;

function stringToUtcTicks(string) {
  var utcTicks = Date.UTC(string.substring(6, 10), string.substring(3, 5) - 1, string.substring(0, 2),
    string.substring(11, 13), string.substring(14, 16), string.substring(17, 19));
  return utcTicks;
}
function getGlobalTicksOffcet() {
  return GLOBAL_TIMEZONE * 3600000;
}
function utcToLocal(u) {
  var utcTicks = stringToUtcTicks(u);
  utcTicks += (new Date).getTimezoneOffset() * 60000 + getGlobalTicksOffcet(); // NUM_TASK: Все даты приводим к московской таймзоне
  var d = new Date(utcTicks);
  var st = wZ(d.getDate()) + '.' + wZ(d.getMonth() + 1) + '.' + d.getFullYear() + ' ' + wZ(d.getHours()) + ':' + wZ(d.getMinutes()) + ':' + wZ(d.getSeconds());
  return st;
}
function wZ(x) { if (x <= 9) return '0' + x; return x; }
function localizeDate() {
  // NUM_TASK: Все даты приводим к глобальной таймзоне
  $(".timeZoneLabel").each(function() {
    var text = $(this).html().replace("utc+0", "utc+" + GLOBAL_TIMEZONE).replace("UTC+0", "UTC+" + GLOBAL_TIMEZONE);
    $(this).html(text);
  });
  $(".utcdateVal").each(function() {
    if ($(this).val()) $(this).attr('value', utcToLocal($(this).val()));
    else if ($(this).text()) $(this).text(utcToLocal($(this).text()));
  });
  $(".utcdateText").each(function() {
    if ($(this).text()) if ($(this).text().length > 9) $(this).html(utcToLocal($(this).text().trim()));
  });
  $('#TimeZone').val(GLOBAL_TIMEZONE);
};