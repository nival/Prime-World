# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import FriendMMInfo

from Friend_base import *

class Friend(RefCounted, Identified, ChangeHandler, BaseObject, Friend_base):
    _changeFields = {
        "fame":1,
        "fraction":1,
        "friendRelation":1,
        "gender":1,
        "guildshortname":1,
        "InMatchmaking":1,
        "IsMuted":1,
        "lastLoginTime":1,
        "lastLogoutTime":1,
        "nickName":1,
        "online":1,
        "person_uid":1,
        "photoUrl":1,
        "Status":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["fame"] = 0
        _dict["fraction"] = 2
        _dict["friendRelation"] = 0
        _dict["gender"] = 0
        _dict["guildshortname"] = ""
        _dict["InMatchmaking"] = False
        _dict["IsMuted"] = False
        _dict["lastLoginTime"] = 0
        _dict["lastLogoutTime"] = 0
        _dict["mmInfo"] = FriendMMInfo.FriendMMInfo(modeldata, None, "")
        _dict["nickName"] = ""
        _dict["online"] = False
        _dict["person_uid"] = 0
        _dict["photoUrl"] = ""
        _dict["Status"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.mmInfo.setPath(self.path + u"/mmInfo")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.mmInfo.setPath(self.path + u"/mmInfo")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.mmInfo.setPath( self.path + u"/mmInfo" )

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.mmInfo.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = Friend_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["fame"]=_dict.get("fame")
        json_dict["fraction"]=_dict.get("fraction")
        json_dict["friendRelation"]=_dict.get("friendRelation")
        json_dict["gender"]=_dict.get("gender")
        json_dict["guildshortname"]=_dict.get("guildshortname")
        json_dict["InMatchmaking"]=_dict.get("InMatchmaking")
        json_dict["IsMuted"]=_dict.get("IsMuted")
        json_dict["lastLoginTime"]=_dict.get("lastLoginTime")
        json_dict["lastLogoutTime"]=_dict.get("lastLogoutTime")
        json_dict["mmInfo"] = _dict.get("mmInfo").generateJsonDict()
        json_dict["nickName"]=_dict.get("nickName")
        json_dict["online"]=_dict.get("online")
        json_dict["person_uid"]=_dict.get("person_uid")
        json_dict["photoUrl"]=_dict.get("photoUrl")
        json_dict["Status"]=_dict.get("Status")
        return {"Friend": json_dict}

if not hasattr(Friend_base, "generateBaseDict"):
    Friend_base.generateBaseDict = generateEmptyDict
