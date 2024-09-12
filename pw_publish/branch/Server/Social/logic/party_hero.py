#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_action import *
from logic.requests.PartyHeroRequest import PartyHeroRequest


class Party_hero(Party_action, PartyHeroRequest):
    """action, который будет обрабатывать данный класс"""
    action = "party_hero"

    @model_callback
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            info("Party_hero(auid=%s): failed param check" % self.acc.auid)
            return

        if self.checkValidIntParam("hero_id"):
            if self.checkValidIntParam("hero_crc"):
                if self.hero_id == -1:
                    self.hero_id = 0
                    self.hero_crc = 0
                    return Party_action.onStart(self)
                tsId = self.getIntParam("talent_set_id", 0)
                session = self.acc.data.mm or {}
                mm_progress = session.get("progress", 0)

                hero = self.acc.model.getHeroByID(self.hero_id)
                if hero:
                    if hero.isHeroInActiveTavern(self.acc.SD, self.acc.model):
                        self.errorResponse("Hero is in Tavern quest")
                        return
                    if hero.PersistentId == self.hero_crc:
                        hero_isValidTS = hero.IsValidTalentSet("", self.acc.SD, tsId, self.acc.model)
                        self.addArguments(hero_isValidTS=hero_isValidTS)

                        hero_skin_id = self.acc.model.getCurrentSkinPersistentId(hero)
                        self.addArguments(hero_skin_id=hero_skin_id)

                        best_league = hero.getBestLeagueFromPrevSeasons(self.acc, self.acc.SD)
                        LeagueIndex = best_league['flashDataIndex'] if best_league else 0
                        self.addArguments(LeagueIndex=LeagueIndex)

                        IsAnimatedAvatar = self.acc.model.getCurrentSkinAnimateAvatar(hero)
                        self.addArguments(IsAnimatedAvatar=toint(IsAnimatedAvatar))

                        hero_level = self.acc.SD.getHeroExpLevel(hero.Experience) + 1
                        self.addArguments(hero_level=hero_level)

                        hero_force = self.acc.SD.getHeroForce(hero, tsId, self.acc.model,
                                                              self.acc.model.getStatPointsFromBuilding(self.acc.SD))
                        self.addArguments(hero_force=hero_force)

                        hero_rating = hero.Rating
                        self.addArguments(hero_rating=hero_rating)

                        hero_status = self.acc.model.getLordStatus(hero, self.acc.getConfig())
                        self.addArguments(hero_status=hero_status)

                        force_change = self.getIntParam("force_change", 0)
                        self.addArguments(force_change=force_change)

                        talentset_id = tsId
                        self.addArguments(talentset_id=talentset_id)

                        game_id = session.get("game_id", 0)
                        allies_key = session.get("allies_key", "")
                        party_id = self.acc.party_id or 0

                        self.addArguments(mm_progress=mm_progress, party_id=party_id)

                        # выселяем героя из всех домиков в которых он сидит
                        for building_id in hero.InBuildings.keys():
                            building = self.acc.model.getConstructionByID(building_id)
                            building.removeHeroFromBuilding(hero, self.acc, self.I)

                        if mm_progress == MM.STATUS_GUARDS_LOBBY:
                            # кроме того, для тамбура нужно отдельно дать tambur_id, чтобы знали куда мапить
                            self.addArguments(game_id=game_id, allies_key=allies_key)

                        info("PartyHeroAction self.arguments: %s" % self.arguments)
                        return Party_action.onStart(self)

                    else:
                        self.fail("bad hero_crc (hero_id %d, hero.PersistentId=%d, hero_crc=%d)" % (
                        self.hero_id, hero.PersistentId, self.hero_crc), EC.HERO_BAD_CRC)
                else:
                    self.fail("no such hero (hero_id %d), possible: %s" % (self.hero_id, self.acc.model.Heroes.keys()),
                              EC.HERO_NOT_FOUND)
        self.fin()
