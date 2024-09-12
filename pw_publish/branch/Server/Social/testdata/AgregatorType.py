# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import KeeperType

from AgregatorType_base import *

class AgregatorType(RefCounted, Identified, ChangeHandler, BaseObject, AgregatorType_base):
    _changeFields = {
        "agrRefVal":1,
        "boolVal":1,
        "enumVal":1,
        "floatVal":1,
        "intVal":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["agrRefVal"] = Ref(modeldata, modeldata.KeeperVal, path, "agrRefVal")
        _dict["boolVal"] = False
        _dict["collectionVal"] = Collection(modeldata)
        _dict["enumVal"] = 0
        _dict["floatVal"] = 0.0
        _dict["intVal"] = 0
        _dict["setVal"] = Set(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        ###self.agrRefVal.init(self._modeldata.KeeperVal, self.path, self._modeldata, "agrRefVal")
        if not getattr(self,"collectionVal",None ):
            self.__dict__["collectionVal"] = Collection(self._modeldata)
        self.collectionVal.init(self._modeldata.KeeperVal, self.path + u"/collectionVal", self._modeldata)
        if not getattr(self,"setVal",None ):
            self.__dict__["setVal"] = Set(self._modeldata)
        self.setVal.init(self._modeldata.KeeperVal, self.path + u"/setVal", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        ###self.agrRefVal.init(self._modeldata.KeeperVal, self.path, self._modeldata, "agrRefVal")
        if not getattr(self,"collectionVal",None ):
            self.__dict__["collectionVal"] = Collection(self._modeldata)
        self.collectionVal.init(self._modeldata.KeeperVal, self.path + u"/collectionVal", self._modeldata)
        if not getattr(self,"setVal",None ):
            self.__dict__["setVal"] = Set(self._modeldata)
        self.setVal.init(self._modeldata.KeeperVal, self.path + u"/setVal", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.agrRefVal.init(self._modeldata.KeeperVal, self.path, self._modeldata, "agrRefVal")
        self.collectionVal.init(self._modeldata.KeeperVal, self.path + u"/collectionVal", self._modeldata)
        self.setVal.init(self._modeldata.KeeperVal, self.path + u"/setVal", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.agrRefVal.deleteByID(id)
            self.collectionVal.deleteByID(id)
            self.setVal.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name == "agrRefVal":
            self.__dict__["agrRefVal"].set(val)
            return
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = AgregatorType_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["agrRefVal"]=_dict.get("agrRefVal").getJsonDict()
        json_dict["boolVal"]=_dict.get("boolVal")
        json_dict["collectionVal"]=_dict.get("collectionVal").getJsonDict()
        json_dict["enumVal"]=_dict.get("enumVal")
        json_dict["floatVal"]=_dict.get("floatVal")
        json_dict["intVal"]=_dict.get("intVal")
        json_dict["setVal"]=_dict.get("setVal").getJsonDict()
        return {"AgregatorType": json_dict}

if not hasattr(AgregatorType_base, "generateBaseDict"):
    AgregatorType_base.generateBaseDict = generateEmptyDict
