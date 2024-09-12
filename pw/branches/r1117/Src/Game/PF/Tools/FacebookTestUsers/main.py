import urllib2
import json
import sys

def getApplicationToken(appId, appSecret):
    request = 'SITE' % (appId, appSecret)
    print request
    try:
        urlRequest = urllib2.Request( request, None, headers={"Accept-Encoding":"gzip"} )
        response = urllib2.urlopen( urlRequest )        
        headers = response.info()   
        responseData = response.read()
        tokens = responseData.split('=')
        return tokens[1]
    except urllib2.URLError:
        return None

appId = 'appId'
appSecret = 'appSecret'

appToken = getApplicationToken(appId, appSecret)

if appToken:
    print 'Token: %r' % appToken
else:
    print 'Application token not recieved'
    sys.exit(1)

names = []
options = []

for arg in sys.argv[1:]:
    if arg.startswith('--'):
        options.append(arg)
    else:
        names.append(arg)

print 'Names:', names
print 'Options:', options

for name in names:
    request = 'SITE' % (appId, name.replace(' ', '%20'), appToken)
    print request
    if '--debug' in options:
        continue
    urlRequest = urllib2.Request( request, None, headers={"Accept-Encoding":"gzip"} )
    response = urllib2.urlopen( urlRequest )        
    headers = response.info()
    responseData = response.read()

    data = json.loads(responseData)

    print json.dumps(data, indent=4)
