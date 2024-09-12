#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, time, os
import unittest

os.chdir('..')
sys.path.append(os.path.abspath('.'))
sys.path.append(os.path.abspath('cfg'))

from ext_main.login import LoginAction
from ext_main.auth import AuthAction
from ext_pw import *

import cfg, coord_cfg  # настройки MC/SQL (будем надеяться, актуальные) возьмем из локального конфига координатора

from base.helpers import *
from binascii import crc32
from modeldata.ModelData import ModelData
from modeldata.MultiStaticData import MultiStaticData

from modeldata.datamanager import PwNewModelManager
from modeldata.persistent_data import PersistentDataManager
from iserialmodel import ISyncSerialModel
from iwebserver import IWebServer
from config.MultiConfig import *
from ifactory import IfaceFactory
from ipersonserver import IFakePersonServer
from pwaccount import UserAccount
from pwserver import PwWorkServer
from guild.guild_bonuses_helper import GuildBonusProcessor

import logging

logging.basicConfig(level=logging.WARNING, format="[%(asctime)s %(levelname)8s] %(message)s")


class ModelDataValidate(unittest.TestCase):
    cfg.TOURNAMENT_SERVER = coord_cfg.COORDINATOR_TOURNAMENT_SERVER
    cfg.TOURNAMENT_SERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_SERVER_ADDR
    cfg.TOURNAMENT_XSERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_XSERVER_ADDR
    cfg.TOURNAMENT_SPECTATOR_AUIDS = coord_cfg.COORDINATOR_TOURNAMENT_SPECTATOR_AUIDS
    cfg.TOURNAMENT_APPLY_RESULTS = coord_cfg.COORDINATOR_TOURNAMENT_APPLY_RESULTS
    I = ClassDict()
    I.coord_res = {}
    I.coord_res["deploy_name"] = "RU"
    I.Config = MultiConfig()
    I.SD = MultiStaticData("./xdb/ExportedSocialData.xml", I.Config.getMainConfig()).getMainSD()
    I.Config.getMainConfig().fillStaticDataDependendValues(I.SD)
    I.WS = IWebServer(test_mode=True)
    I.MD = PwNewModelManager(ifaceDict=I, load_events=False)
    I.PDM = PersistentDataManager(ifaceDict=I)
    I.SMODEL = ISyncSerialModel(I, "1.2.3")
    I.STATS = IfaceFactory.makeIStatsInterface("none", "", I)  # пустая болванка
    I.BILL = IfaceFactory.makeBillingInterface("dummy", I)

    acc = UserAccount(uid=1, guest=0, pending_events=[])
    acc.sex = 1  # male
    acc.loaded = 1
    acc.db = ClassDict()
    acc.db.fraction = 'A'
    acc.data = ClassDict()
    acc.auid = 1
    acc.registration_date = toint(time.time())
    acc.snid = "fb"
    acc.snuid = "100001"
    acc.userlocale = "RU"
    acc.Config = I.Config
    acc.SD = I.SD
    acc.geo_info = {'region_name': '66', 'city': 'Saint Petersburg', 'longitude': 30.264199999999988,
                    'country_code3': 'RUS', 'latitude': 59.89439999999999, 'postal_code': None, 'country_code': 'RU',
                    'country_name': 'Russian Federation'}

    I.BILL.initBilling(acc.auid)
    lampEvent = {"persistentId": 66,
                 "startTime": int(time.time()) - 60*60,
                 "endTime": int(time.time()) + 60*60,
                 "newValue": {"eventDescription": utf8convert('lamp \"2, 3\"')}}
    giveLampEvent = {"persistentId": 67,
                 "startTime": int(time.time()) - 60*60,
                 "endTime": int(time.time()) + 60*60,
                 "newValue": {"eventDescription": utf8convert('give_lamp \"20, 10000, 10, 86400\"')}}

    I.Config.events.append(event(lampEvent))
    I.Config.events.append(event(giveLampEvent))
    I.MD.newModel(acc, I, "1.2.3", random_heroes=-1, random_items=-1, fraction=acc.db.fraction, db=acc.db, guest=1)

    def insertHero(self, hero_name):
        hero_class_id = crc32(hero_name)
        staticHero = self.I.SD.getStaticHeroByClassId(hero_class_id)
        hero, hero_uid = self.acc.model.newHero()
        hero.class_name = staticHero['persistentId']
        hero.PersistentId = hero_class_id
        hero.Hired = True

        hero.EpicWins = 0
        hero.Master = False
        hero.Version = staticHero['lobbyData']['Version']
        for i in xrange(3):
            ts_id = self.acc.model.addNewTalentSet()
            ts = self.acc.model.getTalentSetByID(ts_id)
            hero.TalentSets.add(i, ts)
        #wtf??? undefined method! hero.createDefaultTalentSetGenerateChanges(self.acc.model, staticHero, self.acc.SD, hero.ActiveTalentSet)
        hero.resetHeroStatPoints(self.acc, 0)
        hero.TalentSets[hero.ActiveTalentSet].Force = self.I.SD.getDefaultHeroForce(self.acc.getConfig(), hero.PersistentId, 0,
                                                   self.acc.model.getStatPointsFromBuilding(self.I.SD))
        self.acc.model.Heroes.add(hero)
        self.acc.model.addDefaultTalentSetToInventory(hero)



    def getAnyHero(self):
        for id in self.acc.model.Heroes.keys():
            return self.acc.model.getHeroByID(id)

        return None

    def ignore_testHeroValidation(self):
        self.insertHero("artist")
        self.acc.model.validateHeroes(self.acc.db.fraction, self.acc.SD);
        info(len(self.acc.model.Heroes))
        pass

    def ignore_testHeroStats(self):
        hero = self.getAnyHero()
        info(self.acc.model.getHeroMaxLevelStat(hero, "Life", self.acc.SD))
        pass


    def addBuffs(self,buffs_ids):
        # выдадим
        for buff_persistentId in buffs_ids:
            buff, buff_id = self.acc.model.newGuildBuf()
            buff.IsEnabled = True
            buff.PersistentId = crc32(buff_persistentId)
            buff.GuildOnly = True
            self.acc.model.GuildBufs.add(buff)
            self.acc.model.deactivateAllWeakerBonuses(self.acc.SD)

    def testResources(self):

        self.acc.model.addResourcesForFree({'Gold': 100, 'Currencies': {'currency1': 12}})

        p2 = self.I.SD.copyPrice(self.acc.model.Resources)
        assert self.I.SD.isValidPrice(p2) == True

        p1 = self.I.SD.emptyPrice()
        self.I.SD.getSubtractPrice(p1, p2)
        self.acc.model.sell(p1, self.acc, False)
        assert self.I.SD.isValidPrice(self.acc.model.Resources) == False

        self.acc.model.addResourcesForFree({'Perl': 100, 'Currencies': {'currency1': 12}})

        p1 = self.I.SD.copyPrice(self.acc.model.Resources)
        self.acc.model.sell({'Currencies': {'currency1': -5}}, self.acc, False)
        assert self.I.SD.isEnoughResources(p1, self.acc.model.Resources) == False
        assert self.I.SD.isEnoughCustomCurrencies(p1, self.acc.model.Resources) == False
        self.acc.model.sell({'Perl': -5, 'Currencies': {'currency1': 5}}, self.acc, False)
        assert self.I.SD.isEnoughResources(p1, self.acc.model.Resources) == False
        assert self.I.SD.isEnoughCustomCurrencies(p1, self.acc.model.Resources) == True



    def testGuildBuffsProcessor(self):
        buffs = ["Buf66", "Buf3", "Buf101"]
        self.addBuffs(buffs)

        processor = GuildBonusProcessor(self.I.WS)
        hero = self.getAnyHero()

        debug(hero.class_name)
        res = processor.getModifiersFromGuildBuffs( self.acc, hero.PersistentId, "/Maps/Multiplayer/MOBA/_.ADMPDSCR" )
        debug("%s" % pretty(res))

        session_buffs = []
        for stat, stat_data in res['at36level']:
            debug(("%s : %s") % (stat, pretty(stat_data)))
            session_buffs.append(stat_data['buffPersistentId'])

        debug("%s" % pretty(session_buffs))

        statModAt36Level = PwWorkServer.fillStatsModifiers(self.acc, hero, res['at36level'],0)
        debug("%s" % pretty(statModAt36Level))

    def testPerfomancePathFind(self):
        self.insertHero("thundergod")
        d = self.acc.model.generateJsonDict()
        heroes_set = pathFind( d, "ModelData/Heroes/Set" )
        if heroes_set and isinstance(heroes_set, dict):
            for hero_key in heroes_set:
                hero_id = toint(hero_key)
                if hero_id:
                    hero_path = "ModelData/HeroesKeeper/Keeper/%d/Hero" % hero_id
                    hero = pathFind(d, hero_path, force_int_keys=True) #
                    debug(hero)

    awards_by_season = [
        {"Rating": 0, "Flag": "season1Vamp_simple", "RedPerls": 100, "Talents": [["G451", "G456"], ["G461", "G465"]], "Skin": "firefox_S5", "Lootboxes": ["LB_Orange234"]},
        {"Rating": 1600, "Flag": "season1Vamp_bronze", "RedPerls": 200, "Talents": [["G477", "G482"], ["G487", "G492"]], "Skin": "firefox_S5", "Lootboxes": []},
        {"Rating": sys.maxint, "Flag": "season1Vamp_silver", "RedPerls": 300, "Talents": [["G510", "G515"], ["G520", "G526"]], "Skin": "firefox_S5", "Lootboxes": ["LB_Orange234_Set4", "LB_Orange234_Set5"]}
    ]

    def _testSeasonsRewards0(self):
        arr_seasons_settings = self.acc.SD.getAllSeasons()
        hero = self.getAnyHero()
        hero.lastPlayed = arr_seasons_settings[0]['startTime'] + 1
        hero.Rating = 1599
        self.acc.db.auid = self.acc.auid
        perlsBefor = self.acc.model.Resources.Perl
        ratingBefor = hero.Rating
        self.acc.model.collectSeasonAwards(None, self.acc, arr_seasons_settings[0], arr_seasons_settings[1],
            self.awards_by_season, self.__get_rating_change, {}, False)
        self.__checkSeasonReward(0, perlsBefor, hero, ratingBefor, arr_seasons_settings[0]["persistentId"])

    def _testSeasonsRewards1(self):
        arr_seasons_settings = self.acc.SD.getAllSeasons()
        hero = self.getAnyHero()
        hero.lastPlayed = arr_seasons_settings[0]['startTime'] + 1
        hero.Rating = 1699
        self.acc.db.auid = self.acc.auid
        perlsBefor = self.acc.model.Resources.Perl
        ratingBefor = hero.Rating
        self.acc.model.collectSeasonAwards(None, self.acc, arr_seasons_settings[0], arr_seasons_settings[1],
            self.awards_by_season, self.__get_rating_change, {}, False)
        self.__checkSeasonReward(1, perlsBefor, hero, ratingBefor, arr_seasons_settings[0]["persistentId"])

    def _testSeasonsRewards2(self):
        arr_seasons_settings = self.acc.SD.getAllSeasons()
        hero = self.getAnyHero()
        hero.lastPlayed = arr_seasons_settings[0]['startTime'] + 1
        hero.Rating = 1699
        self.acc.db.auid = self.acc.auid
        perlsBefor = self.acc.model.Resources.Perl
        ratingBefor = hero.Rating
        self.acc.model.collectSeasonAwards(None, self.acc, arr_seasons_settings[0], arr_seasons_settings[1],
            self.awards_by_season, self.__get_rating_change, {str(hero.PersistentId): 10}, False)
        self.__checkSeasonReward(2, perlsBefor, hero, ratingBefor, arr_seasons_settings[0]["persistentId"])

    def testSeasonReward3(self):
        arr_seasons_settings = self.acc.SD.getAllSeasons()
        hero1 = self.acc.model.getHeroByID(self.acc.model.Heroes.keys()[0])
        hero1.lastPlayed = arr_seasons_settings[0]['startTime'] + 1
        hero1.Rating = 1699
        hero2 = self.acc.model.getHeroByID(self.acc.model.Heroes.keys()[1])
        hero2.lastPlayed = arr_seasons_settings[0]['startTime'] + 1
        hero2.Rating = 1699
        self.acc.db.auid = self.acc.auid

        perlsBefor = self.acc.model.Resources.Perl
        rating1Befor = hero1.Rating
        rating2Befor = hero2.Rating
        skinsBefor = len(self.acc.model.SkinsKeeper)
        flagsBefor = len(self.acc.model.Flags)
        lbBefor = len(self.acc.model.Lootboxes)

        self.acc.model.collectSeasonAwards(None, self.acc, arr_seasons_settings[0], arr_seasons_settings[1],
                                           self.awards_by_season, self.__get_rating_change,
                                           {str(hero1.PersistentId): 10, str(hero2.PersistentId): 100}, False)

        seasonAwardInfo = self.acc.model.SeasonsAwardsInfo[crc32(arr_seasons_settings[0]["persistentId"])]
        # for hero
        assert hero1.Rating == rating1Befor
        assert hero2.Rating == rating2Befor
        # TODO: talents
        assert len(seasonAwardInfo.Lootboxes) == 2
        assert sum(1 for lb in seasonAwardInfo.Lootboxes.keys() if lb == crc32('LB_Orange234_Set4')) == 1
        assert sum(1 for lb in seasonAwardInfo.Lootboxes.keys() if lb == crc32('LB_Orange234_Set5')) == 1
        assert len(self.acc.model.Lootboxes) == lbBefor + 2
        assert sum(1 for lb in self.acc.model.Lootboxes.values() if lb.PersistentId == crc32('LB_Orange234_Set4')) == 1
        assert sum(1 for lb in self.acc.model.Lootboxes.values() if lb.PersistentId == crc32('LB_Orange234_Set5')) == 1
        # once
        assert seasonAwardInfo.RedPerls == 300
        assert self.acc.model.Resources.Perl == perlsBefor + 300
        assert seasonAwardInfo.Skin == crc32('firefox_S5')
        assert len(self.acc.model.SkinsKeeper) == skinsBefor + 1
        assert sum(1 for s in self.acc.model.SkinsKeeper.itervalues() if s.PersistentId == crc32('firefox_S5')) == 1
        assert seasonAwardInfo.Flag == 'season1Vamp_silver'
        assert len(self.acc.model.Flags) == flagsBefor + 1
        assert sum(1 for f in self.acc.model.Flags if f == 'season1Vamp_silver') == 1


    def __get_rating_change(self, rating):
        return 0

    def __checkSeasonReward(self, rewardIdx, perlsBefor, hero, ratingBefor, prevSeasonId):
        seasonAwardInfo = self.acc.model.SeasonsAwardsInfo[crc32(prevSeasonId)]
        # flag
        assert seasonAwardInfo.Flag == self.awards_by_season[rewardIdx]['Flag']
        assert self.awards_by_season[rewardIdx]['Flag'] in self.acc.model.Flags
        # perl
        assert seasonAwardInfo.RedPerls == self.awards_by_season[rewardIdx]['RedPerls']
        assert self.acc.model.Resources.Perl == perlsBefor + self.awards_by_season[rewardIdx]['RedPerls']
        # talents
        givenTalents = list(seasonAwardInfo.Talents.keys())
        for talentList in self.awards_by_season[rewardIdx]['Talents']:
            talentListCrc32 = set(crc32(x) for x in talentList)
            givenTalent = next(x for x in givenTalents if x in talentListCrc32)
            givenTalents.remove(givenTalent)
            assert any(x.PersistentId == givenTalent for x in self.acc.model.UserInventory.itervalues())
        assert len(givenTalents) == 0
        # skin
        assert seasonAwardInfo.Skin == crc32(self.awards_by_season[rewardIdx]['Skin'])
        assert any(x.PersistentId == crc32(self.awards_by_season[rewardIdx]['Skin']) for x in self.acc.model.SkinsKeeper.itervalues())
        # lb
        assert len(self.awards_by_season[rewardIdx]['Lootboxes']) == len(seasonAwardInfo.Lootboxes.keys())
        lbCrc32List = list(crc32(x) for x in self.awards_by_season[rewardIdx]['Lootboxes'])
        for lb in seasonAwardInfo.Lootboxes.keys():
            assert lb in lbCrc32List
            lbCrc32List.remove(lb)
        assert len(lbCrc32List) == 0
        # rating
        assert hero.Rating == ratingBefor + 0

    def testAwardForClanWarEvent(self):
        lb_id = crc32('LB_Red567')
        assert sum(1 for _, lb in self.acc.model.Lootboxes.iteritems() if lb.PersistentId == lb_id) == 0
        self.acc.model.awardForClanWarEvent(1, 1, self.acc)
        assert sum(1 for _, lb in self.acc.model.Lootboxes.iteritems() if lb.PersistentId == lb_id) == 1


if __name__ == "__main__":
    unittest.main()
