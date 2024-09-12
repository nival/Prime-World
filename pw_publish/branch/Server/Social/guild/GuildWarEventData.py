# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from GuildWarEventDataCustom import GuildWarEventDataCustom

class GuildWarEventData(ChangeHandler, GuildWarEventDataCustom, IChangeWriter, IAbstractModelData, AutoIncGuidGenerator):
    _changeFields = {
        "Enabled":1,
        "EndTime":1,
        "EventIndex":1,
        "Id":1,
        "Points":1,
        "PointsCap":1,
    } 


    def __init__(self):
        GuildWarEventDataCustom.__init__(self)
        ChangeHandler.__init__(self, u"/", self)
        AutoIncGuidGenerator.__init__(self)
        self._serializator = JSONSerialization(self)
        self.__dict__["Enabled"] = False
        self.__dict__["EndTime"] = 0
        self.__dict__["EventIndex"] = 0
        self.__dict__["Id"] = ""
        self.__dict__["Points"] = 0
        self.__dict__["PointsCap"] = 0


    def init(self, changeWriter):
        self.write(changeWriter)


    @staticmethod
    def initJsonTypes(TCustomGuildWarEventData): # конечный класс CustomGuildWarEventData будет передавать снаружи, из datamanager
        if "GuildWarEventData" not in JSONSerialization.SERIALIZABLE_CLASSES:
            JSONSerialization.updateOurTypes((TCustomGuildWarEventData,
            ))
            JSONSerialization.SERIALIZABLE_CLASSES.update(
            { "GuildWarEventData" : TCustomGuildWarEventData
            , "Keeper" : Keeper
            , "Set" : Set
            , "SimpleList" : SimpleList
            , "SimpleDict" : SimpleDict
            , "Collection" : Collection
            , "Ref" : Ref
            })  
        else:
            err("GuildWarEventData.initJsonTypes called twice! The second call is:\n%s", errStack())

    

    def deleteByID(self, id):

        #≈сли с RefCounter'ами все в пор€дке то объект к этому моменту уже должен быть удален из Keeper'ф
        obj = self.getObjectByID(id)
        if obj:
            #ј если не удален, значит RefCounter'ы глючат, и мы их обнул€ем что бы все нормально удал€лось
            obj.refCounter = 0



    def getObjectByID(self, id):
        obj = None
        return obj


    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)
    

    
    def generateJsonDict(self):
        _dct = GuildWarEventDataCustom.generateBaseDict(self)
        _dct.update(
            path=self.path,
            Enabled=self.__dict__["Enabled"],
            EndTime=self.__dict__["EndTime"],
            EventIndex=self.__dict__["EventIndex"],
            Id=self.__dict__["Id"],
            Points=self.__dict__["Points"],
            PointsCap=self.__dict__["PointsCap"],
        )
        return { "GuildWarEventData": _dct }
    

    def serializeToFile(self, file):
        pass
        file.write("self.Enabled = " + repr(self.Enabled) + "\n")
        file.write("self.EndTime = " + repr(self.EndTime) + "\n")
        file.write("self.EventIndex = " + repr(self.EventIndex) + "\n")
        file.write("self.Id = " + repr(self.Id) + "\n")
        file.write("self.Points = " + repr(self.Points) + "\n")
        file.write("self.PointsCap = " + repr(self.PointsCap) + "\n")

    
# инициализаци€ списка сериализуемых классов при импорте модул€
GuildWarEventData.initJsonTypes(GuildWarEventData)
