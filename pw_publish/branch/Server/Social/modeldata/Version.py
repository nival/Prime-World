# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from Version_base import *

class Version(RefCounted, Identified, ChangeHandler, BaseObject, Version_base):
    _changeFields = {
        "events":1,
        "patch":1,
        "revision":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["events"] = SimpleList(modeldata)
        _dict["patch"] = 0
        _dict["revision"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"events",None ):
            self.__dict__["events"] = SimpleList(self._modeldata)
        self.events.init(self.path + u"/events", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"events",None ):
            self.__dict__["events"] = SimpleList(self._modeldata)
        self.events.init(self.path + u"/events", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.events.init(self.path + u"/events", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.events.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = Version_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["events"]=_dict.get("events").getJsonDict()
        json_dict["patch"]=_dict.get("patch")
        json_dict["revision"]=_dict.get("revision")
        return {"Version": json_dict}

if not hasattr(Version_base, "generateBaseDict"):
    Version_base.generateBaseDict = generateEmptyDict
