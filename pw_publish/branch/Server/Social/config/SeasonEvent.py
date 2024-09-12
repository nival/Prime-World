# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import SeasonProgressRewardRelation
import SeasonEventShopGroup
import WorldRatingRewardRelation

from SeasonEvent_base import *

class SeasonEvent(RefCounted, Identified, ChangeHandler, BaseObject, SeasonEvent_base):
    _changeFields = {
        "BannerUrl":1,
        "CompletionTalentId":1,
        "CompletionTalentRatio":1,
        "EndTimestamp":1,
        "Guid":1,
        "PersistentId":1,
        "RewardsBlockTitle":1,
        "RewardsCurrencyId":1,
        "ShopCurrencyId":1,
        "Text":1,
        "Title":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["BannerUrl"] = ""
        _dict["CompletionTalentId"] = ""
        _dict["CompletionTalentRatio"] = 0
        _dict["EndTimestamp"] = 0
        _dict["Guid"] = 0
        _dict["PersistentId"] = 0
        _dict["ProgressRewardRelations"] = Collection(modeldata)
        _dict["RewardsBlockTitle"] = ""
        _dict["RewardsCurrencyId"] = ""
        _dict["SeasonEventShopGroups"] = Collection(modeldata)
        _dict["ShopCurrencyId"] = ""
        _dict["Text"] = ""
        _dict["Title"] = ""
        _dict["WorldRatingRewardRelations"] = Collection(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"ProgressRewardRelations",None ):
            self.__dict__["ProgressRewardRelations"] = Collection(self._modeldata)
        self.ProgressRewardRelations.init(self._modeldata.SeasonProgressRewardKeeper, self.path + u"/ProgressRewardRelations", self._modeldata)
        if not getattr(self,"SeasonEventShopGroups",None ):
            self.__dict__["SeasonEventShopGroups"] = Collection(self._modeldata)
        self.SeasonEventShopGroups.init(self._modeldata.SeasonEventShopGroupKeeper, self.path + u"/SeasonEventShopGroups", self._modeldata)
        if not getattr(self,"WorldRatingRewardRelations",None ):
            self.__dict__["WorldRatingRewardRelations"] = Collection(self._modeldata)
        self.WorldRatingRewardRelations.init(self._modeldata.TradeWorldRatingRewardKeeper, self.path + u"/WorldRatingRewardRelations", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"ProgressRewardRelations",None ):
            self.__dict__["ProgressRewardRelations"] = Collection(self._modeldata)
        self.ProgressRewardRelations.init(self._modeldata.SeasonProgressRewardKeeper, self.path + u"/ProgressRewardRelations", self._modeldata)
        if not getattr(self,"SeasonEventShopGroups",None ):
            self.__dict__["SeasonEventShopGroups"] = Collection(self._modeldata)
        self.SeasonEventShopGroups.init(self._modeldata.SeasonEventShopGroupKeeper, self.path + u"/SeasonEventShopGroups", self._modeldata)
        if not getattr(self,"WorldRatingRewardRelations",None ):
            self.__dict__["WorldRatingRewardRelations"] = Collection(self._modeldata)
        self.WorldRatingRewardRelations.init(self._modeldata.TradeWorldRatingRewardKeeper, self.path + u"/WorldRatingRewardRelations", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.ProgressRewardRelations.init(self._modeldata.SeasonProgressRewardKeeper, self.path + u"/ProgressRewardRelations", self._modeldata)
        self.SeasonEventShopGroups.init(self._modeldata.SeasonEventShopGroupKeeper, self.path + u"/SeasonEventShopGroups", self._modeldata)
        self.WorldRatingRewardRelations.init(self._modeldata.TradeWorldRatingRewardKeeper, self.path + u"/WorldRatingRewardRelations", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.ProgressRewardRelations.deleteByID(id)
            self.SeasonEventShopGroups.deleteByID(id)
            self.WorldRatingRewardRelations.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = SeasonEvent_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["BannerUrl"]=_dict.get("BannerUrl")
        json_dict["CompletionTalentId"]=_dict.get("CompletionTalentId")
        json_dict["CompletionTalentRatio"]=_dict.get("CompletionTalentRatio")
        json_dict["EndTimestamp"]=_dict.get("EndTimestamp")
        json_dict["Guid"]=_dict.get("Guid")
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["ProgressRewardRelations"]=_dict.get("ProgressRewardRelations").getJsonDict()
        json_dict["RewardsBlockTitle"]=_dict.get("RewardsBlockTitle")
        json_dict["RewardsCurrencyId"]=_dict.get("RewardsCurrencyId")
        json_dict["SeasonEventShopGroups"]=_dict.get("SeasonEventShopGroups").getJsonDict()
        json_dict["ShopCurrencyId"]=_dict.get("ShopCurrencyId")
        json_dict["Text"]=_dict.get("Text")
        json_dict["Title"]=_dict.get("Title")
        json_dict["WorldRatingRewardRelations"]=_dict.get("WorldRatingRewardRelations").getJsonDict()
        return {"SeasonEvent": json_dict}

if not hasattr(SeasonEvent_base, "generateBaseDict"):
    SeasonEvent_base.generateBaseDict = generateEmptyDict
