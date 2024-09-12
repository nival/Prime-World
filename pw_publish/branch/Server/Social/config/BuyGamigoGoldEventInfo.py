# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import BuyGamigoItem

from BuyGamigoGoldEventInfo_base import *

class BuyGamigoGoldEventInfo(RefCounted, Identified, ChangeHandler, BaseObject, BuyGamigoGoldEventInfo_base):
    _changeFields = {
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["GamigoItems"] = Collection(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"GamigoItems",None ):
            self.__dict__["GamigoItems"] = Collection(self._modeldata)
        self.GamigoItems.init(self._modeldata.BuyGamigoItemKeeper, self.path + u"/GamigoItems", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"GamigoItems",None ):
            self.__dict__["GamigoItems"] = Collection(self._modeldata)
        self.GamigoItems.init(self._modeldata.BuyGamigoItemKeeper, self.path + u"/GamigoItems", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.GamigoItems.init(self._modeldata.BuyGamigoItemKeeper, self.path + u"/GamigoItems", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.GamigoItems.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = BuyGamigoGoldEventInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["GamigoItems"]=_dict.get("GamigoItems").getJsonDict()
        return {"BuyGamigoGoldEventInfo": json_dict}

if not hasattr(BuyGamigoGoldEventInfo_base, "generateBaseDict"):
    BuyGamigoGoldEventInfo_base.generateBaseDict = generateEmptyDict
