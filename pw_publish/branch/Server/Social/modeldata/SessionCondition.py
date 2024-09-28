# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from SessionCondition_base import *

class SessionCondition(RefCounted, Identified, ChangeHandler, BaseObject, SessionCondition_base):
    _changeFields = {
        "CollectingType":1,
        "EnemyPartySize":1,
        "GameTypes":1,
        "IncrementPerBattle":1,
        "IsEnemyPartySizeStrongCond":1,
        "IsGuildGame":1,
        "IsPlayerPartySizeStrongCond":1,
        "PickedHeroes":1,
        "PlayerPartySize":1,
        "SessionCheckType":1,
        "TotalValue":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["CollectingType"] = ""
        _dict["EnemyPartySize"] = 1
        _dict["GameTypes"] = SimpleList(modeldata)
        _dict["IncrementPerBattle"] = 0
        _dict["IsEnemyPartySizeStrongCond"] = False
        _dict["IsGuildGame"] = False
        _dict["IsPlayerPartySizeStrongCond"] = False
        _dict["PickedHeroes"] = SimpleList(modeldata)
        _dict["PlayerPartySize"] = 1
        _dict["SessionCheckType"] = 0
        _dict["TotalValue"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"GameTypes",None ):
            self.__dict__["GameTypes"] = SimpleList(self._modeldata)
        self.GameTypes.init(self.path + u"/GameTypes", self._modeldata)
        if not getattr(self,"PickedHeroes",None ):
            self.__dict__["PickedHeroes"] = SimpleList(self._modeldata)
        self.PickedHeroes.init(self.path + u"/PickedHeroes", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"GameTypes",None ):
            self.__dict__["GameTypes"] = SimpleList(self._modeldata)
        self.GameTypes.init(self.path + u"/GameTypes", self._modeldata)
        if not getattr(self,"PickedHeroes",None ):
            self.__dict__["PickedHeroes"] = SimpleList(self._modeldata)
        self.PickedHeroes.init(self.path + u"/PickedHeroes", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.GameTypes.init(self.path + u"/GameTypes", self._modeldata)
        self.PickedHeroes.init(self.path + u"/PickedHeroes", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.GameTypes.deleteByID(id)
            self.PickedHeroes.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = SessionCondition_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["CollectingType"]=_dict.get("CollectingType")
        json_dict["EnemyPartySize"]=_dict.get("EnemyPartySize")
        json_dict["GameTypes"]=_dict.get("GameTypes").getJsonDict()
        json_dict["IncrementPerBattle"]=_dict.get("IncrementPerBattle")
        json_dict["IsEnemyPartySizeStrongCond"]=_dict.get("IsEnemyPartySizeStrongCond")
        json_dict["IsGuildGame"]=_dict.get("IsGuildGame")
        json_dict["IsPlayerPartySizeStrongCond"]=_dict.get("IsPlayerPartySizeStrongCond")
        json_dict["PickedHeroes"]=_dict.get("PickedHeroes").getJsonDict()
        json_dict["PlayerPartySize"]=_dict.get("PlayerPartySize")
        json_dict["SessionCheckType"]=_dict.get("SessionCheckType")
        json_dict["TotalValue"]=_dict.get("TotalValue")
        return {"SessionCondition": json_dict}

if not hasattr(SessionCondition_base, "generateBaseDict"):
    SessionCondition_base.generateBaseDict = generateEmptyDict
