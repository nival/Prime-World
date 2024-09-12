# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import TournamentTicket

from TournamentInfo_base import *

class TournamentInfo(RefCounted, Identified, ChangeHandler, BaseObject, TournamentInfo_base):
    _changeFields = {
        "TournamentState":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["TournamentState"] = 0
        _dict["TournamentTicket"] = TournamentTicket.TournamentTicket(modeldata, None, "")
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.TournamentTicket.setPath(self.path + u"/TournamentTicket")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.TournamentTicket.setPath(self.path + u"/TournamentTicket")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.TournamentTicket.setPath( self.path + u"/TournamentTicket" )

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.TournamentTicket.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = TournamentInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["TournamentState"]=_dict.get("TournamentState")
        json_dict["TournamentTicket"] = _dict.get("TournamentTicket").generateJsonDict()
        return {"TournamentInfo": json_dict}

if not hasattr(TournamentInfo_base, "generateBaseDict"):
    TournamentInfo_base.generateBaseDict = generateEmptyDict
