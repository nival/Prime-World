# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import GuildRecruitmentInfo
import GuildShortInfo
import GuildsListEntity

import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from GuildWarsDataCustom import GuildWarsDataCustom

class GuildWarsData(ChangeHandler, GuildWarsDataCustom, IChangeWriter, IAbstractModelData, AutoIncGuidGenerator):
    _changeFields = {
    } 


    def __init__(self):
        GuildWarsDataCustom.__init__(self)
        ChangeHandler.__init__(self, u"/", self)
        AutoIncGuidGenerator.__init__(self)
        self._serializator = JSONSerialization(self)
        self.__dict__["GuildRecruitmentInfoKeeper"] = Keeper(self)
        self.__dict__["GuildShortInfoKeeper"] = Keeper(self)
        self.__dict__["GuildsListEntityKeeper"] = Keeper(self)
        self.__dict__["AllGuilds"] = Set(self)
        self.__dict__["ExVassals"] = Set(self)
        self.__dict__["RecommendedGuilds"] = Set(self)
        self.__dict__["RecommendedVassals"] = Set(self)
        self.__dict__["VassalApplications"] = Set(self)


    def init(self, changeWriter):
        self.write(changeWriter)
        self.GuildRecruitmentInfoKeeper.init(u"GuildRecruitmentInfoKeeper", self, "GuildRecruitmentInfo")
        self.GuildShortInfoKeeper.init(u"GuildShortInfoKeeper", self, "GuildShortInfo")
        self.GuildsListEntityKeeper.init(u"GuildsListEntityKeeper", self, "GuildsListEntity")
        self.AllGuilds.init(self.GuildsListEntityKeeper, u"AllGuilds", self)
        self.ExVassals.init(self.GuildsListEntityKeeper, u"ExVassals", self)
        self.RecommendedGuilds.init(self.GuildRecruitmentInfoKeeper, u"RecommendedGuilds", self)
        self.RecommendedVassals.init(self.GuildsListEntityKeeper, u"RecommendedVassals", self)
        self.VassalApplications.init(self.GuildsListEntityKeeper, u"VassalApplications", self)


    @staticmethod
    def initJsonTypes(TCustomGuildWarsData): # конечный класс CustomGuildWarsData будет передавать снаружи, из datamanager
        if "GuildWarsData" not in JSONSerialization.SERIALIZABLE_CLASSES:
            JSONSerialization.updateOurTypes((TCustomGuildWarsData,
            GuildRecruitmentInfo.GuildRecruitmentInfo,
            GuildShortInfo.GuildShortInfo,
            GuildsListEntity.GuildsListEntity,
            ))
            JSONSerialization.SERIALIZABLE_CLASSES.update(
            { "GuildWarsData" : TCustomGuildWarsData
            , "Keeper" : Keeper
            , "Set" : Set
            , "SimpleList" : SimpleList
            , "SimpleDict" : SimpleDict
            , "Collection" : Collection
            , "Ref" : Ref
            , "GuildRecruitmentInfo" : GuildRecruitmentInfo.GuildRecruitmentInfo
            , "GuildShortInfo" : GuildShortInfo.GuildShortInfo
            , "GuildsListEntity" : GuildsListEntity.GuildsListEntity
            })  
        else:
            err("GuildWarsData.initJsonTypes called twice! The second call is:\n%s", errStack())

    def addNewGuildRecruitmentInfo(self):
        uid = self.nextGUID()
        var = GuildRecruitmentInfo.GuildRecruitmentInfo(self, uid, "GuildRecruitmentInfoKeeper/"+str(uid))
        var.init_add()
        self.GuildRecruitmentInfoKeeper.add(uid, var)
        return uid


    def getGuildRecruitmentInfoByID(self, id):
        return self.GuildRecruitmentInfoKeeper.get(id)


    def newGuildRecruitmentInfo(self):
        _id = self.addNewGuildRecruitmentInfo()
        _data = self.getGuildRecruitmentInfoByID(_id)
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
    def addNewGuildsListEntity(self):
        uid = self.nextGUID()
        var = GuildsListEntity.GuildsListEntity(self, uid, "GuildsListEntityKeeper/"+str(uid))
        var.init_add()
        self.GuildsListEntityKeeper.add(uid, var)
        return uid


    def getGuildsListEntityByID(self, id):
        return self.GuildsListEntityKeeper.get(id)


    def newGuildsListEntity(self):
        _id = self.addNewGuildsListEntity()
        _data = self.getGuildsListEntityByID(_id)
        return _data, _id
    

    def deleteByID(self, id):
        self.AllGuilds.deleteByID(id)
        self.ExVassals.deleteByID(id)
        self.RecommendedGuilds.deleteByID(id)
        self.RecommendedVassals.deleteByID(id)
        self.VassalApplications.deleteByID(id)

        #≈сли с RefCounter'ами все в пор€дке то объект к этому моменту уже должен быть удален из Keeper'ф
        obj = self.getObjectByID(id)
        if obj:
            #ј если не удален, значит RefCounter'ы глючат, и мы их обнул€ем что бы все нормально удал€лось
            obj.refCounter = 0

        self.GuildRecruitmentInfoKeeper.deleteByID(id)
        self.GuildShortInfoKeeper.deleteByID(id)
        self.GuildsListEntityKeeper.deleteByID(id)


    def getObjectByID(self, id):
        obj = None
        GuildRecruitmentInfo = self.getGuildRecruitmentInfoByID(id)
        if GuildRecruitmentInfo:
            obj = GuildRecruitmentInfo
        GuildShortInfo = self.getGuildShortInfoByID(id)
        if GuildShortInfo:
            obj = GuildShortInfo
        GuildsListEntity = self.getGuildsListEntityByID(id)
        if GuildsListEntity:
            obj = GuildsListEntity
        return obj


    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)
    

    
    def generateJsonDict(self):
        _dct = GuildWarsDataCustom.generateBaseDict(self)
        _dct.update(
            path=self.path,
            AllGuilds=self.__dict__["AllGuilds"].getJsonDict(),
            ExVassals=self.__dict__["ExVassals"].getJsonDict(),
            GuildRecruitmentInfoKeeper=self.__dict__["GuildRecruitmentInfoKeeper"].generateJsonDict(),
            GuildShortInfoKeeper=self.__dict__["GuildShortInfoKeeper"].generateJsonDict(),
            GuildsListEntityKeeper=self.__dict__["GuildsListEntityKeeper"].generateJsonDict(),
            RecommendedGuilds=self.__dict__["RecommendedGuilds"].getJsonDict(),
            RecommendedVassals=self.__dict__["RecommendedVassals"].getJsonDict(),
            VassalApplications=self.__dict__["VassalApplications"].getJsonDict(),
        )
        return { "GuildWarsData": _dct }
    

    def serializeToFile(self, file):
        pass

    
# инициализаци€ списка сериализуемых классов при импорте модул€
GuildWarsData.initJsonTypes(GuildWarsData)
