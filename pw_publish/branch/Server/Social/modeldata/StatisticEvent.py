# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from StatisticEvent_base import *

class StatisticEvent(RefCounted, Identified, ChangeHandler, BaseObject, StatisticEvent_base):
    _changeFields = {
        "actionType":1,
        "description":1,
        "time":1,
        "value":1,
        "valueChange":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["actionType"] = 0
        _dict["description"] = ""
        _dict["time"] = 0
        _dict["value"] = 0
        _dict["valueChange"] = 0
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
        json_dict = StatisticEvent_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["actionType"]=_dict.get("actionType")
        json_dict["description"]=_dict.get("description")
        json_dict["time"]=_dict.get("time")
        json_dict["value"]=_dict.get("value")
        json_dict["valueChange"]=_dict.get("valueChange")
        return {"StatisticEvent": json_dict}

if not hasattr(StatisticEvent_base, "generateBaseDict"):
    StatisticEvent_base.generateBaseDict = generateEmptyDict
