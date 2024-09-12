# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from TalentEvent_base import *

class TalentEvent(RefCounted, Identified, ChangeHandler, BaseObject, TalentEvent_base):
    _changeFields = {
        "Auid1":1,
        "Auid2":1,
        "PersistentId":1,
        "timestamp":1,
        "Type":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Auid1"] = 0
        _dict["Auid2"] = 0
        _dict["PersistentId"] = 0
        _dict["timestamp"] = 0
        _dict["Type"] = 0
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
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = TalentEvent_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Auid1"]=_dict.get("Auid1")
        json_dict["Auid2"]=_dict.get("Auid2")
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["timestamp"]=_dict.get("timestamp")
        json_dict["Type"]=_dict.get("Type")
        return {"TalentEvent": json_dict}

if not hasattr(TalentEvent_base, "generateBaseDict"):
    TalentEvent_base.generateBaseDict = generateEmptyDict
