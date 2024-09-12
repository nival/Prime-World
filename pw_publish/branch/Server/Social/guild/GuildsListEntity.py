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

from GuildsListEntity_base import *

class GuildsListEntity(RefCounted, Identified, ChangeHandler, BaseObject, GuildsListEntity_base):
    _changeFields = {
        "IsInSiege":1,
        "IsLocked":1,
        "ShortInfo":1,
        "SiegeEndTime":1,
        "SuzerainGuildAuid":1,
        "SuzerainGuildFullName":1,
        "SuzerainGuildShortName":1,
        "SuzerainIconChangesCount":1,
        "SuzerainRating":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["IsInSiege"] = False
        _dict["IsLocked"] = False
        _dict["ShortInfo"] = Ref(modeldata, modeldata.GuildShortInfoKeeper, path, "ShortInfo")
        _dict["SiegeEndTime"] = 0
        _dict["SuzerainGuildAuid"] = 0
        _dict["SuzerainGuildFullName"] = ""
        _dict["SuzerainGuildShortName"] = ""
        _dict["SuzerainIconChangesCount"] = 0
        _dict["SuzerainRating"] = 0
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
        json_dict = GuildsListEntity_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["IsInSiege"]=_dict.get("IsInSiege")
        json_dict["IsLocked"]=_dict.get("IsLocked")
        json_dict["ShortInfo"]=_dict.get("ShortInfo").getJsonDict()
        json_dict["SiegeEndTime"]=_dict.get("SiegeEndTime")
        json_dict["SuzerainGuildAuid"]=_dict.get("SuzerainGuildAuid")
        json_dict["SuzerainGuildFullName"]=_dict.get("SuzerainGuildFullName")
        json_dict["SuzerainGuildShortName"]=_dict.get("SuzerainGuildShortName")
        json_dict["SuzerainIconChangesCount"]=_dict.get("SuzerainIconChangesCount")
        json_dict["SuzerainRating"]=_dict.get("SuzerainRating")
        return {"GuildsListEntity": json_dict}

if not hasattr(GuildsListEntity_base, "generateBaseDict"):
    GuildsListEntity_base.generateBaseDict = generateEmptyDict
