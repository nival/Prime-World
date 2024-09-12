# -*- coding: utf-8 -*-

import socket, ssl, pprint, time, sys, os
import hashlib
import urllib2
import random
import logging
import base64

os.chdir('..')
sys.path.append('.')

from base.helpers import *

from friendsdata.FriendsData import FriendsData
from party.PartyData import PartyData
from modeldata.ModelData import ModelData
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from modeldata.change_applicator import ModelChangeApplicator

import EC
import MM


#~ print time.ctime(1352384135)
#~ exit(0)

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
    secret = kwargs.pop("secret", "")
    params = dict( **kwargs )
    params["action"] = action
    req = makeSignedRequest( params, secret=secret )

    request = "http://%s/%s?%s" % (http_addr, server, req)
    info( "\n%s request: %s" % (action, request) )

    reply = urllib2.urlopen( request, None, HTTP_TIMEOUT ).read() # 
    parsed_reply = json_loads(reply)
    
    info( "%s parsed reply: %s" % (action, pretty(parsed_reply)) )
    return parsed_reply.get("response")
    
## --------------------------------------------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------------------------------------------

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
    
##----------------------------------------------------------------------------------------------------------------
##----------------------------------------------------------------------------------------------------------------

def accLogin( **kwargs ):
    acc = ClassDict()
    
    acc.model = ModelData()
    acc.model.init( None ) # чтобы проставились keeperTypeName, и не рассыпались на model changes, приходящих до "init"
    
    acc.friendsdata = FriendsData()
    acc.friendsdata.init( None ) # чтобы проставились keeperTypeName, и не рассыпались на model changes, приходящих до "init"
    
    acc.partydata = PartyData()
    acc.partydata.init( None ) # чтобы проставились keeperTypeName, и не рассыпались на model changes, приходящих до "init"
    
    acc.tamburdata = PartyData()
    acc.tamburdata.init( None ) # чтобы проставились keeperTypeName, и не рассыпались на model changes, приходящих до "init"
    
    acc.guilddata = GuildData()
    acc.guilddata.init( None ) # чтобы проставились keeperTypeName, и не рассыпались на model changes, приходящих до "init"

    acc.siegedata = SiegeData()
    acc.siegedata.init( None ) # чтобы проставились keeperTypeName, и не рассыпались на model changes, приходящих до "init"

    reply = ws_get( "sn_login", **kwargs ) 
    if reply.get('ok', -1) != 1:
        print "--- failed reply:", reply
    assert( reply.get('ok', -1) == 1 )
    
    AUID = reply.get('auid')
    WS_SERVER = reply.get('server')
    UID = reply.get('uid')
    KEY = reply.get('key')
    NICK = reply.get('nick')
    SECRET = md5(kwargs.get("sntoken", ""))
    
    acc.auid = AUID
    
    global accs
    accs[ AUID ] = ClassDict( acc=acc, uid=UID, key=KEY, server=WS_SERVER, secret=SECRET )
    
    time.sleep(1.0) # ждем пока доедет ModelData

    # получаем и инициализируем ModelData
    reply = accGet( AUID, "auth" )
    model_init = reply.get("init")
    model_init_changes = [{"init_auth":[["/","init",model_init]]}]
    ModelChangeApplicator.apply( acc, "model", ModelData, model_init_changes)
    
    #print "auth reply: %r" % reply
    acc.chat = ClassDict( reply.get("chat", {}) )

    return acc
    
# ------------------------------------------
def accGet( AUID, action, _reply_ok=1, **kwargs ):
    acc_dict = accs[ AUID ]
    
    reply = ws_get( action, uid=acc_dict.uid, key=acc_dict.key, server=acc_dict.server, secret=acc_dict.secret, **kwargs )
    if reply.get('ok', -1) != _reply_ok:
        print "--- failed reply:", reply
    assert( reply.get('ok', -1) == _reply_ok )
    
    assert( reply.get('sign_ok', -1) == 1 )
    
    ModelChangeApplicator.apply( acc_dict.acc, "model", ModelData, reply.get("ModelData"))
    ModelChangeApplicator.apply( acc_dict.acc, "friendsdata", FriendsData, reply.get("FriendsData"))
    ModelChangeApplicator.apply( acc_dict.acc, "partydata", PartyData, reply.get("PartyData"))
    ModelChangeApplicator.apply( acc_dict.acc, "tamburdata", PartyData, reply.get("PartyData"))
    ModelChangeApplicator.apply( acc_dict.acc, "guilddata", GuildData, reply.get("GuildData"))
    ModelChangeApplicator.apply( acc_dict.acc, "siegedata", SiegeData, reply.get("SiegeData"))
    
    return reply
    
# ------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------

def test_same_nickname():
    print "- test_same_nickname"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    SNUID2 = '730742963'
    SNTOKEN2 = 'CAAB9M8ptmXMBAIKtfPFSss1Gaa11cN0eimrliTosO7kGi22LM7V33OEm4HYrTgChTw6X9CoQtTF6fpuIn61kdlzuWVoX74dsMWfUZAr55dL9tNlnrB8vSo1EIEYFafUZAN4bfkCPZB5Dv1ZBesDLnW7U7lHZBJOGIP9N9v78JwB7AmV7wPXAaN78vfEKmukMZD'
    
    global accs
    accs = {}
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 ) 
    
    assert( len(accs) == 2 )
    AUID1, AUID2 = acc1.auid, acc2.auid
    
    time.sleep( 1.0 )

    try:
        NICK1 = utf8convert( u"hitro" )
        print "NICK1=%r" % NICK1
        reply = accGet( AUID1, "set_nickname", nickname=NICK1 )
        
        NICK2 = utf8convert( u"Hitro" ) 
        print "NICK2=%r" % NICK2
        reply = accGet( AUID2, "set_nickname", _reply_ok=0, nickname=NICK2 )
        
    except:
        catch()

    #--------------------------------------------------------
    reply = accGet( AUID1, "logout" )
    reply = accGet( AUID2, "logout" )
    

# --------------------------------------------------------

def test_set_admin_nick():
    print "- test_set_admin_nick"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    global accs
    accs = {}
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    AUID1 = acc1.auid
    
    time.sleep( 1.0 )

    try:
        NICK1 = "gamemaster"
        print "NICK1=%r" % NICK1
        reply = accGet( AUID1, "set_nickname", nickname=NICK1, _reply_ok=0 )
        
        print "-- admin name rejected ok"
        
    except:
        catch()

    #--------------------------------------------------------
    reply = accGet( AUID1, "logout" )


# --------------------------------------------------------

