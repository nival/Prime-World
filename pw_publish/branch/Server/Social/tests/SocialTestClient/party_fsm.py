# -*- coding: utf-8 -*-
import sys, time, os, hashlib
import subprocess
import fsm
import transport 
import context
import main_fsm

#from logs import log
import logging, datetime
from logging import debug, info, warning, error

sys.path.append('../../')
from base.helpers import *

from fsm import ContextFSM, TimeoutFailFSM

FIRST_HERO_CRC = 242966457 # archeress
#~ FIRST_HERO_CRC = -1139813982 # assassin

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class TimeoutWaitFSM( ContextFSM ):
    """ ждем указанный таймаут, затем молча спокойно выходим """
    def __init__(self, context, timeoutWait=10.0, **kwargs):
        super(TimeoutWaitFSM, self).__init__(self.Wait, context, **kwargs)
        self.timeStart = 0
        self.timeoutWait = timeoutWait
    
    def Wait(self):
        if not self.timeStart: 
            self.timeStart = time.time() # время начинаем отсчитывать от запуска первого состояния
            info( "%s TimeoutWaitFSM start: %5.3f" % (self.context.tag, self.timeStart) )
        if time.time() > self.timeStart + self.timeoutWait:
            info( "%s TimeoutWaitFSM exit: %5.3f" % (self.context.tag, time.time()) )
            return self.Exit()
        info( "%s TimeoutWait" % self.context.tag )
    
# ------------------------------------------------------------------
# ------------------------------------------------------------------

class GuestLoginFSM(TimeoutFailFSM):
    """ выполняем GuestLogin, без всяких там лишних реквизитов; полученный от соц.сервера auid кладем в указанный out-список """
    def __init__(self, context, comment=None, out_auids=[], timeoutFail=1.0):
        super(GuestLoginFSM, self).__init__(self.Login, context, timeoutFail=timeoutFail)
        self.context = context
        self.out_auids = out_auids
        self.comment = comment

    def Login(self):
        self.context.Login(None, None, 'guest', comment=self.comment) # GUEST login
        return self.WaitLogin

    def WaitLogin(self):
        if self.context.auid:
            warning( "%s auid=%s" % (self.context.tag, self.context.auid) )
            self.out_auids.append( self.context.auid )
            self.Exit()


# ------------------------------------------------------------------
# ------------------------------------------------------------------

