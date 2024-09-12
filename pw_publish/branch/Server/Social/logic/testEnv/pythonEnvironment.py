# -*- coding: utf-8 -*-
# (C) Vadim Petrov 2011, Nival

import os, sys, imp, logging, math

realpath = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.abspath(realpath + '/../..'))
sys.path.append(os.path.abspath(realpath + '/../../cfg'))
from base.helpers import *

import xdbload
import cfg
from modeldata.ModelData import ModelData
from friendsdata.FriendsData import FriendsData
from party.PartyData import PartyData
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from ifactory import IfaceFactory
import ibilling
from binascii import crc32
from ipersonserver import IPersonServer
from subaction import *
from guild.iguildservice import IDummyGuildService
from pwaccount import UserAccount
from ixchange import IFakeSocialExchange
import coord_cfg
import CC
from config.MultiConfig import *
from modeldata.MultiStaticData import MultiStaticData
from ihttp import IHttpDummyPeerNotify
from handlers import SOCAGG_VERSION
from idata import IData

addRelPath('..')
addRelPath('../requests')

FAKE_PWSOC_SERVER_VERSION = "1.2.3"


##DEFAULT_LOG_LEVEL = logging.INFO

class FakeWSGuidGenerator:
    def __init__(self, start_value=0):
        self.inc = start_value

    def nextInt64GUID(self, key):
        self.inc += 1
        return self.inc

    def updateGameDataToPersonServer(self, acc):
        pass


class IFakePersonServerForLogic(IPersonServer):
    def addFriend(self, auid, friend_auid, callback, **kwargs):
        callback(None)

    def deleteFriend(self, auid, friend_auid, callback, **kwargs):
        callback(None)


class IFakeChatForLogic:
    def addUser(self, auid, key, nick, fraction, muted, mutetime, locale, callback):
        callback(None)


class fakeSQL:
    def setNick(self, arg1, arg2, callback):
        callback({'p': 1, 'r': [
            ClassDict(idok=-1)]})  # возвращаем id_ok<0, чтобы SubAction не беспокоился насчет записи в файл никнеймов

    def removeOldNick(self, uid, old_nick, old_nick_encoding):
        pass

    def findUidByNick(self, nick_utf8, callback):
        if nick_utf8 == 'used_nick':
            # мы нашли что-то (пользователя)
            callback({'p': 1, 'r': [{'something': 0}]})
        else:
            # не нашли пользователя с таким ником
            callback({'p': 1, 'r': []})


def generateFakeFriends():
    friendsdata = FriendsData()
    friendsdata.init(None)

    friend_id = friendsdata.addNewFriend()
    friend = friendsdata.getFriendByID(friend_id)
    friend.person_uid = 1
    friend.nickName = "Fake_Male_1"
    friend.gender = 1
    friend.fraction = 0
    friend.fame = 3500
    friend.online = True
    friend.lastLoginTime = time.time()
    friend.lastLogoutTime = time.time()
    friendsdata.myFriends.add(friend_id)

    friend_id = friendsdata.addNewFriend()
    friend = friendsdata.getFriendByID(friend_id)
    friend.person_uid = 2
    friend.nickName = "Fake_Female_1"
    friend.gender = 2
    friend.fraction = 0
    friend.fame = 3500
    friend.online = True
    friend.lastLoginTime = time.time()
    friend.lastLogoutTime = time.time()
    friendsdata.myFriends.add(friend_id)

    friend_id = friendsdata.addNewFriend()
    friend = friendsdata.getFriendByID(friend_id)
    friend.person_uid = 3
    friend.nickName = "Fake_Male_2"
    friend.gender = 1
    friend.fraction = 0
    friend.fame = 3500
    friend.online = True
    friend.lastLoginTime = time.time()
    friend.lastLogoutTime = time.time()
    friendsdata.myFriends.add(friend_id)

    return friendsdata


