# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from SeasonAwards_base import *

class SeasonAwards(RefCounted, Identified, ChangeHandler, BaseObject, SeasonAwards_base):
    _changeFields = {
        "Flag":1,
        "IsShowedToUser":1,
        "Lootboxes":1,
        "RedPerls":1,
        "SeasonId":1,
        "Skin":1,
        "Talents":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Flag"] = ""
        _dict["IsShowedToUser"] = False
        _dict["Lootboxes"] = SimpleList(modeldata)
        _dict["RedPerls"] = 0
        _dict["SeasonId"] = 0
        _dict["Skin"] = 0
        _dict["Talents"] = SimpleList(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"Lootboxes",None ):
            self.__dict__["Lootboxes"] = SimpleList(self._modeldata)
        self.Lootboxes.init(self.path + u"/Lootboxes", self._modeldata)
        if not getattr(self,"Talents",None ):
            self.__dict__["Talents"] = SimpleList(self._modeldata)
        self.Talents.init(self.path + u"/Talents", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"Lootboxes",None ):
            self.__dict__["Lootboxes"] = SimpleList(self._modeldata)
        self.Lootboxes.init(self.path + u"/Lootboxes", self._modeldata)
        if not getattr(self,"Talents",None ):
            self.__dict__["Talents"] = SimpleList(self._modeldata)
        self.Talents.init(self.path + u"/Talents", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Lootboxes.init(self.path + u"/Lootboxes", self._modeldata)
        self.Talents.init(self.path + u"/Talents", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Lootboxes.deleteByID(id)
            self.Talents.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = SeasonAwards_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Flag"]=_dict.get("Flag")
        json_dict["IsShowedToUser"]=_dict.get("IsShowedToUser")
        json_dict["Lootboxes"]=_dict.get("Lootboxes").getJsonDict()
        json_dict["RedPerls"]=_dict.get("RedPerls")
        json_dict["SeasonId"]=_dict.get("SeasonId")
        json_dict["Skin"]=_dict.get("Skin")
        json_dict["Talents"]=_dict.get("Talents").getJsonDict()
        return {"SeasonAwards": json_dict}

if not hasattr(SeasonAwards_base, "generateBaseDict"):
    SeasonAwards_base.generateBaseDict = generateEmptyDict
