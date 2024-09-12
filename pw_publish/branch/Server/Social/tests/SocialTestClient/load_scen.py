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

sys.path.append('../../')
import MM

from base.helpers import *

# --------------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------

def cyclic_login_logout(channel, args):
    clients = [
        ('yozeg',   'a6ec1ce7e89895b6fd594038bdcc5b98', 'faceless', 'A'),
        ('clarice', '51d3790e2ddc683cc3dfa4f9f625355a', 'firefox', 'B'),
        ('TestZ1',  'f5bb0c8de146c67b44babbf4e6584cc0', 'faceless', 'A'),
        ('TestZ2',  'f5bb0c8de146c67b44babbf4e6584cc0', 'faceless', 'B'),
        ('TestZ3',  'f5bb0c8de146c67b44babbf4e6584cc0', 'faceless', 'A'),
        ('TestZ4',  'f5bb0c8de146c67b44babbf4e6584cc0', 'faceless', 'B'),
    ]
    fsms = []
    tag =""
    for user, password, hero, fraction in clients:
        proxy = transport.JsonChannel(channel)
        ctx = context.UserContext(proxy, tag, args.testkeypass, version=args.version)
        fsm = Cyclic_LoginLogoutFSM(ctx, user, password)
        fsms.append(fsm)
    return fsms

# --------------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------

def inc_save( channel, args):
    client_params = [
        ('TestZ1',  'f5bb0c8de146c67b44babbf4e6584cc0', 'faceless', 'A'),
        ('TestZ2',  'f5bb0c8de146c67b44babbf4e6584cc0', 'faceless', 'B'),
        ('TestZ3',  'f5bb0c8de146c67b44babbf4e6584cc0', 'faceless', 'A'),
        ('TestZ4',  'f5bb0c8de146c67b44babbf4e6584cc0', 'faceless', 'B'),
        ('TestZ5',  'f5bb0c8de146c67b44babbf4e6584cc0', 'faceless', 'A'),
        ('TestZ6',  'f5bb0c8de146c67b44babbf4e6584cc0', 'faceless', 'B'),
        ('TestZ7',  'f5bb0c8de146c67b44babbf4e6584cc0', 'faceless', 'A'),
        ('TestZ8',  'f5bb0c8de146c67b44babbf4e6584cc0', 'faceless', 'B'),
        ('TestZ9',  'f5bb0c8de146c67b44babbf4e6584cc0', 'faceless', 'A'),
        ('TestZ10', 'f5bb0c8de146c67b44babbf4e6584cc0', 'faceless', 'B'),
    ]
    
    assert args.clients in range( 1, len(client_params)+1 ), "this scenario works only with --clients=1..%d" % len(client_params)
    fsms = []
    
    # добавляем клиентов
    for i in xrange(args.clients):
        user, password, hero, fraction = client_params[i]
        run_count = random.randint(1,args.inc_save_count)
        
        tag = "Client%d" % i
        warning( "ADD %s -- run_count %d" % (tag, run_count) )
        
        proxy = transport.JsonChannel(channel)
        ctx = context.UserContext(proxy, tag, args.testkeypass, version=args.version)
        
        fsm = LoginHashFSM(ctx, user, password) \
            + IncSaveCounterFSM(ctx, run_count=run_count, timeoutFail=args.inc_save_count*2.0) \
            + LogoutFSM(ctx) \
            + TimeoutWaitFSM(ctx, 5.0) \
            + LoginHashFSM(ctx, user, password) \
            + CheckSaveCounterFSM(ctx, fraction=fraction) \
            + IncSaveCounterFSM(ctx, run_count=run_count, timeoutFail=args.inc_save_count*2.0) \
            + LogoutFSM(ctx) \
            + TimeoutWaitFSM(ctx, 5.0) \
            + LoginHashFSM(ctx, user, password) \
            + CheckSaveCounterFSM(ctx) \
            + LogoutFSM(ctx)
            
        fsms.append(fsm)
        
    return fsms
    
    
# --------------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------

def load_login_keepalive(channel, args):
    fsms = []
    
    # добавляем клиентов
    for i in xrange(args.clients):
        keepalive_count = random.randint(1,args.keepalive_count)
        
        tag = "Client%d" % i
        warning( "ADD %s -- keepalive_count %d" % (tag, keepalive_count) )
        
        proxy = transport.JsonChannel(channel)
        ctx = context.UserContext(proxy, tag, args.testkeypass, version=args.version)
        fraction = 'A' if (i % 2) else 'B' # пусть делятся по фракциям на четный-нечетный
        
        fsm = PersistentGuestLoginFSM(ctx) \
            + CheckAuthAndFractionFSM(ctx, fraction=fraction) \
            + DoKeepaliveCountFSM(ctx, run_count=keepalive_count, keepalive_period=args.keepalive_period) \
            + LogoutFSM(ctx) 
            
        fsms.append(fsm)
        
    return fsms


# --------------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------

def load_login_fraction(channel, args):
    fsms = []
    
    # добавляем клиентов
    for i in xrange(args.clients):
        
        tag = "Client%d" % i
        warning( "ADD %s" % (tag) )
        
        timeoutFail = args.clients * 1.0
        
        proxy = transport.JsonChannel(channel)
        fraction = 'A' if (i % 2) else 'B' # пусть делятся по фракциям на четный-нечетный
        sex = 1 if ((i/2) % 2) else 2 # поочередно мужские и женские
        ctx = context.UserContext(proxy, tag, args.testkeypass, sex=sex, version=args.version)
        
        fsm = PersistentGuestLoginFSM(ctx) \
            + CheckAuthAndFractionFSM(ctx, fraction=fraction, timeoutFail=timeoutFail) \
            + LogoutFSM(ctx) 
            
        fsms.append(fsm)
        
    return fsms


