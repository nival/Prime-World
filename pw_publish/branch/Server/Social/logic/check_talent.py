#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys, math
from subaction import *
from logic.requests.CheckTalentRequest import CheckTalentRequest


class Check_talent(SubAction, CheckTalentRequest):
    """action, который будет обрабатывать данный класс"""
    action = "check_talent"

    @model_callback
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        hero = self.arguments.src_hero
        tsId = self.arguments.talent_set_id
        talent = self.acc.model.getTalentByID(hero.TalentSets[tsId].Talents.get(self.arguments.src_slot_id))

        if talent and hero and hero.Hired:
            # проверяем дубликаты
            countTals = 0
            for key in hero.TalentSets[tsId].Talents.keys():
                tal = self.acc.model.getTalentByID(hero.TalentSets[tsId].Talents.get(key))
                if tal:
                    if tal.PersistentId == talent.PersistentId:
                        countTals += 1
            if countTals > 1:
                #self.acc.model.UserInventory.add(talent)
                hero.moveTalentFromTalentSetToLibrary(talent, talent.id)
                if talent not in self.acc.model.UserInventory.values():
                    self.acc.model.UserInventory.add(talent)

            # проверяем неправильный тур
            staticTalent = self.acc.SD.getStaticTalentByTalentId(talent.PersistentId)
            talentLevel = int(math.ceil(self.arguments.src_slot_id / 6.0)) - 1
            if talentLevel != staticTalent['minLevel']:
                #self.acc.model.UserInventory.add(talent)
                hero.moveTalentFromTalentSetToLibrary(talent, talent.id)
                if talent not in self.acc.model.UserInventory.values():
                    self.acc.model.UserInventory.add(talent)


        self.response["ok"] = 1
        self.fin()
