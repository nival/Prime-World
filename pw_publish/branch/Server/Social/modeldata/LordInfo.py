# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import GuardInfo
import HonorInfo
import LastStartedMap
import MapInfo
import ForgeRoll
import LordRatings

from LordInfo_base import *

class LordInfo(RefCounted, Identified, ChangeHandler, BaseObject, LordInfo_base):
    _changeFields = {
        "AeriaBillingStatus":1,
        "ArcGamesBillingStatus":1,
        "BillingStatus":1,
        "CameraFlybyTime":1,
        "ComplaintsLeft":1,
        "ComplaintsSessionLeft":1,
        "CurrentLoginTime":1,
        "DisabledMaps":1,
        "DraugasLtBillingStatus":1,
        "ExtraComplaints":1,
        "ExtraComplaintsSession":1,
        "Fame":1,
        "GamigoBillingStatus":1,
        "GuildStatus":1,
        "LastBuyValue":1,
        "LastLoginTime":1,
        "LastLogoutTime":1,
        "LastRankedGameTime":1,
        "LastTechGuildBuffs":1,
        "LastTechPremium":1,
        "LevelOfExpansion":1,
        "MailruBillingStatus":1,
        "MassiveBillingStatus":1,
        "PingResults":1,
        "PremiumAccountEnd":1,
        "PremiumAccountStart":1,
        "PunishedNextUpdateTime":1,
        "PunishedPlayers":1,
        "RandomSeed":1,
        "ReforgeRandomSeed":1,
        "Reliability":1,
        "ResetComplaintsTime":1,
        "SteamBillingStatus":1,
        "TalentRandomSeed":1,
        "TavernRandomSeed":1,
        "TodayWinMaps":1,
        "TurtorialVersion":1,
        "TutorialState":1,
        "UpdateGuildApplications":1,
        "UserLocale":1,
        "ZZimaBillingStatus":1,
    }

    def __init__(self, modeldata, id=None, path=None):
        ChangeHandler.__init__(self, path, modeldata)
        RefCounted.__init__(self)
        Identified.__init__(self, id)
        _dict = self.__dict__
        _dict["_modeldata"] = modeldata
        _dict["AeriaBillingStatus"] = 1
        _dict["ArcGamesBillingStatus"] = 1
        _dict["BillingStatus"] = 0
        _dict["CameraFlybyTime"] = 0
        _dict["ComplaintsLeft"] = 0
        _dict["ComplaintsSessionLeft"] = 0
        _dict["CurrentLoginTime"] = 0
        _dict["DisabledMaps"] = SimpleList(modeldata)
        _dict["DraugasLtBillingStatus"] = 1
        _dict["ExtraComplaints"] = 0
        _dict["ExtraComplaintsSession"] = 0
        _dict["Fame"] = 0.0
        _dict["GamigoBillingStatus"] = 1
        _dict["GuardInfo"] = GuardInfo.GuardInfo(modeldata, None, "")
        _dict["GuildStatus"] = 0
        _dict["HonorInfo"] = HonorInfo.HonorInfo(modeldata, None, "")
        _dict["LastBuyValue"] = 0
        _dict["LastLoginTime"] = 0
        _dict["LastLogoutTime"] = 0
        _dict["LastRankedGameTime"] = 0
        _dict["LastStartedMap"] = LastStartedMap.LastStartedMap(modeldata, None, "")
        _dict["LastTechGuildBuffs"] = 0
        _dict["LastTechPremium"] = 0
        _dict["LevelOfExpansion"] = 0
        _dict["MailruBillingStatus"] = 1
        _dict["MapsByType"] = Collection(modeldata)
        _dict["MassiveBillingStatus"] = 1
        _dict["OrdinaryForgeRoll"] = ForgeRoll.ForgeRoll(modeldata, None, "")
        _dict["PingResults"] = SimpleDict(modeldata)
        _dict["PremiumAccountEnd"] = 0
        _dict["PremiumAccountStart"] = 0
        _dict["PremiumForgeRoll"] = ForgeRoll.ForgeRoll(modeldata, None, "")
        _dict["PunishedNextUpdateTime"] = 0
        _dict["PunishedPlayers"] = 0
        _dict["RandomSeed"] = 0
        _dict["Ratings"] = LordRatings.LordRatings(modeldata, None, "")
        _dict["ReforgeRandomSeed"] = 0
        _dict["Reliability"] = 0
        _dict["ResetComplaintsTime"] = 0
        _dict["SteamBillingStatus"] = 1
        _dict["TalentRandomSeed"] = 0
        _dict["TavernRandomSeed"] = 0
        _dict["TodayWinMaps"] = SimpleDict(modeldata)
        _dict["TurtorialVersion"] = 0
        _dict["TutorialState"] = 0
        _dict["UpdateGuildApplications"] = False
        _dict["UserLocale"] = ""
        _dict["ZZimaBillingStatus"] = 1
        _dict["isDeleting"] = False

    # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
    def init(self):
        pass
        if not getattr(self,"DisabledMaps",None ):
            self.__dict__["DisabledMaps"] = SimpleList(self._modeldata)
        self.DisabledMaps.init(self.path + u"/DisabledMaps", self._modeldata)
        self.GuardInfo.setPath(self.path + u"/GuardInfo")
        self.HonorInfo.setPath(self.path + u"/HonorInfo")
        self.LastStartedMap.setPath(self.path + u"/LastStartedMap")
        if not getattr(self,"MapsByType",None ):
            self.__dict__["MapsByType"] = Collection(self._modeldata)
        self.MapsByType.init(self._modeldata.MapInfoKeeper, self.path + u"/MapsByType", self._modeldata)
        self.OrdinaryForgeRoll.setPath(self.path + u"/OrdinaryForgeRoll")
        if not getattr(self,"PingResults",None ):
            self.__dict__["PingResults"] = SimpleDict(self._modeldata)
        self.PingResults.init(self.path + u"/PingResults", self._modeldata)
        self.PremiumForgeRoll.setPath(self.path + u"/PremiumForgeRoll")
        self.Ratings.setPath(self.path + u"/Ratings")
        if not getattr(self,"TodayWinMaps",None ):
            self.__dict__["TodayWinMaps"] = SimpleDict(self._modeldata)
        self.TodayWinMaps.init(self.path + u"/TodayWinMaps", self._modeldata)

    # вызывается после model.addNewName()
    def init_add(self):
        pass
        if not getattr(self,"DisabledMaps",None ):
            self.__dict__["DisabledMaps"] = SimpleList(self._modeldata)
        self.DisabledMaps.init(self.path + u"/DisabledMaps", self._modeldata)
        self.GuardInfo.setPath(self.path + u"/GuardInfo")
        self.HonorInfo.setPath(self.path + u"/HonorInfo")
        self.LastStartedMap.setPath(self.path + u"/LastStartedMap")
        if not getattr(self,"MapsByType",None ):
            self.__dict__["MapsByType"] = Collection(self._modeldata)
        self.MapsByType.init(self._modeldata.MapInfoKeeper, self.path + u"/MapsByType", self._modeldata)
        self.OrdinaryForgeRoll.setPath(self.path + u"/OrdinaryForgeRoll")
        if not getattr(self,"PingResults",None ):
            self.__dict__["PingResults"] = SimpleDict(self._modeldata)
        self.PingResults.init(self.path + u"/PingResults", self._modeldata)
        self.PremiumForgeRoll.setPath(self.path + u"/PremiumForgeRoll")
        self.Ratings.setPath(self.path + u"/Ratings")
        if not getattr(self,"TodayWinMaps",None ):
            self.__dict__["TodayWinMaps"] = SimpleDict(self._modeldata)
        self.TodayWinMaps.init(self.path + u"/TodayWinMaps", self._modeldata)

    def setPath(self, path):
        ChangeHandler.init(self, path, self._modeldata)
        self.DisabledMaps.init(self.path + u"/DisabledMaps", self._modeldata)
        self.GuardInfo.setPath( self.path + u"/GuardInfo" )
        self.HonorInfo.setPath( self.path + u"/HonorInfo" )
        self.LastStartedMap.setPath( self.path + u"/LastStartedMap" )
        self.MapsByType.init(self._modeldata.MapInfoKeeper, self.path + u"/MapsByType", self._modeldata)
        self.OrdinaryForgeRoll.setPath( self.path + u"/OrdinaryForgeRoll" )
        self.PingResults.init(self.path + u"/PingResults", self._modeldata)
        self.PremiumForgeRoll.setPath( self.path + u"/PremiumForgeRoll" )
        self.Ratings.setPath( self.path + u"/Ratings" )
        self.TodayWinMaps.init(self.path + u"/TodayWinMaps", self._modeldata)

    def deleteByID(self, id):
        if not self.isDeleting:
            self.isDeleting = True
            self.DisabledMaps.deleteByID(id)
            self.GuardInfo.deleteByID(id)
            self.HonorInfo.deleteByID(id)
            self.LastStartedMap.deleteByID(id)
            self.MapsByType.deleteByID(id)
            self.OrdinaryForgeRoll.deleteByID(id)
            self.PingResults.deleteByID(id)
            self.PremiumForgeRoll.deleteByID(id)
            self.Ratings.deleteByID(id)
            self.TodayWinMaps.deleteByID(id)
            self.isDeleting = False

    def __setattr__(self, name, val):
        if name not in self.__dict__ or  val != self.__dict__[name]:
            ChangeHandler.__setattr__(self, name, val)


    def generateJsonDict(self):
        json_dict = LordInfo_base.generateBaseDict(self)
        json_dict['id'] = self.id
        json_dict['path'] = self.path
        json_dict['refCounter'] = self.refCounter
        _dict = self.__dict__
        json_dict["AeriaBillingStatus"]=_dict.get("AeriaBillingStatus")
        json_dict["ArcGamesBillingStatus"]=_dict.get("ArcGamesBillingStatus")
        json_dict["BillingStatus"]=_dict.get("BillingStatus")
        json_dict["CameraFlybyTime"]=_dict.get("CameraFlybyTime")
        json_dict["ComplaintsLeft"]=_dict.get("ComplaintsLeft")
        json_dict["ComplaintsSessionLeft"]=_dict.get("ComplaintsSessionLeft")
        json_dict["CurrentLoginTime"]=_dict.get("CurrentLoginTime")
        json_dict["DisabledMaps"]=_dict.get("DisabledMaps").getJsonDict()
        json_dict["DraugasLtBillingStatus"]=_dict.get("DraugasLtBillingStatus")
        json_dict["ExtraComplaints"]=_dict.get("ExtraComplaints")
        json_dict["ExtraComplaintsSession"]=_dict.get("ExtraComplaintsSession")
        json_dict["Fame"]=_dict.get("Fame")
        json_dict["GamigoBillingStatus"]=_dict.get("GamigoBillingStatus")
        json_dict["GuardInfo"] = _dict.get("GuardInfo").generateJsonDict()
        json_dict["GuildStatus"]=_dict.get("GuildStatus")
        json_dict["HonorInfo"] = _dict.get("HonorInfo").generateJsonDict()
        json_dict["LastBuyValue"]=_dict.get("LastBuyValue")
        json_dict["LastLoginTime"]=_dict.get("LastLoginTime")
        json_dict["LastLogoutTime"]=_dict.get("LastLogoutTime")
        json_dict["LastRankedGameTime"]=_dict.get("LastRankedGameTime")
        json_dict["LastStartedMap"] = _dict.get("LastStartedMap").generateJsonDict()
        json_dict["LastTechGuildBuffs"]=_dict.get("LastTechGuildBuffs")
        json_dict["LastTechPremium"]=_dict.get("LastTechPremium")
        json_dict["LevelOfExpansion"]=_dict.get("LevelOfExpansion")
        json_dict["MailruBillingStatus"]=_dict.get("MailruBillingStatus")
        json_dict["MapsByType"]=_dict.get("MapsByType").getJsonDict()
        json_dict["MassiveBillingStatus"]=_dict.get("MassiveBillingStatus")
        json_dict["OrdinaryForgeRoll"] = _dict.get("OrdinaryForgeRoll").generateJsonDict()
        json_dict["PingResults"]=_dict.get("PingResults").getJsonDict()
        json_dict["PremiumAccountEnd"]=_dict.get("PremiumAccountEnd")
        json_dict["PremiumAccountStart"]=_dict.get("PremiumAccountStart")
        json_dict["PremiumForgeRoll"] = _dict.get("PremiumForgeRoll").generateJsonDict()
        json_dict["PunishedNextUpdateTime"]=_dict.get("PunishedNextUpdateTime")
        json_dict["PunishedPlayers"]=_dict.get("PunishedPlayers")
        json_dict["RandomSeed"]=_dict.get("RandomSeed")
        json_dict["Ratings"] = _dict.get("Ratings").generateJsonDict()
        json_dict["ReforgeRandomSeed"]=_dict.get("ReforgeRandomSeed")
        json_dict["Reliability"]=_dict.get("Reliability")
        json_dict["ResetComplaintsTime"]=_dict.get("ResetComplaintsTime")
        json_dict["SteamBillingStatus"]=_dict.get("SteamBillingStatus")
        json_dict["TalentRandomSeed"]=_dict.get("TalentRandomSeed")
        json_dict["TavernRandomSeed"]=_dict.get("TavernRandomSeed")
        json_dict["TodayWinMaps"]=_dict.get("TodayWinMaps").getJsonDict()
        json_dict["TurtorialVersion"]=_dict.get("TurtorialVersion")
        json_dict["TutorialState"]=_dict.get("TutorialState")
        json_dict["UpdateGuildApplications"]=_dict.get("UpdateGuildApplications")
        json_dict["UserLocale"]=_dict.get("UserLocale")
        json_dict["ZZimaBillingStatus"]=_dict.get("ZZimaBillingStatus")
        return {"LordInfo": json_dict}

if not hasattr(LordInfo_base, "generateBaseDict"):
    LordInfo_base.generateBaseDict = generateEmptyDict