class PartyInviteFSM(TimeoutFailFSM):
    """ получаем список auid-ов для приглашения в партию; когда все перечисленные юзеры вступят в партию, делаем Pass """
    def __init__(self, context, invite_auids=[], invite_count=0, **kwargs):
        super(PartyInviteFSM, self).__init__(self.WaitForInviteUidsFilled, context, **kwargs)
        self.context = context
        self.tag = context.tag
        self.context.invite_auids = invite_auids
        self.context.invite_count = invite_count        
        
    def WaitForInviteUidsFilled(self):
        if len(self.context.invite_auids) >= self.context.invite_count:
            info("%s INVITE UIDS: %s" % (self.tag, self.context.invite_auids) )
            self.context.invite_sends_left = self.context.invite_auids[:] # всех по очереди нужно пригласить
            self.context.invite_replies_left = self.context.invite_auids[:] # и дождаться пока все ответят
            
            ## ---------------------------------------------------------------------------------------------------------------------------------
            ## поскольку клиенты могут сразу после JOIN делать ChooseHero, нужно на всякий случай приготовить список party-member-ов в контексте
            self.context.choose_heroes_left = self.context.invite_auids[:] 
            
            return self.InviteNext
        
        info( "%s WAIT for invite uids... (so far: %s, need %d total)" % (self.tag, self.context.invite_auids, self.context.invite_count) )


    def InviteNext(self):
        if self.context.invite_sends_left:
            inv_next = self.context.invite_sends_left.pop()
            warning("%s PARTY INVITE -> %d" % (self.tag, inv_next) )
            self.context.PartyInvite( str(inv_next) )
            return self.WaitForInviteResponse
        else:
            return self.WaitForJoins
            
    def WaitForInviteResponse(self):
        if self.context.party_response:
            return self.InviteNext
            
    def WaitForJoins(self):
        while self.context.invites_delivered:
            invited = self.context.invites_delivered.pop()
            info("%s -> PARTY INVITE DELIVERED: %d" % (self.tag, invited))
            
        if self.context.invite_replies_left:
            info("%s PARTY PING" % self.tag )
            self.context.PartyPing()
        else:
            warning("%s ALL INVITE REPLIES RECEIVED, exiting..." % self.tag )
            self.Pass()
            self.Exit()            
            

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class PartyAcceptFSM(TimeoutFailFSM):
    """ получаем 2 списка auid-ов: от кого отклонять приглашения в партию, и от кого принимать; исполнив действия по обоим спискам, делаем Pass """
    def __init__(self, context, accept_from_auids=[], accepts_total_count=0, accepts_left_count=0, \
            decline_from_auids=[], declines_total_count=0, declines_left_count=0, \
            **kwargs):
        super(PartyAcceptFSM, self).__init__(self.WaitForInviteUidsFilled, context, **kwargs)
        self.context = context
        self.tag = context.tag
        self.context.accept_from_auids = accept_from_auids
        self.context.accepts_total_count = accepts_total_count
        self.context.accepts_left_count = accepts_left_count # столько accept-ов должно остаться (0 == надо ответить всем, перечисленные в accept_from_auids)
        self.context.decline_from_auids = decline_from_auids
        self.context.declines_total_count = declines_total_count
        self.context.declines_left_count = declines_left_count # столько decline-ов должно остаться (0 == надо ответить всем, перечисленным в decline_from_auids)

    def WaitForInviteUidsFilled(self):
        if len(self.context.accept_from_auids) >= self.context.accepts_total_count:
            if len(self.context.decline_from_auids) >= self.context.declines_total_count:
                info("%s ACCEPT FROM UIDS: %s" % (self.tag, self.context.accept_from_auids) )        
                info("%s DECLINE FROM UIDS: %s" % (self.tag, self.context.decline_from_auids) )
                self.context.accepts_left = sorted( self.context.accept_from_auids[:] )
                self.context.declines_left = sorted( self.context.decline_from_auids[:] )
                return self.PingForInvite()
        
        info( "%s WAIT for accept uids... (so far: %s, need %d total)" % (self.tag, self.context.accept_from_auids, self.context.accepts_total_count) )
        info( "%s WAIT for decline uids... (so far: %s, need %d total)" % (self.tag, self.context.decline_from_auids, self.context.declines_total_count) )
            
            
    def PingForInvite(self):
        if self.context.invites_received:
            for master_auid in self.context.invites_received:
                # info("%s -> PARTY INVITE RECEIVED: from %d" % (self.tag, master_auid) )
                if self.context.declines_left and master_auid == self.context.declines_left[0]:
                    # сначала исполняем declines, чтобы можно было выполнять сценарии типа "на первый раз отказать, на второй принять"
                    info("%s DECLINE PARTY INVITE -> %d" % (self.tag, master_auid) )
                    self.context.PartyDecline()
                    
                elif self.context.accepts_left and master_auid == self.context.accepts_left[0]:
                    info("%s ACCEPT PARTY INVITE -> %d" % (self.tag, master_auid) )
                    self.context.PartyAccept( master_auid  )
                    
                    ##TODO: после успеха ACCEPT впилить self.ChooseHero?
                        
        if (self.context.accepts_left and len(self.context.accepts_left) > self.context.accepts_left_count) \
            or (self.context.declines_left and len(self.context.declines_left) > self.context.declines_left_count):
                info("%s PARTY PING" % self.tag )
                self.context.PartyPing()
        else:
            warning("%s ALL ACCEPTS/DECLINES EXECUTED, exiting..." % self.tag )
            self.Pass()
            return self.Exit()            
        
        return self.PingForInvite
        
        
# ------------------------------------------------------------------
# ------------------------------------------------------------------

