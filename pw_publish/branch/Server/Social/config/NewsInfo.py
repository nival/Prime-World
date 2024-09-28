# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from NewsInfo_base import *

class NewsInfo(RefCounted, Identified, ChangeHandler, BaseObject, NewsInfo_base):
    _changeFields = {
        "ButtonText":1,
        "ButtonUrl":1,
        "ExtensionJson":1,
        "HideIfViewed":1,
        "LoginNetworkNews":1,
        "MainUrl":1,
        "MainUrlB":1,
        "MinLordLevel":1,
        "Tooltip":1,
        "WindowCaption":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["ButtonText"] = ""
        _dict["ButtonUrl"] = ""
        _dict["ExtensionJson"] = ""
        _dict["HideIfViewed"] = False
        _dict["LoginNetworkNews"] = ""
        _dict["MainUrl"] = ""
        _dict["MainUrlB"] = ""
        _dict["MinLordLevel"] = 0
        _dict["Tooltip"] = ""
        _dict["WindowCaption"] = ""
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
        json_dict = NewsInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["ButtonText"]=_dict.get("ButtonText")
        json_dict["ButtonUrl"]=_dict.get("ButtonUrl")
        json_dict["ExtensionJson"]=_dict.get("ExtensionJson")
        json_dict["HideIfViewed"]=_dict.get("HideIfViewed")
        json_dict["LoginNetworkNews"]=_dict.get("LoginNetworkNews")
        json_dict["MainUrl"]=_dict.get("MainUrl")
        json_dict["MainUrlB"]=_dict.get("MainUrlB")
        json_dict["MinLordLevel"]=_dict.get("MinLordLevel")
        json_dict["Tooltip"]=_dict.get("Tooltip")
        json_dict["WindowCaption"]=_dict.get("WindowCaption")
        return {"NewsInfo": json_dict}

if not hasattr(NewsInfo_base, "generateBaseDict"):
    NewsInfo_base.generateBaseDict = generateEmptyDict
