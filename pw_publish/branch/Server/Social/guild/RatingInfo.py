# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from RatingInfo_base import *

class RatingInfo(RefCounted, Identified, ChangeHandler, BaseObject, RatingInfo_base):
    _changeFields = {
        "ClanWarBonus":1,
        "DailyRating":1,
        "PrevRating":1,
        "Rating":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["ClanWarBonus"] = 0.0
        _dict["DailyRating"] = 0.0
        _dict["PrevRating"] = 0.0
        _dict["Rating"] = 0.0
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
        json_dict = RatingInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["ClanWarBonus"]=_dict.get("ClanWarBonus")
        json_dict["DailyRating"]=_dict.get("DailyRating")
        json_dict["PrevRating"]=_dict.get("PrevRating")
        json_dict["Rating"]=_dict.get("Rating")
        return {"RatingInfo": json_dict}

if not hasattr(RatingInfo_base, "generateBaseDict"):
    RatingInfo_base.generateBaseDict = generateEmptyDict
