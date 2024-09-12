# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from GuildApplicantInfo_base import *

class GuildApplicantInfo(RefCounted, Identified, ChangeHandler, BaseObject, GuildApplicantInfo_base):
    _changeFields = {
        "Auid":1,
        "ExpireTime":1,
        "Fame":1,
        "MaxRating":1,
        "MaxRatingHeroes":1,
        "Message":1,
        "Nickname":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Auid"] = 0
        _dict["ExpireTime"] = 0
        _dict["Fame"] = 0
        _dict["MaxRating"] = 0
        _dict["MaxRatingHeroes"] = SimpleDict(modeldata)
        _dict["Message"] = ""
        _dict["Nickname"] = ""
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"MaxRatingHeroes",None ):
            self.__dict__["MaxRatingHeroes"] = SimpleDict(self._modeldata)
        self.MaxRatingHeroes.init(self.path + u"/MaxRatingHeroes", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"MaxRatingHeroes",None ):
            self.__dict__["MaxRatingHeroes"] = SimpleDict(self._modeldata)
        self.MaxRatingHeroes.init(self.path + u"/MaxRatingHeroes", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.MaxRatingHeroes.init(self.path + u"/MaxRatingHeroes", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.MaxRatingHeroes.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = GuildApplicantInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Auid"]=_dict.get("Auid")
        json_dict["ExpireTime"]=_dict.get("ExpireTime")
        json_dict["Fame"]=_dict.get("Fame")
        json_dict["MaxRating"]=_dict.get("MaxRating")
        json_dict["MaxRatingHeroes"]=_dict.get("MaxRatingHeroes").getJsonDict()
        json_dict["Message"]=_dict.get("Message")
        json_dict["Nickname"]=_dict.get("Nickname")
        return {"GuildApplicantInfo": json_dict}

if not hasattr(GuildApplicantInfo_base, "generateBaseDict"):
    GuildApplicantInfo_base.generateBaseDict = generateEmptyDict
