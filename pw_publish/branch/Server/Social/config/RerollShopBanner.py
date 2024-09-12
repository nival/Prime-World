# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from RerollShopBanner_base import *

class RerollShopBanner(RefCounted, Identified, ChangeHandler, BaseObject, RerollShopBanner_base):
    _changeFields = {
        "ACTION_END_TIME":1,
        "BANNER_URL":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["ACTION_END_TIME"] = 0
        _dict["BANNER_URL"] = ""
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
        json_dict = RerollShopBanner_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["ACTION_END_TIME"]=_dict.get("ACTION_END_TIME")
        json_dict["BANNER_URL"]=_dict.get("BANNER_URL")
        return {"RerollShopBanner": json_dict}

if not hasattr(RerollShopBanner_base, "generateBaseDict"):
    RerollShopBanner_base.generateBaseDict = generateEmptyDict
