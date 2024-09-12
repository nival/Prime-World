# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from BuyArcGamesItem_base import *

class BuyArcGamesItem(RefCounted, Identified, ChangeHandler, BaseObject, BuyArcGamesItem_base):
    _changeFields = {
        "BonusGold":1,
        "Description":1,
        "Gold":1,
        "Image":1,
        "Price":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["BonusGold"] = 0
        _dict["Description"] = ""
        _dict["Gold"] = 0
        _dict["Image"] = ""
        _dict["Price"] = 0
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
        json_dict = BuyArcGamesItem_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["BonusGold"]=_dict.get("BonusGold")
        json_dict["Description"]=_dict.get("Description")
        json_dict["Gold"]=_dict.get("Gold")
        json_dict["Image"]=_dict.get("Image")
        json_dict["Price"]=_dict.get("Price")
        return {"BuyArcGamesItem": json_dict}

if not hasattr(BuyArcGamesItem_base, "generateBaseDict"):
    BuyArcGamesItem_base.generateBaseDict = generateEmptyDict
