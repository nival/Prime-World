# -*- coding: utf-8 -*-
from base.helpers import *
from binascii import crc32

class RevertTutorialQuests:
  def convertModelData( self, acc, SD, config, stats ):
    info("RevertTutorialQuestsEvent: auid=%r" % acc.db.auid)
    md = acc.model
    questsToAdd = []
    questsToRemove = []
    if acc.country_code == 'US' and config.ALTERNATIVE_QUESTS:
      # Поменяем квесты обратно
      if md.LordInfo.TurtorialVersion == 1:
        md.LordInfo.TurtorialVersion = 0
        for questId in md.ActiveQuests:
          quest = md.getQuestByID(questId)
          staticQuest = SD.getStaticQuest(quest)
          if staticQuest and staticQuest['persistentId']:
            for questKey in config.ALTERNATIVE_QUESTS:
              alternativeQuestsSet = json.loads(config.ALTERNATIVE_QUESTS[questKey])
              for questId in alternativeQuestsSet:
                if questId == staticQuest['persistentId']:
                  if questKey not in questsToAdd:
                    questsToAdd.append(questKey)
                  questsToRemove.append(staticQuest['persistentId'])

        # Убираем квесты, которые нашли у игроков
        for questId in questsToRemove:
          staticQuest = SD.getStaticQuestById(crc32(questId))
          md.removeQuest(staticQuest)

        # Выдаём альтернативные квесты
        for questId in questsToAdd:
          staticQuest = SD.getStaticQuestById(crc32(questId))
          quest = md.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, stats, acc )

    return acc.model
