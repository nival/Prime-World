# -*- coding: utf-8 -*-
import time, os, hashlib, gc
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

from party_scen import *
from load_scen import *
from admin_scen import *

import argparse
parser = argparse.ArgumentParser()
parser.add_argument('--login', default='http://pw.nivalnetwork.com:88', help='Login address')
parser.add_argument('--verbose', type=int, default=0, choices=[0, 1, 2], help='Verbosity level')
parser.add_argument('--threads', type=int, default=1, help='Threads count for request sending')
parser.add_argument('--clients', type=int, default=10, help='Clients count for several load scenarios')
parser.add_argument('--masters', type=int, default=1, help='Master-users count for party scenarios')
parser.add_argument('--scenario', choices=[ 
        'real', 'real_cancel', 'matchmake', 'login', 'real_matchmake', 'girl_matchmake', 'cancel_matchmaking', 
        'cancel_matchmaking_1x1', 'load_matchmaking', 'train_matchmake', 'train_leave', 'cancel_matchmaking_gametest', 'cyclic_login_logout', 'cancel_matchmaking_11',
        'party_invite', 'party_go', 'party_start', 'party_start_client', 'party_reconnect', 'party_reconnect_play', 'party_leave',
        'simple_chat',
        'inc_save', 'load_login', 'load_login_fraction', 'load_login_keepalive', 
        'load_login_fraction_mm', 'load_login_fraction_gtc', 'load_guest_gtc',
        'launcher_login', 'launcher_join', 'launcher_merge',
        'set_geolocation',
        'agg_login', 
    ], default='', help='Scenario')
parser.add_argument('--game', default='train', help='Game type/map for several scenarios')
parser.add_argument('--sn', default='fb', choices=['fb', 'ok'], help='Social network for several scenarios')
parser.add_argument('--sn2', default='fb', choices=['fb', 'ok'], help='Social network for several scenarios')
parser.add_argument('--user', help='User for several scenarios')
parser.add_argument('--user2', help='User for several scenarios')
parser.add_argument('--hero', choices=[1,34], type=int, help='Hero_ID for real scenario')
parser.add_argument('--fraction', choices=['A', 'B'], help='Fraction for real scenario (persistent fraction will be used if not defined)')
parser.add_argument('--password', help='Password for several scenarios')
parser.add_argument('--a_password', help='Additional password for several scenarios')
parser.add_argument('--password2', help='Password for several scenarios')
parser.add_argument('--a_password2', help='Additional password for several scenarios')
parser.add_argument('--client', help='Path to client')
parser.add_argument('--session_key_dir', default='', help='Path to GameTestClient session keys directory')
parser.add_argument('--client_exe', default='PW_Game.exe', help='Path to client')
parser.add_argument('--guest', type=bool, default=False, help='Use guest login')
parser.add_argument('--period', type=float, default=0.0, help='Period between state calls')
parser.add_argument('--logfile', default='', help='Log file name')
parser.add_argument('--loglevel', choices=['debug','info','warning','error'], default='info', help='Logging severity level')
parser.add_argument('--ping_wait', type=float, default=0.0, help='PartyPing long-polling wait period')
parser.add_argument('--inc_save_count', type=int, default=1, help='Times to run inc_save command')
parser.add_argument('--keepalive_count', type=int, default=10, help='Times to do action=keepalive')
parser.add_argument('--keepalive_period', type=float, default=5.0, help='Times between keepalive sends')
parser.add_argument('--game_duration', type=float, default=20.0, help='Time to spend in pvx game sessions (PW_Game or GTC)')
parser.add_argument('--snid', default='fb', choices=['fb', 'ok'], help='Social network type for some scenarios')
parser.add_argument('--snuid', default='', help='Social network user id for some scenarios')
parser.add_argument('--sntoken', default='', help='Social network auth token for some scenarios')
parser.add_argument('--geolocation', default='RU', help='Geolocation prefix for some scenarios')
parser.add_argument('--testkeypass', default='0', help='Test key password for persistent guest logins')
parser.add_argument('--version', default='0.0.0', help='Client version')
parser.add_argument('--send_timeout', default=20.0, type=float, help='Urllib http send timeout')
args = parser.parse_args()

if not args.scenario:
    print "BAD SCENARIO, use --scenario option"
    os.abort()

