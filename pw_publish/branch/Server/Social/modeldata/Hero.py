# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import HeroSkins
import Construction
import SeasonInfo
import TalentSet

from Hero_base import *

class Hero(RefCounted, Identified, ChangeHandler, BaseObject, Hero_base):
    _changeFields = {
        "ActiveTalentSet":1,
        "class_name":1,
        "Enabled":1,
        "EpicWins":1,
        "Experience":1,
        "FirstBuyApplied":1,
        "Hired":1,
        "InMatchmaking":1,
        "IsAnimatedAvatar":1,
        "IsUpgradeHeroEvent":1,
        "lastPlayed":1,
        "Master":1,
        "PersistentId":1,
        "Rating":1,
        "removedDefaultTalents":1,
        "Version":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["ActiveTalentSet"] = 0
        _dict["class_name"] = ""
        _dict["Enabled"] = True
        _dict["EpicWins"] = 0
        _dict["Experience"] = 0
        _dict["FirstBuyApplied"] = False
        _dict["HeroSkins"] = HeroSkins.HeroSkins(modeldata, None, "")
        _dict["Hired"] = False
        _dict["InBuildings"] = Set(modeldata)
        _dict["InMatchmaking"] = False
        _dict["IsAnimatedAvatar"] = False
        _dict["IsUpgradeHeroEvent"] = False
        _dict["lastPlayed"] = 0
        _dict["Master"] = False
        _dict["PersistentId"] = 0
        _dict["Rating"] = 0.0
        _dict["removedDefaultTalents"] = SimpleList(modeldata)
        _dict["SeasonsInfo"] = Collection(modeldata)
        _dict["TalentSets"] = Collection(modeldata)
        _dict["Version"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.HeroSkins.setPath(self.path + u"/HeroSkins")
        if not getattr(self,"InBuildings",None ):
            self.__dict__["InBuildings"] = Set(self._modeldata)
        self.InBuildings.init(self._modeldata.ConstructionsKeeper, self.path + u"/InBuildings", self._modeldata)
        if not getattr(self,"removedDefaultTalents",None ):
            self.__dict__["removedDefaultTalents"] = SimpleList(self._modeldata)
        self.removedDefaultTalents.init(self.path + u"/removedDefaultTalents", self._modeldata)
        if not getattr(self,"SeasonsInfo",None ):
            self.__dict__["SeasonsInfo"] = Collection(self._modeldata)
        self.SeasonsInfo.init(self._modeldata.SeasonInfoKeeper, self.path + u"/SeasonsInfo", self._modeldata)
        if not getattr(self,"TalentSets",None ):
            self.__dict__["TalentSets"] = Collection(self._modeldata)
        self.TalentSets.init(self._modeldata.TalentSetsKeeper, self.path + u"/TalentSets", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.HeroSkins.setPath(self.path + u"/HeroSkins")
        if not getattr(self,"InBuildings",None ):
            self.__dict__["InBuildings"] = Set(self._modeldata)
        self.InBuildings.init(self._modeldata.ConstructionsKeeper, self.path + u"/InBuildings", self._modeldata)
        if not getattr(self,"removedDefaultTalents",None ):
            self.__dict__["removedDefaultTalents"] = SimpleList(self._modeldata)
        self.removedDefaultTalents.init(self.path + u"/removedDefaultTalents", self._modeldata)
        if not getattr(self,"SeasonsInfo",None ):
            self.__dict__["SeasonsInfo"] = Collection(self._modeldata)
        self.SeasonsInfo.init(self._modeldata.SeasonInfoKeeper, self.path + u"/SeasonsInfo", self._modeldata)
        if not getattr(self,"TalentSets",None ):
            self.__dict__["TalentSets"] = Collection(self._modeldata)
        self.TalentSets.init(self._modeldata.TalentSetsKeeper, self.path + u"/TalentSets", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.HeroSkins.setPath( self.path + u"/HeroSkins" )
        self.InBuildings.init(self._modeldata.ConstructionsKeeper, self.path + u"/InBuildings", self._modeldata)
        self.removedDefaultTalents.init(self.path + u"/removedDefaultTalents", self._modeldata)
        self.SeasonsInfo.init(self._modeldata.SeasonInfoKeeper, self.path + u"/SeasonsInfo", self._modeldata)
        self.TalentSets.init(self._modeldata.TalentSetsKeeper, self.path + u"/TalentSets", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.HeroSkins.deleteByID(id)
            self.InBuildings.deleteByID(id)
            self.removedDefaultTalents.deleteByID(id)
            self.SeasonsInfo.deleteByID(id)
            self.TalentSets.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = Hero_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["ActiveTalentSet"]=_dict.get("ActiveTalentSet")
        json_dict["class_name"]=_dict.get("class_name")
        json_dict["Enabled"]=_dict.get("Enabled")
        json_dict["EpicWins"]=_dict.get("EpicWins")
        json_dict["Experience"]=_dict.get("Experience")
        json_dict["FirstBuyApplied"]=_dict.get("FirstBuyApplied")
        json_dict["HeroSkins"] = _dict.get("HeroSkins").generateJsonDict()
        json_dict["Hired"]=_dict.get("Hired")
        json_dict["InBuildings"]=_dict.get("InBuildings").getJsonDict()
        json_dict["InMatchmaking"]=_dict.get("InMatchmaking")
        json_dict["IsAnimatedAvatar"]=_dict.get("IsAnimatedAvatar")
        json_dict["IsUpgradeHeroEvent"]=_dict.get("IsUpgradeHeroEvent")
        json_dict["lastPlayed"]=_dict.get("lastPlayed")
        json_dict["Master"]=_dict.get("Master")
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["Rating"]=_dict.get("Rating")
        json_dict["removedDefaultTalents"]=_dict.get("removedDefaultTalents").getJsonDict()
        json_dict["SeasonsInfo"]=_dict.get("SeasonsInfo").getJsonDict()
        json_dict["TalentSets"]=_dict.get("TalentSets").getJsonDict()
        json_dict["Version"]=_dict.get("Version")
        return {"Hero": json_dict}

if not hasattr(Hero_base, "generateBaseDict"):
    Hero_base.generateBaseDict = generateEmptyDict
