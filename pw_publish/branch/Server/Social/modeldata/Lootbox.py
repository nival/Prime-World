# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import LootboxReward

from Lootbox_base import *

class Lootbox(RefCounted, Identified, ChangeHandler, BaseObject, Lootbox_base):
    _changeFields = {
        "OpenAfterReceive":1,
        "PersistentId":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["OpenAfterReceive"] = False
        _dict["PersistentId"] = 0
        _dict["Reward"] = LootboxReward.LootboxReward(modeldata, None, "")
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.Reward.setPath(self.path + u"/Reward")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.Reward.setPath(self.path + u"/Reward")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Reward.setPath( self.path + u"/Reward" )

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Reward.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = Lootbox_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["OpenAfterReceive"]=_dict.get("OpenAfterReceive")
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["Reward"] = _dict.get("Reward").generateJsonDict()
        return {"Lootbox": json_dict}

if not hasattr(Lootbox_base, "generateBaseDict"):
    Lootbox_base.generateBaseDict = generateEmptyDict
