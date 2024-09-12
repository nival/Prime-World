# -*- coding: utf-8 -*-
from base.helpers import *
import datetime
import functools ,itertools
from datetime import date
from jsonserialize import JSONSerialization
from baseclasses import *
from changes import *
from collects import *
from ref import *
from modeldata.StaticData import StaticData

from Construction import *
from Hero import *
from Talent import *
from ResourceTable import *
import random

import pwconst  # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from validator import *
from handlers import USER_RELIABILITY_INITIAL
from MM import ESex
from binascii import crc32
from modeldata.Construction import *
import ibilling
import EC
from modeldata.ScriptData import *
import MM  # matchmaking const
from enums import *
import isteam
import iaeria
import iarcgames
import izzimacom
from StatisticCore.ttypes import TalentInfo
from StatisticCore.ttypes import TalentChangeOperation
from StatisticCore.ttypes import RuneRollSource
from StatisticCore.ttypes import TournamentQuestResult
from AccountManagementAPI.ttypes import ConfigEventType
from tornado.httpclient import HTTPRequest
import cfg
from base.exceptions import *
from base.helpers import enum2String
import CC
from RerollHelper import RerollHelper
from logic.mute_account import *
from logic.remove_talents import *
from enums.RollEventItemType import RollEventItemType

FAT_CLIENT_SERVER_TIME_MAX_LAG = 5

MAX_TALENTS_FOR_EVENT_CURRENCIES = 1000

ETERNAL_MAPS = ["/Maps/Multiplayer/MOBA/_.ADMPDSCR", ]  # костыль по мотивам PF-95952


