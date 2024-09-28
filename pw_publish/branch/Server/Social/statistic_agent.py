# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# Mock Social Aggregator web-server
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, json, logging
import functools

import tornado.options
from tornado.options import define, options
from tornado.httpclient import HTTPRequest

from base.helpers import *

sys.path.append('cfg')
import coord_cfg

from iwebserver import *
from ifactory import IfaceFactory
from iuserdata import IDataManager

from handlers import * # JsonHandler, IfaceFactory
from subaction import SubAction

import EC
        
## ---------------------------------------------------------------------------------------------
## THRIFT
sys.path.append('thrift_pw/statistics/gen-py')

from StatisticCore import StatisticService
from StatisticCore.ttypes import * # LoginInfo, ...

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

SSTAT_CONNECT_TIOMEOUT = 30.0
SSTAT_REQUEST_TIOMEOUT = 60.0

## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class PacketTracker(object):
    "A container to keep track of package ids received."

    def __init__(self, clear_rate = 60, clear_age = 100):
        # clear_rate - how often to remove very old packet ids
        # clear_age - how old (in number of claer_rates) should be packet id to be removed
        self.fresh = set() # packet ids received during the current tick
        self.old = dict()  # all over ids
        self.rate = clear_rate
        self.max_age = clear_age * clear_rate # store it's value in ticks
        self.tick_count = 0

    def __len__(self):
        return len(self.fresh) + len(self.old)

    def check(self, pkt_id):
        return not((pkt_id in self.fresh) or (pkt_id in self.old))

    def add(self, pkt_id):
        self.fresh.add(pkt_id)

    def tick(self):
        self.tick_count += 1
        self.old.update( (k, self.tick_count) for k in self.fresh )
        self.fresh.clear()
        if self.tick_count % self.rate == 0:
            border = self.tick_count - self.max_age
            for k, v in self.old.items(): # NOTE: not iteritems() because of del() calls
                if v < border:
                    del self.old[k]


class StatisticAgentHandler( JsonHandler ):
    """ main http request mapper (раскидываем запросы по handler methods, в зависимости от "/subaddr" и "action=") """
    
    def __init__( self, application, request, I, SERVICES={}, **kwargs):
        JsonHandler.__init__( self, application, request, **kwargs )
        self._SERVICES = SERVICES
        self.I = I # server interface dict

    ##-------------------------------------------------------------------------------------
    
    def get(self):
        raise tornado.web.HTTPError(400)
    
    ##-------------------------------------------------------------------------------------
    def post(self):
        params = self.request.arguments
        info( "Stats Post Params: " + str(params) )
        self.response = { "server": STATISTIC_SERVER_NAME }
        
        try:
            packet_id = params.get('packet_id')
            if packet_id and type(packet_id) == list:
                packet_id = packet_id[0]
            else:
                warn("STRANGE: packet_id = %r" % (packet_id,))

            if self.I.WS.tracker.check(packet_id):
                info( "Packet #%s: Stats body: %r" % (packet_id, self.request.body) )
                all_args = json_loads( self.request.body )
                info( "Stats Args: " + str(all_args) )
                self.I.WS.processRawData(packet_id, all_args)
            else:
                warn("Duplicate packet #%s, body %r" % (packet_id, self.request.body))
                self.response["dup"] = 1

                # send reply (ok)
            self.set_header("Content-Type", "text/plain")
            self.set_header("charset", "UTF-8")

            self.response["ok"] = 1
            self.response['packet_id'] = packet_id

            self.write(self.response)
            self.finish()
            return 
            
        except:
            catch()
            
        #FAIL:
        raise tornado.web.HTTPError(403)
    
    
## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

