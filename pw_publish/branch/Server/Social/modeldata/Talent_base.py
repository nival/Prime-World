# -*- coding: utf-8 -*-
# !/usr/bin/env python

from ref import Ref
from enums import *
import GuildBankInfo
from changes import IGuidGenerator
from base.helpers import *
from modeldata.collects import *


class Talent_base:
    # DAN: оптимизируем создание ---------------------------------------------------------

    # вызывается вместо __init__
    def init_empty(self, modeldata, id=None, path=None):
        _dict = self.__dict__
        _dict["_changeWriter"] = modeldata  # ChangeHandler
        _dict["path"] = path  # ChangeHandler
        _dict["id"] = id  # Identified
        _dict["_modeldata"] = modeldata
        _dict["isDeleting"] = False

    # вызывается вместо init()
    def init_add(self):
        _dict = self.__dict__
        modeldata = _dict["_modeldata"]
        hk = modeldata.HeroesKeeper
        gbik = modeldata.GuildBankInfoKeeper
        path = _dict["path"]
        _dict["refCounter"] = 0  # RefCounted
        _dict["defaultForHero"] = Ref(modeldata, hk, path, "defaultForHero")
        _dict["IsNew"] = False
        _dict["Points"] = 0
        _dict["Soulbound"] = Ref(modeldata, hk, path, "Soulbound")
        _dict["PersistentId"] = 0
        _dict["GuildBankInfo"] = Ref(modeldata, gbik, path, "GuildBankInfo")
        ParentTalentSets = SimpleDict(modeldata)
        ParentTalentSets.init(path + u"/ParentTalentSets", modeldata)
        _dict["ParentTalentSets"] = ParentTalentSets
        Owner = Ref(modeldata, hk, path, "Owner")
        _dict["Owner"] = Owner

    # вызывается при создании нового таланта (из addCustomHero)
    def init_create_new(self, PersistentId, ref_hero_id, md, hk, path, gbik, need_soulbound):
        _dict = self.__dict__
        _dict["refCounter"] = 1  # в любом случае будем добавляться в TalentSet
        _dict["PersistentId"] = PersistentId
        _dict["IsNew"] = False
        _dict["Points"] = 0

        defaultForHero = Ref(md, hk, path, "defaultForHero")
        defaultForHero.load_set(ref_hero_id)
        _dict["defaultForHero"] = defaultForHero

        Soulbound = Ref(md, hk, path, "Soulbound")
        if need_soulbound:
            Soulbound.load_set(ref_hero_id)            
        _dict["Soulbound"] = Soulbound

        GuildBankInfo = Ref(md, gbik, path, "GuildBankInfo")
        _dict["GuildBankInfo"] = GuildBankInfo
        ParentTalentSets = SimpleDict(md)
        ParentTalentSets.init(path + u"/ParentTalentSets", md)
        _dict["ParentTalentSets"] = ParentTalentSets
        Owner = Ref(md, hk, path, "Owner")
        Owner.load_set(ref_hero_id)
        _dict["Owner"] = Owner

    def addPoints(self, points, SD, MD, WS, acc):
        lvlStart = SD.getTalentLevel(self)

        points = int(points)
        maxPoints = SD.getTalentMaxPoints(self)
        if self.Points + points < 0:
            self.Points = 0
        elif self.Points + points >= maxPoints:
            self.Points = maxPoints
        else:
            self.Points += points

        lvlEnd = SD.getTalentLevel(self)

        hasNewLevel = (lvlStart != lvlEnd)

        if hasNewLevel:
            staticTalent = SD.getStaticTalent(self)
            if staticTalent:
                MD.addStatisticEvent(StatisticEventType.TALENT_UPGRADE,
                                     staticTalent['persistentId'] + "," + str(lvlEnd), lvlEnd - lvlStart)

            if self.Owner and self.Owner.get():
                for tsId in self.ParentTalentSets.keys():
                     self.Owner.CalcForce(MD, WS, acc, tsId)
                return

    def isSoulboundedToHero(self, hero):
        if self.Soulbound == hero or (self.GuildBankInfo.get() and self.GuildBankInfo.HeroClassId == hero.PersistentId):
            return True

        return False

    def isSoulbounded(self):
        if self.Soulbound is None:
            return False

        if self.Soulbound == IGuidGenerator.InvalidUID and ( not self.GuildBankInfo.get() or self.GuildBankInfo.HeroClassId == 0):
            return False

        return True

    def canBeSoulbound(self, SD):
        staticTalent = SD.getStaticTalent(self)
        return staticTalent["rarity"] == "Class" or fromETalentRarity(staticTalent["rarity"]) > fromETalentRarity(SD.data["RaritiesWithoutSoulbound"])
