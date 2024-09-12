import sys
sys.path.append('../common/py')
sys.path.append('../../base')

import helpers 

import hashlib

def md5(s):
    m = hashlib.md5()
    m.update(s)
    return m.hexdigest()

import unittest
import Network.Web.sandbox
import System.logs

from logging import debug

import time

url = 'http://localhost:88'
#url = 'http://pw.nivalnetwork.com:88'

class Test_QueueLogin(unittest.TestCase):

    def test_Ping(self):
        login = Network.Web.sandbox.Caller(url, 'action')                  
        login.SetPage('login')

        login.l_ping(auid=1123, token='aaa')

    def test_OnlyWho(self):
        login = Network.Web.sandbox.Caller(url, 'action')                  
        login.SetPage('login')

        login.l_ping(auid=1123, token='aaa')

        ws = Network.Web.sandbox.Caller(url, 'action')                  

        headers = {'X-Real-Ip' : '173.194.32.135' }
        acc = login.l_who(hostid='0d6093c8be33fff9a18a34da2f52a8b82508a392', ver='0.12.208.24449', locale='ru', muid='hh5kj', ruid='hh5kj', snid='fb', snuid='100000204558976', sntoken='CAAB9M8ptmXMBANBLMrZB6wzwgNa2eHZAXDpLn8dnz3FOvpyEykfIP7SN4ZANTr7k6QlUyupAXvZBkV7ZBJYIDlIgBNq3TXi3ArLSAZBJxR2ZBB15cfzZA8G5NjkAFBHzvDr4togy3VwBo1BlQH2B2Y3kvwFyuyj8qnBHvVyuKTzZCEONejMhAyta6KITfMIZBLvdYZD', primary=1, _headers=headers)

        login.SetPage(acc.response.server)
        lg = login.qlogin(snid='pw', sntoken=acc.response.token, snuid=acc.response.info.auid)

        user = None
        while True:
            if lg and lg.response.get('gserver'):
                ws.SetPage(lg.response.gserver)
                user = ws.sn_login(snid='pw', sntoken=lg.response.token, snuid=acc.response.info.auid)
                break
            else:
                lg = login.qpoll(sntoken=acc.response.token, snuid=acc.response.info.auid)

        if user:    
            ws.logout(uid=user.response.get('uid'), key=user.response.get('key'))


    def test_Simple(self):
        login = Network.Web.sandbox.Caller(url, 'action')                  
        login.SetPage('login')

        login.l_ping(auid=1123, token='aaa')

        ws = Network.Web.sandbox.Caller(url, 'action')                  

        acc = login.l_who(hostid='0d6093c8be33fff9a18a34da2f52a8b82508a392', ver='0.12.208.24449', locale='ru', muid='hh5kj', ruid='hh5kj', snid='fb', snuid='100000204558976', sntoken='CAAB9M8ptmXMBANBLMrZB6wzwgNa2eHZAXDpLn8dnz3FOvpyEykfIP7SN4ZANTr7k6QlUyupAXvZBkV7ZBJYIDlIgBNq3TXi3ArLSAZBJxR2ZBB15cfzZA8G5NjkAFBHzvDr4togy3VwBo1BlQH2B2Y3kvwFyuyj8qnBHvVyuKTzZCEONejMhAyta6KITfMIZBLvdYZD', primary=1)

        login.SetPage(acc.response.server)
        lg = login.qlogin(snid='pw', sntoken=acc.response.token, snuid=acc.response.info.auid)

        while True:
            if lg and lg.response.get('gserver'):
                ws.SetPage(lg.response.gserver)
                ws.sn_login(snid='pw', sntoken=lg.response.token, snuid=acc.response.info.auid)
                break
            else:
                lg = login.qpoll(sntoken=acc.response.token, snuid=acc.response.info.auid)

    def test_Join(self):
        login = Network.Web.sandbox.Caller(url, 'action')                  
        login.SetPage('login')


        acc0 = login.l_who(hostid='0d6093c8be33fff9a18a34da2f52a8b82508a392', ver='0.12.208.24449', locale='ru', muid='hh5kj', ruid='hh5kj', snid='fb', snuid='100000204558976', sntoken='CAAB9M8ptmXMBANBLMrZB6wzwgNa2eHZAXDpLn8dnz3FOvpyEykfIP7SN4ZANTr7k6QlUyupAXvZBkV7ZBJYIDlIgBNq3TXi3ArLSAZBJxR2ZBB15cfzZA8G5NjkAFBHzvDr4togy3VwBo1BlQH2B2Y3kvwFyuyj8qnBHvVyuKTzZCEONejMhAyta6KITfMIZBLvdYZD', primary=1)
        class SignCallback:

            def __init__(self, secret):
                self.secret = secret

            def __call__(self, args):
                return 'sign', helpers.makeParamsSignature(args, self.secret)

        login.SetPage(acc0.response.server)

        pwc = Network.Web.sandbox.Caller('http://localhost:8710', 'action')                  
#        pwc.SetPage('pwc')

        pwc.pwc_register(email='test555@mail.ru', pwd='95012e6c2ad8158a33b47d55e2402fd8', gender=1, birthdate=-81561600, locale='ru', hostid='0d6093c8be33fff9a18a34da2f52a8b82508a392', muid='1mzhg', ruid='1mzhg')


#        acc1 = login.l_who(hostid='0d6093c8be33fff9a18a34da2f52a8b82508a392', ver='0.12.208.24449', locale='ru', muid='hh5kj', ruid='hh5kj', snid='pwe', snuid='9694b9b44eba4282e8326bb5111fb219', primary=0, __sign=SignCallback(md5('1234')))
#        secret = md5('100000204558976') + md5(acc1.response.pwc_snuid)
#        login.l_merge(auid0=acc0.response.info.auid, token0=acc0.response.token, auid1=acc1.response.info.auid, token1=acc1.response.token, __sign=SignCallback(secret))

    def test_ITStatus(self):
        login = Network.Web.sandbox.Caller(url, action=None, json=False)                  
        login.SetPage('login')
        
        login._post_('<?xml version="1.0" encoding="UTF-8"?><OverallRegistrationInfoIn/>')
        login._post_('<?xml version="1.0" encoding="UTF-8"?><OnlineInfoIn/>')


System.logs.setup(None, 'debug')
unittest.main()

