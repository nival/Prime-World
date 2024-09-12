# -*- coding: utf-8 -*-

import socket, ssl, pprint, time, sys, os
import hashlib
import urllib2
import random
import logging

os.chdir('..')
sys.path.append('.')

from base.helpers import *

from friendsdata.FriendsData import FriendsData
from party.PartyData import PartyData
from modeldata.ModelData import ModelData

from modeldata.change_applicator import ModelChangeApplicator

import EC
import MM

def md5( code ):
    return hashlib.md5( str(code) ).hexdigest()

# -------------------------------

X_ANY_SERVER = 'se'
X_SERVER1 = 'ein'
X_SERVER2 = 'zwei'

ANY_WS = ''

SERVER_ADDR = '127.0.0.1'
#~ SERVER_ADDR = 'pw.nivalnetwork.com'
#~ SERVER_ADDR = 'pw.zzima.com'

HTTP_PORT = 88
X_HTTP_PORT = 8888

SERVER_HTTP_ADDR = '%s:%d' % (SERVER_ADDR, HTTP_PORT)
X_SERVER_HTTP_ADDR = '%s:%d' % (SERVER_ADDR, X_HTTP_PORT)

HTTP_TIMEOUT = 20.0

## --------------------------------------------------------------------------------------------------------------------------

def get( method, server=X_ANY_SERVER, **kwargs ):
    params = dict( **kwargs )
    params["method"] = method
    req = makeSignedRequest( params )

    request = "http://%s/%s?%s" % (X_SERVER_HTTP_ADDR, server, req)
    info( "\n%s request: %s" % (method, request) )

    reply = urllib2.urlopen( request, None, HTTP_TIMEOUT ).read() # 
    parsed_reply = json_loads(reply)
    
    info( "%s parsed reply: %s" % (method, pretty(parsed_reply)) )
    return parsed_reply.get("response")

## --------------------------------------------------------------------------------------------------------------------------

def post( method, body="", server=X_ANY_SERVER, **kwargs ):
    params = dict( **kwargs )
    params["method"] = method
    req = makeSignedRequest( params )

    url = "http://%s/%s?%s" % (X_SERVER_HTTP_ADDR, server, req)
    headers = { "Accept-Encoding": "text/plain" }
    info( "\n%s url: %s, \nheaders: %s, \nbody: %s" % (method, url, headers, body) )
    request = urllib2.Request(url, body, headers)

    reply = urllib2.urlopen( request, body, HTTP_TIMEOUT ).read()
    info( "%s reply: %s" % (method, reply) )
    
    parsed_reply = json_loads(reply)
    return parsed_reply.get("response")

## --------------------------------------------------------------------------------------------------------------------------

def ws_get( action, http_addr=SERVER_HTTP_ADDR, server=ANY_WS, **kwargs ):
    params = dict( **kwargs )
    params["action"] = action
    req = makeSignedRequest( params )

    request = "http://%s/%s?%s" % (http_addr, server, req)
    info( "\n%s request: %s" % (action, request) )

    reply = urllib2.urlopen( request, None, HTTP_TIMEOUT ).read() # 
    parsed_reply = json_loads(reply)
    
    info( "%s parsed reply: %s" % (action, pretty(parsed_reply)) )
    return parsed_reply.get("response")
    
## --------------------------------------------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------------------------------------------

def feedSortedMessages( model, messages ):
    try:
        # ????????? ????? ????????????? ?? ???? ?????????
        sorted_messages = []
        for msg_id, msg in messages.iteritems():
            msg_dict = msg
            dt_rcv = toint( msg_dict.get("dt_rcv") )
            sorted_messages.append( (msg_id, dt_rcv, msg_dict) )
            
        def GetDate(item):
            return item[1]
        sorted_messages.sort( key=GetDate )
            
        #.. ? ???????? ??????????? ModelData
        #~ for msg_id, dt_rcv, msg_dict in sorted_messages:
            #~ model.onSocialExchangeMail( msg_id, msg_dict )
    except:
        catch()

def feedSortedMessagesToNewModel( messages ):
    from modeldata.ModelDataCustom import ModelDataCustom
    model = ModelDataCustom()
    feedSortedMessages( model, messages )

def getFriend( acc, friend_auid):
    return acc.friendsdata.FriendsKeeper.get(friend_auid)
    
def prettyFriend( acc, friend_auid ):
    return pretty( getFriend(acc, friend_auid).generateJsonDict() )
    
def wsGetModelChanges( AUID, **kwargs ):
    acc = accs[AUID]
    
def logLevel( level=None ):
    if not level:
        level = DEFAULT_LOG_LEVEL
    logger = logging.getLogger()
    logger.setLevel( level )
    
## --------------------------------------------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------------------------------------------

def test_redirect():
    AUID1 = 3
    AUID2 = 2
    
    # -----------------------------------------
    reply = get( "login", project="pw", auid=AUID1, server=X_SERVER1 )
    assert( reply.get('ok', -1) == 1 )
    SID1 = reply.get('sid')
    SERVER1 = reply.get('server')

    # -----------------------------------------
    reply = get( "login", project="pw", auid=AUID2, server=X_SERVER2 )
    assert( reply.get('ok', -1) == 1 )
    SID2 = reply.get('sid')
    SERVER2 = reply.get('server')

    # -----------------------------------------
    msg_1_2 = json_dumps( [{"type":"MSGTYPE1", "text":"MSGTEXT1"}, {"type":"MSGTYPE2", "text":"MSGTEXT2"}] )
    reply = post( "send", project="pw", recipient=AUID2, sid=SID1, auid=AUID1, body=msg_1_2, server=SERVER1 )
    assert( reply.get('ok', -1) == 1 )

    # -----------------------------------------
    reply = get( "logout", auid=AUID1, sid=SID1, server=SERVER1 )
    assert( reply.get('ok', -1) == 1 )

    reply = get( "logout", auid=AUID2, sid=SID2, server=SERVER2 )
    assert( reply.get('ok', -1) == 1 )
    
    print "-- test_redirect: DONE"

