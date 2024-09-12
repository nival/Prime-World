# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import QuestEventStageStepVariant

from QuestEventStageStep_base import *

class QuestEventStageStep(RefCounted, Identified, ChangeHandler, BaseObject, QuestEventStageStep_base):
    _changeFields = {
        "Title":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Title"] = ""
        _dict["Variants"] = Collection(modeldata)
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"Variants",None ):
            self.__dict__["Variants"] = Collection(self._modeldata)
        self.Variants.init(self._modeldata.QuestEventStageStepVariantKeeper, self.path + u"/Variants", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"Variants",None ):
            self.__dict__["Variants"] = Collection(self._modeldata)
        self.Variants.init(self._modeldata.QuestEventStageStepVariantKeeper, self.path + u"/Variants", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.Variants.init(self._modeldata.QuestEventStageStepVariantKeeper, self.path + u"/Variants", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.Variants.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = QuestEventStageStep_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Title"]=_dict.get("Title")
        json_dict["Variants"]=_dict.get("Variants").getJsonDict()
        return {"QuestEventStageStep": json_dict}

if not hasattr(QuestEventStageStep_base, "generateBaseDict"):
    QuestEventStageStep_base.generateBaseDict = generateEmptyDict
