# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from PingInfo_base import *

class PingInfo(RefCounted, Identified, ChangeHandler, BaseObject, PingInfo_base):
    _changeFields = {
        "addresses":1,
        "Frequency":1,
        "MaxTimeOut":1,
        "TryCount":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["addresses"] = SimpleDict(modeldata)
        _dict["Frequency"] = 900
        _dict["MaxTimeOut"] = 9000
        _dict["TryCount"] = 5
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"addresses",None ):
            self.__dict__["addresses"] = SimpleDict(self._modeldata)
        self.addresses.init(self.path + u"/addresses", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"addresses",None ):
            self.__dict__["addresses"] = SimpleDict(self._modeldata)
        self.addresses.init(self.path + u"/addresses", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.addresses.init(self.path + u"/addresses", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.addresses.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = PingInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["addresses"]=_dict.get("addresses").getJsonDict()
        json_dict["Frequency"]=_dict.get("Frequency")
        json_dict["MaxTimeOut"]=_dict.get("MaxTimeOut")
        json_dict["TryCount"]=_dict.get("TryCount")
        return {"PingInfo": json_dict}

if not hasattr(PingInfo_base, "generateBaseDict"):
    PingInfo_base.generateBaseDict = generateEmptyDict
