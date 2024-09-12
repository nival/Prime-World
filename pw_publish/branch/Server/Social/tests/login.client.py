# -*- coding: utf-8 -*-

import socket, ssl, pprint, time, sys
import hashlib
import urllib, urllib2
import random
import unittest

sys.path.append('../base')
from helpers import makeSignedRequest, makeParamsSignature, checkParamsSignature, json_loads, toint

def md5( code ):
    return hashlib.md5( str(code) ).hexdigest()

CERT_PATH = "ssl_ca/"

#~ print "toint(True)=%s, toint('True')=%s, toint('1')=%s" % (toint(True), toint('True'), toint('1'))

#~ print "hex ts:", hex(1332400209)
#~ print "time:", time.ctime( 1332400209 )
#~ exit(0)

# -------------------------------

SERVER_ADDR = '127.0.0.1'
#~ SERVER_ADDR = 'pw.nivalnetwork.com'
#~ SERVER_ADDR = 'pw.zzima.com'

HTTP_PORT = 88
#~ HTTP_PORT = 99

SERVER_HTTP_ADDR = '%s:%d' % (SERVER_ADDR, HTTP_PORT)

AUID = 6
SNUID = '100006274567752'
SNTOKEN = 'CAAB9M8ptmXMBANOYDgZBcod3kYduE3R4Y8ZByix6WiOEevpVvhObWIAJbhdipQwtONad91T1YmWXyErbdUSYIjvky8iPjthk92w7x0F12D1FqwcDICeUJxKQMGZCFsHvsZCva1ahrqlNuHCK4BZBwxsF1IOOCDQwBZBZCqDRx1JaasMXD8gMQDKTBrfVZB9eVLwZD'
CHALLENGE = ''

#~ SNUID = '100000234693443'
#~ SNTOKEN = 'AAAB9M8ptmXMBAPQhex9USB08I5kg6ZAXPHCVZCkhygGZAYh4RJtHnd6zwIhRk0EDpqWvDlAfX19qw8nSD0XV8qz5BxesgSbDSd06KKZCMQZDZD'


# ----------------------------------------------------------------

def who( snid='fb', snuid=SNUID, sntoken=SNTOKEN, server='', secret='', locale='ru' ):
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

    global SERVER
    global CHALLENGE
    global AUID
    reply_json = json_loads( reply ).get("response")
    SERVER = reply_json.get("server")
    CHALLENGE = reply_json.get("token")

    linfo = reply_json.get("info") or {}
    AUID = toint( linfo.get("auid") )

    return reply_json

# -------------------------------------------------------------
def sn_login( snid="pw", snuid=AUID, sntoken=CHALLENGE, server='', secret='', key='' ):
    params = dict(
        action = "sn_login",
        snid = snid,
        snuid = snuid,
        sntoken = sntoken,
        key = key,
        ver = "0.0.0",
    )
    req = urllib.urlencode(params)
    if snid == 'pw':
        req = makeSignedRequest( params, secret=secret )

    request = "http://%s/%s?%s" % (SERVER_HTTP_ADDR, server, req)
    print "\nsn_login request:", request
    reply = urllib2.urlopen( request ).read()
    print "sn_login reply:", reply

    reply_json = json_loads(reply).get('response')

    global UID
    global KEY
    UID = reply_json.get("uid")
    KEY = reply_json.get("key")

    return reply_json


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


## --------------------------------------------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------------------------------------------
class MainTest(unittest.TestCase):
    def test_login_smoke(self):
        # -------------------------------------------------------------
        # who/sn_login
        reply = who( server="one" )
        assert( reply.get('ok', -1) == 1 )

        reply = sn_login( snuid=AUID, server="one", sntoken=CHALLENGE )
        assert( reply.get('ok', -1) == 1 )

        UID1 = reply.get("uid")
        KEY1 = reply.get("key")

        # -------------------------------------------------------------
        time.sleep( 1.0 )

        # -------------------------------------------------------------
        # who на второй сервер:
        reply = who( server="two" )
        assert( reply.get('ok', -1) == 1 )

        # -------------------------------------------------------------
        # login на второй сервер (redirect):
        ##reply = sn_login( snid='fb', snuid=SNUID, server="two", sntoken=SNTOKEN )
        reply = sn_login( snuid=AUID, server="two", sntoken=CHALLENGE, key=KEY1 )
        #~~ assert( reply.get('ok', -1) == 1 )
        KEY2 = reply.get("key")

        assert( reply.get('ok', -1) == 1 )

        # -------------------------------------------------------------
        reply = logout( uid=UID1, key=KEY2, server="one" )
        assert( reply.get('ec', 0) == 4 )

        # -------------------------------------------------------------
        # и повторный логин на первый сервер (должно, наконец, пофейлиться)
        reply = sn_login(snuid=AUID, server="one", sntoken=CHALLENGE, key=KEY2 )
        KEY3 = reply.get("key")
        assert( reply.get('ec', 0) == 203 )

        # -------------------------------------------------------------
        reply = logout( uid=UID1, key=KEY3, server="one" )
        assert( reply.get('ec', 0) == 4 )

        reply = logout( uid=UID1, key=KEY2, server="two" )
        assert( reply.get('ok', -1) == 1  or reply.get('ec', 0) == 1 )

    def test_pop_login_smoke(self):
        # -------------------------------------------------------------
        # who/sn_login
        reply = who( server="one" )
        assert( reply.get('ok', -1) == 1 )

        reply = sn_login(snuid=AUID, server="one", sntoken=CHALLENGE )
        assert( reply.get('ok', -1) == 1 )

        UID1 = reply.get("uid")
        KEY1 = reply.get("key")

        # -------------------------------------------------------------
        time.sleep( 1.0 )

        # -------------------------------------------------------------
        # who на второй сервер:
        reply = who( server="one" )
        assert( reply.get('ok', -1) == 1 )

        # -------------------------------------------------------------
        # login на второй сервер (redirect):
        ##reply = sn_login( snid='fb', snuid=SNUID, server="two", sntoken=SNTOKEN )
        reply = sn_login(snuid=AUID, server="one", sntoken=CHALLENGE, key=KEY1 )
        #~~ assert( reply.get('ok', -1) == 1 )
        KEY2 = reply.get("key")

        assert( reply.get('ok', -1) == 1 )

        # who на второй сервер:
        reply = who( server="one" )
        assert( reply.get('ok', -1) == 1 )

        # -------------------------------------------------------------
        # и повторный логин на первый сервер (должно, наконец, пофейлиться)
        reply = sn_login( snuid=AUID, server="one", sntoken=CHALLENGE )
        KEY3 = reply.get("key")
        UID3 = reply.get("uid")
        assert( reply.get('ok', -1) == 1 )

        # -------------------------------------------------------------
        reply = logout( uid=UID3, key=KEY3, server="one" )
        assert( reply.get('ok', -1) == 1  or reply.get('ec', 0) == 1 )


unittest.main()