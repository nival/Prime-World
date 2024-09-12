# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from TournamentTicket_base import *

class TournamentTicket(RefCounted, Identified, ChangeHandler, BaseObject, TournamentTicket_base):
    _changeFields = {
        "GameDurations":1,
        "IsSynchronized":1,
        "LastGameTime":1,
        "Losses":1,
        "MissedGames":1,
        "SessionInfo":1,
        "State":1,
        "TicketBoughtType":1,
        "TicketId":1,
        "TicketPriseState":1,
        "UserAuid":1,
        "Wins":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["GameDurations"] = SimpleList(modeldata)
        _dict["IsSynchronized"] = True
        _dict["LastGameTime"] = 0
        _dict["Losses"] = 0
        _dict["MissedGames"] = 0
        _dict["SessionInfo"] = SimpleList(modeldata)
        _dict["State"] = 0
        _dict["TicketBoughtType"] = 0
        _dict["TicketId"] = ""
        _dict["TicketPriseState"] = 0
        _dict["UserAuid"] = 0
        _dict["Wins"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"GameDurations",None ):
            self.__dict__["GameDurations"] = SimpleList(self._modeldata)
        self.GameDurations.init(self.path + u"/GameDurations", self._modeldata)
        if not getattr(self,"SessionInfo",None ):
            self.__dict__["SessionInfo"] = SimpleList(self._modeldata)
        self.SessionInfo.init(self.path + u"/SessionInfo", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"GameDurations",None ):
            self.__dict__["GameDurations"] = SimpleList(self._modeldata)
        self.GameDurations.init(self.path + u"/GameDurations", self._modeldata)
        if not getattr(self,"SessionInfo",None ):
            self.__dict__["SessionInfo"] = SimpleList(self._modeldata)
        self.SessionInfo.init(self.path + u"/SessionInfo", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.GameDurations.init(self.path + u"/GameDurations", self._modeldata)
        self.SessionInfo.init(self.path + u"/SessionInfo", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.GameDurations.deleteByID(id)
            self.SessionInfo.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = TournamentTicket_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["GameDurations"]=_dict.get("GameDurations").getJsonDict()
        json_dict["IsSynchronized"]=_dict.get("IsSynchronized")
        json_dict["LastGameTime"]=_dict.get("LastGameTime")
        json_dict["Losses"]=_dict.get("Losses")
        json_dict["MissedGames"]=_dict.get("MissedGames")
        json_dict["SessionInfo"]=_dict.get("SessionInfo").getJsonDict()
        json_dict["State"]=_dict.get("State")
        json_dict["TicketBoughtType"]=_dict.get("TicketBoughtType")
        json_dict["TicketId"]=_dict.get("TicketId")
        json_dict["TicketPriseState"]=_dict.get("TicketPriseState")
        json_dict["UserAuid"]=_dict.get("UserAuid")
        json_dict["Wins"]=_dict.get("Wins")
        return {"TournamentTicket": json_dict}

if not hasattr(TournamentTicket_base, "generateBaseDict"):
    TournamentTicket_base.generateBaseDict = generateEmptyDict
