# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import GuildInfo
import GuildInvestEvent
import GuildLevelInfo
import GuildMapEntity
import GuildMember
import GuildShortInfo
import GuildTalent
import GuildVersion
import InitiatedSiege
import MemberDayRating
import RatingInfo
import RecommendedVassal
import RecruitmentInfo
import TalentEvent

import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from GuildDataCustom import GuildDataCustom

class GuildData(ChangeHandler, GuildDataCustom, IChangeWriter, IAbstractModelData, AutoIncGuidGenerator):
    _changeFields = {
        "ActiveBuffs":1,
        "ActiveHoldGuildBuffs":1,
        "ActiveSieges":1,
        "ExVassals":1,
        "GuildAuid":1,
        "GuildCreateTime":1,
        "GuildShopItems":1,
        "GuildsRemovedFromSearch":1,
        "GuildSuzerain":1,
        "LockedByOtherGuild":1,
        "LostSiegesGuilds":1,
        "Owner":1,
        "SiegeForMyGuildEndTime":1,
    } 


    def __init__(self):
        GuildDataCustom.__init__(self)
        ChangeHandler.__init__(self, u"/", self)
        AutoIncGuidGenerator.__init__(self)
        self._serializator = JSONSerialization(self)
        self.__dict__["GuildMapEntityKeeper"] = Keeper(self)
        self.__dict__["GuildMemberKeeper"] = Keeper(self)
        self.__dict__["GuildShortInfoKeeper"] = Keeper(self)
        self.__dict__["GuildTalentKeeper"] = Keeper(self)
        self.__dict__["InitiatedSiegeKeeper"] = Keeper(self)
        self.__dict__["InvestStatisticsKeeper"] = Keeper(self)
        self.__dict__["MemberDayRatingKeeper"] = Keeper(self)
        self.__dict__["RecommendedVassalKeeper"] = Keeper(self)
        self.__dict__["TalentEventKeeper"] = Keeper(self)
        self.__dict__["ActiveBuffs"] = SimpleDict(self)
        self.__dict__["ActiveHoldGuildBuffs"] = SimpleDict(self)
        self.__dict__["ActiveSieges"] = SimpleList(self)
        self.__dict__["ExVassals"] = SimpleDict(self)
        self.__dict__["FreeTalents"] = Set(self)
        self.__dict__["GuildAuid"] = 0
        self.__dict__["GuildCreateTime"] = 0
        self.__dict__["GuildInfo"] = GuildInfo.GuildInfo(self)
        self.__dict__["GuildLevelInfo"] = GuildLevelInfo.GuildLevelInfo(self)
        self.__dict__["GuildShopItems"] = SimpleDict(self)
        self.__dict__["GuildsRemovedFromSearch"] = SimpleDict(self)
        self.__dict__["GuildSuzerain"] = Ref(self)
        self.__dict__["GuildVassals"] = Set(self)
        self.__dict__["InitiatedSieges"] = Set(self)
        self.__dict__["InvestStatistics"] = Set(self)
        self.__dict__["LockedByOtherGuild"] = False
        self.__dict__["LostSiegesGuilds"] = SimpleDict(self)
        self.__dict__["Members"] = Set(self)
        self.__dict__["Owner"] = Ref(self)
        self.__dict__["RatingInfo"] = RatingInfo.RatingInfo(self)
        self.__dict__["RecommendedForMapVassals"] = Set(self)
        self.__dict__["RecruitmentInfo"] = RecruitmentInfo.RecruitmentInfo(self)
        self.__dict__["SiegeForMyGuildEndTime"] = 0
        self.__dict__["TakenTalents"] = Set(self)
        self.__dict__["TalentLog"] = Set(self)
        self.__dict__["version"] = GuildVersion.GuildVersion(self)


    def init(self, changeWriter):
        self.write(changeWriter)
        self.GuildMapEntityKeeper.init(u"GuildMapEntityKeeper", self, "GuildMapEntity")
        self.GuildMemberKeeper.init(u"GuildMemberKeeper", self, "GuildMember")
        self.GuildShortInfoKeeper.init(u"GuildShortInfoKeeper", self, "GuildShortInfo")
        self.GuildTalentKeeper.init(u"GuildTalentKeeper", self, "GuildTalent")
        self.InitiatedSiegeKeeper.init(u"InitiatedSiegeKeeper", self, "InitiatedSiege")
        self.InvestStatisticsKeeper.init(u"InvestStatisticsKeeper", self, "GuildInvestEvent")
        self.MemberDayRatingKeeper.init(u"MemberDayRatingKeeper", self, "MemberDayRating")
        self.RecommendedVassalKeeper.init(u"RecommendedVassalKeeper", self, "RecommendedVassal")
        self.TalentEventKeeper.init(u"TalentEventKeeper", self, "TalentEvent")
        self.ActiveBuffs.init(u"ActiveBuffs", self)
        self.ActiveHoldGuildBuffs.init(u"ActiveHoldGuildBuffs", self)
        self.ActiveSieges.init(u"ActiveSieges", self)
        self.ExVassals.init(u"ExVassals", self)
        self.FreeTalents.init(self.GuildTalentKeeper, u"FreeTalents", self)
        self.GuildInfo.setPath(u"GuildInfo")
        self.GuildLevelInfo.setPath(u"GuildLevelInfo")
        self.GuildShopItems.init(u"GuildShopItems", self)
        self.GuildsRemovedFromSearch.init(u"GuildsRemovedFromSearch", self)
        self.GuildSuzerain.init(self.GuildMapEntityKeeper, u"/", self, "GuildSuzerain")
        self.GuildVassals.init(self.GuildMapEntityKeeper, u"GuildVassals", self)
        self.InitiatedSieges.init(self.InitiatedSiegeKeeper, u"InitiatedSieges", self)
        self.InvestStatistics.init(self.InvestStatisticsKeeper, u"InvestStatistics", self)
        self.LostSiegesGuilds.init(u"LostSiegesGuilds", self)
        self.Members.init(self.GuildMemberKeeper, u"Members", self)
        self.Owner.init(self.GuildMemberKeeper, u"/", self, "Owner")
        self.RatingInfo.setPath(u"RatingInfo")
        self.RecommendedForMapVassals.init(self.RecommendedVassalKeeper, u"RecommendedForMapVassals", self)
        self.RecruitmentInfo.setPath(u"RecruitmentInfo")
        self.TakenTalents.init(self.GuildTalentKeeper, u"TakenTalents", self)
        self.TalentLog.init(self.TalentEventKeeper, u"TalentLog", self)
        self.version.setPath(u"version")


    @staticmethod
    def initJsonTypes(TCustomGuildData): # конечный класс CustomGuildData будет передавать снаружи, из datamanager
        if "GuildData" not in JSONSerialization.SERIALIZABLE_CLASSES:
            JSONSerialization.updateOurTypes((TCustomGuildData,
            GuildInfo.GuildInfo,
            GuildInvestEvent.GuildInvestEvent,
            GuildLevelInfo.GuildLevelInfo,
            GuildMapEntity.GuildMapEntity,
            GuildMember.GuildMember,
            GuildShortInfo.GuildShortInfo,
            GuildTalent.GuildTalent,
            GuildVersion.GuildVersion,
            InitiatedSiege.InitiatedSiege,
            MemberDayRating.MemberDayRating,
            RatingInfo.RatingInfo,
            RecommendedVassal.RecommendedVassal,
            RecruitmentInfo.RecruitmentInfo,
            TalentEvent.TalentEvent,
            ))
            JSONSerialization.SERIALIZABLE_CLASSES.update(
            { "GuildData" : TCustomGuildData
            , "Keeper" : Keeper
            , "Set" : Set
            , "SimpleList" : SimpleList
            , "SimpleDict" : SimpleDict
            , "Collection" : Collection
            , "Ref" : Ref
            , "GuildInfo" : GuildInfo.GuildInfo
            , "GuildInvestEvent" : GuildInvestEvent.GuildInvestEvent
            , "GuildLevelInfo" : GuildLevelInfo.GuildLevelInfo
            , "GuildMapEntity" : GuildMapEntity.GuildMapEntity
            , "GuildMember" : GuildMember.GuildMember
            , "GuildShortInfo" : GuildShortInfo.GuildShortInfo
            , "GuildTalent" : GuildTalent.GuildTalent
            , "GuildVersion" : GuildVersion.GuildVersion
            , "InitiatedSiege" : InitiatedSiege.InitiatedSiege
            , "MemberDayRating" : MemberDayRating.MemberDayRating
            , "RatingInfo" : RatingInfo.RatingInfo
            , "RecommendedVassal" : RecommendedVassal.RecommendedVassal
            , "RecruitmentInfo" : RecruitmentInfo.RecruitmentInfo
            , "TalentEvent" : TalentEvent.TalentEvent
            })  
        else:
            err("GuildData.initJsonTypes called twice! The second call is:\n%s", errStack())

    def addNewGuildMapEntity(self):
        uid = self.nextGUID()
        var = GuildMapEntity.GuildMapEntity(self, uid, "GuildMapEntityKeeper/"+str(uid))
        var.init_add()
        self.GuildMapEntityKeeper.add(uid, var)
        return uid


    def getGuildMapEntityByID(self, id):
        return self.GuildMapEntityKeeper.get(id)


    def newGuildMapEntity(self):
        _id = self.addNewGuildMapEntity()
        _data = self.getGuildMapEntityByID(_id)
        return _data, _id
    def addNewGuildMember(self):
        uid = self.nextGUID()
        var = GuildMember.GuildMember(self, uid, "GuildMemberKeeper/"+str(uid))
        var.init_add()
        self.GuildMemberKeeper.add(uid, var)
        return uid


    def getGuildMemberByID(self, id):
        return self.GuildMemberKeeper.get(id)


    def newGuildMember(self):
        _id = self.addNewGuildMember()
        _data = self.getGuildMemberByID(_id)
        return _data, _id
    def addNewGuildShortInfo(self):
        uid = self.nextGUID()
        var = GuildShortInfo.GuildShortInfo(self, uid, "GuildShortInfoKeeper/"+str(uid))
        var.init_add()
        self.GuildShortInfoKeeper.add(uid, var)
        return uid


    def getGuildShortInfoByID(self, id):
        return self.GuildShortInfoKeeper.get(id)


    def newGuildShortInfo(self):
        _id = self.addNewGuildShortInfo()
        _data = self.getGuildShortInfoByID(_id)
        return _data, _id
    def addNewGuildTalent(self):
        uid = self.nextGUID()
        var = GuildTalent.GuildTalent(self, uid, "GuildTalentKeeper/"+str(uid))
        var.init_add()
        self.GuildTalentKeeper.add(uid, var)
        return uid


    def getGuildTalentByID(self, id):
        return self.GuildTalentKeeper.get(id)


    def newGuildTalent(self):
        _id = self.addNewGuildTalent()
        _data = self.getGuildTalentByID(_id)
        return _data, _id
    def addNewInitiatedSiege(self):
        uid = self.nextGUID()
        var = InitiatedSiege.InitiatedSiege(self, uid, "InitiatedSiegeKeeper/"+str(uid))
        var.init_add()
        self.InitiatedSiegeKeeper.add(uid, var)
        return uid


    def getInitiatedSiegeByID(self, id):
        return self.InitiatedSiegeKeeper.get(id)


    def newInitiatedSiege(self):
        _id = self.addNewInitiatedSiege()
        _data = self.getInitiatedSiegeByID(_id)
        return _data, _id
    def addNewGuildInvestEvent(self):
        uid = self.nextGUID()
        var = GuildInvestEvent.GuildInvestEvent(self, uid, "InvestStatisticsKeeper/"+str(uid))
        var.init_add()
        self.InvestStatisticsKeeper.add(uid, var)
        return uid


    def getGuildInvestEventByID(self, id):
        return self.InvestStatisticsKeeper.get(id)


    def newGuildInvestEvent(self):
        _id = self.addNewGuildInvestEvent()
        _data = self.getGuildInvestEventByID(_id)
        return _data, _id
    def addNewMemberDayRating(self):
        uid = self.nextGUID()
        var = MemberDayRating.MemberDayRating(self, uid, "MemberDayRatingKeeper/"+str(uid))
        var.init_add()
        self.MemberDayRatingKeeper.add(uid, var)
        return uid


    def getMemberDayRatingByID(self, id):
        return self.MemberDayRatingKeeper.get(id)


    def newMemberDayRating(self):
        _id = self.addNewMemberDayRating()
        _data = self.getMemberDayRatingByID(_id)
        return _data, _id
    def addNewRecommendedVassal(self):
        uid = self.nextGUID()
        var = RecommendedVassal.RecommendedVassal(self, uid, "RecommendedVassalKeeper/"+str(uid))
        var.init_add()
        self.RecommendedVassalKeeper.add(uid, var)
        return uid


    def getRecommendedVassalByID(self, id):
        return self.RecommendedVassalKeeper.get(id)


    def newRecommendedVassal(self):
        _id = self.addNewRecommendedVassal()
        _data = self.getRecommendedVassalByID(_id)
        return _data, _id
    def addNewTalentEvent(self):
        uid = self.nextGUID()
        var = TalentEvent.TalentEvent(self, uid, "TalentEventKeeper/"+str(uid))
        var.init_add()
        self.TalentEventKeeper.add(uid, var)
        return uid


    def getTalentEventByID(self, id):
        return self.TalentEventKeeper.get(id)


    def newTalentEvent(self):
        _id = self.addNewTalentEvent()
        _data = self.getTalentEventByID(_id)
        return _data, _id
    

    def deleteByID(self, id):
        self.ActiveBuffs.deleteByID(id)
        self.ActiveHoldGuildBuffs.deleteByID(id)
        self.ActiveSieges.deleteByID(id)
        self.ExVassals.deleteByID(id)
        self.FreeTalents.deleteByID(id)
        self.GuildInfo.deleteByID(id)
        self.GuildLevelInfo.deleteByID(id)
        self.GuildShopItems.deleteByID(id)
        self.GuildsRemovedFromSearch.deleteByID(id)
        self.GuildSuzerain.deleteByID(id)
        self.GuildVassals.deleteByID(id)
        self.InitiatedSieges.deleteByID(id)
        self.InvestStatistics.deleteByID(id)
        self.LostSiegesGuilds.deleteByID(id)
        self.Members.deleteByID(id)
        self.Owner.deleteByID(id)
        self.RatingInfo.deleteByID(id)
        self.RecommendedForMapVassals.deleteByID(id)
        self.RecruitmentInfo.deleteByID(id)
        self.TakenTalents.deleteByID(id)
        self.TalentLog.deleteByID(id)
        self.version.deleteByID(id)

        #≈сли с RefCounter'ами все в пор€дке то объект к этому моменту уже должен быть удален из Keeper'ф
        obj = self.getObjectByID(id)
        if obj:
            #ј если не удален, значит RefCounter'ы глючат, и мы их обнул€ем что бы все нормально удал€лось
            obj.refCounter = 0

        self.GuildMapEntityKeeper.deleteByID(id)
        self.GuildMemberKeeper.deleteByID(id)
        self.GuildShortInfoKeeper.deleteByID(id)
        self.GuildTalentKeeper.deleteByID(id)
        self.InitiatedSiegeKeeper.deleteByID(id)
        self.InvestStatisticsKeeper.deleteByID(id)
        self.MemberDayRatingKeeper.deleteByID(id)
        self.RecommendedVassalKeeper.deleteByID(id)
        self.TalentEventKeeper.deleteByID(id)


    def getObjectByID(self, id):
        obj = None
        GuildMapEntity = self.getGuildMapEntityByID(id)
        if GuildMapEntity:
            obj = GuildMapEntity
        GuildMember = self.getGuildMemberByID(id)
        if GuildMember:
            obj = GuildMember
        GuildShortInfo = self.getGuildShortInfoByID(id)
        if GuildShortInfo:
            obj = GuildShortInfo
        GuildTalent = self.getGuildTalentByID(id)
        if GuildTalent:
            obj = GuildTalent
        InitiatedSiege = self.getInitiatedSiegeByID(id)
        if InitiatedSiege:
            obj = InitiatedSiege
        GuildInvestEvent = self.getGuildInvestEventByID(id)
        if GuildInvestEvent:
            obj = GuildInvestEvent
        MemberDayRating = self.getMemberDayRatingByID(id)
        if MemberDayRating:
            obj = MemberDayRating
        RecommendedVassal = self.getRecommendedVassalByID(id)
        if RecommendedVassal:
            obj = RecommendedVassal
        TalentEvent = self.getTalentEventByID(id)
        if TalentEvent:
            obj = TalentEvent
        return obj


    def __setattr__(self, name, val):
        if name == "GuildSuzerain":
            self.__dict__["GuildSuzerain"].set(val)
            return    
        if name == "Owner":
            self.__dict__["Owner"].set(val)
            return    
        ChangeHandler.__setattr__(self, name, val)
    

    
    def generateJsonDict(self):
        _dct = GuildDataCustom.generateBaseDict(self)
        _dct.update(
            path=self.path,
            ActiveBuffs=self.__dict__["ActiveBuffs"].getJsonDict(),
            ActiveHoldGuildBuffs=self.__dict__["ActiveHoldGuildBuffs"].getJsonDict(),
            ActiveSieges=self.__dict__["ActiveSieges"].getJsonDict(),
            ExVassals=self.__dict__["ExVassals"].getJsonDict(),
            FreeTalents=self.__dict__["FreeTalents"].getJsonDict(),
            GuildAuid=self.__dict__["GuildAuid"],
            GuildCreateTime=self.__dict__["GuildCreateTime"],
            GuildInfo = self.__dict__["GuildInfo"].generateJsonDict(),
            GuildLevelInfo = self.__dict__["GuildLevelInfo"].generateJsonDict(),
            GuildMapEntityKeeper=self.__dict__["GuildMapEntityKeeper"].generateJsonDict(),
            GuildMemberKeeper=self.__dict__["GuildMemberKeeper"].generateJsonDict(),
            GuildShopItems=self.__dict__["GuildShopItems"].getJsonDict(),
            GuildShortInfoKeeper=self.__dict__["GuildShortInfoKeeper"].generateJsonDict(),
            GuildsRemovedFromSearch=self.__dict__["GuildsRemovedFromSearch"].getJsonDict(),
            GuildSuzerain=self.__dict__["GuildSuzerain"].getJsonDict(),
            GuildTalentKeeper=self.__dict__["GuildTalentKeeper"].generateJsonDict(),
            GuildVassals=self.__dict__["GuildVassals"].getJsonDict(),
            InitiatedSiegeKeeper=self.__dict__["InitiatedSiegeKeeper"].generateJsonDict(),
            InitiatedSieges=self.__dict__["InitiatedSieges"].getJsonDict(),
            InvestStatistics=self.__dict__["InvestStatistics"].getJsonDict(),
            InvestStatisticsKeeper=self.__dict__["InvestStatisticsKeeper"].generateJsonDict(),
            LockedByOtherGuild=self.__dict__["LockedByOtherGuild"],
            LostSiegesGuilds=self.__dict__["LostSiegesGuilds"].getJsonDict(),
            MemberDayRatingKeeper=self.__dict__["MemberDayRatingKeeper"].generateJsonDict(),
            Members=self.__dict__["Members"].getJsonDict(),
            Owner=self.__dict__["Owner"].getJsonDict(),
            RatingInfo = self.__dict__["RatingInfo"].generateJsonDict(),
            RecommendedForMapVassals=self.__dict__["RecommendedForMapVassals"].getJsonDict(),
            RecommendedVassalKeeper=self.__dict__["RecommendedVassalKeeper"].generateJsonDict(),
            RecruitmentInfo = self.__dict__["RecruitmentInfo"].generateJsonDict(),
            SiegeForMyGuildEndTime=self.__dict__["SiegeForMyGuildEndTime"],
            TakenTalents=self.__dict__["TakenTalents"].getJsonDict(),
            TalentEventKeeper=self.__dict__["TalentEventKeeper"].generateJsonDict(),
            TalentLog=self.__dict__["TalentLog"].getJsonDict(),
            version = self.__dict__["version"].generateJsonDict(),
        )
        return { "GuildData": _dct }
    

    def serializeToFile(self, file):
        pass
        self.ActiveBuffs.serializeToFile(file, "ActiveBuffs")
        self.ActiveHoldGuildBuffs.serializeToFile(file, "ActiveHoldGuildBuffs")
        self.ActiveSieges.serializeToFile(file, "ActiveSieges")
        self.ExVassals.serializeToFile(file, "ExVassals")
        file.write("self.GuildAuid = " + repr(self.GuildAuid) + "\n")
        file.write("self.GuildCreateTime = " + repr(self.GuildCreateTime) + "\n")
        self.GuildInfo.serializeToFile(file, "GuildInfo")
        self.GuildLevelInfo.serializeToFile(file, "GuildLevelInfo")
        self.GuildShopItems.serializeToFile(file, "GuildShopItems")
        self.GuildsRemovedFromSearch.serializeToFile(file, "GuildsRemovedFromSearch")
        file.write("self.LockedByOtherGuild = " + repr(self.LockedByOtherGuild) + "\n")
        self.LostSiegesGuilds.serializeToFile(file, "LostSiegesGuilds")
        self.RatingInfo.serializeToFile(file, "RatingInfo")
        self.RecruitmentInfo.serializeToFile(file, "RecruitmentInfo")
        file.write("self.SiegeForMyGuildEndTime = " + repr(self.SiegeForMyGuildEndTime) + "\n")
        self.version.serializeToFile(file, "version")

    
# инициализаци€ списка сериализуемых классов при импорте модул€
GuildData.initJsonTypes(GuildData)