## --------------------------------------------------------------------------------------------------------------------------

def test_redirect_xs_login():
    AUID1 = 2
    
    # -----------------------------------------
    reply = get( "login", project="pw", auid=AUID1, server=X_SERVER1 )
    assert( reply.get('ok', -1) == 1 )
    assert( reply.get('re', 0) == 0 )
    SID1 = reply.get('sid')
    SERVER1 = reply.get('server')
    
    try:
        # -----------------------------------------
        reply = get( "login", project="pw", auid=AUID1, server=X_SERVER1 )
        assert( reply.get('ok', -1) == 1 )
        assert( reply.get('re', -1) == 1 )
        SID1 = reply.get('sid')
        SERVER1 = reply.get('server')

        # -----------------------------------------
        reply = get( "login", project="pw", auid=AUID1, server=X_SERVER2 )
        assert( reply.get('ok', -1) == 1 )
        assert( reply.get('redirect_from', '')  )
        assert( reply.get('re', -1) == 1 )
        SID1 = reply.get('sid')
        SERVER1 = reply.get('server')
    except:
        catch()

    # -----------------------------------------
    reply = get( "logout", auid=AUID1, sid=SID1, server=SERVER1 )
    assert( reply.get('ok', -1) == 1 )
    
    print "-- test_redirect_xs_login: DONE"

## ----------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------

def test_send_offline():
    AUID1 = 3
    AUID2 = 2
    
    # -----------------------------------------
    reply = get( "login", project="pw", auid=AUID1, server=X_SERVER1 )
    assert( reply.get('ok', -1) == 1 )
    SID1 = reply.get('sid')
    SERVER1 = reply.get('server')

    # -----------------------------------------
    # send to offline user
    msg_1_2 = json_dumps( [{"type":"MSGTYPE3", "text":"MSGTEXT3"}, {"type":"MSGTYPE4", "text":"MSGTEXT4"}] )
    reply = post( "send", project="pw", recipient=AUID2, sid=SID1, auid=AUID1, body=msg_1_2, server=SERVER1 )
    assert( reply.get('ok', -1) == 1 )

    # -----------------------------------------
    reply = get( "logout", auid=AUID1, sid=SID1, server=SERVER1 )
    assert( reply.get('ok', -1) == 1 )

    reply = get( "login", project="pw", auid=AUID2, server=X_SERVER2 )
    assert( reply.get('ok', -1) == 1 )
    SID2 = reply.get('sid')
    SERVER2 = reply.get('server')
    
    messages = reply.get('messages')
    feedSortedMessagesToNewModel( messages )

    reply = get( "logout", auid=AUID2, sid=SID2, server=SERVER2 )
    assert( reply.get('ok', -1) == 1 )

    print "-- test_send_offline: DONE"

## ----------------------------------------------------------------------------------

def test_redirect_send():
    AUID1 = 3
    AUID2 = 2
    
    # -----------------------------------------
    reply = get( "login", project="pw", auid=AUID1, server=X_SERVER1 )
    assert( reply.get('ok', -1) == 1 )
    SID1 = reply.get('sid')
    SERVER1 = reply.get('server')

    reply = get( "login", project="pw", auid=AUID2, server=X_SERVER2 )
    assert( reply.get('ok', -1) == 1 )
    SID2 = reply.get('sid')
    SERVER2 = reply.get('server')
    
    try:
        # -----------------------------------------
        # send to offline user
        msg_1_2 = json_dumps( [{"type":"MSGTYPE3", "text":"MSGTEXT3"}, {"type":"MSGTYPE4", "text":"MSGTEXT4"}] )
        reply = post( "send", project="pw", recipient=AUID2, sid=SID1, auid=AUID1, body=msg_1_2, server=SERVER1 )
        assert( reply.get('ok', -1) == 1 )
    except:
        catch()

    # -----------------------------------------
    reply = get( "logout", auid=AUID1, sid=SID1, server=SERVER1 )
    assert( reply.get('ok', -1) == 1 )

    reply = get( "logout", auid=AUID2, sid=SID2, server=SERVER2 )
    assert( reply.get('ok', -1) == 1 )

    print "-- test_redirect_send: DONE"

## ----------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------

def test_nologin_send_offline():
    AUID1 = 3
    AUID2 = 2
    AUID3 = 10
    
    # -----------------------------------------
    # send to offline user
    msg_1_2 = json_dumps( [{"type":"MSGTYPE3", "text":"MSGTEXT3"}, {"type":"MSGTYPE4", "text":"MSGTEXT4"}] )
    SENDER1 = "%s:%s" % ("em", AUID1)
    reply = post( "send_nl", project="pw", recipient=AUID2, sender=SENDER1, body=msg_1_2, server=X_SERVER1 )
    assert( reply.get('ok', -1) == 1 )

    # -----------------------------------------
    reply = get( "login", project="pw", auid=AUID2, server=X_SERVER2 )
    assert( reply.get('ok', -1) == 1 )
    SID2 = reply.get('sid')
    SERVER2 = reply.get('server')
    
    messages = reply.get('messages')
    try:
        feedSortedMessagesToNewModel( messages )
    except:
        catch()

    reply = get( "logout", auid=AUID2, sid=SID2, server=SERVER2 )
    assert( reply.get('ok', -1) == 1 )

    print "-- test_nologin_send_offline: DONE"

