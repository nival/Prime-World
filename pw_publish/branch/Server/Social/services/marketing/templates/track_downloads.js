var nival = nival || {};

nival.domLoaded = function (callback) {
    /* Internet Explorer */
    /*@cc_on
    @if (@_win32 || @_win64)
        document.write('<script id="ieScriptLoad" defer src="//:"><\/script>');
        document.getElementById('ieScriptLoad').onreadystatechange = function() {
            if (this.readyState == 'complete') {
                callback();
            }
        };
    @end @*/
    /* Mozilla, Chrome, Opera */
    if (document.addEventListener) {
        document.addEventListener('DOMContentLoaded', callback, false);
    }
    /* Safari, iCab, Konqueror */
    else if (/KHTML|WebKit|iCab/i.test(navigator.userAgent)) {
        var DOMLoadTimer = setInterval(function () {
            if (/loaded|complete/i.test(document.readyState)) {
                callback();
                clearInterval(DOMLoadTimer);
            }
        }, 10);
    }
    /* Other web browsers */
    else { window.onload = callback; }
};

nival.domLoaded(function() {
  if (!nival.tracking_key) { return; }
  
  var locale = window.location.host.split('.')[0];
  var installer_addr_locale = window.installer_addr['default'];
  if (window.installer_addr[locale]) {
    installer_addr_locale = window.installer_addr[locale];
  }
  
  var links = document.getElementsByTagName('a'),
      i, j, url, notify_tracker, ifr;
  for (i=0, j=links.length; i<j; i++) {
    url = links[i].getAttribute('href');
    if (in_array(url, window.old_installer_addr)) {
      url = installer_addr_locale + nival.tracking_key;
      links[i].setAttribute('href', url);
    }
  }
});