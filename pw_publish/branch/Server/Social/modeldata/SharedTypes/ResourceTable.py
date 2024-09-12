# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from ResourceTable_base import *

class ResourceTable(RefCounted, Identified, ChangeHandler, BaseObject, ResourceTable_base):
    _changeFields = {
        "Currencies":1,
        "CWPoints_Clan":1,
        "CWPoints_Player":1,
        "Gold":1,
        "Perl":1,
        "Population":1,
        "RedPerl":1,
        "Resource1":1,
        "Resource1_Rare":1,
        "Resource2":1,
        "Resource2_Rare":1,
        "Resource3":1,
        "Resource3_Rare":1,
        "Shard":1,
        "Silver":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Currencies"] = SimpleDict(modeldata)
        _dict["CWPoints_Clan"] = 0
        _dict["CWPoints_Player"] = 0
        _dict["Gold"] = 0
        _dict["Perl"] = 0
        _dict["Population"] = 0
        _dict["RedPerl"] = 0
        _dict["Resource1"] = 0
        _dict["Resource1_Rare"] = 0
        _dict["Resource2"] = 0
        _dict["Resource2_Rare"] = 0
        _dict["Resource3"] = 0
        _dict["Resource3_Rare"] = 0
        _dict["Shard"] = 0
        _dict["Silver"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"Currencies",None ):
            self.__dict__["Currencies"] = SimpleDict(self._modeldata)
        self.Currencies.init(self.path + u"/Currencies", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"Currencies",None ):
            self.__dict__["Currencies"] = SimpleDict(self._modeldata)
        self.Currencies.init(self.path + u"/Currencies", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Currencies.init(self.path + u"/Currencies", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Currencies.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = ResourceTable_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Currencies"]=_dict.get("Currencies").getJsonDict()
        json_dict["CWPoints_Clan"]=_dict.get("CWPoints_Clan")
        json_dict["CWPoints_Player"]=_dict.get("CWPoints_Player")
        json_dict["Gold"]=_dict.get("Gold")
        json_dict["Perl"]=_dict.get("Perl")
        json_dict["Population"]=_dict.get("Population")
        json_dict["RedPerl"]=_dict.get("RedPerl")
        json_dict["Resource1"]=_dict.get("Resource1")
        json_dict["Resource1_Rare"]=_dict.get("Resource1_Rare")
        json_dict["Resource2"]=_dict.get("Resource2")
        json_dict["Resource2_Rare"]=_dict.get("Resource2_Rare")
        json_dict["Resource3"]=_dict.get("Resource3")
        json_dict["Resource3_Rare"]=_dict.get("Resource3_Rare")
        json_dict["Shard"]=_dict.get("Shard")
        json_dict["Silver"]=_dict.get("Silver")
        return {"ResourceTable": json_dict}

if not hasattr(ResourceTable_base, "generateBaseDict"):
    ResourceTable_base.generateBaseDict = generateEmptyDict