## ----------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------

def test_receive_purge():
    AUID1 = 3
    AUID2 = 2
    
    # -----------------------------------------
    reply = get( "login", project="pw", auid=AUID1, server=X_SERVER1 )
    assert( reply.get('ok', -1) == 1 )
    SID1 = reply.get('sid')
    SERVER1 = reply.get('server')
    MESSAGES1 = reply.get('messages')

    # -----------------------------------------
    # send to online user
    msg_1_2 = json_dumps( [{"type":"MSGTYPE5", "text":"MSGTEXT5"}, {"type":"MSGTYPE6", "text":"MSGTEXT6"}] )
    SENDER2 = "%s:%s" % ("em", AUID2)
    reply = post( "send_nl", project="pw", recipient=AUID1, sender=SENDER2, body=msg_1_2, server=X_SERVER1 )
    assert( reply.get('ok', -1) == 1 )

    # -----------------------------------------
    # receive new messages:
    reply = get( "retrieve", auid=AUID1, sid=SID1, server=SERVER1 )
    assert( reply.get('ok', -1) == 1 )
    
    MESSAGES2 = reply.get('messages')
    feedSortedMessagesToNewModel( MESSAGES2 )
    ## print "len(2):%s, len(1):%s" % (len(MESSAGES1), len(MESSAGES2))
    assert( len(MESSAGES2) == len(MESSAGES1) + 2 )
    
    # -----------------------------------------
    # purge with bad body (SHOULD FAIL):
    purge_body = "124125,14625"
    reply = post( "purge", auid=AUID1, sid=SID1, server=SERVER1, body=purge_body )
    assert( reply.get('ok', -1) == 0 )
    assert( reply.get('ec', -1) == EC.XS_BAD_PURGE_MESSAGE_BODY )
    
    # -----------------------------------------
    # purge wrong msg_ids (SHOULD FAIL):
    purge_body = json_dumps( [12345,123456] )
    reply = post( "purge", auid=AUID1, sid=SID1, server=SERVER1, body=purge_body )
    assert( reply.get('ok', -1) == 0 )
    assert( reply.get('ec', -1) == EC.XS_NO_MESSAGES_TO_DELETE )
    
    # -----------------------------------------
    # purge all messages:
    purge_messages = []
    for msg_id, msg in MESSAGES2.iteritems():
        purge_messages.append( msg_id )
    purge_body = json_dumps( purge_messages )
    reply = post( "purge", auid=AUID1, sid=SID1, server=SERVER1, body=purge_body )
    assert( reply.get('ok', -1) == 1 )
        
    # -----------------------------------------
    # receive messages (should be empty list):
    reply = get( "retrieve", auid=AUID1, sid=SID1, server=SERVER1 )
    assert( reply.get('ok', -1) == 1 )
    MESSAGES3 = reply.get('messages')
    assert( len(MESSAGES3) == 0 )
    
    # -----------------------------------------
    # purge again (SHOULD FAIL):
    reply = post( "purge", auid=AUID1, sid=SID1, server=SERVER1, body=purge_body )
    assert( reply.get('ok', -1) == 0 )
    assert( reply.get('ec', -1) == EC.XS_NO_MESSAGES_TO_DELETE )
    
    # -----------------------------------------
    reply = get( "logout", auid=AUID1, sid=SID1, server=SERVER1 )
    assert( reply.get('ok', -1) == 1 )

    print "-- test_receive_purge: DONE"
    
## ----------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------

AWARD_MESSAGE = {
    "type": "session_awards",
    "roll_id": "5753766780766081745",
    u'awards': [
        {u'count': -8, u'type': 4, u'id': 22648455}, 
        {u'count': -40, u'type': 9, u'id': 22648455}, 
        {u'count': 84, u'type': 6, u'id': 22648455}, 
        {u'count': 92, u'type': 10, u'id': 22648455}, 
        {u'count': 1, u'type': 1, u'id': 556178400}, 
        {u'count': 730, u'type': 2, u'id': 0}, 
        {u'count': 99, u'type': 7, u'id': 0}, 
        {u'count': 96, u'type': 8, u'id': 0}, 
        {u'count': 97, u'type': 11, u'id': 0}, 
        {u'count': 5, u'type': 5, u'id': 0}
    ], 
    u'session_roll': u'{"lastFWODTime":"1340200098","rollTable":{\
"Server/CTE_Roll.xdb":[{"dbid":"Server/CTE_Roll.xdb:8414F7EE-D4D2-44C5-BA46-8F7EC3192695","probability":4680},\
{"dbid":"Server/CTE_Roll.xdb:F39DFABA-8739-4BCE-B394-966707C57D46","probability":3680},\
{"dbid":"Server/CTE_Roll.xdb:5895E9FE-6010-402F-A196-3C021C7210F8","probability":990},\
{"dbid":"Server/CTE_Roll.xdb:57775AD0-4A0B-4D04-B310-9582ABCEEF17","probability":150},\
{"dbid":"Server/PvP_RollContainer.xdb:B9213F40-5B6B-404F-8983-4BFD4654FC2F","probability":200}],\
"Server/PvP_Roll.xdb":[{"dbid":"Server/PvP_RollContainer.xdb:962AA71F-C6FD-4E5B-B8A7-E77135364616","probability":4180},\
{"dbid":"Server/PvP_RollContainer.xdb:5B6EA956-07FF-41B1-9CBC-9373FAEF3C07","probability":2680},\
{"dbid":"Server/PvP_RollContainer.xdb:7E6EEEE2-0A28-4027-9A7F-7946570D32E7","probability":790},\
{"dbid":"Server/PvP_RollContainer.xdb:C2E72313-691A-48AC-BCF9-CCF9C38647EA","probability":50},\
{"dbid":"Server/PvP_RollContainer.xdb:B9213F40-5B6B-404F-8983-4BFD4654FC2F","probability":200}],\
"Server/Training_Roll.xdb":[{"dbid":"Server/Training_Roll.xdb:34D0E774-BF86-4E75-993C-70230E250331","probability":5800},\
{"dbid":"Server/Training_Roll.xdb:49CA2037-8D89-4BEA-86C1-0263AEFD99A6","probability":3500},\
{"dbid":"Server/Training_Roll.xdb:1CD53758-14AB-4994-A20E-2A928C06708A","probability":500}]}}\n', 
}