def constructResourcesChangeInfo(**args):
    dict_rchange = args["rchange"].__dict__ if not isinstance(args["rchange"], dict) else args["rchange"]

    thrift_rchange = ResourceTable(Gold=toint(dict_rchange["Gold"]), Silver=toint(dict_rchange["Silver"]), Perl=toint(dict_rchange["Perl"]),
                                   RedPerl=toint(dict_rchange["RedPerl"]), Population=toint(dict_rchange["Population"]), Resource1=toint(dict_rchange["Resource1"]),
                                   Resource2=toint(dict_rchange["Resource2"]), Resource3=toint(dict_rchange["Resource3"]), Shard=toint(dict_rchange["Shard"]), Currencies = dict_rchange['Currencies'])
    dict_rtotal = args["rtotal"].__dict__ if not isinstance(args["rtotal"], dict) else args["rtotal"]

    thrift_rtotal = ResourceTable(Gold=toint(dict_rtotal["Gold"]), Silver=toint(dict_rtotal["Silver"]), Perl=toint(dict_rtotal["Perl"]),
                                  RedPerl=toint(dict_rtotal["RedPerl"]), Population=toint(dict_rtotal["Population"]), Resource1=toint(dict_rtotal["Resource1"]),
                                  Resource2=toint(dict_rtotal["Resource2"]), Resource3=toint(dict_rtotal["Resource3"]), Shard=toint(dict_rtotal["Shard"]), Currencies = dict_rtotal['Currencies'])
    return ResourcesChangeInfo(auid=args["auid"], gain=args["gain"], source=args["source"], buildingname = args["buildingname"],
                               rchange=thrift_rchange, rtotal=thrift_rtotal, timestamp=args["timestamp"])

def constructQuestChangeInfo(**args):
    return QuestChangeInfo(auid=args["auid"], questid=args["questid"], reason=args["reason"], timestamp=args["timestamp"])

def constructDynamicQuestChangeInfo(**args):
    return DynamicQuestChangeInfo(auid=args["auid"], questindex=args["questindex"], questname=args["questname"], reason=args["reason"],
                                  timestamp=args["timestamp"], alternativeline=args["alternativeline"])

def constructTournamentQuestChangeInfo(**args):
    return TournamentQuestChangeInfo(auid=args["auid"], questindex=args["questindex"], questname=args["questname"], reason=args["reason"],
                                  timestamp=args["timestamp"], alternativeline=args["alternativeline"])

def constructTutorialStateChangeInfo(**args):
    return TutorialStateChangeInfo(auid=args["auid"], tutorialstate=args["tutorialstate"], timestamp=args["timestamp"])

def constructTalentChangeInfo(**args):
    if isinstance( args["talent"], TalentInfo ):
        dict_tr = TalentInfo( toint(args["talent"].classId), toint(args["talent"].instanceId), 
                                                        toint(args["talent"].boundHeroClassId) )
    else:
        dict_tr = TalentInfo( toint(args["talent"]["classId"]), toint(args["talent"]["instanceId"]), 
                                                        toint(args["talent"]["boundHeroClassId"]) )
    return TalentChangeInfo(auid=args["auid"], talent=dict_tr, operation=args["operation"], timestamp=args["timestamp"],
                            data=args["data"])

def constructFactionSelectInfo(**args):
    dict_rchange = args["rchange"]
    thrift_rchange = ResourceTable(Gold=toint(dict_rchange["Gold"]), Silver=toint(dict_rchange["Silver"]), Perl=toint(dict_rchange["Perl"]),
                                   RedPerl=toint(dict_rchange["RedPerl"]), Population=toint(dict_rchange["Population"]), Resource1=toint(dict_rchange["Resource1"]),
                                   Resource2=toint(dict_rchange["Resource2"]), Resource3=toint(dict_rchange["Resource3"]), Shard=toint(dict_rchange["Shard"]))
    dict_rtotal = args["rtotal"]
    thrift_rtotal = ResourceTable(Gold=toint(dict_rtotal["Gold"]), Silver=toint(dict_rtotal["Silver"]), Perl=toint(dict_rtotal["Perl"]),
                                  RedPerl=toint(dict_rtotal["RedPerl"]), Population=toint(dict_rtotal["Population"]), Resource1=toint(dict_rtotal["Resource1"]),
                                  Resource2=toint(dict_rtotal["Resource2"]), Resource3=toint(dict_rtotal["Resource3"]), Shard=toint(dict_rtotal["Shard"]))
    return FactionSelectInfo(auid=args["auid"], oldfaction =args["oldfaction"], newfaction=args["newfaction"],
                             rchange=thrift_rchange, rtotal=thrift_rtotal, timestamp=args["timestamp"])


def constructBanInfo(**args):
    args['type'] = GMUserOperationType.Ban
    return GMUserOperationInfo(**args)

def constructMuteInfo(**args):
    args['type'] = GMUserOperationType.Mute
    return GMUserOperationInfo(**args)

def constructUnbanInfo(**args):
    args['type'] = GMUserOperationType.Unban
    return GMUserOperationInfo(**args)

