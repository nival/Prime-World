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
    with open(os.path.join(PATH, "AddNewOperatorHeroesFromList6.auids")) as f:
        OPERATOR_AUIDS = [toint(x.strip()) for x in f]
except Exception:
    catch()


HEROES_DICTIONARY ={ 'highlander' : (( "G399", "G424", "G187"),( "G428", "G029", "G138"),( "G438", "G386", "G286"),("G389", "G436", "G336", "G281", "G284", "G285"),("G445", "G381", "G332", "G260", "G071", "G279"),("G433", "G388", "G413", "G441", "G275", "G266")) , 
                   'firefox' : (( "G425", "G345", "G130"),( "G427", "G342", "G029"),( "G386", "G392", "G287","G229"),("G432", "G327", "G339", "G282", "G283"),("G444", "G385", "G369", "G335", "G261", "G171"),("G430", "G380", "G323", "G182", "G276", "G207")) ,
                  'snowqueen' : (( "G425", "G421", "G130"),( "G427", "G349", "G354"),( "G386", "G368", "G193", "G287"),("G352", "G432", "G390", "G282", "G283"),("G444", "G369", "G357", "G261", "G171", "G443"),("G370", "G434", "G380", "G182", "G276", "G378")) }

CLASS_TALENTS_DICTIONARY = {'highlander' : (crc32("Highlander_A0"), crc32("Highlander_A1"), crc32("Highlander_A1u1"), crc32("Highlander_A1u2"), crc32("Highlander_A2"), crc32("Highlander_A2u"), crc32("Highlander_A3"), crc32("Highlander_A3u"), crc32("Highlander_A4")) ,
                        'firefox' : ( crc32("Firefox_A0"), crc32("Firefox_A1"), crc32("Firefox_A1_Upg1"), crc32("Firefox_A1_Upg2"), crc32("Firefox_A2"), crc32("Firefox_A3"), crc32("Firefox_A3_Upg1"), crc32("Firefox_A4"), crc32("Firefox_A4_Upg1")), 
                        'snowqueen' : ( crc32("SnowQueen_A0"), crc32("SnowQueen_A1"), crc32("SnowQueen_A1u"), crc32("SnowQueen_A2"), crc32("SnowQueen_A3"), crc32("SnowQueen_A3u"), crc32("SnowQueen_A4"), crc32("SnowQueen_A4u"), crc32("SnowQueen_A5")) }
#EXPIRIENCE = 18760

import CC
from modeldata import TalentSet, collects


class AddNewOperatorHeroesFromList6:


    def addHero(self, hero_class_id, md, env, acc):
        return md.hireHero( hero_class_id, acc.sex, env.I.WS, acc, env.I )

    def setTalentSets(self, hero, md, acc, env, HERO):
        #for HERO in HEROES_DICTIONARY :
        ts = hero.TalentSets[0]
        for rowCount, tour in enumerate(HEROES_DICTIONARY[HERO]):
            debug("AddNewOperatorHero rowCount:%r %r", rowCount, tour)
            it = 0
            for itemCount in xrange(1, (1 + rowCount) * 6):
                slotId = rowCount * 6 + itemCount
                oldTalentId = ts.Talents.get(slotId)
                oldTalent = md.getTalentByID(oldTalentId)

                if oldTalent is not None and oldTalentId is not None:
                    #if oldTalent.PersistentId in CLASS_TALENT:
                    if oldTalent.PersistentId in CLASS_TALENTS_DICTIONARY[HERO]:
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
        for HERO in HEROES_DICTIONARY :
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
                        findHero = self.addHero(hero_class_id, md, env, acc)

                if findHero:
                    
                    # https://devjira.nivalnetwork.com/browse/PF-103949 убрал начисление опыта
                    #diff = EXPIRIENCE - findHero.Experience
                    #debug("AddNewOperatorHero EXP: %r", diff)
                    # 
                    #if diff > 0:
                    #    findHero.changeExperience(diff, md, env.I.WS, acc, env.I)
                    
                    self.setTalentSets(findHero, md, acc, env, HERO)

        return md, acc.db