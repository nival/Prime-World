import urllib2
import urllib
import base64
import time
import json

address = 'http://127.0.0.1:90/ch'
progress = 5.0
counter = 0
while True:
   # 
    command = ''
    if progress <= 0.0:
        command = 'PRIVMSG #global :Hi %d!' % counter
        progress = 6.0
        counter += 1
    data = {
        'auid' : '666',
        'key' : 12345,
        'action' : 'ping',
    }
    if command:
        data['chat'] = base64.b64encode(command)
        print '*** OUT:'+repr(json.dumps(data))

    request = '?'+urllib.urlencode(data)
    urlRequest = urllib2.Request( address+request )
    response = urllib2.urlopen( urlRequest )        
    headers = response.info()
    responseData = response.read()
    if responseData:
        data = json.loads(responseData)
        if 'chat' in data['response']:
            text = base64.b64decode(data['response']['chat'])
            if text: 
                print text

    time.sleep(2)
    progress -= 2