def loggingSeverity( name ):
    return getattr( logging, name.upper(), 0) if name else 0

if args.logfile:
    logfilename = args.logfile
else:
    logfilename = None
    
logging.basicConfig( filename=logfilename, filemode="w", level=loggingSeverity( args.loglevel ), format='[%(asctime)s %(levelname)8s] %(message)s' )
debug( "---- logging start ----")


import binascii
def real(channel, args):
    proxy = transport.JsonChannel(channel)
    userContext = context.UserContext(proxy, version=args.version)
    loginType = 'zzima'
    if args.guest:
        loginType = 'guest'
    return LoginFSM(userContext, args.user, args.password, loginType) \
        + MatchmakingFSM(userContext, args.hero, args.fraction, args.game) \
        + StartClientFSM(userContext, args.client, args.client_exe)
    
def real_cancel(channel, args):
    proxy = transport.JsonChannel(channel)
    userContext = context.UserContext(proxy, version=args.version)
    return LoginFSM(userContext, args.user, args.password)+MatchmakingFSM(userContext, args.hero, args.fraction, args.game, 1)
    
def login(channel, args):
    proxy = transport.JsonChannel(channel)
    userContext = context.UserContext(proxy, version=args.version)
    return LoginFSM(userContext, args.user, args.password, 'fb')+LogoutFSM(userContext)

def launcher_login(channel, args):
    proxy = transport.JsonChannel(channel)
    userContext = context.UserContext(proxy, version=args.version)
    import launcher_fsm
    return launcher_fsm.LauncherLoginFSM(userContext, args)

def launcher_join(channel, args):
    proxy = transport.JsonChannel(channel)
    userContext = context.UserContext(proxy, version=args.version)
    import launcher_join_fsm
    return launcher_join_fsm.LauncherJoinFSM(userContext, args)

def launcher_merge(channel, args):
    proxy = transport.JsonChannel(channel)
    userContext = context.UserContext(proxy, version=args.version)
    userContext2 = context.UserContext(proxy)
    import launcher_join_fsm
    return launcher_join_fsm.LauncherMergeFSM(userContext, userContext2, args)

def agg_login(channel, args):
    json_proxy = transport.JsonChannel(channel)
    import agg_fsm
    return agg_fsm.AggregatorLoginFSM(json_proxy, args)

def matchmake(channel, args):
    clients = [
        ('redjack', '8fronHot', 1, 'A'),
        ('TestZ4', '123123123', 1, 'B'),
    ]
    fsms = []
    for user, password, hero_id, fraction in clients:
        proxy = transport.JsonChannel(channel)
        userContext = context.UserContext(proxy, version=args.version)
        fsm = LoginFSM(userContext, user, password) \
                + MatchmakingFSM(userContext, hero_id, fraction, 'pvp1x1') \
                + LogoutFSM(userContext)
        fsms.append(fsm)
    return fsms

def real_matchmake(channel, args):
    clients = [
        ('redjack', '8fronHot', 1, 'A'),
        ('TestZ4', '123123123', 1, 'B'),
    ]
    fsms = []
    for user, password, hero_id, fraction in clients:
        proxy = transport.JsonChannel(channel)
        userContext = context.UserContext(proxy, version=args.version)
        fsm = LoginFSM(userContext, user, password) \
                + MatchmakingFSM(userContext, hero_id, fraction, 'pvp1x1') \
                + StartClientFSM(userContext, args.client, args.client_exe)
        fsms.append(fsm)
    return fsms

def girl_matchmake(channel, args):
    clients = [
        ('yozeg', 'a6ec1ce7e89895b6fd594038bdcc5b98', 1, 'A'),
        ('clarice', '51d3790e2ddc683cc3dfa4f9f625355a', 34, 'B'),
    ]
    fsms = []
    for user, password, hero_id, fraction in clients:
        proxy = transport.JsonChannel(channel)
        userContext = context.UserContext(proxy, version=args.version)
        fsm = LoginHashFSM(userContext, user, password) \
                + MatchmakingFSM(userContext, hero_id, fraction, 'pvp1x1') \
                + StartClientFSM(userContext, args.client, args.client_exe)
        fsms.append(fsm)
    return fsms
    
    