class PythonEnvironment:
    def __init__(self, SD, I):
        options_xdb_path = "../../xdb"
        cfg.DLCs_INFO = coord_cfg.COORDINATOR_DLCS
        cfg.MUID_TO_DLCS = coord_cfg.COORDINATOR_MUID_TO_DLCS
        cfg.TOURNAMENT_SERVER = coord_cfg.COORDINATOR_TOURNAMENT_SERVER
        cfg.TOURNAMENT_SERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_SERVER_ADDR
        cfg.TOURNAMENT_XSERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_XSERVER_ADDR
        cfg.TOURNAMENT_SPECTATOR_AUIDS = coord_cfg.COORDINATOR_TOURNAMENT_SPECTATOR_AUIDS
        cfg.TOURNAMENT_APPLY_RESULTS = coord_cfg.COORDINATOR_TOURNAMENT_APPLY_RESULTS
        # logging.info( "Loading StaticData..." )
        self.I = I
        self.I.coord_res = {}
        self.I.coord_res["deploy_name"] = "RU"
        self.I.WS.reset()
        self.I.BILL = IfaceFactory.makeBillingInterface("dummy", self.I)
        self.I.GS = IDummyGuildService()
        self.I.SEX = IFakeSocialExchange(HTTP=None)
        self.I.HTTP = IHttpDummyPeerNotify()
        self.I.AGG = IfaceFactory.makeSocAggInterface("dummy", "", SOCAGG_VERSION)  # пустая болванка
        self.I.DATA = IData()
        self.I.FRIENDS = IfaceFactory.makeFriendServiceInterface("none")
        self.uid = 1
        self.acc = UserAccount(uid=self.uid, guest=0, pending_events=[])
        self.acc.sex = 1  # male
        self.acc.loaded = 1
        self.acc.db = ClassDict()
        self.acc.data = ClassDict()
        self.acc.auid = 1
        self.acc.db.auid = 1
        self.acc.db.castle_roll = {CC.REROLL_ADDITIONAL_PROBABILITIES: {}, CC.REROLL_DAILY_PROBABILITIES: {},
                                   CC.REROLL_DAILY_WEIGHTS: {}}
        self.acc.registration_date = toint(time.time())
        self.acc.snid = "fb"
        self.acc.snuid = "100001"
        self.acc.userlocale = "RU"

        self.acc.geo_info = {'region_name': '66', 'city': 'Saint Petersburg', 'longitude': 30.264199999999988,
                             'country_code3': 'RUS', 'latitude': 59.89439999999999, 'postal_code': None,
                             'country_code': 'RU', 'country_name': 'Russian Federation'}

        self.acc.Config = I.Config
        # self.acc.Config.fillStaticDataDependendValues(SD)
        self.acc.SD = I.SD.getSD(self.acc.userlocale)
        self.I.BILL.initBilling(self.acc.auid)
        self.I.EXPORT = IfaceFactory.makeExportInterface("none", None)

        self.resetEnv(SD, I)

    def resetEnv(self, SD, I):
        self.I.BILL.setGold(self.acc.auid, 1000)
        self.I.GS = IDummyGuildService()
        self.acc.friendsdata = generateFakeFriends()
        self.acc.partydata = PartyData()
        self.acc.partydata.init(None)
        self.acc.guilddata = GuildData()
        self.acc.guilddata.init(None)
        self.acc.guilddata.GuildSuzerain, _ = self.acc.guilddata.newGuildMapEntity()
        self.acc.guilddata.GuildSuzerain.ShortInfo, _ = self.acc.guilddata.newGuildShortInfo()
        self.acc.siegedata = SiegeData()
        self.acc.siegedata.init(None)
        self.acc.db.currentGuildWarEvent = 1
        self.acc.db.guildAuid = 1
        self.acc.db.fraction = "A"
        self.acc.db.nick = "TestNick"
        self.acc.db.nickChanged = 0
        self.acc.db.fractionChanged = 0
        self.acc.db.dlcs = []
        self.acc.login = "TestLogin"
        self.I.Config = MultiConfig()
        self.I.Config.fillStaticDataDependendValues(SD)
        self.acc.Config = self.I.Config
        self.add_default_events()

    def runTest(self, test):
        self.changeList = {}
        self.changeListIdx = 0

        t0 = time.clock()
        self.I.MD.newModel(self.acc, self.I, FAKE_PWSOC_SERVER_VERSION, random_heroes=-1, random_items=-1,
                           fraction=self.acc.db.fraction, db=self.acc.db, guest=self.acc.guest, old_md=None)
        # сохраним свежесозданные данные, и загрузим обратно (так мы убедимся, что после сериализации ModelData по-прежнему проходит все тесты)
        t1 = time.clock()
        save_data_unicode = self.I.PDM.saveData(self.acc, zip=False)
        t2 = time.clock()
        self.I.PDM.loadAccountData(self.acc, save_data_unicode)
        t3 = time.clock()
        # warn( "-- md.new: %.3f, md.save: %.3f, md.load: %.3f" % (t1-t0, t2-t1, t3-t2) )

        t0 = time.clock()
        self.resetEnv(self.I.SD, self.I)
        test(self)
        t1 = time.clock()
        warn("run time: %.3f (test %s)" % (t1 - t0, test.__name__))

    def execActions(self, requests):
        for action, req in requests:
            if 'rid' not in req.arguments:
                req.arguments['rid'] = ["0"]
                req.rid = 0
            handler = action(req, self.callback, request=self)
            handler.onStart()
            time.sleep(0.01)
            self.checkJson()
        return self.changeList

    def checkJson(self):
        assert (self.changeList and len(self.changeList) > 0)
        changeList = self.changeList.get(self.changeListIdx - 1)
        assert changeList.get("ok") == 1 or changeList.get("ok") == 0
        self.info("changeList: %s" % self.pretty(changeList))

    def getChangeList(self):
        return self.changeList

    def clearChangeList(self):
        self.changeList = {}

    def getChangeListIdx(self):
        return self.changeListIdx

    def callback(self, reply):
        self.changeList.update({self.changeListIdx: reply})
        self.changeListIdx += 1

    def info(self, text):
        logging.info(text)

    def err(self, text):
        logging.error(text)

    def pretty(self, obj):
        if isinstance(obj, dict):
            for key in obj:
                if isinstance(obj[key], ResponseObject):
                    obj[key] = obj[key].makeDict()
        return json_pretty(obj)

    def getFlatParams(self, except_list=[]):
        arg_dict = {"post_data": ""}
        return arg_dict

    def generate_resources(self, amount):
        resources = self.acc.model.createResourcesTable()
        resources.Population = amount
        resources.Gold = amount
        resources.Perl = amount
        resources.RedPerl = amount
        resources.Resource1 = amount
        resources.Resource2 = amount
        resources.Resource3 = amount
        resources.Silver = amount
        self.I.BILL.setGold(self.acc.auid, resources.Gold)
        return resources

    def compare_price(self, p1, p2, p3):
        if isinstance(p1, dict):
            price1 = self.I.SD.getMainSD().copyPrice(p1)
        else:
            price1 = p1
        if isinstance(p2, dict):
            price2 = self.I.SD.getMainSD().copyPrice(p2)
        else:
            price2 = p2
        if isinstance(p3, dict):
            price3 = self.I.SD.getMainSD().copyPrice(p3)
        else:
            price3 = p3

        if (price1.Gold == price2.Gold + price3.Gold) and \
                (price1.Perl == price2.Perl + price3.Perl) and \
                (price1.RedPerl == price2.RedPerl + price3.RedPerl) and \
                (price1.Resource1 == price2.Resource1 + price3.Resource1) and \
                (price1.Resource2 == price2.Resource2 + price3.Resource2) and \
                (price1.Resource3 == price2.Resource3 + price3.Resource3) and \
                (price1.Silver == price2.Silver + price3.Silver):
            p1_currencies = set(price1.Currencies.keys())
            p2_currencies = set(price2.Currencies.keys())
            p3_currencies = set(price3.Currencies.keys())
            if p1_currencies.difference(p2_currencies) or p1_currencies.difference(p3_currencies):
                return False
            for k,v in price1.Currencies.iteritems():
                if v != price2.Currencies[k] + price3.Currencies[k]:
                    return False
            return True
        return False

    def add_construction(self, modeldata, persistent, level=0):
        construction_id = modeldata.addNewConstruction()
        construction = modeldata.getConstructionByID(construction_id)
        construction.PersistentId = crc32(persistent)
        construction.Position.X = 22
        construction.Position.Y = 35
        construction.Position.Pitch = 0
        construction.Level = level
        construction.cycle = -1
        modeldata.Buildings.add(construction_id)
        return construction

    def add_hero(self, modeldata, persistent):
        hero_id = modeldata.addNewHero()
        hero = modeldata.getHeroByID(hero_id)
        hero.PersistentId = crc32(persistent)
        hero.class_name = persistent
        hero.Hired = True

        modeldata.Heroes.add(hero_id)
        for i in xrange(3):
            ts_id = modeldata.addNewTalentSet()
            ts = modeldata.getTalentSetByID(ts_id)
            hero.TalentSets.add(i, ts.id)
            staticHero = self.acc.SD.getStaticHero( hero )
            hero.TalentSets[i].TalentSetCrc = self.acc.SD.getTalantSetCrc(staticHero, i, self.acc.getConfig())
            for idx in xrange(0, 10):
                hero.TalentSets[i].ActionBar[idx] = -1
                hero.TalentSets[i].InstaCast.set(idx, False)

        return hero

    def add_talent(self, modeldata, persistent):
        if isinstance(persistent, (int, long)):
            pertsistentId = persistent
        else:
            pertsistentId = crc32(persistent)

        talent_id = modeldata.addNewTalent()
        talent = modeldata.getTalentByID(talent_id)
        talent.PersistentId = pertsistentId
        talent.IsNew = False

        return talent

    def add_guild_buff(self, id):
        staticBuff = self.acc.SD.getGuildBufById(crc32(id))
        assert staticBuff

        expireTime = int(time.time() + int(staticBuff['duration']))
        self.acc.model.addGuildBuff(self.acc, self.acc.SD, expireTime, staticBuff)

    def add_heroes_to_construction(self, modeldata, construction, amount):
        heroes = []
        for heroId in modeldata.HeroesKeeper:
            hero = modeldata.getHeroByID(heroId)
            if not hero in construction.HeroesInBuilding:
                construction.HeroesInBuilding.add(hero)
                hero.InBuildings.add(construction)
                heroes.append(hero)
                if len(heroes) >= amount:
                    return heroes

        assert len(heroes) >= amount
        return heroes

    def add_default_events(self):
        lampEvent = {"persistentId": 66,
                     "startTime": int(time.time()) - 60 * 60,
                     "endTime": int(time.time()) + 60 * 60,
                     "newValue": {"eventDescription": utf8convert('lamp \"2, 3\"')}}
        giveLampEvent = {"persistentId": 67,
                         "startTime": int(time.time()) - 60 * 60,
                         "endTime": int(time.time()) + 60 * 60,
                         "newValue": {"eventDescription": utf8convert('give_lamp \"20, 10000, 10, 86400\"')}}

        self.I.Config.events.append(event(lampEvent))
        self.I.Config.events.append(event(giveLampEvent))

    def get_paid_cost(self, price1, price2):
        cost = 0
        cost += float(price1.Gold) - float(price2.Gold)
        cost += float(price1.Perl) - float(price2.Perl)
        cost += float(price1.RedPerl) - float(price2.RedPerl)
        cost += float(price1.Resource1) - float(price2.Resource1)
        cost += float(price1.Resource2) - float(price2.Resource2)
        cost += float(price1.Resource3) - float(price2.Resource3)
        cost += float(price1.Silver) - float(price2.Silver)

        return cost

    def get_cost(self, price1, coef=1):
        cost = 0
        cost += float(price1.Gold) * coef
        cost += float(price1.Perl) * coef
        cost += float(price1.RedPerl) * coef
        cost += float(price1.Resource1) * coef
        cost += float(price1.Resource2) * coef
        cost += float(price1.Resource3) * coef
        cost += float(price1.Silver) * coef

        return int(math.floor(cost))

    def printAssert(self, objLeftToCompare, objRightToCompare, isTrueReq=True):
        if objLeftToCompare == objRightToCompare if isTrueReq else objLeftToCompare != objRightToCompare:
            return
        lineWithParams = traceback.format_stack()
        params = lineWithParams[len(lineWithParams) - 2].splitlines()[1].strip().split('(')[1].split(')')[0].split(',')

        error = "Object equals mismatch... \n\nMust be: '{}'({}) {} '{}'({})".format(
            params[0].strip(),
            objLeftToCompare,
            "==" if isTrueReq else "!=",
            params[1].strip(),
            objRightToCompare)

        assert False, error
