# -*- coding: utf-8 -*-
# сценарии для работы с партиями
import sys, time, os, hashlib, random
import fsm
import transport 
import context

#from logs import log
import logging, datetime
from logging import debug, info, warning, error

from main_fsm import * 
from load_fsm import * 

import party_context
from party_fsm import *
            
from fsm import PASSED_STATUS_OK, PASSED_STATUS_FAIL

# --------------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------

def set_geolocation(channel, args):
    sys.path.append('../../cfg')
    from geo_cfg import GEO_LOCATIONS

    check_args = dict(snid=args.snid, snuid=args.snuid, sntoken=args.sntoken, geolocation=args.geolocation)
    for argname, arg in check_args.iteritems():
        if not arg:
            error("MISSING parameter, must be valid --%s=<%s>" % (argname, argname))
            exit(1)
    if args.geolocation not in GEO_LOCATIONS:
        error("BAD geolocation, should be one of %s" % GEO_LOCATIONS)
        exit(1)
        
    fsms = []
    
    proxy = transport.JsonChannel(channel)
    ctx = context.UserContext(proxy, args.snuid, version=args.version)
    
    fsm = LoginFSM( ctx, args.snuid, args.sntoken, loginType=args.snid ) \
        + CheckAuthFSM( ctx ) \
        + SetGeolocationFSM( ctx, args.geolocation ) \
        + LogoutFSM( ctx )

    fsms.append(fsm)
    return fsms

