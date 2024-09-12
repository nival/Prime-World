# -*- coding: utf-8 -*-

import sys

sys.path.append('../')
from binascii import crc32

sys.path.append('../..')
from enums import *


class applyDefaultTalentSet_test:
    def applyDefaultTalentSet_test(self, env):
        modeldata = env.acc.model

        hero = env.add_hero(modeldata, "mowgly")

        createdTalent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(createdTalent)

        createdTalent.Soulbound = hero
        t = hero.TalentSets[0].Talents.get(12)
        if t:
            hero.removeTalentFromTalentSet(0, t, t.id)
        hero.TalentSets[0].Talents.add(12, createdTalent.id)
        createdTalent.Owner = hero
        createdTalent.ParentTalentSets.add(0, hero.TalentSets[0].id)

        defaultinventoryLength = len(modeldata.UserInventory)
        hero.TalentSets[0].TalentSetCrc = -1
        modeldata.checkHeroesDefaultTalentSet(env.I.WS, env.acc)

        assert len(modeldata.UserInventory) == defaultinventoryLength

    def applyDefaultTalentSet_test2(self, env):
        modeldata = env.acc.model

        hero = env.add_hero(modeldata, "mowgly")
        createdTalent = env.add_talent(modeldata, "G137")
        createdTalent.Soulbound = hero
        modeldata.UserInventory.add(createdTalent)
        t = hero.TalentSets[0].Talents.get(12)
        if t:
            hero.removeTalentFromTalentSet(0, t, t.id)
        hero.TalentSets[0].Talents.add(12, createdTalent.id)
        createdTalent.Owner = hero
        createdTalent.ParentTalentSets.add(0, hero.TalentSets[0].id)

        defaultinventoryLength = len(modeldata.UserInventory)
        hero.TalentSets[0].TalentSetCrc = -1
        modeldata.checkHeroesDefaultTalentSet(env.I.WS, env.acc)
        assert len(modeldata.UserInventory) == defaultinventoryLength
        hero.TalentSets[0].TalentSetCrc = -1
        modeldata.checkHeroesDefaultTalentSet(env.I.WS, env.acc)
        assert len(modeldata.UserInventory) == defaultinventoryLength

    def checkCheckHeroesDefaultTalentSet_badTalent(self, env):
        hero = next(h for h in env.acc.model.Heroes.values() if h.PersistentId == crc32('firefox'))
        createdTalent = env.add_talent(env.acc.model, "i am bad talent")
        env.acc.model.UserInventory.add(createdTalent)
        hero.TalentSets[0].TalentSetCrc = -1
        env.acc.model.checkHeroesDefaultTalentSet(env.I.WS, env.acc)
        assert not env.acc.model.UserInventory.get(createdTalent.getID())

    def checkCheckHeroesDefaultTalentSet_doNothing(self, env):
        hero = next(h for h in env.acc.model.Heroes.values() if h.PersistentId == crc32('firefox'))
        _befor = len(env.acc.model.UserInventory)
        hero.TalentSets[0].TalentSetCrc = -1
        env.acc.model.checkHeroesDefaultTalentSet(env.I.WS, env.acc)
        assert len(env.acc.model.UserInventory) == _befor

    def checkCheckHeroesDefaultTalentSet_badClassTalentOnlyInInventary(self, env):
        hero = next(h for h in env.acc.model.Heroes.values() if h.PersistentId == crc32('firefox'))
        createdTalent = env.add_talent(env.acc.model, "Mowgli_A2")
        createdTalent.Soulbound = hero
        env.acc.model.UserInventory.add(createdTalent)
        createdTalent.Owner = hero
        createdTalent.ParentTalentSets.add(0, hero.TalentSets[0].id)
        createdTalent.defaultForHero = hero
        hero.TalentSets[0].TalentSetCrc = -1
        env.acc.model.checkHeroesDefaultTalentSet(env.I.WS, env.acc)
        assert not env.acc.model.UserInventory.get(createdTalent.getID())

    def checkCheckHeroesDefaultTalentSet_badClassTalent(self, env):
        hero = next(h for h in env.acc.model.Heroes.values() if h.PersistentId == crc32('firefox'))
        createdTalent = env.add_talent(env.acc.model, "Mowgli_A2")
        createdTalent.Soulbound = hero
        env.acc.model.UserInventory.add(createdTalent)
        tId = hero.TalentSets[0].Talents.get(12)
        t = env.acc.model.getTalentByID(tId)
        if t:
            hero.removeTalentFromTalentSet(0, t, tId)
        hero.TalentSets[0].Talents.add(12, createdTalent.id)
        createdTalent.Owner = hero
        createdTalent.ParentTalentSets.add(0, hero.TalentSets[0].id)
        createdTalent.defaultForHero = hero
        hero.TalentSets[0].TalentSetCrc = -1
        env.acc.model.checkHeroesDefaultTalentSet(env.I.WS, env.acc)
        assert not env.acc.model.UserInventory.get(createdTalent.getID())
        assert not hero.TalentSets[0].Talents.get(12)

    def checkCheckHeroesDefaultTalentSet_badLevelTalent(self, env):
        hero = next(h for h in env.acc.model.Heroes.values() if h.PersistentId == crc32('firefox'))
        classTalent = next(t for t in env.acc.model.UserInventory.values() if t.PersistentId == crc32('Firefox_A1'))
        hero.TalentSets[0].Talents.remove(1)
        hero.TalentSets[0].Talents[35] = classTalent.id
        hero.TalentSets[0].TalentSetCrc = -1
        env.acc.model.checkHeroesDefaultTalentSet(env.I.WS, env.acc)
        assert not env.acc.model.getTalentByID(hero.TalentSets[0].Talents.get(35))

    def checkCheckHeroesDefaultTalentSet_noClassTalent(self, env):
        hero = next(h for h in env.acc.model.Heroes.values() if h.PersistentId == crc32('firefox'))
        classTalent = next(t for t in env.acc.model.UserInventory.values() if t.PersistentId == crc32('Firefox_A1'))
        env.acc.model.UserInventory.remove(classTalent)
        hero.TalentSets[0].TalentSetCrc = -1
        env.acc.model.checkHeroesDefaultTalentSet(env.I.WS, env.acc)
        classTalent = next(t for t in env.acc.model.UserInventory.values() if t.PersistentId == crc32('Firefox_A1'))  # по сути и есть ассерт
        assert classTalent
