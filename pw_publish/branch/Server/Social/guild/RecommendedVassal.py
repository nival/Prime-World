# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import GuildShortInfo

from RecommendedVassal_base import *

class RecommendedVassal(RefCounted, Identified, ChangeHandler, BaseObject, RecommendedVassal_base):
    _changeFields = {
        "ApplicationSent":1,
        "HasSuzerain":1,
        "IsInSiege":1,
        "ShortInfo":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["ApplicationSent"] = False
        _dict["HasSuzerain"] = False
        _dict["IsInSiege"] = False
        _dict["ShortInfo"] = Ref(modeldata, modeldata.GuildShortInfoKeeper, path, "ShortInfo")
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        ###self.ShortInfo.init(self._modeldata.GuildShortInfoKeeper, self.path, self._modeldata, "ShortInfo")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        ###self.ShortInfo.init(self._modeldata.GuildShortInfoKeeper, self.path, self._modeldata, "ShortInfo")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.ShortInfo.init(self._modeldata.GuildShortInfoKeeper, self.path, self._modeldata, "ShortInfo")

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.ShortInfo.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name == "ShortInfo":
            self.__dict__["ShortInfo"].set(val)
            return
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = RecommendedVassal_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["ApplicationSent"]=_dict.get("ApplicationSent")
        json_dict["HasSuzerain"]=_dict.get("HasSuzerain")
        json_dict["IsInSiege"]=_dict.get("IsInSiege")
        json_dict["ShortInfo"]=_dict.get("ShortInfo").getJsonDict()
        return {"RecommendedVassal": json_dict}

if not hasattr(RecommendedVassal_base, "generateBaseDict"):
    RecommendedVassal_base.generateBaseDict = generateEmptyDict
