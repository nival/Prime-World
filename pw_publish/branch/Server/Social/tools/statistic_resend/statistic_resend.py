#!/usr/bin/env python
# -*- coding: utf-8 -*-

from base.helpers import *
import functools

import tornado.options
from tornado.options import define, options
from tornado.httpclient import HTTPRequest

sys.path.append('cfg')
import coord_cfg

from iwebserver import *
from ifactory import IfaceFactory
from iuserdata import IDataManager

from handlers import * # JsonHandler, IfaceFactory, SubAction (транзитом)

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

from base.wstools import AddLoopCallback

MY_ID = -101
MY_NAME = 'stats-resender'

linere = re.compile(r'^(\d+): (\w+): (\[.+\])')
CONCURRENT_PKT_LIMIT = 4
ADD_PKT_ON = 2
SKIP_TYPES = set(('TalentChange', 'JoinPvpSession', 'MoveTalentToSet', 'MoveTalentFromSet', 'TutorialStateChange', 'HeroLevelChange', 'HeroRankChange', 'CastleLevelChange', 'ClientPing'))
UNSENT_DATA_FILENAME = 'collected-unsent'
ID_SHIFT = 100000000
ID_OK_FNAME = './ids.ok'
ID_OK_OUT_FNAME = 'logs/ids.ok'
#READ_GAP = 0.1
BASE_READ_GAP = 0.05 # per 1 event in a packet
FREEZE_ON_TIMEOUT = 30.0
SSTAT_CONNECT_TIOMEOUT = 60.0
SSTAT_REQUEST_TIOMEOUT = 300.0


## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class StatisticAgentHandler( JsonHandler ):
    """ main http request mapper (раскидываем запросы по handler methods, в зависимости от "/subaddr" и "action=") """
    
    def __init__( self, application, request, I, SERVICES={}, **kwargs):
        JsonHandler.__init__( self, application, request, **kwargs )
        self._SERVICES = SERVICES
        self.I = I # server interface dict

    ##-------------------------------------------------------------------------------------
    
    def get(self):
        raise tornado.web.HTTPError(400)
    
    def post(self):
        raise tornado.web.HTTPError(400)

    
## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

def constructResourcesChangeInfo(**args):
    dict_rchange = args["rchange"]
    thrift_rchange = ResourceTable(Gold=toint(dict_rchange["Gold"]), Silver=toint(dict_rchange["Silver"]), Perl=toint(dict_rchange["Perl"]),
                                   Population=toint(dict_rchange["Population"]), Resource1=toint(dict_rchange["Resource1"]),
                                   Resource2=toint(dict_rchange["Resource2"]), Resource3=toint(dict_rchange["Resource3"]))
    dict_rtotal = args["rtotal"]
    thrift_rtotal = ResourceTable(Gold=toint(dict_rtotal["Gold"]), Silver=toint(dict_rtotal["Silver"]), Perl=toint(dict_rtotal["Perl"]),
                                  Population=toint(dict_rtotal["Population"]), Resource1=toint(dict_rtotal["Resource1"]),
                                  Resource2=toint(dict_rtotal["Resource2"]), Resource3=toint(dict_rtotal["Resource3"]))
    return ResourcesChangeInfo(auid=args["auid"], gain=args["gain"], source=args["source"], buildingname = args["buildingname"],
                               rchange=thrift_rchange, rtotal=thrift_rtotal, timestamp=args["timestamp"])

def constructQuestChangeInfo(**args):
    return QuestChangeInfo(auid=args["auid"], questid=args["questid"], reason=args["reason"], timestamp=args["timestamp"])

def constructDynamicQuestChangeInfo(**args):
    return DynamicQuestChangeInfo(auid=args["auid"], questindex=args["questindex"], questname=args["questname"],
                                  reason=args["reason"], timestamp=args["timestamp"],
                                  alternativeline=args["alternativeline"])