ROLL_MESSAGE = {
    "type": "forge_roll",
    "roll_id": "5753766780766081746",
    u'awards': [
        {u'count': 1, u'type': 1, u'id': 556178400}, 
        {u'count': 1, u'type': 1, u'id': 556178400}, 
    ], 
    u'session_roll': u'{"lastFWODTime":"1340200098","rollTable":{\
"Server/CTE_Roll.xdb":[{"dbid":"Server/CTE_Roll.xdb:8414F7EE-D4D2-44C5-BA46-8F7EC3192695","probability":4680},\
{"dbid":"Server/CTE_Roll.xdb:F39DFABA-8739-4BCE-B394-966707C57D46","probability":3680},\
{"dbid":"Server/CTE_Roll.xdb:5895E9FE-6010-402F-A196-3C021C7210F8","probability":990},\
{"dbid":"Server/CTE_Roll.xdb:57775AD0-4A0B-4D04-B310-9582ABCEEF17","probability":150},\
{"dbid":"Server/PvP_RollContainer.xdb:B9213F40-5B6B-404F-8983-4BFD4654FC2F","probability":200}],\
"Server/PvP_Roll.xdb":[{"dbid":"Server/PvP_RollContainer.xdb:962AA71F-C6FD-4E5B-B8A7-E77135364616","probability":4180},\
{"dbid":"Server/PvP_RollContainer.xdb:5B6EA956-07FF-41B1-9CBC-9373FAEF3C07","probability":2680},\
{"dbid":"Server/PvP_RollContainer.xdb:7E6EEEE2-0A28-4027-9A7F-7946570D32E7","probability":790},\
{"dbid":"Server/PvP_RollContainer.xdb:C2E72313-691A-48AC-BCF9-CCF9C38647EA","probability":50},\
{"dbid":"Server/PvP_RollContainer.xdb:B9213F40-5B6B-404F-8983-4BFD4654FC2F","probability":200}],\
"Server/Training_Roll.xdb":[{"dbid":"Server/Training_Roll.xdb:34D0E774-BF86-4E75-993C-70230E250331","probability":5800},\
{"dbid":"Server/Training_Roll.xdb:49CA2037-8D89-4BEA-86C1-0263AEFD99A6","probability":3500},\
{"dbid":"Server/Training_Roll.xdb:1CD53758-14AB-4994-A20E-2A928C06708A","probability":500}]}}\n', 
}

LONG_RUSSIAN_TEXT = u"??????? ????? 123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941123451235555555871362495871634895761394756891374658917658971634895761894112345123555555587136249587163489576139475689137465891765897163489576189411234512355555558713624958716348957613947568913746589176589716348957618941"

def test_login_ws():
    SNUID1 = '100000234693443'
    SNTOKEN1 = 'AAAB9M8ptmXMBAPQhex9USB08I5kg6ZAXPHCVZCkhygGZAYh4RJtHnd6zwIhRk0EDpqWvDlAfX19qw8nSD0XV8qz5BxesgSbDSd06KKZCMQZDZD'
    AUID2 = 2
    AUID1 = 110
    
    # -----------------------------------------
    # send to OFFLINE user
    msg_1_2 = json_dumps( [{"type":"offline_MSGTYPE9", "text":LONG_RUSSIAN_TEXT}] )
    SENDER2 = "%s:%s" % ("em", AUID2)
    reply = post( "send_nl", project="pw", recipient=AUID1, sender=SENDER2, body=msg_1_2, server=X_ANY_SERVER )
    assert( reply.get('ok', -1) == 1 )
    
    # ????????, ???? ????????? ????? ?????? ?? sql
    time.sleep(0.5)
    
    # -----------------------------------------
    reply = ws_get( "sn_login", snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 )
    assert( reply.get('ok', -1) == 1 )
    AUID1 = reply.get('auid')
    WS_SERVER1 = reply.get('server')
    UID1 = reply.get('uid')
    KEY1 = reply.get('key')
    
    try:
        # ????????, ???? ?? WS-??????? ?????? ?????? ?? ????? (????? ?? ??? acc.locked)
        time.sleep(0.5)
        
        # -----------------------------------------
        # send to online user
        msg_1_2 = json_dumps( [{"type":"online_MSGTYPE7", "text":"MSGTEXT7"}, {"type":"async_mail_test", "text":u"??????? ????? 67890"}, AWARD_MESSAGE, ROLL_MESSAGE] )
        SENDER2 = "%s:%s" % ("em", AUID2)
        reply = post( "send_nl", project="pw", recipient=AUID1, sender=SENDER2, body=msg_1_2, server=X_ANY_SERVER )
        assert( reply.get('ok', -1) == 1 )

        # ????????, ???? ?????????? push ? onPushReply.purge
        time.sleep(0.5)
        
        # -----------------------------------------
        reply = ws_get( "keepalive", uid=UID1, key=KEY1, server=WS_SERVER1 )
        assert( reply.get('ok', -1) == 1 )
        messages = reply.get("message")
        print "-- messages: %s" % messages
        assert( len(messages) == 3 )
        
    except:
        catch()
    
    ## time.sleep(60)
    
    # -----------------------------------------
    reply = ws_get( "logout", uid=UID1, key=KEY1, server=WS_SERVER1 )
    assert( reply.get('ok', -1) == 1 )
    
    
