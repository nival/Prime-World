# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from BuyGoldHeroInfo_base import *

class BuyGoldHeroInfo(RefCounted, Identified, ChangeHandler, BaseObject, BuyGoldHeroInfo_base):
    _changeFields = {
        "DISCOUNT_COEFFICIENT":1,
        "MIN_LORD_LVL_REQUIRED":1,
        "REPLACE_GOLD_PRICES_FEMALE":1,
        "REPLACE_GOLD_PRICES_MALE":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["DISCOUNT_COEFFICIENT"] = 1000
        _dict["MIN_LORD_LVL_REQUIRED"] = 24
        _dict["REPLACE_GOLD_PRICES_FEMALE"] = SimpleDict(modeldata)
        _dict["REPLACE_GOLD_PRICES_MALE"] = SimpleDict(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"REPLACE_GOLD_PRICES_FEMALE",None ):
            self.__dict__["REPLACE_GOLD_PRICES_FEMALE"] = SimpleDict(self._modeldata)
        self.REPLACE_GOLD_PRICES_FEMALE.init(self.path + u"/REPLACE_GOLD_PRICES_FEMALE", self._modeldata)
        if not getattr(self,"REPLACE_GOLD_PRICES_MALE",None ):
            self.__dict__["REPLACE_GOLD_PRICES_MALE"] = SimpleDict(self._modeldata)
        self.REPLACE_GOLD_PRICES_MALE.init(self.path + u"/REPLACE_GOLD_PRICES_MALE", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"REPLACE_GOLD_PRICES_FEMALE",None ):
            self.__dict__["REPLACE_GOLD_PRICES_FEMALE"] = SimpleDict(self._modeldata)
        self.REPLACE_GOLD_PRICES_FEMALE.init(self.path + u"/REPLACE_GOLD_PRICES_FEMALE", self._modeldata)
        if not getattr(self,"REPLACE_GOLD_PRICES_MALE",None ):
            self.__dict__["REPLACE_GOLD_PRICES_MALE"] = SimpleDict(self._modeldata)
        self.REPLACE_GOLD_PRICES_MALE.init(self.path + u"/REPLACE_GOLD_PRICES_MALE", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.REPLACE_GOLD_PRICES_FEMALE.init(self.path + u"/REPLACE_GOLD_PRICES_FEMALE", self._modeldata)
        self.REPLACE_GOLD_PRICES_MALE.init(self.path + u"/REPLACE_GOLD_PRICES_MALE", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.REPLACE_GOLD_PRICES_FEMALE.deleteByID(id)
            self.REPLACE_GOLD_PRICES_MALE.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = BuyGoldHeroInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["DISCOUNT_COEFFICIENT"]=_dict.get("DISCOUNT_COEFFICIENT")
        json_dict["MIN_LORD_LVL_REQUIRED"]=_dict.get("MIN_LORD_LVL_REQUIRED")
        json_dict["REPLACE_GOLD_PRICES_FEMALE"]=_dict.get("REPLACE_GOLD_PRICES_FEMALE").getJsonDict()
        json_dict["REPLACE_GOLD_PRICES_MALE"]=_dict.get("REPLACE_GOLD_PRICES_MALE").getJsonDict()
        return {"BuyGoldHeroInfo": json_dict}

if not hasattr(BuyGoldHeroInfo_base, "generateBaseDict"):
    BuyGoldHeroInfo_base.generateBaseDict = generateEmptyDict