def constructTournamentQuestChangeInfo(**args):
    return TournamentQuestChangeInfo(auid=args["auid"], questindex=args["questindex"], questname=args["questname"],
                                  reason=args["reason"], timestamp=args["timestamp"],
                                  alternativeline=args["alternativeline"])

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
                                   Population=toint(dict_rchange["Population"]), Resource1=toint(dict_rchange["Resource1"]),
                                   Resource2=toint(dict_rchange["Resource2"]), Resource3=toint(dict_rchange["Resource3"]))
    dict_rtotal = args["rtotal"]
    thrift_rtotal = ResourceTable(Gold=toint(dict_rtotal["Gold"]), Silver=toint(dict_rtotal["Silver"]), Perl=toint(dict_rtotal["Perl"]),
                                  Population=toint(dict_rtotal["Population"]), Resource1=toint(dict_rtotal["Resource1"]),
                                  Resource2=toint(dict_rtotal["Resource2"]), Resource3=toint(dict_rtotal["Resource3"]))
    return FactionSelectInfo(auid=args["auid"], oldfaction =args["oldfaction"], newfaction=args["newfaction"],
                             rchange=thrift_rchange, rtotal=thrift_rtotal, timestamp=args["timestamp"])


def constructBanInfo(**args):
    args['type'] = GMUserOperationType.Ban
    return GMUserOperationInfo(**args)

def constructMuteInfo(**args):
    args['type'] = GMUserOperationType.Mute
    return GMUserOperationInfo(**args)

def constructModeratorMuteInfo(**args):
    args['type'] = GMUserOperationType.ModeratorMute
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



def constructUnlockHeroInfo( **args ):
    dict_rchange = args["rchange"]
    thrift_rchange = ResourceTable( Gold=toint(dict_rchange["Gold"]), Silver=toint(dict_rchange["Silver"]), Perl=toint(dict_rchange["Perl"]), Population=toint(dict_rchange["Population"]), Resource1=toint(dict_rchange["Resource1"]), Resource2=toint(dict_rchange["Resource2"]), Resource3=toint(dict_rchange["Resource3"]) )
    dict_rtotal = args["rtotal"]
    thrift_rtotal = ResourceTable( Gold=toint(dict_rtotal["Gold"]), Silver=toint(dict_rtotal["Silver"]), Perl=toint(dict_rtotal["Perl"]), Population=toint(dict_rtotal["Population"]), Resource1=toint(dict_rtotal["Resource1"]), Resource2=toint(dict_rtotal["Resource2"]), Resource3=toint(dict_rtotal["Resource3"]) )
    return UnlockHeroInfo( auid=args["auid"], heroid=args["heroid"], rchange=thrift_rchange, rtotal=thrift_rtotal, timestamp=args["timestamp"] )

def constructSessionAwardsInfo( **args ):
    dict_rchange = args["rchange"]
    thrift_rchange = ResourceTable( Gold=toint(dict_rchange["Gold"]), Silver=toint(dict_rchange["Silver"]),
                                    Perl=toint(dict_rchange["Perl"]), Population=toint(dict_rchange["Population"]),
                                    Resource1=toint(dict_rchange["Resource1"]), Resource2=toint(dict_rchange["Resource2"]),
                                    Resource3=toint(dict_rchange["Resource3"]), CWPoints_Player=toint(dict_rchange["CWPoints_Player"]) )
    dict_rtotal = args["rtotal"]
    thrift_rtotal = ResourceTable( Gold=toint(dict_rtotal["Gold"]), Silver=toint(dict_rtotal["Silver"]),
                                   Perl=toint(dict_rtotal["Perl"]), Population=toint(dict_rtotal["Population"]),
                                   Resource1=toint(dict_rtotal["Resource1"]), Resource2=toint(dict_rtotal["Resource2"]),
                                   Resource3=toint(dict_rtotal["Resource3"]), CWPoints_Player=toint(dict_rtotal["CWPoints_Player"]) )
    
    thrift_talents = []
    for tal in args["talents"]:
        if isinstance( tal, TalentInfo ):
            dict_tr = TalentInfo( toint(tal.classId), toint(tal.instanceId), toint(tal.boundHeroClassId) )
        else:
            dict_tr = TalentInfo( toint(tal["classId"]), toint(tal["instanceId"]), toint(tal["boundHeroClassId"]) )
        thrift_talents.append( dict_tr )

    return SessionAwardsInfo( auid=args["auid"], sessionpersistentid=args["sessionpersistentid"], nick=args["nick"],
              heroid=args["heroid"], inc_reliability=args["inc_reliability"], new_reliability=args["new_reliability"],
              talents=thrift_talents, rchange=thrift_rchange, rtotal=thrift_rtotal, timestamp=args["timestamp"],
              force=args["force"], rune=args["rune"], guildpointschange=args["guildpointschange"],
              guildpointstotal=args["guildpointstotal"], appliedbuffs=args["appliedbuffs"], leaverpointschange=args["leaverpointschange"],
              leaverpointstotal=args["leaverpointstotal"], isleaverchanged=args["isleaverchanged"], isleaver=args["isleaver"])

