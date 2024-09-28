# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import AgregatorType

from KeeperType_base import *

class KeeperType(RefCounted, Identified, ChangeHandler, BaseObject, KeeperType_base):
    _changeFields = {
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
        _dict["boolVal"] = False
        _dict["enumVal"] = 0
        _dict["floatVal"] = 0.0
        _dict["intVal"] = 0
        _dict["keeperAgrVal"] = AgregatorType.AgregatorType(modeldata, None, "")
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.keeperAgrVal.setPath(self.path + u"/keeperAgrVal")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.keeperAgrVal.setPath(self.path + u"/keeperAgrVal")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.keeperAgrVal.setPath( self.path + u"/keeperAgrVal" )

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.keeperAgrVal.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = KeeperType_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["boolVal"]=_dict.get("boolVal")
        json_dict["enumVal"]=_dict.get("enumVal")
        json_dict["floatVal"]=_dict.get("floatVal")
        json_dict["intVal"]=_dict.get("intVal")
        json_dict["keeperAgrVal"] = _dict.get("keeperAgrVal").generateJsonDict()
        return {"KeeperType": json_dict}

if not hasattr(KeeperType_base, "generateBaseDict"):
    KeeperType_base.generateBaseDict = generateEmptyDict
