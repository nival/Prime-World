#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ItemMoveTsToTsRequest import ItemMoveTsToTsRequest


class Item_move_ts2ts(SubAction, ItemMoveTsToTsRequest):
    """action, который будет обрабатывать данный класс"""
    action = "item_move_ts2ts"

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
        hero_talents = self.acc.model.getHeroClassTalents(self.acc.getConfig(), hero.PersistentId, self.acc.SD)
        if hero and hero.Hired:
            if not hero.InMatchmaking:
                # 2) провермм, что в src и dest слотах действительно лежат вещи с указанными item_id (TODO:AUTO-GENERATE?)
                srcData = hero.TalentSets[self.tsId].Talents.get(self.arguments.src_slot_id)
                if srcData is not None and srcData == self.arguments.src_item_id:
                    destData = hero.TalentSets[self.tsId].Talents.get(self.arguments.dest_slot_id)
                    destDataId = 0 if destData is None else destData
                    if destDataId == self.arguments.dest_item_id:
                        # 3) достанем src и dest вещи из keeper-a (TODO:AUTO-GENERATE?)
                        src_item = self.acc.model.getTalentByID(srcData)

                        # ======================================================================================================
                        # 4) проверим, что src вещь подходит в слот назначения, а dest вещь (if any) в слот источника
                        talent_id, response_error = Validator.checkItemFit(self.acc, hero, src_item,
                                                                           self.arguments.dest_slot_id, self.acc.SD, 0,
                                                                           hero_talents, tsId=self.tsId)
                        if response_error:
                            self.errorResponse(response_error)
                            return
                        if talent_id:
                            if destDataId == 0:
                                debug("move talent from " + str(self.arguments.src_slot_id) + " to " + str(self.arguments.dest_slot_id))
                                # ОК, в слоте назначения ничего нет, просто переносим src_item в другой (пустой) слот:
                                hero.TalentSets[self.tsId].Talents.move(self.arguments.src_slot_id,
                                                                        self.arguments.dest_slot_id)
                            else:
                                dest_item = self.acc.model.getTalentByID(destDataId)
                                talent_id, response_error = Validator.checkItemFit(self.acc, hero, dest_item,
                                                                                   self.arguments.src_slot_id,
                                                                                   self.acc.SD, 0, hero_talents,
                                                                                   tsId=self.tsId)
                                if response_error:
                                    self.errorResponse(response_error)
                                    return
                                if talent_id:
                                    # ОК, в слоте назначения есть вещь, меняем их местами; т.е. просто переносим src_item в другой (пустой) слот:
                                    hero.TalentSets[self.tsId].Talents.swap(self.arguments.src_slot_id,
                                                                            self.arguments.dest_slot_id)
                                else:
                                    self.errorResponse("bad src slot filter (cant place dest item)")
                                    return
                        else:
                            self.errorResponse("bad dest slot filter (cant place src item)")
                            return
                    # ======================================================================================================
                    # (TODO:AUTO-GENERATE?) отлупы
                    else:
                        self.errorResponse("bad dest path or item_id")
                        return
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
