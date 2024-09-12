# -*- coding: utf-8 -*-
# сценарии для работы с партиями
import sys, time, os, hashlib
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

def party_invite(channel, args):
    fsms = []
    masters = [] # в этой коллекции будут присвоенные auid-ы party-master-ов
    invite_clients = []
    
    # + GuestLoginFSM: логинится guest-ом, складывает полученный uid в out_auids[]
    # + PartyInviteFSM: приглашает всех из списка invite_auids[], ждет пока не получит ответ (accept/decline) на все свои приглашения
    # + PartyAcceptFSM: принимает приглашения в партию от юзеров из списка accept_from_auids[], отклоняет от юзеров из списка decline_from_auids[]; затем ждет, пока его не удалят из партии
    # + PartyKickFSM: кикает всех юзеров по списку
    
    # добавляем party MASTER 
    for i in xrange(args.masters):
        tag = "Master%d" % i
        info( "ADD %s" % tag )
        proxy = transport.JsonChannel(channel)
        ctx = party_context.PartyUserContext(proxy, tag, args.ping_wait, version=args.version)
        fsm = GuestLoginFSM(ctx, out_auids=masters, comment=tag) \
            + PartyInviteFSM(ctx, invite_auids=invite_clients, invite_count=args.clients, timeoutFail=15.0) \
            + PartyKickFSM(ctx, kick_auids=invite_clients, kick_total_count=args.clients) \
            + LogoutFSM(ctx)
        fsms.append(fsm)
    
    # добавляем клиентов, которых мастер должен всех пригласить, а потом всех кикнуть
    for i in xrange(args.clients):
        tag = "Client%d" % i
        info( "ADD %s" % tag )
        proxy = transport.JsonChannel(channel)
        ctx = party_context.PartyUserContext(proxy, tag, args.ping_wait, version=args.version)
        fsm = GuestLoginFSM(ctx, out_auids=invite_clients, comment=tag) \
            + PartyAcceptFSM(ctx, accept_from_auids=masters, accepts_total_count=args.masters, timeoutFail=15.0) \
            + WaitForDisbandFSM(ctx) \
            + LogoutFSM(ctx)
        fsms.append(fsm)
        
    return fsms


def party_go(channel, args):
    assert args.masters == 1, "this scenario works only with 1 master user"
    fsms = []
    masters = [] # в этой коллекции будут присвоенные auid-ы party-master-ов
    invite_clients = []
    
    # + GuestLoginFSM: логинится guest-ом, складывает полученный uid в out_auids[]
    
    # + PartyAcceptFSM: принимает приглашения в партию от юзеров из списка accept_from_auids[], отклоняет от юзеров из списка decline_from_auids[]; 
    # + ChooseHeroFSM: выбирает героя, дожидается подтверждения от PersonServer
    # + WaitForDisbandFSM: ждет, пока юзера не удалят из партии
    
    # + PartyInviteFSM: приглашает всех из списка invite_auids[], ждет пока не получит ответ (accept/decline) на все свои приглашения
    # + ChooseAllPartyHeroesFSM: ждет, пока все юзеры из списка heroes_left[] (! формируемого ранее в PartyInviteFSM !) не выберут героев для pvp
    # + PartyGoFSM: запускает парти-матчмейкинг
    # + PartyKickFSM: кикает всех юзеров по списку
    
    # добавляем party MASTER 
    for i in xrange(args.masters):
        tag = "Master%d" % i
        info( "ADD %s" % tag )
        proxy = transport.JsonChannel(channel)
        ctx = party_context.PartyUserContext(proxy, tag, args.ping_wait, version=args.version)
        fsm = GuestLoginFSM(ctx, out_auids=masters, comment=tag) \
            + PartyInviteFSM(ctx, invite_auids=invite_clients, invite_count=args.clients) \
            + ChooseAllPartyHeroesFSM(ctx) \
            + PartyGoFSM(ctx) \
            + CheckPartyMmPingFSM(ctx, master_auids=masters, member_auids=invite_clients, timeoutFail=2.0) \
            + TimeoutWaitFSM(ctx, 1.0) \
            + PartyKickFSM(ctx, kick_auids=invite_clients, kick_total_count=args.clients) \
            + LogoutFSM(ctx) 
        fsms.append(fsm)
    
    # добавляем клиентов, которых мастер должен всех пригласить, а потом всех кикнуть
    for i in xrange(args.clients):
        tag = "Client%d" % i
        info( "ADD %s" % tag )
        proxy = transport.JsonChannel(channel)
        ctx = party_context.PartyUserContext(proxy, tag, args.ping_wait, version=args.version)
        fsm = GuestLoginFSM(ctx, out_auids=invite_clients, comment=tag) \
            + PartyAcceptFSM(ctx, accept_from_auids=masters, accepts_total_count=args.masters) \
            + ChooseHeroFSM(ctx) \
            + PartyWaitForGoFSM(ctx) \
            + CheckPartyMmPingFSM(ctx, master_auids=masters, member_auids=invite_clients, timeoutFail=2.0) \
            + WaitForDisbandFSM(ctx) \
            + LogoutFSM(ctx)
        fsms.append(fsm)
        
    return fsms


