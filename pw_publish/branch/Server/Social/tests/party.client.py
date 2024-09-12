# -*- coding: utf-8 -*-

import socket, ssl, pprint, time, sys
import hashlib
import urllib2
import random

sys.path.append('../base')
from helpers import makeSignedRequest, makeParamsSignature, checkParamsSignature, json_loads, toint, pretty

def md5( code ):
    return hashlib.md5( str(code) ).hexdigest()

CERT_PATH = "ssl_ca/"

# -------------------------------

SERVER_ADDR = '127.0.0.1'
#~ SERVER_ADDR = 'pw.nivalnetwork.com'
#~ SERVER_ADDR = 'pw.zzima.com'

HTTP_PORT = 88
#~ HTTP_PORT = 99

SERVER_HTTP_ADDR = '%s:%d' % (SERVER_ADDR, HTTP_PORT)

AUID1 = 0
SNUID1 = '100000234693443'
SNTOKEN1 = 'AAAB9M8ptmXMBAPQhex9USB08I5kg6ZAXPHCVZCkhygGZAYh4RJtHnd6zwIhRk0EDpqWvDlAfX19qw8nSD0XV8qz5BxesgSbDSd06KKZCMQZDZD'
CHALLENGE1 = ''

AUID2 = 0
SNUID2 = '100003297559974'
SNTOKEN2 = 'AAAB9M8ptmXMBAKLjZBe9ViZATa3j0miIp0BkIZA11325znpxQXQ9hdZAy1CnvZB3wgik1G2cqZCV9HzZBqiKJuZCqwUGZAZCD8LvYdZBRDWPBr2ZAgZDZD'
CHALLENGE2 = ''

# ----------------------------------------------------------------

def who( snid='fb', snuid='', sntoken='', server='', secret='', locale='ru' ):
    params = dict( 
        action = "l_who",
        snid = snid,
        snuid = snuid,
        sntoken = sntoken, 
        locale = locale,
        ver = "0.0.0",
    )

    req = makeSignedRequest( params, secret=secret )
    request = "http://%s/%s?%s" % (SERVER_HTTP_ADDR, server, req)
    print "\nwho request:", request

    reply = urllib2.urlopen( request ).read()
    print "who reply:", reply

    reply_json = json_loads( reply ).get("response")
    server = reply_json.get("server")
    challenge = reply_json.get("token")
    auid = toint( linfo.get("auid") )
    
    return reply_json, server, challenge, auid

# -------------------------------------------------------------
def sn_login( snid="pw", snuid='AUID', sntoken='CHALLENGE', server='', secret='', key='' ):
    params = dict( 
        action = "sn_login",
        snid = snid,
        snuid = snuid,
        sntoken = sntoken,
        key = key,
        ver = "0.0.0",
    )

    req = makeSignedRequest( params, secret=secret )
    request = "http://%s/%s?%s" % (SERVER_HTTP_ADDR, server, req)
    print "\nsn_login request:", request
    reply = urllib2.urlopen( request ).read()
    print "sn_login reply:", reply
    
    reply_json = json_loads(reply).get('response')
    
    uid = reply_json.get("uid")
    key = reply_json.get("key")
    server = reply_json.get("server")
    
    return reply_json, uid, key, server


# -------------------------------------------------------------
def logout( uid=0, server='', secret='', key='' ):
    params = dict( 
        action = "logout",
        uid = uid,
        key = key,
        pretty = 1,
    )

    req = makeSignedRequest( params, secret="" ) 
    request = "http://%s/%s?%s" % (SERVER_HTTP_ADDR, server, req)
    print "\nlogout request:", request
    reply = json_loads( urllib2.urlopen( request ).read() ).get("response", {})
    print "logout reply:", reply
    return reply


# -------------------------------------------------------------
def action( action, uid=0, server='', key='', secret='', **moreargs ):
    params = dict( 
        action = action,
        uid = uid,
        key = key,
        pretty = 1,
    )
    params.update( moreargs )

    req = makeSignedRequest( params, secret=secret ) 
    request = "http://%s/%s?%s" % (SERVER_HTTP_ADDR, server, req)
    print "\n%r action request:" % action, request
    reply = json_loads( urllib2.urlopen( request ).read() ).get("response", {})
    print "%r action reply:" % action, pretty(reply)
    return reply


## --------------------------------------------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------------------------------------------


# -------------------------------------------------------------
reply, UID1, KEY1, SERVER1 = sn_login( snid='fb', snuid=SNUID1, sntoken=SNTOKEN1 )
AUID1 = toint( reply.get("auid") )

reply, UID2, KEY2, SERVER2 = sn_login( snid='fb', snuid=SNUID2, sntoken=SNTOKEN2 )
AUID2 = toint( reply.get("auid") )

time.sleep(3.0) 

try:
    
    # -------------------------------------------------------------
    # PARTY INVITE
    reply = action( "party_invite", uid=UID1, key=KEY1, server=SERVER1, invite_auid=AUID2 )

    # немного поспим, пока инвайт дойдет до адресата
    time.sleep(3.0) 

    # -------------------------------------------------------------
    # PARTY INVITE OK?
    reply = action( "keepalive", uid=UID1, key=KEY1, server=SERVER1 )

    # -------------------------------------------------------------
    # PARTY ACCEPT
    #reply = action( "keepalive", uid=UID2, key=KEY2, server=SERVER2 )

    # -------------------------------------------------------------
    # а теперь релогинимся (на последующий keepalive должен прийти непустой PartyData)
    reply, UID1, KEY1, SERVER1 = sn_login( snid='fb', snuid=SNUID1, sntoken=SNTOKEN1, server=SERVER1, key=KEY1 )
    
    # немного поспим, пока пройдет повторный subscribe
    time.sleep(2.0) 
    reply = action( "keepalive", uid=UID1, key=KEY1, server=SERVER1 )
    
except:
    pass
    
# -------------------------------------------------------------
reply = logout( uid=UID1, key=KEY1, server=SERVER1 )
reply = logout( uid=UID2, key=KEY2, server=SERVER2 )


