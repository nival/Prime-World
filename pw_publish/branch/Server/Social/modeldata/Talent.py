# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import Hero
import GuildBankInfo

from Talent_base import *

class Talent(RefCounted, Identified, ChangeHandler, BaseObject, Talent_base):
    _changeFields = {
        "defaultForHero":1,
        "GuildBankInfo":1,
        "IsNew":1,
        "Owner":1,
        "ParentTalentSets":1,
        "PersistentId":1,
        "Points":1,
        "Soulbound":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["defaultForHero"] = Ref(modeldata, modeldata.HeroesKeeper, path, "defaultForHero")
        _dict["GuildBankInfo"] = Ref(modeldata, modeldata.GuildBankInfoKeeper, path, "GuildBankInfo")
        _dict["IsNew"] = False
        _dict["Owner"] = Ref(modeldata, modeldata.HeroesKeeper, path, "Owner")
        _dict["ParentTalentSets"] = SimpleDict(modeldata)
        _dict["PersistentId"] = 0
        _dict["Points"] = 0
        _dict["Soulbound"] = Ref(modeldata, modeldata.HeroesKeeper, path, "Soulbound")
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        ###self.defaultForHero.init(self._modeldata.HeroesKeeper, self.path, self._modeldata, "defaultForHero")
        ###self.GuildBankInfo.init(self._modeldata.GuildBankInfoKeeper, self.path, self._modeldata, "GuildBankInfo")
        ###self.Owner.init(self._modeldata.HeroesKeeper, self.path, self._modeldata, "Owner")
        if not getattr(self,"ParentTalentSets",None ):
            self.__dict__["ParentTalentSets"] = SimpleDict(self._modeldata)
        self.ParentTalentSets.init(self.path + u"/ParentTalentSets", self._modeldata)
        ###self.Soulbound.init(self._modeldata.HeroesKeeper, self.path, self._modeldata, "Soulbound")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        ###self.defaultForHero.init(self._modeldata.HeroesKeeper, self.path, self._modeldata, "defaultForHero")
        ###self.GuildBankInfo.init(self._modeldata.GuildBankInfoKeeper, self.path, self._modeldata, "GuildBankInfo")
        ###self.Owner.init(self._modeldata.HeroesKeeper, self.path, self._modeldata, "Owner")
        if not getattr(self,"ParentTalentSets",None ):
            self.__dict__["ParentTalentSets"] = SimpleDict(self._modeldata)
        self.ParentTalentSets.init(self.path + u"/ParentTalentSets", self._modeldata)
        ###self.Soulbound.init(self._modeldata.HeroesKeeper, self.path, self._modeldata, "Soulbound")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.defaultForHero.init(self._modeldata.HeroesKeeper, self.path, self._modeldata, "defaultForHero")
        self.GuildBankInfo.init(self._modeldata.GuildBankInfoKeeper, self.path, self._modeldata, "GuildBankInfo")
        self.Owner.init(self._modeldata.HeroesKeeper, self.path, self._modeldata, "Owner")
        self.ParentTalentSets.init(self.path + u"/ParentTalentSets", self._modeldata)
        self.Soulbound.init(self._modeldata.HeroesKeeper, self.path, self._modeldata, "Soulbound")

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.defaultForHero.deleteByID(id)
            self.GuildBankInfo.deleteByID(id)
            self.Owner.deleteByID(id)
            self.ParentTalentSets.deleteByID(id)
            self.Soulbound.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name == "defaultForHero":
            self.__dict__["defaultForHero"].set(val)
            return
        if name == "GuildBankInfo":
            self.__dict__["GuildBankInfo"].set(val)
            return
        if name == "Owner":
            self.__dict__["Owner"].set(val)
            return
        if name == "Soulbound":
            self.__dict__["Soulbound"].set(val)
            return
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = Talent_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["defaultForHero"]=_dict.get("defaultForHero").getJsonDict()
        json_dict["GuildBankInfo"]=_dict.get("GuildBankInfo").getJsonDict()
        json_dict["IsNew"]=_dict.get("IsNew")
        json_dict["Owner"]=_dict.get("Owner").getJsonDict()
        json_dict["ParentTalentSets"]=_dict.get("ParentTalentSets").getJsonDict()
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["Points"]=_dict.get("Points")
        json_dict["Soulbound"]=_dict.get("Soulbound").getJsonDict()
        return {"Talent": json_dict}

if not hasattr(Talent_base, "generateBaseDict"):
    Talent_base.generateBaseDict = generateEmptyDict
