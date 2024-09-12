# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import SiegeGuildInfo

from Siege_base import *

class Siege(RefCounted, Identified, ChangeHandler, BaseObject, Siege_base):
    _changeFields = {
        "EndTime":1,
        "IsLocked":1,
        "Target":1,
        "Uid":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["EndTime"] = 0
        _dict["IsLocked"] = False
        _dict["Participants"] = Set(modeldata)
        _dict["Target"] = Ref(modeldata, modeldata.SiegeGuildInfoKeeper, path, "Target")
        _dict["Uid"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"Participants",None ):
            self.__dict__["Participants"] = Set(self._modeldata)
        self.Participants.init(self._modeldata.SiegeGuildInfoKeeper, self.path + u"/Participants", self._modeldata)
        ###self.Target.init(self._modeldata.SiegeGuildInfoKeeper, self.path, self._modeldata, "Target")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"Participants",None ):
            self.__dict__["Participants"] = Set(self._modeldata)
        self.Participants.init(self._modeldata.SiegeGuildInfoKeeper, self.path + u"/Participants", self._modeldata)
        ###self.Target.init(self._modeldata.SiegeGuildInfoKeeper, self.path, self._modeldata, "Target")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Participants.init(self._modeldata.SiegeGuildInfoKeeper, self.path + u"/Participants", self._modeldata)
        self.Target.init(self._modeldata.SiegeGuildInfoKeeper, self.path, self._modeldata, "Target")

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Participants.deleteByID(id)
            self.Target.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name == "Target":
            self.__dict__["Target"].set(val)
            return
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = Siege_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["EndTime"]=_dict.get("EndTime")
        json_dict["IsLocked"]=_dict.get("IsLocked")
        json_dict["Participants"]=_dict.get("Participants").getJsonDict()
        json_dict["Target"]=_dict.get("Target").getJsonDict()
        json_dict["Uid"]=_dict.get("Uid")
        return {"Siege": json_dict}

if not hasattr(Siege_base, "generateBaseDict"):
    Siege_base.generateBaseDict = generateEmptyDict
