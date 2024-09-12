# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from InstantCondition_base import *

class InstantCondition(RefCounted, Identified, ChangeHandler, BaseObject, InstantCondition_base):
    _changeFields = {
        "CustomCurrencyId":1,
        "ResourceType":1,
        "TalentsToPayValue":1,
        "TotalValue":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["CustomCurrencyId"] = ""
        _dict["ResourceType"] = 0
        _dict["TalentsToPayValue"] = ""
        _dict["TotalValue"] = 0
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
        json_dict = InstantCondition_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["CustomCurrencyId"]=_dict.get("CustomCurrencyId")
        json_dict["ResourceType"]=_dict.get("ResourceType")
        json_dict["TalentsToPayValue"]=_dict.get("TalentsToPayValue")
        json_dict["TotalValue"]=_dict.get("TotalValue")
        return {"InstantCondition": json_dict}

if not hasattr(InstantCondition_base, "generateBaseDict"):
    InstantCondition_base.generateBaseDict = generateEmptyDict