def party_start_client(channel, args):
    assert args.masters == 1, "this scenario works only with 1 master user"
    fsms = []
    masters = [] # в этой коллекции будут присвоенные auid-ы party-master-ов
    invite_clients = []
    
    # добавляем party MASTER 
    for i in xrange(args.masters):
        tag = "Master%d" % i
        info( "ADD %s" % tag )
        proxy = transport.JsonChannel(channel)
        ctx = party_context.PartyUserContext(proxy, tag, args.ping_wait, version=args.version)
        fsm = GuestLoginFSM(ctx, out_auids=masters, comment=tag) \
            + PartyInviteFSM(ctx, invite_auids=invite_clients, invite_count=args.clients) \
            + ChooseAllPartyHeroesFSM(ctx) \
            + PartyGoFSM(ctx, "train") \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, timeoutFail=2.0) \
            + PartyMatchmakingFSM(ctx) \
            + StartClientFSM(ctx, args.client, args.client_exe)
        fsms.append(fsm)
    
    # добавляем клиентов, которых мастер должен всех пригласить
    for i in xrange(args.clients):
        tag = "Client%d" % i
        info( "ADD %s" % tag )
        proxy = transport.JsonChannel(channel)
        ctx = party_context.PartyUserContext(proxy, tag, args.ping_wait, version=args.version)
        fsm = GuestLoginFSM(ctx, out_auids=invite_clients, comment=tag) \
            + PartyAcceptFSM(ctx, accept_from_auids=masters, accepts_total_count=args.masters) \
            + ChooseHeroFSM(ctx) \
            + PartyWaitForGoFSM(ctx) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, timeoutFail=2.0) \
            + PartyMatchmakingFSM(ctx) \
            + StartClientFSM(ctx, args.client, args.client_exe)
        fsms.append(fsm)
        
    return fsms
    
    
