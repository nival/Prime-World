#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ItemMoveTsToInvRequest import ItemMoveTsToInvRequest


class Item_move_ts2inv(SubAction, ItemMoveTsToInvRequest):
    """action, который будет обрабатывать данный класс"""
    action = "item_move_ts2inv"

    # ----------------------------------------------------------------------------------------------------------------------
    # клиент просит переместить вещь с места на место (из одного слота/пути в другой)
    @model_callback  # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        # 1) проверим, что есть такой герой (TODO:AUTO-GENERATE?)
        hero = self.arguments.src_hero
        self.tsId = self.arguments.talent_set_id
        #hero_talents = self.acc.model.getHeroClassTalents(hero.PersistentId, self.acc.SD)
        if hero and hero.Hired:
            if not hero.InMatchmaking:
                # 2) провермм, что в src слоте действительно лежит вещь с указанным item_id (TODO:AUTO-GENERATE?)
                tal_id = hero.TalentSets[self.tsId].Talents.get(self.arguments.src_slot_id)
                if tal_id is not None and tal_id == self.arguments.src_item_id:
                    # 3) достанем src вещь из keeper-a TODO:AUTO-GENERATE?)
                    src_item = self.acc.model.getTalentByID(tal_id)
                    staticTalent = self.acc.SD.getStaticTalent(src_item)
                    if staticTalent and not staticTalent['isTakenOnStart']:
                        hero.removeTalentFromTalentSet(self.tsId, src_item, tal_id)
                        hero.CalcForce(self.acc.model, self.I.WS, self.acc, self.tsId)

                        self.I.STATS.addMoveTalentFromSet(self.acc.auid, self.acc.nick, src_item.PersistentId,
                                                          hero.PersistentId, self.arguments.src_slot_id)
                else:
                    self.errorResponse("bad source path or item_id")
                    return
            else:
                self.errorResponse("hero is in matchmaking")
                return
        else:
            self.errorResponse("hero not hired")
            return

        self.response["ok"] = 1  # success
        self.fin()