# --------------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------

def load_login(channel, args):
    fsms = []
    
    # добавляем клиентов
    for i in xrange(args.clients):
        
        tag = "Client%d" % i
        warning( "ADD %s" % (tag) )
        
        timeoutFail = args.clients * 1.0
        
        proxy = transport.JsonChannel(channel)
        ctx = context.UserContext(proxy, tag, args.testkeypass, version=args.version)
        
        fsm = PersistentGuestLoginFSM(ctx) \
            + LogoutFSM(ctx) 
            
        fsms.append(fsm)
        
    return fsms


# --------------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------

def load_login_fraction_mm(channel, args):
    fsms = []
    
    # добавляем клиентов
    for i in xrange(args.clients):
        
        tag = "Client%d" % i
        warning( "ADD %s" % (tag) )
        
        loadTimeoutFail = 5.0 + args.clients * 1.0
        
        proxy = transport.JsonChannel(channel)
        ctx = context.UserContext(proxy, tag, args.testkeypass, version=args.version)
        fraction = 'A' if (i % 2) else 'B' # пусть делятся по фракциям на четный-нечетный
        
        fsm = PersistentGuestLoginFSM(ctx) \
            + CheckAuthAndFractionFSM(ctx, fraction=fraction, timeoutFail=loadTimeoutFail) \
            + MatchmakingAddAcceptFSM(ctx, 0, fraction, args.game, timeoutFail=60.0+loadTimeoutFail) \
            + CancelSessionFSM(ctx) \
            + TimeoutWaitFSM(ctx, 3.0) \
            + MatchmakingAddAcceptFSM(ctx, 0, fraction, args.game, timeoutFail=60.0+loadTimeoutFail) \
            + LogoutFSM(ctx) 
            
        fsms.append(fsm)
        
    return fsms


# --------------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------

def load_login_fraction_gtc(channel, args):
    fsms = []
    
    # добавляем клиентов
    for i in xrange(args.clients):
        
        tag = "Client%d" % i
        warning( "ADD %s" % (tag) )
        
        loginTimeoutFail = 1.0 + args.clients * 1.0
        loadTimeoutFail = 5.0 + args.clients * 1.0
        waitPvxGame104Timeout = 10.0 + args.clients * 0.5
        
        proxy = transport.JsonChannel(channel)
        fraction = 'A' if (i % 2) else 'B' # пусть делятся по фракциям на четный-нечетный
        sex = 1 if ((i/2) % 2) else 2 # поочередно мужские и женские
        ctx = context.UserContext(proxy, tag, args.testkeypass, sex=sex, version=args.version)
        
        hero_index = ((i/4) % 3) # 0..2, порядковый индекс героя, которого мы хотим выбрать для ММ
        
        fsm = PersistentGuestLoginFSM(ctx, timeoutFail=loginTimeoutFail) \
            + CheckAuthAndFractionFSM(ctx, fraction=fraction, timeoutFail=loadTimeoutFail) \
            + ChooseIndexedHeroFSM(ctx, hero_index) \
            + MakeGuardContextHeroFSM(ctx) \
            + MatchmakingContextHeroAddAcceptFSM(ctx, 0, fraction, args.game, timeoutFail=60.0+loadTimeoutFail) \
            + StartGameTestClientFSM(ctx, args.session_key_dir, args.client, args.client_exe, spawnGTC=1, scenario_duration=args.game_duration) \
            + WaitForPvxGameFSM(ctx, timeoutFail=waitPvxGame104Timeout) \
            + WaitForPvxFinishFSM(ctx, timeoutFail=args.game_duration+15.0+20.0) \
            + LogoutFSM(ctx) 
        # WaitForPvxFinishFSM: +15 секунд даем на лишние процессы в GTC (загрузка карты и т.п., видимо не входящие в scenario_duration); +20 секунд на "прореженные" пинги в статусе 104
        
        fsms.append(fsm)
        
    return fsms

# --------------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------

def load_guest_gtc(channel, args):
    fsms = []
    
    # добавляем клиентов
    for i in xrange(args.clients):
        
        tag = "Client%d" % i
        warning( "ADD %s" % (tag) )
        
        loginTimeoutFail = 1.0 + args.clients * 1.0
        loadTimeoutFail = 5.0 + args.clients * 1.0
        waitPvxGame104Timeout = 10.0 + args.clients * 0.5
        
        proxy = transport.JsonChannel(channel)
        fraction = 'A' if (i % 2) else 'B' # пусть делятся по фракциям на четный-нечетный
        sex = 1 if ((i/2) % 2) else 2 # поочередно мужские и женские
        ctx = context.UserContext(proxy, tag, args.testkeypass, sex=sex, version=args.version)
        
        fsm = GuestLoginFSM(ctx, timeoutFail=loginTimeoutFail) \
            + CheckAuthAndFractionFSM(ctx, fraction=fraction, timeoutFail=loadTimeoutFail) \
            + MatchmakingAddAcceptFSM(ctx, 0, fraction, args.game, timeoutFail=60.0+loadTimeoutFail) \
            + StartGameTestClientFSM(ctx, args.session_key_dir, args.client, args.client_exe, spawnGTC=1, scenario_duration=args.game_duration) \
            + WaitForPvxGameFSM(ctx, timeoutFail=waitPvxGame104Timeout) \
            + WaitForPvxFinishFSM(ctx, timeoutFail=args.game_duration+15.0+20.0) \
            + LogoutFSM(ctx) 
        # WaitForPvxFinishFSM: +15 секунд даем на лишние процессы в GTC (загрузка карты и т.п., видимо не входящие в scenario_duration); +20 секунд на "прореженные" пинги в статусе 104
        
        fsms.append(fsm)
        
    return fsms