def constructGuildInfo( **args ):
    dict_rchange = args["rchange"]
    thrift_rchange = ResourceTable( Gold=toint(dict_rchange["Gold"]), Silver=toint(dict_rchange["Silver"]), Perl=toint(dict_rchange["Perl"]), Population=toint(dict_rchange["Population"]), Resource1=toint(dict_rchange["Resource1"]), Resource2=toint(dict_rchange["Resource2"]), Resource3=toint(dict_rchange["Resource3"]) )
    dict_rtotal = args["rtotal"]
    thrift_rtotal = ResourceTable( Gold=toint(dict_rtotal["Gold"]), Silver=toint(dict_rtotal["Silver"]), Perl=toint(dict_rtotal["Perl"]), Population=toint(dict_rtotal["Population"]), Resource1=toint(dict_rtotal["Resource1"]), Resource2=toint(dict_rtotal["Resource2"]), Resource3=toint(dict_rtotal["Resource3"]) )

    coreInfo = GuildCoreInfo(auid=args["auid"], guildid=args["guildid"], timestamp=args["timestamp"], faction=args["faction"], guildmembers=args["guildmembers"])
    return GuildInfo( coreInfo=coreInfo, shortname=args["shortname"], fullname=args["fullname"], rchange=thrift_rchange, rtotal=thrift_rtotal )

def constructGuildCoreInfo( **args ):
    return GuildCoreInfo(auid=args["auid"], guildid=args["guildid"], timestamp=args["timestamp"], faction=args["faction"], guildmembers=args["guildmembers"])

def constructGuildLeaveInfo( **args ):
    coreInfo = GuildCoreInfo( auid=args["auid"], guildid=args["guildid"], timestamp=args["timestamp"], faction=args["faction"], guildmembers=args["guildmembers"] )
    return GuildLeaveInfo( coreInfo=coreInfo, kicked=args["kicked"] )

def constructGuildShopBuyInfo( **args ):
    dict_rchange = args["rchange"]
    thrift_rchange = ResourceTable( Gold=toint(dict_rchange["Gold"]), Silver=toint(dict_rchange["Silver"]), Perl=toint(dict_rchange["Perl"]), Population=toint(dict_rchange["Population"]), Resource1=toint(dict_rchange["Resource1"]), Resource2=toint(dict_rchange["Resource2"]), Resource3=toint(dict_rchange["Resource3"]), CWPoints_Player=toint(dict_rchange["CWPoints_Player"]) )
    dict_rtotal = args["rtotal"]
    thrift_rtotal = ResourceTable( Gold=toint(dict_rtotal["Gold"]), Silver=toint(dict_rtotal["Silver"]), Perl=toint(dict_rtotal["Perl"]), Population=toint(dict_rtotal["Population"]), Resource1=toint(dict_rtotal["Resource1"]), Resource2=toint(dict_rtotal["Resource2"]), Resource3=toint(dict_rtotal["Resource3"]), CWPoints_Player=toint(dict_rtotal["CWPoints_Player"]) )
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