def test_friend_offline_status():
    print "- test_friend_offline_status"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    SNUID2 = '730742963'
    SNTOKEN2 = 'CAAB9M8ptmXMBAIKtfPFSss1Gaa11cN0eimrliTosO7kGi22LM7V33OEm4HYrTgChTw6X9CoQtTF6fpuIn61kdlzuWVoX74dsMWfUZAr55dL9tNlnrB8vSo1EIEYFafUZAN4bfkCPZB5Dv1ZBesDLnW7U7lHZBJOGIP9N9v78JwB7AmV7wPXAaN78vfEKmukMZD'
    
    global accs
    accs = {}
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 ) 
    
    assert( len(accs) == 2 )
    AUID1, AUID2 = acc1.auid, acc2.auid
    
    time.sleep(1.0)
    
    reply = accGet( AUID1, "logout" )
    reply = accGet( AUID2, "logout" )

    time.sleep(2.0) # пусть оба успеют нормально отвалиться

    # заходим первым, и смотрим на статус друга (должен быть оффлайн)    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    
    try:
        time.sleep(2.0) # пусть друзья успеют прийти, a ModelData загрузиться
    
        #--------------------------------------------------------
        reply = accGet( AUID1, "keepalive" )
        assert( getFriend(acc1, AUID2) )

        info("(auid=%s) offline friend[%s]: %s" % (AUID1, AUID2, prettyFriend(acc1, AUID2)))
        
        assert( getFriend(acc1, AUID2).Status == MM.FriendStatus.NOTINGAME )
        print("-- 2 NOTINGAME/offline ok")
        assert( not getFriend(acc1, AUID2).online )
        
    except:
        catch()
    
    #--------------------------------------------------------
    reply = accGet( AUID1, "logout" )
    
## --------------------------------------------------------
## --------------------------------------------------------

def test_friend_online_status():
    print "- test_friend_online_status"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    SNUID2 = '730742963'
    SNTOKEN2 = 'CAAB9M8ptmXMBAIKtfPFSss1Gaa11cN0eimrliTosO7kGi22LM7V33OEm4HYrTgChTw6X9CoQtTF6fpuIn61kdlzuWVoX74dsMWfUZAr55dL9tNlnrB8vSo1EIEYFafUZAN4bfkCPZB5Dv1ZBesDLnW7U7lHZBJOGIP9N9v78JwB7AmV7wPXAaN78vfEKmukMZD'
    
    global accs
    accs = {}
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    AUID1 = acc1.auid

    time.sleep(1.0)
    reply = accGet( AUID1, "keepalive" )
    
    time.sleep(1.0)
    acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 ) 
    AUID2 = acc2.auid
    
    try:
        time.sleep(2.0) # пусть друзья успеют прийти, a ModelData загрузиться
    
        #--------------------------------------------------------
        reply = accGet( AUID2, "keepalive" )
        assert( getFriend(acc2, AUID1) )

        info("(auid=%s) online friend[%s]: %s" % (AUID2, AUID1, prettyFriend(acc2, AUID1)))
        
        assert( getFriend(acc2, AUID1).Status == MM.FriendStatus.INCASTLE )
        assert( getFriend(acc2, AUID1).online )
        print("-- 1 INCASTLE/online ok")
        
    except:
        catch()
    
    #--------------------------------------------------------
    reply = accGet( AUID1, "logout" )
    reply = accGet( AUID2, "logout" )

## --------------------------------------------------------
## --------------------------------------------------------

def test_friends_online_offline():
    print "- test_friends_online_offline"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    SNUID2 = '730742963'
    SNTOKEN2 = 'CAAB9M8ptmXMBAIKtfPFSss1Gaa11cN0eimrliTosO7kGi22LM7V33OEm4HYrTgChTw6X9CoQtTF6fpuIn61kdlzuWVoX74dsMWfUZAr55dL9tNlnrB8vSo1EIEYFafUZAN4bfkCPZB5Dv1ZBesDLnW7U7lHZBJOGIP9N9v78JwB7AmV7wPXAaN78vfEKmukMZD'
    
    global accs
    accs = {}
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 ) 
    
    assert( len(accs) == 2 )
    AUID1, AUID2 = acc1.auid, acc2.auid

    try:
        time.sleep(2.0) # пусть друзья успеют прийти, a ModelData загрузиться
    
        #--------------------------------------------------------
        reply = accGet( AUID1, "keepalive" )
        assert( getFriend(acc1, AUID2) )

        info("(auid=%s) friend[%s]: %s" % (AUID1, AUID2, prettyFriend(acc1, AUID2)))
        
        try:
            assert( getFriend(acc1, AUID2).Status != MM.FriendStatus.INCASTLE )
            print("-- 2 not INCASTLE ok")
        except:
            catch()
        
        #--------------------------------------------------------
        reply = accGet( AUID2, "keepalive" )
        
        assert( getFriend(acc2, AUID1) )
        info("(auid=%s) friend[%s]: %s" % (AUID2, AUID1, prettyFriend(acc2, AUID1)))
        
        #--------------------------------------------------------
        
        time.sleep(2.0) # пусть статус in_castle успеет прийти
        
        #--------------------------------------------------------
        reply = accGet( AUID1, "keepalive" )
        
        info("(auid=%s) friend[%s]: %s" % (AUID1, AUID2, prettyFriend(acc1, AUID2)))
        assert( getFriend(acc1, AUID2).Status == MM.FriendStatus.INCASTLE )
        print("-- 2 INCASTLE ok")
        
        #--------------------------------------------------------
        reply = accGet( AUID2, "keepalive" )
        
        info("(auid=%s) friend[%s]: %s" % (AUID2, AUID1, prettyFriend(acc2, AUID1)))
        assert( getFriend(acc2, AUID1).Status == MM.FriendStatus.INCASTLE ) 
        print("-- 1 INCASTLE ok")
            
        
        #--------------------------------------------------------
        #~ time.sleep(40.0) # пусть статус in_castle успеет протухнуть
        
        #~ reply = accGet( AUID1, "keepalive" )
        #~ #info("keepalive FriendsData (auid=%s): %s" % (AUID1, acc1.friendsdata.save()))
        
        #~ info("(auid=%s) friend[%s]: %s" % (AUID1, AUID2, prettyFriend(acc1, AUID2)))
        #~ assert( acc1.friendsdata.FriendsKeeper.get(AUID2).Status == MM.FriendStatus.LOADING ) 
        
    except:
        catch()
    
    #--------------------------------------------------------
    reply = accGet( AUID1, "logout" )
    
    #--------------------------------------------------------
    time.sleep(2.0) # даем время разослать model changes
    
    try:
        reply = accGet( AUID2, "keepalive" )
        
        info("(auid=%s) friend[%s]: %s" % (AUID2, AUID1, prettyFriend(acc2, AUID1)))
        assert( acc2.friendsdata.FriendsKeeper.get(AUID1).Status == MM.FriendStatus.NOTINGAME ) 
        print("-- 1 OFFLINE ok")
    except:
        catch()
    
    #--------------------------------------------------------
    reply = accGet( AUID2, "logout" )
    

# ------------------------------------------------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------------------------------------------------

