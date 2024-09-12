# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from GuardInfo_base import *

class GuardInfo(RefCounted, Identified, ChangeHandler, BaseObject, GuardInfo_base):
    _changeFields = {
        "badBehaviourReason":1,
        "Dodges":1,
        "isBadBehaviour":1,
        "isLeaver":1,
        "LeavesPoint":1,
        "NumberOfWins":1,
        "OnlyGuard":1,
        "RetiredTime":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["badBehaviourReason"] = 0
        _dict["Dodges"] = 0
        _dict["isBadBehaviour"] = False
        _dict["isLeaver"] = False
        _dict["LeavesPoint"] = 0.0
        _dict["NumberOfWins"] = 0.0
        _dict["OnlyGuard"] = False
        _dict["RetiredTime"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass

    # вызывается после model.addNewName()
    def init_add(self):
        pass

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = GuardInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["badBehaviourReason"]=_dict.get("badBehaviourReason")
        json_dict["Dodges"]=_dict.get("Dodges")
        json_dict["isBadBehaviour"]=_dict.get("isBadBehaviour")
        json_dict["isLeaver"]=_dict.get("isLeaver")
        json_dict["LeavesPoint"]=_dict.get("LeavesPoint")
        json_dict["NumberOfWins"]=_dict.get("NumberOfWins")
        json_dict["OnlyGuard"]=_dict.get("OnlyGuard")
        json_dict["RetiredTime"]=_dict.get("RetiredTime")
        return {"GuardInfo": json_dict}

if not hasattr(GuardInfo_base, "generateBaseDict"):
    GuardInfo_base.generateBaseDict = generateEmptyDict
