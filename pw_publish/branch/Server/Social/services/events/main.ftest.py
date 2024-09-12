import urllib2
import time
import socket
import urllib
import json

url = 'http://localhost:10007/pw/logs'

params = {
    'host' : socket.gethostname(),
    'sid' : 'sid',
    'pid' : 0,
    'skipped' : 0
}

messages = [
    {
        'msg' : 'Test message',
        'tm' : time.time(),
        'type' : 'message',
        'channel' : 'root',
        'file' : 'test.py',
        'line' : 45,
    }
]

for i in range(10000):
    print i    
    params['pid'] = i
    if i % 2 == 0:
        s = '2'
    else:
        s = ''
    furl = url+s+'?'+urllib.urlencode(params)
    request = urllib2.Request(furl, data=json.dumps(messages, indent=4))  
    reply_body = urllib2.urlopen(request).read()
    time.sleep(0.005)

'''
import tornado.ioloop
import tornado.web
import tornadoredis

def OnMsg(res):
    pass

rclient = tornadoredis.Client(host='localhost', port=6379, selected_db=1)
pipe = rclient.pipeline()
pipe.llen('logs'+'_q')
pipe.execute(OnMsg)
tornado.ioloop.IOLoop.instance().start()
'''                
    