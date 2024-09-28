# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import RollEventItem
import QuestEventStageStep

from QuestEventStage_base import *

class QuestEventStage(RefCounted, Identified, ChangeHandler, BaseObject, QuestEventStage_base):
    _changeFields = {
        "Image":1,
        "Text":1,
        "Title":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Image"] = ""
        _dict["LoseRewards"] = Collection(modeldata)
        _dict["Rewards"] = Collection(modeldata)
        _dict["Steps"] = Collection(modeldata)
        _dict["Text"] = ""
        _dict["Title"] = ""
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"LoseRewards",None ):
            self.__dict__["LoseRewards"] = Collection(self._modeldata)
        self.LoseRewards.init(self._modeldata.RollEventItemKeeper, self.path + u"/LoseRewards", self._modeldata)
        if not getattr(self,"Rewards",None ):
            self.__dict__["Rewards"] = Collection(self._modeldata)
        self.Rewards.init(self._modeldata.RollEventItemKeeper, self.path + u"/Rewards", self._modeldata)
        if not getattr(self,"Steps",None ):
            self.__dict__["Steps"] = Collection(self._modeldata)
        self.Steps.init(self._modeldata.QuestEventStageStepKeeper, self.path + u"/Steps", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"LoseRewards",None ):
            self.__dict__["LoseRewards"] = Collection(self._modeldata)
        self.LoseRewards.init(self._modeldata.RollEventItemKeeper, self.path + u"/LoseRewards", self._modeldata)
        if not getattr(self,"Rewards",None ):
            self.__dict__["Rewards"] = Collection(self._modeldata)
        self.Rewards.init(self._modeldata.RollEventItemKeeper, self.path + u"/Rewards", self._modeldata)
        if not getattr(self,"Steps",None ):
            self.__dict__["Steps"] = Collection(self._modeldata)
        self.Steps.init(self._modeldata.QuestEventStageStepKeeper, self.path + u"/Steps", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.LoseRewards.init(self._modeldata.RollEventItemKeeper, self.path + u"/LoseRewards", self._modeldata)
        self.Rewards.init(self._modeldata.RollEventItemKeeper, self.path + u"/Rewards", self._modeldata)
        self.Steps.init(self._modeldata.QuestEventStageStepKeeper, self.path + u"/Steps", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.LoseRewards.deleteByID(id)
            self.Rewards.deleteByID(id)
            self.Steps.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = QuestEventStage_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Image"]=_dict.get("Image")
        json_dict["LoseRewards"]=_dict.get("LoseRewards").getJsonDict()
        json_dict["Rewards"]=_dict.get("Rewards").getJsonDict()
        json_dict["Steps"]=_dict.get("Steps").getJsonDict()
        json_dict["Text"]=_dict.get("Text")
        json_dict["Title"]=_dict.get("Title")
        return {"QuestEventStage": json_dict}

if not hasattr(QuestEventStage_base, "generateBaseDict"):
    QuestEventStage_base.generateBaseDict = generateEmptyDict
