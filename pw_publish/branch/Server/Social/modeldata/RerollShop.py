# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import RerollShopItem

from RerollShop_base import *

class RerollShop(RefCounted, Identified, ChangeHandler, BaseObject, RerollShop_base):
    _changeFields = {
        "NewlyRerolled":1,
        "NextRerollTime":1,
        "RerollsToday":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["NewlyRerolled"] = False
        _dict["NextRerollTime"] = 0
        _dict["RerollsToday"] = 0
        _dict["ShopItems"] = Set(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"ShopItems",None ):
            self.__dict__["ShopItems"] = Set(self._modeldata)
        self.ShopItems.init(self._modeldata.RerollShopItemsKeeper, self.path + u"/ShopItems", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"ShopItems",None ):
            self.__dict__["ShopItems"] = Set(self._modeldata)
        self.ShopItems.init(self._modeldata.RerollShopItemsKeeper, self.path + u"/ShopItems", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.ShopItems.init(self._modeldata.RerollShopItemsKeeper, self.path + u"/ShopItems", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.ShopItems.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = RerollShop_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["NewlyRerolled"]=_dict.get("NewlyRerolled")
        json_dict["NextRerollTime"]=_dict.get("NextRerollTime")
        json_dict["RerollsToday"]=_dict.get("RerollsToday")
        json_dict["ShopItems"]=_dict.get("ShopItems").getJsonDict()
        return {"RerollShop": json_dict}

if not hasattr(RerollShop_base, "generateBaseDict"):
    RerollShop_base.generateBaseDict = generateEmptyDict