def test_friends_add_remove():
    print "- test_friends_add_remove"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    SNUID2 = '730742963'
    SNTOKEN2 = 'CAAB9M8ptmXMBAIKtfPFSss1Gaa11cN0eimrliTosO7kGi22LM7V33OEm4HYrTgChTw6X9CoQtTF6fpuIn61kdlzuWVoX74dsMWfUZAr55dL9tNlnrB8vSo1EIEYFafUZAN4bfkCPZB5Dv1ZBesDLnW7U7lHZBJOGIP9N9v78JwB7AmV7wPXAaN78vfEKmukMZD'
    
    global accs
    accs = {}
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 ) 
    
    assert( len(accs) == 2 )
    AUID1, AUID2 = acc1.auid, acc2.auid

    try:
        time.sleep(2.0) # пусть друзья успеют прийти, a ModelData загрузиться
        
        #--------------------------------------------------------
        reply = accGet( AUID1, "keepalive" )
        assert( getFriend(acc1, AUID2) )
        print("-- BEFORE REMOVE (auid=%s) friend[%s]: %s, ok" % (AUID1, AUID2, getFriend(acc1, AUID2)))
        
        reply = accGet( AUID2, "keepalive" )
        assert( getFriend(acc2, AUID1) )
        print("-- BEFORE REMOVE (auid=%s) friend[%s]: %s, ok" % (AUID2, AUID1, getFriend(acc2, AUID1)))
        
        time.sleep(1.0) # пусть апдейты in_castle успеют пройти
    except:
        catch()
    
    try:
        ## logLevel( logging.INFO ) # -------------
        
        NICK1 = utf8convert( u"Данила %s" % AUID1 )
        print "NICK1=%r" % NICK1
        reply = accGet( AUID1, "set_nickname", nickname=NICK1 )
        
        NICK2 = utf8convert( u"Данила %s" % AUID2 )
        print "NICK2=%r" % NICK2
        reply = accGet( AUID2, "set_nickname", nickname=NICK2 )
        
        logLevel() 
        
        time.sleep(1.0) # пусть апдейты успеют пройти
        
        #=================================================================================
        reply = accGet( AUID1, "remove_friend", rid=12345, friend_uid=AUID2 )
        
        time.sleep(2.0)

        #--------------------------------------------------------
        reply = accGet( AUID1, "keepalive" )
        assert( getFriend(acc1, AUID2) == None )
        print("-- AFTER REMOVE (auid=%s) friend[%s]: %s, ok" % (AUID1, AUID2, getFriend(acc1, AUID2)))

        #--------------------------------------------------------
        reply = accGet( AUID2, "keepalive" )
        assert( getFriend(acc2, AUID1) == None )
        print("-- AFTER REMOVE (auid=%s) friend[%s]: %s, ok" % (AUID2, AUID1, getFriend(acc2, AUID1)))
                    
        #=================================================================================
        reply = accGet( AUID1, "add_friend", rid=12321, friend_name=NICK2 )
        
        time.sleep(2.0) # пусть апдейты успеют пройти
        
        #--------------------------------------------------------
        reply = accGet( AUID2, "keepalive" )
        
        ##info("acc1.model.Friends.IncomingInvites keys=%s" % acc1.model.Friends.IncomingInvites.keys())
        AUID1_invite_id = 0
        info("acc2.model.Friends.IncomingInvites keys=%s" % acc2.model.Friends.IncomingInvites.keys())
        for invite_id, friend in acc2.model.Friends.IncomingInvites.iteritems():
            friend_dict = {}
            if friend:
                friend_dict = friend.generateJsonDict()
                if friend.person_uid == AUID1:
                    AUID1_invite_id = invite_id
            info("(auid=%s) invite_id=%s, friend=%s, friend_dict=%s" % (AUID2, invite_id, friend, friend_dict))

        #--------------------------------------------------------
        if AUID1_invite_id:
            reply = accGet( AUID2, "accept_friend", rid=12322, friend_id=AUID1_invite_id )
        
        time.sleep(1.0) # пусть апдейты успеют пройти

        #--------------------------------------------------------
        reply = accGet( AUID1, "keepalive" )
        assert( getFriend(acc1, AUID2) )
        print("-- AFTER ADD (auid=%s) friend[%s]: %s, ok" % (AUID1, AUID2, getFriend(acc1, AUID2)))
        print("- AFTER ADD (auid=%s) friend[%s] dict: %s" % (AUID1, AUID2, getFriend(acc1, AUID2).generateJsonDict()))
        
        reply = accGet( AUID2, "keepalive" )
        assert( getFriend(acc2, AUID1) )
        print("-- AFTER ADD (auid=%s) friend[%s]: %s, ok" % (AUID2, AUID1, getFriend(acc2, AUID1)))
        print("- AFTER ADD (auid=%s) friend[%s] dict: %s" % (AUID2, AUID1, getFriend(acc2, AUID1).generateJsonDict()))
        
    except:
        catch()

    ############# для проверки shutdown
    #~ for i in xrange(200):
        #~ reply = accGet( AUID1, "keepalive" )
        #~ reply = accGet( AUID2, "keepalive" )
        #~ time.sleep(0.5) 
    ############# 
    
    #--------------------------------------------------------
    reply = accGet( AUID1, "logout" )
    #--------------------------------------------------------
    reply = accGet( AUID2, "logout" )
    
## ----------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------

