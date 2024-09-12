# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from QuestEventProgression_base import *

class QuestEventProgression(RefCounted, Identified, ChangeHandler, BaseObject, QuestEventProgression_base):
    _changeFields = {
        "Choices":1,
        "Locked":1,
        "PersistentId":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Choices"] = SimpleList(modeldata)
        _dict["Locked"] = SimpleList(modeldata)
        _dict["PersistentId"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"Choices",None ):
            self.__dict__["Choices"] = SimpleList(self._modeldata)
        self.Choices.init(self.path + u"/Choices", self._modeldata)
        if not getattr(self,"Locked",None ):
            self.__dict__["Locked"] = SimpleList(self._modeldata)
        self.Locked.init(self.path + u"/Locked", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"Choices",None ):
            self.__dict__["Choices"] = SimpleList(self._modeldata)
        self.Choices.init(self.path + u"/Choices", self._modeldata)
        if not getattr(self,"Locked",None ):
            self.__dict__["Locked"] = SimpleList(self._modeldata)
        self.Locked.init(self.path + u"/Locked", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Choices.init(self.path + u"/Choices", self._modeldata)
        self.Locked.init(self.path + u"/Locked", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Choices.deleteByID(id)
            self.Locked.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = QuestEventProgression_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Choices"]=_dict.get("Choices").getJsonDict()
        json_dict["Locked"]=_dict.get("Locked").getJsonDict()
        json_dict["PersistentId"]=_dict.get("PersistentId")
        return {"QuestEventProgression": json_dict}

if not hasattr(QuestEventProgression_base, "generateBaseDict"):
    QuestEventProgression_base.generateBaseDict = generateEmptyDict
