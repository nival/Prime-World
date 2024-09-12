# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import DonateEventRange

from DonateEvent_base import *

class DonateEvent(RefCounted, Identified, ChangeHandler, BaseObject, DonateEvent_base):
    _changeFields = {
        "EndTimestamp":1,
        "PersistentId":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["EndTimestamp"] = 0
        _dict["PersistentId"] = 0
        _dict["Ranges"] = Set(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"Ranges",None ):
            self.__dict__["Ranges"] = Set(self._modeldata)
        self.Ranges.init(self._modeldata.DonateEventRangeKeeper, self.path + u"/Ranges", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"Ranges",None ):
            self.__dict__["Ranges"] = Set(self._modeldata)
        self.Ranges.init(self._modeldata.DonateEventRangeKeeper, self.path + u"/Ranges", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Ranges.init(self._modeldata.DonateEventRangeKeeper, self.path + u"/Ranges", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Ranges.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = DonateEvent_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["EndTimestamp"]=_dict.get("EndTimestamp")
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["Ranges"]=_dict.get("Ranges").getJsonDict()
        return {"DonateEvent": json_dict}

if not hasattr(DonateEvent_base, "generateBaseDict"):
    DonateEvent_base.generateBaseDict = generateEmptyDict
