# -*- coding: utf-8 -*-
from base.helpers import *

'''
удаляет дубликаты классовых талантов

https://devjira.nivalnetwork.com/browse/PF-107302
'''

class RemoveDuplicatedClassTalents:
    def __compareTalents(self, talent1, talent2):
        delta = talent1.Points != talent2.Points
        if delta != 0:
            return delta

        delta = len(talent1.ParentTalentSets) - len(talent2.ParentTalentSets)
        if delta != 0:
            return delta

        return 0

    def convertModelData(self, env, acc, md, dict):
        theBestClassTalents = {}
        talentsSetsForForceRecalc = {}
        for talentId in md.UserInventory.keys():
            talent = md.getTalentByID(talentId)
            if not talent:
                continue
            staticTalent = acc.SD.getStaticTalent(talent)
            if not staticTalent:
                continue
            if staticTalent['rarity'] != 'Class':
                continue
            if talent.PersistentId in theBestClassTalents:
                _talent = theBestClassTalents[talent.PersistentId]
                if self.__compareTalents(talent, _talent) > 0:
                    theBestClassTalents[talent.PersistentId] = talent
                    talent = _talent
                if talent.Owner and talent.Owner.get():
                    hero = talent.Owner.get()
                    forForceRecalc = talentsSetsForForceRecalc.setdefault(hero, set())
                    for tsIdx in talent.ParentTalentSets.keys():
                        hero.removeTalentFromTalentSet(tsIdx, talent, talent.getID())
                        forForceRecalc.add(tsIdx)
                md.UserInventory.remove(talent)
                debug("RemoveDuplicatedClassTalents.convertModelData: remove talent %s", talent.PersistentId)
            else:
                theBestClassTalents[talent.PersistentId] = talent
        for hero in talentsSetsForForceRecalc:
            for ts in talentsSetsForForceRecalc[hero]:
                hero.CalcForce(md, env.I.WS, acc, ts)
        return md, acc.db