def constructUnmuteInfo(**args):
    args['type'] = GMUserOperationType.Unmute
    return GMUserOperationInfo(**args)

def constructForgiveInfo(**args):
    args['type'] = GMUserOperationType.Forgive
    return GMUserOperationInfo(**args)

def constructSetLeaveInfo(**args):
    args['type'] = GMUserOperationType.SetLeave
    return GMUserOperationInfo(**args)

def constructModeratorMuteInfo(**args):
    args['type'] = GMUserOperationType.ModeratorMute
    return GMUserOperationInfo(**args)


def constructUnlockHeroInfo( **args ):
    dict_rchange = args["rchange"]
    thrift_rchange = ResourceTable( Gold=toint(dict_rchange["Gold"]), Silver=toint(dict_rchange["Silver"]), Perl=toint(dict_rchange["Perl"]), RedPerl=toint(dict_rchange["RedPerl"]), Population=toint(dict_rchange["Population"]), Resource1=toint(dict_rchange["Resource1"]), Resource2=toint(dict_rchange["Resource2"]), Resource3=toint(dict_rchange["Resource3"]), Shard=toint(dict_rchange["Shard"]) )
    dict_rtotal = args["rtotal"]
    thrift_rtotal = ResourceTable( Gold=toint(dict_rtotal["Gold"]), Silver=toint(dict_rtotal["Silver"]), Perl=toint(dict_rtotal["Perl"]), RedPerl=toint(dict_rtotal["RedPerl"]), Population=toint(dict_rtotal["Population"]), Resource1=toint(dict_rtotal["Resource1"]), Resource2=toint(dict_rtotal["Resource2"]), Resource3=toint(dict_rtotal["Resource3"]), Shard=toint(dict_rtotal["Shard"]) )
    return UnlockHeroInfo( auid=args["auid"], heroid=args["heroid"], rchange=thrift_rchange, rtotal=thrift_rtotal, timestamp=args["timestamp"] )

def constructSessionAwardsInfo( **args ):
    dict_rchange = args["rchange"]
    thrift_rchange = ResourceTable( Gold=toint(dict_rchange["Gold"]), Silver=toint(dict_rchange["Silver"]),
                                    Perl=toint(dict_rchange["Perl"]), RedPerl=toint(dict_rchange["RedPerl"]), Population=toint(dict_rchange["Population"]),
                                    Resource1=toint(dict_rchange["Resource1"]), Resource2=toint(dict_rchange["Resource2"]),
                                    Resource3=toint(dict_rchange["Resource3"]), Shard=toint(dict_rchange["Shard"]), CWPoints_Player=toint(dict_rchange["CWPoints_Player"]) )
    dict_rtotal = args["rtotal"]
    thrift_rtotal = ResourceTable( Gold=toint(dict_rtotal["Gold"]), Silver=toint(dict_rtotal["Silver"]),
                                   Perl=toint(dict_rtotal["Perl"]), RedPerl=toint(dict_rtotal["RedPerl"]), Population=toint(dict_rtotal["Population"]),
                                   Resource1=toint(dict_rtotal["Resource1"]), Resource2=toint(dict_rtotal["Resource2"]),
                                   Resource3=toint(dict_rtotal["Resource3"]), Shard=toint(dict_rtotal["Shard"]), CWPoints_Player=toint(dict_rtotal["CWPoints_Player"]) )
    
    thrift_talents = []
    for tal in args["talents"]:
        if isinstance( tal, TalentInfo ):
            dict_tr = TalentInfo( toint(tal.classId), toint(tal.instanceId), toint(tal.boundHeroClassId) )
        else:
            dict_tr = TalentInfo( toint(tal["classId"]), toint(tal["instanceId"]), toint(tal["boundHeroClassId"]) )
        thrift_talents.append( dict_tr )
    lpc = args["leaverpointschange"]
    leaverpointschange = LeaverPointsChangeInfo(
          auid = lpc["auid"],
          type = lpc["type"],
          leaverpointschange = lpc["leaverpointschange"],
          leaverpointstotal = lpc["leaverpointstotal"],
          isleaverchanged = lpc["isleaverchanged"],
          isleaver = lpc["isleaver"],
          isbadbehaviour = lpc["isbadbehaviour"],
          timestamp = lpc["timestamp"],
    )
    return SessionAwardsInfo( auid=args["auid"], sessionpersistentid=args["sessionpersistentid"], nick=args["nick"],
              heroid=args["heroid"],
              inc_reliability=args["inc_reliability"], new_reliability=args["new_reliability"], talents=thrift_talents,
              rchange=thrift_rchange, rtotal=thrift_rtotal, timestamp=args["timestamp"], force=args["force"],
              guildpointschange=args["guildpointschange"], guildpointstotal=args["guildpointstotal"],
              appliedbuffs=args["appliedbuffs"], leaverpointschange=leaverpointschange)

