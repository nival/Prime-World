# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from ForgeRoll_base import *

class ForgeRoll(RefCounted, Identified, ChangeHandler, BaseObject, ForgeRoll_base):
    _changeFields = {
        "TransmutationRandomSeed":1,
        "TransmutationTalentsProduced":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["TransmutationRandomSeed"] = 0
        _dict["TransmutationTalentsProduced"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass

    # вызывается после model.addNewName()
    def init_add(self):
        pass

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = ForgeRoll_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["TransmutationRandomSeed"]=_dict.get("TransmutationRandomSeed")
        json_dict["TransmutationTalentsProduced"]=_dict.get("TransmutationTalentsProduced")
        return {"ForgeRoll": json_dict}

if not hasattr(ForgeRoll_base, "generateBaseDict"):
    ForgeRoll_base.generateBaseDict = generateEmptyDict
