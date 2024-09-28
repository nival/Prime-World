# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import Objective

from Quest_base import *

class Quest(RefCounted, Identified, ChangeHandler, BaseObject, Quest_base):
    _changeFields = {
        "applyConditionalAction":1,
        "dialogPage":1,
        "IsAutoCompleted":1,
        "isVisible":1,
        "persistentId":1,
        "state":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["applyConditionalAction"] = True
        _dict["dialogPage"] = 0
        _dict["IsAutoCompleted"] = False
        _dict["isVisible"] = True
        _dict["objectives"] = Set(modeldata)
        _dict["persistentId"] = 0
        _dict["state"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"objectives",None ):
            self.__dict__["objectives"] = Set(self._modeldata)
        self.objectives.init(self._modeldata.ObjectivesKeeper, self.path + u"/objectives", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"objectives",None ):
            self.__dict__["objectives"] = Set(self._modeldata)
        self.objectives.init(self._modeldata.ObjectivesKeeper, self.path + u"/objectives", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.objectives.init(self._modeldata.ObjectivesKeeper, self.path + u"/objectives", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.objectives.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = Quest_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["applyConditionalAction"]=_dict.get("applyConditionalAction")
        json_dict["dialogPage"]=_dict.get("dialogPage")
        json_dict["IsAutoCompleted"]=_dict.get("IsAutoCompleted")
        json_dict["isVisible"]=_dict.get("isVisible")
        json_dict["objectives"]=_dict.get("objectives").getJsonDict()
        json_dict["persistentId"]=_dict.get("persistentId")
        json_dict["state"]=_dict.get("state")
        return {"Quest": json_dict}

if not hasattr(Quest_base, "generateBaseDict"):
    Quest_base.generateBaseDict = generateEmptyDict