def constructGuildInfo( **args ):
    dict_rchange = args["rchange"]
    thrift_rchange = ResourceTable( Gold=toint(dict_rchange["Gold"]), Silver=toint(dict_rchange["Silver"]), Perl=toint(dict_rchange["Perl"]), RedPerl=toint(dict_rchange["RedPerl"]), Population=toint(dict_rchange["Population"]), Resource1=toint(dict_rchange["Resource1"]), Resource2=toint(dict_rchange["Resource2"]), Resource3=toint(dict_rchange["Resource3"]), Shard=toint(dict_rchange["Shard"]))
    dict_rtotal = args["rtotal"]
    thrift_rtotal = ResourceTable( Gold=toint(dict_rtotal["Gold"]), Silver=toint(dict_rtotal["Silver"]), Perl=toint(dict_rtotal["Perl"]), RedPerl=toint(dict_rtotal["RedPerl"]), Population=toint(dict_rtotal["Population"]), Resource1=toint(dict_rtotal["Resource1"]), Resource2=toint(dict_rtotal["Resource2"]), Resource3=toint(dict_rtotal["Resource3"]), Shard=toint(dict_rtotal["Shard"]))

    coreInfo = GuildCoreInfo(auid=args["auid"], guildid=args["guildid"], timestamp=args["timestamp"], faction=args["faction"], guildmembers=args["guildmembers"])
    return GuildInfo( coreInfo=coreInfo, shortname=args["shortname"], fullname=args["fullname"], rchange=thrift_rchange, rtotal=thrift_rtotal )

def constructGuildCoreInfo( **args ):
    return GuildCoreInfo(auid=args["auid"], guildid=args["guildid"], timestamp=args["timestamp"], faction=args["faction"], guildmembers=args["guildmembers"])

def constructGuildLeaveInfo( **args ):
    coreInfo = GuildCoreInfo( auid=args["auid"], guildid=args["guildid"], timestamp=args["timestamp"], faction=args["faction"], guildmembers=args["guildmembers"] )
    return GuildLeaveInfo( coreInfo=coreInfo, kicked=args["kicked"] )

def constructGuildShopBuyInfo( **args ):
    dict_rchange = args["rchange"]
    thrift_rchange = ResourceTable( Gold=toint(dict_rchange["Gold"]), Silver=toint(dict_rchange["Silver"]), Perl=toint(dict_rchange["Perl"]), RedPerl=toint(dict_rchange["RedPerl"]), Population=toint(dict_rchange["Population"]), Resource1=toint(dict_rchange["Resource1"]), Resource2=toint(dict_rchange["Resource2"]), Resource3=toint(dict_rchange["Resource3"]), Shard=toint(dict_rchange["Shard"]), CWPoints_Player=toint(dict_rchange["CWPoints_Player"]) )
    dict_rtotal = args["rtotal"]
    thrift_rtotal = ResourceTable( Gold=toint(dict_rtotal["Gold"]), Silver=toint(dict_rtotal["Silver"]), Perl=toint(dict_rtotal["Perl"]), RedPerl=toint(dict_rtotal["RedPerl"]), Population=toint(dict_rtotal["Population"]), Resource1=toint(dict_rtotal["Resource1"]), Resource2=toint(dict_rtotal["Resource2"]), Resource3=toint(dict_rtotal["Resource3"]), Shard=toint(dict_rtotal["Shard"]), CWPoints_Player=toint(dict_rtotal["CWPoints_Player"]) )
    return GuildShopBuyInfo( auid=args["auid"], guildid=args["guildid"], hassuzerain=args["hassuzerain"], shoplevel=args["shoplevel"],
                           shopitemid=args["shopitemid"], rchange=thrift_rchange, rtotal=thrift_rtotal, guildpointschange=args["guildpointschange"], guildpointstotal=args["guildpointstotal"], timestamp=args["timestamp"] )

