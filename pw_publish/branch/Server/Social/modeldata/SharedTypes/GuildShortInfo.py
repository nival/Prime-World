# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from GuildShortInfo_base import *

class GuildShortInfo(RefCounted, Identified, ChangeHandler, BaseObject, GuildShortInfo_base):
    _changeFields = {
        "GuildAuid":1,
        "GuildFullName":1,
        "GuildShortName":1,
        "IconChangesCount":1,
        "LastEventIndex":1,
        "Level":1,
        "Locale":1,
        "MembersCount":1,
        "Place":1,
        "PrevPlace":1,
        "PrevRating":1,
        "Rating":1,
        "RatingPositionChange":1,
        "ShopLevel":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["GuildAuid"] = 0
        _dict["GuildFullName"] = ""
        _dict["GuildShortName"] = ""
        _dict["IconChangesCount"] = 0
        _dict["LastEventIndex"] = 0
        _dict["Level"] = 0
        _dict["Locale"] = ""
        _dict["MembersCount"] = 0
        _dict["Place"] = 0
        _dict["PrevPlace"] = 0
        _dict["PrevRating"] = 0
        _dict["Rating"] = 0
        _dict["RatingPositionChange"] = 0
        _dict["ShopLevel"] = 0
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
        json_dict = GuildShortInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["GuildAuid"]=_dict.get("GuildAuid")
        json_dict["GuildFullName"]=_dict.get("GuildFullName")
        json_dict["GuildShortName"]=_dict.get("GuildShortName")
        json_dict["IconChangesCount"]=_dict.get("IconChangesCount")
        json_dict["LastEventIndex"]=_dict.get("LastEventIndex")
        json_dict["Level"]=_dict.get("Level")
        json_dict["Locale"]=_dict.get("Locale")
        json_dict["MembersCount"]=_dict.get("MembersCount")
        json_dict["Place"]=_dict.get("Place")
        json_dict["PrevPlace"]=_dict.get("PrevPlace")
        json_dict["PrevRating"]=_dict.get("PrevRating")
        json_dict["Rating"]=_dict.get("Rating")
        json_dict["RatingPositionChange"]=_dict.get("RatingPositionChange")
        json_dict["ShopLevel"]=_dict.get("ShopLevel")
        return {"GuildShortInfo": json_dict}

if not hasattr(GuildShortInfo_base, "generateBaseDict"):
    GuildShortInfo_base.generateBaseDict = generateEmptyDict
