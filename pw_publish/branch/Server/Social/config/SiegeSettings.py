# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from SiegeSettings_base import *

class SiegeSettings(RefCounted, Identified, ChangeHandler, BaseObject, SiegeSettings_base):
    _changeFields = {
        "MAX_ACTIVE_SIEGES":1,
        "MINIMAL_SIEGE_PARTICIPATION_PRICE":1,
        "SIEGE_DISCOUNT":1,
        "SIEGE_DURATION":1,
        "SIEGE_LOCK":1,
        "SIEGES_START_ADD_COEFF":1,
        "SIEGES_START_MULT_COEFF":1,
        "TIMEOUT_FOR_CAPTURE_AFTER_LOSS":1,
        "TIMEOUT_FOR_EX_VASSAL_CAPTURE":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["MAX_ACTIVE_SIEGES"] = 1
        _dict["MINIMAL_SIEGE_PARTICIPATION_PRICE"] = 120.0
        _dict["SIEGE_DISCOUNT"] = 0.2
        _dict["SIEGE_DURATION"] = 86400
        _dict["SIEGE_LOCK"] = 14400
        _dict["SIEGES_START_ADD_COEFF"] = 100.0
        _dict["SIEGES_START_MULT_COEFF"] = 0.4
        _dict["TIMEOUT_FOR_CAPTURE_AFTER_LOSS"] = 259200
        _dict["TIMEOUT_FOR_EX_VASSAL_CAPTURE"] = 259200
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
        json_dict = SiegeSettings_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["MAX_ACTIVE_SIEGES"]=_dict.get("MAX_ACTIVE_SIEGES")
        json_dict["MINIMAL_SIEGE_PARTICIPATION_PRICE"]=_dict.get("MINIMAL_SIEGE_PARTICIPATION_PRICE")
        json_dict["SIEGE_DISCOUNT"]=_dict.get("SIEGE_DISCOUNT")
        json_dict["SIEGE_DURATION"]=_dict.get("SIEGE_DURATION")
        json_dict["SIEGE_LOCK"]=_dict.get("SIEGE_LOCK")
        json_dict["SIEGES_START_ADD_COEFF"]=_dict.get("SIEGES_START_ADD_COEFF")
        json_dict["SIEGES_START_MULT_COEFF"]=_dict.get("SIEGES_START_MULT_COEFF")
        json_dict["TIMEOUT_FOR_CAPTURE_AFTER_LOSS"]=_dict.get("TIMEOUT_FOR_CAPTURE_AFTER_LOSS")
        json_dict["TIMEOUT_FOR_EX_VASSAL_CAPTURE"]=_dict.get("TIMEOUT_FOR_EX_VASSAL_CAPTURE")
        return {"SiegeSettings": json_dict}

if not hasattr(SiegeSettings_base, "generateBaseDict"):
    SiegeSettings_base.generateBaseDict = generateEmptyDict
