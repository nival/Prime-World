# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import RollEventItem

from TradeGroupMember_base import *

class TradeGroupMember(RefCounted, Identified, ChangeHandler, BaseObject, TradeGroupMember_base):
    _changeFields = {
        "CurrencyCostPerExp":1,
        "CurrencyName":1,
        "Image":1,
        "RewardACost":1,
        "RewardBCost":1,
        "Title":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["CurrencyCostPerExp"] = 0.0
        _dict["CurrencyName"] = ""
        _dict["Image"] = ""
        _dict["RewardA"] = Collection(modeldata)
        _dict["RewardACost"] = 0
        _dict["RewardB"] = Collection(modeldata)
        _dict["RewardBCost"] = 0
        _dict["Title"] = ""
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"RewardA",None ):
            self.__dict__["RewardA"] = Collection(self._modeldata)
        self.RewardA.init(self._modeldata.RollEventItemKeeper, self.path + u"/RewardA", self._modeldata)
        if not getattr(self,"RewardB",None ):
            self.__dict__["RewardB"] = Collection(self._modeldata)
        self.RewardB.init(self._modeldata.RollEventItemKeeper, self.path + u"/RewardB", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"RewardA",None ):
            self.__dict__["RewardA"] = Collection(self._modeldata)
        self.RewardA.init(self._modeldata.RollEventItemKeeper, self.path + u"/RewardA", self._modeldata)
        if not getattr(self,"RewardB",None ):
            self.__dict__["RewardB"] = Collection(self._modeldata)
        self.RewardB.init(self._modeldata.RollEventItemKeeper, self.path + u"/RewardB", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.RewardA.init(self._modeldata.RollEventItemKeeper, self.path + u"/RewardA", self._modeldata)
        self.RewardB.init(self._modeldata.RollEventItemKeeper, self.path + u"/RewardB", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.RewardA.deleteByID(id)
            self.RewardB.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = TradeGroupMember_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["CurrencyCostPerExp"]=_dict.get("CurrencyCostPerExp")
        json_dict["CurrencyName"]=_dict.get("CurrencyName")
        json_dict["Image"]=_dict.get("Image")
        json_dict["RewardA"]=_dict.get("RewardA").getJsonDict()
        json_dict["RewardACost"]=_dict.get("RewardACost")
        json_dict["RewardB"]=_dict.get("RewardB").getJsonDict()
        json_dict["RewardBCost"]=_dict.get("RewardBCost")
        json_dict["Title"]=_dict.get("Title")
        return {"TradeGroupMember": json_dict}

if not hasattr(TradeGroupMember_base, "generateBaseDict"):
    TradeGroupMember_base.generateBaseDict = generateEmptyDict
