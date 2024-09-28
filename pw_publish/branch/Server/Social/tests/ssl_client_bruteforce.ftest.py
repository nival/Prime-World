# -*- coding: utf-8 -*-

import socket, ssl, pprint, time, sys
import hashlib
import urllib2
import random

sys.path.append('../base')
from helpers import makeSignedRequest, makeParamsSignature, checkParamsSignature, json_loads, toint
import CC
def md5( code ):
    return hashlib.md5( str(code) ).hexdigest()

CERT_PATH = "ssl_ca/"

#~ print "toint(True)=%s, toint('True')=%s, toint('1')=%s" % (toint(True), toint('True'), toint('1'))

#~ print "hex ts:", hex(1332400209)
#~ print "time:", time.ctime( 1333308548 )
#~ exit(0)

# -------------------------------

PWC_SERVER = 'pwc'

SERVER_ADDR = '127.0.0.1'
#~ SERVER_ADDR = 'pw.nivalnetwork.com'
#~ SERVER_ADDR = 'pw.zzima.com'

SSL_PORT = 888
HTTP_PORT = 88
#~ SSL_PORT = 999
#~ HTTP_PORT = 99

SERVER_HTTP_ADDR = '%s:%d' % (SERVER_ADDR, HTTP_PORT)
SERVER_SSL_ADDR = '%s:%d' % (SERVER_ADDR, SSL_PORT)

# -------------------------------

##EMAIL = "danvorobiev25674@list.ru"
#EMAIL_UNICODE = u"DanVorobiev11242314543@list.ru"
EMAIL_UNICODE = u"dev_registration_dk_bf4@nivalnetwork.com"
#CHANGE_EMAIL = "danvorobiev@list.ru"

#~ EMAIL = "clarice@mail.ru"
#~ GENDER = 2 # девочка
#~ #PWD = "1234554321"
#~ PWD = "d2ec46fe"
#~ BIRTHDATE = toint( time.mktime( time.strptime("1 Jan 1985", "%d %b %Y") ) )

#~ EMAIL = "niv.all001@ya.ru"
#~ GENDER = 1 # мальчик
#~ PWD = "1234554321"
#~ BIRTHDATE = toint( time.mktime( time.strptime("1 Feb 1984", "%d %b %Y") ) )

#EMAIL_UNICODE = unicode("ДанилаВоробьев@list.ru", "cp1251")
#EMAIL_UNICODE = u"yauheni.ivanou@gmail.com"
#EMAIL_UNICODE = u"danvorobiev@list.ru"
#EMAIL_UNICODE = u"l7bEPO@gmail.com"
#EMAIL_UNICODE = u"olga.mis@gmail.com"
EMAIL_UTF8 = EMAIL_UNICODE.lower().encode("utf8")

CHANGE_EMAIL_UNICODE = u"dev_registration_dk_des4@nivalnetwork.com"
#CHANGE_EMAIL_UNICODE = u"225580980@mail.ru"
CHANGE_EMAIL_UTF8 = CHANGE_EMAIL_UNICODE.encode("utf8")

GENDER = 1 # мальчик
PWD = "123456"
BAD_PWD = "654321"

BIRTHDATE = toint( time.mktime( time.strptime("10 Apr 1976", "%d %b %Y") ) )

#EMAIL = "danvorobiev%d@list.ru" % ( random.randint(1,1000000) )
#CHANGE_EMAIL = "danvorobiev%d@list.ru" % ( random.randint(1,1000000) )

EMAIL_MD5 = md5( EMAIL_UTF8 )
PWD_MD5 = md5(PWD)
BAD_PWD_MD5 = md5( BAD_PWD )
CHANGE_EMAIL_MD5 = md5( CHANGE_EMAIL_UTF8 )

#NEW_PWD = '12345'
NEW_PWD = "1234554321"
NEW_PWD_MD5 = md5( NEW_PWD )

PWC_SNUID = 0

# -------------------------------

