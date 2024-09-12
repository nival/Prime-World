# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from DonateEventReward_base import *

class DonateEventReward(RefCounted, Identified, ChangeHandler, BaseObject, DonateEventReward_base):
    _changeFields = {
        "Lootboxes":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Lootboxes"] = SimpleList(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"Lootboxes",None ):
            self.__dict__["Lootboxes"] = SimpleList(self._modeldata)
        self.Lootboxes.init(self.path + u"/Lootboxes", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"Lootboxes",None ):
            self.__dict__["Lootboxes"] = SimpleList(self._modeldata)
        self.Lootboxes.init(self.path + u"/Lootboxes", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Lootboxes.init(self.path + u"/Lootboxes", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Lootboxes.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = DonateEventReward_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Lootboxes"]=_dict.get("Lootboxes").getJsonDict()
        return {"DonateEventReward": json_dict}

if not hasattr(DonateEventReward_base, "generateBaseDict"):
    DonateEventReward_base.generateBaseDict = generateEmptyDict