def constructGuildDailyStatsInfo( **args ):
    thrift_vassals = []
    thrift_recommended_vassals = []
    for vassal in args["vassals"]:
        if isinstance( vassal, GuildDailyStatsVassalInfo ):
            dict_tr = GuildDailyStatsVassalInfo(toint(vassal.guildid), toint(vassal.guildpoints))
        else:
            dict_tr = GuildDailyStatsVassalInfo(toint(vassal["guildid"]), toint(vassal["guildpoints"]))
        thrift_vassals.append(dict_tr)
    for vassal in args["suggested"]:
        if isinstance( vassal, GuildDailyStatsSuggestedInfo ):
            dict_tr = GuildDailyStatsSuggestedInfo(toint(vassal.guildid), toint(vassal.guildrating))
        else:
            dict_tr = GuildDailyStatsSuggestedInfo(toint(vassal["guildid"]), toint(vassal["guildrating"]))
        thrift_recommended_vassals.append(dict_tr)
    return GuildDailyStatsInfo(guildid=args["guildid"], guildrating=args["guildrating"], guildratingtoday=args["guildratingtoday"],
                               guildpoints=args["guildpoints"], guildrank=args["guildrank"], timestamp=args["timestamp"],
                               vassals=thrift_vassals, suggested=thrift_recommended_vassals)


def constructGuildSiegeInfo(**kwargs):
    kwargs['participants'] = [
        GuildSiegeParticipantInfo(
            guildid=part['id'],
            guildrating=part['rating'],
            starttimestamp=part['start'],
            endtimestamp=part.get('leave') or kwargs['endtimestamp'],
            siegepoints=part['score'],
            guildpointsprice=part['price'],
        )
        for part in kwargs['participants']
    ]
    return GuildSiegeInfo(**kwargs)

def constructAfterPartyInfo(**kwargs):
    kwargs['members'] = [
        AfterPartyMemberInfo(
        auid=member['auid'],
        sessionPersistentId=member['sessionPersistentId'],
        kicked=member['kicked'],
        leaved=member['leaved'],
        )
        for member in kwargs['members']
    ]
    return AfterPartyInfo(**kwargs)

