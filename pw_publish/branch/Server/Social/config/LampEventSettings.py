# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import ActiveGroup

from LampEventSettings_base import *

class LampEventSettings(RefCounted, Identified, ChangeHandler, BaseObject, LampEventSettings_base):
    _changeFields = {
        "BlockLampPeriod":1,
        "BlockLampPeriodFromLastPayment":1,
        "BonusGold":1,
        "Duration":1,
        "FwodLampRollProbability":1,
        "FWODLimit":1,
        "GuarantyLampPeriod":1,
        "LampRollProbability":1,
        "MaxPaymentDaysForGoldStatus":1,
        "Transactions":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["ActiveGroups"] = Set(modeldata)
        _dict["BlockLampPeriod"] = SimpleDict(modeldata)
        _dict["BlockLampPeriodFromLastPayment"] = SimpleDict(modeldata)
        _dict["BonusGold"] = 2000
        _dict["Duration"] = 86400
        _dict["FwodLampRollProbability"] = 100.0
        _dict["FWODLimit"] = 2
        _dict["GuarantyLampPeriod"] = SimpleDict(modeldata)
        _dict["LampRollProbability"] = 100.0
        _dict["MaxPaymentDaysForGoldStatus"] = 30
        _dict["Transactions"] = 1
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"ActiveGroups",None ):
            self.__dict__["ActiveGroups"] = Set(self._modeldata)
        self.ActiveGroups.init(self._modeldata.ActiveGroups, self.path + u"/ActiveGroups", self._modeldata)
        if not getattr(self,"BlockLampPeriod",None ):
            self.__dict__["BlockLampPeriod"] = SimpleDict(self._modeldata)
        self.BlockLampPeriod.init(self.path + u"/BlockLampPeriod", self._modeldata)
        if not getattr(self,"BlockLampPeriodFromLastPayment",None ):
            self.__dict__["BlockLampPeriodFromLastPayment"] = SimpleDict(self._modeldata)
        self.BlockLampPeriodFromLastPayment.init(self.path + u"/BlockLampPeriodFromLastPayment", self._modeldata)
        if not getattr(self,"GuarantyLampPeriod",None ):
            self.__dict__["GuarantyLampPeriod"] = SimpleDict(self._modeldata)
        self.GuarantyLampPeriod.init(self.path + u"/GuarantyLampPeriod", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"ActiveGroups",None ):
            self.__dict__["ActiveGroups"] = Set(self._modeldata)
        self.ActiveGroups.init(self._modeldata.ActiveGroups, self.path + u"/ActiveGroups", self._modeldata)
        if not getattr(self,"BlockLampPeriod",None ):
            self.__dict__["BlockLampPeriod"] = SimpleDict(self._modeldata)
        self.BlockLampPeriod.init(self.path + u"/BlockLampPeriod", self._modeldata)
        if not getattr(self,"BlockLampPeriodFromLastPayment",None ):
            self.__dict__["BlockLampPeriodFromLastPayment"] = SimpleDict(self._modeldata)
        self.BlockLampPeriodFromLastPayment.init(self.path + u"/BlockLampPeriodFromLastPayment", self._modeldata)
        if not getattr(self,"GuarantyLampPeriod",None ):
            self.__dict__["GuarantyLampPeriod"] = SimpleDict(self._modeldata)
        self.GuarantyLampPeriod.init(self.path + u"/GuarantyLampPeriod", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.ActiveGroups.init(self._modeldata.ActiveGroups, self.path + u"/ActiveGroups", self._modeldata)
        self.BlockLampPeriod.init(self.path + u"/BlockLampPeriod", self._modeldata)
        self.BlockLampPeriodFromLastPayment.init(self.path + u"/BlockLampPeriodFromLastPayment", self._modeldata)
        self.GuarantyLampPeriod.init(self.path + u"/GuarantyLampPeriod", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.ActiveGroups.deleteByID(id)
            self.BlockLampPeriod.deleteByID(id)
            self.BlockLampPeriodFromLastPayment.deleteByID(id)
            self.GuarantyLampPeriod.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = LampEventSettings_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["ActiveGroups"]=_dict.get("ActiveGroups").getJsonDict()
        json_dict["BlockLampPeriod"]=_dict.get("BlockLampPeriod").getJsonDict()
        json_dict["BlockLampPeriodFromLastPayment"]=_dict.get("BlockLampPeriodFromLastPayment").getJsonDict()
        json_dict["BonusGold"]=_dict.get("BonusGold")
        json_dict["Duration"]=_dict.get("Duration")
        json_dict["FwodLampRollProbability"]=_dict.get("FwodLampRollProbability")
        json_dict["FWODLimit"]=_dict.get("FWODLimit")
        json_dict["GuarantyLampPeriod"]=_dict.get("GuarantyLampPeriod").getJsonDict()
        json_dict["LampRollProbability"]=_dict.get("LampRollProbability")
        json_dict["MaxPaymentDaysForGoldStatus"]=_dict.get("MaxPaymentDaysForGoldStatus")
        json_dict["Transactions"]=_dict.get("Transactions")
        return {"LampEventSettings": json_dict}

if not hasattr(LampEventSettings_base, "generateBaseDict"):
    LampEventSettings_base.generateBaseDict = generateEmptyDict
