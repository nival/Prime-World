# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import RollEventRule

from RollEvent_base import *

class RollEvent(RefCounted, Identified, ChangeHandler, BaseObject, RollEvent_base):
    _changeFields = {
        "CompletionTalentPersistentId":1,
        "CurrencyIds":1,
        "EndTimestamp":1,
        "Guid":1,
        "Image":1,
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
        _dict["CompletionTalentPersistentId"] = ""
        _dict["CurrencyIds"] = SimpleList(modeldata)
        _dict["EndTimestamp"] = 0
        _dict["Guid"] = 0
        _dict["Image"] = ""
        _dict["PersistentId"] = 0
        _dict["Rolls"] = Set(modeldata)
        _dict["Text"] = ""
        _dict["Title"] = ""
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"CurrencyIds",None ):
            self.__dict__["CurrencyIds"] = SimpleList(self._modeldata)
        self.CurrencyIds.init(self.path + u"/CurrencyIds", self._modeldata)
        if not getattr(self,"Rolls",None ):
            self.__dict__["Rolls"] = Set(self._modeldata)
        self.Rolls.init(self._modeldata.RollEventRuleKeeper, self.path + u"/Rolls", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"CurrencyIds",None ):
            self.__dict__["CurrencyIds"] = SimpleList(self._modeldata)
        self.CurrencyIds.init(self.path + u"/CurrencyIds", self._modeldata)
        if not getattr(self,"Rolls",None ):
            self.__dict__["Rolls"] = Set(self._modeldata)
        self.Rolls.init(self._modeldata.RollEventRuleKeeper, self.path + u"/Rolls", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.CurrencyIds.init(self.path + u"/CurrencyIds", self._modeldata)
        self.Rolls.init(self._modeldata.RollEventRuleKeeper, self.path + u"/Rolls", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.CurrencyIds.deleteByID(id)
            self.Rolls.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = RollEvent_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["CompletionTalentPersistentId"]=_dict.get("CompletionTalentPersistentId")
        json_dict["CurrencyIds"]=_dict.get("CurrencyIds").getJsonDict()
        json_dict["EndTimestamp"]=_dict.get("EndTimestamp")
        json_dict["Guid"]=_dict.get("Guid")
        json_dict["Image"]=_dict.get("Image")
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["Rolls"]=_dict.get("Rolls").getJsonDict()
        json_dict["Text"]=_dict.get("Text")
        json_dict["Title"]=_dict.get("Title")
        return {"RollEvent": json_dict}

if not hasattr(RollEvent_base, "generateBaseDict"):
    RollEvent_base.generateBaseDict = generateEmptyDict
