# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from ConstructionQuest_base import *

class ConstructionQuest(RefCounted, Identified, ChangeHandler, BaseObject, ConstructionQuest_base):
    _changeFields = {
        "Index":1,
        "IsDailyQuestFinished":1,
        "Level":1,
        "StatSum":1,
        "TimeForReroll":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Index"] = -1
        _dict["IsDailyQuestFinished"] = False
        _dict["Level"] = -1
        _dict["StatSum"] = 0
        _dict["TimeForReroll"] = 0
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
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = ConstructionQuest_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Index"]=_dict.get("Index")
        json_dict["IsDailyQuestFinished"]=_dict.get("IsDailyQuestFinished")
        json_dict["Level"]=_dict.get("Level")
        json_dict["StatSum"]=_dict.get("StatSum")
        json_dict["TimeForReroll"]=_dict.get("TimeForReroll")
        return {"ConstructionQuest": json_dict}

if not hasattr(ConstructionQuest_base, "generateBaseDict"):
    ConstructionQuest_base.generateBaseDict = generateEmptyDict