def test_friends_remove_add_offline():
    print "- test_friends_remove_add_offline"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    SNUID2 = '730742963'
    SNTOKEN2 = 'CAAB9M8ptmXMBAIKtfPFSss1Gaa11cN0eimrliTosO7kGi22LM7V33OEm4HYrTgChTw6X9CoQtTF6fpuIn61kdlzuWVoX74dsMWfUZAr55dL9tNlnrB8vSo1EIEYFafUZAN4bfkCPZB5Dv1ZBesDLnW7U7lHZBJOGIP9N9v78JwB7AmV7wPXAaN78vfEKmukMZD'
    
    global accs
    accs = {}
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 ) 
    
    assert( len(accs) == 2 )
    AUID1, AUID2 = acc1.auid, acc2.auid

    try:
        time.sleep(2.0) # пусть друзья успеют прийти, a ModelData загрузиться
        
        #--------------------------------------------------------
        reply = accGet( AUID1, "keepalive" )
        assert( getFriend(acc1, AUID2) )
        print("-- BEFORE REMOVE (auid=%s) friend[%s]: %s, ok" % (AUID1, AUID2, getFriend(acc1, AUID2)))
        
        reply = accGet( AUID2, "keepalive" )
        assert( getFriend(acc2, AUID1) )
        print("-- BEFORE REMOVE (auid=%s) friend[%s]: %s, ok" % (AUID2, AUID1, getFriend(acc2, AUID1)))
        
        time.sleep(1.0) # пусть апдейты in_castle успеют пройти
    except:
        catch()
    
    try:
        NICK1 = utf8convert( u"Дан %s" % AUID1 )
        print "NICK1=%r" % NICK1
        reply = accGet( AUID1, "set_nickname", nickname=NICK1 )
        
        NICK2 = utf8convert( u"Дан %s" % AUID2 )  
        print "NICK2=%r" % NICK2
        reply = accGet( AUID2, "set_nickname", nickname=NICK2 )
        
        time.sleep(1.0) # пусть апдейты успеют пройти
        
        #=================================================================================
        reply = accGet( AUID1, "remove_friend", rid=12345, friend_uid=AUID2 )
        
        time.sleep(2.0)

        #--------------------------------------------------------
        reply = accGet( AUID1, "keepalive" )
        assert( getFriend(acc1, AUID2) == None )
        print("-- AFTER REMOVE (auid=%s) friend[%s]: %s, ok" % (AUID1, AUID2, getFriend(acc1, AUID2)))

        #--------------------------------------------------------
        reply = accGet( AUID2, "keepalive" )
        assert( getFriend(acc2, AUID1) == None )
        print("-- AFTER REMOVE (auid=%s) friend[%s]: %s, ok" % (AUID2, AUID1, getFriend(acc2, AUID1)))
                    
        #=================================================================================
        reply = accGet( AUID1, "add_friend", rid=12321, friend_name=NICK2 )
        
        time.sleep(2.0) # пусть апдейты успеют пройти
        
        #--------------------------------------------------------
        reply = accGet( AUID2, "keepalive" )
        
        ##info("acc1.model.Friends.IncomingInvites keys=%s" % acc1.model.Friends.IncomingInvites.keys())
        AUID1_invite_id = 0
        info("acc2.model.Friends.IncomingInvites keys=%s" % acc2.model.Friends.IncomingInvites.keys())
        for invite_id, friend in acc2.model.Friends.IncomingInvites.iteritems():
            friend_dict = {}
            if friend:
                friend_dict = friend.generateJsonDict()
                if friend.person_uid == AUID1:
                    AUID1_invite_id = invite_id
            info("(auid=%s) invite_id=%s, friend=%s, friend_dict=%s" % (AUID2, invite_id, friend, friend_dict))

        #=================================================================================
        reply = accGet( AUID1, "logout" )
        
        time.sleep(2.0) # пусть апдейты успеют пройти
        
        #--------------------------------------------------------
        if AUID1_invite_id:
            reply = accGet( AUID2, "accept_friend", rid=12322, friend_id=AUID1_invite_id )
        
        time.sleep(3.0) # пусть апдейты успеют пройти

        #--------------------------------------------------------
        reply = accGet( AUID2, "keepalive" )
        assert( getFriend(acc2, AUID1) )
        print("-- AFTER ADD (auid=%s) friend[%s]: %s, ok" % (AUID2, AUID1, getFriend(acc2, AUID1)))
        print("- AFTER ADD (auid=%s) friend[%s] dict: %s" % (AUID2, AUID1, getFriend(acc2, AUID1).generateJsonDict()))
        assert( getFriend(acc2, AUID1).Status == MM.FriendStatus.NOTINGAME )
        assert( getFriend(acc2, AUID1).lastLoginTime )
        print("-- AFTER ADD (auid=%s) friend[%s] status/loginTime ok" % (AUID2, AUID1))
        
    except:
        catch()

    #--------------------------------------------------------
    reply = accGet( AUID2, "logout" )

## ----------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------

def test_party_set_fraction():
    print "- test_party_set_fraction"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    SNUID2 = '730742963'
    SNTOKEN2 = 'CAAB9M8ptmXMBAIKtfPFSss1Gaa11cN0eimrliTosO7kGi22LM7V33OEm4HYrTgChTw6X9CoQtTF6fpuIn61kdlzuWVoX74dsMWfUZAr55dL9tNlnrB8vSo1EIEYFafUZAN4bfkCPZB5Dv1ZBesDLnW7U7lHZBJOGIP9N9v78JwB7AmV7wPXAaN78vfEKmukMZD'
    
    global accs
    accs = {}
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 ) 
    
    assert( len(accs) == 2 )
    AUID1, AUID2 = acc1.auid, acc2.auid

    try:
        time.sleep(2.0) # пусть друзья успеют прийти, a ModelData загрузиться
        
        # logLevel( logging.INFO ) # -------------
        
        # пропустим кирпичи model changes от загрузки
        reply = accGet( AUID1, "set_fraction", fraction="B" )
        reply = accGet( AUID2, "set_fraction", fraction="B" )
        
        time.sleep(1.0) # пусть ModelData успеет создаться
        
    except:
        catch()

    logLevel() 
    
    #--------------------------------------------------------
    reply = accGet( AUID1, "logout" )
    reply = accGet( AUID2, "logout" )
    

##----------------------------------------------------------------------------------------------------------------
##----------------------------------------------------------------------------------------------------------------

def test_party_invite( *subtests, **kwargs  ):
    print "- test_party_invite( subtests=%s, kwargs=%s )" % ( str(subtests), str(kwargs) )
    invite_as_enemy = kwargs.get("invite_as_enemy", 0)
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    SNUID2 = '730742963'
    SNTOKEN2 = 'CAAB9M8ptmXMBAIKtfPFSss1Gaa11cN0eimrliTosO7kGi22LM7V33OEm4HYrTgChTw6X9CoQtTF6fpuIn61kdlzuWVoX74dsMWfUZAr55dL9tNlnrB8vSo1EIEYFafUZAN4bfkCPZB5Dv1ZBesDLnW7U7lHZBJOGIP9N9v78JwB7AmV7wPXAaN78vfEKmukMZD'
    
    global accs, acc1, acc2, AUID1, AUID2
    accs = {}
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 ) 
    
    assert( len(accs) == 2 )
    AUID1, AUID2 = acc1.auid, acc2.auid

    try:
        time.sleep(2.0) # пусть друзья успеют прийти, a ModelData загрузиться
        
        # пропустим кирпичи model changes от загрузки
        reply = accGet( AUID1, "keepalive" )
        reply = accGet( AUID2, "keepalive" )
        
        # logLevel( logging.INFO ) # -------------
        
        #---------------------------------------------------------------------------
        # INVITE 
        reply = accGet( AUID1, "party_invite", invite_auid=AUID2, as_enemy=invite_as_enemy )
        time.sleep(1.0) # пусть инвайт дойдет
        
        reply = accGet( AUID1, "keepalive" )
        reply = accGet( AUID2, "keepalive" )
        
        #---------------------------------------------------------------------------
        # у AUID2 должен появиться инвайт в партию
        invite = acc2.friendsdata.invites.get(AUID1)
        info("acc2.friendsdata.invites.get(AUID1) = %s" % invite)
        assert( invite )

        print "-- invite ok"
        
        #---------------------------------------------------------------------------
        # у AUID1 должна появиться временная партия (мастер - AUID1, во временных member-ах AUID2)
        info( "(auid=%s) partydata dict: %s" % (AUID1, pretty(acc1.partydata.generateJsonDict())) )
        PARTY_ID1 = acc1.partydata.party_uid
        assert( acc1.partydata.party_uid )

        master = acc1.partydata.owner
        ## info( "(auid=%s) partydata master_id: %r, member: %r" % (AUID1, master_id, acc1.partydata.PartyMemberKeeper.get(master_id)) )
        assert( master )
        assert( master.person.person_uid == AUID1 )
        assert( master.person.online == True )
        
        assert( len(acc1.partydata.PersonKeeper.keys()) == 2 )
        assert( len(acc1.partydata.PartyMemberKeeper.keys()) == 2 )
        
        master_member = acc1.partydata.findMemberByUid( AUID1 )
        assert( master_member.isPending == False )
        invited = acc1.partydata.findMemberByUid( AUID2 )
        assert( invited.isPending == True )
        assert( invited.person.person_uid == AUID2 )
        assert( invited.person.online == True )
        
        print "-- temp party ok"

        # ---------------------
        for sub in subtests:
            sub()
        
    except:
        catch()

    logLevel() 

    #--------------------------------------------------------
    reply = accGet( AUID1, "logout" )

    time.sleep(4.0) # пусть дойдет _вся_ инфа насчет logout/expire (+1 сек после логаута на WS; +1 сек после disband на PTS, чтобы убилась партия)
    try:
        reply = accGet( AUID2, "keepalive" )
        assert( acc2.partydata.party_uid == 0 ) # партия полностью прибита
        print "-- party expired ok" 
    except:
        catch()
    
    #--------------------------------------------------------
    reply = accGet( AUID2, "logout" )