def party_reconnect(channel, args):
    assert args.masters == 1, "this scenario works only with 1 master user"
    fsms = []
    masters = [] # в этой коллекции будут присвоенные auid-ы party-master-ов
    invite_clients = []
    
    # добавляем party MASTER 
    for i in xrange(args.masters):
        tag = "Master%d" % i
        info( "ADD %s" % tag )
        proxy = transport.JsonChannel(channel)
        ctx = party_context.PartyUserContext(proxy, tag, args.ping_wait, version=args.version)
        fsm = GuestLoginFSM(ctx, out_auids=masters, comment=tag) \
            + PartyInviteFSM(ctx, invite_auids=invite_clients, invite_count=args.clients) \
            + ChooseAllPartyHeroesFSM(ctx) \
            + PartyGoFSM(ctx, "train") \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, timeoutFail=2.0) \
            + PartyMatchmakingFSM(ctx) \
            + StartClientFSM(ctx, args.client, args.client_exe) \
            + TimeoutWaitFSM(ctx, 20.0) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, check_progress=MM.STATUS_IN_GAME, timeoutFail=2.0) \
            + TimeoutWaitFSM(ctx, 20.0) \
            + TerminateClientFSM(ctx) \
            + LogoutFSM(ctx)
        fsms.append(fsm)
    
    # добавляем клиентов, которых мастер должен всех пригласить
    # клиенты:
    # 1) заходят в pvx 
    # 2) убеждаются что pvx игра стартовала 
    # 3) делают terminate 
    # 4) убеждаются что теперь у них статус ClientDropped 
    # 5) делают релогин и реконнект
    # 6) убеждаются что pvx игра опять стартовала
    # 7) выходят довольные
    for i in xrange(args.clients):
        tag = "Client%d" % i
        info( "ADD %s" % tag )
        proxy = transport.JsonChannel(channel)
        ctx = party_context.PartyUserContext(proxy, tag, args.ping_wait, version=args.version)
        fsm = GuestLoginFSM(ctx, out_auids=invite_clients, comment=tag) \
            + PartyAcceptFSM(ctx, accept_from_auids=masters, accepts_total_count=args.masters) \
            + ChooseHeroFSM(ctx) \
            + PartyWaitForGoFSM(ctx) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, timeoutFail=2.0) \
            + PartyMatchmakingFSM(ctx) \
            + StartClientFSM(ctx, args.client, args.client_exe) \
            + TimeoutWaitFSM(ctx, 20.0) \
            + TerminateClientFSM(ctx) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, check_progress=MM.STATUS_IN_GAME, timeoutFail=2.0) \
            + TimeoutWaitFSM(ctx, 3.0) \
            + ReloginFSM(ctx) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, check_progress=MM.STATUS_CLIENT_DROPPED, timeoutFail=2.0) \
            + ReconnectFSM(ctx) \
            + PartyMatchmakingFSM(ctx) \
            + StartClientFSM(ctx, args.client, args.client_exe) \
            + TimeoutWaitFSM(ctx, 10.0) \
            + TerminateClientFSM(ctx) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, check_progress=MM.STATUS_IN_GAME, timeoutFail=2.0) \
            + LogoutFSM(ctx)
        fsms.append(fsm)
        
    return fsms


# то же самое что party_reconnect, только не убиваем клиенты и не рвем соединение (можно убедиться, что все клиенты играют нормально)
def party_reconnect_play(channel, args):
    assert args.masters == 1, "this scenario works only with 1 master user"
    fsms = []
    masters = [] # в этой коллекции будут присвоенные auid-ы party-master-ов
    invite_clients = []
    
    # добавляем party MASTER 
    for i in xrange(args.masters):
        tag = "Master%d" % i
        info( "ADD %s" % tag )
        proxy = transport.JsonChannel(channel)
        ctx = party_context.PartyUserContext(proxy, tag, args.ping_wait, version=args.version)
        fsm = GuestLoginFSM(ctx, out_auids=masters, comment=tag) \
            + PartyInviteFSM(ctx, invite_auids=invite_clients, invite_count=args.clients) \
            + ChooseAllPartyHeroesFSM(ctx) \
            + PartyGoFSM(ctx, "train") \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, timeoutFail=2.0) \
            + PartyMatchmakingFSM(ctx) \
            + StartClientFSM(ctx, args.client, args.client_exe) \
            + TimeoutWaitFSM(ctx, 20.0) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, check_progress=MM.STATUS_IN_GAME, timeoutFail=2.0) \
            + TimeoutWaitFSM(ctx, 20.0) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, check_progress=MM.STATUS_IN_GAME, timeoutFail=2.0)
        fsms.append(fsm)
    
    # добавляем клиентов, которых мастер должен всех пригласить
    # клиенты:
    # 1) заходят в pvx 
    # 2) убеждаются что pvx игра стартовала 
    # 3) делают terminate 
    # 4) убеждаются что теперь у них статус ClientDropped 
    # 5) делают релогин и реконнект
    # 6) убеждаются что pvx игра опять стартовала
    # 7) выходят довольные
    for i in xrange(args.clients):
        tag = "Client%d" % i
        info( "ADD %s" % tag )
        proxy = transport.JsonChannel(channel)
        ctx = party_context.PartyUserContext(proxy, tag, args.ping_wait, version=args.version)
        fsm = GuestLoginFSM(ctx, out_auids=invite_clients, comment=tag) \
            + PartyAcceptFSM(ctx, accept_from_auids=masters, accepts_total_count=args.masters) \
            + ChooseHeroFSM(ctx) \
            + PartyWaitForGoFSM(ctx) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, timeoutFail=2.0) \
            + PartyMatchmakingFSM(ctx) \
            + StartClientFSM(ctx, args.client, args.client_exe) \
            + TimeoutWaitFSM(ctx, 20.0) \
            + TerminateClientFSM(ctx) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, check_progress=MM.STATUS_IN_GAME, timeoutFail=2.0) \
            + TimeoutWaitFSM(ctx, 3.0) \
            + ReloginFSM(ctx) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, check_progress=MM.STATUS_CLIENT_DROPPED, timeoutFail=2.0) \
            + ReconnectFSM(ctx) \
            + PartyMatchmakingFSM(ctx) \
            + StartClientFSM(ctx, args.client, args.client_exe) \
            + TimeoutWaitFSM(ctx, 10.0) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, check_progress=MM.STATUS_IN_GAME, timeoutFail=2.0)
        fsms.append(fsm)
        
    return fsms


