# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from RerollShopGroupUpgradeLevels_base import *

class RerollShopGroupUpgradeLevels(RefCounted, Identified, ChangeHandler, BaseObject, RerollShopGroupUpgradeLevels_base):
    _changeFields = {
        "MaxUpgradeLevel":1,
        "MinUpgradeLevel":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["MaxUpgradeLevel"] = 0
        _dict["MinUpgradeLevel"] = 0
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
        json_dict = RerollShopGroupUpgradeLevels_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["MaxUpgradeLevel"]=_dict.get("MaxUpgradeLevel")
        json_dict["MinUpgradeLevel"]=_dict.get("MinUpgradeLevel")
        return {"RerollShopGroupUpgradeLevels": json_dict}

if not hasattr(RerollShopGroupUpgradeLevels_base, "generateBaseDict"):
    RerollShopGroupUpgradeLevels_base.generateBaseDict = generateEmptyDict
