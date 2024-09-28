# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import imp
from binascii import crc32   # zlib version is not cross-platform
from threading import Thread, Lock
from operator import itemgetter, attrgetter

from datetime import datetime, date, time

import pwconst # data-константы (про таланты и героев)

import zlib, bz2 ## TEST

from Events.event import *
from Events.EventMap import *
from Events.EventSkin import *

from iuserdata import IUserDataManager
from ModelData import ModelData
from jsonserialize import JSONSerialization
from changes import IGuidGenerator, IRequestChangeWriter
from validator import *

from party.PartyData import PartyData
from friendsdata.FriendsData import FriendsData
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from changes import PendingChangeWriter
from StaticData import StaticData

from MM import ESex
from party_const import FRACTION
from subaction import SubAction
from enums import TicketState, TicketPriseState, TournamentState
from StatisticCore.ttypes import RuneRollSource
import cfg

## --------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------

class ScriptInfo:
    def __init__(self, revision, patch, priority, script_name, scmodule, scclassname):
        self.revision = revision
        self.patch = patch
        self.priority = priority
        self.script_name = script_name
        self.scmodule = scmodule
        self.scclassname = scclassname


class PwNewModelManager(IUserDataManager, IGuidGenerator):
    """ Pw-шная модель данных (ModelData) """
    def __init__(self, ifaceDict, load_events=True, load_techs=True):
        self.scriptsMutex = Lock()
        #self.eventsMutex = Lock()
        #self.eventMapsMutex = Lock()
        #self.eventMapsForBanMutex = Lock()
        self.eventSkinsMutex = Lock()
        self.techsMutex = Lock()
        # заводим сериализатор, write-only (декодировать он не сможет, т.к. у него не будет своей рутовой ModelData)
        self._serializator = JSONSerialization(None)  # modeldata=None
        self.I = ifaceDict

        t0 = time.clock()

        self.__loadScriptList()  # грузим ВСЕ скрипты какие есть

        t1 = time.clock()
        info("load conversion scripts: %.3f" % (t1-t0))

        t3 = time.clock()

        #self.__loadEventList()  # грузим ВСЕ event's какие есть

        t4 = time.clock()
        info("load event scripts: %.3f" % (t4-t3))

        t5 = time.clock()

        #self.__loadEventMapList()  # грузим ВСЕ event's какие есть

        if load_events:
            self.__loadEventSkinList()  # грузим ВСЕ eventSkin'ы какие есть
        else:
            self.eventSkins = []

        #if load_techs:
        #    self.__loadTechs()
        #else:
        #    self.techs = {}
        #info("Techs: %r" % self.techs)

        t6 = time.clock()
        info("load eventMap scripts: %.3f" % (t6-t5))

        self.deployName = self.I.coord_res["deploy_name"]
        if self.deployName == "USA":
            dirUSA = os.path.join(os.path.dirname( os.path.realpath(__file__)), "Scripts/StaticUSAMMFix/ExportedSocialData.xml")
            self.staticUSA = StaticData(dirUSA, None)

        with open( os.path.join(os.path.dirname( os.path.realpath(__file__)), "Scripts/AuidToGuildAuidMap/data.json"), "r") as f:
            self.auidToGuildAuidMap = json.load(f)


    def reloadAllEvents(self):
        self.__loadScriptList()
        #self.__loadEventList()
        #self.__loadEventMapList()  # грузим ВСЕ event's какие есть
        self.__loadEventSkinList()  # грузим ВСЕ eventSkin'ы какие есть
        #self.__loadTechs()


    def resetPendingChanges(self, acc):
        acc.pending_changes = []
        acc.pending = PendingChangeWriter(acc)

    # ---------------------------------------------------------------------------------------------------
    def emptyModel(self, acc, iDict, server_version):
        info("pw emptyModel uid=%s" % str(acc.uid))
        self.iDict = iDict
        acc.model = ModelData()
        acc.friendsdata = FriendsData()
        acc.friendsdata.init(changeWriter=None)
        acc.BufferFriendsData = FriendsData()
        acc.BufferFriendsData.init(changeWriter=None)

        acc.partydata = PartyData()
        acc.partydata.init(changeWriter=None)
        acc.guilddata = GuildData()
        acc.guilddata.init(changeWriter=None)
        acc.siegedata = SiegeData()
        acc.siegedata.init(changeWriter=None)
        self.resetPendingChanges(acc)
        acc.db.fraction = FRACTION.NONE

    # ---------------------------------------------------------------------------------------------------
    # наполняем аккаунт только теми вещами, которые нужны для турнира
    def __createTournamentModel(self, acc, iDict, fraction='N', sex=0):
        self.scriptsMutex.acquire()
        lastScriptInfo = self.scripts[-1]
        self.scriptsMutex.release()
        acc.model.version.revision = lastScriptInfo.revision
        acc.model.version.patch = lastScriptInfo.patch
        acc.model.addTournamentItems(iDict, acc, "x", fraction, sex, create_heroes=1)

        acc.model.validatePingResults( iDict.Config.getConfig( acc.userlocale ) )
        acc.model.setTime()
        acc.model.setRandomSeed()
        acc.model.setTavernRandomSeed()
        acc.model.setTransmutationRandomSeed(iDict.Config.GoodSeeds)
        acc.model.setPremiumTransmutationRandomSeed(iDict.Config.PremiumGoodSeeds)
        acc.model.setTalentRandomSeed()
        acc.model.setReforgeRandomSeed()
        acc.model.updateLoginTime()
        acc.model.resetComplaints( acc )

        if acc.getConfig().TournamentSettings.IS_TOURNAMENT_SERVER and acc.db.auid in cfg.TOURNAMENT_SPECTATOR_AUIDS:
          acc.db.IsSpectator = True

        info( "Create new tournament modeldata version: %s %s" % (acc.model.version.revision, acc.model.version.patch) )

    # ---------------------------------------------------------------------------------------------------
    def newModel(self, acc, iDict, server_version, random_heroes=pwconst.CREATE_ALL_HEROES, random_items=-1, fraction='N', sex=0, guest=0, db=ClassDict(), old_md = None, isReset=False, **kwargs):
        info( "pw newModel uid=%s version: %s" % ( str(acc.uid), str(server_version) ))
        # kwargs: create_heroes, create_items
        t0 = time.time() #------

        self.iDict = iDict
        acc.model = ModelData()

        acc.friendsdata = FriendsData()
        acc.friendsdata.init( changeWriter=None )
        acc.BufferFriendsData = FriendsData()
        acc.BufferFriendsData.init( changeWriter=None )

        acc.partydata = PartyData()
        acc.partydata.init( changeWriter=None )

        acc.guilddata = GuildData()
        acc.guilddata.init( changeWriter=None )

        acc.siegedata = SiegeData()
        acc.siegedata.init(changeWriter=None)

        self.resetPendingChanges(acc)
        acc.model.init( changeWriter=None )

        t1 = time.time() #------
        # проверяем, не турнирный ли у нас сервер
        if iDict.Config.getMainConfig().TournamentSettings.IS_TOURNAMENT_SERVER:
          self.__createTournamentModel( acc, iDict, fraction, sex)
          return

        acc.model.create( acc.SD, acc, create_version=unicode(server_version), create_heroes=-1, fraction=fraction, sex=sex, db=db, guest=guest )
        t2 = time.time() #------

        ### строим вспомогательные индексы
        ##acc.model.buildCrossIndexes( acc.data )
        # на случай если размещение талантов в defaultTalentSet не совпадает с указанными рядами для талантов, надо пройтись по всем TalentSets и выкинуть "неподходящие" таланты в инвентарь
        #Validator.validateTalentSets( acc, server_version )

        t3 = time.time() #------
        #мехнизм сохранения нужных полей после сброса аккаунта
        acc.model.restoreFields(old_md)
        #выдача стартового квеста
        if not isReset:
            acc.model.GiveStartQuest(acc.SD.data["StartQuest"], acc, iDict)
        self.scriptsMutex.acquire()
        lastScriptInfo = self.scripts[-1]
        self.scriptsMutex.release()
        acc.model.version.revision = lastScriptInfo.revision
        acc.model.version.patch = lastScriptInfo.patch

        self.I.Config.eventsMutex.acquire()
        try:
            for event in self.I.Config.events:
                acc.model = event.apply( acc, sex, fraction, iDict )
        finally:
            self.I.Config.eventsMutex.release()

        self.techsMutex.acquire()
        try:
            for rev in self.I.Config.techs.keys():
                if "premium" in self.I.Config.techs[rev] and acc.model.LordInfo.LastTechPremium < rev:
                    acc.model.LordInfo.LastTechPremium = rev
                elif "lamp" in self.I.Config.techs[rev] and acc.model.MarketingEventsInfo.LampEventInfo.LastTechLamp < rev:
                    acc.model.MarketingEventsInfo.LampEventInfo.LastTechLamp = rev
                elif "guild_buffs" in self.I.Config.techs[rev] and acc.model.LordInfo.LastTechGuildBuffs < rev:
                    acc.model.LordInfo.LastTechGuildBuffs = rev
        finally:
            self.techsMutex.release()



        acc.model.calcEventInfo( self.I.Config.eventMaps, acc )
        acc.model.calcBanEventInfo(acc, self.I.Config.eventMapsForBan, self.I.Config.eventMaps )

        self.eventSkinsMutex.acquire()
        try:
            acc.model.calcEventSkin( self.eventSkins, acc )
        finally:
            self.eventSkinsMutex.release()

        acc.model.validatePingResults( iDict.Config.getConfig( acc.userlocale ) )
        acc.model.setTime()
        acc.model.setRandomSeed()
        acc.model.setTavernRandomSeed()
        acc.model.setTransmutationRandomSeed(iDict.Config.GoodSeeds)
        acc.model.setPremiumTransmutationRandomSeed(iDict.Config.PremiumGoodSeeds)
        acc.model.setTalentRandomSeed()
        acc.model.setReforgeRandomSeed()
        acc.model.updateLoginTime()
        acc.model.setLastPvPTime()
        acc.model.resetComplaints( acc )
        # Тут же надо проверить и выдать квесты, чтобы игрок смог их увидеть прямо после туториала
        acc.model.checkNewDynamicQuests(acc, self.I)
        acc.model.checkDynamicQuestPulls(acc, self.I)

        # Восстанавливаем инфу о золотой руне PF-73099
        acc.model.restoreLampInfo( acc )
        #acc.model.applyActiveQuestEvents(acc, iDict.Config)
        #acc.model.applyActiveTradeEvents(acc, iDict.Config)
        acc.model.validateRerollShop(acc)

        info( "Create new modeldata version: %s %s" % (acc.model.version.revision, acc.model.version.patch) )
        info( "new modeldata timing: new/init %.3f, create %.3f, cross/validate %.3f" % (t1-t0, t2-t1, t3-t2) )

    # ---------------------------------------------------------------------------------------------------
    def stampNewModel(self, acc):
        self.scriptsMutex.acquire()
        lastScriptInfo = self.scripts[-1]
        self.scriptsMutex.release()
        acc.model.version.revision = lastScriptInfo.revision
        acc.model.version.patch = lastScriptInfo.patch

        info( "stamp new modeldata version: %s %s",acc.model.version.revision, acc.model.version.patch )


    # --------------------------------------------------------------------------------
    def __preValidateMD( self, acc ):
        acc.model.validateBuildings( acc.SD )

    def __validateMD( self, iDict, acc, server_version, fraction, sex, generateRandomSeed=True, validate_guild=True,
                    validate_default_heroes=True, validate_heroes_stats=True, validate_dynamic_quests=True,
                    validate_last_login=True, do_not_change_time=False):
        if acc.data.mm:
            # если у нас старый формат mm (где могло быть несколько сессий и не было session.mmid), зачистить нафиг
            if not getattr(acc.data.mm, "mmid", None):
                warn("clearing old-style data.mm for uid=%s" % acc.uid)
                acc.data.mm = None

        # на случай если дерево талантов изменилось, надо пройтись по всем TalentSets и выкинуть "неподходящие" таланты
        #Validator.validateTalentSets( acc, server_version )\
        if validate_guild:
            acc.model.validateGuildBonus( acc, iDict )
            acc.model.validateGuildTalents( acc )
        acc.model.validateHeroes( fraction, acc.SD )
        if validate_default_heroes:
            acc.model.validateDefaultHeroes( iDict.WS, acc, iDict )
        acc.model.checkHeroesDefaultTalentSet( iDict.WS, acc)
        acc.model.validateAvailableHeroes( acc )
        if validate_heroes_stats:
            acc.model.validateHeroesStatPoints( acc, iDict.WS )
        acc.model.validateDefaultSkins( acc )
        acc.model.validateHeroesInMatchmaking( acc )
        acc.model.validateQuests( acc.SD )
        acc.model.validateStatisticEvents( acc.SD )
        acc.model.validateFinishSessionEvents( acc.SD )
        acc.model.validateTalentUpgradeEntities( acc.SD )
        for i in xrange(iDict.Config.getMainConfig().MAX_USER_TALENTSETS_COUNT):
            acc.model.validateEmptyTalentPersistentId( acc.SD, i )

        acc.model.validateSkins( iDict.Config.getConfig( acc.userlocale ), acc )
        acc.model.validatePingResults( iDict.Config.getConfig( acc.userlocale ) )
        if not do_not_change_time:
            acc.model.setTime()
        acc.model.validateGuildInvites( acc, iDict )
        if generateRandomSeed:
            acc.model.setRandomSeed()


        if not acc.model.LordInfo.TavernRandomSeed:
            acc.model.setTavernRandomSeed()
        if not acc.model.LordInfo.PremiumForgeRoll.TransmutationRandomSeed:
            acc.model.setPremiumTransmutationRandomSeed(iDict.Config.PremiumGoodSeeds)
        if not acc.model.LordInfo.OrdinaryForgeRoll.TransmutationRandomSeed:
            acc.model.setTransmutationRandomSeed(iDict.Config.GoodSeeds)
        if not acc.model.LordInfo.TalentRandomSeed:
            acc.model.setTalentRandomSeed()
        if not acc.model.LordInfo.ReforgeRandomSeed:
            acc.model.setReforgeRandomSeed()

        for k, v in enumerate(acc.model.LordInfo.Ratings.PlayerRatings):
            if acc.model.LordInfo.Ratings.PlayerRatings[k] is None:
                acc.model.LordInfo.Ratings.PlayerRatings[k] = 0
        if acc.model.LordInfo.Ratings.NumberOfWinsForPR is None:
            acc.model.LordInfo.Ratings.NumberOfWinsForPR = 0

        if not iDict.Config.getMainConfig().TournamentSettings.IS_TOURNAMENT_SERVER:
          if acc.model.TournamentInfo.TournamentTicket.UserAuid == acc.db.auid and acc.model.TournamentInfo.TournamentTicket.TicketPriseState == TicketPriseState.PriseInProgress:
            acc.model.TournamentInfo.TournamentTicket.TicketPriseState = TicketPriseState.HasNoPrise


        if iDict.Config.getMainConfig().TournamentSettings.IS_TOURNAMENT_SERVER and acc.db.auid in cfg.TOURNAMENT_SPECTATOR_AUIDS:
            acc.db.IsSpectator = True

        if iDict.Config.getMainConfig().TournamentSettings.IS_TOURNAMENT_SERVER and acc.model.TournamentInfo.TournamentTicket.IsSynchronized == False:
            acc.model.TournamentInfo.TournamentTicket.IsSynchronized = False
            acc.model.TournamentInfo.sendTournamentTicket( acc, iDict.HTTP )

        acc.model.validateTavern(acc.SD, iDict.Config.getConfig( acc.userlocale ))
        if validate_dynamic_quests:
            acc.model.validateDynamicQuests(acc, iDict)
            acc.model.validateDynamicQuestsActuality(acc, self.I)
        if validate_last_login:
            acc.model.validateLastPvPSession(acc, iDict)
            acc.model.validateLastLogin(acc, iDict)
        acc.model.applyCompletedOperatorEvents(acc, iDict.WS, self.I.STATS)
        acc.model.applyActiveQuestEvents(acc, iDict.Config)
        acc.model.applyActiveTradeEvents(acc, iDict.Config)
        acc.model.applyActiveSeasonEvents(acc, iDict.Config)
        acc.model.updateLoginTime()
        acc.model.validateGuildRequests()
        acc.model.validateRerollShop(acc)
        acc.model.validateMap(acc)

    def __loadTechs(self):
        self.techsMutex.acquire()
        try:
            self.techs = loadTechsFromFile()
        finally:
            self.techsMutex.release()


    def __loadScriptList( self ):
        self.scriptsMutex.acquire()
        try:
            self.scripts = []
            path = os.path.dirname( os.path.realpath(__file__) )
            versionfile = os.path.normpath( os.path.join( path, "Scripts/version.txt" ) )
            file = open( versionfile, "r" )
            lines = file.readlines()
            file.close()
            for line in lines:
                if line[0] == '#': # a comment (or disabled string)
                    continue
                startIdx = 0
                endIdx = line.find( " ", startIdx )
                if endIdx == -1:
                    err( "Bad format line, skip: %r" % line )
                    continue
                revision = int(line[startIdx:endIdx])
                startIdx = endIdx+1
                endIdx = line.find( " ", startIdx )
                if endIdx == -1:
                    err( "Bad format line, skip: %r" % line )
                    continue
                patch = int(line[startIdx:endIdx])
                startIdx = endIdx+1
                endIdx = line.find( " ", startIdx )
                if endIdx == -1:
                    err( "Bad format line, skip: %r" % line )
                    continue
                priority = int(line[startIdx:endIdx])

                filename = line[endIdx+1:].strip()
                if filename[-3:] == ".py":
                    scriptspath = os.path.normpath( os.path.join( path, "Scripts" ) )
                    filename = os.path.normpath( os.path.join( scriptspath, filename ) )
                    if os.path.isfile( filename ):
                        scclassname = os.path.splitext( os.path.basename( filename ) )[0]
                        info( "LoadScript: scclassname %r, script_name %r" % (scclassname, filename) )
                        scmodule = imp.load_source( scclassname, filename )
                        scriptInfo = ScriptInfo( revision, patch, priority, filename, scmodule, scclassname )
                        self.scripts.append( scriptInfo )
                        info( "Add script: file %r, ver %s %s" % (filename, revision, patch) )
                    else:
                        err( "File %r not exist" % filename )
                else:
                    err( "Bad filename in script list: %r, skipping whole line: %r" % (filename, line) )
        finally:
            self.scriptsMutex.release()
        return self.scripts

    # -------------------------------------------------------------------------------------------------------------
    def __loadEventList( self ):
        self.eventsMutex.acquire()
        try:
            self.events = []
            path = os.path.dirname( os.path.realpath(__file__) )
            eventsfile = os.path.normpath( os.path.join( path, "../config/events.txt" ) )
            file = open( eventsfile, "r" )
            lines = file.readlines()
            file.close()
            for line in lines:
                eventInfo = event( line )
                if eventInfo.isValid:
                    self.events.append( eventInfo )
                else:
                    err( "Bad event line format, skiping: %r" % line )
                    #info( "Add event: file %r, ver %s %s" % (filename, revision, patch) )
        finally:
            self.eventsMutex.release()

    #def __loadEventMapList( self ):
    #    self.eventMapsMutex.acquire()
    #    self.eventMapsForBanMutex.acquire()
    #    try:
    #        self.eventMaps = []
    #        self.eventMapsForBan = []
    #        path = os.path.dirname( os.path.realpath(__file__) )
    #        eventMapsfile = os.path.normpath( os.path.join( path, "../config/eventMaps.txt" ) )
    #        file = open( eventMapsfile, "r" )
    #        lines = file.readlines()
    #        file.close()
    #        for line in lines:
    #            eventMapInfo = EventMap( line )
    #            if eventMapInfo.isValid:
    #                if eventMapInfo.isForBan:
    #                    self.eventMapsForBan.append( eventMapInfo )
    #                else:
    #                    self.eventMaps.append( eventMapInfo )
    #            else:
    #                err( "Bad eventMap line format, skiping: %r" % line )
    #    finally:
    #       self.eventMapsMutex.release()
    #       self.eventMapsForBanMutex.release()


    def __loadEventSkinList( self ):
        self.eventSkinsMutex.acquire()
        try:
            self.eventSkins = []
            path = os.path.dirname( os.path.realpath(__file__) )
            eventSkinsfile = os.path.normpath( os.path.join( path, "../config/eventSkins.txt" ) )
            file = open( eventSkinsfile, "r" )
            lines = file.readlines()
            file.close()
            for line in lines:
                eventSkinInfo = EventSkin( line )
                if eventSkinInfo.isValid:
                    self.eventSkins.append( eventSkinInfo )
                else:
                    err( "Bad eventSkin line format, skiping: %r" % line )
        finally:
            self.eventSkinsMutex.release()


    # -------------------------------------------------------------------------------------------------------------
    # выбираем подмножество скриптов, подходящее к текущей версии
    def __generateScriptList( self, version ):
        self.scriptsMutex.acquire()
        try:
            if self.scripts:
                for i,scriptInfo in enumerate(self.scripts):
                    if scriptInfo.revision > version.revision or ( scriptInfo.revision == version.revision and scriptInfo.patch > version.patch ):
                        # поскольку скрипты в self.scripts[] должны лежать строго по порядку ревизий, просто отрезаем часть списка начиная с данного scriptInfo
                        scripts = self.scripts[i:]
                        scripts = self.__sortScriptList( scripts )
                        return scripts
        finally:
            self.scriptsMutex.release()

        return []

    def __sortScriptList( self, scripts ):
        priorityScripts = []

        for i,scriptInfo in enumerate(scripts):

            if scriptInfo.priority != 0:
                priorityScripts.append(scriptInfo)
                del scripts[i]
        priorityScripts = sorted(priorityScripts, key=attrgetter('priority'))

        scripts = priorityScripts + scripts

        return scripts

    # -------------------------------------------------------------------------------------------------------------
    def __runScript( self, scriptInfo, md, load_dict, acc ):
        newmd = None
        db = None
        try:
            scclass = getattr( scriptInfo.scmodule, scriptInfo.scclassname )()
            newmd, db = scclass.convertModelData( self, acc, md, load_dict )
        except:
            err( "Fail run script: " + scriptInfo.script_name )
            raise

        newmd.version.revision = scriptInfo.revision
        newmd.version.patch = scriptInfo.patch
        return newmd, db


    # -------------------------------------------------------------------------------------------------------------
    def loadModel( self, acc, load_string, iDict, server_version, fraction=FRACTION.NONE, sex=0, run_conversion_scripts=True, run_event_scripts=True,
                   generateRandomSeed=True, clear_event_skins=True, validate_guild=True, validate_default_heroes=True,
                   validate_heroes_stats=True, apply_techs=True, validate_dynamic_quests=True, validate_last_login=True,
                   do_not_change_time=False, **kwargs):
        t0 = time.time()

        self.iDict = iDict
        acc.model = ModelData()

        acc.friendsdata = FriendsData()
        acc.friendsdata.init( changeWriter=None )
        acc.BufferFriendsData = FriendsData()
        acc.BufferFriendsData.init( changeWriter=None )

        acc.partydata = PartyData()
        acc.partydata.init( changeWriter=None )

        acc.guilddata = GuildData()
        acc.guilddata.init( changeWriter=None )

        acc.siegedata = SiegeData()
        acc.siegedata.init(changeWriter=None)

        self.resetPendingChanges(acc)
        acc.model.init( changeWriter=None )
        acc.model.create( acc.SD, acc, create_version=u"", create_heroes=0, sex=sex, guest=acc.guest, **kwargs )

        t1 = time.time()

        try:
            acc.model.load( load_string )
            acc.model.init( changeWriter=None )

            ##info( "DEBUG loadModel for uid=%d: %s" % (acc.uid, str(acc.model.generateJsonDict()) ))

            t2 = time.time()

            if run_conversion_scripts:
                info( "ModelData version: " + str(acc.model.version.revision) + " " + str(acc.model.version.patch) )
                scriptInfos = self.__generateScriptList( acc.model.version )
                for scriptInfo in scriptInfos:
                    t10 = time.clock()
                    acc.model, acc.db = self.__runScript( scriptInfo, acc.model, load_string, acc )
                    t11 = time.clock()
                    info( "time %.3f runScript %s OK, ModelData version: %s %s" % (t11-t10, scriptInfo.script_name, acc.model.version.revision, acc.model.version.patch) )

            banned = acc.db.banned and (time.time() < acc.db.bantime or acc.db.bantime == 0)

            self.__preValidateMD( acc )

            if run_event_scripts and not banned:
                self.I.Config.eventsMutex.acquire()
                try:
                    for event in self.I.Config.events:
                        t12 = time.clock()
                        acc.model = event.apply( acc, sex, fraction, iDict)
                        t13 = time.clock()
                        info( "time %.3f runEvent %s OK" % (t13-t12, event.id) )

                finally:
                    self.I.Config.eventsMutex.release()


            t3 = time.time()

            if clear_event_skins:
                acc.model.clearSkinInfo()
                self.eventSkinsMutex.acquire()
                try:
                    acc.model.calcEventSkin( self.eventSkins, acc )
                finally:
                    self.eventSkinsMutex.release()

            acc.model.calcEventInfo( self.I.Config.eventMaps, acc )
            acc.model.calcBanEventInfo(acc, self.I.Config.eventMapsForBan, self.I.Config.eventMaps )

            acc.model.checkNewDynamicQuests(acc,self.I)
            self.__validateMD( iDict, acc, server_version, fraction, sex, generateRandomSeed=generateRandomSeed,
                             validate_guild=validate_guild, validate_default_heroes=validate_default_heroes,
                             validate_heroes_stats=validate_heroes_stats, validate_dynamic_quests=validate_dynamic_quests,
                             validate_last_login=validate_last_login, do_not_change_time=do_not_change_time)
            acc.model.checkDynamicQuestPulls(acc, self.I)
            acc.model.calcResourcesLimit( acc.SD, acc.guest )
            acc.model.recalcPopulation( acc.SD, acc.guest )
            acc.model.resetComplaints( acc )

            # Выдаем бонусную голду и руну нивальцам PF-74335
            if acc.db.IsDeveloper:
                nivalBonusMonths = self.__needNivalBonus( acc )
                if nivalBonusMonths > 0:
                    acc.model.replaceGoldLampEvent( 100, 10000, 1, 48*60*60, False )
                    iDict.BILL.replenish( acc.db.auid, 1000*nivalBonusMonths, "Nival bonus for employment", None )
                    rune = acc.model.getGoldLampType(acc.SD)
                    iDict.STATS.addLampRoll(acc.db.auid, rune, RuneRollSource.NivalGift)
            if apply_techs:
                self.techsMutex.acquire()
                try:
                    techKeys = self.I.Config.techs.keys()
                    techKeys.sort()
                    for key in techKeys:
                        if "premium" in self.I.Config.techs[key] and acc.model.LordInfo.LastTechPremium < key:
                            acc.model.LordInfo.LastTechPremium = key
                            acc.model.LordInfo.PremiumAccountEnd += self.I.Config.techs[key]["premium"]
                        elif "lamp" in self.I.Config.techs[key] and acc.model.MarketingEventsInfo.LampEventInfo.LastTechLamp < key:
                            acc.model.MarketingEventsInfo.LampEventInfo.LastTechLamp = key
                            acc.model.MarketingEventsInfo.LampEventInfo.EndTime += self.I.Config.techs[key]["lamp"]
                        elif "guild_buffs" in self.I.Config.techs[key] and acc.model.LordInfo.LastTechGuildBuffs < key:
                            acc.model.LordInfo.LastTechGuildBuffs = key
                            acc.model.updateGuildBuffs(self.I.Config.techs[key]["guild_buffs"])
                finally:
                    self.techsMutex.release()

            t4 = time.time()

            info( "loadModel timing for uid=%d: create %.3f, load %.3f, scripts %.3f, validate %.3f" % (acc.uid, t1-t0, t2-t1, t3-t2, t4-t3) )

        except:
            catch()
            warn( "loadModel acc failed (uid=%s)" % acc.uid )
            acc.failed = 1 # ставим признак "не сохраняться и не отвечать на logged actions"
            acc.failed_traceback = catch()
            return # если load обломался, не нужно ресетить аккаунт (см. followup "проблема wipe и изменения формата данных на сервере" 28.07.2011 16:40)


    def __monthdelta( self, date, delta ):
        m, y = (date.month+delta) % 12, date.year + ((date.month)+delta-1) // 12
        if not m: m = 12
        d = min(date.day, [31,
            29 if y%4==0 and not y%400==0 else 28,31,30,31,30,31,31,30,31,30,31][m-1])
        return date.replace(day=d,month=m, year=y)


    def __diffmonth( self, d1, d2 ):
        monthsVal = 0
        curTime = int(time.mktime(d1.timetuple()))
        bonusTime = int(time.mktime(d2.timetuple()))
        realTime = bonusTime
        while curTime > realTime:
            realDate = self.__monthdelta( datetime.datetime.fromtimestamp( float(bonusTime) ), monthsVal+1 )
            realTime = int(time.mktime(realDate.timetuple()))
            if curTime > realTime:
                monthsVal += 1
        return monthsVal


    def __needNivalBonus( self, acc ):
        if not acc.db.IsDeveloper:
            return 0

        # Ни разу не заходили - первый заход
        if not hasattr(acc.db, "NivalLastBonusTime") or not acc.db.NivalLastBonusTime:
            now = datetime.datetime.now()
            newdate = datetime.datetime( now.year, now.month, 10 )

            # Зашли после 10го числа, ничего не даем
            if now > newdate:
                acc.db.NivalLastBonusTime = int(time.mktime(newdate.timetuple()))
                return 0
            # Зашли до 10го числа - ставим прошлый месяц
            else:
                newestdate = self.__monthdelta( newdate, -1 )
                acc.db.NivalLastBonusTime = int(time.mktime(newestdate.timetuple()))
                return 0

        # Уже есть поле NivalLastBonusTime
        else:
            now = datetime.datetime.now()
            lastBonusTime = datetime.datetime.fromtimestamp( float(acc.db.NivalLastBonusTime) )
            numberMonths = self.__diffmonth( now, lastBonusTime )
            if numberMonths > 0:
              newdate = self.__monthdelta( lastBonusTime, numberMonths )
              acc.db.NivalLastBonusTime = int(time.mktime(newdate.timetuple()))

            return numberMonths

        return 0


    # ---------------------------------------------------------------------------------------------------
    def pretty(self, save_data):
        SubAction.convertResponseObjects(save_data)
        return json_pretty( save_data )

    # ---------------------------------------------------------------------------------------------------
    # этим методом WS готовит пользовательские данные к сериализации (заглушка просто возвращает сам словарь, в неизмененном виде)
    def prepareModel(self, modeldata):
        return self.toJson( modeldata, forClient=False )