def test_login_ws2():
    SNUID1 = '100000234693443'
    SNTOKEN1 = 'AAAB9M8ptmXMBAPQhex9USB08I5kg6ZAXPHCVZCkhygGZAYh4RJtHnd6zwIhRk0EDpqWvDlAfX19qw8nSD0XV8qz5BxesgSbDSd06KKZCMQZDZD'
    AUID1 = 25
    AUID2 = 2
    
    # -----------------------------------------
    # send to offline user
    msg_1_2 = json_dumps( [{"type":"offline_MSGTYPE9", "text":LONG_RUSSIAN_TEXT}] )
    SENDER2 = "%s:%s" % ("em", AUID2)
    reply = post( "send_nl", project="pw", recipient=AUID1, sender=SENDER2, body=msg_1_2, server=X_ANY_SERVER )
    assert( reply.get('ok', -1) == 1 )
    
    msg_1_2 = json_dumps( [{"type":"online_MSGTYPE8", "text":"MSGTEXT8"}, {"type":"async_mail_test", "text":u"??????? ????? 67890"}, AWARD_MESSAGE, ROLL_MESSAGE] )
    SENDER2 = "%s:%s" % ("em", AUID2)
    reply = post( "send_nl", project="pw", recipient=AUID1, sender=SENDER2, body=msg_1_2, server=X_ANY_SERVER )
    assert( reply.get('ok', -1) == 1 )

    # ????????, ???? ?????????? push ? onPushReply.purge
    time.sleep(0.5)
    
    # -----------------------------------------
    reply = ws_get( "sn_login", snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 )
    assert( reply.get('ok', -1) == 1 )
    AUID1 = reply.get('auid')
    WS_SERVER1 = reply.get('server')
    UID1 = reply.get('uid')
    KEY1 = reply.get('key')
    
    print "AUID1=%s" % AUID1
    
    try:
        # ????????, ???? ?? WS-??????? ?????? ?????? ?? ????? (????? ?? ??? acc.locked)
        time.sleep(0.5)
        
        # -----------------------------------------
        reply = ws_get( "keepalive", uid=UID1, key=KEY1, server=WS_SERVER1 )
        assert( reply.get('ok', -1) == 1 )
        messages = reply.get("message")
        print "-- messages: %s" % messages
        assert( len(messages) == 3 )
        
    except:
        catch()
    
    ## time.sleep(60)
    
    # -----------------------------------------
    reply = ws_get( "logout", uid=UID1, key=KEY1, server=WS_SERVER1 )
    assert( reply.get('ok', -1) == 1 )

## ----------------------------------------------------------------------------------

def test_login_keepalive():
    SNUID1 = '100000234693443'
    SNTOKEN1 = 'AAAB9M8ptmXMBAPQhex9USB08I5kg6ZAXPHCVZCkhygGZAYh4RJtHnd6zwIhRk0EDpqWvDlAfX19qw8nSD0XV8qz5BxesgSbDSd06KKZCMQZDZD'
    AUID2 = 2
    AUID1 = 110
    
    # -----------------------------------------
    reply = ws_get( "sn_login", snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 )
    assert( reply.get('ok', -1) == 1 )
    AUID1 = reply.get('auid')
    WS_SERVER1 = reply.get('server')
    UID1 = reply.get('uid')
    KEY1 = reply.get('key')
    
    try:
        # ????????, ???? ?? WS-??????? ?????? ?????? ?? ????? (????? ?? ??? acc.locked)
        time.sleep(0.5)
        
        # -----------------------------------------
        reply = ws_get( "auth", uid=UID1, key=KEY1, server=WS_SERVER1 )
        assert( reply.get('ok', -1) == 1 )
        
        # -----------------------------------------
        reply = ws_get( "keepalive", uid=UID1, key=KEY1, server=WS_SERVER1 )
        assert( reply.get('ok', -1) == 1 )
        
        time.sleep(9.4)
        
        # -----------------------------------------
        reply = ws_get( "keepalive", uid=UID1, key=KEY1, server=WS_SERVER1 )
        assert( reply.get('ok', -1) == 1 )
        
        time.sleep(9.4)
        
        # -----------------------------------------
        reply = ws_get( "keepalive", uid=UID1, key=KEY1, server=WS_SERVER1 )
        assert( reply.get('ok', -1) == 1 )
        
    except:
        catch()
    
    ## time.sleep(60)
    
    # -----------------------------------------
    reply = ws_get( "logout", uid=UID1, key=KEY1, server=WS_SERVER1 )
    assert( reply.get('ok', -1) == 1 )

## ----------------------------------------------------------------------------------

