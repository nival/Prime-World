# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import QuestEventStage

from QuestEvent_base import *

class QuestEvent(RefCounted, Identified, ChangeHandler, BaseObject, QuestEvent_base):
    _changeFields = {
        "CurrencyIds":1,
        "EndTimestamp":1,
        "Guid":1,
        "PersistentId":1,
        "Text":1,
        "Title":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["CurrencyIds"] = SimpleList(modeldata)
        _dict["EndTimestamp"] = 0
        _dict["Guid"] = 0
        _dict["PersistentId"] = 0
        _dict["Stages"] = Collection(modeldata)
        _dict["Text"] = ""
        _dict["Title"] = ""
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"CurrencyIds",None ):
            self.__dict__["CurrencyIds"] = SimpleList(self._modeldata)
        self.CurrencyIds.init(self.path + u"/CurrencyIds", self._modeldata)
        if not getattr(self,"Stages",None ):
            self.__dict__["Stages"] = Collection(self._modeldata)
        self.Stages.init(self._modeldata.QuestEventStageKeeper, self.path + u"/Stages", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"CurrencyIds",None ):
            self.__dict__["CurrencyIds"] = SimpleList(self._modeldata)
        self.CurrencyIds.init(self.path + u"/CurrencyIds", self._modeldata)
        if not getattr(self,"Stages",None ):
            self.__dict__["Stages"] = Collection(self._modeldata)
        self.Stages.init(self._modeldata.QuestEventStageKeeper, self.path + u"/Stages", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.CurrencyIds.init(self.path + u"/CurrencyIds", self._modeldata)
        self.Stages.init(self._modeldata.QuestEventStageKeeper, self.path + u"/Stages", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.CurrencyIds.deleteByID(id)
            self.Stages.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = QuestEvent_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["CurrencyIds"]=_dict.get("CurrencyIds").getJsonDict()
        json_dict["EndTimestamp"]=_dict.get("EndTimestamp")
        json_dict["Guid"]=_dict.get("Guid")
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["Stages"]=_dict.get("Stages").getJsonDict()
        json_dict["Text"]=_dict.get("Text")
        json_dict["Title"]=_dict.get("Title")
        return {"QuestEvent": json_dict}

if not hasattr(QuestEvent_base, "generateBaseDict"):
    QuestEvent_base.generateBaseDict = generateEmptyDict
