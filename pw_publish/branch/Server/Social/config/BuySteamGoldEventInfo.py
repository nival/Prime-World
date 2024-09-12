# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import BuySteamItem

from BuySteamGoldEventInfo_base import *

class BuySteamGoldEventInfo(RefCounted, Identified, ChangeHandler, BaseObject, BuySteamGoldEventInfo_base):
    _changeFields = {
        "Category":1,
        "CurrencyIndex":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Category"] = ""
        _dict["CurrencyIndex"] = SimpleDict(modeldata)
        _dict["SteamItems"] = Collection(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"CurrencyIndex",None ):
            self.__dict__["CurrencyIndex"] = SimpleDict(self._modeldata)
        self.CurrencyIndex.init(self.path + u"/CurrencyIndex", self._modeldata)
        if not getattr(self,"SteamItems",None ):
            self.__dict__["SteamItems"] = Collection(self._modeldata)
        self.SteamItems.init(self._modeldata.BuySteamItemKeeper, self.path + u"/SteamItems", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"CurrencyIndex",None ):
            self.__dict__["CurrencyIndex"] = SimpleDict(self._modeldata)
        self.CurrencyIndex.init(self.path + u"/CurrencyIndex", self._modeldata)
        if not getattr(self,"SteamItems",None ):
            self.__dict__["SteamItems"] = Collection(self._modeldata)
        self.SteamItems.init(self._modeldata.BuySteamItemKeeper, self.path + u"/SteamItems", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.CurrencyIndex.init(self.path + u"/CurrencyIndex", self._modeldata)
        self.SteamItems.init(self._modeldata.BuySteamItemKeeper, self.path + u"/SteamItems", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.CurrencyIndex.deleteByID(id)
            self.SteamItems.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = BuySteamGoldEventInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Category"]=_dict.get("Category")
        json_dict["CurrencyIndex"]=_dict.get("CurrencyIndex").getJsonDict()
        json_dict["SteamItems"]=_dict.get("SteamItems").getJsonDict()
        return {"BuySteamGoldEventInfo": json_dict}

if not hasattr(BuySteamGoldEventInfo_base, "generateBaseDict"):
    BuySteamGoldEventInfo_base.generateBaseDict = generateEmptyDict
