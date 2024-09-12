# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import HeroStats
import TopBuildHero
import TopBuildTalent

import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from TopBuildsDataCustom import TopBuildsDataCustom

class TopBuildsData(ChangeHandler, TopBuildsDataCustom, IChangeWriter, IAbstractModelData, AutoIncGuidGenerator):
    _changeFields = {
    } 


    def __init__(self):
        TopBuildsDataCustom.__init__(self)
        ChangeHandler.__init__(self, u"/", self)
        AutoIncGuidGenerator.__init__(self)
        self._serializator = JSONSerialization(self)
        self.__dict__["HeroesKeeper"] = Keeper(self)
        self.__dict__["ItemsKeeper"] = Keeper(self)
        self.__dict__["Heroes"] = Set(self)


    def init(self, changeWriter):
        self.write(changeWriter)
        self.HeroesKeeper.init(u"HeroesKeeper", self, "TopBuildHero")
        self.ItemsKeeper.init(u"ItemsKeeper", self, "TopBuildTalent")
        self.Heroes.init(self.HeroesKeeper, u"Heroes", self)


    @staticmethod
    def initJsonTypes(TCustomTopBuildsData): # конечный класс CustomTopBuildsData будет передавать снаружи, из datamanager
        if "TopBuildsData" not in JSONSerialization.SERIALIZABLE_CLASSES:
            JSONSerialization.updateOurTypes((TCustomTopBuildsData,
            HeroStats.HeroStats,
            TopBuildHero.TopBuildHero,
            TopBuildTalent.TopBuildTalent,
            ))
            JSONSerialization.SERIALIZABLE_CLASSES.update(
            { "TopBuildsData" : TCustomTopBuildsData
            , "Keeper" : Keeper
            , "Set" : Set
            , "SimpleList" : SimpleList
            , "SimpleDict" : SimpleDict
            , "Collection" : Collection
            , "Ref" : Ref
            , "HeroStats" : HeroStats.HeroStats
            , "TopBuildHero" : TopBuildHero.TopBuildHero
            , "TopBuildTalent" : TopBuildTalent.TopBuildTalent
            })  
        else:
            err("TopBuildsData.initJsonTypes called twice! The second call is:\n%s", errStack())

    def addNewTopBuildHero(self):
        uid = self.nextGUID()
        var = TopBuildHero.TopBuildHero(self, uid, "HeroesKeeper/"+str(uid))
        var.init_add()
        self.HeroesKeeper.add(uid, var)
        return uid


    def getTopBuildHeroByID(self, id):
        return self.HeroesKeeper.get(id)


    def newTopBuildHero(self):
        _id = self.addNewTopBuildHero()
        _data = self.getTopBuildHeroByID(_id)
        return _data, _id
    def addNewTopBuildTalent(self):
        uid = self.nextGUID()
        var = TopBuildTalent.TopBuildTalent(self, uid, "ItemsKeeper/"+str(uid))
        var.init_add()
        self.ItemsKeeper.add(uid, var)
        return uid


    def getTopBuildTalentByID(self, id):
        return self.ItemsKeeper.get(id)


    def newTopBuildTalent(self):
        _id = self.addNewTopBuildTalent()
        _data = self.getTopBuildTalentByID(_id)
        return _data, _id
    

    def deleteByID(self, id):
        self.Heroes.deleteByID(id)

        #≈сли с RefCounter'ами все в пор€дке то объект к этому моменту уже должен быть удален из Keeper'ф
        obj = self.getObjectByID(id)
        if obj:
            #ј если не удален, значит RefCounter'ы глючат, и мы их обнул€ем что бы все нормально удал€лось
            obj.refCounter = 0

        self.HeroesKeeper.deleteByID(id)
        self.ItemsKeeper.deleteByID(id)


    def getObjectByID(self, id):
        obj = None
        TopBuildHero = self.getTopBuildHeroByID(id)
        if TopBuildHero:
            obj = TopBuildHero
        TopBuildTalent = self.getTopBuildTalentByID(id)
        if TopBuildTalent:
            obj = TopBuildTalent
        return obj


    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)
    

    
    def generateJsonDict(self):
        _dct = TopBuildsDataCustom.generateBaseDict(self)
        _dct.update(
            path=self.path,
            Heroes=self.__dict__["Heroes"].getJsonDict(),
            HeroesKeeper=self.__dict__["HeroesKeeper"].generateJsonDict(),
            ItemsKeeper=self.__dict__["ItemsKeeper"].generateJsonDict(),
        )
        return { "TopBuildsData": _dct }
    

    def serializeToFile(self, file):
        pass

    
# инициализаци€ списка сериализуемых классов при импорте модул€
TopBuildsData.initJsonTypes(TopBuildsData)