def ssl_fetch(request):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # require a certificate from the server
    ssl_sock = ssl.wrap_socket( s,
                                ca_certs = CERT_PATH + "ca.crt",
                                certfile = CERT_PATH + "client01.crt",
                                keyfile = CERT_PATH + "client01.key", 
                                ## certfile = CERT_PATH + "clientBad.crt",
                                ##keyfile = CERT_PATH + "clientBad.key",
                                cert_reqs = ssl.CERT_REQUIRED,
                               )

    ssl_sock.connect((SERVER_ADDR, SSL_PORT))

    ##print "peername:", repr(ssl_sock.getpeername())
    ##print "cipher:", ssl_sock.cipher()
    ##print "cert:", pprint.pformat(ssl_sock.getpeercert())

    # Set a simple HTTP request -- use httplib in actual code.
    ssl_sock.write("""GET %s HTTP/1.0\r
    Host: xxx.xx.xx\r\n\r\n""" % request)

    # Read a chunk of data.  Will not necessarily
    # read all the data returned by the server.
    data = ssl_sock.read()
    ##print "server reply:", data

    # note that closing the SSLSocket will also close the underlying socket
    ssl_sock.close()
    
    return data


# ---------------------------------------------------------------------------------------------------------------------
# по SSL нам отдают неформатированный HTTP reply buffer, со всеми заголовками; давайте ручками достанем body, что ли
def http_body( data ):
    BODY_STRING = "\r\n\r\n"
    pos_body = data.find(BODY_STRING)
    if pos_body >= 0:
        body_start = pos_body+len(BODY_STRING)
        return data[body_start:]
    return ""



def who( secret=PWD_MD5, snuid=EMAIL_MD5 ):
    params = dict( 
        action = "l_who",
        snid = "pwe",
        snuid = snuid,
        ver = "0.0.0",
    )

    req = makeSignedRequest( params, secret=secret )
    request = "http://%s/login?%s" % (SERVER_HTTP_ADDR, req)
    print "\nwho request:", request

    data = urllib2.urlopen( request ).read() #ssl_fetch( request )
    #print "who reply:", data
    reply_json = data #http_body( data )

    #reply_json = urllib2.urlopen( request ).read()
    print "who reply:", reply_json

    global SERVER
    global CHALLENGE
    global AUID
    global PWC_SNUID
    reply = json_loads( reply_json ).get("response")
    SERVER = reply.get("server")
    CHALLENGE = reply.get("token")
    AUID = toint( reply.get("auid") )
    PWC_SNUID = reply.get("pwc_snuid") or PWC_SNUID 
    
    return reply

# -------------------------------------------------------------

def sn_login( secret=PWD_MD5 ):
    params = dict( 
        action = "sn_login",
        snid = "pw",
        snuid = AUID,
        sntoken = CHALLENGE,
        ver = "0.0.0",
    )

    req = makeSignedRequest( params, secret=secret )
    request = "http://%s/%s?%s" % (SERVER_HTTP_ADDR, SERVER, req)
    print "\npwc_login request:", request
    reply = urllib2.urlopen( request ).read()
    print "pwc_login reply:", reply
    
    parsed_reply = json_loads(reply)
    
    return req, parsed_reply.get("response")


## --------------------------------------------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------------------------------------------

params = dict( 
    action = "pwc_register",
    email = EMAIL_UTF8,
    pwd = PWD_MD5,
    gender = GENDER,
    birthdate = BIRTHDATE,
    pretty = 1,
)

req = makeSignedRequest( params, secret=PWD_MD5 )
request = "/%s?%s" % (PWC_SERVER, req)
print "pwc_register request:",request
data = ssl_fetch( request )
reply_json = http_body( data )
print "pwc_register reply:", reply_json

response = json_loads(reply_json).get("response")
PWC_SNUID = toint( response.get("pwc_snuid", 0) )

params2 = params.copy()
sign = makeParamsSignature( params2, secret=PWD_MD5 )
params2["sign"] = sign
checkParamsSignature( params2, secret=PWD_MD5 )
# -------------------------------------------------------------
# -------------------------------------------------------------
print who( md5("123456"))
#for i in list(it)[:CC.TRY_LOGINS_COUNT * 2]:
TRY_LOGINS_COUNT = 10
for i in xrange( TRY_LOGINS_COUNT * 2):
    #print "password:", "".join(i)
    reply = who( md5("654321"))
    print reply.get('ok', -1)

