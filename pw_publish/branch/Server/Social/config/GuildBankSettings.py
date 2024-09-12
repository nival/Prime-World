# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from GuildBankSettings_base import *

class GuildBankSettings(RefCounted, Identified, ChangeHandler, BaseObject, GuildBankSettings_base):
    _changeFields = {
        "GUILD_BANK_ADD_LIMIT":1,
        "GUILD_BANK_HISTORY_TIME":1,
        "GUILD_BANK_TAKE_LIMIT":1,
        "INIT_GUILD_BANK_SLOTS":1,
        "IS_GUILD_BANK_ACTIVE":1,
        "MAX_GUILD_TALENTS_IN_SET":1,
        "MIN_GUILD_LEVEL":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["GUILD_BANK_ADD_LIMIT"] = 3
        _dict["GUILD_BANK_HISTORY_TIME"] = 604800
        _dict["GUILD_BANK_TAKE_LIMIT"] = 1
        _dict["INIT_GUILD_BANK_SLOTS"] = 50
        _dict["IS_GUILD_BANK_ACTIVE"] = False
        _dict["MAX_GUILD_TALENTS_IN_SET"] = 2
        _dict["MIN_GUILD_LEVEL"] = 20
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
        json_dict = GuildBankSettings_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["GUILD_BANK_ADD_LIMIT"]=_dict.get("GUILD_BANK_ADD_LIMIT")
        json_dict["GUILD_BANK_HISTORY_TIME"]=_dict.get("GUILD_BANK_HISTORY_TIME")
        json_dict["GUILD_BANK_TAKE_LIMIT"]=_dict.get("GUILD_BANK_TAKE_LIMIT")
        json_dict["INIT_GUILD_BANK_SLOTS"]=_dict.get("INIT_GUILD_BANK_SLOTS")
        json_dict["IS_GUILD_BANK_ACTIVE"]=_dict.get("IS_GUILD_BANK_ACTIVE")
        json_dict["MAX_GUILD_TALENTS_IN_SET"]=_dict.get("MAX_GUILD_TALENTS_IN_SET")
        json_dict["MIN_GUILD_LEVEL"]=_dict.get("MIN_GUILD_LEVEL")
        return {"GuildBankSettings": json_dict}

if not hasattr(GuildBankSettings_base, "generateBaseDict"):
    GuildBankSettings_base.generateBaseDict = generateEmptyDict
