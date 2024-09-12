# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import ResourceTable

from RollEventItem_base import *

class RollEventItem(RefCounted, Identified, ChangeHandler, BaseObject, RollEventItem_base):
    _changeFields = {
        "ItemType":1,
        "PersistentId":1,
        "Ratio":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["ItemType"] = 0
        _dict["PersistentId"] = ""
        _dict["Ratio"] = 0.0
        _dict["Resource"] = ResourceTable.ResourceTable(modeldata, None, "")
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.Resource.setPath(self.path + u"/Resource")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.Resource.setPath(self.path + u"/Resource")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Resource.setPath( self.path + u"/Resource" )

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Resource.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = RollEventItem_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["ItemType"]=_dict.get("ItemType")
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["Ratio"]=_dict.get("Ratio")
        json_dict["Resource"] = _dict.get("Resource").generateJsonDict()
        return {"RollEventItem": json_dict}

if not hasattr(RollEventItem_base, "generateBaseDict"):
    RollEventItem_base.generateBaseDict = generateEmptyDict
