# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from BeginnersPackItem_base import *

class BeginnersPackItem(RefCounted, Identified, ChangeHandler, BaseObject, BeginnersPackItem_base):
    _changeFields = {
        "Description":1,
        "Gold":1,
        "Image":1,
        "PackTalents":1,
        "PersistentId":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["Description"] = ""
        _dict["Gold"] = 0
        _dict["Image"] = ""
        _dict["PackTalents"] = SimpleList(modeldata)
        _dict["PersistentId"] = ""
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"PackTalents",None ):
            self.__dict__["PackTalents"] = SimpleList(self._modeldata)
        self.PackTalents.init(self.path + u"/PackTalents", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"PackTalents",None ):
            self.__dict__["PackTalents"] = SimpleList(self._modeldata)
        self.PackTalents.init(self.path + u"/PackTalents", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.PackTalents.init(self.path + u"/PackTalents", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.PackTalents.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = BeginnersPackItem_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["Description"]=_dict.get("Description")
        json_dict["Gold"]=_dict.get("Gold")
        json_dict["Image"]=_dict.get("Image")
        json_dict["PackTalents"]=_dict.get("PackTalents").getJsonDict()
        json_dict["PersistentId"]=_dict.get("PersistentId")
        return {"BeginnersPackItem": json_dict}

if not hasattr(BeginnersPackItem_base, "generateBaseDict"):
    BeginnersPackItem_base.generateBaseDict = generateEmptyDict
