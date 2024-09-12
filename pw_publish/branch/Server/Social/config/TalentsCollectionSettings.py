# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from TalentsCollectionSettings_base import *

class TalentsCollectionSettings(RefCounted, Identified, ChangeHandler, BaseObject, TalentsCollectionSettings_base):
    _changeFields = {
        "TALENTS_COLLECTION_DISABLED":1,
        "TALENTS_QUEST_DISABLED":1,
        "TALENTS_QUEST_LIMIT":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["TALENTS_COLLECTION_DISABLED"] = False
        _dict["TALENTS_QUEST_DISABLED"] = False
        _dict["TALENTS_QUEST_LIMIT"] = 3
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
        json_dict = TalentsCollectionSettings_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["TALENTS_COLLECTION_DISABLED"]=_dict.get("TALENTS_COLLECTION_DISABLED")
        json_dict["TALENTS_QUEST_DISABLED"]=_dict.get("TALENTS_QUEST_DISABLED")
        json_dict["TALENTS_QUEST_LIMIT"]=_dict.get("TALENTS_QUEST_LIMIT")
        return {"TalentsCollectionSettings": json_dict}

if not hasattr(TalentsCollectionSettings_base, "generateBaseDict"):
    TalentsCollectionSettings_base.generateBaseDict = generateEmptyDict