def test_login_redirect():
    SNUID1 = '100000234693443'
    SNTOKEN1 = 'AAAB9M8ptmXMBAPQhex9USB08I5kg6ZAXPHCVZCkhygGZAYh4RJtHnd6zwIhRk0EDpqWvDlAfX19qw8nSD0XV8qz5BxesgSbDSd06KKZCMQZDZD'
    AUID2 = 2
    AUID1 = 110
    
    # -----------------------------------------
    reply = ws_get( "sn_login", snid="fb", snuid=SNUID1, server="one", sntoken=SNTOKEN1 ) # rd_ip="86.57.144.74"
    assert( reply.get('ok', -1) == 1 )
    AUID1 = reply.get('auid')
    WS_SERVER1 = reply.get('server')
    UID1 = reply.get('uid')
    KEY1 = reply.get('key')
    
    try:
        # ????????, ???? ?? WS-??????? ?????? ?????? ?? ????? (????? ?? ??? acc.locked)
        time.sleep(0.5)
        
        # -----------------------------------------
        reply = ws_get( "sn_login", snid="fb", snuid=SNUID1, server="two", sntoken=SNTOKEN1, key=KEY1 )
        assert( reply.get('ok', -1) == 1 )
        KEY1 = reply.get('key')
        
    except:
        catch()
    
    ## time.sleep(60)
    
    # -----------------------------------------
    reply = ws_get( "logout", uid=UID1, key=KEY1, server=WS_SERVER1 )
    assert( reply.get('ok', -1) == 1 )

## ----------------------------------------------------------------------------------

def test_who_login():
    SNUID1 = '100000234693443'
    SNTOKEN1 = 'AAAB9M8ptmXMBAPQhex9USB08I5kg6ZAXPHCVZCkhygGZAYh4RJtHnd6zwIhRk0EDpqWvDlAfX19qw8nSD0XV8qz5BxesgSbDSd06KKZCMQZDZD'
    
    # -----------------------------------------
    reply = ws_get( "l_who", snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) # rd_ip="86.57.144.74"
    assert( reply.get('ok', -1) == 1 )
    WS_SERVER1 = reply.get('server')
    LOGIN_TOKEN1 = reply.get('token')
    reply_info = reply.get('info', {})
    AUID1 = reply_info.get('auid')
    
    # -----------------------------------------
    reply = ws_get( "sn_login", snid="pw", snuid=AUID1, server=WS_SERVER1, sntoken=LOGIN_TOKEN1 )
    assert( reply.get('ok', -1) == 1 )
    UID1 = reply.get('uid')
    KEY1 = reply.get('key')
    
    time.sleep( 1.0 ) 
    
    # -----------------------------------------
    reply = ws_get( "logout", uid=UID1, key=KEY1, server=WS_SERVER1 )
    assert( reply.get('ok', -1) == 1 )

## ----------------------------------------------------------------------------------

def test_who_login_nocbt():
    SNUID1 = '100000234693443'
    SNTOKEN1 = 'AAAB9M8ptmXMBAPQhex9USB08I5kg6ZAXPHCVZCkhygGZAYh4RJtHnd6zwIhRk0EDpqWvDlAfX19qw8nSD0XV8qz5BxesgSbDSd06KKZCMQZDZD'
    
    # -----------------------------------------
    reply = ws_get( "l_who", snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1, nocbt=1 ) # rd_ip="86.57.144.74"
    assert( reply.get('ok', -1) == 1 )
    WS_SERVER1 = reply.get('server')
    LOGIN_TOKEN1 = reply.get('token')
    reply_info = reply.get('info', {})
    AUID1 = reply_info.get('auid')
    
    # -----------------------------------------
    reply = ws_get( "sn_login", snid="pw", snuid=AUID1, server=WS_SERVER1, sntoken=LOGIN_TOKEN1 )
    assert( reply.get('ok', -1) == 1 )
    UID1 = reply.get('uid')
    KEY1 = reply.get('key')
    
    time.sleep( 1.0 ) 
    
    # -----------------------------------------
    reply = ws_get( "logout", uid=UID1, key=KEY1, server=WS_SERVER1 )
    assert( reply.get('ok', -1) == 1 )

## ----------------------------------------------------------------------------------

def test_who_login_redirect():
    SNUID1 = '100000234693443'
    SNTOKEN1 = 'AAAB9M8ptmXMBAPQhex9USB08I5kg6ZAXPHCVZCkhygGZAYh4RJtHnd6zwIhRk0EDpqWvDlAfX19qw8nSD0XV8qz5BxesgSbDSd06KKZCMQZDZD'
    
    # -----------------------------------------
    reply = ws_get( "l_who", snid="fb", snuid=SNUID1, server="one", sntoken=SNTOKEN1 ) # rd_ip="86.57.144.74"
    assert( reply.get('ok', -1) == 1 )
    LOGIN_TOKEN1 = reply.get('token')
    reply_info = reply.get('info', {})
    AUID1 = reply_info.get('auid')
    
    # -----------------------------------------
    reply = ws_get( "sn_login", snid="pw", snuid=AUID1, server="one", sntoken=LOGIN_TOKEN1 )
    assert( reply.get('ok', -1) == 1 )
    UID1 = reply.get('uid')
    KEY1 = reply.get('key')
    
    time.sleep( 1.0 ) 
    
    # -----------------------------------------
    reply = ws_get( "l_who", snid="fb", snuid=SNUID1, server="two", sntoken=SNTOKEN1, key=KEY1 ) # rd_ip="86.57.144.74"
    assert( reply.get('ok', -1) == 1 )
    WS_SERVER2 = reply.get('server')
    LOGIN_TOKEN2 = reply.get('token')
    reply_info = reply.get('info', {})
    AUID1 = reply_info.get('auid')
    
    # -----------------------------------------
    reply = ws_get( "sn_login", snid="pw", snuid=AUID1, server="two", sntoken=LOGIN_TOKEN2, key=KEY1 )
    assert( reply.get('ok', -1) == 1 )
    UID1 = reply.get('uid')
    KEY1 = reply.get('key')
    
    # -----------------------------------------
    reply = ws_get( "logout", uid=UID1, key=KEY1, server="one" )
    assert( reply.get('ok', -1) == 1 )