## ----------------------------------------------------------------------------------

def subtest_party_accept():
    reply = accGet( AUID2, "party_accept", master_auid=AUID1 )
    time.sleep(1.0) # пусть дойдет
    
    reply = accGet( AUID1, "keepalive" )
    reply = accGet( AUID2, "keepalive" )
    
    #---------------------------------------------------------------------------
    # у AUID1 теперь постоянная партия (мастер - AUID1, постоянный member AUID2)
    assert( acc1.partydata.party_uid )

    master = acc1.partydata.owner
    ## info( "(auid=%s) partydata master_id: %r, member: %r" % (AUID1, master_id, acc1.partydata.PartyMemberKeeper.get(master_id)) )
    assert( master )
    assert( master.person.person_uid == AUID1 )
    assert( master.person.online == True )
    
    assert( len(acc1.partydata.PersonKeeper.keys()) == 2 )
    assert( len(acc1.partydata.PartyMemberKeeper.keys()) == 2 )
    
    master_member = acc1.partydata.findMemberByUid( AUID1 )
    assert( master_member.isPending == False )
    invited = acc1.partydata.findMemberByUid( AUID2 )
    assert( invited.isPending == False )
    assert( invited.person.person_uid == AUID2 )
    assert( invited.person.online == True )
    
    print "-- (auid=%s) party ok" % AUID1
    
    #---------------------------------------------------------------------------
    # у AUID2 тоже постоянная партия (мастер - AUID1, постоянный member AUID2)
    assert( acc2.partydata.party_uid )

    master = acc2.partydata.owner
    ## info( "(auid=%s) partydata master_id: %r, member: %r" % (AUID1, master_id, acc1.partydata.PartyMemberKeeper.get(master_id)) )
    assert( master )
    assert( master.person.person_uid == AUID1 )
    
    assert( len(acc2.partydata.PersonKeeper.keys()) == 2 )
    assert( len(acc2.partydata.PartyMemberKeeper.keys()) == 2 )
    
    master_member = acc2.partydata.findMemberByUid( AUID1 )
    assert( master_member.isPending == False )
    invited = acc2.partydata.findMemberByUid( AUID2 )
    assert( invited.isPending == False )
    
    print "-- (auid=%s) party ok" % AUID2

## ----------------------------------------------------------------------------------

def subtest_party_decline():
    reply = accGet( AUID2, "party_decline", master_auid=AUID1 )
    
    time.sleep(3.0) # пусть дойдет отказ, и пусть временная партия успеет протухнуть на PTS
    
    reply = accGet( AUID1, "keepalive" )
    reply = accGet( AUID2, "keepalive" )
    
    #---------------------------------------------------------------------------
    # у acc2 больше нет инвайта
    invite = acc2.friendsdata.invites.get(AUID1)
    info("acc2.friendsdata.invites.get(AUID1) = %s" % invite)
    assert( not invite )

    print "-- no invite ok"
    
    # ни у кого нет партии
    assert( acc1.partydata.party_uid == 0 )
    assert( acc2.partydata.party_uid == 0 )
    
    print "-- decline: no parties ok"

## ----------------------------------------------------------------------------------

def subtest_party_disband():
    reply = accGet( AUID2, "party_disband", party_id=acc2.partydata.party_uid )
    
    time.sleep(1.0) # пусть дойдет отказ (у AUID2 не должно быть партии)
    reply = accGet( AUID2, "keepalive" )
    assert( acc2.partydata.party_uid == 0 )
    
    time.sleep(2.0) # пусть временная партия успеет протухнуть на PTS
    reply = accGet( AUID1, "keepalive" )
    assert( acc1.partydata.party_uid == 0 )
    
    print "-- disband: no parties ok"
    
## ----------------------------------------------------------------------------------

def subtest_party_kick_invite():
    #logLevel( logging.INFO ) # -------------
    
    reply = accGet( AUID1, "party_kick", kick_auid=AUID2, party_id=acc1.partydata.party_uid )
    
    time.sleep(2.0) # пусть дойдет кик (у AUID2 не должно быть инвайта)
    reply = accGet( AUID2, "keepalive" )
    invite = acc2.friendsdata.invites.get(AUID1)
    info("acc2.friendsdata.invites.get(AUID1) = %s" % invite)
    assert( not invite )
    
    print "-- kick_invite: no invite ok"
    
    time.sleep(2.0) # пусть временная партия успеет протухнуть на PTS
    reply = accGet( AUID1, "keepalive" )
    assert( acc1.partydata.party_uid == 0 )
    
    print "-- kick_invite: no master party ok"
    
## ----------------------------------------------------------------------------------

def subtest_party_kick_member():
    #logLevel( logging.INFO ) # -------------
    
    reply = accGet( AUID1, "party_kick", kick_auid=AUID2, party_id=acc1.partydata.party_uid )
    
    time.sleep(1.0) # пусть дойдет кик (у AUID2 не должно быть партии)
    reply = accGet( AUID2, "keepalive" )
    assert( acc2.partydata.party_uid == 0 )
    
    print "-- kick_member: no kicked party ok"
    
    time.sleep(2.0) # пусть временная партия успеет протухнуть на PTS
    reply = accGet( AUID1, "keepalive" )
    assert( acc1.partydata.party_uid == 0 )
    
    print "-- kick_invite: no master party ok"


## ----------------------------------------------------------------------------------

def subtest_party_dodge():
    #logLevel( logging.INFO ) # -------------
    
    reply = accGet( AUID1, "add_dodges", dodges=1 )
    time.sleep(1.5) # пусть дойдут изменения про додж
    
    reply = accGet( AUID1, "keepalive" )
    dodge_member = acc1.partydata.findMemberByUid( AUID1 )
    assert( dodge_member.banEndTime )
    
    print "-- (auid=%s) dodge_member: banEndTime ok" % AUID1
    
    reply = accGet( AUID2, "keepalive" )
    dodge_member = acc2.partydata.findMemberByUid( AUID1 )
    assert( dodge_member.banEndTime )
    
    print "-- (auid=%s) dodge_member: banEndTime ok" % AUID2

    # -------------------------
    reply = accGet( AUID1, "add_dodges", dodges=0 ) # clear all dodges (апдейт party_dodge при этом почему-то НЕ рассылается)
    reply = accGet( AUID1, "party_dodge", party_id=acc1.partydata.party_uid ) # вот это событие вызовет апдейт party_dodge, с уже обнуленным banEndTime
    time.sleep(1.5) # пусть дойдут изменения про додж
    
    reply = accGet( AUID1, "keepalive" )
    dodge_member = acc1.partydata.findMemberByUid( AUID1 )
    assert( dodge_member.banEndTime == 0)
    
    print "-- (auid=%s) dodge_member: banEndTime==0 ok" % AUID1
    
    reply = accGet( AUID2, "keepalive" )
    dodge_member = acc2.partydata.findMemberByUid( AUID1 )
    assert( dodge_member.banEndTime == 0)
    
    print "-- (auid=%s) dodge_member: banEndTime==0 ok" % AUID2
    
