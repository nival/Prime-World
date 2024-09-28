# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from SeasonInfo_base import *

class SeasonInfo(RefCounted, Identified, ChangeHandler, BaseObject, SeasonInfo_base):
    _changeFields = {
        "BestLeaguePlace":1,
        "CurLeaguePlace":1,
        "LeagueIndex":1,
        "NearPlaces":1,
        "SeasonId":1,
        "SeasonRating":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["BestLeaguePlace"] = 0
        _dict["CurLeaguePlace"] = 0
        _dict["LeagueIndex"] = 0
        _dict["NearPlaces"] = SimpleList(modeldata)
        _dict["SeasonId"] = 0
        _dict["SeasonRating"] = 0.0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"NearPlaces",None ):
            self.__dict__["NearPlaces"] = SimpleList(self._modeldata)
        self.NearPlaces.init(self.path + u"/NearPlaces", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"NearPlaces",None ):
            self.__dict__["NearPlaces"] = SimpleList(self._modeldata)
        self.NearPlaces.init(self.path + u"/NearPlaces", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.NearPlaces.init(self.path + u"/NearPlaces", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.NearPlaces.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = SeasonInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["BestLeaguePlace"]=_dict.get("BestLeaguePlace")
        json_dict["CurLeaguePlace"]=_dict.get("CurLeaguePlace")
        json_dict["LeagueIndex"]=_dict.get("LeagueIndex")
        json_dict["NearPlaces"]=_dict.get("NearPlaces").getJsonDict()
        json_dict["SeasonId"]=_dict.get("SeasonId")
        json_dict["SeasonRating"]=_dict.get("SeasonRating")
        return {"SeasonInfo": json_dict}

if not hasattr(SeasonInfo_base, "generateBaseDict"):
    SeasonInfo_base.generateBaseDict = generateEmptyDict
