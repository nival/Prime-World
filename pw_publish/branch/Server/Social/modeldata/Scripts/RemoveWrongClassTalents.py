# -*- coding: utf-8 -*-
from subaction import *

class RemoveWrongClassTalents:
  def convertModelData(self, env, acc, md, idict):
    wrongTalents = []
    talentsToRemove = []
    for heroId in md.HeroesKeeper:
      hero = md.getHeroByID(heroId)
      hero_talents = md.getHeroClassTalents(acc.getConfig(), hero.PersistentId, acc.SD)
      # Для каждого вставленного таланта смотрим, в того ли героя он вставлен

      for talId in hero.TalentSet.keys():
        talent = hero.TalentSet.get(talId)
        staticTalent = acc.SD.getStaticTalent(talent)
        if staticTalent:
          if staticTalent['rarity'] == "Class":
            if staticTalent['persistentId'] not in hero_talents:
              if talent.defaultForHero.get():
                talent.Soulbound = talent.defaultForHero.getID()
              else:
                talent.Soulbound = IGuidGenerator.InvalidUID
              md.UserInventory.add(talent)
              hero.TalentSet.remove(talId)
              # Проверяем, сколько неправильных талантов
              wrongTalents.append(talent.PersistentId)
        # Если у нас даже staticTalent отсутствует, то вообще удаляем такие таланты
        else:
          hero.TalentSet.remove(talId)
          talentsToRemove.append(talId)

    # Теперь уберём лишние классовые таланты, если таковые нашлись
    mdTalents = []
    for talPersistentId in wrongTalents:
      for talId in md.ItemsKeeper:
        talent = md.getTalentByID(talId)
        if talent.PersistentId == talPersistentId:
          if talPersistentId in mdTalents:
            talentsToRemove.append(talent.getID())
          else:
            mdTalents.append(talPersistentId)

    for talId in talentsToRemove:
      md.ItemsKeeper.remove(talId)

    return md, acc.db