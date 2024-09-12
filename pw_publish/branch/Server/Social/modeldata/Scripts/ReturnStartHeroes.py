# -*- coding: utf-8 -*-
from base.helpers import *
from binascii import crc32

START_HEROES = ["healer", "thundergod", "mowgly", "highlander", "firefox"]

class ReturnStartHeroes:
    def convertModelData( self, env, acc, md, dict ):
        if len(md.HeroesKeeper) < len(md.Heroes):
            notOwnedHeroes = START_HEROES[:]
            wrongIds = []
            for heroId, hero in md.Heroes.items():
                if not hero:
                    wrongIds.append(heroId)
                    md.Heroes.realdict.remove( heroId )
                    del md.Heroes.dictionary[heroId]
                else:
                    if hero.class_name in notOwnedHeroes:
                        hero.__dict__["refCounter"] += 35  # на новое поле owner
                        notOwnedHeroes.remove(hero.class_name)
            for talentId, talent in md.UserInventory.items():
                if talent.defaultForHero in wrongIds or talent.Owner in wrongIds:
                    md.UserInventory.remove(talent)
            for heroId in notOwnedHeroes:
                hero = md.hireHero(crc32(heroId), None, env.I.WS, acc, env.I)
                hero.Rating = acc.getConfig().HERO_START_RATING
        return md, acc.db
