# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import Hero
import DynamicQuestLampAward
import ResourceTable
import Skin
import Talent
import TalentUpgradeEntity

from LootboxReward_base import *

class LootboxReward(RefCounted, Identified, ChangeHandler, BaseObject, LootboxReward_base):
    _changeFields = {
        "Flags":1,
        "IsApplied":1,
        "PremiumAccDays":1,
        "UpgradeHeroTalentsCount":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Flags"] = SimpleList(modeldata)
        _dict["Heroes"] = Set(modeldata)
        _dict["IsApplied"] = False
        _dict["Lamp"] = DynamicQuestLampAward.DynamicQuestLampAward(modeldata, None, "")
        _dict["PremiumAccDays"] = 0
        _dict["Resources"] = ResourceTable.ResourceTable(modeldata, None, "")
        _dict["Skins"] = Set(modeldata)
        _dict["Talents"] = Set(modeldata)
        _dict["TalentUpgradeEntities"] = Set(modeldata)
        _dict["UpgradeHeroTalentsCount"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"Flags",None ):
            self.__dict__["Flags"] = SimpleList(self._modeldata)
        self.Flags.init(self.path + u"/Flags", self._modeldata)
        if not getattr(self,"Heroes",None ):
            self.__dict__["Heroes"] = Set(self._modeldata)
        self.Heroes.init(self._modeldata.HeroesKeeper, self.path + u"/Heroes", self._modeldata)
        self.Lamp.setPath(self.path + u"/Lamp")
        self.Resources.setPath(self.path + u"/Resources")
        if not getattr(self,"Skins",None ):
            self.__dict__["Skins"] = Set(self._modeldata)
        self.Skins.init(self._modeldata.SkinsKeeper, self.path + u"/Skins", self._modeldata)
        if not getattr(self,"Talents",None ):
            self.__dict__["Talents"] = Set(self._modeldata)
        self.Talents.init(self._modeldata.ItemsKeeper, self.path + u"/Talents", self._modeldata)
        if not getattr(self,"TalentUpgradeEntities",None ):
            self.__dict__["TalentUpgradeEntities"] = Set(self._modeldata)
        self.TalentUpgradeEntities.init(self._modeldata.TalentUpgradeEntitiesKeeper, self.path + u"/TalentUpgradeEntities", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"Flags",None ):
            self.__dict__["Flags"] = SimpleList(self._modeldata)
        self.Flags.init(self.path + u"/Flags", self._modeldata)
        if not getattr(self,"Heroes",None ):
            self.__dict__["Heroes"] = Set(self._modeldata)
        self.Heroes.init(self._modeldata.HeroesKeeper, self.path + u"/Heroes", self._modeldata)
        self.Lamp.setPath(self.path + u"/Lamp")
        self.Resources.setPath(self.path + u"/Resources")
        if not getattr(self,"Skins",None ):
            self.__dict__["Skins"] = Set(self._modeldata)
        self.Skins.init(self._modeldata.SkinsKeeper, self.path + u"/Skins", self._modeldata)
        if not getattr(self,"Talents",None ):
            self.__dict__["Talents"] = Set(self._modeldata)
        self.Talents.init(self._modeldata.ItemsKeeper, self.path + u"/Talents", self._modeldata)
        if not getattr(self,"TalentUpgradeEntities",None ):
            self.__dict__["TalentUpgradeEntities"] = Set(self._modeldata)
        self.TalentUpgradeEntities.init(self._modeldata.TalentUpgradeEntitiesKeeper, self.path + u"/TalentUpgradeEntities", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Flags.init(self.path + u"/Flags", self._modeldata)
        self.Heroes.init(self._modeldata.HeroesKeeper, self.path + u"/Heroes", self._modeldata)
        self.Lamp.setPath( self.path + u"/Lamp" )
        self.Resources.setPath( self.path + u"/Resources" )
        self.Skins.init(self._modeldata.SkinsKeeper, self.path + u"/Skins", self._modeldata)
        self.Talents.init(self._modeldata.ItemsKeeper, self.path + u"/Talents", self._modeldata)
        self.TalentUpgradeEntities.init(self._modeldata.TalentUpgradeEntitiesKeeper, self.path + u"/TalentUpgradeEntities", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Flags.deleteByID(id)
            self.Heroes.deleteByID(id)
            self.Lamp.deleteByID(id)
            self.Resources.deleteByID(id)
            self.Skins.deleteByID(id)
            self.Talents.deleteByID(id)
            self.TalentUpgradeEntities.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = LootboxReward_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Flags"]=_dict.get("Flags").getJsonDict()
        json_dict["Heroes"]=_dict.get("Heroes").getJsonDict()
        json_dict["IsApplied"]=_dict.get("IsApplied")
        json_dict["Lamp"] = _dict.get("Lamp").generateJsonDict()
        json_dict["PremiumAccDays"]=_dict.get("PremiumAccDays")
        json_dict["Resources"] = _dict.get("Resources").generateJsonDict()
        json_dict["Skins"]=_dict.get("Skins").getJsonDict()
        json_dict["Talents"]=_dict.get("Talents").getJsonDict()
        json_dict["TalentUpgradeEntities"]=_dict.get("TalentUpgradeEntities").getJsonDict()
        json_dict["UpgradeHeroTalentsCount"]=_dict.get("UpgradeHeroTalentsCount")
        return {"LootboxReward": json_dict}

if not hasattr(LootboxReward_base, "generateBaseDict"):
    LootboxReward_base.generateBaseDict = generateEmptyDict
