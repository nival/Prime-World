# -*- coding: utf-8 -*-
from subaction import *

# PF-86261
class ReplaceFirefoxTalents:
  def convertModelData(self, env, acc, md, idict):
    for heroId in md.HeroesKeeper:
      hero = md.getHeroByID(heroId)
      staticHero = acc.SD.getStaticHero(hero)
      if staticHero['persistentId'] == 'firefox':
        self.checkForTalentInTS(md, hero, crc32('G110'), 19)
        self.checkForTalentInTS(md, hero, crc32('Firefox_A2'), 20)
    return md, acc.db

  def checkForTalentInTS(self, md, hero, persistentId, defaultPos):
    # сначала проверим, есть ли нужные таланты в талантсете
    for slotId in hero.TalentSets[0].Talents.keys():
      talent = md.getTalentByID(hero.TalentSets[0].Talents.get(slotId))
      if talent and talent.PersistentId == persistentId:
        # Если талант итак на своём месте, ничего не делаем
        if slotId == defaultPos:
          return
        # Вынимаем найденный талант
        hero.removeTalentFromTalentSet(0, talent, talent.getID())
        # Если на дефолтной позиции что-то лежит, вынем и положим в освободившийся слот
        tmpTalId = hero.TalentSets[0].Talents.get(defaultPos)
        tmpTal = md.getTalentByID(tmpTalId)
        if tmpTal != None:
          hero.removeTalentFromTalentSet(0, tmpTal, tmpTalId)
          hero.TalentSets[0].Talents.add(slotId, tmpTal)
        # Положим нужный талант на своё место
        hero.TalentSets[0].Talents.add(defaultPos, talent)
        return

    for talId in md.UserInventory:
      talent = md.getTalentByID(talId)
      if talent.PersistentId == persistentId and talent.defaultForHero == hero:
        talent.Soulbound = hero
        self.switchTalents(md, hero, talent, defaultPos)
        return
    # Таланта не нашли, добавим его сами
    talent_id = md.addNewTalent()
    talent = md.getTalentByID(talent_id)
    talent.IsNew = True
    talent.PersistentId = persistentId
    talent.defaultForHero = hero
    talent.Soulbound = hero
    md.UserInventory.add(talent_id)
    self.switchTalents(md, hero, talent, defaultPos)


  def switchTalents(self, md, hero, talent, defaultPos):
      tmpTalId = hero.TalentSets[0].Talents.get(defaultPos)
      tmpTal = md.getTalentByID(tmpTalId)
      if tmpTal:
        hero.removeTalentFromTalentSet(0, tmpTal, tmpTalId)
      hero.TalentSets[0].Talents.add(defaultPos, talent)