class WaitForDisbandFSM(TimeoutFailFSM):
    """ ждем, пока по какой-то причине не отвалимся от партии (обычно это master партии делает нам kick, по PartyKickFSM) """
    def __init__(self, context, **kwargs):
        super(WaitForDisbandFSM, self).__init__(self.PingForDisband, context, **kwargs)
        self.context = context
        self.tag = context.tag
        self.context.disbanded_ok = 0

    def PingForDisband(self):
        if self.context.disbanded_ok:
            warning("%s DISBAND EXECUTED, exiting..." % self.tag )
            self.Pass()
            return self.Exit()            
            
        info("%s WaitForDisbandFSM PARTY PING" % self.tag )
        self.context.PartyPing()
        

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class PartyKickFSM(TimeoutFailFSM):
    """ кикаем всех юзеров, перечисленных в списке, по получению всех подтверждений делаем Pass """
    def __init__(self, context, kick_auids=[], kick_total_count=0, kick_left_count=0):
        super(PartyKickFSM, self).__init__(self.WaitForKickUidsFilled, context)
        self.context = context
        self.tag = context.tag
        self.context.kick_auids = kick_auids
        self.context.kick_total_count = kick_total_count
        self.context.kick_left_count = kick_left_count 

    def WaitForKickUidsFilled(self):
        if len(self.context.kick_auids) >= self.context.kick_total_count:
            info("%s KICK UIDS: %s" % (self.tag, self.context.kick_auids) )        
            self.context.kicks_left = self.context.kick_auids[:]
            self.context.disbands_left = self.context.kick_auids[:]
            return self.KickNext
        
        info( "%s WAIT for kick uids... (so far: %s, need %d total)" % (self.tag, self.context.kick_auids, self.context.kick_total_count) )
        
    def WaitForKickResponse(self):
        if self.context.party_response:
            return self.KickNext()
            
    def WaitForKickDisbands(self):
        info("%s WaitForKickDisbands PARTY PING" % self.tag )
        self.context.PartyPing()
        
        if not self.context.disbands_left:
            warning("%s ALL DISBANDS EXECUTED, exiting.." % self.tag )
            self.Pass()
            self.Exit()
            return 

        return self.WaitForKickDisbands
            
    def KickNext(self):
        if self.context.kicks_left:
            next = self.context.kicks_left.pop()
            warning("%s PARTY KICK -> %s" % (self.tag, next) )
            self.context.PartyKick( str(next) )
            return self.WaitForKickResponse
        else:
            warning("%s ALL KICKS EXECUTED, wait for disbands: %s" % (self.tag, self.context.disbands_left) )
            return self.WaitForKickDisbands
            


# ------------------------------------------------------------------
# ------------------------------------------------------------------

class ChooseHeroFSM(TimeoutFailFSM):
    """ клиент: выбирает своего героя (и ждет, пока от PS придет оповещение, что герой выбран) """    
    def __init__(self, context, hero_id=0, hero_crc=FIRST_HERO_CRC, fraction="A"): # crc32('assassin'))
        info("ChooseHeroFSM.__init__")
        super(ChooseHeroFSM, self).__init__(self.SetFraction, context)
        self.context = context
        self.tag = context.tag
        self.hero_id = hero_id
        self.hero_crc = hero_crc
        self.fraction = fraction
        
    def SetFraction(self):
        info("ChooseHeroFSM.SetFraction")
        assert self.fraction
        self.context.db = ClassDict()
        self.context.SetFraction(self.fraction)
        return self.WaitFraction

    def WaitFraction(self):
        info("ChooseHeroFSM.WaitFraction")
        if self.context.db and self.context.db.fraction:
            return self.ChooseHero
            
    def ChooseHero(self):
        info("%s ChooseHeroFSM.ChooseHero" % self.tag)
        self.context.choose_heroes_left.append( self.context.auid ) # проследим, чтобы нас оповестили, что мы же выбрали героя
        info( "%s choose_heroes_left: %s" % (self.tag, self.context.choose_heroes_left) )
        
        if not self.hero_id:
            info( "no valid hero specified: searching for hired hero in ModelData.." )
            # если герой не указан (или 0), нужно выбрать по списку первого подходящего (обязательно нанятого, а то ММ не стартует)
            if self.context.model:
                hk = pathFind(self.context.model, "ModelData/HeroesKeeper/Keeper")
                if hk:
                    for hero_id, value in hk.iteritems():
                        # info("checking hero_id %s, value %s" % (hero_id, value))
                        hero = value.get("Hero")
                        if hero and hero.get("Hired", False):
                            self.hero_id = hero_id
                            self.hero_crc = hero.get("PersistentId", 0)
                            info( "found hired hero: hero_id=%s, class=%s" % (self.hero_id, hero.get("class_name", "?")) )
                            break
                else:
                    return self.context.Fail("no HeroesKeeper found")
            else:
                return self.context.Fail("no ModelData found")
                
        self.context.PartyHero( self.hero_id, self.hero_crc )
        return self.WaitForChooseHero
        
    def WaitForChooseHero(self):
        info("ChooseHeroFSM.WaitForChooseHero")
        if not self.context.choose_heroes_left:
            warning("%s CHOOSE_HERO EXECUTED, exiting.." % self.tag )
            self.Pass()
            return self.Exit()
        
        info("%s WaitForChooseHero PARTY PING: choose_heroes_left %s" % (self.tag, self.context.choose_heroes_left) )
        self.context.PartyPing()
        
