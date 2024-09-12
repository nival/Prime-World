# -*- coding: utf-8 -*-

import sys
sys.path.append('../common/py')

import Network.Web.sandbox
import System.logs
import json
import base64

System.logs.setup(None, 'debug')

se = Network.Web.sandbox.Caller('http://192.168.2.126:10000', 'method')

messages = [
    {
        'type' : 'JoinRequest',
        'field0' : 'value0',
    },
]
se.send_nl(sender='roll', recipient=7777, project='pw', _data=json.dumps(messages))

#login0 = se.login(auid=5555, project='pw', url='http://192.168.1.172:8080', force=1)
#login1 = se.login(auid=7777, project='pw', url='http://192.168.1.172:8080', force=1)

#messages = [
#    {
#        'type' : 'JoinRequest',
#        'field0' : 'value0',
#    },
#]
#se.send(sid=login0.login.sid, recipient=7777, project='pw', _data=json.dumps(messages))
#
#se.logout(sid=login0.login.sid)
#se.logout(sid=login1.login.sid)


'''
N = 2
for i in range(N):
    login = se.login(auid=i, project='pw')#
    for j in range(i+1, N):
        if login.login.ec == 0:
            messages = [
                {
                    'type' : 'Message',
                    'body' : base64.b64encode('Test %dx%d'% (i, j)),
                },
                {
                    'type' : 'JoinRequest',
                    'field0' : 'value0',
                },
            ]
            se.send(sid=login.login.sid, recipient=j, postdata=json.dumps(messages))
    se.logout(sid=login.login.sid)
'''