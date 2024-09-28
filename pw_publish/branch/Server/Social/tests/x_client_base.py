# -*- coding: utf-8 -*-

import socket, ssl, pprint, time, sys, os
import hashlib
import urllib2
import random
import logging

#os.chdir('..')
sys.path.append('..')
sys.path.append('../cfg')

from base.helpers import *

from friendsdata.FriendsData import FriendsData
from party.PartyData import PartyData
from modeldata.ModelData import ModelData
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from modeldata.change_applicator import ModelChangeApplicator

import EC
import MM

# --------------------------------------------------------------
#~ DEFAULT_LOG_LEVEL = logging.INFO
DEFAULT_LOG_LEVEL = logging.WARNING
# --------------------------------------------------------------

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

accs = {}

## --------------------------------------------------------------------------------------------------------------------------

def get( method, server=X_ANY_SERVER, **kwargs ):
    secret = kwargs.pop("secret", "")
    params = dict( **kwargs )
    params["method"] = method
    req = makeSignedRequest( params, secret=secret )

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

def accNew():
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
    
    return acc

##----------------------------------------------------------------------------------------------------------------
def accLogin( **kwargs ):
    acc = accNew()

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
    
    return acc
    
# ------------------------------------------
def accApplyModelChangesAll( acc, reply ):
    ModelChangeApplicator.apply( acc, "model", ModelData, reply.get("ModelData"))
    ModelChangeApplicator.apply( acc, "friendsdata", FriendsData, reply.get("FriendsData"))
    ModelChangeApplicator.apply( acc, "partydata", PartyData, reply.get("PartyData"))
    ModelChangeApplicator.apply( acc, "tamburdata", PartyData, reply.get("TamburData"))
    ModelChangeApplicator.apply( acc, "guilddata", GuildData, reply.get("GuildData"))
    ModelChangeApplicator.apply( acc, "siegedata", SiegeData, reply.get("SiegeData"))
    
def accApplyModelChangesTag( acc, reply, model_change_tag="" ):
    if model_change_tag == "ModelData":
        ModelChangeApplicator.apply( acc, "model", ModelData, reply.get("ModelData"))
        return acc.model
    elif model_change_tag == "FriendsData":
        ModelChangeApplicator.apply( acc, "friendsdata", FriendsData, reply.get("FriendsData"))
        return acc.friendsdata
    elif model_change_tag == "PartyData":
        ModelChangeApplicator.apply( acc, "partydata", PartyData, reply.get("PartyData"))
        return acc.partydata
    elif model_change_tag == "TamburData":
        ModelChangeApplicator.apply( acc, "tamburdata", PartyData, reply.get("TamburData"))
        return acc.tamburdata
    elif model_change_tag == "GuildData":
        ModelChangeApplicator.apply( acc, "guilddata", GuildData, reply.get("GuildData"))
        return acc.guilddata
    elif model_change_tag == "SiegeData":
        ModelChangeApplicator.apply( acc, "siegedata", SiegeData, reply.get("SiegeData"))
        return acc.siegedata

# ------------------------------------------
def accGet( AUID, action, _reply_ok=1, **kwargs ):
    acc_dict = accs[ AUID ]
    
    reply = ws_get( action, uid=acc_dict.uid, key=acc_dict.key, server=acc_dict.server, secret=acc_dict.secret, **kwargs )
    if reply.get('ok', -1) != _reply_ok:
        print "--- failed reply:", reply
    assert( reply.get('ok', -1) == _reply_ok )
    
    accApplyModelChangesAll( acc_dict.acc, reply )
    
    return reply
    
