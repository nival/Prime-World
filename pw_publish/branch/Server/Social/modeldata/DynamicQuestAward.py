# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import DynamicQuestLampAward
import DynamicQuestUpgradeHeroTalentsAward

from DynamicQuestAward_base import *

class DynamicQuestAward(RefCounted, Identified, ChangeHandler, BaseObject, DynamicQuestAward_base):
    _changeFields = {
        "AdditionalData":1,
        "AwardConditionType":1,
        "CustomCurrencyId":1,
        "DbId":1,
        "PersistentId":1,
        "QuestAwardType":1,
        "Value":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["AdditionalData"] = ""
        _dict["AwardConditionType"] = 0
        _dict["CustomCurrencyId"] = ""
        _dict["DbId"] = ""
        _dict["Lamp"] = DynamicQuestLampAward.DynamicQuestLampAward(modeldata, None, "")
        _dict["PersistentId"] = 0
        _dict["QuestAwardType"] = 0
        _dict["UpgradeHeroTalents"] = DynamicQuestUpgradeHeroTalentsAward.DynamicQuestUpgradeHeroTalentsAward(modeldata, None, "")
        _dict["Value"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.Lamp.setPath(self.path + u"/Lamp")
        self.UpgradeHeroTalents.setPath(self.path + u"/UpgradeHeroTalents")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.Lamp.setPath(self.path + u"/Lamp")
        self.UpgradeHeroTalents.setPath(self.path + u"/UpgradeHeroTalents")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Lamp.setPath( self.path + u"/Lamp" )
        self.UpgradeHeroTalents.setPath( self.path + u"/UpgradeHeroTalents" )

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Lamp.deleteByID(id)
            self.UpgradeHeroTalents.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = DynamicQuestAward_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["AdditionalData"]=_dict.get("AdditionalData")
        json_dict["AwardConditionType"]=_dict.get("AwardConditionType")
        json_dict["CustomCurrencyId"]=_dict.get("CustomCurrencyId")
        json_dict["DbId"]=_dict.get("DbId")
        json_dict["Lamp"] = _dict.get("Lamp").generateJsonDict()
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["QuestAwardType"]=_dict.get("QuestAwardType")
        json_dict["UpgradeHeroTalents"] = _dict.get("UpgradeHeroTalents").generateJsonDict()
        json_dict["Value"]=_dict.get("Value")
        return {"DynamicQuestAward": json_dict}

if not hasattr(DynamicQuestAward_base, "generateBaseDict"):
    DynamicQuestAward_base.generateBaseDict = generateEmptyDict
