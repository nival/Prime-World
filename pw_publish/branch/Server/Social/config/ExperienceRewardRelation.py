# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import RollEventItem

from ExperienceRewardRelation_base import *

class ExperienceRewardRelation(RefCounted, Identified, ChangeHandler, BaseObject, ExperienceRewardRelation_base):
    _changeFields = {
        "Experience":1,
        "IsMinor":1,
        "RewardCount":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Experience"] = 0
        _dict["IsMinor"] = False
        _dict["Reward"] = Collection(modeldata)
        _dict["RewardCount"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"Reward",None ):
            self.__dict__["Reward"] = Collection(self._modeldata)
        self.Reward.init(self._modeldata.RollEventItemKeeper, self.path + u"/Reward", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"Reward",None ):
            self.__dict__["Reward"] = Collection(self._modeldata)
        self.Reward.init(self._modeldata.RollEventItemKeeper, self.path + u"/Reward", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Reward.init(self._modeldata.RollEventItemKeeper, self.path + u"/Reward", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Reward.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = ExperienceRewardRelation_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Experience"]=_dict.get("Experience")
        json_dict["IsMinor"]=_dict.get("IsMinor")
        json_dict["Reward"]=_dict.get("Reward").getJsonDict()
        json_dict["RewardCount"]=_dict.get("RewardCount")
        return {"ExperienceRewardRelation": json_dict}

if not hasattr(ExperienceRewardRelation_base, "generateBaseDict"):
    ExperienceRewardRelation_base.generateBaseDict = generateEmptyDict
