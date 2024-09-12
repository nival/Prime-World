# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from RerollShopItem_base import *

class RerollShopItem(RefCounted, Identified, ChangeHandler, BaseObject, RerollShopItem_base):
    _changeFields = {
        "GroupId":1,
        "IsBought":1,
        "IsPremium":1,
        "NumBought":1,
        "PersistentId":1,
        "Price":1,
        "PriceResource":1,
        "RandomItemId":1,
        "TalentLevel":1,
        "TotalAmount":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["GroupId"] = 0
        _dict["IsBought"] = False
        _dict["IsPremium"] = False
        _dict["NumBought"] = 0
        _dict["PersistentId"] = 0
        _dict["Price"] = 0
        _dict["PriceResource"] = 0
        _dict["RandomItemId"] = 0
        _dict["TalentLevel"] = 0
        _dict["TotalAmount"] = 0
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
        json_dict = RerollShopItem_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["GroupId"]=_dict.get("GroupId")
        json_dict["IsBought"]=_dict.get("IsBought")
        json_dict["IsPremium"]=_dict.get("IsPremium")
        json_dict["NumBought"]=_dict.get("NumBought")
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["Price"]=_dict.get("Price")
        json_dict["PriceResource"]=_dict.get("PriceResource")
        json_dict["RandomItemId"]=_dict.get("RandomItemId")
        json_dict["TalentLevel"]=_dict.get("TalentLevel")
        json_dict["TotalAmount"]=_dict.get("TotalAmount")
        return {"RerollShopItem": json_dict}

if not hasattr(RerollShopItem_base, "generateBaseDict"):
    RerollShopItem_base.generateBaseDict = generateEmptyDict
