# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import Skin

from HeroSkins_base import *

class HeroSkins(RefCounted, Identified, ChangeHandler, BaseObject, HeroSkins_base):
    _changeFields = {
        "CurrentSkin":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["CurrentSkin"] = Ref(modeldata, modeldata.SkinsKeeper, path, "CurrentSkin")
        _dict["Skins"] = Set(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        ###self.CurrentSkin.init(self._modeldata.SkinsKeeper, self.path, self._modeldata, "CurrentSkin")
        if not getattr(self,"Skins",None ):
            self.__dict__["Skins"] = Set(self._modeldata)
        self.Skins.init(self._modeldata.SkinsKeeper, self.path + u"/Skins", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        ###self.CurrentSkin.init(self._modeldata.SkinsKeeper, self.path, self._modeldata, "CurrentSkin")
        if not getattr(self,"Skins",None ):
            self.__dict__["Skins"] = Set(self._modeldata)
        self.Skins.init(self._modeldata.SkinsKeeper, self.path + u"/Skins", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.CurrentSkin.init(self._modeldata.SkinsKeeper, self.path, self._modeldata, "CurrentSkin")
        self.Skins.init(self._modeldata.SkinsKeeper, self.path + u"/Skins", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.CurrentSkin.deleteByID(id)
            self.Skins.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name == "CurrentSkin":
            self.__dict__["CurrentSkin"].set(val)
            return
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = HeroSkins_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["CurrentSkin"]=_dict.get("CurrentSkin").getJsonDict()
        json_dict["Skins"]=_dict.get("Skins").getJsonDict()
        return {"HeroSkins": json_dict}

if not hasattr(HeroSkins_base, "generateBaseDict"):
    HeroSkins_base.generateBaseDict = generateEmptyDict
