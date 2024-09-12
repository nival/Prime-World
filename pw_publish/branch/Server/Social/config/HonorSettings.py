# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from HonorSettings_base import *

class HonorSettings(RefCounted, Identified, ChangeHandler, BaseObject, HonorSettings_base):
    _changeFields = {
        "NormalVictoryPoints":1,
        "Penalty":1,
        "REWARD_CHECK_TIMEOUT_DURATION":1,
        "SmallVictoryPoints":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["NormalVictoryPoints"] = 1.0
        _dict["Penalty"] = 5.0
        _dict["REWARD_CHECK_TIMEOUT_DURATION"] = 604800
        _dict["SmallVictoryPoints"] = 0.5
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass

    # вызывается после model.addNewName()
    def init_add(self):
        pass

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = HonorSettings_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["NormalVictoryPoints"]=_dict.get("NormalVictoryPoints")
        json_dict["Penalty"]=_dict.get("Penalty")
        json_dict["REWARD_CHECK_TIMEOUT_DURATION"]=_dict.get("REWARD_CHECK_TIMEOUT_DURATION")
        json_dict["SmallVictoryPoints"]=_dict.get("SmallVictoryPoints")
        return {"HonorSettings": json_dict}

if not hasattr(HonorSettings_base, "generateBaseDict"):
    HonorSettings_base.generateBaseDict = generateEmptyDict