class ModelDataCustom(BaseObject):
    def __init__(self):
        self.__dict__["_modelChangeWriter"] = None
        self.__dict__["_writeChanges"] = False
        self.__dict__["_comment"] = "auto"
        self.__dict__["debugVar"] = False

    def newEmptyTalent(self):
        uid = self.nextGUID()
        var = Talent(self, uid, "ItemsKeeper/" + str(uid))
        self.ItemsKeeper.dictionary[
            uid] = var  # self.ItemsKeeper.add( uid, var ) без лишних проверок, ибо мы знаем, что такого uid еще нет
        return var, uid

    def create(self, SD, acc, create_version="x", fraction='N', sex=0, guest=0, **kwargs):
        self.create_version = create_version
        # ссылочку на глобальные GameData прикопаем глобально

        self.calcResourcesLimit(SD, guest)
        if guest == 1:
            initParams = SD.data['GuestInitParams']
        else:
            initParams = SD.data['PlayerInitParams']

        self.sell(initParams['resourceTable'], acc)
        self.LordInfo.Fame = initParams['fame']

        if kwargs.get("create_heroes"):
            # CUSTOM: создадим всех героев с необходимыми талантами
            self.createHeroes(fraction, sex, acc, SD)
            self.createBuildings(SD)
            # Карты по умолчанию
            self.createDefaultMaps(SD)

        self.recalcPopulation(SD, guest)
        self.setGeolocationalFlag(SD, acc.country_code)

        # дефолтные значения полей
        self.LordInfo.Reliability = USER_RELIABILITY_INITIAL
        self.LordInfo.Ratings.LordRating = SD.START_HERO_RATING['rating']
        self.LordInfo.Ratings.LordPublicRating = SD.START_HERO_RATING['rating']
        self.LordInfo.GuardInfo.NumberOfWins = 0.0
        self.initPlayerRatings(acc.getConfig())

        self.initAllTimesCounters()

        self.initInventoryTalents()

    def initPlayerRatings(self, configdata):
        for _ in xrange(configdata.PLAYER_RATING_PERIOD):
            self.LordInfo.Ratings.PlayerRatings.append(0)
        self.LordInfo.Ratings.LastRecalcPlayerRatingTime = int(time.time())
        self.LordInfo.Ratings.NumberOfWinsForPR = 0

    def save(self, save_data=None):
        save_data = save_data or self.generateJsonDict()
        return json_dumps(save_data)

    def load(self, data):
        if isinstance(data, basestring):
            data = json_loads(data)
        t0 = time.clock()  # #############
        self._serializator.fromDict(data)
        t1 = time.clock()  # #############
        info("_serializator.fromDict time: %.3f" % (t1 - t0))

    def dump_file(self, filename):
        f = open(filename, "wt")
        if f:
            save_dict = self.generateJsonDict()
            f.write(pretty(save_dict))

    # region IChangeWriter
    def modelChange(self, path, op, val):
        if self._modelChangeWriter:
            self._modelChangeWriter.writeStringToResponse(self.__class__.__name__, self._comment, path, op, val)

    def canWrite(self):
        return self._modelChangeWriter

    def setComment(self, name):
        self._comment = str(name)

    # включаем авто-запись изменений в нашей ModelData (в указанный changeWriter)
    def write(self, changeWriter):
        self._modelChangeWriter = changeWriter
        self._writeChanges = (changeWriter is not None)

    # отключаем авто-запись изменений в нашей ModelData
    def stop(self):
        self._modelChangeWriter = None
        self._writeChanges = False

    # эмулируем доступ к элементу как у словаря, чтобы работал поиск по абсолютным путям
    def get(self, key):
        return self.__dict__.get(key)

    # endregion - хотел разделить все на регионы... но быстро сдался :(

    def addHero(self):
        uid = self.addNewHero()
        hero = self.getHeroByID(uid)
        return uid, hero

    def addTalent(self, persistentId):
        item_id = self.addNewTalent()
        item = self.getTalentByID(item_id)
        item.PersistentId = persistentId
        item.IsNew = True
        # кладем ref в UserInventory
        self.UserInventory.add(item)
        return item

    def addTalentUpgradeEntity(self, persistentId):
        item_id = self.addNewTalentUpgradeEntity()
        item = self.getTalentUpgradeEntityByID(item_id)
        item.PersistentId = persistentId
        item.IsNew = True
        # кладем ref в TalentUpgradeEntities
        self.TalentUpgradeEntities.add(item)
        return item

    def setTime(self):
        self.FatClientServerTime = self.ServerTime
        self.ServerTime = int(round(time.time()))
        d = self.ServerTime - self.FatClientServerTime
        if d < 0 or d > FAT_CLIENT_SERVER_TIME_MAX_LAG:
            debug( "ModelDataCustom.setTime: wrong time delta: ServerTime - FatClientServerTime = %s. Overriding FatClientServerTime with ServerTime.", d)
            self.FatClientServerTime = self.ServerTime

    def setRandomSeed(self):
        random.seed()
        self.LordInfo.RandomSeed = random.randint(100000000, 2000000000)

    def setTavernRandomSeed(self):
        random.seed()
        self.LordInfo.TavernRandomSeed = random.randint(100000000, 2000000000)

    def setTransmutationRandomSeed(self, GoodSeeds):
        random.seed()
        if GoodSeeds:
            self.LordInfo.OrdinaryForgeRoll.TransmutationRandomSeed = random.choice(GoodSeeds)
        else:
            self.LordInfo.OrdinaryForgeRoll.TransmutationRandomSeed = random.randrange(100000000, 2000000000)
        return self.LordInfo.OrdinaryForgeRoll.TransmutationRandomSeed

    def setPremiumTransmutationRandomSeed(self, PremiumGoodSeeds):
        random.seed()
        if PremiumGoodSeeds:
            self.LordInfo.PremiumForgeRoll.TransmutationRandomSeed = random.choice(PremiumGoodSeeds)
        else:
            self.LordInfo.PremiumForgeRoll.TransmutationRandomSeed = random.randrange(100000000, 2000000000)
        return self.LordInfo.PremiumForgeRoll.TransmutationRandomSeed

    def setTalentRandomSeed(self):
        random.seed()
        self.LordInfo.TalentRandomSeed = random.randrange(100000000, 2000000000)

    def setReforgeRandomSeed(self):
        random.seed()
        self.LordInfo.ReforgeRandomSeed = random.randrange(100000000, 2000000000)

    # Implementation of Lehmer random number generator
    # seed * 16807 mod(2^31 - 1)
    # http://www.firstpr.com.au/dsp/rand31/
    def getRandomPure(self, seed):
        hi = 16807 * (seed >> 16)
        lo = 16807 * (seed & 0xffff)
        lo += (hi & 0x7FFF) << 16
        lo += hi >> 15
        if (lo > 2147483647):
            lo -= 2147483647
        return lo

    def getRandom(self, seed):
        return self.getRandomPure(seed) >> 8

    def getRandomInRange(self, seed, minV, maxV):
        maxrate = maxV - minV + 1
        if maxrate == 0:
            return 0
        return self.getRandom(seed) % maxrate + minV

    def freeNotClassTalents(self, hero, ts, tsId, SD):
        for _id in ts.Talents.keys():
            talent = self.getTalentByID(ts.Talents.get(_id))
            staticTalent = SD.getStaticTalent( talent )
            if staticTalent['rarity'] != "Class":
                hero.removeTalentFromTalentSet(tsId,talent,_id)

    def addCustomHero(self, hero_classname, sex, acc, SD):
        HERO = SD.getStaticHeroByClassName(hero_classname)
        if HERO:
            t0 = time.time()  # ---------------

            hero, hero_uid = self.newHero()
            _dict = hero.__dict__

            ##---- служебное:
            _dict["class_name"] = hero_classname
            _dict["PersistentId"] = crc32(hero_classname)
            ##---- нижеследующее (заведение дефолтных полей с дефолтными значениями), по идее, должна делать кодогенерация
            configdata = acc.getConfig()
            if configdata.GIVE_ALL_HEROES or sex == ESex.TUTORIAL:
                _dict["Hired"] = True
            else:
                _dict["Hired"] = (sex != ESex.FEMALE and HERO['lobbyData']['IsHeroHiredByDefaultMale']) or (
                sex == ESex.FEMALE and HERO['lobbyData']['IsHeroHiredByDefaultFemale'])

            _dict["Rating"] = configdata.HERO_START_RATING
            _dict["EpicWins"] = 0
            _dict["Master"] = False

            staticHero = SD.getStaticHero(hero)

            t1 = time.time()  # ---------------

            for tsId in xrange(0, configdata.MAX_USER_TALENTSETS_COUNT):
                ts, _id = self.newTalentSet()
                hero.TalentSets.add(tsId, ts)
                hero.createTalentSetFromDefault(self, staticHero, SD, tsId, configdata)
                hero.setActionBarIndexes(SD, tsId, self)
                hero.resetHeroStatPoints(acc, tsId)
                hero.CalcForce(self, None, acc, tsId, skipStatisticEvent=False)

            _dict["Version"] = staticHero['lobbyData']['Version']

            self.Heroes.add(hero)
            self.addDefaultTalentSetToInventory(hero)

            t2 = time.time()  # ---------------

            Hero_base.Hero_base_t1 += t1 - t0  # #######
            Hero_base.Hero_base_t3 += t2 - t1  # #######

    def validateHeroes(self, fraction, SD):
        for hero_id in self.Heroes.keys():
            hero = self.getHeroByID(hero_id)

            for tsId in hero.TalentSets.keys():
                for actionBarIdx in hero.TalentSets[tsId].ActionBar:
                    talent = self.getTalentByID(hero.TalentSets[tsId].ActionBar[actionBarIdx])
                    if talent:
                        staticTalent = SD.getStaticTalent(talent)
                        if staticTalent:
                            if (toint(staticTalent['flags']) & 256) != 0 and actionBarIdx not in hero.TalentSets[tsId].InstaCast.keys(): #256 is InstaCastFlag. See - EAbilityFlags in GeneratedFromEditor.cs
                                hero.TalentSets[tsId].InstaCast.set(actionBarIdx, True)

        for hero_id in self.Heroes.keys():
            hero = self.getHeroByID(hero_id)
            staticHero = SD.getStaticHero(hero)
            if staticHero:
                if fraction in SD.getFractions(staticHero['heroRace']):
                    continue
                else:
                    warn("Invalid hero fraction %s, %d (%s)", hero.PersistentId, hero_id, hero.class_name)
            else:
                warn("Invalid hero class %s, %d (%s)", hero.PersistentId, hero_id, hero.class_name)

            # for tsId in hero.TalentSets.keys():
            #     hero.removeHeroTalents(self, SD, tsId)
            self.deleteByID(hero.id)

        # поищем дубликаты героев и грохнем гадов коли найдем
        for hero_id in self.Heroes.keys():
            hero = self.getHeroByID(hero_id)
            dublicates = self.findAllHeroesByCrc32(hero.PersistentId)
            if len(dublicates) <= 1:
                continue
            else:
                mHero = max(dublicates, key=lambda obj: obj.lastPlayed)
                if hero_id != mHero.id:
                    warn("Duplicate of hero(hero_id=%s) PersistentId=%s, hero_id = %d (%s)", mHero.id, hero.PersistentId, hero_id, hero.class_name)
                    for tsId in hero.TalentSets.keys():
                        for key in hero.TalentSets[tsId].Talents.keys():
                            tid = hero.TalentSets[tsId].Talents.get(key)
                            if tid:
                                talent = self.getTalentByID(tid)
                                if talent:
                                    hero.moveTalentFromTalentSetToLibrary(talent, talent.id)
                                    if talent.defaultForHero and talent.defaultForHero.get():
                                        talent.defaultForHero = 0
                                    if talent.Soulbound and talent.Soulbound.get():
                                        talent.Soulbound = 0
                                    self.UserInventory.remove(talent)
                    hero1 = self.getHeroByID(hero_id)
                    if hero1:



                        for tid, talent in self.ItemsKeeper.iteritems():
                            if talent:
                                if talent.defaultForHero and talent.defaultForHero.object == hero_id:
                                    if not talent.defaultForHero.get():
                                        talent.defaultForHero.object = IGuidGenerator.InvalidUID
                                    else:
                                        talent.defaultForHero = 0

                                if talent.Soulbound and talent.Soulbound.object == hero_id:
                                    if not talent.Soulbound.get():
                                        talent.Soulbound.object = IGuidGenerator.InvalidUID
                                    else:
                                        talent.Soulbound = 0

                                if talent.Owner and talent.Owner.object == hero_id:
                                    if not talent.Owner.get():
                                        talent.Owner.object = IGuidGenerator.InvalidUID
                                    else:
                                        hero1.moveTalentFromTalentSetToLibrary(talent, talent.id)
                                        talent.Owner = 0

                                if talent.defaultForHero.object == mHero.id:
                                    self.UserInventory.add(talent)
                                if talent.Soulbound.object == mHero.id:
                                    self.UserInventory.add(talent)
                                if talent.Owner.object == mHero.id:
                                    self.UserInventory.add(talent)
                        # чистим на тот случай если герой почил в суе ранее, чем был удален из Heroes
                        for hid, h in self.Heroes.items():
                            if not h:
                                del self.Heroes.dictionary[hid]

                        self.deleteByID(hero_id)



    def canHireHero(self, hero_class_id, acc):
        staticHero = acc.SD.getStaticHeroByClassId(hero_class_id)
        if not staticHero:
            return None, None, "Invalid hero id"

        if staticHero['persistentId'] in acc.getConfig().INVALID_HEROES:
            return None, None, "Invalid hero"

        if acc.db.fraction not in acc.SD.getFractions(staticHero['heroRace']):
            return None, None, "Invalid hero hero fraction"

        for hero_id in self.Heroes:
            hero = self.getHeroByID(hero_id)
            if hero.PersistentId == hero_class_id:
                if hero.Hired:
                    return None, None, "Hero already hired"
                else:
                    return staticHero, hero, ""

        return staticHero, None, ""

    def hireHero(self, hero_class_id, sex, WS, acc, I):
        staticHero = acc.SD.getStaticHeroByClassId(hero_class_id)
        if staticHero:
            if staticHero['persistentId'] in acc.getConfig().INVALID_HEROES:
                return None

            if acc.db.fraction not in acc.SD.getFractions(staticHero['heroRace']):
                return None

            hero, hero_uid = self.newHero()
            hero.class_name = staticHero['persistentId']
            hero.PersistentId = hero_class_id
            hero.Hired = True

            hero.Rating = 0
            hero.correctRating(self, acc.getConfig(), I, acc, onHire=True)

            hero.EpicWins = 0
            hero.Master = False
            hero.Version = staticHero['lobbyData']['Version']


            staticHero = acc.SD.getStaticHero(hero)

            # попробуем выдать бесплатные скины
            self.giveFreeSkinsForHero(hero, staticHero, acc)

            #firstTalentSet, _id = self.newTalentSet()

            #hero.TalentSets.add(0, firstTalentSet)
            #hero.createTalentSetFromDefault(self, staticHero, acc.SD, 0)
            #hero.setActionBarIndexes(acc.SD, 0, self)
            #hero.resetHeroStatPoints(acc, 0)
            #hero.CalcForce(self, WS, acc,  0, onHire=True)

            for tsId in xrange(0, acc.getConfig().MAX_USER_TALENTSETS_COUNT):
                ts, _id = self.newTalentSet()
                hero.TalentSets.add(tsId, ts)
                hero.createTalentSetFromDefault(self, staticHero, acc.SD, tsId, acc.getConfig())
                hero.setActionBarIndexes(acc.SD, tsId, self)
                hero.resetHeroStatPoints(acc, tsId)
                hero.CalcForce(self, WS, acc, tsId, skipStatisticEvent=True)

            if self.hasBuilding("FirstBuyBuilding", acc.SD, True):
                hero.changeExperience(acc.SD.data['FirstBuyHeroExpBonus'], self, WS, acc, I)
                hero.FirstBuyApplied = True

            if self.MarketingEventsInfo.GoldHouseActionState == GoldHouseActionState.ShowBuyHeroEvent:
                if (self.hasAllHeroesForBuyAction(acc, acc.SD, I.Config.getMainConfig()) and
                        not self.hasGoldProductionHouse()):
                    self.MarketingEventsInfo.GoldHouseActionState = GoldHouseActionState.ShowBuyHouseEvent
            self.Heroes.add(hero)
            self.addDefaultTalentSetToInventory(hero)
            return hero

    def addDefaultTalentSetToInventory(self, hero):
        for tsId in hero.TalentSets.keys():
            ts = hero.TalentSets[tsId]
            badSlots = []
            for slot, talentId in ts.Talents.iteritems():
                talent = self.getTalentByID(talentId)
                if not talent:
                    warn(" HERO %s HAS WRONG TALENT %s IN TS %d", hero.class_name, talentId, tsId )
                    #hero.removeTalentFromTalentSet(tsId, None, talentId, False )
                    badSlots.append(slot)
                    for actionBarIdx, talId in ts.ActionBar.iteritems():
                        if talId == talentId:
                            ts.ActionBar[actionBarIdx] = -1
                            ts.InstaCast.set(actionBarIdx, False)
                            break
                elif talent.id not in self.UserInventory:
                    self.UserInventory.add(talent)

            for slot in badSlots:
                ts.Talents.remove(slot)

    # ----------------------------------------------------------------
    def createHeroes(self, fraction, sex, acc, SD):
        # создадим по одному герою каждого типа для нашей фракции
        Hero_base.Hero_base_t1 = 0.0
        Hero_base.Hero_base_t2 = 0.0
        Hero_base.Hero_base_t3 = 0.0

        t0 = time.time()  # --------

        try:
            hero_names = []
            for PersistentId in SD.data['Heroes']:
                staticHero = SD.data['Heroes'][PersistentId]
                if staticHero:
                    if fraction in SD.getFractions(staticHero['heroRace']):
                        hero_names.append(staticHero['persistentId'])
            if hero_names:
                #hero_count = len(hero_names)
                for class_name in hero_names:
                    #class_name = hero_names[i]
                    HERO = SD.getStaticHeroByClassName(class_name)
                    isHeroHiredByDefault = (sex != ESex.FEMALE and HERO['lobbyData']['IsHeroHiredByDefaultMale']) or (
                    sex == ESex.FEMALE and HERO['lobbyData']['IsHeroHiredByDefaultFemale'])
                    if isHeroHiredByDefault or acc.getConfig().GIVE_ALL_HEROES:
                        self.addCustomHero(class_name, sex, acc, SD)
            else:
                warn("bad hero_names_dict in createHeroes (fraction %s)" % fraction)
        except:
            catch()

        self.validateAvailableHeroes(acc)
        self.validateDefaultSkins(acc)

    def createTutorialHero(self, class_name, acc, MD):
        # note: the player MUST NOT has any heroes this moment!
        debug("createTutorialHero. acc.model = %s", acc.model.generateJsonDict())
        if not acc.model.Heroes:
            acc.model.init(changeWriter=None)

        MD.stampNewModel(acc)

        self.addCustomHero(class_name, ESex.TUTORIAL, acc, acc.SD)
        debug("createTutorialHero: hero %s added", class_name)
        # get it's id, id MUST be the only hero now
        return self.Heroes.keys()[0]  # it must exists!

        # ----------------------------------------------------------------

    def createHeroesForTournament(self, iDict, fraction, sex, acc):
        # создадим по одному герою каждого типа для нашей фракции
        Hero_base.Hero_base_t1 = 0.0
        Hero_base.Hero_base_t2 = 0.0
        Hero_base.Hero_base_t3 = 0.0

        try:
            hero_names = []
            for PersistentId in acc.SD.data['Heroes']:
                staticHero = acc.SD.data['Heroes'][PersistentId]
                if staticHero:
                    if fraction in acc.SD.getFractions(staticHero['heroRace']):
                        hero_names.append(staticHero['persistentId'])
            if hero_names:
                hero_count = len(hero_names)
                for i in xrange(hero_count):
                    class_name = hero_names[i]
                    self.addCustomHero(class_name, sex, acc, acc.SD)
            else:
                warn("bad hero_names_dict in createHeroes (fraction %s)" % fraction)
        except:
            catch()

        for hero_id in self.Heroes:
            hero = self.getHeroByID(hero_id)
            hero.Experience = acc.SD.getMaxHeroExp() - 1
            statPoints = 0
            curLvl = 0
            earnedLvl = acc.SD.getHeroExpLevel(hero.Experience)
            while not curLvl == earnedLvl:
                curLvl += 1
                # Выдаем статпоинты
                statPoints += acc.SD.getHeroStatPoints(curLvl)

            if statPoints:
                for tsId in hero.TalentSets.keys():
                    hero.changeStatPoints(statPoints, tsId)

        self.validateAvailableHeroes(acc)
        self.validateDefaultSkins(acc)

    def addTournamentTalents(self, acc):
        talents = []
        for talentID in acc.SD.data['Talents']:
            staticTalent = acc.SD.getStaticTalentByTalentId(talentID)
            if (staticTalent['rarity'] != "Class" and staticTalent['rarity'] != "ordinary"
                and staticTalent['rarity'] != "good" and talentID != 0 and staticTalent[
                'persistentId'] not in acc.getConfigValue("TALENTS_NOT_FOR_ROLL")):
                talents.append(talentID)

        talents.sort()

        for i in xrange(0, len(talents)):
            talent_id = acc.model.addNewTalent()
            talent = acc.model.getTalentByID(talent_id)
            talent.IsNew = False
            talent.PersistentId = talents[i]
            acc.model.UserInventory.add(talent_id)

    def createDefaultMaps(self, SD, rewrite=False):
        index = -1
        for defMap in SD.data['DefaultMaps']['Item']:
            index += 1
            if rewrite or self.LordInfo.MapsByType.get(index) == None:
                mapInfo, mapId = self.newMapInfo()
                mapInfo.Enabled = defMap['enabled']
                if 'dbid' in defMap['map'] and 'classType' in defMap['map']:
                    mapInfo.MapId = str(defMap['map']['dbid'])
                elif 'dbid' in defMap['group'] and 'classType' in defMap['group']:
                    mapInfo.MapId = str(defMap['group']['dbid'])

                self.LordInfo.MapsByType.remove(index)
                self.LordInfo.MapsByType.add(index, mapInfo)

    def createBuildings(self, SD):
        BuildedConstructions = SD.data['BuildedConstructions']
        if not hasattr(BuildedConstructions, "Item"):
            return
        for BuildedConstruction in BuildedConstructions['Item']:
            crc = crc32(BuildedConstruction['persistentId'])
            if SD.getStaticConstructionByPersistentId(crc):
                building_id = self.addNewConstruction()
                building = self.getConstructionByID(building_id)
                building.PersistentId = crc32(BuildedConstruction['persistentId'])
                building.Position.X = int(BuildedConstruction['position']['x'])
                building.Position.Y = int(BuildedConstruction['position']['y'])
                building.Position.Pitch = int(BuildedConstruction['position']['pitch'])
                building.Level = 0
                self.Buildings.add(building)
            else:
                err("Unknown construction in BuildedConstructions: persistentId = %r, check editor data!", BuildedConstruction['persistentId'])

    # кладем в UserInventory набор общих талантов "для любого героя" (по дизайнерскому списку)
    def initInventoryTalents(self):
        if 'INIT_TALENTS' in globals():
            for itemId in INIT_TALENTS:
                # создаем вещь (в keeper)
                uid = self.addNewTalent()
                item = self.getTalentByID(uid)
                item.PersistentId = crc32(itemId)

                # кладем ref в UserInventory
                self.UserInventory.add(item)

    # возвращаем индекс талантов для данного героя,
    @staticmethod
    def getHeroClassTalents(config, hero_class_id, SD):
        hero = SD.getStaticHeroByClassId(hero_class_id)
        if not hero:
            return []

        res = set([])
        for i in xrange(config.MAX_USER_TALENTSETS_COUNT):
            dts_talents = SD.getDefaultSetTalents(config, hero, i)
            for row in dts_talents:
                for talentData in row:
                    try:
                        if talentData.rarity == "Class":
                            res.add(talentData.name)
                    except:
                        pass

        return list(res)

    def initAllTimesCounters(self):
        self.LordInfo.lastFameUpdateTime_ = time.time()
        self.LordInfo.lastDodgesUpdateTime_ = time.time()
        for heroId in self.HeroesKeeper:
            hero = self.getHeroByID(heroId)

    # находим героя по persistentId == crc32(classname)
    def findHeroByCrc32(self, hero_crc32):
        for heroId, hero in self.HeroesKeeper.iteritems():
            if hero.PersistentId == hero_crc32:
                return hero, heroId
        # fail (нету такого):
        return None, 0

    # находим ВСЕХ героев (списком) по данному persistentId == crc32(classname)
    def findAllHeroesByCrc32(self, hero_crc32):
        heroes = []
        for heroId, hero in self.HeroesKeeper.iteritems():
            if hero.PersistentId == hero_crc32:
                heroes.append(hero)
        return heroes

    def addFame(self, value, acc, SD, STATS):
        lvlStart = SD.getFameLevel(self.LordInfo.Fame)
        if (self.LordInfo.Fame + value) <= 0:
            self.LordInfo.Fame = 0
        elif (self.LordInfo.Fame + value) >= SD.getMaxLordFame():
            self.LordInfo.Fame = SD.getMaxLordFame()
        else:
            self.LordInfo.Fame += value
        lvlEnd = SD.getFameLevel(self.LordInfo.Fame)
        if acc:
            acc.db.lord_level = lvlEnd

        hasNewLevel = (lvlStart != lvlEnd)

        if hasNewLevel:
            if acc:
                STATS.addCastleLevelChange(acc.db.auid, lvlEnd)
            finalprice = SD.emptyPrice()
            # Если поменялся уровень, то обновимся с keepalive
            self.LordInfo.lastFameUpdateTime_ -= MM.FAME_PERIOD
            # Выдадим награды
            for lvl in xrange(lvlStart + 1, lvlEnd + 1):
                price = SD.getResourcesForLevelUp(lvl)
                if price:
                    SD.getAddPrice(finalprice, price)

                _, Level = SD.getInterpolLevels(SD.data['LevelToResources']['resourcesPerLevel'], lvl)
                finalprice.PremiumAccountHours += Level["PremiumAccountHours"] * 60 * 60  # в часах
            self.sell(finalprice, acc, False)

    def getFame(self):
        return self.LordInfo.Fame

    '''
    def getReady2Manoeuvre( self, acc ):
        if acc.getConfig().TournamentSettings.IS_TOURNAMENT_SERVER:
            return True
        return self.LordInfo.ManoeuvreAllowed
    '''

    def canBuy(self, price, check_for_hero = False):
        if self.isEnoughGold(price, check_for_hero) and StaticData.isEnoughResources(price, self.Resources):
            return True
        return False

    def getNumberOfTalents(self, type, SD):
        count = 0
        for heroId in self.HeroesKeeper:
            hero = self.getHeroByID(heroId)
            if hero:
                for tsId in hero.TalentSets.keys():
                    for slot in hero.TalentSets[tsId].Talents.keys():
                        talent = self.getTalentByID(hero.TalentSets[tsId].Talents.get(slot))
                        if talent:
                            staticTalent = SD.getStaticTalent(talent)
                            if staticTalent:
                                if staticTalent['rarity'] == type or not type:
                                    count += 1

        for talentId in self.UserInventory:
            talent = self.getTalentByID(talentId)
            staticTalent = SD.getStaticTalent(talent)
            if staticTalent:
                if staticTalent['rarity'] == type or not type:
                    count += 1
        return count

    def getNumberOfHeroes(self, level, SD):
        count = 0
        for heroId in self.HeroesKeeper:
            hero = self.getHeroByID(heroId)
            if hero:
                if SD.getHeroExpLevel(hero.Experience) >= (int(level) - 1):
                    count += 1
        return count

    def isEnoughGold(self, price, check_for_hero = False):
        # fix for PF-103958
        if check_for_hero and int(price.Silver) <= 0 and int(price.Gold <= 0):
            return False
        return int(price.Gold) <= self.Resources.Gold


    def isEnoughResources(self, price):
        return StaticData.isEnoughResources(price, self.Resources)


    def createResourcesTable(self, **kwargs):
        # print [i for i in dir(a) if not i.endswith('__')]
        price = StaticData.emptyPrice()
        priceFields = ResourceTable._changeFields
        for key in priceFields:
            value = kwargs.get(key, 0)
            if key == 'Currencies':
                if isinstance(value, dict):
                    setattr(price, key, value.copy())
                else:
                    continue
            else:
                setattr(price, key, value)
        return price

    def calcResourseToAdd(self, dx, x, limit, cap):
        dx = int(dx)
        if dx < 0:
            dx = max(int(dx), -x)
        elif dx >= 0 and cap and limit != 0:
            dx = max(min(int(dx), limit - x), 0)

        newValue = x + int(dx)

        if newValue > 2147483647:
            newValue = 2147483647

        return newValue


    def sell(self, price, acc, cap=True):
        isdict = isinstance(price, dict)
        for name in ('Perl', 'RedPerl', 'Silver', 'Population', 'Resource1', 'Resource2', 'Resource3', 'Resource1_Rare',
                     'Resource2_Rare', 'Resource3_Rare', 'CWPoints_Player', 'Shard', 'Currencies'):
            val = price.get(name, 0) if isdict else getattr(price, name, 0)
            if val:
                if name == 'Currencies':
                    for currency, currency_value in val.iteritems():
                        limit = self.ResourcesLimit.Currencies.get(currency, 0)
                        if currency not in self.Resources.Currencies:
                            new_value = self.calcResourseToAdd(currency_value, 0, limit, cap)
                            self.Resources.Currencies.add(currency, new_value)
                        else:
                            was = self.Resources.Currencies.get(currency)
                            self.Resources.Currencies[currency] = self.calcResourseToAdd(currency_value, was, limit, cap)
                else:
                    setattr(self.Resources, name,
                            self.calcResourseToAdd(val, getattr(self.Resources, name, 0), getattr(self.ResourcesLimit, name, 0),
                                                   cap))

        val = price.get('PremiumAccountHours', 0) if isdict else getattr(price, "PremiumAccountHours", 0)
        if val:
            if not acc:
                warn_trace("sell() called without acc and with PremiumAccountHours = %s!", val)
            self.addPremiumAccount(val, acc)

    def checkHeroesDefaultTalentSet(self, WS, acc):
        for heroId in self.HeroesKeeper.keys():
            hero = self.getHeroByID(heroId)

            staticHero = acc.SD.getStaticHero(hero)

            if hero.Version != staticHero['lobbyData']['Version']:
                # инкрементировали версию lobby data - патчим талантсет героя
                info("hero.version mismatch for hero class %s: was %r new %r",
                     hero.class_name, hero.Version, staticHero['lobbyData']['Version'])
                hero.applyDefaultTalentSets(self, acc.SD, acc.getConfig(), True)
                self.__recalcHeroForce(hero, WS, acc, True)
            else:
                for tsId in hero.TalentSets.keys():
                    if hero.TalentSets[tsId].TalentSetCrc != acc.SD.getTalantSetCrc(staticHero, tsId, acc.getConfig()):
                        # изменили дефолтовый талант сет - патчим талантсет героя
                        info("hero.TalentSets[%r].TalentSetCrc mismatch for hero class %s: was %r new %r",
                             tsId, hero.class_name,
                             hero.TalentSets[tsId].TalentSetCrc,
                             acc.SD.getTalantSetCrc(staticHero, tsId, acc.getConfig()))
                        hero.applyDefaultTalentSets(self, acc.SD, acc.getConfig(), False)
                        self.__recalcHeroForce(hero, WS, acc, False)
                        break

    def __recalcHeroForce(self, hero, WS, acc, needResetHeroStatPoints):
        for _tsId in hero.TalentSets.keys():
            if needResetHeroStatPoints:
                hero.resetHeroStatPoints(acc, _tsId)
            hero.CalcForce(self, WS, acc, _tsId)
            debug("checkHeroesDefaultTalentSet hero.TalentSets[%r].Force=%r", _tsId, hero.TalentSets[_tsId].Force)

    def validateDefaultHeroes(self, WS, acc, I):
        for PersistentId in acc.SD.data['Heroes']:
            staticHero = acc.SD.data['Heroes'][PersistentId]
            if staticHero:
                isHeroHiredByDefault = (acc.db.sex != ESex.FEMALE and staticHero['lobbyData'][
                    'IsHeroHiredByDefaultMale']) or (acc.db.sex == ESex.FEMALE and staticHero['lobbyData'][
                    'IsHeroHiredByDefaultFemale'])
                if isHeroHiredByDefault:
                    heroST, heroMD, error_message = self.canHireHero(PersistentId, acc)
                    if heroST:
                        warn("validateDefaultHeroes: default hero %s was added to user data",
                             staticHero['persistentId'])
                        self.hireHero(PersistentId, acc.db.sex, WS, acc, I)

    def validateAvailableHeroes(self, acc):
        for heroId in self.HeroesKeeper:
            hero = self.getHeroByID(heroId)
            if hero:
                hero.__dict__["Enabled"] = True

                if hero.class_name in acc.getConfig().INVALID_HEROES:
                    hero.__dict__["Enabled"] = False
                    for buildingId in self.Buildings:
                        building = self.getConstructionByID(buildingId)
                        if building:
                            if hero.id in building.HeroesInBuilding:
                                building.removeHeroFromBuilding(hero, acc, acc.SD)

    def validateHeroesStatPoints(self, acc, WS):
        for heroId in self.HeroesKeeper:
            hero = self.getHeroByID(heroId)
            if hero:
                for i in hero.TalentSets.keys():
                    realStatPoints = 0
                    realStatPoints += hero.TalentSets[i].Stats.StatPoints
                    realStatPoints += hero.TalentSets[i].Stats.Strength
                    realStatPoints += hero.TalentSets[i].Stats.Intellect
                    realStatPoints += hero.TalentSets[i].Stats.Agility
                    realStatPoints += hero.TalentSets[i].Stats.Cunning
                    realStatPoints += hero.TalentSets[i].Stats.Fortitude
                    realStatPoints += hero.TalentSets[i].Stats.Will
                    realStatPoints += hero.TalentSets[i].Stats.Health / acc.SD.getStatPointsMultiplyer("Life")
                    realStatPoints += hero.TalentSets[i].Stats.Mana / acc.SD.getStatPointsMultiplyer("Energy")

                    statpoints = 0
                    for lvl in xrange(0, acc.SD.getHeroExpLevel(hero.Experience) + 1):
                        statpoints += acc.SD.getHeroStatPoints(lvl)

                    if realStatPoints < statpoints:
                        hero.resetHeroStatPoints(acc, i)
                        hero.CalcForce(self, WS, acc, i)

    def validateEmptyTalentPersistentId(self, SD, tsId):

        for talentId in self.UserInventory.keys():
            talent = self.getTalentByID(talentId)
            staticTalent = SD.getStaticTalent(talent)
            if not staticTalent:
                if talent.Owner and talent.Owner.get():
                    talent.Owner.moveTalentFromTalentSetToLibrary(talent, talentId )
                self.UserInventory.remove(talent)

        for heroId in self.HeroesKeeper:
            hero = self.getHeroByID(heroId)
            if hero and hero.TalentSets[tsId]:
                for slot in hero.TalentSets[tsId].Talents.keys():
                    tid = hero.TalentSets[tsId].Talents.get(slot)
                    item = self.getTalentByID(tid)
                    if item:
                        staticTalent = SD.getStaticTalent(item)
                        if not staticTalent:
                            hero.removeTalentFromTalentSet(tsId, item, item.id)
                    elif item is None and tid is not None:
                         err("validateEmptyTalentPersistentId bad talent hero %r slot %r id %r", hero.PersistentId, slot,tid)
                         hero.TalentSets[tsId].Talents.remove(slot)



        for buildingId in self.ConstructionsKeeper:
            building = self.getConstructionByID(buildingId)
            if building:
                allCrafted = building.CraftedTalents.keys()[:]
                allCrafted.sort()
                for talId in allCrafted:
                    staticTalent = SD.getStaticTalentByTalentId(talId)
                    if not staticTalent:
                        building.CraftedTalents.remove(talId)

    def validateFreeArea(self, SD, staticConstruction):
        availableArea = 0
        occupiedArea = 0

        for level in xrange(self.LordInfo.LevelOfExpansion):
            size = 0
            map = SD.getMap()
            if 'Item' in map['Grades']['Item'][level]['Sections']['Sections']:
                size = len(map['Grades']['Item'][level]['Sections']['Sections']['Item'])
            elif 'sectionsCount' in map['Grades']['Item'][level]:
                size = map['Grades']['Item'][level]['sectionsCount']
            availableArea += size

        for buildingId in self.Buildings:
            building = self.getConstructionByID(buildingId)
            staticBuilding = SD.getStaticConstruction(building)
            if staticBuilding:
                if 'Item' in staticBuilding['SectionsLockedForBuilding']['Sections']:
                    occupiedArea += len(staticBuilding['SectionsLockedForBuilding']['Sections']['Item'])

        if 'Item' in staticConstruction['SectionsLockedForBuilding']['Sections']:
            occupiedArea += len(staticConstruction['SectionsLockedForBuilding']['Sections']['Item'])

        if availableArea >= occupiedArea:
            return True
        return False

    def validateHeroesInMatchmaking(self, acc):
        for md_hero_id, md_hero in self.HeroesKeeper.iteritems():
            mm_InMatchmaking = False
            if acc.data.mm:
                if md_hero.id == acc.data.mm.hero_id:
                    mm_InMatchmaking = True

            if md_hero.InMatchmaking != mm_InMatchmaking:
                md_hero.InMatchmaking = mm_InMatchmaking

    def validateSkins(self, config, acc):
        for md_hero_id, md_hero in self.HeroesKeeper.iteritems():
            skin = md_hero.HeroSkins.CurrentSkin
            if skin and hasattr(skin, "PersistentId"):
                # self.acc.model.getSkinByID( skinId )
                static_skin = acc.SD.getStaticSkinByPersistentId(skin.PersistentId)
                md_hero.HeroSkins.CurrentSkin.IsAnimatedAvatar = static_skin['persistentId'] not in config.SKIN_AVATAR_BLOCK

                if not static_skin or not static_skin['legal'] or (static_skin['persistentId'] in config.INVALID_SKINS and static_skin['persistentId'] not in config.SEASON_SKINS):
                    md_hero.HeroSkins.CurrentSkin = IGuidGenerator.InvalidUID



            skins = md_hero.HeroSkins.Skins
            for skinId in skins.keys():
                skin = self.getSkinByID(skinId)
                static_skin = acc.SD.getStaticSkinByPersistentId(skin.PersistentId)

                if not static_skin or not static_skin['legal'] or (static_skin['persistentId'] in config.INVALID_SKINS and static_skin['persistentId'] not in config.SEASON_SKINS):
                    err("DELETE SKIN(%r) by validateSkins auid(%r)" % (skin.id, acc.db.auid))
                    self.deleteByID(skin.id)
                    continue

                skin.IsAnimatedAvatar = static_skin['persistentId'] not in config.SKIN_AVATAR_BLOCK


    def isInMatchmaking(self):
        for md_hero_id, md_hero in self.HeroesKeeper.iteritems():
            if md_hero.InMatchmaking:
                return True
        return False

    def getTournamentMapData(self, mmMap, acc):
        group = acc.SD.getMapGroup(mmMap)
        if group:
            group = group.lower()
        for slotIndex in self.LordInfo.MapsByType.keys():
            mapInfo = self.LordInfo.MapsByType.get(slotIndex)
            if mapInfo and (
                    mapInfo.MapId.lower().find(mmMap) != -1 or (group and mapInfo.MapId.lower().find(group) != -1)):
                m = acc.SD.getStaticMap(mmMap)
                res = (
                    m["mapSettings"].get('fullPartyOnly', False),
                    m["matchmakingSettings"].get('mock', False),
                    m["matchmakingSettings"].get('fullPartySize', 0)
                )
                return res

    def isValidMap(self, mmMap, acc):
        if mmMap == "SPECTATE":
            return True, -1
        group = acc.SD.getMapGroup(mmMap)
        if group:
            group = group.lower()
        mmMap = mmMap.lower()
        for banMap in self.LordInfo.DisabledMaps:
            if banMap.lower() == mmMap or (group and group == banMap.lower()):
                return False, -1
        for slotIndex in self.LordInfo.MapsByType.keys():
            mapInfo = self.LordInfo.MapsByType.get(slotIndex)
            if mapInfo and (
                    mapInfo.MapId.lower().find(mmMap) != -1 or (group and mapInfo.MapId.lower().find(group) != -1)):

                if not self.isEnableMapForLeavers(mapInfo, acc):
                    return False, -1

                if mapInfo.Enabled:
                    if mapInfo.StartTime == 0 and mapInfo.EndTime == 0:
                        return True, slotIndex
                    curTime = int(round(time.time()))
                    return (mapInfo.StartTime < curTime and curTime < mapInfo.EndTime), slotIndex
                return False, -1

        return False, -1

    def isEnableMapForLeavers(self, mapInfo, acc):
        userStatus = self.getInternalUserStatus(acc.getConfig())
        if userStatus != LordStatus.Leaver:
            return True

        for map in acc.SD.data['AviableMaps']['maps']['Item']:
            if map['dbid'] == mapInfo.MapId:
                return map['AvailableForLeavers']

        return False

    def isPlusPointForLeave(self, mapId, acc):
        for map in acc.SD.data['AviableMaps']['maps']['Item']:
            if map['dbid'] == mapId:
                return map['PlusPointForLeave']
        return False

    def isMinusPointsPerFullGame(self, mapId, acc):
        for map in acc.SD.data['AviableMaps']['maps']['Item']:
            if map['dbid'] == mapId:
                return map['MinusPointsPerFullGame']
        return False

    def validateTalentUpgradeEntities(self, SD):
        for ent_id in self.TalentUpgradeEntities.keys():
            entity = self.getTalentUpgradeEntityByID(ent_id)
            static_entity = SD.getStaticTalentUpgradeEntityById(entity.PersistentId)
            if not static_entity:
                self.TalentUpgradeEntities.remove(entity)




    def validateBuildings(self, SD):
        for buildingId in self.Buildings.keys():
            building = self.getConstructionByID(buildingId)
            staticConstruction = SD.getStaticConstruction(building)
            if not staticConstruction:
                self.Buildings.remove(building)

        for buildingId in self.Pocket.keys():
            building = self.getConstructionByID(buildingId)
            staticConstruction = SD.getStaticConstruction(building)
            if not staticConstruction:
                self.Pocket.remove(building)

    def validateTavern(self, SD, config, rid=0):
        all_buildings = self.Buildings.keys()
        all_buildings.extend(self.Pocket.keys())
        for buildingId in all_buildings:
            building = self.getConstructionByID(buildingId)
            if building and building.ProductionState == ProductionState.Idle:
                staticConstruction = SD.getStaticConstruction(building)
                if staticConstruction and staticConstruction['classType'] == "Tavern":
                    building.checkTavernForReroll(staticConstruction, config, SD, self)

    def resetGuild(self, I, acc):
        self.resetGuildBuilding(I, acc)
        self.resetGuildBonus()
        #self.resetGuildTalents(acc)
        self.Resources.CWPoints_Player = 0

    def resetGuildBonus(self):
        # отбираем плюшки
        for heroId in self.Heroes:
            hero = self.getHeroByID(heroId)
            for tsId, ts in hero.TalentSets.iteritems():
                ts.GuildStats.Strength = 0
                ts.GuildStats.Intellect = 0
                ts.GuildStats.Agility = 0
                ts.GuildStats.Cunning = 0
                ts.GuildStats.Fortitude = 0
                ts.GuildStats.Will = 0
                ts.GuildStats.Health = 0
                ts.GuildStats.Mana = 0
                ts.GuildStats.StatPoints = 0
    """
    def resetGuildTalents(self, acc):
        #это делается раньше специальным мылом из гильдсевриса, но пока оставлю повторных проход тут
        for heroId in self.Heroes:
            hero = self.getHeroByID(heroId)
            for tsId, ts in hero.TalentSets.iteritems():
                to_remove = []
                for slot, at in ts.Talents.iteritems():
                    talent = acc.model.getTalentByID(at)
                    if talent.GuildBankInfo.get() and talent.GuildBankInfo.OwnerId != acc.auid and talent.GuildBankInfo.OwnerId != 0:
                        to_remove.append(talent)

                for talent in to_remove:
                    hero.removeTalentFromTalentSet(tsId, talent, talent.id)
    """

    def getGuildBuilding(self, SD):
        all_buildings = self.Buildings.keys()
        all_buildings.extend(self.Pocket.keys())

        for buildingId in all_buildings:
            building = self.getConstructionByID(buildingId)
            staticConstruction = SD.getStaticConstruction(building)
            if staticConstruction and staticConstruction['classType'] == "GuildBuilding":
                return building
        return None

    def resetGuildBuilding(self, I, acc):
        building = self.getGuildBuilding(acc.SD)
        if building and building.Level != 0:
            building.emptyAndStopBuilding(self, I, acc)
            building.Level = 0

    def getGuildBuildingLevel(self, SD):
        building = self.getGuildBuilding(SD)
        if building:
            return building.Level
        return -1

    def findGuildInviteByPersonAuid(self, person_auid):
        for invite_id, invite in self.GuildInvitesKeeper.iteritems():
            if invite.person_uid == person_auid:
                return invite, invite_id
        # fail (нету такого):
        return None, 0

    def validateQuests(self, SD):
        for questId in self.ActiveQuests.keys():
            quest = self.getQuestByID(questId)
            staticQuest = SD.getStaticQuest(quest)
            if staticQuest == None:
                self.ActiveQuests.remove(quest)

        for questId in self.CompletedQuests.keys():
            quest = self.getQuestByID(questId)
            staticQuest = SD.getStaticQuest(quest)
            if not staticQuest:
                self.CompletedQuests.remove(quest)

    def validateStatisticEvents(self, SD):
        eventsDict = {}
        for questId in self.ActiveQuests.iteritems():
            quest = questId[1]
            for objectiveId in quest.objectives:
                objective = self.getObjectByID(objectiveId)
                staticObjective = SD.getStaticObjective(quest, objective)
                if staticObjective and 'classType' in staticObjective['condition'] and staticObjective['condition'][
                    'classType'] == "StatisticEventCondition":
                    if 'Item' in staticObjective['condition']['events']:
                        for event in staticObjective['condition']['events']['Item']:
                            if event['eventType'] not in eventsDict:
                                eventsDict[event['eventType']] = {}
                            if event['description'] not in eventsDict[event['eventType']] or \
                                            eventsDict[event['eventType']][
                                                event['description']] > objective.lastEventId:
                                eventsDict[event['eventType']][event['description']] = objective.lastEventId
        eventsToDelete = []
        for eventId in self.StatisticEvents:
            event = self.getStatisticEventByID(eventId)
            if event.actionType == 0:
                continue
            if not event.isActual(self, eventsDict):
                # if action not in eventsDict or ((event.description not in eventsDict[action] or event.time < eventsDict[action][event.description]) and ("" not in eventsDict[action] or event.time < eventsDict[action][""])) :
                eventsToDelete.append(event)
        for event in eventsToDelete:
            self.StatisticEvents.remove(event)

    def validateGuildBonus(self, acc, I):
        guildBuildLevel = self.getGuildBuildingLevel(acc.SD)
        if guildBuildLevel > 0:
            if not acc.db.guildAuid:
                info("validateGuildBonus: reset guildBuilding")
                self.resetGuild(I, acc)

    def validateGuildTalents(self, acc):
        for talentId in self.ItemsKeeper.keys():
            talent = self.getTalentByID(talentId)
            if talent.GuildBankInfo.get() and talent.GuildBankInfo.GuildAuid and talent.GuildBankInfo.GuildAuid != acc.db.guildAuid:
                talent.GuildBankInfo = None
                tid = talent.getID()
                if talent.Owner and talent.Owner.get():
                    talent.Owner.moveTalentFromTalentSetToLibrary(talent, tid)
                self.deleteByID(tid)

    def isBadRef(self, auid, GuildData):
        member = GuildData.findMemberByAuid(auid)
        if not member:
            return True
        return False

    def validateGuildTalentsAfterSnLogin(self, acc):
        for talentId in self.ItemsKeeper.keys():
            talent = self.getTalentByID(talentId)
            if talent.GuildBankInfo.get() and talent.GuildBankInfo.GuildAuid and talent.GuildBankInfo.GuildAuid == acc.db.guildAuid:
                if self.isBadRef(talent.GuildBankInfo.OwnerId, acc.guilddata):
                    self.deleteByID(talent.getID())

    def validateFinishSessionEvents(self, SD):
        eventsDict = {}
        for questId in self.ActiveQuests.iteritems():
            quest = questId[1]
            for objectiveId in quest.objectives:
                objective = self.getObjectByID(objectiveId)
                staticObjective = SD.getStaticObjective(quest, objective)
                if staticObjective and 'classType' in staticObjective['condition'] and staticObjective['condition']['classType'] == "FinishSessionCondition":
                    if 'Item' in staticObjective['condition']['maps']:
                        for map in staticObjective['condition']['maps']['Item']:
                            if map['dbid'] not in eventsDict:
                                eventsDict[map['dbid']] = {}
                            if staticObjective['condition']['result'] not in eventsDict[map['dbid']] or \
                                            eventsDict[map['dbid']][
                                                staticObjective['condition']['result']] > objective.lastEventId:
                                eventsDict[map['dbid']][staticObjective['condition']['result']] = objective.lastEventId

        eventsToDelete = []
        for eventId in self.StatisticEvents:
            event = self.getStatisticEventByID(eventId)
            if event.actionType == 0 and not event.isActualFinishSessionEvent(self, eventsDict):
                eventsToDelete.append(event)
        for event in eventsToDelete:
            self.StatisticEvents.remove(event)

    def getUserLocale(self, acc):
        locale = acc.userlocale
        if not locale:
            locale = acc.model.LordInfo.UserLocale
        if not locale:
            locale = 'ru'
        locale = locale.lower()
        return locale

    # region Lootboxes

    def openLootbox(self, acc, static_lootbox):
        roll_result = dict(talents=[], resources=acc.SD.emptyPrice(), heroes=[], skins=[], flags=[],
                           upgradeHeroTalentsCount=0, premiumAcc=0, gold=0, lamp=None, talentUpgradeEntities=[])
        self.__process_RollItem(acc, static_lootbox['rollContainer'], roll_result)
        return roll_result

    def __process_RollItem(self, acc, roll_item, roll_result):
        class_type = roll_item['classType']

        if class_type == 'NothingRollItem':
            return
        if class_type == 'RarityTalentListRollItem':
            self.__process_RarityTalentListRollItem(acc, roll_item, roll_result)
        elif class_type == 'ResourceRollItem':
            self.__process_ResourceRollItem(acc, roll_item, roll_result)
        elif class_type == 'RollContainer':
            for i in xrange(0, roll_item['multiplicator']):
                self.__process_RollContainer(acc, roll_item, roll_result)
        elif class_type == 'TalentRollItem':
            self.__process_TalentRollItem(roll_item, roll_result)
        elif class_type == 'TalentUpgradeRollItem':
            self.__process_TalentUpgradeRollItem(acc, roll_item, roll_result)
        elif class_type == 'HeroRollItem':
            self.__process_HeroRollItem(acc, roll_item, roll_result)
        elif class_type == 'SkinRollItem':
            self.__process_SkinRollItem(acc, roll_item, roll_result)
        elif class_type == 'MarketingEventRollItem':
            self.__process_MarketingEventRollItem(acc, roll_item, roll_result)
        elif class_type == 'FlagRollItem':
            self.__process_FlagRollItem(acc, roll_item, roll_result)
        elif class_type == 'PremiumAccRollItem':
            self.__process_PremiumAccRollItem(acc, roll_item, roll_result)
        elif class_type == 'GoldRollItem':
            self.__process_GoldRollItem(acc, roll_item, roll_result)
        elif class_type == 'TalentUpgradeEntityRollItem':
            self.__process_TalentUpgradeEntityRollItem(acc, roll_item, roll_result)
        else:
            raise NotImplementedError('Unsupported RollItem found: {0}'.format(class_type))

    def __randomize(self, acc):
        #TODO: а зачем эта конструкция на выходе дающия тот же рандом?
        return float(acc.SD.getCffFromRange(random.random(), 0, 65535)) / 65536.0

    def __process_PremiumAccRollItem(self, acc, roll_item, roll_result):
        roll_result['premiumAcc'] += toint(roll_item['days'])

    def __process_GoldRollItem(self, acc, roll_item, roll_result):
        roll_result['gold'] += toint(roll_item['count'])

    def __process_RarityTalentListRollItem(self, acc, roll_item, roll_result):
        rarity = roll_item['rarity']
        talent_id = acc.SD.getEventRandomTalent(rarity, '', self.__randomize(acc))
        roll_result['talents'].append((talent_id, 0))

    def __process_ResourceRollItem(self, acc, roll_item, roll_result):
        lord_level = acc.SD.getFameLevel(self.LordInfo.Fame)
        lord_items = roll_item['itemsFromLord']
        if not lord_items:
            raise NotImplementedError('ResourceRollItem error: itemsFromLord not defined')
        last_item = None
        for item in lord_items:
            if item['level'] > lord_level:
                break
            last_item = item
        if not last_item:
            last_item = lord_items[-1]
        resource_count = last_item['count']
        deviation = last_item['deviation']
        if deviation > 0:
            resource_count = acc.SD.getCffFromRange(self.__randomize(acc),
                                                                   resource_count - deviation,
                                                                   resource_count + deviation)
        resource_type = roll_item['type']
        custom_type = roll_item['customCurrencyId']
        acc.SD.add_standard_value(roll_result['resources'], resource_type, custom_type, resource_count)

    def __process_RollContainer(self, acc, roll_item, roll_result):
        # Find items
        strict_items = []
        probable_items = []
        for item in roll_item['items']:
            probability = item['probability']
            if probability > 0:
                probable_items.append((item['item'], probability))
            elif probability < 0:
                strict_items.append(item['item'])
        # Process strict items
        for item in strict_items:
            self.__process_RollItem(acc, item, roll_result)
        # Find and process probable item
        if not probable_items:
            return
        total_probability = sum(p for (i,p) in probable_items)
        random_val = self.__randomize(acc) * total_probability
        aggregate_probability = 0.0
        for item, probability in probable_items:
            aggregate_probability += probability
            if random_val <= aggregate_probability:
                self.__process_RollItem(acc, item, roll_result)
                return
        self.__process_RollItem(acc, probable_items[-1][0], roll_result)

    def __process_TalentRollItem(self, roll_item, roll_result):
        roll_result['talents'].append((roll_item['talent'], 0))

    def __process_TalentUpgradeRollItem(self, acc, roll_item, roll_result):
        local_roll_result = dict(talents=[])
        self.__process_RollItem(acc, roll_item['talentItem'], local_roll_result)
        if not local_roll_result['talents']:
            return
        points = self.__process_TalentUpgradeProbabilityTable(acc, roll_item['upgradeTable'])
        roll_result['talents'] += ((talent[0], points) for talent in local_roll_result['talents'])

    def __process_TalentUpgradeProbabilityTable(self, acc, table):
        total_probability = sum(item['probability'] for item in table['upgrades'])
        random_val = self.__randomize(acc) * total_probability
        aggregate_probability = 0.0
        for item in table['upgrades']:
            aggregate_probability += item['probability']
            if random_val <= aggregate_probability:
                return item['points']
        return table['upgrades'][-1][0]

    def __process_HeroRollItem(self, acc, roll_item, roll_result):
        if roll_item['hero'] not in roll_result['heroes']:
            roll_result['heroes'].append(roll_item['hero'])

    def __process_SkinRollItem(self, acc, roll_item, roll_result):
        if roll_item['skin'] not in roll_result['skins']:
            roll_result['skins'].append(roll_item['skin'])

    def __process_TalentUpgradeEntityRollItem(self, acc, roll_item, roll_result):
		roll_result['talentUpgradeEntities'].append(roll_item['entity'])

    def __process_MarketingEventRollItem(self, acc, roll_item, roll_result):
        if roll_item['marketingEvent']['classType'] == 'UpgradeHeroTalentsEvent':
            roll_result['upgradeHeroTalentsCount'] += toint(roll_item['marketingEvent']['count'])
        elif roll_item['marketingEvent']['classType'] == 'GoldLampEvent':
            lamp = acc.SD.getMarketingEventRollItem(crc32(roll_item['persistentId']))
            if not lamp:
                warn("openLootbox: cannot resolve id {} as valid lamp".format(roll_item['persistentId']))
            elif self.isLampCanBeApplied(lamp, acc.getConfig().LampEventSettings):
                roll_result['lamp'] = lamp

    def __process_FlagRollItem(self, acc, roll_item, roll_result):
        if roll_item['flag'] not in roll_result['flags']:
            roll_result['flags'].append(roll_item['flag'])

    def applyLootboxRoll(self, acc, I, STATS, stat_name, lootbox, roll_result):
        reward = lootbox.Reward

        reward.IsApplied = True  # странная была выбрана схема - когда лутбокс добавляется через
        # он имеет пустую награду, у которой флаг теперь будет IsApplied == False, но как только
        # лутбокс откроют - он сразу применится в моделдату, проинитит поля награды (для отображения
        # в замке) и выставит флаг IsApplied в True

        # Add talents
        for item in roll_result['talents']:
            static_talent_id = item[0]
            talent_points = item[1]
            static_talent = acc.SD.getStaticTalentByTalentId(static_talent_id)
            if not static_talent:
                err("bad talent in lootbox %s", lootbox.PersistentId)
                continue

            talent_id = self.addNewTalent()
            talent = self.getTalentByID(talent_id)
            talent.PersistentId = static_talent_id
            talent.Points = talent_points
            talent.IsNew = True

            self.UserInventory.add(talent)
            reward.Talents.add(talent)

            statistics_talent_info = TalentInfo(talent.PersistentId, talent.getID(), 0)
            STATS.addTalentChange(acc.auid, statistics_talent_info, TalentChangeOperation.GetFromEvent,
                                         'from_lootbox %s' % lootbox.PersistentId)
        # Add resources
        if not acc.SD.is_empty_price(roll_result['resources']):
            reward.Resources.load_from_sd_dict(roll_result['resources'])
            self.sell(reward.Resources, acc, False)
            STATS.addResourcesChange(acc.auid, True, ResourceChangeItem.ContextBuyResource,
                                     'from_lootbox - Action: %s' % stat_name,
                                     reward.Resources, self.Resources)

        # Add hero
        for static_hero_id in roll_result['heroes']:
            self.__add_hero_from_lootbox(acc, I, static_hero_id, reward)

        # Add skin
        for static_skin_id in roll_result['skins']:
            valid_skin, reason = self.isValidSkin(static_skin_id, acc, True)
            if not valid_skin:
                continue
            static_skin = acc.SD.getStaticSkinByPersistentId(static_skin_id)
            hero = self.getHeroForSkin(static_skin, acc.SD)
            if not hero:
                static_hero_id = self.getHeroClassIdForSkin(static_skin, acc.SD)
                hero = self.__add_hero_from_lootbox(acc, I, static_hero_id, reward)
                if not hero:
                    continue
            skin = self.addSkinForHero(static_skin_id, hero, isDefault=False, wasBought=True,
                                          IsAnimatedAvatar=static_skin['persistentId'] not in acc.getConfig().SKIN_AVATAR_BLOCK)
            reward.Skins.add(skin)

        # Add TalentUpgradeEntity
        for static_entity_id in roll_result['talentUpgradeEntities']:
            static_entity = acc.SD.getStaticTalentUpgradeEntityById(static_entity_id)
            if static_entity:
                ent = self.addTalentUpgradeEntity(static_entity_id)
                reward.TalentUpgradeEntities.add(ent)

                data = "tal_upg_entity from_lootbox: pId={0}, type={1}, lootboxId={2}".format(
                    static_entity['persistentId'], static_entity['type'], lootbox.PersistentId)
                STATS.addTalentChange(acc.db.auid,
                                      TalentInfo(ent.PersistentId, ent.id, 0),
                                      TalentChangeOperation.GetEntityFromLootbox, data)

        # Add upgradeHeroTalents
        upgradeHeroTalentsCount = toint(roll_result['upgradeHeroTalentsCount'])
        self.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft += upgradeHeroTalentsCount
        reward.UpgradeHeroTalentsCount = upgradeHeroTalentsCount

        # Add flags
        for flag_id in roll_result['flags']:
            static_flag = acc.SD.getCustomFlagById(flag_id)
            if not static_flag:
                debug("applyLootboxRoll[open_lootbox] for auid = %d, getCustomFlagById: %s FAILED!" % (acc.db.auid, flag_id))
            else:
                if flag_id not in self.Flags:
                    self.Flags.append(flag_id)
                    reward.Flags.append(flag_id)

        # Add lamp
        if roll_result['lamp']:
            self.applyMarketingEvent(roll_result['lamp'], acc.getConfig().LampEventSettings)
            stats_rune = self.getGoldLampType(acc.SD)
            STATS.addLampRoll(acc.auid, stats_rune, RuneRollSource.CustomEvent) #TODO: завести новый источник рун
            reward.Lamp.DbId = roll_result['lamp']["dbid"]
            #reward.Lamp.Bonus = int(lampInfo[1])
            #reward.Lamp.Transactions = int(lampInfo[2])
            #reward.Lamp.Duration = int(lampInfo[3])

        # Add premium account days
        premium_acc_days = toint(roll_result['premiumAcc'])
        if premium_acc_days:
            self.addPremiumForFree(premium_acc_days, acc)
            reward.PremiumAccDays = premium_acc_days

        # Add gold
        gold = toint(roll_result['gold'])
        if gold:
            I.BILL.replenish(acc.auid, gold, "Gold from Lootbox", None)
            reward.Resources.Gold = gold



    def __add_hero_from_lootbox(self, acc, I, static_hero_id, reward):
        static_hero, hero, error_message = self.canHireHero(static_hero_id, acc)
        if not static_hero:
            return None
        if hero:
            hero.Hired = True
        else:
            hero = self.hireHero(static_hero_id, acc.sex, I.WS, acc, I)
        reward.Heroes.add(hero)
        return hero

    def deleteLootbox(self, lootbox):
        for k,v in lootbox.Reward.TalentUpgradeEntities.items():
            lootbox.Reward.TalentUpgradeEntities.remove(v)

        for k,v in lootbox.Reward.Heroes.items():
            lootbox.Reward.Heroes.remove(v)

        for k, v in lootbox.Reward.Skins.items():
            lootbox.Reward.Skins.remove(v)

        for k, v in lootbox.Reward.Talents.items():
            lootbox.Reward.Talents.remove(v)

        lootbox.Reward.deleteByID(lootbox.Reward.id)

        self.Lootboxes.remove(lootbox)

    # endregion

    # region Custom Events (common)

    def applyCompletedOperatorEvents(self, acc, WS, STATS):
        """
        Finding completed operator events of type RollEvent/QuestEvent (look at '_filter'),
        and apply talent delivery for specified custom currency
        :param acc: Account
        :param WS: Web Service
        :param STATS: Statistics Service
        :return:
        """

        if 'finishedEvents' not in WS.operatorEvents:
            return

        ordered_finished_events = [e for _, e in WS.operatorEvents['finishedEvents'].iteritems()]
        ordered_finished_events.sort(key=lambda e: e['endTime'], reverse=True)
        locale = self.getUserLocale(acc)
        for event in ordered_finished_events:
            if event['newValue'].get('locale', '').lower() != locale:
                continue
            # RollEvent
            # QuestEvent
            if event['type'] == ConfigEventType.RollEvent or event['type'] == ConfigEventType.QuestEvent:
                event_data = event.get('newValue', {})
                for currency in event_data.get('currencyIds', []):
                    if currency not in acc.model.Resources.Currencies:
                        continue
                    currency_value = acc.model.Resources.Currencies[currency]
                    talent_pid = event_data.get('completionTalentId', '')
                    convert_ratio = event_data.get('completionTalentRatio', 1)
                    if self.__give_event_completion_talents(acc, STATS, talent_pid, convert_ratio, currency_value):
                        acc.model.Resources.Currencies.remove(currency)
            # TradeEvent
            elif event['type'] == ConfigEventType.TradeEvent:
                event_data = event.get('newValue', {})
                event_guid = event_data.get('guid', -1)
                if event_guid not in self.TradeEvents:
                    continue
                event_progression = self.TradeEvents.get(event_guid)
                self.__completeTradeEvent(acc, WS, STATS, event_data, event_guid, event['persistentId'], event_progression)
            # SeasonEvent
            elif event['type'] == ConfigEventType.SeasonEvent:
                event_data = event.get('newValue', {})
                event_guid = event_data.get('guid', -1)
                if event_guid not in self.SeasonEvents:
                    continue
                event_progression = self.SeasonEvents.get(event_guid)
                self.__completeSeasonEvent(acc, WS, STATS, event_data, event_guid, event['persistentId'], event_progression)

    def __give_event_completion_talents(self, acc, STATS, talent_id, ratio, points):
        if not talent_id:
            return False
        if ratio <= 0:
            return False
        if points < 0:
            return False
        talent_crc = crc32(talent_id)
        talent_static = acc.SD.getStaticTalentByTalentId(talent_crc)
        if not talent_static:
            err("__give_event_completion_talents: Can't find static talent with id %s" % talent_id)
            return False
        count = int(points / ratio)
        if count > MAX_TALENTS_FOR_EVENT_CURRENCIES:
            count = MAX_TALENTS_FOR_EVENT_CURRENCIES
        for i in range(count):
            talent = acc.model.addTalent(talent_crc)
            talent_info = TalentInfo(talent.PersistentId, talent.getID(), 0)
            STATS.addTalentChange(acc.db.auid, talent_info, TalentChangeOperation.GetFromEvent)
        return True

    # endregion

    # region Roll Events

    # endregion

    # region Quest Events

    def applyActiveQuestEvents(self, acc, config_data):
        locale = self.getUserLocale(acc)
        local_config = config_data.getConfig(locale)

        # Remove obsolete records
        idx_to_remove = []
        for event_guid in self.QuestEvents:
            if not any(e for _, e in local_config.QuestEvents.iteritems() if e.Guid == event_guid):
                idx_to_remove.append(event_guid)

        for event_guid in idx_to_remove:
            self.QuestEvents.remove(event_guid)

        # Create new records in md and apply logic in existing
        idx_to_create = []
        for _, event in local_config.QuestEvents.iteritems():
            if event.Guid not in self.QuestEvents:
                idx_to_create.append(event.Guid)

        for event_id in idx_to_create:
            self.__questEventAddEmptyProgression(acc, event_id)

    def __questEventAddEmptyProgression(self, acc, event_guid):
        progr, _ = acc.model.newQuestEventProgression()
        progr.PersistentId = event_guid
        acc.model.QuestEvents.add(event_guid, progr)
        return True

    # endregion

    # region Trade Events

    def applyActiveTradeEvents(self, acc, config_data):
        locale = self.getUserLocale(acc)
        local_config = config_data.getConfig(locale)

        # Remove obsolete records
        idx_to_remove = []
        for event_guid in self.TradeEvents:
            if not any(e for _, e in local_config.TradeEvents.iteritems() if e.Guid == event_guid):
                idx_to_remove.append(event_guid)

        for event_guid in idx_to_remove:
            self.TradeEvents.remove(event_guid)

        # Create new records in md and apply logic in existing
        idx_to_create = []
        for _, event in local_config.TradeEvents.iteritems():
            if event.Guid not in self.TradeEvents:
                idx_to_create.append(event.Guid)

        for event_guid in idx_to_create:
            self.__tradeEventAddEmptyProgression(event_guid)

    def __tradeEventAddEmptyProgression(self, event_guid):
        progr, _ = self.newTradeEventProgression()
        progr.PersistentId = event_guid
        self.TradeEvents.add(event_guid, progr)

    @staticmethod
    def __isValidRollEventItemInTradeEvent(acc, roll_event_item, event_id):
        if roll_event_item.ItemType != RollEventItemType.Lootbox:
            return False, "checkValidRollEventItemInTradeEvent: Bad type roll_event_item ({}) in TradeEvent ({}) ".format(
                roll_event_item.ItemType, event_id)

        if crc32(roll_event_item.PersistentId) not in acc.SD.getStaticLootboxes():
            return False, "checkValidRollEventItemInTradeEvent: Can't find static lootbox ({}) in static data. TradeEvent ({}) ".format(
                roll_event_item.PersistentId, event_id)

        return True, ''

    def findAndGetTradeEventData(self, acc, event_id, validating=False):
        events = acc.getConfigValue("TradeEvents")
        if event_id not in events:
            return None, None, "findAndGetTradeEvent: Can't find trade event with id %d" % event_id

        if validating:
            # check Experience lootboxes in static data
            for _, experienceRelation in events[event_id].ExperienceRewardRelations.iteritems():
                isOk, errorInfo = ModelDataCustom.__isValidRollEventItemInTradeEvent(acc, experienceRelation.Reward.get(0), event_id)
                if not isOk:
                    return None, None, errorInfo

            # check WorldRating lootboxes in static data
            for _, worldRatingRelation in events[event_id].WorldRatingRewardRelations.iteritems():
                isOk, errorInfo = ModelDataCustom.__isValidRollEventItemInTradeEvent(acc, worldRatingRelation.Reward.get(0), event_id)
                if not isOk:
                    return None, None, errorInfo

        return events[event_id], self.TradeEvents[events[event_id].Guid], ''

    def recalcTradeEventExperience(self, trade_event):
        eventCoeffDict = dict()
        eventCoeffDict[trade_event.ExperienceCurrencyName] = 1
        for _, group in trade_event.TradeEventGroups.iteritems():
            for _, member in group.TradeGroupMembers.iteritems():
                eventCoeffDict[member.CurrencyName] = member.CurrencyCostPerExp

        currentUserCurrencies = dict(self.Resources.Currencies.dictionary)
        for name, _ in eventCoeffDict.iteritems():
            if name not in currentUserCurrencies:
                currentUserCurrencies[name] = 0

        exp = 0
        for name, val in eventCoeffDict.iteritems():
            exp += val * currentUserCurrencies[name]

        return exp

    def checkExperienceRewardsInTradeEventAndGiveIfNeeded(self, acc, trade_event, currentExperience):
        event_progression = self.TradeEvents[trade_event.Guid]

        if not event_progression:
            return False, 'Event_progression is None. TradeEventGuid: {}'.format(trade_event.Guid)

        collectedLootboxes = list(event_progression.CollectedLootboxes)
        lootBoxesWithTargetExperience = [(crc32(e.Reward.get(0).PersistentId), e.RewardCount) for idx, e in trade_event.ExperienceRewardRelations.iteritems() if currentExperience >= e.Experience]

        for lootboxPersistentId, rewardCount in lootBoxesWithTargetExperience:
            if lootboxPersistentId not in collectedLootboxes:
                event_progression.CollectedLootboxes.append(lootboxPersistentId)
                for i in range(rewardCount):
                    isOk, _ = self.addLootbox(lootboxPersistentId, acc)
                    if not isOk:
                        return False, 'checkExperienceRewardsInTradeEventAndGiveIfNeeded: bad lootboxPersistentId {}'.format(lootboxPersistentId)
            else:
                collectedLootboxes.remove(lootboxPersistentId)

        return True, ''

    def __completeTradeEvent(self, acc, WS, STATS, event_dict, event_guid, event_id, event_progression):

        def giveReward(sqlReply, event_progression):
            # kramarov: тут нельзя получать прогрессию евента! ее скорее всего уже удалили!
            reply = sqlReply['r']
            if not reply:
                return
            placeInWorld = int(reply[0]['place'])
            experience = int(reply[0]['experience'])

            debug('start givingReward place: {} exp: {}, {}'.format(placeInWorld, experience, sqlReply))

            # add completion talents
            talent_pid = event_dict.get('completionTalentId', '')
            convert_ratio = event_dict.get('completionTalentRatio', 1)
            self.__give_event_completion_talents(acc, STATS, talent_pid, convert_ratio, experience)

            # add reward to place in world
            if placeInWorld > 0:
                ratingRewardRelationsData = event_dict.get('worldRatingRewardRelations', [])
                for worldRatingRelation in ratingRewardRelationsData:
                    if placeInWorld > worldRatingRelation.get('worldPosition', 0):
                        continue
                    reward = worldRatingRelation.get('reward', {})
                    lb_persistant_id = reward.get('persistentId', '')
                    lb_persistant_id_crc32 = crc32(lb_persistant_id)
                    lb_count = worldRatingRelation.get('rewardCount', 0)
                    for i in range(lb_count):
                        debug('add loot {}'.format(lb_persistant_id_crc32))
                        isOk, _ = self.addLootbox(lb_persistant_id_crc32, acc)
                        if not isOk:
                            err('onTradeEventGiveRewardWithLeaderboard: bad lootboxPersistentId {}'.format(lb_persistant_id))

                    event_progression.Completed = True
                    break

            # remove event currencies
            currencies_for_remove = []
            currencies_for_remove.append(event_dict.get('experienceCurrencyName', ''))
            for group in event_dict.get('tradeEventGroups', []):
                for member in group.get('tradeGroupMembers', []):
                    currencies_for_remove.append(member.get('currencyName', ''))
            for currency in currencies_for_remove:
                if currency not in acc.model.Resources.Currencies:
                    continue
                acc.model.Resources.Currencies.remove(currency)

        if not event_progression:
            return

        if event_progression.Completed:
            return

        info('start getting place {} {} {}'.format(acc.db.auid, event_guid, event_id))
        WS.getTradeEventPlace(acc.db.auid, event_guid, callback=lambda x: giveReward(x, event_progression))

    # endregion

    # region Season Events

    def applyActiveSeasonEvents(self, acc, config_data):
        locale = self.getUserLocale(acc)
        local_config = config_data.getConfig(locale)

        # Remove obsolete records
        # idx_to_remove = []
        # for event_guid in self.SeasonEvents:
        #     if not any(e for _, e in local_config.SeasonEvents.iteritems() if e.Guid == event_guid):
        #         idx_to_remove.append(event_guid)
        #
        # for event_guid in idx_to_remove:
        #     self.SeasonEvents.remove(event_guid)

        # Create new records in md and apply logic in existing
        idx_to_create = []
        for _, event in local_config.SeasonEvents.iteritems():
            if event.Guid not in self.SeasonEvents:
                idx_to_create.append(event.Guid)

        for event_guid in idx_to_create:
            self.__seasonEventAddEmptyProgression(event_guid)

    def __seasonEventAddEmptyProgression(self, event_guid):
        progr, _ = self.newSeasonEventProgression()
        progr.PersistentId = event_guid
        self.SeasonEvents.add(event_guid, progr)

    @staticmethod
    def __isValidRollEventItemInSeasonEvent(acc, roll_event_item, event_id):
        if roll_event_item.ItemType != RollEventItemType.Lootbox:
            return False, "checkValidRollEventItemInTradeEvent: Bad type roll_event_item ({}) in TradeEvent ({}) ".format(
                roll_event_item.ItemType, event_id)

        if crc32(roll_event_item.PersistentId) not in acc.SD.getStaticLootboxes():
            return False, "checkValidRollEventItemInTradeEvent: Can't find static lootbox ({}) in static data. TradeEvent ({}) ".format(
                roll_event_item.PersistentId, event_id)

        return True, ''

    @staticmethod
    def __isValidLootboxInSeasonEvent(acc, lootbox_id, event_id):
        if crc32(lootbox_id) not in acc.SD.getStaticLootboxes():
            return False, "__isValidLootboxInSeasonEvent: Can't find static lootbox ({}) in static data. SeasonEvent ({}) ".format(
                lootbox_id, event_id)

        return True, ''

    def recalcSeasonEventProgress(self, season_event):
        currentUserCurrencies = dict(self.Resources.Currencies.dictionary)
        return currentUserCurrencies[season_event.RewardsCurrencyId] if season_event.RewardsCurrencyId in currentUserCurrencies else 0

    def checkProgressRewardsInSeasonEventAndGiveIfNeeded(self, acc, season_event, currentProgress):
        event_progression = self.SeasonEvents[season_event.Guid]

        if not event_progression:
            return False, 'Event_progression is None. SeasonEventGuid: {}'.format(season_event.Guid)

        collectedLootboxes = list(event_progression.CollectedLootboxes)
        reachedRewardsLootboxes = [(crc32(e.Reward.get(0).PersistentId), e.RewardCount) for idx, e in
                                         season_event.ProgressRewardRelations.iteritems() if
                                         currentProgress >= e.RequiredProgress]

        for lootboxPersistentId, rewardCount in reachedRewardsLootboxes:
            if lootboxPersistentId not in collectedLootboxes:
                event_progression.CollectedLootboxes.append(lootboxPersistentId)
                for i in range(rewardCount):
                    isOk, _ = self.addLootbox(lootboxPersistentId, acc)
                    if not isOk:
                        return False, 'checkProgressRewardsInSeasonEventAndGiveIfNeeded: bad lootboxPersistentId {}'.format(
                            lootboxPersistentId)
            else:
                collectedLootboxes.remove(lootboxPersistentId)

        return True, ''

    def __completeSeasonEvent(self, acc, WS, STATS, event_dict, event_guid, event_id, event_progression):

        def giveReward(sqlReply, user_event_progression):
            # kramarov: тут нельзя получать прогрессию евента! ее скорее всего уже удалили!
            reply = sqlReply['r']
            if not reply:
                return
            placeInWorld = int(reply[0]['place'])
            progress = int(reply[0]['progress'])

            debug('start givingReward place: {} progress: {}, {}'.format(placeInWorld, progress, sqlReply))

            # add reward to place in world
            if placeInWorld > 0:
                ratingRewardRelationsData = event_dict.get('worldRatingRewardRelations', [])
                for worldRatingRelation in ratingRewardRelationsData:
                    if placeInWorld > worldRatingRelation.get('worldPosition', 0):
                        continue
                    reward = worldRatingRelation.get('reward', {})
                    lb_persistant_id = reward.get('persistentId', '')
                    lb_persistant_id_crc32 = crc32(lb_persistant_id)
                    lb_count = worldRatingRelation.get('rewardCount', 0)
                    for i in range(lb_count):
                        debug('add loot {}'.format(lb_persistant_id_crc32))
                        isOk, _ = self.addLootbox(lb_persistant_id_crc32, acc)
                        if not isOk:
                            err('onSeasonEventGiveRewardWithLeaderboard: bad lootboxPersistentId {}'.format(
                                lb_persistant_id))
                    user_event_progression.Completed = True
                    break

            # add completion talents
            talent_pid = event_dict.get('completionTalentId', '')
            convert_ratio = event_dict.get('completionTalentRatio', 1)
            shop_currency_id = event_dict.get('shopCurrencyId', '')
            rewards_currency_id = event_dict.get('rewardsCurrencyId', '')
            currency_value = acc.model.Resources.Currencies[shop_currency_id]
            self.__give_event_completion_talents(acc, STATS, talent_pid, convert_ratio, currency_value)

            # remove event currencies
            currencies_for_remove = [shop_currency_id, rewards_currency_id]
            for currency in currencies_for_remove:
                if currency not in acc.model.Resources.Currencies:
                    continue
                acc.model.Resources.Currencies.remove(currency)

        if not event_progression:
            return

        if event_progression.Completed:
            return

        info('start getting season event place {} {} {}'.format(acc.db.auid, event_guid, event_id))
        WS.getSeasonEventPlace(acc.db.auid, event_guid, callback=lambda x: giveReward(x, event_progression))

    # endregion

    def validateGuildInvites(self, acc, I):
        for giId in self.IncomingGuildInvites.keys():
            guildInvite = self.getGuildInviteByID(giId)
            if guildInvite.timeToAutoDecline <= toint(time.time()):
                self.IncomingGuildInvites.remove(guildInvite)
            else:
                # направляем все изменения Model Data в pending changes
                self.write(acc.pending)
                acc.pending.setPrefix("guildExistanceCheck:")
                acc.model.setComment("auto")
                I.GS.checkGuildExists(acc, guildInvite.guildAuid, giId, self.OnGuildExistanceChecked)

    def OnGuildExistanceChecked(self, response):
        info("OnGuildExistanceChecked response: %s", response)
        try:
            if response and ('exists' in response or 'inviteId' in response):
                if not response["exists"]:
                    self.IncomingGuildInvites.remove(response["inviteId"])
            else:
                err("OnGuildExistanceChecked wrong response %r", response)
        except Exception as e:
            err("OnGuildExistanceChecked error: %s response [%r]", e, response)

    def validateGuildRequests(self):
        for _id in self.GuildApplications.keys():
            self.GuildApplications.remove(_id)
        self.LordInfo.UpdateGuildApplications = True

    def compareResourseToLimit(self, resourse, limit):
        if resourse > limit and limit != 0:
            return limit
        return resourse

    def calcResourcesLimit(self, SD, guest=0): #FEATURENEWRES: maybe add Shard to this def
        # 0 - значит лимита нет

        newLimits = ClassDict()

        limits = SD.data['ResourceAndInventoryLimits']
        if guest == 1:
            limits = SD.data['GuestResourceAndInventoryLimits']

        newLimits.Perl = limits['resourceLimits']['Perl']
        newLimits.RedPerl = limits['resourceLimits']['RedPerl']
        newLimits.Silver = limits['resourceLimits']['Silver']
        newLimits.Population = limits['resourceLimits']['Population']
        newLimits.Resource1 = limits['resourceLimits']['Resource1']
        newLimits.Resource2 = limits['resourceLimits']['Resource2']
        newLimits.Resource3 = limits['resourceLimits']['Resource3']
        newLimits.Resource1_Rare = limits['resourceLimits']['Resource1_Rare']
        newLimits.Resource2_Rare = limits['resourceLimits']['Resource2_Rare']
        newLimits.Resource3_Rare = limits['resourceLimits']['Resource3_Rare']
        newUserInventoryLimit = limits['inventoryLimits']

        for buildingId in self.Buildings:
            building = self.getConstructionByID(buildingId)
            staticBuilding = SD.getStaticConstruction(building)
            if staticBuilding:
                if staticBuilding['classType'] == "StorageBuilding":
                    prLevelFirst, prLevelSecond = SD.getInterpolLevels(staticBuilding['StorageLevels'], building.Level)
                    if prLevelFirst == None or prLevelSecond == None:
                        continue
                    price1 = prLevelFirst['additionalStorage']
                    price2 = prLevelSecond['additionalStorage']
                    coeff = 1.0
                    if prLevelFirst['currentLevel'] != prLevelSecond['currentLevel']:
                        coeff = float(building.Level - prLevelFirst['currentLevel']) / float( prLevelSecond['currentLevel'] - prLevelFirst['currentLevel'])

                    for k, v in newLimits.items():
                        if v > 0:
                            if prLevelFirst['currentLevel'] == prLevelSecond['currentLevel']:
                                newLimits[k] += prLevelFirst['additionalStorage'][k]
                            else:
                                newLimits[k] += SD.roundFloatToInt(price1[k] + (price2[k] - price1[k]) * coeff)

                elif staticBuilding['classType'] == "LibraryBuilding":
                    newUserInventoryLimit += SD.getIntInterpolated(staticBuilding['LibraryLevels'], building.Level, None, "additionalTalentSlots", 0)

                elif staticBuilding['classType'] == "FirstBuyBuilding":
                    prLevelFirst, prLevelSecond = SD.getInterpolLevels(staticBuilding['FirstBuyLevels'], building.Level)
                    if prLevelFirst != None and prLevelSecond != None:
                        if prLevelFirst['currentLevel'] == prLevelSecond['currentLevel']:
                            if newLimits.Resource1 > 0:
                                newLimits.Resource1 += prLevelFirst['additionalStorage']['Resource1']
                            if newLimits.Resource2 > 0:
                                newLimits.Resource2 += prLevelFirst['additionalStorage']['Resource2']
                            if newLimits.Resource3 > 0:
                                newLimits.Resource3 += prLevelFirst['additionalStorage']['Resource3']
                            if newLimits.Resource1_Rare > 0:
                                newLimits.Resource1_Rare += prLevelFirst['additionalStorage']['Resource1_Rare']
                            if newLimits.Resource2_Rare > 0:
                                newLimits.Resource2_Rare += prLevelFirst['additionalStorage']['Resource2_Rare']
                            if newLimits.Resource3_Rare > 0:
                                newLimits.Resource3_Rare += prLevelFirst['additionalStorage']['Resource3_Rare']
                        else:
                            price1 = prLevelFirst['additionalStorage']
                            price2 = prLevelSecond['additionalStorage']
                            coeff = float(building.Level - prLevelFirst['currentLevel']) / float( prLevelSecond['currentLevel'] - prLevelFirst['currentLevel'])
                            if newLimits.Resource1 > 0:
                                newLimits.Resource1 += SD.roundFloatToInt(
                                    price1['Resource1'] + (price2['Resource1'] - price1['Resource1']) * coeff)
                            if newLimits.Resource2 > 0:
                                newLimits.Resource2 += SD.roundFloatToInt( price1['Resource2'] + (price2['Resource2'] - price1['Resource2']) * coeff)
                            if newLimits.Resource3 > 0:
                                newLimits.Resource3 += SD.roundFloatToInt( price1['Resource3'] + (price2['Resource3'] - price1['Resource3']) * coeff)
                            if newLimits.Resource1_Rare > 0:
                                newLimits.Resource1_Rare += SD.roundFloatToInt(price1['Resource1_Rare'] + ( price2['Resource1_Rare'] - price1['Resource1_Rare']) * coeff)
                            if newLimits.Resource2_Rare > 0:
                                newLimits.Resource2_Rare += SD.roundFloatToInt(price1['Resource2_Rare'] + ( price2['Resource2_Rare'] - price1['Resource2_Rare']) * coeff)
                            if newLimits.Resource3_Rare > 0:
                                newLimits.Resource3_Rare += SD.roundFloatToInt(price1['Resource3_Rare'] + ( price2['Resource3_Rare'] - price1['Resource3_Rare']) * coeff)

                    newUserInventoryLimit += SD.getIntInterpolated(staticBuilding['FirstBuyLevels'], building.Level, None, "additionalTalentSlots", 0)

        if self.ResourcesLimit.Perl != newLimits.Perl:
            self.ResourcesLimit.Perl = newLimits.Perl
        if self.ResourcesLimit.RedPerl != newLimits.RedPerl:
            self.ResourcesLimit.RedPerl = newLimits.RedPerl
            # self.Resources.Perl = self.compareResourseToLimit( self.Resources.Perl, self.ResourcesLimit.Perl )
        if self.ResourcesLimit.Silver != newLimits.Silver:
            self.ResourcesLimit.Silver = newLimits.Silver
            # self.Resources.Silver = self.compareResourseToLimit( self.Resources.Silver, self.ResourcesLimit.Silver )
        if self.ResourcesLimit.Population != newLimits.Population:
            self.ResourcesLimit.Population = newLimits.Population
            # self.Resources.Population = self.compareResourseToLimit( self.Resources.Population, self.ResourcesLimit.Population )
        if self.ResourcesLimit.Resource1 != newLimits.Resource1:
            self.ResourcesLimit.Resource1 = newLimits.Resource1
            # self.Resources.Resource1 = self.compareResourseToLimit( self.Resources.Resource1, self.ResourcesLimit.Resource1 )
        if self.ResourcesLimit.Resource2 != newLimits.Resource2:
            self.ResourcesLimit.Resource2 = newLimits.Resource2
            # self.Resources.Resource2 = self.compareResourseToLimit( self.Resources.Resource2, self.ResourcesLimit.Resource2 )
        if self.ResourcesLimit.Resource3 != newLimits.Resource3:
            self.ResourcesLimit.Resource3 = newLimits.Resource3
            # self.Resources.Resource3 = self.compareResourseToLimit( self.Resources.Resource3, self.ResourcesLimit.Resource3 )
        if self.ResourcesLimit.Resource1_Rare != newLimits.Resource1_Rare:
            self.ResourcesLimit.Resource1_Rare = newLimits.Resource1_Rare
            # self.Resources.Resource1_Rare = self.compareResourseToLimit( self.Resources.Resource1_Rare, self.ResourcesLimit.Resource1_Rare )
        if self.ResourcesLimit.Resource2_Rare != newLimits.Resource2_Rare:
            self.ResourcesLimit.Resource2_Rare = newLimits.Resource2_Rare
            # self.Resources.Resource2_Rare = self.compareResourseToLimit( self.Resources.Resource2_Rare, self.ResourcesLimit.Resource2_Rare )
        if self.ResourcesLimit.Resource3_Rare != newLimits.Resource3_Rare:
            self.ResourcesLimit.Resource3_Rare = newLimits.Resource3_Rare
            # self.Resources.Resource3_Rare = self.compareResourseToLimit( self.Resources.Resource3_Rare, self.ResourcesLimit.Resource3_Rare )

        # self.ResourcesLimit = newLimits

        self.UserInventoryLimit = newUserInventoryLimit

        self.recalcPopulation(SD, guest)

    def giveBonusTalent(self, new_social_network_count, new_social_network_names, configdata, acc, I):
        info("giveBonusTalent(%d) -> talent index %d" % (new_social_network_count, new_social_network_count - 1))
        if (new_social_network_count - 1) >= 0 and len(configdata.TALENTIDS_FOR_NEW_SN) > (
                    new_social_network_count - 1):
            talent = self.addTalent(configdata.TALENTIDS_FOR_NEW_SN[new_social_network_count - 1])
            info("giveBonusTalent: added talent_id %s (PersistentId %s)", talent.id, talent.PersistentId)
            data = ""
            if len(new_social_network_names):
                data = "for sn " + new_social_network_names.pop()
            talInfo = TalentInfo(talent.PersistentId, talent.id, 0)
            I.STATS.addTalentChange(acc.db.auid, talInfo, TalentChangeOperation.GetFromSocial, data)

    def CalcPrice(self, cost, amount, SD):
        if cost is None:
            return None

        finalprice = SD.copyPriceFloat(cost)
        SD.applyCoeffToPrice(finalprice, amount)
        return finalprice

    def recalcPopulation(self, SD, guest=False):
        curPopulation = 0
        maxPopulation = (
            SD.data['GuestResourceAndInventoryLimits']['resourceLimits']['Population'] if guest else
            SD.data['ResourceAndInventoryLimits']['resourceLimits']['Population'])
        for buildingId in self.Buildings:
            building = self.getConstructionByID(buildingId)
            staticBuilding = SD.getStaticConstruction(building)
            if staticBuilding:
                price = SD.getBuildingPrice(staticBuilding, building.Level)
                curPopulation += price.Population
                maxPopulation += building.getMaxPopulation(staticBuilding, SD)
        self.Resources.Population = maxPopulation - curPopulation
        self.ResourcesLimit.Population = maxPopulation

    def hasBuilding(self, staticType, SD, fromPocket=False):
        for buildingId in self.Buildings:
            building = self.getConstructionByID(buildingId)
            staticBuilding = SD.getStaticConstruction(building)
            if staticBuilding and staticBuilding['classType'] == staticType:
                return True
        if fromPocket:
            for buildingId in self.Pocket:
                building = self.getConstructionByID(buildingId)
                staticBuilding = SD.getStaticConstruction(building)
                if staticBuilding and staticBuilding['classType'] == staticType:
                    return True
        return False

    def canPlaceBuilding(self, staticConstruction, SD, fromPocket=False, buildingID=0):
        buildingLimits = staticConstruction['GroupBuildingLimits']
        if not buildingLimits or not buildingLimits['Item'] or len(buildingLimits['Item']) == 0:
            return True

        for limit in buildingLimits['Item']:
            count = 0
            for buildingId in self.Buildings:
                building = self.getConstructionByID(buildingId)
                staticBuilding = SD.getStaticConstruction(building)
                if staticBuilding['GroupBuildingLimits'] and staticBuilding['GroupBuildingLimits']['Item'] and len(
                        staticBuilding['GroupBuildingLimits']['Item']) > 0:
                    for newLimit in staticBuilding['GroupBuildingLimits']['Item']:
                        if newLimit['dbid'] == limit['dbid']:
                            if buildingID == 0 or buildingID != buildingId:
                                count += 1
            if limit['CountPocket']:
                for buildingId in self.Pocket:
                    building = self.getConstructionByID(buildingId)
                    staticBuilding = SD.getStaticConstruction(building)
                    if staticBuilding['GroupBuildingLimits'] and staticBuilding['GroupBuildingLimits']['Item'] and len(
                            staticBuilding['GroupBuildingLimits']['Item']) > 0:
                        for newLimit in staticBuilding['GroupBuildingLimits']['Item']:
                            if newLimit['dbid'] == limit['dbid']:
                                if buildingID == 0 or buildingID != buildingId:
                                    count += 1
            if fromPocket and limit['CountPocket']:
                if count > limit['MaxNumberOfBuilding']:
                    return False
            elif count >= limit['MaxNumberOfBuilding']:
                return False

        return True

    def fixAll(self, acc, SD):

        # Выдача утраченных классовых талантов
        diff = Validator.getMissingClassTalents(self, SD, acc.getConfig())
        for tal in diff:
            self.addTalent(tal)

        if len(self.LordInfo.MapsByType) == 0:
            self.createDefaultMaps(SD)

        return None

    def checkValidity(self, acc, SD):
        valid_info = ""
        is_valid = True

        # Проверка на то, что нет утраченных классовых талантов

        diff = Validator.getMissingClassTalents(self, SD, acc.getConfig())
        for tal in diff:
            is_valid = False
            valid_info += "Has not talent " + str(tal) + "\n"
            # Конец проверки на то, что нет утраченных классовых талантов

            ## Проверка на валидность TrainingMap

            # mapName = SD.data['DefaultMaps']['Item'][MapType.Tutorial]['map']['dbid']

            # for questId in self.ActiveQuests:
            # quest = self.getQuestByID(questId)
            # staticQuest = SD.getStaticQuest(quest)
            # if staticQuest['objectives']:
            # for objective in staticQuest['objectives']['Item']:
            # if 'Item' in objective['instant']:
            # for instant in objective['instant']['Item']:
            # if 'classType' in instant and instant['classType'] == "StartSessionAction":
            # if int(instant['genderFractionFilter']) == acc.sex:
            # mapName = instant['map']['dbid']

            # if self.LordInfo.TrainingMapName != mapName and self.LordInfo.TrainingMapName != "":
            # is_valid = False
            # valid_info += "Wrong TrainingMapName '" + self.LordInfo.TrainingMapName + "'. Must be '" + str(mapName) + "'"

        ## Конец проверки на валидность TrainingMap
        if len(self.LordInfo.MapsByType) == 0:
            is_valid = False
            valid_info += "Empty Default Maps"

        return is_valid, valid_info

    def execQuestCondition(self, funcStr, sex, SD, config):
        debug("Condition str: %r", repr(funcStr))
        exec (funcStr)
        scriptData = ScriptData(self, SD, sex, config)
        return Condition(scriptData)

    def arePrerequisiteQuestsCompleted(self, staticQuest, SD):

        if SD.getFameLevel(self.LordInfo.Fame) < int(staticQuest['lordLevelRequirement']):
            return False

        if 'Item' not in staticQuest['prerequisiteQuests']:
            return True

        for stQuest in staticQuest['prerequisiteQuests']['Item']:
            if stQuest and 'persistentId' in stQuest:
                persistentId = crc32(stQuest['persistentId'])
                found = False
                for mdQuest in self.CompletedQuests.keys():
                    quest = self.getQuestByID(mdQuest)
                    # staticQuest = SD.getStaticQuest(quest)
                    if persistentId == quest.persistentId:
                        found = True
                        break
                if not found:
                    return False
        return True

    def removeQuest(self, staticQuest):
        if staticQuest == None:
            return

        staticID = crc32(staticQuest['persistentId'])
        if staticID in self.PendingQuests.keys():
            self.PendingQuests.remove(staticID)

        for questId in self.ActiveQuests.iteritems():
            activeQuest = questId[1]
            if activeQuest.persistentId == staticID:
                self.CompletedQuests.add(activeQuest)
                self.ActiveQuests.remove(activeQuest)
                break

    def addQuest(self, staticQuest, invalidQuests, altenativeQuests, oneTimeQuests, checkPrerequisites, STATS, acc):
        if staticQuest == None:
            return None

        if invalidQuests:
            if staticQuest['persistentId'] in invalidQuests:
                return None

        foundInActive = False
        foundInCompleted = False
        staticID = crc32(staticQuest['persistentId'])

        for questId in self.ActiveQuests.iteritems():
            activeQuest = questId[1]
            if activeQuest.persistentId == staticID:
                foundInActive = True
                break

        for questId in self.CompletedQuests.iteritems():
            completedQuest = questId[1]
            if completedQuest.persistentId == staticID:
                foundInCompleted = True
                break

        if foundInActive or (staticQuest['oneTime'] and foundInCompleted and oneTimeQuests):
            if staticID in self.PendingQuests.keys():
                self.PendingQuests.remove(staticID)
            return

        if checkPrerequisites and not self.arePrerequisiteQuestsCompleted(staticQuest, acc.SD):
            if not staticID in self.PendingQuests.keys():
                self.PendingQuests.append(staticID)
            return None

        # Вспомним, что у американцев может быть другой туториал
        if acc.country_code == 'US' and altenativeQuests is not None:
            if staticQuest['persistentId'] in altenativeQuests and self.LordInfo.TurtorialVersion == 1:
                alternativeQuestsSet = json.loads(altenativeQuests[staticQuest['persistentId']])
                for questId in alternativeQuestsSet:
                    alternativeStaticQuest = acc.SD.getStaticQuestById(crc32(questId))
                    self.addQuest(alternativeStaticQuest, invalidQuests, altenativeQuests, oneTimeQuests,
                                  checkPrerequisites, STATS, acc)
                return

        quest_id = self.addNewQuest()
        quest = self.getQuestByID(quest_id)
        quest.state = QuestState.New
        quest.dialogPage = 0
        quest.persistentId = staticID
        quest.isVisible = staticQuest['isVisible']
        # Скрытые квесты всегда принимаем сразу
        if not quest.isVisible:
            quest.state = QuestState.InProgress

        STATS.addQuestChange(acc.auid, quest.persistentId, 0)
        if 'objectives' in staticQuest and 'Item' in staticQuest['objectives']:
            for i in xrange(0, len(staticQuest['objectives']['Item'])):
                objective_id = self.addNewObjective()
                objective = self.getObjectiveByID(objective_id)
                objective.index = i
                objective.lastEventId = self.StatisticEventId
                quest.objectives.add(objective)
        self.ActiveQuests.add(quest_id)
        if staticID in self.PendingQuests.keys():
            self.PendingQuests.remove(staticID)

        return quest

    def addStatisticEvent(self, actionType, description, value, valueChange=0):
        debug(" addStatisticEvent: type=%r, desc=%s, value=%r, vchange=%r", actionType, description, value, valueChange)
        event_id = self.addNewStatisticEvent()
        event = self.getStatisticEventByID(event_id)
        event.time = self.StatisticEventId
        self.StatisticEventId += 1
        event.actionType = actionType
        event.description = description
        event.value = value
        event.valueChange = valueChange
        self.StatisticEvents.add(event)
        self.checkStatisticsDynamicQuests(event)
        return event

    # дополнительные (server-side) сериализуемые поля
    def generateBaseDict(self):
        return dict(
            next_uid_=self.next_uid_
        )

    def checkActionFilter(self, action, gender, fraction):
        if 'genderFractionFilter' not in action:
            return False
        if int(action['genderFractionFilter']) == 0:
            return True
        if int(action['genderFractionFilter']) & 2 != 0 and (
            int(action['genderFractionFilter']) & 1) == 0 and gender != ESex.FEMALE:
            return False
        if int(action['genderFractionFilter']) & 1 != 0 and (
            int(action['genderFractionFilter']) & 2) == 0 and gender == ESex.FEMALE:
            return False
        if int(action['genderFractionFilter']) & 4 != 0 and (
            int(action['genderFractionFilter']) & 8) == 0 and fraction != 'A':
            return False
        if int(action['genderFractionFilter']) & 8 != 0 and (
            int(action['genderFractionFilter']) & 4) == 0 and fraction != 'B':
            return False
        return True

    def applyActions(self, actions, SD, gender, fraction, WS, acc, config, STATS, bill, randVal, I):
        if 'Item' in actions:
            for action in actions['Item']:
                if not self.checkActionFilter(action, gender, fraction):
                    continue

                if action['classType'] == "ChangeMapAction":
                    self.ChangeMapAction(action, SD)
                elif action['classType'] == "ChangeGroupMapAction":
                    self.ChangeMapAction(action, SD, True)
                elif action['classType'] == "RemoveQuestAction":
                    self.removeQuest(action['quest'])
                elif action['classType'] == "NextQuestAction":
                    self.addQuest(action['quest'], config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS,
                                  config.ONE_TIME_QUESTS, True, STATS, acc)
                elif action['classType'] == "GiveHeroExpAction":
                    for heroId in self.Heroes:
                        hero = self.getHeroByID(heroId)
                        if hero.class_name == action['hero']['persistentId']:
                            hero.changeExperience(int(action['exp']), self, WS, acc, I)
                elif action['classType'] == "GiveRewardAction":
                    if acc.db.sex == ESex.FEMALE:
                        defaultHero = action['defaultTalentsSoulboundFemale']
                    else:
                        defaultHero = action['defaultTalentsSoulboundMale']
                    self.getSimpleReward(action['fame'], action['resources'], action['talents'], defaultHero,
                                         action['heroes'], action['heroesForRandomPick'], action['constructions'],
                                         action['daysForPremiumAcc'], SD, gender, fraction, WS, acc, bill, randVal,
                                         STATS, I)
                    randVal = self.getRandom(randVal)
                elif action['classType'] == "RemoveTalentsIsNewStateAction":
                    self.removeTalentsNewState()
                elif action['classType'] == "MoveTalentFromHeroToLibraryAction":
                    self.removeTalentFromTS(action['hero'], action['talent'], toint(action['slot']), 0)
                elif action['classType'] == "ChangeTutorialStateAction":
                    if not acc.model.isTutorialComplete():
                        debug("applyActions: Change tutorial state %s -> %s",
                            enum2String(TutorialState, self.LordInfo.TutorialState),
                            enum2String(TutorialState, TutorialState))
                        self.LordInfo.TutorialState = getattr(TutorialState, action['state'])
                        STATS.addTutorialStateChange(acc.auid, enum2String(TutorialState, self.LordInfo.TutorialState))
                    if getattr(acc, "isTutorialAccount", False):
                        del acc["isTutorialAccount"]
                elif action['classType'] == "GiveGoldenLampAction":
                    eventInfo = self.MarketingEventsInfo.LampEventInfo
                    eventInfo.dbId = action['lampEventInfo']['dbid']
                    eventInfo.BonusLeft = int(action['bonus'])
                    eventInfo.StartTime = int(round(time.time()))
                    eventInfo.EndTime = eventInfo.StartTime + int(action['duration'])
                    eventInfo.TransactionsLeft = int(action['unsoulbounds'])
                    rune = self.getGoldLampType(acc.SD)
                    STATS.addLampRoll(acc.db.auid, rune, RuneRollSource.Quest)
                elif action['classType'] == "SetLastRankedGameTimeAction":
                    self.LordInfo.LastRankedGameTime = int(time.time())
                elif action['classType'] == 'GiveUpgradeHeroTalentsEventAction':
                    old_value = self.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft
                    self.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft += int(action['count'])
                    STATS.addLampRoll(acc.db.auid, self.getUpgHeroLampType(), RuneRollSource.Quest,
                                      runescountold=old_value,
                                      runescountnew=acc.model.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft)


    def getSimpleReward(self, fame, resources, talents, defaultTalentsSoulbound, heroes, heroesForRandomPick,
                        constructions, daysForPremiumAcc, SD, sex, fraction, WS, acc, bill, randVal, STATS, I):
        self.addFame(int(fame), acc, SD, STATS)
        self.sell(SD.copyPrice(resources), acc, False)
        # TODO: писать статистику по ресурсам за статические квесты
        if int(resources['Gold']) > 0:
            bill.replenish(acc.db.auid, int(resources['Gold']), "QuestAward", None)
        self.addPremiumAccount(int(daysForPremiumAcc) * 24 * 60 * 60, acc)

        if 'Item' in talents:
            soulboundHero = IGuidGenerator.InvalidUID
            if 'persistentId' in defaultTalentsSoulbound:
                for hero_id in self.Heroes:
                    hero = self.getHeroByID(hero_id)
                    if hero.PersistentId == crc32(defaultTalentsSoulbound['persistentId']):
                        soulboundHero = hero
            for staticTalent in talents['Item']:
                if staticTalent:
                    talent = self.addTalent(crc32(staticTalent['persistentId']))
                    if talent.canBeSoulbound(SD):
                        talent.Soulbound = soulboundHero
                    talInfo = TalentInfo(talent.PersistentId, talent.getID(), 0)
                    STATS.addTalentChange(acc.db.auid, talInfo, TalentChangeOperation.GetFromQuest)

        if 'Item' in heroes:
            for staticHero in heroes['Item']:
                heroFound = False
                for heroId in self.Heroes:
                    hero = self.getHeroByID(heroId)
                    if crc32(staticHero['persistentId']) == hero.PersistentId:
                        heroFound = True
                        break
                if not heroFound:
                    self.hireHero(crc32(staticHero['persistentId']), sex, WS, acc, I)

        if 'Item' in heroesForRandomPick and len(heroesForRandomPick['Item']) > 0:
            heroesForRoll = []
            for staticHero in heroesForRandomPick['Item']:
                heroFound = False
                for heroId in self.Heroes:
                    hero = self.getHeroByID(heroId)
                    if crc32(staticHero['persistentId']) == hero.PersistentId:
                        heroFound = True
                        break
                if not heroFound:
                    heroesForRoll.append(staticHero['persistentId'])
            if len(heroesForRoll) > 0:
                valForHero = SD.getValueInRange(randVal, 0, len(heroesForRoll) - 1)
                self.hireHero(crc32(heroesForRoll[valForHero]), sex, WS, acc, I)

        if 'Item' in constructions:
            for rewardConstruction in constructions['Item']:
                if 'construction' in rewardConstruction:
                    staticConstruction = rewardConstruction['construction']
                    if staticConstruction:
                        construction_id = self.addNewConstruction()
                        construction = self.getConstructionByID(construction_id)
                        construction.PersistentId = crc32(staticConstruction['persistentId'])
                        if int(rewardConstruction['level']) < len(staticConstruction['Levels']['Item']):
                            construction.Level = int(rewardConstruction['level'])
                        self.Pocket.add(construction_id)

    def ChangeMapAction(self, action, SD, isGroup=False, isVisible=True):
        if isGroup:
            fieldName = 'group'
        else:
            fieldName = 'map'
        intMapType = getattr(MapType, action['type'])
        if 'dbid' in action[fieldName] and action[fieldName]['dbid'] != None:
            self.updateMap(intMapType, action[fieldName]['dbid'], True, 0, 0, action['isVisible'])
        else:
            self.updateMap(intMapType, "", True, 0, 0, action['isVisible'])

    def updateMap(self, mapType, mapID, isEnabled, start, stop, isVisible):
        mapInfo = self.LordInfo.MapsByType.get(mapType)
        if mapInfo:
            if mapType != MapType.Tutorial:
                mapInfo.MapId = mapID
            mapInfo.Enabled = isEnabled

            if mapInfo.MapId in ETERNAL_MAPS:
                mapInfo.StartTime = 0
                mapInfo.EndTime = 0
            else:
                mapInfo.StartTime = start
                mapInfo.EndTime = stop
            mapInfo.Visible = isVisible

    def addProductionFinishEvent(self, persistentId, finalprice):   #FEATURENEWRES: maybe add Shard to this def
        if finalprice.Resource1 > 0:
            self.addStatisticEvent(StatisticEventType.PRODUCTION_FINISH, persistentId + ",Resource1",
                                   finalprice.Resource1)
        if finalprice.Resource2 > 0:
            self.addStatisticEvent(StatisticEventType.PRODUCTION_FINISH, persistentId + ",Resource2",
                                   finalprice.Resource2)
        if finalprice.Resource3 > 0:
            self.addStatisticEvent(StatisticEventType.PRODUCTION_FINISH, persistentId + ",Resource3",
                                   finalprice.Resource3)
        if finalprice.Silver > 0:
            self.addStatisticEvent(StatisticEventType.PRODUCTION_FINISH, persistentId + ",Silver", finalprice.Silver)
        if finalprice.Perl > 0:
            self.addStatisticEvent(StatisticEventType.PRODUCTION_FINISH, persistentId + ",Perl", finalprice.Perl)

    def GiveStartQuest(self, startQuest, acc, iDict):
        if iDict.Config.getConfig(acc.userlocale).ADD_FIRST_QUEST:
            if 'persistentId' in startQuest:
                staticQuest = acc.SD.getStaticQuestById(crc32(str(startQuest['persistentId'])))
                if staticQuest:
                    config = iDict.Config.getConfig(acc.userlocale)
                    quest = self.addQuest(staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS,
                                          config.ONE_TIME_QUESTS, True, iDict.STATS, acc)
                    if quest:
                        if quest.isComplete(self, acc.SD):
                            quest.state = QuestState.Complete
                            iDict.STATS.addQuestChange(acc.auid, quest.persistentId, 2)
                            quest.completeQuest(None, staticQuest, 0, acc, iDict,
                                                self.getRandom(self.LordInfo.RandomSeed))
                            self.LordInfo.TutorialState = TutorialState.BattleQuestAdded
                            iDict.STATS.addTutorialStateChange(acc.auid,
                                                               enum2String(TutorialState, self.LordInfo.TutorialState))
                            self.CompletedQuests.add(quest)
                            self.ActiveQuests.remove(quest)

    def IsPremiumAccount(self):
        return self.LordInfo.PremiumAccountEnd > time.time()

    def addPremiumAccount(self, duration, acc):
        if duration:
            if self.IsPremiumAccount():
                self.LordInfo.PremiumAccountEnd += duration
            else:
                # fix all production buildings
                if acc:
                    for constructionId, construction in self.ConstructionsKeeper.iteritems():
                        staticConstruction = acc.SD.getStaticConstruction(construction)
                        if staticConstruction and staticConstruction['classType'] == 'ProductionBuilding':
                            construction.storeTimeBasedProduction(staticConstruction, "ProductionLevels", acc.getConfig(), acc.SD, self)
                self.LordInfo.PremiumAccountStart = int(round(time.time()))
                self.LordInfo.PremiumAccountEnd = self.LordInfo.PremiumAccountStart + duration

    def restoreFields(self, old_md):
        if old_md:
            self.LordInfo.PremiumAccountStart = old_md.LordInfo.PremiumAccountStart
            self.LordInfo.PremiumAccountEnd = old_md.LordInfo.PremiumAccountEnd
            self.version.events = old_md.version.events
            self.version.revision = old_md.version.revision
            self.version.patch = old_md.version.patch
            self.TournamentInfo.TournamentState = old_md.TournamentInfo.TournamentState
            self.LordInfo.LastLogoutTime = old_md.LordInfo.LastLogoutTime
            self.LordInfo.TurtorialVersion = old_md.LordInfo.TurtorialVersion

    def updateLoginTime(self):
        self.LordInfo.LastLoginTime = self.LordInfo.CurrentLoginTime
        self.LordInfo.CurrentLoginTime = int(round(time.time()))

    def setLastPvPTime(self):
        self.LordInfo.LastRankedGameTime = int(round(time.time()))

    def IsFirstDayLogin(self):
        curDate = datetime.datetime.fromtimestamp(self.LordInfo.CurrentLoginTime).date()
        lastDate = datetime.datetime.fromtimestamp(self.LordInfo.LastLoginTime).date()
        if curDate == lastDate:
            return False
        return True

    def isTutorialComplete(self):
        return self.LordInfo.TutorialState in [TutorialState.Skipped, TutorialState.Completed,  TutorialState.ClientReturnedFromSession, TutorialState.RewardsReceived]

    def getBonusFromBuilding(self, stat, SD):
        result = 0.0
        for buildingId in self.Buildings:
            building = self.getConstructionByID(buildingId)
            staticBuilding = SD.getStaticConstruction(building)
            if staticBuilding:
                if staticBuilding['classType'] == "HeroesBuilding" and stat in staticBuilding['buffStats']['Item']:
                    result += SD.getFloatInterpolated(staticBuilding['HeroesBuildingLevels'], building.Level, None,
                                                      "statBufValue", 0) * SD.getStatPointsMultiplyer(stat)
        return result

    def getHeroDiscountFromBuilding(self, hero, SD):
        discount = 0.0
        fameReq = 0
        for buildingId in self.Buildings:
            building = self.getConstructionByID(buildingId)
            staticBuilding = SD.getStaticConstruction(building)
            if staticBuilding:
                if staticBuilding['classType'] == "HeroesBuilding" and hero['lobbyData']['Classes'] == staticBuilding['heroClass']:
                    discount += SD.getFloatInterpolated(staticBuilding['HeroesBuildingLevels'], building.Level, None,
                                                        "discount", 0)
                    fameReq += SD.getIntInterpolated(staticBuilding['HeroesBuildingLevels'], building.Level, None,
                                                     "fameReqDecr", 0)
        return discount, fameReq

    def getStatPointsFromBuilding(self, SD):
        result = 0.0
        for buildingId in self.Buildings:
            building = self.getConstructionByID(buildingId)
            staticBuilding = SD.getStaticConstruction(building)
            if staticBuilding:
                if staticBuilding['classType'] == "HeroesBuilding":
                    result += SD.getFloatInterpolated(staticBuilding['HeroesBuildingLevels'], building.Level, None,
                                                      "statBufValue", 0) * len(staticBuilding['buffStats']['Item'])
        return result

    def updateHeroesForce(self, WS, acc):
        for heroId in sorted(self.Heroes):
            hero = self.getHeroByID(heroId)
            for tsId in hero.TalentSets.keys():
                hero.CalcForce(self, WS, acc, tsId)

    def getConsumablesForSession(self, SD):
        consumables = []
        for buildingId in self.Buildings:
            building = self.getConstructionByID(buildingId)
            staticBuilding = SD.getStaticConstruction(building)
            if staticBuilding:
                if staticBuilding['classType'] == "FirstBuyBuilding":
                    if 'petItem' in staticBuilding and 'persistentId' in staticBuilding['petItem'] and len(
                            staticBuilding['petItem']['persistentId']) > 0:
                        consumables.append(crc32(staticBuilding['petItem']['persistentId']))
        return consumables

    def getHeroForSkin(self, static_skin, SD):
        for heroId in self.Heroes:
            hero = self.getHeroByID(heroId)
            if hero and hero.Hired:
                static_hero = SD.getStaticHero(hero)
                if static_hero and static_hero['heroSkins'] and static_hero['heroSkins']['Item'] and len(
                        static_hero['heroSkins']['Item']) > 0:
                    for sk in static_hero['heroSkins']['Item']:
                        if sk['persistentId'] == static_skin['persistentId']:
                            return hero
        return None

    def getHeroClassIdForSkin(self, static_skin, SD):
        for heroClassId in SD.data['Heroes'].keys():
            static_hero = SD.getStaticHeroByClassId(heroClassId)
            if static_hero and static_hero['heroSkins'] and static_hero['heroSkins']['Item'] and len(
                    static_hero['heroSkins']['Item']) > 0:
                for sk in static_hero['heroSkins']['Item']:
                    if sk['persistentId'] == static_skin['persistentId']:
                        return heroClassId

    def isSkinOwned(self, persistentId, SD):
        static_skin = SD.getStaticSkinByPersistentId(persistentId)
        if static_skin:
            for skinId in self.SkinsKeeper:
                skin = self.getSkinByID(skinId)
                if skin.PersistentId == persistentId:
                    return True
        return False

    def isValidSkinByData(self, persistentId, acc):
        static_skin = acc.SD.getStaticSkinByPersistentId(persistentId)
        if not static_skin['legal'] or (static_skin['persistentId'] in acc.getConfig().INVALID_SKINS and static_skin['persistentId'] not in acc.getConfig().SEASON_SKINS):
            return False

        if acc.db.fraction not in acc.SD.getFractions(static_skin['heroRace']):
            return False

        return True

    def isValidSkin(self, persistentId, acc, ignore_hero=False):
        static_skin = acc.SD.getStaticSkinByPersistentId(persistentId)
        if static_skin:
            if self.isSkinOwned(persistentId, acc.SD):
                return False, "Skin is already presented in MD"
        else:
            return False, "No static skin found for " + str(persistentId)

        if not static_skin['legal'] or (static_skin['persistentId'] in acc.getConfig().INVALID_SKINS and static_skin['persistentId'] not in acc.getConfig().SEASON_SKINS):
            return False, "Skin " + str(persistentId) + " is not legal"

        if acc.db.fraction not in acc.SD.getFractions(static_skin['heroRace']):
            return False, "Skin " + str(persistentId) + " has wrong fraction"

        if crc32(static_skin['persistentId']) in self.EventSkins and crc32(
                static_skin['persistentId']) not in self.ActiveEventSkins:
            return False, "Skin " + str(persistentId) + " is event skin and event disabled now"

        if not ignore_hero:
            hero = self.getHeroForSkin(static_skin, acc.SD)
            if not hero:
                return False, "No hero for skin " + str(persistentId)

        return True, ""

    def giveSkinForFree(self, skinID, acc, wasBought=False, withoutCheck=False):
        validSkin, reason = self.isValidSkin(skinID, acc)
        config = acc.getConfig()
        if validSkin or withoutCheck:
            static_skin = acc.SD.getStaticSkinByPersistentId(skinID)
            hero = self.getHeroForSkin(static_skin, acc.SD)
            if hero:
                self.addSkinForHero(skinID, hero, wasBought=wasBought, IsAnimatedAvatar=static_skin['persistentId'] not in config.SKIN_AVATAR_BLOCK)
                return True, reason
        return False, reason

    def giveFreeSkinsForHero(self, hero, static_hero, acc):
        config = acc.getConfig()
        if static_hero and static_hero['heroSkins'] and static_hero['heroSkins']['Item'] and len(
                static_hero['heroSkins']['Item']) > 0:
            for sk in static_hero['heroSkins']['Item']:
                skinID = crc32(sk['persistentId'])
                isDefault = sk['persistentId'] in config.DEFAULT_SKINS
                # скин валидный и эвентовый
                if (isDefault or skinID in self.ActiveEventSkins) and sk['legal'] and (sk[
                    'persistentId'] not in config.INVALID_SKINS and sk['persistentId'] not in config.SEASON_SKINS) and acc.db.fraction in acc.SD.getFractions(
                        sk['heroRace']):
                    # скин бесплатный или дефолтовый
                    if isDefault or self.isSkinFree(skinID, acc):
                        self.addSkinForHero(skinID, hero, isDefault=isDefault, IsAnimatedAvatar=sk['persistentId'] not in config.SKIN_AVATAR_BLOCK)


    def addSkinForHero(self, skinID, hero, isDefault=False, wasBought=False, IsAnimatedAvatar=True):
        skin_id = self.addNewSkin()
        skin = self.getSkinByID(skin_id)
        skin.PersistentId = skinID
        skin.WasBought = wasBought
        skin.IsAnimatedAvatar = IsAnimatedAvatar
        hero.HeroSkins.Skins.add(skin_id)
        if isDefault:
            hero.HeroSkins.CurrentSkin = skin
            hero.IsAnimatedAvatar = IsAnimatedAvatar
        return skin

    def isSkinFree(self, skinID, acc):
        static_skin = acc.SD.getStaticSkinByPersistentId(skinID)
        if static_skin:
            gold = static_skin['cost']
            config = acc.getConfig()
            if static_skin['persistentId'] in config.EventToolsChangeFields.SKIN_GOLD_PRICES:
                gold = config.EventToolsChangeFields.SKIN_GOLD_PRICES[static_skin['persistentId']]
            return gold == 0
        return False

    def validateDefaultSkins(self, acc):
        config = acc.getConfig()
        for defSk in config.DEFAULT_SKINS:
            addedSkin, reason = self.giveSkinForFree(crc32(defSk), acc)

    def getInternalUserStatus(self, configdata):
        if self.LordInfo.GuardInfo.LeavesPoint >= configdata.LEAVES_POINT:
            self.LordInfo.GuardInfo.isLeaver = True
            return LordStatus.Leaver

        if self.LordInfo.GuardInfo.isLeaver and self.LordInfo.GuardInfo.LeavesPoint <= configdata.MIN_LEAVES_POINT:
            self.LordInfo.GuardInfo.isLeaver = False

        if self.LordInfo.GuardInfo.isLeaver:
            return LordStatus.Leaver

        if self.LordInfo.GuardInfo.NumberOfWins < configdata.NEWBIE_WINS:
            return LordStatus.Newbie

        if self.LordInfo.GuardInfo.RetiredTime > int(time.time()):
            return LordStatus.Retired

        return LordStatus.Normal

    def getLordStatus(self, hero, configdata):
        heroStatus = hero.getHeroStatus(configdata)
        userStatus = self.getInternalUserStatus(configdata)
        info("getLordStatus: hero %s, heroStatus %s, userStatus %s", hero.class_name, heroStatus, userStatus)

        if heroStatus == HeroStatus.Normal and userStatus == LordStatus.Leaver:
            return MM.ELordStatus.LEAVER

        if heroStatus == HeroStatus.Normal and userStatus == LordStatus.Normal:
            return MM.ELordStatus.NORMAL

        if heroStatus == HeroStatus.Normal and userStatus == LordStatus.Retired:
            return MM.ELordStatus.NORMAL

        if heroStatus == HeroStatus.Normal and userStatus == LordStatus.Newbie:
            return MM.ELordStatus.NEWBIE

        return MM.ELordStatus.NORMAL

    def addLose(self, hero, map, configdata):
        if hero:
            if hero.TalentSets[hero.ActiveTalentSet].Force * 10.0 > configdata.EPIC_HERO_FORCE:
                hero.Master = True

        if map and (map['mapType'] in ("PvP",))  and map["dbid"] in configdata.MAPS_FOR_PLAYER_RATING:
            self.changePlayerRating(configdata, hero, -1)

    def breakEpicWinsStrike(self, hero):
        if hero:
            hero.EpicWins = 0

    def addWin(self, hero, map, configdata):
        if map:
            self.LordInfo.GuardInfo.NumberOfWins += float(map['victoryPoint'])
        if hero:
            if hero.TalentSets[hero.ActiveTalentSet].Force * 10.0 > configdata.EPIC_HERO_FORCE:
                hero.EpicWins += 1
                hero.Master = True
        if map and (map['mapType'] in ("PvP",)) and map["dbid"] in configdata.MAPS_FOR_PLAYER_RATING:
            NumberOfWinsForPR = self.LordInfo.Ratings.get("NumberOfWinsForPR")
            self.LordInfo.Ratings.NumberOfWinsForPR = (NumberOfWinsForPR if NumberOfWinsForPR else 0) + 1
            self.changePlayerRating(configdata, hero)

    def addLeave(self, configdata, badBehaviourReported=False):
        self.LordInfo.GuardInfo.LeavesPoint += configdata.ADD_LEAVE_POINT if not badBehaviourReported else configdata.POINTS_PER_BAD_BEHAIVIOR_REPORTS
        self.LordInfo.GuardInfo.LeavesPoint = min(configdata.MAX_LEAVES_POINT, self.LordInfo.GuardInfo.LeavesPoint)
        self.getInternalUserStatus(configdata)

    def subLeave(self, configdata):
        self.LordInfo.GuardInfo.LeavesPoint -= configdata.SUB_LEAVE_POINT
        self.LordInfo.GuardInfo.LeavesPoint = max(0, self.LordInfo.GuardInfo.LeavesPoint)
        self.getInternalUserStatus(configdata)

    def setLeaves(self, val, configdata):
        self.LordInfo.GuardInfo.LeavesPoint = val
        self.LordInfo.GuardInfo.LeavesPoint = min(configdata.MAX_LEAVES_POINT, self.LordInfo.GuardInfo.LeavesPoint)
        self.LordInfo.GuardInfo.LeavesPoint = max(0, self.LordInfo.GuardInfo.LeavesPoint)
        self.getInternalUserStatus(configdata)

    def checkForAutoMuteSystem(self, acc, iDict, extra):
        _cfg = acc.getConfig()
        if _cfg.BEHAVIOUR_DETECTED_ENABLE:
            badBehaviourReported = extra.get('badBehaviourReported', False)
            badBehaviourDetected = extra.get('badBehaviourDetected', DetectedBadBehaviour.NONE)
            if badBehaviourReported and badBehaviourDetected == DetectedBadBehaviour.TOXICPLAYER:
                subParams = ClassDict(minutes=[_cfg.AUTOMUTE_DURATION], reason=["AutoMuteSystem Mute"], rid=[1])
                accountAction = Mute_account(subParams, partial(self.callbackFn, acc), I=iDict, acc=acc, uid=acc.uid)
                accountAction.onStart()
                iDict.PS.mute(acc.auid, 1)
                if acc.chat:
                    iDict.CHAT.muteUser(acc.chat['host'], acc.auid, 1, acc.db.mutetime, None)
                else:
                    warn("checkForAutoMuteSystem: no acc.chat for auid=%s", acc.auid)

                return True

        return False

    def callbackFn(self, acc, response ):
        if acc:
            SubAction._postponeResponseChanges(response, acc) # переносим накопленные response model changes в acc.pending_changes
        if not response.get("ok"):
            err("callbackFn Callback failed: response %s", response)

    def changeLeaverStatus(self, acc, game_type, playerLeaver,  extra, iDict, isGM=False, gm_points=0):

        leaverPointsChange = self.LordInfo.GuardInfo.LeavesPoint
        leaverStatusBefore = self.LordInfo.GuardInfo.isLeaver
        leaverPointReason = enum2String(LeavePointReason, LeavePointReason.NONE)
        _cfg = acc.getConfig()
        if self.checkForAutoMuteSystem(acc, iDict, extra):
            return "", 0

        if isGM:
            leaverPointReason = enum2String(LeavePointReason, LeavePointReason.BADBEHAVIOUR_GM)
            self.setLeaves(self.LordInfo.GuardInfo.LeavesPoint + gm_points, _cfg)
            self.LordInfo.GuardInfo.isBadBehaviour = False
            self.LordInfo.GuardInfo.badBehaviourReason = DetectedBadBehaviour.NONE
        else:
            if not playerLeaver:
                if not self.addBehaviourPoints(extra, game_type, acc, leaverPointReason):
                    if self.isMinusPointsPerFullGame(game_type, acc):
                        self.subLeave(_cfg)
            else:
                if not self.addBehaviourPoints(extra, game_type, acc, leaverPointReason):
                    if self.isPlusPointForLeave(game_type, acc):
                        self.addLeave(_cfg)
                    leaverPointReason = enum2String(LeavePointReason, LeavePointReason.LEAVER)

        leaverPointsChange = self.LordInfo.GuardInfo.LeavesPoint - leaverPointsChange
        return leaverPointReason, leaverPointsChange

    def addBehaviourPoints(self, extra, game_type, acc, leaverPointReason):
        _cfg = acc.getConfig()
        res = False
        if _cfg.BEHAVIOUR_DETECTED_ENABLE:
            badBehaviourReported = extra.get('badBehaviourReported', False)
            badBehaviourDetected = extra.get('badBehaviourDetected', DetectedBadBehaviour.NONE)

            if badBehaviourReported and badBehaviourDetected != DetectedBadBehaviour.NONE and ( self.isPlusPointForLeave(game_type, acc)):
                self.addLeave(_cfg, badBehaviourReported)
                leaverPointReason = enum2String(DetectedBadBehaviour, badBehaviourDetected)
                res = True

            self.LordInfo.GuardInfo.isBadBehaviour = badBehaviourReported
            self.LordInfo.GuardInfo.badBehaviourReason = badBehaviourDetected
        return res

    def changeRating(self, value):
        if (self.LordInfo.Ratings.LordRating + value) <= 0:
            self.LordInfo.Ratings.LordRating = 0.0
        else:
            self.LordInfo.Ratings.LordRating += value

    def changePlayerRating(self, configdata, winhero, isWin=1):
        playerRating = self.getPlayerRating()
        debug("changePlayerRating before playerRating=%r winhero=%r heroRating=%r dayPlayerRating=%r isWin=%r", playerRating,
              winhero.class_name if winhero else "unknown",
              winhero.Rating if winhero else 0, self.LordInfo.Ratings.PlayerRatings[0], isWin )
        debug("changePlayerRating %r > %r", self.LordInfo.Ratings.NumberOfWinsForPR, configdata.NEWBIE_WINS)
        if self.LordInfo.Ratings.NumberOfWinsForPR > configdata.NEWBIE_WINS and isWin == 1:

            if winhero and (winhero.Rating > self.LordInfo.Ratings.PlayerRatings[0]):
                self.LordInfo.Ratings.PlayerRatings[0] = winhero.Rating
        elif self.LordInfo.Ratings.NumberOfWinsForPR <= configdata.NEWBIE_WINS:
            res = 0
            currPRating = playerRating
            if self.Statistics.PRSessionsStarted != 0:
                NumberOfWinsForPR = self.LordInfo.Ratings.get("NumberOfWinsForPR")
                res = (NumberOfWinsForPR if NumberOfWinsForPR else 0)/float(self.Statistics.PRSessionsStarted)
            if playerRating == 0:
                currPRating = winhero.Rating
            self.LordInfo.Ratings.PlayerRatings[0] = currPRating + 50 * res * isWin

        if self.LordInfo.Ratings.PlayerRatings[0] >= playerRating:
            self.LordInfo.Ratings.MaxPRHeroLastPlayed = winhero.lastPlayed
            self.LordInfo.Ratings.MaxPRHero = winhero.PersistentId

        debug("changePlayerRating after playerRating=%r winhero=%r heroRating=%r dayPlayerRating=%r", playerRating,
              winhero.class_name if winhero else "unknown",
              winhero.Rating if winhero else 0, self.LordInfo.Ratings.PlayerRatings[0] )

    def calcDayDifference(self, configdata):
        diff = int(time.time()) - self.LordInfo.Ratings.LastRecalcPlayerRatingTime
        days = diff /(24 * 60* 60)
        if days > 0:
            for _ in xrange(days):
                self.recalcPlayerRating(configdata)

    def recalcPlayerRating(self, configdata):
        for idx in xrange(configdata.PLAYER_RATING_PERIOD - 2, -1, -1):
            self.LordInfo.Ratings.PlayerRatings[idx + 1] = self.LordInfo.Ratings.PlayerRatings[idx]
        self.LordInfo.Ratings.PlayerRatings[0] = 0
        self.LordInfo.Ratings.LastRecalcPlayerRatingTime = int(time.time())

    def setPlayerRating(self, rating, configdata):
        for i in xrange(configdata.PLAYER_RATING_PERIOD):
            self.LordInfo.Ratings.PlayerRatings[i] = rating

    def setSeasonShowedToUser(self, seasonId, isShowed):
        debug("setSeasonShowedToUser: seasonID = %s, isShowed = %s"%(str(seasonId), str(isShowed)))
        for sa_id, season_awards_info in self.SeasonAwardsKeeper.iteritems():
            debug("setSeasonShowedToUser: season_awards_info.SeasonId = %s"%(str(season_awards_info.SeasonId)))
            if season_awards_info.SeasonId == seasonId:
                season_awards_info.IsShowedToUser = isShowed
                break

    def getHeroWithMaxRating(self):
        if self.HeroesKeeper:
            return max([self.HeroesKeeper.itervalues()], key=lambda h: h.Rating)

    def getPlayerRating(self):
        return max(self.LordInfo.Ratings.PlayerRatings) if self.LordInfo.Ratings.PlayerRatings else 0

    def getRating(self):
        return self.LordInfo.Ratings.LordRating

    def changePublicRating(self, value):
        if value:
            if (self.LordInfo.Ratings.LordPublicRating + value) <= 0:
                self.LordInfo.Ratings.LordPublicRating = 0.0
            else:
                self.LordInfo.Ratings.LordPublicRating += value

    def getPublicRating(self):
        return self.LordInfo.Ratings.LordPublicRating

    def getNumberOfWins(self):
        return self.LordInfo.GuardInfo.NumberOfWins

    def getLeavesPoint(self):
        return self.LordInfo.GuardInfo.LeavesPoint

    def addDodge(self, WS, acc):
        self.LordInfo.lastDodgesUpdateTime_ = time.time()
        self.LordInfo.GuardInfo.Dodges += 1
        leaveCoeff = self.LordInfo.GuardInfo.Dodges - 1
        timeToRetired = acc.getConfig().EPIC_HERO_RETIRED_TIME_BASE * pow(acc.getConfig().EPIC_HERO_RETIRED_TIME_INC,
                                                                          leaveCoeff)
        if timeToRetired > acc.getConfig().EPIC_HERO_RETIRED_CAP:
            timeToRetired = acc.getConfig().EPIC_HERO_RETIRED_CAP
        self.LordInfo.GuardInfo.RetiredTime = int(round(time.time())) + timeToRetired
        WS.updatePartyDodge(acc)

    def addDodges(self, dodges, WS, acc):
        if dodges > 0:
            for i in xrange(0, dodges):
                self.addDodge(WS, acc)

    def clearDodges(self):
        self.LordInfo.GuardInfo.Dodges = 0
        self.LordInfo.GuardInfo.RetiredTime = 0
        self.LordInfo.lastDodgesUpdateTime_ = time.time()

    def updateDodgesStatus(self, acc):
        # check that dodges exist
        if (self.LordInfo.GuardInfo.Dodges > 0):
            now = time.time()
            lifetime = acc.getConfig().EPIC_HERO_RETIRE_LIFETIME
            # check that update too old
            if (self.LordInfo.lastDodgesUpdateTime_ + lifetime <= now):
                self.clearDodges()
                info("Dodges lifetime was expired, cleared for auid=%r" % (acc.uid))

    def getBanEndTime(self):
        return self.LordInfo.GuardInfo.RetiredTime

    def initialPlaceOnScene(self, WS, acc, staticConstruction, construction, rid, SD, I):
        if construction.WasPlacedOnScene:
            return
        self.addFame(int(staticConstruction['Levels']['Item'][0]['fame']), acc, SD, I.STATS)
        if staticConstruction['classType'] == "FirstBuyBuilding":
            construction.ResourceToProduce = construction.getFirstBuyProductionRandomResource(staticConstruction,
                                                                                              self.getRandom(
                                                                                                  self.LordInfo.RandomSeed + rid))
            self.sell(staticConstruction['FirstBuyLevels']['Item'][0]['resources'], acc)
            for heroId in sorted(self.Heroes):
                hero = self.getHeroByID(heroId)
                if not hero.FirstBuyApplied:
                    hero.changeExperience(SD.data['FirstBuyHeroExpBonus'], self, WS, acc, I)
                    hero.FirstBuyApplied = True
        if staticConstruction['classType'] == "GuildBuilding":
            cycle = SD.getGuildProductionCycle(construction.ProductionLevel)
            if cycle != None:
                construction.ResourceToProduce = construction.getProductionRandomResource(cycle['percents'],
                                                                                          self.getRandom(
                                                                                              self.LordInfo.RandomSeed + rid))
        if staticConstruction['classType'] == "Tavern":
            construction.rollQuestForTavern(staticConstruction, acc.getConfig(), SD, self)
        construction.WasPlacedOnScene = True

    def getSpentGold(self, I, acc):
        gold = 0

        config = acc.getConfig()

        # потраченное на домики
        for buildingId in self.ConstructionsKeeper:
            building = self.getConstructionByID(buildingId)
            if building:
                staticBuilding = acc.SD.getStaticConstruction(building)
                gold += acc.SD.GetBuyPrice(staticBuilding, config).Gold
                # итерируем с 1-ого уровня тк нулевой для покупки.
                for lvl in xrange(1, building.Level):
                    if lvl < len(staticBuilding['Levels']['Item']):
                        gold += staticBuilding['Levels']['Item'][lvl]['price']['Gold']

        # пораченное на скины
        for heroId in self.HeroesKeeper.keys():
            hero = self.getHeroByID(heroId)
            for skinId in hero.HeroSkins.Skins.keys():
                skin = self.getSkinByID(skinId)
                if skin:
                    static_skin = acc.SD.getStaticSkinByPersistentId(skin.PersistentId)

                    price = int(static_skin['cost'])
                    if static_skin['persistentId'] in config.EventToolsChangeFields.SKIN_GOLD_PRICES:
                        price = int(config.EventToolsChangeFields.SKIN_GOLD_PRICES[static_skin['persistentId']])
                    # а был ли скин куплен или получен из event'ов?
                    if skin.WasBought:
                        gold += price

        # потраченное на флаги
        for flagId in self.Flags:
            customFlag = config.getCustomFlagById(flagId)
            if customFlag:
                gold += customFlag.Price
            else:
                staticCustomFlag = acc.SD.getCustomFlagById(flagId)
                if staticCustomFlag:
                    gold += int(staticCustomFlag['Price'])

        return gold

    def giveTalentsForHeroLevelUp(self, hero, staticHero, lvl, acc, I):
        if staticHero['lobbyData']['BonusTalentsForLevel']:
            bonuses = staticHero['lobbyData']['BonusTalentsForLevel']
            if bonuses['Levels'] and bonuses['Levels']['Item'] and len(bonuses['Levels']['Item']) > lvl:
                talents = bonuses['Levels']['Item'][lvl]
                if talents and talents['Talents'] and talents['Talents']['Item'] and len(
                        talents['Talents']['Item']) > 0:
                    for staticTalent in talents['Talents']['Item']:
                        if staticTalent and staticTalent['persistentId']:
                            talent = self.addTalent(crc32(staticTalent['persistentId']))
                            if talent.canBeSoulbound(acc.SD):
                                talent.Soulbound = hero
                            talInfo = TalentInfo(talent.PersistentId, talent.getID(), 0)
                            I.STATS.addTalentChange(acc.db.auid, talInfo, TalentChangeOperation.GetForLevelUp)
                            I.STATS.addTalentChange(acc.db.auid, talInfo, TalentChangeOperation.Soulbound)

    def setFirstWinIfNeed(self, map, configdata):
        userStatus = self.getInternalUserStatus(
            configdata)  # режим первых побед включается после преодоления определенного порога
        if userStatus != LordStatus.Newbie or configdata.FWOD_FOR_NEWBIES:
            if map and map['FWODGroup'] and map['FWODGroup'] != "":
                if map['FWODGroup'] not in self.LordInfo.TodayWinMaps:
                    self.LordInfo.TodayWinMaps.add(map['FWODGroup'], int(round(time.time())))

    def isFirstPlay(self, map, configdata):
        userStatus = self.getInternalUserStatus(
            configdata)  # режим первых побед включается после преодоления определенного порога
        if userStatus != LordStatus.Newbie or configdata.FWOD_FOR_NEWBIES:
            self.updateFirstDayWin()
            if map and map['FWODGroup'] and map['FWODGroup'] != "":
                return map['FWODGroup'] not in self.LordInfo.TodayWinMaps
        return False

    def updateFirstDayWin(self):
        try:
            for key in self.LordInfo.TodayWinMaps.keys():
                lastWinTime = self.LordInfo.TodayWinMaps[key]
                lastWinDate = date.fromtimestamp(lastWinTime)
                curDate = date.fromtimestamp(time.time())
                if curDate.year > lastWinDate.year:
                    del self.LordInfo.TodayWinMaps[key]
                elif curDate.month > lastWinDate.month:
                    del self.LordInfo.TodayWinMaps[key]
                elif curDate.day > lastWinDate.day:
                    del self.LordInfo.TodayWinMaps[key]
        except:
            catch()

    def validatePingResults(self, config):
        for key in self.LordInfo.PingResults.keys():
            if not key in config.PingInfo.addresses:
                del self.LordInfo.PingResults[key]
        for key in config.PingInfo.addresses.keys():
            if not key in self.LordInfo.PingResults:
                self.LordInfo.PingResults.add(key, config.PingInfo.MaxTimeOut)

    def getCurrentSkinName(self, hero, SD):
        if hero:
            if hero.HeroSkins.CurrentSkin.get():
                staticSkin = SD.getStaticSkinByPersistentId(hero.HeroSkins.CurrentSkin.PersistentId)
                if staticSkin:
                    return staticSkin['persistentId']
        return ""

    def getCurrentSkinPersistentId(self, hero):
        if hero:
            if hero.HeroSkins.CurrentSkin.get():
                return hero.HeroSkins.CurrentSkin.PersistentId
        return hero.PersistentId

    def getCurrentSkinAnimateAvatar(self, hero):
        if hero:
            if hero.HeroSkins.CurrentSkin.get():
                return hero.HeroSkins.CurrentSkin.IsAnimatedAvatar
        return hero.IsAnimatedAvatar


    def getLowLevelSameBuilding(self, staticConstruction, SD):
        all_buildings = []
        res_building = None

        for buildingId in self.Buildings.keys():
            building = self.getConstructionByID(buildingId)
            staticBuilding = SD.getStaticConstruction(building)

            if staticBuilding and staticBuilding['persistentId'] == staticConstruction['persistentId']:
                all_buildings.append(buildingId)

        for buildingId in self.Pocket.keys():
            building = self.getConstructionByID(buildingId)
            staticBuilding = SD.getStaticConstruction(building)

            if staticBuilding and staticBuilding['persistentId'] == staticConstruction['persistentId']:
                all_buildings.append(buildingId)

        for buildingId in all_buildings:
            building = self.getConstructionByID(buildingId)
            if not res_building or res_building.Level > building.Level:
                res_building = building

        return res_building

    def applyBuildingLimits(self, buildingNames, SD):
        all_not_ok = True

        while all_not_ok:

            all_not_ok = False
            needDel = None

            all_buildings = self.Buildings.keys()
            all_buildings.extend(self.Pocket.keys())

            for buildingId in all_buildings:
                building = self.getConstructionByID(buildingId)
                staticConstruction = SD.getStaticConstruction(building)
                if not staticConstruction:
                    self.Buildings.remove(building)
                    self.Pocket.remove(building)
                    continue
                if staticConstruction['persistentId'] not in buildingNames:
                    continue

                buildingLimits = staticConstruction['GroupBuildingLimits']
                if not buildingLimits or not buildingLimits['Item'] or len(buildingLimits['Item']) == 0:
                    continue

                for limit in buildingLimits['Item']:
                    count = 0
                    for buildingId in self.Buildings:
                        building = self.getConstructionByID(buildingId)
                        staticBuilding = SD.getStaticConstruction(building)
                        if staticBuilding and staticBuilding['GroupBuildingLimits'] and \
                                staticBuilding['GroupBuildingLimits']['Item'] and len(
                            staticBuilding['GroupBuildingLimits']['Item']) > 0:
                            for newLimit in staticBuilding['GroupBuildingLimits']['Item']:
                                if newLimit['dbid'] == limit['dbid']:
                                    count += 1
                    for buildingId in self.Pocket:
                        building = self.getConstructionByID(buildingId)
                        staticBuilding = SD.getStaticConstruction(building)
                        if staticBuilding['GroupBuildingLimits'] and staticBuilding['GroupBuildingLimits'][
                            'Item'] and len(staticBuilding['GroupBuildingLimits']['Item']) > 0:
                            for newLimit in staticBuilding['GroupBuildingLimits']['Item']:
                                if newLimit['dbid'] == limit['dbid']:
                                    count += 1
                    if count > limit['MaxNumberOfBuilding']:
                        needDel = staticConstruction
                        break

                if needDel:
                    building_to_del = self.getLowLevelSameBuilding(needDel, SD)
                    if building_to_del:
                        staticConstruction = SD.getStaticConstruction(building_to_del)
                        price = SD.getBuildingPrice(staticConstruction, building_to_del.Level)
                        self.sell(price, None, False)  # buildig price shouldn't has PremiumAccountHours != 0
                        self.Buildings.remove(building_to_del)
                        self.Pocket.remove(building_to_del)
                        all_not_ok = True
                        break

    def rollTalentForTavernBuilding(self, building, staticBuilding, SD, randValue):
        quest = building.getCurrentQuest(staticBuilding)
        if quest and 'reward' in quest and quest['reward'] and 'rollContainer' in quest['reward'] and quest['reward'][
            'rollContainer'] and quest['reward']['rollContainer']['dbid'] != '':
            persistentId, rar = SD.getTalentForRoll(quest['reward']['rollContainer']['percents']['Item'], False, "", "",
                                                    randValue, randValue)
            building.CraftedTalents.append(persistentId)

    def rollTalentsForTransmutationBuilding(self, building, acc, I, selectedOrangeSet, selectedRedSet):
        transRandVal = self.LordInfo.PremiumForgeRoll.TransmutationRandomSeed \
            if self.IsPremiumAccount() else self.LordInfo.OrdinaryForgeRoll.TransmutationRandomSeed
        talentsProduced = self.LordInfo.PremiumForgeRoll.TransmutationTalentsProduced \
            if self.IsPremiumAccount() else self.LordInfo.OrdinaryForgeRoll.TransmutationTalentsProduced
        seedUpdateFunc = self.setPremiumTransmutationRandomSeed \
            if self.IsPremiumAccount() else self.setTransmutationRandomSeed
        seeds = I.Config.PremiumGoodSeeds \
            if self.IsPremiumAccount() else I.Config.GoodSeeds
        rollContainer = acc.getConfig().EventToolsChangeFields.PREMIUM_TALENTS_DROP_RARITIES \
            if self.IsPremiumAccount() else acc.getConfig().EventToolsChangeFields.ORDINARY_TALENTS_DROP_RARITIES
        talentRandVal = self.LordInfo.TalentRandomSeed
        replace_exclusive = True
        staticBuilding = acc.SD.getStaticConstruction(building)
        if building.ProductionLevel + 1 >= int(staticBuilding['requiredLeveForExclusiveTalents']):
            replace_exclusive = False

        newTalensByRarity = {}

        for i in xrange(0, building.ProductionCustomValue):
            if talentsProduced >= 100:
                transRandVal = seedUpdateFunc(seeds)
                talentsProduced = 0

            persistentId, rarity = acc.SD.getTalentForRoll(rollContainer, replace_exclusive, selectedOrangeSet, selectedRedSet, transRandVal,
                                                           talentRandVal)
            intRarity = getattr(ETalentRarity, rarity)
            if intRarity in newTalensByRarity:
                newTalensByRarity[intRarity].append(persistentId)
            else:
                newTalensByRarity[intRarity] = [persistentId]
            transRandVal = self.getRandomPure(transRandVal)
            talentRandVal = self.getRandomPure(talentRandVal)
            talentsProduced += 1

        keys = newTalensByRarity.keys()[:]
        keys.sort()
        keys.reverse()

        for rar in keys:
            for talId in newTalensByRarity[rar]:
                talent = self.addTalent(talId)
                building.CraftedTalentsToLibrary.append(talent.id)
                I.STATS.addTalentChange(acc.db.auid, TalentInfo(talent.PersistentId, talent.id, 0),
                                        TalentChangeOperation.GetFromTransmutation)

        self.LordInfo.TalentRandomSeed = talentRandVal
        if self.IsPremiumAccount():
            self.LordInfo.PremiumForgeRoll.TransmutationRandomSeed = transRandVal
            self.LordInfo.PremiumForgeRoll.TransmutationTalentsProduced = talentsProduced
        else:
            self.LordInfo.OrdinaryForgeRoll.TransmutationRandomSeed = transRandVal
            self.LordInfo.OrdinaryForgeRoll.TransmutationTalentsProduced = talentsProduced

    def calcEventSkin(self, eventSkins, acc):
        allSkinsId = {}
        for eventSkin in eventSkins:
            if eventSkin.getSkin() not in self.EventSkins:
                self.EventSkins.append(eventSkin.getSkin())

            if eventSkin.isActual():
                if eventSkin.getSkin() not in self.ActiveEventSkins:
                    self.ActiveEventSkins.append(eventSkin.getSkin())
                    # попробуем подарить скин, если он бесплатен
                    if self.isSkinFree(eventSkin.getSkin(), acc):
                        addedSkin, reason = self.giveSkinForFree(eventSkin.getSkin(), acc)

            allSkinsId.update({eventSkin.getSkin(): eventSkin.isActual()})

        todel = []
        for skinId in self.ActiveEventSkins:
            if skinId not in allSkinsId or not allSkinsId[skinId]:
                todel.append(skinId)
        for skin in todel:
            self.ActiveEventSkins.remove(skin)

    def clearSkinInfo(self):
        todel = self.ActiveEventSkins.keys()[:]
        for skin in todel:
            self.ActiveEventSkins.remove(skin)

        todel = self.EventSkins.keys()[:]
        for skin in todel:
            self.EventSkins.remove(skin)

    def calcBanEventInfo(self, acc, eventMapsForBan, eventMaps):
        forBan = []
        for eventMap in eventMapsForBan:
            if eventMap.isActual():
                forBan.append(eventMap.map)
                if not eventMap.map in self.LordInfo.DisabledMaps:
                    self.LordInfo.DisabledMaps.append(eventMap.map)

        for eventMap in reversed([m for m in eventMaps if m.map in acc.getConfig().TournamentSettings.TOURNAMENT_MAP_LIST]):
            if eventMap.isActual():
                if not self.canActualTournamentMapForQuest(acc, eventMap.map):
                    forBan.append(eventMap.map)
                    if not eventMap.map in self.LordInfo.DisabledMaps:
                        self.LordInfo.DisabledMaps.append(eventMap.map)

        for disMap in self.LordInfo.DisabledMaps.keys():
            if not disMap in forBan:
                self.LordInfo.DisabledMaps.remove(disMap)

    def calcEventInfo(self, eventMaps, acc):
        debug("calcEventInfo %r", eventMaps)
        used_mapTypes = []
        # найдем актуальный эвент
        for eventMap in reversed(eventMaps):
            if eventMap.mapType in used_mapTypes:
                continue
            if eventMap.isActual():
                if eventMap.map not in acc.getConfig().TournamentSettings.TOURNAMENT_MAP_LIST:
                    if eventMap.mapType not in used_mapTypes:
                        used_mapTypes.append(eventMap.mapType)
                    debug("self.updateMap(%r, %r, %r, %r, %r, True)", enum2String(MapType, eventMap.mapType), eventMap.map, eventMap.enabled, eventMap.getStartTime(), eventMap.getEndTime() )
                    self.updateMap(eventMap.mapType, eventMap.map, eventMap.enabled, eventMap.getStartTime(),
                                   eventMap.getEndTime(), True)

        for eventMap in reversed([m for m in eventMaps if m.map in acc.getConfig().TournamentSettings.TOURNAMENT_MAP_LIST]):
            if eventMap.isActual():
                if self.canActualTournamentMapForQuest(acc, eventMap.map):
                    if eventMap.mapType not in used_mapTypes:
                        used_mapTypes.append(eventMap.mapType)
                    debug("self.updateMap(%r, %r, %r, %r, %r, True)", enum2String(MapType, eventMap.mapType), eventMap.map, eventMap.enabled, eventMap.getStartTime(), eventMap.getEndTime() )
                    self.updateMap(eventMap.mapType, eventMap.map, eventMap.enabled, eventMap.getStartTime(),
                                   eventMap.getEndTime(), True)

        # проверим, что нет не актуальных
        curTime = int(round(time.time()))
        for slotIndex in self.LordInfo.MapsByType.keys():
            # но по второму разу не проверяем
            if slotIndex in used_mapTypes:
                continue
            mapInfo = self.LordInfo.MapsByType.get(slotIndex)
            if mapInfo and (mapInfo.StartTime != 0 or mapInfo.EndTime != 0):
                if not (mapInfo.StartTime < curTime and curTime < mapInfo.EndTime):
                    self.updateMap(slotIndex, "", True, 0, 0, True)

    def getGoldLampRollContainer(self, SD, config, firstWin):

        lampEventSettings = config.LampEventSettings
        if not lampEventSettings:
            return ""
        if lampEventSettings.Transactions == 0 or lampEventSettings.BonusGold == 0 or lampEventSettings.Duration == 0:
            return ""
        if self.isLampLimitReached(lampEventSettings):
            return ""

        if self.hasLamp():
            return ""

        now = time.time()
        lastPaymentDays = int(now - self.Statistics.LastPaymentTime) / 86400
        # block period from last lamp drop
        blockLampPeriodFLD = lampEventSettings.BlockLampPeriod
        # block period from last payment
        blockLampPeriodFLP = lampEventSettings.BlockLampPeriodFromLastPayment
        guarantyLampPeriod = lampEventSettings.GuarantyLampPeriod
        lastDropDay = int(now - self.Statistics.LastLampDropTime) / 86400

        if not self.isInEventGroup(lampEventSettings.ActiveGroups, lastPaymentDays, config):
            return ""

        if "start" in blockLampPeriodFLD and "end" in blockLampPeriodFLD and blockLampPeriodFLD[
            "start"] <= lastDropDay and lastDropDay <= blockLampPeriodFLD["end"]:
            return ""

        if "start" in blockLampPeriodFLP and "end" in blockLampPeriodFLP and blockLampPeriodFLP[
            "start"] <= lastPaymentDays and lastPaymentDays <= blockLampPeriodFLP["end"]:
            return ""

        if "start" in guarantyLampPeriod and "end" in guarantyLampPeriod and guarantyLampPeriod[
            "start"] <= lastDropDay and lastDropDay <= guarantyLampPeriod["end"]:
            return SD.getGoldLampRollContainer(lastPaymentDays)

        if firstWin:
            if len(self.LordInfo.TodayWinMaps) < lampEventSettings.FWODLimit:
                if lampEventSettings.FwodLampRollProbability <= 100.0 * random.random():
                    return ""
            else:
                return ""
        elif lampEventSettings.LampRollProbability <= 100.0 * random.random():
            return ""

        return SD.getGoldLampRollContainer(lastPaymentDays)

    def isLampCanBeApplied(self, event, lampEventSettings):
        if self.isLampLimitReached(lampEventSettings):
            warn("cannot apply new gold lamp, no lamps allowed (%d) (%d)" % (
            self.MarketingEventsInfo.LampEventInfo.AllowedLamps,
            self.MarketingEventsInfo.LampEventInfo.AllowedLampsGoldStatus))
            return False

        if self.hasLamp():
            warn("cannot apply new gold lamp, lamp already active (%s, %d)" % (
            self.MarketingEventsInfo.LampEventInfo.dbId, self.MarketingEventsInfo.LampEventInfo.EndTime))
            return False

        if lampEventSettings.Transactions == 0 or lampEventSettings.BonusGold == 0 or lampEventSettings.Duration == 0:
            warn(
                "cannot apply new gold lamp, lamp disabled from cofing (Transactions = %d, BonusGold = %d, Duration = %d)" % (
                lampEventSettings.Transactions, lampEventSettings.BonusGold, lampEventSettings.Duration))
            return False

        return True

    def applyGoldLampEvent(self, event, lampEventSettings):
        if self.isLampCanBeApplied(event, lampEventSettings):
            now = time.time()
            self.MarketingEventsInfo.LampEventInfo.AllowedLamps -= 1
            self.MarketingEventsInfo.LampEventInfo.AllowedLampsGoldStatus -= 1
            self.MarketingEventsInfo.LampEventInfo.BonusLeft = lampEventSettings.BonusGold
            self.MarketingEventsInfo.LampEventInfo.TransactionsLeft = lampEventSettings.Transactions
            self.MarketingEventsInfo.LampEventInfo.dbId = event["dbid"]
            self.MarketingEventsInfo.LampEventInfo.StartTime = now
            self.MarketingEventsInfo.LampEventInfo.EndTime = now + lampEventSettings.Duration
            self.Statistics.LastLampDropTime = now
            info("apply new gold lamp %r" % self.MarketingEventsInfo.LampEventInfo)

    def replaceGoldLampEvent(self, bonus, goldBonus, transaction, duration, updateLastLampDropTime=True):
        eventInfo = self.MarketingEventsInfo.LampEventInfo
        eventInfo.dbId = "/UI/Content/MarketingEvents/GoldLamp_" + str(bonus)
        eventInfo.BonusLeft = goldBonus
        eventInfo.StartTime = int(round(time.time()))
        eventInfo.EndTime = eventInfo.StartTime + duration
        eventInfo.TransactionsLeft = transaction
        if updateLastLampDropTime:
            self.Statistics.LastLampDropTime = eventInfo.StartTime

    def isInEventGroup(self, activeGroups, lastPaymentDays, config):
        for activeGroupId in activeGroups:
            activeGroup = config.getActiveGroupByID(activeGroupId)
            if activeGroup.StartDay <= lastPaymentDays and (
                    activeGroup.EndDay >= lastPaymentDays or activeGroup.EndDay == -1):
                return True

        return False

    def isLampLimitReached(self, lampEventSettings):
        lastPaymentDays = int(time.time() - self.Statistics.LastPaymentTime) / 86400
        if lastPaymentDays <= lampEventSettings.MaxPaymentDaysForGoldStatus:
            return self.MarketingEventsInfo.LampEventInfo.AllowedLampsGoldStatus <= 0
        else:
            return self.MarketingEventsInfo.LampEventInfo.AllowedLamps <= 0

    def hasLamp(self):
        now = time.time()
        if self.MarketingEventsInfo.LampEventInfo.EndTime <= now or self.MarketingEventsInfo.LampEventInfo.dbId == "":
            return False

        return True

    def getGoldLamp(self, SD):
        if not self.hasLamp():
            return None

        return SD.getObjectByDbid(self.MarketingEventsInfo.LampEventInfo.dbId)

    def getGoldLampType(self, SD):
        if self.MarketingEventsInfo.LampEventInfo.dbId == "":
            return 0

        return crc32(self.MarketingEventsInfo.LampEventInfo.dbId[1:] + ".xdb")

    def getUpgHeroLampType(self):
        return crc32('UI/Content/MarketingEvents/UpgradeHeroTalentsEvent.xdb')

    def saveLampInfo(self, acc):
        acc.db.LampInfo = ClassDict()
        if self.hasLamp():
            eventInfo = self.MarketingEventsInfo.LampEventInfo
            if eventInfo:
                acc.db.LampInfo["dbId"] = eventInfo.dbId
                acc.db.LampInfo["BonusLeft"] = eventInfo.BonusLeft
                acc.db.LampInfo["StartTime"] = eventInfo.StartTime
                acc.db.LampInfo["EndTime"] = eventInfo.EndTime
                acc.db.LampInfo["TransactionsLeft"] = eventInfo.TransactionsLeft

                acc.db.LampInfo["TotalTransactionsUsed"] = eventInfo.TotalTransactionsUsed
                acc.db.LampInfo["TotalBonusUsed"] = eventInfo.TotalBonusUsed
                acc.db.LampInfo["AllowedLamps"] = eventInfo.AllowedLamps
                acc.db.LampInfo["AllowedLampsGoldStatus"] = eventInfo.AllowedLampsGoldStatus
            else:
                acc.db.LampInfo["dbId"] = ""
        else:
            acc.db.LampInfo["dbId"] = ""

    def restoreLampInfo(self, acc):
        try:
            if hasattr(acc.db, "LampInfo"):
                eventInfo = self.MarketingEventsInfo.LampEventInfo

                eventInfo.TotalTransactionsUsed = acc.db.LampInfo["TotalTransactionsUsed"]
                eventInfo.TotalBonusUsed = acc.db.LampInfo["TotalBonusUsed"]
                eventInfo.AllowedLamps = acc.db.LampInfo["AllowedLamps"]
                eventInfo.AllowedLampsGoldStatus = acc.db.LampInfo["AllowedLampsGoldStatus"]

                eventInfo.dbId = acc.db.LampInfo["dbId"]
                eventInfo.BonusLeft = acc.db.LampInfo["BonusLeft"]
                eventInfo.StartTime = acc.db.LampInfo["StartTime"]
                eventInfo.EndTime = acc.db.LampInfo["EndTime"]
                eventInfo.TransactionsLeft = acc.db.LampInfo["TransactionsLeft"]
        except:
            pass

    def getRarityIndex(self, rarity):
        rarities = ["Class", "ordinary", "good", "excellent", "magnificent", "exclusive", "outstanding"]

        for index, item in enumerate(rarities):
            if rarity == item:
                return index

        return -1

    def canUnsoulboundWithLamp(self, static_talent, SD):
        dbEvent = self.getGoldLamp(SD)
        if not dbEvent:
            return False

        talent_rarity = self.getRarityIndex(static_talent["rarity"])
        if talent_rarity <= 0:
            return False

        lamp_rarity = self.getRarityIndex(dbEvent["unsoulBoundRarity"])
        if lamp_rarity < 0:
            return False

        return lamp_rarity >= talent_rarity

    def applyMarketingEvent(self, event_item, lampEventSettings):
        info("apply marketing event item %s" % event_item["dbid"])
        marketing_event = event_item["marketingEvent"]
        if not marketing_event:
            warn("cannot get marketing event for item %s" % event_item["dbid"])
        elif marketing_event["classType"] == "GoldLampEvent":
            self.applyGoldLampEvent(marketing_event, lampEventSettings)
        else:
            warn("marketing event %s has unsupported type %s" % (event_item["dbid"], marketing_event["classType"]))

    def getMagicLampBonusValue(self, SD):
        dbEvent = self.getGoldLamp(SD)
        if not dbEvent:
            return 0.0
        return float(dbEvent['bonusPersent'])

    def useMagicLampBonus(self, amount, SD, auid, stats):
        bonusPercents = self.getMagicLampBonusValue(SD)
        if bonusPercents <= 0.0:
            return

        bonusAmount = int(amount * bonusPercents / 100.0)

        if bonusAmount > self.MarketingEventsInfo.LampEventInfo.BonusLeft:
            bonusAmount = self.MarketingEventsInfo.LampEventInfo.BonusLeft

        self.MarketingEventsInfo.LampEventInfo.BonusLeft -= bonusAmount

        infLamp = self.MarketingEventsInfo.LampEventInfo.TransactionsLeft == 0
        if not infLamp:
            self.MarketingEventsInfo.LampEventInfo.TransactionsLeft -= 1

        if self.MarketingEventsInfo.LampEventInfo.BonusLeft <= 0 or (
                self.MarketingEventsInfo.LampEventInfo.TransactionsLeft <= 0 and not infLamp):
            stats.addRuneReplenish(auid, self.getGoldLampType(SD))
            self.MarketingEventsInfo.LampEventInfo.dbId = ""

        return bonusAmount

    def useLampTransaction(self):
        infLamp = self.MarketingEventsInfo.LampEventInfo.TransactionsLeft == 0

        if not infLamp:
            self.MarketingEventsInfo.LampEventInfo.TransactionsLeft -= 1

        if self.MarketingEventsInfo.LampEventInfo.TransactionsLeft <= 0 and not infLamp:
            self.MarketingEventsInfo.LampEventInfo.dbId = ""

    def canBuyTicket(self, acc):
        return "/UI/Content/MarketingEvents/BuyTournamentTicketEvent" in acc.getConfig().MARKETING_EVENTS and acc.model.TournamentInfo.TournamentState == TournamentState.TicketSale

    def registerPayment(self, acc, I, amount, source, txnid):
        info("registerPayment(acc.auid=%s, amount=%s, source=%s, txnid=%s)", acc.auid, amount, source, txnid)
        if source == "STEAM":
            curTime = int(round(time.time()))
            txnid = int(txnid)
            order = acc.db.steamOrders.get(txnid, None)
            if order is not None:
                if order["orderStatus"] in (
                isteam.STEAM_ORDER_STATUS_WAIT_FOR_REPLENISH, isteam.STEAM_ORDER_STATUS_CONFIRM):
                    if (curTime - order["orderTime"]) < isteam.STEAM_REPLENISH_TIMEOUT:
                        _callback = functools.partial(self.onSteamResponse, acc=acc, gold=amount, txnid=txnid, I=I)
                        if order["orderStatus"] == isteam.STEAM_ORDER_STATUS_CONFIRM:
                            # a response for te billing replenish call isn't received yet, set this mark for a future check
                            order["registered"] = True
                        order["orderStatus"] = isteam.STEAM_ORDER_STATUS_WAIT_FOR_STEAMCONFIRM
                        acc.steam.confirmTransaction(txnid, order["orderCode"], _callback)
                    else:
                        err("Timeout register payment %s in state %s", txnid, order["orderStatus"])
                        acc.steam.cancelTransaction(txnid, order["orderCode"])
                        del acc.db.steamOrders[txnid]
                else:
                    err("Wrong payment steam status: %s, txnid = %s. Canceled.", order["orderCode"], txnid)
                    acc.steam.cancelTransaction(txnid, order["orderCode"])
                    del acc.db.steamOrders[txnid]
            else:
                err("Wrong steam order %r, db.steamOrders %r" % (txnid, acc.db.steamOrders))

        elif source == "AERIA":
            curTime = int(round(time.time()))
            if txnid in acc.db.aeriaOrders:
                order = acc.db.aeriaOrders[txnid]
                if order["status"] == iaeria.AERIA_LG_REPLENISH:
                    acc.db.aeriaOrders.pop(txnid, None)
                else:
                    err("Wrong payment aeria status %r" % order)
            else:
                err("Wrong aeria order %r, db.aeriaOrders %r" % (txnid, acc.db.aeriaOrders))

        elif source == "ARCGAMES":
            curTime = int(round(time.time()))
            if txnid in acc.db.arcgamesOrders:
                order = acc.db.arcgamesOrders[txnid]
                if order["status"] == iarcgames.ARCGAMES_LG_REPLENISH:
                    acc.db.arcgamesOrders.pop(txnid, None)
                else:
                    err("Wrong payment arcgames status %r" % order)
            else:
                err("Wrong arcgames order %r, db.arcgamesOrders %r" % (txnid, acc.db.arcgamesOrders))

        elif source == "ZZIMA":
            curTime = int(round(time.time()))
            if txnid in acc.db.zzimacomOrders:
                order = acc.db.zzimacomOrders[txnid]
                if order["status"] == izzimacom.ZZIMA_LG_REPLENISH:
                    acc.db.zzimacomOrders.pop(txnid, None)
                else:
                    err("Wrong payment zzima status %r" % order)
            else:
                err("Wrong zzima order %r, db.zzimacomOrders %r" % (txnid, acc.db.zzimacomsOrders))

        if source != "BONUSES":
            self.Statistics.LastPaymentTime = int(round(time.time()))
            bonus_amount = self.useMagicLampBonus(amount, acc.SD, acc.auid, I.STATS)
            bonus_percents = self.getMagicLampBonusValue(acc.SD)

            # выдаем подарки за донатную акцию
            self.give_rewards_for_donate(acc, amount)

            # уведомляем сервер турнира о том, что игроку выдан билет
            info("Marketing events %r", acc.getConfig().MARKETING_EVENTS.getJsonDict())
            if self.canBuyTicket(acc):
                info("canBuyTicket ok, instant payment size=%r",
                     acc.getConfig().TournamentSettings.INSTANT_PAYMENT_SIZE)
                if amount >= acc.getConfig().TournamentSettings.INSTANT_PAYMENT_SIZE and acc.model.TournamentInfo.TournamentTicket.State == TicketState.NotActivated and acc.model.TournamentInfo.TournamentState == TournamentState.TicketSale:
                    self.TournamentInfo.createTicket(acc.db.auid, TicketBoughtType.GiftedWithPayment)
                    if "tournament0_ticket_dlc" not in acc.db.dlcs:
                        I.WS.tryApplyDLCs(["tournament0_ticket_dlc"], acc, I)
                    # send message to tournament social server
                    args = dict(action="create_account", auid=acc.db.auid, snid=acc.snid, snuid=acc.snuid,
                                nickname=acc.getNickname(), fraction=acc.db.fraction,
                                boughtType=TicketBoughtType.GiftedWithPayment)
                    req = HTTPRequest(url=cfg.TOURNAMENT_SERVER_ADDR + '/?' + urllib.urlencode(args), method="GET",
                                      connect_timeout=20.0, request_timeout=20.0)
                    I.HTTP.fetch(req, self.onRegisterTournament)

            info("registerPayment(acc.auid=%s): bonus_amount=%s bonus_percents=%s", acc.auid, bonus_amount, bonus_percents)
            if bonus_amount > 0:
                I.BILL.replenish(acc.auid, bonus_amount, "MagicLampBonus" + str(bonus_percents), None)
                return bonus_amount

        # просто перезапрашиваем баланс (force check)
        I.BILL.getStatusBalance(acc.auid, force_balance_check=True)
        return 0

    def give_rewards_for_donate(self, acc, amount):
        available_donate_events = acc.getConfigValue("DonateEvents")
        info("GiveRewardForDonate: avilable events count %d", len(available_donate_events))
        for _, donate_event in available_donate_events.iteritems():
            info("DonateEvent: id=%d EndTimestamp=%d", donate_event.PersistentId, donate_event.EndTimestamp)
            if donate_event.EndTimestamp < acc.model.FatClientServerTime:
                continue

            for _, donate_range in donate_event.Ranges.iteritems():
                info("DonateRange: from %d to %d, user amount = %d", donate_range.AmountFrom, donate_range.AmountTo, amount)

                if donate_range.AmountFrom > amount:
                    continue
                if donate_range.AmountTo != -1 and donate_range.AmountTo < amount:
                    continue

                info("DonateRange: give rewards")
                for _, reward in donate_range.Rewards.iteritems():
                    for lootbox_id in reward.Lootboxes:
                        info("DonateRange: give lootbox %s", lootbox_id)
                        lootbox_persistent_id = crc32(lootbox_id)
                        self.addLootbox(lootbox_persistent_id, acc)

    def onRegisterTournament(self, response):
        info("onRegister by payment: %r", response)
        if response and (not response.error) and len(response.body) > 0:
            result = jsonResult(response)
            if result.get("response", None) and result["response"].get("ok", None):
                info("Ticket buy OK")

    def onSteamResponse(self, response, acc, gold, txnid, I):
        if response:
            info("onSteamResponce: %s" % response)
            isOk = response.get("ok") or 0
            if not isOk:
                I.BILL.writeoff(acc.auid, gold, "SteamBuyItemFailed(%s)" % txnid)
                err("Steam response fail %r" % response)
        else:
            err("Steam response null")

        del acc.db.steamOrders[txnid]

    def onAeriaReplenish(self, response, txnid, acc):
        if response:
            info("onAeriaReplenish: %s" % response)
            code = response["result"]
            if code == ibilling.PAYMENTS_OK:
                info("onAeriaReplenish OK")
            elif code == ibilling.PAYMENTS_TXN_IN_QUEUE:
                info("onAeriaReplenish txnid=%r in QUEUE" % txnid)
            else:
                err("Aeria replenish error %r" % response)
        else:
            err("Aeria replenish error %r" % response)

    def onArcGamesReplenish(self, response, txnid, acc):
        if response:
            info("onArcGamesReplenish: %s" % response)
            code = response["result"]
            if code == ibilling.PAYMENTS_OK:
                info("onArcGamesReplenish OK")
            elif code == ibilling.PAYMENTS_TXN_IN_QUEUE:
                info("onArcGamesReplenish txnid=%r in QUEUE" % txnid)
            else:
                err("ArcGames replenish error %r" % response)
        else:
            err("ArcGames replenish error %r" % response)

    def onZZimacomReplenish(self, response, txnid, acc):
        if response:
            info("onZZimacomReplenish: %s" % response)
            code = response["result"]
            if code == ibilling.PAYMENTS_OK:
                info("onZZimacomReplenish OK")
            elif code == ibilling.PAYMENTS_TXN_IN_QUEUE:
                info("onZZimacomReplenish txnid=%r in QUEUE" % txnid)
            else:
                err("ZZimacom replenish error %r" % response)
        else:
            err("ZZimacom replenish error %r" % response)

    def getPaymentBonusActions(self):
        info("getPaymentBonusActions()")
        return []

    def getHeroMaxLevelStat(self, hero, stat, SD):
        staticHero = SD.getStaticHero(hero)
        if not staticHero:
            return 0
        level = 36

        # collecting static stats for easy access in calculations
        heroStaticStats = {}

        staticStatFound = False
        sdStat = None
        for sdStat in staticHero['stats']['stats']['Item']:
            if sdStat:
                statid = sdStat['statId']
                heroStaticStats[statid] = sdStat
                if statid == stat:
                    staticStatFound = True

        # main looking stat not found in hero's static data
        if not staticStatFound:
            return 0

        bestStat = 0
        for talentSetId, talentSet in hero.TalentSets.items():
            # filling with all stats and zeroes
            heroStats = {}
            for f in dir(HeroStat):
                if not re.match('(^__[a-z]*__)', f):
                    heroStats[SD.getEditorStatName(f)] = 0

            k = level / 36
            for cStat in heroStats:
                codeStat = SD.getCodeStatName(cStat)
                staticStat = heroStaticStats.get(cStat)
                calc = 0
                if staticStat:
                    calc = staticStat['calcValue']

                # static stats + hero stats + guild stats
                tryInc(heroStats, cStat, calc + k * (getattr(talentSet.Stats, codeStat)
                                                     + getattr(talentSet.GuildStats, codeStat)))
                # buildings stats
                heroStats[cStat] += self.getBonusFromBuilding(cStat, SD)

            totalBudget = 0
            # base talents stats
            for key in talentSet.Talents.keys():
                talent = self.getTalentByID(talentSet.Talents.get(key))
                staticTalent = SD.getStaticTalent(talent)
                if staticTalent:
                    talentLevel = SD.getTalentLevelByPoints(talent.Points, staticTalent)
                    totalBudget += staticTalent['forceBonus']
                    talentStats = staticTalent['talentStats']
                    if talentStats:
                        for talentStat in talentStats['Item']:
                            if talentLevel >= 0 and talentLevel < len(talentStat['values']['Item']):
                                tryInc(heroStats, talentStat['stat'], tofloat(talentStat['values']['Item'][talentLevel]))

            # stats points from force
            statsBonusBudget = SD.ForceParameters['defaultStatBonus']
            if talentSet.Force > SD.ForceParameters['defaultBaseForce']:
                statsBonusBudget += (talentSet.Force - SD.ForceParameters['defaultBaseForce']) * SD.ForceParameters[
                    'statBonusByForce']

            forceCoef = (statsBonusBudget * totalBudget / staticHero['totalStatsBudget'] / 6.0 / 100.0) + level

            for cStat in heroStats:
                staticStat = heroStaticStats.get(cStat)
                if staticStat:
                    tryInc(heroStats, cStat, staticStat['calcIncrement'] * forceCoef)

            # variative stat mods (stat modsstaticStat['calcIncrement'] * forceCoef depending on current hero stats)
            statModifiersAdditions = {}
            for key in talentSet.Talents.keys():
                talent = self.getTalentByID(talentSet.Talents.get(key))
                staticTalent = SD.getStaticTalent(talent)
                if staticTalent:
                    talentLevel = SD.getTalentLevelByPoints(talent.Points, staticTalent)
                    # info( "talent id=%r, level=%r" % ( staticTalent['persistentId'], talentLevel ) )

                    # in variative stats looking for max stat in hero
                    maxf = 'variativeMaxTalentStats'
                    variativeMaxTalentStats = staticTalent[maxf]
                    variativeMaxByName = {}

                    if variativeMaxTalentStats:
                        for talentStat in variativeMaxTalentStats['Item']:
                            if talentStat.get('addValueName'):
                                if talentStat['addValueName'] not in variativeMaxByName.keys():
                                    variativeMaxByName[talentStat['addValueName']] = []

                                variativeMaxByName[talentStat['addValueName']].append(talentStat)

                        for talentStatsByValueName in variativeMaxByName.values():
                            found = False
                            maxStat = None
                            currentMaxValue = float('-inf')
                            for talentStat in talentStatsByValueName:
                                if heroStats[talentStat['stat']] >= currentMaxValue:
                                    found = True
                                    currentMaxValue = heroStats[talentStat['stat']]
                                    maxStat = talentStat

                            if found:
                                cStat = maxStat['stat']
                                if cStat not in statModifiersAdditions:
                                    statModifiersAdditions[cStat] = 0

                                if talentLevel >= 0 and talentLevel < len(maxStat['values']['Item']):
                                    statModifiersAdditions[cStat] += tofloat(maxStat['values']['Item'][talentLevel])
                                else:
                                    warn(
                                        "Attempting to get variative stat modifier for level %r but it is not exist in static data. Talent %r" % (
                                        talentLevel, staticTalent["persistentId"]))

                # in variative stats looking for min stat in hero
                    minf = 'variativeMinTalentStats'
                    variativeMinTalentStats = staticTalent[minf]
                    variativeMinByName = {}

                    if variativeMinTalentStats:
                        for talentStat in variativeMinTalentStats['Item']:
                            if talentStat.get('addValueName'):
                                if talentStat['addValueName'] not in variativeMinByName.keys():
                                    variativeMinByName[talentStat['addValueName']] = []

                                variativeMinByName[talentStat['addValueName']].append(talentStat)

                        for talentStatsByValueName in variativeMinByName.values():
                            minStat = None
                            found = False
                            currentMinValue = float('+inf')
                            for talentStat in talentStatsByValueName:
                                if heroStats[talentStat['stat']] <= currentMinValue:
                                    found = True
                                    currentMinValue = heroStats[talentStat['stat']]
                                    minStat = talentStat

                            if found:
                                cStat = minStat['stat']
                                if cStat not in statModifiersAdditions:
                                    statModifiersAdditions[cStat] = 0

                                if talentLevel >= 0 and talentLevel < len(minStat['values']['Item']):
                                    statModifiersAdditions[cStat] += tofloat(minStat['values']['Item'][talentLevel])
                                else:
                                    warn(
                                        "Attempting to get variative stat modifier for level %r but it is not exist in static data. Talent %r" % (
                                        talentLevel, staticTalent["persistentId"]))

            for smAdd in statModifiersAdditions:
                tryInc(heroStats, smAdd, statModifiersAdditions[smAdd])
                # info("addvalue %r stat %r", statModifiersAdditions[smAdd], smAdd)

            if stat in heroStats and heroStats[stat] > bestStat:
                bestStat = heroStats[stat]

        return bestStat

    # =================================================================================
    # Выдача разных халявных плюшек, нужно для DLC PF-74501
    # =================================================================================
    def addHeroesForFree(self, args, SD, acc, WS, I):
        try:
            for arg in args:
                exp = 0
                if ":" in arg:
                    pair = arg.split(":")
                    arg = pair[0]
                    exp = int(pair[1])
                heroFound = False
                for heroId in self.Heroes:
                    hero = self.getHeroByID(heroId)
                    staticHero = SD.getStaticHero(hero)
                    if staticHero['persistentId'] == arg.strip():
                        heroFound = True
                if not heroFound:
                    addedHero = self.hireHero(crc32(arg.strip()), acc.sex, WS, acc, I)
                    if addedHero and exp:
                        addedHero.changeExperience(exp, self, WS, acc, I)
        except:
            catch()

    def addGoldForFree(self, arg, auid, BILL):
        try:
            if arg:
                val = int(arg)
                BILL.replenish(auid, val, "Gold for DLC", None)
        except:
            catch()

    # pointsInArgs = True - talent points, False - talent level
    def addTalentsForFree(self, getFromInfo, args, acc, STATS, op, pointsInArgs=False):
        try:

            for arg in args:
                exp = 0
                if ":" in arg:
                    pair = arg.split(":")
                    arg = pair[0]
                    exp = int(pair[1])
                talent_crc = crc32(arg.strip())
                staticTalent = acc.SD.getStaticTalentByTalentId(talent_crc)
                if staticTalent:
                    talent = self.addTalent(talent_crc)
                    if exp > 1:
                        talentPointsToLevel = acc.SD.getTalentPointsToLevel(staticTalent)
                        talent.Points = talentPointsToLevel[exp - 2] if not pointsInArgs else exp
                    talInfo = TalentInfo(talent.PersistentId, talent.getID(), 0)
                    STATS.addTalentChange(acc.db.auid, talInfo, op, getFromInfo)
        except:
            catch()

    def addRandomTalentsForFree(self, getFromInfo, args, SD, acc, STATS, op):
        try:
            rarity = args['Rarity']
            if isinstance(rarity, (long, int)):
                for (talentType, value) in ETalentRarity.__dict__.iteritems():
                    if rarity == value:
                        rarity = str(talentType)

            talentsCount = len(SD.TALENTS_FOR_ROLL[rarity])
            for i in xrange(0, args['Count']):
                talId = SD.getValueInRange(random.randint(0, talentsCount - 1), 0, talentsCount - 1)

                talent_id = acc.model.addNewTalent()
                talent = acc.model.getTalentByID(talent_id)
                talent.IsNew = True
                talent.PersistentId = SD.getRandomTalent(rarity, "", talId)
                self.UserInventory.add(talent_id)
                STATS.addTalentChange(acc.db.auid, TalentInfo(talent.PersistentId, talent_id, 0), op, getFromInfo)
        except:
            catch()

    def addSkinsForFree(self, args, acc):
        try:
            for arg in args:
                skinId = crc32(arg.strip())
                self.giveSkinForFree(skinId, acc, withoutCheck=True)
        except:
            catch()

    def addResourcesForFree(self, arg, acc=None):
        try:
            if arg:
                resources = self.createResourcesTable()
                for key in arg:
                    if isinstance(arg[key], dict):
                        resources[key] = arg[key].copy()
                    else:
                        resources[key] = arg[key]
                self.sell(resources, acc, False)
        except:
            catch()


    def addFameForFree(self, arg, I, acc):
        try:
            if arg:
                self.addFame(int(arg), acc, acc.SD, I.STATS)
        except:
            catch()

    def addPremiumForFree(self, arg, acc):
        try:
            if arg:
                extend_time = int(arg) * 24 * 60 * 60

                if self.IsPremiumAccount():
                    self.LordInfo.PremiumAccountEnd += extend_time
                else:
                    # fix all production buildings
                    if acc:
                        for constructionId, construction in self.ConstructionsKeeper.iteritems():
                            staticConstruction = acc.SD.getStaticConstruction(construction)
                            if staticConstruction and staticConstruction['classType'] == 'ProductionBuilding':
                                construction.storeTimeBasedProduction(staticConstruction, "ProductionLevels", acc.getConfig(), acc.SD, self)
                    self.LordInfo.PremiumAccountStart = int(round(time.time()))
                    self.LordInfo.PremiumAccountEnd = self.LordInfo.PremiumAccountStart + extend_time
        except:
            catch()

    def addHousesForFree(self, args, SD):
        try:
            for arg in args:
                level = 0
                if ":" in arg:
                    pair = arg.split(":")
                    arg = pair[0]
                    level = int(pair[1])
                building_crc = crc32(arg.strip())
                staticConstruction = SD.getStaticConstructionByPersistentId(building_crc)
                if staticConstruction:
                    if self.canPlaceBuilding(staticConstruction, SD):
                        construction_uid = self.addNewConstruction()
                        construction = self.getConstructionByID(construction_uid)
                        construction.PersistentId = building_crc
                        construction.Level = level
                        self.Pocket.add(construction)
        except:
            catch()

    def resetComplaints(self, acc):
        curTime = datetime.datetime.now()
        lastTime = datetime.datetime.fromtimestamp(float(self.LordInfo.ResetComplaintsTime))
        if curTime.day != lastTime.day:
            self.LordInfo.ComplaintsLeft = acc.getConfig().ComplaintsSettings.MAX_COMPLAINTS_PER_DAY + self.LordInfo.ExtraComplaints
            self.LordInfo.ResetComplaintsTime = int(time.mktime(curTime.timetuple()))

    def tryApplyDLCsForMuid(self, muid, acc, I):
        muidKey = str(muid)
        if muidKey in cfg.MUID_TO_DLCS:
            dlcs = cfg.MUID_TO_DLCS[muidKey]
            info("applying dlcs for muid='%s' auid='%s'", muidKey, acc.auid)
            return self.tryApplyDLCs(dlcs, acc, I)
        else:
            info("dlcs for muid='%s' auid='%s' not found in config: %r", muidKey, acc.auid, cfg.MUID_TO_DLCS)
            return False

    def tryApplyDLCs(self, dlcs, acc, I):
        isAnyWasApplied = False
        # применяем DLC
        for dlc in dlcs:
            dlcKey = str(dlc)
            if dlcKey in cfg.DLCs_INFO:
                dlcInfo = cfg.DLCs_INFO[dlcKey]
                canMultiApply = "MultiApply" in dlcInfo and dlcInfo["MultiApply"]
                if dlcKey not in acc.db.dlcs or canMultiApply:
                    acc.model.write(acc.pending)
                    for key in dlcInfo.keys():
                        if key == "Heroes":
                            self.addHeroesForFree(dlcInfo[key], acc.SD, acc, I.WS, I)
                        elif key == "Gold":
                            self.addGoldForFree(dlcInfo[key], acc.auid, I.BILL)
                        elif key == "Talents":
                            self.addTalentsForFree(dlcKey, dlcInfo[key], acc, I.STATS, TalentChangeOperation.GetFromDLC)
                        elif key == "Skins":
                            self.addSkinsForFree(dlcInfo[key], acc)
                        elif key == "Resources":
                            self.addResourcesForFree(dlcInfo[key], acc)
                        elif key == "Fame":
                            self.addFameForFree(dlcInfo[key], I, acc)
                        elif key == "Premium":
                            self.addPremiumForFree(dlcInfo[key], acc)
                        elif key == "Houses":
                            self.addHousesForFree(dlcInfo[key], acc.SD)
                        elif key == "RandomTalents":
                            self.addRandomTalentsForFree(dlcKey, dlcInfo[key], acc.SD, acc, I.STATS,
                                                         TalentChangeOperation.GetFromDLC)
                        else:
                            err("Bad dlc key %r", key)
                    if dlcKey not in acc.db.dlcs:
                        acc.db.dlcs.append(dlcKey)
                    info("Dlc %r was applied", dlcKey)
                    isAnyWasApplied = True
                else:
                    warn("Dlc %r already applied", dlcKey)
            else:
                warn("Not found config for dlc %r in %r", dlcKey, cfg.DLCs_INFO)
        return isAnyWasApplied

    def addTournamentItems(self, iDict, acc, create_version="x", fraction='N', sex=0, **kwargs):
        self.create_version = create_version
        # ссылочку на глобальные GameData прикопаем глобально

        self.calcResourcesLimit(acc.SD, 0)
        tournamentResourceTable = {"Perl": 1000000, "Silver": 1000000, "Population": 0, "Resource1": 0,
                                   "Resource1_Rare": 0,
                                   "Resource2": 0, "Resource2_Rare": 0, "Resource3": 0, "Resource3_Rare": 0,
                                   "CWPoints_Player": 0}

        self.sell(tournamentResourceTable, acc)
        self.LordInfo.Fame = acc.SD.data['LevelToFameTable']['Levels']['Item'][-1]
        self.MarketingEventInfo = []

        if kwargs.get("create_heroes"):
            # CUSTOM: создадим всех героев с необходимыми талантами
            self.createHeroesForTournament(iDict, fraction, sex, acc)
            # Карты по умолчанию
            self.createDefaultMaps(acc.SD)

        # кладём все таланты, кроме ordinary и good
        for i in xrange(12):
            self.addTournamentTalents(acc)

        # добавляем библиотеку
        building_id = self.addNewConstruction()
        building = self.getConstructionByID(building_id)
        building.Level = 0
        building.Position.X = 9
        building.Position.Y = 32
        building.Position.Pitch = 0
        building.PersistentId = crc32('Library')
        building.WasPlacedOnScene = True

        self.Buildings.add(building)
        self.validateBuildings(acc.SD)
        self.calcResourcesLimit(acc.SD, 0)
        # дефолтные значения полей
        self.LordInfo.Reliability = USER_RELIABILITY_INITIAL
        self.LordInfo.Ratings.LordRating = acc.SD.data['HeroRatingToFameLevel']['Ratings']['Item'][-1]['rating']
        self.LordInfo.Ratings.LordPublicRating = acc.SD.data['HeroRatingToFameLevel']['Ratings']['Item'][-1]['rating']
        self.LordInfo.GuardInfo.NumberOfWins = 0.0
        self.LordInfo.ManoeuvreAllowed = True

        self.initAllTimesCounters()

        self.initInventoryTalents()

    def getHeroesExp(self):
        exp = 0
        for hero_id in self.Heroes:
            hero = self.getHeroByID(hero_id)
            exp += hero.Experience
        return exp

    def getBuildingsLvl(self):
        lvl = 0
        for buildingId in self.Buildings:
            building = self.getConstructionByID(buildingId)
            lvl += building.Level
        return lvl

    def setGeolocationalFlag(self, SD, country_code):
        if country_code:
            for countryFlag in SD.data['DBUIData']['countryFlags']['Item']:
                if countryFlag['countryCode'] == country_code:
                    self.FlagInfo.PersistentId = countryFlag['id']
                    self.FlagInfo.FlagType = FlagType.Country
                    return
        self.FlagInfo.PersistentId = SD.getDefaultFlagName()
        self.FlagInfo.FlagType = FlagType.Default

    def removeTalentsNewState(self):
        for talId in self.UserInventory:
            talent = self.getTalentByID(talId)
            if talent.IsNew:
                talent.IsNew = False

    def removeTalentFromTS(self, staticHero, staticTalent, slot_id, tsId):
        # Если герой не задан, то что искать зря?
        if 'persistentId' not in staticHero:
            return
        for hero_id in self.Heroes:
            hero = self.getHeroByID(hero_id)
            if hero.PersistentId == crc32(staticHero['persistentId']):
                # Задан номер слота, вынимаем оттуда
                if slot_id > 0 and slot_id < 37:
                    talent = self.getTalentByID(hero.TalentSets[tsId].Talents.get(slot_id))
                    if talent is not None:
                        #self.UserInventory.add(talent.getID())
                        #hero.TalentSets[tsId].Talents.remove(slot_id)
                        hero.removeTalentFromTalentSet(tsId, talent, talent.id)
                        return
                # Номер слота не задан, ищем указанный талант
                elif 'persistentId' in staticTalent:
                    for tal_id in hero.TalentSets[tsId].Talents.keys():
                        talent = self.getTalentByID(hero.TalentSets[tsId].Talents.get(tal_id))
                        if talent is not None and talent.PersistentId == crc32(staticTalent['persistentId']):
                            #self.UserInventory.add(talent.getID())
                            #hero.TalentSets[tsId].Talents.remove(tal_id)
                            hero.removeTalentFromTalentSet(tsId, talent, talent.id)
                return

    def hasGoldProductionHouse(self):
        for construction_id in self.ConstructionsKeeper:
            construction = self.getConstructionByID(construction_id)
            if construction is not None and construction.PersistentId == crc32("GoldProductionHouse"):
                return True
        return False

    # куплены ли уже все герои по акции герой со скидкой?
    def hasAllHeroesForBuyAction(self, acc, SD, config):
        for static_hero_id in SD.data['Heroes']:
            static_hero = SD.data['Heroes'][static_hero_id]
            if acc.sex == ESex.FEMALE:
                price = SD.copyPrice(static_hero['lobbyData']['CostFemale'])
            else:
                price = SD.copyPrice(static_hero['lobbyData']['CostMale'])
            if price.Silver <= config.BUY_HERO_MAX_ORIGINAL_PRICE:
                hrFr = SD.getFractions(static_hero['heroRace'])
                if acc.db.fraction in hrFr:
                    hero, hero_id = self.findHeroByCrc32(crc32(static_hero['persistentId']))
                    # Есть хоть 1 не купленный герой, акции быть!
                    if hero is None:
                        return False
        return True

    def getActiveStaticQuest(self, staticQuest):
        for questId in self.ActiveQuests:
            quest = self.getQuestByID(questId)
            if quest.persistentId == crc32(staticQuest['persistentId']):
                return quest
        return None

    def getCompletedStaticQuest(self, staticQuest):
        for questId in self.CompletedQuests:
            quest = self.getQuestByID(questId)
            if quest.persistentId == crc32(staticQuest['persistentId']):
                return quest
        return None

    def justRemoveQuest(self, staticQuest):
        for questId in self.QuestsKeeper.keys():
            quest = self.getQuestByID(questId)
            if quest.persistentId == crc32(staticQuest['persistentId']):
                if questId in self.ActiveQuests:
                    self.ActiveQuests.remove(quest)
                elif questId in self.CompletedQuests:
                    self.CompletedQuests.remove(quest)
                self.QuestsKeeper.remove(questId)
                return True
        return False

    # Add new quest from SD
    def addTalentDynamicQuestWithSD(self, printLog, acc, staticTalent):
        sd = acc.SD

        questForTalentsRoot = sd.data['DynamicQuestForTalents']
        if not questForTalentsRoot:
            return False

        # look at to exist overridenDiffMap
        overridenDifficulty = questForTalentsRoot['OverridenDifficultiesMap'][staticTalent['persistentId']] if staticTalent['persistentId'] in questForTalentsRoot['OverridenDifficultiesMap'] else None
        if overridenDifficulty:
            targetDifficulty = overridenDifficulty
            if printLog:
                print "OverridedTargetDifficulty: {}\n".format(targetDifficulty)
        else:
            targetDifficulty = questForTalentsRoot['DifficultiesMap'][staticTalent['rarity']]
            if printLog:
                print "TargetDifficulties: {}\n".format(targetDifficulty)

        return self.__generateNewTalentDynamicQuest(printLog, targetDifficulty, questForTalentsRoot, sd, staticTalent)

    def __generateNewTalentDynamicQuest(self, printLog, targetDifficulty, questForTalentsRoot, sd, staticTalent):
        questsToRandomSelect = questForTalentsRoot['QuestsGroups'][targetDifficulty]

        if not len(questsToRandomSelect):
            return False

        idx = random.choice(range(len(questsToRandomSelect)))
        selectedQuestDict = questsToRandomSelect[idx]

        addedIdsForAPossibleRevert = []
        try:
            if printLog:
                print "SelectedQuestDict: {}\n".format(selectedQuestDict)
            dynamicQuest = self.__getTalentDynamicQuestFromDict(printLog, addedIdsForAPossibleRevert, selectedQuestDict, sd, idx, targetDifficulty, staticTalent)
        except KeyError:
            for id in addedIdsForAPossibleRevert:
                self.deleteByID(id)
            err("Error while adding quest %r", selectedQuestDict)
            catch()
            return False

        self.DynamicQuests.add(dynamicQuest)
        if printLog:
            print "Added quest '{}' completed!.".format(dynamicQuest.QuestName)
        return True

    def __getTalentDynamicQuestFromDict(self, printLog, addedIdsForAPossibleRevert, questDict, sd, idx, targetDifficulty, staticTalent):
        dynamicQuestId = self.addNewDynamicQuest()
        addedIdsForAPossibleRevert.append(dynamicQuestId)
        dynamicQuest = self.getDynamicQuestByID(dynamicQuestId)
        dynamicQuest.Reason = DynamicQuestReasons.Talent
        dynamicQuest.QuestStartTime = int(time.time())
        dynamicQuest.QuestEndTime = dynamicQuest.QuestStartTime + int(questDict["Duration"])  # in seconds
        dynamicQuest.AutoAccept = True
        dynamicQuest.DynamicQuestToTalentsMetaInf.questsGroup = int(targetDifficulty)
        dynamicQuest.DynamicQuestToTalentsMetaInf.questIdx = int(idx)

        # fill objectives from custom logic
        for objectiveDict in questDict['DynamicObjectives']['Item']:
            questObjectiveId = self.addNewDynamicObjective()
            addedIdsForAPossibleRevert.append(questObjectiveId)
            questObjective = self.getDynamicObjectiveByID(questObjectiveId)
            questObjective.fillFromSD(objectiveDict, self.StatisticEventId, dynamicQuest)
            dynamicQuest.Objectives.add(questObjective)
            if printLog:
                print "Add objective '{}' completed!.\n".format(questObjective.Description)

        # add talent
        objectiveAwardId = self.addNewDynamicQuestAward()
        addedIdsForAPossibleRevert.append(objectiveAwardId)
        objectiveAward = self.getDynamicQuestAwardByID(objectiveAwardId)
        objectiveAward.QuestAwardType = DynamicQuestAwardType.Talent
        objectiveAward.AwardConditionType = DynamicQuestAwardConditionType.AfterWin  # TODO
        objectiveAward.PersistentId = crc32(staticTalent['persistentId'])
        objectiveAward.AdditionalData = '7000'
        dynamicQuest.Awards.add(objectiveAward)

        # fill awards from custom logic
        if questDict['DynamicAwards']:
            for awardDict in questDict['DynamicAwards']['Item']:
                objectiveAwardId = self.addNewDynamicQuestAward()
                addedIdsForAPossibleRevert.append(objectiveAwardId)
                objectiveAward = self.getDynamicQuestAwardByID(objectiveAwardId)
                objectiveAward.fillFromSD(awardDict, dynamicQuest, self, sd)
                dynamicQuest.Awards.add(objectiveAward)
                if printLog:
                    print "Add award '{}' completed!.\n".format(objectiveAward.QuestAwardType)

        return dynamicQuest


    def checkNewDynamicQuests(self, acc, iDict):
        for persistentId in acc.SD.DynamicQuests:
            if persistentId == "isMainSD":
                continue
            if persistentId in self.CompletedDynamicQuests:
                continue
            alreadyActive = False
            version = acc.SD.DynamicQuests[persistentId]['version']
            for questId in self.DynamicQuests:
                dynamicQuest = self.getDynamicQuestByID(questId)
                if dynamicQuest.PersistentId == persistentId:
                    alreadyActive = True
                    timeDelta = acc.getConfig().ROTATION_QUEST_LIFETIME if acc.SD.DynamicQuests[persistentId]['pullId'] else 0
                    if dynamicQuest.Version != version:
                        try:
                            dynamicQuest.update(version, acc.SD.DynamicQuests[persistentId]['questData'],
                                                self.StatisticEventId, timeDelta)
                            self.updateDynamicQuestAwards(dynamicQuest, acc.SD.DynamicQuests[persistentId]['questData'],
                                                          acc.SD)
                        except Exception:
                            catch()
                            warn("Failed to update dynamic quest %d", persistentId)
            if alreadyActive:
                continue
            pullId = acc.SD.DynamicQuests[persistentId].get("pullId", 0)
            debug("Quest %d has pullId %d",persistentId, 0 if pullId is None else pullId)
            # квесты, которые принадлежат пуллам, пропускаем, пуллы проверяются отдельно
            if pullId:
                debug("skipping quest %d, as it is in pull", persistentId)
                continue
            # Квеста нигде нет, давайте добавим
            self.tryAddDynamicQuest(persistentId, acc, iDict)

    def tryAddDynamicQuest(self, persistentId, acc, iDict, timeDelta=0):
        if persistentId in acc.SD.DynamicQuests:
            newQuest = acc.SD.DynamicQuests[persistentId]['questData']
            try:
                inGuild = acc.db.guildAuid != 0
                if self.canAcceptDynamicQuest(newQuest, acc.SD, acc.db.fraction, inGuild, acc.auid):
                    self.addDynamicQuest(acc, newQuest, persistentId,
                                         acc.SD.DynamicQuests[persistentId]['version'], iDict, timeDelta)


                    return True
            except Exception:
                err("Error while adding quest with id %r", newQuest)
                catch()
        return False

    def isQuestPullValid(self, questPull):
        return questPull["isActive"] and (questPull["startTime"] < int(time.time()) < questPull["endTime"])

    def checkDynamicQuestPulls(self, acc, iDict):
        for pullId in acc.SD.DynamicQuestPulls:
            try:
                # Уберём неактивные
                if pullId not in acc.SD.DynamicQuestPulls or not self.isQuestPullValid(acc.SD.DynamicQuestPulls[pullId]):
                    for _id, questPull in self.DynamicQuestPulls.items():
                        if questPull.PullId == pullId:
                            self.DynamicQuestPulls.remove(questPull)
                    continue
                # Проверим, есть ли текущие активные квесты из пула
                hasActiveQuestFromPull = False
                for questId, quest in self.DynamicQuests.iteritems():
                    if quest.PersistentId in acc.SD.DynamicQuestPulls[pullId]["quests"]:
                        hasActiveQuestFromPull = True
                        break
                # Пул уже выполняется, проверим следующий
                if hasActiveQuestFromPull:
                    continue

                currentPull = None
                for _id, questPull in self.DynamicQuestPulls.iteritems():
                    if questPull.PullId == pullId:
                        currentPull = questPull
                        break
                # Если не прошли сутки с пердыдущего квеста, пропускаем пул
                if currentPull and (currentPull.LastActiveQuestStartTime + acc.getConfig().ROTATION_QUEST_LIFETIME) > int(
                        time.time()):
                    continue
                if not currentPull:
                    currentPull, _id = self.newDynamicQuestPullInfo()
                    currentPull.PullId = pullId
                availableQuests = acc.SD.DynamicQuestPulls[pullId]["quests"][:]
                for questId in acc.SD.DynamicQuestPulls[pullId]["quests"]:
                    if questId in self.CompletedDynamicQuests:
                        availableQuests.remove(questId)
                # если квесты кончились или остался какой-то одни, и ротируются, то мы должны сбросить пулл
                if len(availableQuests) < 2 and acc.SD.DynamicQuestPulls[pullId]["hasRotation"]:
                    self.resestDynamicQuestsPull(acc.SD.DynamicQuestPulls[pullId]["quests"])
                    availableQuests = acc.SD.DynamicQuestPulls[pullId]["quests"][:]
                    if currentPull.LastActiveQuestId in availableQuests:
                        availableQuests.remove(currentPull.LastActiveQuestId)
                # Все пройденные квесты отмели, выдаём новый, который пользователь может принять
                goodQuestFound = False
                while not goodQuestFound and len(availableQuests):
                    randInt = self.getRandom(self.LordInfo.RandomSeed)
                    newQuestId = availableQuests[randInt % len(availableQuests)]
                    # квест плохой или не подошёл по условиям
                    if not self.tryAddDynamicQuest(newQuestId, acc, iDict, acc.getConfig().ROTATION_QUEST_LIFETIME):
                        availableQuests.remove(newQuestId)
                    else:
                        currentPull.LastActiveQuestStartTime = int(time.time())
                        currentPull.LastActiveQuestId = newQuestId
                        goodQuestFound = True
            except Exception:
                catch()

    # Сбрасываем выполненные квесты из пулла, чтобы можно было их перевыдать
    def resestDynamicQuestsPull(self, quests):
        for questId in quests:
            if questId in self.CompletedDynamicQuests:
                self.CompletedDynamicQuests.remove(questId)

    def checkLossCompleteDQObjectives(self, quest, acc):
        """
            Пытаемся найти причину, чтобы блокировать выполнение цепочки квестов
        """
        debug("checkLossCompleteDQObjectives %r", quest.generateJsonDict())
        if quest.isMainComplete():
            for objectiveId in quest.Objectives:
                objective = self.getDynamicObjectiveByID(objectiveId)
                if objective.QuestCheckType == DynamicQuestCheckType.SessionInfo:
                    if objective.SessionCondition.SessionCheckType == SessionCheckType.Loss and not quest.RepeatOnMiss:
                        self.LossDynamicQuests.append(quest.PersistentId)

        if quest.isAlternativeComplete():
            for objectiveId in quest.AlternativeObjectives:
                objective = self.getDynamicObjectiveByID(objectiveId)
                if objective.QuestCheckType == DynamicQuestCheckType.SessionInfo:
                    if objective.SessionCondition.SessionCheckType == SessionCheckType.Loss and not quest.RepeatOnMiss:
                        self.LossDynamicQuests.append(quest.PersistentId)

    def canAcceptDynamicQuest(self, staticQuest, SD, fraction, inGuild, auid):
        isTimeValid = True
        if staticQuest["QuestEndTime"] != "":
            isTimeValid = isTimeValid and int(staticQuest["QuestEndTime"]) > int(round(time.time()))
        if staticQuest["QuestStartTime"] != "":
            isTimeValid = isTimeValid and int(staticQuest["QuestStartTime"]) < int(round(time.time()))

        if not isTimeValid:
            return False


        acceptFilter = staticQuest["AcceptFilter"]

        if "LastLoginTime" in acceptFilter and int(acceptFilter["LastLoginTime"]) != 0:
            if (self.LordInfo.LastLoginTime > (int(time.time()) - int(acceptFilter["LastLoginTime"]) * 86400)) \
                    or self.LordInfo.LastLoginTime == 0:
                return False


        if "CompletedQuests" in acceptFilter:
            for questId in acceptFilter["CompletedQuests"]:
                if questId in self.LossDynamicQuests:
                    return False
                if questId not in self.CompletedDynamicQuests:
                    return False

        if "NotCompletedQuests" in acceptFilter:
            for questId in acceptFilter["NotCompletedQuests"]:
                if questId in self.CompletedDynamicQuests:
                    return False

        if "MissedQuests" in acceptFilter:
            for questId in acceptFilter["MissedQuests"]:
                if questId in self.DynamicQuests:
                    return False

        if "Donate" in acceptFilter and acceptFilter["Donate"] != "":
            if acceptFilter["Donate"].lower() == "true" and not self.Statistics.LastPaymentTime:
                return False
            if acceptFilter["Donate"].lower() == "false" and self.Statistics.LastPaymentTime:
                return False

        if "NoHero" in acceptFilter and acceptFilter["NoHero"] != "":
            persistentIds = [crc32(h) for h in acceptFilter["NoHero"].split(",")]
            for heroId, hero in self.Heroes.iteritems():
                if hero.PersistentId in persistentIds:
                    return False

        if "NoSkin" in acceptFilter and acceptFilter["NoSkin"] != "":
            persistentIds = [crc32(s) for s in acceptFilter["NoSkin"].split(",")]
            for skinId, skin in self.SkinsKeeper.iteritems():
                if skin.PersistentId in persistentIds:
                    return False

        if "NoFlag" in acceptFilter and acceptFilter["NoFlag"] != "":
            persistentIds = acceptFilter["NoFlag"].split(",")
            for persistentId in persistentIds:
                for flagId in self.Flags:
                    if persistentId == flagId:
                        return False

        if "NoBuilding" in acceptFilter and acceptFilter["NoBuilding"] != "":
            persistentIds = [crc32(h) for h in acceptFilter["NoBuilding"].split(",")]
            for constructionId, construction in self.ConstructionsKeeper.iteritems():
                if construction.PersistentId in persistentIds:
                    return False

        if "HeroesOfMinRating" in acceptFilter:
            if acceptFilter["HeroesOfMinRating"]["Items"] != "":
                persistentIds = [crc32(h) for h in acceptFilter["HeroesOfMinRating"]["Items"].split(",")]
                conditionOk = True
                for persistentId in persistentIds:
                    accepted = [h for hId, h in self.Heroes.iteritems() if
                                (h.Rating >= int(acceptFilter["HeroesOfMinRating"]["Value"])
                                 and h.PersistentId == persistentId)]
                    conditionOk = len(accepted) > 0 and conditionOk
                if not conditionOk:
                    return False
            else:
                accepted = [h for hId, h in self.Heroes.iteritems() if
                            h.Rating >= int(acceptFilter["HeroesOfMinRating"]["Value"])]
                if not accepted:
                    return False

        if "HeroesOfMaxRating" in acceptFilter and int(acceptFilter["HeroesOfMaxRating"]["Value"]) != 0:
            if acceptFilter["HeroesOfMaxRating"]["Items"] != "":
                persistentIds = [crc32(h) for h in acceptFilter["HeroesOfMaxRating"]["Items"].split(",")]
                conditionOk = True
                for persistentId in persistentIds:
                    accepted = [h for hId, h in self.Heroes.iteritems() if
                                (h.Rating >= int(acceptFilter["HeroesOfMaxRating"]["Value"])
                                 and h.PersistentId == persistentId)]
                    conditionOk = len(accepted) > 0 and conditionOk
                if conditionOk:
                    return False
            else:
                accepted = [h for hId, h in self.Heroes.iteritems() if
                            h.Rating >= int(acceptFilter["HeroesOfMaxRating"]["Value"])]
                if len(accepted):
                    return False

        if "HeroesOfForce" in acceptFilter:
            if acceptFilter["HeroesOfForce"]["Items"] != "":
                persistentIds = [crc32(h) for h in acceptFilter["HeroesOfForce"]["Items"].split(",")]
                conditionOk = True
                for persistentId in persistentIds:
                    accepted = []

                    for hId, h in self.Heroes.iteritems():
                        for tsId, talentSet in h.TalentSets.iteritems():
                            if talentSet.Force * 10.0 >= int(acceptFilter["HeroesOfForce"]["Value"]) and h.PersistentId == persistentId:
                                if h not in accepted:
                                    accepted.append(h)
                    conditionOk = len(accepted) > 0 and conditionOk
                if not conditionOk:
                    return False
            else:
                accepted = []

                for hId, h in self.Heroes.iteritems():
                    for tsId, talentSet in h.TalentSets.iteritems():
                        if talentSet.Force * 10.0 >= int(acceptFilter["HeroesOfForce"]["Value"]):
                            if h not in accepted:
                                accepted.append(h)

                if not accepted:
                    return False

        if "HeroesOfLevel" in staticQuest["AcceptFilter"]:
            if acceptFilter["HeroesOfLevel"]["Items"] != "":
                persistentIds = [crc32(h) for h in acceptFilter["HeroesOfLevel"]["Items"].split(",")]
                conditionOk = True
                for persistentId in persistentIds:
                    accepted = [h for hId, h in self.Heroes.iteritems() if
                                (SD.getHeroExpLevel(h.Experience) >= int(acceptFilter["HeroesOfLevel"]["Value"])
                                 and h.PersistentId == persistentId)]
                    conditionOk = len(accepted) > 0 and conditionOk
                if not conditionOk:
                    return False
            else:
                accepted = [h for hId, h in self.Heroes.iteritems() if
                            SD.getHeroExpLevel(h.Experience) >= int(acceptFilter["HeroesOfLevel"]["Value"])]
                if not accepted:
                    return False

        if "HasPremium" in acceptFilter and acceptFilter["HasPremium"] != "":
            if acceptFilter["HasPremium"].lower() == "true" and self.LordInfo.PremiumAccountEnd < int(time.time()):
                return False
            if acceptFilter["HasPremium"].lower() == "false" and self.LordInfo.PremiumAccountEnd > int(time.time()):
                return False

        if "LastPaymentTime" in acceptFilter and int(acceptFilter["LastPaymentTime"]) != 0:
            if int(time.time()) - acceptFilter[
                "LastPaymentTime"] * 60 * 60 * 24 < self.Statistics.LastPaymentTime or self.Statistics.LastPaymentTime == 0:
                return False

        if "BuildingOfLevel" in acceptFilter and acceptFilter["BuildingOfLevel"]["Items"] != "":
            persistentIds = [crc32(b) for b in acceptFilter["BuildingOfLevel"]["Items"].split(",")]
            hasBuilding = False
            for persistentId in persistentIds:
                for constructionId, construction in self.Buildings.iteritems():
                    if construction.Level >= acceptFilter["BuildingOfLevel"][
                        "Value"] and construction.PersistentId == persistentId:
                        hasBuilding = True
                        break
            if not hasBuilding:
                return False

        if "InGuild" in acceptFilter and acceptFilter["InGuild"] != "":
            if acceptFilter["InGuild"].lower() == "true" and not inGuild:
                return False
            if acceptFilter["InGuild"].lower() == "false" and inGuild:
                return False

        if "HasLamp" in acceptFilter and acceptFilter["HasLamp"] != "":
            if acceptFilter["HasLamp"].lower() == "true" and self.MarketingEventsInfo.LampEventInfo.dbId == "":
                return False
            if acceptFilter["HasLamp"].lower() == "false" and self.MarketingEventsInfo.LampEventInfo.dbId != "":
                return False

        if "ForAuids" in acceptFilter and len(acceptFilter["ForAuids"]):
            if auid not in acceptFilter["ForAuids"]:
                return False

        # Отдельно проверим рандомные награды: вдруг, у пользователя уже всё есть
        for award in staticQuest["Awards"]:
            if award["AwardType"] == DynamicQuestAwardType.RandomHero:
                persistentIds = award["TextData"].split(",")
                availableHeroes = persistentIds[:]
                for persistentId in persistentIds:
                    for hero_id, hero in self.Heroes.iteritems():
                        if hero.PersistentId == crc32(persistentId):
                            availableHeroes.remove(persistentId)
                if not len(availableHeroes):
                    return False
            if award["AwardType"] == DynamicQuestAwardType.RandomSkin:
                persistentIds = award["TextData"].split(",")
                availableSkins = persistentIds[:]
                for persistentId in persistentIds:
                    if self.isSkinOwned(persistentId, SD):
                        availableSkins.remove(persistentId)
                if not len(availableSkins):
                    return False

        castleLevel = SD.getFameLevel(self.LordInfo.Fame)
        return (acceptFilter["MinLordLevel"] <= castleLevel <= acceptFilter["MaxLordLevel"]
                and (fraction == acceptFilter["Faction"] or acceptFilter["Faction"] == "All"))

    def getActualTournamentQuestPersistentId(self):
        for questId in self.DynamicQuests.keys():
            dynamicQuest = self.getDynamicQuestByID(questId)
            if dynamicQuest.PersistentId == "isMainSD":
                continue
            if dynamicQuest.PersistentId in self.CompletedDynamicQuests:
                continue
            if dynamicQuest.validateLifetime() and not dynamicQuest.isComplete():
                for _id, cond in dynamicQuest.PreConditions.iteritems():
                    debug("getActualTournamentQuestPersitentId dynamicQuest.PersistentId=%r PreCondition (PreConditionType=%r , TournamentMapType=%r)",
                          dynamicQuest.PersistentId, enum2String(DynamicQuestPreConditionType, cond.PreConditionType), cond.TournamentMapType)
                    if cond.PreConditionType == DynamicQuestPreConditionType.Tournament:
                        sDepTournamentQuest = "-1"
                        if dynamicQuest.DependedTournamentQuests:
                            sDepTournamentQuest = ",".join([str(x) for x in dynamicQuest.DependedTournamentQuests.keys()])
                        else:
                            sDepTournamentQuest = str(dynamicQuest.PersistentId)

                        return dynamicQuest.PersistentId, sDepTournamentQuest
        return -1, "-1"

    def canActualTournamentMapForQuest(self, acc, eventMap):
        debug("canActualTournamentMapForQuest acc.auid=%r,  eventMap=%r)", acc.auid, eventMap)
        for questId in self.DynamicQuests.keys():
            dynamicQuest = self.getDynamicQuestByID(questId)
            if dynamicQuest.PersistentId == "isMainSD":
                continue
            if dynamicQuest.PersistentId in self.CompletedDynamicQuests:
                continue
            if dynamicQuest.validateLifetime() and not dynamicQuest.isComplete():
                for _id, cond in dynamicQuest.PreConditions.iteritems():
                    debug("canActualTournamentMapForQuest acc.auid=%r dynamicQuest.PersistentId=%r PreCondition (PreConditionType=%r , TournamentMapType=%r)", acc.auid,
                          dynamicQuest.PersistentId, enum2String(DynamicQuestPreConditionType, cond.PreConditionType), cond.TournamentMapType)
                    debug("canActualTournamentMapForQuest %r == %r and %r == %r",cond.PreConditionType, DynamicQuestPreConditionType.Tournament,cond.TournamentMapType, eventMap)
                    if cond.PreConditionType == DynamicQuestPreConditionType.Tournament and cond.TournamentMapType == eventMap:
                        return True

        return False


    def setDynamicQuestPreConditions(self, dynamicQuest, acc, iDict):
        '''
         установка preconditions
        '''
        for _id, cond in dynamicQuest.PreConditions.iteritems():
            debug("setDynamicQuestPreConditions dynamicQuest.PersistentId=%r PreCondition (PreConditionType=%r , TournamentMapType=%r)",
                  dynamicQuest.PersistentId, enum2String(DynamicQuestPreConditionType, cond.PreConditionType), cond.TournamentMapType)
            if cond.PreConditionType == DynamicQuestPreConditionType.Tournament:
                if cond.TournamentMapType in self.LordInfo.DisabledMaps:
                    self.LordInfo.DisabledMaps.remove(cond.TournamentMapType)
                self.updateMap(MapType.CTF, cond.TournamentMapType, True, 0, 0, True)
                #self.calcEventInfo( iDict.Config.eventMaps, acc )
                #self.calcBanEventInfo(acc, iDict.Config.eventMapsForBan, iDict.Config.eventMaps )

    def resetDynamicQuestPreConditions(self, dynamicQuest, acc, iDict, tournamentQuests):
        '''
         сброс preconditions
        '''
        for _id, cond in dynamicQuest.PreConditions.iteritems():
            debug("resetDynamicQuestPreConditions dynamicQuest.PersistentId=%r PreCondition (PreConditionType=%r , TournamentMapType=%r)",
                  dynamicQuest.PersistentId, enum2String(DynamicQuestPreConditionType, cond.PreConditionType), cond.TournamentMapType)
            if cond.PreConditionType == DynamicQuestPreConditionType.Tournament and cond.TournamentMapType not in tournamentQuests:
                self.calcEventInfo( iDict.Config.eventMaps, acc )
                self.calcBanEventInfo(acc, iDict.Config.eventMapsForBan, iDict.Config.eventMaps )

    def addDynamicQuest(self, acc, staticQuestInfo, persistentId, version, iDict, timeDelta=0):
        addedIds = []
        dynamicQuestId = self.addNewDynamicQuest()
        dynamicQuest = self.getDynamicQuestByID(dynamicQuestId)
        addedIds.append(dynamicQuestId)
        try:
            dynamicQuest.PersistentId = persistentId
            dynamicQuest.Version = version
            dynamicQuest.fill(staticQuestInfo, timeDelta)

            for objective in staticQuestInfo["QuestData"]:
                questObjectiveId = self.addNewDynamicObjective()
                addedIds.append(questObjectiveId)
                questObjective = self.getDynamicObjectiveByID(questObjectiveId)
                questObjective.fill(objective, self.StatisticEventId, dynamicQuest)
                dynamicQuest.Objectives.add(questObjective)

            if "AlternativeQuestData" in staticQuestInfo:
                for objective in staticQuestInfo["AlternativeQuestData"]:
                    questObjectiveId = self.addNewDynamicObjective()
                    addedIds.append(questObjectiveId)
                    questObjective = self.getDynamicObjectiveByID(questObjectiveId)
                    questObjective.fill(objective, self.StatisticEventId, dynamicQuest)
                    dynamicQuest.AlternativeObjectives.add(questObjective)

            for award in staticQuestInfo["Awards"]:
                objectiveAwardId = self.addNewDynamicQuestAward()
                addedIds.append(objectiveAwardId)
                objectiveAward = self.getDynamicQuestAwardByID(objectiveAwardId)
                objectiveAward.fill(award, dynamicQuest, self, acc.SD)
                dynamicQuest.Awards.add(objectiveAward)

            if "AlternativeAwards" in staticQuestInfo:
                for award in staticQuestInfo["AlternativeAwards"]:
                    objectiveAwardId = self.addNewDynamicQuestAward()
                    addedIds.append(objectiveAwardId)
                    objectiveAward = self.getDynamicQuestAwardByID(objectiveAwardId)
                    objectiveAward.fill(award, dynamicQuest, self, acc.SD)
                    dynamicQuest.AlternativeAwards.add(objectiveAward)

            if "PreConditions" in staticQuestInfo:
                for cond in staticQuestInfo["PreConditions"]:
                    condId = self.addNewPreCondition()
                    addedIds.append(condId)
                    condition = self.getPreConditionByID(condId)
                    condition.fill(cond, dynamicQuest, self, acc.SD)
                    dynamicQuest.PreConditions.add(condition)
                    debug("fill TournamentMapType=%r cond[TournamentMapType] = %r ", condition.TournamentMapType, cond["TournamentMapType"] )

            self.setDynamicQuestPreConditions(dynamicQuest, acc, iDict)
        except Exception:
            for id in addedIds:
                self.deleteByID(id)
            err("Error while adding quest %r", staticQuestInfo)
            catch()
            return None

        self.DynamicQuests.add(dynamicQuest)
        if acc.party_id:
            tournamentDynQuestId, dependedTournamentQuests = self.getActualTournamentQuestPersistentId()
            iDict.PS.updatePartyTournamentInfo(acc.auid, acc.party_id, tournamentDynQuestId, dependedTournamentQuests, iDict.WS.onDummyResponseCallback)

        return dynamicQuest

    def updateDynamicQuestAwards(self, dynamicQuest, questData, SD):
        """ Награды удаляем и заполняем заново, их можно менять, пока пользователь ещё не выполнил квест """
        for _id, objectiveAward in dynamicQuest.Awards.items():
            dynamicQuest.Awards.remove(objectiveAward)
        for award in questData["Awards"]:
            objectiveAwardId = self.addNewDynamicQuestAward()
            objectiveAward = self.getDynamicQuestAwardByID(objectiveAwardId)
            objectiveAward.fill(award, dynamicQuest, self, SD)
            dynamicQuest.Awards.add(objectiveAward)
        for award in questData["AlternativeAwards"]:
            objectiveAwardId = self.addNewDynamicQuestAward()
            objectiveAward = self.getDynamicQuestAwardByID(objectiveAwardId)
            objectiveAward.fill(award, dynamicQuest, self, SD)
            dynamicQuest.AlternativeAwards.add(objectiveAward)

    def getTournamentsMapFromActiveQuests(self):
        tournamentQuests = []
        for questId in self.DynamicQuests.keys():
            quest = self.getDynamicQuestByID(questId)
            if quest.validateLifetime() and quest.QuestState in (QuestState.New,  QuestState.InProgress):
                for _id, cond in quest.PreConditions.iteritems():
                    if cond.PreConditionType == DynamicQuestPreConditionType.Tournament:
                        if cond.TournamentMapType not in tournamentQuests:
                            tournamentQuests.append(cond.TournamentMapType)
        return tournamentQuests

    def validateDynamicQuests(self, acc, iDict):
        tournamentQuests = self.getTournamentsMapFromActiveQuests()

        for questId in self.DynamicQuests.keys():
            quest = self.getDynamicQuestByID(questId)
            if not quest.validateLifetime():
                # Надо проверить, забрал ли человек свою награду
                self.checkDynamicQuestToGiveAward(quest, acc, iDict)
                # теперь добавим награды всем квестам, которые скипались
                self.checkDynamicQuestToGiveAward(quest, acc, iDict, True )
                self.removeDynamicQuest(quest, acc, iDict, tournamentQuests)

    # Проверяем каждый раз при входе в игру,
    # на случай если квест был удалён с сервера ГМ-ом или есть ли он в
    # SD (если он является DynamicQuestToTalent
    def validateDynamicQuestsActuality(self, acc, iDict):
        # Для заходов через биллинг или ГМтулз мы квесты не проверяем
        tournamentQuests = self.getTournamentsMapFromActiveQuests()
        if acc.SD.DynamicQuests.get("isMainSD"):
            return
        for questId in self.DynamicQuests.keys():
            quest = self.getDynamicQuestByID(questId)
            # talent
            if quest.Reason == DynamicQuestReasons.Talent:
                self.validateActuallyForDQToTal(quest, acc, iDict)
            # default
            else:
                if quest.PersistentId not in acc.SD.DynamicQuests:
                    self.removeDynamicQuest(quest, acc, iDict, tournamentQuests)

    def validateActuallyForDQToTal(self, quest, acc, iDict):
        questsToTalentsGroups = acc.SD.data['DynamicQuestForTalents']['QuestsGroups']
        targetQuestsGroup = questsToTalentsGroups[str(quest.DynamicQuestToTalentsMetaInf.questsGroup)] if str(quest.DynamicQuestToTalentsMetaInf.questsGroup) in questsToTalentsGroups else None
        # delete if no group OR bad index
        if not targetQuestsGroup or not index_exists(targetQuestsGroup, quest.DynamicQuestToTalentsMetaInf.questIdx):
            self.removeDynamicQuest(quest, acc, iDict, self.getTournamentsMapFromActiveQuests())

    def checkOwnedDynamicQuestAwards(self, awards, acc):
        for awardId in awards.keys():
            award = self.getDynamicQuestAwardByID(awardId)
            if award.QuestAwardType == DynamicQuestAwardType.Hero:
                staticHero, hero, error = self.canHireHero(award.PersistentId, acc)
                if error != "":
                    return False
            elif award.QuestAwardType == DynamicQuestAwardType.Skin:
                if self.isSkinOwned(award.PersistentId, acc.SD):
                    return False
            elif award.QuestAwardType == DynamicQuestAwardType.Construction:
                staticConstruction = acc.SD.getStaticConstructionByPersistentId(award.PersistentId)
                if not self.canPlaceBuilding(staticConstruction, acc.SD):
                    return False
            elif award.QuestAwardType == DynamicQuestAwardType.CustomFlag:
                for flagId in self.Flags:
                    if award.DbId == flagId:
                        return False
        return True

    def removeDynamicQuest(self, quest, acc, iDict, tournamentQuests):
        debug("removeDynamicQuest: tournamentQuests=%r CompletedDynamicQuests=%r, LossDynamicQuests=%r", tournamentQuests, self.CompletedDynamicQuests.generateJsonDict(), self.LossDynamicQuests.generateJsonDict())
        if quest.isComplete():
            self.checkLossCompleteDQObjectives(quest, acc)

        for objectiveId in quest.Objectives.keys():
            objective = self.getDynamicObjectiveByID(objectiveId)
            quest.Objectives.remove(objective)
        for objectiveId in quest.AlternativeObjectives.keys():
            objective = self.getDynamicObjectiveByID(objectiveId)
            quest.AlternativeObjectives.remove(objective)
        for awardId in quest.Awards.keys():
            award = self.getDynamicQuestAwardByID(awardId)
            quest.Awards.remove(award)
        for awardId in quest.AlternativeAwards.keys():
            award = self.getDynamicQuestAwardByID(awardId)
            quest.AlternativeAwards.remove(award)

        self.resetDynamicQuestPreConditions(quest, acc, iDict, tournamentQuests)
        for condId in quest.PreConditions.keys():
            cond = self.getPreConditionByID(condId)
            quest.PreConditions.remove(cond)

        if getattr(quest, "deleteFromCompleted", False):
            if quest.PersistentId in self.CompletedDynamicQuests:
                self.CompletedDynamicQuests.remove(quest.PersistentId)
            if quest.PersistentId in self.LossDynamicQuests:
                self.LossDynamicQuests.remove(quest.PersistentId)

        debug("After removeDynamicQuest: tournamentQuests=%r CompletedDynamicQuests=%r, LossDynamicQuests=%r", tournamentQuests, self.CompletedDynamicQuests.generateJsonDict(), self.LossDynamicQuests.generateJsonDict())
        self.DynamicQuests.remove(quest)

    # ----------------------------------------------------
    # Операции с квестами по внутрисессионной статистике
    # ----------------------------------------------------

    # Обновление заданий, связанных с накоплением сессионной статистики.
    def checkSessionResultObjective(self, objective, fightData):
        stats = self.Statistics.LastSessionResults
        if not objective.checkModeConditions(self.Statistics.LastSessionInfo, fightData):
            return

        # Типы называются так же, как и поля в структуре SessionResults, так что мы должны автоматически вынимать нужное значение
        val = stats.get(objective.SessionCondition.CollectingType) or 0
        objective.CurrentValue += min(val, objective.SessionCondition.IncrementPerBattle)
        if objective.CurrentValue >= objective.SessionCondition.TotalValue:
            objective.IsCompleted = True

    # Обновление заданий, связанных с победой в конкретном режиме или конкретным героем.
    def checkSessionInfoObjective(self, objective, fightData):
        if not objective.checkModeConditions(self.Statistics.LastSessionInfo, fightData):
            return

        objective.CurrentValue += 1
        if objective.CurrentValue >= objective.SessionCondition.TotalValue:
            objective.IsCompleted = True

    # Обновление "сессионных" заданий (должно выполняться после каждого боя)
    def tryCompleteAfterSessionObjectives(self, fightData):
        for questId in self.DynamicQuests:
            quest = self.getDynamicQuestByID(questId)
            # Готовые квесты и проверять нечего
            if quest.QuestState == QuestState.Complete:
                continue
            canComplete = True
            canCompleteAlternative = True
            for objectiveId in quest.Objectives:
                objective = self.getDynamicObjectiveByID(objectiveId)
                if objective.QuestCheckType == DynamicQuestCheckType.SessionResult:
                    self.checkSessionResultObjective(objective, fightData)
                elif objective.QuestCheckType == DynamicQuestCheckType.SessionInfo:
                    self.checkSessionInfoObjective(objective, fightData)
                canComplete = canComplete and objective.IsCompleted
            for objectiveId in quest.AlternativeObjectives:
                objective = self.getDynamicObjectiveByID(objectiveId)
                if objective.QuestCheckType == DynamicQuestCheckType.SessionResult:
                    self.checkSessionResultObjective(objective, fightData)
                elif objective.QuestCheckType == DynamicQuestCheckType.SessionInfo:
                    self.checkSessionInfoObjective(objective, fightData)
                canCompleteAlternative = canCompleteAlternative and objective.IsCompleted
            # Надо проверить, были ли вообще альтернативные задания
            if (canComplete and len(quest.Objectives)) or (canCompleteAlternative and len(quest.AlternativeObjectives)):
                quest.QuestState = QuestState.Complete

    # ----------------------------------------------------
    # Операции с квестами по конкретным зданиям, скинам..
    # ----------------------------------------------------

    def checkStatisticsDynamicQuests(self, stEvent):
        for questId, quest in self.DynamicQuests.iteritems():
            # Готовые квесты и проверять нечего
            if quest.QuestState == QuestState.Complete:
                continue
            canComplete = True
            canCompleteAlternative = True
            for objectiveId, objective in quest.Objectives.iteritems():
                if objective.QuestCheckType == DynamicQuestCheckType.ModelData:
                    self.tryCompleteMDObjective(objective, stEvent)
                canComplete = canComplete and objective.IsCompleted
            for objectiveId, objective in quest.AlternativeObjectives.iteritems():
                if objective.QuestCheckType == DynamicQuestCheckType.ModelData:
                    self.tryCompleteMDObjective(objective, stEvent)
                canCompleteAlternative = canCompleteAlternative and objective.IsCompleted
            # Надо проверить, были ли вообще альтернативные задания
            if (canComplete and len(quest.Objectives)) or (canCompleteAlternative and len(quest.AlternativeObjectives)):
                quest.QuestState = QuestState.Complete

    # Проверка квестов типа "Построй 10 цветочков", "Сделай 20 перековок" и т.д..
    def tryCompleteMDObjective(self, objective, evt):
        if evt.time < objective.ModelDataCondition.LastEventId:
            objective.ModelDataCondition.LastEventId = self.StatisticEventId
            return

        mdCond = objective.ModelDataCondition
        # Достигните уровня Х героем У
        if mdCond.TypeToCollect == ModelDataConditionType.HeroLevel and evt.actionType == StatisticEventType.HERO_LEVEL:
            if ((len(mdCond.PersistentIds) == 0 or evt.description in mdCond.PersistentIds)
                and evt.value >= mdCond.TotalValue):
                objective.CurrentValue = mdCond.TotalValue
        # Поднимите уровень герою У
        if mdCond.TypeToCollect == ModelDataConditionType.HeroLevelUp and evt.actionType == StatisticEventType.HERO_LEVEL:
            if len(mdCond.PersistentIds) == 0 or evt.description in mdCond.PersistentIds:
                objective.CurrentValue = mdCond.TotalValue
        # Достигните мощи Х героем У
        elif mdCond.TypeToCollect == ModelDataConditionType.HeroForce and evt.actionType == StatisticEventType.HERO_FORCE:
            if ((len(mdCond.PersistentIds) == 0 or evt.description in mdCond.PersistentIds)
                and evt.value >= mdCond.TotalValue):
                objective.CurrentValue = mdCond.TotalValue
        # Поднимите мощь герою У
        elif mdCond.TypeToCollect == ModelDataConditionType.HeroForceUp and evt.actionType == StatisticEventType.HERO_FORCE:
            if ((len(mdCond.PersistentIds) == 0 or evt.description in mdCond.PersistentIds)
                and evt.valueChange > 0):
                objective.CurrentValue = mdCond.TotalValue
        # Достигните рейтинга Х героем У
        elif mdCond.TypeToCollect == ModelDataConditionType.HeroRating and evt.actionType == StatisticEventType.HERO_RATING:
            if ((len(mdCond.PersistentIds) == 0 or evt.description in mdCond.PersistentIds)
                and evt.value >= mdCond.TotalValue):
                objective.CurrentValue = mdCond.TotalValue
        # Поднять рейтинг героем У
        elif mdCond.TypeToCollect == ModelDataConditionType.HeroRatingUp and evt.actionType == StatisticEventType.HERO_RATING:
            if ((len(mdCond.PersistentIds) == 0 or evt.description in mdCond.PersistentIds)
                and evt.valueChange > 0):
                objective.CurrentValue = mdCond.TotalValue
        # Сделать Х талантов в кузнице
        elif mdCond.TypeToCollect == ModelDataConditionType.ForgeTalent and evt.actionType == StatisticEventType.TALENT_FINISH:
            objective.CurrentValue += evt.value
        # Накопить Х единиц ресурса У
        elif mdCond.TypeToCollect == ModelDataConditionType.CollectResources:
            if (evt.actionType in [StatisticEventType.SESSION_RESOURCE, StatisticEventType.GUILD_SESSION_RESOURCE,
                                   StatisticEventType.PRODUCTION_FINISH]
                and evt.description in mdCond.PersistentIds):
                objective.CurrentValue += evt.value
        # Накопить Х единиц ресурса У
        elif mdCond.TypeToCollect == ModelDataConditionType.CollectCWPointsGuildFight:
            if (
                    evt.actionType == StatisticEventType.GUILD_SESSION_RESOURCE and evt.description in mdCond.PersistentIds):
                objective.CurrentValue += evt.value
        # Посроить уровень Х у здания У
        elif mdCond.TypeToCollect == ModelDataConditionType.BuildingLevel and evt.actionType == StatisticEventType.BUILDING_LEVEL:
            if ((len(mdCond.PersistentIds) == 0 or evt.description in mdCond.PersistentIds)
                and evt.value >= mdCond.TotalValue):
                objective.CurrentValue = mdCond.TotalValue
        # Сделать Х переково
        elif mdCond.TypeToCollect == ModelDataConditionType.MakeReforges and evt.actionType == StatisticEventType.TALENT_REFORGE:
            objective.CurrentValue += evt.value

        if objective.CurrentValue >= mdCond.TotalValue:
            objective.IsCompleted = True
        else:
            objective.IsCompleted = False

        mdCond.LastEventId = self.StatisticEventId

    # ----------------------------------------------------
    # Операции с квестами по сдаче ресурсов
    # ----------------------------------------------------

    # Узнать цену квестов на сдачу ресурсов
    def getDynamicObjectivePrice(self, objective):
        # resTable = self.createResourcesTable() - далее эта таблица используется как цена с жестко обозначенным набором
        # мемберов-полей, а createResourcesTable создает пустой дикт, который не гарантирует наличие всех ресурсов в нем
        resTable = StaticData.emptyPrice()
        if objective.InstantCondition.ResourceType == CastleResources.Resource1:
            resTable.Resource1 = objective.InstantCondition.TotalValue
        if objective.InstantCondition.ResourceType == CastleResources.Resource1_Rare:
            resTable.Resource1_Rare = objective.InstantCondition.TotalValue
        if objective.InstantCondition.ResourceType == CastleResources.Resource2:
            resTable.Resource2 = objective.InstantCondition.TotalValue
        if objective.InstantCondition.ResourceType == CastleResources.Resource2_Rare:
            resTable.Resource2_Rare = objective.InstantCondition.TotalValue
        if objective.InstantCondition.ResourceType == CastleResources.Resource3:
            resTable.Resource3 = objective.InstantCondition.TotalValue
        if objective.InstantCondition.ResourceType == CastleResources.Resource3_Rare:
            resTable.Resource3_Rare = objective.InstantCondition.TotalValue
        if objective.InstantCondition.ResourceType == CastleResources.Silver:
            resTable.Silver = objective.InstantCondition.TotalValue
        if objective.InstantCondition.ResourceType == CastleResources.Perl:
            resTable.Perl = objective.InstantCondition.TotalValue
        if objective.InstantCondition.ResourceType == CastleResources.RedPerl:
            resTable.RedPerl = objective.InstantCondition.TotalValue
        if objective.InstantCondition.ResourceType == CastleResources.Gold:
            resTable.Gold = objective.InstantCondition.TotalValue
        if objective.InstantCondition.ResourceType == CastleResources.Shard:
            resTable.Shard = objective.InstantCondition.TotalValue
        if objective.InstantCondition.ResourceType == CastleResources.Custom:
            resTable.Currencies[objective.InstantCondition.CustomCurrencyId] = objective.InstantCondition.TotalValue
        return resTable

    # ----------------------------------------------------

    def applyDynamicQuestAward(self, quest, award, acc, iDict, STATS, condAwardType=DynamicQuestAwardConditionType.AfterWin):
        questName = str(quest.PersistentId)
        try:
            if condAwardType == award.AwardConditionType:
                if award.QuestAwardType == DynamicQuestAwardType.PremiumAcc:
                    self.addPremiumForFree(award.Value, acc)
                elif award.QuestAwardType == DynamicQuestAwardType.Gold:
                    iDict.BILL.replenish(acc.auid, award.Value, "Gold for DynamicQuest", None)
                elif award.QuestAwardType == DynamicQuestAwardType.Resource1:
                    self.addResourcesForFree({"Resource1": award.Value})
                    STATS.addResourcesChange(acc.auid, True, ResourceChangeItem.DynamicQuestReward,
                                             "QuestId=%r)" % questName,
                                             acc.model.createResourcesTable(Resource1=award.Value), acc.model.Resources)
                elif award.QuestAwardType == DynamicQuestAwardType.Resource2:
                    self.addResourcesForFree({"Resource2": award.Value})
                    STATS.addResourcesChange(acc.auid, True, ResourceChangeItem.DynamicQuestReward,
                                             "QuestId=%r)" % questName,
                                             acc.model.createResourcesTable(Resource2=award.Value), acc.model.Resources)
                elif award.QuestAwardType == DynamicQuestAwardType.Resource3:
                    self.addResourcesForFree({"Resource3": award.Value})
                    STATS.addResourcesChange(acc.auid, True, ResourceChangeItem.DynamicQuestReward,
                                             "QuestId=%r)" % questName,
                                             acc.model.createResourcesTable(Resource3=award.Value), acc.model.Resources)
                elif award.QuestAwardType == DynamicQuestAwardType.Silver:
                    self.addResourcesForFree({"Silver": award.Value})
                    STATS.addResourcesChange(acc.auid, True, ResourceChangeItem.DynamicQuestReward,
                                             "QuestId=%r)" % questName,
                                             acc.model.createResourcesTable(Silver=award.Value), acc.model.Resources)
                elif award.QuestAwardType == DynamicQuestAwardType.Perl:
                    self.addResourcesForFree({"Perl": award.Value})
                    STATS.addResourcesChange(acc.auid, True, ResourceChangeItem.DynamicQuestReward,
                                             "QuestId=%r)" % questName,
                                             acc.model.createResourcesTable(Perl=award.Value), acc.model.Resources)
                elif award.QuestAwardType == DynamicQuestAwardType.RedPerl:
                    self.addResourcesForFree({"RedPerl": award.Value})
                    STATS.addResourcesChange(acc.auid, True, ResourceChangeItem.DynamicQuestReward,
                                             "QuestId=%r)" % questName,
                                             acc.model.createResourcesTable(RedPerl=award.Value), acc.model.Resources)
                elif award.QuestAwardType == DynamicQuestAwardType.Shard:
                    self.addResourcesForFree({"Shard": award.Value})
                    STATS.addResourcesChange(acc.auid, True, ResourceChangeItem.DynamicQuestReward,
                                             "QuestId=%r)" % questName,
                                             acc.model.createResourcesTable(Shard=award.Value), acc.model.Resources)
                elif award.QuestAwardType == DynamicQuestAwardType.CustomCurrency:
                    self.addResourcesForFree({"Currencies": {award.CustomCurrencyId: award.Value}})
                    STATS.addResourcesChange(acc.auid, True, ResourceChangeItem.DynamicQuestReward,
                                             "QuestId=%r)" % questName,
                                             acc.model.createResourcesTable(Currencies={award.CustomCurrencyId: award.Value}),
                                             acc.model.Resources)

                elif award.QuestAwardType in [DynamicQuestAwardType.Talent, DynamicQuestAwardType.RandomTalent,
                                              DynamicQuestAwardType.RandomTalentFromPool]:
                    staticTalent = acc.SD.getStaticTalentByTalentId(award.PersistentId)
                    self.addTalentsForFree(questName,
                                           [staticTalent["persistentId"] + ':' + str(toint(award.AdditionalData, default=0))],
                                           acc, iDict.STATS, TalentChangeOperation.GetFromQuest, pointsInArgs=True)
                elif award.QuestAwardType in [DynamicQuestAwardType.Skin, DynamicQuestAwardType.RandomSkin]:
                    staticSkin = acc.SD.getStaticSkinByPersistentId(award.PersistentId)
                    self.addSkinsForFree([staticSkin["persistentId"]], acc)
                elif award.QuestAwardType == DynamicQuestAwardType.Construction:
                    staticConstruction = acc.SD.getStaticConstructionByPersistentId(award.PersistentId)
                    self.addHousesForFree([staticConstruction["persistentId"]], acc.SD)
                elif award.QuestAwardType == DynamicQuestAwardType.Experience:
                    self.addFame(award.Value, acc, acc.SD, STATS)
                elif award.QuestAwardType == DynamicQuestAwardType.Lamp:
                    self.replaceGoldLampEvent(award.Lamp.DbId, award.Lamp.Bonus, award.Lamp.Transactions,
                                              award.Lamp.Duration, False)
                    rune = self.getGoldLampType(acc.SD)
                    STATS.addLampRoll(acc.db.auid, rune, RuneRollSource.DynamicQuest)
                elif award.QuestAwardType == DynamicQuestAwardType.UpgradeHeroTalentsEvent:
                    oldUsesLeft = acc.model.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft
                    acc.model.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft += award.Value
                    STATS.addLampRoll(acc.db.auid, self.getUpgHeroLampType(), RuneRollSource.DynamicQuestUpgHeroTal, runescountold=oldUsesLeft, runescountnew=acc.model.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft)
                elif award.QuestAwardType == DynamicQuestAwardType.CustomFlag:
                    customFlag = acc.SD.getCustomFlagById(award.DbId)
                    if customFlag and "id" in customFlag:
                        acc.model.Flags.append(customFlag['id'])
                    else:
                        warn("Custom flag %r was not found", award.Value)
                elif award.QuestAwardType in [DynamicQuestAwardType.Hero, DynamicQuestAwardType.RandomHero]:
                    staticHero, hero, error = self.canHireHero(award.PersistentId, acc)
                    if error == "":
                        self.hireHero(award.PersistentId, acc.sex, iDict.WS, acc, iDict)
                    else:
                        warn("Can't give hero as dynamic quest award: %r", error)
                elif award.QuestAwardType == DynamicQuestAwardType.FractionChange:
                    acc.db.fractionChanged -= 1
                elif award.QuestAwardType == DynamicQuestAwardType.NicknameChange:
                    acc.db.nickChanged -= 1
                elif award.QuestAwardType == DynamicQuestAwardType.HeroExperience:
                    hero, heroId = self.findHeroByCrc32(award.PersistentId)
                    hero.changeExperience(award.Value, acc.model, iDict.WS, acc, iDict)
                elif award.QuestAwardType == DynamicQuestAwardType.HeroStatsReset:
                    hero, heroId = self.findHeroByCrc32(award.PersistentId)
                    for tsId in hero.TalentSets.keys():
                        hero.resetHeroStatPoints(acc, tsId)
                        hero.CalcForce(acc.model, iDict.WS, acc, tsId)
                elif award.QuestAwardType == DynamicQuestAwardType.AllHeroStatsReset:
                    for heroId in self.Heroes:
                        hero = self.getHeroByID(heroId)
                        for tsId in hero.TalentSets.keys():
                            hero.resetHeroStatPoints(acc, tsId)
                            hero.CalcForce(acc.model, iDict.WS, acc, tsId)
                elif award.QuestAwardType == DynamicQuestAwardType.Quest:
                    self.tryAddAwardDynamicQuest(acc, award.PersistentId, iDict)
                elif award.QuestAwardType == DynamicQuestAwardType.AlreadyCompletedQuest:
                    persistentIds = award.DbId.split(",")
                    for id in persistentIds:
                        if int(id) in self.CompletedDynamicQuests:
                            self.CompletedDynamicQuests.remove(int(id))
                        if int(id) in self.LossDynamicQuests:
                            self.LossDynamicQuests.remove(int(id))

                    quest.deleteFromCompleted = questName in persistentIds
                    self.tryAddAwardDynamicQuest(acc, award.PersistentId, iDict)
                elif award.QuestAwardType == DynamicQuestAwardType.Lootbox:
                    lootbox_persistent_id = award.DbId
                    lootboxes_count = award.Value
                    for i in range(lootboxes_count):
                        isOk, _ = self.addLootbox(crc32(lootbox_persistent_id), acc)
                        if not isOk:
                            err('bad lootbox_persistent_id {} in DynamicQuestAward. DynamicQuestName: {}'.format(lootbox_persistent_id, quest.QuestName.encode('utf-8')))
                else:
                    warn("Illegal dynamic quest award type")
            else:
                debug("Illegal dynamic quest award condition type")
        except Exception:
            catch()
            err("Wrong award value format for dynamic quest award!")

    def checkDynamicQuestToGiveAward(self, quest, acc, I, isSkip=False):
        if quest.QuestState == QuestState.Complete and not isSkip:

            if quest.isMainComplete():
                for awardId in quest.Awards:
                    award = self.getDynamicQuestAwardByID(awardId)
                    self.applyDynamicQuestAward(quest, award, acc, I, I.STATS)
            if quest.isAlternativeComplete():
                for awardId in quest.AlternativeAwards:
                    award = self.getDynamicQuestAwardByID(awardId)
                    self.applyDynamicQuestAward(quest, award, acc, I, I.STATS)
            if not quest.RepeatOnMiss:
                self.CompletedDynamicQuests.append(quest.PersistentId)
        elif isSkip and (quest.QuestState != QuestState.Complete): # скипнутый квест
                for awardId in itertools.chain(quest.Awards, quest.AlternativeAwards):
                    award = self.getDynamicQuestAwardByID(awardId)
                    self.applyDynamicQuestAward(quest, award, acc, I, I.STATS, DynamicQuestAwardConditionType.AfterMiss)

        self.sendCompletedDynamicQuestStatistics(quest, acc, I)

    def sendCompletedDynamicQuestStatistics(self, quest, acc, I):
        isTournamentQuest = False
        for _id, cond in quest.PreConditions.iteritems():
            if cond.PreConditionType == DynamicQuestPreConditionType.Tournament:
                isTournamentQuest = True
                break
        if isTournamentQuest:
            state = TournamentQuestResult.Loss if quest.isAlternativeComplete() else TournamentQuestResult.Win
            I.STATS.addTournamentQuestChange(acc.auid, quest.PersistentId, quest.QuestName, state, quest.isAlternativeComplete())
        else:
            I.STATS.addDynamicQuestChange(acc.auid, quest.PersistentId, quest.QuestName, 2, quest.isAlternativeComplete())


    def tryAddAwardDynamicQuest(self, acc, persistentId, iDict):
        for questId in self.DynamicQuests:
            dynamicQuest = self.getDynamicQuestByID(questId)
            if dynamicQuest.PersistentId == persistentId:
                err("applyDynamicQuestAward: player already has quest %d!", persistentId)
                return


        if persistentId in acc.SD.DynamicQuests:
            try:
                self.addDynamicQuest(acc, acc.SD.DynamicQuests[persistentId]['questData'], persistentId,
                                     acc.SD.DynamicQuests[persistentId]['version'], iDict)
            except Exception:
                err("Error while adding quest %r", acc.SD.DynamicQuests[persistentId])
                catch()
        else:
            err("Can't find next quest for dynamic quest award!")

    def getTransmutationBuilding(self, SD):
        for constrId in self.Buildings:
            construction = self.getConstructionByID(constrId)
            staticConstruction = SD.getStaticConstruction(construction)
            if staticConstruction and staticConstruction['classType'] == "TransmutationBuilding":
                return construction

    def canReforge(self, SD, staticTalent, transmutationBuilding):
        if transmutationBuilding:
            staticConstruction = SD.getStaticConstruction(transmutationBuilding)
            if staticTalent["rarity"] in ["exclusive", "outstanding"]:
                return transmutationBuilding.Level >= staticConstruction["requiredLeveForReforgingExclusiveTalents"]
            if staticTalent["rarity"] in ["excellent", "magnificent"]:
                return transmutationBuilding.Level >= staticConstruction["requiredLeveForReforging"]

        return False

    def canReforgeUpgrade(self, SD, staticTalent, transmutationBuilding):
        if transmutationBuilding:
            staticConstruction = SD.getStaticConstruction(transmutationBuilding)
            if staticTalent["rarity"] in ["magnificent", "exclusive"]:
                return transmutationBuilding.Level >= staticConstruction["requiredLeveForReforgingExclusiveTalents"]
            if staticTalent["rarity"] == "excellent":
                return transmutationBuilding.Level >= staticConstruction["requiredLeveForReforging"]

        return False

    def reforgeTalent(self, SD, talent, selectedSet, rarity):
        talent_id = SD.getRandomTalent(rarity, selectedSet, self.LordInfo.ReforgeRandomSeed >> 8)
        if not talent_id or self.LordInfo.ReforgeRandomSeed == 0:
            warn("Cannot generate random talent with rarity %s" % rarity)
            return None

        while talent_id and talent_id == talent.PersistentId:
            self.LordInfo.ReforgeRandomSeed = self.getRandomPure(self.LordInfo.ReforgeRandomSeed)
            talent_id = SD.getRandomTalent(rarity, selectedSet, self.LordInfo.ReforgeRandomSeed >> 8)

        self.LordInfo.ReforgeRandomSeed = self.getRandomPure(self.LordInfo.ReforgeRandomSeed)
        return talent_id

    def reforgeUpgradeTalent(self, SD, talent, selectedSet, rarity):
        if rarity == "excellent":
            newRarity = "magnificent"
        elif rarity == "magnificent":
            newRarity = "exclusive"
        elif rarity == "exclusive":
            newRarity = "outstanding"
        else:
            return None

        talent_id = SD.getRandomTalent(newRarity, selectedSet, self.LordInfo.ReforgeRandomSeed >> 8)
        if not talent_id or self.LordInfo.ReforgeRandomSeed == 0:
            warn("Cannot generate random talent with rarity %s" % rarity)
            return None

        while talent_id and talent_id == talent.PersistentId:
            self.LordInfo.ReforgeRandomSeed = self.getRandomPure(self.LordInfo.ReforgeRandomSeed)
            talent_id = SD.getRandomTalent(newRarity, selectedSet, self.ReforgeRandomSeed >> 8)

        self.LordInfo.ReforgeRandomSeed = self.getRandomPure(self.LordInfo.ReforgeRandomSeed)
        return talent_id

    def validateLastPvPSession(self, acc, iDict):
        for staticQuest in acc.SD.data['RatingDecreaseByTime']['ratingUpdateQuest']['answers']['Item'][0]['actions']['Item']:
            if self.getActiveStaticQuest(staticQuest['quest']):
                return

        ratingLossLevel = acc.SD.getRatingToLooseLevel(self.LordInfo.LastRankedGameTime)
        if ratingLossLevel:
            hasRatedHeroes = False
            for heroId, hero in self.Heroes.iteritems():
                if hero.Rating > int(acc.SD.data['RatingDecreaseByTime']['minRatingToLoose']):
                    hasRatedHeroes = True
                    break

            if not hasRatedHeroes:
                return
            quest = self.addQuest(acc.SD.data['RatingDecreaseByTime']['ratingUpdateQuest'], None, None, False, False,
                                  iDict.STATS, acc)
            if quest and quest.isComplete(self, acc.SD):
                quest.state = QuestState.Complete
                iDict.STATS.addQuestChange(acc.db.auid, quest.persistentId, 2)
                quest.completeQuest(None, acc.SD.data['RatingDecreaseByTime']['ratingUpdateQuest'], 0, acc, iDict,
                                    self.getRandom(self.LordInfo.RandomSeed))
                self.CompletedQuests.add(quest)
                self.ActiveQuests.remove(quest)

    def validateLastLogin(self, acc, iDict):
        if (self.LordInfo.LastLoginTime < (
            int(time.time()) - acc.getConfig().LAST_LOGIN_TIME_FOR_CASTLE_QUEST)) and self.LordInfo.LastLoginTime != 0:
            staticQuest = acc.SD.getStaticQuestById(crc32("c51_lineStarter"))
            quest = self.addQuest(staticQuest, None, None, False, False, iDict.STATS, acc)
            if quest and quest.isComplete(self, acc.SD):
                quest.state = QuestState.Complete
                iDict.STATS.addQuestChange(acc.auid, quest.persistentId, 2)
                quest.completeQuest(None, staticQuest, 0, acc, iDict, self.getRandom(self.LordInfo.RandomSeed))
                self.CompletedQuests.add(quest)
                self.ActiveQuests.remove(quest)

    def getGuildBufByPersistentId(self, persistentId):
        for bonusId in self.GuildBufs:
            ownedBonus = self.getGuildBufByID(bonusId)
            if ownedBonus.PersistentId == persistentId:
                return ownedBonus

    def deactivateAllWeakerBonuses(self, SD):
        for bonusId in self.GuildBufs:
            bonus = self.getGuildBufByID(bonusId)
            bonus.IsEnabled = True
            staticBonus = SD.getGuildBufById(bonus.PersistentId)
            # info("deactivateAllWeakerBonuses: check bonus %s(%r)", staticBonus['persistentId'], bonus.PersistentId)
            if staticBonus is None:
                warn("can't find buff %s in static data", bonusId)
                bonus.IsEnabled = False
                continue

            if 'doNotWorkWith' in staticBonus and type(staticBonus['doNotWorkWith']) is dict:
                for enemyBonus in staticBonus['doNotWorkWith']['Item']:
                    # info("deactivateAllWeakerBonuses enemyBonus: compare \n"
                    #     "\t %s(%r),%s(%s) vs %s(%r),%s(%s)", enemyBonus['persistentId'], crc32(enemyBonus['persistentId']), enemyBonus['priority'], type(enemyBonus['priority']),
                    #     staticBonus['persistentId'], crc32(staticBonus['persistentId']), staticBonus['priority'], type(staticBonus['priority']))

                    mdBonus = self.getGuildBufByPersistentId(crc32(enemyBonus['persistentId']))
                    if mdBonus and int(enemyBonus['priority']) > int(staticBonus['priority']):
                        # info("deactivateAllWeakerBonuses bonus disabled!")
                        bonus.IsEnabled = False
                        break

    def AddOneTimeGuildShopItem(self, acc, SD, expireTime, staticShopItem):
        staticBonus = SD.getGuildBufById(crc32(staticShopItem['guildBuff']['persistentId']))
        if staticBonus is None:
            err("AddOneTimeGuildShopItem: can't find guild buff '%s' in GuildBuffsCollection!",
                staticShopItem['guildBuff']['persistentId'])
            return False

        return self.addGuildBuff(acc, SD, expireTime, staticBonus)

    def addGuildBuff(self, acc, SD, expireTime, staticBonus):
        bonus = self.getGuildBufByPersistentId(crc32(staticBonus['persistentId']))

        if bonus is None:
            info("AddOneTimeGuildShopItem: add new bonus %s", staticBonus['persistentId'])
            bonus_id = self.addNewGuildBuf()
            bonus = self.getGuildBufByID(bonus_id)
            bonus.PersistentId = crc32(staticBonus['persistentId'])
            bonus.GuildOnly = staticBonus['isGuildBonus']
            self.GuildBufs.add(bonus)

        bonus.IsEnabled = True
        self.deactivateAllWeakerBonuses(SD)

        if staticBonus['duration'] != 0 and staticBonus['numGames'] != 0:
            bonus.ExpireTime = expireTime
            bonus.TransactionsLeft = staticBonus['numGames']
            bonus.DurationType = GuildBufDurationType.Mixed
        elif staticBonus['duration'] != 0:
            bonus.ExpireTime = expireTime
            bonus.DurationType = GuildBufDurationType.TimeBased
        elif staticBonus['numGames'] != 0:
            bonus.DurationType = GuildBufDurationType.GamesBased
            bonus.TransactionsLeft = staticBonus['numGames']

        for _id, construction in self.ConstructionsKeeper.iteritems():
            staticConstruction = acc.SD.getStaticConstruction(construction)
            classType = staticConstruction['classType']
            if classType == 'ProductionBuilding':
                construction.storeTimeBasedProduction(staticConstruction, "ProductionLevels", acc.getConfig(), SD, self)

        return True

    def checkGuildBufsAfterSession(self, isWinner, SD, rollBuffs):
        # PF-106794
        # # Временная заглушка, если вдруг потом надо будет снимать длительность бафов и за проигранные бои.
        # if not isWinner:
        #     return

        needUpdate = False
        for bonusId in self.GuildBufs.keys():
            bonus = self.getGuildBufByID(bonusId)
            # Снимаем счётчик для бафов на определённое кол-во побед, которые были активны в текущей сессии
            if bonus.DurationType in [GuildBufDurationType.GamesBased,
                                      GuildBufDurationType.Mixed] and bonus.PersistentId in rollBuffs:
                bonus.TransactionsLeft -= 1
                if bonus.TransactionsLeft == 0:
                    self.GuildBufs.remove(bonusId)
                    needUpdate = True

        if needUpdate:
            self.deactivateAllWeakerBonuses(SD)

    def updateGuildBuffs(self, techsDuration):
        """Обновим время действия баффов, если они попали на тех-работы"""
        for bonusId in self.GuildBufs.keys():
            bonus = self.getGuildBufByID(bonusId)
            if bonus.DurationType in [GuildBufDurationType.TimeBased, GuildBufDurationType.Mixed]:
                bonus.ExpireTime += techsDuration

    def fillGuildApplication(self, application, lifetime):
        guildApp, _id = self.newGuildApplication()
        guildApp.GuildAuid = application["guild_auid"]
        guildApp.ExpireTime = application["created"] + lifetime
        guildApp.Rejected = application["status"] == 0
        self.GuildApplications.add(guildApp)

    def checkGuildApplicationsAlive(self):
        now = time.time()
        to_remove = []
        for app_id, app in self.GuildApplications.items():
            if app.ExpireTime <= now:
                debug("checkGuildApplicationsAlive: out of date application for guild %s found", app.GuildAuid)
                to_remove.append(app.GuildAuid)
                self.GuildApplications.remove(app)
        return to_remove

    def checkGuildApplication(self, guildAuid):
        for app_id, app in self.GuildApplications.items():
            if app.GuildAuid == guildAuid:
                return True
        return False

    def removeGuildApplication(self, guildAuid, any_state=False):
        for app_id, app in self.GuildApplications.items():
            if app.GuildAuid == guildAuid:
                if app.Rejected and not any_state:
                    warn("removeGuildApplication, guildAuid=%s, any_state=%s: declined application found: %s",
                         guildAuid, any_state, app)
                    raise RecruitAppliationDeclinedError()
                self.GuildApplications.remove(app)
                debug("removeGuildApplication: application to guild %s removed. Remained: %s", guildAuid,
                      self.GuildApplications.items())
                return
        warn("removeGuildApplication, guildAuid=%s: application not found", guildAuid)
        raise NoRecruitApplicationError()

    def updateBalanceInfo(self, acc, BILL, forced_update=False):
        status, balance = BILL.getStatusBalance(acc.auid, force_balance_check=forced_update)

        if status == ibilling.BILLING_OK:
            acc.model.Resources.Gold = int(balance)
            if acc.model.Resources.Gold < 0:
                info("WARNING! GOLD_ACHTUNG happened in keepalive GOLD = %r for USER = %r", acc.model.Resources.Gold, acc.uid)
            elif acc.model.Resources.Gold >= acc.getConfig().APPEARING_GOLDPRODUCTIONHOUSE_PRICE and not acc.model.hasGoldProductionHouse():
                construction_uid = acc.model.addNewConstruction()
                construction = acc.model.getConstructionByID(construction_uid)
                construction.PersistentId = crc32("GoldProductionHouse")
                acc.model.Pocket.add(construction)
                acc.model.MarketingEventsInfo.GoldHouseActionState = GoldHouseActionState.ShowPlaceHouseEvent
            acc.model.LordInfo.BillingStatus = Billing.Ok
        else:
            acc.model.Resources.Gold = 0
            if status <= -1000 and str(status)[:-1] == '-100':
                acc.model.LordInfo.BillingStatus = Billing.UserProblem
            else:
                acc.model.LordInfo.BillingStatus = Billing.Fail

    def getRerollShopItemPrice(self, priceType, priceValue):
        price = self.createResourcesTable()
        if priceType == ERerollShopResources.Resource1 or priceType == "Resource1":
            price.Resource1 = priceValue
        elif priceType == ERerollShopResources.Resource2 or priceType == "Resource2":
            price.Resource2 = priceValue
        elif priceType == ERerollShopResources.Resource3 or priceType == "Resource3":
            price.Resource3 = priceValue
        elif priceType == ERerollShopResources.Silver or priceType == "Silver":
            price.Silver = priceValue
        elif priceType == ERerollShopResources.Gold or priceType == "Gold":
            price.Gold = priceValue
        elif priceType == ERerollShopResources.Perl or priceType == "Perl":
            price.Perl = priceValue
        elif priceType == ERerollShopResources.RedPerl or priceType == "RedPerl":
            price.RedPerl = priceValue
        elif priceType == ERerollShopResources.Shard or priceType == "Shard":
            price.Shard = priceValue
        return price

    def validateRerollShop(self, acc):
        try:
            lastRerollDate = datetime.datetime.utcfromtimestamp(self.RerollShopInfo.NextRerollTime)
            curDate = datetime.datetime.utcnow()
            if curDate.year > lastRerollDate.year or curDate.month > lastRerollDate.month or curDate.day > lastRerollDate.day:
                dateTime = (datetime.datetime.utcnow() + datetime.timedelta(days=1)).replace(hour=0, minute=0, second=0)
                self.RerollShopInfo.NextRerollTime = int(time.time()) + int((dateTime - datetime.datetime.utcnow()).total_seconds()) - 2
                self.RerollShopInfo.RerollsToday = 0
                self.rerollShopItems(acc)
        except:
            catch()

    def rollOneItem(self, acc, item, rerollHelper):
        if rerollHelper.needRerollProbabilities(acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES],
                                                acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS],
                                                acc.db.castle_roll[CC.REROLL_ADDITIONAL_PROBABILITIES],
                                                acc.getConfig()):
            rerollHelper.resetProbabilities(acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES],
                                            acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS],
                                            acc.db.castle_roll[CC.REROLL_ADDITIONAL_PROBABILITIES], 0, acc.getConfig())
            debug("rerolling!")
        groupId = rerollHelper.getNewGroup(acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES], acc)
        item.rollNewItem(groupId, acc.SD, acc.getConfig())

    def rerollShopItems(self, acc):
        self.RerollShopInfo.checkSize(self, acc.getConfig().EventToolsChangeFields.REROLL_SHOP_ORDINARY_SLOTS,
                                      acc.getConfig().EventToolsChangeFields.REROLL_SHOP_PREMIUM_SLOTS)
        rerollHelper = RerollHelper(acc.SD)

        # daily reroll
        if self.RerollShopInfo.RerollsToday == 0:
            self.RerollShopInfo.NewlyRerolled = True
            for _id, item in self.RerollShopInfo.ShopItems.iteritems():
                self.rollOneItem(acc, item, rerollHelper)
        #user reroll
        else:
            currentlyActiveSlots = []
            inactiveSlots = acc.getConfig().EventToolsChangeFields.INACTIVE_REROLL_SHOP_PREMIUM_SLOTS if self.IsPremiumAccount() else\
                          acc.getConfig().EventToolsChangeFields.INACTIVE_REROLL_SHOP_ORDINARY_SLOTS
            # Если слоты с премиумом должны быть открыты, надо перетасовать порядок "закрытия" слотов
            if acc.getConfig().EventToolsChangeFields.PREMIUM_SLOTS_ARE_NOT_INACTIVE and self.IsPremiumAccount():
                inactiveSlots -= acc.getConfig().EventToolsChangeFields.REROLL_SHOP_PREMIUM_SLOTS
                for _id, item in self.RerollShopInfo.ShopItems.iteritems():
                    if item.IsPremium and item.IsBought:
                        item.IsBought = False
                        for _id, otherItem in self.RerollShopInfo.ShopItems.iteritems():
                            if otherItem.NumBought > item.NumBought:
                                otherItem.NumBought -= 1
                        item.NumBought = 0


            debug("Inactive slots = %d", inactiveSlots)
            for _id, item in self.RerollShopInfo.ShopItems.iteritems():
                if not item.IsBought or item.NumBought > inactiveSlots:
                    currentlyActiveSlots.append(item)


            debug("len currently active slots = %d, len shop items = %d", len(currentlyActiveSlots), len(self.RerollShopInfo.ShopItems))
            # Надо активировать уже выкупленные слоты, а то всё скупили
            if len(currentlyActiveSlots) < len(self.RerollShopInfo.ShopItems) - inactiveSlots:
                for item in currentlyActiveSlots:
                    self.rollOneItem(acc, item, rerollHelper)
                slotsToOpen = len(self.RerollShopInfo.ShopItems) - inactiveSlots - len(currentlyActiveSlots)
                for _id, item in self.RerollShopInfo.ShopItems.iteritems():
                    if not item.IsBought or slotsToOpen == 0:
                        continue
                    self.rollOneItem(acc, item, rerollHelper)
                    slotsToOpen -= 1
            else:
                for _id, item in self.RerollShopInfo.ShopItems.iteritems():
                    if not item.IsBought or item.NumBought > inactiveSlots:
                        debug("Rolling item!")
                        self.rollOneItem(acc, item, rerollHelper)

    def isInventoryFull(self):
        return len(filter(lambda t: not(t.Owner and t.Owner.get()), self.UserInventory.values())) > self.UserInventoryLimit

    def validateMap(self,acc):
        mapset = set()
        for mapid, mapinfo in  self.MapInfoKeeper.items():
            if mapinfo:
                mapset.add(mapinfo.MapId)
        for currMap in mapset:
            duplicates = filter(lambda obj: obj.MapId == currMap, self.MapInfoKeeper.itervalues())
            if len(duplicates) > 1:
                for x in duplicates:
                    if x.refCounter <= 0:
                        warn("Duplicate of map (%s) was found map_id=%s", currMap, x.id)
                        self.MapInfoKeeper.pop(x.id)

    def addSeasonInfo(self):
        cur_talent_season, uid = self.newSeasonInfo()
        return cur_talent_season, uid

    def getBestLeagueFromPrevSeasonsByHeroId(self, acc, hero_id):
        hero = self.getHeroByID(hero_id)
        if not hero:
            return None
        return hero.getBestLeagueFromPrevSeasons(acc, acc.SD)

    def getBestLeagueFlashIdxFromPrevSeasonsByHeroId(self, acc, hero_id):
        league = self.getBestLeagueFromPrevSeasonsByHeroId(acc, hero_id)
        if not league:
            return 0
        return league['flashDataIndex']

    def updateHeroLegendLeagueInfo(self, acc, SD, hero_id, new_place):
        for heroId, cur_process_hero in self.HeroesKeeper.iteritems():
            if cur_process_hero.PersistentId == hero_id:
                cur_process_hero.updateLegendPlace(acc, SD, new_place)
                break

    def updateHeroLegendPlaces(self, acc, SD, hero_id, list_places):
        for heroId, cur_process_hero in self.HeroesKeeper.iteritems():
            if cur_process_hero.PersistentId == hero_id:
                cur_process_hero.updateLegendListPlaces(acc, SD, list_places)
                break

    def updateHeroLegendLeagueInfoBySeasonId(self, acc, SD, hero_id, new_place, seasonId):
        for heroId, cur_process_hero in self.HeroesKeeper.iteritems():
            if cur_process_hero.PersistentId == hero_id:
                cur_process_hero.updateLegendInfoBySeasonId(acc, SD, new_place, seasonId)
                break

    def appendSeasonAwards(self, acc, season_id, flag_name, talents_ids, lootboxes_ids):
        for awards_id in self.SeasonAwardsKeeper:
            awards_info = self.getSeasonAwardsByID(awards_id)
            if awards_info.SeasonId != season_id:
                continue

            if flag_name is not None:
                debug("appendSeasonAwards for auid = %d, getCustomFlagById: %s"%(acc.db.auid, flag_name))
                staticCustomFlag = acc.SD.getCustomFlagById(flag_name)
                if not staticCustomFlag:
                    debug("appendSeasonAwards for auid = %d, getCustomFlagById: %s FAILED!"%(acc.db.auid, flag_name))
                else:
                    if flag_name not in acc.model.Flags:
                        acc.model.Flags.append(flag_name)
                    acc.model.FlagInfo.PersistentId = staticCustomFlag["id"]
                    acc.model.FlagInfo.FlagType = FlagType.Special
                    awards_info.Flag = staticCustomFlag["id"]

            for talId in talents_ids:
                staticTalent = acc.SD.getStaticTalentByTalentId( crc32(talId) )
                debug("appendSeasonAwards for auid = %d, add Talent %s"%(acc.db.auid, str(talId)))
                if staticTalent:
                    if staticTalent['rarity'] != "Class":
                        talent_id = acc.model.addNewTalent()
                        talent = acc.model.getTalentByID(talent_id)
                        talent.IsNew = True
                        talent.PersistentId = crc32(talId)
                        self.UserInventory.add(talent_id)
                        awards_info.Talents.append(talent.PersistentId)

            for lootboxDbId in lootboxes_ids:
                isOk, lootbox = self.addLootbox(crc32(lootboxDbId), acc)
                if isOk:
                    awards_info.Lootboxes.append(lootbox.PersistentId)
                else:
                    err('fail append lootbox season award for auid = {}, lootboxPersistentId = {}'.format(acc.db.auid, lootboxDbId))



    def removeSeasonFlag(self, acc, flag_name):
        if flag_name in acc.model.Flags:
            acc.model.Flags.remove(flag_name)
            # Не забудем поменяться на дефолтный, если у игрока флаг был активным
            if acc.model.FlagInfo.PersistentId == flag_name:
                acc.model.FlagInfo.FlagType = FlagType.Default
                acc.model.FlagInfo.PersistentId = acc.SD.getDefaultFlagName()

    def collectSeasonAwards(self, I, acc,
                            prev_season_settings, new_season_settings,
                            awards_by_season, change_rating_func,
                            heroes_top10, need_update_prev_info_struct):
        prev_season_id = crc32(prev_season_settings["persistentId"])
        new_season_id = crc32(new_season_settings["persistentId"])

        debug("collectSeasonAwards for auid = %d, prev_season_settings:%s, new_season_settings:%s"%(acc.db.auid, str(prev_season_settings), str(new_season_settings)))

        # защита от повторной выдачи наград за один и тот же сезон
        # kramarov: кажется, какой-то бесполезной
        list_awards_for_delete = []
        for awards_id in self.SeasonAwardsKeeper:
            awards_info = self.getSeasonAwardsByID(awards_id)
            if awards_info.SeasonId == prev_season_id or awards_info.SeasonId == new_season_id or awards_info.SeasonId == 0:
                 list_awards_for_delete.append(awards_id)

        debug("collectSeasonAwards for auid = %d, clear data for prev_season %d and new_season %d"%(acc.db.auid, prev_season_id, new_season_id))
        for award_id in list_awards_for_delete:
            self.SeasonAwardsKeeper.remove(award_id)
        self.SeasonsAwardsInfo.remove(prev_season_id)
        self.SeasonsAwardsInfo.remove(new_season_id)

        is_legend_league = False
        best_award_index = 0
        talents_ids = []
        lootboxes_ids = []
        is_need_get_awards = False

        for heroId, cur_process_hero in self.HeroesKeeper.iteritems():
            # есть ли функтор, определяющий как изменять рейтинг героя по итогу сезона
            prev_rating = cur_process_hero.Rating
            if change_rating_func:
                diff = change_rating_func(cur_process_hero.Rating)
                debug("""collectSeasonAwards for auid = {}, cur_process_hero: {} ({}), 
                                    Rating: {}, lose: {}""".format(acc.db.auid, str(cur_process_hero.class_name),
                                                                   str(cur_process_hero.PersistentId),
                                                                   cur_process_hero.Rating, diff))
                if diff != 0:
                    # меняем рейтинг героя
                    cur_process_hero.changeRating(diff, I, acc)
                    debug("""collectSeasonAwards for auid = {}, cur_process_hero: {} ({}), 
                                        change Rating from {} to {}""".format(acc.db.auid,
                                                                              str(cur_process_hero.class_name),
                                                                              str(cur_process_hero.PersistentId),
                                                                              prev_rating, cur_process_hero.Rating))

            # если героем не играли вообще или не играли в последнем сезоне - никакой инфы ему добавлять не будем
            if cur_process_hero.lastPlayed <= 0 or cur_process_hero.lastPlayed < prev_season_settings["startTime"]:
                continue

            # заводим запись о prev сезоне
            if not is_need_get_awards:
                season_awards_info, season_awards_id = self.newSeasonAwards()
                season_awards_info.SeasonId = prev_season_id
				# не показываем окно наград для межсезонья и далее - ставим IsShowedToUser в True
                season_awards_info.IsShowedToUser = prev_season_settings["stopTime"] > 1549530000
                is_need_get_awards = True

            debug(
                "collectSeasonAwards for auid = %d, cur_process_hero: %s (%s), id_season: %d, need_update_prev_info_struct: %d" % (
                    acc.db.auid, str(cur_process_hero.class_name), str(cur_process_hero.PersistentId), prev_season_id,
                    need_update_prev_info_struct))

            if need_update_prev_info_struct:
                prev_season_info = cur_process_hero.findOrCreateSeasonInfoById(acc, acc.SD, prev_season_id)
            else:
                prev_season_info = cur_process_hero.findSeasonInfoById(acc, prev_season_id)

            # ниже ищем лучшую награду по МАКСИМАЛЬНОМУ рейтингу героя в сезоне, а так же определяем не надо ли дать за него эпическую награду
            best_award_index_for_hero = 0
            hero_key = str(cur_process_hero.PersistentId)
            if hero_key in heroes_top10.keys() and heroes_top10[hero_key] <= 10:
                if need_update_prev_info_struct:
                    prev_season_info.CurLeaguePlace = heroes_top10[cur_process_hero.PersistentId]
                    prev_season_info.BestLeaguePlace = prev_season_info.CurLeaguePlace
                best_award_index_for_hero = len(awards_by_season)-1
            else:
                for i in range(len(awards_by_season)-1, -1, -1):
                    # если есть запись по сезону у героя - берем рейтинг из нее, если нет - текущий рейтинг берем
                    max_prev_season_rating = prev_season_info.SeasonRating if prev_season_info else prev_rating
                    if max_prev_season_rating >= awards_by_season[i]["Rating"]:
                        if i > best_award_index_for_hero:
                            best_award_index_for_hero = i
                        break

            hero_awards = awards_by_season[best_award_index_for_hero]
            if 'Talents' in hero_awards and len(hero_awards['Talents']) > 0:
                if isinstance(hero_awards['Talents'][0], list):
                    for i in range(len(hero_awards['Talents'])):
                        talents_ids.append(random.choice(hero_awards['Talents'][i]))
                else:
                    talents_ids.append(random.choice(hero_awards['Talents']))

            if 'Lootboxes' in hero_awards:
                lootboxes_ids.extend(hero_awards['Lootboxes'])

            # prev_season_info.LeagueIndex = best_hero_league_index - нельзя сохранять ибо индексы разных сущностей
            if prev_season_info:
                prev_season_info.LeagueIndex = 1  #херня какая-то используемая как костыль, чтобы пометить, что героем играли в сезоне

            if best_award_index_for_hero > best_award_index:
                best_award_index = best_award_index_for_hero

            if need_update_prev_info_struct:
                prev_season_info.SeasonId = prev_season_id
                prev_season_info.SeasonRating = cur_process_hero.Rating
                cur_process_hero.updateLegendPlace(acc, acc.SD, prev_season_info.CurLeaguePlace)

        # всех героев обработали, рейт изменили, таланты выдали, лутбоксы выдали, теперь по лучшей награде выдаем все остальное
        # кристалы, флаг, скин, ...
        if is_need_get_awards:

            debug("collectSeasonAwards for auid = %d, best_award_index: %d", acc.db.auid, best_award_index)
            best_awards = awards_by_season[best_award_index]
            season_awards_info.RedPerls = best_awards["RedPerls"]

            if best_awards["Skin"] is not None:
                skin_id = best_awards["Skin"]
                static_skin = acc.SD.getStaticSkinByPersistentId(crc32(skin_id))
                if static_skin:
                    debug("collectSeasonAwards for auid = %d, skin_id: %s", acc.db.auid, skin_id)
                    hero_for_skin = self.getHeroForSkin(static_skin, acc.SD)
                    if not hero_for_skin:
                        debug("collectSeasonAwards for auid = %d, not hero found for skin %s, try to buy hero %s" % (
                            acc.db.auid, skin_id, static_skin['heroClassId']))
                        hero_for_skin = self.hireHero(crc32(static_skin['heroClassId']), acc.sex, I.WS, acc, I)
                    else:
                        debug("collectSeasonAwards for auid = %d, find haro for skin: %s (%s) skin_id: %s" % (
                            acc.db.auid, str(hero_for_skin.class_name), str(hero_for_skin.PersistentId), skin_id))
                    if hero_for_skin:
                        config = acc.getConfig()
                        debug("collectSeasonAwards for auid = %d, addSkinForHero cur_process_hero: %s (%s) skin_id: %s" % (
                                acc.db.auid, str(hero_for_skin.class_name), str(hero_for_skin.PersistentId), skin_id))
                        self.addSkinForHero(crc32(skin_id), hero_for_skin, isDefault=True, wasBought=True,
                                            IsAnimatedAvatar=static_skin['persistentId'] not in config.SKIN_AVATAR_BLOCK)
                        season_awards_info.Skin = crc32(skin_id)
                    else:
                        debug("collectSeasonAwards for auid = %d, not hero found or buy for skin %s" % (
                            acc.db.auid, skin_id))
                else:
                    debug("collectSeasonAwards for auid = %d, skin for skin_id: %s NOT FOUND in staticData!",
                          acc.db.auid, skin_id)

            flag_name = best_awards["Flag"]

            self.appendSeasonAwards(acc, prev_season_id, flag_name, talents_ids, lootboxes_ids)

            self.addResourcesForFree({"Perl": str(season_awards_info.RedPerls)})

            debug("collectSeasonAwards for auid = %d, result awards: seasonId = %s, Talents: %s, RedPerls: %d, Lootboxes: %s" % (
                acc.db.auid, str(season_awards_info.SeasonId), ', '.join(talents_ids), season_awards_info.RedPerls, lootboxes_ids))

            self.SeasonsAwardsInfo.add(prev_season_id, season_awards_info)

    def addLootbox(self, persistent_id, acc, open_after_receive=True):
        static_lootbox = acc.SD.getStaticLootboxById(persistent_id)
        if not static_lootbox:
            err("StaticLootbox with id {} not found".format(persistent_id))
            return False, None
        lootbox_id = self.addNewLootbox()
        lootbox = self.getLootboxByID(lootbox_id)
        lootbox.PersistentId = persistent_id
        lootbox.OpenAfterReceive = open_after_receive
        self.Lootboxes.add(lootbox_id)
        return True, lootbox

    # region clan war events

    def awardForClanWarEvent(self, guild_place, player_place, acc):
        if guild_place < 1:
            return
        if player_place < 1:
            return
        for award_def in acc.SD.data['ClanWarsData']['guildWarEventData']['awards']['Item']:
            if guild_place > award_def['maxPlace']:
                continue
            if player_place > award_def['members']:
                return
            lb = award_def['award']['lootbox']
            if not lb:
                return
            lb_persistent_id = crc32(lb['persistentId'])
            for i in xrange(award_def['award']['count']):
                self.addLootbox(lb_persistent_id, acc)
            return

    # endregion


# --------------------------------------------------------------------------------------------------------------------------------------
# для отдельных "высоконагруженных" классов -- подменяем кодо-генерированные конструкторы специальными "оптимизированными" вариантами
Talent.__init__ = Talent_base.init_empty
Talent.init_add = Talent_base.init_add

