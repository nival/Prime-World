import urllib2
import base64
import hashlib
import urllib
import httplib

headers = {
    "Content-Type": "application/x-www-form-urlencoded",
    "Accept": "text/xml", 
}
api_key = 'api_key' 
api_secret = 'api_secret'
game_user = 'user_id'
method = 'users.getInfo,'+game_user+',1,1'
format = 'xml'    

_data = [
    ('api_key', api_key),
    ('game_user', game_user),
    ('method', method),
    ('format', format),
]
data = []
requestString = ''
for paramName, paramValue in _data:
    requestString += paramName+'='+base64.b64encode(paramValue)
    data.append( (paramName, base64.b64encode(paramValue)) )
    
    
sigStr = requestString+api_secret    
sig = hashlib.md5()
sig.update(sigStr)                
data.append( ('sig', sig.hexdigest()) )

params = urllib.urlencode(data)

req = urllib2.Request("http://SITE/zzimaApi", params, headers)
f = urllib2.urlopen(req)
print f.read()