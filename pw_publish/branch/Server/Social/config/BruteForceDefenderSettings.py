# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from BruteForceDefenderSettings_base import *

class BruteForceDefenderSettings(RefCounted, Identified, ChangeHandler, BaseObject, BruteForceDefenderSettings_base):
    _changeFields = {
        "ENABLE":1,
        "ENABLE_IP_CHECK":1,
        "ENABLE_SENDING_MAIL":1,
        "FAILED_COUNT_FOR_CAPTCHA":1,
        "LOGIN_BAN_TIME":1,
        "TIME_IP_BAN":1,
        "TRY_IP_COUNT":1,
        "TRY_LOGINS_COUNT":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["ENABLE"] = True
        _dict["ENABLE_IP_CHECK"] = True
        _dict["ENABLE_SENDING_MAIL"] = True
        _dict["FAILED_COUNT_FOR_CAPTCHA"] = 5
        _dict["LOGIN_BAN_TIME"] = 3
        _dict["TIME_IP_BAN"] = 30
        _dict["TRY_IP_COUNT"] = 10
        _dict["TRY_LOGINS_COUNT"] = 10
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
        json_dict = BruteForceDefenderSettings_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["ENABLE"]=_dict.get("ENABLE")
        json_dict["ENABLE_IP_CHECK"]=_dict.get("ENABLE_IP_CHECK")
        json_dict["ENABLE_SENDING_MAIL"]=_dict.get("ENABLE_SENDING_MAIL")
        json_dict["FAILED_COUNT_FOR_CAPTCHA"]=_dict.get("FAILED_COUNT_FOR_CAPTCHA")
        json_dict["LOGIN_BAN_TIME"]=_dict.get("LOGIN_BAN_TIME")
        json_dict["TIME_IP_BAN"]=_dict.get("TIME_IP_BAN")
        json_dict["TRY_IP_COUNT"]=_dict.get("TRY_IP_COUNT")
        json_dict["TRY_LOGINS_COUNT"]=_dict.get("TRY_LOGINS_COUNT")
        return {"BruteForceDefenderSettings": json_dict}

if not hasattr(BruteForceDefenderSettings_base, "generateBaseDict"):
    BruteForceDefenderSettings_base.generateBaseDict = generateEmptyDict
