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
import Siege
import SiegeGuildInfo

import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from SiegeDataCustom import SiegeDataCustom

class SiegeData(ChangeHandler, SiegeDataCustom, IChangeWriter, IAbstractModelData, AutoIncGuidGenerator):
    _changeFields = {
    } 


    def __init__(self):
        SiegeDataCustom.__init__(self)
        ChangeHandler.__init__(self, u"/", self)
        AutoIncGuidGenerator.__init__(self)
        self._serializator = JSONSerialization(self)
        self.__dict__["GuildShortInfoKeeper"] = Keeper(self)
        self.__dict__["SiegeGuildInfoKeeper"] = Keeper(self)
        self.__dict__["SiegeKeeper"] = Keeper(self)
        self.__dict__["ActiveSieges"] = Set(self)


    def init(self, changeWriter):
        self.write(changeWriter)
        self.GuildShortInfoKeeper.init(u"GuildShortInfoKeeper", self, "GuildShortInfo")
        self.SiegeGuildInfoKeeper.init(u"SiegeGuildInfoKeeper", self, "SiegeGuildInfo")
        self.SiegeKeeper.init(u"SiegeKeeper", self, "Siege")
        self.ActiveSieges.init(self.SiegeKeeper, u"ActiveSieges", self)


    @staticmethod
    def initJsonTypes(TCustomSiegeData): # конечный класс CustomSiegeData будет передавать снаружи, из datamanager
        if "SiegeData" not in JSONSerialization.SERIALIZABLE_CLASSES:
            JSONSerialization.updateOurTypes((TCustomSiegeData,
            GuildShortInfo.GuildShortInfo,
            Siege.Siege,
            SiegeGuildInfo.SiegeGuildInfo,
            ))
            JSONSerialization.SERIALIZABLE_CLASSES.update(
            { "SiegeData" : TCustomSiegeData
            , "Keeper" : Keeper
            , "Set" : Set
            , "SimpleList" : SimpleList
            , "SimpleDict" : SimpleDict
            , "Collection" : Collection
            , "Ref" : Ref
            , "GuildShortInfo" : GuildShortInfo.GuildShortInfo
            , "Siege" : Siege.Siege
            , "SiegeGuildInfo" : SiegeGuildInfo.SiegeGuildInfo
            })  
        else:
            err("SiegeData.initJsonTypes called twice! The second call is:\n%s", errStack())

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
    def addNewSiege(self):
        uid = self.nextGUID()
        var = Siege.Siege(self, uid, "SiegeKeeper/"+str(uid))
        var.init_add()
        self.SiegeKeeper.add(uid, var)
        return uid


    def getSiegeByID(self, id):
        return self.SiegeKeeper.get(id)


    def newSiege(self):
        _id = self.addNewSiege()
        _data = self.getSiegeByID(_id)
        return _data, _id
    

    def deleteByID(self, id):
        self.ActiveSieges.deleteByID(id)

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
        Siege = self.getSiegeByID(id)
        if Siege:
            obj = Siege
        return obj


    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)
    

    
    def generateJsonDict(self):
        _dct = SiegeDataCustom.generateBaseDict(self)
        _dct.update(
            path=self.path,
            ActiveSieges=self.__dict__["ActiveSieges"].getJsonDict(),
            GuildShortInfoKeeper=self.__dict__["GuildShortInfoKeeper"].generateJsonDict(),
            SiegeGuildInfoKeeper=self.__dict__["SiegeGuildInfoKeeper"].generateJsonDict(),
            SiegeKeeper=self.__dict__["SiegeKeeper"].generateJsonDict(),
        )
        return { "SiegeData": _dct }
    

    def serializeToFile(self, file):
        pass

    
# инициализаци€ списка сериализуемых классов при импорте модул€
SiegeData.initJsonTypes(SiegeData)
