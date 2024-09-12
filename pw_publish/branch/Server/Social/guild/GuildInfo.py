# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from GuildInfo_base import *

class GuildInfo(RefCounted, Identified, ChangeHandler, BaseObject, GuildInfo_base):
    _changeFields = {
        "AdditionalMembersCount":1,
        "BestPlace":1,
        "CountSuzerainInvites":1,
        "CountSuzerainInvitesTimeLimit":1,
        "CurrentEventId":1,
        "CWPoints_Clan":1,
        "FullName":1,
        "GMLockTime":1,
        "GuildFraction":1,
        "HasUltimateShop":1,
        "IconChangesCount":1,
        "MessageOfTheDay":1,
        "Place":1,
        "PlaceChange":1,
        "PrevPlace":1,
        "ShortName":1,
        "StartAutoRevolt":1,
        "TotalGuildsNumber":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["AdditionalMembersCount"] = 0
        _dict["BestPlace"] = 0
        _dict["CountSuzerainInvites"] = 0
        _dict["CountSuzerainInvitesTimeLimit"] = 0
        _dict["CurrentEventId"] = 0
        _dict["CWPoints_Clan"] = 0
        _dict["FullName"] = ""
        _dict["GMLockTime"] = 0
        _dict["GuildFraction"] = ""
        _dict["HasUltimateShop"] = False
        _dict["IconChangesCount"] = 0
        _dict["MessageOfTheDay"] = ""
        _dict["Place"] = 0
        _dict["PlaceChange"] = 0
        _dict["PrevPlace"] = 0
        _dict["ShortName"] = ""
        _dict["StartAutoRevolt"] = False
        _dict["TotalGuildsNumber"] = 0
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
        json_dict = GuildInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["AdditionalMembersCount"]=_dict.get("AdditionalMembersCount")
        json_dict["BestPlace"]=_dict.get("BestPlace")
        json_dict["CountSuzerainInvites"]=_dict.get("CountSuzerainInvites")
        json_dict["CountSuzerainInvitesTimeLimit"]=_dict.get("CountSuzerainInvitesTimeLimit")
        json_dict["CurrentEventId"]=_dict.get("CurrentEventId")
        json_dict["CWPoints_Clan"]=_dict.get("CWPoints_Clan")
        json_dict["FullName"]=_dict.get("FullName")
        json_dict["GMLockTime"]=_dict.get("GMLockTime")
        json_dict["GuildFraction"]=_dict.get("GuildFraction")
        json_dict["HasUltimateShop"]=_dict.get("HasUltimateShop")
        json_dict["IconChangesCount"]=_dict.get("IconChangesCount")
        json_dict["MessageOfTheDay"]=_dict.get("MessageOfTheDay")
        json_dict["Place"]=_dict.get("Place")
        json_dict["PlaceChange"]=_dict.get("PlaceChange")
        json_dict["PrevPlace"]=_dict.get("PrevPlace")
        json_dict["ShortName"]=_dict.get("ShortName")
        json_dict["StartAutoRevolt"]=_dict.get("StartAutoRevolt")
        json_dict["TotalGuildsNumber"]=_dict.get("TotalGuildsNumber")
        return {"GuildInfo": json_dict}

if not hasattr(GuildInfo_base, "generateBaseDict"):
    GuildInfo_base.generateBaseDict = generateEmptyDict
