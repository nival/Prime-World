# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import GuildApplicantInfo

import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from RecruitsDataCustom import RecruitsDataCustom

class RecruitsData(ChangeHandler, RecruitsDataCustom, IChangeWriter, IAbstractModelData, AutoIncGuidGenerator):
    _changeFields = {
        "HasChanges":1,
    } 


    def __init__(self):
        RecruitsDataCustom.__init__(self)
        ChangeHandler.__init__(self, u"/", self)
        AutoIncGuidGenerator.__init__(self)
        self._serializator = JSONSerialization(self)
        self.__dict__["GuildApplicantInfoKeeper"] = Keeper(self)
        self.__dict__["GuildApplicants"] = Set(self)
        self.__dict__["HasChanges"] = False


    def init(self, changeWriter):
        self.write(changeWriter)
        self.GuildApplicantInfoKeeper.init(u"GuildApplicantInfoKeeper", self, "GuildApplicantInfo")
        self.GuildApplicants.init(self.GuildApplicantInfoKeeper, u"GuildApplicants", self)


    @staticmethod
    def initJsonTypes(TCustomRecruitsData): # конечный класс CustomRecruitsData будет передавать снаружи, из datamanager
        if "RecruitsData" not in JSONSerialization.SERIALIZABLE_CLASSES:
            JSONSerialization.updateOurTypes((TCustomRecruitsData,
            GuildApplicantInfo.GuildApplicantInfo,
            ))
            JSONSerialization.SERIALIZABLE_CLASSES.update(
            { "RecruitsData" : TCustomRecruitsData
            , "Keeper" : Keeper
            , "Set" : Set
            , "SimpleList" : SimpleList
            , "SimpleDict" : SimpleDict
            , "Collection" : Collection
            , "Ref" : Ref
            , "GuildApplicantInfo" : GuildApplicantInfo.GuildApplicantInfo
            })  
        else:
            err("RecruitsData.initJsonTypes called twice! The second call is:\n%s", errStack())

    def addNewGuildApplicantInfo(self):
        uid = self.nextGUID()
        var = GuildApplicantInfo.GuildApplicantInfo(self, uid, "GuildApplicantInfoKeeper/"+str(uid))
        var.init_add()
        self.GuildApplicantInfoKeeper.add(uid, var)
        return uid


    def getGuildApplicantInfoByID(self, id):
        return self.GuildApplicantInfoKeeper.get(id)


    def newGuildApplicantInfo(self):
        _id = self.addNewGuildApplicantInfo()
        _data = self.getGuildApplicantInfoByID(_id)
        return _data, _id
    

    def deleteByID(self, id):
        self.GuildApplicants.deleteByID(id)

        #≈сли с RefCounter'ами все в пор€дке то объект к этому моменту уже должен быть удален из Keeper'ф
        obj = self.getObjectByID(id)
        if obj:
            #ј если не удален, значит RefCounter'ы глючат, и мы их обнул€ем что бы все нормально удал€лось
            obj.refCounter = 0

        self.GuildApplicantInfoKeeper.deleteByID(id)


    def getObjectByID(self, id):
        obj = None
        GuildApplicantInfo = self.getGuildApplicantInfoByID(id)
        if GuildApplicantInfo:
            obj = GuildApplicantInfo
        return obj


    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)
    

    
    def generateJsonDict(self):
        _dct = RecruitsDataCustom.generateBaseDict(self)
        _dct.update(
            path=self.path,
            GuildApplicantInfoKeeper=self.__dict__["GuildApplicantInfoKeeper"].generateJsonDict(),
            GuildApplicants=self.__dict__["GuildApplicants"].getJsonDict(),
            HasChanges=self.__dict__["HasChanges"],
        )
        return { "RecruitsData": _dct }
    

    def serializeToFile(self, file):
        pass
        file.write("self.HasChanges = " + repr(self.HasChanges) + "\n")

    
# инициализаци€ списка сериализуемых классов при импорте модул€
RecruitsData.initJsonTypes(RecruitsData)