# ------------------------------------------------------------------
# ------------------------------------------------------------------

class ChooseAllPartyHeroesFSM( ChooseHeroFSM ):
    """ мастер: выбирает героя сам и ждет, пока все перечисленные в choose_auids[] юзеры выберут героев """
    def __init__(self, context, **kwargs):
        info("ChooseAllPartyHeroesFSM.__init__")
        super(ChooseAllPartyHeroesFSM, self).__init__(context, **kwargs)
        
    # OVERRIDE
    def ChooseHero(self):
        info("ChooseAllPartyHeroesFSM.ChooseHero")
        ##self.context.choose_heroes_left.extend( self.choose_auids ) # добавляем auid-ы всех остальных юзеров -- это теперь делается в Invite-fsm
        info( "%s choose_heroes_left: %s" % (self.tag, self.context.choose_heroes_left) )
        return super(ChooseAllPartyHeroesFSM, self).ChooseHero()

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class PartyGoFSM( TimeoutFailFSM ):
    """ мастер: стартует party matchmaking """
    def __init__(self, context, game_type="pvp", **kwargs):
        info("PartyGoFSM.__init__")
        super(PartyGoFSM, self).__init__(self.Go, context, **kwargs)
        self.tag = self.context.tag
        self.game_type = game_type
        
    def Go(self):
        info("%s PartyGoFSM.GO" % self.tag)
        self.context.party_go = 0
        self.context.PartyGo( self.game_type )
        return self.WaitForPartyGo

    def WaitForPartyGo(self):
        warning("PartyGoFSM.WaitForPartyGo")
        if self.context.party_go:
            warning("%s PARTY GO EXECUTED, exiting.." % self.tag )
            self.Pass()
            return self.Exit()
        
        info("%s WaitForPartyGo PARTY PING" % (self.tag) )
        self.context.PartyPing()


# ------------------------------------------------------------------
# ------------------------------------------------------------------

