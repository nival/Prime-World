# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from HeroStats_base import *

class HeroStats(RefCounted, Identified, ChangeHandler, BaseObject, HeroStats_base):
    _changeFields = {
        "Agility":1,
        "Cunning":1,
        "Fortitude":1,
        "Health":1,
        "Intellect":1,
        "Mana":1,
        "StatPoints":1,
        "Strength":1,
        "Will":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Agility"] = 0.0
        _dict["Cunning"] = 0.0
        _dict["Fortitude"] = 0.0
        _dict["Health"] = 0.0
        _dict["Intellect"] = 0.0
        _dict["Mana"] = 0.0
        _dict["StatPoints"] = 0
        _dict["Strength"] = 0.0
        _dict["Will"] = 0.0
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
        json_dict = HeroStats_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Agility"]=_dict.get("Agility")
        json_dict["Cunning"]=_dict.get("Cunning")
        json_dict["Fortitude"]=_dict.get("Fortitude")
        json_dict["Health"]=_dict.get("Health")
        json_dict["Intellect"]=_dict.get("Intellect")
        json_dict["Mana"]=_dict.get("Mana")
        json_dict["StatPoints"]=_dict.get("StatPoints")
        json_dict["Strength"]=_dict.get("Strength")
        json_dict["Will"]=_dict.get("Will")
        return {"HeroStats": json_dict}

if not hasattr(HeroStats_base, "generateBaseDict"):
    HeroStats_base.generateBaseDict = generateEmptyDict
