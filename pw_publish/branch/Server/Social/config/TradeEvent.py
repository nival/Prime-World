# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import ExperienceRewardRelation
import TradeEventGroup
import WorldRatingRewardRelation

from TradeEvent_base import *

class TradeEvent(RefCounted, Identified, ChangeHandler, BaseObject, TradeEvent_base):
    _changeFields = {
        "BannerUrl":1,
        "CompletionTalentId":1,
        "CompletionTalentRatio":1,
        "EndTimestamp":1,
        "ExperienceCurrencyName":1,
        "Guid":1,
        "PersistentId":1,
        "RewardsBlockTitle":1,
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
        _dict["ExperienceCurrencyName"] = ""
        _dict["ExperienceRewardRelations"] = Collection(modeldata)
        _dict["Guid"] = 0
        _dict["PersistentId"] = 0
        _dict["RewardsBlockTitle"] = ""
        _dict["Text"] = ""
        _dict["Title"] = ""
        _dict["TradeEventGroups"] = Collection(modeldata)
        _dict["WorldRatingRewardRelations"] = Collection(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"ExperienceRewardRelations",None ):
            self.__dict__["ExperienceRewardRelations"] = Collection(self._modeldata)
        self.ExperienceRewardRelations.init(self._modeldata.TradeExperienceRewardKeeper, self.path + u"/ExperienceRewardRelations", self._modeldata)
        if not getattr(self,"TradeEventGroups",None ):
            self.__dict__["TradeEventGroups"] = Collection(self._modeldata)
        self.TradeEventGroups.init(self._modeldata.TradeEventGroupKeeper, self.path + u"/TradeEventGroups", self._modeldata)
        if not getattr(self,"WorldRatingRewardRelations",None ):
            self.__dict__["WorldRatingRewardRelations"] = Collection(self._modeldata)
        self.WorldRatingRewardRelations.init(self._modeldata.TradeWorldRatingRewardKeeper, self.path + u"/WorldRatingRewardRelations", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"ExperienceRewardRelations",None ):
            self.__dict__["ExperienceRewardRelations"] = Collection(self._modeldata)
        self.ExperienceRewardRelations.init(self._modeldata.TradeExperienceRewardKeeper, self.path + u"/ExperienceRewardRelations", self._modeldata)
        if not getattr(self,"TradeEventGroups",None ):
            self.__dict__["TradeEventGroups"] = Collection(self._modeldata)
        self.TradeEventGroups.init(self._modeldata.TradeEventGroupKeeper, self.path + u"/TradeEventGroups", self._modeldata)
        if not getattr(self,"WorldRatingRewardRelations",None ):
            self.__dict__["WorldRatingRewardRelations"] = Collection(self._modeldata)
        self.WorldRatingRewardRelations.init(self._modeldata.TradeWorldRatingRewardKeeper, self.path + u"/WorldRatingRewardRelations", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.ExperienceRewardRelations.init(self._modeldata.TradeExperienceRewardKeeper, self.path + u"/ExperienceRewardRelations", self._modeldata)
        self.TradeEventGroups.init(self._modeldata.TradeEventGroupKeeper, self.path + u"/TradeEventGroups", self._modeldata)
        self.WorldRatingRewardRelations.init(self._modeldata.TradeWorldRatingRewardKeeper, self.path + u"/WorldRatingRewardRelations", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.ExperienceRewardRelations.deleteByID(id)
            self.TradeEventGroups.deleteByID(id)
            self.WorldRatingRewardRelations.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = TradeEvent_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["BannerUrl"]=_dict.get("BannerUrl")
        json_dict["CompletionTalentId"]=_dict.get("CompletionTalentId")
        json_dict["CompletionTalentRatio"]=_dict.get("CompletionTalentRatio")
        json_dict["EndTimestamp"]=_dict.get("EndTimestamp")
        json_dict["ExperienceCurrencyName"]=_dict.get("ExperienceCurrencyName")
        json_dict["ExperienceRewardRelations"]=_dict.get("ExperienceRewardRelations").getJsonDict()
        json_dict["Guid"]=_dict.get("Guid")
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["RewardsBlockTitle"]=_dict.get("RewardsBlockTitle")
        json_dict["Text"]=_dict.get("Text")
        json_dict["Title"]=_dict.get("Title")
        json_dict["TradeEventGroups"]=_dict.get("TradeEventGroups").getJsonDict()
        json_dict["WorldRatingRewardRelations"]=_dict.get("WorldRatingRewardRelations").getJsonDict()
        return {"TradeEvent": json_dict}

if not hasattr(TradeEvent_base, "generateBaseDict"):
    TradeEvent_base.generateBaseDict = generateEmptyDict
