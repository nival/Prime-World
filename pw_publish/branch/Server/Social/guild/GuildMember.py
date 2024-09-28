# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import MemberDayRating

from GuildMember_base import *

class GuildMember(RefCounted, Identified, ChangeHandler, BaseObject, GuildMember_base):
    _changeFields = {
        "AddedTalentsDailyCount":1,
        "DailyRating":1,
        "EventRating":1,
        "InvestedResources":1,
        "IsOfficer":1,
        "JoinTime":1,
        "Person":1,
        "PrevEventPlace":1,
        "TakenTalentsDailyCount":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["AddedTalentsDailyCount"] = 0
        _dict["DailyRating"] = 0.0
        _dict["EventRating"] = 0.0
        _dict["HeroRatings"] = Collection(modeldata)
        _dict["InvestedResources"] = 0
        _dict["IsOfficer"] = False
        _dict["JoinTime"] = 0
        _dict["Person"] = 0
        _dict["PrevEventPlace"] = 0
        _dict["TakenTalentsDailyCount"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"HeroRatings",None ):
            self.__dict__["HeroRatings"] = Collection(self._modeldata)
        self.HeroRatings.init(self._modeldata.MemberDayRatingKeeper, self.path + u"/HeroRatings", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"HeroRatings",None ):
            self.__dict__["HeroRatings"] = Collection(self._modeldata)
        self.HeroRatings.init(self._modeldata.MemberDayRatingKeeper, self.path + u"/HeroRatings", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.HeroRatings.init(self._modeldata.MemberDayRatingKeeper, self.path + u"/HeroRatings", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.HeroRatings.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = GuildMember_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["AddedTalentsDailyCount"]=_dict.get("AddedTalentsDailyCount")
        json_dict["DailyRating"]=_dict.get("DailyRating")
        json_dict["EventRating"]=_dict.get("EventRating")
        json_dict["HeroRatings"]=_dict.get("HeroRatings").getJsonDict()
        json_dict["InvestedResources"]=_dict.get("InvestedResources")
        json_dict["IsOfficer"]=_dict.get("IsOfficer")
        json_dict["JoinTime"]=_dict.get("JoinTime")
        json_dict["Person"]=_dict.get("Person")
        json_dict["PrevEventPlace"]=_dict.get("PrevEventPlace")
        json_dict["TakenTalentsDailyCount"]=_dict.get("TakenTalentsDailyCount")
        return {"GuildMember": json_dict}

if not hasattr(GuildMember_base, "generateBaseDict"):
    GuildMember_base.generateBaseDict = generateEmptyDict