## ----------------------------------------------------------------------------------

def test_sublogin():
    SNUID1 = '100000234693443'
    SNTOKEN1 = 'AAAB9M8ptmXMBAPQhex9USB08I5kg6ZAXPHCVZCkhygGZAYh4RJtHnd6zwIhRk0EDpqWvDlAfX19qw8nSD0XV8qz5BxesgSbDSd06KKZCMQZDZD'
    AUID1 = 110
    
    DIRECT_WS_ONE_HTTP_ADDR = '%s:%d' % (SERVER_ADDR, 8801)
    DIRECT_WS_TWO_HTTP_ADDR = '%s:%d' % (SERVER_ADDR, 8802)
    
    reply = ws_get( "sublogin_fsn", snid="fb", snuid=SNUID1, http_addr=DIRECT_WS_ONE_HTTP_ADDR, server="x", wait_persistent=1 )
    assert( reply.get('ok', -1) == 1 )
    AUID1 = reply.get('auid')
    WS_SERVER1 = reply.get('server')
    UID1 = reply.get('uid')
    KEY1 = reply.get('key')
    
    time.sleep( 1.0 ) # ???? ????? ?????????? ???, ????? ?? ???? locked
    
    try:
        reply = ws_get( "sublogin_fsn", snid="fb", snuid=SNUID1, http_addr=DIRECT_WS_TWO_HTTP_ADDR, server="x", wait_persistent=1 )
        assert( reply.get('ok', -1) == 0 )
        assert( reply.get("ws_name") == "one" ) # ?????? ???????,??? ???? ??? ??????? ?? ws one
    except:
        catch()
    
    # -----------------------------------------
    reply = ws_get( "logout", uid=UID1, key=KEY1, server=WS_SERVER1 )
    assert( reply.get('ok', -1) == 1 )
    
##----------------------------------------------------------------------------------------------------------------

def test_pwc_simple_login():
    LOGIN_EMAIL = u'danvorobiev@list.ru'
    LOGIN_EMAIL_UTF8 = utf8convert( LOGIN_EMAIL.lower() )
    PWC_EMAIL_MD5 = md5( LOGIN_EMAIL_UTF8 )
    
    reply = ws_get( "sn_login", snid="pwe", snuid=PWC_EMAIL_MD5, sntoken=md5("123") )
    assert( reply.get('ok', -1) == 1 )
    AUID1 = reply.get('auid')
    WS_SERVER1 = reply.get('server')
    UID1 = reply.get('uid')
    KEY1 = reply.get('key')
    
    time.sleep( 1.0 ) # ???? ????? ?????????? ???, ????? ?? ???? locked
    
    # -----------------------------------------
    reply = ws_get( "logout", uid=UID1, key=KEY1, server=WS_SERVER1 )
    assert( reply.get('ok', -1) == 1 )

##----------------------------------------------------------------------------------------------------------------
##----------------------------------------------------------------------------------------------------------------

def accLogin( **kwargs ):
    acc = ClassDict()
    
    acc.model = ModelData()
    acc.model.init( None ) # ????? ???????????? keeperTypeName, ? ?? ??????????? ?? model changes, ?????????? ?? "init"
    
    acc.friendsdata = FriendsData()
    acc.friendsdata.init( None ) # ????? ???????????? keeperTypeName, ? ?? ??????????? ?? model changes, ?????????? ?? "init"
    
    acc.partydata = PartyData()
    acc.partydata.init( None ) # ????? ???????????? keeperTypeName, ? ?? ??????????? ?? model changes, ?????????? ?? "init"

    reply = ws_get( "sn_login", **kwargs ) 
    assert( reply.get('ok', -1) == 1 )
    
    AUID = reply.get('auid')
    WS_SERVER = reply.get('server')
    UID = reply.get('uid')
    KEY = reply.get('key')
    NICK = reply.get('nick')
    
    acc.auid = AUID
    
    global accs
    accs[ AUID ] = ClassDict( acc=acc, uid=UID, key=KEY, server=WS_SERVER )
    
    time.sleep(1.0) # ???? ???? ?????? ModelData

    # ???????? ? ?????????????? ModelData
    reply = accGet( AUID, "auth" )
    model_init = reply.get("init")
    model_init_changes = [{"init_auth":[["/","init",model_init]]}]
    ModelChangeApplicator.apply( acc, "model", ModelData, model_init_changes)
    
    return acc
    
# ------------------------------------------
def accGet( AUID, action, **kwargs ):
    acc_dict = accs[ AUID ]
    
    reply = ws_get( action, uid=acc_dict.uid, key=acc_dict.key, server=acc_dict.server, **kwargs )
    assert( reply.get('ok', -1) == 1 )
    ModelChangeApplicator.apply( acc_dict.acc, "model", ModelData, reply.get("ModelData"))
    ModelChangeApplicator.apply( acc_dict.acc, "friendsdata", FriendsData, reply.get("FriendsData"))
    ModelChangeApplicator.apply( acc_dict.acc, "partydata", PartyData, reply.get("PartyData"))
    
    return reply
    