def train_leave(channel, args):
    clients = [
        ('yozeg', 'a6ec1ce7e89895b6fd594038bdcc5b98', 1, 'A'),
    ]
    fsms = []
    for user, password, hero_id, fraction in clients:
        proxy = transport.JsonChannel(channel)
        userContext = context.UserContext(proxy, version=args.version)
        fsm = LoginHashFSM(userContext, user, password) \
            + MatchmakingFSM(userContext, hero_id, fraction, 'train') \
            + StartClientAndLeaveFSM(userContext, args.client, args.client_exe) ## + StartClientFSM(userContext, args.client, args.client_exe) 
        fsms.append(fsm)
    return fsms

def train_matchmake(channel, args):
    clients = [
        #s('yozeg', 'a6ec1ce7e89895b6fd594038bdcc5b98', 1, 'A'),
        ('clarice', '51d3790e2ddc683cc3dfa4f9f625355a', 34, 'B'),
    ]
    fsms = []
    for user, password, hero_id, fraction in clients:
        proxy = transport.JsonChannel(channel)
        userContext = context.UserContext(proxy, version=args.version)
        fsm = LoginHashFSM(userContext, user, password) \
            + MatchmakingFSM(userContext, hero_id, fraction, 'train') \
            + StartClientFSM(userContext, args.client, args.client_exe) 
        fsms.append(fsm)
    return fsms

def cancel_matchmaking_1x1(channel, args):
    clients = [
        ('redjack', '8fronHot', 1, 'A', 0),
        ('TestZ4', '123123123', 34, 'B', 1),
    ]
    fsms = []
    for user, password, hero_id, fraction, cancelCount in clients:
        proxy = transport.JsonChannel(channel)
        userContext = context.UserContext(proxy, version=args.version)
        fsm = LoginFSM(userContext, user, password) \
                + MatchmakingFSM(userContext, hero_id, fraction, 'pvp1x1', cancelCount) \
                + StartClientFSM(userContext, args.client, args.client_exe)
        fsms.append(fsm)
    return fsms

def cancel_matchmaking(channel, args):
    clients = [
        ('TestZ1', '123123123', 1, 'B', 0),
        ('TestZ2', '123123123', 1, 'B', 0),
        ('TestZ3', '123123123', 1, 'B', 0),
        ('TestZ4', '123123123', 1, 'B', 0),
        ('TestZ5', '123123123', 1, 'B', 0),
        ('TestZ6', '123123123', 1, 'A', 1),
        ('TestZ7', '123123123', 1, 'A', 1),
        ('TestZ8', '123123123', 1, 'A', 0),
        ('TestZ9', '123123123', 1, 'A', 0),
        ('redjack', '8fronHot', 1, 'A', 0),
    ]
    fsms = []
    for user, password, hero, fraction, cancelCount in clients:
        proxy = transport.JsonChannel(channel)
        userContext = context.UserContext(proxy, version=args.version)
        fsm = LoginFSM(userContext, user, password) \
            + MatchmakingFSM(userContext, hero, fraction, 'pvp', cancelCount)

        fsms.append(fsm)
    return fsms


def cancel_matchmaking_gametest(channel, args):
    clients = [
        ('TestZ1', '123123123', 1, 'B', 0),
        ('TestZ2', '123123123', 1, 'B', 0),
        ('TestZ3', '123123123', 1, 'B', 0),
        ('TestZ4', '123123123', 1, 'B', 0),
        ('TestZ5', '123123123', 1, 'B', 0),
        ('TestZ6', '123123123', 1, 'A', 1),
        ('TestZ7', '123123123', 1, 'A', 1),
        ('TestZ8', '123123123', 1, 'A', 0),
        ('TestZ9', '123123123', 1, 'A', 0),
        ('redjack', '8fronHot', 1, 'A', 0),
    ]
    fsms = []
    for user, password, hero, fraction, cancelCount in clients:
        proxy = transport.JsonChannel(channel)
        userContext = context.UserContext(proxy, version=args.version)
        fsm =   LoginFSM(userContext, user, password) \
                + MatchmakingFSM(userContext, hero, fraction, 'pvp', cancelCount) \
                + StartGameTestClientFSM(userContext, args.session_key_dir, args.client, args.client_exe)
        fsms.append(fsm)
    return fsms


