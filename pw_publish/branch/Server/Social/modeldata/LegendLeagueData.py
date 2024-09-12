# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import LegendLeagueListEntity

import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from LegendLeagueDataCustom import LegendLeagueDataCustom

class LegendLeagueData(ChangeHandler, LegendLeagueDataCustom, IChangeWriter, IAbstractModelData, AutoIncGuidGenerator):
    _changeFields = {
    } 


    def __init__(self):
        LegendLeagueDataCustom.__init__(self)
        ChangeHandler.__init__(self, u"/", self)
        AutoIncGuidGenerator.__init__(self)
        self._serializator = JSONSerialization(self)
        self.__dict__["LegendLeagueListEntityKeeper"] = Keeper(self)
        self.__dict__["AllLeaguesInfo"] = Set(self)


    def init(self, changeWriter):
        self.write(changeWriter)
        self.LegendLeagueListEntityKeeper.init(u"LegendLeagueListEntityKeeper", self, "LegendLeagueListEntity")
        self.AllLeaguesInfo.init(self.LegendLeagueListEntityKeeper, u"AllLeaguesInfo", self)


    @staticmethod
    def initJsonTypes(TCustomLegendLeagueData): # конечный класс CustomLegendLeagueData будет передавать снаружи, из datamanager
        if "LegendLeagueData" not in JSONSerialization.SERIALIZABLE_CLASSES:
            JSONSerialization.updateOurTypes((TCustomLegendLeagueData,
            LegendLeagueListEntity.LegendLeagueListEntity,
            ))
            JSONSerialization.SERIALIZABLE_CLASSES.update(
            { "LegendLeagueData" : TCustomLegendLeagueData
            , "Keeper" : Keeper
            , "Set" : Set
            , "SimpleList" : SimpleList
            , "SimpleDict" : SimpleDict
            , "Collection" : Collection
            , "Ref" : Ref
            , "LegendLeagueListEntity" : LegendLeagueListEntity.LegendLeagueListEntity
            })  
        else:
            err("LegendLeagueData.initJsonTypes called twice! The second call is:\n%s", errStack())

    def addNewLegendLeagueListEntity(self):
        uid = self.nextGUID()
        var = LegendLeagueListEntity.LegendLeagueListEntity(self, uid, "LegendLeagueListEntityKeeper/"+str(uid))
        var.init_add()
        self.LegendLeagueListEntityKeeper.add(uid, var)
        return uid


    def getLegendLeagueListEntityByID(self, id):
        return self.LegendLeagueListEntityKeeper.get(id)


    def newLegendLeagueListEntity(self):
        _id = self.addNewLegendLeagueListEntity()
        _data = self.getLegendLeagueListEntityByID(_id)
        return _data, _id
    

    def deleteByID(self, id):
        self.AllLeaguesInfo.deleteByID(id)

        #≈сли с RefCounter'ами все в пор€дке то объект к этому моменту уже должен быть удален из Keeper'ф
        obj = self.getObjectByID(id)
        if obj:
            #ј если не удален, значит RefCounter'ы глючат, и мы их обнул€ем что бы все нормально удал€лось
            obj.refCounter = 0

        self.LegendLeagueListEntityKeeper.deleteByID(id)


    def getObjectByID(self, id):
        obj = None
        LegendLeagueListEntity = self.getLegendLeagueListEntityByID(id)
        if LegendLeagueListEntity:
            obj = LegendLeagueListEntity
        return obj


    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)
    

    
    def generateJsonDict(self):
        _dct = LegendLeagueDataCustom.generateBaseDict(self)
        _dct.update(
            path=self.path,
            AllLeaguesInfo=self.__dict__["AllLeaguesInfo"].getJsonDict(),
            LegendLeagueListEntityKeeper=self.__dict__["LegendLeagueListEntityKeeper"].generateJsonDict(),
        )
        return { "LegendLeagueData": _dct }
    

    def serializeToFile(self, file):
        pass

    
# инициализаци€ списка сериализуемых классов при импорте модул€
LegendLeagueData.initJsonTypes(LegendLeagueData)
