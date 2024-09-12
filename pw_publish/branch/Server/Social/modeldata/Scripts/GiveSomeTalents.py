# -*- coding: utf-8 -*-
from base.helpers import *
from enums import ETalentRarity
from itertools import chain

'''
у игроков пропали некторые таланты из дефолтовых талантсетов
https://devjira.nivalnetwork.com/browse/PF-107266
https://devjira.nivalnetwork.com/browse/PF-107272

скрипт возврящает игрокам
- классовые таланты из деф талантсета
- неклассовые выше заданой рарности из деф талантсета
'''

class GiveSomeTalents:
    def convertModelData(self, env, acc, md, dict):
        for heroId in md.HeroesKeeper.keys():

            hero = md.getHeroByID(heroId)
            if not hero:
                continue
            if not hero.Hired:
                continue

            staticHero = acc.SD.getStaticHero(hero)
            if not staticHero:
                continue

            newClassTalents = set()
            newRarityTalents = set()
            for ts in staticHero['talents']:
                for row in ts:
                    for tal in row:
                        if not tal:
                            continue
                        if tal.rarity == 'Class':
                            newClassTalents.add(tal.CRC32)
                        elif getattr(ETalentRarity, tal.rarity, -1) >= ETalentRarity.exclusive:
                            newRarityTalents.add(tal.CRC32)

            for talentId in md.UserInventory.keys():
                talent = md.getTalentByID(talentId)
                if not talent:
                    continue
                if talent.PersistentId in newClassTalents:
                    newClassTalents.remove(talent.PersistentId)
                elif talent.defaultForHero != 0 \
                        and talent.defaultForHero.PersistentId == hero.PersistentId \
                        and talent.PersistentId in newRarityTalents:
                    newRarityTalents.remove(talent.PersistentId)

            newTalents = chain(newClassTalents, newRarityTalents)
            for talentID in newTalents:
                createdTalent, talent_id = md.newTalent()
                createdTalent.__dict__["PersistentId"] = talentID
                createdTalent.__dict__["IsNew"] = False
                createdTalent.defaultForHero = hero
                if createdTalent.canBeSoulbound(acc.SD):
                    createdTalent.Soulbound = hero
                md.UserInventory.add(createdTalent)
                debug("GiveSomeTalents.convertModelData: create talent %s for hero %s", createdTalent.PersistentId, hero.class_name)

        return md, acc.db
