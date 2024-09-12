#!/usr/bin/env python
# -"- coding: utf8 -"- 
# (C) Dmitry Kolb 2016, Nival Network
__author__ = 'dmitry.kolb'
from base.helpers import *
from binascii import crc32
import os
PATH = os.path.dirname(os.path.abspath(__file__))
#OPERATOR_AUIDS = (36, 1)

OPERATOR_AUIDS =[]
try:
    with open(os.path.join(PATH, "AddNewOperatorHero.auids")) as f:
        OPERATOR_AUIDS = [toint(x.strip()) for x in f]
except Exception:
    catch()

HERO = "highlander"

TALENTSET = (
    ( "G423", "G345", "G295"),
    ( "G394", "G341", "G451"),
    ( "G319", "G393", "G410"),
    ("G436", "G391", "G306", "G373", "G374", "G452"),
    ("G406", "G384", "G332", "G442", "G309", "G453"),
    ("G370", "G413", "G377", "G324", "G454", "G455"),
)
CLASS_TALENT = (crc32("Highlander_A1"),
                crc32("Highlander_A3"),
                crc32("Highlander_A0"),
                crc32("Highlander_A1u1"),
                crc32("Highlander_A3u"),
                crc32("Highlander_A2"),
                crc32("Highlander_A1u2"),
                crc32("Highlander_A4"),
                crc32("Highlander_A2u"),
                )
EXPIRIENCE = 18760


import CC
from modeldata import TalentSet, collects


class AddNewOperatorHero:


    def addHero(self, hero_class_id, md, env, acc):
        return md.hireHero( hero_class_id, acc.sex, env.I.WS, acc, env.I )

    def setTalentSets(self, hero, md, acc, env):
        ts = hero.TalentSets[0]
        for rowCount, tour in enumerate(TALENTSET):
            debug("AddNewOperatorHero rowCount:%r %r", rowCount, tour)
            it = 0
            for itemCount in xrange(1, (1 + rowCount) * 6):
                slotId = rowCount * 6 + itemCount
                oldTalentId = ts.Talents.get(slotId)
                oldTalent = md.getTalentByID(oldTalentId)

                if oldTalent is not None and oldTalentId is not None:
                    if oldTalent.PersistentId in CLASS_TALENT:
                        continue
                    hero.moveTalentFromTalentSetToLibrary(oldTalent, oldTalentId)

                talent = md.addTalent(crc32(tour[it]))
                debug("AddNewOperatorHero slotId: %r", slotId)
                staticTalent = acc.SD.getStaticTalent(talent)
                ts.Talents.add(slotId, talent.id)
                if not staticTalent['type'] == "Passive" and not staticTalent['type'] == "Simple":
                    actionBarIdx = hero.GetFreeActionBarSlot(0)
                    if actionBarIdx != -1:
                        ts.ActionBar[actionBarIdx] = talent.getID()

                talent.ParentTalentSets.add(0, ts.id)
                hero.CalcForce(md, env.I.WS, acc, 0, True)
                if talent.canBeSoulbound(acc.SD):
                    talent.Soulbound = hero

                talent.Owner = hero
                it += 1
                if it >= len(tour):
                    break

    def convertModelData( self, env, acc, md, dict ):
        if acc.db.auid in OPERATOR_AUIDS:
            hero_class_id = crc32(HERO)

            # Меняем таланты, которые на героях
            isFindHero = False
            findHero = None
            for heroId in md.HeroesKeeper:
                hero = md.getHeroByID( heroId )
                if hero.PersistentId == hero_class_id:
                    isFindHero = True
                    findHero = hero
                    debug("AddNewOperatorHero find hero: %r", heroId)
            else:
                if not isFindHero:
                    findHero = self.addHero(hero_class_id, md, env, acc )

            if findHero:
                diff = EXPIRIENCE - findHero.Experience
                debug("AddNewOperatorHero EXP: %r", diff)

                if diff > 0:
                    findHero.changeExperience(diff, md, env.I.WS, acc, env.I)
                self.setTalentSets(findHero, md, acc, env)

        return md, acc.db