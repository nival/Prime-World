# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import LampEventInfo
import UpgradeHeroTalentsInfo

from MarketingEventsInfo_base import *

class MarketingEventsInfo(RefCounted, Identified, ChangeHandler, BaseObject, MarketingEventsInfo_base):
    _changeFields = {
        "GoldHouseActionState":1,
        "IsBuyHeroComplete":1,
        "ViewedEvents":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["GoldHouseActionState"] = 0
        _dict["IsBuyHeroComplete"] = False
        _dict["LampEventInfo"] = LampEventInfo.LampEventInfo(modeldata, None, "")
        _dict["UpgradeHeroTalentsInfo"] = UpgradeHeroTalentsInfo.UpgradeHeroTalentsInfo(modeldata, None, "")
        _dict["ViewedEvents"] = SimpleList(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.LampEventInfo.setPath(self.path + u"/LampEventInfo")
        self.UpgradeHeroTalentsInfo.setPath(self.path + u"/UpgradeHeroTalentsInfo")
        if not getattr(self,"ViewedEvents",None ):
            self.__dict__["ViewedEvents"] = SimpleList(self._modeldata)
        self.ViewedEvents.init(self.path + u"/ViewedEvents", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.LampEventInfo.setPath(self.path + u"/LampEventInfo")
        self.UpgradeHeroTalentsInfo.setPath(self.path + u"/UpgradeHeroTalentsInfo")
        if not getattr(self,"ViewedEvents",None ):
            self.__dict__["ViewedEvents"] = SimpleList(self._modeldata)
        self.ViewedEvents.init(self.path + u"/ViewedEvents", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.LampEventInfo.setPath( self.path + u"/LampEventInfo" )
        self.UpgradeHeroTalentsInfo.setPath( self.path + u"/UpgradeHeroTalentsInfo" )
        self.ViewedEvents.init(self.path + u"/ViewedEvents", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.LampEventInfo.deleteByID(id)
            self.UpgradeHeroTalentsInfo.deleteByID(id)
            self.ViewedEvents.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = MarketingEventsInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["GoldHouseActionState"]=_dict.get("GoldHouseActionState")
        json_dict["IsBuyHeroComplete"]=_dict.get("IsBuyHeroComplete")
        json_dict["LampEventInfo"] = _dict.get("LampEventInfo").generateJsonDict()
        json_dict["UpgradeHeroTalentsInfo"] = _dict.get("UpgradeHeroTalentsInfo").generateJsonDict()
        json_dict["ViewedEvents"]=_dict.get("ViewedEvents").getJsonDict()
        return {"MarketingEventsInfo": json_dict}

if not hasattr(MarketingEventsInfo_base, "generateBaseDict"):
    MarketingEventsInfo_base.generateBaseDict = generateEmptyDict
