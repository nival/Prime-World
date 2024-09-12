# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import DynamicQuestAward
import DynamicObjective
import DynamicQuestToTalentsMetaInf
import PreCondition

from DynamicQuest_base import *

class DynamicQuest(RefCounted, Identified, ChangeHandler, BaseObject, DynamicQuest_base):
    _changeFields = {
        "AutoAccept":1,
        "CompletionText":1,
        "DependedTournamentQuests":1,
        "DescriptionImage":1,
        "NPCPortret":1,
        "PersistentId":1,
        "QuestDescription":1,
        "QuestEndTime":1,
        "QuestName":1,
        "QuestStartTime":1,
        "QuestState":1,
        "Reason":1,
        "RepeatOnMiss":1,
        "Version":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["AlternativeAwards"] = Set(modeldata)
        _dict["AlternativeObjectives"] = Set(modeldata)
        _dict["AutoAccept"] = False
        _dict["Awards"] = Set(modeldata)
        _dict["CompletionText"] = ""
        _dict["DependedTournamentQuests"] = SimpleList(modeldata)
        _dict["DescriptionImage"] = ""
        _dict["DynamicQuestToTalentsMetaInf"] = DynamicQuestToTalentsMetaInf.DynamicQuestToTalentsMetaInf(modeldata, None, "")
        _dict["NPCPortret"] = ""
        _dict["Objectives"] = Set(modeldata)
        _dict["PersistentId"] = 0
        _dict["PreConditions"] = Set(modeldata)
        _dict["QuestDescription"] = ""
        _dict["QuestEndTime"] = 0
        _dict["QuestName"] = ""
        _dict["QuestStartTime"] = 0
        _dict["QuestState"] = 0
        _dict["Reason"] = 0
        _dict["RepeatOnMiss"] = False
        _dict["Version"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"AlternativeAwards",None ):
            self.__dict__["AlternativeAwards"] = Set(self._modeldata)
        self.AlternativeAwards.init(self._modeldata.DynamicQuestAwardsKeeper, self.path + u"/AlternativeAwards", self._modeldata)
        if not getattr(self,"AlternativeObjectives",None ):
            self.__dict__["AlternativeObjectives"] = Set(self._modeldata)
        self.AlternativeObjectives.init(self._modeldata.DynamicObjectivesKeeper, self.path + u"/AlternativeObjectives", self._modeldata)
        if not getattr(self,"Awards",None ):
            self.__dict__["Awards"] = Set(self._modeldata)
        self.Awards.init(self._modeldata.DynamicQuestAwardsKeeper, self.path + u"/Awards", self._modeldata)
        if not getattr(self,"DependedTournamentQuests",None ):
            self.__dict__["DependedTournamentQuests"] = SimpleList(self._modeldata)
        self.DependedTournamentQuests.init(self.path + u"/DependedTournamentQuests", self._modeldata)
        self.DynamicQuestToTalentsMetaInf.setPath(self.path + u"/DynamicQuestToTalentsMetaInf")
        if not getattr(self,"Objectives",None ):
            self.__dict__["Objectives"] = Set(self._modeldata)
        self.Objectives.init(self._modeldata.DynamicObjectivesKeeper, self.path + u"/Objectives", self._modeldata)
        if not getattr(self,"PreConditions",None ):
            self.__dict__["PreConditions"] = Set(self._modeldata)
        self.PreConditions.init(self._modeldata.PreConditionsKeeper, self.path + u"/PreConditions", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"AlternativeAwards",None ):
            self.__dict__["AlternativeAwards"] = Set(self._modeldata)
        self.AlternativeAwards.init(self._modeldata.DynamicQuestAwardsKeeper, self.path + u"/AlternativeAwards", self._modeldata)
        if not getattr(self,"AlternativeObjectives",None ):
            self.__dict__["AlternativeObjectives"] = Set(self._modeldata)
        self.AlternativeObjectives.init(self._modeldata.DynamicObjectivesKeeper, self.path + u"/AlternativeObjectives", self._modeldata)
        if not getattr(self,"Awards",None ):
            self.__dict__["Awards"] = Set(self._modeldata)
        self.Awards.init(self._modeldata.DynamicQuestAwardsKeeper, self.path + u"/Awards", self._modeldata)
        if not getattr(self,"DependedTournamentQuests",None ):
            self.__dict__["DependedTournamentQuests"] = SimpleList(self._modeldata)
        self.DependedTournamentQuests.init(self.path + u"/DependedTournamentQuests", self._modeldata)
        self.DynamicQuestToTalentsMetaInf.setPath(self.path + u"/DynamicQuestToTalentsMetaInf")
        if not getattr(self,"Objectives",None ):
            self.__dict__["Objectives"] = Set(self._modeldata)
        self.Objectives.init(self._modeldata.DynamicObjectivesKeeper, self.path + u"/Objectives", self._modeldata)
        if not getattr(self,"PreConditions",None ):
            self.__dict__["PreConditions"] = Set(self._modeldata)
        self.PreConditions.init(self._modeldata.PreConditionsKeeper, self.path + u"/PreConditions", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.AlternativeAwards.init(self._modeldata.DynamicQuestAwardsKeeper, self.path + u"/AlternativeAwards", self._modeldata)
        self.AlternativeObjectives.init(self._modeldata.DynamicObjectivesKeeper, self.path + u"/AlternativeObjectives", self._modeldata)
        self.Awards.init(self._modeldata.DynamicQuestAwardsKeeper, self.path + u"/Awards", self._modeldata)
        self.DependedTournamentQuests.init(self.path + u"/DependedTournamentQuests", self._modeldata)
        self.DynamicQuestToTalentsMetaInf.setPath( self.path + u"/DynamicQuestToTalentsMetaInf" )
        self.Objectives.init(self._modeldata.DynamicObjectivesKeeper, self.path + u"/Objectives", self._modeldata)
        self.PreConditions.init(self._modeldata.PreConditionsKeeper, self.path + u"/PreConditions", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.AlternativeAwards.deleteByID(id)
            self.AlternativeObjectives.deleteByID(id)
            self.Awards.deleteByID(id)
            self.DependedTournamentQuests.deleteByID(id)
            self.DynamicQuestToTalentsMetaInf.deleteByID(id)
            self.Objectives.deleteByID(id)
            self.PreConditions.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = DynamicQuest_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["AlternativeAwards"]=_dict.get("AlternativeAwards").getJsonDict()
        json_dict["AlternativeObjectives"]=_dict.get("AlternativeObjectives").getJsonDict()
        json_dict["AutoAccept"]=_dict.get("AutoAccept")
        json_dict["Awards"]=_dict.get("Awards").getJsonDict()
        json_dict["CompletionText"]=_dict.get("CompletionText")
        json_dict["DependedTournamentQuests"]=_dict.get("DependedTournamentQuests").getJsonDict()
        json_dict["DescriptionImage"]=_dict.get("DescriptionImage")
        json_dict["DynamicQuestToTalentsMetaInf"] = _dict.get("DynamicQuestToTalentsMetaInf").generateJsonDict()
        json_dict["NPCPortret"]=_dict.get("NPCPortret")
        json_dict["Objectives"]=_dict.get("Objectives").getJsonDict()
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["PreConditions"]=_dict.get("PreConditions").getJsonDict()
        json_dict["QuestDescription"]=_dict.get("QuestDescription")
        json_dict["QuestEndTime"]=_dict.get("QuestEndTime")
        json_dict["QuestName"]=_dict.get("QuestName")
        json_dict["QuestStartTime"]=_dict.get("QuestStartTime")
        json_dict["QuestState"]=_dict.get("QuestState")
        json_dict["Reason"]=_dict.get("Reason")
        json_dict["RepeatOnMiss"]=_dict.get("RepeatOnMiss")
        json_dict["Version"]=_dict.get("Version")
        return {"DynamicQuest": json_dict}

if not hasattr(DynamicQuest_base, "generateBaseDict"):
    DynamicQuest_base.generateBaseDict = generateEmptyDict