## ----------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------

def test_alien_login():
    SNUID1 = '100000234693443'
    SNTOKEN1 = 'AAAB9M8ptmXMBAPQhex9USB08I5kg6ZAXPHCVZCkhygGZAYh4RJtHnd6zwIhRk0EDpqWvDlAfX19qw8nSD0XV8qz5BxesgSbDSd06KKZCMQZDZD'
    
    # -----------------------------------------
    reply = ws_get( "l_who", snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) # rd_ip="86.57.144.74"
    assert( reply.get('ok', -1) == 1 )
    WS_SERVER1 = reply.get('server')
    LOGIN_TOKEN1 = reply.get('token')
    reply_info = reply.get('info', {})
    AUID1 = reply_info.get('auid')
    
    # ??????? "?????? ??????" ?? ??????????? ????
    WS_SERVERS = ["one", "two"]
    WS_SERVERS.remove(WS_SERVER1)
    WS_SERVER2 = WS_SERVERS[0]
    
    # -----------------------------------------
    try:
        # BAD WS:
        reply = ws_get( "alien_login", snuid=AUID1, server=WS_SERVER2, sntoken=LOGIN_TOKEN1 )
        warn("alien_login (WRONG WS) reply: %s" % reply)
        assert( reply.get('ok', -1) == 0 )
        #assert( reply.get('ec', -1) == 203 )
        
        # BAD TOKEN:
        reply = ws_get( "alien_login", snuid=AUID1, server=WS_SERVER1, sntoken="XXXXX" )
        warn("alien_login (WRONG TOKEN) reply: %s" % reply)
        assert( reply.get('ok', -1) == 0 )
        
        # BAD AUID:
        reply = ws_get( "alien_login", snuid=12345, server=WS_SERVER1, sntoken=LOGIN_TOKEN1 )
        warn("alien_login (WRONG AUID) reply: %s" % reply)
        assert( reply.get('ok', -1) == 0 )
        
        # CORRECT LOGIN:
        reply = ws_get( "alien_login", snuid=AUID1, server=WS_SERVER1, sntoken=LOGIN_TOKEN1 )
        warn("alien_login reply: %s" % reply)
        assert( reply.get('ok', -1) == 1 )
        
        # REPEAT LOGIN (must fail, token should be immediately cleared)
        reply = ws_get( "alien_login", snuid=AUID1, server=WS_SERVER1, sntoken=LOGIN_TOKEN1 )
        warn("alien_login (REPEAT) reply: %s" % reply)
        assert( reply.get('ok', -1) == 0 )
        assert( reply.get('ec', -1) == 203 )
        
        print "- test_alien_login ok"
    except:
        catch()

## ----------------------------------------------------------------------------------

def test_double_login():
    print "- test_double_login"
    
    SNUID1 = '100000234693443'
    SNTOKEN1 = 'AAAB9M8ptmXMBAPQhex9USB08I5kg6ZAXPHCVZCkhygGZAYh4RJtHnd6zwIhRk0EDpqWvDlAfX19qw8nSD0XV8qz5BxesgSbDSd06KKZCMQZDZD'
    
    SNUID2 = '100003297559974'
    SNTOKEN2 = 'AAAB9M8ptmXMBAKLjZBe9ViZATa3j0miIp0BkIZA11325znpxQXQ9hdZAy1CnvZB3wgik1G2cqZCV9HzZBqiKJuZCqwUGZAZCD8LvYdZBRDWPBr2ZAgZDZD'
    
    global accs
    accs = {}
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    try:
        acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 ) 
    except:
        catch()
        acc2 = ClassDict()
    
    time.sleep(2.0) # пусть пройдет апдейт
    
    AUID1, AUID2 = acc1.auid, acc2.auid
    
    print "--- test_double_login ok"
    
    logLevel()
    reply = accGet( AUID1, "logout" )
    
    if acc2:
        try:
            reply = accGet( AUID2, "logout" )
        except:
            catch()
    
    
## ----------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------

DEFAULT_LOG_LEVEL = logging.INFO
#~ DEFAULT_LOG_LEVEL = logging.WARNING
logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )

## ----------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------

#~ test_redirect()
#~ time.sleep(1.0)

#~ test_redirect_xs_login()
#~ time.sleep(1.0)

#~ test_redirect_send()
#~ time.sleep(1.0)

#~ test_send_offline()
#~ time.sleep(1.0)

#~ test_nologin_send_offline()
#~ time.sleep(1.0)

#~ test_receive_purge()
#~ time.sleep(1.0)

#~ test_login_ws2()
#~ time.sleep(1.0)

#~ ### test_login_keepalive() # ???? ??? ???????? keepalive ? ?????????? ??????? in_castle
#~ ### time.sleep(1.0)

#~ test_login_redirect()
#~ time.sleep(1.0)

#~ test_sublogin()
#~ time.sleep(1.0)

#~ test_who_login()
#~ time.sleep(2.0)

test_who_login_nocbt()
time.sleep(2.0)

#~ test_alien_login()
#~ time.sleep(2.0)

#~ test_pwc_simple_login()
#~ time.sleep(2.0)

#~ test_who_login()
#~ time.sleep(1.0)

#~ test_who_login_redirect()
#~ time.sleep(2.0)

#~ test_double_login()
#~ time.sleep(2.0)
