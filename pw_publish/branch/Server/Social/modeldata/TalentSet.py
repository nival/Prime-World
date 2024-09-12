# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import HeroStats

from TalentSet_base import *

class TalentSet(RefCounted, Identified, ChangeHandler, BaseObject, TalentSet_base):
    _changeFields = {
        "ActionBar":1,
        "Force":1,
        "InstaCast":1,
        "IsActiveTalentSet":1,
        "Talents":1,
        "TalentSetCrc":1,
        "TalentSetName":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["ActionBar"] = SimpleDict(modeldata)
        _dict["Force"] = 0.0
        _dict["GuildStats"] = HeroStats.HeroStats(modeldata, None, "")
        _dict["InstaCast"] = SimpleDict(modeldata)
        _dict["IsActiveTalentSet"] = False
        _dict["Stats"] = HeroStats.HeroStats(modeldata, None, "")
        _dict["Talents"] = SimpleDict(modeldata)
        _dict["TalentSetCrc"] = 0
        _dict["TalentSetName"] = ""
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"ActionBar",None ):
            self.__dict__["ActionBar"] = SimpleDict(self._modeldata)
        self.ActionBar.init(self.path + u"/ActionBar", self._modeldata)
        self.GuildStats.setPath(self.path + u"/GuildStats")
        if not getattr(self,"InstaCast",None ):
            self.__dict__["InstaCast"] = SimpleDict(self._modeldata)
        self.InstaCast.init(self.path + u"/InstaCast", self._modeldata)
        self.Stats.setPath(self.path + u"/Stats")
        if not getattr(self,"Talents",None ):
            self.__dict__["Talents"] = SimpleDict(self._modeldata)
        self.Talents.init(self.path + u"/Talents", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"ActionBar",None ):
            self.__dict__["ActionBar"] = SimpleDict(self._modeldata)
        self.ActionBar.init(self.path + u"/ActionBar", self._modeldata)
        self.GuildStats.setPath(self.path + u"/GuildStats")
        if not getattr(self,"InstaCast",None ):
            self.__dict__["InstaCast"] = SimpleDict(self._modeldata)
        self.InstaCast.init(self.path + u"/InstaCast", self._modeldata)
        self.Stats.setPath(self.path + u"/Stats")
        if not getattr(self,"Talents",None ):
            self.__dict__["Talents"] = SimpleDict(self._modeldata)
        self.Talents.init(self.path + u"/Talents", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.ActionBar.init(self.path + u"/ActionBar", self._modeldata)
        self.GuildStats.setPath( self.path + u"/GuildStats" )
        self.InstaCast.init(self.path + u"/InstaCast", self._modeldata)
        self.Stats.setPath( self.path + u"/Stats" )
        self.Talents.init(self.path + u"/Talents", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.ActionBar.deleteByID(id)
            self.GuildStats.deleteByID(id)
            self.InstaCast.deleteByID(id)
            self.Stats.deleteByID(id)
            self.Talents.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = TalentSet_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["ActionBar"]=_dict.get("ActionBar").getJsonDict()
        json_dict["Force"]=_dict.get("Force")
        json_dict["GuildStats"] = _dict.get("GuildStats").generateJsonDict()
        json_dict["InstaCast"]=_dict.get("InstaCast").getJsonDict()
        json_dict["IsActiveTalentSet"]=_dict.get("IsActiveTalentSet")
        json_dict["Stats"] = _dict.get("Stats").generateJsonDict()
        json_dict["Talents"]=_dict.get("Talents").getJsonDict()
        json_dict["TalentSetCrc"]=_dict.get("TalentSetCrc")
        json_dict["TalentSetName"]=_dict.get("TalentSetName")
        return {"TalentSet": json_dict}

if not hasattr(TalentSet_base, "generateBaseDict"):
    TalentSet_base.generateBaseDict = generateEmptyDict
