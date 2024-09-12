#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ItemSetActoinBarIndexRequest import ItemSetActoinBarIndexRequest


class Item_set_actbar_idx(SubAction, ItemSetActoinBarIndexRequest):
    """action, который будет обрабатывать данный класс"""
    action = "item_set_actbar_idx"

    # ----------------------------------------------------------------------------------------------------------------------
    # клиент просит добавить индекс вещи в ActionBar
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
        # 2) провермм, что в src слоте действительно лежит вещь с указанным item_id (TODO:AUTO-GENERATE?)
        talent_id  = hero.TalentSets[self.tsId].Talents.get(self.arguments.slot_id)
        if hero and talent_id is not None and talent_id == self.arguments.item_id:
            # 3) достанем src вещь из keeper-a TODO:AUTO-GENERATE?)
            item = self.acc.model.getTalentByID(hero.TalentSets[self.tsId].Talents.get(self.arguments.slot_id))
            # - проверим, что у данной вещи действительно указанный talent_id (TODO:AUTO-GENERATE?)
            if item and item.PersistentId == self.arguments.talent_id:
                for actionBarIdx in hero.TalentSets[self.tsId].ActionBar:
                    if hero.TalentSets[self.tsId].ActionBar[actionBarIdx] == talent_id:
                        hero.TalentSets[self.tsId].ActionBar[actionBarIdx] = -1
                        hero.TalentSets[self.tsId].InstaCast.set(actionBarIdx, False)
                # ======================================================================================================
                # ОК, ставим вещи указанный ActionBarIdx
                if self.arguments.actbar_idx in xrange(0, 10):
                    hero.TalentSets[self.tsId].ActionBar[self.arguments.actbar_idx] = talent_id
                    hero.TalentSets[self.tsId].InstaCast.set(self.arguments.actbar_idx, self.arguments.is_insta_cast)

                self.response["ok"] = 1  # success
                # ======================================================================================================
            else:
                self.errorResponse("bad item talentId")
                return
        # (TODO:AUTO-GENERATE?) отлупы
        else:
           self.errorResponse("bad source path or item_id")
           return
        self.fin()
