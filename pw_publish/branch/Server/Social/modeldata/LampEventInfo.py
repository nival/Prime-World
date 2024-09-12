# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from LampEventInfo_base import *

class LampEventInfo(RefCounted, Identified, ChangeHandler, BaseObject, LampEventInfo_base):
    _changeFields = {
        "AllowedLamps":1,
        "AllowedLampsGoldStatus":1,
        "BonusLeft":1,
        "dbId":1,
        "EndTime":1,
        "LastTechLamp":1,
        "StartTime":1,
        "TotalBonusUsed":1,
        "TotalTransactionsUsed":1,
        "TransactionsLeft":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["AllowedLamps"] = 0
        _dict["AllowedLampsGoldStatus"] = 0
        _dict["BonusLeft"] = 0
        _dict["dbId"] = ""
        _dict["EndTime"] = 0
        _dict["LastTechLamp"] = 0
        _dict["StartTime"] = 0
        _dict["TotalBonusUsed"] = 0
        _dict["TotalTransactionsUsed"] = 0
        _dict["TransactionsLeft"] = 0
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
        json_dict = LampEventInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["AllowedLamps"]=_dict.get("AllowedLamps")
        json_dict["AllowedLampsGoldStatus"]=_dict.get("AllowedLampsGoldStatus")
        json_dict["BonusLeft"]=_dict.get("BonusLeft")
        json_dict["dbId"]=_dict.get("dbId")
        json_dict["EndTime"]=_dict.get("EndTime")
        json_dict["LastTechLamp"]=_dict.get("LastTechLamp")
        json_dict["StartTime"]=_dict.get("StartTime")
        json_dict["TotalBonusUsed"]=_dict.get("TotalBonusUsed")
        json_dict["TotalTransactionsUsed"]=_dict.get("TotalTransactionsUsed")
        json_dict["TransactionsLeft"]=_dict.get("TransactionsLeft")
        return {"LampEventInfo": json_dict}

if not hasattr(LampEventInfo_base, "generateBaseDict"):
    LampEventInfo_base.generateBaseDict = generateEmptyDict
