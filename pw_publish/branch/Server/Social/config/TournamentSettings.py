# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from TournamentSettings_base import *

class TournamentSettings(RefCounted, Identified, ChangeHandler, BaseObject, TournamentSettings_base):
    _changeFields = {
        "CAN_SELL_TALENTS":1,
        "GOLDEN_PRISE_AMOUNT":1,
        "GOLDEN_TICKET_PRICE":1,
        "HOURS_FOR_MISS":1,
        "HOURS_FROM_LAST_PLAY":1,
        "INSTANT_PAYMENT_SIZE":1,
        "IS_ENEMY_PORTRAITS_DISABLED":1,
        "IS_TOURNAMENT_SERVER":1,
        "MAX_GAMES_TO_MISS":1,
        "SILVER_TICKET_PRICE":1,
        "TOURNAMENT_MAP_LIST":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["CAN_SELL_TALENTS"] = False
        _dict["GOLDEN_PRISE_AMOUNT"] = 25
        _dict["GOLDEN_TICKET_PRICE"] = 100
        _dict["HOURS_FOR_MISS"] = 30
        _dict["HOURS_FROM_LAST_PLAY"] = 54
        _dict["INSTANT_PAYMENT_SIZE"] = 500
        _dict["IS_ENEMY_PORTRAITS_DISABLED"] = False
        _dict["IS_TOURNAMENT_SERVER"] = False
        _dict["MAX_GAMES_TO_MISS"] = 1
        _dict["SILVER_TICKET_PRICE"] = 1000000
        _dict["TOURNAMENT_MAP_LIST"] = SimpleList(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"TOURNAMENT_MAP_LIST",None ):
            self.__dict__["TOURNAMENT_MAP_LIST"] = SimpleList(self._modeldata)
        self.TOURNAMENT_MAP_LIST.init(self.path + u"/TOURNAMENT_MAP_LIST", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"TOURNAMENT_MAP_LIST",None ):
            self.__dict__["TOURNAMENT_MAP_LIST"] = SimpleList(self._modeldata)
        self.TOURNAMENT_MAP_LIST.init(self.path + u"/TOURNAMENT_MAP_LIST", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.TOURNAMENT_MAP_LIST.init(self.path + u"/TOURNAMENT_MAP_LIST", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.TOURNAMENT_MAP_LIST.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = TournamentSettings_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["CAN_SELL_TALENTS"]=_dict.get("CAN_SELL_TALENTS")
        json_dict["GOLDEN_PRISE_AMOUNT"]=_dict.get("GOLDEN_PRISE_AMOUNT")
        json_dict["GOLDEN_TICKET_PRICE"]=_dict.get("GOLDEN_TICKET_PRICE")
        json_dict["HOURS_FOR_MISS"]=_dict.get("HOURS_FOR_MISS")
        json_dict["HOURS_FROM_LAST_PLAY"]=_dict.get("HOURS_FROM_LAST_PLAY")
        json_dict["INSTANT_PAYMENT_SIZE"]=_dict.get("INSTANT_PAYMENT_SIZE")
        json_dict["IS_ENEMY_PORTRAITS_DISABLED"]=_dict.get("IS_ENEMY_PORTRAITS_DISABLED")
        json_dict["IS_TOURNAMENT_SERVER"]=_dict.get("IS_TOURNAMENT_SERVER")
        json_dict["MAX_GAMES_TO_MISS"]=_dict.get("MAX_GAMES_TO_MISS")
        json_dict["SILVER_TICKET_PRICE"]=_dict.get("SILVER_TICKET_PRICE")
        json_dict["TOURNAMENT_MAP_LIST"]=_dict.get("TOURNAMENT_MAP_LIST").getJsonDict()
        return {"TournamentSettings": json_dict}

if not hasattr(TournamentSettings_base, "generateBaseDict"):
    TournamentSettings_base.generateBaseDict = generateEmptyDict
