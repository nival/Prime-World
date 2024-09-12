# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import ConstructionQuest
import Hero
import ConstructionPosition

from Construction_base import *

class Construction(RefCounted, Identified, ChangeHandler, BaseObject, Construction_base):
    _changeFields = {
        "BoostEndTime":1,
        "CraftedTalents":1,
        "CraftedTalentsToLibrary":1,
        "cycle":1,
        "EndProductionTime":1,
        "FameValue":1,
        "Level":1,
        "mdIndex":1,
        "PersistentId":1,
        "ProductionCustomValue":1,
        "ProductionLevel":1,
        "ProductionPremium":1,
        "ProductionState":1,
        "ProductionValue":1,
        "ResourceToProduce":1,
        "StartProductionTime":1,
        "WasPlacedOnScene":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["BoostEndTime"] = 0
        _dict["BuildingQuest"] = ConstructionQuest.ConstructionQuest(modeldata, None, "")
        _dict["CraftedTalents"] = SimpleList(modeldata)
        _dict["CraftedTalentsToLibrary"] = SimpleList(modeldata)
        _dict["cycle"] = 0
        _dict["EndProductionTime"] = 0
        _dict["FameValue"] = 0.0
        _dict["HeroesInBuilding"] = Set(modeldata)
        _dict["Level"] = 0
        _dict["mdIndex"] = 78336
        _dict["PersistentId"] = 0
        _dict["Position"] = ConstructionPosition.ConstructionPosition(modeldata, None, "")
        _dict["ProductionCustomValue"] = 0
        _dict["ProductionLevel"] = 0
        _dict["ProductionPremium"] = False
        _dict["ProductionState"] = 0
        _dict["ProductionValue"] = 0.0
        _dict["ResourceToProduce"] = 0
        _dict["StartProductionTime"] = 0
        _dict["WasPlacedOnScene"] = False
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.BuildingQuest.setPath(self.path + u"/BuildingQuest")
        if not getattr(self,"CraftedTalents",None ):
            self.__dict__["CraftedTalents"] = SimpleList(self._modeldata)
        self.CraftedTalents.init(self.path + u"/CraftedTalents", self._modeldata)
        if not getattr(self,"CraftedTalentsToLibrary",None ):
            self.__dict__["CraftedTalentsToLibrary"] = SimpleList(self._modeldata)
        self.CraftedTalentsToLibrary.init(self.path + u"/CraftedTalentsToLibrary", self._modeldata)
        if not getattr(self,"HeroesInBuilding",None ):
            self.__dict__["HeroesInBuilding"] = Set(self._modeldata)
        self.HeroesInBuilding.init(self._modeldata.HeroesKeeper, self.path + u"/HeroesInBuilding", self._modeldata)
        self.Position.setPath(self.path + u"/Position")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.BuildingQuest.setPath(self.path + u"/BuildingQuest")
        if not getattr(self,"CraftedTalents",None ):
            self.__dict__["CraftedTalents"] = SimpleList(self._modeldata)
        self.CraftedTalents.init(self.path + u"/CraftedTalents", self._modeldata)
        if not getattr(self,"CraftedTalentsToLibrary",None ):
            self.__dict__["CraftedTalentsToLibrary"] = SimpleList(self._modeldata)
        self.CraftedTalentsToLibrary.init(self.path + u"/CraftedTalentsToLibrary", self._modeldata)
        if not getattr(self,"HeroesInBuilding",None ):
            self.__dict__["HeroesInBuilding"] = Set(self._modeldata)
        self.HeroesInBuilding.init(self._modeldata.HeroesKeeper, self.path + u"/HeroesInBuilding", self._modeldata)
        self.Position.setPath(self.path + u"/Position")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.BuildingQuest.setPath( self.path + u"/BuildingQuest" )
        self.CraftedTalents.init(self.path + u"/CraftedTalents", self._modeldata)
        self.CraftedTalentsToLibrary.init(self.path + u"/CraftedTalentsToLibrary", self._modeldata)
        self.HeroesInBuilding.init(self._modeldata.HeroesKeeper, self.path + u"/HeroesInBuilding", self._modeldata)
        self.Position.setPath( self.path + u"/Position" )

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.BuildingQuest.deleteByID(id)
            self.CraftedTalents.deleteByID(id)
            self.CraftedTalentsToLibrary.deleteByID(id)
            self.HeroesInBuilding.deleteByID(id)
            self.Position.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = Construction_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["BoostEndTime"]=_dict.get("BoostEndTime")
        json_dict["BuildingQuest"] = _dict.get("BuildingQuest").generateJsonDict()
        json_dict["CraftedTalents"]=_dict.get("CraftedTalents").getJsonDict()
        json_dict["CraftedTalentsToLibrary"]=_dict.get("CraftedTalentsToLibrary").getJsonDict()
        json_dict["cycle"]=_dict.get("cycle")
        json_dict["EndProductionTime"]=_dict.get("EndProductionTime")
        json_dict["FameValue"]=_dict.get("FameValue")
        json_dict["HeroesInBuilding"]=_dict.get("HeroesInBuilding").getJsonDict()
        json_dict["Level"]=_dict.get("Level")
        json_dict["mdIndex"]=_dict.get("mdIndex")
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["Position"] = _dict.get("Position").generateJsonDict()
        json_dict["ProductionCustomValue"]=_dict.get("ProductionCustomValue")
        json_dict["ProductionLevel"]=_dict.get("ProductionLevel")
        json_dict["ProductionPremium"]=_dict.get("ProductionPremium")
        json_dict["ProductionState"]=_dict.get("ProductionState")
        json_dict["ProductionValue"]=_dict.get("ProductionValue")
        json_dict["ResourceToProduce"]=_dict.get("ResourceToProduce")
        json_dict["StartProductionTime"]=_dict.get("StartProductionTime")
        json_dict["WasPlacedOnScene"]=_dict.get("WasPlacedOnScene")
        return {"Construction": json_dict}

if not hasattr(Construction_base, "generateBaseDict"):
    Construction_base.generateBaseDict = generateEmptyDict
