# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import AdminMessage
import Construction
import ConstructionPosition
import ConstructionQuest
import DynamicObjective
import DynamicQuest
import DynamicQuestAward
import DynamicQuestLampAward
import DynamicQuestPullInfo
import DynamicQuestToTalentsMetaInf
import DynamicQuestUpgradeHeroTalentsAward
import FlagInfo
import ForgeRoll
import Friends
import GuardInfo
import GuildApplication
import GuildBankInfo
import GuildBuf
import GuildInvite
import Hero
import HeroSkins
import HeroStats
import HonorInfo
import HonorReward
import InstantCondition
import LampEventInfo
import LastStartedMap
import Lootbox
import LootboxReward
import LordInfo
import LordRatings
import MapInfo
import MarketingEventsInfo
import MDCondition
import Objective
import PreCondition
import Quest
import QuestEventProgression
import RerollShop
import RerollShopItem
import ResourceTable
import SeasonAwards
import SeasonEventProgression
import SeasonInfo
import SessionCondition
import SessionResults
import ShortSessionInfo
import SimpleFriend
import Skin
import StatisticEvent
import Talent
import TalentSet
import TalentUpgradeEntity
import TournamentInfo
import TournamentTicket
import TradeEventProgression
import UpgradeHeroTalentsInfo
import UserStatistics
import Version

import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from ModelDataCustom import ModelDataCustom

