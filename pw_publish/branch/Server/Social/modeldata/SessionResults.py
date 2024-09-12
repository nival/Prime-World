# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from SessionResults_base import *

class SessionResults(RefCounted, Identified, ChangeHandler, BaseObject, SessionResults_base):
    _changeFields = {
        "achievScore":1,
        "assists":1,
        "currentDeathSpree":1,
        "currentKillSpree":1,
        "damageDealedMagic":1,
        "damageDealedMaterial":1,
        "damageDealedPure":1,
        "damageDealedToHeroesMagic":1,
        "damageDealedToHeroesMaterial":1,
        "damageDealedToHeroesPure":1,
        "damageDealedToHeroesTotal":1,
        "damageDealedTotal":1,
        "damageReceivedFromHeroesMagic":1,
        "damageReceivedFromHeroesMaterial":1,
        "damageReceivedFromHeroesPure":1,
        "damageReceivedFromHeroesTotal":1,
        "damageReceivedMagic":1,
        "damageReceivedMaterial":1,
        "damageReceivedPure":1,
        "damageReceivedTotal":1,
        "deaths":1,
        "enemyCreepsKilled":1,
        "finalLevel":1,
        "flagsDestroyed":1,
        "flagsRaised":1,
        "glyphsPickuped":1,
        "grandScore":1,
        "healedAmount":1,
        "killedByNeutrals":1,
        "kills":1,
        "money":1,
        "neutralCreepsKilled":1,
        "numBossKillsAssist":1,
        "numCatKillAssist":1,
        "numDragonKillAssist":1,
        "numKillsTotal":1,
        "saviourTime":1,
        "score":1,
        "sexHelp":1,
        "specialPoints":1,
        "teleportsByAbility":1,
        "timeAtHome":1,
        "timeElapsed":1,
        "timeInDeath":1,
        "timeInIdle":1,
        "totalMedalsCountDone":1,
        "totalMedalsCountFailed":1,
        "totalMedalsCountGold":1,
        "totalMedalsCountSilver":1,
        "totalNumQuartersDestroyed":1,
        "totalNumTowersAssisted":1,
        "totalNumTowersKilled":1,
        "usedPotions":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["achievScore"] = 0
        _dict["assists"] = 0
        _dict["currentDeathSpree"] = 0
        _dict["currentKillSpree"] = 0
        _dict["damageDealedMagic"] = 0.0
        _dict["damageDealedMaterial"] = 0.0
        _dict["damageDealedPure"] = 0.0
        _dict["damageDealedToHeroesMagic"] = 0.0
        _dict["damageDealedToHeroesMaterial"] = 0.0
        _dict["damageDealedToHeroesPure"] = 0.0
        _dict["damageDealedToHeroesTotal"] = 0.0
        _dict["damageDealedTotal"] = 0.0
        _dict["damageReceivedFromHeroesMagic"] = 0.0
        _dict["damageReceivedFromHeroesMaterial"] = 0.0
        _dict["damageReceivedFromHeroesPure"] = 0.0
        _dict["damageReceivedFromHeroesTotal"] = 0.0
        _dict["damageReceivedMagic"] = 0.0
        _dict["damageReceivedMaterial"] = 0.0
        _dict["damageReceivedPure"] = 0.0
        _dict["damageReceivedTotal"] = 0.0
        _dict["deaths"] = 0
        _dict["enemyCreepsKilled"] = 0
        _dict["finalLevel"] = 0
        _dict["flagsDestroyed"] = 0
        _dict["flagsRaised"] = 0
        _dict["glyphsPickuped"] = 0
        _dict["grandScore"] = 0
        _dict["healedAmount"] = 0.0
        _dict["killedByNeutrals"] = 0
        _dict["kills"] = 0
        _dict["money"] = 0.0
        _dict["neutralCreepsKilled"] = 0
        _dict["numBossKillsAssist"] = 0
        _dict["numCatKillAssist"] = 0
        _dict["numDragonKillAssist"] = 0
        _dict["numKillsTotal"] = 0
        _dict["saviourTime"] = 0.0
        _dict["score"] = 0
        _dict["sexHelp"] = 0
        _dict["specialPoints"] = 0
        _dict["teleportsByAbility"] = 0
        _dict["timeAtHome"] = 0.0
        _dict["timeElapsed"] = 0
        _dict["timeInDeath"] = 0.0
        _dict["timeInIdle"] = 0.0
        _dict["totalMedalsCountDone"] = 0
        _dict["totalMedalsCountFailed"] = 0
        _dict["totalMedalsCountGold"] = 0
        _dict["totalMedalsCountSilver"] = 0
        _dict["totalNumQuartersDestroyed"] = 0
        _dict["totalNumTowersAssisted"] = 0
        _dict["totalNumTowersKilled"] = 0
        _dict["usedPotions"] = 0
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
        json_dict = SessionResults_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["achievScore"]=_dict.get("achievScore")
        json_dict["assists"]=_dict.get("assists")
        json_dict["currentDeathSpree"]=_dict.get("currentDeathSpree")
        json_dict["currentKillSpree"]=_dict.get("currentKillSpree")
        json_dict["damageDealedMagic"]=_dict.get("damageDealedMagic")
        json_dict["damageDealedMaterial"]=_dict.get("damageDealedMaterial")
        json_dict["damageDealedPure"]=_dict.get("damageDealedPure")
        json_dict["damageDealedToHeroesMagic"]=_dict.get("damageDealedToHeroesMagic")
        json_dict["damageDealedToHeroesMaterial"]=_dict.get("damageDealedToHeroesMaterial")
        json_dict["damageDealedToHeroesPure"]=_dict.get("damageDealedToHeroesPure")
        json_dict["damageDealedToHeroesTotal"]=_dict.get("damageDealedToHeroesTotal")
        json_dict["damageDealedTotal"]=_dict.get("damageDealedTotal")
        json_dict["damageReceivedFromHeroesMagic"]=_dict.get("damageReceivedFromHeroesMagic")
        json_dict["damageReceivedFromHeroesMaterial"]=_dict.get("damageReceivedFromHeroesMaterial")
        json_dict["damageReceivedFromHeroesPure"]=_dict.get("damageReceivedFromHeroesPure")
        json_dict["damageReceivedFromHeroesTotal"]=_dict.get("damageReceivedFromHeroesTotal")
        json_dict["damageReceivedMagic"]=_dict.get("damageReceivedMagic")
        json_dict["damageReceivedMaterial"]=_dict.get("damageReceivedMaterial")
        json_dict["damageReceivedPure"]=_dict.get("damageReceivedPure")
        json_dict["damageReceivedTotal"]=_dict.get("damageReceivedTotal")
        json_dict["deaths"]=_dict.get("deaths")
        json_dict["enemyCreepsKilled"]=_dict.get("enemyCreepsKilled")
        json_dict["finalLevel"]=_dict.get("finalLevel")
        json_dict["flagsDestroyed"]=_dict.get("flagsDestroyed")
        json_dict["flagsRaised"]=_dict.get("flagsRaised")
        json_dict["glyphsPickuped"]=_dict.get("glyphsPickuped")
        json_dict["grandScore"]=_dict.get("grandScore")
        json_dict["healedAmount"]=_dict.get("healedAmount")
        json_dict["killedByNeutrals"]=_dict.get("killedByNeutrals")
        json_dict["kills"]=_dict.get("kills")
        json_dict["money"]=_dict.get("money")
        json_dict["neutralCreepsKilled"]=_dict.get("neutralCreepsKilled")
        json_dict["numBossKillsAssist"]=_dict.get("numBossKillsAssist")
        json_dict["numCatKillAssist"]=_dict.get("numCatKillAssist")
        json_dict["numDragonKillAssist"]=_dict.get("numDragonKillAssist")
        json_dict["numKillsTotal"]=_dict.get("numKillsTotal")
        json_dict["saviourTime"]=_dict.get("saviourTime")
        json_dict["score"]=_dict.get("score")
        json_dict["sexHelp"]=_dict.get("sexHelp")
        json_dict["specialPoints"]=_dict.get("specialPoints")
        json_dict["teleportsByAbility"]=_dict.get("teleportsByAbility")
        json_dict["timeAtHome"]=_dict.get("timeAtHome")
        json_dict["timeElapsed"]=_dict.get("timeElapsed")
        json_dict["timeInDeath"]=_dict.get("timeInDeath")
        json_dict["timeInIdle"]=_dict.get("timeInIdle")
        json_dict["totalMedalsCountDone"]=_dict.get("totalMedalsCountDone")
        json_dict["totalMedalsCountFailed"]=_dict.get("totalMedalsCountFailed")
        json_dict["totalMedalsCountGold"]=_dict.get("totalMedalsCountGold")
        json_dict["totalMedalsCountSilver"]=_dict.get("totalMedalsCountSilver")
        json_dict["totalNumQuartersDestroyed"]=_dict.get("totalNumQuartersDestroyed")
        json_dict["totalNumTowersAssisted"]=_dict.get("totalNumTowersAssisted")
        json_dict["totalNumTowersKilled"]=_dict.get("totalNumTowersKilled")
        json_dict["usedPotions"]=_dict.get("usedPotions")
        return {"SessionResults": json_dict}

if not hasattr(SessionResults_base, "generateBaseDict"):
    SessionResults_base.generateBaseDict = generateEmptyDict