## ----------------------------------------------------------------------------------

def subtest_party_go():
    # logLevel( logging.INFO ) # -------------

    reply = accGet( AUID1, "party_go", party_id=acc1.partydata.party_uid, game_type="train", is_fixed_match=0 )
    time.sleep(1.5) # пусть дойдут изменения 
    
    # -------------
    # ММ должен стартовать
    reply = accGet( AUID1, "keepalive" )
    assert( acc1.partydata.InMatchmaking ) # 
    member1 = acc1.partydata.findMemberByUid( AUID1 )
    assert( member1.person.InMatchmaking  ) 
    member2 = acc1.partydata.findMemberByUid( AUID2 )
    assert( member2.person.InMatchmaking  ) 

    reply = accGet( AUID2, "keepalive" )
    assert( acc2.partydata.InMatchmaking )
    member1 = acc2.partydata.findMemberByUid( AUID1 )
    assert( member1.person.InMatchmaking  ) 
    member2 = acc2.partydata.findMemberByUid( AUID2 )
    assert( member2.person.InMatchmaking  ) 
    
    print "-- party InMatchmaking ok"
    

def subtest_party_go_fixed():
    # logLevel( logging.INFO ) # -------------

    reply = accGet( AUID1, "party_go", party_id=acc1.partydata.party_uid, game_type="/Maps/Multiplayer/CTE/Test_PVP_1x1.ADMPDSCR", is_fixed_match=1 )
    time.sleep(1.5) # пусть дойдут изменения 
    
    # -------------
    # ММ должен стартовать
    reply = accGet( AUID1, "keepalive" )
    assert( acc1.partydata.InMatchmaking ) # 
    member1 = acc1.partydata.findMemberByUid( AUID1 )
    assert( member1.person.InMatchmaking  ) 
    member2 = acc1.partydata.findMemberByUid( AUID2 )
    assert( member2.person.InMatchmaking  ) 

    reply = accGet( AUID2, "keepalive" )
    assert( acc2.partydata.InMatchmaking )
    member1 = acc2.partydata.findMemberByUid( AUID1 )
    assert( member1.person.InMatchmaking  ) 
    member2 = acc2.partydata.findMemberByUid( AUID2 )
    assert( member2.person.InMatchmaking  ) 
    
    print "-- party InMatchmaking ok"


## ----------------------------------------------------------------------------------
def subtest_party_heroes():
    #logLevel( logging.INFO ) 

    # -------------
    hero_keys = sorted( acc1.model.HeroesKeeper.keys() )
    hero_id1 = hero_keys[0]
    hero1 = acc1.model.HeroesKeeper.get( hero_id1 )
    reply = accGet( AUID1, "party_hero", party_id=acc1.partydata.party_uid, hero_id=hero_id1, hero_crc=hero1.PersistentId )
    
    # ---------------
    hero_keys = sorted( acc2.model.HeroesKeeper.keys() )
    hero_id2 = hero_keys[1]
    hero2 = acc2.model.HeroesKeeper.get( hero_id2 )
    reply = accGet( AUID2, "party_hero", party_id=acc2.partydata.party_uid, hero_id=hero_id2, hero_crc=hero2.PersistentId )
    
    time.sleep(1.5) # пусть дойдут изменения 
    
    # -------------
    # проверим, что герои выбрались
    reply = accGet( AUID1, "keepalive" )
    
    party_member1 = acc1.partydata.findMemberByUid( AUID1 )
    assert( party_member1.isValidTS )
    assert( party_member1.hero_id == hero_id1 )
    assert( party_member1.heroClassId == hero1.PersistentId )
    
    party_member2 = acc1.partydata.findMemberByUid( AUID2 )
    assert( party_member2.isValidTS )
    assert( party_member2.hero_id == hero_id2 )
    assert( party_member2.heroClassId == hero2.PersistentId )
    
    print "-- (auid=%s) heroes chosen ok" % AUID1
    
    # -------------
    reply = accGet( AUID2, "keepalive" )
    
    party_member1 = acc2.partydata.findMemberByUid( AUID1 )
    assert( party_member1.isValidTS )
    assert( party_member1.hero_id == hero_id1 )
    assert( party_member1.heroClassId == hero1.PersistentId )
    
    party_member2 = acc2.partydata.findMemberByUid( AUID2 )
    assert( party_member2.isValidTS )
    assert( party_member2.hero_id == hero_id2 )
    assert( party_member2.heroClassId == hero2.PersistentId )
    
    print "-- (auid=%s) heroes chosen ok" % AUID2
    


def subtest_party_enemy_heroes():
    #logLevel( logging.INFO ) 

    # -------------
    hero_keys = sorted( acc1.model.HeroesKeeper.keys() )
    hero_id1 = hero_keys[0]
    hero1 = acc1.model.HeroesKeeper.get( hero_id1 )
    reply = accGet( AUID1, "party_hero", party_id=acc1.partydata.party_uid, hero_id=hero_id1, hero_crc=hero1.PersistentId )
    
    # ---------------
    hero_keys = sorted( acc2.model.HeroesKeeper.keys() )
    hero_id2 = hero_keys[1]
    hero2 = acc2.model.HeroesKeeper.get( hero_id2 )
    reply = accGet( AUID2, "party_hero", party_id=acc2.partydata.party_uid, hero_id=hero_id2, hero_crc=hero2.PersistentId )
    
    time.sleep(1.5) # пусть дойдут изменения 
    
    # -------------
    # проверим, что герои выбрались
    reply = accGet( AUID1, "keepalive" )
    
    party_member1 = acc1.partydata.findMemberByUid( AUID1 )
    assert( party_member1.isValidTS )
    assert( party_member1.hero_id == hero_id1 )
    assert( party_member1.heroClassId == hero1.PersistentId )
    
    party_member2 = acc1.partydata.findMemberByUid( AUID2 )
    # для "врага" мы должны видеть только флаг isHeroChosen, а сам герой должен быть не виден
    assert( party_member2.isHeroChosen == True )
    assert( party_member2.isValidTS == False )
    assert( party_member2.hero_id == 0 )
    assert( party_member2.heroClassId == 0 )
    
    print "-- (auid=%s) heroes chosen ok" % AUID1
    
    # -------------
    reply = accGet( AUID2, "keepalive" )
    
    party_member1 = acc2.partydata.findMemberByUid( AUID1 )
    # для "врага" мы должны видеть только флаг isHeroChosen, а сам герой должен быть не виден
    assert( party_member1.isHeroChosen == True )
    assert( party_member1.isValidTS == False )
    assert( party_member1.hero_id == 0 )
    assert( party_member1.heroClassId == 0 )
    
    party_member2 = acc2.partydata.findMemberByUid( AUID2 )
    assert( party_member2.isValidTS )
    assert( party_member2.hero_id == hero_id2 )
    assert( party_member2.heroClassId == hero2.PersistentId )
    
    print "-- (auid=%s) heroes chosen ok" % AUID2

