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
import RollEventItem

from RollEventRule_base import *

class RollEventRule(RefCounted, Identified, ChangeHandler, BaseObject, RollEventRule_base):
    _changeFields = {
        "Description":1,
        "RuleType":1,
        "Title":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Description"] = ""
        _dict["Price"] = ResourceTable.ResourceTable(modeldata, None, "")
        _dict["ReforgeSources"] = Set(modeldata)
        _dict["Rewards"] = Set(modeldata)
        _dict["RuleType"] = 0
        _dict["Title"] = ""
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.Price.setPath(self.path + u"/Price")
        if not getattr(self,"ReforgeSources",None ):
            self.__dict__["ReforgeSources"] = Set(self._modeldata)
        self.ReforgeSources.init(self._modeldata.RollEventItemKeeper, self.path + u"/ReforgeSources", self._modeldata)
        if not getattr(self,"Rewards",None ):
            self.__dict__["Rewards"] = Set(self._modeldata)
        self.Rewards.init(self._modeldata.RollEventItemKeeper, self.path + u"/Rewards", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.Price.setPath(self.path + u"/Price")
        if not getattr(self,"ReforgeSources",None ):
            self.__dict__["ReforgeSources"] = Set(self._modeldata)
        self.ReforgeSources.init(self._modeldata.RollEventItemKeeper, self.path + u"/ReforgeSources", self._modeldata)
        if not getattr(self,"Rewards",None ):
            self.__dict__["Rewards"] = Set(self._modeldata)
        self.Rewards.init(self._modeldata.RollEventItemKeeper, self.path + u"/Rewards", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Price.setPath( self.path + u"/Price" )
        self.ReforgeSources.init(self._modeldata.RollEventItemKeeper, self.path + u"/ReforgeSources", self._modeldata)
        self.Rewards.init(self._modeldata.RollEventItemKeeper, self.path + u"/Rewards", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Price.deleteByID(id)
            self.ReforgeSources.deleteByID(id)
            self.Rewards.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = RollEventRule_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Description"]=_dict.get("Description")
        json_dict["Price"] = _dict.get("Price").generateJsonDict()
        json_dict["ReforgeSources"]=_dict.get("ReforgeSources").getJsonDict()
        json_dict["Rewards"]=_dict.get("Rewards").getJsonDict()
        json_dict["RuleType"]=_dict.get("RuleType")
        json_dict["Title"]=_dict.get("Title")
        return {"RollEventRule": json_dict}

if not hasattr(RollEventRule_base, "generateBaseDict"):
    RollEventRule_base.generateBaseDict = generateEmptyDict
