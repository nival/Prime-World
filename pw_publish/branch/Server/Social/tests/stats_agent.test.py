#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network
import time
import unittest
import os, sys, logging

os.chdir('..')
sys.path.append( os.path.abspath('.') )

sys.path.append('cfg')
sys.path.append('memcache')

from base.helpers import info, warn, ClassDict, IncDict, catch, err
import coord_cfg

sys.path.append(os.path.abspath('thrift_pw/statistics/gen-py'))
from StatisticCore.ttypes import ResourceTable
from StatisticCore.ttypes import GMOperationType
from StatisticCore.ttypes import TalentChangeOperation
from StatisticCore.ttypes import TalentInfo
from StatisticCore.ttypes import GuildInteractionType
from StatisticCore.ttypes import RuneRollSource

from thrift import Thrift
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

# -------------------------------------------------
from statistic_agent import StatisticAgentServer
from istats import StatsAgent

import functools

DEFAULT_LOG_LEVEL = logging.INFO

class DummyThriftClient:
    def __init__(self):
        self.keys_received = IncDict()
        self.objects_received = {}
        
    def dump(self, thrift_obj_list, key="?"):
        info( "client dump (%s): obj_list %s" % (key,thrift_obj_list) )
        assert( thrift_obj_list )
        assert( len(thrift_obj_list) == 1 )
        
        self.keys_received.inc( key )
        
        # ну и прикопаем на всяк.случай сами объекты; вдруг кто-то захочет покопать, что там до нас дошло
        self.objects_received[key] = self.objects_received.get(key) or []
        self.objects_received[key].extend( thrift_obj_list )

    def full_dump(self, thrift_obj_list, key="?"):
        info("client dump (%s): obj_list %s" % (key,thrift_obj_list))

        self.keys_received.add(key, len(thrift_obj_list))

        # ну и прикопаем на всяк.случай сами объекты; вдруг кто-то захочет покопать, что там до нас дошло
        self.objects_received[key] = self.objects_received.get(key) or []
        self.objects_received[key].extend(thrift_obj_list)
        

class DummyStatsAgent(StatsAgent):
    # транспортная часть отправки сообщения (для тестов можно override именно эту часть; например, на прямой вызов StatisticAgentHandler.processRawData)
    def startSend(self, send_dict):
        packet_id = self.I.WS.nextStringGUID('stat_send')
        self.I.AGENT.processRawData( packet_id, send_dict )


class DummyStatisticAgentServer( StatisticAgentServer ):
    _THRIFT_LIST_METHODS = dict(
        LoginUsers=functools.partial(DummyThriftClient.dump, key="LoginUsers"),
        LogoutUsers=functools.partial(DummyThriftClient.dump, key="LogoutUsers"),
        BanUser=functools.partial(DummyThriftClient.dump, key="BanUser"),
        MuteUser=functools.partial(DummyThriftClient.dump, key="MuteUser"),
        MoveTalentToSet=functools.partial(DummyThriftClient.dump, key="MoveTalentToSet"),
        MoveTalentFromSet=functools.partial(DummyThriftClient.dump, key="MoveTalentFromSet"),
        UnlockHero=functools.partial(DummyThriftClient.dump, key="UnlockHero"),
        JoinPvpSession=functools.partial(DummyThriftClient.dump, key="JoinPvpSession"),
        ChatMessages=functools.partial(DummyThriftClient.dump, key="ChatMessages"),
        UnbanUser=functools.partial(DummyThriftClient.dump, key="UnbanUser"),
        UnmuteUser=functools.partial(DummyThriftClient.dump, key="UnmuteUser"),
        GMEditUser=functools.partial(DummyThriftClient.dump, key="GMEditUser"),
        GMUnlockHero=functools.partial(DummyThriftClient.dump, key="GMUnlockHero"),
        GMLockHero=functools.partial(DummyThriftClient.dump, key="GMLockHero"),
        MonitoringResults=functools.partial(DummyThriftClient.dump, key="MonitoringResults"),
        AddIgnore=functools.partial(DummyThriftClient.dump, key="AddIgnore"),
        RemoveIgnore=functools.partial(DummyThriftClient.dump, key="RemoveIgnore"),
        GiveSessionAwards=functools.partial(DummyThriftClient.dump, key="GiveSessionAwards"),
        LauncherStart=functools.partial(DummyThriftClient.dump, key="LauncherStart"),
        LauncherEvents=functools.partial(DummyThriftClient.dump, key="LauncherEvents"),
        LauncherDActions=functools.partial(DummyThriftClient.dump, key="LauncherDActions"),
        SocialRegister=functools.partial(DummyThriftClient.dump, key="SocialRegister"),
        SocialJoin=functools.partial(DummyThriftClient.dump, key="SocialJoin"),
        SocialMerge=functools.partial(DummyThriftClient.dump, key="SocialMerge"),
        ResourcesChange=functools.partial(DummyThriftClient.full_dump, key="ResourcesChange"),
        QuestChange=functools.partial(DummyThriftClient.dump, key="QuestChange"),
        DynamicQuestChange=functools.partial(DummyThriftClient.dump, key="DynamicQuestChange"),
        TournamentQuestChange=functools.partial(DummyThriftClient.dump, key="TournamentQuestChange"),
        TutorialStateChange=functools.partial(DummyThriftClient.dump, key="TutorialStateChange"),
        TalentChange=functools.partial(DummyThriftClient.dump, key="TalentChange"),
        FactionSelect=functools.partial(DummyThriftClient.dump, key="FactionSelect"),
        RatingChange=functools.partial(DummyThriftClient.dump, key="RatingChange"),
        GuildCreated=functools.partial(DummyThriftClient.dump, key="GuildCreated"),
        GuildRenamed=functools.partial(DummyThriftClient.dump, key="GuildRenamed"),
        GuildJoined=functools.partial(DummyThriftClient.dump, key="GuildJoined"),
        GuildLeaved=functools.partial(DummyThriftClient.dump, key="GuildLeaved"),
        GuildDisbanded=functools.partial(DummyThriftClient.dump, key="GuildDisbanded"),
        ClientPings=functools.partial(DummyThriftClient.dump, key="ClientPings"),
        RuneExpire=functools.partial(DummyThriftClient.dump, key="RuneExpire"),
        RuneUnsoulbound=functools.partial(DummyThriftClient.dump, key="RuneUnsoulbound"),
        RuneReplenish=functools.partial(DummyThriftClient.dump, key="RuneReplenish"),
        GMOperation=functools.partial(DummyThriftClient.dump, key="GMOperation"),
        GuildShopBuy=functools.partial(DummyThriftClient.dump, key="GuildShopBuy"),
        GuildDailyStats=functools.partial(DummyThriftClient.dump, key="GuildDailyStats"),
        GuildInteraction=functools.partial(DummyThriftClient.dump, key="GuildInteraction"),
        GuildPointsChange=functools.partial(DummyThriftClient.dump, key="GuildPointsChange"),
        RuneRoll=functools.partial(DummyThriftClient.dump, key="RuneRoll"),
    )
    
    def initTransportClient(self):
        self.client = DummyThriftClient()
        
    # ----------------------------------------------------------------------------------------------
    # для тестов оставляем все по-старому, с прямым вызовом thrift-метода
    def sendThrift( self ):
        # часть thrift-методов принимает сразу списки записей
        for ttypename, method in self._THRIFT_LIST_METHODS.iteritems():
            tlist = getattr( self, ttypename )
            if tlist:
                info( "sendThrift LIST: key %r, data %r" % (ttypename, tlist) )

                # THRIFT SEND/RECV(reply):
                if self.client:
                    try:
                        method( self.client, tlist )
                    except:
                        catch()
                    
                setattr( self, ttypename, [] ) # clear list
                

