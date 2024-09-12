# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import ResourceTable

from QuestEventStageStepVariant_base import *

class QuestEventStageStepVariant(RefCounted, Identified, ChangeHandler, BaseObject, QuestEventStageStepVariant_base):
    _changeFields = {
        "LoseMessage":1,
        "Message":1,
        "WinMessage":1,
        "WinRatioBase":1,
        "WinRatioGold":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["LoseMessage"] = ""
        _dict["Message"] = ""
        _dict["Price"] = ResourceTable.ResourceTable(modeldata, None, "")
        _dict["WinMessage"] = ""
        _dict["WinRatioBase"] = 0.0
        _dict["WinRatioGold"] = 0.0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.Price.setPath(self.path + u"/Price")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.Price.setPath(self.path + u"/Price")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Price.setPath( self.path + u"/Price" )

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Price.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = QuestEventStageStepVariant_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["LoseMessage"]=_dict.get("LoseMessage")
        json_dict["Message"]=_dict.get("Message")
        json_dict["Price"] = _dict.get("Price").generateJsonDict()
        json_dict["WinMessage"]=_dict.get("WinMessage")
        json_dict["WinRatioBase"]=_dict.get("WinRatioBase")
        json_dict["WinRatioGold"]=_dict.get("WinRatioGold")
        return {"QuestEventStageStepVariant": json_dict}

if not hasattr(QuestEventStageStepVariant_base, "generateBaseDict"):
    QuestEventStageStepVariant_base.generateBaseDict = generateEmptyDict