def party_leave(channel, args):
    assert args.masters == 1, "this scenario works only with 1 master user"
    fsms = []
    masters = [] # в этой коллекции будут присвоенные auid-ы party-master-ов
    invite_clients = []
    
    # добавляем party MASTER 
    for i in xrange(args.masters):
        tag = "Master%d" % i
        info( "ADD %s" % tag )
        proxy = transport.JsonChannel(channel)
        ctx = party_context.PartyUserContext(proxy, tag, args.ping_wait, version=args.version)
        fsm = GuestLoginFSM(ctx, out_auids=masters, comment=tag) \
            + PartyInviteFSM(ctx, invite_auids=invite_clients, invite_count=args.clients) \
            + ChooseAllPartyHeroesFSM(ctx) \
            + PartyGoFSM(ctx, "train") \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, timeoutFail=2.0) \
            + PartyMatchmakingFSM(ctx) \
            + StartClientFSM(ctx, args.client, args.client_exe) \
            + TimeoutWaitFSM(ctx, 15.0) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, check_progress=MM.STATUS_IN_GAME, timeoutFail=2.0) \
            + TimeoutWaitFSM(ctx, 10.0) \
            + TerminateClientFSM(ctx) \
            + LogoutFSM(ctx)
        fsms.append(fsm)
    
    # добавляем клиентов, которых мастер должен всех пригласить
    # клиенты:
    # 1) заходят в pvx 
    # 2) убеждаются что pvx игра стартовала 
    # 3) делают terminate 
    # 4) убеждаются что теперь у них статус ClientDropped 
    # 5) делают mm_leave
    # 6) убеждаются что попали в статус 109 (Wait for Game Finish)
    # 7) убеждаются, что после выхода мастера сессия рассыпается, и все участники получают "no active sessions"
    # 8) выходят довольные
    for i in xrange(args.clients):
        tag = "Client%d" % i
        info( "ADD %s" % tag )
        proxy = transport.JsonChannel(channel)
        ctx = party_context.PartyUserContext(proxy, tag, args.ping_wait, version=args.version)
        fsm = GuestLoginFSM(ctx, out_auids=invite_clients, comment=tag) \
            + PartyAcceptFSM(ctx, accept_from_auids=masters, accepts_total_count=args.masters) \
            + ChooseHeroFSM(ctx) \
            + PartyWaitForGoFSM(ctx) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, timeoutFail=2.0) \
            + PartyMatchmakingFSM(ctx) \
            + StartClientFSM(ctx, args.client, args.client_exe) \
            + TimeoutWaitFSM(ctx, 15.0) \
            + TerminateClientFSM(ctx) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, check_progress=MM.STATUS_IN_GAME, timeoutFail=2.0) \
            + TimeoutWaitFSM(ctx, 5.0) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, check_progress=MM.STATUS_CLIENT_DROPPED, timeoutFail=2.0) \
            + LeaveSessionFSM(ctx) \
            + TimeoutWaitFSM(ctx, 5.0) \
            + CheckPartyMmPingFSM(ctx, game_type="train", master_auids=masters, member_auids=invite_clients, check_progress=MM.STATUS_WAITING_GAME_FINISH, \
                timeoutFail=2.0) \
            + WaitForDisbandFSM(ctx, timeoutFail=5.0) \
            + TimeoutWaitFSM(ctx, 10.0) \
            + CheckNoMmPingFSM(ctx, timeoutFail=10.0) \
            + LogoutFSM(ctx)
            
            
        fsms.append(fsm)
        
    return fsms
