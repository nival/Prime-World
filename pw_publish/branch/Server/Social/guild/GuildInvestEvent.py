# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from GuildInvestEvent_base import *

class GuildInvestEvent(RefCounted, Identified, ChangeHandler, BaseObject, GuildInvestEvent_base):
    _changeFields = {
        "amount":1,
        "auid":1,
        "timestamp":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["amount"] = 0
        _dict["auid"] = 0
        _dict["timestamp"] = 0
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
        json_dict = GuildInvestEvent_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["amount"]=_dict.get("amount")
        json_dict["auid"]=_dict.get("auid")
        json_dict["timestamp"]=_dict.get("timestamp")
        return {"GuildInvestEvent": json_dict}

if not hasattr(GuildInvestEvent_base, "generateBaseDict"):
    GuildInvestEvent_base.generateBaseDict = generateEmptyDict
