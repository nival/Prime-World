# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from RerollShopWeightsToTimes_base import *

class RerollShopWeightsToTimes(RefCounted, Identified, ChangeHandler, BaseObject, RerollShopWeightsToTimes_base):
    _changeFields = {
        "LevelToWeights":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["LevelToWeights"] = SimpleDict(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"LevelToWeights",None ):
            self.__dict__["LevelToWeights"] = SimpleDict(self._modeldata)
        self.LevelToWeights.init(self.path + u"/LevelToWeights", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"LevelToWeights",None ):
            self.__dict__["LevelToWeights"] = SimpleDict(self._modeldata)
        self.LevelToWeights.init(self.path + u"/LevelToWeights", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.LevelToWeights.init(self.path + u"/LevelToWeights", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.LevelToWeights.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = RerollShopWeightsToTimes_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["LevelToWeights"]=_dict.get("LevelToWeights").getJsonDict()
        return {"RerollShopWeightsToTimes": json_dict}

if not hasattr(RerollShopWeightsToTimes_base, "generateBaseDict"):
    RerollShopWeightsToTimes_base.generateBaseDict = generateEmptyDict
