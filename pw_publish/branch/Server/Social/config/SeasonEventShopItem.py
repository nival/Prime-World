# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from SeasonEventShopItem_base import *

class SeasonEventShopItem(RefCounted, Identified, ChangeHandler, BaseObject, SeasonEventShopItem_base):
    _changeFields = {
        "Cost":1,
        "Image":1,
        "Limit":1,
        "LootboxPersistentId":1,
        "Title":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Cost"] = 0
        _dict["Image"] = ""
        _dict["Limit"] = 0
        _dict["LootboxPersistentId"] = ""
        _dict["Title"] = ""
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
        json_dict = SeasonEventShopItem_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Cost"]=_dict.get("Cost")
        json_dict["Image"]=_dict.get("Image")
        json_dict["Limit"]=_dict.get("Limit")
        json_dict["LootboxPersistentId"]=_dict.get("LootboxPersistentId")
        json_dict["Title"]=_dict.get("Title")
        return {"SeasonEventShopItem": json_dict}

if not hasattr(SeasonEventShopItem_base, "generateBaseDict"):
    SeasonEventShopItem_base.generateBaseDict = generateEmptyDict
