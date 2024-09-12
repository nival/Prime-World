# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import BuyAeriaItem

from BuyAeriaGoldEventInfo_base import *

class BuyAeriaGoldEventInfo(RefCounted, Identified, ChangeHandler, BaseObject, BuyAeriaGoldEventInfo_base):
    _changeFields = {
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["AeriaItems"] = Collection(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"AeriaItems",None ):
            self.__dict__["AeriaItems"] = Collection(self._modeldata)
        self.AeriaItems.init(self._modeldata.BuyAeriaItemKeeper, self.path + u"/AeriaItems", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"AeriaItems",None ):
            self.__dict__["AeriaItems"] = Collection(self._modeldata)
        self.AeriaItems.init(self._modeldata.BuyAeriaItemKeeper, self.path + u"/AeriaItems", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.AeriaItems.init(self._modeldata.BuyAeriaItemKeeper, self.path + u"/AeriaItems", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.AeriaItems.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = BuyAeriaGoldEventInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["AeriaItems"]=_dict.get("AeriaItems").getJsonDict()
        return {"BuyAeriaGoldEventInfo": json_dict}

if not hasattr(BuyAeriaGoldEventInfo_base, "generateBaseDict"):
    BuyAeriaGoldEventInfo_base.generateBaseDict = generateEmptyDict
