# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import HeroStats
import TopBuildTalent

from TopBuildHero_base import *

class TopBuildHero(RefCounted, Identified, ChangeHandler, BaseObject, TopBuildHero_base):
    _changeFields = {
        "Auid":1,
        "Force":1,
        "Level":1,
        "Nickname":1,
        "PersistentId":1,
        "Rating":1,
        "Skin":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Auid"] = 0
        _dict["Force"] = 0.0
        _dict["Level"] = 0
        _dict["Nickname"] = ""
        _dict["PersistentId"] = 0
        _dict["Rating"] = 0.0
        _dict["Skin"] = 0
        _dict["Stats"] = HeroStats.HeroStats(modeldata, None, "")
        _dict["TalentSet"] = Collection(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.Stats.setPath(self.path + u"/Stats")
        if not getattr(self,"TalentSet",None ):
            self.__dict__["TalentSet"] = Collection(self._modeldata)
        self.TalentSet.init(self._modeldata.ItemsKeeper, self.path + u"/TalentSet", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.Stats.setPath(self.path + u"/Stats")
        if not getattr(self,"TalentSet",None ):
            self.__dict__["TalentSet"] = Collection(self._modeldata)
        self.TalentSet.init(self._modeldata.ItemsKeeper, self.path + u"/TalentSet", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Stats.setPath( self.path + u"/Stats" )
        self.TalentSet.init(self._modeldata.ItemsKeeper, self.path + u"/TalentSet", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Stats.deleteByID(id)
            self.TalentSet.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = TopBuildHero_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Auid"]=_dict.get("Auid")
        json_dict["Force"]=_dict.get("Force")
        json_dict["Level"]=_dict.get("Level")
        json_dict["Nickname"]=_dict.get("Nickname")
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["Rating"]=_dict.get("Rating")
        json_dict["Skin"]=_dict.get("Skin")
        json_dict["Stats"] = _dict.get("Stats").generateJsonDict()
        json_dict["TalentSet"]=_dict.get("TalentSet").getJsonDict()
        return {"TopBuildHero": json_dict}

if not hasattr(TopBuildHero_base, "generateBaseDict"):
    TopBuildHero_base.generateBaseDict = generateEmptyDict
