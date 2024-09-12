#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_hero import *
from logic.requests.SelectSkinRequest import SelectSkinRequest


class Select_skin(SubAction, SelectSkinRequest):
    """action, который будет обрабатывать данный класс"""
    action = "select_skin"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.skin_id = self.arguments.skin_id
        self.hero = self.arguments.hero
        self.guardParty = self.arguments.guardParty
        self.master_auid = self.arguments.master_auid
        self.change_party_skin = self.arguments.change_party_skin

        found = False
        if self.hero:
            if self.skin_id == 0:
                self.hero.HeroSkins.CurrentSkin = None
                found = True
            else:
                for skinId in self.hero.HeroSkins.Skins:
                    if self.skin_id == skinId:
                        skin = self.acc.model.getSkinByID(skinId)
                        if skin:
                            static_skin = self.acc.SD.getStaticSkinByPersistentId(skin.PersistentId)
                            if not static_skin['legal'] or (static_skin['persistentId'] in self.acc.getConfigValue(
                                    "INVALID_SKINS") and static_skin['persistentId'] not in self.acc.getConfigValue("SEASON_SKINS") ):
                                self.errorResponse("Bad skin")
                                return

                            self.hero.HeroSkins.CurrentSkin = self.acc.model.getSkinByID(skinId)
                            self.hero.HeroSkins.CurrentSkin.IsAnimatedAvatar = static_skin['persistentId'] not in self.acc.getConfigValue("SKIN_AVATAR_BLOCK")
                            found = True
                            break
        else:
            self.errorResponse("Hero is null")
            return

        if not found:
            self.errorResponse("Skin not found")
            return

        try:
            if self.master_auid and self.change_party_skin:
                subParams = ClassDict(master_auid=[self.master_auid], hero_id=[self.hero.getID()],
                                      hero_crc=[self.hero.PersistentId], guardParty=[self.guardParty])
                self.arguments = self.arguments.arguments
                self.arguments['hero_id'] = [self.hero.getID()]
                self.arguments['hero_crc'] = [self.hero.PersistentId]
                partyAction = Party_hero(subParams, None, I=self.I, acc=self.acc, uid=self.acc.uid, request=self)
                partyAction.onStart()
        except:
            catch()

        self.response["ok"] = 1
        self.fin()
