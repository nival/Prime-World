# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import GuildMember

from GuildTalent_base import *

class GuildTalent(RefCounted, Identified, ChangeHandler, BaseObject, GuildTalent_base):
    _changeFields = {
        "HeroClassId":1,
        "Holder":1,
        "Owner":1,
        "PersistentId":1,
        "Points":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["HeroClassId"] = 0
        _dict["Holder"] = Ref(modeldata, modeldata.GuildMemberKeeper, path, "Holder")
        _dict["Owner"] = Ref(modeldata, modeldata.GuildMemberKeeper, path, "Owner")
        _dict["PersistentId"] = 0
        _dict["Points"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        ###self.Holder.init(self._modeldata.GuildMemberKeeper, self.path, self._modeldata, "Holder")
        ###self.Owner.init(self._modeldata.GuildMemberKeeper, self.path, self._modeldata, "Owner")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        ###self.Holder.init(self._modeldata.GuildMemberKeeper, self.path, self._modeldata, "Holder")
        ###self.Owner.init(self._modeldata.GuildMemberKeeper, self.path, self._modeldata, "Owner")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Holder.init(self._modeldata.GuildMemberKeeper, self.path, self._modeldata, "Holder")
        self.Owner.init(self._modeldata.GuildMemberKeeper, self.path, self._modeldata, "Owner")

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Holder.deleteByID(id)
            self.Owner.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name == "Holder":
            self.__dict__["Holder"].set(val)
            return
        if name == "Owner":
            self.__dict__["Owner"].set(val)
            return
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = GuildTalent_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["HeroClassId"]=_dict.get("HeroClassId")
        json_dict["Holder"]=_dict.get("Holder").getJsonDict()
        json_dict["Owner"]=_dict.get("Owner").getJsonDict()
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["Points"]=_dict.get("Points")
        return {"GuildTalent": json_dict}

if not hasattr(GuildTalent_base, "generateBaseDict"):
    GuildTalent_base.generateBaseDict = generateEmptyDict
