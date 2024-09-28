# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import SimpleFriend

from Friends_base import *

class Friends(RefCounted, Identified, ChangeHandler, BaseObject, Friends_base):
    _changeFields = {
        "Favorites":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Favorites"] = SimpleList(modeldata)
        _dict["IncomingInvites"] = Set(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"Favorites",None ):
            self.__dict__["Favorites"] = SimpleList(self._modeldata)
        self.Favorites.init(self.path + u"/Favorites", self._modeldata)
        if not getattr(self,"IncomingInvites",None ):
            self.__dict__["IncomingInvites"] = Set(self._modeldata)
        self.IncomingInvites.init(self._modeldata.FriendsKeeper, self.path + u"/IncomingInvites", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"Favorites",None ):
            self.__dict__["Favorites"] = SimpleList(self._modeldata)
        self.Favorites.init(self.path + u"/Favorites", self._modeldata)
        if not getattr(self,"IncomingInvites",None ):
            self.__dict__["IncomingInvites"] = Set(self._modeldata)
        self.IncomingInvites.init(self._modeldata.FriendsKeeper, self.path + u"/IncomingInvites", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Favorites.init(self.path + u"/Favorites", self._modeldata)
        self.IncomingInvites.init(self._modeldata.FriendsKeeper, self.path + u"/IncomingInvites", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Favorites.deleteByID(id)
            self.IncomingInvites.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = Friends_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Favorites"]=_dict.get("Favorites").getJsonDict()
        json_dict["IncomingInvites"]=_dict.get("IncomingInvites").getJsonDict()
        return {"Friends": json_dict}

if not hasattr(Friends_base, "generateBaseDict"):
    Friends_base.generateBaseDict = generateEmptyDict
