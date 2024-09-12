# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import HonorReward

from HonorInfo_base import *

class HonorInfo(RefCounted, Identified, ChangeHandler, BaseObject, HonorInfo_base):
    _changeFields = {
        "CurrentLevel":1,
        "CurrentLevelPoints":1,
        "PenaltyPoints":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["CurrentLevel"] = 0
        _dict["CurrentLevelPoints"] = 0.0
        _dict["LevelUpReward"] = HonorReward.HonorReward(modeldata, None, "")
        _dict["PenaltyPoints"] = 0.0
        _dict["WeeklyReward"] = HonorReward.HonorReward(modeldata, None, "")
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.LevelUpReward.setPath(self.path + u"/LevelUpReward")
        self.WeeklyReward.setPath(self.path + u"/WeeklyReward")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.LevelUpReward.setPath(self.path + u"/LevelUpReward")
        self.WeeklyReward.setPath(self.path + u"/WeeklyReward")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.LevelUpReward.setPath( self.path + u"/LevelUpReward" )
        self.WeeklyReward.setPath( self.path + u"/WeeklyReward" )

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.LevelUpReward.deleteByID(id)
            self.WeeklyReward.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = HonorInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["CurrentLevel"]=_dict.get("CurrentLevel")
        json_dict["CurrentLevelPoints"]=_dict.get("CurrentLevelPoints")
        json_dict["LevelUpReward"] = _dict.get("LevelUpReward").generateJsonDict()
        json_dict["PenaltyPoints"]=_dict.get("PenaltyPoints")
        json_dict["WeeklyReward"] = _dict.get("WeeklyReward").generateJsonDict()
        return {"HonorInfo": json_dict}

if not hasattr(HonorInfo_base, "generateBaseDict"):
    HonorInfo_base.generateBaseDict = generateEmptyDict