def cancel_matchmaking_11(channel, args):
    clients = [
        ('TestZ1', '123123123', 1, 'B', 0),
        ('TestZ2', '123123123', 1, 'B', 0),
        ('TestZ3', '123123123', 1, 'B', 0),
        ('TestZ4', '123123123', 1, 'B', 0),
        ('TestZ5', '123123123', 1, 'B', 0),
        ('TestZ6', '123123123', 1, 'A', 0),
        ('TestZ7', '123123123', 1, 'A', 0),
        ('TestZ8', '123123123', 1, 'A', 0),
        ('TestZ9', '123123123', 1, 'A', 0),
        ('redjack', '8fronHot', 1, 'A', 1),
        ('matolog', 'desert77', 1, 'A', 0),
    ]
    fsms = []
    for user, password, hero, fraction, cancelCount in clients:
        proxy = transport.JsonChannel(channel)
        userContext = context.UserContext(proxy, version=args.version)
        fsm =   LoginFSM(userContext, user, password) \
                + MatchmakingAddAcceptCancelFSM(userContext, hero, fraction, 'pvp', cancelCount)
        fsms.append(fsm)
    return fsms
    
def load_matchmaking(channel, args):
    fsms = []
    fractions = ['A', 'B']
    for i in range(args.clients):
        proxy = transport.JsonChannel(channel)
        userContext = context.UserContext(proxy, version=args.version)  # random hero if empty
        user = 'user%d' % (i+1)
        fsm = LoginFSM(userContext, user, '', False)+MatchmakingFSM(userContext, args.hero, fractions[i % 2], 'pvp')+LogoutFSM(userContext)
        fsms.append(fsm)
    return fsms

def simple_chat(channel, args):
    proxy = transport.JsonChannel(channel)
    userContext = context.UserContext(proxy, version=args.version)
    import chat_fsm
    return LoginFSM(userContext, args.user, args.password, args.sn)+chat_fsm.SimpleMessageFSM(userContext, args)+LogoutFSM(userContext)

# ------------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------------

#~ gc.set_threshold( 500000, 5, 5 ) # garbage collection пореже, но помощнее плз
gc.disable()

channel = transport.AsyncHTTPChannel(args.login, args.verbose, args.threads, args.send_timeout)

fsms = []
fsm = eval(args.scenario+'(channel, args)')
if type(fsm) == list:
    fsms.extend(fsm)
else:
    fsms.append(fsm)
    
# давайте, что ли, посчитаем, сколько FSM-ок прошло тест, сколько пофейлило.. и т.п.
count_total = len(fsms)
count_passed = 0
count_failed = 0

if args.period > 0:
    for fsm in fsms:
        fsm.SetPeriod(args.period)

try:
    channel.start()
    tStart = time.time()

    while len(fsms) > 0:
        finishedFsms = []
        for fsm in fsms:
            fsm.Update()
            if fsm.finished:
                passed_status = fsm.GetPassedStatus()
                if fsm.GetPassedStatus() == PASSED_STATUS_OK:
                    warn( "passed fsm %s" % fsm )
                    count_passed += 1
                    msg = "passed %d/%d" % (count_passed, count_total)
                    warn(msg)
                    print msg
                elif fsm.GetPassedStatus() == PASSED_STATUS_FAIL:
                    warn( "failed fsm %s" % fsm )
                    fail_message = fsm.GetFailMessage()
                    warn( fail_message )
                    count_failed += 1
                    msg = fail_message + "\n" + "failed %d/%d" % (count_failed, count_total)
                    warn(msg)
                    print msg
                finishedFsms.append(fsm)
            time.sleep(0.001)
            
        for fsm in finishedFsms:
            fsms.remove(fsm)
finally:
    tFin = time.time()
    channel.shutdown()

    time.sleep(0.5) # подождем, пока все thread-ы допишут свои дампы, и подытожим
    
    # FIXME: грязными руками зачищаем запущенные глобальные процессы типа GTC
    if StartGameTestClientFSM.processGTC:
        StartGameTestClientFSM.KillGTC()

    if count_failed > 0:
        msg = "PASSED: %d/%d (FAILED: %d) :: %5.3f seconds" % (count_passed, count_total, count_failed, tFin-tStart)
    else:            
        msg = "PASSED: %d/%d :: %5.3f seconds" % (count_passed, count_total, tFin-tStart)
    warn( msg )
    print "-" * 40  
    print msg
      
