# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import ReforgeTalentPrices
import RerollShopGroupUpgradeLevels
import RerollShopWeightsToTimes
import ResourceTable
import RerollShopBanner

from EventToolsChangeFields_base import *

class EventToolsChangeFields(RefCounted, Identified, ChangeHandler, BaseObject, EventToolsChangeFields_base):
    _changeFields = {
        "FIRST_BUY_GOLD_PRICES":1,
        "HERO_SILVER_PRICES":1,
        "INACTIVE_REROLL_SHOP_ORDINARY_SLOTS":1,
        "INACTIVE_REROLL_SHOP_PREMIUM_SLOTS":1,
        "ORDINARY_TALENTS_DROP_RARITIES":1,
        "PREMIUM_SLOTS_ARE_NOT_INACTIVE":1,
        "PREMIUM_TALENTS_DROP_RARITIES":1,
        "REROLL_SHOP_ORDINARY_SLOTS":1,
        "REROLL_SHOP_PREMIUM_SLOTS":1,
        "REROLL_SHOP_SLOT_RESOURCES_AMOUNT":1,
        "REROLL_SHOP_TOOLTIP":1,
        "SKIN_GOLD_PRICES":1,
        "TRANSMUTATION_TALENTS_PER_PERL":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["FIRST_BUY_GOLD_PRICES"] = SimpleDict(modeldata)
        _dict["HERO_SILVER_PRICES"] = SimpleDict(modeldata)
        _dict["INACTIVE_REROLL_SHOP_ORDINARY_SLOTS"] = 0
        _dict["INACTIVE_REROLL_SHOP_PREMIUM_SLOTS"] = 0
        _dict["ORDINARY_TALENTS_DROP_RARITIES"] = SimpleList(modeldata)
        _dict["PREMIUM_SLOTS_ARE_NOT_INACTIVE"] = False
        _dict["PREMIUM_TALENTS_DROP_RARITIES"] = SimpleList(modeldata)
        _dict["ReforgePrices"] = Set(modeldata)
        _dict["REROLL_SHOP_GROUP_UPGRADE_LEVELS"] = Collection(modeldata)
        _dict["REROLL_SHOP_GROUP_WEIGHTS"] = Collection(modeldata)
        _dict["REROLL_SHOP_ORDINARY_SLOTS"] = 0
        _dict["REROLL_SHOP_PREMIUM_SLOTS"] = 0
        _dict["REROLL_SHOP_PRICE"] = ResourceTable.ResourceTable(modeldata, None, "")
        _dict["REROLL_SHOP_SLOT_RESOURCES_AMOUNT"] = SimpleDict(modeldata)
        _dict["REROLL_SHOP_TOOLTIP"] = ""
        _dict["RerollShopBanner"] = RerollShopBanner.RerollShopBanner(modeldata, None, "")
        _dict["SKIN_GOLD_PRICES"] = SimpleDict(modeldata)
        _dict["TRANSMUTATION_TALENTS_PER_PERL"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"FIRST_BUY_GOLD_PRICES",None ):
            self.__dict__["FIRST_BUY_GOLD_PRICES"] = SimpleDict(self._modeldata)
        self.FIRST_BUY_GOLD_PRICES.init(self.path + u"/FIRST_BUY_GOLD_PRICES", self._modeldata)
        if not getattr(self,"HERO_SILVER_PRICES",None ):
            self.__dict__["HERO_SILVER_PRICES"] = SimpleDict(self._modeldata)
        self.HERO_SILVER_PRICES.init(self.path + u"/HERO_SILVER_PRICES", self._modeldata)
        if not getattr(self,"ORDINARY_TALENTS_DROP_RARITIES",None ):
            self.__dict__["ORDINARY_TALENTS_DROP_RARITIES"] = SimpleList(self._modeldata)
        self.ORDINARY_TALENTS_DROP_RARITIES.init(self.path + u"/ORDINARY_TALENTS_DROP_RARITIES", self._modeldata)
        if not getattr(self,"PREMIUM_TALENTS_DROP_RARITIES",None ):
            self.__dict__["PREMIUM_TALENTS_DROP_RARITIES"] = SimpleList(self._modeldata)
        self.PREMIUM_TALENTS_DROP_RARITIES.init(self.path + u"/PREMIUM_TALENTS_DROP_RARITIES", self._modeldata)
        if not getattr(self,"ReforgePrices",None ):
            self.__dict__["ReforgePrices"] = Set(self._modeldata)
        self.ReforgePrices.init(self._modeldata.ReforgeTalentPricesKeeper, self.path + u"/ReforgePrices", self._modeldata)
        if not getattr(self,"REROLL_SHOP_GROUP_UPGRADE_LEVELS",None ):
            self.__dict__["REROLL_SHOP_GROUP_UPGRADE_LEVELS"] = Collection(self._modeldata)
        self.REROLL_SHOP_GROUP_UPGRADE_LEVELS.init(self._modeldata.RerollShopGroupUpgradeLevelsKeeper, self.path + u"/REROLL_SHOP_GROUP_UPGRADE_LEVELS", self._modeldata)
        if not getattr(self,"REROLL_SHOP_GROUP_WEIGHTS",None ):
            self.__dict__["REROLL_SHOP_GROUP_WEIGHTS"] = Collection(self._modeldata)
        self.REROLL_SHOP_GROUP_WEIGHTS.init(self._modeldata.RerollShopWeightsToTimesKeeper, self.path + u"/REROLL_SHOP_GROUP_WEIGHTS", self._modeldata)
        self.REROLL_SHOP_PRICE.setPath(self.path + u"/REROLL_SHOP_PRICE")
        if not getattr(self,"REROLL_SHOP_SLOT_RESOURCES_AMOUNT",None ):
            self.__dict__["REROLL_SHOP_SLOT_RESOURCES_AMOUNT"] = SimpleDict(self._modeldata)
        self.REROLL_SHOP_SLOT_RESOURCES_AMOUNT.init(self.path + u"/REROLL_SHOP_SLOT_RESOURCES_AMOUNT", self._modeldata)
        self.RerollShopBanner.setPath(self.path + u"/RerollShopBanner")
        if not getattr(self,"SKIN_GOLD_PRICES",None ):
            self.__dict__["SKIN_GOLD_PRICES"] = SimpleDict(self._modeldata)
        self.SKIN_GOLD_PRICES.init(self.path + u"/SKIN_GOLD_PRICES", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"FIRST_BUY_GOLD_PRICES",None ):
            self.__dict__["FIRST_BUY_GOLD_PRICES"] = SimpleDict(self._modeldata)
        self.FIRST_BUY_GOLD_PRICES.init(self.path + u"/FIRST_BUY_GOLD_PRICES", self._modeldata)
        if not getattr(self,"HERO_SILVER_PRICES",None ):
            self.__dict__["HERO_SILVER_PRICES"] = SimpleDict(self._modeldata)
        self.HERO_SILVER_PRICES.init(self.path + u"/HERO_SILVER_PRICES", self._modeldata)
        if not getattr(self,"ORDINARY_TALENTS_DROP_RARITIES",None ):
            self.__dict__["ORDINARY_TALENTS_DROP_RARITIES"] = SimpleList(self._modeldata)
        self.ORDINARY_TALENTS_DROP_RARITIES.init(self.path + u"/ORDINARY_TALENTS_DROP_RARITIES", self._modeldata)
        if not getattr(self,"PREMIUM_TALENTS_DROP_RARITIES",None ):
            self.__dict__["PREMIUM_TALENTS_DROP_RARITIES"] = SimpleList(self._modeldata)
        self.PREMIUM_TALENTS_DROP_RARITIES.init(self.path + u"/PREMIUM_TALENTS_DROP_RARITIES", self._modeldata)
        if not getattr(self,"ReforgePrices",None ):
            self.__dict__["ReforgePrices"] = Set(self._modeldata)
        self.ReforgePrices.init(self._modeldata.ReforgeTalentPricesKeeper, self.path + u"/ReforgePrices", self._modeldata)
        if not getattr(self,"REROLL_SHOP_GROUP_UPGRADE_LEVELS",None ):
            self.__dict__["REROLL_SHOP_GROUP_UPGRADE_LEVELS"] = Collection(self._modeldata)
        self.REROLL_SHOP_GROUP_UPGRADE_LEVELS.init(self._modeldata.RerollShopGroupUpgradeLevelsKeeper, self.path + u"/REROLL_SHOP_GROUP_UPGRADE_LEVELS", self._modeldata)
        if not getattr(self,"REROLL_SHOP_GROUP_WEIGHTS",None ):
            self.__dict__["REROLL_SHOP_GROUP_WEIGHTS"] = Collection(self._modeldata)
        self.REROLL_SHOP_GROUP_WEIGHTS.init(self._modeldata.RerollShopWeightsToTimesKeeper, self.path + u"/REROLL_SHOP_GROUP_WEIGHTS", self._modeldata)
        self.REROLL_SHOP_PRICE.setPath(self.path + u"/REROLL_SHOP_PRICE")
        if not getattr(self,"REROLL_SHOP_SLOT_RESOURCES_AMOUNT",None ):
            self.__dict__["REROLL_SHOP_SLOT_RESOURCES_AMOUNT"] = SimpleDict(self._modeldata)
        self.REROLL_SHOP_SLOT_RESOURCES_AMOUNT.init(self.path + u"/REROLL_SHOP_SLOT_RESOURCES_AMOUNT", self._modeldata)
        self.RerollShopBanner.setPath(self.path + u"/RerollShopBanner")
        if not getattr(self,"SKIN_GOLD_PRICES",None ):
            self.__dict__["SKIN_GOLD_PRICES"] = SimpleDict(self._modeldata)
        self.SKIN_GOLD_PRICES.init(self.path + u"/SKIN_GOLD_PRICES", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.FIRST_BUY_GOLD_PRICES.init(self.path + u"/FIRST_BUY_GOLD_PRICES", self._modeldata)
        self.HERO_SILVER_PRICES.init(self.path + u"/HERO_SILVER_PRICES", self._modeldata)
        self.ORDINARY_TALENTS_DROP_RARITIES.init(self.path + u"/ORDINARY_TALENTS_DROP_RARITIES", self._modeldata)
        self.PREMIUM_TALENTS_DROP_RARITIES.init(self.path + u"/PREMIUM_TALENTS_DROP_RARITIES", self._modeldata)
        self.ReforgePrices.init(self._modeldata.ReforgeTalentPricesKeeper, self.path + u"/ReforgePrices", self._modeldata)
        self.REROLL_SHOP_GROUP_UPGRADE_LEVELS.init(self._modeldata.RerollShopGroupUpgradeLevelsKeeper, self.path + u"/REROLL_SHOP_GROUP_UPGRADE_LEVELS", self._modeldata)
        self.REROLL_SHOP_GROUP_WEIGHTS.init(self._modeldata.RerollShopWeightsToTimesKeeper, self.path + u"/REROLL_SHOP_GROUP_WEIGHTS", self._modeldata)
        self.REROLL_SHOP_PRICE.setPath( self.path + u"/REROLL_SHOP_PRICE" )
        self.REROLL_SHOP_SLOT_RESOURCES_AMOUNT.init(self.path + u"/REROLL_SHOP_SLOT_RESOURCES_AMOUNT", self._modeldata)
        self.RerollShopBanner.setPath( self.path + u"/RerollShopBanner" )
        self.SKIN_GOLD_PRICES.init(self.path + u"/SKIN_GOLD_PRICES", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.FIRST_BUY_GOLD_PRICES.deleteByID(id)
            self.HERO_SILVER_PRICES.deleteByID(id)
            self.ORDINARY_TALENTS_DROP_RARITIES.deleteByID(id)
            self.PREMIUM_TALENTS_DROP_RARITIES.deleteByID(id)
            self.ReforgePrices.deleteByID(id)
            self.REROLL_SHOP_GROUP_UPGRADE_LEVELS.deleteByID(id)
            self.REROLL_SHOP_GROUP_WEIGHTS.deleteByID(id)
            self.REROLL_SHOP_PRICE.deleteByID(id)
            self.REROLL_SHOP_SLOT_RESOURCES_AMOUNT.deleteByID(id)
            self.RerollShopBanner.deleteByID(id)
            self.SKIN_GOLD_PRICES.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = EventToolsChangeFields_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["FIRST_BUY_GOLD_PRICES"]=_dict.get("FIRST_BUY_GOLD_PRICES").getJsonDict()
        json_dict["HERO_SILVER_PRICES"]=_dict.get("HERO_SILVER_PRICES").getJsonDict()
        json_dict["INACTIVE_REROLL_SHOP_ORDINARY_SLOTS"]=_dict.get("INACTIVE_REROLL_SHOP_ORDINARY_SLOTS")
        json_dict["INACTIVE_REROLL_SHOP_PREMIUM_SLOTS"]=_dict.get("INACTIVE_REROLL_SHOP_PREMIUM_SLOTS")
        json_dict["ORDINARY_TALENTS_DROP_RARITIES"]=_dict.get("ORDINARY_TALENTS_DROP_RARITIES").getJsonDict()
        json_dict["PREMIUM_SLOTS_ARE_NOT_INACTIVE"]=_dict.get("PREMIUM_SLOTS_ARE_NOT_INACTIVE")
        json_dict["PREMIUM_TALENTS_DROP_RARITIES"]=_dict.get("PREMIUM_TALENTS_DROP_RARITIES").getJsonDict()
        json_dict["ReforgePrices"]=_dict.get("ReforgePrices").getJsonDict()
        json_dict["REROLL_SHOP_GROUP_UPGRADE_LEVELS"]=_dict.get("REROLL_SHOP_GROUP_UPGRADE_LEVELS").getJsonDict()
        json_dict["REROLL_SHOP_GROUP_WEIGHTS"]=_dict.get("REROLL_SHOP_GROUP_WEIGHTS").getJsonDict()
        json_dict["REROLL_SHOP_ORDINARY_SLOTS"]=_dict.get("REROLL_SHOP_ORDINARY_SLOTS")
        json_dict["REROLL_SHOP_PREMIUM_SLOTS"]=_dict.get("REROLL_SHOP_PREMIUM_SLOTS")
        json_dict["REROLL_SHOP_PRICE"] = _dict.get("REROLL_SHOP_PRICE").generateJsonDict()
        json_dict["REROLL_SHOP_SLOT_RESOURCES_AMOUNT"]=_dict.get("REROLL_SHOP_SLOT_RESOURCES_AMOUNT").getJsonDict()
        json_dict["REROLL_SHOP_TOOLTIP"]=_dict.get("REROLL_SHOP_TOOLTIP")
        json_dict["RerollShopBanner"] = _dict.get("RerollShopBanner").generateJsonDict()
        json_dict["SKIN_GOLD_PRICES"]=_dict.get("SKIN_GOLD_PRICES").getJsonDict()
        json_dict["TRANSMUTATION_TALENTS_PER_PERL"]=_dict.get("TRANSMUTATION_TALENTS_PER_PERL")
        return {"EventToolsChangeFields": json_dict}

if not hasattr(EventToolsChangeFields_base, "generateBaseDict"):
    EventToolsChangeFields_base.generateBaseDict = generateEmptyDict
