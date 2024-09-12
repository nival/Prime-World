# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import InstantCondition
import MDCondition
import SessionCondition

from DynamicObjective_base import *

class DynamicObjective(RefCounted, Identified, ChangeHandler, BaseObject, DynamicObjective_base):
    _changeFields = {
        "ButtonDescription":1,
        "CurrentValue":1,
        "Description":1,
        "EditId":1,
        "IsCompleted":1,
        "QuestCheckType":1,
        "ShowProgress":1,
        "talentsToDeletePersistentIds":1,
        "verifiedTalentsToRemove":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["ButtonDescription"] = ""
        _dict["CurrentValue"] = 0
        _dict["Description"] = ""
        _dict["EditId"] = 0
        _dict["InstantCondition"] = InstantCondition.InstantCondition(modeldata, None, "")
        _dict["IsCompleted"] = False
        _dict["ModelDataCondition"] = MDCondition.MDCondition(modeldata, None, "")
        _dict["QuestCheckType"] = 0
        _dict["SessionCondition"] = SessionCondition.SessionCondition(modeldata, None, "")
        _dict["ShowProgress"] = False
        _dict["talentsToDeletePersistentIds"] = SimpleList(modeldata)
        _dict["verifiedTalentsToRemove"] = SimpleList(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.InstantCondition.setPath(self.path + u"/InstantCondition")
        self.ModelDataCondition.setPath(self.path + u"/ModelDataCondition")
        self.SessionCondition.setPath(self.path + u"/SessionCondition")
        if not getattr(self,"talentsToDeletePersistentIds",None ):
            self.__dict__["talentsToDeletePersistentIds"] = SimpleList(self._modeldata)
        self.talentsToDeletePersistentIds.init(self.path + u"/talentsToDeletePersistentIds", self._modeldata)
        if not getattr(self,"verifiedTalentsToRemove",None ):
            self.__dict__["verifiedTalentsToRemove"] = SimpleList(self._modeldata)
        self.verifiedTalentsToRemove.init(self.path + u"/verifiedTalentsToRemove", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.InstantCondition.setPath(self.path + u"/InstantCondition")
        self.ModelDataCondition.setPath(self.path + u"/ModelDataCondition")
        self.SessionCondition.setPath(self.path + u"/SessionCondition")
        if not getattr(self,"talentsToDeletePersistentIds",None ):
            self.__dict__["talentsToDeletePersistentIds"] = SimpleList(self._modeldata)
        self.talentsToDeletePersistentIds.init(self.path + u"/talentsToDeletePersistentIds", self._modeldata)
        if not getattr(self,"verifiedTalentsToRemove",None ):
            self.__dict__["verifiedTalentsToRemove"] = SimpleList(self._modeldata)
        self.verifiedTalentsToRemove.init(self.path + u"/verifiedTalentsToRemove", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.InstantCondition.setPath( self.path + u"/InstantCondition" )
        self.ModelDataCondition.setPath( self.path + u"/ModelDataCondition" )
        self.SessionCondition.setPath( self.path + u"/SessionCondition" )
        self.talentsToDeletePersistentIds.init(self.path + u"/talentsToDeletePersistentIds", self._modeldata)
        self.verifiedTalentsToRemove.init(self.path + u"/verifiedTalentsToRemove", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.InstantCondition.deleteByID(id)
            self.ModelDataCondition.deleteByID(id)
            self.SessionCondition.deleteByID(id)
            self.talentsToDeletePersistentIds.deleteByID(id)
            self.verifiedTalentsToRemove.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = DynamicObjective_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["ButtonDescription"]=_dict.get("ButtonDescription")
        json_dict["CurrentValue"]=_dict.get("CurrentValue")
        json_dict["Description"]=_dict.get("Description")
        json_dict["EditId"]=_dict.get("EditId")
        json_dict["InstantCondition"] = _dict.get("InstantCondition").generateJsonDict()
        json_dict["IsCompleted"]=_dict.get("IsCompleted")
        json_dict["ModelDataCondition"] = _dict.get("ModelDataCondition").generateJsonDict()
        json_dict["QuestCheckType"]=_dict.get("QuestCheckType")
        json_dict["SessionCondition"] = _dict.get("SessionCondition").generateJsonDict()
        json_dict["ShowProgress"]=_dict.get("ShowProgress")
        json_dict["talentsToDeletePersistentIds"]=_dict.get("talentsToDeletePersistentIds").getJsonDict()
        json_dict["verifiedTalentsToRemove"]=_dict.get("verifiedTalentsToRemove").getJsonDict()
        return {"DynamicObjective": json_dict}

if not hasattr(DynamicObjective_base, "generateBaseDict"):
    DynamicObjective_base.generateBaseDict = generateEmptyDict