class PartyWaitForGoFSM( PartyGoFSM ):
    """ party member: ждет, пока кто-нибудь стартует party matchmaking """
    def Go(self):
        info("%s PartyWaitForGoFSM.GO" % self.tag)
        self.context.party_go = 0
        return self.WaitForPartyGo

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class CheckPartyMmPingFSM( TimeoutFailFSM ):
    """ выполняем mm_ping и проверяем, что в ответе нормальная party mm session, со всеми нашими членами партии """
    def __init__(self, context, game_type="pvp", master_auids=[], member_auids=[], check_progress=0, **kwargs):
        info("CheckPartyMmPingFSM.__init__")
        super(CheckPartyMmPingFSM, self).__init__(self.Ping, context, **kwargs)
        self.in_master_auids = master_auids
        self.in_member_auids = member_auids
        self.tag = self.context.tag
        self.game_type = game_type
        self.check_progress = check_progress
        
    def Ping(self):
        self.party_auids = self.in_master_auids[:]
        self.party_auids.extend( self.in_member_auids )
        self.context.mm = context.Matchmaking( 0 ) # временная структура: мы еще сами не знаем своего mmid
        info("%s CheckPartyMmPingFSM.Ping, self.context.mm=%s" % (self.tag, self.context.mm))
        self.context.PingMM()
        return self.WaitForPingReply
        
    def WaitForPingReply(self):
        warning("CheckPartyMmPingFSM.WaitForPingReply")
        if self.context.mm.mmid:
            #TODO: ASSERT правильный формат ответа mm_ping, наличие всех членов партии и т.п.
            party_id = toint( self.context.mm.lastPingResponse.get("party_id") )
            party_auids = str(self.context.mm.lastPingResponse.get("party_auids"))
            game_type = str(self.context.mm.lastPingResponse.get("game_type"))
            progress = toint(self.context.mm.lastPingResponse.get("progress"))
            self_party_auids_string = strList( sorted(self.party_auids) )
            
            warning( "%s PARTY MM PING EXECUTED: party_id %d, self.context.party_id %d, game_type %s, self.game_type %s\n     party_auids: %r \nself.party_auids: %r" \
                % (self.tag, party_id, self.context.party_id, game_type, self.game_type, party_auids, self_party_auids_string) )
            
            try:
                assert party_id == self.context.party_id
                assert party_auids == self_party_auids_string
                assert game_type == self.game_type
                if self.check_progress:
                    warning( "%s (more MM PING params): progress %d, self.check_progress %s" \
                        % (self.tag, progress, self.check_progress) )
                    assert progress == self.check_progress
                self.Pass()
            except AssertionError, ex:
                catch()
                self.context.Fail("mm ping assertion failed")
                self.context.mm.sessionId = None # чтобы не пытались потом запускать pvx клиент с заведомо неправильным ключом
            
            return self.Exit()
        
        info("%s WaitForPingReply PARTY MM PING" % (self.tag) )


# ------------------------------------------------------------------
# ------------------------------------------------------------------

class CheckNoMmPingFSM( TimeoutFailFSM ):
    """ выполняем mm_ping и проверяем, что в ответе no active sessions """
    def __init__(self, context, **kwargs):
        info("CheckNoMmPingFSM.__init__")
        super(CheckNoMmPingFSM, self).__init__(self.Ping, context, **kwargs)
        self.tag = self.context.tag
        
    def Ping(self):
        info("%s CheckNoMmPingFSM.Ping" % (self.tag))
        self.context.CheckNoPingMM()
        return self.WaitForPingReply
        
    def WaitForPingReply(self):
        if self.context.receivedFailMessage("no active matchmaking sessions"):
            # expectFailMessage сбросился, значит случился ожидаемый context.Fail( no active sessions )
            self.Pass()
            self.Exit()
            return
        info("%s CheckNoMmPingFSM.WaitForPingReply" % (self.tag))
            
        
# ------------------------------------------------------------------
# ------------------------------------------------------------------

class PartyMatchmakingFSM( main_fsm.MatchmakingFSM ): 

    def __init__(self, context, cancelCount=0):
        # параметры mm-сессии достанем на старте, прямо из существующего context.mm
        main_fsm.MatchmakingFSM.__init__(self, context, 0, "N", "none", cancelCount)

    def Check(self):
        try:
            assert self.context.mm
            assert self.context.mm.mmid
            assert self.context.db
            assert self.context.db.fraction
            assert self.context.mm.heroId
            assert self.context.mm.gameType
            
            self.hero = self.context.mm.heroId
            self.fraction = self.context.db.fraction
            self.gameType = self.context.mm.gameType
            
            return self.WaitForPending
            
        except AssertionError, ex:
            catch()
            self.context.Fail( "PartyMatchmakingFSM: bad context (failed initial assert checks)")                
        