## ----------------------------------------------------------------------------------
def subtest_party_relogin():
    print "- subtest_party_relogin"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    global accs
    
    #logLevel( logging.INFO ) 
    
    acc_dict = accs[ AUID1 ]
    acc1 = accLogin( snid="fb", snuid=SNUID1, sntoken=SNTOKEN1, key=acc_dict.key, server=acc_dict.server ) 
    
    time.sleep(2.0)
    
    reply = accGet( AUID1, "keepalive" )
    print "-- relogin PartyData: %s" % reply.get("PartyData")
    assert( reply.get("PartyData") )
    
    print "-- party_relogin: PartyData received ok" 
    
## ----------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------

def test_client_ping():
    print "- test_client_ping"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    global accs
    accs = {}
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    AUID1 = acc1.auid

    try:
        reply = accGet( AUID1, "refresh_ping_results", pingName="ru0", pingTime=42 )
        print "- pings sent ok"
    except:
        catch()
        
    #--------------------------------------------------------
    reply = accGet( AUID1, "logout" )

## ----------------------------------------------------------------------------------

def test_mm_ping():
    print "- test_mm_ping"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    global accs
    accs = {}
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    AUID1 = acc1.auid

    time.sleep(2.0)
    
    try:
        reply = accGet( AUID1, "mm_ping", _reply_ok=0 )
        print "- mm_ping sent ok"
    except:
        catch()
        
    #--------------------------------------------------------
    reply = accGet( AUID1, "logout" )

## ----------------------------------------------------------------------------------

# на текущем сервере не будет работать, т.к. set_nickname не разрешит квадратные скобки в нике 
def __test_square_nicks():
    print "- test_square_nicks"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    SNUID2 = '730742963'
    SNTOKEN2 = 'CAAB9M8ptmXMBAIKtfPFSss1Gaa11cN0eimrliTosO7kGi22LM7V33OEm4HYrTgChTw6X9CoQtTF6fpuIn61kdlzuWVoX74dsMWfUZAr55dL9tNlnrB8vSo1EIEYFafUZAN4bfkCPZB5Dv1ZBesDLnW7U7lHZBJOGIP9N9v78JwB7AmV7wPXAaN78vfEKmukMZD'
    
    global accs
    accs = {}
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 ) 
    
    time.sleep(2.0) # пусть пройдет апдейт
    
    assert( len(accs) == 2 )
    AUID1, AUID2 = acc1.auid, acc2.auid

    ##logLevel( logging.INFO ) 
    
    NICK1_UNCONVERTED = u"Da[n]"
    NICK1_CONVERTED = "Dan"
    
    NICK2_UNCONVERTED = u"[D[a[n]"
    NICK2_CONVERTED = "Dan%s" % AUID2
    
    try:
        NICK1 = utf8convert( NICK1_UNCONVERTED )
        print "NICK1=%r" % NICK1
        reply = accGet( AUID1, "set_nickname", nickname=NICK1 )
        
        NICK2 = utf8convert( NICK2_UNCONVERTED )  # после выкидывания кв.скобок ники станут совпадать
        print "NICK2=%r" % NICK2
        reply = accGet( AUID2, "set_nickname", nickname=NICK2 )
        
        time.sleep(1.0) # пусть апдейты успеют пройти
    except:
        catch()
        
    #--------------------------------------------------------
    reply = accGet( AUID1, "logout" )
    reply = accGet( AUID2, "logout" )

    time.sleep(2.0) # пусть пройдет logout

    #------------------------------------------------------------------------------------
    # при следующей загрузке должна пройти насильная конверсия кв.скобок
    ##logLevel( logging.INFO ) ######## посмотрим, что вернут на keepalive
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    
    time.sleep(2.0) # пусть пройдет login со сменой ника и апдейтом в аггрегатор
    
    acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 ) 

    time.sleep(1.0)
    #------------------------------------------------------------------------------------
    try:
        reply = accGet( AUID1, "keepalive" )
        reply = accGet( AUID2, "keepalive" )
        
        # проверяем, что обоим аккаунтам пришли апдейты FriendsData с отконвертированными никами
        f11 = getFriend(acc1, AUID1)
        f12 = getFriend(acc1, AUID2)
        f21 = getFriend(acc2, AUID1)
        f22 = getFriend(acc2, AUID2)
        
        assert(f11.nickName == NICK1_CONVERTED)
        assert(f12.nickName == NICK2_CONVERTED)
        assert(f21.nickName == NICK1_CONVERTED)
        assert(f22.nickName == NICK2_CONVERTED)
        
        print "- nicks converted ok"
        
    except:
        catch()
        print("f11.nickName=%s, f12.nickName=%s, f21.nickName=%s, f22.nickName=%s" % (f11.nickName, f12.nickName, f21.nickName, f22.nickName))
            
    #------------------------------------------------------------------------------------
    logLevel()
    reply = accGet( AUID1, "logout" )
    reply = accGet( AUID2, "logout" )

## ----------------------------------------------------------------------------------

def test_chat_msg():
    print "- test_chat_msg"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    ##SNUID2 = '730742963'
    ##SNTOKEN2 = 'CAAB9M8ptmXMBAIKtfPFSss1Gaa11cN0eimrliTosO7kGi22LM7V33OEm4HYrTgChTw6X9CoQtTF6fpuIn61kdlzuWVoX74dsMWfUZAr55dL9tNlnrB8vSo1EIEYFafUZAN4bfkCPZB5Dv1ZBesDLnW7U7lHZBJOGIP9N9v78JwB7AmV7wPXAaN78vfEKmukMZD'
    
    global accs
    accs = {}
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    ##acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 ) 
    
    ##assert( len(accs) == 2 )
    ##AUID1, AUID2 = acc1.auid, acc2.auid
    AUID1 = acc1.auid
    
    
    try:
        reply = accGet( AUID1, "keepalive" )
        time.sleep( 1.0 )
        
        logLevel( logging.INFO )
        
        reply = ws_get( "lping", server=acc1.chat.host, auid=AUID1, key=acc1.chat.key )
        assert( reply.get("ec", -1) == 0 )
        time.sleep( 1.0 )
        
        #------------------------------------------------------------------------------------
        chat_message = "PRIVMSG #globalRU1 : Hello auid %d" % AUID1
        encoded_message = base64.urlsafe_b64encode(chat_message)
        reply = ws_get( "send", server=acc1.chat.host, auid=AUID1, key=acc1.chat.key, chat=encoded_message )
        assert( reply.get("ec", -1) == 0 )

        #chat_message = "PRIVMSG #globalRU1 : Holy nigger motherfucking shit!"
        chat_message = utf8convert( u"PRIVMSG #globalRU1 : Ах ты ж ебаный ты нахуй!" )
        encoded_message = base64.urlsafe_b64encode(chat_message)
        reply = ws_get( "send", server=acc1.chat.host, auid=AUID1, key=acc1.chat.key, chat=encoded_message )
        assert( reply.get("ec", -1) == 0 )
        # http://pw.nivalnetwork.com:88/chat0?action=send&auid=5&key=eb6977bbe6565800&chat=UFJJVk1TRyAjZ2xvYmFsUlUxIDrQv9GA0LjQstC10YI%3D 
        
        time.sleep( 3.0 )
        
        reply = ws_get( "lping", server=acc1.chat.host, auid=AUID1, key=acc1.chat.key )
        assert( reply.get("ec", -1) == 0 )
        chat_messages = base64.b64decode( reply.get("chat") )
        if chat_messages:
            info( "decoded chat messages:\n%s" % chat_messages )
    except:
        catch()
    
    #------------------------------------------------------------------------------------
    logLevel()
    reply = accGet( AUID1, "logout" )
    ## reply = accGet( AUID2, "logout" )

