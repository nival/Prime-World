# -*- coding: utf-8 -*-
import sys, os, imp
from base.helpers import *
import datetime
import time
from binascii import crc32
from StatisticCore.ttypes import TalentInfo
from StatisticCore.ttypes import TalentChangeOperation
from StatisticCore.ttypes import RuneRollSource
from enums import TournamentState

class event:

    def __repr__( self ):
        return str(self.startTime)+"   "+str(self.endTime)+"   "+str(self.type)+"   "+str(self.eventArgs)

    def __init__(self, configEvent):
        self.isValid = False
        line = configEvent["newValue"]["eventDescription"]
        #event type
        startIdx = 0
        endIdx = line.find( " ", startIdx )
        if endIdx == -1:
            err( "Bad line format (type), skip: %r" % line )
            return
        eventType = line[startIdx:endIdx].lower()
        if not eventType.strip().lower() in ["heroes", "resources", "fame", "talents", "houses", "custom", "gold",
                                             "extend_premium", "quests", "remove_quests", "skins", "lamp", "give_lamp",
                                             "tournament_state", "resources_for_games"]:
            err( "Bad line format (unknown event type), skip: %r" % line )
            return

        #event_args
        startIdx = endIdx+2
        endIdx = line.find( "\"", startIdx )
        if endIdx == -1:
            err( "Bad line format(args), skip: %r" % line )
            return
        eventArgs = line[startIdx:endIdx].split(",")

        if eventType == "custom":
            self.scclass = self.loadScript( eventArgs )
        if eventType == "always":
            self.scclass = self.loadScript( eventArgs )

        self.id = configEvent["persistentId"]
        self.startTime = configEvent["startTime"]
        self.endTime = configEvent["endTime"]
        self.type = eventType
        self.eventArgs = eventArgs
        self.isValid = True

    def apply(self, acc, sex, fraction, iDict):
        info("apply Event: %r %r %r" % (self.id, self.startTime, self.endTime))

        if not self.isActualEvent(acc.model.version.events):
            return acc.model

        if self.type == "heroes":
            for arg in self.eventArgs:
                exp = 0
                if ":" in arg:
                    pair = arg.split(":")
                    arg = pair[0]
                    exp = int(pair[1])
                heroFound = False
                for heroId in acc.model.Heroes:
                    hero = acc.model.getHeroByID( heroId )
                    staticHero = acc.SD.getStaticHero( hero )
                    if staticHero['persistentId'] == arg.strip():
                        heroFound = True
                if not heroFound:
                    addedHero = acc.model.hireHero( crc32(arg.strip()), acc.sex, iDict.WS, acc, iDict )
                    if addedHero and exp:
                        addedHero.changeExperience( exp, acc.model, iDict.WS, acc, iDict )

        elif self.type == "resources":
            for arg in self.eventArgs:
                res = arg.split("=")
                resources = acc.model.createResourcesTable()
                if hasattr(resources, res[0].strip()):
                    setattr(resources, res[0].strip(), self.parseStrToNum(res[1].strip()))
                acc.model.sell(resources, acc, False)

        elif self.type == "fame":
            acc.model.addFame(int(self.eventArgs[0].strip()), acc, acc.SD, iDict.STATS)

        elif self.type == "quests":
            for arg in self.eventArgs:
                force = 0
                if ":" in arg:
                    pair = arg.split(":")
                    arg = pair[0]
                    force = int(pair[1])

                strid = arg.strip()
                persistentId = int( crc32(strid) )
                staticQuest = acc.SD.getStaticQuestById( persistentId )
                config = iDict.Config.getConfig( acc.userlocale )
                if staticQuest:
                    if force:
                        acc.model.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, False, False, iDict.STATS, acc )
                    else:
                        acc.model.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, iDict.STATS, acc )

        elif self.type == "remove_quests":
            for arg in self.eventArgs:
                strid = arg.strip()
                persistentId = int( crc32(strid) )
                staticQuest = acc.SD.getStaticQuestById( persistentId )
                if staticQuest:
                    pendings = acc.model.PendingQuests.keys()[:]
                    for questID in pendings:
                        if persistentId == questID:
                            acc.model.PendingQuests.remove( questID )

                    actives = acc.model.ActiveQuests.keys()[:]
                    for questID in actives:
                        quest = acc.model.getQuestByID( questID )
                        if persistentId == quest.persistentId:
                            acc.model.ActiveQuests.remove( questID )

        elif self.type == "extend_premium":
            extend_time = int(self.eventArgs[0].strip()) * 24 * 60 * 60

            if acc.model.IsPremiumAccount():
                acc.model.LordInfo.PremiumAccountEnd += extend_time
            else:
                acc.model.LordInfo.PremiumAccountStart = int(round(time.time()))
                acc.model.LordInfo.PremiumAccountEnd = acc.model.LordInfo.PremiumAccountStart + extend_time

        elif self.type == "talents":
            for arg in self.eventArgs:
                talent_crc = crc32(arg.strip())
                staticTalent = acc.SD.getStaticTalentByTalentId( talent_crc )
                if staticTalent:
                    talent = acc.model.addTalent(talent_crc)
                    talInfo = TalentInfo( talent.PersistentId, talent.getID(), 0 )
                    iDict.STATS.addTalentChange(acc.db.auid, talInfo, TalentChangeOperation.GetFromEvent, str(self.id))
                else:
                    err( "Bad talent %r %r" % (arg.strip(), talent_crc) )

        elif self.type == "skins":
            for arg in self.eventArgs:
                args = arg.split(" ")
                if len(args) != 2:
                    err( "Bad skin args %r" % args )
                    return acc.model
                action = args[0].strip().lower()
                skin = crc32(args[1].strip())

                if action == "add":
                    addedSkin, reason = acc.model.giveSkinForFree(skin, acc)
                    if not addedSkin:
                        warn( reason )
                        return acc.model

                elif action == "delete":
                    skinToDelete = None
                    for skinId in acc.model.SkinsKeeper:
                        mdSkin = acc.model.getSkinByID( skinId )
                        if mdSkin.PersistentId == skin and not mdSkin.WasBought:
                            skinToDelete = mdSkin
                            break
                    if skinToDelete:
                        acc.model.deleteByID( mdSkin.id )
                    else:
                        warn( "Skin " + str(skin) + " not found" )

        elif self.type == "houses":
            for arg in self.eventArgs:
                level = 0
                if ":" in arg:
                    pair = arg.split(":")
                    arg = pair[0]
                    level = int(pair[1])
                building_crc = crc32(arg.strip())
                staticConstruction = acc.SD.getStaticConstructionByPersistentId( building_crc )
                if staticConstruction:
                    construction_uid = acc.model.addNewConstruction()
                    construction = acc.model.getConstructionByID( construction_uid )
                    construction.PersistentId = building_crc
                    construction.Level = level
                    acc.model.Pocket.add( construction )
                else:
                    err( "Bad construction %r" % building_crc )
                    return acc.model

        elif self.type == "custom":
            if self.scclass != None:
                acc.model = self.scclass.convertModelData( acc, acc.SD, iDict.Config.getConfig( acc.userlocale ), iDict.STATS )
            else:
                return acc.model

        elif self.type == "lamp":
            allowed_lamps = int(self.eventArgs[0].strip())
            info( "set allowed lamps to %d" % allowed_lamps )
            allowed_lamps_gold = allowed_lamps
            if len(self.eventArgs) >1:
                allowed_lamps_gold = int(self.eventArgs[1].strip())
            info( "set allowed lamps for gold status to %d" % allowed_lamps_gold )
            acc.model.MarketingEventsInfo.LampEventInfo.AllowedLamps = allowed_lamps
            acc.model.MarketingEventsInfo.LampEventInfo.AllowedLampsGoldStatus = allowed_lamps_gold

        elif self.type == "give_lamp":
            if(len(self.eventArgs)) >= 4:
                updateLastLampDropTime = True
                if len(self.eventArgs) > 4:
                    updateLastLampDropTime = int(self.eventArgs[4].strip())

                acc.model.replaceGoldLampEvent(self.eventArgs[0].strip(), int(self.eventArgs[1].strip()),
                                               int(self.eventArgs[2].strip()), int(self.eventArgs[3].strip()),
                                               updateLastLampDropTime)
                rune = acc.model.getGoldLampType(acc.SD)
                iDict.STATS.addLampRoll(acc.db.auid, rune, RuneRollSource.CustomEvent)

        elif self.type == "tournament_state":
            if self.eventArgs>0:
                if (self.eventArgs[0] =="none"):
                    acc.model.TournamentInfo.TournamentState = TournamentState.NotStarted
                elif self.eventArgs[0]=="ticketPhase":
                    acc.model.TournamentInfo.TournamentState = TournamentState.TicketSale
                elif self.eventArgs[0]=="tournamentPhase":
                    acc.model.TournamentInfo.TournamentState = TournamentState.InProgress
                    acc.model.TournamentInfo.TournamentTicket.LastGameTime = time.mktime(self.startTime.timetuple())

        elif self.type == "resources_for_games":
            if(len(self.eventArgs)) >= 2:
                games_required = int(self.eventArgs[0].strip())
                games = acc.model.Statistics.SessionsStarted

                if games >= games_required:
                    resources = acc.model.createResourcesTable()
                    for i in xrange(1, len(self.eventArgs)):
                        res = self.eventArgs[i].split("=")

                        if hasattr(resources, res[0].strip()):
                            setattr(resources, res[0].strip(), self.parseStrToNum(res[1].strip()))

                    info( "adding %r for %r games (%r required)", resources, games, games_required)
                    acc.model.sell(resources, acc, False)

        if self.id != "*":
            acc.model.version.events.append(self.id)
        return acc.model


    #def replenish_callback( self, response ):
    #    code = response["code"]
    #    if self.acc.db.eventsApplied:
    #        if code == ibilling.ERROR_CODE_OK:
    #            self.acc.db.eventsApplied.append(self.id)
    #    else:
    #        if code == ibilling.ERROR_CODE_OK:
    #            self.acc.db.eventsApplied = [self.id]
    #        else:
    #            self.acc.db.eventsApplied = []
    #    self.replenish = True


    def isActualEvent(self, events):
        if not self.id in events or self.id == "*":
            now = int(time.time())
            if now >= self.startTime and now <= self.endTime :
                return True
        return False

    def parseStrToNum( self, string ):
        try:
            x = float(string) if '.' in string else int(string)
            return x
        except ValueError:
            return 0

    def loadScript( self, args ):
        path = os.path.dirname( os.path.realpath(__file__) )
        filename = args[0].strip()
        try:
            if filename[-3:] == ".py":
                scriptspath = os.path.normpath( path )
                filename = os.path.normpath( os.path.join( scriptspath, filename ) )
                if os.path.isfile( filename ):
                    scclassname = os.path.splitext( os.path.basename( filename ) )[0]
                    info( "LoadScript: scclassname %r, script_name %r" % (scclassname, filename) )
                    scmodule = imp.load_source( scclassname, filename )
                    scclass = getattr( scmodule, scclassname )()
                    return scclass
                else:
                    err( "File %r doesn't exist" % filename )
                    return
            else:
                err( "Bad filename: %r, skipping" % (filename) )
                return
        except:
            catch()
            err( "Fail run script: " + filename )
            return




