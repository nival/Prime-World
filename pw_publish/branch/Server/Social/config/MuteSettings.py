# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from MuteSettings_base import *

class MuteSettings(RefCounted, Identified, ChangeHandler, BaseObject, MuteSettings_base):
    _changeFields = {
        "MUTE_BIG_CONTEXT_MENU_TOOLTIP":1,
        "MUTE_BIG_HOURS":1,
        "MUTE_FOREVER_CONTEXT_MENU_TOOLTIP":1,
        "MUTE_SMALL_CONTEXT_MENU_TOOLTIP":1,
        "MUTE_SMALL_HOURS":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["MUTE_BIG_CONTEXT_MENU_TOOLTIP"] = "Mute for 8h"
        _dict["MUTE_BIG_HOURS"] = 8
        _dict["MUTE_FOREVER_CONTEXT_MENU_TOOLTIP"] = "Mute forever"
        _dict["MUTE_SMALL_CONTEXT_MENU_TOOLTIP"] = "Mute for 1h"
        _dict["MUTE_SMALL_HOURS"] = 1
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
        json_dict = MuteSettings_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["MUTE_BIG_CONTEXT_MENU_TOOLTIP"]=_dict.get("MUTE_BIG_CONTEXT_MENU_TOOLTIP")
        json_dict["MUTE_BIG_HOURS"]=_dict.get("MUTE_BIG_HOURS")
        json_dict["MUTE_FOREVER_CONTEXT_MENU_TOOLTIP"]=_dict.get("MUTE_FOREVER_CONTEXT_MENU_TOOLTIP")
        json_dict["MUTE_SMALL_CONTEXT_MENU_TOOLTIP"]=_dict.get("MUTE_SMALL_CONTEXT_MENU_TOOLTIP")
        json_dict["MUTE_SMALL_HOURS"]=_dict.get("MUTE_SMALL_HOURS")
        return {"MuteSettings": json_dict}

if not hasattr(MuteSettings_base, "generateBaseDict"):
    MuteSettings_base.generateBaseDict = generateEmptyDict
