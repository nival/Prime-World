# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import DonateEventReward

from DonateEventRange_base import *

class DonateEventRange(RefCounted, Identified, ChangeHandler, BaseObject, DonateEventRange_base):
    _changeFields = {
        "AmountFrom":1,
        "AmountTo":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["AmountFrom"] = 0
        _dict["AmountTo"] = 0
        _dict["Rewards"] = Set(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"Rewards",None ):
            self.__dict__["Rewards"] = Set(self._modeldata)
        self.Rewards.init(self._modeldata.DonateEventRewardKeeper, self.path + u"/Rewards", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"Rewards",None ):
            self.__dict__["Rewards"] = Set(self._modeldata)
        self.Rewards.init(self._modeldata.DonateEventRewardKeeper, self.path + u"/Rewards", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Rewards.init(self._modeldata.DonateEventRewardKeeper, self.path + u"/Rewards", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Rewards.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = DonateEventRange_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["AmountFrom"]=_dict.get("AmountFrom")
        json_dict["AmountTo"]=_dict.get("AmountTo")
        json_dict["Rewards"]=_dict.get("Rewards").getJsonDict()
        return {"DonateEventRange": json_dict}

if not hasattr(DonateEventRange_base, "generateBaseDict"):
    DonateEventRange_base.generateBaseDict = generateEmptyDict