class StatsAgentTest(unittest.TestCase):
    def setUp(self):
        self.I = ClassDict()
        
        agent = DummyStatisticAgentServer( I=self.I )
        self.I.AGENT = agent
        self.I.WS = agent
        self.I.STATS = DummyStatsAgent( "", self.I )

    def testCurrencyToStats(self):
        price1 = ClassDict(Gold=1, Silver=2, Perl=3, RedPerl=4, Population=5, Resource1=6, Resource2=7, Resource3=8,
                           Shard=8, CWPoints_Player=9, Currencies=ClassDict(Cur1=10, Cur2=30, Cur3=50, Cur4=80))
        price2 = ClassDict(Gold=10, Silver=20, Perl=30, RedPerl=40, Population=50, Resource1=60, Resource2=70,
                           Resource3=80, Shard=80, CWPoints_Player=90, Currencies=ClassDict(Cur1=20, Cur2=40, Cur3=50 + 20,
                                                                                       Cur4=50 + 80))

        self.I.STATS.addResourcesChange(29, True, 0, "test_resources", price1, price2)

        self.I.STATS.Send()
        self.I.AGENT.sendThrift()

        # проверим, что через dummy-клиента прошло по 2 запроса
        client = self.I.AGENT.client
        key = 'ResourcesChange'
        count = client.keys_received.get(key)
        warn("check key %r: request count = %s" % (key, count))
        self.assert_(count == 4)

        # теперь проверим, правильные ли поля доехали "до статистики" в конечных thrift-объектах
        firstChanges = client.objects_received["ResourcesChange"][0]
        secondChanges = client.objects_received["ResourcesChange"][1]
        threeChanges = client.objects_received["ResourcesChange"][2]
        fourChanges = client.objects_received["ResourcesChange"][3]

        # time.sleep(0.1)
        # print "firstChanges change: {}".format(firstChanges.rchange.Currencies)
        # print "firstChanges total: {}".format(firstChanges.rtotal.Currencies)
        # print ''
        # print "secondChanges change: {}".format(secondChanges.rchange.Currencies)
        # print "secondChanges total: {}".format(secondChanges.rtotal.Currencies)
        # print ''
        # print "threeChanges change: {}".format(threeChanges.rchange.Currencies)
        # print "threeChanges total: {}".format(threeChanges.rtotal.Currencies)
        # print ''
        # print "fourChanges change: {}".format(fourChanges.rchange.Currencies)
        # print "fourChanges total: {}".format(fourChanges.rtotal.Currencies)
        # time.sleep(0.1)

        # ResourcesChange
        self.assert_(firstChanges)
        self.assert_(firstChanges.auid == 29)
        self.assert_(firstChanges.gain == True)
        self.assert_(firstChanges.source == 0)
        self.assert_(firstChanges.buildingname == "test_resources")

        # change all
        self.assert_(firstChanges.rchange.Gold == 1)
        self.assert_(firstChanges.rchange.Silver == 2)
        self.assert_(firstChanges.rchange.Perl == 3)
        self.assert_(firstChanges.rchange.RedPerl == 4)
        self.assert_(firstChanges.rchange.Population == 5)
        self.assert_(firstChanges.rchange.Resource1 == 6)
        self.assert_(firstChanges.rchange.Resource2 == 7)
        self.assert_(firstChanges.rchange.Resource3 == 8)
        self.assert_(firstChanges.rchange.Shard == 8)

        # change currencies
        self.assert_(fourChanges.rchange.Currencies['Cur1'] == 10)

        self.assert_(firstChanges.rchange.Currencies['Cur2'] == 30)
        self.assert_('Cur2' not in fourChanges.rchange.Currencies)
        self.assert_('Cur2' not in threeChanges.rchange.Currencies)


        # before all
        self.assert_(firstChanges.rtotal.Gold == 10)
        self.assert_(firstChanges.rtotal.Silver == 20)
        self.assert_(firstChanges.rtotal.Perl == 30)
        self.assert_(firstChanges.rtotal.RedPerl == 40)
        self.assert_(firstChanges.rtotal.Population == 50)
        self.assert_(firstChanges.rtotal.Resource1 == 60)
        self.assert_(firstChanges.rtotal.Resource2 == 70)
        self.assert_(firstChanges.rtotal.Resource3 == 80)
        self.assert_(firstChanges.rtotal.Shard == 80)

        # before currencies
        self.assert_(fourChanges.rtotal.Currencies['Cur1'] == 20)

        self.assert_(firstChanges.rtotal.Currencies['Cur2'] == 40)
        self.assert_('Cur2' not in fourChanges.rtotal.Currencies)
        self.assert_('Cur2' not in threeChanges.rtotal.Currencies)



        self.assert_(firstChanges.timestamp and isinstance(firstChanges.timestamp, int))
        self.assert_(secondChanges.timestamp and isinstance(secondChanges.timestamp, int))



    def testXXX(self):
        self.I.STATS.addLogin(1, "nick1", "servername1", "ip1", "A", True, True, "EN", 1, "shnm1", "full_guild_name", 11, True)
        self.I.STATS.addLogout(2, "nick2", "servername2")

        self.I.STATS.addBanUser(3, "gmlogin3", 33, "reason3", [1])
        self.I.STATS.addMuteUser(4, "gmlogin4", 44, "reason4", [1])

        self.I.STATS.addMoveTalentToSet(6, "nick6", 6666, 666, 66)
        self.I.STATS.addMoveTalentFromSet(7, "nick7", 7777, 777, 77)
        price1 = ClassDict( Gold=1, Silver=2, Perl=3, RedPerl=4, Population=5, Resource1=6, Resource2=7, Resource3=8, Shard=8, CWPoints_Player=9, Currencies={'Cur1': 10 } )
        price2 = ClassDict( Gold=10, Silver=20, Perl=30, RedPerl=40, Population=50, Resource1=60, Resource2=70, Resource3=80, Shard=80, CWPoints_Player=90, Currencies={'Cur1': 20 } )
        self.I.STATS.addUnlockHero(8, 88, price1, price2)
        self.I.STATS.addJoinPvpSession(9, 99999, 99, [1,2,3,4,5], [1,2,3,4,5], True)

        self.I.STATS.addChatMessages(10, "channel10", "message10")
        self.I.STATS.addUnbanUser(11, "gmlogin11")
        self.I.STATS.addUnmuteUser(12, "gmlogin12")
        self.I.STATS.addGMEditUser(13, "gmlogin13", "field13", "oldvalue13", "newvalue13")
        self.I.STATS.addGMUnlockHero(14, "gmlogin14", 1414)
        self.I.STATS.addGMLockHero(15, "gmlogin15", 1515)
        self.I.STATS.addMonitoringResults("property18", "counter18", 18)

        self.I.STATS.addAddIgnore(19, 1919, "reason19")
        self.I.STATS.addRemoveIgnore(20, 2020)

        t1 = TalentInfo( 1, 2, 3 )
        t2 = TalentInfo( 4, 5, 6 )
        self.I.STATS.addGiveSessionAwards(22, 222222222222, 'nick22', 222, price1, price2, 222222, 2222222, [t1, t2], 22.22, 2, 22, [22, 222], 2, 22, True, True, "true leaver", True)

        self.I.STATS.addLauncherStart('hostid23', 'version23', 23, "ip23", "geo23", "loc23")

        self.I.STATS.addSocialRegister('hostid26', 'auid26', 'snid26', 'snuid26', 'muid26', 'ruid26')
        self.I.STATS.addSocialJoin('auid27', 'snid27', 'snuid27')
        self.I.STATS.addSocialMerge('auid1_28', 'auid2_28')

        self.I.STATS.addResourcesChange(29, True, 0, "testbuilding", price1, price2)

        self.I.STATS.addQuestChange(29, 100500, 0)
        self.I.STATS.addDynamicQuestChange(29, 100600, "testdquest", 1, True)
        self.I.STATS.addTournamentQuestChange(29, 100600, "testdquest", 1, True)

        self.I.STATS.addLauncherEvents('ruid30', 'muid30', 30, 3030, 303030, "loc30")

        self.I.STATS.addFactionSelect(5, "A", "B", price1, price2) # номер 5 в списке выше пропущен (видимо, удалили соотв. евент)

        self.I.STATS.addLauncherDActions( muid='muid31', auid='31', timestamp=313131, locale="loc31")

        self.I.STATS.addRatingChange( 32, 0, 3232323232323232, 3232, 32, 323232 )


        self.I.STATS.addGuildCreated( 33, 34, 'A', 'O_O', 'Boobs', price1, price2, 1 )
        self.I.STATS.addGuildRenamed( 35, 36, 'B', 'NUB', 'Nubiki', price1, price2, 3 )
        self.I.STATS.addGuildJoined( 37, 38, 'N', 3 )
        self.I.STATS.addGuildLeaved( 39, 40, 'A', True, 5 )
        self.I.STATS.addGuildDisbanded( 41, 42, 'B', 0 )

        self.I.STATS.addClientPing( 43, "43", 4343 )

        self.I.STATS.addRuneExpire( 44, 444, 4444, 44444 )
        self.I.STATS.addRuneUnsoulbound( 45, 4545, 454545 )
        self.I.STATS.addRuneReplenish( 46, 4646 )
        self.I.STATS.addGMOperation( 47, GMOperationType.BuildingMoveToStorage, "gmlogin47", "Building(47) moved to storage" )

        self.I.STATS.addTalentChange( 48, t1, TalentChangeOperation.GetFromTransmutation )

        RuneExpire=functools.partial(DummyThriftClient.dump, key="RuneExpire"),
        RuneUnsoulbound=functools.partial(DummyThriftClient.dump, key="RuneUnsoulbound"),
        RuneReplenish=functools.partial(DummyThriftClient.dump, key="RuneReplenish"),

        self.I.STATS.addTutorialStateChange( 49, "SessionStarted" )
        self.I.STATS.addBuyGuildShopItem(50, 3, True, 5, 123, price1, price2, 8, 10)
        vassals = [{"guildid": 1, "guildpoints": 11}, {"guildid": 2, "guildpoints": 22}]
        recVassals = [{"guildid": 1, "guildrating": 11}, {"guildid": 2, "guildrating": 22}]
        self.I.STATS.addGuildDailyStatsInfo(51, 500, 20, 42, 3, vassals, recVassals)
        self.I.STATS.addGuildInteraction(52, 8, GuildInteractionType.Decline, 1, 500)
        self.I.STATS.addGuildPointsChange(53, 1, "GMGuildStopSiege", 3, 4, 5, 6)
        #self.I.STATS.addLampRoll(54, 20, RuneRollSource.Quest, 33333333333)
        self.I.STATS.addLampRoll(54, 20, RuneRollSource.Quest)

        self.I.STATS.Send()

        # якобы отправляем STATS AGENT -> внешняя статистика
        self.I.AGENT.sendThrift()

        # проверим, что через dummy-клиента прошло по 1 запросу со всеми типы данных
        checked_count = 0
        client = self.I.AGENT.client
        for key in DummyStatisticAgentServer._THRIFT_LIST_METHODS:
            count = client.keys_received.get(key)
            warn( "check key %r: request count = %s" % (key, count) )
            self.assert_( count == 1 )
            checked_count += 1

        warn( "total checked_count: %d" % checked_count )

        # теперь проверим, правильные ли поля доехали "до статистики" в конечных thrift-объектах

        # Login
        obj = client.objects_received["LoginUsers"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 1 )
        self.assert_( obj.nick == "nick1" )
        self.assert_( obj.server == "servername1" )
        self.assert_( obj.ip == "ip1" )
        self.assert_( obj.faction == "A" )
        self.assert_( obj.factionselected == True )
        self.assert_( obj.isdeveloper == True )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )
        self.assert_( obj.guildid == 1 )
        self.assert_( obj.guildshortname == "shnm1" )
        self.assert_( obj.guildfullname == "full_guild_name" )
        self.assert_( obj.leaverpoints == 11 )
        self.assert_( obj.isleaver )

        # Logout
        obj = client.objects_received["LogoutUsers"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 2 )
        self.assert_( obj.nick == "nick2" )
        self.assert_( obj.server == "servername2" )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # Ban
        obj = client.objects_received["BanUser"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 3 )
        self.assert_( obj.gmlogin == "gmlogin3" )
        self.assert_( obj.minutes == 33 )
        self.assert_( obj.reason == "reason3" )
        self.assert_( obj.claimIds == [1] )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # Mute
        obj = client.objects_received["MuteUser"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 4 )
        self.assert_( obj.gmlogin == "gmlogin4" )
        self.assert_( obj.minutes == 44 )
        self.assert_( obj.reason == "reason4" )
        self.assert_( obj.claimIds == [1] )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # MoveTalentToSet
        obj = client.objects_received["MoveTalentToSet"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 6 )
        self.assert_( obj.nick == "nick6" )
        self.assert_( obj.talentid == 6666 )
        self.assert_( obj.heroid == 666 )
        self.assert_( obj.slot == 66 )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # MoveTalentFromSet
        obj = client.objects_received["MoveTalentFromSet"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 7 )
        self.assert_( obj.nick == "nick7" )
        self.assert_( obj.talentid == 7777 )
        self.assert_( obj.heroid == 777 )
        self.assert_( obj.slot == 77 )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # UnlockHero
        obj = client.objects_received["UnlockHero"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 8 )
        self.assert_( obj.heroid == 88 )
        self.assert_( obj.rchange.Gold == 1 )
        self.assert_( obj.rchange.Silver == 2 )
        self.assert_( obj.rchange.Perl == 3 )
        self.assert_( obj.rchange.RedPerl == 4 )
        self.assert_( obj.rchange.Population == 5 )
        self.assert_( obj.rchange.Resource1 == 6 )
        self.assert_( obj.rchange.Resource2 == 7 )
        self.assert_( obj.rchange.Resource3 == 8 )
        self.assert_( obj.rchange.Shard == 8 )
        self.assert_( obj.rtotal.Gold == 10 )
        self.assert_( obj.rtotal.Silver == 20 )
        self.assert_( obj.rtotal.Perl == 30 )
        self.assert_( obj.rtotal.RedPerl == 40 )
        self.assert_( obj.rtotal.Population == 50 )
        self.assert_( obj.rtotal.Resource1 == 60 )
        self.assert_( obj.rtotal.Resource2 == 70 )
        self.assert_( obj.rtotal.Resource3 == 80 )
        self.assert_( obj.rtotal.Shard == 80 )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # JoinPvpSession
        obj = client.objects_received["JoinPvpSession"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 9 )
        self.assert_( obj.heroid == 99 )
        self.assert_( obj.sessionpersistentid == 99999 )
        self.assert_( obj.talentset == [1,2,3,4,5] )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # ChatMessages
        obj = client.objects_received["ChatMessages"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 10 )
        self.assert_( obj.channel == "channel10" )
        self.assert_( obj.message == "message10" )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # UnbanUser
        obj = client.objects_received["UnbanUser"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 11 )
        self.assert_( obj.gmlogin == "gmlogin11" )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # UnmuteUser
        obj = client.objects_received["UnmuteUser"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 12)
        self.assert_( obj.gmlogin == "gmlogin12" )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # GMEditUser
        obj = client.objects_received["GMEditUser"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 13)
        self.assert_( obj.gmlogin == "gmlogin13" )
        self.assert_( obj.field == "field13" )
        self.assert_( obj.oldvalue == "oldvalue13" )
        self.assert_( obj.newvalue == "newvalue13" )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # GMUnlockHero
        obj = client.objects_received["GMUnlockHero"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 14 )
        self.assert_( obj.gmlogin == "gmlogin14" )
        self.assert_( obj.heroid == 1414 )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # GMLockHero
        obj = client.objects_received["GMLockHero"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 15 )
        self.assert_( obj.gmlogin == "gmlogin15" )
        self.assert_( obj.heroid == 1515 )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # MonitoringResults
        obj = client.objects_received["MonitoringResults"][0]
        self.assert_( obj )
        self.assert_( obj.property == "property18" )
        self.assert_( obj.counter == "counter18" )
        self.assert_( obj.value == 18 )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # AddIgnore
        obj = client.objects_received["AddIgnore"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 19 )
        self.assert_( obj.ignoreauid == 1919 )
        self.assert_( obj.reason == "reason19" )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # RemoveIgnore
        obj = client.objects_received["RemoveIgnore"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 20 )
        self.assert_( obj.ignoreauid == 2020 )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # GiveSessionAwards
        obj = client.objects_received["GiveSessionAwards"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 22 )
        self.assert_( obj.sessionpersistentid == 222222222222 )
        self.assert_( obj.nick == "nick22" )
        self.assert_( obj.heroid == 222 )
        self.assert_( obj.rchange.Gold == 1 )
        self.assert_( obj.rchange.Silver == 2 )
        self.assert_( obj.rchange.Perl == 3 )
        self.assert_( obj.rchange.RedPerl == 4 )
        self.assert_( obj.rchange.Population == 5 )
        self.assert_( obj.rchange.Resource1 == 6 )
        self.assert_( obj.rchange.Resource2 == 7 )
        self.assert_( obj.rchange.Resource3 == 8 )
        self.assert_( obj.rchange.Shard == 8 )
        self.assert_( obj.rtotal.Gold == 10 )
        self.assert_( obj.rtotal.Silver == 20 )
        self.assert_( obj.rtotal.Perl == 30 )
        self.assert_( obj.rtotal.RedPerl == 40 )
        self.assert_( obj.rtotal.Population == 50 )
        self.assert_( obj.rtotal.Resource1 == 60 )
        self.assert_( obj.rtotal.Resource2 == 70 )
        self.assert_( obj.rtotal.Resource3 == 80 )
        self.assert_( obj.rtotal.Shard == 80 )
        self.assert_( obj.rtotal.CWPoints_Player == 90 )
        self.assert_( obj.inc_reliability == 222222 )
        self.assert_( obj.new_reliability == 2222222 )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )
        self.assert_( obj.talents and isinstance(obj.talents, list) and len(obj.talents) == 2)
        self.assert_( obj.talents[0].classId == 1 )
        self.assert_( obj.talents[0].instanceId == 2 )
        self.assert_( obj.talents[0].boundHeroClassId == 3 )
        self.assert_( obj.talents[1].classId == 4 )
        self.assert_( obj.talents[1].instanceId == 5 )
        self.assert_( obj.talents[1].boundHeroClassId == 6 )
        self.assert_( obj.force == 22.22 )
        self.assert_( obj.guildpointschange == 2 )
        self.assert_( obj.guildpointstotal == 22 )
        self.assert_( obj.appliedbuffs == [22, 222] )
        self.assert_( obj.leaverpointschange.leaverpointschange == 2 )
        self.assert_( obj.leaverpointschange.leaverpointstotal == 22 )
        self.assert_( obj.leaverpointschange.isleaverchanged == True )
        self.assert_( obj.leaverpointschange.isbadbehaviour == True )
        self.assert_( obj.leaverpointschange.isleaver == True )
        self.assert_( obj.leaverpointschange.type == "true leaver" )

        # LauncherStart
        obj = client.objects_received["LauncherStart"][0]
        self.assert_( obj )
        self.assert_( obj.hostid == 'hostid23' )
        self.assert_( obj.version == 'version23' )
        self.assert_( obj.auid == 23 )
        self.assert_( obj.locale == 'loc23' )

        # SocialRegister
        obj = client.objects_received["SocialRegister"][0]
        self.assert_( obj )
        self.assert_( obj.hostid == 'hostid26' )
        self.assert_( obj.auid == 'auid26' )
        self.assert_( obj.snid == 'snid26' )
        self.assert_( obj.snuid == 'snuid26' )
        self.assert_( obj.muid == 'muid26' )

        # SocialJoin
        obj = client.objects_received["SocialJoin"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 'auid27' )
        self.assert_( obj.snuid == 'snuid27' )

        # SocialMerge
        obj = client.objects_received["SocialMerge"][0]
        self.assert_( obj )
        self.assert_( obj.auid1 == 'auid1_28' )
        self.assert_( obj.auid2 == 'auid2_28' )

        # ResourcesChange
        obj = client.objects_received["ResourcesChange"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 29 )
        self.assert_( obj.gain == True )
        self.assert_( obj.source == 0 )
        self.assert_( obj.buildingname == "testbuilding" )
        self.assert_( obj.rchange.Gold == 1 )
        self.assert_( obj.rchange.Silver == 2 )
        self.assert_( obj.rchange.Perl == 3 )
        self.assert_( obj.rchange.RedPerl == 4 )
        self.assert_( obj.rchange.Population == 5 )
        self.assert_( obj.rchange.Resource1 == 6 )
        self.assert_( obj.rchange.Resource2 == 7 )
        self.assert_( obj.rchange.Resource3 == 8 )
        self.assert_( obj.rchange.Shard == 8 )
        self.assert_( obj.rchange.Currencies['Cur1'] ==  10)
        self.assert_( obj.rtotal.Gold == 10 )
        self.assert_( obj.rtotal.Silver == 20 )
        self.assert_( obj.rtotal.Perl == 30 )
        self.assert_( obj.rtotal.RedPerl == 40 )
        self.assert_( obj.rtotal.Population == 50 )
        self.assert_( obj.rtotal.Resource1 == 60 )
        self.assert_( obj.rtotal.Resource2 == 70 )
        self.assert_( obj.rtotal.Resource3 == 80 )
        self.assert_( obj.rtotal.Shard == 80 )
        self.assert_( obj.rtotal.Currencies['Cur1'] == 20 )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # QuestChange
        obj = client.objects_received["QuestChange"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 29 )
        self.assert_( obj.questid == 100500 )
        self.assert_( obj.reason == 0 )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # DynamicQuestChange
        obj = client.objects_received["DynamicQuestChange"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 29 )
        self.assert_( obj.questindex == 100600 )
        self.assert_( obj.questname == "testdquest" )
        self.assert_( obj.reason == 1 )
        self.assert_( obj.alternativeline == True )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # TournamentQuestChange
        obj = client.objects_received["TournamentQuestChange"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 29 )
        self.assert_( obj.questindex == 100600 )
        self.assert_( obj.questname == "testdquest" )
        self.assert_( obj.reason == 1 )
        self.assert_( obj.alternativeline == True )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # LauncherEvents
        obj = client.objects_received["LauncherEvents"][0]
        self.assert_( obj )
        self.assert_( obj.muid == 'muid30' )
        self.assert_( obj.auid == 30 )
        self.assert_( obj.bitmask == 3030 )
        self.assert_( obj.timestamp == 303030 )
        self.assert_( obj.locale == 'loc30' )

        # FactionSelect
        obj = client.objects_received["FactionSelect"][0]
        self.assert_( obj )
        self.assert_( obj.oldfaction  == "A" )
        self.assert_( obj.newfaction == "B" )
        self.assert_( obj.rchange.Gold == 1 )
        self.assert_( obj.rchange.Silver == 2 )
        self.assert_( obj.rchange.Perl == 3 )
        self.assert_( obj.rchange.RedPerl == 4 )
        self.assert_( obj.rchange.Population == 5 )
        self.assert_( obj.rchange.Resource1 == 6 )
        self.assert_( obj.rchange.Resource2 == 7 )
        self.assert_( obj.rchange.Resource3 == 8 )
        self.assert_( obj.rchange.Shard == 8 )
        self.assert_( obj.rtotal.Gold == 10 )
        self.assert_( obj.rtotal.Silver == 20 )
        self.assert_( obj.rtotal.Perl == 30 )
        self.assert_( obj.rtotal.RedPerl == 40 )
        self.assert_( obj.rtotal.Population == 50 )
        self.assert_( obj.rtotal.Resource1 == 60 )
        self.assert_( obj.rtotal.Resource2 == 70 )
        self.assert_( obj.rtotal.Resource3 == 80 )
        self.assert_( obj.rtotal.Shard == 80 )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # LauncherDActions
        obj = client.objects_received["LauncherDActions"][0]
        self.assert_( obj )
        self.assert_( obj.muid == 'muid31' )
        self.assert_( obj.auid == '31' )
        self.assert_( obj.timestamp == 313131 )
        self.assert_( obj.locale == 'loc31' )

        # RatingChange
        obj = client.objects_received["RatingChange"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 32 )
        self.assert_( obj.type == 0 )
        self.assert_( obj.sessionpersistentid == 3232323232323232 )
        self.assert_( obj.heroid == 3232 )
        self.assert_( obj.rating_inc == 32 )
        self.assert_( obj.rating_new == 323232 )

        # GuildCreated
        obj = client.objects_received["GuildCreated"][0]
        self.assert_( obj )
        self.assert_( obj.coreInfo.auid == 33 )
        self.assert_( obj.coreInfo.guildid == 34 )
        self.assert_( obj.coreInfo.faction == 'A' )
        self.assert_( obj.shortname == 'O_O' )
        self.assert_( obj.fullname == 'Boobs' )
        self.assert_( obj.rchange.Gold == 1 )
        self.assert_( obj.rchange.Silver == 2 )
        self.assert_( obj.rchange.Perl == 3 )
        self.assert_( obj.rchange.RedPerl == 4 )
        self.assert_( obj.rchange.Population == 5 )
        self.assert_( obj.rchange.Resource1 == 6 )
        self.assert_( obj.rchange.Resource2 == 7 )
        self.assert_( obj.rchange.Resource3 == 8 )
        self.assert_( obj.rchange.Shard == 8 )
        self.assert_( obj.rtotal.Gold == 10 )
        self.assert_( obj.rtotal.Silver == 20 )
        self.assert_( obj.rtotal.Perl == 30 )
        self.assert_( obj.rtotal.RedPerl == 40 )
        self.assert_( obj.rtotal.Population == 50 )
        self.assert_( obj.rtotal.Resource1 == 60 )
        self.assert_( obj.rtotal.Resource2 == 70 )
        self.assert_( obj.rtotal.Resource3 == 80 )
        self.assert_( obj.rtotal.Shard == 80 )
        self.assert_( obj.coreInfo.timestamp and isinstance(obj.coreInfo.timestamp, int) )

        # GuildRenamed
        obj = client.objects_received["GuildRenamed"][0]
        self.assert_( obj )
        self.assert_( obj.coreInfo.auid == 35 )
        self.assert_( obj.coreInfo.guildid == 36 )
        self.assert_( obj.coreInfo.faction == 'B' )
        self.assert_( obj.shortname == 'NUB' )
        self.assert_( obj.fullname == 'Nubiki' )
        self.assert_( obj.rchange.Gold == 1 )
        self.assert_( obj.rchange.Silver == 2 )
        self.assert_( obj.rchange.Perl == 3 )
        self.assert_( obj.rchange.RedPerl == 4 )
        self.assert_( obj.rchange.Population == 5 )
        self.assert_( obj.rchange.Resource1 == 6 )
        self.assert_( obj.rchange.Resource2 == 7 )
        self.assert_( obj.rchange.Resource3 == 8 )
        self.assert_( obj.rchange.Shard == 8 )
        self.assert_( obj.rtotal.Gold == 10 )
        self.assert_( obj.rtotal.Silver == 20 )
        self.assert_( obj.rtotal.Perl == 30 )
        self.assert_( obj.rtotal.RedPerl == 40 )
        self.assert_( obj.rtotal.Population == 50 )
        self.assert_( obj.rtotal.Resource1 == 60 )
        self.assert_( obj.rtotal.Resource2 == 70 )
        self.assert_( obj.rtotal.Resource3 == 80 )
        self.assert_( obj.rtotal.Shard == 80 )
        self.assert_( obj.coreInfo.timestamp and isinstance(obj.coreInfo.timestamp, int) )

        # GuildJoined
        obj = client.objects_received["GuildJoined"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 37 )
        self.assert_( obj.guildid == 38 )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )
        self.assert_( obj.faction == 'N' )

        # GuildLeaved
        obj = client.objects_received["GuildLeaved"][0]
        self.assert_( obj )
        self.assert_( obj.coreInfo.auid == 39 )
        self.assert_( obj.coreInfo.guildid == 40 )
        self.assert_( obj.coreInfo.faction == 'A' )
        self.assert_( obj.kicked == True )
        self.assert_( obj.coreInfo.timestamp and isinstance(obj.coreInfo.timestamp, int) )

        # GuildDisbanded
        obj = client.objects_received["GuildDisbanded"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 41 )
        self.assert_( obj.guildid == 42 )
        self.assert_( obj.faction == 'B' )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # ClientPings
        obj = client.objects_received["ClientPings"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 43 )
        self.assert_( obj.location == "43" )
        self.assert_( obj.msecPing == 4343 )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # RuneExpire( 44, 444, 4444, 44444 )
        obj = client.objects_received["RuneExpire"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 44 )
        self.assert_( obj.rune == 444 )
        self.assert_( obj.transactionsLeft == 4444 )
        self.assert_( obj.bonusLeft == 44444 )

        # RuneUnsoulbound( 45, 4545, 454545 )
        obj = client.objects_received["RuneUnsoulbound"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 45 )
        self.assert_( obj.rune == 4545 )
        self.assert_( obj.talent == 454545 )

        # RuneReplenish( 46, 4646 )
        obj = client.objects_received["RuneReplenish"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 46 )
        self.assert_( obj.rune == 4646 )

        # GMOperation( 47, BuildingMoveToStorage, "gmlogin47", "Building(47) moved to storage" )
        obj = client.objects_received["GMOperation"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 47 )
        self.assert_( obj.gmlogin == "gmlogin47" )
        self.assert_( obj.operation == GMOperationType.BuildingMoveToStorage )

        # TalentChange( 48, t1, GetFromTransmutation )
        obj = client.objects_received["TalentChange"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 48 )
        self.assert_( obj.talent.classId == 1 )
        self.assert_( obj.talent.instanceId == 2 )
        self.assert_( obj.talent.boundHeroClassId == 3 )
        self.assert_( obj.operation == TalentChangeOperation.GetFromTransmutation )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # TutorialStateChange
        obj = client.objects_received["TutorialStateChange"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 49 )
        self.assert_( obj.tutorialstate == "SessionStarted" )
        self.assert_( obj.timestamp and isinstance(obj.timestamp, int) )

        # GuildShopBuy
        obj = client.objects_received["GuildShopBuy"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 50 )
        self.assert_( obj.hassuzerain == True )
        self.assert_( obj.shoplevel == 5 )
        self.assert_( obj.shopitemid == 123 )
        self.assert_( obj.rchange.Gold == 1 )
        self.assert_( obj.rchange.Silver == 2 )
        self.assert_( obj.rchange.Perl == 3 )
        self.assert_( obj.rchange.RedPerl == 4 )
        self.assert_( obj.rchange.Population == 5 )
        self.assert_( obj.rchange.Resource1 == 6 )
        self.assert_( obj.rchange.Resource2 == 7 )
        self.assert_( obj.rchange.Resource3 == 8 )
        self.assert_( obj.rchange.Shard == 8 )
        self.assert_( obj.rtotal.Gold == 10 )
        self.assert_( obj.rtotal.Silver == 20 )
        self.assert_( obj.rtotal.Perl == 30 )
        self.assert_( obj.rtotal.RedPerl == 40 )
        self.assert_( obj.rtotal.Population == 50 )
        self.assert_( obj.rtotal.Resource1 == 60 )
        self.assert_( obj.rtotal.Resource2 == 70 )
        self.assert_( obj.rtotal.Resource3 == 80 )
        self.assert_( obj.rtotal.Shard == 80 )
        self.assert_( obj.rtotal.CWPoints_Player == 90 )
        self.assert_( obj.guildpointschange == 8 )
        self.assert_( obj.guildpointstotal == 10 )

        # GuildDailyStats
        obj = client.objects_received["GuildDailyStats"][0]
        self.assert_( obj )
        self.assert_( obj.guildid == 51 )
        self.assert_( obj.guildrating == 500 )
        self.assert_( obj.guildratingtoday == 20 )
        self.assert_( obj.guildpoints == 42 )
        self.assert_( obj.guildrank == 3 )
        self.assert_( len(obj.vassals) == 2 )
        self.assert_( obj.vassals[0].guildid == 1 )
        self.assert_( obj.vassals[0].guildpoints == 11 )
        self.assert_( obj.vassals[1].guildid == 2 )
        self.assert_( obj.vassals[1].guildpoints == 22 )
        self.assert_( len(obj.suggested) == 2 )
        self.assert_( obj.suggested[0].guildid == 1 )
        self.assert_( obj.suggested[0].guildrating == 11 )
        self.assert_( obj.suggested[1].guildid == 2 )
        self.assert_( obj.suggested[1].guildrating == 22 )

        # GuildInteraction
        obj = client.objects_received["GuildInteraction"][0]
        self.assert_( obj )
        self.assert_( obj.guildid == 52 )
        self.assert_( obj.type == GuildInteractionType.Decline )
        self.assert_( obj.siegeid == 1 )
        self.assert_( obj.waitingtime == 500 )

        # GuildPointsChange
        obj = client.objects_received["GuildPointsChange"][0]
        self.assert_( obj )
        self.assert_( obj.guildid == 53 )
        self.assert_( obj.auid == 1 )
        self.assert_( obj.source == "GMGuildStopSiege" )
        self.assert_( obj.playerpointschange == 3 )
        self.assert_( obj.playerpointstotal == 4 )
        self.assert_( obj.guildpointschange == 5 )
        self.assert_( obj.guildpointstotal == 6 )

        # RuneRoll
        obj = client.objects_received["RuneRoll"][0]
        self.assert_( obj )
        self.assert_( obj.auid == 54 )
        self.assert_( obj.rune == 20 )
        self.assert_( obj.source == RuneRollSource.Quest )
        self.assert_( obj.sessionpersistentid == 0 )

if __name__=="__main__":
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )
    unittest.main()
