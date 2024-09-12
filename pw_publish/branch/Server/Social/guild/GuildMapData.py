# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import GuildShortInfo
import SiegeGuildInfo
import SiegeInfo

import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from GuildMapDataCustom import GuildMapDataCustom

class GuildMapData(ChangeHandler, GuildMapDataCustom, IChangeWriter, IAbstractModelData, AutoIncGuidGenerator):
    _changeFields = {
        "GuildMapSuzerain":1,
        "HasUltimateShop":1,
        "ShortInfo":1,
    } 


    def __init__(self):
        GuildMapDataCustom.__init__(self)
        ChangeHandler.__init__(self, u"/", self)
        AutoIncGuidGenerator.__init__(self)
        self._serializator = JSONSerialization(self)
        self.__dict__["GuildShortInfoKeeper"] = Keeper(self)
        self.__dict__["SiegeGuildInfoKeeper"] = Keeper(self)
        self.__dict__["SiegeKeeper"] = Keeper(self)
        self.__dict__["GuildMapSuzerain"] = Ref(self)
        self.__dict__["GuildMapVassals"] = Set(self)
        self.__dict__["HasUltimateShop"] = False
        self.__dict__["ShortInfo"] = Ref(self)
        self.__dict__["Sieges"] = Set(self)


    def init(self, changeWriter):
        self.write(changeWriter)
        self.GuildShortInfoKeeper.init(u"GuildShortInfoKeeper", self, "GuildShortInfo")
        self.SiegeGuildInfoKeeper.init(u"SiegeGuildInfoKeeper", self, "SiegeGuildInfo")
        self.SiegeKeeper.init(u"SiegeKeeper", self, "SiegeInfo")
        self.GuildMapSuzerain.init(self.GuildShortInfoKeeper, u"/", self, "GuildMapSuzerain")
        self.GuildMapVassals.init(self.GuildShortInfoKeeper, u"GuildMapVassals", self)
        self.ShortInfo.init(self.GuildShortInfoKeeper, u"/", self, "ShortInfo")
        self.Sieges.init(self.SiegeKeeper, u"Sieges", self)


    @staticmethod
    def initJsonTypes(TCustomGuildMapData): # конечный класс CustomGuildMapData будет передавать снаружи, из datamanager
        if "GuildMapData" not in JSONSerialization.SERIALIZABLE_CLASSES:
            JSONSerialization.updateOurTypes((TCustomGuildMapData,
            GuildShortInfo.GuildShortInfo,
            SiegeGuildInfo.SiegeGuildInfo,
            SiegeInfo.SiegeInfo,
            ))
            JSONSerialization.SERIALIZABLE_CLASSES.update(
            { "GuildMapData" : TCustomGuildMapData
            , "Keeper" : Keeper
            , "Set" : Set
            , "SimpleList" : SimpleList
            , "SimpleDict" : SimpleDict
            , "Collection" : Collection
            , "Ref" : Ref
            , "GuildShortInfo" : GuildShortInfo.GuildShortInfo
            , "SiegeGuildInfo" : SiegeGuildInfo.SiegeGuildInfo
            , "SiegeInfo" : SiegeInfo.SiegeInfo
            })  
        else:
            err("GuildMapData.initJsonTypes called twice! The second call is:\n%s", errStack())

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
    def addNewSiegeGuildInfo(self):
        uid = self.nextGUID()
        var = SiegeGuildInfo.SiegeGuildInfo(self, uid, "SiegeGuildInfoKeeper/"+str(uid))
        var.init_add()
        self.SiegeGuildInfoKeeper.add(uid, var)
        return uid


    def getSiegeGuildInfoByID(self, id):
        return self.SiegeGuildInfoKeeper.get(id)


    def newSiegeGuildInfo(self):
        _id = self.addNewSiegeGuildInfo()
        _data = self.getSiegeGuildInfoByID(_id)
        return _data, _id
    def addNewSiegeInfo(self):
        uid = self.nextGUID()
        var = SiegeInfo.SiegeInfo(self, uid, "SiegeKeeper/"+str(uid))
        var.init_add()
        self.SiegeKeeper.add(uid, var)
        return uid


    def getSiegeInfoByID(self, id):
        return self.SiegeKeeper.get(id)


    def newSiegeInfo(self):
        _id = self.addNewSiegeInfo()
        _data = self.getSiegeInfoByID(_id)
        return _data, _id
    

    def deleteByID(self, id):
        self.GuildMapSuzerain.deleteByID(id)
        self.GuildMapVassals.deleteByID(id)
        self.ShortInfo.deleteByID(id)
        self.Sieges.deleteByID(id)

        #≈сли с RefCounter'ами все в пор€дке то объект к этому моменту уже должен быть удален из Keeper'ф
        obj = self.getObjectByID(id)
        if obj:
            #ј если не удален, значит RefCounter'ы глючат, и мы их обнул€ем что бы все нормально удал€лось
            obj.refCounter = 0

        self.GuildShortInfoKeeper.deleteByID(id)
        self.SiegeGuildInfoKeeper.deleteByID(id)
        self.SiegeKeeper.deleteByID(id)


    def getObjectByID(self, id):
        obj = None
        GuildShortInfo = self.getGuildShortInfoByID(id)
        if GuildShortInfo:
            obj = GuildShortInfo
        SiegeGuildInfo = self.getSiegeGuildInfoByID(id)
        if SiegeGuildInfo:
            obj = SiegeGuildInfo
        SiegeInfo = self.getSiegeInfoByID(id)
        if SiegeInfo:
            obj = SiegeInfo
        return obj


    def __setattr__(self, name, val):
        if name == "GuildMapSuzerain":
            self.__dict__["GuildMapSuzerain"].set(val)
            return    
        if name == "ShortInfo":
            self.__dict__["ShortInfo"].set(val)
            return    
        ChangeHandler.__setattr__(self, name, val)
    

    
    def generateJsonDict(self):
        _dct = GuildMapDataCustom.generateBaseDict(self)
        _dct.update(
            path=self.path,
            GuildMapSuzerain=self.__dict__["GuildMapSuzerain"].getJsonDict(),
            GuildMapVassals=self.__dict__["GuildMapVassals"].getJsonDict(),
            GuildShortInfoKeeper=self.__dict__["GuildShortInfoKeeper"].generateJsonDict(),
            HasUltimateShop=self.__dict__["HasUltimateShop"],
            ShortInfo=self.__dict__["ShortInfo"].getJsonDict(),
            SiegeGuildInfoKeeper=self.__dict__["SiegeGuildInfoKeeper"].generateJsonDict(),
            SiegeKeeper=self.__dict__["SiegeKeeper"].generateJsonDict(),
            Sieges=self.__dict__["Sieges"].getJsonDict(),
        )
        return { "GuildMapData": _dct }
    

    def serializeToFile(self, file):
        pass
        file.write("self.HasUltimateShop = " + repr(self.HasUltimateShop) + "\n")

    
# инициализаци€ списка сериализуемых классов при импорте модул€
GuildMapData.initJsonTypes(GuildMapData)
