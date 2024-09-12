# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from TradeEventProgression_base import *

class TradeEventProgression(RefCounted, Identified, ChangeHandler, BaseObject, TradeEventProgression_base):
    _changeFields = {
        "CollectedLootboxes":1,
        "Completed":1,
        "PersistentId":1,
        "PlayerPlace":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["CollectedLootboxes"] = SimpleList(modeldata)
        _dict["Completed"] = False
        _dict["PersistentId"] = 0
        _dict["PlayerPlace"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"CollectedLootboxes",None ):
            self.__dict__["CollectedLootboxes"] = SimpleList(self._modeldata)
        self.CollectedLootboxes.init(self.path + u"/CollectedLootboxes", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"CollectedLootboxes",None ):
            self.__dict__["CollectedLootboxes"] = SimpleList(self._modeldata)
        self.CollectedLootboxes.init(self.path + u"/CollectedLootboxes", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.CollectedLootboxes.init(self.path + u"/CollectedLootboxes", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.CollectedLootboxes.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = TradeEventProgression_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["CollectedLootboxes"]=_dict.get("CollectedLootboxes").getJsonDict()
        json_dict["Completed"]=_dict.get("Completed")
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["PlayerPlace"]=_dict.get("PlayerPlace")
        return {"TradeEventProgression": json_dict}

if not hasattr(TradeEventProgression_base, "generateBaseDict"):
    TradeEventProgression_base.generateBaseDict = generateEmptyDict