class ModelData(ChangeHandler, ModelDataCustom, IChangeWriter, IAbstractModelData, AutoIncGuidGenerator):
    _changeFields = {
        "ActiveEventSkins":1,
        "CompletedDynamicQuests":1,
        "EventSkins":1,
        "FatClientServerTime":1,
        "Flags":1,
        "LossDynamicQuests":1,
        "PendingQuests":1,
        "ServerTime":1,
        "StatisticEventId":1,
        "UserInventoryLimit":1,
    } 


    def __init__(self):
        ModelDataCustom.__init__(self)
        ChangeHandler.__init__(self, u"/", self)
        AutoIncGuidGenerator.__init__(self)
        self._serializator = JSONSerialization(self)
        self.__dict__["AdminMessagesKeeper"] = Keeper(self)
        self.__dict__["ConstructionsKeeper"] = Keeper(self)
        self.__dict__["DynamicObjectivesKeeper"] = Keeper(self)
        self.__dict__["DynamicQuestAwardsKeeper"] = Keeper(self)
        self.__dict__["DynamicQuestKeeper"] = Keeper(self)
        self.__dict__["DynamicQuestPullInfoKeeper"] = Keeper(self)
        self.__dict__["FriendsKeeper"] = Keeper(self)
        self.__dict__["GuildApplicationKeeper"] = Keeper(self)
        self.__dict__["GuildBankInfoKeeper"] = Keeper(self)
        self.__dict__["GuildBufsKeeper"] = Keeper(self)
        self.__dict__["GuildInvitesKeeper"] = Keeper(self)
        self.__dict__["HeroesKeeper"] = Keeper(self)
        self.__dict__["ItemsKeeper"] = Keeper(self)
        self.__dict__["LootboxKeeper"] = Keeper(self)
        self.__dict__["MapInfoKeeper"] = Keeper(self)
        self.__dict__["ObjectivesKeeper"] = Keeper(self)
        self.__dict__["PreConditionsKeeper"] = Keeper(self)
        self.__dict__["QuestEventProgressionKeeper"] = Keeper(self)
        self.__dict__["QuestsKeeper"] = Keeper(self)
        self.__dict__["RerollShopItemsKeeper"] = Keeper(self)
        self.__dict__["SeasonAwardsKeeper"] = Keeper(self)
        self.__dict__["SeasonEventProgressionKeeper"] = Keeper(self)
        self.__dict__["SeasonInfoKeeper"] = Keeper(self)
        self.__dict__["SkinsKeeper"] = Keeper(self)
        self.__dict__["StatisticEventsKeeper"] = Keeper(self)
        self.__dict__["TalentSetsKeeper"] = Keeper(self)
        self.__dict__["TalentUpgradeEntitiesKeeper"] = Keeper(self)
        self.__dict__["TradeEventProgressionKeeper"] = Keeper(self)
        self.__dict__["ActiveEventSkins"] = SimpleList(self)
        self.__dict__["ActiveQuests"] = Set(self)
        self.__dict__["AdminMessages"] = Set(self)
        self.__dict__["Buildings"] = Set(self)
        self.__dict__["CompletedDynamicQuests"] = SimpleList(self)
        self.__dict__["CompletedQuests"] = Set(self)
        self.__dict__["DynamicQuestPulls"] = Set(self)
        self.__dict__["DynamicQuests"] = Set(self)
        self.__dict__["EventSkins"] = SimpleList(self)
        self.__dict__["FatClientServerTime"] = 0
        self.__dict__["FlagInfo"] = FlagInfo.FlagInfo(self)
        self.__dict__["Flags"] = SimpleList(self)
        self.__dict__["Friends"] = Friends.Friends(self)
        self.__dict__["GuildApplications"] = Set(self)
        self.__dict__["GuildBufs"] = Set(self)
        self.__dict__["Heroes"] = Set(self)
        self.__dict__["IncomingGuildInvites"] = Set(self)
        self.__dict__["Lootboxes"] = Set(self)
        self.__dict__["LordInfo"] = LordInfo.LordInfo(self)
        self.__dict__["LossDynamicQuests"] = SimpleList(self)
        self.__dict__["MarketingEventsInfo"] = MarketingEventsInfo.MarketingEventsInfo(self)
        self.__dict__["PendingQuests"] = SimpleList(self)
        self.__dict__["Pocket"] = Set(self)
        self.__dict__["QuestEvents"] = Collection(self)
        self.__dict__["RerollShopInfo"] = RerollShop.RerollShop(self)
        self.__dict__["Resources"] = ResourceTable.ResourceTable(self)
        self.__dict__["ResourcesLimit"] = ResourceTable.ResourceTable(self)
        self.__dict__["SeasonEvents"] = Collection(self)
        self.__dict__["SeasonsAwardsInfo"] = Collection(self)
        self.__dict__["ServerTime"] = 0
        self.__dict__["StatisticEventId"] = 0
        self.__dict__["StatisticEvents"] = Set(self)
        self.__dict__["Statistics"] = UserStatistics.UserStatistics(self)
        self.__dict__["TalentUpgradeEntities"] = Set(self)
        self.__dict__["TournamentInfo"] = TournamentInfo.TournamentInfo(self)
        self.__dict__["TradeEvents"] = Collection(self)
        self.__dict__["UserInventory"] = Set(self)
        self.__dict__["UserInventoryLimit"] = 32
        self.__dict__["version"] = Version.Version(self)


    def init(self, changeWriter):
        self.write(changeWriter)
        self.AdminMessagesKeeper.init(u"AdminMessagesKeeper", self, "AdminMessage")
        self.ConstructionsKeeper.init(u"ConstructionsKeeper", self, "Construction")
        self.DynamicObjectivesKeeper.init(u"DynamicObjectivesKeeper", self, "DynamicObjective")
        self.DynamicQuestAwardsKeeper.init(u"DynamicQuestAwardsKeeper", self, "DynamicQuestAward")
        self.DynamicQuestKeeper.init(u"DynamicQuestKeeper", self, "DynamicQuest")
        self.DynamicQuestPullInfoKeeper.init(u"DynamicQuestPullInfoKeeper", self, "DynamicQuestPullInfo")
        self.FriendsKeeper.init(u"FriendsKeeper", self, "SimpleFriend")
        self.GuildApplicationKeeper.init(u"GuildApplicationKeeper", self, "GuildApplication")
        self.GuildBankInfoKeeper.init(u"GuildBankInfoKeeper", self, "GuildBankInfo")
        self.GuildBufsKeeper.init(u"GuildBufsKeeper", self, "GuildBuf")
        self.GuildInvitesKeeper.init(u"GuildInvitesKeeper", self, "GuildInvite")
        self.HeroesKeeper.init(u"HeroesKeeper", self, "Hero")
        self.ItemsKeeper.init(u"ItemsKeeper", self, "Talent")
        self.LootboxKeeper.init(u"LootboxKeeper", self, "Lootbox")
        self.MapInfoKeeper.init(u"MapInfoKeeper", self, "MapInfo")
        self.ObjectivesKeeper.init(u"ObjectivesKeeper", self, "Objective")
        self.PreConditionsKeeper.init(u"PreConditionsKeeper", self, "PreCondition")
        self.QuestEventProgressionKeeper.init(u"QuestEventProgressionKeeper", self, "QuestEventProgression")
        self.QuestsKeeper.init(u"QuestsKeeper", self, "Quest")
        self.RerollShopItemsKeeper.init(u"RerollShopItemsKeeper", self, "RerollShopItem")
        self.SeasonAwardsKeeper.init(u"SeasonAwardsKeeper", self, "SeasonAwards")
        self.SeasonEventProgressionKeeper.init(u"SeasonEventProgressionKeeper", self, "SeasonEventProgression")
        self.SeasonInfoKeeper.init(u"SeasonInfoKeeper", self, "SeasonInfo")
        self.SkinsKeeper.init(u"SkinsKeeper", self, "Skin")
        self.StatisticEventsKeeper.init(u"StatisticEventsKeeper", self, "StatisticEvent")
        self.TalentSetsKeeper.init(u"TalentSetsKeeper", self, "TalentSet")
        self.TalentUpgradeEntitiesKeeper.init(u"TalentUpgradeEntitiesKeeper", self, "TalentUpgradeEntity")
        self.TradeEventProgressionKeeper.init(u"TradeEventProgressionKeeper", self, "TradeEventProgression")
        self.ActiveEventSkins.init(u"ActiveEventSkins", self)
        self.ActiveQuests.init(self.QuestsKeeper, u"ActiveQuests", self)
        self.AdminMessages.init(self.AdminMessagesKeeper, u"AdminMessages", self)
        self.Buildings.init(self.ConstructionsKeeper, u"Buildings", self)
        self.CompletedDynamicQuests.init(u"CompletedDynamicQuests", self)
        self.CompletedQuests.init(self.QuestsKeeper, u"CompletedQuests", self)
        self.DynamicQuestPulls.init(self.DynamicQuestPullInfoKeeper, u"DynamicQuestPulls", self)
        self.DynamicQuests.init(self.DynamicQuestKeeper, u"DynamicQuests", self)
        self.EventSkins.init(u"EventSkins", self)
        self.FlagInfo.setPath(u"FlagInfo")
        self.Flags.init(u"Flags", self)
        self.Friends.setPath(u"Friends")
        self.GuildApplications.init(self.GuildApplicationKeeper, u"GuildApplications", self)
        self.GuildBufs.init(self.GuildBufsKeeper, u"GuildBufs", self)
        self.Heroes.init(self.HeroesKeeper, u"Heroes", self)
        self.IncomingGuildInvites.init(self.GuildInvitesKeeper, u"IncomingGuildInvites", self)
        self.Lootboxes.init(self.LootboxKeeper, u"Lootboxes", self)
        self.LordInfo.setPath(u"LordInfo")
        self.LossDynamicQuests.init(u"LossDynamicQuests", self)
        self.MarketingEventsInfo.setPath(u"MarketingEventsInfo")
        self.PendingQuests.init(u"PendingQuests", self)
        self.Pocket.init(self.ConstructionsKeeper, u"Pocket", self)
        self.QuestEvents.init(self.QuestEventProgressionKeeper, u"QuestEvents", self)
        self.RerollShopInfo.setPath(u"RerollShopInfo")
        self.Resources.setPath(u"Resources")
        self.ResourcesLimit.setPath(u"ResourcesLimit")
        self.SeasonEvents.init(self.SeasonEventProgressionKeeper, u"SeasonEvents", self)
        self.SeasonsAwardsInfo.init(self.SeasonAwardsKeeper, u"SeasonsAwardsInfo", self)
        self.StatisticEvents.init(self.StatisticEventsKeeper, u"StatisticEvents", self)
        self.Statistics.setPath(u"Statistics")
        self.TalentUpgradeEntities.init(self.TalentUpgradeEntitiesKeeper, u"TalentUpgradeEntities", self)
        self.TournamentInfo.setPath(u"TournamentInfo")
        self.TradeEvents.init(self.TradeEventProgressionKeeper, u"TradeEvents", self)
        self.UserInventory.init(self.ItemsKeeper, u"UserInventory", self)
        self.version.setPath(u"version")


    @staticmethod
    def initJsonTypes(TCustomModelData): # конечный класс CustomModelData будет передавать снаружи, из datamanager
        if "ModelData" not in JSONSerialization.SERIALIZABLE_CLASSES:
            JSONSerialization.updateOurTypes((TCustomModelData,
            AdminMessage.AdminMessage,
            Construction.Construction,
            ConstructionPosition.ConstructionPosition,
            ConstructionQuest.ConstructionQuest,
            DynamicObjective.DynamicObjective,
            DynamicQuest.DynamicQuest,
            DynamicQuestAward.DynamicQuestAward,
            DynamicQuestLampAward.DynamicQuestLampAward,
            DynamicQuestPullInfo.DynamicQuestPullInfo,
            DynamicQuestToTalentsMetaInf.DynamicQuestToTalentsMetaInf,
            DynamicQuestUpgradeHeroTalentsAward.DynamicQuestUpgradeHeroTalentsAward,
            FlagInfo.FlagInfo,
            ForgeRoll.ForgeRoll,
            Friends.Friends,
            GuardInfo.GuardInfo,
            GuildApplication.GuildApplication,
            GuildBankInfo.GuildBankInfo,
            GuildBuf.GuildBuf,
            GuildInvite.GuildInvite,
            Hero.Hero,
            HeroSkins.HeroSkins,
            HeroStats.HeroStats,
            HonorInfo.HonorInfo,
            HonorReward.HonorReward,
            InstantCondition.InstantCondition,
            LampEventInfo.LampEventInfo,
            LastStartedMap.LastStartedMap,
            Lootbox.Lootbox,
            LootboxReward.LootboxReward,
            LordInfo.LordInfo,
            LordRatings.LordRatings,
            MapInfo.MapInfo,
            MarketingEventsInfo.MarketingEventsInfo,
            MDCondition.MDCondition,
            Objective.Objective,
            PreCondition.PreCondition,
            Quest.Quest,
            QuestEventProgression.QuestEventProgression,
            RerollShop.RerollShop,
            RerollShopItem.RerollShopItem,
            ResourceTable.ResourceTable,
            SeasonAwards.SeasonAwards,
            SeasonEventProgression.SeasonEventProgression,
            SeasonInfo.SeasonInfo,
            SessionCondition.SessionCondition,
            SessionResults.SessionResults,
            ShortSessionInfo.ShortSessionInfo,
            SimpleFriend.SimpleFriend,
            Skin.Skin,
            StatisticEvent.StatisticEvent,
            Talent.Talent,
            TalentSet.TalentSet,
            TalentUpgradeEntity.TalentUpgradeEntity,
            TournamentInfo.TournamentInfo,
            TournamentTicket.TournamentTicket,
            TradeEventProgression.TradeEventProgression,
            UpgradeHeroTalentsInfo.UpgradeHeroTalentsInfo,
            UserStatistics.UserStatistics,
            Version.Version,
            ))
            JSONSerialization.SERIALIZABLE_CLASSES.update(
            { "ModelData" : TCustomModelData
            , "Keeper" : Keeper
            , "Set" : Set
            , "SimpleList" : SimpleList
            , "SimpleDict" : SimpleDict
            , "Collection" : Collection
            , "Ref" : Ref
            , "AdminMessage" : AdminMessage.AdminMessage
            , "Construction" : Construction.Construction
            , "ConstructionPosition" : ConstructionPosition.ConstructionPosition
            , "ConstructionQuest" : ConstructionQuest.ConstructionQuest
            , "DynamicObjective" : DynamicObjective.DynamicObjective
            , "DynamicQuest" : DynamicQuest.DynamicQuest
            , "DynamicQuestAward" : DynamicQuestAward.DynamicQuestAward
            , "DynamicQuestLampAward" : DynamicQuestLampAward.DynamicQuestLampAward
            , "DynamicQuestPullInfo" : DynamicQuestPullInfo.DynamicQuestPullInfo
            , "DynamicQuestToTalentsMetaInf" : DynamicQuestToTalentsMetaInf.DynamicQuestToTalentsMetaInf
            , "DynamicQuestUpgradeHeroTalentsAward" : DynamicQuestUpgradeHeroTalentsAward.DynamicQuestUpgradeHeroTalentsAward
            , "FlagInfo" : FlagInfo.FlagInfo
            , "ForgeRoll" : ForgeRoll.ForgeRoll
            , "Friends" : Friends.Friends
            , "GuardInfo" : GuardInfo.GuardInfo
            , "GuildApplication" : GuildApplication.GuildApplication
            , "GuildBankInfo" : GuildBankInfo.GuildBankInfo
            , "GuildBuf" : GuildBuf.GuildBuf
            , "GuildInvite" : GuildInvite.GuildInvite
            , "Hero" : Hero.Hero
            , "HeroSkins" : HeroSkins.HeroSkins
            , "HeroStats" : HeroStats.HeroStats
            , "HonorInfo" : HonorInfo.HonorInfo
            , "HonorReward" : HonorReward.HonorReward
            , "InstantCondition" : InstantCondition.InstantCondition
            , "LampEventInfo" : LampEventInfo.LampEventInfo
            , "LastStartedMap" : LastStartedMap.LastStartedMap
            , "Lootbox" : Lootbox.Lootbox
            , "LootboxReward" : LootboxReward.LootboxReward
            , "LordInfo" : LordInfo.LordInfo
            , "LordRatings" : LordRatings.LordRatings
            , "MapInfo" : MapInfo.MapInfo
            , "MarketingEventsInfo" : MarketingEventsInfo.MarketingEventsInfo
            , "MDCondition" : MDCondition.MDCondition
            , "Objective" : Objective.Objective
            , "PreCondition" : PreCondition.PreCondition
            , "Quest" : Quest.Quest
            , "QuestEventProgression" : QuestEventProgression.QuestEventProgression
            , "RerollShop" : RerollShop.RerollShop
            , "RerollShopItem" : RerollShopItem.RerollShopItem
            , "ResourceTable" : ResourceTable.ResourceTable
            , "SeasonAwards" : SeasonAwards.SeasonAwards
            , "SeasonEventProgression" : SeasonEventProgression.SeasonEventProgression
            , "SeasonInfo" : SeasonInfo.SeasonInfo
            , "SessionCondition" : SessionCondition.SessionCondition
            , "SessionResults" : SessionResults.SessionResults
            , "ShortSessionInfo" : ShortSessionInfo.ShortSessionInfo
            , "SimpleFriend" : SimpleFriend.SimpleFriend
            , "Skin" : Skin.Skin
            , "StatisticEvent" : StatisticEvent.StatisticEvent
            , "Talent" : Talent.Talent
            , "TalentSet" : TalentSet.TalentSet
            , "TalentUpgradeEntity" : TalentUpgradeEntity.TalentUpgradeEntity
            , "TournamentInfo" : TournamentInfo.TournamentInfo
            , "TournamentTicket" : TournamentTicket.TournamentTicket
            , "TradeEventProgression" : TradeEventProgression.TradeEventProgression
            , "UpgradeHeroTalentsInfo" : UpgradeHeroTalentsInfo.UpgradeHeroTalentsInfo
            , "UserStatistics" : UserStatistics.UserStatistics
            , "Version" : Version.Version
            })  
        else:
            err("ModelData.initJsonTypes called twice! The second call is:\n%s", errStack())

    def addNewAdminMessage(self):
        uid = self.nextGUID()
        var = AdminMessage.AdminMessage(self, uid, "AdminMessagesKeeper/"+str(uid))
        var.init_add()
        self.AdminMessagesKeeper.add(uid, var)
        return uid


    def getAdminMessageByID(self, id):
        return self.AdminMessagesKeeper.get(id)


    def newAdminMessage(self):
        _id = self.addNewAdminMessage()
        _data = self.getAdminMessageByID(_id)
        return _data, _id
    def addNewConstruction(self):
        uid = self.nextGUID()
        var = Construction.Construction(self, uid, "ConstructionsKeeper/"+str(uid))
        var.init_add()
        self.ConstructionsKeeper.add(uid, var)
        return uid


    def getConstructionByID(self, id):
        return self.ConstructionsKeeper.get(id)


    def newConstruction(self):
        _id = self.addNewConstruction()
        _data = self.getConstructionByID(_id)
        return _data, _id
    def addNewDynamicObjective(self):
        uid = self.nextGUID()
        var = DynamicObjective.DynamicObjective(self, uid, "DynamicObjectivesKeeper/"+str(uid))
        var.init_add()
        self.DynamicObjectivesKeeper.add(uid, var)
        return uid


    def getDynamicObjectiveByID(self, id):
        return self.DynamicObjectivesKeeper.get(id)


    def newDynamicObjective(self):
        _id = self.addNewDynamicObjective()
        _data = self.getDynamicObjectiveByID(_id)
        return _data, _id
    def addNewDynamicQuestAward(self):
        uid = self.nextGUID()
        var = DynamicQuestAward.DynamicQuestAward(self, uid, "DynamicQuestAwardsKeeper/"+str(uid))
        var.init_add()
        self.DynamicQuestAwardsKeeper.add(uid, var)
        return uid


    def getDynamicQuestAwardByID(self, id):
        return self.DynamicQuestAwardsKeeper.get(id)


    def newDynamicQuestAward(self):
        _id = self.addNewDynamicQuestAward()
        _data = self.getDynamicQuestAwardByID(_id)
        return _data, _id
    def addNewDynamicQuest(self):
        uid = self.nextGUID()
        var = DynamicQuest.DynamicQuest(self, uid, "DynamicQuestKeeper/"+str(uid))
        var.init_add()
        self.DynamicQuestKeeper.add(uid, var)
        return uid


    def getDynamicQuestByID(self, id):
        return self.DynamicQuestKeeper.get(id)


    def newDynamicQuest(self):
        _id = self.addNewDynamicQuest()
        _data = self.getDynamicQuestByID(_id)
        return _data, _id
    def addNewDynamicQuestPullInfo(self):
        uid = self.nextGUID()
        var = DynamicQuestPullInfo.DynamicQuestPullInfo(self, uid, "DynamicQuestPullInfoKeeper/"+str(uid))
        var.init_add()
        self.DynamicQuestPullInfoKeeper.add(uid, var)
        return uid


    def getDynamicQuestPullInfoByID(self, id):
        return self.DynamicQuestPullInfoKeeper.get(id)


    def newDynamicQuestPullInfo(self):
        _id = self.addNewDynamicQuestPullInfo()
        _data = self.getDynamicQuestPullInfoByID(_id)
        return _data, _id
    def addNewSimpleFriend(self):
        uid = self.nextGUID()
        var = SimpleFriend.SimpleFriend(self, uid, "FriendsKeeper/"+str(uid))
        var.init_add()
        self.FriendsKeeper.add(uid, var)
        return uid


    def getSimpleFriendByID(self, id):
        return self.FriendsKeeper.get(id)


    def newSimpleFriend(self):
        _id = self.addNewSimpleFriend()
        _data = self.getSimpleFriendByID(_id)
        return _data, _id
    def addNewGuildApplication(self):
        uid = self.nextGUID()
        var = GuildApplication.GuildApplication(self, uid, "GuildApplicationKeeper/"+str(uid))
        var.init_add()
        self.GuildApplicationKeeper.add(uid, var)
        return uid


    def getGuildApplicationByID(self, id):
        return self.GuildApplicationKeeper.get(id)


    def newGuildApplication(self):
        _id = self.addNewGuildApplication()
        _data = self.getGuildApplicationByID(_id)
        return _data, _id
    def addNewGuildBankInfo(self):
        uid = self.nextGUID()
        var = GuildBankInfo.GuildBankInfo(self, uid, "GuildBankInfoKeeper/"+str(uid))
        var.init_add()
        self.GuildBankInfoKeeper.add(uid, var)
        return uid


    def getGuildBankInfoByID(self, id):
        return self.GuildBankInfoKeeper.get(id)


    def newGuildBankInfo(self):
        _id = self.addNewGuildBankInfo()
        _data = self.getGuildBankInfoByID(_id)
        return _data, _id
    def addNewGuildBuf(self):
        uid = self.nextGUID()
        var = GuildBuf.GuildBuf(self, uid, "GuildBufsKeeper/"+str(uid))
        var.init_add()
        self.GuildBufsKeeper.add(uid, var)
        return uid


    def getGuildBufByID(self, id):
        return self.GuildBufsKeeper.get(id)


    def newGuildBuf(self):
        _id = self.addNewGuildBuf()
        _data = self.getGuildBufByID(_id)
        return _data, _id
    def addNewGuildInvite(self):
        uid = self.nextGUID()
        var = GuildInvite.GuildInvite(self, uid, "GuildInvitesKeeper/"+str(uid))
        var.init_add()
        self.GuildInvitesKeeper.add(uid, var)
        return uid


    def getGuildInviteByID(self, id):
        return self.GuildInvitesKeeper.get(id)


    def newGuildInvite(self):
        _id = self.addNewGuildInvite()
        _data = self.getGuildInviteByID(_id)
        return _data, _id
    def addNewHero(self):
        uid = self.nextGUID()
        var = Hero.Hero(self, uid, "HeroesKeeper/"+str(uid))
        var.init_add()
        self.HeroesKeeper.add(uid, var)
        return uid


    def getHeroByID(self, id):
        return self.HeroesKeeper.get(id)


    def newHero(self):
        _id = self.addNewHero()
        _data = self.getHeroByID(_id)
        return _data, _id
    def addNewTalent(self):
        uid = self.nextGUID()
        var = Talent.Talent(self, uid, "ItemsKeeper/"+str(uid))
        var.init_add()
        self.ItemsKeeper.add(uid, var)
        return uid


    def getTalentByID(self, id):
        return self.ItemsKeeper.get(id)


    def newTalent(self):
        _id = self.addNewTalent()
        _data = self.getTalentByID(_id)
        return _data, _id
    def addNewLootbox(self):
        uid = self.nextGUID()
        var = Lootbox.Lootbox(self, uid, "LootboxKeeper/"+str(uid))
        var.init_add()
        self.LootboxKeeper.add(uid, var)
        return uid


    def getLootboxByID(self, id):
        return self.LootboxKeeper.get(id)


    def newLootbox(self):
        _id = self.addNewLootbox()
        _data = self.getLootboxByID(_id)
        return _data, _id
    def addNewMapInfo(self):
        uid = self.nextGUID()
        var = MapInfo.MapInfo(self, uid, "MapInfoKeeper/"+str(uid))
        var.init_add()
        self.MapInfoKeeper.add(uid, var)
        return uid


    def getMapInfoByID(self, id):
        return self.MapInfoKeeper.get(id)


    def newMapInfo(self):
        _id = self.addNewMapInfo()
        _data = self.getMapInfoByID(_id)
        return _data, _id
    def addNewObjective(self):
        uid = self.nextGUID()
        var = Objective.Objective(self, uid, "ObjectivesKeeper/"+str(uid))
        var.init_add()
        self.ObjectivesKeeper.add(uid, var)
        return uid


    def getObjectiveByID(self, id):
        return self.ObjectivesKeeper.get(id)


    def newObjective(self):
        _id = self.addNewObjective()
        _data = self.getObjectiveByID(_id)
        return _data, _id
    def addNewPreCondition(self):
        uid = self.nextGUID()
        var = PreCondition.PreCondition(self, uid, "PreConditionsKeeper/"+str(uid))
        var.init_add()
        self.PreConditionsKeeper.add(uid, var)
        return uid


    def getPreConditionByID(self, id):
        return self.PreConditionsKeeper.get(id)


    def newPreCondition(self):
        _id = self.addNewPreCondition()
        _data = self.getPreConditionByID(_id)
        return _data, _id
    def addNewQuestEventProgression(self):
        uid = self.nextGUID()
        var = QuestEventProgression.QuestEventProgression(self, uid, "QuestEventProgressionKeeper/"+str(uid))
        var.init_add()
        self.QuestEventProgressionKeeper.add(uid, var)
        return uid


    def getQuestEventProgressionByID(self, id):
        return self.QuestEventProgressionKeeper.get(id)


    def newQuestEventProgression(self):
        _id = self.addNewQuestEventProgression()
        _data = self.getQuestEventProgressionByID(_id)
        return _data, _id
    def addNewQuest(self):
        uid = self.nextGUID()
        var = Quest.Quest(self, uid, "QuestsKeeper/"+str(uid))
        var.init_add()
        self.QuestsKeeper.add(uid, var)
        return uid


    def getQuestByID(self, id):
        return self.QuestsKeeper.get(id)


    def newQuest(self):
        _id = self.addNewQuest()
        _data = self.getQuestByID(_id)
        return _data, _id
    def addNewRerollShopItem(self):
        uid = self.nextGUID()
        var = RerollShopItem.RerollShopItem(self, uid, "RerollShopItemsKeeper/"+str(uid))
        var.init_add()
        self.RerollShopItemsKeeper.add(uid, var)
        return uid


    def getRerollShopItemByID(self, id):
        return self.RerollShopItemsKeeper.get(id)


    def newRerollShopItem(self):
        _id = self.addNewRerollShopItem()
        _data = self.getRerollShopItemByID(_id)
        return _data, _id
    def addNewSeasonAwards(self):
        uid = self.nextGUID()
        var = SeasonAwards.SeasonAwards(self, uid, "SeasonAwardsKeeper/"+str(uid))
        var.init_add()
        self.SeasonAwardsKeeper.add(uid, var)
        return uid


    def getSeasonAwardsByID(self, id):
        return self.SeasonAwardsKeeper.get(id)


    def newSeasonAwards(self):
        _id = self.addNewSeasonAwards()
        _data = self.getSeasonAwardsByID(_id)
        return _data, _id
    def addNewSeasonEventProgression(self):
        uid = self.nextGUID()
        var = SeasonEventProgression.SeasonEventProgression(self, uid, "SeasonEventProgressionKeeper/"+str(uid))
        var.init_add()
        self.SeasonEventProgressionKeeper.add(uid, var)
        return uid


    def getSeasonEventProgressionByID(self, id):
        return self.SeasonEventProgressionKeeper.get(id)


    def newSeasonEventProgression(self):
        _id = self.addNewSeasonEventProgression()
        _data = self.getSeasonEventProgressionByID(_id)
        return _data, _id
    def addNewSeasonInfo(self):
        uid = self.nextGUID()
        var = SeasonInfo.SeasonInfo(self, uid, "SeasonInfoKeeper/"+str(uid))
        var.init_add()
        self.SeasonInfoKeeper.add(uid, var)
        return uid


    def getSeasonInfoByID(self, id):
        return self.SeasonInfoKeeper.get(id)


    def newSeasonInfo(self):
        _id = self.addNewSeasonInfo()
        _data = self.getSeasonInfoByID(_id)
        return _data, _id
    def addNewSkin(self):
        uid = self.nextGUID()
        var = Skin.Skin(self, uid, "SkinsKeeper/"+str(uid))
        var.init_add()
        self.SkinsKeeper.add(uid, var)
        return uid


    def getSkinByID(self, id):
        return self.SkinsKeeper.get(id)


    def newSkin(self):
        _id = self.addNewSkin()
        _data = self.getSkinByID(_id)
        return _data, _id
    def addNewStatisticEvent(self):
        uid = self.nextGUID()
        var = StatisticEvent.StatisticEvent(self, uid, "StatisticEventsKeeper/"+str(uid))
        var.init_add()
        self.StatisticEventsKeeper.add(uid, var)
        return uid


    def getStatisticEventByID(self, id):
        return self.StatisticEventsKeeper.get(id)


    def newStatisticEvent(self):
        _id = self.addNewStatisticEvent()
        _data = self.getStatisticEventByID(_id)
        return _data, _id
    def addNewTalentSet(self):
        uid = self.nextGUID()
        var = TalentSet.TalentSet(self, uid, "TalentSetsKeeper/"+str(uid))
        var.init_add()
        self.TalentSetsKeeper.add(uid, var)
        return uid


    def getTalentSetByID(self, id):
        return self.TalentSetsKeeper.get(id)


    def newTalentSet(self):
        _id = self.addNewTalentSet()
        _data = self.getTalentSetByID(_id)
        return _data, _id
    def addNewTalentUpgradeEntity(self):
        uid = self.nextGUID()
        var = TalentUpgradeEntity.TalentUpgradeEntity(self, uid, "TalentUpgradeEntitiesKeeper/"+str(uid))
        var.init_add()
        self.TalentUpgradeEntitiesKeeper.add(uid, var)
        return uid


    def getTalentUpgradeEntityByID(self, id):
        return self.TalentUpgradeEntitiesKeeper.get(id)


    def newTalentUpgradeEntity(self):
        _id = self.addNewTalentUpgradeEntity()
        _data = self.getTalentUpgradeEntityByID(_id)
        return _data, _id
    def addNewTradeEventProgression(self):
        uid = self.nextGUID()
        var = TradeEventProgression.TradeEventProgression(self, uid, "TradeEventProgressionKeeper/"+str(uid))
        var.init_add()
        self.TradeEventProgressionKeeper.add(uid, var)
        return uid


    def getTradeEventProgressionByID(self, id):
        return self.TradeEventProgressionKeeper.get(id)


    def newTradeEventProgression(self):
        _id = self.addNewTradeEventProgression()
        _data = self.getTradeEventProgressionByID(_id)
        return _data, _id
    

    def deleteByID(self, id):
        self.ActiveEventSkins.deleteByID(id)
        self.ActiveQuests.deleteByID(id)
        self.AdminMessages.deleteByID(id)
        self.Buildings.deleteByID(id)
        self.CompletedDynamicQuests.deleteByID(id)
        self.CompletedQuests.deleteByID(id)
        self.DynamicQuestPulls.deleteByID(id)
        self.DynamicQuests.deleteByID(id)
        self.EventSkins.deleteByID(id)
        self.FlagInfo.deleteByID(id)
        self.Flags.deleteByID(id)
        self.Friends.deleteByID(id)
        self.GuildApplications.deleteByID(id)
        self.GuildBufs.deleteByID(id)
        self.Heroes.deleteByID(id)
        self.IncomingGuildInvites.deleteByID(id)
        self.Lootboxes.deleteByID(id)
        self.LordInfo.deleteByID(id)
        self.LossDynamicQuests.deleteByID(id)
        self.MarketingEventsInfo.deleteByID(id)
        self.PendingQuests.deleteByID(id)
        self.Pocket.deleteByID(id)
        self.QuestEvents.deleteByID(id)
        self.RerollShopInfo.deleteByID(id)
        self.Resources.deleteByID(id)
        self.ResourcesLimit.deleteByID(id)
        self.SeasonEvents.deleteByID(id)
        self.SeasonsAwardsInfo.deleteByID(id)
        self.StatisticEvents.deleteByID(id)
        self.Statistics.deleteByID(id)
        self.TalentUpgradeEntities.deleteByID(id)
        self.TournamentInfo.deleteByID(id)
        self.TradeEvents.deleteByID(id)
        self.UserInventory.deleteByID(id)
        self.version.deleteByID(id)

        #≈сли с RefCounter'ами все в пор€дке то объект к этому моменту уже должен быть удален из Keeper'ф
        obj = self.getObjectByID(id)
        if obj:
            #ј если не удален, значит RefCounter'ы глючат, и мы их обнул€ем что бы все нормально удал€лось
            obj.refCounter = 0

        self.AdminMessagesKeeper.deleteByID(id)
        self.ConstructionsKeeper.deleteByID(id)
        self.DynamicObjectivesKeeper.deleteByID(id)
        self.DynamicQuestAwardsKeeper.deleteByID(id)
        self.DynamicQuestKeeper.deleteByID(id)
        self.DynamicQuestPullInfoKeeper.deleteByID(id)
        self.FriendsKeeper.deleteByID(id)
        self.GuildApplicationKeeper.deleteByID(id)
        self.GuildBankInfoKeeper.deleteByID(id)
        self.GuildBufsKeeper.deleteByID(id)
        self.GuildInvitesKeeper.deleteByID(id)
        self.HeroesKeeper.deleteByID(id)
        self.ItemsKeeper.deleteByID(id)
        self.LootboxKeeper.deleteByID(id)
        self.MapInfoKeeper.deleteByID(id)
        self.ObjectivesKeeper.deleteByID(id)
        self.PreConditionsKeeper.deleteByID(id)
        self.QuestEventProgressionKeeper.deleteByID(id)
        self.QuestsKeeper.deleteByID(id)
        self.RerollShopItemsKeeper.deleteByID(id)
        self.SeasonAwardsKeeper.deleteByID(id)
        self.SeasonEventProgressionKeeper.deleteByID(id)
        self.SeasonInfoKeeper.deleteByID(id)
        self.SkinsKeeper.deleteByID(id)
        self.StatisticEventsKeeper.deleteByID(id)
        self.TalentSetsKeeper.deleteByID(id)
        self.TalentUpgradeEntitiesKeeper.deleteByID(id)
        self.TradeEventProgressionKeeper.deleteByID(id)


    def getObjectByID(self, id):
        obj = None
        AdminMessage = self.getAdminMessageByID(id)
        if AdminMessage:
            obj = AdminMessage
        Construction = self.getConstructionByID(id)
        if Construction:
            obj = Construction
        DynamicObjective = self.getDynamicObjectiveByID(id)
        if DynamicObjective:
            obj = DynamicObjective
        DynamicQuestAward = self.getDynamicQuestAwardByID(id)
        if DynamicQuestAward:
            obj = DynamicQuestAward
        DynamicQuest = self.getDynamicQuestByID(id)
        if DynamicQuest:
            obj = DynamicQuest
        DynamicQuestPullInfo = self.getDynamicQuestPullInfoByID(id)
        if DynamicQuestPullInfo:
            obj = DynamicQuestPullInfo
        SimpleFriend = self.getSimpleFriendByID(id)
        if SimpleFriend:
            obj = SimpleFriend
        GuildApplication = self.getGuildApplicationByID(id)
        if GuildApplication:
            obj = GuildApplication
        GuildBankInfo = self.getGuildBankInfoByID(id)
        if GuildBankInfo:
            obj = GuildBankInfo
        GuildBuf = self.getGuildBufByID(id)
        if GuildBuf:
            obj = GuildBuf
        GuildInvite = self.getGuildInviteByID(id)
        if GuildInvite:
            obj = GuildInvite
        Hero = self.getHeroByID(id)
        if Hero:
            obj = Hero
        Talent = self.getTalentByID(id)
        if Talent:
            obj = Talent
        Lootbox = self.getLootboxByID(id)
        if Lootbox:
            obj = Lootbox
        MapInfo = self.getMapInfoByID(id)
        if MapInfo:
            obj = MapInfo
        Objective = self.getObjectiveByID(id)
        if Objective:
            obj = Objective
        PreCondition = self.getPreConditionByID(id)
        if PreCondition:
            obj = PreCondition
        QuestEventProgression = self.getQuestEventProgressionByID(id)
        if QuestEventProgression:
            obj = QuestEventProgression
        Quest = self.getQuestByID(id)
        if Quest:
            obj = Quest
        RerollShopItem = self.getRerollShopItemByID(id)
        if RerollShopItem:
            obj = RerollShopItem
        SeasonAwards = self.getSeasonAwardsByID(id)
        if SeasonAwards:
            obj = SeasonAwards
        SeasonEventProgression = self.getSeasonEventProgressionByID(id)
        if SeasonEventProgression:
            obj = SeasonEventProgression
        SeasonInfo = self.getSeasonInfoByID(id)
        if SeasonInfo:
            obj = SeasonInfo
        Skin = self.getSkinByID(id)
        if Skin:
            obj = Skin
        StatisticEvent = self.getStatisticEventByID(id)
        if StatisticEvent:
            obj = StatisticEvent
        TalentSet = self.getTalentSetByID(id)
        if TalentSet:
            obj = TalentSet
        TalentUpgradeEntity = self.getTalentUpgradeEntityByID(id)
        if TalentUpgradeEntity:
            obj = TalentUpgradeEntity
        TradeEventProgression = self.getTradeEventProgressionByID(id)
        if TradeEventProgression:
            obj = TradeEventProgression
        return obj


    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)
    

    
    def generateJsonDict(self):
        _dct = ModelDataCustom.generateBaseDict(self)
        _dct.update(
            path=self.path,
            ActiveEventSkins=self.__dict__["ActiveEventSkins"].getJsonDict(),
            ActiveQuests=self.__dict__["ActiveQuests"].getJsonDict(),
            AdminMessages=self.__dict__["AdminMessages"].getJsonDict(),
            AdminMessagesKeeper=self.__dict__["AdminMessagesKeeper"].generateJsonDict(),
            Buildings=self.__dict__["Buildings"].getJsonDict(),
            CompletedDynamicQuests=self.__dict__["CompletedDynamicQuests"].getJsonDict(),
            CompletedQuests=self.__dict__["CompletedQuests"].getJsonDict(),
            ConstructionsKeeper=self.__dict__["ConstructionsKeeper"].generateJsonDict(),
            DynamicObjectivesKeeper=self.__dict__["DynamicObjectivesKeeper"].generateJsonDict(),
            DynamicQuestAwardsKeeper=self.__dict__["DynamicQuestAwardsKeeper"].generateJsonDict(),
            DynamicQuestKeeper=self.__dict__["DynamicQuestKeeper"].generateJsonDict(),
            DynamicQuestPullInfoKeeper=self.__dict__["DynamicQuestPullInfoKeeper"].generateJsonDict(),
            DynamicQuestPulls=self.__dict__["DynamicQuestPulls"].getJsonDict(),
            DynamicQuests=self.__dict__["DynamicQuests"].getJsonDict(),
            EventSkins=self.__dict__["EventSkins"].getJsonDict(),
            FatClientServerTime=self.__dict__["FatClientServerTime"],
            FlagInfo = self.__dict__["FlagInfo"].generateJsonDict(),
            Flags=self.__dict__["Flags"].getJsonDict(),
            Friends = self.__dict__["Friends"].generateJsonDict(),
            FriendsKeeper=self.__dict__["FriendsKeeper"].generateJsonDict(),
            GuildApplicationKeeper=self.__dict__["GuildApplicationKeeper"].generateJsonDict(),
            GuildApplications=self.__dict__["GuildApplications"].getJsonDict(),
            GuildBankInfoKeeper=self.__dict__["GuildBankInfoKeeper"].generateJsonDict(),
            GuildBufs=self.__dict__["GuildBufs"].getJsonDict(),
            GuildBufsKeeper=self.__dict__["GuildBufsKeeper"].generateJsonDict(),
            GuildInvitesKeeper=self.__dict__["GuildInvitesKeeper"].generateJsonDict(),
            Heroes=self.__dict__["Heroes"].getJsonDict(),
            HeroesKeeper=self.__dict__["HeroesKeeper"].generateJsonDict(),
            IncomingGuildInvites=self.__dict__["IncomingGuildInvites"].getJsonDict(),
            ItemsKeeper=self.__dict__["ItemsKeeper"].generateJsonDict(),
            Lootboxes=self.__dict__["Lootboxes"].getJsonDict(),
            LootboxKeeper=self.__dict__["LootboxKeeper"].generateJsonDict(),
            LordInfo = self.__dict__["LordInfo"].generateJsonDict(),
            LossDynamicQuests=self.__dict__["LossDynamicQuests"].getJsonDict(),
            MapInfoKeeper=self.__dict__["MapInfoKeeper"].generateJsonDict(),
            MarketingEventsInfo = self.__dict__["MarketingEventsInfo"].generateJsonDict(),
            ObjectivesKeeper=self.__dict__["ObjectivesKeeper"].generateJsonDict(),
            PendingQuests=self.__dict__["PendingQuests"].getJsonDict(),
            Pocket=self.__dict__["Pocket"].getJsonDict(),
            PreConditionsKeeper=self.__dict__["PreConditionsKeeper"].generateJsonDict(),
            QuestEventProgressionKeeper=self.__dict__["QuestEventProgressionKeeper"].generateJsonDict(),
            QuestEvents=self.__dict__["QuestEvents"].getJsonDict(),
            QuestsKeeper=self.__dict__["QuestsKeeper"].generateJsonDict(),
            RerollShopInfo = self.__dict__["RerollShopInfo"].generateJsonDict(),
            RerollShopItemsKeeper=self.__dict__["RerollShopItemsKeeper"].generateJsonDict(),
            Resources = self.__dict__["Resources"].generateJsonDict(),
            ResourcesLimit = self.__dict__["ResourcesLimit"].generateJsonDict(),
            SeasonAwardsKeeper=self.__dict__["SeasonAwardsKeeper"].generateJsonDict(),
            SeasonEventProgressionKeeper=self.__dict__["SeasonEventProgressionKeeper"].generateJsonDict(),
            SeasonEvents=self.__dict__["SeasonEvents"].getJsonDict(),
            SeasonInfoKeeper=self.__dict__["SeasonInfoKeeper"].generateJsonDict(),
            SeasonsAwardsInfo=self.__dict__["SeasonsAwardsInfo"].getJsonDict(),
            ServerTime=self.__dict__["ServerTime"],
            SkinsKeeper=self.__dict__["SkinsKeeper"].generateJsonDict(),
            StatisticEventId=self.__dict__["StatisticEventId"],
            StatisticEvents=self.__dict__["StatisticEvents"].getJsonDict(),
            StatisticEventsKeeper=self.__dict__["StatisticEventsKeeper"].generateJsonDict(),
            Statistics = self.__dict__["Statistics"].generateJsonDict(),
            TalentSetsKeeper=self.__dict__["TalentSetsKeeper"].generateJsonDict(),
            TalentUpgradeEntities=self.__dict__["TalentUpgradeEntities"].getJsonDict(),
            TalentUpgradeEntitiesKeeper=self.__dict__["TalentUpgradeEntitiesKeeper"].generateJsonDict(),
            TournamentInfo = self.__dict__["TournamentInfo"].generateJsonDict(),
            TradeEventProgressionKeeper=self.__dict__["TradeEventProgressionKeeper"].generateJsonDict(),
            TradeEvents=self.__dict__["TradeEvents"].getJsonDict(),
            UserInventory=self.__dict__["UserInventory"].getJsonDict(),
            UserInventoryLimit=self.__dict__["UserInventoryLimit"],
            version = self.__dict__["version"].generateJsonDict(),
        )
        return { "ModelData": _dct }
    

    def serializeToFile(self, file):
        pass
        self.ActiveEventSkins.serializeToFile(file, "ActiveEventSkins")
        self.CompletedDynamicQuests.serializeToFile(file, "CompletedDynamicQuests")
        self.EventSkins.serializeToFile(file, "EventSkins")
        file.write("self.FatClientServerTime = " + repr(self.FatClientServerTime) + "\n")
        self.FlagInfo.serializeToFile(file, "FlagInfo")
        self.Flags.serializeToFile(file, "Flags")
        self.Friends.serializeToFile(file, "Friends")
        self.LordInfo.serializeToFile(file, "LordInfo")
        self.LossDynamicQuests.serializeToFile(file, "LossDynamicQuests")
        self.MarketingEventsInfo.serializeToFile(file, "MarketingEventsInfo")
        self.PendingQuests.serializeToFile(file, "PendingQuests")
        self.RerollShopInfo.serializeToFile(file, "RerollShopInfo")
        self.Resources.serializeToFile(file, "Resources")
        self.ResourcesLimit.serializeToFile(file, "ResourcesLimit")
        file.write("self.ServerTime = " + repr(self.ServerTime) + "\n")
        file.write("self.StatisticEventId = " + repr(self.StatisticEventId) + "\n")
        self.Statistics.serializeToFile(file, "Statistics")
        self.TournamentInfo.serializeToFile(file, "TournamentInfo")
        file.write("self.UserInventoryLimit = " + repr(self.UserInventoryLimit) + "\n")
        self.version.serializeToFile(file, "version")

    
# инициализаци€ списка сериализуемых классов при импорте модул€
ModelData.initJsonTypes(ModelData)