class StatisticAgentServer( ITornadoServer ):
    
    _THRIFT_TYPES = dict(
        LoginUsers=LoginInfo,
        LogoutUsers=LoginInfo,
        MoveTalentToSet=MoveTalentInfo,
        MoveTalentFromSet=MoveTalentInfo,
        UnlockHero=constructUnlockHeroInfo,
        JoinPvpSession=JoinSessionInfo,
        ChatMessages=ChatMessageInfo,
        BanUser=constructBanInfo,
        MuteUser=constructMuteInfo,
        ModeratorMuteUser=constructModeratorMuteInfo,
        UnbanUser=constructUnbanInfo,
        UnmuteUser=constructUnmuteInfo,
        ForgiveUser=constructForgiveInfo,
        SetLeaveUser=constructSetLeaveInfo,
        GMEditUser=GMEditFieldInfo,
        GMUnlockHero=GMHeroActionInfo,
        GMLockHero=GMHeroActionInfo,
        MonitoringResults=MonitoringResultInfo,
        AddIgnore=AddIgnoreInfo,
        RemoveIgnore=RemoveIgnoreInfo,
        GiveSessionAwards=constructSessionAwardsInfo,
        LauncherStart=LauncherInfo,
        LauncherEvents=LauncherEventsInfo,
        LauncherDActions=LauncherDActionsInfo,
        SocialRegister=SocialRegisterInfo,
        SocialJoin=SocialJoinInfo,
        SocialMerge=SocialMergeInfo,
        ResourcesChange=constructResourcesChangeInfo,
        QuestChange=constructQuestChangeInfo,
        DynamicQuestChange=constructDynamicQuestChangeInfo,
        TournamentQuestChange=constructTournamentQuestChangeInfo,
        TutorialStateChange=constructTutorialStateChangeInfo,
        TalentChange=constructTalentChangeInfo,
        FactionSelect=constructFactionSelectInfo,
        RatingChange=RatingChangeInfo,
        HeroLevelChange=HeroLevelChangeInfo,
        HeroRankChange=HeroRankChangeInfo,
        CastleLevelChange=CastleLevelChangeInfo,
        GuildCreated=constructGuildInfo,
        GuildRenamed=constructGuildInfo,
        GuildJoined=constructGuildCoreInfo,
        GuildLeaved=constructGuildLeaveInfo,
        GuildDisbanded=constructGuildCoreInfo,
        ClientPings=ClientPingInfo,
        RuneExpire=RuneExpireInfo,
        RuneUnsoulbound=RuneSoulboundInfo,
        RuneReplenish=RuneReplenishInfo,
        RuneHeroApply=RuneHeroApplyInfo,
        GMOperation=GMOperationInfo,
        GMUserOperation=GMUserOperationInfo,
        UserClaims=ClaimInfo,
        GuildShopBuy=constructGuildShopBuyInfo,
        GuildDailyStats=constructGuildDailyStatsInfo,
        GuildInteraction=GuildInteractionInfo,
        GuildSiege=constructGuildSiegeInfo,
        GuildPointsChange=GuildPointsChangeInfo,
        AfterParty=constructAfterPartyInfo,
        LeaverPointsChange=LeaverPointsChangeInfo,
        RuneRoll=RuneRollInfo,
        GWEventAdd=GWEventInfo,
        GWScoreChange=GWScoreChangeInfo,
        ReRollShop=ReRollShopInfo,
        QuestEventStageChange=QuestEventsStagesInfo,
        QuestEventStateChange=QuestEventsStatesInfo,
    )
    
    _THRIFT_LIST_METHODS = dict(
        LoginUsers=StatisticService.Client.send_LoginUsers,
        LogoutUsers=StatisticService.Client.send_LogoutUsers,
        MoveTalentToSet=StatisticService.Client.send_MoveTalentToSet,
        MoveTalentFromSet=StatisticService.Client.send_MoveTalentFromSet,
        UnlockHero=StatisticService.Client.send_UnlockHero,
        JoinPvpSession=StatisticService.Client.send_JoinPvpSession,
        ChatMessages=StatisticService.Client.send_ChatMessages,
        BanUser=StatisticService.Client.send_GMUserOperation,
        MuteUser=StatisticService.Client.send_GMUserOperation,
        ModeratorMuteUser=StatisticService.Client.send_GMUserOperation,
        UnbanUser=StatisticService.Client.send_GMUserOperation,
        UnmuteUser=StatisticService.Client.send_GMUserOperation,
        ForgiveUser=StatisticService.Client.send_GMUserOperation,
        SetLeaveUser=StatisticService.Client.send_GMUserOperation,
        GMEditUser=StatisticService.Client.send_GMEditUser,
        GMUnlockHero=StatisticService.Client.send_GMUnlockHero,
        GMLockHero=StatisticService.Client.send_GMLockHero,
        MonitoringResults=StatisticService.Client.send_MonitoringResults,
        AddIgnore=StatisticService.Client.send_AddIgnore,
        RemoveIgnore=StatisticService.Client.send_RemoveIgnore,
        GiveSessionAwards=StatisticService.Client.send_GiveSessionAwards,
        LauncherStart=StatisticService.Client.send_LauncherStart,
        LauncherEvents=StatisticService.Client.send_LauncherEvents,
        LauncherDActions=StatisticService.Client.send_LauncherDActions,
        SocialRegister=StatisticService.Client.send_SocialRegister,
        SocialJoin=StatisticService.Client.send_SocialJoin,
        SocialMerge=StatisticService.Client.send_SocialMerge,
        ResourcesChange=StatisticService.Client.send_ResourcesChange,
        QuestChange=StatisticService.Client.send_QuestChange,
        DynamicQuestChange=StatisticService.Client.send_DynamicQuestChange,
        TournamentQuestChange=StatisticService.Client.send_TournamentQuestChange,
        TutorialStateChange=StatisticService.Client.send_TutorialStateChange,
        TalentChange=StatisticService.Client.send_TalentChange,
        FactionSelect=StatisticService.Client.send_FactionSelect,
        RatingChange=StatisticService.Client.send_RatingChange,
        HeroLevelChange=StatisticService.Client.send_HeroLevelChange,
        HeroRankChange=StatisticService.Client.send_HeroRankChange,
        CastleLevelChange=StatisticService.Client.send_CastleLevelChange,
        GuildCreated=StatisticService.Client.send_GuildCreated,
        GuildRenamed=StatisticService.Client.send_GuildRenamed,
        GuildJoined=StatisticService.Client.send_GuildJoined,
        GuildLeaved=StatisticService.Client.send_GuildLeaved,
        GuildDisbanded=StatisticService.Client.send_GuildDisbanded,
        ClientPings=StatisticService.Client.send_ClientPings,
        RuneExpire=StatisticService.Client.send_RuneExpire,
        RuneUnsoulbound=StatisticService.Client.send_RuneUnsoulbound,
        RuneReplenish=StatisticService.Client.send_RuneReplenish,
        RuneHeroApply=StatisticService.Client.send_RuneHeroApply,
        GMOperation=StatisticService.Client.send_GMOperation,
        GMUserOperation=StatisticService.Client.send_GMUserOperation,
        UserClaims=StatisticService.Client.send_UserClaims,
        GuildShopBuy=StatisticService.Client.send_GuildShopBuy,
        GuildDailyStats=StatisticService.Client.send_GuildDailyStats,
        GuildInteraction=StatisticService.Client.send_GuildInteraction,
        GuildSiege=StatisticService.Client.send_GuildSiege,
        GuildPointsChange=StatisticService.Client.send_GuildPointsChange,
        AfterParty=StatisticService.Client.send_AfterParty,
        LeaverPointsChange=StatisticService.Client.send_LeaverPointsChange,
        RuneRoll=StatisticService.Client.send_RuneRoll,
        GWEventAdd=StatisticService.Client.send_GWEventAdd,
        GWScoreChange=StatisticService.Client.send_GWScoreChange,
        ReRollShop=StatisticService.Client.send_ReRollShop,
        QuestEventStageChange=StatisticService.Client.send_QuestEventStageChange,
        QuestEventStateChange=StatisticService.Client.send_QuestEventStateChange,
    )
    
    # ----------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------
    
    def __init__(self, **kwargs):
        super(StatisticAgentServer, self).__init__( **kwargs )
        self.tracker = PacketTracker()

        # заводим пустые списки для кэширования отправляемых thrift-объектов
        for ttypename in self._THRIFT_TYPES:
            setattr( self, ttypename, [] )
        
        #FIXME: адрес статистики пока берем напрямую из конфига (вообще-то надо бы получать по сети от координатора)
        self.initTransportClient()
                
    # -----------------------------------------------
    # OVERRIDE для тестов 
    def initTransportClient(self):
        pass
        #~ if coord_cfg.COORDINATOR_STATS_URL:
            #~ self.http_client = THttpClient.THttpClient( coord_cfg.COORDINATOR_STATS_URL )
            #~ self.transport = TTransport.TBufferedTransport( self.http_client )
            #~ self.protocol = TBinaryProtocol.TBinaryProtocolAccelerated( self.transport )
            #~ self.client = StatisticService.Client( self.protocol )
            #~ self.transport.open()
        
    # -----------------------------------------------
    def tick(self):
        self.sendThrift()
        self.tracker.tick()

    # -----------------------------------------------
    def initHandlers(self, application):
        application.add_handlers( r"(.*)", [ 
            ( r"/x", StatisticAgentHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I) ),
        ] )
            
        
    # -----------------------------------------------
    # return True if startup enviroment is bad
    @staticmethod
    def checkStartupFail():
        # проверяем, не слушает ли на нашем порту кто-то еще (защита от повторного запуска координатора)
        self_addr = "127.0.0.1:"+str(options.port)
        res = httpClientRequest( addr=self_addr, server="x", params="action=check_alive&name=_statistic_server_" )
        if res and res.get("ok") != None:
            fatal( "DUPLICATE STATISTIC SERVER: already listening on " + self_addr + "\n(reply was %s)" % str(res) )
            return True # обламываемся, уже запущена копия веб-сервера на этом порту
            
        print( "check startup environment: ok, port free (" + self_addr + ")" )
        
        
    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = STATISTIC_SERVER_ID
            options.server_name = STATISTIC_SERVER_NAME
            options.server_class = "stats"
        else:
            options["server_id"].set(STATISTIC_SERVER_ID)
            options["server_name"].set(STATISTIC_SERVER_NAME)
            options["server_class"].set("stats")

    # -----------------------------------------------
    @staticmethod
    def initInterfaces( classOf=None ):
        iDict = ClassDict()

        # http-клиент, нужен для отправки thrift-пакетов и лог-мониторинга
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient(max_clients=coord_cfg.COORDINATOR_HTTP_CURL_WORKERS)
        
        iDict.WS = IWebServer()  # чисто для генерации GUID-ов

        return iDict

    # ----------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------
    # обработчик стат. данных нам удобнее держать прямо в сервере 
    # (чтобы в тестах даже не создавать StatisticAgentHandler при передаче запросов напрямую, без HTTP)
    def processRawData(self, packet_id, stats_data):
        self.tracker.add(packet_id)
        for key,arglist in stats_data.iteritems():
            ttype = self._THRIFT_TYPES.get(key)
            if ttype:
                if isinstance(arglist, list):
                    for args in arglist:
                        deunicode_dict( args )
                        info( "to add: key %r, args %r" % (key, args) )
                        try:
                            t = ttype( **args )
                        except:
                            catch()
                            warn( "failed: key %r, args %r" % (key, args) )
                        self.addThriftType(key, t)
                else:
                    warn( "bad arglist %r for key %r (list of ttype dicts expected: [{k:v,k:v,},])" % (arglist, key) )
            else:
                warn( "bad stats key %r (no such thrift type)" % key )
                
                
    # ----------------------------------------------------------------------------------------------
    # добавляем очередной thrift-объект в соответствующий tosend-список
    def addThriftType( self, ttypename, t ):
        tlist = getattr( self, ttypename )
        tlist.append( t )
        
    # ----------------------------------------------------------------------------------------------
    # методы для пересылки берутся из self._THRIFT_LIST_METHODS
    # (поэтому если хотим для тестов подменить механизм пересылки, нужно подменить self.client на аналог StatisticService.Client, 
    #  а values в _THRIFT_LIST_METHODS на аналоги его методов)
    def sendThrift( self ):
        t0 = time.clock()
        
        # часть thrift-методов принимает сразу списки записей
        for ttypename, method in self._THRIFT_LIST_METHODS.iteritems():
            tlist = getattr( self, ttypename )
            if tlist:
                packet_id = self.I.WS.nextUid("stats")
                info( "sendThrift LIST: key=%r, data=%r, packet_id=%s" % (ttypename, tlist, packet_id) )

                # THRIFT SEND/RECV(reply):
                try:
                    # пакуем вызов метода в строчку, и отсылаем ее обычным HTTP post
                    send_transport = TTransport.TMemoryBuffer()
                    send_protocol = TBinaryProtocol.TBinaryProtocol( send_transport )
                    send_client = StatisticService.Client( send_protocol )
                    send_transport.open()
                    method( send_client, tlist )
                    send_body = send_transport.getvalue()
                    
                    _callback = functools.partial( self.onSendThriftHttpResponse, send_body=send_body, ttypename=ttypename, packet_id=packet_id )
                    request = HTTPRequest(coord_cfg.COORDINATOR_STATS_URL, method="POST", body=send_body,
                                          connect_timeout=SSTAT_CONNECT_TIOMEOUT, request_timeout=SSTAT_REQUEST_TIOMEOUT)
                    self.I.HTTP.fetch( request, _callback )
                except:
                    catch()
                    
                setattr( self, ttypename, [] ) # clear list
                
        t1 = time.clock()
        if t1-t0 > 0.0001:
            info( "sendThrift timing: list sends %.3f" % (t1-t0) )
            
    def onSendThriftHttpResponse(self, response, ttypename="", packet_id=0, send_body=""):
        info( "onSendThriftHttpResponse: key=%r, packet_id=%s, response=%s" % (ttypename, packet_id, response) )
        # распаковку thrift-ответа игнорируем, т.к. все методы StatisticService возаращают void
        ##TODO: нужно только убедиться, что ответ валидный, и пакет не надо ретраить
        
    
## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

def test_args():
    args = {
        u"userid":123, u"login":u"\u0414\u0430\u043d\u0438\u043b\u0430", u"server":u"server", u"cluster":u"cluster", u"timestamp":456
    }
    deunicode_dict(args)
    
    x = LoginInfo( **args )
    print x
    exit(0)

## ---------------------------------------------------------------------------------------------

def main():
    ITornadoServer.main( StatisticAgentServer )

if __name__ == "__main__":
    #tornado 3.4 fix
    if options.__class__.__name__ == "OptionParser":
        options.port = 8709
    else:
        options["port"].set(8709)
    main()
    
