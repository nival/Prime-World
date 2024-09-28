# -*- coding: utf-8 -*-
import sys
sys.path.append('../common/py')
sys.path.append('../..')

import Network

from logging import debug, info, error, warning

from string import Template
import tornado.web

template = '''
var nival = window.nival || {};
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
nival.tracking_key = '${nv_key}';

$(document).ready(sendVisit('${nv_ms}', nival.tracking_key, function(){}, window.partner, window.subid));
'''

class KeyHandler(tornado.web.RequestHandler):

    def initialize(self, config, service):
        self.config = config
        self.service = service

    @tornado.web.asynchronous
    def get(self):
        key = self.get_cookie(self.config.tracking.key_name)
        if key:
            self.service.OnReturn(self, key) 
        else:
            self.service.CreateMuid(self)

    def Fail(self, code, error):
        self.finish()

    def _Finish(self, key):
        ip = self.request.headers.get("X-Real-IP", "")
        self.service.OnPageView(key, ip)
        args = {
            'nv_ms' : self.config.tracking.host,
            'nv_key' : key,
        }
        self.finish(Template(template).safe_substitute(args))

    def Finish(self, result):
        key = result['muid']
        if result.get('new', True):
            self.set_cookie(self.config.tracking.key_name, key, expires_days=365*10)
        self._Finish(key)

class EventHandler(tornado.web.RequestHandler):

    def initialize(self, config, service):
        self.config = config
        self.service = service

    @tornado.web.asynchronous
    def get(self):
        muid = self.get_argument('muid')
        partner = self.get_argument('partner')
        program = self.get_argument('program', None)
        puid = self.get_argument('puid', None)
        subid = self.get_argument('subid', None)
        request = Network.Web.Request(self, 'link', False, False)
        self.service.LinkPartner(request, muid, partner, program, puid, subid)