class FakeResponse:
    def __init__(self, code):
        self.code = code
    def __str__(self):
        return "FakeResponse(code=%s)" % self.code

class StatisticAgentServer(ITornadoServer):

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
        LeaverPointsChange=LeaverPointsChangeInfo,
        ReRollShop=ReRollShopInfo,
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
        LeaverPointsChange=StatisticService.Client.send_LeaverPointsChange,
        ReRollShop=StatisticService.Client.send_ReRollShop,
    )
    
    # ----------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------
    
    def __init__(self, **kwargs):
        super(StatisticAgentServer, self).__init__( **kwargs )

        # заводим пустые списки для кэширования отправляемых thrift-объектов
        for ttypename in self._THRIFT_TYPES:
            setattr( self, ttypename, [] )
        
        #FIXME: адрес статистики пока берем напрямую из конфига (вообще-то надо бы получать по сети от координатора)
        self.initTransportClient()

        self.dataFile = open(UNSENT_DATA_FILENAME)
        self.dataLines = 0
        self.wrongLines = 0
        self.skipped = 0
        self.unknownTypeLiness = 0
        self.skippedByType = 0
        self.OKPackets = 0
        self.Fails = 0
        self.pkt = {}
        self.start_at = time.time() + 0.5
        self.idsOk = self.loadIdsOk()
        #info("IDS OK: %s", self.idsOk)
        self.idsOkOut = open(ID_OK_OUT_FNAME, "wt")
        self.wasTimedOut = False
        self.suspended = 0 # сколько назначено отложенных запусков


    def loadIdsOk(self):
        if os.access(ID_OK_FNAME, os.R_OK):
            try:
                with open(ID_OK_FNAME) as f:
                    return set(int(line) for line in f)
            except IOError as e:
                catch("Error reading file %s, skpped", ID_OK_FNAME)
                return set()
        else:
            info("IDs OK file %s not found, ignored", ID_OK_FNAME)
            return set()


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
        if time.time() > self.start_at and self.dataFile and len(self.pkt) == 0 and not self.wasTimedOut:
            self.readUnsent(chain=True)
        self.checkDone()

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
            options.server_id = MY_ID
            options.server_name = MY_NAME
            options.server_class = "stats-resender"
        else:
            options["server_id"].set(MY_ID)
            options["server_name"].set(MY_NAME)
            options["server_class"].set("stats-resender")

    # -----------------------------------------------
    @staticmethod
    def initInterfaces( classOf=None ):
        iDict = ClassDict()

        # http-клиент, нужен для отправки thrift-пакетов и лог-мониторинга
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient(max_clients=coord_cfg.COORDINATOR_HTTP_CURL_WORKERS)
        iDict.WS = IWebServer()  # чисто для генерации GUID-ов

        return iDict

    # ----------------------------------------------------------------------------------------------

    def readUnsent(self, chain=False):
        line = None
        try:
            if self.dataFile is not None and (self.suspended + len(self.pkt)) < CONCURRENT_PKT_LIMIT:
                while True:
                    line = self.dataFile.readline()
                    if len(line) == 0:
                        self.dataFile.close()
                        self.dataFile = None
                        return
                    self.dataLines += 1
                    m = linere.match(line)
                    if not m:
                        err("Wrong line: %s", line.rstrip())
                        self.wrongLines += 1
                        continue
                    p_id, tt, data_str = m.group(1,2,3)
                    p_id = int(p_id)
                    if p_id in self.idsOk:
                        info("Packet %s is already sent", p_id)
                        self.skipped += 1
                        continue
                    if not tt in self._THRIFT_TYPES:
                        self.unknownTypeLiness += 1
                        err("Unknown type: %s", tt)
                    if tt in SKIP_TYPES:
                        info("Packet %s type %s skipped", p_id, tt)
                        self.skippedByType += 1
                        continue
                    data = eval(data_str)
                    self.processUnsentData(p_id, tt, data)
                    if chain:
                        debug("readUnsent: Suspening next send for %s", len(data) * BASE_READ_GAP)
                        AddLoopCallback(functools.partial(self.readUnsent, chain), BASE_READ_GAP * len(data))
                    return
        except Exception:
            catch("Failed to process line: %s", '<None>' if line is None else line.rstrip())


    def checkDone(self):
        if not self.dataFile:
            if len(self.pkt):
                info("All data sent, waiting for %s responses", len(self.pkt))
            else:
                info("All responses received. Done.")
                self.idsOkOut.close()
                info("TOTAL: %s lines read, %s wrong lines. %s already sent, %s sent OK, %s fails; %s unknown type lines (not skipped), %s skipped by type",
                     self.dataLines, self.wrongLines, self.skipped, self.OKPackets, self.Fails, self.unknownTypeLiness, self.skippedByType)
                self.fadeoutServer()


    def processUnsentData(self, packet_id, key, data):
        packet_id += ID_SHIFT
        self.pkt[packet_id] = (key, data)
        method = self._THRIFT_LIST_METHODS[key]
        info("Sending [%s:%s] packet %s type %s: %s", self.dataLines, len(self.pkt), packet_id, key, data)
        # THRIFT SEND/RECV(reply):
        try:
            # пакуем вызов метода в строчку, и отсылаем ее обычным HTTP post
            send_transport = TTransport.TMemoryBuffer()
            send_protocol = TBinaryProtocol.TBinaryProtocol( send_transport )
            send_client = StatisticService.Client( send_protocol )
            send_transport.open()
            method( send_client, data )
            send_body = send_transport.getvalue()

            _callback = functools.partial( self.onResendThriftHttpResponse, send_body=send_body, ttypename=key, packet_id=packet_id )
            request = HTTPRequest( coord_cfg.COORDINATOR_STATS_URL, method="POST", body=send_body,
				connect_timeout=SSTAT_CONNECT_TIOMEOUT, request_timeout=SSTAT_REQUEST_TIOMEOUT)
            ## DEBUG ## AddLoopCallback(functools.partial(_callback, FakeResponse(200 if random.random() > 0.2 else 599)), random.random()*3+0.5)
            ## для отладки раскомментировать предыдущую и закомментировать следующую строку
            self.I.HTTP.fetch( request, _callback )
        except:
            catch("Failed to send packet %s: %s", key, data)



    def onResendThriftHttpResponse(self, response, ttypename="", packet_id=0, send_body=""):
        info( "onResendThriftHttpResponse: key=%r, packet_id=%s, response=%s" % (ttypename, packet_id, response) )
        code = getattr(response, 'code', 0) if response else 0
        if code == 200:
            self.OKPackets += 1
            print >>self.idsOkOut, packet_id - ID_SHIFT
            self.wasTimedOut = False
        else:
            self.Fails += 1
            if code == 599:
                self.wasTimedOut = True
        p = self.pkt.pop(packet_id)
        if len(self.pkt) <= ADD_PKT_ON and self.dataFile:
            tm = getattr(response, 'request_time', 0)
            gap = FREEZE_ON_TIMEOUT if self.wasTimedOut else (len(p[1]) * BASE_READ_GAP)
            if tm > 1:
                gap += tm * (5 if tm > 20 else 10)
            debug("onResendThriftHttpResponse: Suspening next send for %s", gap)
            self.suspended += 1
            AddLoopCallback(self.nextRead, gap)

    def nextRead(self):
        self.suspended -= 1
        self.readUnsent()

## ---------------------------------------------------------------------------------------------

def main():
    ITornadoServer.main( StatisticAgentServer )

if __name__ == "__main__":
    #tornado 3.4 fix
    if options.__class__.__name__ == "OptionParser":
        options.port = 18709 # Just any unused port
    else:
        options["port"].set(18709) # Just any unused port
    main()
    
