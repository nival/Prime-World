# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from ComplaintsSettings_base import *

class ComplaintsSettings(RefCounted, Identified, ChangeHandler, BaseObject, ComplaintsSettings_base):
    _changeFields = {
        "CHAT_MSG_HISTORY_SIZE":1,
        "CHAT_MSG_HISTORY_TIME":1,
        "COMPLAINTS_TYPES":1,
        "MAX_COMPLAINTS_PER_DAY":1,
        "MAX_COMPLAITS_PER_SESSION":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["CHAT_MSG_HISTORY_SIZE"] = 200
        _dict["CHAT_MSG_HISTORY_TIME"] = 600
        _dict["COMPLAINTS_TYPES"] = SimpleDict(modeldata)
        _dict["MAX_COMPLAINTS_PER_DAY"] = 3
        _dict["MAX_COMPLAITS_PER_SESSION"] = 2
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"COMPLAINTS_TYPES",None ):
            self.__dict__["COMPLAINTS_TYPES"] = SimpleDict(self._modeldata)
        self.COMPLAINTS_TYPES.init(self.path + u"/COMPLAINTS_TYPES", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"COMPLAINTS_TYPES",None ):
            self.__dict__["COMPLAINTS_TYPES"] = SimpleDict(self._modeldata)
        self.COMPLAINTS_TYPES.init(self.path + u"/COMPLAINTS_TYPES", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.COMPLAINTS_TYPES.init(self.path + u"/COMPLAINTS_TYPES", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.COMPLAINTS_TYPES.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = ComplaintsSettings_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["CHAT_MSG_HISTORY_SIZE"]=_dict.get("CHAT_MSG_HISTORY_SIZE")
        json_dict["CHAT_MSG_HISTORY_TIME"]=_dict.get("CHAT_MSG_HISTORY_TIME")
        json_dict["COMPLAINTS_TYPES"]=_dict.get("COMPLAINTS_TYPES").getJsonDict()
        json_dict["MAX_COMPLAINTS_PER_DAY"]=_dict.get("MAX_COMPLAINTS_PER_DAY")
        json_dict["MAX_COMPLAITS_PER_SESSION"]=_dict.get("MAX_COMPLAITS_PER_SESSION")
        return {"ComplaintsSettings": json_dict}

if not hasattr(ComplaintsSettings_base, "generateBaseDict"):
    ComplaintsSettings_base.generateBaseDict = generateEmptyDict
