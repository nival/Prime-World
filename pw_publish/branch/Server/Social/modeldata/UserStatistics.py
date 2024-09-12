# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import ShortSessionInfo
import SessionResults

from UserStatistics_base import *

class UserStatistics(RefCounted, Identified, ChangeHandler, BaseObject, UserStatistics_base):
    _changeFields = {
        "LastLampDropTime":1,
        "LastPaymentTime":1,
        "PRSessionsStarted":1,
        "SessionsEndedByGate":1,
        "SessionsStarted":1,
        "StartSessionByGate":1,
        "TotalSessionResultsReceived":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["LastLampDropTime"] = 0
        _dict["LastPaymentTime"] = 0
        _dict["LastSessionInfo"] = ShortSessionInfo.ShortSessionInfo(modeldata, None, "")
        _dict["LastSessionResults"] = SessionResults.SessionResults(modeldata, None, "")
        _dict["MaxSessionResults"] = SessionResults.SessionResults(modeldata, None, "")
        _dict["PRSessionsStarted"] = 0
        _dict["SessionsEndedByGate"] = 0
        _dict["SessionsStarted"] = 0
        _dict["StartSessionByGate"] = False
        _dict["SummarySessionResults"] = SessionResults.SessionResults(modeldata, None, "")
        _dict["TotalSessionResultsReceived"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        self.LastSessionInfo.setPath(self.path + u"/LastSessionInfo")
        self.LastSessionResults.setPath(self.path + u"/LastSessionResults")
        self.MaxSessionResults.setPath(self.path + u"/MaxSessionResults")
        self.SummarySessionResults.setPath(self.path + u"/SummarySessionResults")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        self.LastSessionInfo.setPath(self.path + u"/LastSessionInfo")
        self.LastSessionResults.setPath(self.path + u"/LastSessionResults")
        self.MaxSessionResults.setPath(self.path + u"/MaxSessionResults")
        self.SummarySessionResults.setPath(self.path + u"/SummarySessionResults")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.LastSessionInfo.setPath( self.path + u"/LastSessionInfo" )
        self.LastSessionResults.setPath( self.path + u"/LastSessionResults" )
        self.MaxSessionResults.setPath( self.path + u"/MaxSessionResults" )
        self.SummarySessionResults.setPath( self.path + u"/SummarySessionResults" )

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.LastSessionInfo.deleteByID(id)
            self.LastSessionResults.deleteByID(id)
            self.MaxSessionResults.deleteByID(id)
            self.SummarySessionResults.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = UserStatistics_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["LastLampDropTime"]=_dict.get("LastLampDropTime")
        json_dict["LastPaymentTime"]=_dict.get("LastPaymentTime")
        json_dict["LastSessionInfo"] = _dict.get("LastSessionInfo").generateJsonDict()
        json_dict["LastSessionResults"] = _dict.get("LastSessionResults").generateJsonDict()
        json_dict["MaxSessionResults"] = _dict.get("MaxSessionResults").generateJsonDict()
        json_dict["PRSessionsStarted"]=_dict.get("PRSessionsStarted")
        json_dict["SessionsEndedByGate"]=_dict.get("SessionsEndedByGate")
        json_dict["SessionsStarted"]=_dict.get("SessionsStarted")
        json_dict["StartSessionByGate"]=_dict.get("StartSessionByGate")
        json_dict["SummarySessionResults"] = _dict.get("SummarySessionResults").generateJsonDict()
        json_dict["TotalSessionResultsReceived"]=_dict.get("TotalSessionResultsReceived")
        return {"UserStatistics": json_dict}

if not hasattr(UserStatistics_base, "generateBaseDict"):
    UserStatistics_base.generateBaseDict = generateEmptyDict
