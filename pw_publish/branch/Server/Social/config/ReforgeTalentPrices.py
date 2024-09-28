# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from ReforgeTalentPrices_base import *

class ReforgeTalentPrices(RefCounted, Identified, ChangeHandler, BaseObject, ReforgeTalentPrices_base):
    _changeFields = {
        "Rarity":1,
        "RerollPrice":1,
        "TalentsToUpgrade":1,
        "UpgradePrice":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Rarity"] = 0
        _dict["RerollPrice"] = 0
        _dict["TalentsToUpgrade"] = 0
        _dict["UpgradePrice"] = 0
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
        json_dict = ReforgeTalentPrices_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Rarity"]=_dict.get("Rarity")
        json_dict["RerollPrice"]=_dict.get("RerollPrice")
        json_dict["TalentsToUpgrade"]=_dict.get("TalentsToUpgrade")
        json_dict["UpgradePrice"]=_dict.get("UpgradePrice")
        return {"ReforgeTalentPrices": json_dict}

if not hasattr(ReforgeTalentPrices_base, "generateBaseDict"):
    ReforgeTalentPrices_base.generateBaseDict = generateEmptyDict
