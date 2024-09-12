# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from LegendLeagueListEntity_base import *

class LegendLeagueListEntity(RefCounted, Identified, ChangeHandler, BaseObject, LegendLeagueListEntity_base):
    _changeFields = {
        "HeroId":1,
        "Nickname":1,
        "Place":1,
        "RatingPositionChange":1,
        "Uid":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["HeroId"] = 0
        _dict["Nickname"] = ""
        _dict["Place"] = 0
        _dict["RatingPositionChange"] = 0
        _dict["Uid"] = 0
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
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = LegendLeagueListEntity_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["HeroId"]=_dict.get("HeroId")
        json_dict["Nickname"]=_dict.get("Nickname")
        json_dict["Place"]=_dict.get("Place")
        json_dict["RatingPositionChange"]=_dict.get("RatingPositionChange")
        json_dict["Uid"]=_dict.get("Uid")
        return {"LegendLeagueListEntity": json_dict}

if not hasattr(LegendLeagueListEntity_base, "generateBaseDict"):
    LegendLeagueListEntity_base.generateBaseDict = generateEmptyDict
