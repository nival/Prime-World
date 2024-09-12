# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import Friend

from PartyMember_base import *

class PartyMember(RefCounted, Identified, ChangeHandler, BaseObject, PartyMember_base):
    _changeFields = {
        "ActiveTalentSet":1,
        "agreed":1,
        "banEndTime":1,
        "dependedTournamentQuests":1,
        "flagPersistentId":1,
        "flagType":1,
        "hero_id":1,
        "heroClassId":1,
        "heroForce":1,
        "heroLevel":1,
        "heroRating":1,
        "IsAnimatedAvatar":1,
        "isEnemy":1,
        "isHeroChosen":1,
        "isInventoryFull":1,
        "isLeaver":1,
        "isMMAllowed":1,
        "isPending":1,
        "isTamburReady":1,
        "isValidTS":1,
        "LeagueIndex":1,
        "person":1,
        "realPartyUid":1,
        "skin_persistent_id":1,
        "tournamentDynQuestId":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["ActiveTalentSet"] = 0
        _dict["agreed"] = False
        _dict["banEndTime"] = 0
        _dict["dependedTournamentQuests"] = ""
        _dict["flagPersistentId"] = ""
        _dict["flagType"] = 0
        _dict["hero_id"] = 0
        _dict["heroClassId"] = 0
        _dict["heroForce"] = 0.0
        _dict["heroLevel"] = 0
        _dict["heroRating"] = 0.0
        _dict["IsAnimatedAvatar"] = False
        _dict["isEnemy"] = False
        _dict["isHeroChosen"] = False
        _dict["isInventoryFull"] = False
        _dict["isLeaver"] = False
        _dict["isMMAllowed"] = False
        _dict["isPending"] = False
        _dict["isTamburReady"] = False
        _dict["isValidTS"] = False
        _dict["LeagueIndex"] = 0
        _dict["person"] = Ref(modeldata, modeldata.PersonKeeper, path, "person")
        _dict["realPartyUid"] = 0
        _dict["skin_persistent_id"] = 0
        _dict["tournamentDynQuestId"] = 0
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        ###self.person.init(self._modeldata.PersonKeeper, self.path, self._modeldata, "person")

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        ###self.person.init(self._modeldata.PersonKeeper, self.path, self._modeldata, "person")

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.person.init(self._modeldata.PersonKeeper, self.path, self._modeldata, "person")

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.person.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name == "person":
            self.__dict__["person"].set(val)
            return
        ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = PartyMember_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["ActiveTalentSet"]=_dict.get("ActiveTalentSet")
        json_dict["agreed"]=_dict.get("agreed")
        json_dict["banEndTime"]=_dict.get("banEndTime")
        json_dict["dependedTournamentQuests"]=_dict.get("dependedTournamentQuests")
        json_dict["flagPersistentId"]=_dict.get("flagPersistentId")
        json_dict["flagType"]=_dict.get("flagType")
        json_dict["hero_id"]=_dict.get("hero_id")
        json_dict["heroClassId"]=_dict.get("heroClassId")
        json_dict["heroForce"]=_dict.get("heroForce")
        json_dict["heroLevel"]=_dict.get("heroLevel")
        json_dict["heroRating"]=_dict.get("heroRating")
        json_dict["IsAnimatedAvatar"]=_dict.get("IsAnimatedAvatar")
        json_dict["isEnemy"]=_dict.get("isEnemy")
        json_dict["isHeroChosen"]=_dict.get("isHeroChosen")
        json_dict["isInventoryFull"]=_dict.get("isInventoryFull")
        json_dict["isLeaver"]=_dict.get("isLeaver")
        json_dict["isMMAllowed"]=_dict.get("isMMAllowed")
        json_dict["isPending"]=_dict.get("isPending")
        json_dict["isTamburReady"]=_dict.get("isTamburReady")
        json_dict["isValidTS"]=_dict.get("isValidTS")
        json_dict["LeagueIndex"]=_dict.get("LeagueIndex")
        json_dict["person"]=_dict.get("person").getJsonDict()
        json_dict["realPartyUid"]=_dict.get("realPartyUid")
        json_dict["skin_persistent_id"]=_dict.get("skin_persistent_id")
        json_dict["tournamentDynQuestId"]=_dict.get("tournamentDynQuestId")
        return {"PartyMember": json_dict}

if not hasattr(PartyMember_base, "generateBaseDict"):
    PartyMember_base.generateBaseDict = generateEmptyDict
