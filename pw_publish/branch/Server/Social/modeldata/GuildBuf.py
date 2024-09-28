# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from GuildBuf_base import *

class GuildBuf(RefCounted, Identified, ChangeHandler, BaseObject, GuildBuf_base):
    _changeFields = {
        "DurationType":1,
        "ExpireTime":1,
        "GuildOnly":1,
        "IsEnabled":1,
        "PersistentId":1,
        "TransactionsLeft":1,
        "WillBeAppliedAfterBattle":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["DurationType"] = 0
        _dict["ExpireTime"] = 0
        _dict["GuildOnly"] = False
        _dict["IsEnabled"] = False
        _dict["PersistentId"] = 0
        _dict["TransactionsLeft"] = 0
        _dict["WillBeAppliedAfterBattle"] = False
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
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = GuildBuf_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["DurationType"]=_dict.get("DurationType")
        json_dict["ExpireTime"]=_dict.get("ExpireTime")
        json_dict["GuildOnly"]=_dict.get("GuildOnly")
        json_dict["IsEnabled"]=_dict.get("IsEnabled")
        json_dict["PersistentId"]=_dict.get("PersistentId")
        json_dict["TransactionsLeft"]=_dict.get("TransactionsLeft")
        json_dict["WillBeAppliedAfterBattle"]=_dict.get("WillBeAppliedAfterBattle")
        return {"GuildBuf": json_dict}

if not hasattr(GuildBuf_base, "generateBaseDict"):
    GuildBuf_base.generateBaseDict = generateEmptyDict
