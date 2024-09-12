# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from LordRatings_base import *

class LordRatings(RefCounted, Identified, ChangeHandler, BaseObject, LordRatings_base):
    _changeFields = {
        "LastRecalcPlayerRatingTime":1,
        "LordPublicRating":1,
        "LordRating":1,
        "MaxPRHero":1,
        "MaxPRHeroLastPlayed":1,
        "MaxRank":1,
        "NumberOfWinsForPR":1,
        "PlayerRatings":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["LastRecalcPlayerRatingTime"] = 0
        _dict["LordPublicRating"] = 0.0
        _dict["LordRating"] = 0.0
        _dict["MaxPRHero"] = 0
        _dict["MaxPRHeroLastPlayed"] = 0
        _dict["MaxRank"] = 0
        _dict["NumberOfWinsForPR"] = 0
        _dict["PlayerRatings"] = SimpleList(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"PlayerRatings",None ):
            self.__dict__["PlayerRatings"] = SimpleList(self._modeldata)
        self.PlayerRatings.init(self.path + u"/PlayerRatings", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"PlayerRatings",None ):
            self.__dict__["PlayerRatings"] = SimpleList(self._modeldata)
        self.PlayerRatings.init(self.path + u"/PlayerRatings", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.PlayerRatings.init(self.path + u"/PlayerRatings", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.PlayerRatings.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = LordRatings_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["LastRecalcPlayerRatingTime"]=_dict.get("LastRecalcPlayerRatingTime")
        json_dict["LordPublicRating"]=_dict.get("LordPublicRating")
        json_dict["LordRating"]=_dict.get("LordRating")
        json_dict["MaxPRHero"]=_dict.get("MaxPRHero")
        json_dict["MaxPRHeroLastPlayed"]=_dict.get("MaxPRHeroLastPlayed")
        json_dict["MaxRank"]=_dict.get("MaxRank")
        json_dict["NumberOfWinsForPR"]=_dict.get("NumberOfWinsForPR")
        json_dict["PlayerRatings"]=_dict.get("PlayerRatings").getJsonDict()
        return {"LordRatings": json_dict}

if not hasattr(LordRatings_base, "generateBaseDict"):
    LordRatings_base.generateBaseDict = generateEmptyDict
