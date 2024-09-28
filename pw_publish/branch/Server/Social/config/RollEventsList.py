# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import RollEvent

from RollEventsList_base import *

class RollEventsList(RefCounted, Identified, ChangeHandler, BaseObject, RollEventsList_base):
    _changeFields = {
        "Events":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Events"] = SimpleDict(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"Events",None ):
            self.__dict__["Events"] = SimpleDict(self._modeldata)
        self.Events.init(self.path + u"/Events", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"Events",None ):
            self.__dict__["Events"] = SimpleDict(self._modeldata)
        self.Events.init(self.path + u"/Events", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Events.init(self.path + u"/Events", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Events.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = RollEventsList_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Events"]=_dict.get("Events").getJsonDict()
        return {"RollEventsList": json_dict}

if not hasattr(RollEventsList_base, "generateBaseDict"):
    RollEventsList_base.generateBaseDict = generateEmptyDict