## ----------------------------------------------------------------------------------

def test_mm_spectate():
    print "- test_mm_spectate"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    SNUID2 = '730742963'
    SNTOKEN2 = 'CAAB9M8ptmXMBAIKtfPFSss1Gaa11cN0eimrliTosO7kGi22LM7V33OEm4HYrTgChTw6X9CoQtTF6fpuIn61kdlzuWVoX74dsMWfUZAr55dL9tNlnrB8vSo1EIEYFafUZAN4bfkCPZB5Dv1ZBesDLnW7U7lHZBJOGIP9N9v78JwB7AmV7wPXAaN78vfEKmukMZD'
    
    global accs
    accs = {}
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 ) 
    
    time.sleep(2.0) # пусть пройдет апдейт
    
    assert( len(accs) == 2 )
    AUID1, AUID2 = acc1.auid, acc2.auid

    NICK2 = "Dan%s" % AUID2
    
    try:
        NICK2 = utf8convert( NICK2 ) 
        print "NICK2=%r" % NICK2
        reply = accGet( AUID2, "set_nickname", nickname=NICK2 )
        time.sleep( 1.0 )
        
        reply = accGet( AUID1, "keepalive" )
        
        # logLevel( logging.INFO ) 
        
        reply = accGet( AUID1, "mm_spectate", nickname=NICK2 )
        time.sleep( 1.0 )
        MMID1 = reply.get("mmid")
        
        for i in xrange(3):
            reply = accGet( AUID1, "mm_ping" )
            time.sleep( 3.0 )
            
        reply = accGet( AUID1, "mm_cancel", mmid=MMID1 )
                    
    except:
        catch()
    
    #------------------------------------------------------------------------------------
    logLevel()
    reply = accGet( AUID1, "logout" )
    reply = accGet( AUID2, "logout" )

## ----------------------------------------------------------------------------------

def test_admin_change_acc():
    print "- test_admin_change_acc"
    
    SNUID1 = '100006274567752'
    SNTOKEN1 = 'CAAB9M8ptmXMBAKaMuMJTO6mP8pICVcTpVXLRoX8V4hsrWGtZBZA4pSkBPkywfUqxsnZBdq19kGDLvzmGtBPwdEsDKSqnTnp7kc5yoomXtAmouVa7m6p9SYRXCdxhgtuCcV1nY4N62HkmGSlTjWsOp8mY2RHAZCthZAWQPPwQnGjQ7com7QZAnz'
    
    SNUID2 = '730742963'
    SNTOKEN2 = 'CAAB9M8ptmXMBAIKtfPFSss1Gaa11cN0eimrliTosO7kGi22LM7V33OEm4HYrTgChTw6X9CoQtTF6fpuIn61kdlzuWVoX74dsMWfUZAr55dL9tNlnrB8vSo1EIEYFafUZAN4bfkCPZB5Dv1ZBesDLnW7U7lHZBJOGIP9N9v78JwB7AmV7wPXAaN78vfEKmukMZD'
    
    global accs
    accs = {}
    
    acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 ) 
    acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 ) 
    
    assert( len(accs) == 2 )
    AUID1, AUID2 = acc1.auid, acc2.auid
    
    try:
        # logLevel( logging.INFO )
        reply = accGet( AUID1, "change_user_acc", acc_auid=AUID2, acc_path="model/ModelData/NullKey", json_value="null" )
        reply = accGet( AUID1, "change_user_acc", acc_auid=AUID2, acc_path="model/ModelData/IntKey", json_value="12345" )
        reply = accGet( AUID1, "change_user_acc", acc_auid=AUID2, acc_path="model/ModelData/DictKey", json_value='{"123":123}' )
        
        txt = utf8convert(u'Русский текст') 
        info("txt: %r (class %r)" % (txt, txt.__class__.__name__))
        reply = accGet( AUID1, "change_user_acc", acc_auid=AUID2, acc_path="model/ModelData/StringKey", string_value=txt )
        
    except:
        catch()
    
    #------------------------------------------------------------------------------------
    logLevel()
    reply = accGet( AUID1, "logout" )
    reply = accGet( AUID2, "logout" )
    

## ----------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------

#~ DEFAULT_LOG_LEVEL = logging.INFO
DEFAULT_LOG_LEVEL = logging.WARNING
logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )

## ----------------------------------------------------------------------------------

#~ test_party_set_fraction() ### для первого запуска на пустом деплое: нужно выбрать сторону 
#~ time.sleep(1.0)

test_chat_msg()
time.sleep(2.0)

test_same_nickname()
time.sleep(2.0)

test_friends_add_remove()
time.sleep(2.0)

test_friends_remove_add_offline()
time.sleep(2.0)

test_friend_offline_status()
time.sleep(2.0)
test_friend_online_status()
time.sleep(2.0)
test_friends_online_offline()
time.sleep(2.0)

test_party_invite( subtest_party_kick_invite )
time.sleep(2.0)
test_party_invite( subtest_party_accept, subtest_party_kick_member )
time.sleep(2.0)
test_party_invite( subtest_party_decline )
time.sleep(2.0)
test_party_invite( subtest_party_accept, subtest_party_dodge )
time.sleep(2.0)
test_party_invite( subtest_party_accept, subtest_party_relogin )
time.sleep(2.0)

test_party_invite( subtest_party_accept, subtest_party_heroes, subtest_party_go )
time.sleep(2.0)

test_party_invite( subtest_party_accept, subtest_party_enemy_heroes, subtest_party_go_fixed, invite_as_enemy=1 )
time.sleep(2.0)

test_client_ping()
time.sleep(2.0)

test_mm_ping()
time.sleep(2.0)

##test_square_nicks()
##time.sleep(2.0)

test_admin_change_acc()
time.sleep(2.0)

test_set_admin_nick()
time.sleep(2.0)

test_mm_spectate()
time.sleep(2.0)
