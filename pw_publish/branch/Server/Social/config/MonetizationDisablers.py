# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from MonetizationDisablers_base import *

class MonetizationDisablers(RefCounted, Identified, ChangeHandler, BaseObject, MonetizationDisablers_base):
    _changeFields = {
        "disabledBuildings":1,
        "DisableSkins":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["disabledBuildings"] = SimpleList(modeldata)
        _dict["DisableSkins"] = False
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"disabledBuildings",None ):
            self.__dict__["disabledBuildings"] = SimpleList(self._modeldata)
        self.disabledBuildings.init(self.path + u"/disabledBuildings", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"disabledBuildings",None ):
            self.__dict__["disabledBuildings"] = SimpleList(self._modeldata)
        self.disabledBuildings.init(self.path + u"/disabledBuildings", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.disabledBuildings.init(self.path + u"/disabledBuildings", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.disabledBuildings.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = MonetizationDisablers_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["disabledBuildings"]=_dict.get("disabledBuildings").getJsonDict()
        json_dict["DisableSkins"]=_dict.get("DisableSkins")
        return {"MonetizationDisablers": json_dict}

if not hasattr(MonetizationDisablers_base, "generateBaseDict"):
    MonetizationDisablers_base.generateBaseDict = generateEmptyDict
